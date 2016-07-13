#pragma once
#include "cocos2d.h"
#include "SceneManager.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;
class BeginScene :
	public Scene
{
private:
	Node *rootNode;
	Button *startButton;
	Button *guideButton;
public:
	BeginScene();
	~BeginScene();

	virtual bool init();

	//开始游戏回调函数
	void startGame(Ref *pSender, Widget::TouchEventType type);
	//跳转到玩法教程回调函数
	void guideGame(Ref *pSender, Widget::TouchEventType type);
	//加载全部动画
	void loadAnimation();
	//加载全部音频文件
	void loadMusic();
	//加载资源文件
	void loadRes(float dt);
	CREATE_FUNC(BeginScene);

	SceneManager *tsm;

};

