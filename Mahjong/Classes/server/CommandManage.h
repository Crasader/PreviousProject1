#ifndef __JSON_MANAGE_H__
#define __JSON_MANAGE_H__
#include "cocos2d.h"
USING_NS_CC;


class CommandManage{
public:
    static CommandManage* getInstance();
    std::string getHeartCommmand();//心跳
    std::string getHeartRespCommmand();//心跳回复
    std::string getGiveUpCpgCommmand();//放弃吃碰杠
    std::string getReadyCommmand();//准备
    std::string getPlayPokerCommmand(int poker);//打牌
    std::string getChiCommand(std::string chi,int poker);//吃
    std::string getPengCommand(std::string peng ,int poker);//碰
    std::string getGangCommand(std::string gang, int poker,int flag);//杠
    std::string getGiveUpTingCommand();//放弃听牌
    std::string getTingCommand(int poker);//听牌
    std::string getRoomListCommand(std::string gameId);//房间列表
    std::string getEnterRoomCommand(std::string gameId, std::string roomId);//进入房间请求
    std::string getQuitRoomCommand();//退出房间
    std::string getChangeHeadCommand(std::string pic);//更换头像
    std::string getChangeGenderCommand(std::string gender);//更换性别
    std::string getOpenRoomCommand(std::string ftype,std::string dihua,std::string lz,std::string fcy,std::string ifkb,std::string ifemsc,std::string size);//开设房间
    std::string getEnterFriendRoomCommand(std::string pid);//进入私人房间
    std::string getBillCommand();//账单
    std::string getBillDetailCommand(std::string billId);//账单明细
    std::string getLobbyQuitCommand();//退出大厅
    std::string getDailyPrideCommand();//抽奖情况
    std::string getTodayPrideCommand();//当次抽奖
    std::string getFirstChargeInfoCommand();//首冲
    std::string getGoldChargeListCommand();//金币充值列表
    std::string getGoldChangeCommand(std::string fangka);//金币兑换列表
    std::string getFangkaChargeListCommand();//房卡充值
    std::string getLequanChangeListCommand();//乐券兑换列表
    std::string getLequanChangeCommand(std::string propId,std::string phone,std::string name,std::string address);//乐券兑换
    std::string getPlayerInfoCommand();//获取用户信息
    std::string getLequanChangeRecordCommand();//乐券兑换记录
    std::string getFeedBackCommand(std::string msg);//反馈
    std::string getOutResumeCommand();//切到后台
    std::string getContinueGameCommand();//再来一局
    std::string getPlayerChatMsgCommand(std::string msg,std::string pid,bool sound);//聊天
    std::string getThirdLoginCommand(std::string openid,std::string unionid,std::string head,std::string sex,std::string nickname,std::string hsman,std::string hstype,std::string imsi,std::string imei,std::string ver1,bool tag = false);//第三方登录
    std::string getEnterRoomByIdCommand(std::string roomid);//加入房间
    std::string getDissolveRoomCommand();//房主解散房间
    std::string getDissolveRoomRequestCommand();//设置界面解散
    std::string getDissolveRoomSelectCommand(std::string agree);//是否同意解散
    std::string getOpenRoomRequestCommand();//开设房间询问
    std::string getEnterRoomRequestCommand();//加入房间询问
    std::string getScrollTextCommand();//跑马灯
    std::string getWanJiaQunCommand();//玩家群
    std::string getNoticeCommand();//公告
    std::string getGamePayType();//获取支付方式
    std::string getVistorLogin();//游客登录
    std::string getVistorLoginAgain(std::string username,std::string password);
    std::string getFupanInfo(std::string recordId);
    std::string getTuiGuangCommand();
    std::string getTuiGuangPrideCommand();
    std::string getGongGaoCommand();
    std::string getCertification(std::string name, std::string sfz);
    /** ------------------------------红中麻将协议开始 ------------------- **/
    std::string getEnterHongZhongCommand(std::string ftype,std::string ma,std::string difen,std::string size);
    std::string getHZDissolveRoomCommand();
    std::string getHZPlayerReadyCommand();
    std::string getHZEnterRoomCommand(std::string roomId);
    std::string getHZPlayPokerCommand(std::string pokerId);
    std::string getHZPlayerPengCommand(std::string poker,std::string seatId,std::string peng);
    std::string getHZPlayerGangCommand(std::string poker,std::string seatId,std::string peng,std::string flag);
    std::string getHZPlayerCanclePGCommand(std::string seatId);
    std::string getHZHuActionCommand(std::string msg);
    std::string getHZDissolveRoomSelectCommand(std::string agree);
    std::string getHZDissolveRoomInGameCommand();
    std::string getHZPlayGameAgain();
    std::string getHZOutResumeCommand();
    std::string getHZQuitRoomCommand();
    /** ------------------------------红中麻将协议结束 ------------------- **/
    
    /* -------------- 崇明麻将协议开始 ------ */
    std::string getCMOpenRoomCommand(std::string ftype,std::string dihua,std::string lz,std::string fcy,std::string ifkb,std::string size);//开设房间
    std::string getCMDissovleRoomReq();
    std::string sendInviteCodeCommand(std::string code);
    std::string sendCmReadyCommand();
    std::string sendCMDissovleRoomRequest();
    std::string getCMDissolveRoomSelectCommand(std::string agr);
    std::string getCMPlayPokeCommand(int po);
    std::string getCMPlayerChiCommand(std::string chi,int poker);
    std::string getCMPengCommand(std::string peng ,int poker);//碰
    std::string getCMGangCommand(std::string gang, int poker,int flag);//杠
    std::string getCMGiveUpCommand();//放弃听牌
    std::string getCMHuActionCommand(std::string hu);
    std::string getCMOutResumeCommand();
    std::string getCMContinueGameCommand();
     /* ______________ 崇明麻将协议结束 ------ */
    
    /** ---------------------- 比赛协议 ---------------------------**/
    std::string sendJoinCompetiotnCommand(std::string competitionId);
    std::string sendQuitCompetitionCommand(std::string competitionId);
    std::string sendHuafeiRecordCommmand();
    std::string sendCancleTruCommand();
    /** ---------------红包协议--------------------- **/
    std::string sendGetHongbaoPride();
    std::string sendGiveupHongbaoPride();
    /** --------------- 排行榜 ---------------------- **/
    std::string sendLobbyPaiHangCommand();
    std::string sendTurntableCommmand();
    std::string sendTurntableShareCommand();
    std::string sendTurntableStartCommand();
    std::string sendExchangeHuaFeiCommand();
    std::string sendDuiHuanHuafeiCommand(std::string fee,std::string phone);
    std::string sendDuiHuanFangkaCommand(std::string fee);
private:
    CommandManage();
    static CommandManage* _instance;
    std::string commandString(std::map<std::string, std::string> keyValue);
    std::string itos(int target);
};
#endif
