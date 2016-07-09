#pragma once
#include "cocos2d.h"
#include "SceneManager.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;
class GameOverScene :
	public Scene
{
private:
	Node *rootNode;
public:
	GameOverScene();
	~GameOverScene();

	virtual bool init();

	CREATE_FUNC(GameOverScene);

	SceneManager *tsm;

	//�����������ص�����
	void goBackGame(Ref *pSender, Widget::TouchEventType type);
	//��ȡ��ǰ����������
	void setFinalScore(std::string score);
	//��ȡ��߷ֲ�����
	void getHighScore();
};

