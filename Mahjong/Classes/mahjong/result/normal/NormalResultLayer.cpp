//
//  PublicResultLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/21.
//
//

#include "mahjong/result/normal/NormalResultLayer.hpp"
#include "mahjong/result/normal/PlayerResultCell.hpp"
#include "mahjong/result/ResultScene.hpp"
#include "mahjong/lobby/goldroom/GoldRoomPlate.hpp"
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
#include "mahjong/dialog/network/LostNetwork.hpp"


bool NormalResultLayer::init(){
    if(!Layer::init()){
        return false;
    }
    auto reslut_bg = Sprite::create("result/result_bg.jpg");
    reslut_bg->setPosition(640, 360);
    addChild(reslut_bg,-1);
    showGameResult();//结算界面标题
    showRoomInfo();
    showPlayerResluts();
    showLayerBtn();
    updatePlayerData();
    return true;
}

void NormalResultLayer::showGameResult(){
    vector<GameResultData> results = GAMEDATA::getInstance()->getGameResults();
    for (GameResultData data: results) {
        if(data.seatId == GAMEDATA::getInstance()->getHeroSeatId()){
            //result0为平,1为自摸,2为放炮 3胡牌 4输
            auto resultTitle = Sprite::create();
            resultTitle->setPosition(640,625);
            addChild(resultTitle);
            if(data.result == 0){
                resultTitle->setTexture("result/public_da_jiang_you.png");
            }else if(data.result == 1){
                vector<std::string> hu = StringUtil::split(data.huType, ",");
                for(auto var:hu){
                    if(var == "3"){
                        resultTitle->setTexture("result/game_result_gangkai.png");
                        return;
                    }
                }
                resultTitle->setTexture("result/public_zimo.png");
                showPrideAnim(data);
            }else if(data.result == 2){
                resultTitle->setTexture("result/public_chuchong.png");
            }else if(data.result == 3){
                //检查是否含有杠开的胡牌类型
                resultTitle->setTexture("result/public_hupai.png");
                showPrideAnim(data);
            }else if(data.result == 4){
                resultTitle->setTexture("result/public_shu.png");
            }
        }
    }
}

