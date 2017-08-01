//
//  OtherPlayerInfo.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/5/18.
//
//

#include "mahjong/common/heroinfo/OtherPlayerInfo.hpp"
#include "mahjong/common/dialog/prompt/HintDialog.hpp"
#include "mahjong/common/widget/HeadImage.hpp"
#include "mahjong/common/state/GameData.h"
#include "mahjong/common/utils/Chinese.h"
#include "mahjong/common/utils/SeatIdUtil.h"
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
}

void OtherPlayerInfo::onExit(){
    Layer::onExit();
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
    nickNameLabel->setColor(Color3B(116, 90, 61));
    nickNameLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    nickNameLabel->setPosition(130, 190);
    dialogBg->addChild(nickNameLabel);
    
    
    std::string gen = player->getGender() == 0 ? "playerinfo/female.png" : "playerinfo/male.png";
    auto playerGender = Sprite::create(gen);
    playerGender->setPosition(nickNameLabel->getPositionX()+nickNameLabel->getContentSize().width+15, 192);
    playerGender->setScale(0.6f);
    dialogBg->addChild(playerGender);
    
    
    auto playerID= Label::createWithSystemFont(StringUtils::format("ID:%s",player->getUmark().c_str()), "arial", 20);
    playerID->setColor(Color3B(116, 90, 61));
    playerID->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    playerID->setPosition(130, 160);
    dialogBg->addChild(playerID);
    
    auto playerIP= Label::createWithSystemFont(StringUtils::format("IP:%s",player->getIP().c_str()), "arial", 20);
    playerIP->setColor(Color3B(116, 90, 61));
    playerIP->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    playerIP->setPosition(130, 130);
    dialogBg->addChild(playerIP);
    
    //fangka
    auto fangka_bg = Sprite::create("gameview/other_player_num_bg.png");
    fangka_bg->setPosition(90, 80);
    dialogBg->addChild(fangka_bg);
    auto fangka_icon = Sprite::create("common/fangka_icon.png");
    fangka_icon->setPosition(50, 77);
    fangka_icon->setScale(0.7f);
    dialogBg->addChild(fangka_icon);
    auto fangkaNum = Label::createWithSystemFont(StringUtils::format("%0.1f", player->getFangka()),
                                                 "arial",20);
    fangkaNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    fangkaNum->setColor(Color3B::WHITE);
    fangkaNum->setPosition(75, 80);
    dialogBg->addChild(fangkaNum);
    
    //话费券
    auto gold_bg = Sprite::create("gameview/other_player_num_bg.png");
    gold_bg->setPosition(220, 80);
    dialogBg->addChild(gold_bg);
    auto gold_icon = Sprite::create("gameview/other_player_gold.png");
    gold_icon->setPosition(178, 78);
    dialogBg->addChild(gold_icon);
    std::string gold_num = StringUtils::format("%d", player->getGold());
    if(player->getGold()>9999999){
		gold_num = StringUtils::format("%d%s", player->getGold() / 10000, ChineseWord("wan").c_str());
    }
    auto goldNum = Label::createWithSystemFont(gold_num,"arial",20);
    goldNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    goldNum->setColor(Color3B::WHITE);
    goldNum->setPosition(205, 80);
    dialogBg->addChild(goldNum);
    
    //lequan
    auto lequan_bg = Sprite::create("gameview/other_player_num_bg.png");
    lequan_bg->setPosition(90, 40);
    dialogBg->addChild(lequan_bg);
    auto lequan_icon = Sprite::create("common/lequan_icon.png");
    lequan_icon->setPosition(50, 37);
    lequan_icon->setScale(0.8f);
    dialogBg->addChild(lequan_icon);
    auto lequanNum = Label::createWithSystemFont(StringUtils::format("%d", player->getTicket()),"arial",20);
    lequanNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    lequanNum->setColor(Color3B::WHITE);
    lequanNum->setPosition(75, 40);
    dialogBg->addChild(lequanNum);
    
    return true;
}

void OtherPlayerInfo::closeView(){
    removeFromParent();
}
