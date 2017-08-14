#include "mahjong/splash/SplashScene.h"
#include "mahjong/splash/LoadResource.hpp"
#include "mahjong/lobby/friend/dialog/RoomFullDialog.hpp"
#include "mahjong/lobby/friend/dialog/RoomIdErrorDialog.hpp"
#include "mahjong/common/dialog/prompt/HintDialog.hpp"
#include "mahjong/lobby/LobbyScene.h"
#include "mahjong/lobby/shop/fangka/FangkaNotEnoughDialog.hpp"
#include "mahjong/common/loading/Loading.h"
#include "mahjong/common/utils/SeatIdUtil.h"
#include "mahjong/common/audio/Audio.h"
#include "mahjong/common/utils/Chinese.h"
#include "wechat/android/CallAndroidMethod.h"
#include "wechat/ios/CallIOSMethod.h"
#include "server/NetworkManage.h"
#include "mahjong/GameConfig.h"

Scene* SplashScene::createScene()
{
    auto scene = Scene::create();
    auto layer = SplashScene::create();
    scene->addChild(layer);
    return scene;
}

bool SplashScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    //draw scene
    drawLonginScene();
    showSplashAnim();
    //add event listener
    addTocuhListener();
    return true;
}


void SplashScene::onEnterTransitionDidFinish(){
    GAMEDATA::getInstance()->setLogingGame(false);
    if(Audio::getInstance()->getBgmId()<0)
        Audio::getInstance()->playBGM();
    TuiGuangReward myReward;
    myReward.fangka =0;
    myReward.gold=0;
    GAMEDATA::getInstance()->setTuiGuangReward(myReward);
    TuiGuangPride myPride;
    myPride.fangka =0;
    myPride.gold=0;
    GAMEDATA::getInstance()->setTuiGuangPride(myPride);
    TuiGuangRecord myRecord;
    myRecord.fangka =0;
    myRecord.gold=0;
    GAMEDATA::getInstance()->setTuiGuangRecord(myRecord);
    GAMEDATA::getInstance()->setWanJiaQun("");
    GAMEDATA::getInstance()->setDaiLiQun("");
    if(UserData::getInstance()->getWxOpenId()!= "unknow"){
        showLoading();
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getThirdLoginCommand(UserData::getInstance()->getWxOpenId(),UserData::getInstance()->getWxUnionid(),UserData::getInstance()->getPicture(),StringUtils::format("%d",UserData::getInstance()->getGender()),UserData::getInstance()->getNickName(),UserData::getInstance()->getHsman(),UserData::getInstance()->getHstype(),UserData::getInstance()->getImsi(),UserData::getInstance()->getImei(),UserData::getInstance()->getAppVer()));
        schedule(schedule_selector(SplashScene::updateCount), 0, 0, 10);
    }
}

void SplashScene::drawLonginScene(){
    //add game bg to layer
    Sprite* splash_bg = Sprite::create("common/shang_hai_bg.jpg");
    splash_bg->setPosition(640,360);
    this->addChild(splash_bg, -1);
    
    auto log = Sprite::create("mainlogin/logo.png");
    log->setPosition(640,530);
    addChild(log);
    
    auto desk = Sprite::create("mainlogin/login_desk.png");
    desk->setPosition(640,30);
    addChild(desk);
    
}


void SplashScene::loginByWechat(){
    Audio::getInstance()->playSoundClick();
    showLoading();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    //oTIvfwqK9YwoAi1dANUQjhlhOAZ4 shanjun
    //oTIvfwm1C14AtD2bnuoQrXtGWzhY xinkai
    //oTIvfwnO4yCaBasG7qJedNbiGuG0  ziji
    //oTIvfwmTH71Oqx_XRJTPB4p2TjkU 魂斗罗
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getThirdLoginCommand("oTIvfwmTH71Oqx_XRJTPB4p2TjkU","1131111","http://wx.qlogo.cn/mmopen/iaS020Z6hznYwWiacdX0aia7ia9XANXWGKReDZYCjSM8Jt1MFqtnaPRL4ugpZK8cU2bhVmgHs24KB3LDicrQ1cxjeQngXmburObUM/0","1","Poli","APPLE","iphone","11111111111","11111111111","1.0.4"));
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CallIOSMethod::getInstance()->doWechatLogin();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CallAndroidMethod::getInstance()->weChatLogin();
#endif
}

