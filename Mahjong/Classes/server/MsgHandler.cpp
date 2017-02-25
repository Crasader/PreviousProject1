#include "json/document.h"
#include "json/rapidjson.h"
#include "server/MsgHandler.h"
#include "server/MsgConfig.h"
#include "userdata/UserData.h"
#include "userdata/UserData.h"
#include "mahjong/state/GameData.h"
#include "mahjong/state/GAMEDATA.h"
#include "mahjong/utils/SeatIdUtil.h"
#include "mahjong/utils/StringUtil.h"
#include "server/SocketDataManage.h"
#include "server/NetworkManage.h"

#define RETURN_IF(cond)           if((cond)) return

MsgHandler* MsgHandler::_instance = 0;

MsgHandler* MsgHandler::getInstance(){
    
    if (_instance == 0){
        _instance = new MsgHandler();
    }
    return _instance;
    
}

MsgHandler::MsgHandler(){
    
}

void MsgHandler::handleMsg(std::string msg){
    //    log("server msg = %s", msg.c_str());
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &code = _mDoc["code"];
    if (code.IsInt()) {
        distribute(code.GetInt(), msg);
    }
    else{
        log("msg from server is error");
    }
}


void MsgHandler::distribute(int code, std::string msg){
    switch (code)
    {
        case MSGCODE_HEARTBEAT_RETURN:{
            NetworkManage::getInstance()->resetBeatCount();
            break;
        }
        case MSGCODE_GET_ROOMSTYLE_LIST_RESPONSE:
        {
            log(" *** room list resp *** ");
            roomListResp(msg);
            break;
        }
            
        case MSGCODE_MODIFY_GENDER_RESPONSE:
        {
            log(" *** change gender resp *** ");
            changeGenderResp(msg);
            break;
        }
        case MSGCODE_INTO_ROOMSTYLE_RESPONSE:
        {
            log(" *** enter room resp *** ");
            enterRoomResp(msg);
            break;
        }
        case MSGCODE_LOGIN_RESPONSE:
        {
            log(" *** login resp *** ");
            loginResp(msg);
            break;
        }
            
        case MSGCODE_READY_RESPONSE:
        {
            log(" *** ready resp *** ");
            break;
        }
            
        case MSGCODE_LOGIN_NOTIFY:
        {
            log(" *** enter room notify *** ");
            addPalyer(msg);
            break;
        }
            
        case MSGCODE_READY_NOTIFY:
        {
            log(" *** ready notify *** ");
            showOtherReady(msg);
            break;
        }
        case MSGCODE_MAJIANG_DISCARD_NOTIFY:
        {
            log(" *** start fa pai *** ");
            getHeroJongs(msg);
            break;
        }
        case MSGCODE_MAJIANG_KICKOUT_NOTIFY:
        {
            log(" *** remove plaeyer *** ");
            removePlayerNotify(msg);
            break;
        }
        case MSGCODE_MAJIANG_POKER_NOTIFY:
        {
            log(" *** next player turn *** ");
            nextPlayer(msg);
            break;
        }
            
        case MSGCODE_MAJIANG_DISPATCH_NOTIFY:
        {
            log(" *** other player pai *** ");
            showOtherPlayedJong(msg);
            break;
        }
        case MSGCODE_MAJIANG_PLAYER_CPG_NOTIFY:
        {
            log(" ***  hero cpg notify *** ");
            showCpgNotify(msg);
            break;
        }
        case MSGCODE_MAJIANG_CHI_NOTIFY:
        {
            log(" ***  player chi notify *** ");
            showOtherChiNotify(msg);
            break;
        }
        case MSGCODE_MAJIANG_PENG_NOTIFY:
        {
            log(" ***  player peng notify *** ");
            showOtherPengNotify(msg);
            break;
        }
        case MSGCODE_MAJIANG_GANG_NOTIFY:
        {
            log(" ***  player chi notify *** ");
            showOtherGangNotify(msg);
            break;
        }
            
        case MSGCODE_MAJIANG_TING_GANG_NOTIFY:
        {
            log(" *** hero ting pai notify *** ");
            heroTingMsg(msg);
            break;
        }
        case MSGCODE_MAJIANG_TING_RESPONSE:
        {
            log(" *** ting pai resp *** ");
            playerTingResp(msg);
            break;
        }
        case MSGCODE_MAJIANG_HU_NOTIFY:
        {
            log(" *** game result notify *** ");
            gameResultNotify(msg);
            break;
        }
        case MSGCODE_MAJIANG_TING_NOTIFY:
        {
            log(" *** ting notify *** ");
            playerTingNotify(msg);
            break;
        }
        case MSGCODE_MAJIANG_OUTLINE_RESUME_NOTIFY:
        {
            log(" *** re connect notify *** ");
            playerConnectAgain(msg);
            break;
        }
        case MSGCODE_MAJIANG_CHI_RESPONSE:
        {
            log(" *** chi resp *** ");
            heroChiResp(msg);
            break;
        }
        case MSGCODE_MAJIANG_PENG_RESPONSE:
        {
            log(" *** peng resp *** ");
            heroPengResp(msg);
            break;
        }
        case MSGCODE_MAJIANG_GANG_RESPONSE:
        {
            log(" *** gang resp *** ");
            heroGangResp(msg);
            break;
        }
        case MSGCODE_FRIEND_GAME_RESPONSE:
        {
            log(" *** friend open room resp *** ");
            friendOpenRoomResp(msg);
            break;
        }
        case MSGCODE_FRIEND_GAME_NOTIFY:
        {
            log(" *** friend open room  notify *** ");
            friendOpenRoomNotify(msg);
            break;
        }
        case MSGCODE_FRIEND_JOIN_GAME_RESPONSE:
        {
            log(" *** friend enter room  resp *** ");
            friendEnterRoomResp(msg);
            break;
        }
        case MSGCODE_GAME_CHART_NOTIFY:
        {
            log(" *** chat info notify *** ");
            playerChatNotify(msg);
            break;
        }
            
        case MSGCODE_FRIEND_GAME_BILL_RESPONSE:
        {
            billResp(msg);
            break;
        }
        case MSGCODE_FRIEND_GAME_BILL_DETAIL_RESPONSE:{
            billDetailResp(msg);
            break;
        }
            
        case MSGCODE_LOTTERY_RESPONSE:{
            dailyPrideResp(msg);
            break;
        }
        case MSGCODE_LOTTERY_GET_RESPONSE:{
            todayPrideResp(msg);
            break;
        }
        case MSGCODE_FIRST_CHARGE_GET_RESPONSE:{
            firstChargeInfoResp(msg);
            break;
        }
        case MSGCODE_EXCHANGE_LIST_RESPONSE:{
            goldChangeListResp(msg);
            break;
        }
            
        case MSGCODE_EXCHANGE_RESPONSE:{
            goldChangeResp(msg);
            break;
        }
        case MSGCODE_CHARGE_LIST_RESPONSE:{
            diamondChangeListResp(msg);
            break;
        }
        case MSGCODE_LEQUAN_MALL_RESPONSE:{
            lequanChangeListResp(msg);
            break;
        }
        case MSGCODE_LEQUAN_MALL_EXCHANGE_RESPONSE:{
            getLequanExchangeResp(msg);
            break;
        };
        case MSGCODE_GETINFO_RESPONSE:{
            getPlayerInfoResp(msg);
            break;
        }
        case MSGCODE_DX_NOTIFY:{
            getPlayerOffLineNotify(msg);
            break;
        }
        case MSGCODE_LEQUAN_MALL_EXCHANGE_RECORD_RESPONSE:{
            getLequanChangeRecordResp(msg);
            break;
        }
        case MSGCODE_MODIFY_PIC_RESPONSE:{
            getHeadImageChangeResp(msg);
            break;
        }
        case MSGCODE_FEEDBACK_RESPONSE:{
            getFeedBackResp(msg);
            break;
        }
        case  MSGCODE_MAJIANG_AGAIN_RESPONSE:{
            gameContinueResp(msg);
            break;
        }
        case MSGCODE_OTHER_REPLACE:{
            otherClientReplace(msg);
            break;
        }
        case MSGCODE_FRIEND_GAME_RESULT_NOTIFY:{
            inviteOthersResp(msg);
            break;
        }
            
        case MSGCODE_FRIEND_DISMISS_NOTIFY:{
            hanleFangzhuDismissRoom(msg);
            break;
        }
        case MSGCODE_FRIEND_DISMISS_AGREE_NOTIFY:{
            handleDissovleRoomNotify(msg);
            break;
        }
        case MSGCODE_FRIEND_DISMISS_AGREE_RESULT_NOTIFY:{
            handleDissovleRoomSelectedNotify(msg);
            break;
        }
        case MSGCODE_FANG_RESPONSE:{
            openRoomEnquireResp(msg);
            break;
        }
        case MSGCODE_FANG1_RESPONSE:{
            enterRoomEnquireResp(msg);
            break;
        }
        case MSGCODE_MAJIANG_OUT_RESPONSE:{
            handleQuitGameViewResp(msg);
            break;
        }
        case MSGCODE_MARQUEE_RESPONSE:{
            handleScrollTextResp(msg);
            break;
        }
        case MSGCODE_QUNEWM_RESPONSE:{
            handleWanJiaQunResp(msg);
            break;
        }
        case MSGCODE_GONGGAO_RESPONSE:{
            handleNoticeResp(msg);
            break;
        }
        case MSGCODE_APPLE_SWITCH_RESPONE:{
            handleGamePayType(msg);
            break;
        }
        case MSGCODE_PLAY_BACK_RESPONE:{
            handleFupanInfo(msg);
            break;
        }
        case MSGCODE_FUPAN_PLAYER_NOTIFY:{
            handleFupanPlayerInfo(msg);
            break;
        }
        case MSGCODE_FANGZHU_OUT:{
            fangZhuLeaveRoom(msg);
            break;
        }
        case MSGCODE_SPREAD_NEWUSER_RESPONSE:{
            handleTuiGuangInfo(msg);
            break;
        }
        case MSGCODE_SPREAD_NEWUSER_REWARD_RESPNOSE:{
            handleTuiGuangPrideInfo(msg);
            break;
        }
        default:
            break;
    }
}

void MsgHandler::postNotifyMessage(std::string event_name, std::string msg){
    char* buf = const_cast<char*>(msg.c_str());
    _eventDispatcher->dispatchCustomEvent(event_name, buf);
}

void MsgHandler::postNotifyMessage2(std::string event_name, void* msg){
    _eventDispatcher->dispatchCustomEvent(event_name, msg);
}


// 玩家群二维码版本号回复 {code:6,ver1:"1",desc1:"33",ver2:"2",desc2:"33"}
void MsgHandler::handleWanJiaQunResp(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if(_mDoc.HasMember("ver1")){
        const rapidjson::Value &ver1 = _mDoc["ver1"];
        GAMEDATA::getInstance()->setWanJiaQunVer(atoi(ver1.GetString()));
    }
    if(_mDoc.HasMember("ver2")){
        const rapidjson::Value &ver2 = _mDoc["ver2"];
        GAMEDATA::getInstance()->setDailiQunVer(atoi(ver2.GetString()));
    }
    if(_mDoc.HasMember("desc1")){
        const rapidjson::Value &desc1 = _mDoc["desc1"];
        GAMEDATA::getInstance()->setWanJiaQun(desc1.GetString());
    }
    if(_mDoc.HasMember("desc2")){
        const rapidjson::Value &desc2 = _mDoc["desc2"];
        GAMEDATA::getInstance()->setDaiLiQun(desc2.GetString());
    }
    postNotifyMessage(MSG_WAN_JIA_WEI_XIN_QUN, "");
}

