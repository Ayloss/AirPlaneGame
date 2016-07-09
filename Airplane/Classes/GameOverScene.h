#pragma once
#include "cocos2d.h"
#include "SceneManager.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;
class GameOverScene :
	public Scene
{
private:
	Node *rootNode;
public:
	GameOverScene();
	~GameOverScene();

	virtual bool init();

	CREATE_FUNC(GameOverScene);

	SceneManager *tsm;

	//返回主场景回调函数
	void goBackGame(Ref *pSender, Widget::TouchEventType type);
	//获取当前分数并设置
	void setFinalScore(std::string score);
	//获取最高分并设置
	void getHighScore();
};

