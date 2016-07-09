#pragma once
//难度等级
extern float difficultyLevel;

//敌机基础数据
extern const int speedBaseValue[3];
extern const int speedValueRange[3];
extern const int scoreValue[3];
extern const int lifeValue[3];

//难度系数:分数每增加该系数,难度上升一个等级
#define DIFFICULTY_DEGREE 300000

//敌人产生间隔的基础时间
#define ENEMY1_CREATE_INTERVAL_BASE 1.0
#define ENEMY2_CREATE_INTERVAL_BASE 5.0
#define ENEMY3_CRAETE_INTERVAL_BASE 10.0

//敌人飞机速度随难度增加的幅度
#define ENEMY1_SPEED_INCREASE_WITH_DIFFICULTY 50
#define ENEMY2_SPEED_INCREASE_WITH_DIFFICULTY 30
#define ENEMY3_SPEED_INCREASE_WITH_DIFFICULTY 20

//敌人飞机生命随难度增加的幅度
#define ENEMY1_LIFE_INCREASE_WITH_DIFFICULTY 0
#define ENEMY2_LIFE_INCREASE_WITH_DIFFICULTY 1
#define ENEMY3_LIFE_INCREASE_WITH_DIFFICULTY 3