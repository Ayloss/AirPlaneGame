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

	//��ȡ��ť�ڵ�
	auto startButton = dynamic_cast<Button*>(rootNode->getChildByName("start"));
	auto guideButton = dynamic_cast<Button*>(rootNode->getChildByName("guide"));
	//����С�ɻ�����
	auto littlePlaneAnimation = CSLoader::createTimeline("littlePlane.csb");
	rootNode->runAction(littlePlaneAnimation);
	littlePlaneAnimation->gotoFrameAndPlay(0, 72, true);

	//����ȫ������
	loadAnimation();
	//����ȫ����Ч
	loadMusic();
	//startButton->setEnabled(true);
	//�˴�����Ӽ����¼�

	//��Ӱ�ť�ļ����¼�
	startButton->addTouchEventListener(CC_CALLBACK_2(BeginScene::startGame, this));
	guideButton->addTouchEventListener(CC_CALLBACK_2(BeginScene::guideGame, this));

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
	//���Ƿɻ������ļ�
	static const char* heroAnimationFile[6] = {
		"./ui/shoot/hero1.png",
		"./ui/shoot/hero2.png",
		"./ui/shoot/hero_blowup_n1.png",
		"./ui/shoot/hero_blowup_n2.png",
		"./ui/shoot/hero_blowup_n3.png",
		"./ui/shoot/hero_blowup_n4.png"
	};

	//�л������ļ�
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
	//�������Ƿɻ�����
	for (int i = 0;i < 6;i++)
	{
		char cache[100] = { 0 };
		sprintf(cache, heroAnimationFile[i]);
		if (i < 2)
			loader[0]->addSpriteFrameWithFile(cache);
		else
			loader[1]->addSpriteFrameWithFile(cache);
	}
	AnimationCache::sharedAnimationCache()->addAnimation(loader[0], "heroAlive");
	AnimationCache::sharedAnimationCache()->addAnimation(loader[1], "heroDead");
	//���صл�����
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
	AnimationCache::sharedAnimationCache()->addAnimation(loader[2], "enemy1Down");
	AnimationCache::sharedAnimationCache()->addAnimation(loader[3], "enemy2Hitted");
	AnimationCache::sharedAnimationCache()->addAnimation(loader[4], "enemy2Down");
	AnimationCache::sharedAnimationCache()->addAnimation(loader[5], "enemy3Alive");
	AnimationCache::sharedAnimationCache()->addAnimation(loader[6], "enemy3Hitted");
	AnimationCache::sharedAnimationCache()->addAnimation(loader[7], "enemy3Down");
}

void BeginScene::loadMusic()
{
	//ȫ����Ƶ�ļ�
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
	//Ԥ����ȫ����Ƶ�ļ�
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(musicFile[0]);
	for (int i = 1;i < 13;i++)
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(musicFile[i]);

}
