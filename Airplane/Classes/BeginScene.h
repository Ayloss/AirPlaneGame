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
public:
	BeginScene();
	~BeginScene();

	virtual bool init();

	//��ʼ��Ϸ�ص�����
	void startGame(Ref *pSender, Widget::TouchEventType type);
	//��ת���淨�̳̻ص�����
	void guideGame(Ref *pSender, Widget::TouchEventType type);
	//����ȫ������
	void loadAnimation();

	CREATE_FUNC(BeginScene);

	SceneManager *tsm;
};

