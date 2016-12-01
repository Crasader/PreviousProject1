#ifndef __STRING_UTiL_H__
#define __STRING_UTiL_H__
#include "cocos2d.h"
USING_NS_CC;

class StringUtil{
public:
    static bool checkPhone(std::string str);
    static bool checkPassword(std::string string);
    static bool checkAccount(std::string string);
	static std::string itos(int target);
	static std::vector<std::string> split(std::string str, std::string pattern);
};

#endif