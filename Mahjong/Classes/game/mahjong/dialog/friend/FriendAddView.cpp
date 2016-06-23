#include "FriendAddView.h"
#include "server/NetworkManage.h"
#include "game/loading/Loading.h"
#include "game/mahjong/dialog/prompt/HintDialog.hpp"

bool FriendAddView::init(){
	if (!Layer::init()){
		return false;
	}
	showDialog();
	return true;
}

void FriendAddView::onEnter(){
	Layer::onEnter();
	addCustomEventlistener();
}


void FriendAddView::onExit(){
	Layer::onExit();
	_eventDispatcher->removeEventListener(friendSearchListener);
    _eventDispatcher->removeEventListener(quickAddFriendListener);
}

void FriendAddView::showDialog(){
	MenuItem* item1 = MenuItem::create();
	item1->setContentSize(Size(1280, 720));
	Menu* menu1 = Menu::create(item1, NULL);
	this->addChild(menu1);

	auto all_bg = Sprite::create("common/all_bg.jpg");
	all_bg->setPosition(640, 360);
	addChild(all_bg);


	auto  dialogBg = Sprite::create("common/dialog_bg.png");
	dialogBg->setPosition(640, 360);
	this->addChild(dialogBg);

	auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(FriendAddView::closeView, this));
	auto closeMenu = Menu::create(closeImage, NULL);
	closeMenu->setPosition(980, 580);
	addChild(closeMenu);

	auto paodai = Sprite::create("common/piaodai_zi.png");
	paodai->setPosition(640, 590);
	this->addChild(paodai);
	auto icon = Sprite::create("friend/friend_title.png");
	icon->setPosition(640, 615);
	addChild(icon);

	Scale9Sprite* tabBg = Scale9Sprite::create("common/tab_bg.png");
	tabBg->setContentSize(Size(360, 71));
	tabBg->setPosition(475, 525);
	addChild(tabBg);

	auto searchImage1 = MenuItemImage::create("common/tab_btn_1.png", "common/tab_btn_1.png");
	auto searchImage2 = MenuItemImage::create("common/tab_btn_2.png", "common/tab_btn_2.png");
	searchToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(FriendAddView::clickTabBtn, this), searchImage1, searchImage2, NULL);
	searchToggle->setTag(0);
	searchToggle->setSelectedIndex(1);

	auto quickImage1 = MenuItemImage::create("common/tab_btn_1.png", "common/tab_btn_1.png");
	auto quickImage2 = MenuItemImage::create("common/tab_btn_2.png", "common/tab_btn_2.png");
	quickToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(FriendAddView::clickTabBtn, this), quickImage1, quickImage2, NULL);
	quickToggle->setTag(1);

	auto menu = Menu::create(searchToggle, quickToggle, NULL);
	menu->alignItemsHorizontallyWithPadding(5);
	menu->setPosition(475, 523);
	addChild(menu);

	searchSprite = Sprite::create("friend/search_friend_2.png");
	searchSprite->setPosition(390, 525);
	addChild(searchSprite);


	quickSpite = Sprite::create("friend/quick_add_1.png");
	quickSpite->setPosition(565, 525);
	addChild(quickSpite);

	tabLayer1 = Layer::create();
	tabLayer1->setVisible(true);
	addChild(tabLayer1);

	auto input_bg_1 = Scale9Sprite::create("common/input_box_bg.png");
	input_bg_1->setContentSize(Size(600, 81));
	input_bg_1->setPosition(640, 420);
	tabLayer1->addChild(input_bg_1);
	_editName = EditBox::create(Size(370, 81), Scale9Sprite::create());
	_editName->setPosition(Point(620, 420));
	_editName->setTag(0);
	_editName->setFont("arial", 24);
    _editName->setInputMode(EditBox::InputMode::SINGLE_LINE);
    _editName->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	_editName->setDelegate(this);
	tabLayer1->addChild(_editName);

	auto magnifier = Sprite::create("friend/magnifier.png");
	magnifier->setPosition(380, 420);
	tabLayer1->addChild(magnifier);
	hintInfo = Sprite::create("friend/input_hint_text.png");
	hintInfo->setPosition(510,420);
	tabLayer1->addChild(hintInfo);
	auto itemImage = MenuItemImage::create("friend/search_btn_1.png", "friend/search_btn_1.png",
		CC_CALLBACK_0(FriendAddView::clickSearch,this));
	Menu* searchMenu = Menu::create(itemImage,NULL);
	searchMenu->setPosition(835, 417);
	tabLayer1->addChild(searchMenu);

	auto wxItem = MenuItemImage::create("friend/wx_bnt_1.png", "friend/wx_bnt_1.png", 
		CC_CALLBACK_0(FriendAddView::clickWeChat,this));
	wxMenu = Menu::create(wxItem,NULL);
	wxMenu->setPosition(640,320);
	tabLayer1->addChild(wxMenu);

	wxText = Sprite::create("friend/wx_friend_text.png");
	wxText->setPosition(640, 200);
	tabLayer1->addChild(wxText);

	tabLayer2 = Layer::create();
	tabLayer2->setVisible(false);
	addChild(tabLayer2);

	auto quickText = Sprite::create("friend/quick_add_text.png");
	quickText->setPosition(640,420);
	tabLayer2->addChild(quickText);
	auto input_bg_2 = Sprite::create("friend/quick_add_bg.png");
	input_bg_2->setPosition(640, 290);
	tabLayer2->addChild(input_bg_2);
	_number = EditBox::create(Size(310, 81), Scale9Sprite::create());
	_number->setPosition(Point(640, 290));
    _number->setInputMode(EditBox::InputMode::PHONE_NUMBER);
    _number->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	_number->setTag(0);
	_number->setFont("arial", 24);
	_number->setDelegate(this);
	tabLayer2->addChild(_number);
	auto confirm = MenuItemImage::create("common/confirm_btn_1.png", "common/confirm_btn_2.png",
		CC_CALLBACK_0(FriendAddView::quickAdd, this));
	auto confirmMenu = Menu::create(confirm, NULL);
	confirmMenu->setPosition(640, 180);
	tabLayer2->addChild(confirmMenu);


}

