#include "SimpleAudioEngine.h"
#include "SceneManager.h"
#include "BeginScene.h"
#include "GuideScene.h"
#include "MainScene.h"
#include "GameOverScene.h"

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

cocos2d::Scene* SceneManager::getBeginScene()
{
	return gameOverScene;
}

cocos2d::Scene* SceneManager::getMainScene()
{
	return mainScene;
}

cocos2d::Scene* SceneManager::getGameOverScene()
{
	return gameOverScene;
}


void SceneManager::createBeginScene()
{
	beginScene = Scene::create();
	BeginScene *begin = BeginScene::create();
	begin->tsm = this;
	beginScene->addChild(begin);
	Director::getInstance()->runWithScene(beginScene);
}

void SceneManager::gotoGuideScene()
{
	guideScene = Scene::create();
	GuideScene *guide = GuideScene::create();
	guide->tsm = this;
	guideScene->addChild(guide);
	TransitionMoveInT *guideSceneWithAnimation = TransitionMoveInT::create(0.5, guideScene);
	Director::getInstance()->replaceScene(guideSceneWithAnimation);
}

void SceneManager::gotoMainScene()
{
	mainScene = Scene::create();
	MainScene *gameMain = MainScene::create();
	gameMain->tsm = this;
	mainScene->addChild(gameMain);
	//获得带切换动画的场景指针
	auto *mainSceneWithAnimation = TransitionZoomFlipX::create(0.5, mainScene);
	Director::getInstance()->replaceScene(mainSceneWithAnimation);
}

void SceneManager::gotoGameOverScene(std::string finalScore)
{
	gameOverScene = Scene::create();
	GameOverScene *gameOver = GameOverScene::create();
	gameOver->tsm = this;
	//设置当前分数与最高分
	gameOver->setFinalScore(finalScore);
	gameOver->getHighScore();
	gameOverScene->addChild(gameOver);
	auto *gameOverSceneWithAnimation = TransitionMoveInT::create(0.5, gameOverScene);
	//切换场景
	Director::getInstance()->replaceScene(gameOverSceneWithAnimation);
}
