#include "server/CommandManage.h"
#include "json/document.h"
#include "json/rapidjson.h"
#include "json/stringbuffer.h"
#include "json/prettywriter.h"  
#include "json/filestream.h"
#include "userdata/UserData.h"
#include "game/mahjong/state/GAMEDATA.h"
#include "game/utils/StringUtil.h"
#include "server/MsgConfig.h"

CommandManage* CommandManage::_instance = 0;



CommandManage* CommandManage::getInstance(){

	if (_instance == 0){
		_instance = new CommandManage();
	}
	return _instance;

}


CommandManage::CommandManage(){
	//私有构造
}

std::string CommandManage::getHeartCommmand(){
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_HEARTBEAT)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	return commandString(keyValue);
}

std::string CommandManage::getLoginCommmand(std::string username, std::string password){
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_LOGIN_REQUEST)));
	keyValue.insert(map<string, string>::value_type("username", username));
	keyValue.insert(map<string, string>::value_type("password", password));
	return commandString(keyValue);
}

std::string CommandManage::getGiveUpCpgCommmand(){
	//{code:2008, poxiaoId : poxiaoId, seatId : seatId}
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_MAJIANG_NO_CHI_PENG_GANG_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	keyValue.insert(map<string, string>::value_type("seatId", StringUtil::itos(GAMEDATA::getInstance()->getHeroSeatId())));
	keyValue.insert(map<string, string>::value_type("GID", StringUtil::itos(1)));
	return commandString(keyValue);
}


std::string CommandManage::getReadyCommmand(){
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_READY_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	keyValue.insert(map<string, string>::value_type("GID", StringUtil::itos(1)));
	return commandString(keyValue);
}

std::string CommandManage::getPlayPokerCommmand(int poker){
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_MAJIANG_DISPATCH_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	keyValue.insert(map<string, string>::value_type("seatId", StringUtil::itos(GAMEDATA::getInstance()->getHeroSeatId())));
	keyValue.insert(map<string, string>::value_type("GID", StringUtil::itos(1)));
	keyValue.insert(map<string, string>::value_type("poker", StringUtil::itos(poker)));
	return commandString(keyValue);
}

std::string CommandManage::getChiCommand(std::string chi, int poker){
	//{code:2007, poxiaoId : poxiaoId, seatId : seatId, chi : "1,2", poker : poker}
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_MAJIANG_CHI_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	keyValue.insert(map<string, string>::value_type("seatId", StringUtil::itos(GAMEDATA::getInstance()->getHeroSeatId())));
	keyValue.insert(map<string, string>::value_type("chi", chi));
	keyValue.insert(map<string, string>::value_type("poker", StringUtil::itos(poker)));
	keyValue.insert(map<string, string>::value_type("GID", StringUtil::itos(1)));
	return commandString(keyValue);
}

std::string CommandManage::getPengCommand(std::string peng, int poker){
	//{code:2007, poxiaoId : poxiaoId, seatId : seatId, chi : "1,2", poker : poker}
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_MAJIANG_PENG_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	keyValue.insert(map<string, string>::value_type("seatId", StringUtil::itos(GAMEDATA::getInstance()->getHeroSeatId())));
	keyValue.insert(map<string, string>::value_type("peng", peng));
	keyValue.insert(map<string, string>::value_type("poker", StringUtil::itos(poker)));
	keyValue.insert(map<string, string>::value_type("GID", StringUtil::itos(1)));
	return commandString(keyValue);
}


std::string CommandManage::getGangCommand(std::string gang, int poker, int flag){
	//{code:2007, poxiaoId : poxiaoId, seatId : seatId, chi : "1,2", poker : poker}
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_MAJIANG_GANG_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	keyValue.insert(map<string, string>::value_type("seatId", StringUtil::itos(GAMEDATA::getInstance()->getHeroSeatId())));
	keyValue.insert(map<string, string>::value_type("gang", gang));
	keyValue.insert(map<string, string>::value_type("poker", StringUtil::itos(poker)));
	keyValue.insert(map<string, string>::value_type("flag", StringUtil::itos(flag)));
	keyValue.insert(map<string, string>::value_type("GID", StringUtil::itos(1)));
	return commandString(keyValue);
}


