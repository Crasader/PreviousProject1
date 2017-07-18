//
//  DissovleRoomDialog.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/7/10.
//
//

#include "mahjong/common/dialog/dissolve/DissovleRoomDialog.hpp"
#include "mahjong/common/state/GameData.h"
#include "userdata/UserData.h"
#include "server/NetworkManage.h"
#include "mahjong/lobby/LobbyScene.h"

bool DissovleRoomDialog::init(){
    if(!Layer::init()){
        return false;
    }
    GAMEDATA::getInstance()->setDissovleDialogRemove(false);
    
    auto bg0 = LayerColor::create(Color4B(0, 0, 0, 204), 1280, 720);
    addChild(bg0);
    
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
    
    auto  dialogBg = Sprite::create("common/dialog_bg.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    
    auto titleIcon = Sprite::create("dissolve/dissovle_room.png");
    titleIcon->setPosition(640, 575);
    addChild(titleIcon);
    
    //显示谁主动提出解散房间
    auto wanjia = Label::createWithSystemFont(StringUtils::format("玩家%s要求解散房间,是否同意",GAMEDATA::getInstance()->getDissolveName().c_str()), "arial", 30);
    wanjia->setColor(Color3B(70,40,20));
    wanjia->setPosition(327,525);
    wanjia->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(wanjia);
    
    auto time = Label::createWithSystemFont(StringUtils::format("(%d秒后自动同意)",residueTime), "arial", 30);
    time->setColor(Color3B(70,40,20));
    time->setPosition(640,275);
    addChild(time);
    
    for(int i=0;i<GAMEDATA::getInstance()->getPlayersInfo().size();i++){
        DissolveItem* item = DissolveItem::create(GAMEDATA::getInstance()->getPlayersInfo().at(i)->getNickname(),GAMEDATA::getInstance()->getPlayersInfo().at(i)->getPoxiaoId());
        item->setPosition(475+330*(i%2),440-(i/2)*100);
        addChild(item);
        items.push_back(item);
        if(GAMEDATA::getInstance()->getPlayersInfo().at(i)->getNickname() == GAMEDATA::getInstance()->getDissolveName()){
            item->updateState(1);
        }
    }
    
    img1 = MenuItemImage::create("dissolve/agree_1.png", "dissolve/agree_2.png","dissolve/agree_3.png",CC_CALLBACK_0(DissovleRoomDialog::doAgree,this));
    img2 = MenuItemImage::create("dissolve/dis_agree_1.png", "dissolve/dis_agree_2.png", "dissolve/dis_agree_3.png",CC_CALLBACK_0(DissovleRoomDialog::doNotAgree, this));
    auto menu = Menu::create(img1,img2,NULL);
    menu->alignItemsHorizontallyWithPadding(50);
    menu->setPosition(640,200);
    addChild(menu);
    if(UserData::getInstance()->getNickName() == GAMEDATA::getInstance()->getDissolveName()){
        img1->setEnabled(false);
        img2->setEnabled(false);
    }
    scheduleUpdate();
    return true;
}

void DissovleRoomDialog::doAgree(){
    img1->setEnabled(false);
    img2->setEnabled(false);
    for(int i=0; i<items.size();i++){
        if(items.at(i)->getPoxiaoId() == UserData::getInstance()->getPoxiaoId()){
            items.at(i)->updateState(1);
        }
    }
    // 发送协议
    if(GAMEDATA::getInstance()->getGameType() == 1){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getDissolveRoomSelectCommand("1"));
    }else if(GAMEDATA::getInstance()->getGameType() == 3){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getHZDissolveRoomSelectCommand("1"));
    }
    checkAllConfirm();
}


void DissovleRoomDialog::doNotAgree(){
    img1->setEnabled(false);
    img2->setEnabled(false);
    for(int i=0; i<items.size();i++){
        if(items.at(i)->getPoxiaoId() == UserData::getInstance()->getPoxiaoId()){
            items.at(i)->updateState(2);
        }
    }
    // 发送协议
    if(GAMEDATA::getInstance()->getGameType() == 1){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getDissolveRoomSelectCommand("0"));
    }else if(GAMEDATA::getInstance()->getGameType() == 3){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getHZDissolveRoomSelectCommand("0"));
    }
    checkAllConfirm();
}

void DissovleRoomDialog::onEnter(){
    Layer::onEnter();
    dissovleListener = EventListenerCustom::create(MSG_DISSOVLE_ROOM_SELECTED_NOTIFY, [=](EventCustom* event){
        for(int i=0; i<items.size();i++){
            if(items.at(i)->getPoxiaoId() == GAMEDATA::getInstance()->getDissolveData().pid){
                items.at(i)->updateState(GAMEDATA::getInstance()->getDissolveData().agree == "1"?1:2);
            }
        }
        checkAllConfirm();
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(dissovleListener, 1);
}


void DissovleRoomDialog::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(dissovleListener);
}

void DissovleRoomDialog::update(float dt){

}

void DissovleRoomDialog::checkAllConfirm(){
    bool needRemove =  false;
    int count = 0;
    for(int i=0; i<items.size();i++){
        if(items.at(i)->getConfirm() == 2){
            needRemove =  true;
        }else if(items.at(i)->getConfirm() > 0){
            count++;
        }
    }
    if(needRemove||count == items.size()){
        GAMEDATA::getInstance()->setDissovleDialogRemove(true);
        schedule([=](float dt){
            removeFromParent();
        }, 0, 0, 2,"KKKKK");
    }
}
