//
//  PublicResultLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/21.
//
//

#include "mahjong/result/special/SpecialResultLayer.hpp"
#include "mahjong/result/special/GameResultCell.hpp"
#include "mahjong/lobby/LobbyScene.h"
#include "mahjong/jong/Jong.h"
#include "mahjong/core/MjGameScene.h"
#include "mahjong/core/MahjongView.h"
#include "mahjong/lobby/EnterRoomDialog.hpp"
#include "mahjong/shop/gold/GoldNotEnoughDialog.hpp"
#include "mahjong/shop/gold/ChargeGold.hpp"
#include "mahjong/dialog/prompt/HintDialog.hpp"
#include "mahjong/utils/SeatIdUtil.h"
#include "mahjong/utils/StringUtil.h"
#include "mahjong/utils/Chinese.h"
#include "mahjong/widget/ParticleUtil.hpp"
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
    
    auto fanghao = Sprite::create("result/fang_jian_hao.png");
    fanghao->setPosition(940,570);
    addChild(fanghao,1);
    
    auto fanghaoNum = LabelAtlas::create(GAMEDATA::getInstance()->getFriendOpenRoomResp().prid, "result/ju_num.png",16,22,'0');
    fanghaoNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    fanghaoNum->setPosition(980,570);
    addChild(fanghaoNum);

    
    vector<GameResultData> results = GAMEDATA::getInstance()->getGameResults();
    for (int i=0; i<results.size();i++) {
        GameResultCell* cell = GameResultCell::create(results.at(i));
        cell->setPosition(250+260*i,340);
        addChild(cell);
    }
    //大结算的时候获取玩家信息
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getPlayerInfoCommand());
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
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getQuitRoomCommand());
    Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
}