//{code:107, poxiaoId : poxiaoId, roomstyle : [{rsid:"1111", rsname : "ddd"}, { rsid:"1112", rsname : "dddd" }]}
void MsgHandler::roomListResp(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &roomstyle = _mDoc["roomstyle"];
    RoomListData* roomlist = new RoomListData();
    for (int i = 0; i < roomstyle.Capacity(); ++i){
        RoomData data;
        const rapidjson::Value &temp = roomstyle[i];
        data.roomId = temp["rsid"].GetInt();
        data.maxGold = temp["max"].GetInt();
        data.minGold = temp["min"].GetInt();
        data.base = temp["base"].GetInt();
        data.hua = temp["hua"].GetInt();
        roomlist->rooms.push_back(data);
    }
    postNotifyMessage2(MSG_ROOM_LIST_RESP,roomlist);
    CC_SAFE_DELETE(roomlist);
}

//{code:1001,poxiaoId:poxiaoId,result:"0",seatId:1,
//other:[{seatId:seatId,gold:0,diamond:0,jifen:0,lequan:0,gender:0,nickname:'aaa',ifready:1}]}
void MsgHandler::enterRoomResp(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    GAMEDATA::getInstance()->clearPlayersInfo();//清除全部的玩家数据
    EnterRoomResp* resp = new EnterRoomResp();
    const rapidjson::Value &result = _mDoc["result"];
    resp->result = StringUtil::itos(result.GetInt());
    if(_mDoc.HasMember("rsid")){
        const rapidjson::Value &rsid = _mDoc["rsid"];
        resp->rsid = rsid.GetString();
    }
    if(_mDoc.HasMember("money")){
        const rapidjson::Value &money = _mDoc["money"];
        resp->money = money.GetString();
    }
    if(_mDoc.HasMember("gold")){
        const rapidjson::Value &gold = _mDoc["gold"];
        resp->gold = gold.GetString();
    }
    if(_mDoc.HasMember("id")){
        const rapidjson::Value &payid = _mDoc["id"];
        resp->payid = payid.GetString();
    }
    if(_mDoc.HasMember("min")){
        const rapidjson::Value &min = _mDoc["min"];
        resp->min = min.GetString();
    }
    //进入房间成功才会有其他玩家的数据
    if (result.GetInt() == 1){
        const rapidjson::Value &seatId = _mDoc["seatId"];
        GAMEDATA::getInstance()->setHeroSeatId(seatId.GetInt());
        if (_mDoc.HasMember("other")){
            const rapidjson::Value &pArr = _mDoc["other"];
            for (int i = 0; i < pArr.Capacity(); ++i){
                const rapidjson::Value &temp = pArr[i];
                auto seatId = temp["seatId"].GetInt();
                auto gold = temp["gold"].GetInt();
                auto diamond = temp["diamond"].GetInt();
                auto jifen = temp["jifen"].GetInt();
                auto lequan = temp["lequan"].GetInt();
                auto gender = temp["gender"].GetInt();
                auto ifready = temp["ifready"].GetInt();
                auto nickname = temp["nickname"].GetString();
                auto poxiaoId = temp["poxiaoId"].GetString();
                auto lockdiamond = temp["bangzuan"].GetInt();
                auto fangka = temp["fangka"].GetDouble();
                auto pic = temp["pic"].GetString();
                Player* info = new Player();
                info->setPoxiaoId(poxiaoId);
                info->setSeatId(seatId);
                info->setBanker(false);
                info->setIsReady(ifready == 0 ? false : true);
                info->setGold(gold);
                info->setDiamond(diamond);
                info->setLockDiamond(lockdiamond);
                info->setFangka(fangka);
                info->setScore(jifen);
                info->setGender(gender);
                info->setNickname(nickname);
                if(temp.HasMember("ip")){
                    auto ip = temp["ip"].GetString();
                    info->setIP(ip);
                }
                info->setTicket(lequan);
                info->setPicture(pic);
                GAMEDATA::getInstance()->addPlayersInfo(info);
            }
        }
    }
    //构造自己的数据添加到玩家列表中
    Player* info = new Player();
    info->setSeatId(GAMEDATA::getInstance()->getHeroSeatId());
    info->setPoxiaoId(UserData::getInstance()->getPoxiaoId());
    info->setIsReady(false);
    info->setTicket(UserData::getInstance()->getTicket());
    info->setGold(UserData::getInstance()->getGold());
    info->setGender(UserData::getInstance()->getGender());
    info->setNickname(UserData::getInstance()->getNickName());
    info->setPicture(UserData::getInstance()->getPicture());
    info->setFangka(UserData::getInstance()->getFangkaNum());
    info->setIP(GAMEDATA::getInstance()->getIP());
    info->setUmark(UserData::getInstance()->getMarkId());
    info->setScore(GAMEDATA::getInstance()->getScore());
    GAMEDATA::getInstance()->addPlayersInfo(info);
    
    postNotifyMessage2(MSG_ENTER_ROOM_RESP, resp);
    CC_SAFE_DELETE(resp);
}

//{code:1005, result : 0, poxiaoId : poxiaoId, mobile : "1111", username : "avc", password : "123", result : 1,
//gold : 0, diamond : 0, jifen : 0, lequan : 0, gender : 0, nickname : 'aaa', level : "滚地龙",
//firstcharge : "1", ischacc : "1"}result0 用户名密码错误 1成功 2 用户名已存在 3验证码错误  4其他错误   gender性别0女1男
void MsgHandler::loginResp(std::string msg){
    
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    
    const rapidjson::Value &result = _mDoc["result"];
    if (result.GetInt() == 1){
        const rapidjson::Value &poxiaoId = _mDoc["poxiaoId"];
        UserData::getInstance()->setPoxiaoId(poxiaoId.GetString());
        const rapidjson::Value &nickname = _mDoc["nickname"];
        UserData::getInstance()->setNickName(nickname.GetString());
        const rapidjson::Value &gold = _mDoc["gold"];
        UserData::getInstance()->setGold(gold.GetInt());
        const rapidjson::Value &fangka = _mDoc["fangka"];
        UserData::getInstance()->setFangkaNum(fangka.GetDouble());
        const rapidjson::Value &gender = _mDoc["gender"];
        UserData::getInstance()->setGender(gender.GetInt());
        const rapidjson::Value &lequan = _mDoc["lequan"];
        UserData::getInstance()->setTicket(lequan.GetInt());
        if(_mDoc.HasMember("mobile")){
            const rapidjson::Value &mobile = _mDoc["mobile"];
            UserData::getInstance()->setBoundPhone(mobile.GetString());
        }else{
            UserData::getInstance()->setBoundPhone("unknow");
        }
        if (_mDoc.HasMember("pic")){
            const rapidjson::Value &pic = _mDoc["pic"];
            UserData::getInstance()->setPicture(pic.GetString());
        }
        if (_mDoc.HasMember("firstcharge")){
            const rapidjson::Value &firstcharge = _mDoc["firstcharge"];//首充
            UserData::getInstance()->setFirstCharge(firstcharge.GetInt() == 1 ? true : false);
        }
        if (_mDoc.HasMember("ischacc")){
            const rapidjson::Value &ischacc = _mDoc["ischacc"];
            UserData::getInstance()->setChangeName( ischacc.GetInt() == 1 ? true : false);
        }
        if (_mDoc.HasMember("username")){
            const rapidjson::Value &username = _mDoc["username"];
            UserData::getInstance()->setUserName(username.GetString());
        }
        if (_mDoc.HasMember("password")){
            const rapidjson::Value &password = _mDoc["password"];
            UserData::getInstance()->setPassword(password.GetString());
        }
        if (_mDoc.HasMember("umark")){
            const rapidjson::Value &umark = _mDoc["umark"];
            UserData::getInstance()->setMarkId(umark.GetString());
        }
        if(_mDoc.HasMember("ip")){
            const rapidjson::Value &ip = _mDoc["ip"];
            GAMEDATA::getInstance()->setIP(ip.GetString());
        }
        postNotifyMessage(MSG_LOGIN_RESP, LOGIN_SUCCESS);
    }
    else{
        postNotifyMessage(MSG_LOGIN_RESP, "");
    }
}

//{code:1008,result:0,poxiaoId:poxiaoId,seatId:seatId,gold:0,diamond:0,jifen:0,lequan:0,gender:0,nickname:'aaa',ifready:0}
void MsgHandler::addPalyer(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &seatId = _mDoc["seatId"];
    const rapidjson::Value &gold = _mDoc["gold"];
    const rapidjson::Value &diamond = _mDoc["diamond"];
    const rapidjson::Value &lockdiamond = _mDoc["bangzuan"];
    const rapidjson::Value &jifen = _mDoc["jifen"];
    const rapidjson::Value &lequan = _mDoc["lequan"];
    const rapidjson::Value &gender = _mDoc["gender"];
    const rapidjson::Value &nickname = _mDoc["nickname"];
    const rapidjson::Value &ifready = _mDoc["ifready"];
    const rapidjson::Value &pId = _mDoc["pId"];
    const rapidjson::Value &pic = _mDoc["pic"];
    const rapidjson::Value &fangka = _mDoc["fangka"];
    
    Player* info = new Player();
    info->setSeatId(seatId.GetInt());
    if (seatId.GetInt() == 1){
        info->setBanker(true);
    }
    else{
        info->setBanker(false);
    }
    info->setPoxiaoId(pId.GetString());
    info->setGold(gold.GetInt());
    info->setDiamond(diamond.GetInt());
    info->setLockDiamond(lockdiamond.GetInt());
    info->setScore(jifen.GetInt());
    info->setGender(gender.GetInt());
    info->setNickname(nickname.GetString());
    info->setTicket(lequan.GetInt());
    info->setPicture(pic.GetString());
    info->setIsReady(ifready.GetInt() == 0 ? false : true);
    info->setIsReady(false);
    info->setFangka(fangka.GetDouble());
    if(_mDoc.HasMember("ip")){
        const rapidjson::Value &ip = _mDoc["ip"];
        info->setIP(ip.GetString());
    }
    if(_mDoc.HasMember("umark")){
        const rapidjson::Value &umark = _mDoc["umark"];
        info->setUmark(umark.GetString());
    }
    GAMEDATA::getInstance()->addPlayersInfo(info);
    GAMEDATA::getInstance()->setNeedAddPlayer(true);//为了解决场景跳转会有消息丢失的问题
}


//{{code:1009, poxiaoId : poxiaoId, seatId : 1 }
void MsgHandler::showOtherReady(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    //	const rapidjson::Value &poxiaoId = _mDoc["poxiaoId"];
    const rapidjson::Value &seatId = _mDoc["seatId"];
    vector<Player*> players = GAMEDATA::getInstance()->getPlayersInfo();
    for (int i = 0; i < players.size(); i++){
        if(players.at(i)->getSeatId() == seatId.GetInt() ){
            players.at(i)->setIsReady(true);
        }
    }
    postNotifyMessage(MSG_READY_NOTIFY, StringUtil::itos(seatId.GetInt()));
}

