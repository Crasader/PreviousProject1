#include "game/utils/StringUtil.h"
#include <Regex>

std::string StringUtil::itos(int target){
    char ctime[16];
    sprintf(ctime, "%d", target);
    return ctime;
}

std::vector<std::string> StringUtil::split(std::string str, std::string pattern)
{
    std::string::size_type pos;
    std::vector<std::string> result;
    str += pattern;
    int size = str.size();
    
    for (int i = 0; i<size; i++)
    {
        pos = str.find(pattern, i);
        if (pos<size)
        {
            std::string s = str.substr(i, pos - i);
            result.push_back(s);
            i = pos + pattern.size() - 1;
        }
    }
    return result;
}


bool StringUtil::checkPhone(std::string phone){
    
    if (phone.length() != 11){
        return false;
    }
    std::regex rx("[0-9]+");
    bool result = std::regex_match(phone.begin(), phone.end(), rx);
    return result;
}


bool StringUtil::checkPassword(std::string string){
    if (string.length() < 5 || string.length() > 10){
        return false;
    }
    std::regex rx1("^[A-Za-z0-9]+$");
    bool result_1 = std::regex_match(string.begin(), string.end(), rx1);
    //    std::regex rx2("[0-9]+");
    //    bool result_2 = std::regex_match(string.begin(), string.end(), rx2);
    //    std::regex rx3("^[A-Za-z]+$");
    //    bool result_3 = std::regex_match(string.begin(), string.end(), rx3);
    //    return result_1 && (!result_2) && (!result_3);
    return result_1;
}

bool StringUtil::checkAccount(std::string string){
    if (string.length() < 6 || string.length() > 12){
        return false;
    }
    std::regex rx1("^[A-Za-z0-9]+$");
    bool result_1 = std::regex_match(string.begin(), string.end(), rx1);
    //    std::regex rx2("[0-9]+");
    //    bool result_2 = std::regex_match(string.begin(), string.end(), rx2);
    //    std::regex rx3("^[A-Za-z]+$");
    //    bool result_3 = std::regex_match(string.begin(), string.end(), rx3);
    //    return result_1 && (!result_2) && (!result_3);
    return result_1;
}


std::vector<int> StringUtil::getArrayByInt(std::string string){
    std::vector<int> result;
    char tmp1[10];
    strncpy(tmp1,string.c_str(),string.length());
}
