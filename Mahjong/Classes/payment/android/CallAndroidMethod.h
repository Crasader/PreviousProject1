#ifndef _CALLANDROIDMETHOD_H_
#define _CALLANDROIDMETHOD_H_

#include "cocos2d.h"
#include "userdata/UserData.h"

using namespace cocos2d;

class CallAndroidMethod{
public:
	static CallAndroidMethod* getInstance();
	void requestEvent(std::string poxiaoId,std::string payId);
    void queryEventResult();
    void weChatLogin();
    void clearWechatOpenId();
    void shareToWeChat(std::string url,std::string title,std::string content,bool friends);
	const char* getJniPath();
private:
	std::string _jniPath;
	CallAndroidMethod();
	static CallAndroidMethod* _instance;
};
#endif