//{code:2002, poxiaoId : poxiaoId, start : 1, poker : 1, 2, 4, 5, 6}
void MsgHandler::getHeroJongs(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    
    MahjongFaPaiData* faPaiData = new MahjongFaPaiData();
    faPaiData->heroPokers = _mDoc["poker"].GetString();
    faPaiData->dice = _mDoc["dice"].GetString();
    faPaiData->kaibao = _mDoc["kb"].GetString();
    faPaiData->huangfan = _mDoc["hf"].GetString();
    faPaiData->dice = _mDoc["dice"].GetString();
    faPaiData->start = _mDoc["start"].GetInt();
    if(_mDoc.HasMember("prjucount")){
        faPaiData->prjucount = _mDoc["prjucount"].GetInt();
    }
    ReplaceJongVec  replaceVec;
    const rapidjson::Value &hua = _mDoc["hua"];
    const rapidjson::Value &rest = _mDoc["rest"];
    replaceVec.rest = rest.GetString();
    for (int i = 0; i < hua.Capacity(); i++){
        const rapidjson::Value &player = hua[i];
        ReplaceJong replacePoker;
        replacePoker.seatId = player["seatId"].GetInt();
        const rapidjson::Value &poker = player["poker"];
        for (int i = 0; i < poker.Capacity(); ++i){
            const rapidjson::Value &temp = poker[i];
            auto pokers = temp["poker"].GetString();
            auto replace = temp["replace"].GetString();
            replacePoker.poker.push_back(pokers);
            replacePoker.replace.push_back(replace);
        }
        replaceVec.times.push_back(replacePoker);
    }
    faPaiData->mjReplaceVec = replaceVec;
    PlayerCpgtData tingData;
    if(_mDoc.HasMember("angang")){
        const rapidjson::Value &angang = _mDoc["angang"];
        tingData.gang = angang.GetString();
        tingData.flag = 1;
        tingData.seatId = GAMEDATA::getInstance()->getHeroSeatId();
    }
    if(_mDoc.HasMember("ting")){
        const rapidjson::Value &ting = _mDoc["ting"];
        tingData.seatId = GAMEDATA::getInstance()->getHeroSeatId();
        tingData.ting = ting.GetString();
    }
    faPaiData->mjTingData = tingData;
    postNotifyMessage2(MSG_GAME_START_FAPAI_NOTIFY, faPaiData);
    CC_SAFE_DELETE(faPaiData);
}

 //{"code":2005,"poker":"28","poxiaoId":"e8fec2c3-47ba-4063-ad07-6b7c014c4dca","seatId":3}
void MsgHandler::showOtherPlayedJong(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &poker = _mDoc["poker"];
    const rapidjson::Value &seatId = _mDoc["seatId"];
    std::string resultMsg = StringUtils::format("%d,%s",seatId.GetInt(),poker.GetString());
    postNotifyMessage(MSG_OTHER_PALYER_JONG, resultMsg);
}

//{code:2006,poxiaoId:poxiaoId,seatId:seatId,poker:1,chi:[{chi:1,2,3},{chi:2,3,4}],peng:"1,2,3",gang:"1,1,1,1"}
void MsgHandler::showCpgNotify(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &poker = _mDoc["poker"];
    const rapidjson::Value &seatId = _mDoc["sId"];
    PlayerCpgtData* cpgData = new PlayerCpgtData();
    cpgData->poker = poker.GetString();
    cpgData->sId = seatId.GetInt();
    if (_mDoc.HasMember("chi")){
        const rapidjson::Value &chi = _mDoc["chi"];
        for (int i = 0; i < chi.Capacity(); ++i){
            const rapidjson::Value &temp = chi[i];
            cpgData->chi.push_back(temp["chi"].GetString());
        }
        sort(cpgData->chi.begin(), cpgData->chi.end());
    }
    if (_mDoc.HasMember("peng")){
        const rapidjson::Value &peng = _mDoc["peng"];
        cpgData->peng = peng.GetString();
    }
    if (_mDoc.HasMember("gang")){
        const rapidjson::Value &gang = _mDoc["gang"];
        cpgData->gang = gang.GetString();
        cpgData->flag = 0;
    }
    postNotifyMessage2(MSG_PLAYER_CPG, cpgData);
    CC_SAFE_DELETE(cpgData);
}

 // {code:2010,poxiaoId:poxiaoId,seatId:seatId,chi:"1,2",poker:poker}
void MsgHandler::showOtherChiNotify(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &poker = _mDoc["poker"];
    const rapidjson::Value &seatId = _mDoc["seatId"];
    const rapidjson::Value &chi = _mDoc["chi"];
    const rapidjson::Value &sId = _mDoc["sId"];
    PlayerCpgtData* cpgData = new PlayerCpgtData();
    cpgData->poker = poker.GetString();
    cpgData->seatId = seatId.GetInt();
    cpgData->chi.push_back(chi.GetString());
    cpgData->sId = sId.GetInt();
    postNotifyMessage2(MSG_OTHER_PLAYER_CHI, cpgData);
    CC_SAFE_DELETE(cpgData);
}

//{"code":2014,"peng":"25,25","poker":"25","poxiaoId":"cac1681d-28e2-4b1e-b0d3-b47c249b8979","sId":0,"seatId":3}
void MsgHandler::showOtherPengNotify(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &poker = _mDoc["poker"];
    const rapidjson::Value &seatId = _mDoc["seatId"];
    const rapidjson::Value &pengPoker = _mDoc["peng"];
    const rapidjson::Value &sId = _mDoc["sId"];
    PlayerCpgtData* data = new PlayerCpgtData();
    data->poker = poker.GetString();
    data->seatId = seatId.GetInt();
    data->peng = pengPoker.GetString();
    data->sId = sId.GetInt();
    postNotifyMessage2(MSG_OTHER_PLAYER_PENG, data);
    CC_SAFE_DELETE(data);
}

//{"code":2018,"flag":"1","gang":"18,18,18","poker":18,"poxiaoId":"9cbc6365-5be4-4c33-bc9e-a00c17ac4697","sId":0,"seatId":3}
void MsgHandler::showOtherGangNotify(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &poker = _mDoc["poker"];
    const rapidjson::Value &seatId = _mDoc["seatId"];
    const rapidjson::Value &gang = _mDoc["gang"];
    const rapidjson::Value &flag = _mDoc["flag"];
    const rapidjson::Value &sId = _mDoc["sId"];
    PlayerCpgtData* cpgData = new PlayerCpgtData();
    cpgData->flag = atoi(flag.GetString());
    cpgData->poker = poker.GetString();
    cpgData->seatId = seatId.GetInt();
    cpgData->gang = gang.GetString();
    cpgData->sId = sId.GetInt();
    postNotifyMessage2(MSG_OTHER_PLAYER_GANG, cpgData);
    CC_SAFE_DELETE(cpgData);
}

void MsgHandler::nextPlayer(std::string msg){
    //{code:2019,poxiaoId:poxiaoId,seatId:seatId,poker:{poker:1,hua:32,33}}
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    PlayerTurnData playerTurnData;
    playerTurnData.seatId = _mDoc["seatId"].GetInt();
    if (_mDoc.HasMember("poker")){
        const rapidjson::Value &poker = _mDoc["poker"];
        const rapidjson::Value &finalPoker = poker["poker"];
        playerTurnData.poker = finalPoker.GetInt();
        if (poker.HasMember("hua")){
            const rapidjson::Value &hua = poker["hua"];
            playerTurnData.replace = hua.GetString();
        }
    }
    const rapidjson::Value &rest = _mDoc["rest"];
    playerTurnData.rest = rest.GetString();
    
    PlayerCpgtData tingData;
    tingData.seatId = _mDoc["seatId"].GetInt();
    if (_mDoc.HasMember("ting")){
        const rapidjson::Value &ting = _mDoc["ting"];
        tingData.ting = ting.GetString();
        //为了解决吃听不起牌的bug加的这3行代码
        HeroCpgRespData heroTingData;
        heroTingData.ting = ting.GetString();
        GAMEDATA::getInstance()->setHeroCpgResp(heroTingData);
    }
    if (_mDoc.HasMember("angang")){
        const rapidjson::Value &angang = _mDoc["angang"];
        tingData.gang = angang.GetString();
        tingData.flag = 1;
    }
    if (_mDoc.HasMember("penggang")){
        const rapidjson::Value &penggang = _mDoc["penggang"];
        tingData.gang = penggang.GetString();
        tingData.flag = 2;
    }
    if (_mDoc.HasMember("ting") || _mDoc.HasMember("angang") || _mDoc.HasMember("penggang")){
        //        GAMEDATA::getInstance()->setPlayerCpgt(tingData);
        playerTurnData.hastinggang = true;
    }
    GAMEDATA::getInstance()->setPlayerTurn(playerTurnData);
    postNotifyMessage(MSG_PLAYER_TURN_WHO, "");
    
}


void MsgHandler::heroTingMsg(std::string msg){
    //MSGCODE_MAJIANG_TING_GANG_NOTIFY
    //{ code:2020, poxiaoId : poxiaoId, seatId : seatId, ting : "1,2,3", angang : "1,1,1,1", penggang : "1" }
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &seatId = _mDoc["seatId"];
    PlayerCpgtData tingData;
    tingData.seatId = seatId.GetInt();
    if (_mDoc.HasMember("ting")){
        const rapidjson::Value &ting = _mDoc["ting"];
        tingData.ting = ting.GetString();
    }
    if (_mDoc.HasMember("angang")){
        const rapidjson::Value &angang = _mDoc["angang"];
        tingData.gang = angang.GetString();
        tingData.flag = 1;
    }
    if (_mDoc.HasMember("penggang")){
        const rapidjson::Value &penggang = _mDoc["penggang"];
        tingData.gang = penggang.GetString();
        tingData.flag = 2;
    }
    //    GAMEDATA::getInstance()->setPlayerCpgt(tingData);
    postNotifyMessage(MSG_HERO_TING_GANG, "");
}

void MsgHandler::playerTingResp(std::string msg){
    //{code:2023,poxiaoId:poxiaoId,seatId:seatId,result:1}
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &result = _mDoc["result"];
    postNotifyMessage(MSG_PLAYER_TING_RESP, StringUtil::itos(result.GetInt()));
}

