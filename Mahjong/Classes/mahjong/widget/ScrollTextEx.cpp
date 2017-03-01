#include "ScrollTextEx.h"

#define IF_RETURN(cont,p) if ((cont)){return (p);}
#define IF_RETURN_FALSE(cont) IF_RETURN(cont,false)

bool ScrollTextEx::init() {
    bool ret = true;
    if (Node::init()) {
        m_strs.clear();
        pMask = Sprite::create("gameview/sroll_bg.png");
        pMask->setOpacity(0);

	
        pMoved = Label::create("","arial",24);
        pMoved->setAnchorPoint(Point::ANCHOR_MIDDLE);
        pMoved->setColor(Color3B::YELLOW);
        pMoved->setPosition(0,0);

		pFrame = LayerColor::create(Color4B(76,70,90,150), pMoved->getContentSize().width, pMoved->getContentSize().height);
		pFrame->setAnchorPoint(Point::ANCHOR_MIDDLE);
		pMoved->addChild(pFrame,-1);
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
	for (auto var : strs)
    {
        setScrollStr(var);
        
    }
}

bool ScrollTextEx::initClipper(cocos2d::Sprite* pMask,
                               Label* pMoveChild) {
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
    
  
    setContentSize(pMask->getContentSize());
    return true;
}

ScrollTextEx::ScrollTextEx() :
_autoScroll(false) {
}

ScrollTextEx::~ScrollTextEx() {
    //	CC_SAFE_RELEASE(_mLable);
}

#define  contentX getContentSize().width * (-1.2f)
void ScrollTextEx::update(float delta) {
    if (!pMoved) {
        return;
    }
    float speed = 1.0f;
    
    float lableX = pMoved->getContentSize().width * (-1.0f);
    if (_autoScroll) {
        if (pMoved->getPositionX() >= (lableX + contentX)){
            pMoved->setPositionX(pMoved->getPositionX() -speed);
        }
        else {
            if (m_strs.size()>0)
            {
				auto str = m_strs.front();
				m_strs.pop_front();
				loadNewStr(str);
			
            }
            else
            {
				pMoved->setVisible(false);
            }
            
        }
        
    } else {
        pMoved->setPositionX(-contentX);

    }
}
void ScrollTextEx::loadNewStr(std::string str)
{
	log("loadNewStr");

	pMoved->setString(str);
	pMoved->setPositionX(-contentX);
	pMoved->setVisible(true);

	pFrame->changeWidthAndHeight(pMoved->getContentSize().width, pMoved->getContentSize().height);

	setVisible(true);
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

