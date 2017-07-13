#ifndef __USER_DATA_H__
#define __USER_DATA_H__
#include "cocos2d.h"
USING_NS_CC;

class UserData{
public:
	static UserData* getInstance();

	std::string getPoxiaoId();
	void setPoxiaoId(std::string poxiaoId);

	int getGold();
	void setGold(int gold);
    
    float getFangkaNum();
    void setFangkaNum(float num);

	int getDiamond();
	void setDiamond(int num);
    
    int getLockDiamond();
    void setLockDiamond(int num);
    
    float getHuafeiQuan();
    void setHuafeiQuan(float num);

	int getTicket();
	void setTicket(int num);

	std::string getUserName();
	void setUserName(std::string name);

	std::string getNickName();
	void setNickName(std::string name);

	std::string getPassword();
	void setPassword(std::string pwd);

	int getGender();
	void setGender(int gender);

	std::string getBoundPhone();
	void setBoundPhone(std::string phone);

	std::string getPicture();
	void setPicture(std::string pic);

	bool isFirstCharge();
	void setFirstCharge(bool firstcharge);

	bool isChangeName();
	void setChangeName(bool firstcharge);
    
    float getMusicValue();
    void setMusicValue(float value);
    
    float getSoundValue();
    void setSoundValue(float value);
    
    std::string getWxOpenId();
    void setWxOpenId(std::string openId);
    
    std::string getWxUnionid();
    void setWxUnionid(std::string unionid);
    
    std::string getMarkId();
    void setMarkId(std::string markid);
    
    int getWanJiaQunVersion();
    void setWanJiaQunVersion(int ver);
    
    int getDailiQunVersion();
    void setDailiQunVersion(int ver);
    
    bool isWeixinPayOpen();
    void setWeixinPayOpen(bool open);
    
    bool isFangYan();
    void setFangYan(bool open);
    
    bool isInviteCodeBind();
    void setInviteCodeBind(bool bind);
    
    bool isClickShare();
    void setIsClickShare(bool bind);
    
    std::string getInvitePropMoney();
    void setInvitePropMoney(std::string money);
    
    std::string getInvitePropType();
    void setInvitePropType(std::string type);
    
    std::string getInvitePropNum();
    void setInvitePropNum(std::string num);
    
    std::string getHsman();
    void setHsman(std::string num);
    
    std::string getHstype();
    void setHstype(std::string num);

    
    std::string getImsi();
    void setImsi(std::string num);
    
    std::string getImei();
    void setImei(std::string num);
    
    std::string getAppVer();
    void setAppVer(std::string num);

    std::string getShareTextContent();
    void setShareTextContent(std::string num);
    
    std::string getShareTextContentNum();
    void setShareTextContentNum(std::string msg);
    
    std::string getTurntableNumber();
    void setTurntableNumber(std::string msg);
    
    std::string getGongZhongHao();
    void setGongZhongHao(std::string msg);
    
    std::string getUserPayWay();
    void setUserPayWay(std::string msg);
    
    CC_SYNTHESIZE(std::string, poxiaoOrderID, PoxiaoOrderID);
private:
	UserData();
	static UserData* _instance;	
	void init();
};
#endif
