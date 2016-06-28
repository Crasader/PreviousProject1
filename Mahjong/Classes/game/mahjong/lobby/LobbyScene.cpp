#include "game/mahjong/lobby/LobbyScene.h"
#include "game/mahjong/dialog/bill/BillInfo.h"
#include "game/mahjong/dialog/shop/Redwallet.h"
#include "game/mahjong/dialog/prompt/PromptDialog.h"
#include "game/mahjong/dialog/daily/DailyEvent.h"
#include "game/mahjong/dialog/playerinfo/HeroInfoEdit.h"
#include "game/mahjong/dialog/shop/FirstChageDialog.hpp"
#include "game/mahjong/dialog/shop/ChargeGold.hpp"
#include "game/mahjong/dialog/shop/ChargeDiamond.hpp"
#include "game/mahjong/dialog/shop/LequanShop.hpp"
#include "game/mahjong/lobby/EnterRoomDialog.hpp"
#include "game/mahjong/dialog/shop/GoldNotEnoughDialog.hpp"

bool LobbyScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    initView();
    //add sprite to scene
    drawSceneTop();
    drawSceneMid();
    drawSceneBot();
    //add touch listener
    addEventListener();
    showLobbyAnim();
    return true;
}


void LobbyScene::onEnter(){
    Scene::onEnter();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getPlayerInfoCommand());
    updateHeroInfo();
    GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::publicRoom);
    addCustomEventListener();
    schedule(schedule_selector(LobbyScene::signUpdate), 0, CC_REPEAT_FOREVER, 0.2f);
}


void LobbyScene::signUpdate(float dt){
    DailySignData data = GAMEDATA::getInstance()->getDailySignData();
    if (data.result == "1"){
        unschedule(schedule_selector(LobbyScene::signUpdate));
        if(NULL == getChildByTag(6667)){
            DailyEvent* day = DailyEvent::create();
            day->setTag(6667);
            day->showDailyEvent(DailyType::sign);
            addChild(day,3);
        }
    }
}


void LobbyScene::onExit(){
    Scene::onExit();
    _eventDispatcher->removeEventListener(enterRoomListener);
    _eventDispatcher->removeEventListener(enterFriendRoomListener);
    _eventDispatcher->removeEventListener(openFriendRoomListener);
    _eventDispatcher->removeEventListener(friendInviteListener);
    _eventDispatcher->removeEventListener(updateHeroInfoListener);
    _eventDispatcher->removeEventListener(heroInfoListener);
}

void LobbyScene::updateHeroInfo(){
    ((Sprite*)getChildByTag(962))->setTexture(UserData::getInstance()->getPicture());
    nickName->setString(UserData::getInstance()->getNickName());
    goldNum ->setString(cocos2d::String::createWithFormat("%d", UserData::getInstance()->getGold())->_string);
    diamondNum->setString(cocos2d::String::createWithFormat("%d", UserData::getInstance()->getDiamond())->_string);
    lequanNum->setString(cocos2d::String::createWithFormat("%d", UserData::getInstance()->getTicket())->_string);
    lockDiamondNum->setString(cocos2d::String::createWithFormat("%d", UserData::getInstance()->getLockDiamond())->_string);
}

void LobbyScene::initView(){
    //add game bg to layer
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Sprite* lobby_bg = Sprite::create("mjlobby/lobby_bg.jpg");
    lobby_bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    addChild(lobby_bg, -1);
}

void LobbyScene::startGame(Ref* psend){
    MenuItemImage* item = (MenuItemImage*)psend;
    GAMEDATA::getInstance()->setCurrentSelectRoomId(item->getTag());
    if (item->getTag() == ROOM_1){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getEnterRoomCommand("1", StringUtil::itos(ROOM_1)));
    }
    else if (item->getTag() == ROOM_2){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getEnterRoomCommand("1", StringUtil::itos(ROOM_2)));
    }
    else if (item->getTag() == ROOM_3){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getEnterRoomCommand("1", StringUtil::itos(ROOM_3)));
    }
    showLoading();
}


