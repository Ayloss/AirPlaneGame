#pragma once
#include "cocos2d.h"
USING_NS_CC;
class PlaneLayer :
	public Layer
{
private:
	Sprite *heroPlane;
	Node *rootNode;
public:
	virtual bool init();

	//创建全局的飞机层
	static PlaneLayer* sharedPlaneLayer;
	static PlaneLayer* create();

	PlaneLayer();
	~PlaneLayer();

	Sprite* shareHeroPlane();

	//键盘事件回调函数
	void movePlaneBegin(EventKeyboard::KeyCode keyCode, Event* event);
	void movePlaneEnd(EventKeyboard::KeyCode keyCode, Event* event);

	//飞机往四个方向的移动
	void moveUp(float dt);
	void moveDown(float dt);
	void moveLeft(float dt);
	void moveRight(float dt);

	//设置飞机的初始动画
	void setAnimation();

	//停用所有定时器和动画
	void removeAllListenersAndActions();
};

