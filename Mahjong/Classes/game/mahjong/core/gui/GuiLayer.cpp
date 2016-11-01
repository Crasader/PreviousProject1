#include "game/mahjong/core/gui/GuiLayer.h"
#include "game/mahjong/lobby/LobbyScene.h"
#include "game/mahjong/state/GameData.h"
#include "game/mahjong/bill/BillInfo.h"
#include "game/mahjong/core/widget/QuitRoomDialog.hpp"
#include "game/mahjong/chat/ChatDialog.hpp"
#include "game/utils/Audio.h"
#include "game/utils/SeatIdUtil.h"
#include "server/MsgHandler.h"
#include "server/NetworkManage.h"
#include "userdata/UserData.h"
#include "game/utils/GameConfig.h"



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

void GuiLayer::initView(){
    
    auto chatButton = MenuItemImage::create("gameview/chat_btn_1.png", "gameview/chat_btn_2.png",
                                            CC_CALLBACK_0(GuiLayer::chatButtonClick, this));
    auto settingButton = MenuItemImage::create("gameview/setting_btn_1.png", "gameview/setting_btn_2.png",
                                               CC_CALLBACK_0(GuiLayer::settingButtonClick, this));
    Menu* myMenu = Menu::create(chatButton, settingButton, NULL);
    myMenu->setPosition(1225,300);
    myMenu->alignItemsVerticallyWithPadding(10);
    this->addChild(myMenu);
    
    auto quitBut = MenuItemImage::create("gameview/go_back_1.png", "gameview/go_back_2.png",
                                         CC_CALLBACK_0(GuiLayer::quitButtonClick, this));
    Menu* quit = Menu::create(quitBut, NULL);
    quit->setPosition(Point(55, 670));
    this->addChild(quit);
    
    if (GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom){
        //私人房间
        auto kaibaoBg = Sprite::create("gameview/room_id.png");
        kaibaoBg->setPosition(1180,645);
        addChild(kaibaoBg);
        
        auto openRoomId = LabelAtlas::create(GAMEDATA::getInstance()->getFriendOpenRoomResp().prid,"gameview/hua_num.png",17,24,'0');
        openRoomId->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        openRoomId->setScale(0.8f);
        openRoomId->setPosition(1180,675);
        addChild(openRoomId);
        
        kaibaoNum = LabelAtlas::create(":"+GAMEDATA::getInstance()->getKaibao(),"gameview/hua_num.png",17,24,'0');
        kaibaoNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        kaibaoNum->setScale(0.8f);
        kaibaoNum->setPosition(1180,648);
        addChild(kaibaoNum);
        
        haungNum = LabelAtlas::create(":"+GAMEDATA::getInstance()->getHuangfan(), "gameview/hua_num.png", 17, 24, '0');
        haungNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        haungNum->setScale(0.8f);
        haungNum->setPosition(1180, 618);
        addChild(haungNum);
        
        //解散牌局按钮
        if(atoi(GAMEDATA::getInstance()->getFriendOpenRoomResp().prjucount.c_str())<=1){
            auto dissolveRoom = MenuItemImage::create("gameview/dissovle_room_btn_1.png","gameview/dissovle_room_btn_2.png",CC_CALLBACK_0(GuiLayer::dissovleRoom, this));
            auto disMenu = Menu::create(dissolveRoom,NULL);
            disMenu->setPosition(1140,100);
            addChild(disMenu);
        }
        
    }
    else{
        auto kaibao = Sprite::create("gameview/kai_bao.png");
        kaibao->setPosition(1193,644);
        addChild(kaibao);
        kaibaoNum = LabelAtlas::create(":"+GAMEDATA::getInstance()->getKaibao(),"gameview/hua_num.png",17,24,'0');
        kaibaoNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        kaibaoNum->setPosition(1220,644);
        addChild(kaibaoNum);
        auto huangfan = Sprite::create("gameview/hua_fan.png");
        huangfan->setPosition(1193, 614);
        addChild(huangfan);
        haungNum = LabelAtlas::create(":"+GAMEDATA::getInstance()->getHuangfan(), "gameview/hua_num.png", 17, 24, '0');
        haungNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        haungNum->setPosition(1220, 614);
        addChild(haungNum);
    }
    
    
    
    if (GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom){
        
        if(!GAMEDATA::getInstance()->GAMEDATA::getInstance()->getIsRecover()){
            drawPlayerInvite();
        }
        auto bill = MenuItemImage::create("gameview/bill_btn_1.png", "gameview/bill_btn_2.png",
                                          CC_CALLBACK_0(GuiLayer::showPlayerBill, this));
        Menu* billMenu = Menu::create(bill, NULL);
        billMenu->setPosition(Point(1225, 180));
        addChild(billMenu);
    }
    
}

//测试方法
void GuiLayer::soundButtonClick(){
    vector<GameResultData> gameResults;
    for (int i = 0; i < 4; i++){
        GameResultData resultData;
        resultData.result = 3;
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
    EventCustom event(MSG_GAME_RESULT);
    _eventDispatcher->dispatchEvent(&event);
}

void GuiLayer::chatButtonClick(){
    auto gameChat = ChatDialog::create("");
    gameChat->setTag(1001);
    addChild(gameChat,2);
}

void GuiLayer::settingButtonClick(){
    Audio::getInstance()->playSoundClick();
    UserSetting* setting = UserSetting::create();
    this->addChild(setting,3);
}

void GuiLayer::quitButtonClick(){
    Audio::getInstance()->playSoundClick();
    if(!GAMEDATA::getInstance()->getIsPlaying()){
        GAMEDATA::getInstance()->clearPlayersInfo();
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getQuitRoomCommand());
        Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
    }else{
        QuitRoomDialog* dialog = QuitRoomDialog::create();
        addChild(dialog);
    }
}


void GuiLayer::updateData(){
    kaibaoNum->setString(":"+GAMEDATA::getInstance()->getKaibao());
    haungNum->setString(":"+GAMEDATA::getInstance()->getHuangfan());
}

void GuiLayer::hideInvitePlayer(int clientId){
    if (clientId == ClientSeatId::left){
        leftPlayerInvite->setVisible(false);
    }
    else if (clientId == ClientSeatId::right){
        rightPlayerInvite->setVisible(false);
    }
    else if (clientId == ClientSeatId::opposite){
        oppositePlayerInvite->setVisible(false);
    }
}


void GuiLayer::showInvitePlayer(int clientId){
    if (clientId == ClientSeatId::left){
        leftPlayerInvite->setVisible(true);
    }
    else if (clientId == ClientSeatId::right){
        rightPlayerInvite->setVisible(true);
    }
    else if (clientId == ClientSeatId::opposite){
        oppositePlayerInvite->setVisible(true);
    }
}


void GuiLayer::showPlayerBill(){
    Audio::getInstance()->playSoundClick();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getBillCommand());
    BillInfo* bill = BillInfo::create();
    bill->setShowPosition();
    addChild(bill);
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
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getDissolveRoomCommand());
}
