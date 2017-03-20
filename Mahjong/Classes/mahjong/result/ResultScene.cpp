//
//  ResultScene.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/5/17.
//
//

#include "mahjong/result/ResultScene.hpp"
#include "mahjong/result/normal/NormalResultLayer.hpp"
#include "mahjong/result/special/SpecialResultLayer.hpp"
#include "mahjong/lobby/LobbyScene.h"
#include "mahjong/jong/Jong.h"
#include "mahjong/gameview/MjGameScene.h"
#include "mahjong/gameview/normal/MahjongView.h"
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

Scene* ResultScene::createScene(int type)
{
//    initTestData();
    auto scene = Scene::create();
    if(type == 0){
        NormalResultLayer* layer = NormalResultLayer::create();
        scene->addChild(layer);
    }else{
        SpecialResultLayer* layer = SpecialResultLayer::create();
        scene->addChild(layer);
    }
    GAMEDATA::getInstance()->setLogingGame(true);
    return scene;
}


bool ResultScene::init(){
    if (!Scene::init()){
        scheduleUpdate();
        return false;
    }
    return true;
}


void ResultScene::initTestData(){
    //test--------------------------------------
    vector<GameResultData> gameResults;
    for (int i = 0; i < 4; i++){
        GameResultData resultData;
        resultData.result = 1;
        resultData.gold = 100;
        resultData.diamond = 100;
        resultData.jifen =10;
        resultData.lequan = 10;
        resultData.golddelta = 200000;
        resultData.diamonddelta =2;
        resultData.jifendelta = 4000000;
        resultData.lequandelta = 222220;
        resultData.seatId = i+1;
        resultData.umark ="100010000";
        resultData.hua = 3;
        resultData.lz = "2";
        resultData.fan = "10";
        resultData.showPoker = "1,2,3,4,5,6,7,8,9,10,11,12,13,14";
        resultData.huType = "1,3";
        resultData.nickName = "这里是装电视台";
        gameResults.push_back(resultData);
    }
    GAMEDATA::getInstance()->setGameResults(gameResults);
    GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
    GAMEDATA::getInstance()->setHeroSeatId(1);
    GAMEDATA::getInstance()->setPrivateLezi("0");
    GAMEDATA::getInstance()->setCurrentBank(1);
    GAMEDATA::getInstance()->setNeedShowLastResult(true);
    FriendOpenRoomRespData opendata;
    opendata.prjushu ="8";
    opendata.prjucount ="2";
    GAMEDATA::getInstance()->setFriendOpenRoomResp(opendata);
    //----------------------------------------
}
