#include "game/mahjong/widget/ScrollTextEx.h"

#define IF_RETURN(cont,p) if ((cont)){return (p);}
#define IF_RETURN_FALSE(cont) IF_RETURN(cont,false)

bool ScrollTextEx::init() {
    bool ret = true;
    if (Node::init()) {
        m_strs.clear();
        pMask = Sprite::create("gameview/sroll_bg.png");
        pMask->setOpacity(0);
        pMoved = ScrollCell::create("");
        pMoved->setAnchorPoint(Point::ANCHOR_MIDDLE);
        pMoved->setPosition(0,0);
        IF_RETURN_FALSE(!initClipper(pMask, pMoved));
        scheduleUpdate();
        return ret;
    }
    return ret;
}
void ScrollTextEx::setScrollStr(std::string str)
{
    if (str.size()>0)
    {
        m_strs.push_back(str);
    }
    
}
void ScrollTextEx::setScrollStrs(std::vector<std::string> strs)
{
    auto vec = strs;
    if (vec.size()<=0)
    {
        return;
    }
    std::string str1;
    for (auto var : vec)
    {
        setScrollStr(var);
        
    }
    
}

void ScrollTextEx::setpMaskString(std::string string) {
    pMoved = ScrollCell::create(string);
}

bool ScrollTextEx::initClipper(cocos2d::Sprite* pMask,
                               ScrollCell* pMoveChild) {
    auto clipper = ClippingNode::create();
    IF_RETURN_FALSE(!clipper);
    IF_RETURN_FALSE(!pMask);
    setContentSize(Size(pMask->getContentSize().width,pMask->getContentSize().height));
    IF_RETURN_FALSE(!pMask->getTexture());
    auto _clipperStencil = Sprite::createWithTexture(pMask->getTexture());
    IF_RETURN_FALSE(!_clipperStencil);
    _clipperStencil->retain();
    clipper->setAlphaThreshold(0.1f);
    clipper->setStencil(_clipperStencil);
    clipper->setInverted(false);
    clipper->addChild(pMask);
    
    clipper->addChild(pMoveChild, 1);
    addChild(clipper);
    
    for (auto child : _mNodes) {
        IF_RETURN_FALSE(!child);
        clipper->addChild(child);
    }
    setContentSize(pMask->getContentSize());
    return true;
}

ScrollTextEx::ScrollTextEx() :
_autoScroll(false) {
}

ScrollTextEx::~ScrollTextEx() {
    //	CC_SAFE_RELEASE(_mLable);
}


void ScrollTextEx::update(float delta) {
    if (!pMoved) {
        return;
    }
    float speed = 0.7f;
    float contentX = getContentSize().width * (-1.0f);
    float lableX = pMoved->getContentSize().width * (-1.0f);
    if (_autoScroll) {
        if (pMoved->getPositionX() >= (lableX + contentX / 2)){
            pMoved->setPositionX(pMoved->getPositionX() -speed);
        }
        else {
            if (m_strs.size()>0)
            {
                auto str = m_strs.front();
                m_strs.pop_front();
                pMoved->setString(str);
                pMoved->setPositionX(-contentX / 2 );
            }
            else
            {
                /*removeFromParentAndCleanup(1);*/
            }
            
        }
        
    } else {
        pMoved->setPositionX(contentX / 2);
    }
}

void ScrollTextEx::setAutoScroll(bool isScroll, bool byWidth/*=false*/) {
    if (!byWidth) {
        _autoScroll = isScroll;
    } else {
        _autoScroll =
        pMoved->getContentSize().width > getContentSize().width ?
        true : false;
    }
}
bool ScrollTextEx::initWithDatas(cocos2d::Sprite* pMask,
                                 ScrollCell* pMoveChild) {
    bool ret = false;
    if (Node::init()) {
        IF_RETURN_FALSE(!pMask);
        pMoved = pMoveChild;
        pMoved->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
        initClipper(pMask, pMoved);
        scheduleUpdate();
        return true;
    }
    return ret;
}
