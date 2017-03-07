#include "mahjong/core/gui/GuiLayer.h"
#include "mahjong/lobby/LobbyScene.h"
#include "mahjong/state/GameData.h"
#include "mahjong/bill/BillInfo.h"
#include "mahjong/core/widget/QuitRoomDialog.hpp"
#include "mahjong/dialog/prompt/HintDialog.hpp"
#include "mahjong/chat/ChatDialog.hpp"
#include "mahjong/audio/Audio.h"
#include "mahjong/utils/SeatIdUtil.h"
#include "mahjong/utils/GameConfig.h"
#include "server/MsgHandler.h"
#include "server/NetworkManage.h"
#include "userdata/UserData.h"
#include "mahjong/chat/chatAndroid/ChatAndroidMethod.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#import "payment/ios/IOSBridge.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "payment/android/CallAndroidMethod.h"
#endif

bool GuiLayer::init(){
    if (!Layer::init()){
        return false;
    }
    initView();
    return true;
}


void GuiLayer::initView(){
    if(!GAMEDATA::getInstance()->getIsFuPan()){
        drawGuiButton();//设置,账单,聊天，解散房间，退出
    }
    drawGameInfo(); //开宝，荒番，房间号的绘制
    drawTestButton();
    scheduleUpdate();
}


void GuiLayer::drawGuiButton(){
    auto chatButton = MenuItemImage::create("gameview/chat_btn_1.png", "gameview/chat_btn_2.png",
                                            CC_CALLBACK_0(GuiLayer::chatButtonClick, this));
    auto settingButton = MenuItemImage::create("gameview/setting_btn_1.png", "gameview/setting_btn_2.png",
                                               CC_CALLBACK_0(GuiLayer::settingButtonClick, this));
    Menu* myMenu = Menu::create(chatButton, settingButton, NULL);
    myMenu->setPosition(1225,285);
    myMenu->alignItemsVerticallyWithPadding(10);
    this->addChild(myMenu);
    
    auto quitBut = MenuItemImage::create("gameview/go_back_1.png", "gameview/go_back_2.png",
                                         CC_CALLBACK_0(GuiLayer::quitButtonClick, this));
    Menu* quit = Menu::create(quitBut, NULL);
    quit->setTag(1212);
    quit->setPosition(Point(55, 650));
    this->addChild(quit);
    
    if (GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom){
        //解散牌局按钮
        if(atoi(GAMEDATA::getInstance()->getFriendOpenRoomResp().prjucount.c_str())==0 && UserData::getInstance()->getPoxiaoId()==GAMEDATA::getInstance()->getFangZhuId() && !GAMEDATA::getInstance()->getIsPlaying()){
            auto dissolveRoom = MenuItemImage::create("gameview/dissovle_room_btn_1.png","gameview/dissovle_room_btn_2.png",CC_CALLBACK_0(GuiLayer::dissovleRoom, this));
            auto disMenu = Menu::create(dissolveRoom,NULL);
            disMenu->setPosition(1140,85);
            disMenu->setTag(9999);
            addChild(disMenu);
        }
        
        if(!GAMEDATA::getInstance()->GAMEDATA::getInstance()->getIsRecover()||GAMEDATA::getInstance()->getLastGameDataBackup().result == 0){
            if(!GAMEDATA::getInstance()->getIsFuPan())
                drawPlayerInvite();
        }
        auto bill = MenuItemImage::create("gameview/bill_btn_1.png", "gameview/bill_btn_2.png",
                                          CC_CALLBACK_0(GuiLayer::showPlayerBill, this));
        Menu* billMenu = Menu::create(bill, NULL);
        billMenu->setPosition(Point(1225, 165));
        addChild(billMenu);
        
    }
}

