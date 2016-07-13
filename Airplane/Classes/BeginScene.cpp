#include "BeginScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace ui;


BeginScene::BeginScene()
{
}


BeginScene::~BeginScene()
{
}

bool BeginScene::init()
{
	if (!Scene::init())
		return false;

	rootNode = CSLoader::createNode("BeginScene.csb");
	addChild(rootNode);

	//获取按钮节点
	startButton = dynamic_cast<Button*>(rootNode->getChildByName("start"));
	guideButton = dynamic_cast<Button*>(rootNode->getChildByName("guide"));
	//加载小飞机动画
	auto littlePlaneAnimation = CSLoader::createTimeline("littlePlane.csb");
	rootNode->runAction(littlePlaneAnimation);
	littlePlaneAnimation->gotoFrameAndPlay(0, 72, true);

	scheduleOnce(schedule_selector(BeginScene::loadRes), 0.1);
	//startButton->setEnabled(true);
	//此处待添加加载事件

	return true;

}
void BeginScene::startGame(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./sound/button.wav");
		break;
	}
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	{
		tsm->gotoMainScene();
		break;
	}
	}

}

void BeginScene::guideGame(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./sound/button.wav");
		break;
	}
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	{
		tsm->gotoGuideScene();
		break;
	}
	}
		
}

void BeginScene::loadAnimation()
{
	//主角飞机动画文件
	static const char* heroAnimationFile[6] = {
		"./ui/shoot/hero1.png",
		"./ui/shoot/hero2.png",
		"./ui/shoot/hero_blowup_n1.png",
		"./ui/shoot/hero_blowup_n2.png",
		"./ui/shoot/hero_blowup_n3.png",
		"./ui/shoot/hero_blowup_n4.png"
	};

	//敌机动画文件
	static const char* enemyAnimationFile[] = {
		"./ui/shoot/enemy1_down1.png",
		"./ui/shoot/enemy1_down2.png",
		"./ui/shoot/enemy1_down3.png",
		"./ui/shoot/enemy1_down4.png",
		"./ui/shoot/enemy2_hit.png",
		"./ui/shoot/enemy2_down1.png",
		"./ui/shoot/enemy2_down2.png",
		"./ui/shoot/enemy2_down3.png",
		"./ui/shoot/enemy2_down4.png",
		"./ui/shoot/enemy3_n1.png",
		"./ui/shoot/enemy3_n2.png",
		"./ui/shoot/enemy3_hit.png",
		"./ui/shoot/enemy3_down1.png",
		"./ui/shoot/enemy3_down2.png",
		"./ui/shoot/enemy3_down3.png",
		"./ui/shoot/enemy3_down4.png",
		"./ui/shoot/enemy3_down5.png",
		"./ui/shoot/enemy3_down6.png"
	};

	Animation *loader[8];
	for (int i = 0;i < 8;i++)
	{
		loader[i] = Animation::create();
	}
	//加载主角飞机动画
	for (int i = 0;i < 6;i++)
	{
		char cache[100] = { 0 };
		sprintf(cache, heroAnimationFile[i]);
		if (i < 2)
			loader[0]->addSpriteFrameWithFile(cache);
		else
			loader[1]->addSpriteFrameWithFile(cache);
	}
	AnimationCache::getInstance()->addAnimation(loader[0], "heroAlive");
	AnimationCache::getInstance()->addAnimation(loader[1], "heroDead");
	//加载敌机动画
	for (int i = 0;i < 18;i++)
	{
		char cache[100] = { 0 };
		sprintf(cache, enemyAnimationFile[i]);
		if (i < 4)
			loader[2]->addSpriteFrameWithFile(cache);
		else if (i == 4)
			loader[3]->addSpriteFrameWithFile(cache);
		else if (i >= 5 && i < 9)
			loader[4]->addSpriteFrameWithFile(cache);
		else if (i >= 9 && i < 11)
			loader[5]->addSpriteFrameWithFile(cache);
		else if (i == 11)
			loader[6]->addSpriteFrameWithFile(cache);
		else if (i > 11 && i < 18)
			loader[7]->addSpriteFrameWithFile(cache);
	}
	AnimationCache::getInstance()->addAnimation(loader[2], "enemy1Down");
	AnimationCache::getInstance()->addAnimation(loader[3], "enemy2Hitted");
	AnimationCache::getInstance()->addAnimation(loader[4], "enemy2Down");
	AnimationCache::getInstance()->addAnimation(loader[5], "enemy3Alive");
	AnimationCache::getInstance()->addAnimation(loader[6], "enemy3Hitted");
	AnimationCache::getInstance()->addAnimation(loader[7], "enemy3Down");
}

void BeginScene::loadMusic()
{
	//全部音频文件
	static const char* musicFile[13] = {
		"./sound/game_music.wav"
		,"./sound/achievement.wav"
		,"./sound/big_spaceship_flying.wav"
		,"./sound/bullet.wav"
		,"./sound/button.wav"
		,"./sound/enemy1_down.wav"
		,"./sound/enemy2_down.wav"
		,"./sound/enemy3_down.wav"
		,"./sound/game_over.wav"
		,"./sound/get_bomb.wav"
		,"./sound/get_double_laser.wav"
		,"./sound/out_porp.wav"
		,"./sound/use_bomb.wav"
	};
	//预加载全部音频文件
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(musicFile[0]);
	for (int i = 1;i < 13;i++)
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(musicFile[i]);


}

void BeginScene::loadRes(float dt)
{
	//加载动画和音乐
	loadAnimation();
	loadMusic();

	//添加按钮的监听事件
	startButton->addTouchEventListener(CC_CALLBACK_2(BeginScene::startGame, this));
	guideButton->addTouchEventListener(CC_CALLBACK_2(BeginScene::guideGame, this));

	//设置按钮可用
	startButton->setEnabled(true);
	guideButton->setEnabled(true);
}
