//
//  QuitRoomDialog.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/5/31.
//
//

#include "mahjong/gameview/widget/QuitRoomDialog.hpp"
#include "mahjong/lobby/LobbyScene.h"
#include "mahjong/common/state/GameData.h"
#include "server/NetworkManage.h"


bool QuitRoomDialog::init(){
    if(!Layer::init()){
        return false;
    }
    showDialog();
    return true;
}


void QuitRoomDialog::showDialog(){
    MenuItem* item = MenuItem::create();
    item->setContentSize(Size(1280, 720));
    Menu* bg = Menu::create(item, NULL);
    this->addChild(bg);
    
    auto quitBg = Sprite::create("common/dialog_bg_small.png");
    quitBg->setPosition(640,360);
    addChild(quitBg);
    
    auto text = Sprite::create("gameview/quit_room_text.png");
    text->setPosition(640,380);
    addChild(text);
    
    
    auto quitImage = MenuItemImage::create("common/confirm_btn_1.png","common/confirm_btn_1.png",CC_CALLBACK_0(QuitRoomDialog::quitRoom, this));
    quitImage->setScale(0.8f);
    auto continueImage = MenuItemImage::create("gameview/btn_not_1.png","gameview/btn_not_1.png",CC_CALLBACK_0(QuitRoomDialog::contiueGame, this));
    auto menu = Menu::create(quitImage,continueImage,NULL);
    menu->alignItemsHorizontallyWithPadding(10);
    menu->setPosition(640,260);
    addChild(menu);
}


void QuitRoomDialog::contiueGame(){
    removeFromParent();
}


void QuitRoomDialog::quitRoom(){
    GAMEDATA::getInstance()->clearPlayersInfo();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getPlayerInfoCommand());
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getQuitRoomCommand());
    Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
}
