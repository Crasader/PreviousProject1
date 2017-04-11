#ifndef __MSG_HANDLER_H__
#define __MSG_HANDLER_H__
#include "cocos2d.h"

USING_NS_CC;

class MsgHandler:public Node{
public:
	static MsgHandler* getInstance();
	void handleMsg(std::string msg);
private:
	static MsgHandler* _instance;
	MsgHandler();
    void postNotifyMessage(std::string event_name, void* msg);
	void distribute(int code, std::string msg);
	void roomListResp(std::string msg);
	void enterRoomResp(std::string msg);
	void loginResp(std::string msg);
	void addPalyer(std::string msg);
	void showOtherReady(std::string msg);
	void getHeroJongs(std::string msg);
	void nextPlayer(std::string msg);
	void showOtherPlayedJong(std::string msg);
	void showCpgNotify(std::string msg);
	void showOtherChiNotify(std::string msg);
	void showOtherPengNotify(std::string msg);
	void showOtherGangNotify(std::string msg);
	void heroTingMsg(std::string msg);
	void playerTingResp(std::string msg);
	void gameResultNotify(std::string msg);
	void playerTingNotify(std::string msg);
	void playerConnectAgain(std::string msg);
	void changeGenderResp(std::string msg);
    void heroChiResp(std::string msg);
	void heroGangResp(std::string msg);
	void heroPengResp(std::string msg);
	void removePlayerNotify(std::string msg);
	void friendOpenRoomResp(std::string msg);
	void friendOpenRoomNotify(std::string msg);
	void friendEnterRoomResp(std::string msg);
	void playerChatNotify(std::string msg);
	void billResp(std::string msg);
	void billDetailResp(std::string msg);
	void dailyPrideResp(std::string msg);
	void todayPrideResp(std::string msg);
    void firstChargeInfoResp(std::string msg);
    void goldChangeListResp(std::string msg);
    void goldChangeResp(std::string msg);
    void diamondChangeListResp(std::string msg);
    void lequanChangeListResp(std::string msg);
    void getLequanExchangeResp(std::string msg);
    void getPlayerInfoResp(std::string msg);
    void getPlayerOffLineNotify(std::string msg);
    void getLequanChangeRecordResp(std::string msg);
    void getHeadImageChangeResp(std::string msg);
    void getFeedBackResp(std::string msg);
    void gameContinueResp(std::string msg);
    void otherClientReplace(std::string msg);
    void inviteOthersResp(std::string msg);
    void openRoomEnquireResp(std::string msg);
    void enterRoomEnquireResp(std::string msg);
    void handleDissovleRoomNotify(std::string msg);
    void handleDissovleRoomSelectedNotify(std::string msg);
    void handleQuitGameViewResp(std::string msg);
    void handleScrollTextResp(std::string msg);
    void handleWanJiaQunResp(std::string msg);
    void handleNoticeResp(std::string msg);
    void hanleFangzhuDismissRoom(std::string msg);
    void handleGamePayType(std::string msg);
    void handleFupanInfo(std::string msg);
    void handleFupanPlayerInfo(std::string msg);
    void fangZhuLeaveRoom(std::string msg);
    void handleTuiGuangInfo(std::string msg);
    void handleTuiGuangPrideInfo(std::string msg);
    void handleGongGaoInfo(std::string msg);
    void handleCertification(std::string msg);
    void handleHongZhongEnterRoom(std::string msg);
    void handleHZEnterRoomResp(std::string msg);
    void handleHZReadyNoyify(std::string msg);
    void handleHZFaPaiNotify(std::string msg);
    void handleHZPlayerPlayPokerNotify(std::string msg);
    void handleHZDispatchPokerNotify(std::string msg);
    void handleHZGameReconnectNotify(std::string msg);
    void handleHZPlayerActionNotify(std::string msg);
    void handleHZGameResultNotify(std::string msg);
    void handleHZPlayerPengNotify(std::string msg);
    void handleHZPlayerGangNotify(std::string msg);
    void handleHZPlayerCanclePGResp(std::string msg);
    void handleHZPlayerFanMaNotify(std::string msg);
};
#endif
