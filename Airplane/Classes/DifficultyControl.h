#pragma once
//�Ѷȵȼ�
extern float difficultyLevel;

//�л���������
extern const int speedBaseValue[3];
extern const int speedValueRange[3];
extern const int scoreValue[3];
extern const int lifeValue[3];

//�Ѷ�ϵ��:����ÿ���Ӹ�ϵ��,�Ѷ�����һ���ȼ�
#define DIFFICULTY_DEGREE 300000

//���˲�������Ļ���ʱ��
#define ENEMY1_CREATE_INTERVAL_BASE 1.0
#define ENEMY2_CREATE_INTERVAL_BASE 5.0
#define ENEMY3_CRAETE_INTERVAL_BASE 10.0

//���˷ɻ��ٶ����Ѷ����ӵķ���
#define ENEMY1_SPEED_INCREASE_WITH_DIFFICULTY 50
#define ENEMY2_SPEED_INCREASE_WITH_DIFFICULTY 30
#define ENEMY3_SPEED_INCREASE_WITH_DIFFICULTY 20

//���˷ɻ��������Ѷ����ӵķ���
#define ENEMY1_LIFE_INCREASE_WITH_DIFFICULTY 0
#define ENEMY2_LIFE_INCREASE_WITH_DIFFICULTY 1
#define ENEMY3_LIFE_INCREASE_WITH_DIFFICULTY 3