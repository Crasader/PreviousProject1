#include"mahjong/gameview/MjGameScene.h"
#include "mahjong/gameview/suzhou/normal/SuZhouView.h"
#include "mahjong/gameview/suzhou/review/SuZhouReview.h"
#include "mahjong/gameview/hongzhong/normal/HongZhongView.hpp"
#include "mahjong/gameview/hongzhong/review/HongZhongReview.hpp"
#include "mahjong/gameview/baida/normal/BaiDaView.h"
#include "mahjong/gameview/baida/review/BaiDaReview.h"
#include "mahjong/gameview/fanpai/normal/FanPaiView.hpp"
#include "mahjong/gameview/fanpai/review/FanPaiReview.hpp"

bool MjGameScene::init(){
    if (!Scene::init()){
        return false;
    }
    if(GAMEDATA::getInstance()->getGameType() == 1){
        SuZhouView* mjView = SuZhouView::create();
        addChild(mjView);
    }else if(GAMEDATA::getInstance()->getGameType() == 2){
        SuZhouReview* gview = SuZhouReview::create();
        addChild(gview);
    }else if(GAMEDATA::getInstance()->getGameType() == 3){
        HongZhongView* view = HongZhongView::create();
        addChild(view);
    }else if(GAMEDATA::getInstance()->getGameType() == 4){
        HongZhongReview* view = HongZhongReview::create();
        addChild(view);
    }else if(GAMEDATA::getInstance()->getGameType() == 5){
        BaiDaView* mjView = BaiDaView::create();
        addChild(mjView);
    }else if(GAMEDATA::getInstance()->getGameType() == 6){
        BaiDaReview* mjView = BaiDaReview::create();
        addChild(mjView);
    }else if(GAMEDATA::getInstance()->getGameType() == 7){
        FanPaiView* mjView = FanPaiView::create();
        addChild(mjView);
    }else if(GAMEDATA::getInstance()->getGameType() == 8){
        FanPaiReview* mjView = FanPaiReview::create();
        addChild(mjView);
    }else{
        log("gametype is error ...");
    }
    GAMEDATA::getInstance()->setLogingGame(true);
    return true;
}

void MjGameScene::onEnter(){
    Scene::onEnter();
}


void MjGameScene::onExit(){
    Scene::onExit();
}
