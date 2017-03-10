#include "mahjong/lobby/LobbyScene.h"
#include "mahjong/lobby/goldroom/GoldRoomPlate.hpp"
#include "mahjong/lobby/EnterRoomDialog.hpp"
#include "mahjong/lobby/notice/NoticeDialog.hpp"
#include "mahjong/heroinfo/HeroInfoEdit.h"
#include "mahjong/bill/BillInfo.h"
#include "mahjong/dialog/prompt/HintDialog.hpp"
#include "mahjong/dialog/prompt/TextHintDialog.hpp"
#include "mahjong/daily/DailyEvent.h"
#include "mahjong/shop/FirstChageDialog.hpp"
#include "mahjong/shop/gold/ChargeGold.hpp"
#include "mahjong/shop/fangka/ChargeFangka.hpp"
#include "mahjong/shop/fangka/FangkaNotEnoughDialog.hpp"
#include "mahjong/shop/mall/LequanShop.hpp"
#include "mahjong/shop/gold/GoldNotEnoughDialog.hpp"
#include "mahjong/share/ShareToFriendLayer.hpp"
#include "mahjong/shop/ShopHintDialog.hpp"
#include "mahjong/widget/HeadImage.hpp"
#include "mahjong/friend/MahjongNumberKeypads.hpp"
#include "mahjong/friend/dialog/RoomIdErrorDialog.hpp"
#include "mahjong/wanjiaqun/WanJiaQunLayer.hpp"
#include "mahjong/friend/dialog/RoomFullDialog.hpp"
#include "mahjong/widget/ScrollTextEx.h"
#include "mahjong/friend/FriendRoom.h"
#include "mahjong/audio/Audio.h"
#include "mahjong/GameConfig.h"
#include "mahjong/widget/ParticleUtil.hpp"
#include "payment/android/CallAndroidMethod.h"
#include "http/image/UrlImageMannger.h"
#include "mahjong/dialog/network/LostNetwork2.hpp"
#include "mahjong/gonggao/GameGongGaoLayer.hpp"
#include "mahjong/chat/chatAndroid/ChatAndroidMethod.h"
#include "mahjong/shiming/ShiMingLayer.hpp"

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


