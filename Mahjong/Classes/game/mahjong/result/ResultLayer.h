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
    CC_SYNTHESIZE(GameResultData, heroData, heroData);
    EventListenerCustom* continueAgainLisetner;
	int timeToatal;
	LabelAtlas* timeLable;
	Menu* resultMenu;
	void initView();
	void initData();
    void drawPokerPad(std::string pokers, std::string hutype,int hua);
	void drawHuType(std::string hutype);
	void drawHuaNum(int hua);
	void createPokersSprite(std::vector<std::string> showPokers);
	void drawTimeClock();
	void clickContinu();
	void clickQuit();
	void showContinueButton(float dt);
	std::string getImageNameById(int id, bool normal);
    void showCaidaiAnim(Sprite* sprite);
    void showLequanExplosion();
    void showGoldExplosion();
    void setWinOrLose();
    void showWinAnim();
    void showLoseAnim();
};

#endif