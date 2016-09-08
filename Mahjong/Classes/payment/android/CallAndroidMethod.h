#ifndef _CALLANDROIDMETHOD_H_
#define _CALLANDROIDMETHOD_H_

#include "cocos2d.h"
#include "userdata/UserData.h"

using namespace cocos2d;

class CallAndroidMethod{
public:
	static CallAndroidMethod* getInstance();
	void requestEvent(std::string poxiaoId,std::string payId);
	void dealEventCallBack(int requestId, bool isOpen, bool payResult, int propIds[], int propNums[], int count);
	const char* getJniPath();
private:
	std::string _jniPath;
	CallAndroidMethod();
	static CallAndroidMethod* _instance;
};
#endif
