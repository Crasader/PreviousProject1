#ifndef _CHATANDROIDMETHOD_H_
#define _CHATANDROIDMETHOD_H_

#include "cocos2d.h"
#include "userdata/UserData.h"

using namespace cocos2d;

class ChatAndroidMethod{
public:
	static ChatAndroidMethod* getInstance();
	const char* getJniPath();
    
    void beginRecordAudio();
    void endRecordAudio();
    void deleteAudio();
    void playAudio();
    
    void loginChatServer(std::string poxiaoId);
    void createChatRoom(std::string poxiaoId);
    void sendChatInfo(std::string poxiaoId,std::string msg);
    void addMember(std::string myPoxiaoId,std::string poxiaoId);
private:
	std::string _jniPath;
	ChatAndroidMethod();
	static ChatAndroidMethod* _instance;
};
#endif
