#include "game/mahjong/lobby/LobbyScene.h"
#include "game/mahjong/lobby/GoldRoomPlate.hpp"
#include "game/mahjong/lobby/EnterRoomDialog.hpp"
#include "game/mahjong/heroinfo/HeroInfoEdit.h"
#include "game/mahjong/bill/BillInfo.h"
#include "game/mahjong/dialog/prompt/HintDialog.hpp"
#include "game/mahjong/dialog/prompt/TextHintDialog.hpp"
#include "game/mahjong/daily/DailyEvent.h"
#include "game/mahjong/shop/FirstChageDialog.hpp"
#include "game/mahjong/shop/gold/ChargeGold.hpp"
#include "game/mahjong/shop/fangka/ChargeFangka.hpp"
#include "game/mahjong/shop/fangka/FangkaNotEnoughDialog.hpp"
#include "game/mahjong/shop/mall/LequanShop.hpp"
#include "game/mahjong/shop/gold/GoldNotEnoughDialog.hpp"
#include "game/mahjong/share/HongbaoPride.hpp"
#include "game/mahjong/shop/ShopHintDialog.hpp"
#include "game/mahjong/widget/HeadImage.hpp"
#include "game/mahjong/friend/MahjongNumberKeypads.hpp"
#include "game/mahjong/friend/dialog/RoomIdErrorDialog.hpp"
#include "game/mahjong/wanjiaqun/WanJiaQunLayer.hpp"
#include "game/mahjong/friend/dialog/RoomFullDialog.hpp"
#include "game/mahjong/widget/ScrollTextEx.h"
#include "game/mahjong/friend/FriendRoom.h"
#include "payment/android/CallAndroidMethod.h"
#include "game/utils/ParticleUtil.hpp"
#include "game/utils/GameConfig.h"
#include "game/utils/Audio.h"
#include "http/image/UrlImageMannger.h"



bool LobbyScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    isButtonCilckable = true;
    clickTime =0;
    initView();
    //add sprite to scene
    drawSceneTop();
    drawSceneMid();
    drawSceneBot();
    showLobbyAnim();
    return true;
}

bool LobbyScene::checkCilckabale(){
    return isButtonCilckable;
}

void LobbyScene::signUpdate(float dt){
    
    clickTime += dt;
    if(clickTime>3){
        isButtonCilckable = true;
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
        FangkaNotEnoughDialog* charge = FangkaNotEnoughDialog::create();
        addChild(charge,30);
        GAMEDATA::getInstance()->setShowDialogType(-1);
    }
}

//刷新显示的用户信息
void LobbyScene::updateHeroInfo(){
    ((HeadImage*)getChildByTag(962))->updateImage();
    nickName->setString(UserData::getInstance()->getNickName());
    goldNum ->setString(StringUtils::format("%d", UserData::getInstance()->getGold()));
    fangkaNum->setString(StringUtils::format("%d", UserData::getInstance()->getFangkaNum()));
    lequanNum->setString(StringUtils::format("%d", UserData::getInstance()->getTicket()));
}

void LobbyScene::initView(){
    //add game bg to layer
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Sprite* lobby_bg = Sprite::create("mjlobby/lobby_bg.jpg");
    lobby_bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    addChild(lobby_bg, -1);
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
    addChild(nickName);
    
    auto markid = Label::createWithSystemFont(StringUtils::format("ID号:%s",UserData::getInstance()->getMarkId().c_str()), "arial", 20);
    markid->setPosition(225, 628);
    markid->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    markid->setAlignment(TextHAlignment::LEFT);
    addChild(markid);
    
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
    fangkaNum = LabelAtlas::create(StringUtils::format("%d", UserData::getInstance()->getFangkaNum()),
                                   "mjlobby/room_info_num.png", 10, 15, '0');
    fangkaNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
    fangkaNum->setPosition(392, 685);
    addChild(fangkaNum);
    auto diamond_btn = MenuItemImage::create("mjlobby/charge_btn_1.png", "mjlobby/charge_btn_2.png", CC_CALLBACK_0(LobbyScene::chargeFangka, this));
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
    if(atoi(GAMEDATA::getInstance()->getPrivateGameNum().c_str())>0||GAMEDATA::getInstance()->getFangZhuId() == UserData::getInstance()->getPoxiaoId()){
        Sprite* frame = Sprite::create("mjlobby/go_to_friend_room_1.png");
        openBtn->setNormalImage(frame);
        Sprite* frame2 = Sprite::create("mjlobby/go_to_friend_room_2.png");
        openBtn->setSelectedImage(frame2);
    }
    auto joinBtn = MenuItemImage::create("mjlobby/join_room_btn_img_1.png", "mjlobby/join_room_btn_img_2.png", CC_CALLBACK_0(LobbyScene::joinRoom, this));
    auto roomMenu = Menu::create(openBtn,joinBtn,NULL);
    roomMenu->alignItemsHorizontallyWithPadding(180);
    roomMenu->setPosition(640,230);
    addChild(roomMenu);
    
    //跑马灯
    ScrollTextEx* scroll = ScrollTextEx::create();
    scroll->setAutoScroll(true);
    scroll->setTag(9980);
    scroll->setPosition(600,600);
    addChild(scroll,2);
}

