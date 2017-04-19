#include"mahjong/gameview/MjGameScene.h"
#include"mahjong/gameview/shanghai/normal/MahjongView.h"
#include "mahjong/gameview/shanghai/special/ReviewGame.h"
#include "mahjong/gameview/hongzhong/normal/HongZhongView.hpp"
#include "mahjong/gameview/hongzhong/special/ReviewHongZhong.hpp"

bool MjGameScene::init(){
    if (!Scene::init()){
        return false;
    }
    if(GAMEDATA::getInstance()->getGameType() == 2){
        ReviewGame* gview = ReviewGame::create();
        addChild(gview);
    }else if(GAMEDATA::getInstance()->getGameType() == 3){
        HongZhongView* view = HongZhongView::create();
        addChild(view);
    }else if(GAMEDATA::getInstance()->getGameType() == 4){
        ReviewHongZhong* view = ReviewHongZhong::create();
        addChild(view);
    }else{
        MahjongView* mjView = MahjongView::create();
        addChild(mjView);
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