//draw scene top view
void LobbyScene::drawSceneTop(){
    auto topbg = Sprite::create("mjlobby/lobby_top_bg.png");
    topbg->setPosition(430, 680);
    this->addChild(topbg);
    
    auto head_bg = Sprite::create("mjlobby/head_image_bg.png");
    head_bg->setPosition(61, 660);
    this->addChild(head_bg);
    
    auto image = Sprite::create(UserData::getInstance()->getPicture());
    image->setTag(962);
    image->setPosition(61, 660);
    addChild(image);
    
    auto head = MenuItem::create(CC_CALLBACK_0(LobbyScene::showHeroInfo, this));
    head->setContentSize(Size(90,90));
    auto headmenu = Menu::create(head, NULL);
    headmenu->setPosition(61, 660);
    this->addChild(headmenu);
    
    nickName = Label::create(UserData::getInstance()->getNickName(), "arial", 20);
    nickName->setPosition(125, 628);
    nickName->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    nickName->setAlignment(TextHAlignment::LEFT);
    this->addChild(nickName);
    
    //gold
    auto gold_bg = Sprite::create("mjlobby/room_info_bg.png");
    gold_bg->setPosition(212, 685);
    addChild(gold_bg);
    auto gold_icon = Sprite::create("mjlobby/gold_icon.png");
    gold_icon->setPosition(150, 685);
    addChild(gold_icon);
    goldNum = LabelAtlas::create(cocos2d::String::createWithFormat("%d", UserData::getInstance()->getGold())->_string,
                                 "mjlobby/room_info_num.png", 10, 15, '0');
    goldNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
    goldNum->setPosition(212, 685);
    addChild(goldNum);
    auto gold_btn = MenuItemImage::create("mjlobby/plus_btn_1.png", "mjlobby/plus_btn_2.png", CC_CALLBACK_0(LobbyScene::chargeGold, this));
    auto chargGold = Menu::create(gold_btn, NULL);
    chargGold->setPosition(274, 685);
    addChild(chargGold);
    
    //diamond
    auto diamond_bg = Sprite::create("mjlobby/room_info_bg.png");
    diamond_bg->setPosition(390, 685);
    addChild(diamond_bg);
    auto diamond_icon = Sprite::create("mjlobby/diamond_icon.png");
    diamond_icon->setPosition(329, 680);
    addChild(diamond_icon);
    diamondNum = LabelAtlas::create(cocos2d::String::createWithFormat("%d", UserData::getInstance()->getDiamond())->_string,
                                    "mjlobby/room_info_num.png", 10, 15, '0');
    diamondNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
    diamondNum->setPosition(392, 685);
    addChild(diamondNum);
    auto diamond_btn = MenuItemImage::create("mjlobby/charge_btn_1.png", "mjlobby/charge_btn_2.png", CC_CALLBACK_0(LobbyScene::chargeDiamond, this));
    auto chargDiamond = Menu::create(diamond_btn, NULL);
    chargDiamond->setPosition(457, 682);
    addChild(chargDiamond);
    
    //lock diamond
    auto lock_diamond_bg = Scale9Sprite::create("mjlobby/room_info_bg.png");
    lock_diamond_bg->setContentSize(Size(108,47));
    lock_diamond_bg->setPosition(540, 685);
    this->addChild(lock_diamond_bg);
    auto lock_diamond_icon = Sprite::create("mjlobby/lock_diamond_icon.png");
    lock_diamond_icon->setPosition(510, 680);
    addChild(lock_diamond_icon);
    lockDiamondNum = LabelAtlas::create(cocos2d::String::createWithFormat("%d", UserData::getInstance()->getLockDiamond())->_string,
                                        "mjlobby/room_info_num.png", 10, 15, '0');
    lockDiamondNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
    lockDiamondNum->setPosition(557, 685);
    addChild(lockDiamondNum);
    
    //lequan
    auto lequan_bg = Sprite::create("mjlobby/room_info_bg.png");
    lequan_bg->setPosition(690, 685);
    this->addChild(lequan_bg);
    auto lequan_icon = Sprite::create("mjlobby/lequan_icon.png");
    lequan_icon->setPosition(632, 685);
    this->addChild(lequan_icon);
    lequanNum = LabelAtlas::create(cocos2d::String::createWithFormat("%d", UserData::getInstance()->getTicket())->_string,
                                   "mjlobby/room_info_num.png", 10, 15, '0');
    lequanNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
    lequanNum->setPosition(692, 685);
    this->addChild(lequanNum);
    auto lequan_btn = MenuItemImage::create("mjlobby/plus_btn_1.png", "mjlobby/plus_btn_2.png", CC_CALLBACK_0(LobbyScene::exchangeLequan, this));
    auto chargLequan = Menu::create(lequan_btn, NULL);
    chargLequan->setPosition(756, 685);
    addChild(chargLequan);
}