void LobbyScene::signUpdate(float dt){
    if(GAMEDATA::getInstance()->getShowProtected()){
        if(NULL == getChildByTag(2000)){
            LostNetwork2* net = LostNetwork2::create();
            net->setTag(2000);
            addChild(net,200);
        }
        GAMEDATA::getInstance()->setShowProtected(false);
    }
    if(GAMEDATA::getInstance()->getWaitNetwork()){
        if(NULL == getChildByTag(2000)){
            LostNetwork2* net = LostNetwork2::create();
            net->setTag(2000);
            addChild(net,200);
        }
        if(NetworkManage::getInstance()->reConnectSocket()){
            int  delayTime = 2.5f;
            schedule([=](float dt){
                if(UserData::getInstance()->getWxOpenId() ==  "unknow"){
                    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getVistorLoginAgain(UserData::getInstance()->getUserName(), UserData::getInstance()->getPassword()));
                }else{
                    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getThirdLoginCommand(UserData::getInstance()->getWxOpenId(), UserData::getInstance()->getWxUnionid(),UserData::getInstance()->getPicture(), StringUtils::format("%d",UserData::getInstance()->getGender()), UserData::getInstance()->getNickName(), GAMEDATA::getInstance()->getHsman(), GAMEDATA::getInstance()->getHstype(), GAMEDATA::getInstance()->getImsi(),GAMEDATA::getInstance()->getImei(),GAMEDATA::getInstance()->getAppVer(),true));
                }
            }, 0, 0, delayTime, "socket_reconnect2000");
            NetworkManage::getInstance()->startSocketBeat(CommandManage::getInstance()->getHeartCommmand());
        }else{
            HintDialog* dia = HintDialog::create("无法连接网络,请检查当前网络环境", NULL);
            addChild(dia,1000);
        }
        GAMEDATA::getInstance()->setWaitNetwork(false);
    }
    
    if(GAMEDATA::getInstance()->getShowDialogType() == 2){
                for(auto var : GAMEDATA::getInstance()->getRoomList().rooms){
                    if(GAMEDATA::getInstance()->getCurrentSelectRoomId() == var.roomId){
        #if(CC_TARGET_PLATFORM ==  CC_PLATFORM_ANDROID)
                        if(UserData::getInstance()->isWeixinPayOpen()){
                            GoldNotEnoughDialog* gold = GoldNotEnoughDialog::create(GAMEDATA::getInstance()->getEnterRoomResp(),GAMEDATA::getInstance()->getCurrentSelectRoomId());
                            addChild(gold,30);
                        }else{
                            HintDialog* hint = HintDialog::create("游戏金币不足",NULL);
                            addChild(hint,100);
                        }
        #elif(CC_TARGET_PLATFORM ==  CC_PLATFORM_IOS)
                        GoldNotEnoughDialog* gold = GoldNotEnoughDialog::create(GAMEDATA::getInstance()->getEnterRoomResp(),GAMEDATA::getInstance()->getCurrentSelectRoomId());
                        addChild(gold,30);
        #endif
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
#if(CC_TARGET_PLATFORM ==  CC_PLATFORM_ANDROID)
        if(UserData::getInstance()->isWeixinPayOpen()){
            FangkaNotEnoughDialog* charge = FangkaNotEnoughDialog::create();
            addChild(charge,30);
            GAMEDATA::getInstance()->setShowDialogType(-1);
        }else{
            HintDialog* hint = HintDialog::create("房卡有一定几率在游戏中掉落",NULL);
            addChild(hint,30);
        }
#elif(CC_TARGET_PLATFORM ==  CC_PLATFORM_IOS)
        FangkaNotEnoughDialog* charge = FangkaNotEnoughDialog::create();
        addChild(charge,30);
        GAMEDATA::getInstance()->setShowDialogType(-1);
#endif
    }
}



void LobbyScene::initView(){
    //add game bg to layer
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Sprite* lobby_bg = Sprite::create("mjlobby/lobby_bg.jpg");
    lobby_bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    addChild(lobby_bg, -1);
    if(getChildByTag(2000)!=NULL){
        getChildByTag(2000)->removeFromParent();
    }
    GAMEDATA::getInstance()->setLogingGame(true);
}



//draw scene top view
void LobbyScene::drawSceneTop(){
    auto topbg = Sprite::create("mjlobby/lobby_top_bg.png");
    topbg->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    topbg->setPosition(0, 680);
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
    
    nickName = Label::createWithSystemFont(UserData::getInstance()->getNickName(), "arial", 24);
    nickName->setPosition(125, 628);
    nickName->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    nickName->setAlignment(TextHAlignment::LEFT);
    addChild(nickName);
    
    auto markid = Label::createWithSystemFont(StringUtils::format("ID号:%s",UserData::getInstance()->getMarkId().c_str()), "arial", 24);
    markid->setPosition(nickName->getPositionX()+nickName->getContentSize().width+30, 628);
    markid->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    markid->setAlignment(TextHAlignment::LEFT);
    addChild(markid);
    
    //fangka
    auto fangka_bg = Sprite::create("mjlobby/room_info_bg.png");
    fangka_bg->setPosition(235, 685);
    addChild(fangka_bg);
    auto fangka_icon = Sprite::create("mjitem/fangka_icon.png");
    fangka_icon->setPosition(157, 680);
    addChild(fangka_icon);
    fangkaNum = Label::createWithSystemFont(StringUtils::format("%0.1f",UserData::getInstance()->getFangkaNum()),"Arial",24);
    fangkaNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
    fangkaNum->setColor(Color3B(242,227,75));
    fangkaNum->setPosition(232, 685);
    addChild(fangkaNum);
    auto diamond_btn = MenuItemImage::create("mjlobby/charge_btn_1.png", "mjlobby/charge_btn_2.png", CC_CALLBACK_0(LobbyScene::chargeFangka, this));
    auto chargDiamond = Menu::create(diamond_btn, NULL);
    chargDiamond->setPosition(315, 682);
    addChild(chargDiamond);
    
    
    //gold
    auto gold_bg = Sprite::create("mjlobby/room_info_bg.png");
    gold_bg->setPosition(462, 685);
    gold_bg->setTag(801);
    addChild(gold_bg);
    auto gold_icon = Sprite::create("mjlobby/gold_icon.png");
    gold_icon->setPosition(380, 685);
    gold_icon->setTag(802);
    addChild(gold_icon);
    goldNum = Label::createWithSystemFont(StringUtils::format("%d",UserData::getInstance()->getGold()),"Arial",24);
    goldNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
    goldNum->setColor(Color3B(242,227,75));
    goldNum->setPosition(462, 685);
    addChild(goldNum);
    auto gold_btn = MenuItemImage::create("mjlobby/plus_btn_1.png", "mjlobby/plus_btn_2.png", CC_CALLBACK_0(LobbyScene::chargeGold, this));
    auto chargGold = Menu::create(gold_btn, NULL);
    chargGold->setPosition(543, 685);
    chargGold->setTag(803);
    addChild(chargGold);

    
    
    //lequan
    auto lequan_bg = Sprite::create("mjlobby/room_info_bg.png");
    lequan_bg->setTag(901);
    lequan_bg->setPosition(690, 685);
    addChild(lequan_bg);
    auto lequan_icon = Sprite::create("mjlobby/lequan_icon.png");
    lequan_icon->setTag(902);
    lequan_icon->setPosition(610, 685);
    addChild(lequan_icon);
    lequanNum = Label::createWithSystemFont(StringUtils::format("%d", UserData::getInstance()->getTicket()),
                                            "Arial",24);
    lequanNum->setColor(Color3B(242,227,75));
    lequanNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
    lequanNum->setPosition(690, 685);
    addChild(lequanNum);
    
    auto lequan_btn = MenuItemImage::create("mjlobby/plus_btn_1.png", "mjlobby/plus_btn_2.png", CC_CALLBACK_0(LobbyScene::exchangeLequan, this));
    auto chargLequan = Menu::create(lequan_btn, NULL);
    chargLequan->setTag(903);
    chargLequan->setPosition(770, 685);
    addChild(chargLequan);

    //支付审核专用
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    gold_bg->setVisible(UserData::getInstance()->isWeixinPayOpen());
    gold_icon->setVisible(UserData::getInstance()->isWeixinPayOpen());
    goldNum->setVisible(UserData::getInstance()->isWeixinPayOpen());
    chargGold->setVisible(UserData::getInstance()->isWeixinPayOpen());
#endif
    lequan_bg->setVisible(UserData::getInstance()->isWeixinPayOpen());
    lequan_icon->setVisible(UserData::getInstance()->isWeixinPayOpen());
    lequanNum->setVisible(UserData::getInstance()->isWeixinPayOpen());
    chargLequan->setVisible(UserData::getInstance()->isWeixinPayOpen());
    
}

void LobbyScene::drawSceneMid(){
    auto gameTitle = Sprite::create("mjlobby/game_icon.png");
    gameTitle->setPosition(1070, 640);
    this->addChild(gameTitle);
    
    auto sharefriend = MenuItemImage::create("mjlobby/red_wallet_1.png", "mjlobby/red_wallet_2.png",
                                             CC_CALLBACK_0(LobbyScene::showRedWallet, this));
    auto shareMenu = Menu::create(sharefriend, NULL);
    shareMenu->alignItemsHorizontallyWithPadding(15);
    shareMenu->setPosition(90, 552);
    addChild(shareMenu);
    
    auto first_chaege = MenuItemImage::create("mjlobby/first_charge_btn_1.png", "mjlobby/first_charge_btn_2.png",
                                              CC_CALLBACK_0(LobbyScene::showFirstCharge, this));
    
    firstMenu = Menu::create(first_chaege, NULL);
    firstMenu->alignItemsHorizontallyWithPadding(15);
    firstMenu->setPosition(200, 552);
    addChild(firstMenu);
    firstMenu->runAction(Repeat::create(Sequence::create(MoveTo::create(0.6f,Point(200, 562)),MoveTo::create(0.6f,Point(200, 542)),NULL), CC_REPEAT_FOREVER));
    //感叹号
    ganTanhao = Sprite::create("mjlobby/gantanhao.png");
    ganTanhao->setPosition(230,575);
    addChild(ganTanhao);
    ganTanhao->runAction(Repeat::create(Sequence::create(MoveTo::create(0.6f,Point(230, 590)),MoveTo::create(0.6f,Point(230, 570)),NULL), CC_REPEAT_FOREVER));
    if(UserData::getInstance()->isFirstCharge()){
        firstMenu->setVisible(false);
        ganTanhao->setVisible(false);
    }
    //房间按钮
    auto openRoom = MenuItemImage::create("mjlobby/open_room_image.png","mjlobby/open_room_image.png",CC_CALLBACK_0(LobbyScene::openRoom, this));
    auto opmneu = Menu::create(openRoom,NULL);
    opmneu->setPosition(260,360);
    addChild(opmneu);
    auto joinRooom = MenuItemImage::create("mjlobby/join_room_image.png","mjlobby/join_room_image.png",CC_CALLBACK_0(LobbyScene::joinRoom, this));
    auto joimenu = Menu::create(joinRooom,NULL);
    joimenu->setPosition(700,360);
    addChild(joimenu);
    auto openBtn = MenuItemImage::create("mjlobby/open_room_btn_img_1.png", "mjlobby/open_room_btn_img_2.png", CC_CALLBACK_0(LobbyScene::openRoom, this));
    if(atoi(GAMEDATA::getInstance()->getPrivateGameNum().c_str())>0||GAMEDATA::getInstance()->getFangZhuId() == UserData::getInstance()->getPoxiaoId()){
        Sprite* frame = Sprite::create("mjlobby/go_to_friend_room_1.png");
        openBtn->setNormalImage(frame);
        Sprite* frame2 = Sprite::create("mjlobby/go_to_friend_room_2.png");
        openBtn->setSelectedImage(frame2);
    }
    auto joinBtn = MenuItemImage::create("mjlobby/join_room_btn_img_1.png", "mjlobby/join_room_btn_img_2.png", CC_CALLBACK_0(LobbyScene::joinRoom, this));
    auto roomMenu = Menu::create(openBtn,joinBtn,NULL);
    roomMenu->alignItemsHorizontallyWithPadding(130);
    roomMenu->setPosition(485,190);
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
    
    auto btn_0 = MenuItemImage::create("mjlobby/sm_btn_1.png", "mjlobby/sm_btn_2.png", CC_CALLBACK_0(LobbyScene::showShiMing, this));
    auto btn_1 = MenuItemImage::create("mjlobby/wan_jia_quan_1.png", "mjlobby/wan_jia_quan_2.png", CC_CALLBACK_0(LobbyScene::showWanJiaQun, this));
    auto btn_2 = MenuItemImage::create("mjlobby/task_btn_1.png", "mjlobby/task_btn_2.png", CC_CALLBACK_0(LobbyScene::showDayTask, this));
    auto btn_3 = MenuItemImage::create("mjlobby/bill_btn_1.png", "mjlobby/bill_btn_2.png", CC_CALLBACK_0(LobbyScene::showPlayerBill, this));
    auto btn_4 = MenuItemImage::create("mjlobby/setting_btn_1.png", "mjlobby/setting_btn_2.png", CC_CALLBACK_0(LobbyScene::showGameSetting, this));
    auto gameMenu = Menu::create(btn_0,btn_1,btn_2,btn_3, btn_4, NULL);
    gameMenu->alignItemsHorizontallyWithPadding(45);
    gameMenu->setPosition(870, 43);
    addChild(gameMenu);
    auto openRoom = MenuItemImage::create("mjlobby/gold_room_btn_1.png", "mjlobby/gold_room_btn_2.png", CC_CALLBACK_0(LobbyScene::showGoldRoomPad, this));
    auto openMenu = Menu::create(openRoom,NULL);
    openMenu->setPosition(1203,67);
    openMenu->setTag(6656);
    addChild(openMenu);
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    //支付审核
    openMenu->setVisible(UserData::getInstance()->isWeixinPayOpen());
#endif
}

//刷新显示的用户信息
void LobbyScene::updateHeroInfo(){
    ((HeadImage*)getChildByTag(962))->updateImage();
    nickName->setString(UserData::getInstance()->getNickName());
    goldNum ->setString(StringUtils::format("%d", UserData::getInstance()->getGold()));
    fangkaNum->setString(StringUtils::format("%0.1f", UserData::getInstance()->getFangkaNum()));
    if(NULL != lequanNum)
        lequanNum->setString(StringUtils::format("%d", UserData::getInstance()->getTicket()));
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
    //首冲
    FirstChargeDialog* firCharge = FirstChargeDialog::create();
    addChild(firCharge,3);
}

void LobbyScene::showRedWallet(){
    Audio::getInstance()->playSoundClick();
    ShareToFriendLayer* wallet = ShareToFriendLayer::create();
    addChild(wallet,3);
}

void LobbyScene::showWanJiaQun(){
    Audio::getInstance()->playSoundClick();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getGongGaoCommand());
    Loading* load = Loading::create();
    load->setTag(1209);
    addChild(load,5);
}