void SplashScene::loginByVisitor(){
    if (UserData::getInstance()->getUserName() == "unknow"&&UserData::getInstance()->getPassword() == "unknow"){
        showLoading();
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getVistorLogin());
    }
    else{
        showLoading();
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getVistorLoginAgain(UserData::getInstance()->getUserName(), UserData::getInstance()->getPassword()));
    }
    
}



void SplashScene::showLoading(){
    Loading* loadLayer = Loading::create();
    loadLayer->setTag(1000);
    addChild(loadLayer,200);
}



void SplashScene::removeLoading(){
    if(NULL != getChildByTag(1000)){
        getChildByTag(1000)->removeFromParent();
    }
}


void SplashScene::showSplashAnim(){
    
    showLoadLayerAnim();
    
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    if(!CallIOSMethod::getInstance()->isWenxinInstalled()){
        auto visitorBtn = MenuItemImage::create("mainlogin/youke_chat_btn_1.png", "mainlogin/youke_chat_btn_1.png",
                                                CC_CALLBACK_0(SplashScene::loginByVisitor, this));
        auto loginMenu = Menu::create(visitorBtn, NULL);
        loginMenu->setPosition(640,140);
        addChild(loginMenu);
    }else{
        auto visitorBtn = MenuItemImage::create("mainlogin/we_chat_btn_1.png", "mainlogin/we_chat_btn_2.png",
                                                CC_CALLBACK_0(SplashScene::loginByWechat, this));
        auto loginMenu = Menu::create(visitorBtn, NULL);
        loginMenu->setPosition(640,140);
        addChild(loginMenu);
    }
#else
    auto visitorBtn = MenuItemImage::create("mainlogin/we_chat_btn_1.png", "mainlogin/we_chat_btn_2.png",
                                            CC_CALLBACK_0(SplashScene::loginByWechat, this));
    auto loginMenu = Menu::create(visitorBtn, NULL);
    loginMenu->setPosition(640,140);
    addChild(loginMenu);
#endif
    
}

void SplashScene::updateCount(float dt){
    NetworkManage::getInstance()->changeSocketAddress(SERVER_ADDRESS_2);
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getThirdLoginCommand(UserData::getInstance()->getWxOpenId(),UserData::getInstance()->getWxUnionid(),UserData::getInstance()->getPicture(),StringUtils::format("%d",UserData::getInstance()->getGender()),UserData::getInstance()->getNickName(),UserData::getInstance()->getHsman(),UserData::getInstance()->getHstype(),UserData::getInstance()->getImsi(),UserData::getInstance()->getImei(),UserData::getInstance()->getAppVer()));
}