void MsgHandler::gameResultNotify(std::string msg){
    //{code:2024,poxiaoId:poxiaoId,
    //finish:[{result:1,hutype:1,2,3,seatId:1,nickname:"rr",gold:0,diamond:0,jifen:0,lequan:0,
    //golddelta:0,diamonddelta:0,jifendelta:0,lequandelta:0},
    //{result:1,hutype:1,2,3,seatId:1,nickname:"rr",gold:0,diamond:0,jifen:0,lequan:0,
    //golddelta:0,diamonddelta:0,jifendelta:0,lequandelta:0}]}
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if(_mDoc.HasMember("poker")){
        GAMEDATA::getInstance()->setDiaopao(_mDoc["poker"].GetString());
    }else{
        GAMEDATA::getInstance()->setDiaopao("");
    }
    if(_mDoc.HasMember("lezi")){
        GAMEDATA::getInstance()->setPrivateLezi(_mDoc["lezi"].GetString());
    }
    if(_mDoc.HasMember("ifkb")){
        GAMEDATA::getInstance()->setPrivateKaibao(_mDoc["ifkb"].GetString());
    }
    if(_mDoc.HasMember("ifemsc")){
        GAMEDATA::getInstance()->setPrivateEmsc(_mDoc["ifemsc"].GetString());
    }
    if(_mDoc.HasMember("fzId")){
        GAMEDATA::getInstance()->setFangZhuId(_mDoc["fzId"].GetString());
    }
    
    if(_mDoc.HasMember("prjucount")){
        GAMEDATA::getInstance()->setPrivateRoomType(_mDoc["prjucount"].GetString());
    }
    if(_mDoc.HasMember("fee")){
        GAMEDATA::getInstance()->setFee(_mDoc["fee"].GetString());
    }
    const rapidjson::Value &flag = _mDoc["flag"];
    const rapidjson::Value &finish = _mDoc["finish"];
    vector<GameResultData> gameResults;
    for (int i = 0; i < finish.Capacity(); ++i){
        GameResultData resultData;
        const rapidjson::Value &temp = finish[i];
        resultData.result = temp["result"].GetInt();
        if (temp.HasMember("gold")){
            resultData.gold = temp["gold"].GetInt();
        }
        if (temp.HasMember("golddelta")){
            resultData.golddelta = temp["golddelta"].GetInt();
        }
        if (temp.HasMember("jifen")){
            resultData.jifen = temp["jifen"].GetInt();
        }
        if (temp.HasMember("jifendelta")){
            resultData.jifendelta = temp["jifendelta"].GetInt();
        }
        if (temp.HasMember("lequan")){
            resultData.lequan = temp["lequan"].GetInt();
        }
        if (temp.HasMember("lequandelta")){
            resultData.lequandelta = temp["lequandelta"].GetInt();
        }
        if(temp.HasMember("pic")){
            resultData.pic = temp["pic"].GetString();
        }
        resultData.seatId = temp["seatId"].GetInt();
        resultData.showPoker = temp["poker"].GetString();
        if (temp.HasMember("hua")){
            resultData.hua = temp["hua"].GetInt();
        }
        if (temp.HasMember("hutype")){
            resultData.huType = temp["hutype"].GetString();
        }
        else{
            resultData.huType = "";
        }
        if (temp.HasMember("umark")){
            resultData.umark = temp["umark"].GetString();
        }
        if (temp.HasMember("fan")){
            resultData.fan = temp["fan"].GetString();
        }
        if (temp.HasMember("nickname")){
            resultData.nickName = temp["nickname"].GetString();
        }
        if (temp.HasMember("lost")){
            resultData.lost = temp["lost"].GetString();
        }
        if (temp.HasMember("win")){
            resultData.win = temp["win"].GetString();
        }
        if (temp.HasMember("even")){
            resultData.even = temp["even"].GetString();
        }
        if (temp.HasMember("lz")){
            resultData.lz = temp["lz"].GetString();
        }
        if (temp.HasMember("poxiaoId")){
            resultData.poxiaoId = temp["poxiaoId"].GetString();
        }
        gameResults.push_back(resultData);
    }
    //对GameResult进行一次排序
    vector<GameResultData> rankGameResults;
    for(int i= 0;i<gameResults.size();i++){
        if(gameResults.at(i).seatId ==  GAMEDATA::getInstance()->getHeroSeatId()){
            for(int j=i;j<gameResults.size();j++){
                rankGameResults.push_back(gameResults.at(j));
            }
            for(int k=0;k<i;k++){
                rankGameResults.push_back(gameResults.at(k));
            }
        }
    }
    GAMEDATA::getInstance()->setGameResults(rankGameResults);
    postNotifyMessage(MSG_GAME_RESULT, flag.GetString());
}


void MsgHandler::playerTingNotify(std::string msg){
    //{code:2025,poxiaoId:poxiaoId,seatId:seatId}
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &seatId = _mDoc["seatId"];
    GAMEDATA::getInstance()->setCurrentTingSeatId(seatId.GetInt());
    postNotifyMessage(MSG_PLAYER_TING_NOTIFY, "");
}


void MsgHandler::playerConnectAgain(std::string msg){
    //  {code:2031,poxiaoId:poxiaoId,seatId:1,lord:1,rest:"123",status:1,all:[{seatId:1,hua:"1",chi:[{chi:"1,2,3",poker:"3"},{chi:"11,12,13",poker:"13"}],peng:[{peng:"11",peId:"1"},{peng:"12",peId:"2"}],gang:[{gang:"11",gaId:"1"},{gang:"12",gaId:"2"}],angang:"6",out:"11,22,33,44",gold:0,diamond:0,jifen:0,lequan:0,gender:0,nickname:'aaa',hand:"2",status:1}]} status1为听牌
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if(_mDoc.HasMember("poxiaoId")){
        const rapidjson::Value &poxiaoId = _mDoc["poxiaoId"];
        UserData::getInstance()->setPoxiaoId(poxiaoId.GetString());
    }
    if(_mDoc.HasMember("umark")){
        const rapidjson::Value &umark = _mDoc["umark"];
        UserData::getInstance()->setMarkId(umark.GetString());
    }
    FriendOpenRoomRespData opdata;
    if(_mDoc.HasMember("prjushu")){
        const rapidjson::Value &prjushu = _mDoc["prjushu"];
        opdata.prjushu = prjushu.GetString();
    }
    if(_mDoc.HasMember("prId")){
        const rapidjson::Value &prId = _mDoc["prId"];
        opdata.prid = prId.GetString();
    }
    if(_mDoc.HasMember("fzId")){
        const rapidjson::Value &fzId = _mDoc["fzId"];
        GAMEDATA::getInstance()->setFangZhuId(fzId.GetString());
    }
    if(_mDoc.HasMember("prjucount")){
        const rapidjson::Value &prjucount = _mDoc["prjucount"];
        opdata.prjucount = prjucount.GetString();
    }
    if(_mDoc.HasMember("ifkb")){
        GAMEDATA::getInstance()->setPrivateKaibao(_mDoc["ifkb"].GetString());
    }
    if(_mDoc.HasMember("ifemsc")){
        GAMEDATA::getInstance()->setPrivateEmsc(_mDoc["ifemsc"].GetString());
    }
    if(_mDoc.HasMember("iflezi")){
        GAMEDATA::getInstance()->setPrivateLezi(_mDoc["iflezi"].GetString());
    }
    GAMEDATA::getInstance()->setFriendOpenRoomResp(opdata);
    const rapidjson::Value &seatId = _mDoc["seatId"];
    const rapidjson::Value &rest = _mDoc["rest"];
    const rapidjson::Value &loard = _mDoc["lord"];
    const rapidjson::Value &isprivate = _mDoc["isprivate"];
    const rapidjson::Value &kb = _mDoc["kb"];
    const rapidjson::Value &hf = _mDoc["hf"];
    const rapidjson::Value &turn = _mDoc["turn"];
    GAMEDATA::getInstance()->setHeroSeatId(seatId.GetInt());
    //设置是否是私人房间
    std::string roomType = isprivate.GetString();
    GAMEDATA::getInstance()->setMahjongRoomType(roomType == "1" ? (MahjongRoom::privateRoom):(MahjongRoom::publicRoom));
    LastGameData lastGameData;
    lastGameData.result = 1;//游戏中
    lastGameData.seatId = seatId.GetInt();
    lastGameData.rest = rest.GetString();
    lastGameData.loard = loard.GetInt();
    lastGameData.kb = kb.GetInt();
    lastGameData.hf = hf.GetInt();
    lastGameData.turn = turn.GetInt();
    if(_mDoc.HasMember("pre")){
        const rapidjson::Value &pre = _mDoc["pre"];
        lastGameData.pre = pre.GetInt();
    }
    const rapidjson::Value &all = _mDoc["all"];
    for (int i = 0; i < all.Capacity(); ++i){
        PlayerGameData  data;
        const rapidjson::Value &temp = all[i];
        data.poxiaoId = temp["poxiaoId"].GetString();
        data.seatId = temp["seatId"].GetInt();
        data.status = temp["status"].GetInt();
        data.gold = temp["gold"].GetInt();
        data.jifen = temp["jifen"].GetInt();
        data.bangzuan = temp["bangzuan"].GetInt();
        data.lequan = temp["lequan"].GetInt();
        data.diamond = temp["diamond"].GetInt();
        data.lequan = temp["lequan"].GetInt();
        data.fangka = temp["fangka"].GetDouble();
        data.hua = temp["hua"].GetInt();
        data.tru = temp["tru"].GetInt();
        data.ifready = 1;
        data.isOnline = temp["isonline"].GetInt();
        if(data.seatId == GAMEDATA::getInstance()->getHeroSeatId()&&data.status== 1){
            GAMEDATA::getInstance()->setIsTingState(true);
        }
        if(temp.HasMember("chi")){
            const rapidjson::Value &chi = temp["chi"];
            for(int j = 0; j < chi.Capacity(); ++j){
                const rapidjson::Value &temp2 = chi[j];
                PlayerChiData chiDa;
                chiDa.chi = temp2["chi"].GetString();
                chiDa.poker = temp2["poker"].GetString();
                data.chiData.push_back(chiDa);
            }
        }
        if(temp.HasMember("peng")){
            const rapidjson::Value &peng = temp["peng"];
            for(int j = 0; j < peng.Capacity(); ++j){
                const rapidjson::Value &temp3 = peng[j];
                PlayerPengData pengDa;
                pengDa.peng = temp3["peng"].GetString();
                pengDa.peId = temp3["peId"].GetString();
                data.pengData.push_back(pengDa);
            }
        }
        if(temp.HasMember("gang")){
            const rapidjson::Value &gang = temp["gang"];
            for(int j = 0; j < gang.Capacity(); ++j){
                const rapidjson::Value &temp4 = gang[j];
                PlayerGangData pengDa;
                pengDa.gang = temp4["gang"].GetString();
                pengDa.gaId = temp4["gaId"].GetString();
                data.gangData.push_back(pengDa);
            }
        }
        data.angang = temp["angang"].GetString();
        data.hand = temp["hand"].GetString();
        data.outhand = temp["out"].GetString();
        data.nickname =temp["nickname"].GetString();
        data.pic =temp["pic"].GetString();
        data.gender = temp["gender"].GetInt();
        if(temp.HasMember("ip")){
            data.ip = temp["ip"].GetString();
        }
        if(temp.HasMember("umark")){
            data.umark = temp["umark"].GetString();
        }
        lastGameData.players.push_back(data);
    }
    GAMEDATA::getInstance()->setLastGameDataBackup(lastGameData);
    postNotifyMessage(MSG_PLAYER_CONNECT_AGAIN, StringUtil::itos(seatId.GetInt()));
}


void MsgHandler::changeGenderResp(std::string msg){
    // {code:118,result:"1"}
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &result = _mDoc["result"];
    if(_mDoc.HasMember("gender")){
        const rapidjson::Value &gender = _mDoc["gender"];
        UserData::getInstance()->setGender(gender.GetInt());
    }
    if(_mDoc.HasMember("pic")){
        const rapidjson::Value &pic = _mDoc["pic"];
        UserData::getInstance()->setPicture(pic.GetString());
    }
    postNotifyMessage(MSG_CHANGE_GENDER_RESP, StringUtil::itos(result.GetInt()));
}

void MsgHandler::heroChiResp(std::string msg){
    // {code:2009,poxiaoId:poxiaoId,seatId:seatId,result:1,ting:"1,2,3"}
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    HeroCpgRespData cpgRespData;
    const rapidjson::Value &result = _mDoc["result"];
    cpgRespData.result = result.GetInt();
    if (_mDoc.HasMember("ting")){
        const rapidjson::Value &ting = _mDoc["ting"];
        cpgRespData.ting = ting.GetString();
    }
    else{
        cpgRespData.ting = "";
    }
    if (_mDoc.HasMember("forbit")){
        const rapidjson::Value &forbit = _mDoc["forbit"];
        cpgRespData.forbit = forbit.GetString();
    }
    GAMEDATA::getInstance()->setHeroCpgResp(cpgRespData);
    postNotifyMessage(MSG_HERO_CHI_RESP, "");
}

