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
	int life;//������
	int speed;//�ٶ�
	int score;//����
	EnemyType enemyType;//�л�����
	
public:
	Enemy();
	~Enemy();


	static Enemy* create(EnemyType type);
	//���ó�ʼ����ֵ
	//type:�ɻ�������
	void setData(EnemyType type);

	//��÷ɻ�������ֵ
	int getLife();

	//��÷ɻ����ٶ�
	int getSpeed();

	//�������л��ķ���
	int getScore();

	//����ֵ��һ,���ű���Ч��
	void getHurt();

	//�ָ�����״̬�Ķ���
	void recover();

	//���ó�ʼ����
	void setAnimation();

	//�Ƴ��õл�,������ʧ����
	void destoryed();
};

