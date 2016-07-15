#pragma once
#include "cocos2d.h"
USING_NS_CC;

enum EnemyType
{
	little,
	middle,
	large
};
class Enemy :
	public Sprite
{
private:
	int life;//生命数
	int speed;//速度
	int score;//分数
	EnemyType enemyType;//敌机类型
	
public:
	Enemy();
	~Enemy();


	static Enemy* create(EnemyType type);
	//设置初始的数值
	//type:飞机的类型
	void setData(EnemyType type);

	//获得飞机的生命值
	int getLife();

	//获得飞机的速度
	int getSpeed();

	//获得消灭敌机的分数
	int getScore();

	//生命值减一,播放被击效果
	void getHurt();

	//恢复正常状态的动画
	void recover();

	//设置初始动画
	void setAnimation();

	//移除该敌机,播放消失动画
	void destoryed();
};

