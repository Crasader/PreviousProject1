//
//  RankLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/7/6.
//
//

#include "mahjong/lobby/rank/RankLayer.hpp"
#include "server/NetworkManage.h"
#include "server/MsgConfig.h"

RankLayer* RankLayer::create(LobbyPaiHangData data){
    RankLayer* cell = new RankLayer();
    if(cell && cell->init(data)){
        cell -> autorelease();
        return cell;
    }
    CC_SAFE_DELETE(cell);
    return NULL;
}


bool RankLayer::init(LobbyPaiHangData data){

    auto rank_bg = Sprite::create("mjlobby/rank_bg.png");
    rank_bg->setPosition(280,360);
    addChild(rank_bg);
    
    auto yeqian = Sprite::create("mjlobby/tab_bg.png");
    yeqian->setPosition(280,547);
    addChild(yeqian);
    
    auto fen1 = Sprite::create("mjlobby/fen_ge.png");
    fen1->setPosition(200,547);
    addChild(fen1);
    
    auto fen2 = Sprite::create("mjlobby/fen_ge.png");
    fen2->setPosition(362,547);
    addChild(fen2);
    
    tab1 = MenuItemImage::create("mjlobby/rank_btn_1.png", "mjlobby/rank_btn_1.png", CC_CALLBACK_0(RankLayer::showRank1,this));
    auto tabMenu = Menu::create(tab1,NULL);
    tab1->setOpacity(0);
    tabMenu->setPosition(125,545);
    addChild(tabMenu);
    
    tab2 = MenuItemImage::create("mjlobby/rank_btn_1.png", "mjlobby/rank_btn_1.png", CC_CALLBACK_0(RankLayer::showRank2,this));
    tab2->setOpacity(0);
    auto tabMenu2 = Menu::create(tab2,NULL);
    tabMenu2->setPosition(280,545);
    addChild(tabMenu2);
    
    tab3 = MenuItemImage::create("mjlobby/rank_btn_1.png", "mjlobby/rank_btn_1.png", CC_CALLBACK_0(RankLayer::showRank3,this));
    tab3->setOpacity(0);
    auto tabMenu3 = Menu::create(tab3,NULL);
    tabMenu3->setPosition(435,545);
    addChild(tabMenu3);
    
    rankName1 = Label::createWithSystemFont(data.name1, "arial", 25);
    rankName1->setColor(Color3B(177,88,8));
    rankName1->setPosition(125,545);
    addChild(rankName1,1);
    
    rankName2 = Label::createWithSystemFont(data.name2, "arial", 25);
    rankName2->setColor(Color3B(255,252,248));
    rankName2->setPosition(280,545);
    addChild(rankName2,1);
    
    rankName3 = Label::createWithSystemFont(data.name3, "arial", 25);
    rankName3->setColor(Color3B(255,252,248));
    rankName3->setPosition(435,545);
    addChild(rankName3,1);
    
    ranA = RankList::create();
    ranA->updateRankLayer(data.content1);
    addChild(ranA);
    
    return true;
}

void RankLayer::onEnterTransitionDidFinish(){
    
}

void RankLayer::onEnter(){
    Layer::onEnter();
    updateRank =  EventListenerCustom::create(MSG_UPDATE_LOBBY_RANK, [=](EventCustom* event){
        LobbyPaiHangData data = GAMEDATA::getInstance()->getLobbyPaiHangData();
        
        tab1->setOpacity(255);
        rankName1->setString(data.name1);
        rankName2->setString(data.name2);
        rankName3->setString(data.name3);
        ranA->updateRankLayer(data.content1);
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(updateRank, 1);
}


void RankLayer::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(updateRank);
}

void RankLayer::showRank1(){
    tab1->setOpacity(255);
    tab2->setOpacity(0);
    tab3->setOpacity(0);
    rankName1->setColor(Color3B(177,88,8));
    rankName2->setColor(Color3B(255,252,248));
    rankName3->setColor(Color3B(255,252,248));
    ranA->updateRankLayer(GAMEDATA::getInstance()->getLobbyPaiHangData().content1);
}
void RankLayer::showRank2(){
    tab1->setOpacity(0);
    tab2->setOpacity(255);
    tab3->setOpacity(0);
    rankName2->setColor(Color3B(177,88,8));
    rankName1->setColor(Color3B(255,252,248));
    rankName3->setColor(Color3B(255,252,248));
    ranA->updateRankLayer(GAMEDATA::getInstance()->getLobbyPaiHangData().content2);
}
void RankLayer::showRank3(){
    tab1->setOpacity(0);
    tab2->setOpacity(0);
    tab3->setOpacity(255);
    rankName3->setColor(Color3B(177,88,8));
    rankName2->setColor(Color3B(255,252,248));
    rankName1->setColor(Color3B(255,252,248));
    ranA->updateRankLayer(GAMEDATA::getInstance()->getLobbyPaiHangData().content3);
}
