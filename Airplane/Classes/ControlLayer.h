#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace ui;

class ControlLayer :
	public Layer
{
private:
	Node *rootNode;
	int scoreNum;
	int bombNum;
	Button* gameControlButton;
	TextBMFont* bombNumBox;
	TextBMFont* scoreBox;
public:
	virtual bool init();

	static ControlLayer* sharedControlLayer;
	static ControlLayer* create();

	ControlLayer();
	~ControlLayer();

	//炸弹数加一
	void bombNumIncrease();
	//炸弹数减一
	void bombNumDecrease();
	//返回炸弹数
	int getBombNum();
	//增加分数
	void scoreIncrease(int score);
	//返回分数
	int getScore();
	//暂停游戏与继续游戏
	void menuCallBack(Ref *event, Widget::TouchEventType type);
};

