#include"mahjong/core/MjGameScene.h"
#include"mahjong/core/MahjongView.h"
#include "mahjong/dialog/prompt/HintDialog.hpp"
#include "server/NetworkManage.h"

bool MjGameScene::init(){
    if (!Scene::init()){
        return false;
    }
    MahjongView* mjView = MahjongView::create();
    mjView->setTag(100);
    addChild(mjView);
    return true;
}

void MjGameScene::onEnter(){
    Scene::onEnter();
   }


void MjGameScene::onExit(){
    Scene::onExit();
}
