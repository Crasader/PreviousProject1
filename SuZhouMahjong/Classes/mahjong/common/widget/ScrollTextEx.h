#pragma once
#include "cocos2d.h"
USING_NS_CC;

class ScrollTextEx : public cocos2d::Node {
public:
    
    CREATE_FUNC(ScrollTextEx);
CC_CONSTRUCTOR_ACCESS:
    ScrollTextEx();
    virtual ~ScrollTextEx();
private:
    virtual bool init();
    bool initClipper(cocos2d::Sprite* pMask, Label* pMoveChild);
    void update(float delta);
	void loadNewStr(std::string str);

public:
    void setScrollStrs(std::vector<std::string> strs);
    void setScrollStr(std::string str);
    void setAutoScroll(bool isScroll, bool byWidth = false);
private:
    Label* pMoved;
    cocos2d::Sprite* pMask;
	LayerColor*pFrame;
    bool _autoScroll;
    std::list<std::string> m_strs;
};