void SplashScene::addTocuhListener(){
    auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
        switch (code)
        {
            case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
                Director::getInstance()->end();
                break;
                
            default:
                break;
        }
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void SplashScene::onEnter(){
    Layer::onEnter();
    unschedule(schedule_selector(SplashScene::updateCount));
    loginRespListener = EventListenerCustom::create(MSG_LOGIN_RESP, [=](EventCustom* event){
        std::string result = static_cast<char*>(event->getUserData());
        removeLoading();
        
        if (result == LOGIN_SUCCESS){
            NetworkManage::getInstance()->startSocketBeat(CommandManage::getInstance()->getHeartCommmand());
            Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
        }
        else{
            showLoading();
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getThirdLoginCommand(UserData::getInstance()->getWxOpenId(),UserData::getInstance()->getWxUnionid(),UserData::getInstance()->getPicture(),StringUtils::format("%d",UserData::getInstance()->getGender()),UserData::getInstance()->getNickName(),UserData::getInstance()->getHsman(),UserData::getInstance()->getHstype(),UserData::getInstance()->getImsi(),UserData::getInstance()->getImei(),UserData::getInstance()->getAppVer()));
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(loginRespListener, 1);
    
    
    //断线续玩
    reConnectAgain = EventListenerCustom::create(MSG_PLAYER_CONNECT_AGAIN, [=](EventCustom* event){
        GAMEDATA::getInstance()->setIsRecover(true);
        NetworkManage::getInstance()->startSocketBeat(CommandManage::getInstance()->getHeartCommmand());
        Director::getInstance()->replaceScene(MjGameScene::create());
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(reConnectAgain, 1);
    
    hzReConnectAgain= EventListenerCustom::create(MSG_HZ_PLAYER_CONNECT_AGAIN, [=](EventCustom* event){
        GAMEDATA::getInstance()->setIsRecover(true);
        NetworkManage::getInstance()->startSocketBeat(CommandManage::getInstance()->getHeartCommmand());
        Director::getInstance()->replaceScene(MjGameScene::create());
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(hzReConnectAgain, 1);
    
    //断线续玩CM
    cmLobbyConncetAgainListener=  Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_PLAYER_CM_CONNECT_AGAIN, [=](EventCustom* event){
        GAMEDATA::getInstance()->setIsRecover(true);
        NetworkManage::getInstance()->startSocketBeat(CommandManage::getInstance()->getHeartCommmand());
        Director::getInstance()->replaceScene(MjGameScene::create());
    });
    
    //进入好友房间回复
    reEnterFriendRoomListener =  Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_ENTER_FRIEND_ROOM_RESP, [=](EventCustom* event){
        char* buf = static_cast<char*>(event->getUserData());
        std::string result = buf;
        if (result == "1"){
            NetworkManage::getInstance()->startSocketBeat(CommandManage::getInstance()->getHeartCommmand());
            GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
            Director::getInstance()->replaceScene(TransitionFade::create(1, MjGameScene::create()));
        } else
        {
            showLoading();
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getThirdLoginCommand(UserData::getInstance()->getWxOpenId(),UserData::getInstance()->getWxUnionid(),UserData::getInstance()->getPicture(),StringUtils::format("%d",UserData::getInstance()->getGender()),UserData::getInstance()->getNickName(),UserData::getInstance()->getHsman(),UserData::getInstance()->getHstype(),UserData::getInstance()->getImsi(),UserData::getInstance()->getImei(),UserData::getInstance()->getAppVer()));
        }
    });
    
    hzReEnterFriendRoomListener  =  Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_HZ_ENTER_FRIEND_ROOM_RESP, [=](EventCustom* event){
        char* buf = static_cast<char*>(event->getUserData());
        std::string result = buf;
        if (result == "1"){
            NetworkManage::getInstance()->startSocketBeat(CommandManage::getInstance()->getHeartCommmand());
            GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
            Director::getInstance()->replaceScene(TransitionFade::create(1, MjGameScene::create()));
        } else
        {
            showLoading();
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getThirdLoginCommand(UserData::getInstance()->getWxOpenId(),UserData::getInstance()->getWxUnionid(),UserData::getInstance()->getPicture(),StringUtils::format("%d",UserData::getInstance()->getGender()),UserData::getInstance()->getNickName(),UserData::getInstance()->getHsman(),UserData::getInstance()->getHstype(),UserData::getInstance()->getImsi(),UserData::getInstance()->getImei(),UserData::getInstance()->getAppVer()));
        }
    });
    
    cmReEnterFriendRoomListener  =  Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_CM_ENTER_FRIEND_ROOM_RESP, [=](EventCustom* event){
        char* buf = static_cast<char*>(event->getUserData());
        std::string result = buf;
        if (result == "1"){
            NetworkManage::getInstance()->startSocketBeat(CommandManage::getInstance()->getHeartCommmand());
            GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
            Director::getInstance()->replaceScene(TransitionFade::create(1, MjGameScene::create()));
        } else
        {
            showLoading();
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getThirdLoginCommand(UserData::getInstance()->getWxOpenId(),UserData::getInstance()->getWxUnionid(),UserData::getInstance()->getPicture(),StringUtils::format("%d",UserData::getInstance()->getGender()),UserData::getInstance()->getNickName(),UserData::getInstance()->getHsman(),UserData::getInstance()->getHstype(),UserData::getInstance()->getImsi(),UserData::getInstance()->getImei(),UserData::getInstance()->getAppVer()));
        }
    });

    
    
    reOpenFriendRoomListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_FRIEND_OPEN_ROOM_RESP, [=](EventCustom* event){
        GAMEDATA::getInstance()->setGameType(1);
        GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
        FriendOpenRoomRespData resp = GAMEDATA::getInstance()->getFriendOpenRoomResp();
        if(resp.result == 1){
            NetworkManage::getInstance()->startSocketBeat(CommandManage::getInstance()->getHeartCommmand());
            GAMEDATA::getInstance()->setFangZhuId(UserData::getInstance()->getPoxiaoId());
            Director::getInstance()->replaceScene(TransitionFade::create(1, MjGameScene::create()));
        }else {
            showLoading();
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getThirdLoginCommand(UserData::getInstance()->getWxOpenId(),UserData::getInstance()->getWxUnionid(),UserData::getInstance()->getPicture(),StringUtils::format("%d",UserData::getInstance()->getGender()),UserData::getInstance()->getNickName(),UserData::getInstance()->getHsman(),UserData::getInstance()->getHstype(),UserData::getInstance()->getImsi(),UserData::getInstance()->getImei(),UserData::getInstance()->getAppVer()));
        }
    });
    
    //好友开房红中麻将
    hzOpenFriendRoomListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_ENTER_FRIEND_ROOM_HONGZHONG_RESP, [=](EventCustom* event){
        GAMEDATA::getInstance()->setGameType(3);
        GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
        FriendOpenRoomRespData resp = GAMEDATA::getInstance()->getFriendOpenRoomResp();
        if(resp.result == 1){
            GAMEDATA::getInstance()->setFangZhuId(UserData::getInstance()->getPoxiaoId());
            Director::getInstance()->replaceScene(TransitionFade::create(1, MjGameScene::create()));
        }else {
            showLoading();
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getThirdLoginCommand(UserData::getInstance()->getWxOpenId(),UserData::getInstance()->getWxUnionid(),UserData::getInstance()->getPicture(),StringUtils::format("%d",UserData::getInstance()->getGender()),UserData::getInstance()->getNickName(),UserData::getInstance()->getHsman(),UserData::getInstance()->getHstype(),UserData::getInstance()->getImsi(),UserData::getInstance()->getImei(),UserData::getInstance()->getAppVer()));
        }
    });
    
    cmOpenRoomListener  = EventListenerCustom::create(MSG_CM_FRIEND_OPEN_ROOM_RESP, [=](EventCustom* event){
        
        GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
        GAMEDATA::getInstance()->setGameType(5);
        FriendOpenRoomRespData resp = GAMEDATA::getInstance()->getFriendOpenRoomResp();
        if(resp.result == 1){
            GAMEDATA::getInstance()->setFangZhuId(UserData::getInstance()->getPoxiaoId());
            Director::getInstance()->replaceScene(TransitionFade::create(1, MjGameScene::create()));
        }else {
            showLoading();
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getThirdLoginCommand(UserData::getInstance()->getWxOpenId(),UserData::getInstance()->getWxUnionid(),UserData::getInstance()->getPicture(),StringUtils::format("%d",UserData::getInstance()->getGender()),UserData::getInstance()->getNickName(),UserData::getInstance()->getHsman(),UserData::getInstance()->getHstype(),UserData::getInstance()->getImsi(),UserData::getInstance()->getImei(),UserData::getInstance()->getAppVer()));
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(cmOpenRoomListener, 1);
    
    competitionQueueListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_COMPETITION_QUEUE_RESP, [=](EventCustom* event){
        std::string roomId = static_cast<char*>(event->getUserData());
        if(atoi(roomId.c_str()) == CompetitionRoomId::Shanghai_High||atoi(roomId.c_str()) == CompetitionRoomId::Shanghai_Normal){
            GAMEDATA::getInstance()->setIsCompetitionQueue(true);
            GAMEDATA::getInstance()->setGameType(1);
            Director::getInstance()->replaceScene(TransitionFade::create(1, MjGameScene::create()));
        }else{
            GAMEDATA::getInstance()->setIsCompetitionQueue(true);
            GAMEDATA::getInstance()->setGameType(3);
            Director::getInstance()->replaceScene(TransitionFade::create(1, MjGameScene::create()));
        }
    });
}