void LobbyScene::drawSceneMid(){
    auto gameTitle = Sprite::create("mjlobby/game_icon.png");
    gameTitle->setPosition(1070, 640);
    this->addChild(gameTitle);
    
    auto red_wallet = MenuItemImage::create("mjlobby/red_wallet_1.png", "mjlobby/red_wallet_2.png",
                                            CC_CALLBACK_0(LobbyScene::showRedWallet, this));
    auto first_chaege = MenuItemImage::create("mjlobby/first_charge_btn_1.png", "mjlobby/first_charge_btn_2.png",
                                              CC_CALLBACK_0(LobbyScene::showFirstCharge, this));
    auto giftMenu = Menu::create(first_chaege, red_wallet, NULL);
    giftMenu->alignItemsHorizontallyWithPadding(10);
    giftMenu->setPosition(120, 542);
    this->addChild(giftMenu);
    
    auto room1 = MenuItemImage::create("mjlobby/room_level_1.png", "mjlobby/room_level_1.png", CC_CALLBACK_1(LobbyScene::startGame, this));
    auto room2 = MenuItemImage::create("mjlobby/room_level_2.png", "mjlobby/room_level_2.png", CC_CALLBACK_1(LobbyScene::startGame, this));
    auto room3 = MenuItemImage::create("mjlobby/room_level_3.png", "mjlobby/room_level_3.png", CC_CALLBACK_1(LobbyScene::startGame, this));
    auto gameMenu = Menu::create();
    RoomListData roomList = GAMEDATA::getInstance()->getRoomList();
    for (int i = 0; i < roomList.rooms.size(); i++){
        if (roomList.rooms.at(i) == ROOM_1){
            gameMenu->addChild(room1);
            room1->setTag(ROOM_1);
        }
        else if (roomList.rooms.at(i) == ROOM_2){
            gameMenu->addChild(room2);
            room2->setTag(ROOM_2);
        }
        else if (roomList.rooms.at(i) == ROOM_3){
            gameMenu->addChild(room3);
            room3->setTag(ROOM_3);
        }
    }
    gameMenu->alignItemsHorizontallyWithPadding(20);
    gameMenu->setPosition(790, 342);
    this->addChild(gameMenu,2);
    
    //    LabelAtlas* fen_500 = LabelAtlas::create("500","mjlobby/player_info_num.png",15,22,'0');
    //    fen_500->setAnchorPoint(Point::ANCHOR_MIDDLE);
    //    fen_500->setPosition(457, 165);
    //    addChild(fen_500);
    //    Sprite* di_1 = Sprite::create("mjlobby/font_di.png");
    //    di_1->setPosition(496,165);
    //    addChild(di_1);
    //    LabelAtlas* hua_500 = LabelAtlas::create("500", "mjlobby/player_info_num.png", 15, 22, '0');
    //    hua_500->setAnchorPoint(Point::ANCHOR_MIDDLE);
    //    hua_500->setPosition(539, 165);
    //    addChild(hua_500);
    //    Sprite* hua_1 = Sprite::create("mjlobby/font_hua.png");
    //    hua_1->setPosition(578, 165);
    //    addChild(hua_1);
    
    //    LabelAtlas* fen_5k = LabelAtlas::create("5000", "mjlobby/player_info_num.png", 15, 22, '0');
    //    fen_5k->setAnchorPoint(Point::ANCHOR_MIDDLE);
    //    fen_5k->setPosition(753, 165);
    //    addChild(fen_5k);
    //    Sprite* di_2 = Sprite::create("mjlobby/font_di.png");
    //    di_2->setPosition(793, 165);
    //    addChild(di_2);
    //    LabelAtlas* hua_5k = LabelAtlas::create("5000", "mjlobby/player_info_num.png", 15, 22, '0');
    //    hua_5k->setAnchorPoint(Point::ANCHOR_MIDDLE);
    //    hua_5k->setPosition(838, 165);
    //    addChild(hua_5k);
    //    Sprite* hua_2 = Sprite::create("mjlobby/font_hua.png");
    //    hua_2->setPosition(880, 165);
    //    addChild(hua_2);
    
    //    LabelAtlas* fen_5w = LabelAtlas::create("5", "mjlobby/player_info_num.png", 15, 22, '0');
    //    fen_5w->setAnchorPoint(Point::ANCHOR_MIDDLE);
    //    fen_5w->setPosition(1030, 165);
    //    addChild(fen_5w);
    //    Sprite* font_w1= Sprite::create("mjlobby/font_wan.png");
    //    font_w1->setPosition(1050,165);
    //    addChild(font_w1);
    //    Sprite* di_3= Sprite::create("mjlobby/font_di.png");
    //    di_3->setPosition(1075, 165);
    //    addChild(di_3);
    //    LabelAtlas* hua_5w= LabelAtlas::create("5", "mjlobby/player_info_num.png", 15, 22, '0');
    //    hua_5w->setAnchorPoint(Point::ANCHOR_MIDDLE);
    //    hua_5w->setPosition(1120, 165);
    //    addChild(hua_5w);
    //    Sprite* font_w2 = Sprite::create("mjlobby/font_wan.png");
    //    font_w2->setPosition(1140, 165);
    //    addChild(font_w2);
    //    Sprite* hua_3 = Sprite::create("mjlobby/font_hua.png");
    //    hua_3->setPosition(1164, 165);
    //    addChild(hua_3);
}