void NormalResultLayer::showRoomInfo(){
    if(GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom){
        auto fanghao = Sprite::create("result/fang_jian_hao.png");
        fanghao->setPosition(900,560);
        addChild(fanghao,1);
        
        auto fanghaoNum = LabelAtlas::create(GAMEDATA::getInstance()->getFriendOpenRoomResp().prid, "result/ju_num.png",16,22,'0');
        fanghaoNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        fanghaoNum->setPosition(940,560);
        addChild(fanghaoNum);
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
    }else{
        auto xioahao = Sprite::create("result/mei_ju_xiao_hao.png");
        xioahao->setPosition(640,560);
        addChild(xioahao);
        auto fee = LabelAtlas::create(GAMEDATA::getInstance()->getFee(),"result/ju_num.png",16,22,'0');
        fee->setAnchorPoint(Point::ANCHOR_MIDDLE);
        fee->setPosition(665,560);
        addChild(fee,1);
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
    if(GAMEDATA::getInstance()->getNeedShowLastResult()){
        GAMEDATA::getInstance()->setNeedShowLastResult(false);
        schedule([=](float dt){
            Director::getInstance()->replaceScene(TransitionFade::create(0.8f,ResultScene::createScene(1)));
        }, 0, 0, 5,"KillBill");
    }else{
        auto quitImage = MenuItemImage::create("result/quit_btn_1.png","result/quit_btn_1.png",CC_CALLBACK_0(NormalResultLayer::gotoLobby, this));
        
        auto helpImage = MenuItemImage::create("result/xuan_yao_btn_1.png","result/xuan_yao_btn_2.png",
                                               CC_CALLBACK_0(NormalResultLayer::shareResult, this));
        auto feedImage = MenuItemImage::create("result/continue_btn_1.png","result/continue_btn_2.png",
                                               CC_CALLBACK_0(NormalResultLayer::continueGame, this));
        if(GAMEDATA::getInstance()->getMahjongRoomType() ==  MahjongRoom::privateRoom){
            auto iamge1 = Sprite::create("result/start_game_btn_1.png");
            feedImage->setNormalImage(iamge1);
            auto iamge2 = Sprite::create("result/start_game_btn_2.png");
            feedImage->setSelectedImage(iamge2);
        }
        Menu* myMneu = Menu::create();
        if(GAMEDATA::getInstance()->getMahjongRoomType() !=  MahjongRoom::privateRoom){
            myMneu->addChild(quitImage);
        }
        myMneu->addChild(helpImage);
        myMneu->addChild(feedImage);
        if(GAMEDATA::getInstance()->getMahjongRoomType() !=  MahjongRoom::privateRoom){
            myMneu->alignItemsHorizontallyWithPadding(60);
        }else{
            myMneu->alignItemsHorizontallyWithPadding(100);
        }
        myMneu->setPosition(640,60);
        addChild(myMneu);
        
        schedule(schedule_selector(NormalResultLayer::updateTime), 1.0f, kRepeatForever, 0);
    }
}

void NormalResultLayer::updatePlayerData(){
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

void NormalResultLayer::gotoLobby(){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getQuitRoomCommand());
    Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
}

void NormalResultLayer::showPrideAnim(GameResultData data){
    if(GAMEDATA::getInstance()->getMahjongRoomType() != MahjongRoom::privateRoom){
        if(data.golddelta>0&&data.lequandelta>0){
            ParticleUtil* par = ParticleUtil::create(MyParticleType::goldAndLequan);
            addChild(par,5);
        }else{
            ParticleUtil* par = ParticleUtil::create(MyParticleType::goldOnly);
            addChild(par,5);
        }
    }
}


void NormalResultLayer::shareResult(){
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string path =StringUtils::format("%s/mahjong_screen_shot.png",CallAndroidMethod::getInstance()->getSdCardDir().c_str());
    log("screenShot path = %s",path.c_str());
    utils::captureScreen(CC_CALLBACK_2(NormalResultLayer::afterCaptured, this) ,path);
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    std::string path =StringUtils::format("%smahjong_screen_shot.png",FileUtils::sharedFileUtils()->getWritablePath().c_str());
    log("screenShot path = %s",path.c_str());
    utils::captureScreen(CC_CALLBACK_2(NormalResultLayer::afterCaptured, this) ,path);
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
    vector<Player*> players = GAMEDATA::getInstance()->getPlayersInfo();
    for (int i = 0; i < players.size(); i++){
        if(players.at(i)->getSeatId() != GAMEDATA::getInstance()->getHeroSeatId()){
            players.at(i)->setIsReady(false);
        }
    }
    schedule([=](float dt){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getContinueGameCommand());
    }, 0.0f, 0.0f, 1.0f,"delayGame");
}


void NormalResultLayer::updateTime(float dt){
    if(GAMEDATA::getInstance()->getWaitNetwork()){
        LostNetwork* net = LostNetwork::create();
        net->setTag(2000);
        addChild(net,200);
        schedule([=](float dt){
            if(NetworkManage::getInstance()->reConnectSocket()){
                log("重新连接成功");
                net->removeFromParent();
                NetworkManage::getInstance()->startSocketBeat(CommandManage::getInstance()->getHeartCommmand());
            }else{
                net->removeFromParent();
                HintDialog* dia = HintDialog::create("无法连接网络,请检查当前网络环境", NULL);
                addChild(dia,1000);
            }
        }, 0, 0, 2.0f, "socket_reconnect");
        GAMEDATA::getInstance()->setWaitNetwork(false);
    }
}

void NormalResultLayer::onEnter(){
    Layer::onEnter();
    continueAgainLisetner =  EventListenerCustom::create(MSG_HERO_CONTINUE_RESP, [=](EventCustom* event){
        std::string result  = static_cast<char*>(event->getUserData());
        if (GAMEDATA::getInstance()->getEnterRoomResp().result == "1"){
            //返回正常可以继续游戏
            GAMEDATA::getInstance()->setContinueAgain(true);
            Director::getInstance()->replaceScene(TransitionFade::create(1, MjGameScene::create()));
        }else{
            Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
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

void NormalResultLayer::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(continueAgainLisetner);
    Director::getInstance()->getEventDispatcher()->removeEventListener(playerReplaceLoginListener);
}
