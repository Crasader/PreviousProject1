//
//  OtherPlayerInfo.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/5/18.
//
//

#include "game/mahjong/heroinfo/OtherPlayerInfo.hpp"
#include "game/mahjong/dialog/prompt/HintDialog.hpp"
#include "game/mahjong/widget/HeadImage.hpp"
#include "game/mahjong/state/GameData.h"
#include "game/utils/Chinese.h"
#include "game/utils/SeatIdUtil.h"
#include "userdata/UserData.h"
#include "server/NetworkManage.h"

OtherPlayerInfo* OtherPlayerInfo::create(Player* player){
    OtherPlayerInfo* bRet = new OtherPlayerInfo();
    if (bRet&&bRet->init(player))
    {
        bRet->autorelease();
        return bRet;
    }
    else
    {
        delete bRet;
        bRet = NULL;
        return NULL;
    }
}

void OtherPlayerInfo::onEnter(){
    Layer::onEnter();
    addFriendRespListener2 = EventListenerCustom::create(MSG_ADD_FRIEND_RESP, [=](EventCustom* event){
        char* buf = static_cast<char*>(event->getUserData());
        std::string result = buf;
        if (result == "1"){
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getFriendListCommand());
            HintDialog* hint = HintDialog::create("添加好友成功",NULL);
            addChild(hint);
        }else{
            HintDialog* hint = HintDialog::create("添加好友失败",NULL);
            addChild(hint);
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(addFriendRespListener2, 1);
}

void OtherPlayerInfo::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(addFriendRespListener2);
}



bool OtherPlayerInfo::init(Player* player){
    if(!Layer::init()){
        return false;
    }
    setPlayer(player);
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    item1->setCallback(CC_CALLBACK_0(OtherPlayerInfo::closeView, this));
    Menu* menu1 = Menu::create(item1, NULL);
    addChild(menu1);
    auto  dialogBg = Sprite::create("gameview/other_player_bg.png");
    int cSeatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), player->getSeatId());
    if(cSeatId == ClientSeatId::left){
        dialogBg->setPosition(265, 455);
    }else if(cSeatId == ClientSeatId::opposite){
        dialogBg->setPosition(745, 605);
    }else if(cSeatId == ClientSeatId::right){
        dialogBg->setPosition(1015, 455);
    }else{
        dialogBg->setPosition(275, 220);
    }
    addChild(dialogBg);
    
    
    auto headBg = HeadImage::createByImage(player->getPicture(), Size(90,90));
    headBg->setPosition(70,160);
    dialogBg->addChild(headBg);
    
    
    auto nickNameLabel = Label::createWithSystemFont(player->getNickname(), "arial", 20);
    nickNameLabel->setColor(Color3B(87, 195, 186));
    nickNameLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    nickNameLabel->setPosition(130, 190);
    dialogBg->addChild(nickNameLabel);
    
    
    std::string gen = player->getGender() == 0 ? "playerinfo/female.png" : "playerinfo/male.png";
    auto playerGender = Sprite::create(gen);
    playerGender->setPosition(nickNameLabel->getPositionX()+nickNameLabel->getContentSize().width+15, 192);
    playerGender->setScale(0.6f);
    dialogBg->addChild(playerGender);
    
    
    auto playerID= Label::createWithSystemFont(StringUtils::format("ID:%s",player->getUmark().c_str()), "arial", 20);
    playerID->setColor(Color3B(87, 195, 186));
    playerID->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    playerID->setPosition(130, 160);
    dialogBg->addChild(playerID);
    
    auto playerIP= Label::createWithSystemFont(StringUtils::format("IP:%s",player->getIP().c_str()), "arial", 20);
    playerIP->setColor(Color3B(87, 195, 186));
    playerIP->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    playerIP->setPosition(130, 130);
    dialogBg->addChild(playerIP);
    
    //fangka
    auto fangka_bg = Sprite::create("gameview/other_player_num_bg.png");
    fangka_bg->setPosition(90, 80);
    dialogBg->addChild(fangka_bg);
    auto fangka_icon = Sprite::create("mjitem/fangka_icon.png");
    fangka_icon->setPosition(50, 75);
    fangka_icon->setScale(0.7f);
    dialogBg->addChild(fangka_icon);
    auto fangkaNum = Label::createWithSystemFont(StringUtils::format("%d", player->getFangka()),
                                                 "arial",20);
    fangkaNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    fangkaNum->setColor(Color3B(87, 195, 186));
    fangkaNum->setPosition(75, 80);
    dialogBg->addChild(fangkaNum);
    //gold
    auto gold_bg = Sprite::create("gameview/other_player_num_bg.png");
    gold_bg->setPosition(220, 80);
    dialogBg->addChild(gold_bg);
    auto gold_icon = Sprite::create("gameview/other_player_gold.png");
    gold_icon->setPosition(180, 75);
    dialogBg->addChild(gold_icon);
    std::string gold_num = StringUtils::format("%d", player->getGold());
    if(player->getGold()>9999999){
        gold_num = StringUtils::format("%d万", player->getGold()/10000);
    }
    auto goldNum = Label::createWithSystemFont(gold_num,"arial",20);
    goldNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    goldNum->setColor(Color3B(87, 195, 186));
    goldNum->setPosition(198, 80);
    dialogBg->addChild(goldNum);
    //lequan
    auto lequan_bg = Sprite::create("gameview/other_player_num_bg.png");
    lequan_bg->setPosition(90, 40);
    dialogBg->addChild(lequan_bg);
    auto lequan_icon = Sprite::create("gameview/other_player_lequan.png");
    lequan_icon->setPosition(50, 35);
    dialogBg->addChild(lequan_icon);
    auto lequanNum = Label::createWithSystemFont(StringUtils::format("%d", player->getTicket()),"arial",20);
    lequanNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    lequanNum->setColor(Color3B(87, 195, 186));
    lequanNum->setPosition(75, 40);
    dialogBg->addChild(lequanNum);
    
    return true;
}

void OtherPlayerInfo::closeView(){
    removeFromParent();
}
