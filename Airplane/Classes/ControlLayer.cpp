#include "cstring"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"
#include "ControlLayer.h"
#include "PlaneLayer.h"
#include "DifficultyControl.h"

USING_NS_CC;
using namespace ui;

ControlLayer* ControlLayer::sharedControlLayer = NULL;

bool ControlLayer::init()
{
	if (!Layer::init())
		return false;

	rootNode = CSLoader::createNode("ControlLayer.csb");
	addChild(rootNode);

	//��ȡ���ư�ť,������,ը��������
	gameControlButton = dynamic_cast<Button*>(rootNode->getChildByName("gameControl"));
	bombNumBox = dynamic_cast<TextBMFont*>(rootNode->getChildByName("bombNum"));
	scoreBox = dynamic_cast<TextBMFont*>(rootNode->getChildByName("score"));
	//�����ͣ��ť�ļ����¼�
	gameControlButton->addTouchEventListener(CC_CALLBACK_2(ControlLayer::menuCallBack, this));

	return true;
}

ControlLayer* ControlLayer::create()
{
	ControlLayer *pRet = new ControlLayer;
	if (pRet &&pRet->init())
	{
		pRet->autorelease();
		sharedControlLayer = pRet;
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}

ControlLayer::ControlLayer()
{
	bombNum = 0;
	scoreNum = 0;
}


ControlLayer::~ControlLayer()
{
}

void ControlLayer::bombNumIncrease()
{
	//���Ż��ը����Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./sound/get_bomb.wav");

	bombNum++;
	//������ʾ��ը����
	std::string b = "X";
	bombNumBox->setText(b + String::createWithFormat("%d", bombNum)->getCString());
}

void ControlLayer::bombNumDecrease()
{
	//����ʹ��ը����Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./sound/use_bomb.wav");

	bombNum--;
	//������ʾ��ը����
	std::string b = "X";
	bombNumBox->setText(b + String::createWithFormat("%d", bombNum)->getCString());
}

int ControlLayer::getBombNum()
{
	return bombNum;
}

void ControlLayer::scoreIncrease(int score)
{
	scoreNum += score;
	//�����Ѷ�ϵ��
	difficultyLevel = scoreNum / DIFFICULTY_DEGREE;
	//���ķ���
	scoreBox->setText(String::createWithFormat("%d", scoreNum)->getCString());
}

int ControlLayer::getScore()
{
	return scoreNum;
}

void ControlLayer::menuCallBack(Ref *event, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./sound/button.wav");
		break;
	}
	case Widget::TouchEventType::ENDED:
	{
		if (!Director::sharedDirector()->isPaused())
		{
			//���İ�ť��ͼƬ
			gameControlButton->loadTextureNormal("./ui/shoot/game_resume_nor.png");
			gameControlButton->loadTexturePressed("./ui/shoot/game_resume_pressed.png");
			Director::sharedDirector()->pause();
		}
		else
		{
			gameControlButton->loadTextureNormal("./ui/shoot/game_pause_nor.png");
			gameControlButton->loadTexturePressed("./ui/shoot/game_pause_pressed.png");
			Director::sharedDirector()->resume();
		}
		break;
	}
	}
}
