//
//  PublicResultLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/21.
//
//

#include "mahjong/result/hongzhong/normal/HZNormalResultLayer.hpp"
#include "mahjong/result/hongzhong/normal/HZPlayerResultCell.hpp"
#include "mahjong/result/ResultScene.hpp"
#include "mahjong/common/jong/Jong.h"
#include "mahjong/common/dialog/prompt/HintDialog.hpp"
#include "mahjong/common/dialog/network/LostNetwork2.hpp"
#include "mahjong/common/utils/SeatIdUtil.h"
#include "mahjong/common/utils/StringUtil.h"
#include "mahjong/common/utils/Chinese.h"
#include "mahjong/common/widget/ParticleUtil.hpp"
#include "mahjong/lobby/goldroom/GoldRoomPlate.hpp"
#include "mahjong/lobby/LobbyScene.h"
#include "mahjong/lobby/dialog/EnterRoomDialog.hpp"
#include "mahjong/lobby/shop/gold/GoldNotEnoughDialog.hpp"
#include "mahjong/lobby/shop/gold/ChargeGold.hpp"
#include "mahjong/gameview/MjGameScene.h"
#include "mahjong/gameview/shanghai/normal/MahjongView.h"
#include "server/NetworkManage.h"
#include "server/CommandManage.h"
#include "wechat/android/CallAndroidMethod.h"
#include "wechat/ios/CallIOSMethod.h"
#include "mahjong/common/dialog/dissolve/DissovleRoomDialog.hpp"


bool HZNormalResultLayer::init(){
    if(!Layer::init()){
        return false;
    }
    auto reslut_bg = Sprite::create("result/result_bg.jpg");
    reslut_bg->setPosition(640, 360);
    addChild(reslut_bg,-1);
    timeLabel = LabelAtlas::create(StringUtils::format("%d",totalTime),"competition/daojishi_num.png",31,45,'0');
    timeLabel->setVisible(false);
    addChild(timeLabel);
    showGameResult();//结算界面标题
    showRoomInfo();
    showHZMa();
    showPlayerResluts();
    showLayerBtn();
    updatePlayerData();
    if(!GAMEDATA::getInstance()->getDissovleDialogRemove()){
        GAMEDATA::getInstance()->setDissolveName(GAMEDATA::getInstance()->getDissolveName());
        DissovleRoomDialog* dia = DissovleRoomDialog::create();
        addChild(dia,20);
    }
    return true;
}

