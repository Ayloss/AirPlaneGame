#pragma once
#include "cocos2d.h"
#include "PlaneLayer.h"
USING_NS_CC;
class BulletLayer :
	public Layer
{
private:
	Node *rootNode;
	Vector<Sprite*> *allBullets;
	int specialBullets;//特殊子弹数
public:
	virtual bool init();

	static BulletLayer* sharedBulletLayer;
	static BulletLayer* create();

	BulletLayer();
	~BulletLayer();

	//返回子弹的数组
	Vector<Sprite*>* getAllBullets();
	//子弹产生回调函数
	void bulletCreate(float dt);
	//子弹自然消失回调函数
	void bulletDisappear(Node *pSender);
	//设立产生子弹定时器
	void startShooting();
	//取消产生子弹定时器
	void stopShooting();
	//增加特殊子弹
	void getSpecialBullets();

};

