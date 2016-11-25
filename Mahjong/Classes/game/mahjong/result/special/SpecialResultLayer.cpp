//
//  PublicResultLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/21.
//
//

#include "game/mahjong/result/special/SpecialResultLayer.hpp"
#include "game/mahjong/result/special/GameResultCell.hpp"
#include "game/mahjong/lobby/LobbyScene.h"
#include "game/mahjong/jong/Jong.h"
#include "game/mahjong/core/MjGameScene.h"
#include "game/mahjong/core/MahjongView.h"
#include "game/mahjong/lobby/EnterRoomDialog.hpp"
#include "game/mahjong/shop/gold/GoldNotEnoughDialog.hpp"
#include "game/mahjong/shop/gold/ChargeGold.hpp"
#include "game/mahjong/dialog/prompt/HintDialog.hpp"
#include "game/utils/SeatIdUtil.h"
#include "game/utils/StringUtil.h"
#include "game/utils/Chinese.h"
#include "game/utils/ParticleUtil.hpp"
#include "server/NetworkManage.h"
#include "server/CommandManage.h"
#include "payment/android/CallAndroidMethod.h"
#import "payment/ios/IOSBridge.h"

bool SpecialResultLayer::init(){
    if(!Layer::init()){
        return false;
    }
    auto reslut_bg = Sprite::create("result/result_bg.jpg");
    reslut_bg->setPosition(640, 360);
    addChild(reslut_bg,-1);
    showResultTitle();//结算界面标题
    showGameReslut();
    showLayerBtn();
    return true;
}

void SpecialResultLayer::showResultTitle(){
    auto resultTitle = Sprite::create();
    resultTitle->setTexture("result/game_result_title.png");
    resultTitle->setPosition(640,625);
    addChild(resultTitle);
}


void SpecialResultLayer::showGameReslut(){
    auto infoBg = Sprite::create("result/result_game_bg.png");
    infoBg->setPosition(640, 340);
    addChild(infoBg);
    
    vector<GameResultData> results = GAMEDATA::getInstance()->getGameResults();
    for (int i=0; i<results.size();i++) {
        GameResultCell* cell = GameResultCell::create(results.at(i));
        cell->setPosition(250+260*i,340);
        addChild(cell);
    }
}

void SpecialResultLayer::showLayerBtn(){

    auto helpImage = MenuItemImage::create("result/xuan_yao_btn_1.png","result/xuan_yao_btn_2.png",
                                           CC_CALLBACK_0(SpecialResultLayer::shareResult, this));
    auto golobby = MenuItemImage::create("result/go_lobby_btn_1.png","result/go_lobby_btn_2.png",
                                           CC_CALLBACK_0(SpecialResultLayer::gotoLobby, this));
    
    Menu* myMneu = Menu::create(helpImage,golobby,NULL);
    myMneu->setPosition(640,60);
    myMneu->alignItemsHorizontallyWithPadding(160);
    addChild(myMneu);
    
    auto info = Sprite::create();
    info->setPosition(1050,40);
    addChild(info);
    if(GAMEDATA::getInstance()->getPrivateRoomType() == "16"){
        info->setTexture("result/game_over_16.png");
    }else{
        info->setTexture("result/game_over_8.png");
    }
}

void SpecialResultLayer::shareResult(){
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string path =StringUtils::format("%s/mahjong_screen_shot.png",CallAndroidMethod::getInstance()->getSdCardDir().c_str());
    log("screenShot path = %s",path.c_str());
    utils::captureScreen(CC_CALLBACK_2(SpecialResultLayer::afterCaptured, this) ,path);
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    std::string path =StringUtils::format("%smahjong_screen_shot.png",FileUtils::sharedFileUtils()->getWritablePath().c_str());
    log("screenShot path = %s",path.c_str());
    utils::captureScreen(CC_CALLBACK_2(SpecialResultLayer::afterCaptured, this) ,path);
#endif
}


void SpecialResultLayer::afterCaptured(bool succeed, const std::string &outputFile)
{
    if (succeed) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        CallAndroidMethod::getInstance()->shareImageToWeChat("mahjong_screen_shot.png", false);
#endif
        
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        IOSBridge::getInstance()->doWechatShareImg(outputFile, 0);
#endif
    }
}

void SpecialResultLayer::gotoLobby(){
    GAMEDATA::getInstance()->clearPlayersInfo();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getQuitRoomCommand());
    Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
}
