#include "json/document.h"
#include "json/rapidjson.h"
#include "server/MsgHandler.h"
#include "server/MsgConfig.h"
#include "userdata/UserData.h"
#include "userdata/UserData.h"
#include "server/SocketDataManage.h"
#include "server/NetworkManage.h"
#include "mahjong/common/state/GameData.h"
#include "mahjong/common/utils/SeatIdUtil.h"
#include "mahjong/common/utils/StringUtil.h"

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
        case MSGCODE_HUODONG_RESPONSE:{
            handleGongGaoInfo(msg);
            break;
        }
        case MSGCODE_IDCARD_RESPONSE:{
            handleCertification(msg);
            break;
        }
        case MSGCODE_HH_FRIEND_GAME_RESPONSE:{
            handleHongZhongEnterRoom(msg);
            break;
        }
        case MSGCODE_HH_FRIEND_JOIN_GAME_RESPONSE:
        {
            handleHZEnterRoomResp(msg);
        }
            break;
        case MSGCODE_HH_READY_NOTIFY:{
            handleHZReadyNoyify(msg);
        }
            break;
        case MSGCODE_HH_MAJIANG_DISCARD_NOTIFY:{
            handleHZFaPaiNotify(msg);
        }
            break;
        case MSGCODE_HH_LOGIN_NOTIFY:{
            addPalyer(msg);
        }
            break;
        case MSGCODE_HH_MAJIANG_DISPATCH_NOTIFY:{
            showOtherPlayedJong(msg);
        }
            break;
        case MSGCODE_HH_MAJIANG_POKER_NOTIFY:
        {
            handleHZDispatchPokerNotify(msg);
        }
            break;
        case MSGCODE_HH_MAJIANG_OUTLINE_RESUME_NOTIFY:{
            handleHZGameReconnectNotify(msg);
        }
            break;
        case MSGCODE_HH_MAJIANG_PLAYER_CPG_NOTIFY:{
            handleHZPlayerActionNotify(msg);
        }
            break;
        case MSGCODE_HH_MAJIANG_PENG_NOTIFY:{
            handleHZPlayerPengNotify(msg);
        }
            break;
        case MSGCODE_HH_MAJIANG_GANG_NOTIFY:{
            handleHZPlayerGangNotify(msg);
        }
            break;
        case MSGCODE_HH_MAJIANG_NO_CHI_PENG_GANG_RESPONSE:{
            handleHZPlayerCanclePGResp(msg);
        }
            break;
        case MSGCODE_HH_MAJIANG_FINISH_NOTIFY:{
            handleHZGameResultNotify(msg);
        }
            break;
        case MSGCODE_HH_IFHU_NOTIFY:{
            handleHZPlayerHuNotify(msg);
        }
            break;
        case MSGCODE_HH_FRIEND_DISMISS_AGREE_NOTIFY:{
            handleDissovleRoomNotify(msg);
        }
            break;
        case MSGCODE_HH_MAJIANG_AGAIN_RESPONSE:{
            handleHZGameContinueResp(msg);
        }
            break;
        case MSGCODE_YQM_RESPONSE:{
            handleInviteCodeResp(msg);
        }
            break;
        case MSGCODE_FEE_TO_FANGKA_LIST_RESPONSE:{
            handleHuafeiChangeListResp(msg);
            break;
        }
            
        case MSGCODE_FEE_TO_FANGKA_RESPONSE:
        {
            handleHuafeiChangeResp(msg);
            break;
        }
            
        case MSGCODE_FEE_EXCHANGE_RECORD_RESPONSE:
        {
            handleHuafeiChangeRecord(msg);
            break;
        }
            break;
        case MSGCODE_MAJIANG_TRUSTEESHIP_NOTIFY:{
            handleTruNotify(msg);
            break;
        }
        case MSGCODE_PHB_RESPONSE:{
            handleLobbyPaiHang(msg);
            break;
        }
        case MSGCODE_DZP_RESPONSE:{
            handleTurntableData(msg);
            break;
        }
        case MSGCODE_DZP_Z_RESPONSE:{
            handleTurntableResult(msg);
            break;
        }
            
        case MSGCODE_DZP_B_SHARE_RESPONSE:{
            handleTurntableShare(msg);
            break;
        }
        case MSGCODE_HH_FRIEND_DISMISS_AGREE_RESULT_NOTIFY:{
            handleHZDissovleRoomNotify(msg);
            break;
        }
        case MSGCODE_FANGKA_TO_FEE_RESPONSE:{
            handleHuafeiChangeFangka(msg);
            break;
        }
        case MSGCODE_CM_FRIEND_GAME_RESPONSE:{
            handleCMOpenRoomResp(msg);
            break;
        }
        case MSGCODE_CM_MAJIANG_DISCARD_NOTIFY:{
            handleCMFapaiNotify(msg);
            break;
        }
        case MSGCODE_CM_FRIEND_JOIN_GAME_RESPONSE:{
            handleCMEnterRoomResp(msg);
            break;
        }
        case MSGCODE_CM_READY_NOTIFY:{
            showOtherReady(msg);
            break;
        }
            
        case MSGCODE_CM_MAJIANG_OUTLINE_RESUME_NOTIFY:{
            handleCMReConnectResp(msg);
            break;
        }
        case MSGCODE_CM_FRIEND_DISMISS_AGREE_NOTIFY:{
            handleDissovleRoomNotify(msg);
            break;
        }
        case MSGCODE_CM_FRIEND_DISMISS_AGREE_RESULT_NOTIFY:{
            handleDissovleRoomSelectedNotify(msg);
            break;
        }
        case MSGCODE_CM_MAJIANG_DISPATCH_NOTIFY:
        {
            showOtherPlayedJong(msg);
            break;
        }
        case MSGCODE_CM_MAJIANG_POKER_NOTIFY:{
            cmNextPlayer(msg);
            break;
        }
        case MSGCODE_CM_MAJIANG_PLAYER_CPG_NOTIFY:{
            showBDCpgNotify(msg);
            break;
        }
        case MSGCODE_CM_MAJIANG_CHI_RESPONSE:
        {
            cmHeroChiResp(msg);
            break;
        }
        case MSGCODE_CM_MAJIANG_CHI_NOTIFY:
        {
            showCMOtherChiNotify(msg);
            break;
        }
        case MSGCODE_CM_MAJIANG_PENG_RESPONSE:{
            bdHeroPengResp(msg);
            break;
        }
        case MSGCODE_CM_MAJIANG_PENG_NOTIFY:{
            showBDOtherPengNotify(msg);
            break;
        }
        case MSGCODE_CM_MAJIANG_GANG_RESPONSE:{
            bdHeroGangResp(msg);
            break;
        }
        case MSGCODE_CM_MAJIANG_GANG_NOTIFY:{
            showBDOtherGangNotify(msg);
            break;
        }
        case MSGCODE_CM_MAJIANG_FINISH_NOTIFY:{
            gameCMResultNotify(msg);
            break;
        }
        case MSGCODE_CM_IFHU_NOTIFY:{
            handleCMPlayerHuNotify(msg);
            break;
        }
        case MSGCODE_CM_MAJIANG_AGAIN_RESPONSE:{
            gameBDContinueResp(msg);
            break;
        }
        case MSGCODE_SPREAD_RESULT_RESPONSE:{
            gameTuiGuangResp(msg);
            break;
        }
        case MSGCODE_HH_MAJIANG_PENG_RESPONSE:{
            handleHzPengResp(msg);
            break;
        }
        case MSGCODE_IFHU_NOTIFY:{
            handleSuZhouHuNotify(msg);
            break;
        }
        case MSGCODE_CM_LOGIN_NOTIFY:{
            addPalyer(msg);
            break;
        }
        case MSGCODE_FPBD_FRIEND_GAME_RESPONSE:{
            handleFanPaiOpenRoom(msg);
            break;
        }
        case MSGCODE_FPBD_MAJIANG_OUTLINE_RESUME_NOTIFY:{
            handleFanPaiConnect(msg);
            break;
        }
        case MSGCODE_FPBD_FRIEND_JOIN_GAME_RESPONSE:{
            handleFanPaiEnterRoom(msg);
            break;
        }
        case MSGCODE_FPBD_LOGIN_NOTIFY:{
            addPalyer(msg);
            break;
        }
        case MSGCODE_FPBD_READY_NOTIFY:{
            showOtherReady(msg);
            break;
        }
        case MSGCODE_FPBD_MAJIANG_DISCARD_NOTIFY:{
            handleFPFapaiNotify(msg);
            break;
        }
        case MSGCODE_FPBD_MAJIANG_DISPATCH_NOTIFY:
        {
            showOtherPlayedJong(msg);
            break;
        }
        case MSGCODE_FPBD_MAJIANG_POKER_NOTIFY:{
            fpNextPlayer(msg);
            break;
        }
        case MSGCODE_FPBD_FRIEND_DISMISS_AGREE_NOTIFY:{
            handleDissovleRoomNotify(msg);
            break;
        }
        case MSGCODE_FPBD_FRIEND_DISMISS_AGREE_RESULT_NOTIFY:{
            handleDissovleRoomSelectedNotify(msg);
            break;
        }
        case MSGCODE_FPBD_MAJIANG_PLAYER_CPG_NOTIFY:{
            showBDCpgNotify(msg);
            break;
        }
        case MSGCODE_FPBD_MAJIANG_PENG_RESPONSE:{
            bdHeroPengResp(msg);
            break;
        }
        case MSGCODE_FPBD_MAJIANG_PENG_NOTIFY:{
            showBDOtherPengNotify(msg);
            break;
        }
        case MSGCODE_FPBD_MAJIANG_GANG_RESPONSE:{
            bdHeroGangResp(msg);
            break;
        }
        case MSGCODE_FPBD_MAJIANG_GANG_NOTIFY:{
            showBDOtherGangNotify(msg);
            break;
        }
        case MSGCODE_FPBD_MAJIANG_FINISH_NOTIFY:{
            gameCMResultNotify(msg);
            break;
        }
        case MSGCODE_FPBD_MAJIANG_AGAIN_RESPONSE:{
            gameBDContinueResp(msg);
            break;
        }
        case MSGCODE_FPBD_IFHU_NOTIFY:{
            handleCMPlayerHuNotify(msg);
            break;
        }
        case MSGCODE_DAIKAI_RESPONSE:{
            manageAgencyResp(msg);
            break;
        }
        case MSGCODE_DAIKAI_FRIEND_GAME_BILL_RESPONSE:{
            agencyBillResp(msg);
            break;
        }
        case MSGCODE_IP_NOTIFY:{
            playerIPCheckNotify(msg);
            break;
        }
        case MSGCODE_DAIKAI_BILL_RESPONSE:{
            agencyResultResp(msg);
            break;
        }
        default:
            break;
    }
}


void MsgHandler::postNotifyMessage(std::string event_name, void* msg){
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
    postNotifyMessage(MSG_WAN_JIA_WEI_XIN_QUN, nullptr);
}

