#pragma once
#include "cocos2d.h"
#define  KEY_USERNICKNAME_  "KEY_USERNICKNAME_"
using namespace cocos2d;





class LoginMannger{
public:
	static LoginMannger* getInstance();
	void loadMemoryNickname();
	std::list<std::string> getMemoryNickname(){ loadMemoryNickname(); return _memoryNickname; };
	bool checkNicknameIsdefault(const char* nickname);
	void addMemoryNickname(const char*_nickName, const char*_password);
	void removeMemoryNickname(const char*_nickName);
    std::string getPassword(const char* nickname);
private:
	LoginMannger();
	static LoginMannger* _instance;
	std::list<std::string> _memoryNickname;
};

