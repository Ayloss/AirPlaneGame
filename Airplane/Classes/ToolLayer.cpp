#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "ToolLayer.h"

USING_NS_CC;

#define TOOL_MOVE_SPEED 400 //�����ƶ��ٶ�pixel/s

ToolLayer* ToolLayer::sharedToolLayer = NULL;
bool ToolLayer::init()
{
	if (!Layer::init())
		return false;

	rootNode = CSLoader::createNode("ToolLayer.csb");
	addChild(rootNode);

	schedule(schedule_selector(ToolLayer::createTool),15);

	return true;
}

ToolLayer* ToolLayer::create()
{
	ToolLayer *pRet = new ToolLayer;
	if (pRet &&pRet->init())
	{
		pRet->autorelease();
		sharedToolLayer = pRet;
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}

ToolLayer::ToolLayer()
{
	tool = new Vector<Sprite *>;
}


ToolLayer::~ToolLayer()
{
	tool->clear();
	tool->~Vector();
}

void ToolLayer::createTool(float dt)
{
	auto winSize = Director::sharedDirector()->getWinSize();
	Sprite* temp;
	//�������һ�ֵ���
	if (rand() % 2 == 0)
	{
		temp = Sprite::create("./ui/shoot/ufo1.png");
		temp->setTag(0);//���ñ�ǩ,�ͷɻ�������ײʱ�жϵ��ߵ�����
	}
	else
	{
		temp = Sprite::create("./ui/shoot/ufo2.png");
		temp->setTag(1);
	}
	tool->pushBack(temp);
	rootNode->addChild(temp);

	//������ߵĳ�ʼλ��
	float x = temp->getContentSize().width / 2 + rand() % (int)(winSize.width - temp->getContentSize().width);
	float y = winSize.height + temp->getContentSize().height / 2;
	float Y = -temp->getContentSize().height / 2;
	temp->setPosition(ccp(x, y));

	//���õ��ߵ��˶�
	temp->runAction(Sequence::create(MoveTo::create((winSize.height + temp->getContentSize().height) / TOOL_MOVE_SPEED, ccp(x, Y)),
		CallFuncN::create(CC_CALLBACK_0(ToolLayer::toolDisappear, this, temp)),
		NULL));

}

void ToolLayer::toolDisappear(Node* pSender)
{
	pSender->removeFromParentAndCleanup(true);
	tool->eraseObject((Sprite*)pSender);
}
cocos2d::Vector<Sprite*>* ToolLayer::getTool()
{
	return tool;
}
