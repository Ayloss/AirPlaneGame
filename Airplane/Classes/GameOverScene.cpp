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
	//播放游戏结束音效
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./sound/game_over.wav");

	//添加返回按钮点击事件
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
	//未生成数据文件,创建新数据文件
	if (!UserDefault::sharedUserDefault()->getBoolForKey("isHaveSaveFileXml"))
	{
		UserDefault::sharedUserDefault()->setBoolForKey("isHaveSaveFileXml", true);
		UserDefault::sharedUserDefault()->setIntegerForKey("highScore", 0);
		UserDefault::sharedUserDefault()->flush();
		
	}
	//已有数据文件,读取最高分
	else
	{
		CCLOG("%s", UserDefault::sharedUserDefault()->getXMLFilePath());
		highScore = UserDefault::sharedUserDefault()->getIntegerForKey("highScore");
	}

	auto finalScoreBox = dynamic_cast<TextBMFont*>(rootNode->getChildByName("finalScore"));
	auto highScoreBox = dynamic_cast<TextBMFont*>(rootNode->getChildByName("highScore"));
	int finalScore = atoi(finalScoreBox->getString().c_str());

	//目前分数大于最高分时,更改最高分
	if(highScore<finalScore)
	{
		//播放获得成就音效
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./sound/achievement.wav");

		highScore = finalScore;

		UserDefault::sharedUserDefault()->setIntegerForKey("highScore", highScore);
		UserDefault::sharedUserDefault()->flush();
	}
	highScoreBox->setString(String::createWithFormat("%d", highScore)->getCString());
}