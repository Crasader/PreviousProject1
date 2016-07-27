#ifndef __RESULT_LAYER_H__
#define __RESULT_LAYER_H__
#include "cocos2d.h"
#include "game/mahjong/state/GameData.h"
#include "game/mahjong/result/PlayerInfoCell.hpp"
USING_NS_CC;

class ResultLayer :public Layer{
public:
	virtual bool init();
    virtual void onEnter() override;
    virtual void onExit() override;
	void updateTime(float dt);
	CREATE_FUNC(ResultLayer);
private:
   
	int timeToatal;//自动再来一局的时间
	Menu* resultMenu;
    EventListenerCustom* continueAgainLisetner;
    
	void initView();
	void initData();
    void setWinOrLose();//设置玩家自己的结算信息
    void showWinAnim();
    void showLoseAnim();
    void drawPokerPad(std::string pokers, std::string hutype,int hua);
	void drawHuType(std::string hutype);
	void drawHuaNum(int hua);
	void clickContinu();//再来一局
	void clickQuit();//回到大厅
    void showCaidaiAnim(Sprite* sprite);
    
    CC_SYNTHESIZE(GameResultData, heroData, heroData);
};

#endif