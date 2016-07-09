#pragma once
#include "cocos2d.h"
USING_NS_CC;
class ToolLayer :
	public Layer
{
private:
	Node* rootNode;
	Vector<Sprite*> *tool;//����
public:
	virtual bool init();

	static ToolLayer* sharedToolLayer;
	static ToolLayer* create();

	ToolLayer();
	~ToolLayer();

	//��������һ�ֵ���
	void createTool(float dt);
	//������ʧ�ص�����
	void toolDisappear(Node* pSender);
	//���ص��������ָ��
	Vector<Sprite*>* getTool();
};

