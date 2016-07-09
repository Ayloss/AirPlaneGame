#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "DifficultyControl.h"
#include "EnemyLayer.h"
#include "Enemy.h"
USING_NS_CC;

EnemyLayer* EnemyLayer::sharedEnemyLayer = NULL;

bool EnemyLayer::init()
{
	if (!Layer::init())
		return false;

	rootNode = CSLoader::createNode("EnemyLayer.csb");
	addChild(rootNode);
	
	//创建产生敌人定时器
	schedule(schedule_selector(EnemyLayer::createEnemy1), ENEMY1_CREATE_INTERVAL_BASE);
	schedule(schedule_selector(EnemyLayer::createEnemy2), ENEMY2_CREATE_INTERVAL_BASE);
	schedule(schedule_selector(EnemyLayer::createEnemy3), ENEMY3_CRAETE_INTERVAL_BASE);

	return true;
}

EnemyLayer* EnemyLayer::create()
{
	EnemyLayer *pRet = new EnemyLayer;
	if (pRet &&pRet->init())
	{
		pRet->autorelease();
		sharedEnemyLayer = pRet;
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}

EnemyLayer::EnemyLayer()
{
	enemies = new Vector<Enemy *>;
}


EnemyLayer::~EnemyLayer()
{
	enemies->clear();
	enemies->~Vector();
}

void EnemyLayer::addEnemy(EnemyType type)
{
	Enemy* enemy = Enemy::create(type);
	rootNode->addChild(enemy);
	enemy->setAnimation();
	enemies->pushBack(enemy);

	auto winHeight = Director::sharedDirector()->getWinSize().height;
	auto winWidth = Director::sharedDirector()->getWinSize().width;

	auto enemyHeight = enemy->getContentSize().height;
	auto enemyWidth = enemy->getContentSize().width;

	//计算敌机的初始位置
	float x = rand() % (int)(winWidth);
	float y = winHeight + enemyHeight / 2;
	float Y = -enemyHeight / 2;

	enemy->setPosition(ccp(x, y));
	enemy->runAction(Sequence::create(MoveTo::create((y - Y) / enemy->getSpeed(), ccp(x, Y)),
		CallFuncN::create((CC_CALLBACK_0(EnemyLayer::enemyDisappear, this, enemy))),
		NULL));
}

void EnemyLayer::createEnemy1(float dt)
{
	addEnemy(little);
	//难度系数更改时
	float newDt = ENEMY1_CREATE_INTERVAL_BASE / (1 + difficultyLevel / (difficultyLevel + 1));
	if(dt - newDt>1e-6)
	{
		unschedule(schedule_selector(EnemyLayer::createEnemy1));
		schedule(schedule_selector(EnemyLayer::createEnemy1), newDt);
	}
}

void EnemyLayer::createEnemy2(float dt)
{
	addEnemy(middle);
	float newDt = ENEMY2_CREATE_INTERVAL_BASE / (1 + difficultyLevel / (difficultyLevel + 1));
	if (dt - newDt>1e-6)
	{
		unschedule(schedule_selector(EnemyLayer::createEnemy2));
		schedule(schedule_selector(EnemyLayer::createEnemy2), newDt);
	}
}

void EnemyLayer::createEnemy3(float dt)
{
	addEnemy(large);
	float newDt = ENEMY3_CRAETE_INTERVAL_BASE / (1 + difficultyLevel / (difficultyLevel + 1));
	if (dt-newDt>1e-6)
	{
		unschedule(schedule_selector(EnemyLayer::createEnemy2));
		schedule(schedule_selector(EnemyLayer::createEnemy2), newDt);
	}
}

void EnemyLayer::enemyDisappear(Node *pSender)
{
	pSender->removeFromParentAndCleanup(true);
	enemies->eraseObject((Enemy*)pSender);
}

int EnemyLayer::destroyEverything()
{
	int score = 0;
	for (auto &i : *enemies)
	{
		i->destoryed();
		score += i->getScore();
	}
	enemies->clear();
	return score;
}

cocos2d::Vector<Enemy*>* EnemyLayer::getEnemies()
{
	return enemies;
}
