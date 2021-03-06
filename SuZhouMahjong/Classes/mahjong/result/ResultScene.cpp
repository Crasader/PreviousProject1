//
//  ResultScene.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/5/17.
//
//

#include "mahjong/result/ResultScene.hpp"
#include "mahjong/result/suzhou/normal/SZNormalResultLayer.hpp"
#include "mahjong/result/suzhou/special/SZSpecialResultLayer.hpp"
#include "mahjong/result/hongzhong/normal/HZNormalResultLayer.hpp"
#include "mahjong/result/hongzhong/special/HZSpecialResultLayer.hpp"
#include "mahjong/result/baida/normal/BDNormalResultLayer.hpp"
#include "mahjong/result/baida/special/BDSpecialResultLayer.hpp"
#include "mahjong/result/fanpai/normal/FPNormalResultLayer.hpp"
#include "mahjong/result/fanpai/special/FPSpecialResultLayer.hpp"
#include "mahjong/common/jong/Jong.h"
#include "mahjong/common/dialog/prompt/HintDialog.hpp"
#include "mahjong/common/utils/SeatIdUtil.h"
#include "mahjong/common/utils/StringUtil.h"
#include "mahjong/common/utils/Chinese.h"
#include "mahjong/common/widget/ParticleUtil.hpp"
#include "mahjong/lobby/LobbyScene.h"
#include "mahjong/lobby/dialog/EnterRoomDialog.hpp"
#include "mahjong/lobby/shop/gold/GoldNotEnoughDialog.hpp"
#include "mahjong/lobby/shop/gold/ChargeGold.hpp"
#include "mahjong/gameview/MjGameScene.h"
#include "server/NetworkManage.h"
#include "server/CommandManage.h"

Scene* ResultScene::createScene(int type)
{
    auto scene = Scene::create();
    if(GAMEDATA::getInstance()->getGameType()==1){
        if(type == 0){
            SZNormalResultLayer* layer = SZNormalResultLayer::create();
            scene->addChild(layer);
        }else{
            SZSpecialResultLayer* layer = SZSpecialResultLayer::create();
            scene->addChild(layer);
        }
    }else if(GAMEDATA::getInstance()->getGameType() == 3){
        if(type == 0){
            HZNormalResultLayer* layer = HZNormalResultLayer::create();
            scene->addChild(layer);
        }else{
            HZSpecialResultLayer* layer = HZSpecialResultLayer::create();
            scene->addChild(layer);
        }
    }if(GAMEDATA::getInstance()->getGameType()==5){
        if(type == 0){
            BDNormalResultLayer* layer = BDNormalResultLayer::create();
            scene->addChild(layer);
        }else{
            BDSpecialResultLayer* layer = BDSpecialResultLayer::create();
            scene->addChild(layer);
        }
    }if(GAMEDATA::getInstance()->getGameType()==7){
        if(type == 0){
            FPNormalResultLayer* layer = FPNormalResultLayer::create();
            scene->addChild(layer);
        }else{
            FPSpecialResultLayer* layer = FPSpecialResultLayer::create();
            scene->addChild(layer);
        }
    }
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
        //resultData.nickName = "这里是装电视台";
        gameResults.push_back(resultData);
    }
    GAMEDATA::getInstance()->setGameResults(gameResults);
    GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
    GAMEDATA::getInstance()->setHeroSeatId(1);
    GAMEDATA::getInstance()->setCurrentBank(1);
    GAMEDATA::getInstance()->setNeedShowLastResult(true);
    FriendOpenRoomRespData opendata;
    opendata.prjushu ="8";
    opendata.prjucount ="2";
    GAMEDATA::getInstance()->setFriendOpenRoomResp(opendata);
    //----------------------------------------
}
