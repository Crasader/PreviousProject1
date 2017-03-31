#ifndef _MENU_SCENE_PAY_HANDLER_H_
#define _MENU_SCENE_PAY_HANDLER_H_
#include "cocos2d.h"

class MahjongPayHandler
{       
public:
	MahjongPayHandler() {};
	~MahjongPayHandler() {};
	void dealEventCallBack(int eventId, int result);
    void loginThirdPlatform(std::string openid,std::string unionid,std::string url,std::string sex,std::string nickname,std::string hsman,std::string hstype,std::string imsi,std::string imei,std::string ver1);
	static MahjongPayHandler* getInstance();
private:
	void doPayEvent1(int result);
	void doPayEvent2(int result);
	void doPayEvent3(int result);
};
#endif
