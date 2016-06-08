#include "game/mahjong/splash/DropDownListBox.h"
#include "game/mahjong/splash/LoginMannger.h"
#include "game/utils/Chinese.h"

DropDownList::DropDownList(Sprite* label, Size size)
	: showLabel(label)
	, isShowMenu(false)
	, lastSelectedIndex(0)
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

DropDownList*DropDownList::create(Sprite* label, CCSize size)
{
	DropDownList* list = new DropDownList(label, size);
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
    auto rect = _loginscene->_editName->getBoundingBox();
    if (rect.containsPoint(touch->getLocation()))
    {
        if (!isShowMenu)
        {
            bgFrame->setVisible(true);
            isShowMenu = true;
            addChild(mainMenu);
            _loginscene->_editName->setText("使用其他账号登录");
            _loginscene->_editName->setFontColor(Color3B::GRAY);
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
            _loginscene->setChangeNickName(selectLabels.at(0),LoginMannger::getInstance()->getPassword(selectLabels.at(lastSelectedIndex).c_str()));
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
        _loginscene->setChangeNickName(selectLabels.at(lastSelectedIndex),LoginMannger::getInstance()->getPassword(selectLabels.at(lastSelectedIndex).c_str()));

	}
	onClose();
}


void DropDownList::onClose()
{
	removeChild(mainMenu, true); 
	isShowMenu = false;
	bgFrame->setVisible(false);
}

void DropDownList::setLoginscene(SplashScene* scene)
{
	_loginscene = scene;
}