//
//  PublicResultLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/21.
//
//

#include "mahjong/result/shanghai/normal/NormalResultLayer.hpp"
#include "mahjong/result/shanghai/normal/PlayerResultCell.hpp"
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


bool NormalResultLayer::init(){
    if(!Layer::init()){
        return false;
    }
    auto reslut_bg = Sprite::create("result/result_bg.jpg");
    reslut_bg->setPosition(640, 360);
    addChild(reslut_bg,-1);
    timeLabel = LabelAtlas::create(StringUtils::format("%d",totalTime),"competition/daojishi_num.png",31,45,'0');
    timeLabel->setAnchorPoint(Point::ANCHOR_MIDDLE);
    timeLabel->setPosition(850,55);
    addChild(timeLabel);
    showGameResult();//结算界面标题
    showRoomInfo();
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
        auto wukaibao  = Sprite::create("result/public_wu_kaibao.png");
        wukaibao->setVisible(false);
        wukaibao->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        addChild(wukaibao);
        if(GAMEDATA::getInstance()->getPrivateKaibao() == "0"){
            wukaibao->setVisible(true);
        }
        auto dihua = Sprite::create();
        dihua->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        addChild(dihua);
        
        if(GAMEDATA::getInstance()->getPrivateDihua() == "0"){
            dihua->setTexture("result/js_11.png");
        }else if(GAMEDATA::getInstance()->getPrivateDihua() == "1"){
            dihua->setTexture("result/js_22.png");
        }else if(GAMEDATA::getInstance()->getPrivateDihua() == "2"){
            dihua->setTexture("result/js_62.png");
        }else if(GAMEDATA::getInstance()->getPrivateDihua() == "3"){
            dihua->setTexture("result/js_55.png");
        }
        auto lezi = Sprite::create();
        lezi->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        addChild(lezi);
        if(GAMEDATA::getInstance()->getPrivateLezi() == "0"){
            lezi->setTexture("result/js_lezi_20.png");
        }else if(GAMEDATA::getInstance()->getPrivateLezi() == "1"){
            lezi->setTexture("result/js_lezi_50.png");
        }else if(GAMEDATA::getInstance()->getPrivateLezi() == "2"){
            lezi->setTexture("result/js_lezi_100.png");
        }else if(GAMEDATA::getInstance()->getPrivateLezi() == "3"){
            lezi->setTexture("result/js_wulezi.png");
        }
        auto emsc =  Sprite::create("result/public_2mo_3chong.png");
        emsc->setVisible(false);
        emsc->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        addChild(emsc);
        if(GAMEDATA::getInstance()->getPrivateEmsc() == "1"){
            emsc->setVisible(true);
        }
        
        auto fcy = Sprite::create("result/js_feicangyin.png");
        fcy->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        fcy->setVisible(false);
        addChild(fcy);
        if(GAMEDATA::getInstance()->getPrivateFcy() == "1"){
            fcy->setVisible(true);
        }
        auto jucount = Sprite::create();
        jucount->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        addChild(jucount);
        if(GAMEDATA::getInstance()->getFriendOpenRoomResp().prjushu == "4"){
            jucount->setTexture("result/4ju_bg.png");
        }else if(GAMEDATA::getInstance()->getFriendOpenRoomResp().prjushu == "16"){
            jucount->setTexture("result/16ju_bg.png");
        }else{
            jucount->setTexture("result/8ju_bg.png");
        }
        auto juNum = LabelAtlas::create(StringUtils::format("%s",GAMEDATA::getInstance()->getFriendOpenRoomResp().prjucount.c_str()),"result/ju_num.png" , 16, 22, '0');
        juNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
        addChild(juNum);
        
        int wid = lezi->getContentSize().width + dihua->getContentSize().width + jucount->getContentSize().width+(wukaibao->isVisible()?(wukaibao->getContentSize().width):0)+(emsc->isVisible()?(emsc->getContentSize().width):0)+(fcy->isVisible()?(fcy->getContentSize().width):0);
        wukaibao->setPosition((Director::getInstance()->getVisibleSize().width-wid)/2-(wukaibao->isVisible()?(wukaibao->getContentSize().width):0)/2,560);
        dihua->setPosition((Director::getInstance()->getVisibleSize().width-wid)/2+(wukaibao->isVisible()?(wukaibao->getContentSize().width):0)/2,560);
        lezi->setPosition((Director::getInstance()->getVisibleSize().width-wid)/2+(wukaibao->isVisible()?(wukaibao->getContentSize().width):0)/2+ dihua->getContentSize().width,560);
        emsc->setPosition((Director::getInstance()->getVisibleSize().width-wid)/2+lezi->getContentSize().width+(wukaibao->isVisible()?(wukaibao->getContentSize().width):0)/2+ dihua->getContentSize().width,560);
        fcy->setPosition((Director::getInstance()->getVisibleSize().width-wid)/2+lezi->getContentSize().width+(wukaibao->isVisible()?(wukaibao->getContentSize().width):0)/2+(emsc->isVisible()?(emsc->getContentSize().width):0)+ dihua->getContentSize().width,560);
        jucount->setPosition((Director::getInstance()->getVisibleSize().width-wid)/2+lezi->getContentSize().width+(wukaibao->isVisible()?(wukaibao->getContentSize().width):0)/2+(emsc->isVisible()?(emsc->getContentSize().width):0)+(fcy->isVisible()?(fcy->getContentSize().width):0) +dihua->getContentSize().width,560);
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
        if(GAMEDATA::getInstance()->getMyGameModel() == GameModel::TWOPLAYER){
            cell->setPosition(640,470-180*i);
        }else{
            cell->setPosition(640,490-110*i);
        }
        addChild(cell);
    }
}

