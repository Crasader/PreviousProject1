#ifndef __SYSTEM_UI_H__
#define __SYSTEM_UI_H__

#include "cocos2d.h"
USING_NS_CC;

#include "SetPanel.h"

class SystemUI : public Node
{
public:
	CREATE_FUNC(SystemUI);


private:
	MenuItem* backBtn;
	MenuItem* inforBtn;
	MenuItem* gameBtn;
	MenuItem* setBtn;
	bool init();
	void onBackBtnCallBack(Ref* pSender);

	void onInforBtnCallBack(Ref* pSender);
	void onGameBtnCallBack(Ref* pSender);
	void onSetBtnCallBack(Ref* pSender);
	void onAddCoinBtnCallBack(Ref* pSender);

	SetPanel* setPanel = nullptr;
};
#endif