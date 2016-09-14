#include "game/mahjong/lobby/LobbyScene.h"
#include "game/mahjong/bill/BillInfo.h"
#include "game/mahjong/dialog/prompt/HintDialog.hpp"
#include "game/mahjong/daily/DailyEvent.h"
#include "game/mahjong/lobby/EnterRoomDialog.hpp"
#include "game/mahjong/playerinfo/HeroInfoEdit.h"
#include "game/mahjong/activities/MahjongActivities.hpp"
#include "game/mahjong/shop/FirstChageDialog.hpp"
#include "game/mahjong/shop/ChargeGold.hpp"
#include "game/mahjong/shop/ChargeDiamond.hpp"
#include "game/mahjong/shop/LequanShop.hpp"
#include "game/mahjong/shop/GoldNotEnoughDialog.hpp"
#include "game/mahjong/shop/DiamondNotEnoughDialog.hpp"
#include "game/mahjong/shop/relieve/GoldRelieve.hpp"
#include "game/mahjong/share/Redwallet.h"
#include "game/mahjong/shop/ShopHintDialog.hpp"
#include "payment/android/CallAndroidMethod.h"
#include "game/utils/ParticleUtil.hpp"
#include "game/utils/GameConfig.h"
#include "game/utils/Audio.h"


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
    showLobbyAnim();
    return true;
}


void LobbyScene::onEnter(){
    Scene::onEnter();
    addEventListener();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getPlayerInfoCommand());
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getFriendListCommand());
    GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::publicRoom);
    schedule(schedule_selector(LobbyScene::signUpdate), 0, CC_REPEAT_FOREVER, 0.2f);
    schedule([=](float dt){
        updateHeroInfo();
    }, 1.0, 5, 0,"updatePlayerInfo");
    
}


