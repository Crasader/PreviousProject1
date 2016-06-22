#ifndef __FRIENDINVITEINFO_H__
#define __FRIENDINVITEINFO_H__
#include "cocos2d.h"
#include "game/mahjong/dialog/base/BaseDialog.h"
USING_NS_CC;

class PromptDialog : public BaseDialog{
public:
	virtual bool init();
	void setTextInfo(int type);
	CREATE_FUNC(PromptDialog);
	CC_SYNTHESIZE(int, dialogType, DialogType);
	CC_SYNTHESIZE(std::string, poxiaoId, PoxiaoId);
private:
	virtual void drawDialog() override;
	Sprite* textInfo;
	std::string myWrap(std::string str, int length);
	void clickComfirm();
};
#endif