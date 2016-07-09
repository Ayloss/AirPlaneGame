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
	Node *rootNode;//�������ڵ�
	PlaneLayer *planeLayer;//�ɻ���
	BulletLayer *bulletLayer;//�ӵ���
	ControlLayer *controlLayer;//���Ʋ�
	EnemyLayer *enemyLayer;//�л���
	ToolLayer *toolLayer;//���߲�

	Node *bg1;//�����ı���ͼ
	Node *bg2;
public:
	MainScene();
	~MainScene();
	
	virtual bool init();

	CREATE_FUNC(MainScene);

	SceneManager *tsm;//��������������ָ��

	//�����ƶ��ص�����
	void bgMove(float dt);

	//���̼����¼��ص�����,�����Ƿ�ʹ��ը��
	void useBomb(EventKeyboard::KeyCode keyCode, Event* event);

	//���ߺ����Ƿɻ�����ײ���
	void collisionDetectionForToolAndHero();

	//�ӵ��͵л�����ײ���
	void collisionDetectionForBulletAndEnemy();

	//�л������ǵ���ײ���
	void collisionDetectionForEnemyAndHero();

	//֡ˢ�¶�ʱ��,������ײ���
	void update(float delta);

	//������Ϸ
	void gameOver();

	//��ת���������ص�����
	//finalScore:���յĵ÷�
	void endGame(std::string &finalScore);
};