void GuiLayer::drawGameInfo(){
    
    auto roomInfoBg = Sprite::create("gameview/room_id_bg.png");
    roomInfoBg->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);
    roomInfoBg->setPosition(1275,710);
    addChild(roomInfoBg);
    
    auto kaibao = Sprite::create("gameview/kai_bao.png");
    addChild(kaibao);
    
    kaibaoNum = Label::createWithSystemFont("X "+GAMEDATA::getInstance()->getKaibao(),"Arial",25);
    kaibaoNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    kaibaoNum->setColor(Color3B(233,209,112));
    addChild(kaibaoNum);
    
    auto huangfan = Sprite::create("gameview/huang_fan.png");
    addChild(huangfan);
    
    haungNum = Label::createWithSystemFont("X "+GAMEDATA::getInstance()->getHuangfan(), "Arial",25);
    haungNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    haungNum->setColor(Color3B(233,209,112));
    addChild(haungNum);
    
    if (GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom){
        //私人房间
        auto roomId = Sprite::create("gameview/fang_hao.png");
        addChild(roomId);
        auto roomIdNum = Label::createWithSystemFont(GAMEDATA::getInstance()->getFriendOpenRoomResp().prid,"Arial",25);
        roomIdNum->setTag(1088);
        roomIdNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        roomIdNum->setColor(Color3B(233,209,112));
        addChild(roomIdNum);
        
        roomId->setPosition(1160,680);
        roomIdNum->setPosition(1185,678);
        kaibao->setPosition(1160,640);
        kaibaoNum->setPosition(1200,638);
        huangfan->setPosition(1160, 610);
        haungNum->setPosition(1200, 608);
        
    }else{
        roomInfoBg->setScale(0.95, 0.68);
        kaibao->setPosition(1170,680);
        kaibaoNum->setPosition(1210,678);
        huangfan->setPosition(1170, 650);
        haungNum->setPosition(1210, 648);
    }
}





void GuiLayer::chatButtonClick(){
    auto gameChat = ChatDialog::create();
    getParent()->addChild(gameChat,50);
}

void GuiLayer::settingButtonClick(){
    Audio::getInstance()->playSoundClick();
    UserSetting* setting = UserSetting::create();
    getParent()->addChild(setting,50);
}

void GuiLayer::quitButtonClick(){
    Audio::getInstance()->playSoundClick();
    if(!GAMEDATA::getInstance()->getIsPlaying()){
        if(atoi(GAMEDATA::getInstance()->getFriendOpenRoomResp().prjucount.c_str())==0 && UserData::getInstance()->getPoxiaoId()==GAMEDATA::getInstance()->getFangZhuId() && !GAMEDATA::getInstance()->getIsPlaying()){
            HintDialog* dia = HintDialog::create("返回大厅,如需解散房间,请按解散房间按钮", [=](Ref* ref){
                GAMEDATA::getInstance()->clearPlayersInfo();
                GAMEDATA::getInstance()->setIsPlaying(false);
                NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getQuitRoomCommand());
                Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
            });
            getParent()->addChild(dia,50);
        }else if(GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom){
            HintDialog* dia = HintDialog::create("是否退出当前房间?", [=](Ref* ref){
                GAMEDATA::getInstance()->clearPlayersInfo();
                NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getQuitRoomCommand());
                Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
            });
            getParent()->addChild(dia,50);
        }else{
            GAMEDATA::getInstance()->clearPlayersInfo();
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getQuitRoomCommand());
            Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
            
        }
    }else{
        QuitRoomDialog* dialog = QuitRoomDialog::create();
        getParent()->addChild(dialog,50);
    }
}


void GuiLayer::updateData(){
    kaibaoNum->setString("X "+GAMEDATA::getInstance()->getKaibao());
    haungNum->setString("X "+GAMEDATA::getInstance()->getHuangfan());
    if(NULL != getChildByTag(1088)){
        ((Label*)getChildByTag(1088))->setString(GAMEDATA::getInstance()->getFriendOpenRoomResp().prid);
    }
}

