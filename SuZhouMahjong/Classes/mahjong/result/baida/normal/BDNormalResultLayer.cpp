//
//  PublicResultLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/21.
//
//

#include "mahjong/result/baida/normal/BDNormalResultLayer.hpp"
#include "mahjong/result/baida/normal/BDPlayerResultCell.hpp"
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
#include "server/NetworkManage.h"
#include "server/CommandManage.h"
#include "wechat/android/CallAndroidMethod.h"
#include "wechat/ios/CallIOSMethod.h"
#include "mahjong/common/dialog/dissolve/DissovleRoomDialog.hpp"


bool BDNormalResultLayer::init(){
    if(!Layer::init()){
        return false;
    }
    auto reslut_bg = Sprite::create("result/result_bg.jpg");
    reslut_bg->setPosition(640, 360);
    addChild(reslut_bg,-1);
    auto gu  = Sprite::create("result/gu.png");
    gu->setPosition(1050,65);
    addChild(gu);
    timeLabel = LabelAtlas::create(StringUtils::format("%d",totalTime),"competition/daojishi_num.png",31,45,'0');
    timeLabel->setAnchorPoint(Point::ANCHOR_MIDDLE);
    timeLabel->setPosition(1050,70);
    addChild(timeLabel);
    showGameResult();//结算界面标题
    showRoomInfo();
    showPlayerResluts();
    showLayerBtn();
    showBDFanPai();
    updatePlayerData();
    if(!GAMEDATA::getInstance()->getDissovleDialogRemove()){
        GAMEDATA::getInstance()->setDissolveName(GAMEDATA::getInstance()->getDissolveName());
        DissovleRoomDialog* dia = DissovleRoomDialog::create();
        addChild(dia,20);
    }
    return true;
}

