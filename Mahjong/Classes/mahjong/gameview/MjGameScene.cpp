#include"mahjong/gameview/MjGameScene.h"
#include"mahjong/gameview/shanghai/normal/MahjongView.h"
#include "mahjong/gameview/hongzhong/normal/HongZhongView.hpp"
#include "mahjong/gameview/chongming/normal/ChongMingView.h"

bool MjGameScene::init(){
    if (!Scene::init()){
        return false;
    }
    if(GAMEDATA::getInstance()->getGameType() == 3){
        HongZhongView* view = HongZhongView::create();
        addChild(view);
    } if(GAMEDATA::getInstance()->getGameType() == 5){
        ChongMingView* mjView = ChongMingView::create();
        addChild(mjView);
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
