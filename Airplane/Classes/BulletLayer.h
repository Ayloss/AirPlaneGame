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
	int specialBullets;//�����ӵ���
public:
	virtual bool init();

	static BulletLayer* sharedBulletLayer;
	static BulletLayer* create();

	BulletLayer();
	~BulletLayer();

	//�����ӵ�������
	Vector<Sprite*>* getAllBullets();
	//�ӵ������ص�����
	void bulletCreate(float dt);
	//�ӵ���Ȼ��ʧ�ص�����
	void bulletDisappear(Node *pSender);
	//���������ӵ���ʱ��
	void startShooting();
	//ȡ�������ӵ���ʱ��
	void stopShooting();
	//���������ӵ�
	void getSpecialBullets();

};

