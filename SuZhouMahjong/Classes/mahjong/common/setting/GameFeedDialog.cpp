//
//  GameFeedDialog.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/7/6.
//
//

#include "mahjong/common/setting/GameFeedDialog.hpp"
#include "server/NetworkManage.h"

bool GameFeedDialog::init(){
    if(!Layer::init()){
        return false;
    }
    auto bg0 = LayerColor::create(Color4B(0, 0, 0, 150), 1280, 720);
    addChild(bg0);
    
    MenuItem* item = MenuItem::create();
    item->setContentSize(Size(1280, 720));
    Menu* bg = Menu::create(item, NULL);
    this->addChild(bg,-1);
    
    
    auto  dialogBg = Sprite::create("common/dialog_bg.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(GameFeedDialog::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(990, 590);
    addChild(closeMenu);
    
    auto icon = Sprite::create("rule/usr_feedback_title.png");
    icon->setPosition(640, 585);
    addChild(icon);
    
    
    auto input_bg = ui::Scale9Sprite::create("rule/input_box_bg.png");
    input_bg->setContentSize(Size(700,320));
    input_bg->setPosition(640, 390);
    addChild(input_bg);
    
    auto _editName = ui::EditBox::create(Size(670, 200), ui::Scale9Sprite::create());
    _editName->setPosition(Point(655, 400));
    _editName->setTag(0);
    _editName->setFont("arial", 24);
    _editName->setColor(Color3B(124,37,7));
    _editName->setInputMode(cocos2d::ui::EditBox::InputMode::ANY);
    _editName->setInputFlag(cocos2d::ui::EditBox::InputFlag::SENSITIVE);
    _editName->setReturnType(cocos2d::ui::EditBox::KeyboardReturnType::DONE);
    _editName->setDelegate(this);
    addChild(_editName);
    
    
    auto text = Sprite::create("rule/input_your_advice.png");
    text->setTag(1000);
    text->setPosition(640,380);
    addChild(text);
    
    auto confirm = MenuItemImage::create("common/confirm_btn_1.png", "common/confirm_btn_2.png",
                                         CC_CALLBACK_0(GameFeedDialog::clickComfirm, this));
    auto confirmMenu = Menu::create(confirm, NULL);
    confirmMenu->setPosition(640, 180);
    addChild(confirmMenu);
    
    
    
    return true;
}


void GameFeedDialog::onEnter() {
    Layer::onEnter();
    feedListener = EventListenerCustom::create("", [=](EventCustom* event){
        
        
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(feedListener, 1);
}


void GameFeedDialog::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(feedListener);
}


void GameFeedDialog::closeView(){
    removeFromParent();
}


void GameFeedDialog::clickComfirm(){
    if(NULL != getChildByTag(0)){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getFeedBackCommand(((EditBox*)getChildByTag(0))->getText()));
    }
    removeFromParent();
}


void GameFeedDialog::editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox){
    if(NULL != getChildByTag(1000)){
        getChildByTag(1000)->setVisible(false);
    }
    
}

void GameFeedDialog::editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox){
    
}

void GameFeedDialog::editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text){
    
    
}

void GameFeedDialog::editBoxReturn(cocos2d::extension::EditBox* editBox){
    
    
}