void MsgHandler::heroPengResp(std::string msg){
    //{code:2013,poxiaoId:poxiaoId,seatId:seatId,result:1}
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    HeroCpgRespData cpgRespData;
    const rapidjson::Value &result = _mDoc["result"];
    cpgRespData.result = result.GetInt();
    if (_mDoc.HasMember("ting")){
        const rapidjson::Value &result = _mDoc["ting"];
        cpgRespData.ting = result.GetString();
    }
    else{
        cpgRespData.ting = "";
    }
    GAMEDATA::getInstance()->setHeroCpgResp(cpgRespData);
    postNotifyMessage(MSG_HERO_PENG_RESP, "");
}

void MsgHandler::heroGangResp(std::string msg){
    // {code:2017,poxiaoId:poxiaoId,seatId:seatId,result:1}
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    HeroCpgRespData cpgRespData;
    const rapidjson::Value &result = _mDoc["result"];
    cpgRespData.result = result.GetInt();
    if (_mDoc.HasMember("ting")){
        const rapidjson::Value &result = _mDoc["ting"];
        cpgRespData.ting = result.GetString();
    }
    else{
        cpgRespData.ting = "";
    }
    GAMEDATA::getInstance()->setHeroCpgResp(cpgRespData);
    postNotifyMessage(MSG_HERO_GANG_RESP, "");
}

void MsgHandler::removePlayerNotify(std::string msg){
    //{code:2001, poxiaoId : poxiaoId, seatId : seatId}
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &seatId = _mDoc["seatId"];
    const rapidjson::Value &pId = _mDoc["pId"];
    RemovePlayerData data;
    data.pid = pId.GetString();
    data.setaId = seatId.GetInt();
    if(data.pid != UserData::getInstance()->getPoxiaoId()){
        GAMEDATA::getInstance()->erasePlayersInfo(data.pid);
    }else{
        log("hero is out room");
        GAMEDATA::getInstance()->clearPlayersInfo();
        GAMEDATA::getInstance()->setIsGotoLobby(true);
        GAMEDATA::getInstance()->setFangZhuId("");
        GAMEDATA::getInstance()->setPrivateGameNum("0");
    }
    GAMEDATA::getInstance()->setRemovePlayer(data);
    postNotifyMessage(MSG_PLAYER_REMOVE, "");
}



void MsgHandler::friendOpenRoomNotify(std::string msg){
    // {code:2037,poxiaoId:"123",nickname:"aaa",pId:"456"}
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &nickname = _mDoc["nickname"];
    const rapidjson::Value &pId = _mDoc["pId"];
    FriendOpenRoomNotifyData data;
    data.nickname = nickname.GetString();
    data.pid = pId.GetString();
    GAMEDATA::getInstance()->setFriendOpenRoomNotify(data);
    postNotifyMessage(MSG_FRIEND_OPEN_ROOM_NOTIFY, "");
}

void MsgHandler::friendOpenRoomResp(std::string msg){
    //{code:2038,poxiaoId:poxiaoId,result:"0",seatId:1}
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if(_mDoc.HasMember("poxiaoId")){
        const rapidjson::Value &poxiaoId = _mDoc["poxiaoId"];
        UserData::getInstance()->setPoxiaoId(poxiaoId.GetString());
    }
    if(_mDoc.HasMember("umark")){
        const rapidjson::Value &umark = _mDoc["umark"];
        UserData::getInstance()->setMarkId(umark.GetString());
    }
    if(_mDoc.HasMember("ifkb")){
        GAMEDATA::getInstance()->setPrivateKaibao(_mDoc["ifkb"].GetString());
    }
    if(_mDoc.HasMember("ifemsc")){
        GAMEDATA::getInstance()->setPrivateEmsc(_mDoc["ifemsc"].GetString());
    }
    if(_mDoc.HasMember("iflezi")){
        GAMEDATA::getInstance()->setPrivateLezi(_mDoc["iflezi"].GetString());
    }
    FriendOpenRoomRespData data;
    if(_mDoc.HasMember("kb")){
        const rapidjson::Value &kb = _mDoc["kb"];
        data.kb = kb.GetString();
    }
    if(_mDoc.HasMember("huangfan")){
        const rapidjson::Value &huangfan = _mDoc["huangfan"];
        data.huangfan = huangfan.GetString();
    }
    if(_mDoc.HasMember("prjushu")){
        const rapidjson::Value &prjushu = _mDoc["prjushu"];
        data.prjushu = prjushu.GetString();
    }
    if(_mDoc.HasMember("prJucount")){
        const rapidjson::Value &prjucount = _mDoc["prJucount"];
        data.prjucount = prjucount.GetString();
    }
    if(_mDoc.HasMember("prId")){
        const rapidjson::Value &prid = _mDoc["prId"];
        data.prid = prid.GetString();
    }
    if(_mDoc.HasMember("jifen")){
        const rapidjson::Value &jifen = _mDoc["jifen"];
        GAMEDATA::getInstance()->setScore(jifen.GetInt());
    }
    if(_mDoc.HasMember("seatId")){
        const rapidjson::Value &seatId = _mDoc["seatId"];
        data.seatId = seatId.GetInt();
        GAMEDATA::getInstance()->setHeroSeatId(seatId.GetInt());
    }
    if(_mDoc.HasMember("ip")){
        const rapidjson::Value &ip = _mDoc["ip"];
        GAMEDATA::getInstance()->setIP(ip.GetString());
    }
    const rapidjson::Value &result = _mDoc["result"];
    data.result = result.GetInt();
    GAMEDATA::getInstance()->clearPlayersInfo();
    GAMEDATA::getInstance()->setFriendOpenRoomResp(data);
    if (_mDoc.HasMember("other")){
        const rapidjson::Value &pArr = _mDoc["other"];
        for (int i = 0; i < pArr.Capacity(); ++i){
            const rapidjson::Value &temp = pArr[i];
            Player* info = new Player();
            info->setPoxiaoId(temp["poxiaoId"].GetString());
            info->setSeatId(temp["seatId"].GetInt());
            info->setBanker(false);
            info->setIsReady(temp["ifready"].GetInt() == 0 ? false : true);
            
            info->setGold(temp["gold"].GetInt());
            info->setTicket(temp["lequan"].GetInt());
            info->setScore(temp["jifen"].GetInt());
            info->setGender(temp["gender"].GetInt());
            info->setNickname(temp["nickname"].GetString());
            info->setPicture(temp["pic"].GetString());
            info->setFangka(temp["fangka"].GetDouble());
            if(temp.HasMember("ip")){
                info->setIP(temp["ip"].GetString());
            }
            if(temp.HasMember("umark")){
                info->setUmark(temp["umark"].GetString());
            }
            GAMEDATA::getInstance()->addPlayersInfo(info);
        }
    }
    Player* info = new Player();
    info->setSeatId(GAMEDATA::getInstance()->getHeroSeatId());
    info->setPoxiaoId(UserData::getInstance()->getPoxiaoId());
    info->setIsReady(false);
    info->setTicket(UserData::getInstance()->getTicket());
    info->setGold(UserData::getInstance()->getGold());
    info->setGender(UserData::getInstance()->getGender());
    info->setNickname(UserData::getInstance()->getNickName());
    info->setPicture(UserData::getInstance()->getPicture());
    info->setFangka(UserData::getInstance()->getFangkaNum());
    info->setIP(GAMEDATA::getInstance()->getIP());
    info->setUmark(UserData::getInstance()->getMarkId());
    info->setScore(GAMEDATA::getInstance()->getScore());
    GAMEDATA::getInstance()->addPlayersInfo(info);
    postNotifyMessage(MSG_FRIEND_OPEN_ROOM_RESP, "");
}


void MsgHandler::friendEnterRoomResp(std::string msg){
    // code:2040
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if(_mDoc.HasMember("poxiaoId")){
        const rapidjson::Value &poxiaoId = _mDoc["poxiaoId"];
        UserData::getInstance()->setPoxiaoId(poxiaoId.GetString());
    }
    if(_mDoc.HasMember("ifkb")){
        GAMEDATA::getInstance()->setPrivateKaibao(_mDoc["ifkb"].GetString());
    }
    if(_mDoc.HasMember("ifemsc")){
        GAMEDATA::getInstance()->setPrivateEmsc(_mDoc["ifemsc"].GetString());
    }
    if(_mDoc.HasMember("iflezi")){
        GAMEDATA::getInstance()->setPrivateLezi(_mDoc["iflezi"].GetString());
    }
    const rapidjson::Value &result = _mDoc["result"];
    FriendOpenRoomRespData data = GAMEDATA::getInstance()->getFriendOpenRoomResp();
    if(_mDoc.HasMember("kb")){
        const rapidjson::Value &kb = _mDoc["kb"];
        data.kb = kb.GetString();
    }
    if(_mDoc.HasMember("seatId")){
        const rapidjson::Value &seatId = _mDoc["seatId"];
        GAMEDATA::getInstance()->setHeroSeatId(seatId.GetInt());
    }
    if (_mDoc.HasMember("prId")){
        const rapidjson::Value &prid = _mDoc["prId"];
        data.prid =prid.GetString();
    }
    if (_mDoc.HasMember("prjushu")){
        const rapidjson::Value &prjushu = _mDoc["prjushu"];
        data.prjushu = prjushu.GetString();
    }
    if(_mDoc.HasMember("prjucount")){
        const rapidjson::Value &prjucount = _mDoc["prjucount"];
        data.prjucount = prjucount.GetString();
    }
    if(_mDoc.HasMember("jifen")){
        const rapidjson::Value &myjifen = _mDoc["jifen"];
        GAMEDATA::getInstance()->setScore(myjifen.GetInt());
    }
    GAMEDATA::getInstance()->clearPlayersInfo();
    GAMEDATA::getInstance()->setFriendOpenRoomResp(data);
    if (_mDoc.HasMember("other")){
        const rapidjson::Value &pArr = _mDoc["other"];
        for (int i = 0; i < pArr.Capacity(); ++i){
            const rapidjson::Value &temp = pArr[i];
            Player* info = new Player();
            info->setPoxiaoId(temp["poxiaoId"].GetString());
            info->setSeatId(temp["seatId"].GetInt());
            info->setBanker(false);
            info->setIsReady(temp["ifready"].GetInt() == 0 ? false : true);
            info->setGold(temp["gold"].GetInt());
            info->setTicket(temp["lequan"].GetInt());
            info->setScore(temp["jifen"].GetInt());
            info->setGender(temp["gender"].GetInt());
            info->setNickname(temp["nickname"].GetString());
            info->setPicture(temp["pic"].GetString());
            info->setFangka(temp["fangka"].GetDouble());
            if(temp.HasMember("ip")){
                info->setIP(temp["ip"].GetString());
            }
            if(temp.HasMember("umark")){
                info->setUmark(temp["umark"].GetString());
            }
            
            GAMEDATA::getInstance()->addPlayersInfo(info);
        }
    }
    Player* info = new Player();
    info->setSeatId(GAMEDATA::getInstance()->getHeroSeatId());
    info->setPoxiaoId(UserData::getInstance()->getPoxiaoId());
    info->setIsReady(false);
    info->setTicket(UserData::getInstance()->getTicket());
    info->setGold(UserData::getInstance()->getGold());
    info->setGender(UserData::getInstance()->getGender());
    info->setNickname(UserData::getInstance()->getNickName());
    info->setPicture(UserData::getInstance()->getPicture());
    info->setFangka(UserData::getInstance()->getFangkaNum());
    info->setIP(GAMEDATA::getInstance()->getIP());
    info->setUmark(UserData::getInstance()->getMarkId());
    info->setScore(GAMEDATA::getInstance()->getScore());
    GAMEDATA::getInstance()->addPlayersInfo(info);
    postNotifyMessage(MSG_ENTER_FRIEND_ROOM_RESP, StringUtil::itos(result.GetInt()));
}