void LobbyScene::drawSceneBot(){
    auto bot_bg = Sprite::create("mjlobby/lobby_bottom_bg.png");
    bot_bg->setPosition(955,48);
    addChild(bot_bg);
    
     auto btn_1 = MenuItemImage::create("mjlobby/wan_jia_quan_1.png", "mjlobby/wan_jia_quan_2.png", CC_CALLBACK_0(LobbyScene::showWanJiaQun, this));
    auto btn_2 = MenuItemImage::create("mjlobby/task_btn_1.png", "mjlobby/task_btn_2.png", CC_CALLBACK_0(LobbyScene::showDayTask, this));
    auto btn_3 = MenuItemImage::create("mjlobby/bill_btn_1.png", "mjlobby/bill_btn_2.png", CC_CALLBACK_0(LobbyScene::showPlayerBill, this));
    auto btn_4 = MenuItemImage::create("mjlobby/setting_btn_1.png", "mjlobby/setting_btn_2.png", CC_CALLBACK_0(LobbyScene::showGameSetting, this));
    auto gameMenu = Menu::create(btn_1,btn_2,btn_3, btn_4, NULL);
    gameMenu->alignItemsHorizontallyWithPadding(50);
    gameMenu->setPosition(900, 43);
    addChild(gameMenu);
    auto openRoom = MenuItemImage::create("mjlobby/gold_room_btn_1.png", "mjlobby/gold_room_btn_2.png", CC_CALLBACK_0(LobbyScene::showGoldRoomPad, this));
    auto openMenu = Menu::create(openRoom,NULL);
    openMenu->setPosition(1203,67);
    addChild(openMenu);
    
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

void LobbyScene::showWanJiaQun(){
    WanJiaQunLayer* wanjia = WanJiaQunLayer::create();
    addChild(wanjia,5);
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

void LobbyScene::chargeFangka(){
    Audio::getInstance()->playSoundClick();
    ChargeFangka* charge = ChargeFangka::create();
    addChild(charge,3);
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

void LobbyScene:: openRoom(){
    if(checkCilckabale()){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getOpenRoomRequestCommand());
        isButtonCilckable = false;
        clickTime = 0;
    }
}


void LobbyScene::joinRoom(){
    if(checkCilckabale()){
         NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getEnterRoomRequestCommand());
        isButtonCilckable = false;
        clickTime = 0;
    }
}


void LobbyScene::showGoldRoomPad(){
    GoldRoomPlate* plate = GoldRoomPlate::create();
    addChild(plate,2);
}

void LobbyScene::onEnter(){
    Scene::onEnter();
    addEventListener();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getPlayerInfoCommand());
    GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::publicRoom);
    schedule(schedule_selector(LobbyScene::signUpdate), 0, CC_REPEAT_FOREVER, 0.2f);
    schedule([=](float dt){
        updateHeroInfo();
    }, 1.0, 5, 0,"updatePlayerInfo");
    
}

void LobbyScene::onEnterTransitionDidFinish(){
  NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getScrollTextCommand());
  NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getWanJiaQunCommand());
}

