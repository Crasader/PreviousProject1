//
//  PublicResultLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/21.
//
//

#include "game/mahjong/result/PublicResultLayer.hpp"
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

bool PublicResultLayer::init(){
    if(!Layer::init()){
        return false;
    }
    auto reslut_bg = Sprite::create("result/result_bg.jpg");
    reslut_bg->setPosition(640, 360);
    addChild(reslut_bg,-1);
    //test
    vector<GameResultData> gameResults;
    for (int i = 0; i < 4; i++){
        GameResultData resultData;
        resultData.result = 0;
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
        resultData.nickName = "abc";
        gameResults.push_back(resultData);
    }
    GAMEDATA::getInstance()->setGameResults(gameResults);
    GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
    GAMEDATA::getInstance()->setHeroSeatId(1);
    GAMEDATA::getInstance()->setPrivateLezi("0");
    FriendOpenRoomRespData opendata;
    opendata.prjushu ="8";
    opendata.prjucount ="2";
    GAMEDATA::getInstance()->setFriendOpenRoomResp(opendata);
    //-----------------------------------------
    showGameResult();//结算界面标题
    showRoomInfo();
    return true;
}

void PublicResultLayer::showGameResult(){
    vector<GameResultData> results = GAMEDATA::getInstance()->getGameResults();
    for (GameResultData data: results) {
        if(data.seatId == GAMEDATA::getInstance()->getHeroSeatId()){
            //result0为平,1为自摸,2为放炮 3胡牌  4输
            auto resultTitle = Sprite::create();
            resultTitle->setPosition(640,625);
            addChild(resultTitle);
            if(data.result == 0){
                resultTitle->setTexture("result/public_da_jiang_you.png");
            }else if(data.result == 1){
                 resultTitle->setTexture("result/public_zimo.png");
            }else if(data.result == 2){
                 resultTitle->setTexture("result/public_chuchong.png");
            }else if(data.result == 3){
                 resultTitle->setTexture("result/public_hupai.png");
            }else if(data.result == 4){
                 resultTitle->setTexture("result/public_shu.png");
            }
        }
    }
}

void PublicResultLayer::showRoomInfo(){
    if(GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom){
        auto lezi = Sprite::create();
        addChild(lezi);
        auto jucount = Sprite::create();
        addChild(jucount);
        if(GAMEDATA::getInstance()->getPrivateLezi() == "1"){
            //有乐子
            lezi->setTexture("result/public_40_lezi.png");
        }else{
             lezi->setTexture("result/public_wu_lezi.png");
        }
        if(GAMEDATA::getInstance()->getFriendOpenRoomResp().prjushu == "16"){
            jucount->setTexture("result/16ju_bg.png");
        }else{
            jucount->setTexture("result/8ju_bg.png");
        }
        auto juNum = LabelAtlas::create(StringUtils::format("%s",GAMEDATA::getInstance()->getFriendOpenRoomResp().prjucount.c_str()),"result/ju_num.png" , 16, 22, '0');
        addChild(juNum);
        
        int wid = lezi->getContentSize().width + jucount->getContentSize().width;
        lezi->setPosition((Director::getInstance()->getVisibleSize().width-wid)/2,555);
        lezi->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        jucount->setPosition((Director::getInstance()->getVisibleSize().width-wid)/2+lezi->getContentSize().width,555);
        jucount->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        juNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
        juNum->setPosition(jucount->getPositionX()+45,jucount->getPositionY());
    }
}