void MsgHandler::playerChatNotify(std::string msg){
    //{code:105,poxiaoId:"123",content:"abc",seatId:1}
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    ChatData chatData;
    chatData.isRead = false;
    if (_mDoc.HasMember("content")){
        const rapidjson::Value &content = _mDoc["content"];
        chatData.content = content.GetString();
    }
    if (_mDoc.HasMember("fId")){
        const rapidjson::Value &fId = _mDoc["fId"];
        chatData.poxiaoId = fId.GetString();
    }
    if (_mDoc.HasMember("nickname")){
        const rapidjson::Value &nickname = _mDoc["nickname"];
        chatData.nickname = nickname.GetString();
    }
    if (_mDoc.HasMember("flag")){
        const rapidjson::Value &flag = _mDoc["flag"];
        if(flag.GetInt() == 0){
            FriendChatMsgList list = GAMEDATA::getInstance()->getFriendChatMsgList();
            bool findChatRecord = false;
            for(int i=0;i<list.friendMsgList.size();i++){
                if(chatData.poxiaoId == list.friendMsgList.at(i).poxiaoId){
                    list.friendMsgList.at(i).msgList.push_back(chatData);
                    findChatRecord = true;
                }
            }
            if(!findChatRecord){
                FriendChatData data;
                data.poxiaoId = chatData.poxiaoId;
                data.msgList.push_back(chatData);
                list.friendMsgList.push_back(data);
            }
            GAMEDATA::getInstance()->setFriendChatMsgList(list);
        }else{
            RoomChatMsgList list = GAMEDATA::getInstance()->getRoomChatMsgList();
            list.msgList.push_back(chatData);
            GAMEDATA::getInstance()->setRoomChatMsgList(list);
        }
    }else{
        FriendChatMsgList list = GAMEDATA::getInstance()->getFriendChatMsgList();
        bool findChatRecord = false;
        for(int i=0;i<list.friendMsgList.size();i++){
            if(chatData.poxiaoId == list.friendMsgList.at(i).poxiaoId){
                list.friendMsgList.at(i).msgList.push_back(chatData);
                findChatRecord = true;
            }
        }
        if(!findChatRecord){
            FriendChatData data;
            data.poxiaoId = chatData.poxiaoId;
            data.msgList.push_back(chatData);
            list.friendMsgList.push_back(data);
        }
        GAMEDATA::getInstance()->setFriendChatMsgList(list);
    }
    
    GAMEDATA::getInstance()->setChatData(chatData);
    postNotifyMessage(MSG_PLAYER_CHAT_NOTIFY, "");
}



void MsgHandler::billResp(std::string msg){
    //    获取账单回复{code:2042,poxiaoId:poxiaoId,bill:[{date:"2015-06-06 15:15",count:"10",billid:"8888888888",content:[{nickname:"张三",score:"1000"},{nickname:"李四",score:"2000"},{nickname:"王五",score:"1000"},{nickname:"赵六",score:"1100"}]}]}
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if (_mDoc.HasMember("bill")){
        BillInfoAll infoAll;
        infoAll.needInit = false;
        const rapidjson::Value &bill = _mDoc["bill"];
        BillInfoData data;
        for (int i = 0; i < bill.Capacity(); i++){
            const rapidjson::Value &temp = bill[i];
            data.content.clear();
            data.billId = temp["billid"].GetString();
            data.date = temp["date"].GetString();
            data.prid = temp["prId"].GetString();
            data.atype = temp["atype"].GetString();
            if (temp.HasMember("content")){
                BillContent con;
                const rapidjson::Value &content = temp["content"];
                for (int j = 0; j < content.Capacity(); j++){
                    const rapidjson::Value &tempInfo = content[j];
                    con.nickName = tempInfo["nickname"].GetString();
                    con.score = tempInfo["score"].GetString();
                    data.content.push_back(con);
                }
            }
            infoAll.bills.push_back(data);
        }
        GAMEDATA::getInstance()->setBillInfoAll(infoAll);
    }
    postNotifyMessage(MSG_PLAYER_BILL, "");
}

void MsgHandler::billDetailResp(std::string msg){
    //账单详情{code:2044,poxiaoId:poxiaoId,detail:[{nickname:"",score:"1000"},
    //{nickname:"",score:"2000"},{nickname:"",score:"-1000"},{nickname:"",score:"-1100"}]}
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if (_mDoc.HasMember("detail")){
        BillInfoDetailAll detailAll;
        detailAll.needInit = false;
        const rapidjson::Value &detail = _mDoc["detail"];
        for (int i = 0; i < detail.Capacity(); i++){
            const rapidjson::Value &temp0 = detail[i];
            BillInfoDetail data;
            if(temp0.HasMember("bill")){
                const rapidjson::Value &temp1 = temp0["bill"];
                for (int j = 0; j < temp1.Capacity(); j++){
                    BillContent con;
                    const rapidjson::Value &tempInfo = temp1[j];
                    con.nickName = tempInfo["nickname"].GetString();
                    con.score = tempInfo["score"].GetString();
                    data.detail.push_back(con);
                }
            }
            if(temp0.HasMember("recordId")){
                data.recordId = temp0["recordId"].GetString();
            }
            detailAll.detail.push_back(data);
        }
        GAMEDATA::getInstance()->setBillInfoDetailAll(detailAll);
    }
    postNotifyMessage(MSG_PLAYER_BILL_DETAIL, "");
}


void MsgHandler::dailyPrideResp(std::string msg){
    // 金币抽奖情况获取回复{code:1023,poxiaoId:poxiaoId,result:"1",gold:"50000",
    //prize:[{gold:30000},{lequan:300},{lequan:800},{lequan:100},{bangzuan:80},{bangzuan:50},{bangzuan:20},{gold:60000},{diamond:11}],
    //count:"1",max:"5"} result1为可以参加，0为不可参加 ，count为可以抽奖几次，max为最多能抽奖几次，prize奖品里面数值为整数
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    DailyPrideData data;
    if (_mDoc.HasMember("result")){
        data.result = _mDoc["result"].GetString();
    }
    if (_mDoc.HasMember("gold")){
        data.needGold = _mDoc["gold"].GetString();
    }
    if (_mDoc.HasMember("count")){
        data.count = _mDoc["count"].GetString();
    }
    if (_mDoc.HasMember("max")){
        data.max = _mDoc["max"].GetString();
    }
    if (_mDoc.HasMember("prize")){
        const rapidjson::Value &prize = _mDoc["prize"];
        for (int i = 0; i < prize.Capacity(); i++){
            PrideData info;
            const rapidjson::Value &temp = prize[i];
            if (temp.HasMember("gold")){
                info.type = PrideType::gold;
                info.number = temp["gold"].GetInt();
            }
            if (temp.HasMember("lequan")){
                info.type = PrideType::lequan;
                info.number = temp["lequan"].GetInt();
            }
            if (temp.HasMember("bangzuan")){
                info.type = PrideType::lockDiammond;
                info.number = temp["bangzuan"].GetInt();
            }
            if (temp.HasMember("fangka")){
                info.type = PrideType::fangka;
                info.number = temp["fangka"].GetDouble();
            }
            data.prides.push_back(info);
        }
    }
    GAMEDATA::getInstance()->setDailyPrideData(data);
    postNotifyMessage(MSG_PLAYER_DAILY_PRIDE, "");
}

void MsgHandler::todayPrideResp(std::string msg){
    // 金币抽奖奖励领取回复{code:1025,poxiaoId:poxiaoId,result:"1",prize:{gold:10}}
    //1为成功 0失败,prize为抽到的奖品，奖品里面数值为整数
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    TodayPrideData  data;
    if (_mDoc.HasMember("result")){
        data.result = _mDoc["result"].GetString();
    }
    if (_mDoc.HasMember("rest")){
        data.rest = _mDoc["rest"].GetInt();
    }
    if (_mDoc.HasMember("prize")){
        PrideData info;
        const rapidjson::Value &temp = _mDoc["prize"];
        if (temp.HasMember("gold")){
            info.type = PrideType::gold;
            info.number = temp["gold"].GetInt();
        }
        if (temp.HasMember("lequan")){
            info.type = PrideType::lequan;
            info.number = temp["lequan"].GetInt();
        }
        if (temp.HasMember("bangzuan")){
            info.type = PrideType::lockDiammond;
            info.number = temp["bangzuan"].GetInt();
        }
        if (temp.HasMember("fangka")){
            info.type = PrideType::fangka;
            info.number = temp["fangka"].GetDouble();
        }
        data.pride = info;
    }
    GAMEDATA::getInstance()->setTodayPrideData(data);
    postNotifyMessage(MSG_PLAYER_TODAY_PRIDE, "");
}


void MsgHandler::firstChargeInfoResp(std::string msg){
    // 首次充值获取回复{code:1053,poxiaoId:poxiaoId,gold:"123",fangka:"456",money:"10"}
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    FirstChargeData data;
    if(_mDoc.HasMember("gold")){
        const rapidjson::Value &gold = _mDoc["gold"];
        data.gold = atoi(gold.GetString());
    }
    if(_mDoc.HasMember("fangka")){
        const rapidjson::Value &fangka = _mDoc["fangka"];
        data.fangka = atoi(fangka.GetString());
    }
    if(_mDoc.HasMember("money")){
        const rapidjson::Value &money = _mDoc["money"];
        data.money = atoi(money.GetString());
    }
    data.needInit = false;
    GAMEDATA::getInstance()->setFirstChargeData(data);
    postNotifyMessage(MSG_PLAYER_FIRST_CHARGE, "");
}

void MsgHandler::goldChangeListResp(std::string msg){
    // 兑换列表回复{code:1049,poxiaoId:poxiaoId,list:[{id:"1",gold:"1000",diamond:"100"},{id:"2",gold:"2000",diamond:"200"}]}
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &list = _mDoc["list"];
    GoldChangeList data;
    data.needInit = true;
    for(int i=0;i<list.Capacity();i++){
        const rapidjson::Value &temp = list[i];
        GoldChange change;
        change.gold = atoi(temp["gold"].GetString());
        change.diamond = atoi(temp["diamond"].GetString());
        change.fangka = atoi(temp["fangka"].GetString());
        data.list.push_back(change);
    }
    GAMEDATA::getInstance()->setGoldChangeList(data);
    postNotifyMessage(MSG_PLAYER_GOLD_CHANGE_LIST, "");
}

void MsgHandler:: goldChangeResp(std::string msg){
    // 兑换回复{code:1051,poxiaoId:poxiaoId,result:"1"} 1成功0失败
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &result = _mDoc["result"];
    if(_mDoc.HasMember("gold")){
        const rapidjson::Value &gold = _mDoc["gold"];
        UserData::getInstance()->setGold(gold.GetInt());
    }
    if(_mDoc.HasMember("diamond")){
        const rapidjson::Value &diamond = _mDoc["diamond"];
        UserData::getInstance()->setDiamond(diamond.GetInt());
    }
    postNotifyMessage(MSG_PLAYER_GOLD_CHANGE_RESP, result.GetString());
}

void MsgHandler::diamondChangeListResp(std::string msg){
    //充值列表回复{code:1045,poxiaoId:poxiaoId,list:[{id:"1",money:"1000",diamond:"100"},{id:"2",money:"2000",diamond:"200"}]}
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &list = _mDoc["list"];
    FangkaChargeList data;
    data.needInit = true;
    for(int i=0;i<list.Capacity();i++){
        const rapidjson::Value &temp = list[i];
        FangkaCharge change;
        change.money = atoi(temp["money"].GetString());
        change.fangka = atoi(temp["fangka"].GetString());
        change.payId = atoi(temp["id"].GetString());
        data.list.push_back(change);
    }
    GAMEDATA::getInstance()->setFangkaChargeList(data);
    postNotifyMessage(MSG_PLAYER_GOLD_CHANGE_LIST, "");
    
}

