// 选择倍数界面，　增加硬币界面
#ifndef __ADDCOINPANEL_H__
#define __ADDCOINPANEL_H__

#include "cocos2d.h"
USING_NS_CC;

class AddCoinPanel : public Node
{
public:
	CREATE_FUNC(AddCoinPanel);

	void showPanel();
	void hidePanel();

private:
	bool init();
	float time = 0.2f;
};


class ChooseTimesPanel : public Node
{
public:
	CREATE_FUNC(ChooseTimesPanel);

	void showPanel();
	void hidePanel();

private:
	bool init();
	float time = 0.2f;
};

#endif