void GuiLayer::hideInvitePlayer(int clientId){
    if (clientId == ClientSeatId::left){
        if(NULL != leftPlayerInvite)
            leftPlayerInvite->setVisible(false);
    }
    else if (clientId == ClientSeatId::right){
        if(NULL != rightPlayerInvite)
            rightPlayerInvite->setVisible(false);
    }
    else if (clientId == ClientSeatId::opposite){
        if(NULL != oppositePlayerInvite)
            oppositePlayerInvite->setVisible(false);
    }
}


void GuiLayer::showInvitePlayer(int clientId){
    if (clientId == ClientSeatId::left){
        if(NULL != leftPlayerInvite)
            leftPlayerInvite->setVisible(true);
    }
    else if (clientId == ClientSeatId::right){
        if(NULL != rightPlayerInvite)
            rightPlayerInvite->setVisible(true);
    }
    else if (clientId == ClientSeatId::opposite){
        if(NULL != oppositePlayerInvite)
            oppositePlayerInvite->setVisible(true);
    }
}


void GuiLayer::showPlayerBill(){
    Audio::getInstance()->playSoundClick();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getBillCommand());
    BillInfo* bill = BillInfo::create();
    bill->setShowPosition();
    getParent()->addChild(bill,50);
}

void GuiLayer::drawPlayerInvite(){
    MenuItemImage* left = MenuItemImage::create("headportrait/userbk.png", "headportrait/userbk.png",
                                                CC_CALLBACK_1(GuiLayer::invitePlayer, this));
    left->setTag(ClientSeatId::left);
    leftPlayerInvite = Menu::create(left, NULL);
    leftPlayerInvite->setPosition(Point(70, 455));
    addChild(leftPlayerInvite);
    MenuItemImage* right = MenuItemImage::create("headportrait/userbk.png", "headportrait/userbk.png",
                                                 CC_CALLBACK_1(GuiLayer::invitePlayer, this));
    right->setTag(ClientSeatId::right);
    rightPlayerInvite = Menu::create(right, NULL);
    rightPlayerInvite->setPosition(Point(1213, 455));
    addChild(rightPlayerInvite);
    MenuItemImage* opp = MenuItemImage::create("headportrait/userbk.png", "headportrait/userbk.png",
                                               CC_CALLBACK_1(GuiLayer::invitePlayer, this));
    opp->setTag(ClientSeatId::opposite);
    oppositePlayerInvite = Menu::create(opp, NULL);
    oppositePlayerInvite->setPosition(Point(945, 642));
    addChild(oppositePlayerInvite);
}

void GuiLayer::invitePlayer(Ref* ref){
    //TODO
}


void GuiLayer::dissovleRoom(){
    HintDialog* dia = HintDialog::create("游戏未开始前解散房间不扣除房卡,是否解散?", [=](Ref* ref){
        GAMEDATA::getInstance()->clearPlayersInfo();
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getDissolveRoomCommand());
    });
    getParent()->addChild(dia,50);
}


void GuiLayer::hideDissovleBtn(){
    if(NULL != getChildByTag(9999)){
        getChildByTag(9999)->setVisible(false);
    }
}

void GuiLayer::update(float dt){
    if(getChildByTag(1212)!=NULL){
        if(GAMEDATA::getInstance()->getIsPlaying()&&GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom){
            if(getChildByTag(1212)->isVisible())
                getChildByTag(1212)->setVisible(false);
        }
    }
    updateData();
}


void GuiLayer::onEnter(){
    Layer::onEnter();
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(UPDATE_DICE_KAOBAO_STATE, [=](EventCustom* event){
        updateData();
    });
};


void GuiLayer::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(UPDATE_DICE_KAOBAO_STATE);
};


void GuiLayer::drawTestButton(){
    auto testIamge = MenuItemImage::create("gameview/setting_btn_1.png", "gameview/setting_btn_2.png",
                                           CC_CALLBACK_0(GuiLayer::testButtonClick, this));
    Menu* testMenu = Menu::create(testIamge, NULL);
    testMenu->setPosition(640,380);
    addChild(testMenu);
    
}

