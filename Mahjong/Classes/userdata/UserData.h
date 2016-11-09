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
    
    int getFangkaNum();
    void setFangkaNum(int num);

	int getDiamond();
	void setDiamond(int num);
    
    int getLockDiamond();
    void setLockDiamond(int num);

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
    
    std::string getMarkId();
    void setMarkId(std::string markid);
    
    int getWanJiaQunVersion();
    void setWanJiaQunVersion(int ver);
    
    int getDailiQunVersion();
    void setDailiQunVersion(int ver);
    
private:
	UserData();
	static UserData* _instance;	
	void init();
};
#endif