void LobbyScene::showDayTask(){
    Audio::getInstance()->playSoundClick();
    DailyEvent* day = DailyEvent::create();
    day->showDailyEvent(DailyType::pride);
    addChild(day,3);
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
#if(CC_TARGET_PLATFORM ==  CC_PLATFORM_ANDROID)
    if(UserData::getInstance()->isWeixinPayOpen()){
        ChargeFangka* charge = ChargeFangka::create();
        addChild(charge,3);
    }else{
        HintDialog* hint = HintDialog::create("房卡有一定几率在游戏中掉落",NULL);
        addChild(hint,3);
    }
#elif(CC_TARGET_PLATFORM ==  CC_PLATFORM_IOS)
    ChargeFangka* charge = ChargeFangka::create();
    addChild(charge,3);
#endif
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
    addChild(loadLayer,3);
}

void LobbyScene::showShiMing(){
    
    if(GAMEDATA::getInstance()->getCertification()){
        HintDialog* hd = HintDialog::create("你已经完成实名认证", nullptr);
        addChild(hd,5);
    }else{
        ShiMingLayer* shim = ShiMingLayer::create();
        addChild(shim,5);
    }
}

void LobbyScene::removeLoading(){
    if(NULL != getChildByTag(1000)){
        getChildByTag(1000)->removeFromParent();
    }
}

