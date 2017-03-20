#include"mahjong/gameview/MjGameScene.h"
#include"mahjong/gameview/normal/MahjongView.h"
#include "mahjong/gameview/special/ReviewGame.h"

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
    GAMEDATA::getInstance()->setLogingGame(true);
    return true;
}

void MjGameScene::onEnter(){
    Scene::onEnter();
   }


void MjGameScene::onExit(){
    Scene::onExit();
}
