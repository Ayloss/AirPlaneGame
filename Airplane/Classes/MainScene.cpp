#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MainScene.h"
#include "DifficultyControl.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;

#define DISTANCE_BG_PERMOVE 2//����ÿһ�ι����ľ���

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
	//����bgm
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("./sound/game_music.wav", true);
	
	//��ʼ�����Ѷȵȼ�Ϊ0
	difficultyLevel = 0;

	rootNode = CSLoader::createNode("MainScene.csb");
	addChild(rootNode);

	//���ñ�������
	bg1 = rootNode->getChildByName("bg1");
	bg2 = rootNode->getChildByName("bg2");
	schedule(schedule_selector(MainScene::bgMove), 0.04);

	planeLayer = PlaneLayer::create();
	bulletLayer = BulletLayer::create();
	toolLayer = ToolLayer::create();
	controlLayer = ControlLayer::create();
	enemyLayer = EnemyLayer::create();

	//���ò�ĵ��Ŵ���
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

	//�����Ƿ�ʹ��ը��
	auto bombUseListener = EventListenerKeyboard::create();
	bombUseListener->onKeyPressed = CC_CALLBACK_2(MainScene::useBomb, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(bombUseListener, this);

	//����֡ˢ�¶�ʱ��
	schedule(schedule_selector(MainScene::update));
	//bulletLayer->getSpecialBullet();

	return true;
}

void MainScene::bgMove(float dt)
{
	//��������,����λ�������Ϸ�
	if (bg1->getPositionY() == -852)
	{
		bg1->setPosition(ccp(0, 852));
	}
	if (bg2->getPositionY() == -852)
	{
		bg2->setPosition(ccp(0, 852));
	}
	//����y�������
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
			//ը������һ
			controlLayer->bombNumDecrease();
			//����ȫ����ը����

			//���ел���ʧ��÷���
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
	//������������
	for (auto &i : *tool)
	{
		//������ײ
		if (i->getBoundingBox().intersectsRect(hero->getBoundingBox()))
		{
			toolToDelete.pushBack(i);
			//�жϵ��ߵ�����,����ɾ���ĵ�������
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
	//ɾ������
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
	//�����ӵ�������л�����
	for (auto &j : *enemies)
	{
		for (auto &i : *bullets)
		{
			//������ײ
			if (i->getBoundingBox().intersectsRect(j->getBoundingBox()))
			{
				//�л���Ѫ
				j->getHurt();
				//�ӵ����뱻ɾ�����ӵ�����
				bulletsToDelete.pushBack(i);
			}
			//�л�Ѫ�۹�
			if (j->getLife() == 0)
			{
				//���뱻ɾ���ĵл�����
				enemiesToDelete.pushBack(j);
				//���ӷ���
				controlLayer->scoreIncrease(j->getScore());
				break;
			}
		}
	}

	//ɾ���ӵ��͵л�
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

	//�����л�����
	for (auto &i : *enemies)
	{
		//�л��Ծɴ���������Ƿ�����ײ,������Ϸ
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
	//ͣ�÷ɻ������ж����Ϳ���
	planeLayer->removeAllListenersAndActions();
	//ͣ�������¼�����
	_eventDispatcher->removeAllEventListeners();
	//ȡ�������ײ�Ķ�ʱ��
	unschedule(schedule_selector(MainScene::update));
	//���Ƿɻ���ը����
	Animation* animation = Animation::create();
	animation = AnimationCache::getInstance()->getAnimation("heroDead");
	animation->setDelayPerUnit(0.2);
	animation->setLoops(1);
	Animate* animate = Animate::create(animation);
	//ֹͣ����ӵ�
	bulletLayer->stopShooting();
	//����ת���ַ���,������һ����
	char temp[20] = { 0 };
	sprintf(temp, "%d", controlLayer->getScore());
	std::string finalScore;
	finalScore = temp;
	//�������Ƿɻ���ը����,������Ϻ��Ƴ��ɻ���,��ת����������
	planeLayer->shareHeroPlane()->runAction(Sequence::create(animate
		, CallFuncN::create(CC_CALLBACK_0(MainScene::removeChild, this, planeLayer, true))
		, CallFuncN::create(CC_CALLBACK_0(MainScene::endGame, this, finalScore))
		, NULL));
}

void MainScene::endGame(std::string &finalScore)
{
	tsm->gotoGameOverScene(finalScore);
}
