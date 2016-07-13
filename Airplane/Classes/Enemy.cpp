#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "DifficultyControl.h"
#include "SimpleAudioEngine.h"
#include "Enemy.h"

USING_NS_CC;

//敌机基础数据
extern const int speedBaseValue[3] = { 100,80,50 };//基础速度
extern const int speedValueRange[3] = { 250,150,100 };//速度变化范围
extern const int scoreValue[3] = { 1000,5000,20000 };//分数
extern const int lifeValue[3] = { 1,2,3 };//生命值
static const std::string initFileName[3] = { "./ui/shoot/enemy1.png","./ui/shoot/enemy2.png","./ui/shoot/enemy3_n1.png" };//精灵初始图片

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

Enemy* Enemy::create(EnemyType type)
{
	Enemy* pRet = new Enemy;

	if (pRet&&pRet->initWithFile(initFileName[type]))
	{
		pRet->setData(type);
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

void Enemy::setData(EnemyType type)
{
	enemyType = type;

	//根据难度给不同飞机设置速度和生命
	switch (type)
	{
	case little:
	{
		life = lifeValue[type] + difficultyLevel*ENEMY1_LIFE_INCREASE_WITH_DIFFICULTY;
		speed = speedBaseValue[type] + rand() % (speedValueRange[type]) + difficultyLevel*ENEMY1_SPEED_INCREASE_WITH_DIFFICULTY;
		break;
	}
	case middle:
	{
		life = lifeValue[type] + difficultyLevel*ENEMY2_LIFE_INCREASE_WITH_DIFFICULTY;
		speed = speedBaseValue[type] + rand() % (speedValueRange[type]) + difficultyLevel*ENEMY2_SPEED_INCREASE_WITH_DIFFICULTY;
		break;
	}
	case large:
	{
		life = lifeValue[type] + difficultyLevel*ENEMY3_LIFE_INCREASE_WITH_DIFFICULTY;
		speed = speedBaseValue[type] + rand() % (speedValueRange[type]) + difficultyLevel*ENEMY3_SPEED_INCREASE_WITH_DIFFICULTY;
		break;
	}
	}
	score = scoreValue[type];
}

int Enemy::getLife()
{
	return life;
}

int Enemy::getSpeed()
{
	return speed;
}

int Enemy::getScore()
{
	return score;
}

void Enemy::getHurt()
{
	if (life > 0)
		life--;
	//创建被击动画
	Animation *animation = Animation::create();
	switch (enemyType)
	{
	case little:
		break;
	case middle:
	{
		animation = AnimationCache::getInstance()->getAnimation("enemy2Hitted");
		break;
	}
	case large:
	{
		animation = AnimationCache::getInstance()->getAnimation("enemy3Hitted");
		break;
	}
	}
	if (enemyType != little)
	{
		animation->setDelayPerUnit(0.2);
		animation->setLoops(1);
		runAction(Sequence::create(Animate::create(animation), CallFuncN::create(CC_CALLBACK_0(Enemy::recover, this)), NULL));
	}
}

void Enemy::recover()
{
	switch (enemyType)
	{
	case little:
		break;
	case middle:
	{
		//重设中型飞机贴图
		setTexture(initFileName[1]);
		break;
	}
	case large:
		break;
	}
}

void Enemy::setAnimation()
{
	switch (enemyType)
	{
	case little:
		break;
	case middle:
		break;
	case large:
	{
		//超大型飞机初始动画
		auto animation = Animation::create();
		animation = AnimationCache::getInstance()->getAnimation("enemy3Alive");
		animation->setDelayPerUnit(0.1);
		auto animate = RepeatForever::create(Animate::create(animation));
		runAction(RepeatForever::create(animate));
		break;
	}
	}
}

void Enemy::destoryed()
{
	//停用所有动作
	stopAllActions();
	//创建损毁动画并播放损毁音乐
	auto animation = Animation::create();
	switch (enemyType)
	{
	case little:
	{
		animation = AnimationCache::getInstance()->getAnimation("enemy1Down");
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./sound/enemy1_down.wav");
		break;
	}
	case middle:
	{
		animation = AnimationCache::getInstance()->getAnimation("enemy2Down");
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./sound/enemy2_down.wav");
		break;
	}
	case large:
	{
		animation = AnimationCache::getInstance()->getAnimation("enemy3Down");
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./sound/enemy3_down.wav");
		break;
	}
	}
	animation->setLoops(1);
	animation->setDelayPerUnit(0.2);
	auto animate = Animate::create(animation);

	//移动动画,损毁后继续飞行一段时间消失
	//计算坐标
	float x = getPositionX();
	float y = getPositionY();
	float Y = -getContentSize().height / 2;

	//运行继续移动的动画
	runAction(Sequence::create(MoveTo::create((y - Y) / speed, ccp(x, Y))
		, CallFuncN::create(CC_CALLBACK_0(Enemy::removeFromParentAndCleanup, this, true))
		, NULL));
	//运行损毁动画
	runAction(Sequence::create(animate
		, CallFuncN::create(CC_CALLBACK_0(Enemy::removeFromParentAndCleanup, this, true))
		, NULL));

}
