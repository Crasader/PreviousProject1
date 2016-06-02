/// ͷ����
//	��������ͷ��

#ifndef __HEAD_PORTRAIT_H__
#define __HEAD_PORTRAIT_H__

#include "cocos2d.h"
USING_NS_CC;

class HeadPortrait : public Node
{
public:
	CREATE_FUNC(HeadPortrait);

	bool init();
	void setHeadProtrait(int dir, std::string name, int photo, int coins);

	//void startProgress(float time);
	//void StopProgress();

	void WStrToUTF8(std::string& dest, const std::wstring& src);

private:
	// ͷ�񣺡��׿򣬱���ɫ������ͷ����������ҡ�
	int playerPhoto;
	int playerCoins;
	//ProgressTimer* progress;
	std::string playerName;
};

#endif // end MahjongScene.h