void NormalResultLayer::showLayerBtn(){
    if(GAMEDATA::getInstance()->getNeedShowLastResult()){
        GAMEDATA::getInstance()->setNeedShowLastResult(false);
        if(GAMEDATA::getInstance()->getIsCompetitionState()){
            schedule([=](float dt){
                Director::getInstance()->replaceScene(TransitionFade::create(0.8f,ResultScene::createScene(2)));
            }, 0, 0, 3,"KillBill");
        }else{
            schedule([=](float dt){
                Director::getInstance()->replaceScene(TransitionFade::create(0.8f,ResultScene::createScene(1)));
            }, 0, 0, 3,"KillBill");
        }
    }else{
        
        schedule(schedule_selector(NormalResultLayer::updateTime), 1.0f, kRepeatForever, 0);
        if(GAMEDATA::getInstance()->getIsCompetitionState()){
            auto feedImage = MenuItemImage::create("result/start_game_btn_1.png","result/start_game_btn_2.png",
                                                   CC_CALLBACK_0(NormalResultLayer::continueGame, this));
            Menu* myMneu = Menu::create();
            myMneu->addChild(feedImage);
            myMneu->setPosition(640,60);
            addChild(myMneu);
            
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
        }
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
        CallAndroidMethod::getInstance()->shareImageToWeChat(outputFile, false);
#endif
        
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        CallIOSMethod::getInstance()->doWechatShareImg(outputFile, 0);
#endif
    }
}

void NormalResultLayer::continueGame(){
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
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getContinueGameCommand());
        }, 0.0f, 0.0f, 0.8f,"delayGame");
    }
}


void NormalResultLayer::updateTime(float dt){
    totalTime --;
    if(totalTime>=0){
        timeLabel->setString(StringUtils::format("%d",totalTime));
    }
    if(totalTime<=0){
        continueGame();
    }
    
    if(GAMEDATA::getInstance()->getShowProtected()){
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MSG_NETWORK_BREAK_INFO);
        GAMEDATA::getInstance()->setShowProtected(false);
    }
}

void NormalResultLayer::onEnter(){
    Layer::onEnter();
    continueAgainLisetner =  EventListenerCustom::create(MSG_HERO_CONTINUE_RESP, [=](EventCustom* event){
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

void NormalResultLayer::onExit(){
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
