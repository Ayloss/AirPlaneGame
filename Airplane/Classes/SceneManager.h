#pragma once
#include "cocos2d.h"
USING_NS_CC;
class SceneManager
{
private:
	Scene *beginScene;
	Scene *guideScene;
	Scene *mainScene;
	Scene *gameOverScene;
public:
	SceneManager();
	~SceneManager();

	Scene* getBeginScene();
	Scene* getMainScene();
	Scene* getGameOverScene();

	//������ʼ����
	void createBeginScene();
	//�л��̳̳���
	void gotoGuideScene();
	//�л�������
	void gotoMainScene();
	//�л���������
	void gotoGameOverScene(std::string finalScore);
};



