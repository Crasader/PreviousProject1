#ifndef _CALLANDROIDMETHOD_H_
#define _CALLANDROIDMETHOD_H_

#include "cocos2d.h"

using namespace cocos2d;

class CallAndroidMethod{
public:
	static CallAndroidMethod* getInstance();
	void requestEvent(int eventId);
	void dealEventCallBack(int requestId, bool isOpen, bool payResult, int propIds[], int propNums[], int count);
	const char* getJniPath();
private:
	std::string _jniPath;
	CallAndroidMethod();
	static CallAndroidMethod* _instance;
};
#endif
