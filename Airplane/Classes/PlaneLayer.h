#pragma once
#include "cocos2d.h"
USING_NS_CC;
class PlaneLayer :
	public Layer
{
private:
	Sprite *heroPlane;//���Ƿɻ�
	Node *rootNode;//���ڵ�
public:
	virtual bool init();

	//����ȫ�ֵķɻ���
	static PlaneLayer* sharedPlaneLayer;
	static PlaneLayer* create();

	PlaneLayer();
	~PlaneLayer();

	//�������Ƿɻ��ľ���
	Sprite* shareHeroPlane();

	//�����¼��ص�����
	void movePlaneBegin(EventKeyboard::KeyCode keyCode, Event* event);
	void movePlaneEnd(EventKeyboard::KeyCode keyCode, Event* event);

	//�ɻ����ĸ�������ƶ�
	void moveUp(float dt);
	void moveDown(float dt);
	void moveLeft(float dt);
	void moveRight(float dt);

	//���÷ɻ��ĳ�ʼ����
	void setAnimation();

	//ͣ�����ж�ʱ���Ͷ���
	void removeAllListenersAndActions();
};