void BDNormalResultLayer::showGameResult(){
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
                        resultTitle->setTexture("result/public_gangkai.png");
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

void BDNormalResultLayer::showRoomInfo(){
    if(GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom){
        auto fanghao = Sprite::create("result/fang_jian_hao.png");
        fanghao->setPosition(910,560);
        addChild(fanghao,1);
        
        auto fanghaoNum = LabelAtlas::create(GAMEDATA::getInstance()->getFriendOpenRoomResp().prid, "result/ju_num.png",16,22,'0');
        fanghaoNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        fanghaoNum->setPosition(950,560);
        addChild(fanghaoNum);        auto jucount = Sprite::create();
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
        
        int wid = jucount->getContentSize().width;
        jucount->setPosition((Director::getInstance()->getVisibleSize().width-wid)/2,560);
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

void BDNormalResultLayer::showBDFanPai(){
    if(GAMEDATA::getInstance()->getFanMa() != ""){
        vector<std::string> ma = StringUtil::split(GAMEDATA::getInstance()->getFanMa(), ",");
        //对翻码的牌进行排序
        vector<int>  fanZhong;
        vector<int>  meiZhong;
        for(int i =0; i<ma.size();i++){
            int code  = atoi(ma.at(i).c_str());
            if(code == 1 || code == 10 || code == 19 || code == 5
               || code == 14 || code == 23 || code == 9 || code == 18
               || code == 27 || code == 28 || code == 29 || code == 30
               || code == 31 || code == 47){
                fanZhong.push_back(code);
            }else{
                meiZhong.push_back(code);
            }
        }
        auto mabg = Sprite::create("result/fanma_di.png");
        mabg->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        mabg->setPosition(50,650);
        addChild(mabg);
        if(ma.size() > 4){
            mabg->setScaleX(1.6f);
        }
        auto light = ui::Scale9Sprite::create("result/fan_pai_xuan_zhong.png");
        light->setPosition(56,650);
        light->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        light->setContentSize(Size(70*fanZhong.size()+15,129));
        addChild(light);
        if(fanZhong.size() == 0){
            light->setVisible(false);
        }
        for (int j=0; j<fanZhong.size(); j++) {
            auto jong = Jong::create();
            jong->showJong(herohand,fanZhong.at(j));
            jong->setPosition(100+j*70,650);
            jong->setScale(0.8f);
            addChild(jong);
        }
        for (int k=0; k<meiZhong.size(); k++) {
            auto jong = Jong::create();
            jong->showJong(herohand,meiZhong.at(k));
            jong->setPosition(100+(k+fanZhong.size())*70,650);
            jong->setScale(0.8f);
            addChild(jong);
        }
    }
}

void BDNormalResultLayer::showPlayerResluts(){
    vector<GameResultData> results = GAMEDATA::getInstance()->getGameResults();
    for (int i=0; i<results.size();i++) {
        BDPlayerResultCell* cell = BDPlayerResultCell::create(results.at(i));
        if(GAMEDATA::getInstance()->getMyGameModel() == GameModel::TWOPLAYER){
            cell->setPosition(640,470-180*i);
        }else{
            cell->setPosition(640,490-110*i);
        }
        addChild(cell);
    }
}

void BDNormalResultLayer::showLayerBtn(){
    if(GAMEDATA::getInstance()->getNeedShowLastResult()){
        GAMEDATA::getInstance()->setNeedShowLastResult(false);
        schedule([=](float dt){
            Director::getInstance()->replaceScene(TransitionFade::create(0.8f,ResultScene::createScene(1)));
        }, 0, 0, 5,"KillBill");

    }else{
        
        schedule(schedule_selector(BDNormalResultLayer::updateTime), 1.0f, kRepeatForever, 0);
        auto quitImage = MenuItemImage::create("result/quit_btn_1.png","result/quit_btn_1.png",CC_CALLBACK_0(BDNormalResultLayer::gotoLobby, this));
        
        auto helpImage = MenuItemImage::create("result/xuan_yao_btn_1.png","result/xuan_yao_btn_2.png",
                                               CC_CALLBACK_0(BDNormalResultLayer::shareResult, this));
        auto feedImage = MenuItemImage::create("result/continue_btn_1.png","result/continue_btn_2.png",
                                               CC_CALLBACK_0(BDNormalResultLayer::continueGame, this));
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

void BDNormalResultLayer::updatePlayerData(){
    for(GameResultData resData : GAMEDATA::getInstance()->getGameResults()){
        vector<PlayerInfo*> players = GAMEDATA::getInstance()->getPlayersInfo();
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

void BDNormalResultLayer::gotoLobby(){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getQuitRoomCommand());
    Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
}

void BDNormalResultLayer::showPrideAnim(GameResultData data){
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


void BDNormalResultLayer::shareResult(){
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string path =StringUtils::format("%s/mahjong_screen_shot.png",CallAndroidMethod::getInstance()->getSdCardDir().c_str());
    log("screenShot path = %s",path.c_str());
    utils::captureScreen(CC_CALLBACK_2(BDNormalResultLayer::afterCaptured, this) ,path);
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    std::string path =StringUtils::format("%smahjong_screen_shot.png",FileUtils::sharedFileUtils()->getWritablePath().c_str());
    log("screenShot path = %s",path.c_str());
    utils::captureScreen(CC_CALLBACK_2(BDNormalResultLayer::afterCaptured, this) ,path);
#endif
}


void BDNormalResultLayer::afterCaptured(bool succeed, const std::string &outputFile)
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

void BDNormalResultLayer::continueGame(){
    if(GAMEDATA::getInstance()->getIsGotoLobby()){
        Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
    }else{
        vector<PlayerInfo*> players = GAMEDATA::getInstance()->getPlayersInfo();
        for (int i = 0; i < players.size(); i++){
            if(players.at(i)->getSeatId() != GAMEDATA::getInstance()->getHeroSeatId()){
                players.at(i)->setIsReady(false);
            }
        }
        schedule([=](float dt){
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getBDContinueGameCommand());
        }, 0.0f, 0.0f, 0.8f,"delayGame");
    }
}


void BDNormalResultLayer::updateTime(float dt){
    totalTime --;
    if(totalTime>=0){
        timeLabel->setString(StringUtils::format("%d",totalTime));
    }
    if(totalTime<=0){
        if(totalTime== -1){
                continueGame();
        }
    }
    
//    if(GAMEDATA::getInstance()->getShowProtected()){
//        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MSG_NETWORK_BREAK_INFO);
//        GAMEDATA::getInstance()->setShowProtected(false);
//    }
}

void BDNormalResultLayer::onEnter(){
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
        if(NetworkManage::getInstance()->connect()){
            if(UserData::getInstance()->getWxOpenId() ==  "unknow"){
                NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getVistorLoginAgain(UserData::getInstance()->getUserName(), UserData::getInstance()->getPassword()));
            }else{
                NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getThirdLoginCommand(UserData::getInstance()->getWxOpenId(), UserData::getInstance()->getWxUnionid(),UserData::getInstance()->getPicture(), StringUtils::format("%d",UserData::getInstance()->getGender()), UserData::getInstance()->getNickName(), UserData::getInstance()->getHsman(), UserData::getInstance()->getHstype(), UserData::getInstance()->getImsi(),UserData::getInstance()->getImei(),UserData::getInstance()->getAppVer(),UserData::getInstance()->getLongitude(),UserData::getInstance()->getLatitude(),true));
            }
            NetworkManage::getInstance()->startSocketBeat(CommandManage::getInstance()->getHeartCommmand());
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(networkBreakListener, 1);
    
    //好友开房
    openFriendRoomListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_CM_FRIEND_OPEN_ROOM_RESP, [=](EventCustom* event){
        GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
        FriendOpenRoomRespData resp = GAMEDATA::getInstance()->getFriendOpenRoomResp();
        if(resp.result == 1){
            GAMEDATA::getInstance()->setGameType(5);
            GAMEDATA::getInstance()->setFangZhuId(UserData::getInstance()->getPoxiaoId());
            Director::getInstance()->replaceScene(TransitionFade::create(1, MjGameScene::create()));
        }
    });
    
    enterFriendRoomListener=  Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_CM_ENTER_FRIEND_ROOM_RESP, [=](EventCustom* event){
         int result = GAMEDATA::getInstance()->getFriendOpenRoomResp().result;
        if (result == 1){
            GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
            GAMEDATA::getInstance()->setGameType(5);
            Director::getInstance()->replaceScene(TransitionFade::create(1.0f, MjGameScene::create()));
        }
    });
    
    
    dissovelRoomSelectNotifyListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_DISSOVLE_ROOM_SELECTED_NOTIFY_NEW, [=](EventCustom* event){
        DissovleRoomDialog* dialog = DissovleRoomDialog::create();
        addChild(dialog,10);
    });
}

void BDNormalResultLayer::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(continueAgainLisetner);
    Director::getInstance()->getEventDispatcher()->removeEventListener(playerReplaceLoginListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(myCoreLoginRespListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(networkBreakListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(openFriendRoomListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(enterFriendRoomListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(dissovelRoomSelectNotifyListener);
}
