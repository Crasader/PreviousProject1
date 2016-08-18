#include "game/mahjong/core/gui/GuiLayer.h"
#include "game/mahjong/dialog/shop/ChargeDiamond.hpp"
#include "game/mahjong/lobby/LobbyScene.h"
#include "game/mahjong/dialog/friend/FriendInvite.h"
#include "game/mahjong/state/GameData.h"
#include "game/utils/SeatIdUtil.h"
#include "server/MsgHandler.h"
#include "server/NetworkManage.h"
#include "userdata/UserData.h"
#include "game/mahjong/dialog/bill/BillInfo.h"
#include "game/mahjong/core/widget/QuitRoomDialog.hpp"
#include "game/utils/Audio.h"
#include "game/mahjong/chat/ChatDialog.hpp"
#include "ui/UIImageView.h"
#include "ui/UIRichText.h"
#include "game/mahjong/chat/PlayerChatManage.hpp"



bool GuiLayer::init(){
    if (!Layer::init()){
        return false;
    }
    initView();
    return true;
}


void GuiLayer::onEnter(){
    Layer::onEnter();
    auto roomChatListener = EventListenerCustom::create(MSG_PLAYER_ROOM_CHAT_SHOW, [=](EventCustom* event){
        ChatData data = GAMEDATA::getInstance()->getChatData();
        std::string content = data.content;
        vector<std::string> msgs =PlayerChatManage::getInstance()->splitContentByFace(content);
        RichText* text = RichText ::create();
        text->setAnchorPoint(Point::ANCHOR_MIDDLE);
        for(auto var : msgs){
            if(!PlayerChatManage::getInstance()->isFaceImage(var)){
                RichElementText* element1 = RichElementText::create(1, Color3B(255,255,255), 255, var, "arial", 20);
                text->pushBackElement(element1);
                text->formatText();
            }else{
                RichElementImage* element2 = RichElementImage::create(1, Color3B(255,255,255), 255, PlayerChatManage::getInstance()->getFaceImageName(var));
                text->pushBackElement(element2);
                text->formatText();
            }
        }

    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(roomChatListener, 1);
};


void GuiLayer::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(MSG_PLAYER_ROOM_CHAT_SHOW);
};

void GuiLayer::initView(){
//    auto soundButton = MenuItemImage::create("gameview/chat_sound_1.png", "gameview/chat_sound_2.png",
//                                             CC_CALLBACK_0(GuiLayer::soundButtonClick, this));
//    auto soundMenu = Menu::create(soundButton,NULL);
//    soundMenu->setPosition(65,45);
//    addChild(soundMenu);
    
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
    
    auto kaibaoBg = Sprite::create("gameview/kai_bao_bg.png");
    kaibaoBg->setPosition(1215,625);
    this->addChild(kaibaoBg);
    auto kaibao = Sprite::create("gameview/kai_bao.png");
    kaibao->setPosition(1193,644);
    this->addChild(kaibao);
    kaibaoNum = LabelAtlas::create(":"+GAMEDATA::getInstance()->getKaibao(),"gameview/hua_num.png",17,24,'0');
    kaibaoNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    kaibaoNum->setPosition(1220,644);
    addChild(kaibaoNum);
    auto huangfan = Sprite::create("gameview/hua_fan.png");
    huangfan->setPosition(1193, 614);
    this->addChild(huangfan);
    haungNum = LabelAtlas::create(":"+GAMEDATA::getInstance()->getHuangfan(), "gameview/hua_num.png", 17, 24, '0');
    haungNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    haungNum->setPosition(1220, 614);
    addChild(haungNum);
    
    if (GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom && !GAMEDATA::getInstance()->GAMEDATA::getInstance()->getIsRecover()){
        
        drawPlayerInvite();
        
        auto bill = MenuItemImage::create("gameview/bill_btn_1.png", "gameview/bill_btn_2.png",
                                          CC_CALLBACK_0(GuiLayer::showPlayerBill, this));
        Menu* billMenu = Menu::create(bill, NULL);
        billMenu->setPosition(Point(1225, 180));
        addChild(billMenu);
    }
}

void GuiLayer::soundButtonClick(){
//        vector<GameResultData> gameResults;
//        for (int i = 0; i < 4; i++){
//            GameResultData resultData;
//            resultData.result = 3;
//            resultData.gold = 100;
//            resultData.diamond = 100;
//            resultData.jifen =10;
//            resultData.lequan = 10;
//            resultData.golddelta = 200000;
//            resultData.diamonddelta =2;
//            resultData.jifendelta = 2;
//            resultData.lequandelta = 2000;
//            resultData.seatId = i+1;
//            resultData.hua = 3;
//            resultData.showPoker = "1,2,3,4,5,5,5,5";
//            resultData.huType = "1";
//            resultData.nickName = "abc";
//            gameResults.push_back(resultData);
//        }
//        GAMEDATA::getInstance()->setGameResults(gameResults);
//        EventCustom event(MSG_GAME_RESULT);
//        _eventDispatcher->dispatchEvent(&event);
}

void GuiLayer::chatButtonClick(){
    auto gameChat = ChatDialog::create("");
    gameChat->setTag(1001);
    addChild(gameChat);
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
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getFriendListCommand());
    FriendInvite* invite = FriendInvite::create();
    addChild(invite);
}