#include "json/document.h"
#include "json/rapidjson.h"
#include "json/stringbuffer.h"
#include "json/prettywriter.h"
#include "json/filestream.h"
#include "server/CommandManage.h"
#include "mahjong/common/state/GameData.h"
#include "mahjong/common/utils/StringUtil.h"
#include "mahjong/GameConfig.h"
#include "server/MsgConfig.h"
#include "userdata/UserData.h"



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

std::string CommandManage::getHeartRespCommmand(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_HEARTBEAT_RETURN)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
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
    keyValue.insert(map<string, string>::value_type("plat", PAY_PLAT_VALUE));
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


std::string CommandManage::getQuitRoomCommand(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_MAJIANG_OUT_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    return commandString(keyValue);
}




std::string CommandManage::getChangeHeadCommand(std::string pic){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_MODIFY_PIC_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    keyValue.insert(map<string, string>::value_type("pic", pic));
    return commandString(keyValue);
}

std::string CommandManage::getOpenRoomCommand(std::string ftype,std::string dihua,std::string lz,std::string fcy,std::string ifkb,std::string ifemsc,std::string size){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_FRIEND_GAME_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    keyValue.insert(map<string, string>::value_type("pId", ""));
    keyValue.insert(map<string, string>::value_type("dihua", dihua));
    keyValue.insert(map<string, string>::value_type("lz", lz));
    keyValue.insert(map<string, string>::value_type("fcy", fcy));
    keyValue.insert(map<string, string>::value_type("ftype", ftype));
    keyValue.insert(map<string, string>::value_type("ifkb", ifkb));
    keyValue.insert(map<string, string>::value_type("ifemsc", ifemsc));
    keyValue.insert(map<string, string>::value_type("size", size));
    return commandString(keyValue);
}

std::string CommandManage::getEnterFriendRoomCommand(std::string pid){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_FRIEND_JOIN_GAME_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    keyValue.insert(map<string, string>::value_type("pId", pid));
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


std::string CommandManage::getFirstChargeInfoCommand(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_FIRST_CHARGE_GET_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    keyValue.insert(map<string, string>::value_type("plat", PAY_PLAT_VALUE));
    return commandString(keyValue);
}

std::string CommandManage::getGoldChargeListCommand(){
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

std::string CommandManage::getFangkaChargeListCommand(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_CHARGE_LIST_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    keyValue.insert(map<string, string>::value_type("plat", PAY_PLAT_VALUE));
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


std::string CommandManage::getOutResumeCommand(){
    std::map<std::string, std::string> keyValue;
    if("" != UserData::getInstance()->getPoxiaoId() && "unknow" != UserData::getInstance()->getPoxiaoId()){
        keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_MAJIANG_BACK_OUT_REQUEST)));
        keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    }
    return commandString(keyValue);
}

//std::string CommandManage::getOnResumeCommand(){
//    std::map<std::string, std::string> keyValue;
//    if("" != UserData::getInstance()->getPoxiaoId() && "unknow" != UserData::getInstance()->getPoxiaoId()){
//        keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_MAJIANG_BACK_RESUME_REQUEST)));
//        keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
//    }
//    return commandString(keyValue);
//}

std::string CommandManage:: getContinueGameCommand(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_MAJIANG_AGAIN_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    keyValue.insert(map<string, string>::value_type("plat", PAY_PLAT_VALUE));
    return commandString(keyValue);
}

std::string CommandManage::getPlayerChatMsgCommand(std::string msg,std::string pid,bool sound){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_GAME_CHART_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    keyValue.insert(map<string, string>::value_type("content", msg));
    keyValue.insert(map<string, string>::value_type("pId", pid));
    if(sound){
        keyValue.insert(map<string, string>::value_type("mark", "1"));
    }
    return commandString(keyValue);
}

