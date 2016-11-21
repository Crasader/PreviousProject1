//
//  PublicResultLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/21.
//
//

#include "game/mahjong/result/normal/NormalResultLayer.hpp"
#include "game/mahjong/result/normal/PlayerResultCell.hpp"
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

bool NormalResultLayer::init(){
    if(!Layer::init()){
        return false;
    }
    timeToatal = 25;
    auto reslut_bg = Sprite::create("result/result_bg.jpg");
    reslut_bg->setPosition(640, 360);
    addChild(reslut_bg,-1);
    showGameResult();//结算界面标题
    showRoomInfo();
    showPlayerResluts();
    showLayerBtn();
    updateplayerData();
    return true;
}

void NormalResultLayer::showGameResult(){
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

void NormalResultLayer::showRoomInfo(){
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
        lezi->setPosition((Director::getInstance()->getVisibleSize().width-wid)/2,560);
        lezi->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        jucount->setPosition((Director::getInstance()->getVisibleSize().width-wid)/2+lezi->getContentSize().width,560);
        jucount->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        juNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
        juNum->setPosition(jucount->getPositionX()+45,jucount->getPositionY());
    }
}

void NormalResultLayer::showPlayerResluts(){
    vector<GameResultData> results = GAMEDATA::getInstance()->getGameResults();
    for (int i=0; i<results.size();i++) {
        PlayerResultCell* cell = PlayerResultCell::create(results.at(i));
        cell->setPosition(640,490-110*i);
        addChild(cell);
    }
}

void NormalResultLayer::showLayerBtn(){
    
    auto helpImage = MenuItemImage::create("result/xuan_yao_btn_1.png","result/xuan_yao_btn_2.png",
                                           CC_CALLBACK_0(NormalResultLayer::shareResult, this));
    auto feedImage = MenuItemImage::create("result/continue_btn_1.png","result/continue_btn_2.png",
                                           CC_CALLBACK_0(NormalResultLayer::continueGame, this));
    
    Menu* myMneu = Menu::create(helpImage,feedImage,NULL);
    myMneu->setPosition(640,60);
    myMneu->alignItemsHorizontallyWithPadding(160);
    addChild(myMneu);
    
    schedule(schedule_selector(NormalResultLayer::updateTime), 1.0f, kRepeatForever, 0);
}

void NormalResultLayer::updateplayerData(){
    for(GameResultData resData : GAMEDATA::getInstance()->getGameResults()){
        vector<Player*> players = GAMEDATA::getInstance()->getPlayersInfo();
        for (int i = 0; i < players.size(); i++){
            if (players.at(i)->getSeatId() == resData.seatId){
                players.at(i)->setDiamond(resData.diamond);
                players.at(i)->setLockDiamond(resData.bangzuan);
                players.at(i)->setGold(resData.gold);
                players.at(i)->setTicket(resData.lequan);
                players.at(i)->setScore(resData.jifen);
            }
        }
    }
}


void NormalResultLayer::shareResult(){
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string path =StringUtils::format("%s/mahjong_screen_shot.png",CallAndroidMethod::getInstance()->getSdCardDir().c_str());
    log("screenShot path = %s",path.c_str());
    utils::captureScreen(CC_CALLBACK_2(BillDetailInfo::afterCaptured, this) ,path);
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    std::string path =StringUtils::format("%smahjong_screen_shot.png",FileUtils::sharedFileUtils()->getWritablePath().c_str());
    log("screenShot path = %s",path.c_str());
    utils::captureScreen(CC_CALLBACK_2(BillDetailInfo::afterCaptured, this) ,path);
#endif
}


void NormalResultLayer::afterCaptured(bool succeed, const std::string &outputFile)
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

void NormalResultLayer::continueGame(){
    schedule([=](float dt){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getContinueGameCommand());
    }, 0.0f, 0.0f, 1.0f,"delayGame");
}


void NormalResultLayer::updateTime(float dt){
    if (isVisible()){
        timeToatal--;
        if (timeToatal <= 0){
            continueGame();
            timeToatal = 10000000000;//填一个极大值
        }
    }
}