void FriendAddView::clickTabBtn(Ref* ref){
	MenuItemToggle* temp = (MenuItemToggle*)ref;
	if (temp->getTag() == 0){
		searchToggle->setSelectedIndex(1);
		quickToggle->setSelectedIndex(0);
		searchSprite->setTexture("friend/search_friend_2.png");
		quickSpite->setTexture("friend/quick_add_1.png");
		tabLayer1->setVisible(true);
		tabLayer2->setVisible(false);
        if(NULL != getChildByTag(1001)){
            getChildByTag(1001)->removeFromParent();
        }
		wxText->setVisible(true);
		wxMenu->setVisible(true);
	}
	else if (temp->getTag() == 1){
		searchToggle->setSelectedIndex(0);
		quickToggle->setSelectedIndex(1);
		searchSprite->setTexture("friend/search_friend_1.png");
		quickSpite->setTexture("friend/quick_add_2.png");
		tabLayer1->setVisible(false);
		tabLayer2->setVisible(true);
        if(NULL != getChildByTag(1001)){
            getChildByTag(1001)->removeFromParent();
        }
	}

}

void FriendAddView::closeView(){

	removeFromParent();
}

void FriendAddView::clickSearch(){
    std::string key = _editName->getText();
    if(key!= ""){
        Loading* load = Loading::create();
        load->setTag(1000);
        addChild(load);
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getSearchFriendCommand(key));
    }
}

void FriendAddView::clickWeChat(){
	
}

void FriendAddView::quickAdd(){
    std::string key = _number->getText();
    if(key!= ""){
        Loading* load = Loading::create();
        load->setTag(1000);
        addChild(load);
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getAddFriendQuickCommand(key));
    }

}

void FriendAddView::addCustomEventlistener(){
	friendSearchListener = EventListenerCustom::create(MSG_SEARCH_FRIEND_RESULT, [=](EventCustom* event){
        if(NULL != getChildByTag(1000)){
            getChildByTag(1000)->removeFromParent();
        }
        if(NULL != getChildByTag(1001)){
            getChildByTag(1001)->removeFromParent();
        }
        SearchResult* resultLayer = SearchResult::create();
        resultLayer->setTag(1001);
        addChild(resultLayer);
		wxText->setVisible(false);
		wxMenu->setVisible(false);
	});
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(friendSearchListener, 1);
    
    quickAddFriendListener =EventListenerCustom::create(MSG_PLAYER_ADD_FRIEND_QUICK, [=](EventCustom* event){
        std::string result = static_cast<char*>(event->getUserData());
        if(NULL != getChildByTag(1000)){
            getChildByTag(1000)->removeFromParent();
        }
        if (result == "1"){
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getFriendListCommand());
            HintDialog* hint = HintDialog::create("添加好友成功",false);
            addChild(hint);
        }else{
            HintDialog* hint = HintDialog::create("添加好友失败",false);
            addChild(hint);
        }

    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(quickAddFriendListener, 1);
    
}



void FriendAddView::editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox){
	hintInfo->setVisible(false);
}

void FriendAddView::editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox){

}

void FriendAddView::editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text){


}

void FriendAddView::editBoxReturn(cocos2d::extension::EditBox* editBox){


}