void MsgHandler::lequanChangeListResp(std::string msg){
    // 乐券商城回复{code:1041,poxiaoId:poxiaoId,mall:[{goodsId:"1",goodsName:"手机",goodsPrice:"100"},{goodsId:"2",goodsName:"流量",goodsPrice:"1000"}]}
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &mall = _mDoc["mall"];
    LequanChangeList data;
    data.needInit = true;
    for(int i=0;i<mall.Capacity();i++){
        const rapidjson::Value &temp = mall[i];
        LequanChange change;
        change.propId = temp["goodsId"].GetString();
        change.propPrice = temp["goodsPrice"].GetString();
        change.propName = temp["goodsName"].GetString();
        change.propType = temp["goodsType"].GetString();
        change.url = temp["url"].GetString();
        data.list.push_back(change);
    }
    GAMEDATA::getInstance()->setLequanChangeList(data);
    postNotifyMessage(MSG_PLAYER_LEQUAN_CHANGE_LIST, "");
    
}


void MsgHandler::getLequanExchangeResp(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &result = _mDoc["result"];
    LequanChangeResult myResult;
    myResult.result = result.GetString();
    if(_mDoc.HasMember("lequan")){
        const rapidjson::Value &lequan = _mDoc["lequan"];
        myResult.lequan = lequan.GetInt();
    }
    GAMEDATA::getInstance()->setLequanChangeResult(myResult);
    postNotifyMessage(MSG_PLAYER_LEQUAN_EXCHANGE, "");
}

void MsgHandler::getPlayerInfoResp(std::string msg){
    //{code:150,poxiaoId:poxiaoId,lequan:11,bangzuan:22,diamond:33,gold:55,jifen:0}
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if(_mDoc.HasMember("lequan")){
        const rapidjson::Value &lequan = _mDoc["lequan"];
        UserData::getInstance()->setTicket(lequan.GetInt());
    }
    if(_mDoc.HasMember("fangka")){
        const rapidjson::Value &fangka = _mDoc["fangka"];
        UserData::getInstance()->setFangkaNum(fangka.GetDouble());
    }
    
    if(_mDoc.HasMember("gold")){
        const rapidjson::Value &gold = _mDoc["gold"];
        UserData::getInstance()->setGold(gold.GetInt());
    }
    if(_mDoc.HasMember("jifen")){
        const rapidjson::Value &jifen = _mDoc["jifen"];
        GAMEDATA::getInstance()->setScore(jifen.GetInt());
    }
    
    if(_mDoc.HasMember("ip")){
        const rapidjson::Value &ip = _mDoc["ip"];
        GAMEDATA::getInstance()->setIP(ip.GetString());
    }
}



void MsgHandler::getPlayerOffLineNotify(std::string msg){
    // 服务端到客户端掉线通知{code:1010,poxiaoId:poxiaoId}
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if(_mDoc.HasMember("seatId")){
        const rapidjson::Value &seatId = _mDoc["seatId"];
        postNotifyMessage(MSG_PLAYER_OFF_LINE_NOTIFY, seatId.GetString());
    }
}

void MsgHandler::getLequanChangeRecordResp(std::string msg){
    // 乐券商城兑换记录回复{code:1057,poxiaoId:poxiaoId,list:[{id:"1",status:"1"},{id:"2",status:"2"}]} //0兑换中 1已兑换
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    LeChangeRecord records;
    if(_mDoc.HasMember("list")){
        const rapidjson::Value &list = _mDoc["list"];
        for(int i=0;i<list.Capacity();i++){
            LeRecord rec;
            const rapidjson::Value &temp = list[i];
            rec.propId =temp["id"].GetString();
            rec.state = temp["status"].GetString();
            records.records.push_back(rec);
        }
    }
    GAMEDATA::getInstance()->setLeChangeRecord(records);
    postNotifyMessage(MSG_PLAYER_LEQUAN_EXCHANGE_RECORD, "");
}


void MsgHandler::getHeadImageChangeResp(std::string msg){
    // 修改图片回复{code:153,result:"1",gender:1} 1成功 其他 失败
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &result = _mDoc["result"];
    if(_mDoc.HasMember("gender")){
        const rapidjson::Value &gender = _mDoc["gender"];
        UserData::getInstance()->setGender(gender.GetInt());
    }
    if(_mDoc.HasMember("pic")){
        const rapidjson::Value &pic = _mDoc["pic"];
        UserData::getInstance()->setPicture(pic.GetString());
    }
    postNotifyMessage(MSG_PLAYER_CHANGE_HEAD_RESP, StringUtil::itos(result.GetInt()));
}


void MsgHandler::getFeedBackResp(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &result = _mDoc["result"];
    postNotifyMessage(MSG_PLAYER_FEED_BACK_RESP, result.GetString());
}

//void MsgHandler::gameResumeResp(std::string msg){
//    //1998后台切回
//    rapidjson::Document _mDoc;
//    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
//    _mDoc.Parse<0>(msg.c_str());
//    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
//    if(_mDoc.HasMember("poxiaoId")){
//        const rapidjson::Value &poxiaoId = _mDoc["poxiaoId"];
//        UserData::getInstance()->setPoxiaoId(poxiaoId.GetString());
//    }
//    if(_mDoc.HasMember("ifkb")){
//        GAMEDATA::getInstance()->setPrivateKaibao(_mDoc["ifkb"].GetString());
//    }
//    if(_mDoc.HasMember("ifemsc")){
//        GAMEDATA::getInstance()->setPrivateEmsc(_mDoc["ifemsc"].GetString());
//    }
//    if(_mDoc.HasMember("iflezi")){
//        GAMEDATA::getInstance()->setPrivateLezi(_mDoc["iflezi"].GetString());
//    }
//    FriendOpenRoomRespData opdata;
//    if(_mDoc.HasMember("prjushu")){
//        const rapidjson::Value &prjushu = _mDoc["prjushu"];
//        opdata.prjushu = prjushu.GetString();
//    }
//    if(_mDoc.HasMember("prId")){
//        const rapidjson::Value &prId = _mDoc["prId"];
//        opdata.prid = prId.GetString();
//    }
//    if(_mDoc.HasMember("fzId")){
//        const rapidjson::Value &fzId = _mDoc["fzId"];
//        GAMEDATA::getInstance()->setFangZhuId(fzId.GetString());
//    }
//    if(_mDoc.HasMember("prjucount")){
//        const rapidjson::Value &prjucount = _mDoc["prjucount"];
//        opdata.prjucount = prjucount.GetString();
//    }else{
//        opdata.prjucount = "0";
//    }
//    GAMEDATA::getInstance()->setFriendOpenRoomResp(opdata);
//    //设置是否是私人房间
//    const rapidjson::Value &isprivate = _mDoc["isprivate"];
//    std::string roomType = isprivate.GetString();
//    GAMEDATA::getInstance()->setMahjongRoomType(roomType == "1" ? (MahjongRoom::privateRoom):(MahjongRoom::publicRoom));
//    LastGameData lastGameData;
//    const rapidjson::Value &result = _mDoc["result"];
//    lastGameData.result = result.GetInt();
//    const rapidjson::Value &seatId = _mDoc["seatId"];
//    lastGameData.seatId = seatId.GetInt();
//    GAMEDATA::getInstance()->setHeroSeatId(seatId.GetInt());
//    if(_mDoc.HasMember("pre")){
//        const rapidjson::Value &pre = _mDoc["pre"];
//        lastGameData.pre = pre.GetInt();
//    }
//    if(_mDoc.HasMember("rest")){
//        const rapidjson::Value &rest = _mDoc["rest"];
//        lastGameData.rest = rest.GetString();
//    }
//    if(_mDoc.HasMember("lord")){
//        const rapidjson::Value &loard = _mDoc["lord"];
//        lastGameData.loard = loard.GetInt();
//    }
//    if(_mDoc.HasMember("kb")){
//        const rapidjson::Value &kb = _mDoc["kb"];
//        lastGameData.kb = kb.GetInt();
//    }
//    if(_mDoc.HasMember("hf")){
//        const rapidjson::Value &hf = _mDoc["hf"];
//        lastGameData.hf = hf.GetInt();
//    }
//    if(_mDoc.HasMember("turn")){
//        const rapidjson::Value &turn = _mDoc["turn"];
//        lastGameData.turn = turn.GetInt();
//    }
//
//    if(_mDoc.HasMember("all")){
//        const rapidjson::Value &all = _mDoc["all"];
//        for (int i = 0; i < all.Capacity(); ++i){
//            PlayerGameData  data;
//            const rapidjson::Value &temp = all[i];
//            data.poxiaoId = temp["poxiaoId"].GetString();
//            data.seatId = temp["seatId"].GetInt();
//            if(temp.HasMember("status"))
//                data.status = temp["status"].GetInt();
//            data.gold = temp["gold"].GetInt();
//            data.jifen = temp["jifen"].GetInt();
//            data.bangzuan = temp["bangzuan"].GetInt();
//            data.lequan = temp["lequan"].GetInt();
//            data.diamond = temp["diamond"].GetInt();
//            data.lequan = temp["lequan"].GetInt();
//            data.fangka = temp["fangka"].GetDouble();
//            data.hua = temp["hua"].GetInt();
//            if(temp.HasMember("ifready"))
//                data.ifready = temp["ifready"].GetInt();
//            if(temp.HasMember("isonline"))
//                data.isOnline = temp["isonline"].GetInt();
//            if(temp.HasMember("lastpoker")){
//                data.lastpoker = temp["lastpoker"].GetString();
//            }
//            if(temp.HasMember("chi")){
//                const rapidjson::Value &chi = temp["chi"];
//                for(int j = 0; j < chi.Capacity(); ++j){
//                    const rapidjson::Value &temp2 = chi[j];
//                    PlayerChiData chiDa;
//                    chiDa.chi = temp2["chi"].GetString();
//                    chiDa.poker = temp2["poker"].GetString();
//                    data.chiData.push_back(chiDa);
//                }
//            }
//            if(temp.HasMember("peng")){
//                const rapidjson::Value &peng = temp["peng"];
//                for(int j = 0; j < peng.Capacity(); ++j){
//                    const rapidjson::Value &temp3 = peng[j];
//                    PlayerPengData pengDa;
//                    pengDa.peng = temp3["peng"].GetString();
//                    pengDa.peId = temp3["peId"].GetString();
//                    data.pengData.push_back(pengDa);
//                }
//            }
//            if(temp.HasMember("gang")){
//                const rapidjson::Value &gang = temp["gang"];
//                for(int j = 0; j < gang.Capacity(); ++j){
//                    const rapidjson::Value &temp4 = gang[j];
//                    PlayerGangData pengDa;
//                    pengDa.gang = temp4["gang"].GetString();
//                    pengDa.gaId = temp4["gaId"].GetString();
//                    data.gangData.push_back(pengDa);
//                }
//            }
//            if(temp.HasMember("angang"))
//                data.angang = temp["angang"].GetString();
//            if(temp.HasMember("hand"))
//                data.hand = temp["hand"].GetString();
//            if(temp.HasMember("out"))
//                data.outhand = temp["out"].GetString();
//            data.nickname =temp["nickname"].GetString();
//            data.pic =temp["pic"].GetString();
//            data.gender = temp["gender"].GetInt();
//            if(temp.HasMember("ip")){
//                data.ip = temp["ip"].GetString();
//            }
//            if(temp.HasMember("umark")){
//                data.umark = temp["umark"].GetString();
//            }
//            lastGameData.players.push_back(data);
//        }
//    }
//    GAMEDATA::getInstance()->setLastGameDataBackup(lastGameData);
//    postNotifyMessage(MSG_PLAYER_RESUME_GAME, "");
//}

