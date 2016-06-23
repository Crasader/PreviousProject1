#include "DropDownListBox.h"
#include "LoginMannger.h"
#include "game/mahjong/state/GameData.h"
#include "game/utils/Chinese.h"

DropDownList::DropDownList(Sprite* label, Size size,std::string eventName)
	: showLabel(label)
	, isShowMenu(false)
	, lastSelectedIndex(0)
    , eventName(eventName)
{
//    auto bgFrame = MenuItemImage::create("mainlogin/drop_list_bg.png","mainlogin/drop_list_bg.png");
	mainMenu =Menu::create();
    mainMenu->setContentSize(size);
	mainMenu->setPosition(Point(size.width , size.height / 2));
	mainMenu->retain();
	bgFrame = Sprite::create("mainlogin/drop_list_bg.png");
	bgFrame->setPosition(Point(size.width , size.height / 2));
	addChild(bgFrame,-1);
	bgFrame->setVisible(false);

	showLabel->setPosition(Point(size.width / 2, size.height / 2));
	addChild(showLabel);
	setContentSize(size);
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(DropDownList::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(DropDownList::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(DropDownList::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

}

DropDownList::~DropDownList()
{
	
}

DropDownList*DropDownList::create(Sprite* label, CCSize size,std::string eventName)
{
	DropDownList* list = new DropDownList(label, size,eventName);
	list->autorelease();
	return list;
}


void DropDownList::onEnter()
{
	setTouchEnabled(true);
	CCLayer::onEnter();
}


bool DropDownList::onTouchBegan(CCTouch *touch, CCEvent *event)
{
    auto rect = getTouchAbleRect();
    if (rect.containsPoint(touch->getLocation()))
    {
        if (!isShowMenu)
        {
            bgFrame->setVisible(true);
            isShowMenu = true;
            addChild(mainMenu);
            LoginAccPwd lap ;
            lap.account = "使用其他账号登录";
            lap.password = "";
            GAMEDATA::getInstance()->setLoginAccPwd(lap);
            EventCustom ev(eventName);
            _eventDispatcher->dispatchEvent(&ev);
            selectLabels.clear();
            mainMenu->removeAllChildren();
            for(auto var:LoginMannger::getInstance()->getMemoryNickname()){
                addLabel(var);
            }
            return true;
            
        }
        else
        {
            onClose();
            return false;
        }
        
    }
    else
    {
        if (isShowMenu)
        {
            if(selectLabels.size()>0){
                LoginAccPwd lap ;
                lap.account = selectLabels.at(0);
                lap.password = LoginMannger::getInstance()->getPassword(selectLabels.at(0).c_str());
                GAMEDATA::getInstance()->setLoginAccPwd(lap);
                EventCustom ev(eventName);
                _eventDispatcher->dispatchEvent(&ev);
            }
            onClose();
            return true;
        }
        
        
    }
    return false;
}


void DropDownList::addLabel(std::string label)
{
	Size size = getContentSize();

	auto ttf = LabelTTF::create(label, "arial",22);
	auto frame = Sprite::create();
	frame->setPosition(ttf->getContentSize() / 2);
	ttf->addChild(frame,-1);

	selectLabels.push_back(label);
    auto labelttf = LabelTTF::create(label, "arial", 30);
	MenuItem* item = MenuItemSprite::create(labelttf
		,ttf,
		CC_CALLBACK_1(DropDownList::onSelected,this)
		);
	item->setAnchorPoint(Point::ANCHOR_MIDDLE);
	item->setPosition(0, -(int)selectLabels.size() * 45+125);
	mainMenu->addChild(item);
	item->setTag((int)selectLabels.size() - 1);
}


void DropDownList::onSelected(CCObject* sender)
{
	MenuItem* item = dynamic_cast<MenuItem*>(sender);
	if (item)
	{
		lastSelectedIndex = item->getTag();
        LoginAccPwd lap ;
        lap.account = selectLabels.at(lastSelectedIndex);
        lap.password = LoginMannger::getInstance()->getPassword(selectLabels.at(lastSelectedIndex).c_str());
        GAMEDATA::getInstance()->setLoginAccPwd(lap);
        EventCustom ev(eventName);
        _eventDispatcher->dispatchEvent(&ev);
	}
	onClose();
}


void DropDownList::onClose()
{
	removeChild(mainMenu, true); 
	isShowMenu = false;
	bgFrame->setVisible(false);
}
