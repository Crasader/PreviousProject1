//
//  ShiMingLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/3/9.
//
//

#include "mahjong/lobby/shiming/ShiMingLayer.hpp"
#include "mahjong/common/state/GameData.h"
#include "server/NetworkManage.h"
#include "mahjong/common/utils/Chinese.h"

bool ShiMingLayer::init(){
    if(!Layer::init()){
        return false;
    }
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
    
    auto bg0 = LayerColor::create(Color4B(0, 0, 0, 204), 1280, 720);
    addChild(bg0);
    
    auto  dialogBg = Sprite::create("common/dialog_bg.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(ShiMingLayer::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(990, 590);
    addChild(closeMenu);
    
    auto paodai = Sprite::create("shiming/shi_ming_title.png");
    paodai->setPosition(640, 585);
    this->addChild(paodai);
    
    auto xingming = Sprite::create("shiming/xin_ming.png");
    xingming->setPosition(410,470);
    addChild(xingming);
    auto input_bg_1 = ui::Scale9Sprite::create("shiming/input_box_bg.png");
    input_bg_1->setContentSize(Size(430,81));
    input_bg_1->setPosition(710, 470);
    addChild(input_bg_1);
    
    auto sfz = Sprite::create("shiming/shen_fen_zhen.png");
    sfz->setPosition(410,370);
    addChild(sfz);
    auto input_bg_2 = ui::Scale9Sprite::create("shiming/input_box_bg.png");
    input_bg_2->setContentSize(Size(430, 81));
    input_bg_2->setPosition(710, 370);
    addChild(input_bg_2);
    
    auto sjh = Sprite::create("shiming/phone_num.png");
    sjh->setPosition(410,270);
    addChild(sjh);
    auto input_bg_3 = ui::Scale9Sprite::create("shiming/input_box_bg.png");
    input_bg_3->setContentSize(Size(430, 81));
    input_bg_3->setPosition(710, 270);
    addChild(input_bg_3);
    
    if(!GAMEDATA::getInstance()->getCertification()){
        _editName1 = ui::EditBox::create(Size(400, 50), ui::Scale9Sprite::create());
        _editName1->setPosition(Point(710, 470));
        _editName1->setTag(100);
        _editName1->setFont("arial", 24);
        _editName1->setPlaceHolder(ChineseWord("dialog_text_13").c_str());
        _editName1->setInputMode(cocos2d::ui::EditBox::InputMode::ANY);
        _editName1->setInputFlag(cocos2d::ui::EditBox::InputFlag::SENSITIVE);
        _editName1->setReturnType(cocos2d::ui::EditBox::KeyboardReturnType::DONE);
        _editName1->setDelegate(this);
        addChild(_editName1);
        
        _editName2 = ui::EditBox::create(Size(400, 50), ui::Scale9Sprite::create());
        _editName2->setPosition(Point(710, 370));
        _editName2->setTag(200);
        _editName2->setFont("arial", 24);
        _editName2->setPlaceHolder(ChineseWord("dialog_text_14").c_str());
        _editName2->setInputMode(cocos2d::ui::EditBox::InputMode::ANY);
        _editName2->setInputFlag(cocos2d::ui::EditBox::InputFlag::SENSITIVE);
        _editName2->setReturnType(cocos2d::ui::EditBox::KeyboardReturnType::DONE);
        _editName2->setDelegate(this);
        addChild(_editName2);
        
        _editName3 = ui::EditBox::create(Size(400, 50), ui::Scale9Sprite::create());
        _editName3->setPosition(Point(710, 270));
        _editName3->setTag(300);
        _editName3->setFont("arial", 24);
        _editName3->setPlaceHolder(ChineseWord("dialog_text_26").c_str());
        _editName3->setInputMode(cocos2d::ui::EditBox::InputMode::PHONE_NUMBER);
        _editName3->setInputFlag(cocos2d::ui::EditBox::InputFlag::SENSITIVE);
        _editName3->setReturnType(cocos2d::ui::EditBox::KeyboardReturnType::DONE);
        _editName3->setDelegate(this);
        addChild(_editName3);
        
        auto comfimImage = MenuItemImage::create("common/confirm_btn_1.png", "common/confirm_btn_2.png",CC_CALLBACK_0(ShiMingLayer::comfirmInfo, this));
        auto myMneu = Menu::create(comfimImage,NULL);
        myMneu->setPosition(640,170);
        addChild(myMneu);
        
        auto error = Sprite::create("shiming/error_code.png");
        error->setTag(400);
        error->setPosition(640,320);
        error->setVisible(false);
        addChild(error);
        
        auto error2 = Sprite::create("shiming/sjhsryw.png");
        error2->setTag(500);
        error2->setPosition(640,220);
        error2->setVisible(false);
        addChild(error2);
        
    }
    
    return true;
}


void ShiMingLayer::closeView(){
    removeFromParent();
}

void ShiMingLayer::onEnter(){
    Layer::onEnter();
    resultListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_GET_WAN_JIA_SHI_MING, [=](EventCustom* event){
        char* result = static_cast<char*>(event->getUserData());
        int newResult = atoi(result);
        if(NULL != getChildByTag(400)){
            if(newResult == 1){
                getChildByTag(400)->setVisible(false);
                removeFromParent();
                GAMEDATA::getInstance()->setCertification(true);
            }else if(newResult == 2){
                if(NULL != getChildByTag(500)){
                    getChildByTag(500)->setVisible(true);
                }
            }else{
                getChildByTag(400)->setVisible(true);
            }
        }
    });
}


void ShiMingLayer::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(resultListener);
}

void ShiMingLayer::comfirmInfo(){
    std::string name = _editName1->getText();
    std::string sfz = _editName2->getText();
    std::string sjh = _editName3->getText();
    if(name != "" && sfz != "" && sjh != ""){
        if(NULL != getChildByTag(500)){
            getChildByTag(500)->setVisible(false);
        }
        if(sjh.length() == 11){
             NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getCertification(name,sfz,sjh));
        }else{
            if(NULL != getChildByTag(500)){
                getChildByTag(500)->setVisible(true);
            }
        }
    }
}

void ShiMingLayer::editBoxEditingDidBegin(ui::EditBox* editBox){
    
    
}

void ShiMingLayer::editBoxEditingDidEnd(ui::EditBox* editBox){
    
}

void ShiMingLayer::editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text){
    
    
}

void ShiMingLayer::editBoxReturn(cocos2d::ui::EditBox* editBox){
    
    
}

