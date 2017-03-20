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
#include "mahjong/lobby/EnterRoomDialog.hpp"
#include "mahjong/lobby/shop/gold/GoldNotEnoughDialog.hpp"
#include "mahjong/lobby/shop/gold/ChargeGold.hpp"
#include "mahjong/common/jong/Jong.h"
#include "mahjong/common/dialog/prompt/HintDialog.hpp"
#include "mahjong/common/dialog/network/LostNetwork2.hpp"
#include "mahjong/common/utils/SeatIdUtil.h"
#include "mahjong/common/utils/StringUtil.h"
#include "mahjong/common/utils/Chinese.h"
#include "mahjong/common/widget/ParticleUtil.hpp"
#include "mahjong/gameview/MjGameScene.h"
#include "mahjong/gameview/normal/MahjongView.h"
#include "server/NetworkManage.h"
#include "server/CommandManage.h"
#include "wechat/android/CallAndroidMethod.h"
#include "wechat/ios/IOSBridge.h"

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
    scheduleUpdate();
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
    if(GAMEDATA::getInstance()->getPrivateRoomType() == "4"){
        info->setTexture("result/game_over_4.png");
    }else if(GAMEDATA::getInstance()->getPrivateRoomType() == "16"){
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

void SpecialResultLayer::onEnter(){
    Layer::onEnter();
    myCoreLoginRespListener = EventListenerCustom::create(MSG_LOGIN_RESP, [=](EventCustom* event){
        Director::getInstance()->replaceScene(TransitionFade::create(0.3, LobbyScene::create()));
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(myCoreLoginRespListener, 1);
    networkBreakListener = EventListenerCustom::create(MSG_NETWORK_BREAK_INFO, [=](EventCustom* event){
        if(NULL == getChildByTag(2000)){
            LostNetwork2* net = LostNetwork2::create();
            net->setTag(2000);
            addChild(net,200);
        }
        if(NetworkManage::getInstance()->reConnectSocket()){
            int  delayTime = 3.0f;
            schedule([=](float dt){
                if(UserData::getInstance()->getWxOpenId() ==  "unknow"){
                    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getVistorLoginAgain(UserData::getInstance()->getUserName(), UserData::getInstance()->getPassword()));
                }else{
                    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getThirdLoginCommand(UserData::getInstance()->getWxOpenId(), UserData::getInstance()->getWxUnionid(),UserData::getInstance()->getPicture(), StringUtils::format("%d",UserData::getInstance()->getGender()), UserData::getInstance()->getNickName(), GAMEDATA::getInstance()->getHsman(), GAMEDATA::getInstance()->getHstype(), GAMEDATA::getInstance()->getImsi(),GAMEDATA::getInstance()->getImei(),GAMEDATA::getInstance()->getAppVer(),true));
                }
            }, 0, 0, delayTime, "socket_reconnect2000");
            NetworkManage::getInstance()->startSocketBeat(CommandManage::getInstance()->getHeartCommmand());
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(networkBreakListener, 1);

}

void SpecialResultLayer::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(myCoreLoginRespListener);
     Director::getInstance()->getEventDispatcher()->removeEventListener(networkBreakListener);
}

void SpecialResultLayer::gotoLobby(){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getQuitRoomCommand());
    Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
}

void SpecialResultLayer::update(float dt){
    if(GAMEDATA::getInstance()->getShowProtected()){
        if(NULL == getChildByTag(2000)){
            LostNetwork2* net = LostNetwork2::create();
            net->setTag(2000);
            addChild(net,200);
        }
        GAMEDATA::getInstance()->setShowProtected(false);
    }
}
