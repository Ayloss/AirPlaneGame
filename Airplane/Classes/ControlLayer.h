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

	//ը������һ
	void bombNumIncrease();
	//ը������һ
	void bombNumDecrease();
	//����ը����
	int getBombNum();
	//���ӷ���
	void scoreIncrease(int score);
	//���ط���
	int getScore();
	//��ͣ��Ϸ�������Ϸ
	void menuCallBack(Ref *event, Widget::TouchEventType type);
};

