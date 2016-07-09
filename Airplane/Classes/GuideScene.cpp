#include "GuideScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SceneManager.h"

USING_NS_CC;
using namespace ui;

GuideScene::GuideScene()
{
}


GuideScene::~GuideScene()
{
}

bool GuideScene::init()
{
	if (!Scene::init())
		return false;

	rootNode = CSLoader::createNode("GuideScene.csb");
	addChild(rootNode);

	//获取开始游戏按钮
	auto startButton = dynamic_cast<Button*>(rootNode->getChildByName("start"));
	//添加按钮监听事件
	startButton->addTouchEventListener(CC_CALLBACK_2(GuideScene::startGame,this));

	return true;
}

void GuideScene::startGame(Ref *pSender,Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
		tsm->gotoMainScene();

}
