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
    void shareImageToWeChat(std::string imagePath,bool friends);
    void shareSDCardImageToWeChat(std::string imagePath,bool friends);
    void copyToPasteboard(std::string msg);
    void updateClientAppVersion();
    void downLoadAndroidApk(std::string url);
    std::string getBatteryPersent();
    std::string getSdCardDir();
	const char* getJniPath();
private:
	std::string _jniPath;
	CallAndroidMethod();
	static CallAndroidMethod* _instance;
};
#endif