//{code:105,poxiaoId:"adv",content:"abc",seatId:1}
void MsgHandler::playerChatNotify(std::string msg){
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
    if (_mDoc.HasMember("mark")){
        chatData.mark = true;
    }else{
        chatData.mark = false;
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
    postNotifyMessage(MSG_PLAYER_CHAT_NOTIFY, nullptr);
}


//{code:107, poxiaoId : poxiaoId, roomstyle : [{rsid:"1111", rsname : "ddd"}, { rsid:"1112", rsname : "dddd" }]}
void MsgHandler::roomListResp(std::string msg){
    //    rapidjson::Document _mDoc;
    //    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    //    _mDoc.Parse<0>(msg.c_str());
    //    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    //    const rapidjson::Value &roomstyle = _mDoc["roomstyle"];
    //    RoomListData roomlist;
    //    for (int i = 0; i < roomstyle.Capacity(); ++i){
    //        RoomData data;
    //        const rapidjson::Value &temp = roomstyle[i];
    //        data.roomId = temp["rsid"].GetInt();
    //        data.maxGold = temp["max"].GetInt();
    //        data.minGold = temp["min"].GetInt();
    //        data.base = temp["base"].GetInt();
    //        data.hua = temp["hua"].GetInt();
    //        roomlist.rooms.push_back(data);
    //    }
    //    if(_mDoc.HasMember("match")){
    //        const rapidjson::Value &match = _mDoc["match"];
    //        for (int j=0 ; j<match.Capacity(); j++){
    //            CompetitionRoom room;
    //            const rapidjson::Value &temp = match[j];
    //            room.roomId = temp["id"].GetString();
    //            room.name = temp["name"].GetString();
    //            room.fangka = temp["fangka"].GetString();
    //            room.prize = temp["prize"].GetString();
    //            room.rule = temp["rule"].GetString();
    //            roomlist.matchList.push_back(room);
    //        }
    //    }
    //    GAMEDATA::getInstance()->setRoomList(roomlist);
    //    postNotifyMessage(MSG_ROOM_LIST_RESP,&roomlist);
}

// {code:118,result:"1"}
void MsgHandler::changeGenderResp(std::string msg){
    
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
    char* buf = const_cast<char*>(StringUtil::itos(result.GetInt()).c_str());
    postNotifyMessage(MSG_CHANGE_GENDER_RESP, buf);
}

// 获取公告回复{code:141,poxiaoId:poxiaoId,content:"11111111"}
void MsgHandler::handleNoticeResp(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    GameActivityData* data = new GameActivityData();
    if(_mDoc.HasMember("content")){
        auto &content = _mDoc["content"];
        data->imageUrl = content.GetString();
    }
    if(_mDoc.HasMember("url")){
        auto &url = _mDoc["url"];
        data->jumpUrl = url.GetString();
    }else{
        data->jumpUrl = "";
    }
    if(_mDoc.HasMember("time")){
        auto &time = _mDoc["time"];
        data->showTime = time.GetString();
    }else{
        data->showTime = "";
    }
    if(_mDoc.HasMember("cc")){
        auto &cc = _mDoc["cc"];
        if(cc.HasMember("pic")){
            data->imageUrl2 = cc["pic"].GetString();
        }
        if(cc.HasMember("android")){
            data->downLoadUrlAndroid = cc["android"].GetString();
        }
        if(cc.HasMember("apple")){
            data->downLoadUrlIOS = cc["apple"].GetString();
        }
    }
    postNotifyMessage(MSG_WAN_JIA_GONG_GAO, data);
}

// 获取走马灯回复{code:143,poxiaoId:poxiaoId,content:"11111111"}
void MsgHandler::handleScrollTextResp(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if(_mDoc.HasMember("content")){
        const rapidjson::Value &content = _mDoc["content"];
        char* buf = const_cast<char*>(content.GetString());
        postNotifyMessage(MSG_SCROLL_TEXT, buf);
    }
}

//{code:150,poxiaoId:poxiaoId,lequan:11,bangzuan:22,diamond:33,gold:55,jifen:0}
void MsgHandler::getPlayerInfoResp(std::string msg){
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
    
    if(_mDoc.HasMember("fee")){
        const rapidjson::Value &fee = _mDoc["fee"];
        UserData::getInstance()->setHuafeiQuan(fee.GetDouble());
    }
    
    if(_mDoc.HasMember("jifen")){
        const rapidjson::Value &jifen = _mDoc["jifen"];
        GAMEDATA::getInstance()->setScore(jifen.GetInt());
    }
    
    if(_mDoc.HasMember("ip")){
        const rapidjson::Value &ip = _mDoc["ip"];
        GAMEDATA::getInstance()->setIP(ip.GetString());
    }
    if(_mDoc.HasMember("share1")){
        const rapidjson::Value &share1 = _mDoc["share1"];
        MahjongShareData1 data1;
        data1.pic = share1["pic"].GetString();
        data1.url = share1["url"].GetString();
        data1.content = share1["content"].GetString();
        data1.head = share1["head"].GetString();
        if(share1.HasMember("type")){
            data1.type = share1["type"].GetString();
        }
        if(share1.HasMember("phead")){
            data1.phead = share1["phead"].GetString();
        }
        if(share1.HasMember("pcontent")){
            data1.pcontent = share1["pcontent"].GetString();
        }
        GAMEDATA::getInstance()->setMahjongShareData1(data1);
    }
    if(_mDoc.HasMember("share2")){
        const rapidjson::Value &share2 = _mDoc["share2"];
        MahjongShareData2 data2;
        data2.pic = share2["pic"].GetString();
        data2.url = share2["url"].GetString();
        data2.content = share2["content"].GetString();
        data2.head = share2["head"].GetString();
        if(share2.HasMember("phead")){
            data2.phead = share2["phead"].GetString();
        }
        if(share2.HasMember("pcontent")){
            data2.pcontent = share2["pcontent"].GetString();
        }
        if(share2.HasMember("type")){
            data2.type = share2["type"].GetString();
        }
        GAMEDATA::getInstance()->setMahjongShareData2(data2);
    }
    if(_mDoc.HasMember("share3")){
        const rapidjson::Value &share3 = _mDoc["share3"];
        MahjongShareData3 data3;
        data3.pic = share3["pic"].GetString();
        data3.url = share3["url"].GetString();
        data3.head = share3["head"].GetString();
        data3.content = share3["content"].GetString();
        if(share3.HasMember("phead")){
            data3.phead = share3["phead"].GetString();
        }
        if(share3.HasMember("pcontent")){
            data3.pcontent = share3["pcontent"].GetString();
        }
        if(share3.HasMember("type")){
            data3.type = share3["type"].GetString();
        }
        GAMEDATA::getInstance()->setMahjongShareData3(data3);
    }
    if(_mDoc.HasMember("share4")){
        const rapidjson::Value &share4 = _mDoc["share4"];
        MahjongShareData4 data4;
        data4.pic = share4["pic"].GetString();
        data4.url = share4["url"].GetString();
        data4.head = share4["head"].GetString();
        data4.content = share4["content"].GetString();
        if(share4.HasMember("phead")){
            data4.phead = share4["phead"].GetString();
        }
        if(share4.HasMember("pcontent")){
            data4.pcontent = share4["pcontent"].GetString();
        }
        if(share4.HasMember("type")){
            data4.type = share4["type"].GetString();
        }
        GAMEDATA::getInstance()->setMahjongShareData4(data4);
    }
    if(_mDoc.HasMember("share5")){
        const rapidjson::Value &share5 = _mDoc["share5"];
        MahjongShareData5 data5;
        data5.pic = share5["pic"].GetString();
        data5.url = share5["url"].GetString();
        data5.head = share5["head"].GetString();
        data5.content = share5["content"].GetString();
        if(share5.HasMember("phead")){
            data5.phead = share5["phead"].GetString();
        }
        if(share5.HasMember("pcontent")){
            data5.pcontent = share5["pcontent"].GetString();
        }
        if(share5.HasMember("type")){
            data5.type = share5["type"].GetString();
        }
        GAMEDATA::getInstance()->setMahjongShareData5(data5);
    }
    if(_mDoc.HasMember("share6")){
        const rapidjson::Value &share6 = _mDoc["share6"];
        MahjongShareData6 data6;
        data6.pic = share6["pic"].GetString();
        data6.url = share6["url"].GetString();
        data6.head = share6["head"].GetString();
        data6.content = share6["content"].GetString();
        if(share6.HasMember("phead")){
            data6.phead = share6["phead"].GetString();
        }
        if(share6.HasMember("pcontent")){
            data6.pcontent = share6["pcontent"].GetString();
        }
        if(share6.HasMember("type")){
            data6.type = share6["type"].GetString();
        }
        GAMEDATA::getInstance()->setMahjongShareData6(data6);
    }
    
}


// 修改图片回复{code:153,result:"1",gender:1} 1成功 其他 失败
void MsgHandler::getHeadImageChangeResp(std::string msg){
    
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
    char* buf = const_cast<char*>(StringUtil::itos(result.GetInt()).c_str());
    postNotifyMessage(MSG_PLAYER_CHANGE_HEAD_RESP,buf);
}

// 用户反馈回复{code:155,poxiaoId:poxiaoId,result:"1"} 1成功 0 5分钟内发送一次
void MsgHandler::getFeedBackResp(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &result = _mDoc["result"];
    char* buf = const_cast<char*>(result.GetString());
    postNotifyMessage(MSG_PLAYER_FEED_BACK_RESP, buf);
}

// 用户在别的设备上登陆{code:156,poxiaoId:poxiaoId}
void MsgHandler::otherClientReplace(std::string msg){
    postNotifyMessage(MSG_PLAYER_REPLACE_LOGIN, nullptr);
}



// 苹果开关回复{code:158,poxiaoId:poxiaoId,result:0} 0微信1苹果
void MsgHandler::handleGamePayType(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if(_mDoc.HasMember("result")){
        const rapidjson::Value &result = _mDoc["result"];
        UserData::getInstance()->setWeixinPayOpen(result.GetInt() == 0 ?true:false);
    }
    postNotifyMessage(MSG_UPDATE_LEQUAN_SHANG_CHEN_SHOW, nullptr);
}

//获取推广回复{code:162,poxiaoId:poxiaoId,reward:[{gold:50000},{fangka:1}],result:1,havegot:[{gold:50000},{fangka:1},{people:1}],willget:[{gold:50000},{fangka:1},{people:1}]}
void MsgHandler::handleTuiGuangInfo(std::string msg){
    
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


// 领取推广奖励回复{code:164,poxiaoId:poxiaoId,result:0}
void MsgHandler::handleTuiGuangPrideInfo(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &result = _mDoc["result"];
    char* buf = const_cast<char*>(StringUtils::format("%d",result.GetInt()).c_str());
    postNotifyMessage(MSG_GET_TUI_GUANG_PRIDE,buf);
}

//{code:166,poxiaoId:poxiaoId,content:[{pic:"http://1212.com",url:"11",time:"6"},{pic:"http://1212.com",url:"11",time:"6"}]}
void MsgHandler::handleGongGaoInfo(std:: string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    GameGongGao gameGongGao;
    if(_mDoc.HasMember("content")){
        auto &content = _mDoc["content"];
        for (int i=0; i<content.Capacity(); i++){
            GameActivityData data;
            auto &temp = content[i];
            data.imageUrl = temp["pic"].GetString();
            data.jumpUrl = temp["url"].GetString();
            data.showTime = StringUtils::format("%d",temp["time"].GetInt());
            gameGongGao.gongGaoData.push_back(data);
        }
    }
    postNotifyMessage(MSG_GET_WAN_JIA_GONG_GAO,&gameGongGao);
}

// 实名认证回复{code:168,poxiaoId:poxiaoId,result:0}
void MsgHandler::handleCertification(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &result = _mDoc["result"];
    std:: string newResult = StringUtils::format("%d",result.GetInt());
    auto buf = const_cast<char*>(newResult.c_str());
    postNotifyMessage(MSG_GET_WAN_JIA_SHI_MING,buf);
}



//{code:1001,poxiaoId:poxiaoId,result:"0",seatId:1,other:[{seatId:seatId,gold:0,diamond:0,jifen:0,lequan:0,gender:0,nickname:'aaa',ifready:1}]}
void MsgHandler::enterRoomResp(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    GAMEDATA::getInstance()->clearPlayersInfo();//清除全部的玩家数据
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
    PayGoldPoint pointInfo;
    if(_mDoc.HasMember("fee")){
        const rapidjson::Value &fee = _mDoc["fee"];
        pointInfo.fee = fee.GetString();
    }
    if(_mDoc.HasMember("gold")){
        const rapidjson::Value &fangka = _mDoc["gold"];
        pointInfo.gold = fangka.GetString();
    }
    if(_mDoc.HasMember("applegold")){
        const rapidjson::Value &applefangka = _mDoc["applegold"];
        pointInfo.applegold = applefangka.GetString();
    }
    if(_mDoc.HasMember("applefee")){
        const rapidjson::Value &applefee = _mDoc["applefee"];
        pointInfo.applefee = applefee.GetString();
    }
    if(_mDoc.HasMember("point")){
        const rapidjson::Value &point = _mDoc["point"];
        pointInfo.payId = point.GetString();
    }
    GAMEDATA::getInstance()->setPayGoldPoint(pointInfo);
    
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
                PlayerInfo* info = new PlayerInfo();
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
    PlayerInfo* info = new PlayerInfo();
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
    GAMEDATA::getInstance()->setGameType(1);
    postNotifyMessage(MSG_ENTER_ROOM_RESP, &resp);
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
        //分享界面信息
        if(_mDoc.HasMember("scon")){
            const rapidjson::Value &scon = _mDoc["scon"];
            UserData::getInstance()->setShareTextContent(scon.GetString());
        }
        //推广的用户数量
        if(_mDoc.HasMember("sconnum")){
            const rapidjson::Value &scon = _mDoc["sconnum"];
            UserData::getInstance()->setShareTextContentNum(scon.GetString());
        }
        //公众号
        if(_mDoc.HasMember("gongzhonghao")){
            const rapidjson::Value &gongzhonghao = _mDoc["gongzhonghao"];
            UserData::getInstance()->setGongZhongHao(gongzhonghao.GetString());
        }
        //用户当前的支付方式
        if(_mDoc.HasMember("payway")){
            const rapidjson::Value &payway = _mDoc["payway"];
            UserData::getInstance()->setUserPayWay(payway.GetString());
        }
        //微信公众号折扣信息
        if(_mDoc.HasMember("gzh")){
            const rapidjson::Value &gzh = _mDoc["gzh"];
            UserData::getInstance()->setDiscountInfo(gzh.GetString());
        }
        //用户当前拥有的抽奖次数
        if(_mDoc.HasMember("dzpc")){
            const rapidjson::Value &dzpc = _mDoc["dzpc"];
            UserData::getInstance()->setTurntableNumber(dzpc.GetString());
        }
        if(_mDoc.HasMember("dzpw")){
            const rapidjson::Value &dzpw = _mDoc["dzpw"];
            GAMEDATA::getInstance()->setShowTurnTableState(atoi(dzpw.GetString()));
        }
        //比赛开关
        if(_mDoc.HasMember("matchsw")){
            const rapidjson::Value &matchsw = _mDoc["matchsw"];
            UserData::getInstance()->setNeedShowCompetition((strcmp(matchsw.GetString(),"1") == 0)?true:false);
        }else{
            UserData::getInstance()->setNeedShowCompetition(false);
        }
        //
        if(_mDoc.HasMember("lys")){
            const rapidjson::Value &lys = _mDoc["lys"];
            UserData::getInstance()->setNeedShowYaoQingButton((strcmp(lys.GetString(),"1") == 0)?true:false);
        }
        if(_mDoc.HasMember("lss")){
            const rapidjson::Value &lss = _mDoc["lss"];
            UserData::getInstance()->setNeedShowJiZanButton((strcmp(lss.GetString(),"1") == 0)?true:false);
        }
        if(_mDoc.HasMember("oper")){
            const rapidjson::Value &oper = _mDoc["oper"];
            UserData::getInstance()->setCollaborateUrl(oper.GetString());
        }
        //是否是代理
        if(_mDoc.HasMember("isdaili")){
            const rapidjson::Value &isdaili = _mDoc["isdaili"];
            UserData::getInstance()->setIsAgency((strcmp(isdaili.GetString(),"1") == 0)?true:false);
        }
        //服务端提供最新的app版本号
        if(_mDoc.HasMember("newv")){
            const rapidjson::Value &newv = _mDoc["newv"];
            UserData::getInstance()->setServerAppVersion(newv.GetString());
        }
        //集赞领奖
        if(_mDoc.HasMember("wxs")){
            const rapidjson::Value &wxs = _mDoc["wxs"];
            UserData::getInstance()->setJiZanText(wxs.GetString());
        }
        if(_mDoc.HasMember("wxk")){
            const rapidjson::Value &wxk = _mDoc["wxk"];
            UserData::getInstance()->setJiZanKefu(wxk.GetString());
        }
        
        if(_mDoc.HasMember("wxt")){
            const rapidjson::Value &wxt = _mDoc["wxt"];
            if(wxt.HasMember("wxkf")){
                const rapidjson::Value &wxkf = wxt["wxkf"];
                UserData::getInstance()->setWeiXinKeFu(wxkf.GetString());
            }
            if(wxt.HasMember("wxtip")){
                const rapidjson::Value &wxtip = wxt["wxtip"];
                UserData::getInstance()->setWeiXinPayText(wxtip.GetString());
            }
            
        }
        //微信分享配置
        if(_mDoc.HasMember("share1")){
            const rapidjson::Value &share1 = _mDoc["share1"];
            MahjongShareData1 data1;
            data1.pic = share1["pic"].GetString();
            data1.url = share1["url"].GetString();
            data1.content = share1["content"].GetString();
            data1.head = share1["head"].GetString();
            if(share1.HasMember("type")){
                data1.type = share1["type"].GetString();
            }
            if(share1.HasMember("phead")){
                data1.phead = share1["phead"].GetString();
            }
            if(share1.HasMember("pcontent")){
                data1.pcontent = share1["pcontent"].GetString();
            }
            GAMEDATA::getInstance()->setMahjongShareData1(data1);
        }
        if(_mDoc.HasMember("share2")){
            const rapidjson::Value &share2 = _mDoc["share2"];
            MahjongShareData2 data2;
            data2.pic = share2["pic"].GetString();
            data2.url = share2["url"].GetString();
            data2.content = share2["content"].GetString();
            data2.head = share2["head"].GetString();
            if(share2.HasMember("phead")){
                data2.phead = share2["phead"].GetString();
            }
            if(share2.HasMember("pcontent")){
                data2.pcontent = share2["pcontent"].GetString();
            }
            if(share2.HasMember("type")){
                data2.type = share2["type"].GetString();
            }
            GAMEDATA::getInstance()->setMahjongShareData2(data2);
        }
        if(_mDoc.HasMember("share3")){
            const rapidjson::Value &share3 = _mDoc["share3"];
            MahjongShareData3 data3;
            data3.pic = share3["pic"].GetString();
            data3.url = share3["url"].GetString();
            data3.head = share3["head"].GetString();
            data3.content = share3["content"].GetString();
            if(share3.HasMember("phead")){
                data3.phead = share3["phead"].GetString();
            }
            if(share3.HasMember("pcontent")){
                data3.pcontent = share3["pcontent"].GetString();
            }
            if(share3.HasMember("type")){
                data3.type = share3["type"].GetString();
            }
            GAMEDATA::getInstance()->setMahjongShareData3(data3);
        }
        if(_mDoc.HasMember("share4")){
            const rapidjson::Value &share4 = _mDoc["share4"];
            MahjongShareData4 data4;
            data4.pic = share4["pic"].GetString();
            data4.url = share4["url"].GetString();
            data4.head = share4["head"].GetString();
            data4.content = share4["content"].GetString();
            if(share4.HasMember("phead")){
                data4.phead = share4["phead"].GetString();
            }
            if(share4.HasMember("pcontent")){
                data4.pcontent = share4["pcontent"].GetString();
            }
            if(share4.HasMember("type")){
                data4.type = share4["type"].GetString();
            }
            GAMEDATA::getInstance()->setMahjongShareData4(data4);
        }
        if(_mDoc.HasMember("share5")){
            const rapidjson::Value &share5 = _mDoc["share5"];
            MahjongShareData5 data5;
            data5.pic = share5["pic"].GetString();
            data5.url = share5["url"].GetString();
            data5.head = share5["head"].GetString();
            data5.content = share5["content"].GetString();
            if(share5.HasMember("phead")){
                data5.phead = share5["phead"].GetString();
            }
            if(share5.HasMember("pcontent")){
                data5.pcontent = share5["pcontent"].GetString();
            }
            if(share5.HasMember("type")){
                data5.type = share5["type"].GetString();
            }
            GAMEDATA::getInstance()->setMahjongShareData5(data5);
        }
        if(_mDoc.HasMember("dyjpic")){
            const rapidjson::Value &dyjpic = _mDoc["dyjpic"];
            GAMEDATA::getInstance()->setDaYingJiaPic(dyjpic.GetString());
        }
        if(_mDoc.HasMember("bottom")){
            const rapidjson::Value &bottom = _mDoc["bottom"];
            GAMEDATA::getInstance()->setBottomText(bottom.GetString());
        }
        if(_mDoc.HasMember("free")){
            const rapidjson::Value &free = _mDoc["free"];
            GAMEDATA::getInstance()->setNeedShowShareBtn((strcmp(free.GetString(),"1") == 0)?true:false);
        }
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
        if(_mDoc.HasMember("fee")){
            const rapidjson::Value &fee = _mDoc["fee"];
            UserData::getInstance()->setHuafeiQuan(fee.GetDouble());
        }
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
        if(_mDoc.HasMember("idcard")){
            const rapidjson::Value &idcard = _mDoc["idcard"];
            GAMEDATA::getInstance()->setCertification(idcard.GetInt()==1?true:false);
        }
        GameHongBaoPride2 pride;
        if(_mDoc.HasMember("dyjfee")){
            pride.dyjfee = _mDoc["dyjfee"].GetString();
            GAMEDATA::getInstance()->setNeedShowHongbaoResult(true);
        }else{
            pride.dyjfee = "0";
        }
        if(_mDoc.HasMember("dsjfee")){
            pride.dsjfee = _mDoc["dsjfee"].GetString();
            GAMEDATA::getInstance()->setNeedShowHongbaoResult(true);
        }else{
            pride.dsjfee = "0";
        }
        if(_mDoc.HasMember("fzfee")){
            pride.fzfee = _mDoc["fzfee"].GetString();
            GAMEDATA::getInstance()->setNeedShowHongbaoResult(true);
        }else{
            pride.fzfee = "0";
        }
        if(_mDoc.HasMember("sxlmfee")){
            pride.sxlmfee = _mDoc["sxlmfee"].GetString();
            GAMEDATA::getInstance()->setNeedShowHongbaoResult(true);
        }else{
            pride.sxlmfee = "0";
        }
        GAMEDATA::getInstance()->setGameHongBaoPride2(pride);
        
        ShareActivityData data;
        if(_mDoc.HasMember("share")){
            const rapidjson::Value &share = _mDoc["share"];
            data.result = share.GetString();
        }
        if(_mDoc.HasMember("wx")){
            const rapidjson::Value &wx = _mDoc["wx"];
            data.wx = wx.GetString();
        }
        if(_mDoc.HasMember("prize1")){
            const rapidjson::Value &prize1 = _mDoc["prize1"];
            data.prize = prize1.GetString();
        }
        if(_mDoc.HasMember("num1")){
            const rapidjson::Value &num1 = _mDoc["num1"];
            data.num = num1.GetString();
        }
        GAMEDATA::getInstance()->setShareActivityData(data);
        char* buf = const_cast<char*>(LOGIN_SUCCESS);
        postNotifyMessage(MSG_LOGIN_RESP, buf);
    }
    else{
        char* buf = const_cast<char*>("");
        postNotifyMessage(MSG_LOGIN_RESP,buf);
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
    
    PlayerInfo* info = new PlayerInfo();
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
    postNotifyMessage(MSG_PALYER_ENTER_GAME, nullptr);
}


//{{code:1009, poxiaoId : poxiaoId, seatId : 1 }
void MsgHandler::showOtherReady(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &seatId = _mDoc["seatId"];
    vector<PlayerInfo*> players = GAMEDATA::getInstance()->getPlayersInfo();
    for (int i = 0; i < players.size(); i++){
        if(players.at(i)->getSeatId() == seatId.GetInt() ){
            players.at(i)->setIsReady(true);
        }
    }
    char* buf = const_cast<char*>(StringUtil::itos(seatId.GetInt()).c_str());
    postNotifyMessage(MSG_READY_NOTIFY, buf);
}
//服务端到客户端掉线通知{code:1010,poxiaoId:poxiaoId}
void MsgHandler::getPlayerOffLineNotify(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if(_mDoc.HasMember("seatId")){
        const rapidjson::Value &seatId = _mDoc["seatId"];
        char* buf = const_cast<char*>(StringUtils::format("%d",seatId.GetInt()).c_str());
        postNotifyMessage(MSG_PLAYER_OFF_LINE_NOTIFY, buf);
    }
}

void MsgHandler::dailyPrideResp(std::string msg){
    // 金币抽奖情况获取回复{code:1023,poxiaoId:poxiaoId,result:"1",gold:"50000",
    //prize:[{gold:30000},{lequan:300},{lequan:800},{lequan:100},{bangzuan:80},{bangzuan:50},{bangzuan:20},{gold:60000},{diamond:11}],
    //count:"1",max:"5"} result1为可以参加，0为不可参加 ，count为可以抽奖几次，max为最多能抽奖几次，prize奖品里面数值为整数
    //    rapidjson::Document _mDoc;
    //    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    //    _mDoc.Parse<0>(msg.c_str());
    //    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    //    DailyPrideData data;
    //    if (_mDoc.HasMember("result")){
    //        data.result = _mDoc["result"].GetString();
    //    }
    //    if (_mDoc.HasMember("gold")){
    //        data.needGold = _mDoc["gold"].GetString();
    //    }
    //    if (_mDoc.HasMember("count")){
    //        data.count = _mDoc["count"].GetString();
    //    }
    //    if (_mDoc.HasMember("max")){
    //        data.max = _mDoc["max"].GetString();
    //    }
    //    if (_mDoc.HasMember("prize")){
    //        const rapidjson::Value &prize = _mDoc["prize"];
    //        for (int i = 0; i < prize.Capacity(); i++){
    //            PrideData info;
    //            const rapidjson::Value &temp = prize[i];
    //            if (temp.HasMember("gold")){
    //                info.type = PrideType::gold;
    //                info.number = temp["gold"].GetInt();
    //            }
    //            if (temp.HasMember("lequan")){
    //                info.type = PrideType::lequan;
    //                info.number = temp["lequan"].GetInt();
    //            }
    //            if (temp.HasMember("bangzuan")){
    //                info.type = PrideType::lockDiammond;
    //                info.number = temp["bangzuan"].GetInt();
    //            }
    //            if (temp.HasMember("fangka")){
    //                info.type = PrideType::fangka;
    //                info.number = temp["fangka"].GetDouble();
    //            }
    //            data.prides.push_back(info);
    //        }
    //    }
    //    GAMEDATA::getInstance()->setDailyPrideData(data);
    //    postNotifyMessage(MSG_PLAYER_DAILY_PRIDE, nullptr);
}

void MsgHandler::todayPrideResp(std::string msg){
    // 金币抽奖奖励领取回复{code:1025,poxiaoId:poxiaoId,result:"1",prize:{gold:10}}
    //1为成功 0失败,prize为抽到的奖品，奖品里面数值为整数
    //    rapidjson::Document _mDoc;
    //    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    //    _mDoc.Parse<0>(msg.c_str());
    //    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    //    TodayPrideData  data;
    //    if (_mDoc.HasMember("result")){
    //        data.result = _mDoc["result"].GetString();
    //    }
    //    if (_mDoc.HasMember("rest")){
    //        data.rest = _mDoc["rest"].GetInt();
    //    }
    //    if (_mDoc.HasMember("prize")){
    //        PrideData info;
    //        const rapidjson::Value &temp = _mDoc["prize"];
    //        if (temp.HasMember("gold")){
    //            info.type = PrideType::gold;
    //            info.number = temp["gold"].GetInt();
    //        }
    //        if (temp.HasMember("lequan")){
    //            info.type = PrideType::lequan;
    //            info.number = temp["lequan"].GetInt();
    //        }
    //        if (temp.HasMember("bangzuan")){
    //            info.type = PrideType::lockDiammond;
    //            info.number = temp["bangzuan"].GetInt();
    //        }
    //        if (temp.HasMember("fangka")){
    //            info.type = PrideType::fangka;
    //            info.number = temp["fangka"].GetDouble();
    //        }
    //        data.pride = info;
    //    }
    //    GAMEDATA::getInstance()->setTodayPrideData(data);
    //    postNotifyMessage(MSG_PLAYER_TODAY_PRIDE, nullptr);
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
    postNotifyMessage(MSG_PLAYER_LEQUAN_CHANGE_LIST, nullptr);
    
}


// 乐券商城兑换回复{code:1043,poxiaoId:poxiaoId,result:"1"} 1成功0失败
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
    postNotifyMessage(MSG_PLAYER_LEQUAN_EXCHANGE, nullptr);
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
    postNotifyMessage(MSG_PLAYER_GOLD_CHANGE_LIST, nullptr);
    
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
    postNotifyMessage(MSG_PLAYER_GOLD_CHANGE_LIST, nullptr);
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
    char* buf = const_cast<char*>(result.GetString());
    postNotifyMessage(MSG_PLAYER_GOLD_CHANGE_RESP, buf);
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
    postNotifyMessage(MSG_PLAYER_FIRST_CHARGE, nullptr);
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
            rec.time =temp["time"].GetString();
            rec.phone = temp["phone"].GetString();
            records.records.push_back(rec);
        }
    }
    GAMEDATA::getInstance()->setLeChangeRecord(records);
    postNotifyMessage(MSG_PLAYER_LEQUAN_EXCHANGE_RECORD, nullptr);
}

//再来一局回复{code:1996,poxiaoId:poxiaoId,result:1,rsid:1000}1为成功 2为金币小于下限 3为金币高于上限rsid为跳转房间
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
    GAMEDATA::getInstance()->setShowDialogType(result.GetInt());
    GAMEDATA::getInstance()->setEnterRoomResp(resp);
    postNotifyMessage(MSG_HERO_CONTINUE_RESP, nullptr);
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
        GAMEDATA::getInstance()->setDissovleDialogRemove(true);
        if(GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom){
            GAMEDATA::getInstance()->setShowRoomDismiss(true);
        }
    }
    GAMEDATA::getInstance()->setRemovePlayer(data);
    postNotifyMessage(MSG_PLAYER_REMOVE, nullptr);
}