void LobbyScene::drawSceneBot(){
    auto bot_bg = Sprite::create("mjlobby/lobby_bottom_bg.png");
    bot_bg->setPosition(821,48);
    addChild(bot_bg);
    
    auto btn_1 = MenuItemImage::create("mjlobby/friend_btn_1.png", "mjlobby/friend_btn_2.png", CC_CALLBACK_0(LobbyScene::showAddFriend, this));
    auto btn_2 = MenuItemImage::create("mjlobby/bill_btn_1.png", "mjlobby/bill_btn_2.png", CC_CALLBACK_0(LobbyScene::showPlayerBill, this));
    auto btn_3 = MenuItemImage::create("mjlobby/task_btn_1.png", "mjlobby/task_btn_2.png", CC_CALLBACK_0(LobbyScene::showDayTask, this));
    auto btn_4 = MenuItemImage::create("mjlobby/activity_btn_1.png", "mjlobby/activity_btn_2.png", CC_CALLBACK_0(LobbyScene::showHotActivity, this));
    auto btn_5 = MenuItemImage::create("mjlobby/setting_btn_1.png", "mjlobby/setting_btn_2.png", CC_CALLBACK_0(LobbyScene::showGameSetting, this));
    auto gameMenu = Menu::create(btn_1, btn_2, btn_3, btn_4, btn_5, NULL);
    gameMenu->alignItemsHorizontallyWithPadding(65);
    gameMenu->setPosition(785, 43);
    addChild(gameMenu);
    //TODO 好友开房功能暂时关闭
    //    auto openRoom = MenuItemImage::create("mjlobby/open_room_btn_1.png", "mjlobby/open_room_btn_2.png", CC_CALLBACK_0(LobbyScene::showOpenRoom, this));
    //    auto openMenu = Menu::create(openRoom,NULL);
    //    openMenu->setPosition(1203,67);
    //    addChild(openMenu);
    
}

