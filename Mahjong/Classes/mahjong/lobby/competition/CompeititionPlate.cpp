//
//  CompeititionPlate.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/7/20.
//
//

#include "mahjong/lobby/competition/CompeititionPlate.hpp"
#include "mahjong/common/competition/CompetitonItem.hpp"
#include "mahjong/lobby/shop/fangka/FangkaNotEnoughDialog.hpp"
#include "mahjong/common/dialog/prompt/HintDialog.hpp"
#include "userdata/UserData.h"
#include "server/NetworkManage.h"
#include"mahjong/gameview/MjGameScene.h"

bool CompeititionPlate::init(){
    if(!Layer::init()){
        return false;
    }
    
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1,-1);
    
    auto bg = LayerColor::create(Color4B(0, 0, 0, 204), 1280, 720);
    addChild(bg);
    
    auto comebg = Sprite::create("competition/lobby_com_bg.png");
    comebg->setPosition(640,360);
    addChild(comebg);
    
    auto title = Sprite::create("competition/com_title.png");
    title->setPosition(640,645);
    addChild(title);
    
    auto close = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png",
                                       CC_CALLBACK_0(CompeititionPlate::closeView, this));
    
    auto menu =Menu::create(close,NULL);
    menu->setPosition(1090,635);
    addChild(menu,3);
    
    RoomListData newData = GAMEDATA::getInstance()->getRoomList();
    for (int i=0; i<newData.matchList.size();i++) {
        CompetitionRoomId roomId = (CompetitionRoomId)atoi(newData.matchList.at(i).roomId.c_str());
        CompetitonItem* com = CompetitonItem::create(roomId,newData.matchList.at(i).prize, newData.matchList.at(i).fangka,newData.matchList.at(i).rule);
        com->setPosition(640,535-128*i);
        addChild(com);
    }
    
    return true;
}

void CompeititionPlate::onEnter(){
    Layer::onEnter();
    joinResp = EventListenerCustom::create(MSG_JOIN_COMPETITION_RESP, [=](EventCustom* event){
        JoinCompetitionData* result = static_cast<JoinCompetitionData*>(event->getUserData());
        JoinCompetitionData newData = *result;
        if(newData.result == 1){
            GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
            GAMEDATA::getInstance()->setCompetitionId(newData.roomId);
            GAMEDATA::getInstance()->setCompetitionText(newData.text);
            GAMEDATA::getInstance()->setCompetitionNumber(newData.num);
            if(atoi(newData.roomId.c_str()) == CompetitionRoomId::Shanghai_High||atoi(newData.roomId.c_str()) == CompetitionRoomId::Shanghai_Normal){
                GAMEDATA::getInstance()->setIsCompetitionQueue(true);
                GAMEDATA::getInstance()->setGameType(1);
                Director::getInstance()->replaceScene(TransitionFade::create(0.1, MjGameScene::create()));
            }else{
                GAMEDATA::getInstance()->setIsCompetitionQueue(true);
                GAMEDATA::getInstance()->setGameType(3);
                Director::getInstance()->replaceScene(TransitionFade::create(0.1, MjGameScene::create()));
            }
        }else  if(newData.result == 2||newData.result == 3){
            HintDialog* dialog = HintDialog::create(newData.tip != ""?newData.tip:"功能暂不可用",[=](Ref* ref){
                removeFromParent();
            },[=](Ref* ref){
                removeFromParent();
            });
            addChild(dialog,100);
        }else{
            if(NULL != getChildByTag(1024)){
                getChildByTag(1024)->removeFromParentAndCleanup(true);
            }
            FangkaNotEnoughDialog* da =  FangkaNotEnoughDialog::create();
            if(GAMEDATA::getInstance()->getCompetitionId() == StringUtils::format("%d",CompetitionRoomId::Shanghai_High)||
               GAMEDATA::getInstance()->getCompetitionId() == StringUtils::format("%d",CompetitionRoomId::Hongzhong_High)){
                da->initView(5,24);
                
            }else{
                da->initView(1,5);
            }
            addChild(da);
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(joinResp, 1);
}


void CompeititionPlate::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(joinResp);
}

void CompeititionPlate::closeView(){
    removeFromParent();
}
