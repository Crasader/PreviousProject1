#include "HeadPortrait.h"
#include "GB23122Utf8.h"
using namespace std;
std::string WStrToUTF81(const std::wstring& src)
{
	std::string dest;
	dest.clear();
	for (size_t i = 0; i < src.size(); i++)
	{
		wchar_t w = src[i];
		if (w <= 0x7f)
		{
			dest.push_back((char)w);
		}
		else if(w <= 0x7ff)
		{
			dest.push_back(0xc0 | ((w >> 6) & 0x1f));
			dest.push_back(0x80 | (w & 0x3f));
		}
		else if(w <= 0xffff)
		{
			dest.push_back(0xe0 | ((w >> 12) & 0x0f));
			dest.push_back(0x80 | ((w >> 6) & 0x3f));
			dest.push_back(0x80 | (w & 0x3f));
		}
		else if(sizeof(wchar_t) > 2 && w <= 0x10ffff)
		{
			dest.push_back(0xf0 | ((w >> 18) & 0x07));
			dest.push_back(0x80 | ((w >> 12) & 0x3f));
			dest.push_back(0x80 | ((w >> 6) & 0x3f));
			dest.push_back(0x80 | (w & 0x3f));
		}
		else
			dest.push_back('?');
	}
	return dest;
}

void HeadPortrait::setHeadProtrait(int dir, std::string name, int photo, int coins)
{
	this->setName("Head");
	// 位置
	switch (dir)
	{
	case 0://43
		this->setPosition(43, 60);		// 下
		break;
	case 1:
		this->setPosition(755, 280);		// 右
		break;
	case 2:
		this->setPosition(575, 420);		// 上
		break;
	case 3:
		this->setPosition(43, 280);		// 左
		break;
	}
	
	// 头像
	string str = "headPortrait_" + String::createWithFormat("%d", dir)->_string + ".png";
	Sprite* headPhoto = Sprite::create(str);
	Vec2 center = headPhoto->getContentSize() / 2;
	this->addChild(headPhoto);

	// 姓名
	string strName = "玩家" + String::createWithFormat("%d", (dir + 1))->_string;
	Label* nameLabel = Label::createWithTTF(strName, "fonts/arial.ttf", 12.0f);
	nameLabel->setHorizontalAlignment(TextHAlignment::CENTER);
	nameLabel->setPosition(center.x, center.y + 42.0f);
	headPhoto->addChild(nameLabel);

	// 金币数
	string coinStr = String::createWithFormat("%d", coins)->_string;
	Label* coinsLabel = Label::createWithCharMap("coins_num.png", 11, 14, '0');
	coinsLabel->setString(coinStr);
	coinsLabel->setAdditionalKerning(-3.0f);
	coinsLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
	coinsLabel->setPosition(center.x + 3.0f, center.y - 40.0f);
	headPhoto->addChild(coinsLabel);
}


inline void HeadPortrait::WStrToUTF8(std::string& dest, const std::wstring& src)
{
	dest.clear();
	for (size_t i = 0; i < src.size(); i++)
	{
		wchar_t w = src[i];
		if (w <= 0x7f)
			dest.push_back((char)w);
		else if (w <= 0x7ff){
			dest.push_back(0xc0 | ((w >> 6) & 0x1f));
			dest.push_back(0x80 | (w & 0x3f));
		}
		else if (w <= 0xffff){
			dest.push_back(0xe0 | ((w >> 12) & 0x0f));
			dest.push_back(0x80 | ((w >> 6) & 0x3f));
			dest.push_back(0x80 | (w & 0x3f));
		}
		else if (sizeof(wchar_t) > 2 && w <= 0x10ffff){
			dest.push_back(0xf0 | ((w >> 18) & 0x07)); // wchar_t 4-bytes situation  
			dest.push_back(0x80 | ((w >> 12) & 0x3f));
			dest.push_back(0x80 | ((w >> 6) & 0x3f));
			dest.push_back(0x80 | (w & 0x3f));
		}
		else
			dest.push_back('?');
	}
}

// 初始化头像：【底框，背景色】，【头像，姓名，金币】
bool HeadPortrait::init()
{
	if (!Node::init())
	{
		return false;
	}

	// 背景色
	Sprite* bkgColor = Sprite::create("headPortrait_bkg.png");
	this->addChild(bkgColor);

	// 金币
	Sprite* coinIcon = Sprite::create("coinIcon.png");
	coinIcon->setPosition(-25, -39);
	this->addChild(coinIcon);

	// 倒计时蒙版
	//Sprite* mask = Sprite::create("mask.png");
	//progress = ProgressTimer::create(mask);
	//this->addChild(progress);
	//progress->setType(ProgressTimerType::RADIAL);
	return true;
}

