#ifndef __DATA_STRUCT_H__
#define __DATA_STRUCT_H__
#include "cocos2d.h"
#include "json/document.h"
#include "json/rapidjson.h"
#include "mahjong/common/jong/Jong.h"
USING_NS_CC;

enum MahjongRoom{
    publicRoom,
    privateRoom
};

enum PrideType{
    gold,
    lequan,
   	lockDiammond,
    fangka
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

enum LeziType{
    type1100 = 0,// 1/1 无勒子
    type1120,// 1/1 20勒子
    type1150,// 1/1 50勒子
    type2200,// 2/2 无勒子
    type2240,// 2/2 40勒子
    type22100 // 2/2 100勒子
};

enum CompetitionRoomId{
    Competition_Error,
    Shanghai_Normal,
    Shanghai_High,
    Hongzhong_Normal,
    Hongzhong_High,
};

//麻将游戏状态
enum MahjongState{
    heroChi,//吃牌
    heroPeng,//碰牌
    heroGang,//杠牌
    heroPreTing,//预备听（玩家点击听牌）
    heroTing,//听牌
    readyGo,//已准备
    playing,//游戏中
    continueAgain//断线续玩
};

struct PlayerReady{
    int ifready;
    int seatId;
    std::string poxiaoId;
};

struct EnterRoomResp{
    std::string result;
    std::string rsid;
    std::string kb;
    std::string huangfan;
    std::string money;
    std::string gold;
    std::string payid;
    std::string min;
    std::vector<PlayerReady> playerReadys;
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

struct HeroHuPaiData{
    int poker;
    std::string hu;
};

struct GangData{
    int flag;//0明杠，1暗杠，2碰杠
    std::string gang;
};

struct PlayerCpgtData
{
    int seatId;
    int sId;
    int hu;
    std::string ting;
    std::string poker;
    std::string chi[3];
    std::string peng;
    std::vector<GangData> playerGang;
    std::vector<HeroHuPaiData> heroHu;
};

struct HeroCpgRespData{
    int result;
    std::string forbit;
    PlayerCpgtData playCpgt;
};

struct PlayerTurnData
{
    int seatId;
    int poker;
    int handNum;
    std::string rest;
    std::string replace;
    bool hastinggang = false;
    PlayerCpgtData cpgData;
};

struct CompetitionResultInfo{
    std::string matchid;
    std::string pride;
    std::string paiming;
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
    int bangzuan;
    int bangzuandelta;
    int hua;
    std::string gangfen;
    std::string lz;
    std::string win;
    std::string lost;
    std::string even;
    std::string fan;
    std::string umark;
    std::string pic;
    std::string nickName;
    std::string huType;
    std::string showPoker;
    std::string poxiaoId;
};

struct PlayerCpgRecord
{
    int pengDir;//碰牌方向
    int type;//吃碰杠类型
    int gangValue;//杠的值
    bool anGangFan = false;
    Vector<Jong*> pokersRecord;
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
    int bangzuan;
    int fangka;
    int gender;
    int lequan;
    int hua;
    int status;
    int tru;
    int isOnline;
    int ifready;
    std::vector<PlayerChiData> chiData;
    std::vector<PlayerPengData> pengData;
    std::vector<PlayerGangData> gangData;
    std::string angang;
    std::string outhand;
    std::string nickname;
    std::string money;
    std::string hand;
    std::string lastpoker;
    std::string pic;
    std::string poxiaoId;
    std::string umark;
    std::string ip;
};

struct LastGameData
{
    int result;
    int seatId;
    int pre;
    int loard;
    int kb;
    int hf;
    int turn;
    MahjongRoom roomType;
    std::string rest;
    std::string hand;
    std::vector <PlayerGameData> players;
};

struct RoomData{
    int roomId;
    int maxGold;
    int minGold;
    int base;
    int hua;
};

struct CompetitionRoom{
    std::string name;
    std::string fangka;
    std::string roomId;
    std::string prize;
    std::string rule;
};

struct RoomListData
{
    std::vector <RoomData> rooms;
    std::vector <CompetitionRoom> matchList;
};





struct FriendInfo{
    std::string poxiaoId;
    std::string image;
    std::string nickname;
    std::string pic;
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
    std::string kb;
    std::string huangfan;
    std::string prjushu;
    std::string prjucount;
    std::string prid;
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
    std::string gameType;
    std::string date;
    std::string billId;
    std::string prid;
    std::string atype;
    std::vector<BillContent> content;
};


struct BillInfoAll{
    bool needInit = true;
    std::vector<BillInfoData> bills;
};

struct BillInfoDetail
{
    std::vector<BillContent> detail;
    std::string recordId;
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
    std::string result;
    std::string bangzuan;
};

struct WelfareGold{
    std::string result;
    std::string gold;
};


struct DailyPrideData{
    std::string needGold;
    std::string result;
    std::string count;
    std::string max;
    std::vector<PrideData> prides;
};

struct TodayPrideData{
    std::string result;
    PrideData pride;
    int rest;
};

struct BoundPhoneData{
    int result;
    std::string phoneNum;
};


struct FirstChargeData{
    bool needInit;
    int gold;
    int money;
    int fangka;
};

struct GoldChange{
    int gold;
    int diamond;
    int fangka;
};

struct GoldChangeList{
    bool needInit;
    std::vector<GoldChange> list;
};

struct FangkaCharge{
    int money;
    int fangka;
    int payId;
};

struct FangkaChargeList{
    bool needInit;
    std::vector<FangkaCharge> list;
};

struct LequanChange{
    std::string propId;
    std::string propPrice;
    std::string propName;
    std::string propType;
    std::string url;
};

struct LequanChangeList{
    bool needInit;
    std::vector<LequanChange> list;
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
    std::vector<RedShareFriend> friends;
};

struct ReciveRedWallet{
    std::string result;
    std::string gold;
    std::string lequan;
    std::string diamond;
    std::string bangzuan;
};

struct LoginAccPwd{
    std::string account;
    std::string password;
};

struct LeRecord{
    std::string propId;
    std::string state;
};

struct LeChangeRecord{
    std::vector<LeRecord> records;
};

struct PlayerResumeData{
    int seatId;
    int hua;
    int status;
    int tru;
    int isOnline;
    std::string angang;
    std::string outhand;
    std::string hand;
    std::string lastpoker;
    std::vector<PlayerChiData> chiData;
    std::vector<PlayerPengData> pengData;
    std::vector<PlayerGangData> gangData;
};

struct GameResumeData
{
    int kb;
    int hf;
    int turn;
    std::string rest;
    std::vector <PlayerResumeData> players;
};

struct ChatData{
    std::string nickname;
    std::string content;
    std::string poxiaoId;
    bool mark;
    bool isRead;
};

struct RoomChatMsgList{
    std::vector<ChatData> msgList;
};

struct FriendChatData{
    std::string poxiaoId;
    std::vector<ChatData> msgList;
};

struct FriendChatMsgList{
    std::vector<FriendChatData> friendMsgList;
};

struct InviteRespData{
    std::string nickname;
    std::string result;
};

struct ActivityRank{
    std::string nickname;
    std::string lequan;
};

struct ActivityRankList{
    std::vector<ActivityRank> rank;
    std::string weekName;
    std::string weekLequan;
};

struct ActivityTime{
    std::string start;
    std::string end;
};

struct ActivityPride{
    int rid;
    std::string pid;
    std::string status;
    std::string name;
};

struct ActivityPrideList{
    std::vector<ActivityPride> prideList;
};

struct DissolveData{
    std::string pid;
    std::string agree;
};

struct CpgPokerRec{
    int clientseatid;
    std::vector<std::vector<int>> cpg;
};

struct PlayerCpgRecShow{
    std::vector<CpgPokerRec> playercpg;
};


struct PlayBackInfo{
    int result;
    std::string gameType;
    std::string heroid;
    std::vector<std::string> playBackInfo;
};

struct FupanGameData
{
    std::vector <PlayerGameData> players;
};

struct PlayerMingpai{
    bool  isTing = false;
    int seatId;
    int hua;
    Vector<Jong*> playerHandJongs;//玩家手牌
    Vector<Jong*> playerPlayedJongs;
    std::vector<PlayerCpgRecord>  playerCpgRecords;//玩家吃碰杠记录
};

struct PlayMingpaiRecord{
    std::vector<PlayerMingpai> record;//4个玩家的牌
    int step;
};

struct TuiGuangReward{
    int gold;
    int fangka;
};

struct TuiGuangPride{
    int gold;
    int fangka;
};

struct TuiGuangRecord{
    int gold;
    int fangka;
};

struct MahjongFaPaiData{
    int start;
    int prjucount;
    std::string heroPokers;
    std::string kaibao;
    std::string huangfan;
    std::string dice;
    std::string ting;
    std::string gang;
    std::string matchId;
    ReplaceJongVec  mjReplaceVec;
    PlayerCpgtData mjTingData;
};

struct GameActivityData{
    std::string imageUrl;
    std::string showTime;
    std::string jumpUrl;
};

struct GameGongGao{
    std::vector<GameActivityData> gongGaoData;
};

struct JoinCompetitionData{
    int result;
    std::string roomId;
    std::string text;
};
#endif
