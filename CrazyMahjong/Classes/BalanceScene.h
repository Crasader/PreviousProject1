#ifndef __BALANCE_SCENE_H__
#define __BALANCE_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class BalanceScene : public Node
{
public:
	static Scene* createScene();

	// MahjongScene::create�����init����ʼ���Լ�
	CREATE_FUNC(BalanceScene);
	bool init();
	
private:

};

#endif // !__BALANCE_SCENE_H__
