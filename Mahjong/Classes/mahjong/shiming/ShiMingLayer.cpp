//
//  ShiMingLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/3/9.
//
//

#include "mahjong/shiming/ShiMingLayer.hpp"
#include "mahjong/state/GameData.h"
#include "server/NetworkManage.h"

bool ShiMingLayer::init(){
    if(!Layer::init()){
        return false;
    }
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
    
    
    auto  dialogBg = Sprite::create("common/dialog_bg.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(ShiMingLayer::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(980, 580);
    addChild(closeMenu);
    
    auto paodai = Sprite::create("mjlobby/shi_ming_title.png");
    paodai->setPosition(640, 590);
    this->addChild(paodai);
    
    auto xingming = Sprite::create("mjlobby/xin_ming.png");
    xingming->setPosition(410,460);
    addChild(xingming);
    auto input_bg_1 = ui::Scale9Sprite::create("common/input_box_bg.png");
    input_bg_1->setContentSize(Size(430,81));
    input_bg_1->setPosition(710, 460);
    addChild(input_bg_1);
    
    auto sfz = Sprite::create("mjlobby/xin_ming.png");
    sfz->setPosition(410,350);
    addChild(sfz);
    auto input_bg_2 = ui::Scale9Sprite::create("common/input_box_bg.png");
    input_bg_2->setContentSize(Size(430, 81));
    input_bg_2->setPosition(710, 350);
    addChild(input_bg_2);
    
    if(GAMEDATA::getInstance()->getCertification()){
        //    Label* accountLabel = Label::createWithSystemFont("aaaa", "arial", 30);
        //    accountLabel->setColor(Color3B(93,172,221));
        //    accountLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        //    accountLabel->setPosition(630, 460);
        //    addChild(accountLabel);
        
        //    auto nickNameLabel = Label::createWithSystemFont("aaaaaaa", "arial", 30);
        //    nickNameLabel->setColor(Color3B(93, 172, 221));
        //    nickNameLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        //    nickNameLabel->setPosition(630, 350);
        //    addChild(nickNameLabel);
        
    }else{
        _editName1 = ui::EditBox::create(Size(400, 50), ui::Scale9Sprite::create());
        _editName1->setPosition(Point(710, 460));
        _editName1->setTag(100);
        _editName1->setFont("arial", 18);
        _editName1->setPlaceHolder("请输入姓名");
        _editName1->setInputMode(cocos2d::ui::EditBox::InputMode::ANY);
        _editName1->setInputFlag(cocos2d::ui::EditBox::InputFlag::SENSITIVE);
        _editName1->setReturnType(cocos2d::ui::EditBox::KeyboardReturnType::DONE);
        _editName1->setDelegate(this);
        addChild(_editName1);
        
        _editName2 = ui::EditBox::create(Size(400, 50), ui::Scale9Sprite::create());
        _editName2->setPosition(Point(710, 350));
        _editName2->setTag(200);
        _editName2->setFont("arial", 18);
        _editName2->setPlaceHolder("请输入身份证号码");
        _editName2->setInputMode(cocos2d::ui::EditBox::InputMode::ANY);
        _editName2->setInputFlag(cocos2d::ui::EditBox::InputFlag::SENSITIVE);
        _editName2->setReturnType(cocos2d::ui::EditBox::KeyboardReturnType::DONE);
        _editName2->setDelegate(this);
        addChild(_editName2);
        
        auto comfimImage = MenuItemImage::create("common/confirm_btn_1.png", "common/confirm_btn_1.png",CC_CALLBACK_0(ShiMingLayer::comfirmInfo, this));
        auto myMneu = Menu::create(comfimImage,NULL);
        myMneu->setPosition(640,200);
        addChild(myMneu);
        
        Label* error = Label::createWithSystemFont("输入的身份证号码不正确", "arial", 20);
        error->setTag(300);
        error->setColor(Color3B::RED);
        error->setPosition(640,300);
        error->setVisible(false);
        addChild(error);
    }
    
    
    
    return true;
}


void ShiMingLayer::closeView(){
    removeFromParent();
}

void ShiMingLayer::onEnter(){
    Layer::onEnter();
    resultListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_GET_WAN_JIA_SHI_MING, [=](EventCustom* event){
        std::string result = static_cast<char*>(event->getUserData());
        if(NULL != getChildByTag(300)){
            if(result == "0"){
                
                getChildByTag(300)->setVisible(true);
                
            }else{
                getChildByTag(300)->setVisible(false);
            }
        }
    });
}


void ShiMingLayer::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(resultListener);
}

void ShiMingLayer::comfirmInfo(){
    if(_editName1->getText() != "" && _editName2->getText() != "")
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getCertification(_editName1->getText(),_editName2->getText()));
}

void ShiMingLayer::editBoxEditingDidBegin(ui::EditBox* editBox){
    
    
}

void ShiMingLayer::editBoxEditingDidEnd(ui::EditBox* editBox){
    
}

void ShiMingLayer::editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text){
    
    
}

void ShiMingLayer::editBoxReturn(cocos2d::ui::EditBox* editBox){
    
    
}

