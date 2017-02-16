#ifndef _GAMEDATA_H_
#define _GAMEDATA_H_
#include "cocos2d.h"
#include "mahjong/player/playerinfo/Player.h"
#include "mahjong/state/DataStruct.h"
USING_NS_CC;



class GAMEDATA{
public:
    static GAMEDATA* getInstance();
    
    vector<Player*> getPlayersInfo();
    void addPlayersInfo(Player* players);
    void erasePlayersInfo(std::string poxiaoId);
    void clearPlayersInfo();
    
    std::vector<std::string> getHeroJongs();
    void setHeroJongs(std::vector<std::string> heroJongs);
    
    vector<GameResultData> getGameResults();
    void setGameResults(vector<GameResultData> result);
    
    FriendListData sortFriendList(FriendListData data);
    //服务端返回数据结构体
    CC_SYNTHESIZE(EnterRoomResp, enterRoomResp, EnterRoomResp);
//    CC_SYNTHESIZE(OtherPlayedJong, otherPlayJong, OtherPlayJong);
    CC_SYNTHESIZE(PlayerCpgtData, playerCpgtData, PlayerCpgt);
    CC_SYNTHESIZE(PlayerTurnData, playerTurnData, PlayerTurn);
    CC_SYNTHESIZE(LastGameData, lastGameData, LastGameDataBackup);
    CC_SYNTHESIZE(RoomListData, roomListData, RoomList);
    CC_SYNTHESIZE(HeroCpgRespData, heroCpgRespData, HeroCpgResp);
    CC_SYNTHESIZE(FriendListData, friendListData, FriendList);
    CC_SYNTHESIZE(FriendSearchData, friendSearchData, FriendSearch);
    CC_SYNTHESIZE(FriendInfo, friendInfo, FriendInfoData);
    CC_SYNTHESIZE(RemovePlayerData, removePlayerData, RemovePlayer);
    CC_SYNTHESIZE(FriendOpenRoomRespData, friendOpenRoomRespData, FriendOpenRoomResp);
    CC_SYNTHESIZE(FriendOpenRoomNotifyData, friendOpenRoomNotifyData, FriendOpenRoomNotify);
    CC_SYNTHESIZE(ReplaceJongVec, replaceJongVecData, ReplaceJongVec);
    CC_SYNTHESIZE(BillInfoAll, billInfoAllData,BillInfoAll);
    CC_SYNTHESIZE(BillInfoData, billInfoData, BillInfoData)
    CC_SYNTHESIZE(BillInfoDetailAll, billInfoDetailAll, BillInfoDetailAll);
    CC_SYNTHESIZE(DailyTaskData, dailyTaskData, DailyTaskInfo);
    CC_SYNTHESIZE(DailySignData, dailySignData, DailySignData);
    CC_SYNTHESIZE(TodaySignData, todaySignData, TodaySignData);
    CC_SYNTHESIZE(WelfareData, welfareData, WelfareData);
    CC_SYNTHESIZE(WelfareBZ, welfareBZ, WelfareBZ);
    CC_SYNTHESIZE(WelfareGold, welfareGold, WelfareGold);
    CC_SYNTHESIZE(DailyPrideData, dailyPrideData, DailyPrideData);
    CC_SYNTHESIZE(TodayPrideData, todayPrideData, TodayPrideData);
    CC_SYNTHESIZE(BoundPhoneData, boundPhoneData, BoundPhoneData);
    CC_SYNTHESIZE(FirstChargeData, firstChargeData, FirstChargeData);
    CC_SYNTHESIZE(GoldChangeList, goldChangeList, GoldChangeList);
    CC_SYNTHESIZE(FangkaChargeList, fangkaChargeList, FangkaChargeList);
    CC_SYNTHESIZE(LequanChangeList, lequanChangeList, LequanChangeList);
    CC_SYNTHESIZE(LequanChangeResult, lequanChangeResult, LequanChangeResult);
    CC_SYNTHESIZE(RedWalletRespData, redWalletRespData, RedWalletRespData);
    CC_SYNTHESIZE(ReciveRedWallet, reciveRedWallet, ReciveRedWallet);
    CC_SYNTHESIZE(LoginAccPwd, loginAccPwd, LoginAccPwd);
    CC_SYNTHESIZE(MahjongRoom, mahjongRoomType, MahjongRoomType);
    CC_SYNTHESIZE(MahjongState, mahjongState, MahjongState);
    CC_SYNTHESIZE(LeChangeRecord, leChangeRecord, LeChangeRecord);
    CC_SYNTHESIZE(InviteRespData, inviteRespData, InviteRespData);
    CC_SYNTHESIZE(ActivityRankList, activityRankList, ActivityRankList);
    CC_SYNTHESIZE(ActivityTime, activityTime, ActivityTime);
    CC_SYNTHESIZE(ActivityPrideList, activityPrideList, ActivityPrideList);
    CC_SYNTHESIZE(DissolveData, dissolveData, DissolveData);
    CC_SYNTHESIZE(ChatData, chatData, ChatData);
    CC_SYNTHESIZE(RoomChatMsgList, roomChatMsgList, RoomChatMsgList);
    CC_SYNTHESIZE(FriendChatMsgList, friendChatMsgList, FriendChatMsgList);
    CC_SYNTHESIZE(PlayerCpgRecShow, playerCpgRecShow, PlayerCpgRecShow);
    CC_SYNTHESIZE(PlayBackInfo, PlaybackInfo, PlaybackInfo);
    CC_SYNTHESIZE(FupanGameData, fupanGameData, FupanGameData);
    //游戏状态
    CC_SYNTHESIZE(int, heroSeatId, HeroSeatId);
    CC_SYNTHESIZE(int, currentBank, CurrentBank);
    CC_SYNTHESIZE(int, currentTingSeatId, CurrentTingSeatId);
    CC_SYNTHESIZE(int, currentSelectRoomId, CurrentSelectRoomId);
    CC_SYNTHESIZE(int, playRoomID, PlayRoomID);
    CC_SYNTHESIZE(int, reliveNumber, ReliveNumber);
    CC_SYNTHESIZE(bool, isSelected, IsSelected);
    CC_SYNTHESIZE(bool, continueAgain, ContinueAgain);
    CC_SYNTHESIZE(bool, isPlaying, IsPlaying);
    CC_SYNTHESIZE(bool, updatePlayer, UpdatePlayer);
    CC_SYNTHESIZE(bool, replaceFlower, ReplaceFlower);
    CC_SYNTHESIZE(bool, otherPlayed, OtherPlayed);
    CC_SYNTHESIZE(bool, heroturn, Heroturn);
    CC_SYNTHESIZE(bool, isTingProcess, IsTingProcess);
    CC_SYNTHESIZE(bool, isTingState, IsTingState);
    CC_SYNTHESIZE(bool, isTrusteeship, IsTrusteeship);
    CC_SYNTHESIZE(bool, isRecover, IsRecover);
    CC_SYNTHESIZE(bool, needAddPlayer,NeedAddPlayer);
    CC_SYNTHESIZE(bool, isLiuJu, IsLiuJu);
    CC_SYNTHESIZE(bool, needShowLastResult, NeedShowLastResult);
    CC_SYNTHESIZE(bool, isGotoLobby, IsGotoLobby);
    CC_SYNTHESIZE(bool, isInPay, IsInPay);
    CC_SYNTHESIZE(bool, isInGameScene, IsInGameScene);
    CC_SYNTHESIZE(int, showDialogType, ShowDialogType);
    CC_SYNTHESIZE(int, score, Score);
    CC_SYNTHESIZE(int, wanJiaQunVer, WanJiaQunVer);
    CC_SYNTHESIZE(int, dailiQunVer, DailiQunVer);
    CC_SYNTHESIZE(bool, waitNetwork, WaitNetwork);//网络状态
    CC_SYNTHESIZE(bool, haveShowNotice, HaveShowNotice);//是否展示过推广
    CC_SYNTHESIZE(bool, showFangZhuDismiss, ShowFangZhuDismiss);//是否房主解散了房间
    CC_SYNTHESIZE(bool, startPaiAngang, StartPaiAngang);
    CC_SYNTHESIZE(bool, startFaPai, StartFaPai);//是否开始发牌
    CC_SYNTHESIZE(bool, isFuPan, IsFuPan);//是否开始发牌
    CC_SYNTHESIZE(bool, showDissolveDialog, ShowDissolveDialog);
    CC_SYNTHESIZE(string, privateGameNum, PrivateGameNum);//私人房间游戏局数
    CC_SYNTHESIZE(string, ip, IP);//玩家IP
    CC_SYNTHESIZE(string, dice, Dice);
    CC_SYNTHESIZE(string, kaibao, Kaibao);
    CC_SYNTHESIZE(string, huangfan, Huangfan);
    CC_SYNTHESIZE(string, diaopao, Diaopao);
    CC_SYNTHESIZE(string, fangZhuId, FangZhuId);
    CC_SYNTHESIZE(string, privateRoomType, PrivateRoomType);
    CC_SYNTHESIZE(string, fee, Fee);
    CC_SYNTHESIZE(string, privateLezi, PrivateLezi);
    CC_SYNTHESIZE(string, privateKaibao, PrivateKaibao);
    CC_SYNTHESIZE(string, privateEmsc, PrivateEmsc);
    CC_SYNTHESIZE(string, noticeUrl, NoticeUrl);
    CC_SYNTHESIZE(string, dissolveName, DissolveName);
    CC_SYNTHESIZE(string, hsman, Hsman);
    CC_SYNTHESIZE(string, hstype, Hstype);
    CC_SYNTHESIZE(string, imsi, Imsi);
    CC_SYNTHESIZE(string, imei, Imei);
    CC_SYNTHESIZE(string, appVer, AppVer);
private:
    GAMEDATA();
    void init();
    std::mutex m_mutex;
    static GAMEDATA* _instance;
    std::vector<Player*> playerVector;
    std::vector<GameResultData> gameResults;
    std::vector<std::string> heroJongs;
    std::vector<PlayerCpgRecord> heroCpgRecord;
};

#endif
