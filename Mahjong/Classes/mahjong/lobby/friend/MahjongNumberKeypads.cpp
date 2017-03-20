//
//  NumberKeypads.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/10/17.
//
//

#include "mahjong/lobby/friend/MahjongNumberKeypads.hpp"
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
    closeImage->setScale(0.85f);
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(930, 565);
    addChild(closeMenu);
    
    numberShow = Label::createWithSystemFont("", "arial", 48);
    numberShow->setAnchorPoint(Point::ANCHOR_MIDDLE);
    numberShow->setPosition(640,490);
    addChild(numberShow);
    
    auto numberMenu = Menu::create();
    numberMenu->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(numberMenu);
    for(int i=0;i<12;i++){
        auto numebrBtn = MenuItemImage::create("friend/num_btn_1.png", "friend/num_btn_2.png", CC_CALLBACK_1(MahjongNumberKeypads::clickNumber, this));
        numebrBtn->setTag(i);
        numberMenu->addChild(numebrBtn);
        numebrBtn->setPosition(-185+(i%3)*185,36-(i/3)*74);
        if(i<10){
            auto numberLabel = Label::createWithSystemFont(StringUtils::format("%d",(i+1)%10), "arial", 48);
            numberLabel->setPosition(85,35);
            numberLabel->setColor(Color3B(239,239,239));
            numebrBtn->addChild(numberLabel);
        }else if (i==10){
            auto del = Sprite::create("friend/num_deleta.png");
            del->setPosition(85,35);
            numebrBtn->addChild(del);
        }else{
            auto ok = Sprite::create("friend/confirm_iamge.png");
            ok->setPosition(85,35);
            numebrBtn->addChild(ok);
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
    if(index == 11){
        std::string num = numberShow->getString();
        if(num.size() == 6){
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getEnterRoomByIdCommand(num));
        }
        removeFromParent();
    }else if(index == 10){
        //delete
        enterRoomNumber = enterRoomNumber.substr(0,enterRoomNumber.size()-1);
        numberShow->setString(enterRoomNumber);
    }else{
        enterRoomNumber = enterRoomNumber+ StringUtils::format("%d",(index+1)%10);
        numberShow->setString(enterRoomNumber);
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