void LobbyScene::onExit(){
    Scene::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(enterRoomListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(enterFriendRoomListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(openFriendRoomListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(friendInviteListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(updateHeroInfoListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(lobbyConncetAgainListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(intnetListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(loginReplaceListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(inviteReplaceListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(payDialogListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(payResultListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(imageUpdateListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(firstChargeListenr);
    Director::getInstance()->getEventDispatcher()->removeEventListener(openRoomAskListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(enterRoomAskListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(scrollTetxListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(wanjiaqunListener);
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
            //金币救济金暂时取消了
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
            RoomFullDialog* doo = RoomFullDialog::create();
            addChild(doo);
        }
        else if(result == "3")
        {
            FangkaNotEnoughDialog* dialog = FangkaNotEnoughDialog::create();
            addChild(dialog,4);        }
        else if(result == "4"){
            RoomIdErrorDialog* idd = RoomIdErrorDialog::create();
            addChild(idd,4);
        }
    });
    
    
    //好友开房
    openFriendRoomListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_FRIEND_OPEN_ROOM_RESP, [=](EventCustom* event){
        GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
        FriendOpenRoomRespData resp = GAMEDATA::getInstance()->getFriendOpenRoomResp();
        if(resp.result == 1){
            GAMEDATA::getInstance()->setFangZhuId(UserData::getInstance()->getPoxiaoId());
            Director::getInstance()->replaceScene(TransitionFade::create(1, MjGameScene::create()));
        }else if(resp.result == 2){
            FangkaNotEnoughDialog* dia =FangkaNotEnoughDialog::create();
            addChild(dia,4);
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
    
    //网络连接
    intnetListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(CLIENT_LOST_CONNECT, [=](EventCustom* event){
        Director ::getInstance ()-> getScheduler()-> performFunctionInCocosThread ([&,this]{
            TextHintDialog* hint = TextHintDialog::create("网络出现问题啦");
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
    
    
    //启动支付
    payDialogListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener("mahjong_start_pay", [=](EventCustom* event){
        Loading* loa = Loading::create();
        loa->setTag(4843);
        addChild(loa,20);
    });
    
    //支付结果
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
    
    //首冲礼包
    firstChargeListenr =  Director::getInstance()->getEventDispatcher()->addCustomEventListener("hide_first_charge_btn", [=](EventCustom* event){
        first_chaege->setVisible(false);
    });
    
    //开房询问
    openRoomAskListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_LOBBY_ASK_OPEN_ROOM, [=](EventCustom* event){
        if(UserData::getInstance()->getFangkaNum()>0){
            FriendRoom* friendroom = FriendRoom::create();
            addChild(friendroom);
        }else{
            ChargeFangka* cha = ChargeFangka::create();
            addChild(cha);
        }
    });
    
    //进入房间询问
    enterRoomAskListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_LOBBY_ASK_ENTER_ROOM, [=](EventCustom* event){
        MahjongNumberKeypads* keypads = MahjongNumberKeypads::create();
        addChild(keypads);
    });
    
    
    scrollTetxListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_SCROLL_TEXT, [=](EventCustom* event){
        std::string msg = static_cast<char*>(event->getUserData());
        if(nullptr != ((ScrollTextEx*)getChildByTag(9980))){
            ((ScrollTextEx*)getChildByTag(9980))->setScrollStr(msg);
        }
    });

    wanjiaqunListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_WAN_JIA_WEI_XIN_QUN, [=](EventCustom* event){
        if(GAMEDATA::getInstance()->getWanJiaQunVer()>UserData::getInstance()->getWanJiaQunVersion()){
            UrlImageMannger::getInstance()->downloadQunImgByUrl(WECHAT_WAN_JIA_QUN_URL);
        }
        if(GAMEDATA::getInstance()->getDailiQunVer()>UserData::getInstance()->getDailiQunVersion()){
             UrlImageMannger::getInstance()->downloadDailiImgByUrl(WECHAT_DAI_LI_QUN_URL);
        }
    });

    
    //点击事件
    auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
        switch (code)
        {
            case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
            {
                HintDialog* hit = HintDialog::create("确定要离开游戏吗？",[=](Ref* ref){
                    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getLobbyQuitCommand());
                    Director::getInstance()->end();
                });
                addChild(hit,100);
                break;
            }
            default:
                break;
        }
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}




