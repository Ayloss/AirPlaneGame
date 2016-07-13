#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MainScene.h"
#include "DifficultyControl.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;

#define DISTANCE_BG_PERMOVE 2//背景每一次滚动的距离

extern float difficultyLevel = 0;

MainScene::MainScene()
{
}


MainScene::~MainScene()
{
}

bool MainScene::init()
{
	if (!Scene::init())
		return false;
	//播放bgm
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("./sound/game_music.wav", true);
	
	//初始设置难度等级为0
	difficultyLevel = 0;

	rootNode = CSLoader::createNode("MainScene.csb");
	addChild(rootNode);

	//设置背景滚动
	bg1 = rootNode->getChildByName("bg1");
	bg2 = rootNode->getChildByName("bg2");
	schedule(schedule_selector(MainScene::bgMove), 0.04);

	planeLayer = PlaneLayer::create();
	bulletLayer = BulletLayer::create();
	toolLayer = ToolLayer::create();
	controlLayer = ControlLayer::create();
	enemyLayer = EnemyLayer::create();

	//设置层的叠放次序
	bulletLayer->setZOrder(toolLayer->getZOrder() + 1);
	enemyLayer->setZOrder(bulletLayer->getZOrder() + 1);
	planeLayer->setZOrder(bulletLayer->getZOrder() + 1);
	controlLayer->setZOrder(planeLayer->getZOrder() + 1);

	rootNode->addChild(planeLayer);
	rootNode->addChild(bulletLayer);
	rootNode->addChild(toolLayer);
	rootNode->addChild(controlLayer);
	rootNode->addChild(enemyLayer);

	bulletLayer->startShooting();

	//监听是否使用炸弹
	auto bombUseListener = EventListenerKeyboard::create();
	bombUseListener->onKeyPressed = CC_CALLBACK_2(MainScene::useBomb, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(bombUseListener, this);

	//设置帧刷新定时器
	schedule(schedule_selector(MainScene::update));
	//bulletLayer->getSpecialBullet();

	return true;
}

void MainScene::bgMove(float dt)
{
	//背景到底,重设位置再最上方
	if (bg1->getPositionY() == -852)
	{
		bg1->setPosition(ccp(0, 852));
	}
	if (bg2->getPositionY() == -852)
	{
		bg2->setPosition(ccp(0, 852));
	}
	//背景y坐标减少
	bg1->setPosition(ccp(0, bg1->getPositionY() - DISTANCE_BG_PERMOVE));
	bg2->setPosition(ccp(0, bg2->getPositionY() - DISTANCE_BG_PERMOVE));
}

void MainScene::useBomb(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_Q:
	case EventKeyboard::KeyCode::KEY_CAPITAL_Q:
	{
		if (controlLayer->getBombNum() > 0)
		{
			//炸弹数减一
			controlLayer->bombNumDecrease();
			//播放全屏爆炸动画

			//所有敌机消失获得分数
			controlLayer->scoreIncrease(enemyLayer->destroyEverything());
		}
		break;
	}
	}
}

void MainScene::collisionDetectionForToolAndHero()
{
	Vector<Sprite*> toolToDelete;
	auto tool = toolLayer->getTool();
	auto hero = planeLayer->shareHeroPlane();
	//遍历道具数组
	for (auto &i : *tool)
	{
		//发生碰撞
		if (i->getBoundingBox().intersectsRect(hero->getBoundingBox()))
		{
			toolToDelete.pushBack(i);
			//判断道具的类型,加入删除的道具数组
			switch (i->getTag())
			{
			case 0:
			{
				bulletLayer->getSpecialBullets();
				break;
			}
			case 1:
			{
				controlLayer->bombNumIncrease();
				break;
			}
			}
		}
	}
	//删除道具
	for (auto &i : toolToDelete)
	{
		tool->eraseObject(i);
		i->removeFromParentAndCleanup(true);
	}
}

void MainScene::collisionDetectionForBulletAndEnemy()
{
	Vector<Sprite*> *bullets, bulletsToDelete;
	Vector<Enemy*> *enemies, enemiesToDelete;
	bullets = bulletLayer->getAllBullets();
	enemies = enemyLayer->getEnemies();
	//遍历子弹数组与敌机数组
	for (auto &j : *enemies)
	{
		for (auto &i : *bullets)
		{
			//发生碰撞
			if (i->getBoundingBox().intersectsRect(j->getBoundingBox()))
			{
				//敌机扣血
				j->getHurt();
				//子弹加入被删除的子弹数组
				bulletsToDelete.pushBack(i);
			}
			//敌机血扣光
			if (j->getLife() == 0)
			{
				//加入被删除的敌机数组
				enemiesToDelete.pushBack(j);
				//增加分数
				controlLayer->scoreIncrease(j->getScore());
				break;
			}
		}
	}

	//删除子弹和敌机
	for (auto &i : bulletsToDelete)
	{
		bullets->eraseObject(i);
		i->removeFromParentAndCleanup(true);
	}
	for (auto *j : enemiesToDelete)
	{
		enemies->eraseObject(j);
		j->destoryed();
	}

}

void MainScene::collisionDetectionForEnemyAndHero()
{
	Sprite* hero = planeLayer->shareHeroPlane();
	Vector<Enemy*> *enemies = enemyLayer->getEnemies();

	//遍历敌机数组
	for (auto &i : *enemies)
	{
		//敌机仍旧存活且与主角发生碰撞,结束游戏
		if (i->getLife() > 0 && i->getBoundingBox().intersectsRect(hero->getBoundingBox()))
		{
			gameOver();
			break;
		}
	}
}

void MainScene::update(float delta)
{
	collisionDetectionForToolAndHero();
	collisionDetectionForBulletAndEnemy();
	collisionDetectionForEnemyAndHero();
}

void MainScene::gameOver()
{
	//停用飞机的所有动作和控制
	planeLayer->removeAllListenersAndActions();
	//停用所有事件监听
	_eventDispatcher->removeAllEventListeners();
	//取消检测碰撞的定时器
	unschedule(schedule_selector(MainScene::update));
	//主角飞机爆炸动画
	Animation* animation = Animation::create();
	animation = AnimationCache::getInstance()->getAnimation("heroDead");
	animation->setDelayPerUnit(0.2);
	animation->setLoops(1);
	Animate* animate = Animate::create(animation);
	//停止射击子弹
	bulletLayer->stopShooting();
	//分数转成字符串,传入下一场景
	char temp[20] = { 0 };
	sprintf(temp, "%d", controlLayer->getScore());
	std::string finalScore;
	finalScore = temp;
	//运行主角飞机爆炸动画,运行完毕后移除飞机层,跳转到结束场景
	planeLayer->shareHeroPlane()->runAction(Sequence::create(animate
		, CallFuncN::create(CC_CALLBACK_0(MainScene::removeChild, this, planeLayer, true))
		, CallFuncN::create(CC_CALLBACK_0(MainScene::endGame, this, finalScore))
		, NULL));
}

void MainScene::endGame(std::string &finalScore)
{
	tsm->gotoGameOverScene(finalScore);
}