void HZNormalResultLayer::showGameResult(){
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

void HZNormalResultLayer::showRoomInfo(){
    if(GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom){
        
        if(GAMEDATA::getInstance()->getIsCompetitionState()){
            auto fanghaoNum = LabelAtlas::create(GAMEDATA::getInstance()->getCompetitionPride(), "result/ju_num.png",16,22,'0');
            fanghaoNum->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
            fanghaoNum->setPosition(940,560);
            addChild(fanghaoNum);
            auto yuan = Sprite::create("competition/yuan_hua_fei.png");
            yuan->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
            yuan->setPosition(945,560);
            addChild(yuan);
            if(!UserData::getInstance()->isWeixinPayOpen()){
                fanghaoNum->setVisible(false);
                yuan->setVisible(false);
                auto spri = Label::createWithSystemFont("", "arial", 22);
                if(GAMEDATA::getInstance()->getCompetitionPride() == "36"){
                    spri->setString("8张房卡比赛");
                }else{
                    spri->setString("2张房卡比赛");
                }
                spri->setPosition(945,560);
                addChild(spri);
            }
        }else{
        
            auto fanghao = Sprite::create("result/fang_jian_hao.png");
            fanghao->setPosition(900,560);
            addChild(fanghao,1);
            
            auto fanghaoNum = LabelAtlas::create(GAMEDATA::getInstance()->getFriendOpenRoomResp().prid, "result/ju_num.png",16,22,'0');
            fanghaoNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
            fanghaoNum->setPosition(940,560);
            addChild(fanghaoNum);
        }
        
        auto maType  = Sprite::create();
        addChild(maType);
        if(GAMEDATA::getInstance()->getFanMaType() == "4"){
            maType->setTexture("result/ma_159zh.png");
        }else if(GAMEDATA::getInstance()->getFanMaType() == "3"){
            maType->setTexture("result/ma_159.png");
        }else{
            maType->setTexture("result/ma_1.png");
        }
        
        auto difen = Sprite::create();
        difen->setTexture(StringUtils::format("result/difen_%s.png",GAMEDATA::getInstance()->getHZDiFen().c_str()));
        addChild(difen);
        
        auto jucount = Sprite::create();
        addChild(jucount);
        
        if(GAMEDATA::getInstance()->getFriendOpenRoomResp().prjushu == "4"){
            jucount->setTexture("result/4ju_bg.png");
        }else if(GAMEDATA::getInstance()->getFriendOpenRoomResp().prjushu == "16"){
            jucount->setTexture("result/16ju_bg.png");
        }else{
            jucount->setTexture("result/8ju_bg.png");
        }
        auto juNum = LabelAtlas::create(StringUtils::format("%s",GAMEDATA::getInstance()->getFriendOpenRoomResp().prjucount.c_str()),"result/ju_num.png" , 16, 22, '0');
        addChild(juNum);
        
        int wid = difen->getContentSize().width + jucount->getContentSize().width+(maType->isVisible()?(maType->getContentSize().width):0);
        maType->setPosition((Director::getInstance()->getVisibleSize().width-wid)/2-(maType->isVisible()?(maType->getContentSize().width):0)/2,560);
        maType->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        difen->setPosition((Director::getInstance()->getVisibleSize().width-wid)/2+(maType->isVisible()?(maType->getContentSize().width):0)/2,560);
        difen->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        jucount->setPosition((Director::getInstance()->getVisibleSize().width-wid)/2+difen->getContentSize().width+(maType->isVisible()?(maType->getContentSize().width):0)/2,560);
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

void HZNormalResultLayer::showHZMa(){
    if(GAMEDATA::getInstance()->getFanMa() != ""){
        auto mabg = Sprite::create("result/fanma_di.png");
        mabg->setPosition(150,650);
        addChild(mabg);
        vector<std::string> ma = StringUtil::split(GAMEDATA::getInstance()->getFanMa(), ",");
        for (int i=0; i<ma.size(); i++) {
            auto jong = Jong::create();
            jong->showJong(herohand,atoi(ma.at(i).c_str()));
            jong->setPosition(150- 70*(ma.size()-1)/2+i*70,650);
            jong->setScale(0.8f);
            addChild(jong);
        }
    }
}

void HZNormalResultLayer::showPlayerResluts(){
    vector<GameResultData> results = GAMEDATA::getInstance()->getGameResults();
    for (int i=0; i<results.size();i++) {
        HZPlayerResultCell* cell = HZPlayerResultCell::create(results.at(i));
        if(GAMEDATA::getInstance()->getMyGameModel() == GameModel::TWOPLAYER){
            cell->setPosition(640,470-180*i);
        }else{
            cell->setPosition(640,490-110*i);
        }
        addChild(cell);
    }
}

void HZNormalResultLayer::showLayerBtn(){
    if(GAMEDATA::getInstance()->getNeedShowLastResult()){
        GAMEDATA::getInstance()->setNeedShowLastResult(false);
        if(GAMEDATA::getInstance()->getIsCompetitionState()){
            schedule([=](float dt){
                Director::getInstance()->replaceScene(TransitionFade::create(0.8f,ResultScene::createScene(2)));
            }, 0, 0, 5,"KillBill");
        }else{
            schedule([=](float dt){
                Director::getInstance()->replaceScene(TransitionFade::create(0.8f,ResultScene::createScene(1)));
            }, 0, 0, 5,"KillBill");
        }
    }else{
        schedule(schedule_selector(HZNormalResultLayer::updateTime), 1.0f, kRepeatForever, 0);
        if(GAMEDATA::getInstance()->getIsCompetitionState()){
            auto feedImage = MenuItemImage::create("result/start_game_btn_1.png","result/start_game_btn_2.png",
                                                   CC_CALLBACK_0(HZNormalResultLayer::continueGame, this));
            Menu* myMneu = Menu::create();
            myMneu->addChild(feedImage);
            myMneu->setPosition(640,60);
            addChild(myMneu);

            
            timeLabel->setVisible(true);
            timeLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
            timeLabel->setPosition(850,55);

            
        }else{
            auto quitImage = MenuItemImage::create("result/quit_btn_1.png","result/quit_btn_1.png",CC_CALLBACK_0(HZNormalResultLayer::gotoLobby, this));
            
            auto helpImage = MenuItemImage::create("result/xuan_yao_btn_1.png","result/xuan_yao_btn_2.png",
                                                   CC_CALLBACK_0(HZNormalResultLayer::shareResult, this));
            auto feedImage = MenuItemImage::create("result/continue_btn_1.png","result/continue_btn_2.png",
                                                   CC_CALLBACK_0(HZNormalResultLayer::continueGame, this));
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
        }
    }
}

void HZNormalResultLayer::updatePlayerData(){
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

void HZNormalResultLayer::gotoLobby(){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getQuitRoomCommand());
    Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
}

void HZNormalResultLayer::showPrideAnim(GameResultData data){
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


void HZNormalResultLayer::shareResult(){
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string path =StringUtils::format("%s/mahjong_screen_shot.png",CallAndroidMethod::getInstance()->getSdCardDir().c_str());
    log("screenShot path = %s",path.c_str());
    utils::captureScreen(CC_CALLBACK_2(HZNormalResultLayer::afterCaptured, this) ,path);
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    std::string path =StringUtils::format("%smahjong_screen_shot.png",FileUtils::sharedFileUtils()->getWritablePath().c_str());
    log("screenShot path = %s",path.c_str());
    utils::captureScreen(CC_CALLBACK_2(HZNormalResultLayer::afterCaptured, this) ,path);
#endif
}


void HZNormalResultLayer::afterCaptured(bool succeed, const std::string &outputFile)
{
    if (succeed) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        CallAndroidMethod::getInstance()->shareImageToWeChat(outputFile, false);
#endif
        
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        CallIOSMethod::getInstance()->doWechatShareImg(outputFile, 0);
#endif
    }
}

void HZNormalResultLayer::continueGame(){
    if(GAMEDATA::getInstance()->getIsGotoLobby()){
        Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
    }else{
        vector<Player*> players = GAMEDATA::getInstance()->getPlayersInfo();
        for (int i = 0; i < players.size(); i++){
            if(players.at(i)->getSeatId() != GAMEDATA::getInstance()->getHeroSeatId()){
                players.at(i)->setIsReady(false);
            }
        }
        schedule([=](float dt){
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getHZPlayGameAgain());
        }, 0.0f, 0.0f, 0.8f,"delayGame");
    }
}


void HZNormalResultLayer::updateTime(float dt){
    totalTime --;
    if(totalTime>=0){
        timeLabel->setString(StringUtils::format("%d",totalTime));
    }
    if(totalTime<=0&&GAMEDATA::getInstance()->getIsCompetitionState()){
        continueGame();
    }
    if(GAMEDATA::getInstance()->getShowProtected()){
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MSG_NETWORK_BREAK_INFO);
        GAMEDATA::getInstance()->setShowProtected(false);
    }
    
}

void HZNormalResultLayer::onEnter(){
    Layer::onEnter();
    continueAgainLisetner =  EventListenerCustom::create(MSG_HZ_HERO_CONTINUE_RESP, [=](EventCustom* event){
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
            int  delayTime = 1.0f;
            schedule([=](float dt){
                if(UserData::getInstance()->getWxOpenId() ==  "unknow"){
                    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getVistorLoginAgain(UserData::getInstance()->getUserName(), UserData::getInstance()->getPassword()));
                }else{
                    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getThirdLoginCommand(UserData::getInstance()->getWxOpenId(), UserData::getInstance()->getWxUnionid(),UserData::getInstance()->getPicture(), StringUtils::format("%d",UserData::getInstance()->getGender()), UserData::getInstance()->getNickName(), UserData::getInstance()->getHsman(), UserData::getInstance()->getHstype(), UserData::getInstance()->getImsi(),UserData::getInstance()->getImei(),UserData::getInstance()->getAppVer(),true));
                }
            }, 0, 0, delayTime, "socket_reconnect2000");
            NetworkManage::getInstance()->startSocketBeat(CommandManage::getInstance()->getHeartCommmand());
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(networkBreakListener, 1);
    
    //好友开房
    openFriendRoomListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_FRIEND_OPEN_ROOM_RESP, [=](EventCustom* event){
        GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
        FriendOpenRoomRespData resp = GAMEDATA::getInstance()->getFriendOpenRoomResp();
        if(resp.result == 1){
            GAMEDATA::getInstance()->setGameType(1);
            GAMEDATA::getInstance()->setFangZhuId(UserData::getInstance()->getPoxiaoId());
            Director::getInstance()->replaceScene(TransitionFade::create(1, MjGameScene::create()));
        }
    });
    
    enterFriendRoomListener=  Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_ENTER_FRIEND_ROOM_RESP, [=](EventCustom* event){
        char* buf = static_cast<char*>(event->getUserData());
        std::string result = buf;
        if (result == "1"){
            GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
            GAMEDATA::getInstance()->setGameType(1);
            Director::getInstance()->replaceScene(TransitionFade::create(1.0f, MjGameScene::create()));
        }
    });
    
    
    hzEnterFriendRoomListener =  Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_HZ_ENTER_FRIEND_ROOM_RESP, [=](EventCustom* event){
        char* buf = static_cast<char*>(event->getUserData());
        std::string result = buf;
        if (result == "1"){
            GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
            GAMEDATA::getInstance()->setGameType(3);
            Director::getInstance()->replaceScene(TransitionFade::create(1.0f, MjGameScene::create()));
        }
    });
    
    dissovelRoomSelectNotifyListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_DISSOVLE_ROOM_SELECTED_NOTIFY_HZ, [=](EventCustom* event){
        DissovleRoomDialog* dialog = DissovleRoomDialog::create();
        addChild(dialog,10);
    });
    
}

void HZNormalResultLayer::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(continueAgainLisetner);
    Director::getInstance()->getEventDispatcher()->removeEventListener(playerReplaceLoginListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(myCoreLoginRespListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(networkBreakListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(openFriendRoomListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(enterFriendRoomListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(hzEnterFriendRoomListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(dissovelRoomSelectNotifyListener);

}
