#ifndef __DATA_STRUCT_H__
#define __DATA_STRUCT_H__
#include "cocos2d.h"
#include "game/mahjong/jong/Jong.h"
USING_NS_CC;

struct EnterRoomResp{
    std::string result;
    std::string rsid;
};

struct ReplaceJong
{
    int seatId;
    std::vector<std::string> poker;
    std::vector<std::string> replace;
};

struct ReplaceJongVec{
    std::string rest;
    std::vector<ReplaceJong> times;
};

struct OtherPlayedJong
{
    int poker;
    int seatId;
};

struct PlayerTurnData
{
    int seatId;
    int poker;
    std::string rest;
    std::string replace;
};

struct PlayerCpgtData
{
    int seatId;
    int sId;
    int flag;
    std::string ting;
    std::string poker;
    std::vector<std::string> chi;
    std::string peng;
    std::string gang;
};

struct GameResultData
{
    int result;//0打酱油,1自摸,3胡牌,2点炮
    int seatId;
    int gold;
    int diamond;
    int jifen;
    int lequan;
    int golddelta;
    int diamonddelta;
    int jifendelta;
    int lequandelta;
    int hua;
    std::string nickName;
    std::string huType;
    std::string showPoker;
};

struct PlayerCpgRecord
{
    int pengDir;//碰牌方向
    int type;
    Vector<Jong*> pokersRecord;
};

struct HeroCpgRespData{
    int result;
    std::string ting;
};


struct PlayerChiData{
    std::string chi;
    std::string poker;
};

struct PlayerPengData{
    std::string peng;
    std::string peId;
};

struct PlayerGangData{
    std::string gang;
    std::string gaId;
};

struct PlayerGameData{
    int seatId;
    int gold;
    int diamond;
    int jifen;
    int lequan;
    int hua;
    int status;
    vector<PlayerChiData> chiData;
    vector<PlayerPengData> pengData;
    vector<PlayerGangData> gangData;
    std::string angang;
    std::string outhand;
    std::string nickname;
    std::string money;
    std::string hand;
    std::string pic;
};

struct LastGameData
{
    int seatId;
    int loard;
    bool isprivate;
    std::string rest;
    std::string hand;
    std::vector <PlayerGameData> players;
};

struct RoomListData
{
    std::vector <int> rooms;
};


struct FriendInfo{
    std::string poxiaoId;
    std::string image;
    std::string nickname;
    int diamond;
    int lockDiamond;
    int gold;
    int lequan;
    bool isOnLine;
};

struct FriendListData{
    std::vector<FriendInfo> friends;
};

struct FriendSearchData{
    std::vector<FriendInfo> friends;
};

struct RemovePlayerData{
    int setaId;
    std::string pid;
};

struct FriendOpenRoomRespData{
    int seatId;
    int result;
};

struct FriendOpenRoomNotifyData{
    std::string nickname;
    std::string pid;
};

struct BillContent{
    std::string nickName;
    std::string score;
};

struct BillInfoData{
    std::string date;
    std::string billId;
    std::vector<BillContent> content;
};


struct BillInfoAll{
    bool needInit = true;
    std::vector<BillInfoData> bills;
};

struct BillInfoDetail
{
    std::vector<BillContent> detail;
};

struct BillInfoDetailAll
{
    bool needInit = true;
    std::vector<BillInfoDetail> detail;
};

struct DailyTaskData{
    std::string task1;
    std::string task2;
    std::string task3;
    std::string task4;
    std::string extra;
};

enum PrideType{
    gold,
    lequan,
   	lockDiammond,
    diamond
};

struct PrideData{
    PrideType type;
    int number;
};

struct DailySignData{
    std::string day;
    std::vector<PrideData> pride;
    std::string result;
};

struct TodaySignData{
    std::string day;
    std::vector<PrideData> pride;
};

struct WelfareData{
    bool needInit;
    std::string jjj_count;
    std::string jjj_used;
    std::string jjj_gold;
    std::string jjj_result;
    std::string wx_result;
    std::string wx_gold;
    std::string wx_bangzuan;
    std::string bzjjj_count;
    std::string bzjjj_used;
    std::string bzjjj_bangzuan;
    std::string bzjjj_result;
    std::string mobile_result;
    std::string mobile_gold;
};


struct WelfareBZ{
    string result;
    string bangzuan;
};

struct WelfareGold{
    string result;
    string gold;
};


struct DailyPrideData{
    string needGold;
    string result;
    string count;
    string max;
    vector<PrideData> prides;
};

struct TodayPrideData{
    string result;
    PrideData pride;
};

struct BoundPhoneData{
    int result;
    string phoneNum;
};


struct FirstChargeData{
    bool needInit;
    int gold;
    int diamond;
    int lequan;
    int lockDiamond;
};

struct GoldChange{
    int gold;
    int diamond;
};

struct GoldChangeList{
    bool needInit;
    vector<GoldChange> list;
};

struct DiamondChange{
    int money;
    int diamond;
};

struct DiamondChangeList{
    bool needInit;
    vector<DiamondChange> list;
};

struct LequanChange{
    std::string propId;
    std::string propPrice;
    std::string propName;
};

struct LequanChangeList{
    bool needInit;
    vector<LequanChange> list;
};

struct LequanChangeResult{
    std::string result;
    int  lequan;
};

struct RedShareFriend{
    std::string pId;
    std::string nickname;
    std::string status;
};

struct RedWalletRespData{
    bool needInit;
    std::string hbcode;
    std::string lequan;
    std::string gold;
    std::string diamond;
    std::string count;
    std::string lequan2;
    std::string gold2;
    std::string diamond2;
    vector<RedShareFriend> friends;
};

struct ReciveRedWallet{
    std::string result;
    std::string gold;
    std::string lequan;
    std::string diamond;
    std::string bangzuan;
};



enum CpgType
{
    chi,
    peng,
    gang,
    angang,
    penggang,
    ting
};

enum HuType{
    kaibao  = 1,
    huangfan,
    gangkai,
    mengqing,
    hunpeng,
    qingpeng,
    dadiaoche,
    qingyise,
    hunyise,
    pengpenghu,
    lajihu
};



#endif
