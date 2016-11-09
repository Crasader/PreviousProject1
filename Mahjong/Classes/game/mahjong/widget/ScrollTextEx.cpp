#include "game/mahjong/widget/ScrollTextEx.h"

#define IF_RETURN(cont,p) if ((cont)){return (p);}
#define IF_RETURN_FALSE(cont) IF_RETURN(cont,false)

bool ScrollTextEx::init() {
    bool ret = true;
    if (Node::init()) {
        pMask = Sprite::create("gameview/sroll_bg.png");
        _mLable = Label::createWithSystemFont("", "Arial", 24);
        _mLable->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
        _mLable->setColor(Color3B::YELLOW);
        IF_RETURN_FALSE(!initClipper(pMask, _mLable));
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
    _mLable = Label::createWithSystemFont(string, "Arial", 16);
}

bool ScrollTextEx::initClipper(cocos2d::Sprite* pMask,
                               cocos2d::Label* pMoveChild) {
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
    clipper->addChild(pMask);
    clipper->addChild(pMoveChild, 1);
    addChild(clipper);
    
    for (auto child : _mNodes) {
        IF_RETURN_FALSE(!child);
        clipper->addChild(child);
    }
    this->setContentSize(pMask->getContentSize());
    return true;
}

ScrollTextEx::ScrollTextEx() :
_autoScroll(false) {
}

ScrollTextEx::~ScrollTextEx() {
    //	CC_SAFE_RELEASE(_mLable);
}


void ScrollTextEx::update(float delta) {
    if (!_mLable) {
        return;
    }
    float speed = 0.7f;
//    float currentX = _mLable->getPositionX();
    float contentX = getContentSize().width * (-1.0f);
    float lableX = _mLable->getContentSize().width * (-1.0f);
    if (_autoScroll) {
        if (_mLable->getPositionX() >= (lableX + contentX / 2)){
            _mLable->setPositionX(_mLable->getPositionX() -speed);
        }
        else {
            if (m_strs.size()>0)
            {
                auto str = m_strs.front();
                m_strs.pop_front();
                _mLable->setString(str);
                _mLable->setPositionX(-contentX / 2 );
            }
            else
            {
                /*removeFromParentAndCleanup(1);*/
            }
            
        }
        
    } else {
        _mLable->setPositionX(contentX / 2);
    }
}

void ScrollTextEx::setAutoScroll(bool isScroll, bool byWidth/*=false*/) {
    if (!byWidth) {
        _autoScroll = isScroll;
    } else {
        _autoScroll =
        _mLable->getContentSize().width > getContentSize().width ?
        true : false;
    }
}
bool ScrollTextEx::initWithDatas(cocos2d::Sprite* pMask,
                                 cocos2d::Label* pMoveChild) {
    bool ret = false;
    if (Node::init()) {
        IF_RETURN_FALSE(!pMask);
        _mLable = pMoveChild;
        _mLable->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
        initClipper(pMask, _mLable);
        scheduleUpdate();
        return true;
    }
    return ret;
}
