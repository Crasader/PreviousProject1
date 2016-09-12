#ifndef __JSON_MANAGE_H__
#define __JSON_MANAGE_H__
#include "cocos2d.h"
USING_NS_CC;


class CommandManage{
public:
	static CommandManage* getInstance();
	std::string getHeartCommmand();
	std::string getLoginCommmand(std::string username, std::string password);
	std::string getGiveUpCpgCommmand();
	std::string getReadyCommmand();
	std::string getPlayPokerCommmand(int poker);
	std::string getChiCommand(std::string chi,int poker);
	std::string getPengCommand(std::string peng ,int poker);
	std::string getGangCommand(std::string gang, int poker,int flag);
	std::string getGiveUpTingCommand();
	std::string getTingCommand(int poker);
	std::string getVisitorLoginCommand();
	std::string getRoomListCommand(std::string gameId);
	std::string getEnterRoomCommand(std::string gameId, std::string roomId);
	std::string getRegisterCommand(std::string account, std::string password);
    std::string getFindPassword(std::string account,std::string password);
	std::string getVerifyCommand(std::string phone);
	std::string getChangeNickNameCommand(std::string nickname);
	std::string getChangeAccountCommand(std::string account);
	std::string getChangePasswordCommand(std::string password);
	std::string getChangeGenderCommand(std::string gender);
	std::string getBoundPhoneCommand(std::string phone, std::string verify);
	std::string getTrusteeshipCommand();
	std::string getTrusteeshipCancelCommand();
	std::string getQuitRoomCommand();
	std::string getFriendListCommand();
	std::string getSearchFriendCommand(std::string name);
	std::string getAddFriendCommand(std::string poxiaoId,std::string nickname);
    std::string getAddFriendQuickCommand(std::string key);
	std::string getDeleteFriendCommand(std::string poxiaoId);
	std::string getChangeHeadCommand(std::string pic);
	std::string getOpenRoomCommand(std::string pids);
	std::string getEnterFriendRoomCommand(std::string pid);
	std::string getSendRedWalletCommand();
	std::string getReciveRedWalletCommand(std::string hbcode);
    std::string getRedWalletPushCommand();
	std::string getBillCommand();
	std::string getBillDetailCommand(std::string billId);
	std::string getLobbyQuitCommand();
	std::string getDailyTaskCommand();
	std::string getTaskMQ3Command();
	std::string getTaskPPH3Command();
	std::string getTaskLZ4Command();
    std::string getTaskExtraCommand();
	std::string getWelfareCommand();
	std::string getDailySignCommand();
	std::string getSignCommand();
	std::string getDailyPrideCommand();
	std::string getTodayPrideCommand();
	std::string getWelfareJJJ();
	std::string getWelfareBZJJJ();
	std::string getWelfareMobile();
	std::string getWelfareWx();
	std::string getAccountCheckCommand(std::string usrname);
    std::string getStartHuaCommand();
    std::string getFirstChargeInfoCommand();
    std::string getGoldChangeListCommand();
    std::string getGoldChangeCommand(std::string diamond);
    std::string getDiamondChangeListCommand();
    std::string getLequanChangeListCommand();
    std::string getLequanChangeCommand(std::string propId,std::string phone,std::string name,std::string address);
    std::string getPlayerInfoCommand();
    std::string getLequanChangeRecordCommand();
    std::string getFeedBackCommand(std::string msg);
    std::string getOnResumeCommand();
    std::string getContinueGameCommand();
    std::string getPlayerChatMsgCommand(std::string msg,std::string pid);
    std::string getThirdLoginCommand(std::string openid);
private:
	CommandManage();
	static CommandManage* _instance;
	std::string commandString(std::map<std::string, std::string> keyValue);
	std::string itos(int target);
};
#endif