#ifndef __DEAL_JONG_ANIM__
#define __DEAL_JONG_ANIM__
#include "cocos2d.h"
#include "mahjong/utils/SeatIdUtil.h"
USING_NS_CC;

class DealJongAnim :public Layer{
public:
	virtual bool init();
	CREATE_FUNC(DealJongAnim);
	void showDealJong(int seatId, int dian1, int dian2);
    void updateRest(std::string num);
    void drawPaidui(int num);
private:
    Layer* paishuLayer;//剩余牌堆图层
	int rounds;
    int index =0;
    int currentSeadId =ClientSeatId::left;
	Point heroStarPos;
	Point leftStarPos;
	Point rightStarPos;
	Point oppositeStarPos;
	void initPosition();
	Sprite* createJong4();
    Sprite* createJong4(int seatId);
	Point caluMove2Pos(int type);
	int getTypeByDirection(int direction);
	Point getPosByDirection(int direction, int index);
    void showDiceAnim(Sprite* sprite);
    void showKaibaoAnim(Sprite* sprite);
    void showFapai(Sprite* sprite);
    void faPaiAction(int firstSeatId,int rounds);
    int  getNextSeatId(int seatId);
    Point getPaiduiPos(int seatId,int round);
   
};
#endif
