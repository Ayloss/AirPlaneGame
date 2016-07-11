#include "GameOverScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace ui;


GameOverScene::GameOverScene()
{
}


GameOverScene::~GameOverScene()
{
}

bool GameOverScene::init()
{
	if (!Scene::init())
		return false;

	rootNode = CSLoader::createNode("GameOverScene.csb");
	addChild(rootNode);
	//������Ϸ������Ч
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./sound/game_over.wav");

	//��ӷ��ذ�ť����¼�
	auto goBackButton = dynamic_cast<Button*>(rootNode->getChildByName("goBack"));
	goBackButton->addTouchEventListener(CC_CALLBACK_2(GameOverScene::goBackGame, this));

	return true;
}

void GameOverScene::goBackGame(Ref *pSender, Widget::TouchEventType type)
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
		tsm->gotoMainScene();
		break;
	}
	}
}

void GameOverScene::setFinalScore(std::string score)
{
	auto finalScoreBox = dynamic_cast<TextBMFont*>(rootNode->getChildByName("finalScore"));
	finalScoreBox->setText(score);
}
void GameOverScene::getHighScore()
{
	int highScore = 0;
	//δ���������ļ�,�����������ļ�
	if (!UserDefault::sharedUserDefault()->getBoolForKey("isHaveSaveFileXml"))
	{
		UserDefault::sharedUserDefault()->setBoolForKey("isHaveSaveFileXml", true);
		UserDefault::sharedUserDefault()->setIntegerForKey("highScore", 0);
		UserDefault::sharedUserDefault()->flush();
		
	}
	//���������ļ�,��ȡ��߷�
	else
	{
		CCLOG("%s", UserDefault::sharedUserDefault()->getXMLFilePath());
		highScore = UserDefault::sharedUserDefault()->getIntegerForKey("highScore");
	}

	auto finalScoreBox = dynamic_cast<TextBMFont*>(rootNode->getChildByName("finalScore"));
	auto highScoreBox = dynamic_cast<TextBMFont*>(rootNode->getChildByName("highScore"));
	int finalScore = atoi(finalScoreBox->getString().c_str());

	//Ŀǰ����������߷�ʱ,������߷�
	if(highScore<finalScore)
	{
		//���Ż�óɾ���Ч
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./sound/achievement.wav");

		highScore = finalScore;

		UserDefault::sharedUserDefault()->setIntegerForKey("highScore", highScore);
		UserDefault::sharedUserDefault()->flush();
	}
	highScoreBox->setString(String::createWithFormat("%d", highScore)->getCString());
}