std::string CommandManage::getThirdLoginCommand(std::string openid,std::string unionid,std::string head,std::string sex,std::string nickname,std::string hsman,std::string hstype,std::string imsi,std::string imei,std::string ver1,bool tag){
    //    第三方登录请求{code:999,open_id:123,type:1,hsman:厂商,hstype:机型,imsi:imsi,imei:imei} typ为1表示微信
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_THIRED_LOGIN_REQUEST)));
    keyValue.insert(map<string, string>::value_type("type", "1"));
    keyValue.insert(map<string, string>::value_type("open_id", openid));
    keyValue.insert(map<string, string>::value_type("unionid", unionid));
    keyValue.insert(map<string, string>::value_type("head", head));
    keyValue.insert(map<string, string>::value_type("sex", sex));
    keyValue.insert(map<string, string>::value_type("nickname", nickname));
    keyValue.insert(map<string, string>::value_type("ver1", ver1));
    keyValue.insert(map<string, string>::value_type("hsman", hsman));
    keyValue.insert(map<string, string>::value_type("hstype", hstype));
    keyValue.insert(map<string, string>::value_type("imsi", imsi));
    keyValue.insert(map<string, string>::value_type("imei", imei));
    keyValue.insert(map<string, string>::value_type("fff", "1"));
    if(tag)
        keyValue.insert(map<string, string>::value_type("abc","1"));
    return commandString(keyValue);
    
}



std::string CommandManage::getEnterRoomByIdCommand(std::string roomid){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_FRIEND_JOIN_GAME_FJH_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    keyValue.insert(map<string, string>::value_type("prId", roomid));
    return commandString(keyValue);
}


std::string CommandManage::getDissolveRoomCommand(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_FRIEND_DISMISS_FZ_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    return commandString(keyValue);
}

std::string CommandManage::getDissolveRoomRequestCommand(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_FRIEND_DISMISS_FZAGREE_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    return commandString(keyValue);
}

std::string CommandManage::getDissolveRoomSelectCommand(std::string agree){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_FRIEND_DISMISS_AGREE_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    keyValue.insert(map<string, string>::value_type("agree",agree));
    return commandString(keyValue);
}




std::string CommandManage::getOpenRoomRequestCommand(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_FANG_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    keyValue.insert(map<string, string>::value_type("plat", PAY_PLAT_VALUE));
    return commandString(keyValue);
}

std::string CommandManage::getEnterRoomRequestCommand(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_FANG1_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    return commandString(keyValue);
}


std::string CommandManage::getScrollTextCommand(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_MARQUEE_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    return commandString(keyValue);
}

std::string CommandManage::getWanJiaQunCommand(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_QUNEWM_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    return commandString(keyValue);
}

std::string CommandManage::getNoticeCommand(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_GONGGAO_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    return commandString(keyValue);
}


std::string CommandManage::getGamePayType(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_APPLE_SWITCH_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    keyValue.insert(map<string, string>::value_type("plat", PAY_PLAT_VALUE));
    return commandString(keyValue);
}


std::string CommandManage::getVistorLogin(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_LOGIN_GUEST_REQUEST)));
    keyValue.insert(map<string, string>::value_type("hsman", "APPLE"));
    keyValue.insert(map<string, string>::value_type("hstype", "IOS_VISITOR"));
    keyValue.insert(map<string, string>::value_type("fff", "1"));
    return commandString(keyValue);
}

std::string CommandManage::getVistorLoginAgain(std::string username,std::string password){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_LOGIN_REQUEST)));
    keyValue.insert(map<string, string>::value_type("hsman", "APPLE"));
    keyValue.insert(map<string, string>::value_type("hstype", "IOS_VISITOR"));
    keyValue.insert(map<string, string>::value_type("username", username));
    keyValue.insert(map<string, string>::value_type("password", password));
    keyValue.insert(map<string, string>::value_type("fff", "1"));
    return commandString(keyValue);
}

std::string CommandManage::getFupanInfo(std::string recordId){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_PLAY_BACK_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    keyValue.insert(map<string, string>::value_type("recordid", recordId));
    return commandString(keyValue);
}

