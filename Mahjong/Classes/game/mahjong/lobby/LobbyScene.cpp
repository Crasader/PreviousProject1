#include "game/mahjong/lobby/LobbyScene.h"
#include "game/mahjong/bill/BillInfo.h"
#include "game/mahjong/dialog/prompt/HintDialog.hpp"
#include "game/mahjong/daily/DailyEvent.h"
#include "game/mahjong/lobby/EnterRoomDialog.hpp"
#include "game/mahjong/heroinfo/HeroInfoEdit.h"
#include "game/mahjong/activities/MahjongActivities.hpp"
#include "game/mahjong/shop/FirstChageDialog.hpp"
#include "game/mahjong/shop/ChargeGold.hpp"
#include "game/mahjong/shop/ChargeDiamond.hpp"
#include "game/mahjong/shop/LequanShop.hpp"
#include "game/mahjong/shop/GoldNotEnoughDialog.hpp"
#include "game/mahjong/shop/DiamondNotEnoughDialog.hpp"
#include "game/mahjong/shop/relieve/GoldRelieve.hpp"
#include "game/mahjong/share/HongbaoPride.hpp"
#include "game/mahjong/shop/ShopHintDialog.hpp"
#include "game/mahjong/widget/HeadImage.hpp"
#include "game/mahjong/friend/MahjongNumberKeypads.hpp"
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
    Director::getInstance()->getEventDispatcher()->removeEventListener(imageUpdateListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(firstChargeListenr);
    
}

