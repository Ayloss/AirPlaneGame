#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SceneManager.h"

USING_NS_CC;
using namespace ui;

class GuideScene :
	public Scene
{
private:
	Node* rootNode;
public:
	GuideScene();
	~GuideScene();

	virtual bool init();

	void startGame(Ref *pSender, Widget::TouchEventType type);
	SceneManager *tsm;

	CREATE_FUNC(GuideScene);
};

