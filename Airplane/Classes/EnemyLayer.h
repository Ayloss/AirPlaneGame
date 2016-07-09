#pragma once
#include "cocos2d.h"
#include "Enemy.h"
USING_NS_CC;
class EnemyLayer :
	public Layer
{
private:
	Node* rootNode;
	Vector<Enemy*> *enemies;
public:
	virtual bool init();

	static EnemyLayer* sharedEnemyLayer;
	static EnemyLayer* create();

	EnemyLayer();
	~EnemyLayer();

	void addEnemy(EnemyType type);
	void difficultyControl(float dt);
	//�����л��ص�����
	void createEnemy1(float dt);
	void createEnemy2(float dt);
	void createEnemy3(float dt);
	//�л���Ȼ��ʧ�ص�����
	void enemyDisappear(Node *pSender);
	int destroyEverything();

	Vector<Enemy*>* getEnemies();
};

