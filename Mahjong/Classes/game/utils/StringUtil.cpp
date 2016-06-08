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