//{code:2002, poxiaoId : poxiaoId, start : 1, poker : 1, 2, 4, 5, 6}
void MsgHandler::getHeroJongs(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if(_mDoc.HasMember("seatId")){
        GAMEDATA::getInstance()->setHeroSeatId(atoi(_mDoc["seatId"].GetString()));
    }
    MahjongFaPaiData faPaiData;
    faPaiData.heroPokers = _mDoc["poker"].GetString();
    if(_mDoc.HasMember("hua")){
        const rapidjson::Value &huama = _mDoc["hua"];
        for (int i=0; i<huama.Capacity(); i++) {
            const rapidjson::Value &temp = huama[i];
            HuaData data;
            data.hua = temp["hua"].GetString();
            data.setaId = temp["seatId"].GetString();
            data.poxiaoId = temp["poxiaoId"].GetString();
            faPaiData.huas.push_back(data);
        }
    }
    faPaiData.dice = _mDoc["dice"].GetString();
    faPaiData.baozi = _mDoc["baozi"].GetString();
    if(_mDoc.HasMember("diling")){
        const rapidjson::Value &diling = _mDoc["diling"];
        GAMEDATA::getInstance()->setPrivateDLNum(diling.GetString());
        faPaiData.diling = diling.GetString();
    }
    if(_mDoc.HasMember("huangfan")){
        const rapidjson::Value &huangfan = _mDoc["huangfan"];
        GAMEDATA::getInstance()->setPrivateHFNum(huangfan.GetString());
        faPaiData.huangfan = huangfan.GetString();
    }
    faPaiData.start = _mDoc["start"].GetInt();
    if(_mDoc.HasMember("prjucount")){
        faPaiData.prjucount = _mDoc["prjucount"].GetInt();
    }
    const rapidjson::Value &rest = _mDoc["rest"];
    faPaiData.rest = rest.GetString();;
    PlayerCpgtData tingData;
    if(_mDoc.HasMember("hu")){
        tingData.hu =  1;
    }else{
        tingData.hu =  0;
    }
    if(_mDoc.HasMember("angang")){
        faPaiData.hasGang = true;
        const rapidjson::Value &angang = _mDoc["angang"];
        GangData gangData;
        gangData.gang = angang.GetString();
        gangData.flag = 1;
        tingData.playerGang.push_back(gangData);
        tingData.seatId = GAMEDATA::getInstance()->getHeroSeatId();
    }
    if (_mDoc.HasMember("ting1")){
        const rapidjson::Value &ting1 = _mDoc["ting1"];
        for(int i=0;i<ting1.Capacity();i++){
            HeroHuPaiData huPaiData;
            auto &temp = ting1[i];
            if(temp.HasMember("poker")){
                huPaiData.poker = temp["poker"].GetInt();
            }
            if(temp.HasMember("hu1")){
                const rapidjson::Value &data =  temp["hu1"];
                for (int i=0; i<data.Capacity(); i++) {
                    const rapidjson::Value &tem = data[i];
                    HuPokerData pd;
                    pd.poker = tem["hu"].GetString();
                    pd.num = tem["num"].GetString();
                    huPaiData.data.push_back(pd);
                }
            }
            tingData.heroHu.push_back(huPaiData);
        }
    }
    faPaiData.mjHuData = tingData;
    GAMEDATA::getInstance()->setIsTrusteeship(false);
    GAMEDATA::getInstance()->setMahjongFaPaiData(faPaiData);
    postNotifyMessage(MSG_GAME_START_FAPAI_NOTIFY, nullptr);
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
    char* buf = const_cast<char*>(resultMsg.c_str());
    postNotifyMessage(MSG_OTHER_PALYER_JONG, buf);
}

//{code:2006,poxiaoId:poxiaoId,seatId:seatId,poker:1,chi:[{chi:1,2,3},{chi:2,3,4}],peng:"1,2,3",gang:"1,1,1,1"}
void MsgHandler::showCpgNotify(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &poker = _mDoc["poker"];
    const rapidjson::Value &seatId = _mDoc["sId"];
    HeroCpgRespData cpgRespData;
    PlayerCpgtData cpgData;
    cpgData.poker = poker.GetString();
    cpgData.sId = seatId.GetInt();
    if (_mDoc.HasMember("peng")){
        const rapidjson::Value &peng = _mDoc["peng"];
        cpgData.peng = peng.GetString();
    }
    if (_mDoc.HasMember("gang")){
        const rapidjson::Value &gang = _mDoc["gang"];
        GangData gangData;
        gangData.gang = gang.GetString();
        gangData.flag = 0;
        cpgData.playerGang.push_back(gangData);
    }
    if (_mDoc.HasMember("hu")){
        cpgData.hu = 1;
    }else{
        cpgData.hu = 0;
    }
    cpgRespData.playCpgt = cpgData;
    postNotifyMessage(MSG_PLAYER_CPG,&cpgRespData);
}


// {code:2009,poxiaoId:poxiaoId,seatId:seatId,result:1,ting:"1,2,3"}
void MsgHandler::heroChiResp(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    HeroCpgRespData cpgRespData;
    const rapidjson::Value &result = _mDoc["result"];
    PlayerCpgtData playerCpg;
    cpgRespData.result = result.GetInt();
    
    if (_mDoc.HasMember("forbit")){
        const rapidjson::Value &forbit = _mDoc["forbit"];
        cpgRespData.forbit = forbit.GetString();
    }
    if (_mDoc.HasMember("gang")){
        const rapidjson::Value &gang = _mDoc["gang"];
        GangData gangData;
        gangData.gang = gang.GetString();
        gangData.flag = 0;
        playerCpg.playerGang.push_back(gangData);
    }
    
    if (_mDoc.HasMember("ting1")){
        const rapidjson::Value &ting1 = _mDoc["ting1"];
        for(int i=0;i<ting1.Capacity();i++){
            HeroHuPaiData huPaiData;
            auto &temp = ting1[i];
            if(temp.HasMember("poker")){
                huPaiData.poker = temp["poker"].GetInt();
            }
            if(temp.HasMember("hu1")){
                const rapidjson::Value &data =  temp["hu1"];
                for (int i=0; i<data.Capacity(); i++) {
                    const rapidjson::Value &tem = data[i];
                    HuPokerData pd;
                    pd.poker = tem["hu"].GetString();
                    pd.num = tem["num"].GetString();
                    huPaiData.data.push_back(pd);
                }
            }
            playerCpg.heroHu.push_back(huPaiData);
        }
    }
    cpgRespData.playCpgt = playerCpg;
    postNotifyMessage(MSG_HERO_CHI_RESP, &cpgRespData);
}

//{code:2013,poxiaoId:poxiaoId,seatId:seatId,result:1}
void MsgHandler::heroPengResp(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    HeroCpgRespData cpgRespData;
    const rapidjson::Value &result = _mDoc["result"];
    cpgRespData.result = result.GetInt();
    PlayerCpgtData playerCpg;
    if (_mDoc.HasMember("poker")){
        const rapidjson::Value &poker = _mDoc["poker"];
        playerCpg.poker = poker.GetString();
    }
    if (_mDoc.HasMember("seatId")){
        const rapidjson::Value &seatId = _mDoc["seatId"];
        playerCpg.seatId = seatId.GetInt();
    }
    if (_mDoc.HasMember("peng")){
        const rapidjson::Value &pengPoker = _mDoc["peng"];
        playerCpg.peng = pengPoker.GetString();
    }
    if (_mDoc.HasMember("sId")){
        const rapidjson::Value &sId = _mDoc["sId"];
        playerCpg.sId = sId.GetInt();
    }
    
    
    if (_mDoc.HasMember("gang")){
        const rapidjson::Value &gang = _mDoc["gang"];
        GangData gangData;
        gangData.gang = gang.GetString();
        gangData.flag = 0;
        playerCpg.playerGang.push_back(gangData);
    }else{
        playerCpg.playerGang.clear();
    }
    if (_mDoc.HasMember("ting1")){
        const rapidjson::Value &ting1 = _mDoc["ting1"];
        for(int i=0;i<ting1.Capacity();i++){
            HeroHuPaiData huPaiData;
            auto &temp = ting1[i];
            if(temp.HasMember("poker")){
                huPaiData.poker = temp["poker"].GetInt();
            }
            if(temp.HasMember("hu1")){
                const rapidjson::Value &data =  temp["hu1"];
                for (int i=0; i<data.Capacity(); i++) {
                    const rapidjson::Value &tem = data[i];
                    HuPokerData pd;
                    pd.poker = tem["hu"].GetString();
                    pd.num = tem["num"].GetString();
                    huPaiData.data.push_back(pd);
                }
            }
            playerCpg.heroHu.push_back(huPaiData);
        }
    }
    cpgRespData.playCpgt = playerCpg;
    postNotifyMessage(MSG_HERO_PENG_RESP, &cpgRespData);
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
    PlayerCpgtData data;
    data.poker = poker.GetString();
    data.seatId = seatId.GetInt();
    data.peng = pengPoker.GetString();
    data.sId = sId.GetInt();
    postNotifyMessage(MSG_OTHER_PLAYER_PENG, &data);
}

//{code:2017,poxiaoId:poxiaoId,seatId:seatId,result:1}
void MsgHandler::heroGangResp(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    HeroCpgRespData cpgRespData;
    const rapidjson::Value &result = _mDoc["result"];
    cpgRespData.result = result.GetInt();
    PlayerCpgtData playerCpg;
    if (_mDoc.HasMember("gang")&&_mDoc.HasMember("flag")){
        const rapidjson::Value &gang = _mDoc["gang"];
        const rapidjson::Value &flag = _mDoc["flag"];
        GangData gangData;
        gangData.gang = gang.GetString();
        gangData.flag = atoi(flag.GetString());
        playerCpg.playerGang.push_back(gangData);
    }
    if (_mDoc.HasMember("sId")){
        const rapidjson::Value &sId = _mDoc["sId"];
        playerCpg.sId= sId.GetInt();
    }
    if (_mDoc.HasMember("poker")){
        const rapidjson::Value &poker = _mDoc["poker"];
        playerCpg.poker= atoi(poker.GetString());
    }
    cpgRespData.playCpgt = playerCpg;
    postNotifyMessage(MSG_HERO_GANG_RESP, &cpgRespData);
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
    PlayerCpgtData cpgData;
    cpgData.poker = poker.GetString();
    cpgData.seatId = seatId.GetInt();
    cpgData.sId = sId.GetInt();
    GangData gangData;
    gangData.gang = gang.GetString();
    gangData.flag = atoi(flag.GetString());
    cpgData.playerGang.push_back(gangData);
    postNotifyMessage(MSG_OTHER_PLAYER_GANG, &cpgData);
}


//{code:2019,poxiaoId:poxiaoId,seatId:seatId,poker:{poker:1,hua:32,33}}
void MsgHandler::nextPlayer(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    PlayerTurnData playerTurnData;
    playerTurnData.seatId = _mDoc["seatId"].GetInt();
    if (_mDoc.HasMember("poker")){
        const rapidjson::Value &poker = _mDoc["poker"];
        playerTurnData.poker = atoi(poker.GetString());
    }
    const rapidjson::Value &rest = _mDoc["rest"];
    playerTurnData.rest = rest.GetString();
    if (_mDoc.HasMember("num")){
        const rapidjson::Value &num = _mDoc["num"];
        playerTurnData.handNum = num.GetInt();
    }
    PlayerCpgtData tingData;
    tingData.seatId = _mDoc["seatId"].GetInt();
    if (_mDoc.HasMember("hu")){
        tingData.hu = 1;
    }else{
        tingData.hu = 0;
    }
    if (_mDoc.HasMember("angang")){
        const rapidjson::Value &angang = _mDoc["angang"];
        GangData gangData;
        gangData.gang = angang.GetString();
        gangData.flag = 1;
        tingData.playerGang.push_back(gangData);
        playerTurnData.hastinggang = true;
    }
    if (_mDoc.HasMember("penggang")){
        const rapidjson::Value &penggang = _mDoc["penggang"];
        GangData gangData;
        gangData.gang = penggang.GetString();
        gangData.flag = 2;
        tingData.playerGang.push_back(gangData);
        playerTurnData.hastinggang = true;
    }
    if (_mDoc.HasMember("ting1")){
        const rapidjson::Value &ting1 = _mDoc["ting1"];
        for(int i=0;i<ting1.Capacity();i++){
            HeroHuPaiData huPaiData;
            auto &temp = ting1[i];
            if(temp.HasMember("poker")){
                huPaiData.poker = temp["poker"].GetInt();
            }
            if(temp.HasMember("hu1")){
                const rapidjson::Value &data =  temp["hu1"];
                for (int i=0; i<data.Capacity(); i++) {
                    const rapidjson::Value &tem = data[i];
                    HuPokerData pd;
                    pd.poker = tem["hu"].GetString();
                    pd.num = tem["num"].GetString();
                    huPaiData.data.push_back(pd);
                }
            }
            tingData.heroHu.push_back(huPaiData);
        }
    }
    playerTurnData.cpgData = tingData;
    postNotifyMessage(MSG_PLAYER_TURN_WHO, &playerTurnData);
}

//{code:2023,poxiaoId:poxiaoId,seatId:seatId,result:1}
void MsgHandler::playerTingResp(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &result = _mDoc["result"];
    char* buf = const_cast<char*>(StringUtil::itos(result.GetInt()).c_str());
    postNotifyMessage(MSG_PLAYER_TING_RESP, buf);
}