//测试方法
void GuiLayer::testButtonClick(){
    //        PlayerCpgtData cpg;
    //        cpg.chi.push_back("1,2");
    //        cpg.peng ="3,3";
    //        cpg.flag = 1;
    //        cpg.poker = "1";
    //        cpg.seatId = 1;
    //        cpg.gang = "1,1,1";
    //        cpg.sId = 3;
    //        GAMEDATA::getInstance()->setPlayerCpgt(cpg);
    //        EventCustom event(MSG_OTHER_PLAYER_PENG);
    //        _eventDispatcher->dispatchEvent(&event);
    //            EventCustom event2(MSG_OTHER_PLAYER_CHI);
    //            _eventDispatcher->dispatchEvent(&event2);
    
    //    vector<GameResultData> gameResults;
    //    for (int i = 0; i < 4; i++){
    //        GameResultData resultData;
    //        if(i == 0){
    //            resultData.result = 3;
    //        }else if(i==1){
    //            resultData.result = 3;
    //        }
    //        else if(i==2){
    //            resultData.result = 2;
    //        }else{
    //            resultData.result = 0;
    //        }
    //        resultData.gold = 100;
    //        resultData.diamond = 100;
    //        resultData.jifen =10;
    //        resultData.lequan = 10;
    //        resultData.golddelta = 200000;
    //        resultData.diamonddelta =2;
    //        resultData.jifendelta = 4000000;
    //        resultData.lequandelta = 222220;
    //        resultData.seatId = i+1;
    //        resultData.umark ="100010000";
    //        resultData.hua = 3;
    //        resultData.lz = "2";
    //        resultData.fan = "10";
    //        resultData.showPoker = "1,2,3,4,5,6,7,8";
    //        resultData.huType = "3,4,13";
    //        resultData.nickName = StringUtils::format("这里是装电视台%d",i+1);
    //        gameResults.push_back(resultData);
    //    }
    //    GAMEDATA::getInstance()->setDiaopao("8");
    //    GAMEDATA::getInstance()->setGameResults(gameResults);
    //    GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
    //    GAMEDATA::getInstance()->setHeroSeatId(1);
    //    GAMEDATA::getInstance()->setPrivateLezi("0");
    //    GAMEDATA::getInstance()->setPrivateKaibao("0");
    //    GAMEDATA::getInstance()->setPrivateEmsc("1");
    //    GAMEDATA::getInstance()->setCurrentBank(1);
    //    FriendOpenRoomRespData opendata;
    //    opendata.prjushu ="8";
    //    opendata.prjucount ="2";
    //    GAMEDATA::getInstance()->setFriendOpenRoomResp(opendata);
    //    char* buf = const_cast<char*>("2");
    //    _eventDispatcher->dispatchCustomEvent(MSG_GAME_RESULT,buf);
    
//    PlayerTurnData playerTurnData;
//    playerTurnData.seatId = GAMEDATA::getInstance()->getHeroSeatId();
//    PlayerCpgtData tingData;
//    tingData.seatId = GAMEDATA::getInstance()->getHeroSeatId();
//    tingData.ting ="1";
//    playerTurnData.hastinggang = true;
//    HeroHuPaiData huPaiData;
//    huPaiData.poker = 1;
//    huPaiData.hu = "2";
//    tingData.heroHu.push_back(huPaiData);
//    HeroHuPaiData huPaiData2;
//    huPaiData2.poker = 8;
//    huPaiData2.hu = "2,5,6,7";
//    tingData.heroHu.push_back(huPaiData2);
//    playerTurnData.cpgData = tingData;
//    _eventDispatcher->dispatchCustomEvent(MSG_PLAYER_TURN_WHO, &playerTurnData);
    ChatAndroidMethod::getInstance()->sendChatInfo(UserData::getInstance()->getPoxiaoId(), "hello word");
}
