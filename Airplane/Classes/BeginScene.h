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
	Node *rootNode;//�������ڵ�
	Button *startButton;//��ʼ��ť
	Button *guideButton;//�淨��ť
public:
	BeginScene();
	~BeginScene();

	virtual bool init();

	CREATE_FUNC(BeginScene);

	//��ʼ��Ϸ�ص�����
	void startGame(Ref *pSender, Widget::TouchEventType type);
	//��ת���淨�̳̻ص�����
	void guideGame(Ref *pSender, Widget::TouchEventType type);
	//����ȫ������
	void loadAnimation();
	//����ȫ����Ƶ�ļ�
	void loadMusic();
	//������Դ�ļ�
	void loadRes(float dt);

	//ָ�򳡾���������ָ��
	SceneManager *tsm;

};