std::string CommandManage::getGiveUpTingCommand(){
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_MAJIANG_NO_TING_GANG_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	keyValue.insert(map<string, string>::value_type("seatId", StringUtil::itos(GAMEDATA::getInstance()->getHeroSeatId())));
	keyValue.insert(map<string, string>::value_type("GID", StringUtil::itos(1)));
	return commandString(keyValue);
}

std::string CommandManage::getTingCommand(int poker){
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_MAJIANG_TING_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	keyValue.insert(map<string, string>::value_type("seatId", StringUtil::itos(GAMEDATA::getInstance()->getHeroSeatId())));
	keyValue.insert(map<string, string>::value_type("poker", StringUtil::itos(poker)));
	keyValue.insert(map<string, string>::value_type("GID", StringUtil::itos(1)));
	return commandString(keyValue);
}


std::string CommandManage::getVisitorLoginCommand(){
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_LOGIN_GUEST_REQUEST)));
	return commandString(keyValue);
}


std::string CommandManage::getRoomListCommand(std::string gameId){
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_GET_ROOMSTYLE_LIST_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	keyValue.insert(map<string, string>::value_type("gameid", gameId));
	return commandString(keyValue);

}

std::string CommandManage::getEnterRoomCommand(std::string gameId, std::string roomId){
	//code:1000,poxiaoId:poxiaoId,rsid:1111,gameid:"1"}
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_INTO_ROOMSTYLE_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	keyValue.insert(map<string, string>::value_type("gameid", gameId));
	keyValue.insert(map<string, string>::value_type("rsid", roomId));
	return commandString(keyValue);
}

std::string CommandManage::getRegisterCommand(std::string account, std::string password){
	// {code:101,mobile:13989877777,yzm:56789,username:abc,password:678aaa}
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_REGISTER_REQUEST)));
	keyValue.insert(map<string, string>::value_type("password", password));
	keyValue.insert(map<string, string>::value_type("username", account));
	//keyValue.insert(map<string, string>::value_type("yzm", verify));
	//keyValue.insert(map<string, string>::value_type("mobile", phone));
	return commandString(keyValue);
}

std::string CommandManage::getFindPassword(std::string account,std::string phone){
    // 找回密码请求{code:148,account:"真心常在",mobile:"131111111"}
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_FIND_PASSWORD_REQUEST)));
    keyValue.insert(map<string, string>::value_type("account", account));
    keyValue.insert(map<string, string>::value_type("mobile", phone));
    return commandString(keyValue);
}

std::string CommandManage::getVerifyCommand(std::string phone){
	//{code:100,mobile:13989877777}
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_REGISTER_MOBILE_YZM)));
	keyValue.insert(map<string, string>::value_type("mobile", phone));
	return commandString(keyValue);
}

std::string CommandManage::getChangeNickNameCommand(std::string nickname){
	// {code:109,nickname:"π˛π˛"}
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_MODIFY_NICKNAME_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	keyValue.insert(map<string, string>::value_type("nickname", nickname));
	return commandString(keyValue);
}

std::string CommandManage::getChangeAccountCommand(std::string account){
	//{code:111,poxiaoId:poxiaoId,account:"aaa"}
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_MODIFY_ACCOUNT_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	keyValue.insert(map<string, string>::value_type("account", account));
	return commandString(keyValue);
}

std::string CommandManage::getChangePasswordCommand(std::string password){
	// {code:115,password:"123"}
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_MODIFY_PASSWORD_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	keyValue.insert(map<string, string>::value_type("password", password));
	return commandString(keyValue);
}

std::string CommandManage::getChangeGenderCommand(std::string gender){
	//{code:117,poxiaoId:"123",gender:"1"}
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_MODIFY_GENDER_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	keyValue.insert(map<string, string>::value_type("gender", gender));
	return commandString(keyValue);
}

std::string CommandManage::getBoundPhoneCommand(std::string phone, std::string verify){
	//{code:113,poxiaoId:poxiaoId,mobile:"13122221111",yzm:"33"}
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_MODIFY_PHONE_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	keyValue.insert(map<string, string>::value_type("mobile", phone));
	keyValue.insert(map<string, string>::value_type("yzm", verify));
	return commandString(keyValue);
}


