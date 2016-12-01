#pragma once
#include "cocos2d.h"
#include "mahjong/widget/ScrollCell.hpp"
USING_NS_CC;

class ScrollTextEx : public cocos2d::Node {
public:
    
    CREATE_FUNC(ScrollTextEx);
CC_CONSTRUCTOR_ACCESS:
    ScrollTextEx();
    virtual ~ScrollTextEx();
    virtual bool init();
    virtual bool initWithDatas(cocos2d::Sprite* pMask,
                               ScrollCell* pMoveChild);
    bool initClipper(cocos2d::Sprite* pMask, ScrollCell* pMoveChild);
    void update(float delta);
    void setpMaskString(std::string string);
    long getCurrentTime();
public:
    void setScrollStrs(std::vector<std::string> strs);
    void setScrollStr(std::string str);
    void setAutoScroll(bool isScroll, bool byWidth = false);
private:
    ScrollCell* pMoved;
    cocos2d::Sprite* pMask;
    cocos2d::Vector<Node*> _mNodes;
    bool _autoScroll;
    std::list<std::string> m_strs;
};
