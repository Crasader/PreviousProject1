//
//  NumberKeypads.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/10/17.
//
//

#include "mahjong/lobby/friend/MahjongNumberKeypads.hpp"
#include "mahjong/common/state/GameData.h"
#include "server/NetworkManage.h"


bool MahjongNumberKeypads::init(){
    
    if(!Layer::init()){
        return false;
    }
    enterRoomNumber="";
    
    auto numbg = Sprite::create("friend/numberkeypads_bg.png");
    numbg->setTag(962);
    numbg->setPosition(640,350);
    addChild(numbg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(MahjongNumberKeypads::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(1065, 675);
    addChild(closeMenu);
    
    numberShow = Label::createWithSystemFont("", "arial", 68);
    numberShow->setAnchorPoint(Point::ANCHOR_MIDDLE);
    numberShow->setColor(Color3B(123,36,16));
    numberShow->setPosition(640,550);
    addChild(numberShow);
    
    auto numberMenu = Menu::create();
    numberMenu->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(numberMenu);
    for(int i=0;i<12;i++){
        auto numebrBtn = MenuItemImage::create("friend/num_btn_1.png", "friend/num_btn_2.png", CC_CALLBACK_1(MahjongNumberKeypads::clickNumber, this));
        numebrBtn->setTag(i);
        numberMenu->addChild(numebrBtn);
        numebrBtn->setPosition(-266+(i%3)*266,60-(i/3)*105);
        if(i<9){
            auto numberLabel = Label::createWithSystemFont(StringUtils::format("%d",(i+1)%10), "arial", 68);
            numberLabel->setPosition(125,55);
            numberLabel->setColor(Color3B(120,108,71));
            numebrBtn->addChild(numberLabel);
        }else if (i==9){
            auto ok = Sprite::create("friend/num_chongshu.png");
            ok->setPosition(125,55);
            numebrBtn->addChild(ok);
        }else if (i==10){
            auto numberLabel = Label::createWithSystemFont(StringUtils::format("%d",0), "arial", 68);
            numberLabel->setPosition(125,55);
            numberLabel->setColor(Color3B(120,108,71));
            numebrBtn->addChild(numberLabel);
        }else{
            auto del = Sprite::create("friend/num_deleta.png");
            del->setPosition(125,55);
            numebrBtn->addChild(del);
        }
        
    }
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(MahjongNumberKeypads::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(MahjongNumberKeypads::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);
    
    return true;
}

void MahjongNumberKeypads::clickNumber(Ref* ref){
    MenuItemImage* temp = (MenuItemImage*) ref;
    int index = temp->getTag();
    if(index == 9){
        //delete
        enterRoomNumber.clear();
        numberShow->setString(enterRoomNumber);
    }else if(index == 10){
        enterRoomNumber = enterRoomNumber+ StringUtils::format("%d",0);
        numberShow->setString(enterRoomNumber);
    }else if(index == 11){
        //back
        enterRoomNumber = enterRoomNumber.substr(0,enterRoomNumber.size()-1);
        numberShow->setString(enterRoomNumber);
    }else{
        enterRoomNumber = enterRoomNumber+ StringUtils::format("%d",(index+1)%10);
        numberShow->setString(enterRoomNumber);
    }
    std::string num = numberShow->getString();
    if(num.size() == 6){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getEnterRoomByIdCommand(num));
    }
}

void MahjongNumberKeypads::closeView(){
    removeFromParent();
}

bool MahjongNumberKeypads::onTouchBegan(Touch *touch, Event  *event){
    return true;
}

void MahjongNumberKeypads::onTouchEnded(Touch *touch, Event  *event){
    if(NULL != getChildByTag(962)){
        if(!((Sprite*)getChildByTag(962))->getBoundingBox().containsPoint(touch->getLocation())){
            removeFromParent();
        }
    }
}
