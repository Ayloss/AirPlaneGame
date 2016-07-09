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

	//创建开始场景
	void createBeginScene();
	//切换教程场景
	void gotoGuideScene();
	//切换主场景
	void gotoMainScene();
	//切换结束场景
	void gotoGameOverScene(std::string finalScore);
};