std::string CommandManage::getTrusteeshipCommand(){
	//{ code:2028, poxiaoId : poxiaoId }
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_MAJIANG_TRUSTEESHIP_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	return commandString(keyValue);
}

std::string CommandManage::getTrusteeshipCancelCommand(){
	//{ code:2029, poxiaoId : poxiaoId }
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_MAJIANG_CANCEL_TRUSTEESHIP_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	return commandString(keyValue);
}

std::string CommandManage::getQuitRoomCommand(){
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_MAJIANG_OUT_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	return commandString(keyValue);
}

std::string CommandManage::getFriendListCommand(){
	// {code:126,poxiaoId:"456"}
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_GET_FRIEND_LIST_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	return commandString(keyValue);
}

std::string CommandManage::getSearchFriendCommand(std::string name){
	//{code:121, poxiaoId : "123", key : "∫√∞°"}
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_SEARCH_FRIEND_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	keyValue.insert(map<string, string>::value_type("key", name));
	return commandString(keyValue);
}

std::string CommandManage::getAddFriendCommand(std::string poxiaoId,std::string nickname){
	//{code:123,poxiaoId:"123",pId:"456"}
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_ADD_FRIEND_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	keyValue.insert(map<string, string>::value_type("pId", poxiaoId));
    keyValue.insert(map<string, string>::value_type("nickname", nickname));
	return commandString(keyValue);
}

std::string CommandManage::getAddFriendQuickCommand(std::string key){
    // 快速互加好友请求{code:144,poxiaoId:poxiaoId,key:"1234"}
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_QUICK_ADD_FRIEND_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    keyValue.insert(map<string, string>::value_type("key", key));
    return commandString(keyValue);
}

std::string CommandManage::getDeleteFriendCommand(std::string poxiaoId){
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_DEL_FRIEND_LIST_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	keyValue.insert(map<string, string>::value_type("pId", poxiaoId));
	return commandString(keyValue);
}

std::string CommandManage::getChangeHeadCommand(std::string pic){
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_MODIFY_PIC_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    keyValue.insert(map<string, string>::value_type("pic", pic));
	return commandString(keyValue);
}

std::string CommandManage::getOpenRoomCommand(std::string pids){
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_FRIEND_GAME_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	keyValue.insert(map<string, string>::value_type("pId", pids));
	return commandString(keyValue);
}

std::string CommandManage::getEnterFriendRoomCommand(std::string pid){
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_FRIEND_JOIN_GAME_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	keyValue.insert(map<string, string>::value_type("pId", pid));
	return commandString(keyValue);
}

std::string CommandManage::getSendRedWalletCommand(){
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_HONGBAO_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	return commandString(keyValue);
}

std::string CommandManage::getReciveRedWalletCommand(std::string hbcode){
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_HONGBAO_GET_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    keyValue.insert(map<string, string>::value_type("hbcode", hbcode));
	return commandString(keyValue);
}


std::string CommandManage::getRedWalletPushCommand(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_HONGBAO_GETED_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    return commandString(keyValue);
}


std::string CommandManage::getBillCommand(){
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_FRIEND_GAME_BILL_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	return commandString(keyValue);
}

std::string CommandManage::getBillDetailCommand(std::string billId){
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_FRIEND_GAME_BILL_DETAIL_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	keyValue.insert(map<string, string>::value_type("billid", billId));
	return commandString(keyValue);
}


std::string CommandManage::getLobbyQuitCommand(){
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_QUIT_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	return commandString(keyValue);
}




std::string CommandManage::getTaskMQ3Command(){
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_MQ3_GET_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	return commandString(keyValue);
}


std::string CommandManage::getTaskPPH3Command(){
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_PPH3_GET_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	return commandString(keyValue);
}
std::string CommandManage::getTaskLZ4Command(){
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_LEZI4_GET_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	return commandString(keyValue);
}

std::string CommandManage::getTaskExtraCommand(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_ALLTASK_GET_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    return commandString(keyValue);
}

std::string CommandManage::getDailyTaskCommand(){
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_TASK_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	return commandString(keyValue);
}
std::string CommandManage::getWelfareCommand(){
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_FULI_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	return commandString(keyValue);
}

