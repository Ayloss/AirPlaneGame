#pragma once
#include "cocos2d.h"
#include "SceneManager.h"
#include "PlaneLayer.h"
#include "BulletLayer.h"
#include "EnemyLayer.h"
#include "ControlLayer.h"
#include "ToolLayer.h"
#include "Enemy.h"

USING_NS_CC;

class MainScene :
	public Scene
{
private:
	Node *rootNode;//场景根节点
	PlaneLayer *planeLayer;//飞机层
	BulletLayer *bulletLayer;//子弹层
	ControlLayer *controlLayer;//控制层
	EnemyLayer *enemyLayer;//敌机层
	ToolLayer *toolLayer;//道具层

	Node *bg1;//滚动的背景图
	Node *bg2;
public:
	MainScene();
	~MainScene();
	
	virtual bool init();

	CREATE_FUNC(MainScene);

	SceneManager *tsm;//场景控制器访问指针

	//背景移动回调函数
	void bgMove(float dt);

	//键盘监听事件回调函数,监听是否使用炸弹
	void useBomb(EventKeyboard::KeyCode keyCode, Event* event);

	//道具和主角飞机的碰撞检测
	void collisionDetectionForToolAndHero();

	//子弹和敌机的碰撞检测
	void collisionDetectionForBulletAndEnemy();

	//敌机和主角的碰撞检测
	void collisionDetectionForEnemyAndHero();

	//帧刷新定时器,包含碰撞检测
	void update(float delta);

	//结束游戏
	void gameOver();

	//跳转结束场景回调函数
	//finalScore:最终的得分
	void endGame(std::string &finalScore);
};