std::string CommandManage::getTuiGuangCommand(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_SPREAD_NEWUSER_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    return commandString(keyValue);
}

std::string CommandManage::getTuiGuangPrideCommand(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_SPREAD_NEWUSER_REWARD_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    return commandString(keyValue);
}

std::string CommandManage::getGongGaoCommand(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_HUODONG_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    return commandString(keyValue);
}

std::string CommandManage::getCertification(std::string name, std::string sfz){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_IDCARD_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    keyValue.insert(map<string, string>::value_type("name", name));
    keyValue.insert(map<string, string>::value_type("idcard", sfz));
    return commandString(keyValue);
}

std::string CommandManage::getEnterHongZhongCommand(std::string ftype,std::string ma,std::string difen,std::string size){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code",StringUtil::itos(MSGCODE_HH_FRIEND_GAME_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId",UserData::getInstance()->getPoxiaoId()));
    keyValue.insert(map<string, string>::value_type("difen",difen));
    keyValue.insert(map<string, string>::value_type("fanma",ma));
    keyValue.insert(map<string, string>::value_type("ftype",ftype));
    keyValue.insert(map<string, string>::value_type("size",size));
    return commandString(keyValue);
}

std::string CommandManage::getHZDissolveRoomCommand(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_HH_FRIEND_DISMISS_FZ_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    return commandString(keyValue);
}

std::string CommandManage::getHZPlayerReadyCommand(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_HH_READY_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    return commandString(keyValue);
}

std::string CommandManage::getHZEnterRoomCommand(std::string roomId){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_HH_FRIEND_JOIN_GAME_FJH_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    keyValue.insert(map<string, string>::value_type("prId", roomId));
    return commandString(keyValue);
}

std::string CommandManage::getHZPlayPokerCommand(std::string pokerId){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_HH_MAJIANG_DISPATCH_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    keyValue.insert(map<string, string>::value_type("seatId", StringUtil::itos(GAMEDATA::getInstance()->getHeroSeatId())));
    keyValue.insert(map<string, string>::value_type("poker", pokerId));
    return commandString(keyValue);
}

std::string CommandManage::getHZPlayerPengCommand(std::string poker,std::string seatId,std::string peng){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_HH_MAJIANG_PENG_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    keyValue.insert(map<string, string>::value_type("seatId", seatId));
    keyValue.insert(map<string, string>::value_type("poker", poker));
    keyValue.insert(map<string, string>::value_type("peng", peng));
    return commandString(keyValue);
}



std::string CommandManage::getHZPlayerGangCommand(std::string poker,std::string seatId,std::string gang,std::string flag){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_HH_MAJIANG_GANG_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    keyValue.insert(map<string, string>::value_type("seatId", seatId));
    keyValue.insert(map<string, string>::value_type("poker", poker));
    keyValue.insert(map<string, string>::value_type("gang", gang));
    keyValue.insert(map<string, string>::value_type("flag", flag));
    return commandString(keyValue);
}

std::string CommandManage::getHZPlayerCanclePGCommand(std::string seatId){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_HH_MAJIANG_NO_CHI_PENG_GANG_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    keyValue.insert(map<string, string>::value_type("seatId", seatId));
    return commandString(keyValue);
}


std::string CommandManage::getHZHuActionCommand(std::string msg){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_HH_IFHU_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    keyValue.insert(map<string, string>::value_type("flag", msg));
    return commandString(keyValue);
    
}

std::string CommandManage::getHZDissolveRoomSelectCommand(std::string agree){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_HH_FRIEND_DISMISS_AGREE_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    keyValue.insert(map<string, string>::value_type("agree",agree));
    return commandString(keyValue);
}

std::string CommandManage::getHZDissolveRoomInGameCommand(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_HH_FRIEND_DISMISS_FZAGREE_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    return commandString(keyValue);
}

