#ifndef __JONG_H__
#define __JONG_H__
#include "cocos2d.h"
USING_NS_CC;

enum JongEnum
{
    hz =0,wan_1, wan_2, wan_3, wan_4, wan_5, wan_6, wan_7, wan_8, wan_9,
    tong_1,tong_2,tong_3,tong_4,tong_5,tong_6,tong_7,tong_8,tong_9,
    tiao_1,tiao_2,tiao_3,tiao_4,tiao_5,tiao_6,tiao_7,tiao_8,tiao_9,
    east,south,west,north,zhong,fa,bai,spring, summer, autumn, winter,
    ju,mei, zhu,lan,shu,cai,mao,bao,baida
};

enum JongViewType{
    herohand,//玩家手牌
    heroplayed,//玩家打出的牌
    herodeal,//玩家发牌
    heroangang,//玩家暗杠
    herocpgportrait,//吃碰杠纵向
    herocpglandscape,//吃碰杠横向
    
    lefthand,
    leftmingpai,
    leftplayed,
    leftdeal,
    leftangang,
    leftcpgportrait,
    leftcpglandscape,
    
    righthand,
    rightmingpai,
    rightplayed,
    rightdeal,
    rightangang,
    rightcpgportrait,
    rightcpglandscape,
    
    oppositehand,
    oppositemingpai,
    oppositeplayed,
    oppositedeal,
    oppositeangang,
    oppositecpgportrait,
    oppositecpglandscape,
    
    playedshow//大牌显示
    
};

class Jong :public Node{
public:
    static std::string getContextImage(int ctype);//获取内容图片
    virtual bool init();
    void showJong(int bType,int cType,bool show = true);//显示牌
    cocos2d::Rect getJongBoundingBox();//获取牌的区域
    std::string getJongName(int type);//获取牌的名字
    void setJongSelectIcon(bool show);//选择框
    void setTingJongHint(bool show,std::string texure ="");//听牌箭头
    void showTingIcon(int bType);//玩家听牌标记,打出去的牌堆显示
    void showBackShadow(bool show);//阴影保护
//    void showBackShadowNotLock(bool show);//显示阴影但是不锁定牌
//    bool isJongShowShadow();//牌上是否有阴影
    void showBaiDaPoker();
    CC_SYNTHESIZE(int, jongType, JongType);
    CC_SYNTHESIZE(bool, isProtected, IsProtected);
    CREATE_FUNC(Jong);
private:
    Sprite* background;
    Sprite* contentSprite;
    Sprite* selcetedIcon;
    Sprite* tingPaiArrow;
    Sprite* protectedIcon;
    float getContentScaleByType(int bType);//内容缩放比例
    float getBackgroundScaleByType(int bType);//背景缩放比例
    void setFlipByType(Sprite* sprite,int bType);//水平翻转
    float getRotationByType(int bType);//旋转
    cocos2d::Point getContentPosition(int bType,cocos2d::Point bpos);//内容的坐标
    std::string getBackgroundImage(int btype);//获取背景图片
};
#endif