//{code:2024,poxiaoId:poxiaoId,
//finish:[{result:1,hutype:1,2,3,seatId:1,nickname:"rr",gold:0,diamond:0,jifen:0,lequan:0,
//golddelta:0,diamonddelta:0,jifendelta:0,lequandelta:0},
//{result:1,hutype:1,2,3,seatId:1,nickname:"rr",gold:0,diamond:0,jifen:0,lequan:0,
//golddelta:0,diamonddelta:0,jifendelta:0,lequandelta:0}]}
void MsgHandler::gameResultNotify(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if(_mDoc.HasMember("matchid")){
        CompetitionResultInfo competitionData;
        competitionData.matchid = _mDoc["matchid"].GetString();
        competitionData.pride = _mDoc["prize"].GetString();
        competitionData.paiming = _mDoc["paiming"].GetString();
        GAMEDATA::getInstance()->setCompetitionResultData(competitionData);
    }
    if(_mDoc.HasMember("ifaa")){
        const rapidjson::Value &ifaa = _mDoc["ifaa"];
        GAMEDATA::getInstance()->setIsPayWayAA(strcmp(ifaa.GetString(), "1") == 0?true:false);
        UserData::getInstance()->setLatelyPayWayAA(strcmp(ifaa.GetString(), "1") == 0?true:false);
    }
    if(_mDoc.HasMember("poker")){
        GAMEDATA::getInstance()->setDiaopao(_mDoc["poker"].GetString());
    }else{
        GAMEDATA::getInstance()->setDiaopao("");
    }
    GameHongBaoPride pride;
    if(_mDoc.HasMember("dyj")){
        pride.dyj = _mDoc["dyj"].GetString();
    }else{
        pride.dyj = "-999";
    }
    if(_mDoc.HasMember("dyjfee")){
        pride.dyjfee = _mDoc["dyjfee"].GetString();
    }else{
        pride.dyjfee = "0";
    }
    
    if(_mDoc.HasMember("dsj")){
        pride.dsj = _mDoc["dsj"].GetString();
    }else{
        pride.dsj = "-999";
    }
    if(_mDoc.HasMember("dsjfee")){
        pride.dsjfee = _mDoc["dsjfee"].GetString();
    }else{
        pride.dsjfee = "0";
    }
    if(_mDoc.HasMember("fzfee")){
        pride.fzfee = _mDoc["fzfee"].GetString();
    }else{
        pride.fzfee = "0";
    }
    if(_mDoc.HasMember("sxlmfee")){
        pride.sxlmfee = _mDoc["sxlmfee"].GetString();
    }else{
        pride.sxlmfee = "0";
    }
    if(_mDoc.HasMember("fzId")){
        pride.fzid = _mDoc["fzId"].GetString();
        GAMEDATA::getInstance()->setFangZhuId(_mDoc["fzId"].GetString());
    }else{
        pride.fzid = "-999";
    }
    GAMEDATA::getInstance()->setGameHongBaoPride(pride);
    if(_mDoc.HasMember("diling")){
        const rapidjson::Value &diling = _mDoc["diling"];
        GAMEDATA::getInstance()->setPrivateDLNum(diling.GetString());
    }
    if(_mDoc.HasMember("huangfan")){
        const rapidjson::Value &huangfan = _mDoc["huangfan"];
        GAMEDATA::getInstance()->setPrivateHFNum(huangfan.GetString());
    }
    if(_mDoc.HasMember("hgdlb")){
        const rapidjson::Value &hgdlb = _mDoc["hgdlb"];
        GAMEDATA::getInstance()->setHuiGuiLiBao(hgdlb.GetString());
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
        if (temp.HasMember("tip")){
            resultData.tip = temp["tip"].GetString();
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
        if (temp.HasMember("zimocount")){
            resultData.zimocount = temp["zimocount"].GetString();
        }
        if (temp.HasMember("jiepaocount")){
            resultData.jiepaocount = temp["jiepaocount"].GetString();
        }
        if (temp.HasMember("dianpaocount")){
            resultData.dianpaocount = temp["dianpaocount"].GetString();
        }
        if (temp.HasMember("angangcount")){
            resultData.angangcount = temp["angangcount"].GetString();
        }
        if (temp.HasMember("minggangcount")){
            resultData.minggangcount = temp["minggangcount"].GetString();
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
    char* buf = const_cast<char*>(flag.GetString());
    postNotifyMessage(MSG_GAME_RESULT, buf);
}

//{code:2025,poxiaoId:poxiaoId,seatId:seatId}
void MsgHandler::playerTingNotify(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &seatId = _mDoc["seatId"];
    std::string seat = StringUtils::format("%d",seatId.GetInt());
    char* buf = const_cast<char*>(seat.c_str());
    postNotifyMessage(MSG_PLAYER_TING_NOTIFY, buf);
}

// 退出游戏回复{code:2027,poxiaoId:poxiaoId,seatId:seatId,result:1}
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


//{code:2031,poxiaoId:poxiaoId,seatId:1,lord:1,rest:"123",status:1,all:[{seatId:1,hua:"1",chi:[{chi:"1,2,3",poker:"3"},{chi:"11,12,13",poker:"13"}],peng:[{peng:"11",peId:"1"},{peng:"12",peId:"2"}],gang:[{gang:"11",gaId:"1"},{gang:"12",gaId:"2"}],angang:"6",out:"11,22,33,44",gold:0,diamond:0,jifen:0,lequan:0,gender:0,nickname:'aaa',hand:"2",status:1}]} status1为听牌
void MsgHandler::playerConnectAgain(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if(_mDoc.HasMember("poxiaoId")){
        const rapidjson::Value &poxiaoId = _mDoc["poxiaoId"];
        UserData::getInstance()->setPoxiaoId(poxiaoId.GetString());
    }
    if(_mDoc.HasMember("ifaa")){
        const rapidjson::Value &ifaa = _mDoc["ifaa"];
        GAMEDATA::getInstance()->setIsPayWayAA(strcmp(ifaa.GetString(), "1") == 0?true:false);
        UserData::getInstance()->setLatelyPayWayAA(strcmp(ifaa.GetString(), "1") == 0?true:false);
    }
    if(_mDoc.HasMember("size")){
        const rapidjson::Value &size = _mDoc["size"];
        GAMEDATA::getInstance()->setMyGameModel(atoi(size.GetString()));
    }
    if(_mDoc.HasMember("prize")){
        GAMEDATA::getInstance()->setCompetitionPride(_mDoc["prize"].GetString());
    }
    if(_mDoc.HasMember("umark")){
        const rapidjson::Value &umark = _mDoc["umark"];
        UserData::getInstance()->setMarkId(umark.GetString());
    }
    if(_mDoc.HasMember("dice")){
        const rapidjson::Value &dice = _mDoc["dice"];
        GAMEDATA::getInstance()->setMahjongDice(dice.GetString());
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
    if(_mDoc.HasMember("diling")){
        const rapidjson::Value &diling = _mDoc["diling"];
        GAMEDATA::getInstance()->setPrivateDLNum(diling.GetString());
    }
    if(_mDoc.HasMember("huangfan")){
        const rapidjson::Value &huangfan = _mDoc["huangfan"];
        GAMEDATA::getInstance()->setPrivateHFNum(huangfan.GetString());
    }
    if(_mDoc.HasMember("fzId")){
        const rapidjson::Value &fzId = _mDoc["fzId"];
        GAMEDATA::getInstance()->setFangZhuId(fzId.GetString());
    }
    if(_mDoc.HasMember("prjucount")){
        const rapidjson::Value &prjucount = _mDoc["prjucount"];
        opdata.prjucount = prjucount.GetString();
    }
    if(_mDoc.HasMember("ifdiling")){
        GAMEDATA::getInstance()->setPrivateDiLing(_mDoc["ifdiling"].GetString());
        UserData::getInstance()->setLatelySZDiLing(_mDoc["ifdiling"].GetString());
    }
    if(_mDoc.HasMember("ifhaoqi")){
        GAMEDATA::getInstance()->setPrivateHaoQi(_mDoc["ifhaoqi"].GetString());
        UserData::getInstance()->setLatelySZHaoQi(_mDoc["ifhaoqi"].GetString());
    }
    if(_mDoc.HasMember("baozi")){
        GAMEDATA::getInstance()->setPrivateBaoZi(_mDoc["baozi"].GetString());
    }
    GAMEDATA::getInstance()->setFriendOpenRoomResp(opdata);
    const rapidjson::Value &seatId = _mDoc["seatId"];
    const rapidjson::Value &rest = _mDoc["rest"];
    const rapidjson::Value &loard = _mDoc["lord"];
    const rapidjson::Value &isprivate = _mDoc["isprivate"];
    const rapidjson::Value &turn = _mDoc["turn"];
    if(_mDoc.HasMember("s")){
        GAMEDATA::getInstance()->setTurnHeroCpg(true);
    }
    GAMEDATA::getInstance()->setHeroSeatId(seatId.GetInt());
    //设置是否是私人房间
    std::string roomType = isprivate.GetString();
    GAMEDATA::getInstance()->setMahjongRoomType(roomType == "1" ? (MahjongRoom::privateRoom):(MahjongRoom::publicRoom));
    LastGameData lastGameData;
    lastGameData.result = 1;//游戏中
    lastGameData.seatId = seatId.GetInt();
    lastGameData.rest = rest.GetString();
    lastGameData.loard = loard.GetInt();
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
        data.hua = temp["hua"].GetString();
        data.tru = temp["tru"].GetInt();
        data.ifready = 1;
        data.isOnline = temp["isonline"].GetInt();
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
    GAMEDATA::getInstance()->setGameType(1);
    GAMEDATA::getInstance()->setLastGameDataBackup(lastGameData);
    char* buf = const_cast<char*>(StringUtil::itos(seatId.GetInt()).c_str());
    postNotifyMessage(MSG_PLAYER_CONNECT_AGAIN, buf);
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
    postNotifyMessage(MSG_FRIEND_OPEN_ROOM_NOTIFY, nullptr);
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
    if(_mDoc.HasMember("ifaa")){
        const rapidjson::Value &ifaa = _mDoc["ifaa"];
        GAMEDATA::getInstance()->setIsPayWayAA(strcmp(ifaa.GetString(), "1") == 0?true:false);
        UserData::getInstance()->setLatelyPayWayAA(strcmp(ifaa.GetString(), "1") == 0?true:false);
    }
    if(_mDoc.HasMember("umark")){
        const rapidjson::Value &umark = _mDoc["umark"];
        UserData::getInstance()->setMarkId(umark.GetString());
    }
    if(_mDoc.HasMember("ifdiling")){
        GAMEDATA::getInstance()->setPrivateDiLing(_mDoc["ifdiling"].GetString());
        UserData::getInstance()->setLatelySZDiLing(_mDoc["ifdiling"].GetString());
    }
    if(_mDoc.HasMember("ifhaoqi")){
        GAMEDATA::getInstance()->setPrivateHaoQi(_mDoc["ifhaoqi"].GetString());
        UserData::getInstance()->setLatelySZHaoQi(_mDoc["ifhaoqi"].GetString());
    }
    if(_mDoc.HasMember("baozi")){
        GAMEDATA::getInstance()->setPrivateBaoZi(_mDoc["baozi"].GetString());
    }
    if(_mDoc.HasMember("baozi")){
        GAMEDATA::getInstance()->setPrivateBaoZi(_mDoc["baozi"].GetString());
    }
    if(_mDoc.HasMember("diling")){
        const rapidjson::Value &diling = _mDoc["diling"];
        GAMEDATA::getInstance()->setPrivateDLNum(diling.GetString());
    }
    if(_mDoc.HasMember("huangfan")){
        const rapidjson::Value &huangfan = _mDoc["huangfan"];
        GAMEDATA::getInstance()->setPrivateHFNum(huangfan.GetString());
    }
    FriendOpenRoomRespData data;
    if(_mDoc.HasMember("dkf")){
        data.agency = true;
        AgencyRoomList roomList;
        const rapidjson::Value &agency = _mDoc["dkf"];
        for (int i=0; i<agency.Capacity(); i++){
            const rapidjson::Value &temp = agency[i];
            AgencyRoomData data;
            data.roomid = temp["prid"].GetString();
            data.gameInfo = temp["desc"].GetString();
            data.playername = temp["user"].GetString();
            data.createtime = temp["time"].GetString();
            data.type = temp["type"].GetString();
            if(temp.HasMember("rs"))
                data.rs = temp["rs"].GetString();
            if(temp.HasMember("js"))
                data.js = temp["js"].GetString();
            roomList.roomlist.push_back(data);
        }
        GAMEDATA::getInstance()->setAgencyRoomList(roomList);
    }else{
        data.agency = false;
    }
    if(_mDoc.HasMember("prjushu")){
        const rapidjson::Value &prjushu = _mDoc["prjushu"];
        data.prjushu = prjushu.GetString();
        UserData::getInstance()->setLatelyGameJuShu(prjushu.GetString());
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
    if(_mDoc.HasMember("size")){
        const rapidjson::Value &size = _mDoc["size"];
        GAMEDATA::getInstance()->setMyGameModel(atoi(size.GetString()));
    }
    
    PayPointInfo pointInfo;
    if(_mDoc.HasMember("point")){
        const rapidjson::Value &point = _mDoc["point"];
        pointInfo.point = point.GetString();
    }
    if(_mDoc.HasMember("wxfee")){
        const rapidjson::Value &fee = _mDoc["wxfee"];
        pointInfo.fee = fee.GetString();
    }
    if(_mDoc.HasMember("wxfangka")){
        const rapidjson::Value &fangka = _mDoc["wxfangka"];
        pointInfo.fangka = fangka.GetString();
    }
    if(_mDoc.HasMember("applefangka")){
        const rapidjson::Value &applefangka = _mDoc["applefangka"];
        pointInfo.applefangka = applefangka.GetString();
    }
    if(_mDoc.HasMember("applefee")){
        const rapidjson::Value &applefee = _mDoc["applefee"];
        pointInfo.applefee = applefee.GetString();
    }
    GAMEDATA::getInstance()->setPayPointInfo(pointInfo);
    
    const rapidjson::Value &result = _mDoc["result"];
    data.result = result.GetInt();
    GAMEDATA::getInstance()->clearPlayersInfo();
    GAMEDATA::getInstance()->setFriendOpenRoomResp(data);
    if (_mDoc.HasMember("other")){
        const rapidjson::Value &pArr = _mDoc["other"];
        for (int i = 0; i < pArr.Capacity(); ++i){
            const rapidjson::Value &temp = pArr[i];
            PlayerInfo* info = new PlayerInfo();
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
    PlayerInfo* info = new PlayerInfo();
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
    GAMEDATA::getInstance()->setGameType(1);
    UserData::getInstance()->setLatelyMahjongType(GameMahjongType::SuZhou);
    postNotifyMessage(MSG_FRIEND_OPEN_ROOM_RESP, nullptr);
}

// code:2040
void MsgHandler::friendEnterRoomResp(std::string msg){
    
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if(_mDoc.HasMember("poxiaoId")){
        const rapidjson::Value &poxiaoId = _mDoc["poxiaoId"];
        UserData::getInstance()->setPoxiaoId(poxiaoId.GetString());
    }
    if(_mDoc.HasMember("ifaa")){
        const rapidjson::Value &ifaa = _mDoc["ifaa"];
        GAMEDATA::getInstance()->setIsPayWayAA(strcmp(ifaa.GetString(), "1") == 0?true:false);
        UserData::getInstance()->setLatelyPayWayAA(strcmp(ifaa.GetString(), "1") == 0?true:false);
    }
    if(_mDoc.HasMember("size")){
        const rapidjson::Value &size = _mDoc["size"];
        GAMEDATA::getInstance()->setMyGameModel(atoi(size.GetString()));
        
    }
    if(_mDoc.HasMember("ifdiling")){
        GAMEDATA::getInstance()->setPrivateDiLing(_mDoc["ifdiling"].GetString());
        UserData::getInstance()->setLatelySZDiLing(_mDoc["ifdiling"].GetString());
    }
    if(_mDoc.HasMember("ifhaoqi")){
        GAMEDATA::getInstance()->setPrivateHaoQi(_mDoc["ifhaoqi"].GetString());
        UserData::getInstance()->setLatelySZHaoQi(_mDoc["ifhaoqi"].GetString());
    }
    if(_mDoc.HasMember("baozi")){
        GAMEDATA::getInstance()->setPrivateBaoZi(_mDoc["baozi"].GetString());
    }
    if(_mDoc.HasMember("diling")){
        const rapidjson::Value &diling = _mDoc["diling"];
        GAMEDATA::getInstance()->setPrivateDLNum(_mDoc["diling"].GetString());
    }
    if(_mDoc.HasMember("huangfan")){
        const rapidjson::Value &huangfan = _mDoc["huangfan"];
        GAMEDATA::getInstance()->setPrivateHFNum(_mDoc["huangfan"].GetString());
    }
    PayPointInfo pointInfo;
    if(_mDoc.HasMember("point")){
        const rapidjson::Value &point = _mDoc["point"];
        pointInfo.point = point.GetString();
    }
    if(_mDoc.HasMember("wxfee")){
        const rapidjson::Value &fee = _mDoc["wxfee"];
        pointInfo.fee = fee.GetString();
    }
    if(_mDoc.HasMember("wxfangka")){
        const rapidjson::Value &fangka = _mDoc["wxfangka"];
        pointInfo.fangka = fangka.GetString();
    }
    if(_mDoc.HasMember("applefangka")){
        const rapidjson::Value &applefangka = _mDoc["applefangka"];
        pointInfo.applefangka = applefangka.GetString();
    }
    if(_mDoc.HasMember("applefee")){
        const rapidjson::Value &applefee = _mDoc["applefee"];
        pointInfo.applefee = applefee.GetString();
    }
    GAMEDATA::getInstance()->setPayPointInfo(pointInfo);
    FriendOpenRoomRespData data = GAMEDATA::getInstance()->getFriendOpenRoomResp();
    const rapidjson::Value &result = _mDoc["result"];
    data.result = result.GetInt();
    
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
        UserData::getInstance()->setLatelyGameJuShu(prjushu.GetString());
    }
    if(_mDoc.HasMember("prjucount")){
        const rapidjson::Value &prjucount = _mDoc["prjucount"];
        data.prjucount = StringUtils::format("%d",atoi(prjucount.GetString())+1);
    }
    if(_mDoc.HasMember("jifen")){
        const rapidjson::Value &myjifen = _mDoc["jifen"];
        GAMEDATA::getInstance()->setScore(myjifen.GetInt());
    }
    if(_mDoc.HasMember("prize")){
        GAMEDATA::getInstance()->setCompetitionPride(_mDoc["prize"].GetString());
    }
    
    GAMEDATA::getInstance()->clearPlayersInfo();
    GAMEDATA::getInstance()->setFriendOpenRoomResp(data);
    
    if (_mDoc.HasMember("other")){
        const rapidjson::Value &pArr = _mDoc["other"];
        for (int i = 0; i < pArr.Capacity(); ++i){
            const rapidjson::Value &temp = pArr[i];
            PlayerInfo* info = new PlayerInfo();
            info->setScore(temp["jifen"].GetInt());
            info->setSeatId(temp["seatId"].GetInt());
            info->setPoxiaoId(temp["poxiaoId"].GetString());
            info->setBanker(false);
            info->setIsReady(temp["ifready"].GetInt() == 0 ? false : true);
            info->setGold(temp["gold"].GetInt());
            info->setTicket(temp["lequan"].GetInt());
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
    PlayerInfo* info = new PlayerInfo();
    info->setScore(GAMEDATA::getInstance()->getScore());
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
    GAMEDATA::getInstance()->addPlayersInfo(info);
    GAMEDATA::getInstance()->setIsPlaying(false);
    GAMEDATA::getInstance()->setGameType(1);
    UserData::getInstance()->setLatelyMahjongType(GameMahjongType::SuZhou);
    postNotifyMessage(MSG_ENTER_FRIEND_ROOM_RESP, nullptr);
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
            data.gameType = temp["t"].GetString();
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
    postNotifyMessage(MSG_PLAYER_BILL, nullptr);
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
    postNotifyMessage(MSG_PLAYER_BILL_DETAIL, nullptr);
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
    postNotifyMessage(FRIEND_IS_PLAYING_GAME, nullptr);
}

// 私人房间可以解散通知{code:2047,poxiaoId:"123"}
void MsgHandler::hanleFangzhuDismissRoom(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    GAMEDATA::getInstance()->setShowFangZhuDismiss(true);
}



// 私人房间是否同意解散通知{code:2049,poxiaoId:"123"}
void MsgHandler::handleDissovleRoomNotify(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if(_mDoc.HasMember("nickName")){
        const rapidjson::Value &nickName = _mDoc["nickName"];
        std::string name = nickName.GetString();
        GAMEDATA::getInstance()->setDissolveName(name);
        postNotifyMessage(MSG_DISSOVLE_ROOM_SELECTED_NOTIFY_NEW, nullptr);
    }
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
    postNotifyMessage(MSG_DISSOVLE_ROOM_SELECTED_NOTIFY, nullptr);
}

//开房进房前回复{code:2054,poxiaoId:poxiaoId}
void MsgHandler::openRoomEnquireResp(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if(_mDoc.HasMember("le")){
        auto &lequan = _mDoc["le"];
        GAMEDATA::getInstance()->setFangzhuLequan(lequan.GetString());
    }
    //    4f  8f  16f
    if(_mDoc.HasMember("4f")){
        auto &f4 = _mDoc["4f"];
        GAMEDATA::getInstance()->setKaiFangXiaoHao4(f4.GetString());
    }
    if(_mDoc.HasMember("8f")){
        auto &f8 = _mDoc["8f"];
        GAMEDATA::getInstance()->setKaiFangXiaoHao8(f8.GetString());
    }
    if(_mDoc.HasMember("16f")){
        auto &f16 = _mDoc["16f"];
        GAMEDATA::getInstance()->setKaiFangXiaoHao16(f16.GetString());
    }
    postNotifyMessage(MSG_LOBBY_ASK_OPEN_ROOM, nullptr);
}

//开房进房前回复{code:2056,poxiaoId:poxiaoId}
void MsgHandler::enterRoomEnquireResp(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    postNotifyMessage(MSG_LOBBY_ASK_ENTER_ROOM, nullptr);
}


//开房进房前回复{code:2057,poxiaoId:poxiaoId,seatId:1}
void MsgHandler::fangZhuLeaveRoom(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if(_mDoc.HasMember("seatId")){
        const rapidjson::Value &result = _mDoc["seatId"];
        char* buf = const_cast<char*>(StringUtils::format("%d",result.GetInt()).c_str());
        postNotifyMessage(MSG_GAME_FANG_ZHU_LEAVE,buf);
    }
}

//复盘玩家数据
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
    if(_mDoc.HasMember("size")){
        const rapidjson::Value &who = _mDoc["size"];
        if(strcmp(who.GetString(), "2") == 0){
            GAMEDATA::getInstance()->setMyGameModel(GameModel::TWOPLAYER);
        }else{
            GAMEDATA::getInstance()->setMyGameModel(GameModel::FOURPLAYER);
        }
    }
    if(_mDoc.HasMember("t")){
        const rapidjson::Value &temp = _mDoc["t"];
        info.gameType =temp.GetString();
    }
    GAMEDATA::getInstance()->setPlaybackInfo(info);
    postNotifyMessage(MSG_GAME_FU_PAN_NOTIFY, NULL);
}

//复盘发牌
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
    if(_mDoc.HasMember("fanma")){
        GAMEDATA::getInstance()->setFanMaType(_mDoc["fanma"].GetString());
    }
    
    if(_mDoc.HasMember("difen")){
        GAMEDATA::getInstance()->setHZDiFen(_mDoc["difen"].GetString());
    }
    
    if(_mDoc.HasMember("fanpai")){
        auto fan = _mDoc["fanpai"].GetString();
        GAMEDATA::getInstance()->setFanPaiPoker(fan);
    }
    if(_mDoc.HasMember("baida")){
        auto baida = _mDoc["baida"].GetString();
        GAMEDATA::getInstance()->setBaiDaPoker(baida);
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
        if(temp.HasMember("hua")){
            data.hua = temp["hua"].GetString();
        }
        data.status = 2;
        data.ifready = 0;
        data.hand = temp["poker"].GetString();
        fupan.players.push_back(data);
    }
    GAMEDATA::getInstance()->setFupanGameData(fupan);
    postNotifyMessage(MSG_GAME_FU_PAN_PLAYER_NOTIFY, nullptr);
}

void MsgHandler::handleHongZhongEnterRoom(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if(_mDoc.HasMember("poxiaoId")){
        const rapidjson::Value &poxiaoId = _mDoc["poxiaoId"];
        UserData::getInstance()->setPoxiaoId(poxiaoId.GetString());
    }
    if(_mDoc.HasMember("ifaa")){
        const rapidjson::Value &ifaa = _mDoc["ifaa"];
        GAMEDATA::getInstance()->setIsPayWayAA(strcmp(ifaa.GetString(), "1") == 0?true:false);
        UserData::getInstance()->setLatelyPayWayAA(strcmp(ifaa.GetString(), "1") == 0?true:false);
    }
    if(_mDoc.HasMember("umark")){
        const rapidjson::Value &umark = _mDoc["umark"];
        UserData::getInstance()->setMarkId(umark.GetString());
    }
    if(_mDoc.HasMember("size")){
        const rapidjson::Value &size = _mDoc["size"];
        GAMEDATA::getInstance()->setMyGameModel(atoi(size.GetString()));
        
    }
    
    if(_mDoc.HasMember("fanma")){
        GAMEDATA::getInstance()->setFanMaType(_mDoc["fanma"].GetString());
        UserData::getInstance()->setLatelyHZFanMa(_mDoc["fanma"].GetString());
    }
    
    if(_mDoc.HasMember("difen")){
        GAMEDATA::getInstance()->setHZDiFen(_mDoc["difen"].GetString());
        UserData::getInstance()->setLatelyHZDi(_mDoc["difen"].GetString());
    }
    
    FriendOpenRoomRespData data;
    if(_mDoc.HasMember("dkf")){
        data.agency = true;
        AgencyRoomList roomList;
        const rapidjson::Value &agency = _mDoc["dkf"];
        for (int i=0; i<agency.Capacity(); i++){
            const rapidjson::Value &temp = agency[i];
            AgencyRoomData data;
            data.roomid = temp["prid"].GetString();
            data.gameInfo = temp["desc"].GetString();
            data.playername = temp["user"].GetString();
            data.createtime = temp["time"].GetString();
            data.type = temp["type"].GetString();
            if(temp.HasMember("rs"))
                data.rs = temp["rs"].GetString();
            if(temp.HasMember("js"))
                data.js = temp["js"].GetString();
            roomList.roomlist.push_back(data);
        }
        GAMEDATA::getInstance()->setAgencyRoomList(roomList);
    }else{
        data.agency = false;
    }
    if(_mDoc.HasMember("prjushu")){
        const rapidjson::Value &prjushu = _mDoc["prjushu"];
        data.prjushu = prjushu.GetString();
        UserData::getInstance()->setLatelyGameJuShu(prjushu.GetString());
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
    
    PayPointInfo pointInfo;
    if(_mDoc.HasMember("point")){
        const rapidjson::Value &point = _mDoc["point"];
        pointInfo.point = point.GetString();
    }
    if(_mDoc.HasMember("wxfee")){
        const rapidjson::Value &fee = _mDoc["wxfee"];
        pointInfo.fee = fee.GetString();
    }
    if(_mDoc.HasMember("wxfangka")){
        const rapidjson::Value &fangka = _mDoc["wxfangka"];
        pointInfo.fangka = fangka.GetString();
    }
    if(_mDoc.HasMember("applefangka")){
        const rapidjson::Value &applefangka = _mDoc["applefangka"];
        pointInfo.applefangka = applefangka.GetString();
    }
    if(_mDoc.HasMember("applefee")){
        const rapidjson::Value &applefee = _mDoc["applefee"];
        pointInfo.applefee = applefee.GetString();
    }
    GAMEDATA::getInstance()->setPayPointInfo(pointInfo);
    
    const rapidjson::Value &result = _mDoc["result"];
    data.result = result.GetInt();
    GAMEDATA::getInstance()->clearPlayersInfo();
    GAMEDATA::getInstance()->setFriendOpenRoomResp(data);
    if (_mDoc.HasMember("other")){
        const rapidjson::Value &pArr = _mDoc["other"];
        for (int i = 0; i < pArr.Capacity(); ++i){
            const rapidjson::Value &temp = pArr[i];
            PlayerInfo* info = new PlayerInfo();
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
    GAMEDATA::getInstance()->setGameType(3);
    PlayerInfo* info = new PlayerInfo();
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
    UserData::getInstance()->setLatelyMahjongType(GameMahjongType::HongZhong);
    postNotifyMessage(MSG_ENTER_FRIEND_ROOM_HONGZHONG_RESP, nullptr);
}


void MsgHandler::handleHZEnterRoomResp(std::string msg){
    
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if(_mDoc.HasMember("poxiaoId")){
        const rapidjson::Value &poxiaoId = _mDoc["poxiaoId"];
        UserData::getInstance()->setPoxiaoId(poxiaoId.GetString());
    }
    if(_mDoc.HasMember("ifaa")){
        const rapidjson::Value &ifaa = _mDoc["ifaa"];
        GAMEDATA::getInstance()->setIsPayWayAA(strcmp(ifaa.GetString(), "1") == 0?true:false);
        UserData::getInstance()->setLatelyPayWayAA(strcmp(ifaa.GetString(), "1") == 0?true:false);
    }
    if(_mDoc.HasMember("fanma")){
        GAMEDATA::getInstance()->setFanMaType(_mDoc["fanma"].GetString());
        UserData::getInstance()->setLatelyHZFanMa(_mDoc["fanma"].GetString());
    }
    if(_mDoc.HasMember("size")){
        const rapidjson::Value &size = _mDoc["size"];
        GAMEDATA::getInstance()->setMyGameModel(atoi(size.GetString()));
        
    }
    
    if(_mDoc.HasMember("difen")){
        GAMEDATA::getInstance()->setHZDiFen(_mDoc["difen"].GetString());
        UserData::getInstance()->setLatelyHZDi(_mDoc["difen"].GetString());
    }
    if(_mDoc.HasMember("seatId")){
        const rapidjson::Value &seatId = _mDoc["seatId"];
        GAMEDATA::getInstance()->setHeroSeatId(seatId.GetInt());
    }
    
    PayPointInfo pointInfo;
    if(_mDoc.HasMember("point")){
        const rapidjson::Value &point = _mDoc["point"];
        pointInfo.point = point.GetString();
    }
    if(_mDoc.HasMember("wxfee")){
        const rapidjson::Value &fee = _mDoc["wxfee"];
        pointInfo.fee = fee.GetString();
    }
    if(_mDoc.HasMember("wxfangka")){
        const rapidjson::Value &fangka = _mDoc["wxfangka"];
        pointInfo.fangka = fangka.GetString();
    }
    if(_mDoc.HasMember("applefangka")){
        const rapidjson::Value &applefangka = _mDoc["applefangka"];
        pointInfo.applefangka = applefangka.GetString();
    }
    if(_mDoc.HasMember("applefee")){
        const rapidjson::Value &applefee = _mDoc["applefee"];
        pointInfo.applefee = applefee.GetString();
    }
    GAMEDATA::getInstance()->setPayPointInfo(pointInfo);
    FriendOpenRoomRespData data = GAMEDATA::getInstance()->getFriendOpenRoomResp();
    const rapidjson::Value &result = _mDoc["result"];
    data.result = result.GetInt();
    
    if (_mDoc.HasMember("prId")){
        const rapidjson::Value &prid = _mDoc["prId"];
        data.prid =prid.GetString();
    }
    if (_mDoc.HasMember("prjushu")){
        const rapidjson::Value &prjushu = _mDoc["prjushu"];
        data.prjushu = prjushu.GetString();
        UserData::getInstance()->setLatelyGameJuShu(prjushu.GetString());
    }
    if(_mDoc.HasMember("prjucount")){
        const rapidjson::Value &prjucount = _mDoc["prjucount"];
        data.prjucount = StringUtils::format("%d",atoi(prjucount.GetString())+1);
    }
    if(_mDoc.HasMember("jifen")){
        const rapidjson::Value &myjifen = _mDoc["jifen"];
        GAMEDATA::getInstance()->setScore(myjifen.GetInt());
    }
    if(_mDoc.HasMember("prize")){
        GAMEDATA::getInstance()->setCompetitionPride(_mDoc["prize"].GetString());
    }
    GAMEDATA::getInstance()->clearPlayersInfo();
    GAMEDATA::getInstance()->setFriendOpenRoomResp(data);
    
    if (_mDoc.HasMember("other")){
        const rapidjson::Value &pArr = _mDoc["other"];
        for (int i = 0; i < pArr.Capacity(); ++i){
            const rapidjson::Value &temp = pArr[i];
            PlayerInfo* info = new PlayerInfo();
            info->setScore(temp["jifen"].GetInt());
            info->setSeatId(temp["seatId"].GetInt());
            info->setPoxiaoId(temp["poxiaoId"].GetString());
            info->setBanker(false);
            info->setIsReady(temp["ifready"].GetInt() == 0 ? false : true);
            info->setGold(temp["gold"].GetInt());
            info->setTicket(temp["lequan"].GetInt());
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
    PlayerInfo* info = new PlayerInfo();
    info->setScore(GAMEDATA::getInstance()->getScore());
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
    GAMEDATA::getInstance()->addPlayersInfo(info);
    GAMEDATA::getInstance()->setGameType(3);
    GAMEDATA::getInstance()->setIsPlaying(false);
    UserData::getInstance()->setLatelyMahjongType(GameMahjongType::HongZhong);
    postNotifyMessage(MSG_HZ_ENTER_FRIEND_ROOM_RESP, nullptr);
    
}

void MsgHandler::handleHZReadyNoyify(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &seatId = _mDoc["seatId"];
    vector<PlayerInfo*> players = GAMEDATA::getInstance()->getPlayersInfo();
    for (int i = 0; i < players.size(); i++){
        if(players.at(i)->getSeatId() == seatId.GetInt() ){
            players.at(i)->setIsReady(true);
        }
    }
    char* buf = const_cast<char*>(StringUtil::itos(seatId.GetInt()).c_str());
    postNotifyMessage(MSG_READY_NOTIFY, buf);
}


void MsgHandler::handleHZFaPaiNotify(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if(_mDoc.HasMember("seatId")){
        GAMEDATA::getInstance()->setHeroSeatId(atoi(_mDoc["seatId"].GetString()));
    }
    MahjongFaPaiData faPaiData;
    faPaiData.heroPokers = _mDoc["poker"].GetString();
    faPaiData.dice = _mDoc["dice"].GetString();
    faPaiData.start = _mDoc["start"].GetInt();
    if(_mDoc.HasMember("prjucount")){
        faPaiData.prjucount = _mDoc["prjucount"].GetInt();
    }
    const rapidjson::Value &rest = _mDoc["rest"];
    faPaiData.rest = rest.GetString();
    PlayerCpgtData tingData;
    if(_mDoc.HasMember("angang")){
        faPaiData.hasGang = true;
        const rapidjson::Value &angang = _mDoc["angang"];
        GangData gangData;
        gangData.gang = angang.GetString();
        gangData.flag = 1;
        tingData.playerGang.push_back(gangData);
        tingData.seatId = GAMEDATA::getInstance()->getHeroSeatId();
    }
    if(_mDoc.HasMember("hu")){
        tingData.hu = 1;
    }else{
        tingData.hu = 0;
    }
    faPaiData.mjHuData = tingData;
    GAMEDATA::getInstance()->setIsTrusteeship(false);
    GAMEDATA::getInstance()->setMahjongFaPaiData(faPaiData);
    postNotifyMessage(MSG_HZ_GAME_START_FAPAI_NOTIFY, &faPaiData);
}


void MsgHandler::handleHZDispatchPokerNotify(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    PlayerTurnData playerTurnData;
    playerTurnData.seatId = _mDoc["seatId"].GetInt();
    if (_mDoc.HasMember("poker")){
        const rapidjson::Value &poker = _mDoc["poker"];
        const rapidjson::Value &pokerId = poker["poker"];
        playerTurnData.poker = pokerId.GetInt();
    }
    const rapidjson::Value &rest = _mDoc["rest"];
    playerTurnData.rest = rest.GetString();
    if (_mDoc.HasMember("num")){
        const rapidjson::Value &num = _mDoc["num"];
        playerTurnData.handNum = num.GetInt();
    }
    PlayerCpgtData tingData;
    tingData.seatId = _mDoc["seatId"].GetInt();
    if (_mDoc.HasMember("angang")){
        const rapidjson::Value &angang = _mDoc["angang"];
        GangData gangData;
        gangData.gang = angang.GetString();
        gangData.flag = 1;
        tingData.playerGang.push_back(gangData);
    }
    if (_mDoc.HasMember("penggang")){
        const rapidjson::Value &penggang = _mDoc["penggang"];
        GangData gangData;
        gangData.gang = penggang.GetString();
        gangData.flag = 2;
        tingData.playerGang.push_back(gangData);
    }
    if(_mDoc.HasMember("hu")){
        tingData.hu = 1;//红中麻将可胡
    }else{
        tingData.hu = 0;
    }
    if (_mDoc.HasMember("ting") || _mDoc.HasMember("angang") || _mDoc.HasMember("penggang")||_mDoc.HasMember("hu")){
        playerTurnData.hastinggang = true;
    }
    if (_mDoc.HasMember("ting1")){
        const rapidjson::Value &ting1 = _mDoc["ting1"];
        for(int i=0;i<ting1.Capacity();i++){
            HeroHuPaiData huPaiData;
            auto &temp = ting1[i];
            if(temp.HasMember("poker")){
                huPaiData.poker = temp["poker"].GetInt();
            }
            if(temp.HasMember("hu1")){
                const rapidjson::Value &data =  temp["hu1"];
                for (int i=0; i<data.Capacity(); i++) {
                    const rapidjson::Value &tem = data[i];
                    HuPokerData pd;
                    pd.poker = tem["hu"].GetString();
                    pd.num = tem["num"].GetString();
                    huPaiData.data.push_back(pd);
                }
            }
            tingData.heroHu.push_back(huPaiData);
        }
    }
    playerTurnData.cpgData = tingData;
    postNotifyMessage(MSG_HZ_PLAYER_TURN_WHO, &playerTurnData);
}

void MsgHandler::handleHZGameReconnectNotify(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if(_mDoc.HasMember("poxiaoId")){
        const rapidjson::Value &poxiaoId = _mDoc["poxiaoId"];
        UserData::getInstance()->setPoxiaoId(poxiaoId.GetString());
    }
    if(_mDoc.HasMember("ifaa")){
        const rapidjson::Value &ifaa = _mDoc["ifaa"];
        GAMEDATA::getInstance()->setIsPayWayAA(strcmp(ifaa.GetString(), "1") == 0?true:false);
        UserData::getInstance()->setLatelyPayWayAA(strcmp(ifaa.GetString(), "1") == 0?true:false);
    }
    if(_mDoc.HasMember("umark")){
        const rapidjson::Value &umark = _mDoc["umark"];
        UserData::getInstance()->setMarkId(umark.GetString());
    }
    if(_mDoc.HasMember("prize")){
        GAMEDATA::getInstance()->setCompetitionPride(_mDoc["prize"].GetString());
    }
    if(_mDoc.HasMember("size")){
        const rapidjson::Value &size = _mDoc["size"];
        GAMEDATA::getInstance()->setMyGameModel(atoi(size.GetString()));
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
    if(_mDoc.HasMember("dice")){
        const rapidjson::Value &dice = _mDoc["dice"];
        GAMEDATA::getInstance()->setMahjongDice(dice.GetString());
    }
    if(_mDoc.HasMember("prjucount")){
        const rapidjson::Value &prjucount = _mDoc["prjucount"];
        opdata.prjucount = prjucount.GetString();
    }
    if(_mDoc.HasMember("fanma")){
        GAMEDATA::getInstance()->setFanMaType(_mDoc["fanma"].GetString());
    }
    
    if(_mDoc.HasMember("difen")){
        GAMEDATA::getInstance()->setHZDiFen(_mDoc["difen"].GetString());
    }
    GAMEDATA::getInstance()->setFriendOpenRoomResp(opdata);
    const rapidjson::Value &seatId = _mDoc["seatId"];
    const rapidjson::Value &rest = _mDoc["rest"];
    const rapidjson::Value &loard = _mDoc["lord"];
    const rapidjson::Value &isprivate = _mDoc["isprivate"];
    const rapidjson::Value &turn = _mDoc["turn"];
    if(_mDoc.HasMember("s")){
        GAMEDATA::getInstance()->setTurnHeroCpg(true);
    }
    GAMEDATA::getInstance()->setHeroSeatId(seatId.GetInt());
    //设置是否是私人房间
    std::string roomType = isprivate.GetString();
    GAMEDATA::getInstance()->setMahjongRoomType(roomType == "1" ? (MahjongRoom::privateRoom):(MahjongRoom::publicRoom));
    GAMEDATA::getInstance()->setGameType(3);
    LastGameData lastGameData;
    lastGameData.result = 1;//游戏中
    lastGameData.seatId = seatId.GetInt();
    lastGameData.rest = rest.GetString();
    lastGameData.loard = loard.GetInt();
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
        data.tru = temp["tru"].GetInt();
        data.ifready = 1;
        data.isOnline = temp["isonline"].GetInt();
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
    char* buf = const_cast<char*>(StringUtil::itos(seatId.GetInt()).c_str());
    postNotifyMessage(MSG_HZ_PLAYER_CONNECT_AGAIN, buf);
}

void MsgHandler::handleHZPlayerActionNotify(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &poker = _mDoc["poker"];
    const rapidjson::Value &seatId = _mDoc["sId"];
    HeroCpgRespData cpgRespData;
    PlayerCpgtData cpgData;
    cpgData.poker = poker.GetString();
    cpgData.sId = seatId.GetInt();
    cpgData.hu = 0;
    if (_mDoc.HasMember("peng")){
        const rapidjson::Value &peng = _mDoc["peng"];
        cpgData.peng = peng.GetString();
    }
    if (_mDoc.HasMember("gang")){
        const rapidjson::Value &gang = _mDoc["gang"];
        GangData gangData;
        gangData.gang = gang.GetString();
        gangData.flag = 0;
        cpgData.playerGang.push_back(gangData);
    }
    cpgRespData.playCpgt = cpgData;
    postNotifyMessage(MSG_HZ_PLAYER_PG,&cpgRespData);
}


void MsgHandler::handleHZGameResultNotify(std::string msg){
    
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    
    if(_mDoc.HasMember("matchid")){
        CompetitionResultInfo competitionData;
        competitionData.matchid = _mDoc["matchid"].GetString();
        competitionData.pride = _mDoc["prize"].GetString();
        competitionData.paiming = _mDoc["paiming"].GetString();
        GAMEDATA::getInstance()->setCompetitionResultData(competitionData);
    }
    if(_mDoc.HasMember("ifaa")){
        const rapidjson::Value &ifaa = _mDoc["ifaa"];
        GAMEDATA::getInstance()->setIsPayWayAA(strcmp(ifaa.GetString(), "1") == 0?true:false);
        UserData::getInstance()->setLatelyPayWayAA(strcmp(ifaa.GetString(), "1") == 0?true:false);
    }
    if(_mDoc.HasMember("poker")){
        GAMEDATA::getInstance()->setDiaopao(_mDoc["poker"].GetString());
    }else{
        GAMEDATA::getInstance()->setDiaopao("");
    }
    GameHongBaoPride pride;
    if(_mDoc.HasMember("dyj")){
        pride.dyj = _mDoc["dyj"].GetString();
    }else{
        pride.dyj = "-999";
    }
    if(_mDoc.HasMember("dyjfee")){
        pride.dyjfee = _mDoc["dyjfee"].GetString();
    }else{
        pride.dyjfee = "0";
    }
    
    if(_mDoc.HasMember("dsj")){
        pride.dsj = _mDoc["dsj"].GetString();
    }else{
        pride.dsj = "-999";
    }
    if(_mDoc.HasMember("dsjfee")){
        pride.dsjfee = _mDoc["dsjfee"].GetString();
    }else{
        pride.dsjfee = "0";
    }
    if(_mDoc.HasMember("fzfee")){
        pride.fzfee = _mDoc["fzfee"].GetString();
    }else{
        pride.fzfee = "0";
    }
    if(_mDoc.HasMember("sxlmfee")){
        pride.sxlmfee = _mDoc["sxlmfee"].GetString();
    }else{
        pride.sxlmfee = "0";
    }
    if(_mDoc.HasMember("fzId")){
        pride.fzid = _mDoc["fzId"].GetString();
        GAMEDATA::getInstance()->setFangZhuId(_mDoc["fzId"].GetString());
    }else{
        pride.fzid = "-999";
    }
    GAMEDATA::getInstance()->setGameHongBaoPride(pride);
    if(_mDoc.HasMember("hgdlb")){
        const rapidjson::Value &hgdlb = _mDoc["hgdlb"];
        GAMEDATA::getInstance()->setHuiGuiLiBao(hgdlb.GetString());
    }
    if(_mDoc.HasMember("prjucount")){
        GAMEDATA::getInstance()->setPrivateRoomType(_mDoc["prjucount"].GetString());
    }
    if(_mDoc.HasMember("fee")){
        GAMEDATA::getInstance()->setFee(_mDoc["fee"].GetString());
    }
    
    if(_mDoc.HasMember("ma")){
        GAMEDATA::getInstance()->setFanMa(_mDoc["ma"].GetString());
    }else{
        GAMEDATA::getInstance()->setFanMa("");
    }
    
    if(_mDoc.HasMember("fanma")){
        GAMEDATA::getInstance()->setFanMaType(_mDoc["fanma"].GetString());
    }
    
    if(_mDoc.HasMember("difen")){
        GAMEDATA::getInstance()->setHZDiFen(_mDoc["difen"].GetString());
    }
    
    
    if(_mDoc.HasMember("mashu")){
        GAMEDATA::getInstance()->setHZMaShu(_mDoc["mashu"].GetString());
    }else{
        GAMEDATA::getInstance()->setHZMaShu("0");
    }
    
    const rapidjson::Value &flag = _mDoc["flag"];
    const rapidjson::Value &finish = _mDoc["finish"];
    vector<GameResultData> gameResults;
    for (int i = 0; i < finish.Capacity(); ++i){
        GameResultData resultData;
        const rapidjson::Value &temp = finish[i];
        
        if(temp.HasMember("gangfen")){
            resultData.gangfen = temp["gangfen"].GetString();
        }else{
            resultData.gangfen ="";
        }
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
        if (temp.HasMember("tip")){
            resultData.tip = temp["tip"].GetString();
        }
        if (temp.HasMember("even")){
            resultData.even = temp["even"].GetString();
        }
        if (temp.HasMember("poxiaoId")){
            resultData.poxiaoId = temp["poxiaoId"].GetString();
        }
        if (temp.HasMember("zimocount")){
            resultData.zimocount = temp["zimocount"].GetString();
        }
        if (temp.HasMember("jiepaocount")){
            resultData.jiepaocount = temp["jiepaocount"].GetString();
        }
        if (temp.HasMember("dianpaocount")){
            resultData.dianpaocount = temp["dianpaocount"].GetString();
        }
        if (temp.HasMember("angangcount")){
            resultData.angangcount = temp["angangcount"].GetString();
        }
        if (temp.HasMember("minggangcount")){
            resultData.minggangcount = temp["minggangcount"].GetString();
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
    char* buf = const_cast<char*>(flag.GetString());
    postNotifyMessage(MSG_HZ_GAME_RESULT, buf);
    
}


void MsgHandler:: handleHZPlayerPengNotify(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &poker = _mDoc["poker"];
    const rapidjson::Value &seatId = _mDoc["seatId"];
    const rapidjson::Value &pengPoker = _mDoc["peng"];
    const rapidjson::Value &sId = _mDoc["sId"];
    PlayerCpgtData data;
    data.poker = poker.GetString();
    data.seatId = seatId.GetInt();
    data.peng = pengPoker.GetString();
    data.sId = sId.GetInt();
    postNotifyMessage(MSG_HZ_PLAYER_PENG, &data);
}

void MsgHandler::handleHZPlayerGangNotify(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &poker = _mDoc["poker"];
    const rapidjson::Value &seatId = _mDoc["seatId"];
    const rapidjson::Value &gang = _mDoc["gang"];
    const rapidjson::Value &flag = _mDoc["flag"];
    const rapidjson::Value &sId = _mDoc["sId"];
    PlayerCpgtData cpgData;
    cpgData.poker = poker.GetString();
    cpgData.seatId = seatId.GetInt();
    cpgData.sId = sId.GetInt();
    GangData gangData;
    gangData.gang = gang.GetString();
    gangData.flag = atoi(flag.GetString());
    cpgData.playerGang.push_back(gangData);
    postNotifyMessage(MSG_HZ_PLAYER_GANG, &cpgData);
}

void MsgHandler::handleHZPlayerCanclePGResp(std::string msg){
    
}


void MsgHandler::handleHZPlayerFanMaNotify(std::string msg){
    
}

void MsgHandler::handleHZPlayerHuNotify(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    PlayerCpgtData cpgData;
    cpgData.hu = 1;
    if(_mDoc.HasMember("angang")){
        const rapidjson::Value &angang = _mDoc["angang"];
        GangData gangData;
        gangData.gang = angang.GetString();
        gangData.flag = 1;
        cpgData.playerGang.push_back(gangData);
        cpgData.seatId = GAMEDATA::getInstance()->getHeroSeatId();
    }
    if(_mDoc.HasMember("penggang")){
        const rapidjson::Value &angang = _mDoc["penggang"];
        GangData gangData;
        gangData.gang = angang.GetString();
        gangData.flag = 2;
        cpgData.playerGang.push_back(gangData);
        cpgData.seatId = GAMEDATA::getInstance()->getHeroSeatId();
    }
    //    log("收到了服务端的胡牌协议1");
    postNotifyMessage(MSG_HZ_GAME_HU_ACTION, &cpgData);
}

void MsgHandler::handleHZDissovleRoomSelectedNotify(std::string msg){
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
    postNotifyMessage(MSG_HZ_DISSOVLE_ROOM_SELECTED_NOTIFY, nullptr);
}

void MsgHandler::handleHZDissovleRoomNotify(std::string msg){
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
    postNotifyMessage(MSG_DISSOVLE_ROOM_SELECTED_NOTIFY, nullptr);
}

void MsgHandler::handleHZGameContinueResp(std::string msg){
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
    GAMEDATA::getInstance()->setShowDialogType(result.GetInt());
    GAMEDATA::getInstance()->setEnterRoomResp(resp);
    postNotifyMessage(MSG_HZ_HERO_CONTINUE_RESP, nullptr);
}

void MsgHandler::handleInviteCodeResp(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &result = _mDoc["result"];
    char* buf = const_cast<char*>(result.GetString());
    postNotifyMessage(MSG_INVITE_CODE_RESP, buf);
}

void MsgHandler::handleHuafeiChangeListResp(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if(_mDoc.HasMember("list2")){
        const rapidjson::Value &mall = _mDoc["list2"];
        HuafeiChangeList data;
        data.needInit = true;
        for(int i=0;i<mall.Capacity();i++){
            const rapidjson::Value &temp = mall[i];
            HuafeiChange change;
            change.url = temp["url"].GetString();
            change.fee = StringUtils::format("%d",temp["fee"].GetInt());
            change.tofee =  StringUtils::format("%d",temp["tofee"].GetInt());
            data.list.push_back(change);
        }
        GAMEDATA::getInstance()->setHuafeiChangeList(data);
    }
    if(_mDoc.HasMember("list1")){
        const rapidjson::Value &mall = _mDoc["list1"];
        FangkaChangeList data;
        data.needInit = true;
        for(int i=0;i<mall.Capacity();i++){
            const rapidjson::Value &temp = mall[i];
            FangkaChange change;
            change.url = temp["url"].GetString();
            change.fee = StringUtils::format("%d",temp["fee"].GetInt());
            change.tofangka = StringUtils::format("%d",temp["tofangka"].GetInt());
            data.list.push_back(change);
        }
        GAMEDATA::getInstance()->setFangkaChangeList(data);
    }
    postNotifyMessage(MSG_PLAYER_HUAFEI_CHANGE_LIST, nullptr);
    
}

void MsgHandler::handleHuafeiChangeResp(std::string msg){
    
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &result = _mDoc["result"];
    HuafeiChangeResult myResult;
    myResult.result = result.GetString();
    if(_mDoc.HasMember("fee")){
        const rapidjson::Value &lequan = _mDoc["fee"];
        myResult.huafei = lequan.GetString();
    }
    GAMEDATA::getInstance()->setHuafeiChangeResult(myResult);
    postNotifyMessage(MSG_PLAYER_HUAFEI_CHANGE_RESP, nullptr);
    
}

// 话费兑换\房卡兑换记录回复{code:1069,poxiaoId:poxiaoId,list:[{id:"3",url:"",status:"1",fee:"",time:""},{id:"4",url:"",status:"2",fee:"",time:""}],list1:[{fangka:"3",url:"",time:""},{fangka:"4",url:"",time:""}]} //0兑换中 1已兑换
void MsgHandler::handleHuafeiChangeRecord(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    HuaChangeRecord records;
    if(_mDoc.HasMember("list")){
        const rapidjson::Value &list = _mDoc["list"];
        for(int i=0;i<list.Capacity();i++){
            HuaRecord rec;
            const rapidjson::Value &temp = list[i];
            rec.url =temp["url"].GetString();
            rec.fee =temp["fee"].GetString();
            rec.state = temp["status"].GetString();
            rec.time =temp["time"].GetString();
            rec.phone = temp["phone"].GetString();
            records.records.push_back(rec);
        }
    }
    GAMEDATA::getInstance()->setHuaChangeRecord(records);
    
    FangkaChangeRecord fangRecord;
    if(_mDoc.HasMember("list2")){
        const rapidjson::Value &list = _mDoc["list2"];
        for(int i=0;i<list.Capacity();i++){
            FangkaRecord rec;
            const rapidjson::Value &temp = list[i];
            rec.fee =StringUtils::format("%d",atoi(temp["fangka"].GetString()));
            rec.time =temp["time"].GetString();
            if(temp.HasMember("url"))
                rec.url = temp["url"].GetString();
            fangRecord.records.push_back(rec);
        }
    }
    GAMEDATA::getInstance()->setFangkaChangeRecord(fangRecord);
    
    postNotifyMessage(MSG_PLAYER_HAUFEI_EXCHANGE_RECORD, nullptr);
}

void MsgHandler::handleTruNotify(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if(_mDoc.HasMember("seatId")){
        TruStateData data;
        const rapidjson::Value &result = _mDoc["seatId"];
        data.seatId = result.GetString();
        const rapidjson::Value &flag = _mDoc["flag"];
        data.flag = flag.GetString();
        postNotifyMessage(MSG_PLAYER_TRU_NOTIFY, &data);
    }
}

void MsgHandler::handleLobbyPaiHang(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    LobbyPaiHangData data;
    if(_mDoc.HasMember("name1")){
        const rapidjson::Value &name1 = _mDoc["name1"];
        data.name1 = name1.GetString();
    }
    if(_mDoc.HasMember("tab1")){
        const rapidjson::Value &tab1 = _mDoc["tab1"];
        for(int a = 0; a<tab1.Capacity();a++){
            PlayerRank rank;
            const rapidjson::Value &temp = tab1[a];
            rank.key = temp["key"].GetString();
            rank.value = temp["value"].GetString();
            rank.pic = temp["pic"].GetString();
            data.content1.push_back(rank);
        }
    }
    if(_mDoc.HasMember("name2")){
        const rapidjson::Value &name2 = _mDoc["name2"];
        data.name2 = name2.GetString();
    }
    if(_mDoc.HasMember("tab2")){
        const rapidjson::Value &tab2 = _mDoc["tab2"];
        for(int a = 0; a<tab2.Capacity();a++){
            PlayerRank rank;
            const rapidjson::Value &temp = tab2[a];
            rank.key = temp["key"].GetString();
            rank.value = temp["value"].GetString();
            rank.pic = temp["pic"].GetString();
            data.content2.push_back(rank);
        }
    }
    if(_mDoc.HasMember("name3")){
        const rapidjson::Value &name3 = _mDoc["name3"];
        data.name3 = name3.GetString();
    }
    if(_mDoc.HasMember("tab3")){
        const rapidjson::Value &tab3 = _mDoc["tab3"];
        for(int a = 0; a<tab3.Capacity();a++){
            PlayerRank rank;
            const rapidjson::Value &temp = tab3[a];
            rank.key = temp["key"].GetString();
            rank.value = temp["value"].GetString();
            rank.pic = temp["pic"].GetString();
            data.content3.push_back(rank);
        }
    }
    GAMEDATA::getInstance()->setLobbyPaiHangData(data);
    postNotifyMessage(MSG_UPDATE_LOBBY_RANK, nullptr);
}

void MsgHandler::handleTurntableData(std::string msg){
    //玩家大转盘
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    TurnTableData  data;
    if (_mDoc.HasMember("result")){
        data.result = _mDoc["result"].GetString();
    }
    if (_mDoc.HasMember("content")){
        const rapidjson::Value &prize = _mDoc["content"];
        for (int i = 0; i < prize.Capacity(); i++){
            PrideData info;
            const rapidjson::Value &temp = prize[i];
            if (temp.HasMember("gold")){
                info.type = PrideType::gold;
                info.number = temp["gold"].GetString();
            }
            if (temp.HasMember("lequan")){
                info.type = PrideType::lequan;
                info.number = temp["lequan"].GetString();
            }
            if (temp.HasMember("fangka")){
                info.type = PrideType::fangka;
                info.number = temp["fangka"].GetString();
            }
            if (temp.HasMember("fee")){
                info.type = PrideType::fee;
                info.number = temp["fee"].GetString();
            }
            if (temp.HasMember("iphone7")){
                info.type = PrideType::prop;
                info.number = temp["iphone7"].GetString();
            }
            if (temp.HasMember("nothing")){
                info.type = PrideType::nothing;
                info.number = temp["nothing"].GetString();
            }
            data.prides.push_back(info);
        }
    }
    GAMEDATA::getInstance()->setTurnTableData(data);
    postNotifyMessage(MSG_PLAYER_TURNTABLE_PRIDE, nullptr);
}


void MsgHandler::handleTurntableResult(std::string msg){
    //玩家大转盘结果
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    TurnTablePrideData  data;
    if (_mDoc.HasMember("result")){
        data.result = _mDoc["result"].GetString();
    }
    if(_mDoc.HasMember("rest")){
        const rapidjson::Value &rest = _mDoc["rest"];
        UserData::getInstance()->setTurntableNumber(rest.GetString());
    }
    if (_mDoc.HasMember("content")){
        const rapidjson::Value &temp = _mDoc["content"];
        PrideData info;
        if (temp.HasMember("gold")){
            info.type = PrideType::gold;
            info.number = temp["gold"].GetString();
        }
        if (temp.HasMember("lequan")){
            info.type = PrideType::lequan;
            info.number = temp["lequan"].GetString();
        }
        if (temp.HasMember("fangka")){
            info.type = PrideType::fangka;
            info.number = temp["fangka"].GetString();
        }
        if (temp.HasMember("fee")){
            info.type = PrideType::fee;
            info.number = temp["fee"].GetString();
        }
        if (temp.HasMember("iphone7")){
            info.type = PrideType::prop;
            info.number = temp["iphone7"].GetString();
        }
        if (temp.HasMember("nothing")){
            info.type = PrideType::nothing;
            info.number = temp["nothing"].GetString();
        }
        data.pride = info;
    }
    GAMEDATA::getInstance()->setTurnTablePrideData(data);
    postNotifyMessage(MSG_PLAYER_TURNTABLE_PRIDE_RESULT, nullptr);
}

void MsgHandler::handleHuafeiChangeFangka(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &result = _mDoc["result"];
    HuafeiChangeResult myResult;
    myResult.result = result.GetString();
    if(_mDoc.HasMember("fee")){
        const rapidjson::Value &lequan = _mDoc["fee"];
        myResult.huafei = lequan.GetString();
    }
    GAMEDATA::getInstance()->setHuafeiChangeResult(myResult);
    postNotifyMessage(MSG_PLAYER_HUAFEI_CHANGE_RESP, nullptr);
}

void MsgHandler::handleTurntableShare(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if(_mDoc.HasMember("dzpc")){
        const rapidjson::Value &dzpc = _mDoc["dzpc"];
        UserData::getInstance()->setTurntableNumber(dzpc.GetString());
    }
}

void MsgHandler:: handleCMOpenRoomResp(std::string msg){
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
    if(_mDoc.HasMember("ifaa")){
        const rapidjson::Value &ifaa = _mDoc["ifaa"];
        GAMEDATA::getInstance()->setIsPayWayAA(strcmp(ifaa.GetString(), "1") == 0?true:false);
        UserData::getInstance()->setLatelyPayWayAA(strcmp(ifaa.GetString(), "1") == 0?true:false);
    }
    FriendOpenRoomRespData data;
    if(_mDoc.HasMember("dkf")){
        data.agency = true;
        AgencyRoomList roomList;
        const rapidjson::Value &agency = _mDoc["dkf"];
        for (int i=0; i<agency.Capacity(); i++){
            const rapidjson::Value &temp = agency[i];
            AgencyRoomData data;
            data.roomid = temp["prid"].GetString();
            data.gameInfo = temp["desc"].GetString();
            data.playername = temp["user"].GetString();
            data.createtime = temp["time"].GetString();
            data.type = temp["type"].GetString();
            if(temp.HasMember("rs"))
                data.rs = temp["rs"].GetString();
            if(temp.HasMember("js"))
                data.js = temp["js"].GetString();
            roomList.roomlist.push_back(data);
        }
        GAMEDATA::getInstance()->setAgencyRoomList(roomList);
    }else{
        data.agency = false;
    }
    if(_mDoc.HasMember("ifzm")){
        const rapidjson::Value &ifzm = _mDoc["ifzm"];
        GAMEDATA::getInstance()->setPrivateZiMo(ifzm.GetString());
        UserData::getInstance()->setLatelyBDZiMo(ifzm.GetString());
    }
    if(_mDoc.HasMember("qidui")){
        const rapidjson::Value &qidui = _mDoc["qidui"];
        GAMEDATA::getInstance()->setPrivateQiDui(qidui.GetString());
        UserData::getInstance()->setLatelyBDQiDui(qidui.GetString());
    }
    if(_mDoc.HasMember("fanpai")){
        const rapidjson::Value &fanpai = _mDoc["fanpai"];
        GAMEDATA::getInstance()->setPrivateFanPai(fanpai.GetString());
        UserData::getInstance()->setLatelyBDFanPai(fanpai.GetString());
    }
    if(_mDoc.HasMember("prjushu")){
        const rapidjson::Value &prjushu = _mDoc["prjushu"];
        data.prjushu = prjushu.GetString();
        UserData::getInstance()->setLatelyGameJuShu(prjushu.GetString());
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
    if(_mDoc.HasMember("size")){
        const rapidjson::Value &size = _mDoc["size"];
        GAMEDATA::getInstance()->setMyGameModel(atoi(size.GetString()));
        
    }
    
    PayPointInfo pointInfo;
    if(_mDoc.HasMember("point")){
        const rapidjson::Value &point = _mDoc["point"];
        pointInfo.point = point.GetString();
    }
    if(_mDoc.HasMember("wxfee")){
        const rapidjson::Value &fee = _mDoc["wxfee"];
        pointInfo.fee = fee.GetString();
    }
    if(_mDoc.HasMember("wxfangka")){
        const rapidjson::Value &fangka = _mDoc["wxfangka"];
        pointInfo.fangka = fangka.GetString();
    }
    if(_mDoc.HasMember("applefangka")){
        const rapidjson::Value &applefangka = _mDoc["applefangka"];
        pointInfo.applefangka = applefangka.GetString();
    }
    if(_mDoc.HasMember("applefee")){
        const rapidjson::Value &applefee = _mDoc["applefee"];
        pointInfo.applefee = applefee.GetString();
    }
    GAMEDATA::getInstance()->setPayPointInfo(pointInfo);
    
    const rapidjson::Value &result = _mDoc["result"];
    data.result = result.GetInt();
    GAMEDATA::getInstance()->clearPlayersInfo();
    GAMEDATA::getInstance()->setFriendOpenRoomResp(data);
    if (_mDoc.HasMember("other")){
        const rapidjson::Value &pArr = _mDoc["other"];
        for (int i = 0; i < pArr.Capacity(); ++i){
            const rapidjson::Value &temp = pArr[i];
            PlayerInfo* info = new PlayerInfo();
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
    PlayerInfo* info = new PlayerInfo();
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
    GAMEDATA::getInstance()->setGameType(5);
    UserData::getInstance()->setLatelyMahjongType(GameMahjongType::BaiDa);
    postNotifyMessage(MSG_CM_FRIEND_OPEN_ROOM_RESP, nullptr);
    
}

void MsgHandler::handleCMFapaiNotify(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if(_mDoc.HasMember("seatId")){
        GAMEDATA::getInstance()->setHeroSeatId(atoi(_mDoc["seatId"].GetString()));
    }
    MahjongFaPaiData faPaiData;
    faPaiData.heroPokers = _mDoc["poker"].GetString();
    if(_mDoc.HasMember("hua")){
        const rapidjson::Value &huama = _mDoc["hua"];
        for (int i=0; i<huama.Capacity(); i++) {
            const rapidjson::Value &temp = huama[i];
            HuaData data;
            data.hua = temp["hua"].GetString();
            data.setaId = temp["seatId"].GetString();
            data.poxiaoId = temp["poxiaoId"].GetString();
            faPaiData.huas.push_back(data);
        }
    }
    faPaiData.dice = _mDoc["dice"].GetString();
    faPaiData.start = _mDoc["start"].GetInt();
    if(_mDoc.HasMember("prjucount")){
        faPaiData.prjucount = _mDoc["prjucount"].GetInt();
    }
    const rapidjson::Value &rest = _mDoc["rest"];
    faPaiData.rest = rest.GetString();
    PlayerCpgtData tingData;
    if(_mDoc.HasMember("angang")){
        faPaiData.hasGang = true;
        const rapidjson::Value &angang = _mDoc["angang"];
        GangData gangData;
        gangData.gang = angang.GetString();
        gangData.flag = 1;
        tingData.playerGang.push_back(gangData);
        tingData.seatId = GAMEDATA::getInstance()->getHeroSeatId();
    }
    if(_mDoc.HasMember("hu")){
        tingData.hu =  1;
    }else{
        tingData.hu =  0;
    }
    if (_mDoc.HasMember("ting1")){
        const rapidjson::Value &ting1 = _mDoc["ting1"];
        for(int i=0;i<ting1.Capacity();i++){
            HeroHuPaiData huPaiData;
            auto &temp = ting1[i];
            if(temp.HasMember("poker")){
                huPaiData.poker = temp["poker"].GetInt();
            }
            if(temp.HasMember("hu1")){
                const rapidjson::Value &data =  temp["hu1"];
                for (int i=0; i<data.Capacity(); i++) {
                    const rapidjson::Value &tem = data[i];
                    HuPokerData pd;
                    pd.poker = tem["hu"].GetString();
                    pd.num = tem["num"].GetString();
                    huPaiData.data.push_back(pd);
                }
            }
            tingData.heroHu.push_back(huPaiData);
        }
    }
    faPaiData.mjHuData = tingData;
    GAMEDATA::getInstance()->setIsTrusteeship(false);
    GAMEDATA::getInstance()->setMahjongFaPaiData(faPaiData);
    postNotifyMessage(MSG_GAME_BD_START_FAPAI_NOTIFY, nullptr);
    
}

void MsgHandler::handleCMEnterRoomResp(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if(_mDoc.HasMember("poxiaoId")){
        const rapidjson::Value &poxiaoId = _mDoc["poxiaoId"];
        UserData::getInstance()->setPoxiaoId(poxiaoId.GetString());
    }
    if(_mDoc.HasMember("size")){
        const rapidjson::Value &size = _mDoc["size"];
        GAMEDATA::getInstance()->setMyGameModel(atoi(size.GetString()));
        
    }
    if(_mDoc.HasMember("ifaa")){
        const rapidjson::Value &ifaa = _mDoc["ifaa"];
        GAMEDATA::getInstance()->setIsPayWayAA(strcmp(ifaa.GetString(), "1") == 0?true:false);
        UserData::getInstance()->setLatelyPayWayAA(strcmp(ifaa.GetString(), "1") == 0?true:false);
    }
    
    FriendOpenRoomRespData data = GAMEDATA::getInstance()->getFriendOpenRoomResp();
    const rapidjson::Value &result = _mDoc["result"];
    data.result = result.GetInt();
    if(_mDoc.HasMember("ifzm")){
        const rapidjson::Value &ifzm = _mDoc["ifzm"];
        GAMEDATA::getInstance()->setPrivateZiMo(ifzm.GetString());
        UserData::getInstance()->setLatelyBDZiMo(ifzm.GetString());
    }
    if(_mDoc.HasMember("qidui")){
        const rapidjson::Value &qidui = _mDoc["qidui"];
        GAMEDATA::getInstance()->setPrivateQiDui(qidui.GetString());
        UserData::getInstance()->setLatelyBDQiDui(qidui.GetString());
    }
    if(_mDoc.HasMember("fanpai")){
        const rapidjson::Value &fanpai = _mDoc["fanpai"];
        GAMEDATA::getInstance()->setPrivateFanPai(fanpai.GetString());
        UserData::getInstance()->setLatelyBDFanPai(fanpai.GetString());
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
        UserData::getInstance()->setLatelyGameJuShu(prjushu.GetString());
    }
    if(_mDoc.HasMember("prjucount")){
        const rapidjson::Value &prjucount = _mDoc["prjucount"];
        data.prjucount = StringUtils::format("%d",atoi(prjucount.GetString())+1);
    }
    if(_mDoc.HasMember("jifen")){
        const rapidjson::Value &myjifen = _mDoc["jifen"];
        GAMEDATA::getInstance()->setScore(myjifen.GetInt());
    }
    if(_mDoc.HasMember("prize")){
        GAMEDATA::getInstance()->setCompetitionPride(_mDoc["prize"].GetString());
    }
    PayPointInfo pointInfo;
    if(_mDoc.HasMember("point")){
        const rapidjson::Value &point = _mDoc["point"];
        pointInfo.point = point.GetString();
    }
    if(_mDoc.HasMember("wxfee")){
        const rapidjson::Value &fee = _mDoc["wxfee"];
        pointInfo.fee = fee.GetString();
    }
    if(_mDoc.HasMember("wxfangka")){
        const rapidjson::Value &fangka = _mDoc["wxfangka"];
        pointInfo.fangka = fangka.GetString();
    }
    if(_mDoc.HasMember("applefangka")){
        const rapidjson::Value &applefangka = _mDoc["applefangka"];
        pointInfo.applefangka = applefangka.GetString();
    }
    if(_mDoc.HasMember("applefee")){
        const rapidjson::Value &applefee = _mDoc["applefee"];
        pointInfo.applefee = applefee.GetString();
    }
    GAMEDATA::getInstance()->setPayPointInfo(pointInfo);
    GAMEDATA::getInstance()->clearPlayersInfo();
    GAMEDATA::getInstance()->setFriendOpenRoomResp(data);
    if (_mDoc.HasMember("other")){
        const rapidjson::Value &pArr = _mDoc["other"];
        for (int i = 0; i < pArr.Capacity(); ++i){
            const rapidjson::Value &temp = pArr[i];
            PlayerInfo* info = new PlayerInfo();
            info->setScore(temp["jifen"].GetInt());
            info->setSeatId(temp["seatId"].GetInt());
            info->setPoxiaoId(temp["poxiaoId"].GetString());
            info->setBanker(false);
            info->setIsReady(temp["ifready"].GetInt() == 0 ? false : true);
            info->setGold(temp["gold"].GetInt());
            info->setTicket(temp["lequan"].GetInt());
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
    PlayerInfo* info = new PlayerInfo();
    info->setScore(GAMEDATA::getInstance()->getScore());
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
    
    GAMEDATA::getInstance()->addPlayersInfo(info);
    GAMEDATA::getInstance()->setIsPlaying(false);
    GAMEDATA::getInstance()->setGameType(5);
    UserData::getInstance()->setLatelyMahjongType(GameMahjongType::BaiDa);
    postNotifyMessage(MSG_CM_ENTER_FRIEND_ROOM_RESP, nullptr);
}

void MsgHandler::handleCMReConnectResp(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if(_mDoc.HasMember("poxiaoId")){
        const rapidjson::Value &poxiaoId = _mDoc["poxiaoId"];
        UserData::getInstance()->setPoxiaoId(poxiaoId.GetString());
    }
    if(_mDoc.HasMember("ifaa")){
        const rapidjson::Value &ifaa = _mDoc["ifaa"];
        GAMEDATA::getInstance()->setIsPayWayAA(strcmp(ifaa.GetString(), "1") == 0?true:false);
        UserData::getInstance()->setLatelyPayWayAA(strcmp(ifaa.GetString(), "1") == 0?true:false);
    }
    if(_mDoc.HasMember("size")){
        const rapidjson::Value &size = _mDoc["size"];
        GAMEDATA::getInstance()->setMyGameModel(atoi(size.GetString()));
    }
    if(_mDoc.HasMember("prize")){
        GAMEDATA::getInstance()->setCompetitionPride(_mDoc["prize"].GetString());
    }
    if(_mDoc.HasMember("umark")){
        const rapidjson::Value &umark = _mDoc["umark"];
        UserData::getInstance()->setMarkId(umark.GetString());
    }
    if(_mDoc.HasMember("dice")){
        const rapidjson::Value &dice = _mDoc["dice"];
        GAMEDATA::getInstance()->setMahjongDice(dice.GetString());
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
    if(_mDoc.HasMember("ifzm")){
        const rapidjson::Value &ifzm = _mDoc["ifzm"];
        GAMEDATA::getInstance()->setPrivateZiMo(ifzm.GetString());
        UserData::getInstance()->setLatelyBDZiMo(ifzm.GetString());
    }
    if(_mDoc.HasMember("qidui")){
        const rapidjson::Value &qidui = _mDoc["qidui"];
        GAMEDATA::getInstance()->setPrivateQiDui(qidui.GetString());
        UserData::getInstance()->setLatelyBDQiDui(qidui.GetString());
    }
    if(_mDoc.HasMember("fanpai")){
        const rapidjson::Value &fanpai = _mDoc["fanpai"];
        GAMEDATA::getInstance()->setPrivateFanPai(fanpai.GetString());
        UserData::getInstance()->setLatelyBDFanPai(fanpai.GetString());
    }
    GAMEDATA::getInstance()->setFriendOpenRoomResp(opdata);
    const rapidjson::Value &seatId = _mDoc["seatId"];
    const rapidjson::Value &rest = _mDoc["rest"];
    const rapidjson::Value &loard = _mDoc["lord"];
    const rapidjson::Value &isprivate = _mDoc["isprivate"];
    const rapidjson::Value &turn = _mDoc["turn"];
    if(_mDoc.HasMember("s")){
        GAMEDATA::getInstance()->setTurnHeroCpg(true);
    }
    GAMEDATA::getInstance()->setHeroSeatId(seatId.GetInt());
    //设置是否是私人房间
    std::string roomType = isprivate.GetString();
    GAMEDATA::getInstance()->setMahjongRoomType(roomType == "1" ? (MahjongRoom::privateRoom):(MahjongRoom::publicRoom));
    LastGameData lastGameData;
    lastGameData.result = 1;//游戏中
    lastGameData.seatId = seatId.GetInt();
    lastGameData.rest = rest.GetString();
    lastGameData.loard = loard.GetInt();
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
        data.hua = temp["hua"].GetString();
        data.tru = temp["tru"].GetInt();
        data.ifready = 1;
        data.isOnline = temp["isonline"].GetInt();
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
    GAMEDATA::getInstance()->setGameType(5);
    GAMEDATA::getInstance()->setLastGameDataBackup(lastGameData);
    char* buf = const_cast<char*>(StringUtil::itos(seatId.GetInt()).c_str());
    postNotifyMessage(MSG_PLAYER_CM_CONNECT_AGAIN, buf);
    
}

void MsgHandler::cmNextPlayer(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    PlayerTurnData playerTurnData;
    playerTurnData.seatId = _mDoc["seatId"].GetInt();
    if (_mDoc.HasMember("poker")){
        const rapidjson::Value &poker = _mDoc["poker"];
        playerTurnData.poker = atoi(poker.GetString());
    }
    const rapidjson::Value &rest = _mDoc["rest"];
    playerTurnData.rest = rest.GetString();
    if (_mDoc.HasMember("num")){
        const rapidjson::Value &num = _mDoc["num"];
        playerTurnData.handNum = num.GetInt();
    }
    PlayerCpgtData tingData;
    tingData.seatId = _mDoc["seatId"].GetInt();
    if (_mDoc.HasMember("angang")){
        const rapidjson::Value &angang = _mDoc["angang"];
        GangData gangData;
        gangData.gang = angang.GetString();
        gangData.flag = 1;
        tingData.playerGang.push_back(gangData);
    }
    if (_mDoc.HasMember("penggang")){
        const rapidjson::Value &penggang = _mDoc["penggang"];
        GangData gangData;
        gangData.gang = penggang.GetString();
        gangData.flag = 2;
        tingData.playerGang.push_back(gangData);
    }
    if(_mDoc.HasMember("hu")){
        tingData.hu = 1;//红中麻将可胡
    }else{
        tingData.hu = 0;
    }
    if (_mDoc.HasMember("ting") || _mDoc.HasMember("angang") || _mDoc.HasMember("penggang")||_mDoc.HasMember("hu")){
        playerTurnData.hastinggang = true;
    }
    if (_mDoc.HasMember("ting1")){
        const rapidjson::Value &ting1 = _mDoc["ting1"];
        for(int i=0;i<ting1.Capacity();i++){
            HeroHuPaiData huPaiData;
            auto &temp = ting1[i];
            if(temp.HasMember("poker")){
                huPaiData.poker = temp["poker"].GetInt();
            }
            if(temp.HasMember("hu1")){
                const rapidjson::Value &data =  temp["hu1"];
                for (int i=0; i<data.Capacity(); i++) {
                    const rapidjson::Value &tem = data[i];
                    HuPokerData pd;
                    pd.poker = tem["hu"].GetString();
                    pd.num = tem["num"].GetString();
                    huPaiData.data.push_back(pd);
                }
            }
            tingData.heroHu.push_back(huPaiData);
        }
    }
    playerTurnData.cpgData = tingData;
    postNotifyMessage(MSG_CM_PLAYER_TURN_WHO, &playerTurnData);
}


void MsgHandler::showBDCpgNotify(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &poker = _mDoc["poker"];
    const rapidjson::Value &seatId = _mDoc["sId"];
    HeroCpgRespData cpgRespData;
    PlayerCpgtData cpgData;
    cpgData.poker = poker.GetString();
    cpgData.sId = seatId.GetInt();
    if (_mDoc.HasMember("peng")){
        const rapidjson::Value &peng = _mDoc["peng"];
        cpgData.peng = peng.GetString();
    }
    if (_mDoc.HasMember("gang")){
        const rapidjson::Value &gang = _mDoc["gang"];
        GangData gangData;
        gangData.gang = gang.GetString();
        gangData.flag = 0;
        cpgData.playerGang.push_back(gangData);
    }
    if(_mDoc.HasMember("hu")){
        cpgData.hu = 1;
    }else{
        cpgData.hu = 0;
    }
    cpgRespData.playCpgt = cpgData;
    postNotifyMessage(MSG_CM_PLAYER_CPG,&cpgRespData);
}

void MsgHandler::cmHeroChiResp(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    HeroCpgRespData cpgRespData;
    const rapidjson::Value &result = _mDoc["result"];
    PlayerCpgtData playerCpg;
    cpgRespData.result = result.GetInt();
    
    if (_mDoc.HasMember("forbit")){
        const rapidjson::Value &forbit = _mDoc["forbit"];
        cpgRespData.forbit = forbit.GetString();
    }
    if (_mDoc.HasMember("gang")){
        const rapidjson::Value &gang = _mDoc["gang"];
        GangData gangData;
        gangData.gang = gang.GetString();
        gangData.flag = 0;
        playerCpg.playerGang.push_back(gangData);
    }
    
    if (_mDoc.HasMember("ting1")){
        const rapidjson::Value &ting1 = _mDoc["ting1"];
        for(int i=0;i<ting1.Capacity();i++){
            HeroHuPaiData huPaiData;
            auto &temp = ting1[i];
            if(temp.HasMember("poker")){
                huPaiData.poker = temp["poker"].GetInt();
            }
            if(temp.HasMember("hu1")){
                const rapidjson::Value &data =  temp["hu1"];
                for (int i=0; i<data.Capacity(); i++) {
                    const rapidjson::Value &tem = data[i];
                    HuPokerData pd;
                    pd.poker = tem["hu"].GetString();
                    pd.num = tem["num"].GetString();
                    huPaiData.data.push_back(pd);
                }
            }
            playerCpg.heroHu.push_back(huPaiData);
        }
    }
    cpgRespData.playCpgt = playerCpg;
    postNotifyMessage(MSG_HERO_CHI_RESP, &cpgRespData);
}

void MsgHandler::showCMOtherChiNotify(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &poker = _mDoc["poker"];
    const rapidjson::Value &seatId = _mDoc["seatId"];
    const rapidjson::Value &chi = _mDoc["chi"];
    const rapidjson::Value &sId = _mDoc["sId"];
    PlayerCpgtData cpgData;
    cpgData.poker = poker.GetString();
    cpgData.seatId = seatId.GetInt();
    cpgData.sId = sId.GetInt();
    postNotifyMessage(MSG_OTHER_PLAYER_CHI, &cpgData);
}

void MsgHandler::bdHeroPengResp(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    HeroCpgRespData cpgRespData;
    const rapidjson::Value &result = _mDoc["result"];
    cpgRespData.result = result.GetInt();
    PlayerCpgtData playerCpg;
    if (_mDoc.HasMember("poker")){
        const rapidjson::Value &poker = _mDoc["poker"];
        playerCpg.poker = poker.GetString();
    }
    if (_mDoc.HasMember("seatId")){
        const rapidjson::Value &seatId = _mDoc["seatId"];
        playerCpg.seatId = seatId.GetInt();
    }
    if (_mDoc.HasMember("peng")){
        const rapidjson::Value &pengPoker = _mDoc["peng"];
        playerCpg.peng = pengPoker.GetString();
    }
    if (_mDoc.HasMember("sId")){
        const rapidjson::Value &sId = _mDoc["sId"];
        playerCpg.sId = sId.GetInt();
    }
    if (_mDoc.HasMember("gang")){
        const rapidjson::Value &gang = _mDoc["gang"];
        GangData gangData;
        gangData.gang = gang.GetString();
        gangData.flag = 0;
        playerCpg.playerGang.push_back(gangData);
    }else{
        playerCpg.playerGang.clear();
    }
    if (_mDoc.HasMember("ting1")){
        const rapidjson::Value &ting1 = _mDoc["ting1"];
        for(int i=0;i<ting1.Capacity();i++){
            HeroHuPaiData huPaiData;
            auto &temp = ting1[i];
            if(temp.HasMember("poker")){
                huPaiData.poker = temp["poker"].GetInt();
            }
            if(temp.HasMember("hu1")){
                const rapidjson::Value &data =  temp["hu1"];
                for (int i=0; i<data.Capacity(); i++) {
                    const rapidjson::Value &tem = data[i];
                    HuPokerData pd;
                    pd.poker = tem["hu"].GetString();
                    pd.num = tem["num"].GetString();
                    huPaiData.data.push_back(pd);
                }
            }
            playerCpg.heroHu.push_back(huPaiData);
        }
    }
    cpgRespData.playCpgt = playerCpg;
    postNotifyMessage(MSG_HERO_PENG_RESP, &cpgRespData);
}

void MsgHandler::showBDOtherPengNotify(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &poker = _mDoc["poker"];
    const rapidjson::Value &seatId = _mDoc["seatId"];
    const rapidjson::Value &pengPoker = _mDoc["peng"];
    const rapidjson::Value &sId = _mDoc["sId"];
    PlayerCpgtData data;
    data.poker = poker.GetString();
    data.seatId = seatId.GetInt();
    data.peng = pengPoker.GetString();
    data.sId = sId.GetInt();
    postNotifyMessage(MSG_OTHER_PLAYER_PENG, &data);
}

void MsgHandler::bdHeroGangResp(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    HeroCpgRespData cpgRespData;
    const rapidjson::Value &result = _mDoc["result"];
    cpgRespData.result = result.GetInt();
    PlayerCpgtData playerCpg;
    if (_mDoc.HasMember("gang")&&_mDoc.HasMember("flag")){
        const rapidjson::Value &gang = _mDoc["gang"];
        const rapidjson::Value &flag = _mDoc["flag"];
        GangData gangData;
        gangData.gang = gang.GetString();
        gangData.flag = atoi(flag.GetString());
        playerCpg.playerGang.push_back(gangData);
    }
    if (_mDoc.HasMember("sId")){
        const rapidjson::Value &sId = _mDoc["sId"];
        playerCpg.sId= sId.GetInt();
    }
    if (_mDoc.HasMember("poker")){
        const rapidjson::Value &poker = _mDoc["poker"];
        playerCpg.poker= atoi(poker.GetString());
    }
    cpgRespData.playCpgt = playerCpg;
    postNotifyMessage(MSG_HERO_GANG_RESP, &cpgRespData);
}


void MsgHandler::showBDOtherGangNotify(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &poker = _mDoc["poker"];
    const rapidjson::Value &seatId = _mDoc["seatId"];
    const rapidjson::Value &gang = _mDoc["gang"];
    const rapidjson::Value &flag = _mDoc["flag"];
    const rapidjson::Value &sId = _mDoc["sId"];
    PlayerCpgtData cpgData;
    cpgData.poker = poker.GetString();
    cpgData.seatId = seatId.GetInt();
    cpgData.sId = sId.GetInt();
    GangData gangData;
    gangData.gang = gang.GetString();
    gangData.flag = atoi(flag.GetString());
    cpgData.playerGang.push_back(gangData);
    postNotifyMessage(MSG_OTHER_PLAYER_GANG, &cpgData);
}

void MsgHandler::gameCMResultNotify(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if(_mDoc.HasMember("matchid")){
        CompetitionResultInfo competitionData;
        competitionData.matchid = _mDoc["matchid"].GetString();
        competitionData.pride = _mDoc["prize"].GetString();
        competitionData.paiming = _mDoc["paiming"].GetString();
        GAMEDATA::getInstance()->setCompetitionResultData(competitionData);
    }
    if(_mDoc.HasMember("ifaa")){
        const rapidjson::Value &ifaa = _mDoc["ifaa"];
        GAMEDATA::getInstance()->setIsPayWayAA(strcmp(ifaa.GetString(), "1") == 0?true:false);
        UserData::getInstance()->setLatelyPayWayAA(strcmp(ifaa.GetString(), "1") == 0?true:false);
    }
    if(_mDoc.HasMember("poker")){
        GAMEDATA::getInstance()->setDiaopao(_mDoc["poker"].GetString());
    }else{
        GAMEDATA::getInstance()->setDiaopao("");
    }
    GameHongBaoPride pride;
    if(_mDoc.HasMember("dyj")){
        pride.dyj = _mDoc["dyj"].GetString();
    }else{
        pride.dyj = "-999";
    }
    if(_mDoc.HasMember("dyjfee")){
        pride.dyjfee = _mDoc["dyjfee"].GetString();
    }else{
        pride.dyjfee = "0";
    }
    
    if(_mDoc.HasMember("dsj")){
        pride.dsj = _mDoc["dsj"].GetString();
    }else{
        pride.dsj = "-999";
    }
    if(_mDoc.HasMember("dsjfee")){
        pride.dsjfee = _mDoc["dsjfee"].GetString();
    }else{
        pride.dsjfee = "0";
    }
    if(_mDoc.HasMember("fzfee")){
        pride.fzfee = _mDoc["fzfee"].GetString();
    }else{
        pride.fzfee = "0";
    }
    if(_mDoc.HasMember("sxlmfee")){
        pride.sxlmfee = _mDoc["sxlmfee"].GetString();
    }else{
        pride.sxlmfee = "0";
    }
    if(_mDoc.HasMember("fzId")){
        pride.fzid = _mDoc["fzId"].GetString();
        GAMEDATA::getInstance()->setFangZhuId(_mDoc["fzId"].GetString());
    }else{
        pride.fzid = "-999";
    }
    GAMEDATA::getInstance()->setGameHongBaoPride(pride);
    
    if(_mDoc.HasMember("hgdlb")){
        const rapidjson::Value &hgdlb = _mDoc["hgdlb"];
        GAMEDATA::getInstance()->setHuiGuiLiBao(hgdlb.GetString());
    }
    
    if(_mDoc.HasMember("prjucount")){
        GAMEDATA::getInstance()->setPrivateRoomType(_mDoc["prjucount"].GetString());
    }
    if(_mDoc.HasMember("fee")){
        GAMEDATA::getInstance()->setFee(_mDoc["fee"].GetString());
    }
    if(_mDoc.HasMember("ma")){
        GAMEDATA::getInstance()->setFanMa(_mDoc["ma"].GetString());
    }
    if(_mDoc.HasMember("ifmq")){
        const rapidjson::Value &ifmq = _mDoc["ifmq"];
        GAMEDATA::getInstance()->setFPMenQing(ifmq.GetString());
        UserData::getInstance()->setLatelyFPMenQing(ifmq.GetString());
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
        if (temp.HasMember("tip")){
            resultData.tip = temp["tip"].GetString();
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
        if (temp.HasMember("zimocount")){
            resultData.zimocount = temp["zimocount"].GetString();
        }
        if (temp.HasMember("jiepaocount")){
            resultData.jiepaocount = temp["jiepaocount"].GetString();
        }
        if (temp.HasMember("dianpaocount")){
            resultData.dianpaocount = temp["dianpaocount"].GetString();
        }
        if (temp.HasMember("angangcount")){
            resultData.angangcount = temp["angangcount"].GetString();
        }
        if (temp.HasMember("minggangcount")){
            resultData.minggangcount = temp["minggangcount"].GetString();
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
    char* buf = const_cast<char*>(flag.GetString());
    postNotifyMessage(MSG_GAME_RESULT, buf);
}

void MsgHandler::handleCMPlayerHuNotify(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    PlayerCpgtData cpgData;
    cpgData.hu = 1;
    if(_mDoc.HasMember("angang")){
        const rapidjson::Value &angang = _mDoc["angang"];
        GangData gangData;
        gangData.gang = angang.GetString();
        gangData.flag = 1;
        cpgData.playerGang.push_back(gangData);
        cpgData.seatId = GAMEDATA::getInstance()->getHeroSeatId();
    }
    if(_mDoc.HasMember("penggang")){
        const rapidjson::Value &angang = _mDoc["penggang"];
        GangData gangData;
        gangData.gang = angang.GetString();
        gangData.flag = 2;
        cpgData.playerGang.push_back(gangData);
        cpgData.seatId = GAMEDATA::getInstance()->getHeroSeatId();
    }
    //    log("收到了服务端的胡牌协议1");
    postNotifyMessage(MSG_CM_GAME_HU_ACTION, &cpgData);
}

void MsgHandler::gameBDContinueResp(std::string msg){
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
    GAMEDATA::getInstance()->setShowDialogType(result.GetInt());
    GAMEDATA::getInstance()->setEnterRoomResp(resp);
    postNotifyMessage(MSG_HERO_CONTINUE_RESP, nullptr);
}

void MsgHandler::gameTuiGuangResp(std::string msg){
    //获取推广结果回复{code:1082,poxiaoId:poxiaoId,desc:"上方文字",content: [{nickname:"123",count:"1",money:"1"}]}
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    YongHuTuiGuang tuiGuang;
    const rapidjson::Value &text = _mDoc["desc"];
    tuiGuang.showText = text.GetString();
    if(_mDoc.HasMember("content")){
        const rapidjson::Value &content = _mDoc["content"];
        for(int i=0;i<content.Capacity();i++){
            TuiGuangData dat;
            const rapidjson::Value &temp =content[i];
            dat.count =temp["count"].GetString();
            dat.money =temp["money"].GetString();
            dat.name =temp["nickname"].GetString();
            dat.pic =temp["pic"].GetString();
            dat.total =temp["total"].GetString();
            tuiGuang.datas.push_back(dat);
        }
    }
    postNotifyMessage(MSG_PLAYER_LA_XIN_DATA, &tuiGuang);
}

void MsgHandler::handleHzPengResp(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    HeroCpgRespData cpgRespData;
    PlayerCpgtData playerCpg;
    if (_mDoc.HasMember("poker")){
        const rapidjson::Value &poker = _mDoc["poker"];
        playerCpg.poker = poker.GetString();
    }
    if (_mDoc.HasMember("seatId")){
        const rapidjson::Value &seatId = _mDoc["seatId"];
        playerCpg.seatId = seatId.GetInt();
    }
    if (_mDoc.HasMember("peng")){
        const rapidjson::Value &pengPoker = _mDoc["peng"];
        playerCpg.peng = pengPoker.GetString();
    }
    if (_mDoc.HasMember("sId")){
        const rapidjson::Value &sId = _mDoc["sId"];
        playerCpg.sId = sId.GetInt();
    }
    
    if (_mDoc.HasMember("ting1")){
        const rapidjson::Value &ting1 = _mDoc["ting1"];
        for(int i=0;i<ting1.Capacity();i++){
            HeroHuPaiData huPaiData;
            auto &temp = ting1[i];
            if(temp.HasMember("poker")){
                huPaiData.poker = temp["poker"].GetInt();
            }
            if(temp.HasMember("hu1")){
                const rapidjson::Value &data =  temp["hu1"];
                for (int i=0; i<data.Capacity(); i++) {
                    const rapidjson::Value &tem = data[i];
                    HuPokerData pd;
                    pd.poker = tem["hu"].GetString();
                    pd.num = tem["num"].GetString();
                    huPaiData.data.push_back(pd);
                }
            }
            playerCpg.heroHu.push_back(huPaiData);
        }
    }
    cpgRespData.playCpgt = playerCpg;
    postNotifyMessage(MSG_HZ_PLAYER_PENG_RESP, &cpgRespData);
}

void MsgHandler::handleSuZhouHuNotify(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    PlayerCpgtData cpgData;
    cpgData.hu = 1;
    if(_mDoc.HasMember("angang")){
        const rapidjson::Value &angang = _mDoc["angang"];
        GangData gangData;
        gangData.gang = angang.GetString();
        gangData.flag = 1;
        cpgData.playerGang.push_back(gangData);
        cpgData.seatId = GAMEDATA::getInstance()->getHeroSeatId();
    }
    if(_mDoc.HasMember("penggang")){
        const rapidjson::Value &angang = _mDoc["penggang"];
        GangData gangData;
        gangData.gang = angang.GetString();
        gangData.flag = 2;
        cpgData.playerGang.push_back(gangData);
        cpgData.seatId = GAMEDATA::getInstance()->getHeroSeatId();
    }
    postNotifyMessage(MSG_SZ_GAME_HU_ACTION, &cpgData);
}

void MsgHandler::handleFanPaiOpenRoom(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if(_mDoc.HasMember("poxiaoId")){
        const rapidjson::Value &poxiaoId = _mDoc["poxiaoId"];
        UserData::getInstance()->setPoxiaoId(poxiaoId.GetString());
    }
    if(_mDoc.HasMember("ifaa")){
        const rapidjson::Value &ifaa = _mDoc["ifaa"];
        GAMEDATA::getInstance()->setIsPayWayAA(strcmp(ifaa.GetString(), "1") == 0?true:false);
        UserData::getInstance()->setLatelyPayWayAA(strcmp(ifaa.GetString(), "1") == 0?true:false);
    }
    if(_mDoc.HasMember("umark")){
        const rapidjson::Value &umark = _mDoc["umark"];
        UserData::getInstance()->setMarkId(umark.GetString());
    }
    if(_mDoc.HasMember("difen")){
        const rapidjson::Value &difen = _mDoc["difen"];
        GAMEDATA::getInstance()->setFPDiFen(difen.GetString());
        UserData::getInstance()->setLatelyFPDiFen(difen.GetString());
    }
    if(_mDoc.HasMember("ifmq")){
        const rapidjson::Value &ifmq = _mDoc["ifmq"];
        GAMEDATA::getInstance()->setFPMenQing(ifmq.GetString());
        UserData::getInstance()->setLatelyFPMenQing(ifmq.GetString());
    }
    FriendOpenRoomRespData data;
    if(_mDoc.HasMember("dkf")){
        data.agency = true;
        AgencyRoomList roomList;
        const rapidjson::Value &agency = _mDoc["dkf"];
        for (int i=0; i<agency.Capacity(); i++){
            const rapidjson::Value &temp = agency[i];
            AgencyRoomData data;
            data.roomid = temp["prid"].GetString();
            data.gameInfo = temp["desc"].GetString();
            data.playername = temp["user"].GetString();
            data.createtime = temp["time"].GetString();
            data.type = temp["type"].GetString();
            if(temp.HasMember("rs"))
                data.rs = temp["rs"].GetString();
            if(temp.HasMember("js"))
                data.js = temp["js"].GetString();
            roomList.roomlist.push_back(data);
        }
        GAMEDATA::getInstance()->setAgencyRoomList(roomList);
    }else{
        data.agency = false;
    }
    if(_mDoc.HasMember("prjushu")){
        const rapidjson::Value &prjushu = _mDoc["prjushu"];
        data.prjushu = prjushu.GetString();
        UserData::getInstance()->setLatelyGameJuShu(prjushu.GetString());
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
    if(_mDoc.HasMember("size")){
        const rapidjson::Value &size = _mDoc["size"];
        GAMEDATA::getInstance()->setMyGameModel(atoi(size.GetString()));
        
    }
    
    PayPointInfo pointInfo;
    if(_mDoc.HasMember("point")){
        const rapidjson::Value &point = _mDoc["point"];
        pointInfo.point = point.GetString();
    }
    if(_mDoc.HasMember("wxfee")){
        const rapidjson::Value &fee = _mDoc["wxfee"];
        pointInfo.fee = fee.GetString();
    }
    if(_mDoc.HasMember("wxfangka")){
        const rapidjson::Value &fangka = _mDoc["wxfangka"];
        pointInfo.fangka = fangka.GetString();
    }
    if(_mDoc.HasMember("applefangka")){
        const rapidjson::Value &applefangka = _mDoc["applefangka"];
        pointInfo.applefangka = applefangka.GetString();
    }
    if(_mDoc.HasMember("applefee")){
        const rapidjson::Value &applefee = _mDoc["applefee"];
        pointInfo.applefee = applefee.GetString();
    }
    GAMEDATA::getInstance()->setPayPointInfo(pointInfo);
    
    const rapidjson::Value &result = _mDoc["result"];
    data.result = result.GetInt();
    GAMEDATA::getInstance()->clearPlayersInfo();
    GAMEDATA::getInstance()->setFriendOpenRoomResp(data);
    if (_mDoc.HasMember("other")){
        const rapidjson::Value &pArr = _mDoc["other"];
        for (int i = 0; i < pArr.Capacity(); ++i){
            const rapidjson::Value &temp = pArr[i];
            PlayerInfo* info = new PlayerInfo();
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
    PlayerInfo* info = new PlayerInfo();
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
    GAMEDATA::getInstance()->setGameType(7);
    UserData::getInstance()->setLatelyMahjongType(GameMahjongType::FanPai);
    postNotifyMessage(MSG_FP_FRIEND_OPEN_ROOM_RESP, nullptr);
}

void MsgHandler::handleFanPaiConnect(std::string msg){
    
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if(_mDoc.HasMember("poxiaoId")){
        const rapidjson::Value &poxiaoId = _mDoc["poxiaoId"];
        UserData::getInstance()->setPoxiaoId(poxiaoId.GetString());
    }
    if(_mDoc.HasMember("ifaa")){
        const rapidjson::Value &ifaa = _mDoc["ifaa"];
        GAMEDATA::getInstance()->setIsPayWayAA(strcmp(ifaa.GetString(), "1") == 0?true:false);
        UserData::getInstance()->setLatelyPayWayAA(strcmp(ifaa.GetString(), "1") == 0?true:false);
    }
    if(_mDoc.HasMember("size")){
        const rapidjson::Value &size = _mDoc["size"];
        GAMEDATA::getInstance()->setMyGameModel(atoi(size.GetString()));
    }
    if(_mDoc.HasMember("prize")){
        GAMEDATA::getInstance()->setCompetitionPride(_mDoc["prize"].GetString());
    }
    if(_mDoc.HasMember("umark")){
        const rapidjson::Value &umark = _mDoc["umark"];
        UserData::getInstance()->setMarkId(umark.GetString());
    }
    if(_mDoc.HasMember("dice")){
        const rapidjson::Value &dice = _mDoc["dice"];
        GAMEDATA::getInstance()->setMahjongDice(dice.GetString());
    }
    
    if(_mDoc.HasMember("difen")){
        const rapidjson::Value &difen = _mDoc["difen"];
        GAMEDATA::getInstance()->setFPDiFen(difen.GetString());
        UserData::getInstance()->setLatelyFPDiFen(difen.GetString());
    }
    if(_mDoc.HasMember("fanpai")){
        auto fan = _mDoc["fanpai"].GetString();
        GAMEDATA::getInstance()->setFanPaiPoker(fan);
    }
    if(_mDoc.HasMember("baida")){
        auto baida = _mDoc["baida"].GetString();
        GAMEDATA::getInstance()->setBaiDaPoker(baida);
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
    if(_mDoc.HasMember("ifmq")){
        const rapidjson::Value &ifmq = _mDoc["ifmq"];
        GAMEDATA::getInstance()->setFPMenQing(ifmq.GetString());
        UserData::getInstance()->setLatelyFPMenQing(ifmq.GetString());
    }
    GAMEDATA::getInstance()->setFriendOpenRoomResp(opdata);
    const rapidjson::Value &seatId = _mDoc["seatId"];
    const rapidjson::Value &rest = _mDoc["rest"];
    const rapidjson::Value &loard = _mDoc["lord"];
    const rapidjson::Value &isprivate = _mDoc["isprivate"];
    const rapidjson::Value &turn = _mDoc["turn"];
    if(_mDoc.HasMember("s")){
        GAMEDATA::getInstance()->setTurnHeroCpg(true);
    }
    GAMEDATA::getInstance()->setHeroSeatId(seatId.GetInt());
    //设置是否是私人房间
    std::string roomType = isprivate.GetString();
    GAMEDATA::getInstance()->setMahjongRoomType(roomType == "1" ? (MahjongRoom::privateRoom):(MahjongRoom::publicRoom));
    LastGameData lastGameData;
    lastGameData.result = 1;//游戏中
    lastGameData.seatId = seatId.GetInt();
    lastGameData.rest = rest.GetString();
    lastGameData.loard = loard.GetInt();
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
        data.hua = temp["hua"].GetString();
        data.tru = temp["tru"].GetInt();
        data.ifready = 1;
        data.isOnline = temp["isonline"].GetInt();
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
    GAMEDATA::getInstance()->setGameType(7);
    GAMEDATA::getInstance()->setLastGameDataBackup(lastGameData);
    char* buf = const_cast<char*>(StringUtil::itos(seatId.GetInt()).c_str());
    postNotifyMessage(MSG_PLAYER_FP_CONNECT_AGAIN, buf);
}


void MsgHandler::handleFanPaiEnterRoom(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if(_mDoc.HasMember("poxiaoId")){
        const rapidjson::Value &poxiaoId = _mDoc["poxiaoId"];
        UserData::getInstance()->setPoxiaoId(poxiaoId.GetString());
    }
    if(_mDoc.HasMember("size")){
        const rapidjson::Value &size = _mDoc["size"];
        GAMEDATA::getInstance()->setMyGameModel(atoi(size.GetString()));
        
    }
    if(_mDoc.HasMember("ifaa")){
        const rapidjson::Value &ifaa = _mDoc["ifaa"];
        GAMEDATA::getInstance()->setIsPayWayAA(strcmp(ifaa.GetString(), "1") == 0?true:false);
        UserData::getInstance()->setLatelyPayWayAA(strcmp(ifaa.GetString(), "1") == 0?true:false);
    }
    if(_mDoc.HasMember("difen")){
        const rapidjson::Value &difen = _mDoc["difen"];
        GAMEDATA::getInstance()->setFPDiFen(difen.GetString());
        UserData::getInstance()->setLatelyFPDiFen(difen.GetString());
    }
    if(_mDoc.HasMember("ifmq")){
        const rapidjson::Value &ifmq = _mDoc["ifmq"];
        GAMEDATA::getInstance()->setFPMenQing(ifmq.GetString());
        UserData::getInstance()->setLatelyFPMenQing(ifmq.GetString());
    }
    PayPointInfo pointInfo;
    if(_mDoc.HasMember("point")){
        const rapidjson::Value &point = _mDoc["point"];
        pointInfo.point = point.GetString();
    }
    if(_mDoc.HasMember("wxfee")){
        const rapidjson::Value &fee = _mDoc["wxfee"];
        pointInfo.fee = fee.GetString();
    }
    if(_mDoc.HasMember("wxfangka")){
        const rapidjson::Value &fangka = _mDoc["wxfangka"];
        pointInfo.fangka = fangka.GetString();
    }
    if(_mDoc.HasMember("applefangka")){
        const rapidjson::Value &applefangka = _mDoc["applefangka"];
        pointInfo.applefangka = applefangka.GetString();
    }
    if(_mDoc.HasMember("applefee")){
        const rapidjson::Value &applefee = _mDoc["applefee"];
        pointInfo.applefee = applefee.GetString();
    }
    GAMEDATA::getInstance()->setPayPointInfo(pointInfo);
    FriendOpenRoomRespData data = GAMEDATA::getInstance()->getFriendOpenRoomResp();
    const rapidjson::Value &result = _mDoc["result"];
    data.result = result.GetInt();
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
        UserData::getInstance()->setLatelyGameJuShu(prjushu.GetString());
    }
    if(_mDoc.HasMember("prjucount")){
        const rapidjson::Value &prjucount = _mDoc["prjucount"];
        data.prjucount = StringUtils::format("%d",atoi(prjucount.GetString())+1);
    }
    if(_mDoc.HasMember("jifen")){
        const rapidjson::Value &myjifen = _mDoc["jifen"];
        GAMEDATA::getInstance()->setScore(myjifen.GetInt());
    }
    if(_mDoc.HasMember("prize")){
        GAMEDATA::getInstance()->setCompetitionPride(_mDoc["prize"].GetString());
    }
    
    GAMEDATA::getInstance()->clearPlayersInfo();
    GAMEDATA::getInstance()->setFriendOpenRoomResp(data);
    if (_mDoc.HasMember("other")){
        const rapidjson::Value &pArr = _mDoc["other"];
        for (int i = 0; i < pArr.Capacity(); ++i){
            const rapidjson::Value &temp = pArr[i];
            PlayerInfo* info = new PlayerInfo();
            info->setScore(temp["jifen"].GetInt());
            info->setSeatId(temp["seatId"].GetInt());
            info->setPoxiaoId(temp["poxiaoId"].GetString());
            info->setBanker(false);
            info->setIsReady(temp["ifready"].GetInt() == 0 ? false : true);
            info->setGold(temp["gold"].GetInt());
            info->setTicket(temp["lequan"].GetInt());
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
    PlayerInfo* info = new PlayerInfo();
    info->setScore(GAMEDATA::getInstance()->getScore());
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
    
    GAMEDATA::getInstance()->addPlayersInfo(info);
    GAMEDATA::getInstance()->setIsPlaying(false);
    GAMEDATA::getInstance()->setGameType(7);
    UserData::getInstance()->setLatelyMahjongType(GameMahjongType::FanPai);
    postNotifyMessage(MSG_FP_ENTER_FRIEND_ROOM_RESP, nullptr);
}

void MsgHandler::handleFPFapaiNotify(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if(_mDoc.HasMember("seatId")){
        GAMEDATA::getInstance()->setHeroSeatId(atoi(_mDoc["seatId"].GetString()));
    }
    MahjongFaPaiData faPaiData;
    faPaiData.heroPokers = _mDoc["poker"].GetString();
    if(_mDoc.HasMember("hua")){
        const rapidjson::Value &huama = _mDoc["hua"];
        for (int i=0; i<huama.Capacity(); i++) {
            const rapidjson::Value &temp = huama[i];
            HuaData data;
            data.hua = temp["hua"].GetString();
            data.setaId = temp["seatId"].GetString();
            data.poxiaoId = temp["poxiaoId"].GetString();
            faPaiData.huas.push_back(data);
        }
    }
    faPaiData.dice = _mDoc["dice"].GetString();
    faPaiData.start = _mDoc["start"].GetInt();
    if(_mDoc.HasMember("prjucount")){
        faPaiData.prjucount = _mDoc["prjucount"].GetInt();
    }
    if(_mDoc.HasMember("fanpai")){
        auto fan = _mDoc["fanpai"].GetString();
        GAMEDATA::getInstance()->setFanPaiPoker(fan);
    }
    if(_mDoc.HasMember("baida")){
        auto baida = _mDoc["baida"].GetString();
        GAMEDATA::getInstance()->setBaiDaPoker(baida);
    }
    const rapidjson::Value &rest = _mDoc["rest"];
    faPaiData.rest = rest.GetString();
    PlayerCpgtData tingData;
    if(_mDoc.HasMember("angang")){
        faPaiData.hasGang = true;
        const rapidjson::Value &angang = _mDoc["angang"];
        GangData gangData;
        gangData.gang = angang.GetString();
        gangData.flag = 1;
        tingData.playerGang.push_back(gangData);
        tingData.seatId = GAMEDATA::getInstance()->getHeroSeatId();
    }
    if(_mDoc.HasMember("hu")){
        tingData.hu =  1;
    }else{
        tingData.hu =  0;
    }
    if (_mDoc.HasMember("ting1")){
        const rapidjson::Value &ting1 = _mDoc["ting1"];
        for(int i=0;i<ting1.Capacity();i++){
            HeroHuPaiData huPaiData;
            auto &temp = ting1[i];
            if(temp.HasMember("poker")){
                huPaiData.poker = temp["poker"].GetInt();
            }
            if(temp.HasMember("hu1")){
                const rapidjson::Value &data =  temp["hu1"];
                for (int i=0; i<data.Capacity(); i++) {
                    const rapidjson::Value &tem = data[i];
                    HuPokerData pd;
                    pd.poker = tem["hu"].GetString();
                    pd.num = tem["num"].GetString();
                    huPaiData.data.push_back(pd);
                }
            }
            tingData.heroHu.push_back(huPaiData);
        }
    }
    faPaiData.mjHuData = tingData;
    GAMEDATA::getInstance()->setIsTrusteeship(false);
    GAMEDATA::getInstance()->setMahjongFaPaiData(faPaiData);
    postNotifyMessage(MSG_GAME_FP_START_FAPAI_NOTIFY, nullptr);
}

void MsgHandler::fpNextPlayer(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    PlayerTurnData playerTurnData;
    playerTurnData.seatId = _mDoc["seatId"].GetInt();
    if (_mDoc.HasMember("poker")){
        const rapidjson::Value &poker = _mDoc["poker"];
        playerTurnData.poker = atoi(poker.GetString());
    }
    const rapidjson::Value &rest = _mDoc["rest"];
    playerTurnData.rest = rest.GetString();
    if (_mDoc.HasMember("num")){
        const rapidjson::Value &num = _mDoc["num"];
        playerTurnData.handNum = num.GetInt();
    }
    PlayerCpgtData tingData;
    tingData.seatId = _mDoc["seatId"].GetInt();
    if (_mDoc.HasMember("angang")){
        const rapidjson::Value &angang = _mDoc["angang"];
        GangData gangData;
        gangData.gang = angang.GetString();
        gangData.flag = 1;
        tingData.playerGang.push_back(gangData);
    }
    if (_mDoc.HasMember("penggang")){
        const rapidjson::Value &penggang = _mDoc["penggang"];
        GangData gangData;
        gangData.gang = penggang.GetString();
        gangData.flag = 2;
        tingData.playerGang.push_back(gangData);
    }
    if(_mDoc.HasMember("hu")){
        tingData.hu = 1;//红中麻将可胡
    }else{
        tingData.hu = 0;
    }
    if (_mDoc.HasMember("ting") || _mDoc.HasMember("angang") || _mDoc.HasMember("penggang")||_mDoc.HasMember("hu")){
        playerTurnData.hastinggang = true;
    }
    if (_mDoc.HasMember("ting1")){
        const rapidjson::Value &ting1 = _mDoc["ting1"];
        for(int i=0;i<ting1.Capacity();i++){
            HeroHuPaiData huPaiData;
            auto &temp = ting1[i];
            if(temp.HasMember("poker")){
                huPaiData.poker = temp["poker"].GetInt();
            }
            if(temp.HasMember("hu1")){
                const rapidjson::Value &data =  temp["hu1"];
                for (int i=0; i<data.Capacity(); i++) {
                    const rapidjson::Value &tem = data[i];
                    HuPokerData pd;
                    pd.poker = tem["hu"].GetString();
                    pd.num = tem["num"].GetString();
                    huPaiData.data.push_back(pd);
                }
            }
            tingData.heroHu.push_back(huPaiData);
        }
    }
    playerTurnData.cpgData = tingData;
    postNotifyMessage(MSG_FP_PLAYER_TURN_WHO, &playerTurnData);
}

void MsgHandler::manageAgencyResp(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    if(_mDoc.HasMember("dkc")){
        //区分可以操作的房间和不可操作的房间
        AgencyRoomList roomList;
        AgencyRecordList recordList;
        const rapidjson::Value &flag = _mDoc["flag"];
        const rapidjson::Value &agency = _mDoc["dkc"];
        if(strcmp(flag.GetString(),"0") == 0){
            for (int i=0; i<agency.Capacity(); i++){
                const rapidjson::Value &temp = agency[i];
                AgencyRoomData data;
                data.roomid = temp["prid"].GetString();
                data.gameInfo = temp["desc"].GetString();
                data.playername = temp["user"].GetString();
                data.createtime = temp["time"].GetString();
                data.type = temp["type"].GetString();
                if(temp.HasMember("rs"))
                    data.rs = temp["rs"].GetString();
                if(temp.HasMember("js"))
                    data.js = temp["js"].GetString();
                roomList.roomlist.push_back(data);
            }
            GAMEDATA::getInstance()->setAgencyRoomList(roomList);
        }else{
            for (int i=0; i<agency.Capacity(); i++){
                const rapidjson::Value &temp = agency[i];
                AgencyRecordData rdata;
                rdata.roomid = temp["prid"].GetString();
                rdata.gameInfo = temp["desc"].GetString();
                rdata.playername = temp["user"].GetString();
                rdata.createtime = temp["time"].GetString();
                rdata.type = temp["type"].GetString();
                rdata.progress = temp["ratio"].GetString();
                recordList.roomlist.push_back(rdata);
            }
            GAMEDATA::getInstance()->setAgencyRecordList(recordList);
        }
        postNotifyMessage(MSG_AGENCY_LIST, nullptr);
    }
}

void MsgHandler::agencyBillResp(std::string msg){
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
            data.gameType = temp["t"].GetString();
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
    postNotifyMessage(DAIKAI_FRIEND_GAME_BILL_REQUEST, nullptr);
}

void MsgHandler::playerIPCheckNotify(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    IPConflictData conflict;
    if (_mDoc.HasMember("ip")){
        const rapidjson::Value &ip = _mDoc["ip"];
        for (int i=0; i<ip.Capacity(); i++) {
            const rapidjson::Value &temp = ip[i];
            conflict.conflict.push_back(temp.GetString());
        }
    }
    if (_mDoc.HasMember("ip1")){
        const rapidjson::Value &ip1 = _mDoc["ip1"];
        conflict.IP1 = ip1.GetString();
    }else{
        conflict.IP1 = "";
    }
    if(_mDoc.HasMember("line")){
        const rapidjson::Value &line = _mDoc["line"];
        conflict.line = line.GetString();
    }else{
        conflict.line = "";
    }
    GAMEDATA::getInstance()->setIPConflictData(conflict);
    postNotifyMessage(MSG_IP_CONFLICT, nullptr);
}

void MsgHandler::agencyResultResp(std::string msg){
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    AgencyResultList list;
    if(_mDoc.HasMember("time")){
         const rapidjson::Value &time = _mDoc["time"];
         list.time = time.GetString();
    }
    if(_mDoc.HasMember("bill")){
        const rapidjson::Value &bill = _mDoc["bill"];
        for (int i=0; i<bill.Capacity(); i++) {
            AgencyResultData res;
            const rapidjson::Value &temp = bill[i];
            res.name = temp["nickname"].GetString();
            res.count = temp["count"].GetString();
            res.fangka = temp["fangka"].GetString();
            list.results.push_back(res);
        }
    }
    GAMEDATA::getInstance()->setAgencyResultList(list);
    postNotifyMessage(MSG_RESULT_MSG, nullptr);
}