std::string CommandManage::getDailySignCommand(){
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_SIGN_CONTENT_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	return commandString(keyValue);
}

std::string CommandManage::getSignCommand(){
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_SIGN_ON_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	return commandString(keyValue);
}


std::string CommandManage::getDailyPrideCommand(){
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_LOTTERY_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	return commandString(keyValue);
}

std::string CommandManage::getTodayPrideCommand(){
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_LOTTERY_GET_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	return commandString(keyValue);
}

std::string CommandManage::getWelfareJJJ(){
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_JJJ_GET_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	return commandString(keyValue);
}

std::string CommandManage::getWelfareBZJJJ(){
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_BZJJJ_GET_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	return commandString(keyValue);
}

std::string CommandManage::getWelfareMobile(){
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_BDPHONE_GET_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	return commandString(keyValue);
}

std::string CommandManage::getWelfareWx(){
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_BDWEIXIN_GET_REQUEST)));
	keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
	return commandString(keyValue);
}

std::string CommandManage::getAccountCheckCommand(std::string usrname){
	std::map<std::string, std::string> keyValue;
	keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_ACCOUNTREPEAT_REQUEST)));
	keyValue.insert(map<string, string>::value_type("username", usrname));
	return commandString(keyValue);
}

std::string CommandManage::getStartHuaCommand(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_MAJIANG_FIRSTHUA_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    return commandString(keyValue);
}

std::string CommandManage::getFirstChargeInfoCommand(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_FIRST_CHARGE_GET_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    return commandString(keyValue);
}

std::string CommandManage::getGoldChangeListCommand(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_EXCHANGE_LIST_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    return commandString(keyValue);
}

std::string CommandManage::getGoldChangeCommand(std::string diamond){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_EXCHANGE_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    keyValue.insert(map<string, string>::value_type("gold", diamond));
    return commandString(keyValue);
}

std::string CommandManage::getDiamondChangeListCommand(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_CHARGE_LIST_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    return commandString(keyValue);
}

std::string CommandManage::getLequanChangeListCommand(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_LEQUAN_MALL_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    return commandString(keyValue);
}

std::string CommandManage::getLequanChangeCommand(std::string propId,std::string phone,std::string name,std::string address){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_LEQUAN_MALL_EXCHANGE_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    keyValue.insert(map<string, string>::value_type("goodsId", propId));
    keyValue.insert(map<string, string>::value_type("phone", phone));
    keyValue.insert(map<string, string>::value_type("name", name));
    keyValue.insert(map<string, string>::value_type("address", address));
    return commandString(keyValue);
}

std::string CommandManage::getPlayerInfoCommand(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_GETINFO_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    return commandString(keyValue);
}

std::string CommandManage::getLequanChangeRecordCommand(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_LEQUAN_MALL_EXCHANGE_RECORD_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    return commandString(keyValue);
}

std::string CommandManage::getFeedBackCommand(std::string msg){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_FEEDBACK_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    keyValue.insert(map<string, string>::value_type("content", msg));
    return commandString(keyValue);
}

std::string CommandManage::getOnResumeCommand(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_MAJIANG_BACK_RESUME_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    return commandString(keyValue);
}

std::string CommandManage:: getContinueGameCommand(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_MAJIANG_AGAIN_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    return commandString(keyValue);
}

std::string CommandManage::getPlayerChatMsgCommand(std::string msg,std::string pid){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_GAME_CHART_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    keyValue.insert(map<string, string>::value_type("content", msg));
    keyValue.insert(map<string, string>::value_type("pId", pid));
    return commandString(keyValue);
}

std::string CommandManage::commandString(std::map<std::string, std::string> keyValue){
	rapidjson::Document document;
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	rapidjson::Value root(rapidjson::kObjectType);
	map<string, string>::iterator it;
	for (it = keyValue.begin(); it != keyValue.end(); ++it){
		rapidjson::Value info(rapidjson::kStringType);
		std::string myValue(it->second);
		info.SetString(myValue.c_str(), myValue.size(), allocator);
		root.AddMember(rapidjson::Value(it->first.c_str(), allocator), info, allocator);
	}
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	root.Accept(writer);
	std::string result = buffer.GetString();
	return result;
}