void LobbyScene::onExit(){
    Scene::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(enterRoomListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(enterFriendRoomListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(openFriendRoomListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(friendInviteListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(updateHeroInfoListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(lobbyConncetAgainListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(jjjPrideListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(bzjjjPrideListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(intnetListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(loginReplaceListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(inviteReplaceListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(friendChatListener);
     Director::getInstance()->getEventDispatcher()->removeEventListener(payDialogListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(payResultListener);
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
    
    if(GAMEDATA::getInstance()->getShowDialogType() == 2){
        for(auto var : GAMEDATA::getInstance()->getRoomList().rooms){
            if(GAMEDATA::getInstance()->getCurrentSelectRoomId() == var.roomId){
                GoldNotEnoughDialog* gold = GoldNotEnoughDialog::create(GAMEDATA::getInstance()->getCurrentSelectRoomId());
                addChild(gold,30);
            }
        }
        GAMEDATA::getInstance()->setShowDialogType(-1);
    }
    else if(GAMEDATA::getInstance()->getShowDialogType() == 3){
        if(atoi(GAMEDATA::getInstance()->getEnterRoomResp().rsid.c_str()) == ROOM_2){
            EnterRoomDialog* dia = EnterRoomDialog::create(EnterRoomDialogType::goldMoreLeve1);
            addChild(dia,30);
        }else if(atoi(GAMEDATA::getInstance()->getEnterRoomResp().rsid.c_str()) == ROOM_3){
            EnterRoomDialog* dia = EnterRoomDialog::create(EnterRoomDialogType::goldMoreLeve2);
            addChild(dia,30);
        }
        GAMEDATA::getInstance()->setShowDialogType(-1);
    }
    else if(GAMEDATA::getInstance()->getShowDialogType() == 4){
        DiamondNotEnoughDialog* charge = DiamondNotEnoughDialog::create();
        addChild(charge,30);
        GAMEDATA::getInstance()->setShowDialogType(-1);
    }
}

void LobbyScene::updateHeroInfo(){
    
    if(UserData::getInstance()->getPicture() == "1"){
        ((Sprite*)getChildByTag(962))->setTexture("gameview/head_image_1.png");
    }else if(UserData::getInstance()->getPicture() == "2"){
        ((Sprite*)getChildByTag(962))->setTexture("gameview/head_image_2.png");
    }else if(UserData::getInstance()->getPicture() == "3"){
        ((Sprite*)getChildByTag(962))->setTexture("gameview/head_image_3.png");
    }else if(UserData::getInstance()->getPicture() == "4"){
        ((Sprite*)getChildByTag(962))->setTexture("gameview/head_image_4.png");
    }else{
        //TODO
        log("服务器下发的头像图片不存在");
    }
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
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getEnterRoomCommand("1",StringUtil::itos(ROOM_1)));
        showLoading();
    }
    else if (item->getTag() == ROOM_2){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getEnterRoomCommand("1", StringUtil::itos(ROOM_2)));
        showLoading();
    }
    else if (item->getTag() == ROOM_3){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getEnterRoomCommand("1", StringUtil::itos(ROOM_3)));
        showLoading();
    }
    
}


//draw scene top view
void LobbyScene::drawSceneTop(){
    auto topbg = Sprite::create("mjlobby/lobby_top_bg.png");
    topbg->setPosition(430, 680);
    this->addChild(topbg);
    
    auto head_bg = Sprite::create("mjlobby/head_image_bg.png");
    head_bg->setPosition(61, 660);
    this->addChild(head_bg);
    
    auto image = Sprite::create();
    if(UserData::getInstance()->getPicture() == "1"){
        image->setTexture("gameview/head_image_1.png");
    }else if(UserData::getInstance()->getPicture() == "2"){
        image->setTexture("gameview/head_image_2.png");
    }else if(UserData::getInstance()->getPicture() == "3"){
        image->setTexture("gameview/head_image_3.png");
    }else if(UserData::getInstance()->getPicture() == "4"){
        image->setTexture("gameview/head_image_4.png");
    }else{
        //TODO
        log("服务器下发的头像图片不存在");
    }
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
        if (roomList.rooms.at(i).roomId == ROOM_1){
            gameMenu->addChild(room1);
            room1->setTag(ROOM_1);
        }
        else if (roomList.rooms.at(i).roomId == ROOM_2){
            gameMenu->addChild(room2);
            room2->setTag(ROOM_2);
        }
        else if (roomList.rooms.at(i).roomId == ROOM_3){
            gameMenu->addChild(room3);
            room3->setTag(ROOM_3);
        }
    }
    gameMenu->alignItemsHorizontallyWithPadding(20);
    gameMenu->setPosition(790, 342);
    this->addChild(gameMenu,2);
    
}

void LobbyScene::drawSceneBot(){
    auto bot_bg = Sprite::create("mjlobby/lobby_bottom_bg.png");
    bot_bg->setPosition(821,48);
    addChild(bot_bg);
    
    auto btn_1 = MenuItemImage::create("mjlobby/friend_btn_1.png", "mjlobby/friend_btn_2.png", CC_CALLBACK_0(LobbyScene::showAddFriend, this));
    auto btn_2 = MenuItemImage::create("mjlobby/bill_btn_1.png", "mjlobby/bill_btn_2.png", CC_CALLBACK_0(LobbyScene::showPlayerBill, this));
    auto btn_3 = MenuItemImage::create("mjlobby/task_btn_1.png", "mjlobby/task_btn_2.png", CC_CALLBACK_0(LobbyScene::showDayTask, this));
//    auto btn_4 = MenuItemImage::create("mjlobby/activity_btn_1.png", "mjlobby/activity_btn_2.png", CC_CALLBACK_0(LobbyScene::showHotActivity, this));
    auto btn_5 = MenuItemImage::create("mjlobby/setting_btn_1.png", "mjlobby/setting_btn_2.png", CC_CALLBACK_0(LobbyScene::showGameSetting, this));
    auto gameMenu = Menu::create(btn_1, btn_2,btn_3, btn_5, NULL);
    gameMenu->alignItemsHorizontallyWithPadding(75);
    gameMenu->setPosition(785, 43);
    addChild(gameMenu);
    auto openRoom = MenuItemImage::create("mjlobby/open_room_btn_1.png", "mjlobby/open_room_btn_2.png", CC_CALLBACK_0(LobbyScene::showOpenRoom, this));
    auto openMenu = Menu::create(openRoom,NULL);
    openMenu->setPosition(1203,67);
    addChild(openMenu);
    
}

void LobbyScene::showFirstCharge(){
    Audio::getInstance()->playSoundClick();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getFirstChargeInfoCommand());
    //首冲
    FirstChargeDialog* firCharge = FirstChargeDialog::create();
    addChild(firCharge,3);
}

void LobbyScene::showRedWallet(){
    Audio::getInstance()->playSoundClick();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getSendRedWalletCommand());
    Redwallet* wallet = Redwallet::create();
    this->addChild(wallet,3);
}

void LobbyScene::showDayTask(){
    Audio::getInstance()->playSoundClick();
    DailyEvent* day = DailyEvent::create();
    day->showDailyEvent(DailyType::task);
    addChild(day,3);
}


void LobbyScene::showAddFriend(){
    Audio::getInstance()->playSoundClick();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getFriendListCommand());
    FriendListView* friendAdd = FriendListView::create();
    friendAdd->setTag(524);
    addChild(friendAdd,3);
    
}

void LobbyScene::showOpenRoom(){
    Audio::getInstance()->playSoundClick();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getFriendListCommand());
    if(UserData::getInstance()->getDiamond()+UserData::getInstance()->getLockDiamond()<2){
        DiamondNotEnoughDialog* charge = DiamondNotEnoughDialog::create();
        addChild(charge,30);
    }else{
        FriendRoom* friendroom = FriendRoom::create();
        friendroom->setTag(525);
        this->addChild(friendroom,3);
    }
}

void LobbyScene::showPlayerBill(){
    Audio::getInstance()->playSoundClick();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getBillCommand());
    BillInfo* billInfoView = BillInfo::create();
    billInfoView->setTag(526);
    addChild(billInfoView,3);
}

void LobbyScene::showGameSetting(){
    Audio::getInstance()->playSoundClick();
    UserSetting* setting = UserSetting::create();
    addChild(setting,3);
}

void LobbyScene::showHotActivity(){
    Audio::getInstance()->playSoundClick();
    MahjongActivities* act = MahjongActivities::create();
    addChild(act,3);
}

void LobbyScene::showHeroInfo(){
    Audio::getInstance()->playSoundClick();
    HeroInfoEdit* dialog = HeroInfoEdit::create(1);
    this->addChild(dialog,3);
}

void LobbyScene::chargeGold(){
    Audio::getInstance()->playSoundClick();
    ChargeGold* gold = ChargeGold::create();
    addChild(gold,3);
}

void LobbyScene::chargeDiamond(){
    Audio::getInstance()->playSoundClick();
    ChargeDiamond* charge = ChargeDiamond::create();
    this->addChild(charge,3);
}

void LobbyScene::exchangeLequan(){
    Audio::getInstance()->playSoundClick();
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


void LobbyScene::addEventListener(){
    //进入房间回复
    enterRoomListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_ENTER_ROOM_RESP, [=](EventCustom* event){
        removeLoading();
        if (GAMEDATA::getInstance()->getEnterRoomResp().result == "1"){
            Director::getInstance()->replaceScene(TransitionFade::create(1, MjGameScene::create()));
        } else if(GAMEDATA::getInstance()->getEnterRoomResp().result == "2"){
            
            for(auto var : GAMEDATA::getInstance()->getRoomList().rooms){
                if(GAMEDATA::getInstance()->getCurrentSelectRoomId() == var.roomId){
                    GoldNotEnoughDialog* gold = GoldNotEnoughDialog::create(GAMEDATA::getInstance()->getCurrentSelectRoomId());
                    addChild(gold,4);
                }
            }
        }
        else if(GAMEDATA::getInstance()->getEnterRoomResp().result == "3"){
            if(atoi(GAMEDATA::getInstance()->getEnterRoomResp().rsid.c_str()) == ROOM_2){
                EnterRoomDialog* dia = EnterRoomDialog::create(EnterRoomDialogType::goldMoreLeve1);
                addChild(dia,4);
            }else if(atoi(GAMEDATA::getInstance()->getEnterRoomResp().rsid.c_str()) == ROOM_3){
                EnterRoomDialog* dia = EnterRoomDialog::create(EnterRoomDialogType::goldMoreLeve2);
                addChild(dia,4);
            }
        }else if(GAMEDATA::getInstance()->getEnterRoomResp().result == "5"){
            GoldRelieve* goldRelieve = GoldRelieve::create();
            goldRelieve->setRelieveNum(atoi(GAMEDATA::getInstance()->getEnterRoomResp().jjj_count.c_str())-atoi(GAMEDATA::getInstance()->getEnterRoomResp().jjj_used.c_str()));
            addChild(goldRelieve,3);
        }
    });
    
    //进入好友房间回复
    enterFriendRoomListener=  Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_ENTER_FRIEND_ROOM_RESP, [=](EventCustom* event){
        char* buf = static_cast<char*>(event->getUserData());
        std::string result = buf;
        removeLoading();
        if (result == "1"){
            GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
            Director::getInstance()->replaceScene(TransitionFade::create(1, MjGameScene::create()));
        } else if(result == "2")
        {
            HintDialog* invite = HintDialog::create("房间已经坐满",NULL);
            addChild(invite,4);
        }
        else if(result == "3")
        {
            DiamondNotEnoughDialog* dialog = DiamondNotEnoughDialog::create();
            addChild(dialog,4);        }
    });
    
    
    //好友开房
    openFriendRoomListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_FRIEND_OPEN_ROOM_RESP, [=](EventCustom* event){
        GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
        FriendOpenRoomRespData resp = GAMEDATA::getInstance()->getFriendOpenRoomResp();
        if(resp.result == 1){
            Director::getInstance()->replaceScene(TransitionFade::create(1, MjGameScene::create()));
        }else if(resp.result == 2){
            DiamondNotEnoughDialog* dialog = DiamondNotEnoughDialog::create();
            addChild(dialog,4);
        }
        
    });
    
    
    //好友开房通知
    friendInviteListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_FRIEND_OPEN_ROOM_NOTIFY, [=](EventCustom* event){
        FriendOpenRoomNotifyData data = GAMEDATA::getInstance()->getFriendOpenRoomNotify();
        HintDialog* invite = HintDialog::create("好友"+data.nickname+"邀请你一起打牌",[=](Ref* ref){
            FriendOpenRoomNotifyData data = GAMEDATA::getInstance()->getFriendOpenRoomNotify();
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getEnterFriendRoomCommand(data.pid));
            auto item = (MenuItemImage*)ref;
            item->getParent()->getParent()->removeFromParent();
        });
        addChild(invite,4);
    });
    
    
    //刷新自己的信息
    updateHeroInfoListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_UPDATE_HERO_INFO, [=](EventCustom* event){
        updateHeroInfo();
    });
    
    
    //断线续玩
    lobbyConncetAgainListener=  Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_PLAYER_CONNECT_AGAIN, [=](EventCustom* event){
        GAMEDATA::getInstance()->setIsRecover(true);
        Director::getInstance()->replaceScene(MjGameScene::create());
    });
    
    
    //救济经领取
    jjjPrideListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_PLAYER_WELFARE_JJJ, [=](EventCustom* event){
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(GET_JJJ_RESPONSE_REMOVE_LOADING);
        WelfareGold gold = GAMEDATA::getInstance()->getWelfareGold();
        if(gold.result == "1"){
            ParticleUtil* util = ParticleUtil::create(MyParticleType::goldOnly);
            addChild(util,5);
            UserData::getInstance()->setGold(UserData::getInstance()->getGold()+atoi(gold.gold.c_str()));
            updateHeroInfo();
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(UPDATE_JJJ_COUNT_RESP);
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getWelfareCommand());//福利
        }else {
            HintDialog* hint = HintDialog::create("救济金领取失败",NULL);
            addChild(hint,5);
        }
    });
    
    //绑钻救济金领取
    bzjjjPrideListener =  Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_PLAYER_WELFARE_BZJJJ, [=](EventCustom* event){
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(GET_JJJ_RESPONSE_REMOVE_LOADING);
        WelfareBZ gold = GAMEDATA::getInstance()->getWelfareBZ();
        if(gold.result == "1"){
            ParticleUtil* util = ParticleUtil::create(MyParticleType::diamondOnly);
            addChild(util,5);
            UserData::getInstance()->setLockDiamond(UserData::getInstance()->getLockDiamond()+atoi(gold.bangzuan.c_str()));
            updateHeroInfo();
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getWelfareCommand());//福利
        }else {
            HintDialog* hint = HintDialog::create("绑钻救济金领取失败",NULL);
            addChild(hint,5);
        }
    });
    
    //网络连接
    intnetListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(CLIENT_LOST_CONNECT, [=](EventCustom* event){
        Director ::getInstance ()-> getScheduler()-> performFunctionInCocosThread ([&,this]{
            HintDialog* hint = HintDialog::create("网络出现问题啦",NULL);
            addChild(hint,5);
            Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(CLIENT_LOST_CONNECT);
        });
    });
    
    //登录地址变更
    loginReplaceListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_PLAYER_REPLACE_LOGIN, [=](EventCustom* event){
        HintDialog* hin = HintDialog::create("你的账号在其他客户端登录",[=](Ref* ref){
            exit(0);
        });
        addChild(hin,5);
    });
    
    //好友邀请回复
    inviteReplaceListener =  Director::getInstance()->getEventDispatcher()->addCustomEventListener(FRIEND_IS_PLAYING_GAME, [=](EventCustom* event){
        InviteRespData inv = GAMEDATA::getInstance()->getInviteRespData();
        if(inv.result == "1"){
            HintDialog* hin = HintDialog::create(StringUtils::format("你的好友%s不在线",inv.nickname.c_str()),NULL);
            addChild(hin,5);
        }else if(inv.result == "2"){
            HintDialog* hin = HintDialog::create(StringUtils::format("你的好友%s正在游戏",inv.nickname.c_str()),NULL);
            addChild(hin,5);
        }
        
    });
    
    
    friendChatListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_PLAYER_CHAT_NOTIFY, [=](EventCustom* event){
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MSG_PLAYER_ROOM_CHAT_SHOW);
    });
    
    payDialogListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener("mahjong_start_pay", [=](EventCustom* event){
        Loading* loa = Loading::create();
        loa->setTag(4843);
        addChild(loa,20);
    });

    payResultListener  = Director::getInstance()->getEventDispatcher()->addCustomEventListener("mahjong_pay_result", [=](EventCustom* event){
        if(NULL != getChildByTag(4843)){
            getChildByTag(4843)->removeFromParent();
        }
        std::string result = static_cast<char*>(event->getUserData());
        ShopHintDialog* da = ShopHintDialog::create();
        if(result == "1"){
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getPlayerInfoCommand());
            da->showText("充值成功");
        }else{
            da->showText("充值失败");
        }
        addChild(da,20);
    });

    
    //点击事件
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




