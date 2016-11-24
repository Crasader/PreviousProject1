#ifndef __JONG_H__
#define __JONG_H__
#include "cocos2d.h"
USING_NS_CC;

enum JongEnum
{
    wan_1 = 1, wan_2, wan_3, wan_4, wan_5, wan_6, wan_7, wan_8, wan_9,
    tong_1,tong_2,tong_3,tong_4,tong_5,tong_6,tong_7,tong_8,tong_9,
    tiao_1,tiao_2,tiao_3,tiao_4,tiao_5,tiao_6,tiao_7,tiao_8,tiao_9,
    east,south,west,north,zhong,fa,bai,
    spring, summer, autumn, winter, ju,mei, zhu,lan
};

enum JongViewType{
    herohand,
    herocpg,
    heroplayed,
    herodeal,
    
    lefthand,
    leftplayed,
    leftdeal,
    
    righthand,
    rightplayed,
    rightdeal,
    
    oppositehand,
    oppositeplayed,
    oppositedeal,
    oppositeangang,
    
    playedshow,
    herocpg2
};

class Jong :public Node{
public:
	virtual bool init();
	void showJong(int bType,int cType);
	Rect getJongBoundingBox();
	static std::string getContextImage(int btype);
    std::string getJongName(int type);
    void setJongSelectIcon(bool show);
 	CC_SYNTHESIZE(int, jongType, JongType);
	CREATE_FUNC(Jong);
private:
	Sprite* background;
	Sprite* contentSprite;
    Sprite* selcetedIcon;
	float getScaleByType(int bType);
	void setFlipByType(Sprite* sprite,int bType);
	float getRotationByType(int bType);
	Point getContentPosition(int bType,Point bpos);
	std::string getBackgroundImage(int btype);
};
#endif
