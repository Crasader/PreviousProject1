#ifndef _CALLBAIDUANDROIDMETHOD_H_
#define _CALLBAIDUANDROIDMETHOD_H_

#include "cocos2d.h"
#include "userdata/UserData.h"

using namespace cocos2d;

class CallBDAndroidMethod{
public:
	static CallBDAndroidMethod* getInstance();
	const char* getJniPath();
    void updateLongitude();
    void updateLatitude();
private:
	std::string _jniPath;
	CallBDAndroidMethod();
	static CallBDAndroidMethod* _instance;
};
#endif
