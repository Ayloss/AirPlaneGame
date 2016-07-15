#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "PlaneLayer.h"

USING_NS_CC;

#define MOVE_INTERVAL 0.01
#define DISTANCE_PER_MOVE 4//飞机每次移动的距离

PlaneLayer* PlaneLayer::sharedPlaneLayer = NULL;
bool PlaneLayer::init()
{
	if (!Layer::init())
		return false;

	//加载主角飞机层
	rootNode = CSLoader::createNode("PlaneLayer.csb");
	addChild(rootNode);

	//找到主角飞机节点
	heroPlane = (Sprite*)rootNode->getChildByName("heroPlane");

	//加载主角飞机动画
	setAnimation();

	//键盘监听事件,控制飞机移动
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->setEnabled(true);
	keyboardListener->onKeyPressed = CC_CALLBACK_2(PlaneLayer::movePlaneBegin, this);//键盘按下,设定移动的定时器
	keyboardListener->onKeyReleased = CC_CALLBACK_2(PlaneLayer::movePlaneEnd, this);//键盘松开,卸载之前设立的定时器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, heroPlane);

	return true;
}

PlaneLayer* PlaneLayer::create()
{
	PlaneLayer *pRet = new PlaneLayer;
	if (pRet &&pRet->init())
	{
		pRet->autorelease();
		sharedPlaneLayer = pRet;
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}

PlaneLayer::PlaneLayer()
{
}


PlaneLayer::~PlaneLayer()
{
}

cocos2d::Sprite* PlaneLayer::shareHeroPlane()
{
	return heroPlane;
}

void PlaneLayer::movePlaneBegin(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_CAPITAL_W:
	case EventKeyboard::KeyCode::KEY_W:
	{
		schedule(schedule_selector(PlaneLayer::moveUp), MOVE_INTERVAL);
		break;
	}
	case EventKeyboard::KeyCode::KEY_CAPITAL_S:
	case EventKeyboard::KeyCode::KEY_S:
	{
		schedule(schedule_selector(PlaneLayer::moveDown), MOVE_INTERVAL);
		break;
	}
	case EventKeyboard::KeyCode::KEY_CAPITAL_A:
	case EventKeyboard::KeyCode::KEY_A:
	{
		schedule(schedule_selector(PlaneLayer::moveLeft), MOVE_INTERVAL);
		break;
	}

	case EventKeyboard::KeyCode::KEY_CAPITAL_D:
	case EventKeyboard::KeyCode::KEY_D:
	{
		schedule(schedule_selector(PlaneLayer::moveRight), MOVE_INTERVAL);
		break;
	}
	}
}
void PlaneLayer::movePlaneEnd(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_CAPITAL_W:
	case EventKeyboard::KeyCode::KEY_W:
	{
		unschedule(schedule_selector(PlaneLayer::moveUp));
		break;
	}
	case EventKeyboard::KeyCode::KEY_CAPITAL_S:
	case EventKeyboard::KeyCode::KEY_S:
	{
		unschedule(schedule_selector(PlaneLayer::moveDown));
		break;
	}
	case EventKeyboard::KeyCode::KEY_CAPITAL_A:
	case EventKeyboard::KeyCode::KEY_A:
	{
		unschedule(schedule_selector(PlaneLayer::moveLeft));
		break;
	}

	case EventKeyboard::KeyCode::KEY_CAPITAL_D:
	case EventKeyboard::KeyCode::KEY_D:
	{
		unschedule(schedule_selector(PlaneLayer::moveRight));
		break;
	}
	}
}

void PlaneLayer::moveUp(float dt)
{
	if (heroPlane->getPositionY() <
		Director::sharedDirector()->getWinSize().height
		- heroPlane->getContentSize().height)
		heroPlane->setPosition(ccp(heroPlane->getPosition().x, heroPlane->getPosition().y + DISTANCE_PER_MOVE));
}


void PlaneLayer::moveDown(float dt)
{
	if (heroPlane->getPositionY() >= 0)
		heroPlane->setPosition(ccp(heroPlane->getPosition().x, heroPlane->getPosition().y - DISTANCE_PER_MOVE));
}

void PlaneLayer::moveLeft(float dt)
{
	if (heroPlane->getPositionX() >= -heroPlane->getContentSize().width / 2 + 5)
		heroPlane->setPosition(ccp(heroPlane->getPosition().x - DISTANCE_PER_MOVE, heroPlane->getPosition().y));
}

void PlaneLayer::moveRight(float dt)
{
	if (heroPlane->getPositionX() <=
		Director::sharedDirector()->getWinSize().width
		- heroPlane->getContentSize().width / 2 - 5)
		heroPlane->setPosition(ccp(heroPlane->getPosition().x + DISTANCE_PER_MOVE, heroPlane->getPosition().y));
}

void PlaneLayer::setAnimation()
{
	Animation* animation = Animation::create();

	animation = AnimationCache::getInstance()->getAnimation("heroAlive");
	animation->setDelayPerUnit(0.1);
	Animate* animate = Animate::create(animation);
	heroPlane->runAction(RepeatForever::create(animate));

	

}

void PlaneLayer::removeAllListenersAndActions()
{
	_eventDispatcher->removeAllEventListeners();
	unscheduleAllSelectors();
	heroPlane->stopAllActions();
	
}