void LobbyScene::showFirstCharge(){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getFirstChargeInfoCommand());
    //首冲
    FirstChargeDialog* firCharge = FirstChargeDialog::create();
    addChild(firCharge,3);
}

void LobbyScene::showRedWallet(){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getSendRedWalletCommand());
    Redwallet* wallet = Redwallet::create();
    this->addChild(wallet,3);
}

void LobbyScene::showDayTask(){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getDailyTaskCommand());
    DailyEvent* day = DailyEvent::create();
    day->showDailyEvent(DailyType::task);
    addChild(day,3);
}


void LobbyScene::showAddFriend(){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getFriendListCommand());
    FriendListView* friendAdd = FriendListView::create();
    friendAdd->setTag(524);
    addChild(friendAdd,3);
    
}

void LobbyScene::showOpenRoom(){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getFriendListCommand());
    FriendRoom* friendroom = FriendRoom::create();
    friendroom->setTag(525);
    this->addChild(friendroom,3);
}

void LobbyScene::showPlayerBill(){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getBillCommand());
    BillInfo* billInfoView = BillInfo::create();
    billInfoView->setTag(526);
    addChild(billInfoView,3);
}

void LobbyScene::showGameSetting(){
    UserSetting* setting = UserSetting::create();
    this->addChild(setting,3);
}

void LobbyScene::showHotActivity(){
    //TODO
}

void LobbyScene::showHeroInfo(){
    HeroInfoEdit* dialog = HeroInfoEdit::create(1);
    this->addChild(dialog,3);
}

void LobbyScene::chargeGold(){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getGoldChangeListCommand());
    ChargeGold* gold = ChargeGold::create();
    addChild(gold,3);
}

void LobbyScene::chargeDiamond(){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getDiamondChangeListCommand());
    ChargeDiamond* charge = ChargeDiamond::create();
    this->addChild(charge,3);
}

void LobbyScene::exchangeLequan(){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getLequanChangeListCommand());
    LequanShop* shop = LequanShop::create();
    addChild(shop,3);
}

void LobbyScene::showLoading(){
    Loading* loadLayer = Loading::create();
    loadLayer->setTag(1000);
    this->addChild(loadLayer,3);
}



void LobbyScene::removeLoading(){
    if(NULL != getChildByTag(1000)){
        getChildByTag(1000)->removeFromParent();
    }
}

