//
//  PrideLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/10/9.
//
//

#include "game/mahjong/activities/PrideLayer.hpp"
#include "game/mahjong/activities/PropCell.hpp"
#include "game/mahjong/state/GameData.h"
#include "server/NetworkManage.h"
#include "game/mahjong/dialog/prompt/HintDialog.hpp"

bool PrideLayer::init(){
    if(!Layer::init()){
        return false;
    }
    drawLayerUi();
    return true;
}


void PrideLayer::onEnter(){
    Layer::onEnter();
    
    prideListListener = EventListenerCustom::create(MSG_ACTIVITY_PRIDE_LIST_INFO, [=](EventCustom* event){
        removeAllChildren();
        ActivityPrideList prideList = GAMEDATA::getInstance()->getActivityPrideList();
        for (int i=0; i<prideList.prideList.size(); i++) {
            PropCell* cell = PropCell::create(prideList.prideList.at(i).pid, prideList.prideList.at(i).rid,prideList.prideList.at(i).name, prideList.prideList.at(i).status);
            cell->setScale(0.88f);
            cell->setPosition(310+220*(i%4),380-210*(i/4));
            addChild(cell);
        }
        
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(prideListListener, 1);
    
    prideListener = EventListenerCustom::create(MSG_ACTIVITY_PRIDE_INFO, [=](EventCustom* event){
        std::string result = static_cast<char*>(event->getUserData()) ;
        if(result == "1"){
            HintDialog* dia = HintDialog::create("兑换成功", NULL);
            addChild(dia);
        }else{
            HintDialog* dia = HintDialog::create("兑换失败", NULL);
            addChild(dia);
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(prideListener, 1);
    
}

void PrideLayer::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(prideListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(prideListListener);
    
}

void PrideLayer::drawLayerUi(){
    ActivityPrideList prideList = GAMEDATA::getInstance()->getActivityPrideList();
    for (int i=0; i<prideList.prideList.size(); i++) {
        PropCell* cell = PropCell::create(prideList.prideList.at(i).pid, prideList.prideList.at(i).rid,prideList.prideList.at(i).name, prideList.prideList.at(i).status);
        cell->setScale(0.88f);
        cell->setPosition(310+220*(i%4),380-210*(i/4));
        addChild(cell);
    }
}