//
//  ResultScene.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/5/17.
//
//

#include "game/mahjong/result/ResultScene.hpp"
#include "game/mahjong/result/normal/NormalResultLayer.hpp"
#include "game/mahjong/result/special/SpecialResultLayer.hpp"
#include "game/mahjong/lobby/LobbyScene.h"
#include "game/mahjong/jong/Jong.h"
#include"game/mahjong/core/MjGameScene.h"
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

Scene* ResultScene::createScene(int type)
{
    //test--------------------------------------
    vector<GameResultData> gameResults;
    for (int i = 0; i < 4; i++){
        GameResultData resultData;
        resultData.result = 2;
        resultData.gold = 100;
        resultData.diamond = 100;
        resultData.jifen =10;
        resultData.lequan = 10;
        resultData.golddelta = 200000;
        resultData.diamonddelta =2;
        resultData.jifendelta = 2;
        resultData.lequandelta = 2000;
        resultData.seatId = i+1;
        resultData.hua = 3;
        resultData.showPoker = "1,2,3,4,5,5,5,5";
        resultData.huType = "1";
        resultData.nickName = "这里是装电视台";
        gameResults.push_back(resultData);
    }
    GAMEDATA::getInstance()->setGameResults(gameResults);
    GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
    GAMEDATA::getInstance()->setHeroSeatId(1);
    GAMEDATA::getInstance()->setPrivateLezi("0");
    GAMEDATA::getInstance()->setCurrentBank(1);
    FriendOpenRoomRespData opendata;
    opendata.prjushu ="8";
    opendata.prjucount ="2";
    GAMEDATA::getInstance()->setFriendOpenRoomResp(opendata);
    //-----------------------------------------
    
    auto scene = Scene::create();
    if(type == 0){
        NormalResultLayer* layer = NormalResultLayer::create();
        scene->addChild(layer);
    }else{
        SpecialResultLayer* layer = SpecialResultLayer::create();
        scene->addChild(layer);
    }
    return scene;
}


bool ResultScene::init(){
    if (!Scene::init()){
        return false;
    }
       return true;
}

void ResultScene::onEnter(){
    Scene::onEnter();
    continueAgainLisetner =  EventListenerCustom::create(MSG_HERO_CONTINUE_RESP, [=](EventCustom* event){
        std::string result  = static_cast<char*>(event->getUserData());
        if (GAMEDATA::getInstance()->getEnterRoomResp().result == "0"){
            Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
        }else if (GAMEDATA::getInstance()->getEnterRoomResp().result == "1"){
            //返回正常可以继续游戏
            GAMEDATA::getInstance()->setContinueAgain(true);
            Director::getInstance()->replaceScene(TransitionFade::create(1, MjGameScene::create()));
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(continueAgainLisetner, 1);
    
    //登录地址变更
    playerReplaceLoginListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_PLAYER_REPLACE_LOGIN, [=](EventCustom* event){
        HintDialog* hin = HintDialog::create("你的账号在其他客户端登录",[=](Ref* ref){
            exit(0);
        });
        addChild(hin,5);
    });
}

void ResultScene::onExit(){
    Scene::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(continueAgainLisetner);
    Director::getInstance()->getEventDispatcher()->removeEventListener(playerReplaceLoginListener);
}

