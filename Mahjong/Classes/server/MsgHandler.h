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
	void postNotifyMessage(std::string event_name, std::string msg);
	void distribute(int code, std::string msg);
	void roomListResp(std::string msg);
	void enterRoomResp(std::string msg);
	void loginResp(std::string msg);
	void addPalyer(std::string msg);
	void showOtherReady(std::string msg);
	void getHeroJongs(std::string msg);
	void replaceFlower(std::string msg);
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
	void changeNickNameResp(std::string msg);
	void changeAccountResp(std::string msg);
	void boundPhoneResp(std::string msg);
	void changePasswordResp(std::string msg);
	void changeGenderResp(std::string msg);
	void trusteeshipResp(std::string msg);
	void trusteeshipCancelResp(std::string msg);
	void trusteeshipNotify(std::string msg);
	void heroChiResp(std::string msg);
	void heroGangResp(std::string msg);
	void heroPengResp(std::string msg);
	void removePlayerNotify(std::string msg);
	void friendListResp(std::string msg);
	void friendSearchResp(std::string msg);
	void friendAddResp(std::string msg);
	void friendDeleteResp(std::string msg);
	void friendAddNotify(std::string msg);
	void friendOpenRoomResp(std::string msg);
	void friendOpenRoomNotify(std::string msg);
	void friendEnterRoomResp(std::string msg);
	void playerChatNotify(std::string msg);
	void sendRedWalletResp(std::string msg);
	void reciveRedWalletResp(std::string msg);
	void billResp(std::string msg);
	void billDetailResp(std::string msg);
	void dailyTaskResp(std::string msg);
	void dailySignResp(std::string msg);
	void signTodayResp(std::string msg);
	void welfareResp(std::string msg);
	void welfareJJJResp(std::string msg);
	void welfareBZJJJResp(std::string msg);
	void welfareMobileResp(std::string msg);
	void welfareWxResp(std::string msg);
	void dailyPrideResp(std::string msg);
	void todayPrideResp(std::string msg);
	void checkAccountResp(std::string msg);
    void firstChargeInfoResp(std::string msg);
    void goldChangeListResp(std::string msg);
    void goldChangeResp(std::string msg);
    void diamondChangeListResp(std::string msg);
    void lequanChangeListResp(std::string msg);

};
#endif