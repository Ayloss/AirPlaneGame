#pragma once
#include "cocos2d.h"
USING_NS_CC;
class ToolLayer :
	public Layer
{
private:
	Node* rootNode;
	Vector<Sprite*> *tool;//道具
public:
	virtual bool init();

	static ToolLayer* sharedToolLayer;
	static ToolLayer* create();

	ToolLayer();
	~ToolLayer();

	//任意生成一种道具
	void createTool(float dt);
	//道具消失回调函数
	void toolDisappear(Node* pSender);
	//返回道具数组的指针
	Vector<Sprite*>* getTool();
};