void LobbyScene:: openRoom(){
    EventCustom imageEvent(MSG_LOBBY_SHOW_LOADING_LAYER);
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&imageEvent);
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getOpenRoomRequestCommand());
    
}


void LobbyScene::joinRoom(){
    EventCustom imageEvent(MSG_LOBBY_SHOW_LOADING_LAYER);
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&imageEvent);
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getEnterRoomRequestCommand());
}


void LobbyScene::showGoldRoomPad(){
    if(NULL != getChildByTag(1298)){
        getChildByTag(1298)->setVisible(!getChildByTag(1298)->isVisible());
    }
}

void LobbyScene::onEnter(){
    Scene::onEnter();
    addEventListener();
    GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::publicRoom);
    schedule(schedule_selector(LobbyScene::signUpdate), 0, CC_REPEAT_FOREVER, 0.2f);
    schedule([=](float dt){
        updateHeroInfo();
    }, 0.4f, CC_REPEAT_FOREVER, 0,"updatePlayerInfo");
    
}

void LobbyScene::onEnterTransitionDidFinish(){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getRoomListCommand("1"));
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getPlayerInfoCommand());
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getScrollTextCommand());
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getNoticeCommand());
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getGamePayType());
    if(GAMEDATA::getInstance()->getShowFangZhuDismiss()){
        HintDialog* hint  = HintDialog::create("房主已经解散了房间", nullptr);
        addChild(hint,50);
        GAMEDATA::getInstance()->setShowFangZhuDismiss(false);
    }
}