void SplashScene::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(loginRespListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(reConnectAgain);
    Director::getInstance()->getEventDispatcher()->removeEventListener(reEnterFriendRoomListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(reOpenFriendRoomListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(hzOpenFriendRoomListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(hzReConnectAgain);
    Director::getInstance()->getEventDispatcher()->removeEventListener(hzReEnterFriendRoomListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(cmOpenRoomListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(cmReEnterFriendRoomListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(cmLobbyConncetAgainListener);
    
}

void SplashScene::showLoadLayerAnim(){
    auto poker1 = Sprite::create("mainlogin/pai_img_3.png");
    poker1->setPosition(250,320);
    addChild(poker1,2);
    poker1->runAction(Repeat::create(Sequence::create(MoveTo::create(0.8,Point(250,300)),MoveTo::create(0.8,Point(250,320)),NULL), CC_REPEAT_FOREVER));
    
    auto poker2 = Sprite::create("mainlogin/pai_img_2.png");
    poker2->setPosition(1050,308);
    addChild(poker2,2);
    poker2->runAction(Repeat::create(Sequence::create(MoveTo::create(0.9,Point(1050,280)),MoveTo::create(0.9,Point(1050,308)),NULL), CC_REPEAT_FOREVER));
    
    auto poker3 = Sprite::create("mainlogin/pai_img_1.png");
    poker3->setPosition(1075,612);
    addChild(poker3,2);
    poker3->runAction(Repeat::create(Sequence::create(MoveTo::create(0.7,Point(1075,595)),MoveTo::create(0.7,Point(1075,612)),NULL), CC_REPEAT_FOREVER));
    
    auto hua1 = Sprite::create("mainlogin/flower_1.png");
    hua1->setPosition(270,730);
    addChild(hua1);
    hua1->runAction(Spawn::create(MoveTo::create(2,Point(960,420)),FadeTo::create(2,0),NULL));
    
    auto hua2 = Sprite::create("mainlogin/flower_2.png");
    hua2->setPosition(-10,420);
    addChild(hua2);
    hua2->runAction(Spawn::create(MoveTo::create(2,Point(480,200)),FadeTo::create(2,0),NULL));
    
    auto hua3 = Sprite::create("mainlogin/flower_2.png");
    hua3->setPosition(500,730);
    addChild(hua3);
    hua3->runAction(Spawn::create(MoveTo::create(2,Point(1060,510)),FadeTo::create(2,0),NULL));
    
    auto hua4 = Sprite::create("mainlogin/flower_3.png");
    hua4->setPosition(-10,260);
    addChild(hua4);
    hua4->runAction(Spawn::create(MoveTo::create(2,Point(770,110)),FadeTo::create(2,0),NULL));
}
