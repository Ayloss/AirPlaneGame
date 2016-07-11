#include "BulletLayer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#define  BULLET_SPEED 500//�ӵ������ٶ� pixel/s
#define BULLET_NUM_PER_SECOND 5.0//ÿ���ӵ��ӵ���
USING_NS_CC;

BulletLayer* BulletLayer::sharedBulletLayer = NULL;
bool BulletLayer::init()
{
	if (!Layer::init())
		return false;

	rootNode = CSLoader::createNode("BulletLayer.csb");
	addChild(rootNode);

	return true;
}

BulletLayer* BulletLayer::create()
{
	BulletLayer *pRet = new BulletLayer;
	if (pRet &&pRet->init())
	{
		pRet->autorelease();
		sharedBulletLayer = pRet;
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}

BulletLayer::BulletLayer()
{
	allBullets = new Vector<Sprite*>;
	specialBullets = 0;
}


BulletLayer::~BulletLayer()
{
	allBullets->clear();
	allBullets->~Vector();
}

cocos2d::Vector<Sprite*>* BulletLayer::getAllBullets()
{
	return allBullets;
}

void BulletLayer::bulletCreate(float dt)
{
	Sprite *pHeroPlane = PlaneLayer::sharedPlaneLayer->shareHeroPlane();
	float heroPlaneWidth = pHeroPlane->getContentSize().width;
	float heroPlaneHeight = pHeroPlane->getContentSize().height;
	float winHeight = Director::sharedDirector()->getWinSize().height;

	//�����ӵ���Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./sound/bullet.wav");
	//������ͨ�ӵ�
	if (specialBullets == 0)
	{
		Sprite *oneBullet = Sprite::create("./ui/shoot/bullet1.png");
		rootNode->addChild(oneBullet);
		allBullets->pushBack(oneBullet);

		//�����ӵ����е���Ϣ
		float x = pHeroPlane->getPositionX()+heroPlaneWidth/2;//x��λ��
		float y = pHeroPlane->getPositionY() + heroPlaneHeight;//���y��λ��
		float Y = winHeight + oneBullet->getContentSize().height;//�յ�y��λ��
		float flyTime = (winHeight -y ) / BULLET_SPEED;//�����ӵ�����ʱ��
		//�����ӵ��ĳ�ʼλ��
		oneBullet->setPosition(ccp(x, y));
		//�����ӵ����еĶ���
		oneBullet->runAction(Sequence::create(MoveTo::create(flyTime, ccp(x, Y)), CallFuncN::create(CC_CALLBACK_0(BulletLayer::bulletDisappear, this, oneBullet)), NULL));
	}
	//���������ӵ�
	else if (specialBullets > 0)
	{
		Sprite *leftBullet = Sprite::create("./ui/shoot/bullet2.png");
		Sprite *rightBullet = Sprite::create("./ui/shoot/bullet2.png");
		rootNode->addChild(leftBullet);
		rootNode->addChild(rightBullet);
		allBullets->pushBack(leftBullet);
		allBullets->pushBack(rightBullet);


		float x1 = pHeroPlane->getPositionX() - 32+heroPlaneWidth/2;//����ӵ���x������
		float x2 = pHeroPlane->getPositionX() + 32+heroPlaneWidth/2;//�ұ��ӵ���y������
		float y = pHeroPlane->getPositionY() + 25+heroPlaneHeight/2;//���y��λ��
		float Y = winHeight + leftBullet->getContentSize().height;//�յ�y��λ��
		float flyTime = (winHeight-y) / BULLET_SPEED;

		leftBullet->setPosition(ccp(x1, y));
		rightBullet->setPosition(ccp(x2, y));

		leftBullet->runAction(Sequence::create(MoveTo::create(flyTime, ccp(x1, Y)), CallFuncN::create(CC_CALLBACK_0(BulletLayer::bulletDisappear, this, leftBullet)), NULL));
		rightBullet->runAction(Sequence::create(MoveTo::create(flyTime, ccp(x2, Y)), CallFuncN::create(CC_CALLBACK_0(BulletLayer::bulletDisappear, this, rightBullet)), NULL));

		specialBullets--;//�����ӵ�����һ
	}
}

void BulletLayer::bulletDisappear(Node* pSender)
{
	if (pSender != NULL)
	{
		allBullets->eraseObject((Sprite*)pSender);
		pSender->removeFromParentAndCleanup(true);
	}
}

void BulletLayer::startShooting()
{
	schedule(schedule_selector(BulletLayer::bulletCreate), 1.0 / BULLET_NUM_PER_SECOND);
}

void BulletLayer::stopShooting()
{
	unschedule(schedule_selector(BulletLayer::bulletCreate));
}

void BulletLayer::getSpecialBullets()
{
	//���Ż�������ӵ���Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./sound/get_double_laser.wav");
	specialBullets += 30;
}