void LobbyScene::signUpdate(float dt){
    
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

//刷新显示的用户信息
void LobbyScene::updateHeroInfo(){
    ((HeadImage*)getChildByTag(962))->updateImage();
    nickName->setString(UserData::getInstance()->getNickName());
    goldNum ->setString(StringUtils::format("%d", UserData::getInstance()->getGold()));
    fangkaNum->setString(StringUtils::format("%d", UserData::getInstance()->getDiamond()));
    lequanNum->setString(StringUtils::format("%d", UserData::getInstance()->getTicket()));
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
    addChild(topbg);
    
    auto head_bg = Sprite::create("mjlobby/head_image_bg.png");
    head_bg->setPosition(61, 660);
    addChild(head_bg);
    
    auto image = HeadImage::create(Size(90,90));
    image->setTag(962);
    image->setPosition(61, 660);
    addChild(image);
    
    auto head = MenuItem::create(CC_CALLBACK_0(LobbyScene::showHeroInfo, this));
    head->setContentSize(Size(90,90));
    auto headmenu = Menu::create(head, NULL);
    headmenu->setPosition(61, 660);
    addChild(headmenu);
    
    nickName = Label::createWithSystemFont(UserData::getInstance()->getNickName(), "arial", 20);
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
    goldNum = LabelAtlas::create(StringUtils::format("%d", UserData::getInstance()->getGold()),
                                 "mjlobby/room_info_num.png", 10, 15, '0');
    goldNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
    goldNum->setPosition(212, 685);
    addChild(goldNum);
    auto gold_btn = MenuItemImage::create("mjlobby/plus_btn_1.png", "mjlobby/plus_btn_2.png", CC_CALLBACK_0(LobbyScene::chargeGold, this));
    auto chargGold = Menu::create(gold_btn, NULL);
    chargGold->setPosition(274, 685);
    addChild(chargGold);
    
    //fangka
    auto fangka_bg = Sprite::create("mjlobby/room_info_bg.png");
    fangka_bg->setPosition(390, 685);
    addChild(fangka_bg);
    auto fangka_icon = Sprite::create("mjitem/fangka_icon.png");
    fangka_icon->setPosition(335, 680);
    addChild(fangka_icon);
    fangkaNum = LabelAtlas::create(StringUtils::format("%d", UserData::getInstance()->getDiamond()),
                                    "mjlobby/room_info_num.png", 10, 15, '0');
    fangkaNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
    fangkaNum->setPosition(392, 685);
    addChild(fangkaNum);
    auto diamond_btn = MenuItemImage::create("mjlobby/charge_btn_1.png", "mjlobby/charge_btn_2.png", CC_CALLBACK_0(LobbyScene::chargeDiamond, this));
    auto chargDiamond = Menu::create(diamond_btn, NULL);
    chargDiamond->setPosition(457, 682);
    addChild(chargDiamond);
    
    //lequan
    auto lequan_bg = Sprite::create("mjlobby/room_info_bg.png");
    lequan_bg->setPosition(580, 685);
    this->addChild(lequan_bg);
    auto lequan_icon = Sprite::create("mjlobby/lequan_icon.png");
    lequan_icon->setPosition(522, 685);
    this->addChild(lequan_icon);
    lequanNum = LabelAtlas::create(StringUtils::format("%d", UserData::getInstance()->getTicket()),
                                   "mjlobby/room_info_num.png", 10, 15, '0');
    lequanNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
    lequanNum->setPosition(582, 685);
    this->addChild(lequanNum);
    auto lequan_btn = MenuItemImage::create("mjlobby/plus_btn_1.png", "mjlobby/plus_btn_2.png", CC_CALLBACK_0(LobbyScene::exchangeLequan, this));
    auto chargLequan = Menu::create(lequan_btn, NULL);
    chargLequan->setPosition(646, 685);
    addChild(chargLequan);
}

void LobbyScene::drawSceneMid(){
    auto gameTitle = Sprite::create("mjlobby/game_icon.png");
    gameTitle->setPosition(1070, 640);
    this->addChild(gameTitle);
    
    auto red_wallet = MenuItemImage::create("mjlobby/red_wallet_1.png", "mjlobby/red_wallet_2.png",
                                            CC_CALLBACK_0(LobbyScene::showRedWallet, this));
    first_chaege = MenuItemImage::create("mjlobby/first_charge_btn_1.png", "mjlobby/first_charge_btn_2.png",
                                         CC_CALLBACK_0(LobbyScene::showFirstCharge, this));
    if(UserData::getInstance()->isFirstCharge()){
        first_chaege->setVisible(false);
    }
    auto giftMenu = Menu::create(red_wallet, first_chaege, NULL);
    giftMenu->setTag(1313);
    giftMenu->alignItemsHorizontallyWithPadding(10);
    giftMenu->setPosition(120, 542);
    addChild(giftMenu);
    //房间按钮
    auto openRoom = Sprite::create("mjlobby/open_room_image.png");
    openRoom->setPosition(390,400);
    addChild(openRoom);
    auto joinRooom = Sprite::create("mjlobby/join_room_image.png");
    joinRooom->setPosition(880,400);
    addChild(joinRooom);
    auto openBtn = MenuItemImage::create("mjlobby/open_room_btn_img_1.png", "mjlobby/open_room_btn_img_2.png", CC_CALLBACK_0(LobbyScene::openRoom, this));
    auto joinBtn = MenuItemImage::create("mjlobby/join_room_btn_img_1.png", "mjlobby/join_room_btn_img_2.png", CC_CALLBACK_0(LobbyScene::joinRoom, this));
    auto roomMenu = Menu::create(openBtn,joinBtn,NULL);
    roomMenu->alignItemsHorizontallyWithPadding(180);
    roomMenu->setPosition(640,230);
    addChild(roomMenu);
    
}

void LobbyScene::drawSceneBot(){
    auto bot_bg = Sprite::create("mjlobby/lobby_bottom_bg.png");
    bot_bg->setPosition(955,48);
    addChild(bot_bg);
    
//    auto btn_2 = MenuItemImage::create("mjlobby/bill_btn_1.png", "mjlobby/bill_btn_2.png", CC_CALLBACK_0(LobbyScene::showPlayerBill, this));
    auto btn_3 = MenuItemImage::create("mjlobby/task_btn_1.png", "mjlobby/task_btn_2.png", CC_CALLBACK_0(LobbyScene::showDayTask, this));
     auto btn_4 = MenuItemImage::create("mjlobby/activity_btn_1.png", "mjlobby/activity_btn_2.png", CC_CALLBACK_0(LobbyScene::showHotActivity, this));
    auto btn_5 = MenuItemImage::create("mjlobby/setting_btn_1.png", "mjlobby/setting_btn_2.png", CC_CALLBACK_0(LobbyScene::showGameSetting, this));
    auto gameMenu = Menu::create(btn_3,btn_4, btn_5, NULL);
    gameMenu->alignItemsHorizontallyWithPadding(80);
    gameMenu->setPosition(900, 43);
    addChild(gameMenu);
    auto openRoom = MenuItemImage::create("mjlobby/gold_room_btn_1.png", "mjlobby/gold_room_btn_2.png", CC_CALLBACK_0(LobbyScene::showGoldRoomPad, this));
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
    HongbaoPride* wallet = HongbaoPride::create();
    addChild(wallet,3);
}

void LobbyScene::showDayTask(){
    Audio::getInstance()->playSoundClick();
    DailyEvent* day = DailyEvent::create();
    day->showDailyEvent(DailyType::pride);
    addChild(day,3);
}


void LobbyScene::showAddFriend(){
    Audio::getInstance()->playSoundClick();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getFriendListCommand());
    FriendListView* friendAdd = FriendListView::create();
    friendAdd->setTag(524);
    addChild(friendAdd,3);
    
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
    
    //logo光效
    auto logoLight = Sprite::create();
    logoLight->setPosition(1070, 645);
    addChild(logoLight);
    auto animation = Animation::create();
    for( int i=1;i<4;i++)
    {
        std::string imageName = StringUtils::format("mjlobby/lobby_logo_light_%d.png",i);
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
        std::string imageName = StringUtils::format("mjlobby/lobby_logo_text_%d.png",j);
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
        else if(result == "4"){
            HintDialog* invite = HintDialog::create("房间号错误",NULL);
            addChild(invite,4);
        }
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
    
    //刷新头像
    imageUpdateListener  = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_UPDATE_PLAYER_WECHAT_IMAGE, [=](EventCustom* event){
        if(NULL != getChildByTag(962))
            ((HeadImage*)getChildByTag(962))->updateImage();
    });
    
    firstChargeListenr =  Director::getInstance()->getEventDispatcher()->addCustomEventListener("hide_first_charge_btn", [=](EventCustom* event){
        first_chaege->setVisible(false);
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

void LobbyScene:: openRoom(){
    //TODO
}


void LobbyScene::joinRoom(){
    MahjongNumberKeypads* keypads = MahjongNumberKeypads::create();
    addChild(keypads);
}


void LobbyScene::showGoldRoomPad(){

}




