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
	Node *rootNode;//场景根节点
	Button *startButton;//开始按钮
	Button *guideButton;//玩法按钮
public:
	BeginScene();
	~BeginScene();

	virtual bool init();

	CREATE_FUNC(BeginScene);

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

	//指向场景控制器的指针
	SceneManager *tsm;

};