void LobbyScene::addCustomEventListener(){
    //进入房间回复
    enterRoomListener = EventListenerCustom::create(MSG_ENTER_ROOM_RESP, [=](EventCustom* event){
        
        removeLoading();
        
        if (GAMEDATA::getInstance()->getEnterRoomResp().result == "1"){
            Director::getInstance()->replaceScene(TransitionFade::create(1, MjGameScene::create()));
        } else if(GAMEDATA::getInstance()->getEnterRoomResp().result == "2"){
            GoldNotEnoughDialog* gold = GoldNotEnoughDialog::create(GAMEDATA::getInstance()->getCurrentSelectRoomId());
            addChild(gold,4);
        }
        else if(GAMEDATA::getInstance()->getEnterRoomResp().result == "3"){
            if(atoi(GAMEDATA::getInstance()->getEnterRoomResp().rsid.c_str()) == ROOM_2){
                EnterRoomDialog* dia = EnterRoomDialog::create(EnterRoomDialogType::goldMoreLeve1);
                addChild(dia,4);
            }else if(atoi(GAMEDATA::getInstance()->getEnterRoomResp().rsid.c_str()) == ROOM_3){
                EnterRoomDialog* dia = EnterRoomDialog::create(EnterRoomDialogType::goldMoreLeve2);
                addChild(dia,4);
            }
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(enterRoomListener, 1);
    //进入好友房间回复
    enterFriendRoomListener = EventListenerCustom::create(MSG_ENTER_FRIEND_ROOM_RESP, [=](EventCustom* event){
        char* buf = static_cast<char*>(event->getUserData());
        std::string result = buf;
        if (result == "1"){
            removeLoading();
            GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
            Director::getInstance()->replaceScene(TransitionFade::create(1, MjGameScene::create()));
        }
        else{
            removeLoading();
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(enterFriendRoomListener, 1);
    
    //好友开房
    openFriendRoomListener = EventListenerCustom::create(MSG_FRIEND_OPEN_ROOM_RESP, [=](EventCustom* event){
        GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
        Director::getInstance()->replaceScene(TransitionFade::create(1, MjGameScene::create()));
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(openFriendRoomListener, 1);
    
    //好友开房通知
    friendInviteListener = EventListenerCustom::create(MSG_FRIEND_OPEN_ROOM_NOTIFY, [=](EventCustom* event){
        PromptDialog* invite = PromptDialog::create();
        invite->setTextInfo(0);
        addChild(invite,4);
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(friendInviteListener, 1);
    
    //刷新自己的信息
    updateHeroInfoListener =  EventListenerCustom::create(MSG_UPDATE_HERO_INFO, [=](EventCustom* event){
        updateHeroInfo();
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(updateHeroInfoListener, 1);
    
    heroInfoListener = EventListenerCustom::create(MSG_PLAYER_INFO_RESP, [=](EventCustom* event){
        updateHeroInfo();
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(heroInfoListener, 1);
}


void LobbyScene::addEventListener(){
    auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
        switch (code)
        {
            case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
                NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getLobbyQuitCommand());
                Director::getInstance()->end();
                break;
                
            default:
                break;
        }
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}



void LobbyScene::showLobbyAnim(){
    //中级房间眨眼
    auto levelMidEye = Sprite::create();
    levelMidEye->setPosition(790,342);
    addChild(levelMidEye,2);
    levelMidEye->runAction(Repeat::create(Sequence::create(
                                                           CallFunc::create([=](){
        levelMidEye->setTexture("mjlobby/level_2_eye_1.png");
    }),
                                                           DelayTime::create(2.0/24),
                                                           CallFunc::create([=](){
        levelMidEye->setTexture("mjlobby/level_2_eye_2.png");
    }),
                                                           DelayTime::create(2.0/24),
                                                           CallFunc::create([=](){
        levelMidEye->setTexture("mjlobby/level_2_eye_1.png");
    }),
                                                           DelayTime::create(2.0/24),
                                                           CallFunc::create([=](){
        levelMidEye->setTexture("");
    }),
                                                           DelayTime::create(96.0/24),
                                                           NULL), CC_REPEAT_FOREVER));
    
    
    //高级房间眨眼
    auto levelHighEye = Sprite::create();
    levelHighEye->setPosition(1084,342);
    addChild(levelHighEye,2);
    levelHighEye->runAction(Repeat::create(Sequence::create(DelayTime::create(20.0/24),
                                                            CallFunc::create([=](){
        levelHighEye->setTexture("mjlobby/level_3_eye_1.png");
    }),
                                                            DelayTime::create(2.0/24),
                                                            CallFunc::create([=](){
        levelHighEye->setTexture("mjlobby/level_3_eye_2.png");
    }),
                                                            DelayTime::create(2.0/24),
                                                            CallFunc::create([=](){
        levelHighEye->setTexture("mjlobby/level_3_eye_1.png");
    }),
                                                            DelayTime::create(2.0/24),
                                                            CallFunc::create([=](){
        levelHighEye->setTexture("");
    }),
                                                            DelayTime::create(76.0/24),
                                                            NULL), CC_REPEAT_FOREVER));
    
    //初级房间眨眼
    auto levelLowEye = Sprite::create();
    levelLowEye->setPosition(496,342);
    addChild(levelLowEye,2);
    levelLowEye->runAction(Repeat::create(Sequence::create(
                                                           DelayTime::create(40.0/24),
                                                           CallFunc::create([=](){
        levelLowEye->setTexture("mjlobby/level_1_eye_1.png");
    }),
                                                           DelayTime::create(2.0/24),
                                                           CallFunc::create([=](){
        levelLowEye->setTexture("mjlobby/level_1_eye_2.png");
    }),
                                                           DelayTime::create(2.0/24),
                                                           CallFunc::create([=](){
        levelLowEye->setTexture("mjlobby/level_1_eye_1.png");
    }),
                                                           DelayTime::create(2.0/24),
                                                           CallFunc::create([=](){
        levelLowEye->setTexture("");
    }),
                                                           DelayTime::create(56.0/24),
                                                           NULL), CC_REPEAT_FOREVER));
    //中级房光效
    auto midLight1 = Sprite::create("mjlobby/mid_light.png");
    midLight1->setVisible(false);
    addChild(midLight1,2);
    midLight1->runAction(Repeat::create(Sequence::create(DelayTime::create(10.0/24), CallFunc::create([=](){
        midLight1->setPosition(800,190);
        midLight1->setVisible(true);
    }), MoveTo::create(20.0/24, Point(800,500)),CallFunc::create([=](){
        midLight1->setVisible(false);
    }), DelayTime::create(66.0/24),NULL), CC_REPEAT_FOREVER));
    
    auto midLight2 = Sprite::create("mjlobby/mid_light.png");
    addChild(midLight2,2);
    midLight2->runAction(Repeat::create(Sequence::create(DelayTime::create(18.0/24), CallFunc::create([=](){
        midLight2->setPosition(800,190);
        midLight2->setVisible(true);
    }), MoveTo::create(20.0/24, Point(800,500)),CallFunc::create([=](){
        midLight2->setVisible(false);
    }),DelayTime::create(58.0/24),NULL), CC_REPEAT_FOREVER));
    
    auto midLight3 = Sprite::create("mjlobby/mid_light.png");
    addChild(midLight3,2);
    midLight3->runAction(Repeat::create(Sequence::create(DelayTime::create(26.0/24), CallFunc::create([=](){
        midLight3->setPosition(800,190);
        midLight3->setVisible(true);
    }), MoveTo::create(20.0/24, Point(800,500)),CallFunc::create([=](){
        midLight3->setVisible(false);
    }),DelayTime::create(50.0/24),NULL), CC_REPEAT_FOREVER));
    
    auto midLight4 = Sprite::create("mjlobby/mid_light_yellow.png");
    midLight4->setPosition(790,342);
    midLight4->setOpacity(0);
    addChild(midLight4,2);
    midLight4->runAction(Repeat::create(Sequence::create(DelayTime::create(10.0/24),FadeTo::create(36.0/24, 255),CallFunc::create([=](){
        midLight4->setOpacity(0);
    }),DelayTime::create(50.0/24), NULL),CC_REPEAT_FOREVER));
    
    //logo光效
    auto logoLight = Sprite::create();
    logoLight->setPosition(1070, 645);
    addChild(logoLight);
    auto animation = Animation::create();
    for( int i=1;i<4;i++)
    {
        std::string imageName = cocos2d::String::createWithFormat("mjlobby/lobby_logo_light_%d.png",i)->_string;
        animation->addSpriteFrameWithFile(imageName);
    }
    // should last 1 seconds. And there are 24 frames.
    animation->setDelayPerUnit(4.0f/ 24.0f);
    animation->setRestoreOriginalFrame(true);
    auto action = Animate::create(animation);
    logoLight->runAction(Sequence::create(Repeat::create(Sequence::create(action,DelayTime::create(12.0f/24), NULL), CC_REPEAT_FOREVER), NULL));
    
    //文字光效
    auto logoText = Sprite::create();
    logoText->setPosition(1070, 645);
    addChild(logoText);
    auto animation2 = Animation::create();
    for( int j=1;j<5;j++)
    {
        std::string imageName = cocos2d::String::createWithFormat("mjlobby/lobby_logo_text_%d.png",j)->_string;
        animation2->addSpriteFrameWithFile(imageName);
    }
    // should last 1 seconds. And there are 24 frames.
    animation2->setDelayPerUnit(3.0f / 24.0f);
    animation2->setRestoreOriginalFrame(true);
    auto action2 = Animate::create(animation2);
    logoText->runAction(Sequence::create(Repeat::create(Sequence::create(action2,DelayTime::create(24.0/24), NULL), CC_REPEAT_FOREVER), NULL));
    
    //光效
    auto lobbyLight_1 = Sprite::create("mjlobby/lobby_light_1.png");
    lobbyLight_1->setPosition(640, 360);
    addChild(lobbyLight_1);
    lobbyLight_1->runAction(Sequence::create(Repeat::create(Sequence::create(FadeTo::create(1.0f, 0),FadeTo::create(1.0f, 255),NULL), CC_REPEAT_FOREVER),NULL));
    
    auto lobbyLight_2 = Sprite::create("mjlobby/lobby_light_2.png");
    lobbyLight_2->setPosition(640, 360);
    addChild(lobbyLight_2);
    lobbyLight_2->runAction(Sequence::create(Repeat::create(Sequence::create(FadeTo::create(1.0f, 0),FadeTo::create(1.0f, 255),NULL), CC_REPEAT_FOREVER),NULL));
    
    auto lobbyLight_3 = Sprite::create("mjlobby/lobby_light_3.png");
    lobbyLight_3->setPosition(640, 360);
    addChild(lobbyLight_3);
    lobbyLight_3->runAction(Sequence::create(Repeat::create(Sequence::create(FadeTo::create(1.0f, 0),FadeTo::create(1.0f, 255),NULL), CC_REPEAT_FOREVER),NULL));
    
    //光斑
    auto lightSpot1 = Sprite::create("mjlobby/light_spot.png");
    lightSpot1->setPosition(640,360);
    lightSpot1->setTag(602);
    addChild(lightSpot1);
    auto lightSpot = Sprite::create("mjlobby/light_spot.png");
    lightSpot->setPosition(-640,360);
    lightSpot1->setTag(603);
    addChild(lightSpot);
    schedule(schedule_selector(LobbyScene:: scrollLightSpot), 0, CC_REPEAT_FOREVER, 0);
    
    
}


void LobbyScene:: scrollLightSpot(float dt){
    if(NULL!=getChildByTag(602)){
        if(getChildByTag(602)->getPositionX()>1920){
            getChildByTag(602)->setPosition(-640,360);
        }else{
            getChildByTag(602)->setPosition(getChildByTag(602)->getPosition().x+1,getChildByTag(602)->getPosition().y);
        }
    }
    if(NULL!=getChildByTag(603)){
        if(getChildByTag(603)->getPositionX()>1920){
            getChildByTag(603)->setPosition(-640,360);
        }
        getChildByTag(603)->setPosition(getChildByTag(603)->getPosition().x+1,getChildByTag(603)->getPosition().y);
    }
}






