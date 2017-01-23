#include"mahjong/core/MjGameScene.h"
#include"mahjong/core/MahjongView.h"
#include "mahjong/core/special/ReviewGame.h"

bool MjGameScene::init(){
    if (!Scene::init()){
        return false;
    }
    if(GAMEDATA::getInstance()->getIsFuPan()){
        ReviewGame* gview = ReviewGame::create();
        addChild(gview);
    }else{
        MahjongView* mjView = MahjongView::create();
        addChild(mjView);
    }
    return true;
}

void MjGameScene::onEnter(){
    Scene::onEnter();
   }


void MjGameScene::onExit(){
    Scene::onExit();
}