std::string CommandManage::getHZPlayGameAgain(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_HH_MAJIANG_AGAIN_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    return commandString(keyValue);
}

std::string CommandManage::getHZOutResumeCommand(){
    std::map<std::string, std::string> keyValue;
    if("" != UserData::getInstance()->getPoxiaoId() && "unknow" != UserData::getInstance()->getPoxiaoId()){
        keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_HH_MAJIANG_BACK_OUT_REQUEST)));
        keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    }
    return commandString(keyValue);
}

std::string CommandManage::getHZQuitRoomCommand(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_HH_MAJIANG_OUT_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    return commandString(keyValue);
}

std::string CommandManage::sendInviteCodeCommand(std::string code){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_YQM_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    keyValue.insert(map<string, string>::value_type("yqm", code));
    return commandString(keyValue);
}

std::string CommandManage::sendJoinCompetiotnCommand(std::string competitionId){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_MATCH_SIGN_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    keyValue.insert(map<string, string>::value_type("id", competitionId));
    return commandString(keyValue);
}

std::string CommandManage::sendQuitCompetitionCommand(std::string competitionId){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_MATCH_OUT_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    keyValue.insert(map<string, string>::value_type("id", competitionId));
    return commandString(keyValue);
}


std::string CommandManage::sendHuafeiRecordCommmand(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_FEE_EXCHANGE_RECORD_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    return commandString(keyValue);
}

std::string CommandManage::sendCancleTruCommand(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_MAJIANG_CANCEL_TRUSTEESHIP_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    return commandString(keyValue);
}

std::string CommandManage::sendGetHongbaoPride(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_FEE_GET_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    return commandString(keyValue);
}


std::string CommandManage::sendGiveupHongbaoPride(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_FEE_GIVEUP_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    return commandString(keyValue);
}

std::string CommandManage::sendLobbyPaiHangCommand(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_PHB_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    return commandString(keyValue);
}

std::string CommandManage::sendTurntableCommmand(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_DZP_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    return commandString(keyValue);
}


std::string CommandManage::sendTurntableShareCommand(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_DZP_B_SHARE_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    return commandString(keyValue);
}

std::string CommandManage::sendTurntableStartCommand(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_DZP_Z_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    return commandString(keyValue);
}

std::string CommandManage::sendExchangeHuaFeiCommand(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_FEE_TO_FANGKA_LIST_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    return commandString(keyValue);
}

std::string CommandManage::sendDuiHuanHuafeiCommand(std::string fee,std::string phone){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_FEE_TO_FANGKA_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    keyValue.insert(map<string, string>::value_type("fee", fee));
    keyValue.insert(map<string, string>::value_type("phone", phone));
    return commandString(keyValue);
}

std::string CommandManage::sendDuiHuanFangkaCommand(std::string fee){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_FANGKA_TO_FEE_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    keyValue.insert(map<string, string>::value_type("fee", fee));
    return commandString(keyValue);
}

std::string CommandManage::getCMOpenRoomCommand(std::string ftype,std::string dihua,std::string lz,std::string fcy,std::string ifkb,std::string size){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_CM_FRIEND_GAME_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
    keyValue.insert(map<string, string>::value_type("dihua", dihua));
    keyValue.insert(map<string, string>::value_type("lz", lz));
    keyValue.insert(map<string, string>::value_type("fcy", fcy));
    keyValue.insert(map<string, string>::value_type("ftype", ftype));
    keyValue.insert(map<string, string>::value_type("ifkb", ifkb));
    keyValue.insert(map<string, string>::value_type("size", size));
    return commandString(keyValue);
}

std::string CommandManage::getCMDissovleRoomReq(){
    std::map<std::string, std::string> keyValue;
    keyValue.insert(map<string, string>::value_type("code", StringUtil::itos(MSGCODE_CM_FRIEND_DISMISS_FZAGREE_REQUEST)));
    keyValue.insert(map<string, string>::value_type("poxiaoId", UserData::getInstance()->getPoxiaoId()));
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


