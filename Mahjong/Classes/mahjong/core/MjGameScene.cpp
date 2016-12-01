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
    enterFrinedRoomListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_ENTER_FRIEND_ROOM_RESP, [=](EventCustom* event){
        char* buf = static_cast<char*>(event->getUserData());
        std::string result = buf;
        if (result == "1"){
            if(NULL!= getChildByTag(100)){
                getChildByTag(100)->removeFromParent();
            }
            GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
            MahjongView* mjView = MahjongView::create();
            mjView->setTag(100);
            addChild(mjView);
        }
        else if(result == "2"){
            HintDialog* invite = HintDialog::create("房间已坐满",NULL);
            addChild(invite,4);
        }  else if(result == "4"){
            HintDialog* invite = HintDialog::create("房间号错误",NULL);
            addChild(invite,4);
        }
    });
}


void MjGameScene::onExit(){
    Scene::onExit();
    
    Director::getInstance()->getEventDispatcher()->removeEventListener(enterFrinedRoomListener);
}