void MsgHandler::gameContinueResp(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    EnterRoomResp resp;
    const rapidjson::Value &result = _mDoc["result"];
    resp.result = StringUtil::itos(result.GetInt());
    
    if(_mDoc.HasMember("rsid")){
        const rapidjson::Value &rsid = _mDoc["rsid"];
        resp.rsid = rsid.GetString();
    }
    if(_mDoc.HasMember("money")){
        const rapidjson::Value &money = _mDoc["money"];
        resp.money = money.GetString();
    }
    if(_mDoc.HasMember("gold")){
        const rapidjson::Value &gold = _mDoc["gold"];
        resp.gold = gold.GetString();
    }
    if(_mDoc.HasMember("id")){
        const rapidjson::Value &payid = _mDoc["id"];
        resp.payid = payid.GetString();
    }
    if(_mDoc.HasMember("min")){
        const rapidjson::Value &min = _mDoc["min"];
        resp.min = min.GetString();
    }
    if(_mDoc.HasMember("kb")){
        const rapidjson::Value &kb = _mDoc["kb"];
        resp.kb = kb.GetString();
    }
    if(_mDoc.HasMember("huangfan")){
        const rapidjson::Value &huangfan = _mDoc["huangfan"];
        resp.huangfan = huangfan.GetString();
    }
    if(_mDoc.HasMember("all")){
        const rapidjson::Value &all = _mDoc["all"];
        for (int i = 0; i < all.Capacity(); ++i){
            const rapidjson::Value &temp = all[i];
            PlayerReady ready;
            if(temp.HasMember("ifready")){
                ready.ifready = temp["ifready"].GetInt();
            }
            if(temp.HasMember("poxiaoId")){
                ready.poxiaoId = temp["poxiaoId"].GetString();
            }
            if(temp.HasMember("seatId")){
                ready.seatId = temp["seatId"].GetInt();
            }
            resp.playerReadys.push_back(ready);
        }
    }
    //    GAMEDATA::getInstance()->setEnterRoomResp(resp);
    GAMEDATA::getInstance()->setShowDialogType(result.GetInt());
    postNotifyMessage(MSG_HERO_CONTINUE_RESP, "");
}

void MsgHandler::otherClientReplace(std::string msg){
    postNotifyMessage(MSG_PLAYER_REPLACE_LOGIN, "");
}

void MsgHandler::inviteOthersResp(std::string msg){
    // 好友邀请结果通知{code:2045,poxiaoId:"123",pId:"456",result:1,nickname:""} result 为1是好友不在线 2是好友在游戏中，邀请成功不发送次通知
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    InviteRespData resp;
    const rapidjson::Value &result = _mDoc["result"];
    resp.result = StringUtils::format("%d",result.GetInt());
    const rapidjson::Value &nickname = _mDoc["nickname"];
    resp.nickname = nickname.GetString();
    GAMEDATA::getInstance()->setInviteRespData(resp);
    postNotifyMessage(FRIEND_IS_PLAYING_GAME, "");
}


void MsgHandler::openRoomEnquireResp(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    postNotifyMessage(MSG_LOBBY_ASK_OPEN_ROOM, "");
}

void MsgHandler::enterRoomEnquireResp(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    postNotifyMessage(MSG_LOBBY_ASK_ENTER_ROOM, "");
}


void MsgHandler::handleDissovleRoomNotify(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if(_mDoc.HasMember("nickName")){
        const rapidjson::Value &nickName = _mDoc["nickName"];
        std::string name = nickName.GetString();
        //        postNotifyMessage(MSG_DISSOVLE_ROOM_NOTIFY, name);
        GAMEDATA::getInstance()->setDissolveName(name);
        GAMEDATA::getInstance()->setIsSelected(false);
    }
}

void MsgHandler::hanleFangzhuDismissRoom(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    GAMEDATA::getInstance()->setShowFangZhuDismiss(true);
}

void MsgHandler::handleDissovleRoomSelectedNotify(std::string msg){
    //私人房间是否同意解散通知{code:2051,poxiaoId:poxiaoId,pId:11,agree:0} 0为不同
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    DissolveData data;
    const rapidjson::Value &pId = _mDoc["pId"];
    data.pid = pId.GetString();
    if(_mDoc.HasMember("agree")){
        const rapidjson::Value &agree = _mDoc["agree"];
        data.agree = agree.GetString();
    }
    GAMEDATA::getInstance()->setDissolveData(data);
    postNotifyMessage(MSG_DISSOVLE_ROOM_SELECTED_NOTIFY, "");
}


void MsgHandler::handleQuitGameViewResp(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if(_mDoc.HasMember("prjucount")){
        const rapidjson::Value &prjucount = _mDoc["prjucount"];
        if(GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom)
            GAMEDATA::getInstance()->setPrivateGameNum(prjucount.GetString());
    }
}

void MsgHandler::handleScrollTextResp(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if(_mDoc.HasMember("content")){
        const rapidjson::Value &content = _mDoc["content"];
        postNotifyMessage(MSG_SCROLL_TEXT, content.GetString());
    }
}



void MsgHandler::handleNoticeResp(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if(_mDoc.HasMember("content")){
        const rapidjson::Value &content = _mDoc["content"];
        GAMEDATA::getInstance()->setNoticeUrl(content.GetString());
    }
    postNotifyMessage(MSG_WAN_JIA_GONG_GAO, "");
}


void MsgHandler::handleGamePayType(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if(_mDoc.HasMember("result")){
        const rapidjson::Value &result = _mDoc["result"];
        UserData::getInstance()->setWeixinPayOpen(result.GetInt() == 0 ?true:false);
    }
    postNotifyMessage(MSG_UPDATE_LEQUAN_SHANG_CHEN_SHOW, "");
}

void MsgHandler::handleFupanInfo(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    PlayBackInfo info;
    if(_mDoc.HasMember("result")){
        info.result =_mDoc["result"].GetInt();
    }
    if(_mDoc.HasMember("playback")){
        const rapidjson::Value &playback = _mDoc["playback"];
        
        for(int i=0;i<playback.Capacity();i++){
            const rapidjson::Value &temp = playback[i];
            if(temp.HasMember("key")){
                info.playBackInfo.push_back(temp["key"].GetString());
            }
        }
        
    }
    if(_mDoc.HasMember("who")){
        const rapidjson::Value &who = _mDoc["who"];
        info.heroid =who.GetString();
    }
    GAMEDATA::getInstance()->setPlaybackInfo(info);
    postNotifyMessage(MSG_GAME_FU_PAN_NOTIFY, "");
}

void MsgHandler::handleFupanPlayerInfo(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    FupanGameData fupan;
    FriendOpenRoomRespData data;
    if(_mDoc.HasMember("fanghao")){
        
        data.prid = _mDoc["fanghao"].GetString();
    }
    if(_mDoc.HasMember("prjucount")){
        data.prjucount = StringUtils::format("%d",_mDoc["prjucount"].GetInt());
    }
    if(_mDoc.HasMember("prjushu")){
        data.prjushu = StringUtils::format("%d",_mDoc["prjushu"].GetInt());
    }
    GAMEDATA::getInstance()->setFriendOpenRoomResp(data);
    if(_mDoc.HasMember("hf")){
        GAMEDATA::getInstance()->setHuangfan(StringUtils::format("%d",_mDoc["hf"].GetInt()));
    }
    if(_mDoc.HasMember("kb")){
        GAMEDATA::getInstance()->setKaibao(StringUtils::format("%d",_mDoc["kb"].GetInt()));
    }
    const rapidjson::Value &all = _mDoc["all"];
    for (int i = 0; i < all.Capacity(); ++i){
        PlayerGameData  data;
        const rapidjson::Value &temp = all[i];
        data.poxiaoId = temp["poxiaoId"].GetString();
        data.seatId = temp["seatId"].GetInt();
        if(data.poxiaoId ==  GAMEDATA::getInstance()->getPlaybackInfo().heroid){
            GAMEDATA::getInstance()->setHeroSeatId(data.seatId);
        }
        data.nickname = temp["nickname"].GetString();
        data.gold = temp["golden"].GetInt();
        data.jifen = temp["jifen"].GetInt();
        data.lequan = temp["lequan"].GetInt();
        data.fangka = temp["fangka"].GetDouble();
        data.pic = temp["pic"].GetString();
        //        data.ip = temp["ip"].GetString();
        data.hua = temp["hua"].GetInt();
        data.status = 2;
        data.ifready = 0;
        data.hand = temp["poker"].GetString();
        fupan.players.push_back(data);
    }
    GAMEDATA::getInstance()->setFupanGameData(fupan);
    postNotifyMessage(MSG_GAME_FU_PAN_PLAYER_NOTIFY, "");
}


void MsgHandler::fangZhuLeaveRoom(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if(_mDoc.HasMember("seatId")){
        const rapidjson::Value &result = _mDoc["seatId"];
        postNotifyMessage(MSG_GAME_FANG_ZHU_LEAVE,StringUtils::format("%d",result.GetInt()));
    }
}

void MsgHandler::handleTuiGuangInfo(std::string msg){
    // 获取推广回复{code:162,poxiaoId:poxiaoId,reward:[{gold:50000},{fangka:1}],result:1,havegot:[{gold:50000},{fangka:1},{people:1}],willget:[{gold:50000},{fangka:1},{people:1}]}
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &result = _mDoc["result"];
    if(result.GetInt() != 0){
        if(_mDoc.HasMember("reward")){
            const rapidjson::Value &reward = _mDoc["reward"];
            TuiGuangReward myReward;
            if(reward.HasMember("gold")){
                const rapidjson::Value &gold = reward["gold"];
                myReward.gold = gold.GetInt();
            }
            if(reward.HasMember("fangka")){
                const rapidjson::Value &fangka = reward["fangka"];
                myReward.fangka = fangka.GetInt();
            }
            GAMEDATA::getInstance()->setTuiGuangReward(myReward);
        }
        if(_mDoc.HasMember("havegot")){
            const rapidjson::Value &havegot = _mDoc["havegot"];
            TuiGuangRecord myReward;
            if(havegot.HasMember("gold")){
                const rapidjson::Value &gold = havegot["gold"];
                myReward.gold = gold.GetInt();
            }
            if(havegot.HasMember("fangka")){
                const rapidjson::Value &fangka = havegot["fangka"];
                myReward.fangka = fangka.GetInt();
            }
            GAMEDATA::getInstance()->setTuiGuangRecord(myReward);
        }
        if(_mDoc.HasMember("willget")){
            const rapidjson::Value &willget = _mDoc["willget"];
            TuiGuangPride myReward;
            if(willget.HasMember("gold")){
                const rapidjson::Value &gold = willget["gold"];
                myReward.gold = gold.GetInt();
            }
            if(willget.HasMember("fangka")){
                const rapidjson::Value &fangka = willget["fangka"];
                myReward.fangka = fangka.GetInt();
            }
            GAMEDATA::getInstance()->setTuiGuangPride(myReward);
        }
    }
}


void MsgHandler::handleTuiGuangPrideInfo(std::string msg){
    
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &result = _mDoc["result"];
    postNotifyMessage(MSG_GET_TUI_GUANG_PRIDE,StringUtils::format("%d",result.GetInt()));
}