void LobbyScene::onExit(){
    Scene::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(enterRoomListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(enterFriendRoomListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(openFriendRoomListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(lobbyConncetAgainListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(intnetListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(loginReplaceListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(payDialogListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(payResultListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(imageUpdateListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(firstChargeListenr);
    Director::getInstance()->getEventDispatcher()->removeEventListener(openRoomAskListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(enterRoomAskListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(scrollTetxListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(wanjiaqunListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(noticeUrlLitener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(upateLequanShopLitener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(showLoobyLoadingLayer);
    Director::getInstance()->getEventDispatcher()->removeEventListener(gameFupanListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(roomListRespListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(lobbyReconnectRespListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(gongGaoInfoListener);
}

void LobbyScene::addEventListener(){
    //进入房间回复
    enterRoomListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_ENTER_ROOM_RESP, [=](EventCustom* event){
        removeLoading();
        
        EnterRoomResp* respData = static_cast<EnterRoomResp*>(event->getUserData());
        EnterRoomResp newRespData = *respData;
        if (newRespData.result == "1"){
            Director::getInstance()->replaceScene(TransitionFade::create(1, MjGameScene::create()));
        } else if(newRespData.result == "2"){
            for(auto var : GAMEDATA::getInstance()->getRoomList().rooms){
                if(GAMEDATA::getInstance()->getCurrentSelectRoomId() == var.roomId){
#if(CC_TARGET_PLATFORM ==  CC_PLATFORM_ANDROID)
                    if(UserData::getInstance()->isWeixinPayOpen()){
                        GoldNotEnoughDialog* gold = GoldNotEnoughDialog::create(newRespData,GAMEDATA::getInstance()->getCurrentSelectRoomId());
                        addChild(gold,4);
                    }else{
                        HintDialog* hint = HintDialog::create("游戏金币不足",NULL);
                        addChild(hint,100);
                    }
#elif(CC_TARGET_PLATFORM ==  CC_PLATFORM_IOS||CC_TARGET_PLATFORM ==  CC_PLATFORM_MAC)
                    GoldNotEnoughDialog* gold = GoldNotEnoughDialog::create(newRespData,GAMEDATA::getInstance()->getCurrentSelectRoomId());
                    addChild(gold,4);
#endif
                }
            }
        }
        else if(newRespData.result == "3"){
            if(atoi(respData->rsid.c_str()) == ROOM_2){
                EnterRoomDialog* dia = EnterRoomDialog::create(EnterRoomDialogType::goldMoreLeve1);
                addChild(dia,4);
            }else if(atoi(respData->rsid.c_str()) == ROOM_3){
                EnterRoomDialog* dia = EnterRoomDialog::create(EnterRoomDialogType::goldMoreLeve2);
                addChild(dia,4);
            }
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
#if(CC_TARGET_PLATFORM ==  CC_PLATFORM_ANDROID)
            if(UserData::getInstance()->isWeixinPayOpen()){
                FangkaNotEnoughDialog* charge = FangkaNotEnoughDialog::create();
                addChild(charge,14);
                GAMEDATA::getInstance()->setShowDialogType(-1);
            }else{
                HintDialog* hint = HintDialog::create("房卡有一定几率在游戏中掉落",NULL);
                addChild(hint,14);
            }
#elif(CC_TARGET_PLATFORM ==  CC_PLATFORM_IOS||CC_TARGET_PLATFORM ==  CC_PLATFORM_MAC)
            FangkaNotEnoughDialog* charge = FangkaNotEnoughDialog::create();
            addChild(charge,14);
#endif
        }
        else if(result == "4"){
            RoomIdErrorDialog* idd = RoomIdErrorDialog::create();
            addChild(idd,14);
        }
    });
    
    
    //好友开房
    openFriendRoomListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_FRIEND_OPEN_ROOM_RESP, [=](EventCustom* event){
        GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
        FriendOpenRoomRespData resp = GAMEDATA::getInstance()->getFriendOpenRoomResp();
        if(resp.result == 1){
//            ChatAndroidMethod::getInstance()->createChatRoom(UserData::getInstance()->getPoxiaoId());
            GAMEDATA::getInstance()->setFangZhuId(UserData::getInstance()->getPoxiaoId());
            Director::getInstance()->replaceScene(TransitionFade::create(1, MjGameScene::create()));
        }else if(resp.result == 2){
#if(CC_TARGET_PLATFORM ==  CC_PLATFORM_ANDROID)
            if(UserData::getInstance()->isWeixinPayOpen()){
                FangkaNotEnoughDialog* charge = FangkaNotEnoughDialog::create();
                addChild(charge,14);
                GAMEDATA::getInstance()->setShowDialogType(-1);
            }else{
                HintDialog* hint = HintDialog::create("房卡有一定几率在游戏中掉落",NULL);
                addChild(hint,14);
            }
#elif(CC_TARGET_PLATFORM ==  CC_PLATFORM_IOS||CC_TARGET_PLATFORM ==  CC_PLATFORM_MAC)
            FangkaNotEnoughDialog* charge = FangkaNotEnoughDialog::create();
            addChild(charge,14);
#endif
        }
    });
    
    
    //断线续玩
    lobbyConncetAgainListener=  Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_PLAYER_CONNECT_AGAIN, [=](EventCustom* event){
        GAMEDATA::getInstance()->setIsRecover(true);
        Director::getInstance()->replaceScene(MjGameScene::create());
    });
    
    
    //登录地址变更
    loginReplaceListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_PLAYER_REPLACE_LOGIN, [=](EventCustom* event){
        HintDialog* hin = HintDialog::create("你的账号在其他客户端登录",[=](Ref* ref){
            exit(0);
        });
        addChild(hin,500);
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
        firstMenu->setVisible(false);
        ganTanhao->setVisible(false);
    });
    
    //开房询问
    openRoomAskListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_LOBBY_ASK_OPEN_ROOM, [=](EventCustom* event){
        removeLoading();
        if(UserData::getInstance()->getFangkaNum()>0){
            FriendRoom* friendroom = FriendRoom::create();
            addChild(friendroom,10);
        }else{
#if(CC_TARGET_PLATFORM ==  CC_PLATFORM_ANDROID)
            if(UserData::getInstance()->isWeixinPayOpen()){
                FangkaNotEnoughDialog* charge = FangkaNotEnoughDialog::create();
                addChild(charge,14);
            }else{
                HintDialog* hint = HintDialog::create("房卡有一定几率在游戏中掉落",NULL);
                addChild(hint,14);
            }
#elif(CC_TARGET_PLATFORM ==  CC_PLATFORM_IOS||CC_TARGET_PLATFORM ==  CC_PLATFORM_MAC)
            FangkaNotEnoughDialog* charge = FangkaNotEnoughDialog::create();
            addChild(charge,14);
#endif
        }
    });
    
    //进入房间询问
    enterRoomAskListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_LOBBY_ASK_ENTER_ROOM, [=](EventCustom* event){
        removeLoading();
        MahjongNumberKeypads* keypads = MahjongNumberKeypads::create();
        addChild(keypads);
    });
    
    //跑马灯
    scrollTetxListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_SCROLL_TEXT, [=](EventCustom* event){
        std::string msg = static_cast<char*>(event->getUserData());
        if(nullptr != ((ScrollTextEx*)getChildByTag(9980))){
            ((ScrollTextEx*)getChildByTag(9980))->setScrollStr(msg);
        }
    });
    
    //玩家群
    wanjiaqunListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_WAN_JIA_WEI_XIN_QUN, [=](EventCustom* event){
        if(GAMEDATA::getInstance()->getWanJiaQunVer()>UserData::getInstance()->getWanJiaQunVersion()){
            UrlImageMannger::getInstance()->downloadQunImgByUrl(WECHAT_WAN_JIA_QUN_URL,true);
        }
        if(GAMEDATA::getInstance()->getDailiQunVer()>UserData::getInstance()->getDailiQunVersion()){
            UrlImageMannger::getInstance()->downloadDailiImgByUrl(WECHAT_DAI_LI_QUN_URL,true);
        }
    });
    
    //游戏广告
    noticeUrlLitener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_WAN_JIA_GONG_GAO, [=](EventCustom* event){
        GameActivityData* data = static_cast<GameActivityData*>(event->getUserData());
        GameActivityData newData = *data;
        GAMEDATA::getInstance()->setGameActivityData(newData);
        if(!GAMEDATA::getInstance()->getHaveShowNotice()){
            NoticeDialog* nod = NoticeDialog::create();
            nod->setContentImage(newData.imageUrl,newData.showTime);
            addChild(nod,100);
            GAMEDATA::getInstance()->setHaveShowNotice(true);
        }
    });
    
    upateLequanShopLitener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_UPDATE_LEQUAN_SHANG_CHEN_SHOW, [=](EventCustom* event){
        if(NULL != getChildByTag(901))
            getChildByTag(901)->setVisible(UserData::getInstance()->isWeixinPayOpen());
        if(NULL != getChildByTag(902))
            getChildByTag(902)->setVisible(UserData::getInstance()->isWeixinPayOpen());
        if(NULL != getChildByTag(903))
            getChildByTag(903)->setVisible(UserData::getInstance()->isWeixinPayOpen());
        if(NULL != lequanNum)
            lequanNum->setVisible(UserData::getInstance()->isWeixinPayOpen());
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        if(NULL != getChildByTag(801))
            getChildByTag(801)->setVisible(UserData::getInstance()->isWeixinPayOpen());
        if(NULL != getChildByTag(802))
            getChildByTag(802)->setVisible(UserData::getInstance()->isWeixinPayOpen());
        if(NULL != getChildByTag(803))
            getChildByTag(803)->setVisible(UserData::getInstance()->isWeixinPayOpen());
        if(NULL != goldNum)
            goldNum->setVisible(UserData::getInstance()->isWeixinPayOpen());
        if(NULL != getChildByTag(1298)){
            getChildByTag(1298)->setVisible(UserData::getInstance()->isWeixinPayOpen());
        }
        if(NULL != getChildByTag(6656)){
            getChildByTag(6656)->setVisible(UserData::getInstance()->isWeixinPayOpen());
        }
        if(UserData::getInstance()->isFirstCharge()){
            firstMenu->setVisible(false);
            ganTanhao->setVisible(false);
        }else{
            firstMenu->setVisible(UserData::getInstance()->isWeixinPayOpen());
            ganTanhao->setVisible(UserData::getInstance()->isWeixinPayOpen());
        }
#endif
    });
    
    showLoobyLoadingLayer = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_LOBBY_SHOW_LOADING_LAYER, [=](EventCustom* event){
        showLoading();
    });
    //游戏复盘
    gameFupanListener  = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_GAME_FU_PAN_NOTIFY, [=](EventCustom* event){
        if(GAMEDATA::getInstance()->getPlaybackInfo().result == 1){
            GAMEDATA::getInstance()->setIsFuPan(true);
            Director::getInstance()->replaceScene(MjGameScene::create());
        }
    });
    
    gameFupanListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_GET_TUI_GUANG_PRIDE, [=](EventCustom* event){
        std::string buf = static_cast<char*>(event->getUserData());
        ShopHintDialog* da = ShopHintDialog::create();
        if(buf == "1"){
            da->showText("领取成功");
            ParticleUtil* par = ParticleUtil::create(MyParticleType::goldOnly);
            addChild(par,10);
            //刷新用户信息
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getTuiGuangCommand());
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getPlayerInfoCommand());
        }else{
            da->showText("领取失败");
        }
        addChild(da,10);
    });
    
    
    //获取房间列表
    roomListRespListener = EventListenerCustom::create(MSG_ROOM_LIST_RESP, [=](EventCustom* event){
        RoomListData* data = static_cast<RoomListData*>(event->getUserData());
        RoomListData newData = *data;
        if(data->rooms.size()>0 && getChildByTag(1298) == NULL){
            GAMEDATA::getInstance()->setRoomList(newData);
            GoldRoomPlate* plate = GoldRoomPlate::create(newData);
            plate->setTag(1298);
            addChild(plate,2);
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
            //支付审核
            plate->setVisible(UserData::getInstance()->isWeixinPayOpen());
#endif
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(roomListRespListener, 1);
    
    
    lobbyReconnectRespListener = EventListenerCustom::create(MSG_LOGIN_RESP, [=](EventCustom* event){
        if(getChildByTag(2000)!=NULL){
            getChildByTag(2000)->removeFromParent();
        }
//        ChatAndroidMethod::getInstance()->loginChatServer(UserData::getInstance()->getPoxiaoId());
        Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(lobbyReconnectRespListener, 1);
    
    gongGaoInfoListener = EventListenerCustom::create(MSG_GET_WAN_JIA_GONG_GAO, [=](EventCustom* event){
        if(getChildByTag(1209)!=NULL){
            getChildByTag(1209)->removeFromParent();
        }
        GameGongGao* gonggaoData = static_cast<GameGongGao*>(event->getUserData());
        GameGongGaoLayer* gonggao = GameGongGaoLayer::create(*gonggaoData);
        addChild(gonggao,5);
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(gongGaoInfoListener, 1);
    
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




