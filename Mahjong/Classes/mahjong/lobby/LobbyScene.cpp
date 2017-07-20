#include "mahjong/lobby/LobbyScene.h"
#include "mahjong/lobby/friend/MahjongNumberKeypads.hpp"
#include "mahjong/lobby/friend/dialog/RoomIdErrorDialog.hpp"
#include "mahjong/lobby/wanjiaqun/WanJiaQunLayer.hpp"
#include "mahjong/lobby/friend/dialog/RoomFullDialog.hpp"
#include "mahjong/lobby/friend/FriendRoom.h"
#include "mahjong/common/competition/CompetitonItem.hpp"
#include "mahjong/lobby/goldroom/GoldRoomPlate.hpp"
#include "mahjong/lobby/dialog/EnterRoomDialog.hpp"
#include "mahjong/lobby/notice/NoticeDialog.hpp"
#include "mahjong/lobby/gonggao/GameGongGaoLayer.hpp"
#include "mahjong/lobby/shiming/ShiMingLayer.hpp"
#include "mahjong/lobby/shop/FirstChageDialog.hpp"
#include "mahjong/lobby/shop/gold/ChargeGold.hpp"
#include "mahjong/lobby/shop/fangka/ChargeFangka.hpp"
#include "mahjong/lobby/shop/fangka/FangkaNotEnoughDialog.hpp"
#include "mahjong/lobby/shop/mall/LequanShop.hpp"
#include "mahjong/lobby/shop/gold/GoldNotEnoughDialog.hpp"
#include "mahjong/lobby/shop/ShopHintDialog.hpp"
#include "mahjong/lobby/share/ShareToFriendLayer.hpp"
#include "mahjong/lobby/invitecode/InviteCodeLayer.hpp"
#include "mahjong/lobby/rank/RankLayer.hpp"
#include "mahjong/lobby/turntable/DailyPride.h"
#include "mahjong/common/heroinfo/HeroInfoEdit.h"
#include "mahjong/common/bill/BillInfo.h"
#include "mahjong/common/dialog/prompt/HintDialog.hpp"
#include "mahjong/common/dialog/prompt/TextHintDialog.hpp"
#include "mahjong/lobby/shop/huafei/HuafeiShop.hpp"
#include "mahjong/common/widget/HeadImage.hpp"
#include "mahjong/common/widget/ScrollTextEx.h"
#include "mahjong/common/audio/Audio.h"
#include "mahjong/common/widget/ParticleUtil.hpp"
#include "mahjong/common/utils/Chinese.h"
#include "mahjong/GameConfig.h"
#include "http/image/UrlImageMannger.h"
#include "mahjong/result/hongbao/HongbaoAnim.hpp"
#include "mahjong/result/hongbao/HongbaoAnim2.hpp"
#include "mahjong/lobby/share/ShareActivityLayer.hpp"
#include "mahjong/lobby/share/ShareSelectLayer.hpp"
#include "mahjong/lobby/gongzhonghao/GongZhongHaoLayer.hpp"
#include "mahjong/lobby/competition/CompeititionPlate.hpp"


bool LobbyScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    showDissolveDialog = false;
    initView();
    //    showLobbyAnim();
    //add sprite to scene
    drawSceneTop();
    drawSceneMid();
    drawSceneBot();
    
    return true;
}


void LobbyScene::signUpdate(float dt){
    if(GAMEDATA::getInstance()->getShowProtected()){
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MSG_NETWORK_BREAK_INFO);
        GAMEDATA::getInstance()->setShowProtected(false);
    }
    
    if(GAMEDATA::getInstance()->getShowDialogType() == 2){
        for(auto var : GAMEDATA::getInstance()->getRoomList().rooms){
            if(GAMEDATA::getInstance()->getCurrentSelectRoomId() == var.roomId){
#if(CC_TARGET_PLATFORM ==  CC_PLATFORM_ANDROID)
                if(UserData::getInstance()->isWeixinPayOpen()){
                    GoldNotEnoughDialog* gold = GoldNotEnoughDialog::create(GAMEDATA::getInstance()->getEnterRoomResp(),GAMEDATA::getInstance()->getCurrentSelectRoomId());
                    addChild(gold,30);
                }else{
                    HintDialog* hint = HintDialog::create(ChineseWord("dialog_text_16"),NULL);
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
            HintDialog* hint = HintDialog::create(ChineseWord("dialog_text_17"),NULL);
            addChild(hint,30);
        }
#elif(CC_TARGET_PLATFORM ==  CC_PLATFORM_IOS)
        FangkaNotEnoughDialog* charge = FangkaNotEnoughDialog::create();
        addChild(charge,30);
        GAMEDATA::getInstance()->setShowDialogType(-1);
#endif
    }
    
    if(NULL != getChildByTag(1988) && !getChildByTag(1988)->isVisible()){
        if(NULL != getChildByTag(1980)){
            getChildByTag(1980)->setPosition(650, 435);
        }
    }
}



void LobbyScene::initView(){
    //add game bg to layer
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Sprite* lobby_bg = Sprite::create("common/shang_hai_bg.jpg");
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
    
    nickName = Label::createWithSystemFont(UserData::getInstance()->getNickName(), "arial", 22);
    nickName->setPosition(115, 690);
    nickName->setColor(Color3B(255,252,242));
    nickName->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    nickName->setAlignment(TextHAlignment::LEFT);
    addChild(nickName);
    
    auto markid = Label::createWithSystemFont(StringUtils::format("ID:%s",UserData::getInstance()->getMarkId().c_str()), "arial", 22);
    markid->setPosition(115, 660);
    markid->setColor(Color3B(255,252,242));
    markid->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    markid->setAlignment(TextHAlignment::LEFT);
    addChild(markid);
    
    //fangka
    auto fangka_bg = Sprite::create("mjlobby/room_info_bg.png");
    fangka_bg->setPosition(365, 687);
    addChild(fangka_bg);
    auto fangka_icon = Sprite::create("common/fangka_icon.png");
    fangka_icon->setPosition(305, 687);
    addChild(fangka_icon);
    fangkaNum = Label::createWithSystemFont(StringUtils::format("%0.1f",UserData::getInstance()->getFangkaNum()),"Arial",24);
    fangkaNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
    fangkaNum->setColor(Color3B(242,227,75));
    fangkaNum->setPosition(365, 687);
    addChild(fangkaNum);
    auto fangka_btn = MenuItemImage::create("mjlobby/plus_btn_1.png", "mjlobby/plus_btn_2.png", CC_CALLBACK_0(LobbyScene::chargeFangka, this));
    auto chargfangka = Menu::create(fangka_btn, NULL);
    chargfangka->setPosition(425, 687);
    addChild(chargfangka);
    
    
    //gold
    auto gold_bg = Sprite::create("mjlobby/room_info_bg.png");
    gold_bg->setPosition(550, 687);
    gold_bg->setTag(801);
    addChild(gold_bg);
    auto gold_icon = Sprite::create("mjlobby/gold_icon.png");
    gold_icon->setPosition(490, 687);
    gold_icon->setTag(802);
    addChild(gold_icon);
    goldNum = Label::createWithSystemFont("0","Arial",24);
    if(UserData::getInstance()->getGold()>100000000){
        goldNum->setString(StringUtils::format("%.0f亿",UserData::getInstance()->getGold()/100000000.0));
    }else if(UserData::getInstance()->getGold()>100000){
        goldNum->setString(StringUtils::format("%.0f万",UserData::getInstance()->getGold()/10000.0));
    }else{
        goldNum->setString(StringUtils::format("%d",UserData::getInstance()->getGold()));
    }
    goldNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
    goldNum->setColor(Color3B(242,227,75));
    goldNum->setPosition(550, 687);
    addChild(goldNum);
    auto gold_btn = MenuItemImage::create("mjlobby/plus_btn_1.png", "mjlobby/plus_btn_2.png", CC_CALLBACK_0(LobbyScene::chargeGold, this));
    auto chargGold = Menu::create(gold_btn, NULL);
    chargGold->setPosition(610, 687);
    chargGold->setTag(803);
    addChild(chargGold);
    
    //huafei
    auto huafei_bg = Sprite::create("mjlobby/room_info_bg.png");
    huafei_bg->setTag(904);
    huafei_bg->setPosition(735, 687);
    addChild(huafei_bg);
    auto huafei_icon = Sprite::create("common/huafei_icon.png");
    huafei_icon->setTag(905);
    huafei_icon->setPosition(675, 687);
    addChild(huafei_icon);
    haufeiNum = Label::createWithSystemFont(StringUtils::format("%0.1f",UserData::getInstance()->getHuafeiQuan()),"Arial",24);
    haufeiNum->setColor(Color3B(242,227,75));
    haufeiNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
    haufeiNum->setPosition(735, 687);
    addChild(haufeiNum);
    auto haufei_btn = MenuItemImage::create("mjlobby/plus_btn_1.png", "mjlobby/plus_btn_2.png", CC_CALLBACK_0(LobbyScene::exchangeHuafei, this));
    auto chargHuaFei = Menu::create(haufei_btn, NULL);
    chargHuaFei->setTag(906);
    chargHuaFei->setPosition(795, 687);
    addChild(chargHuaFei);
    
    //lequan
    auto lequan_bg = Sprite::create("mjlobby/room_info_bg.png");
    lequan_bg->setTag(901);
    lequan_bg->setPosition(910, 687);
    addChild(lequan_bg);
    auto lequan_icon = Sprite::create("common/lequan_icon.png");
    lequan_icon->setTag(902);
    lequan_icon->setPosition(850, 687);
    addChild(lequan_icon);
    lequanNum = Label::createWithSystemFont("0","Arial",24);
    if(UserData::getInstance()->getTicket()>100000000){
        lequanNum->setString(StringUtils::format("%.0f亿",UserData::getInstance()->getTicket()/100000000.0));
    }else if(UserData::getInstance()->getTicket()>100000){
        lequanNum->setString(StringUtils::format("%.0f万",UserData::getInstance()->getTicket()/10000.0));
    }else{
        lequanNum->setString(StringUtils::format("%d",UserData::getInstance()->getTicket()));
    }
    lequanNum->setColor(Color3B(242,227,75));
    lequanNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
    lequanNum->setPosition(910, 687);
    addChild(lequanNum);
    auto lequan_btn = MenuItemImage::create("mjlobby/plus_btn_1.png", "mjlobby/plus_btn_2.png", CC_CALLBACK_0(LobbyScene::exchangeLequan, this));
    auto chargLequan = Menu::create(lequan_btn, NULL);
    chargLequan->setTag(903);
    chargLequan->setPosition(970, 687);
    addChild(chargLequan);
    
    //支付审核专用
    lequan_bg->setVisible(UserData::getInstance()->isWeixinPayOpen());
    lequan_icon->setVisible(UserData::getInstance()->isWeixinPayOpen());
    lequanNum->setVisible(UserData::getInstance()->isWeixinPayOpen());
    chargLequan->setVisible(UserData::getInstance()->isWeixinPayOpen());
    huafei_bg->setVisible(UserData::getInstance()->isWeixinPayOpen());
    huafei_icon->setVisible(UserData::getInstance()->isWeixinPayOpen());
    haufeiNum->setVisible(UserData::getInstance()->isWeixinPayOpen());
    chargHuaFei->setVisible(UserData::getInstance()->isWeixinPayOpen());
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    gold_bg->setVisible(UserData::getInstance()->isWeixinPayOpen());
    gold_icon->setVisible(UserData::getInstance()->isWeixinPayOpen());
    goldNum->setVisible(UserData::getInstance()->isWeixinPayOpen());
    chargGold->setVisible(UserData::getInstance()->isWeixinPayOpen());
#endif
}

void LobbyScene::drawSceneMid(){
    
    auto sharefriend = MenuItemImage::create("mjlobby/share_1.png", "mjlobby/share_2.png",
                                             CC_CALLBACK_0(LobbyScene::showRedWallet, this));
    auto shareMenu = Menu::create(sharefriend, NULL);
    shareMenu->alignItemsHorizontallyWithPadding(15);
    shareMenu->setPosition(650, 535);
    shareMenu->setTag(1987);
    addChild(shareMenu);
    
    if(GAMEDATA::getInstance()->getBottomText() != "" && UserData::getInstance()->isWeixinPayOpen()){
        auto textbg = Sprite::create("mjlobby/ti_shi_2.png");
        textbg->setPosition(750,570);
        addChild(textbg);
        auto text = Label::createWithSystemFont("分享有钱拿!", "arial", 20);
        text->setAnchorPoint(Point::ANCHOR_MIDDLE);
        text->setColor(Color3B(255,247,217));
        text->setPosition(90,30);
        textbg->addChild(text);
        textbg->runAction(Repeat::create(Sequence::create(MoveTo::create(0.92f,Point(750,580)),MoveTo::create(0.92f,Point(750,570)),NULL), CC_REPEAT_FOREVER));
    }
    
    
    auto first_chaege = MenuItemImage::create("mjlobby/first_charge_btn_1.png", "mjlobby/first_charge_btn_2.png",
                                              CC_CALLBACK_0(LobbyScene::showFirstCharge, this));
    firstMenu = Menu::create(first_chaege, NULL);
    firstMenu->setTag(1988);
    firstMenu->setPosition(650, 435);
    addChild(firstMenu);
    firstMenu->setVisible(UserData::getInstance()->isFirstCharge()?false:true);
    
    auto huodong = MenuItemImage::create("mjlobby/red_wallet_1.png","mjlobby/red_wallet_2.png",CC_CALLBACK_0(LobbyScene::showHotActivity, this));
    auto mymenu = Menu::create(huodong,NULL);
    mymenu->setPosition(650,335);
    mymenu->setTag(1980);
    addChild(mymenu);
    mymenu->setVisible(false);
    
    //跑马灯
    ScrollTextEx* scroll = ScrollTextEx::create();
    scroll->setAutoScroll(true);
    scroll->setTag(9980);
    scroll->setPosition(600,620);
    addChild(scroll,2);
    
    RankLayer* rlayer = RankLayer::create(GAMEDATA::getInstance()->getLobbyPaiHangData());
    addChild(rlayer);
    
    
    auto btn_open = MenuItemImage::create("mjlobby/open_room_btn_1.png", "mjlobby/open_room_btn_2.png", CC_CALLBACK_0(LobbyScene::openRoom, this));
    auto btn_enter = MenuItemImage::create("mjlobby/enter_room_btn_1.png", "mjlobby/enter_room_btn_2.png", CC_CALLBACK_0(LobbyScene::joinRoom, this));
    auto gameMenu = Menu::create(btn_open,btn_enter, NULL);
    gameMenu->alignItemsVerticallyWithPadding(2);
    gameMenu->setPosition(1025, 475);
    addChild(gameMenu);
    if(atoi(GAMEDATA::getInstance()->getPrivateGameNum().c_str())>0||GAMEDATA::getInstance()->getFangZhuId() == UserData::getInstance()->getPoxiaoId()){
        Sprite* frame = Sprite::create("mjlobby/go_to_friend_room_1.png");
        btn_open->setNormalImage(frame);
        Sprite* frame2 = Sprite::create("mjlobby/go_to_friend_room_2.png");
        btn_open->setSelectedImage(frame2);
    }
    RoomListData newData = GAMEDATA::getInstance()->getRoomList();
    if(newData.matchList.size()>0 && UserData::getInstance()->isWeixinPayOpen()){
        auto competitionImg = MenuItemImage::create("mjlobby/com_btn_1.png", "mjlobby/com_btn_2.png", CC_CALLBACK_0(LobbyScene:: showCompetitionLayer,this));
        auto comMenu = Menu::create(competitionImg,NULL);
        comMenu->setPosition(1025,290);
        addChild(comMenu);
    }
    if(newData.rooms.size()>0 && getChildByTag(1298) == NULL){
        auto jinImg = MenuItemImage::create("mjlobby/gold_room_btn_1.png","mjlobby/gold_room_btn_1.png",CC_CALLBACK_0(LobbyScene:: spreadGoldRoom,this));
        auto jinMenu =  Menu ::create(jinImg,NULL);
        jinMenu->setPosition(1115,180);
        jinMenu->setTag(1297);
        addChild(jinMenu);
        
        GoldRoomPlate* plate = GoldRoomPlate::create(newData);
        plate->setTag(1298);
        plate->setVisible(false);
        addChild(plate,2);
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        //支付审核
        jinMenu->setVisible(UserData::getInstance()->isWeixinPayOpen());
#endif
    }
}

void LobbyScene::drawSceneBot(){
    auto bottomBg = Sprite::create("mjlobby/open_room_bg_bot.png");
    bottomBg->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    bottomBg->setPosition(640,0);
    addChild(bottomBg);
    
    
    auto btn_1 = MenuItemImage::create("mjlobby/sm_btn_1.png", "mjlobby/sm_btn_2.png", CC_CALLBACK_0(LobbyScene::showShiMing, this));
    auto gameMenu2 = Menu::create(btn_1, NULL);
    gameMenu2->setPosition(320, 50);
    addChild(gameMenu2);
    
    auto gongzh = MenuItemImage::create("mjlobby/gzh_btn1.png","mjlobby/gzh_btn2.png",CC_CALLBACK_0(LobbyScene::showGongZhongHao, this));
    auto mymenu2 = Menu::create(gongzh,NULL);
    mymenu2->setPosition(480,50);
    addChild(mymenu2);
    
    auto btn_bill = MenuItemImage::create("mjlobby/bill_btn_1.png", "mjlobby/bill_btn_1.png", CC_CALLBACK_0(LobbyScene::showPlayerBill, this));
    auto billMenu = Menu::create(btn_bill, NULL);
    
    billMenu->setPosition(640,50);
    addChild(billMenu);
    
    auto btn_2 = MenuItemImage::create("mjlobby/wan_jia_quan_1.png", "mjlobby/wan_jia_quan_2.png", CC_CALLBACK_0(LobbyScene::showWanJiaQun, this));
    auto gameMenu3 = Menu::create(btn_2, NULL);
    gameMenu3->alignItemsHorizontallyWithPadding(5);
    gameMenu3->setPosition(800, 50);
    addChild(gameMenu3);
    
    auto btn_setting = MenuItemImage::create("mjlobby/setting_btn_1.png", "mjlobby/setting_btn_1.png", CC_CALLBACK_0(LobbyScene::showGameSetting, this));
    auto settingMenu = Menu::create(btn_setting, NULL);
    
    settingMenu->setPosition(975,50);
    addChild(settingMenu);
    
    //显示公告小信息
    if(GAMEDATA::getInstance()->getBottomText() != ""&& UserData::getInstance()->isWeixinPayOpen()){
        auto textbg = Sprite::create("mjlobby/ti_shi_kuang.png");
        textbg->setPosition(782,107);
        addChild(textbg);
        auto text = Label::createWithSystemFont(GAMEDATA::getInstance()->getBottomText(), "arial", 20);
        text->setAnchorPoint(Point::ANCHOR_MIDDLE);
        text->setColor(Color3B(255,247,217));
        text->setPosition(220,40);
        textbg->addChild(text);
        textbg->runAction(Repeat::create(Sequence::create(MoveTo::create(0.9f,Point(782,117)),MoveTo::create(0.9f,Point(782,107)),NULL), CC_REPEAT_FOREVER));
    }
}

//刷新显示的用户信息
void LobbyScene::updateHeroInfo(){
    ((HeadImage*)getChildByTag(962))->updateImage();
    nickName->setString(UserData::getInstance()->getNickName());
    if(UserData::getInstance()->getGold()>100000000){
        goldNum->setString(StringUtils::format("%.0f亿",UserData::getInstance()->getGold()/100000000.0));
    }else if(UserData::getInstance()->getGold()>100000){
        goldNum->setString(StringUtils::format("%.0f万",UserData::getInstance()->getGold()/10000.0));
    }else{
        goldNum->setString(StringUtils::format("%d",UserData::getInstance()->getGold()));
    }
    fangkaNum->setString(StringUtils::format("%0.1f",UserData::getInstance()->getFangkaNum()));
    if(NULL != lequanNum){
        if(UserData::getInstance()->getTicket()>100000000){
            lequanNum->setString(StringUtils::format("%.0f亿",UserData::getInstance()->getTicket()/100000000.0));
        }else if(UserData::getInstance()->getTicket()>100000){
            lequanNum->setString(StringUtils::format("%.0f万",UserData::getInstance()->getTicket()/10000.0));
        }else{
            lequanNum->setString(StringUtils::format("%d",UserData::getInstance()->getTicket()));
        }
    }
    if(NULL != haufeiNum)
        haufeiNum->setString(StringUtils::format("%0.1f",UserData::getInstance()->getHuafeiQuan()));
}

void LobbyScene::showLobbyAnim(){
    
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
    
    auto star = Sprite::create("competition/star.png");
    star->setPosition(365,112);
    star->setOpacity(0);
    addChild(star,1);
    star->runAction(Repeat::create(Sequence::create(FadeTo::create(0.5, 255),FadeTo::create(0.5,0),DelayTime::create(7), NULL),CC_REPEAT_FOREVER));
    
    auto blink = Sprite::create("mjlobby/light_btn_anim_2.png");
    blink->setPosition(430,65);
    addChild(blink,1);
    blink->setVisible(false);
    blink->runAction(Repeat::create(Sequence::create(DelayTime::create(1),CallFunc::create([=](){
        blink->setVisible(true);
        blink->setPosition(430,65);
    }),MoveTo::create(1.5,Point(810,65)),CallFunc::create([=](){
        blink->setVisible(false);
    }),DelayTime::create(5.5), NULL),CC_REPEAT_FOREVER));
    auto blink2 = Sprite::create("mjlobby/light_btn_anim_2.png");
    blink2->setPosition(470,65);
    addChild(blink2,1);
    blink2->setVisible(false);
    blink2->runAction(Repeat::create(Sequence::create(DelayTime::create(1),CallFunc::create([=](){
        blink2->setPosition(470,65);
        blink2->setVisible(true);
    }),MoveTo::create(1.5,Point(850,65)),CallFunc::create([=](){
        blink2->setVisible(false);
    }),DelayTime::create(5.5), NULL),CC_REPEAT_FOREVER));
    
    auto btnlight = Sprite::create("mjlobby/light_btn_anim_1.png");
    btnlight->setPosition(640,70);
    addChild(btnlight,1);
    btnlight->runAction(Repeat::create(Sequence::create(DelayTime::create(1),Blink::create(2, 2),DelayTime::create(5), NULL),CC_REPEAT_FOREVER));
    
    auto blue = Sprite::create("mjlobby/btn_blue_light.png");
    blue->setPosition(1025,58);
    addChild(blue,1);
    blue->setVisible(false);
    blue->runAction(Repeat::create(Sequence::create(DelayTime::create(3),CallFunc::create([=](){
        blue->setVisible(true);
    }),Blink::create(2, 2),CallFunc::create([=](){
        blue->setVisible(false);
    }), DelayTime::create(3),NULL),CC_REPEAT_FOREVER));
    
    
    auto blue2 = Sprite::create("mjlobby/btn_blue_light.png");
    blue->setFlippedX(true);
    blue2->setPosition(255,58);
    addChild(blue2,1);
    blue2->setVisible(false);
    blue2->runAction(Repeat::create(Sequence::create(DelayTime::create(3),CallFunc::create([=](){
        blue2->setVisible(true);
    }),Blink::create(2, 2),CallFunc::create([=](){
        blue2->setVisible(false);
    }), DelayTime::create(3),NULL),CC_REPEAT_FOREVER));
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

void LobbyScene::showGongZhongHao(){
    GongZhongHaoLayer* hao = GongZhongHaoLayer::create();
    addChild(hao,100);
}

void LobbyScene::showFirstCharge(){
    Audio::getInstance()->playSoundClick();
    //首冲
    FirstChargeDialog* firCharge = FirstChargeDialog::create();
    addChild(firCharge,3);
}

void LobbyScene::showRedWallet(){
    Audio::getInstance()->playSoundClick();
    ShareSelectLayer* laye = ShareSelectLayer::create();
    addChild(laye,100);
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
    DailyPride* pride = DailyPride::create();
    addChild(pride,10);
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
        //        if(!UserData::getInstance()->isInviteCodeBind()){
        //            InviteCodeLayer* lay = InviteCodeLayer::create();
        //            addChild(lay,6);
        //        }
        ChargeFangka* charge = ChargeFangka::create();
        addChild(charge,3);
    }else{
        HintDialog* hint = HintDialog::create(ChineseWord("dialog_text_17"),NULL);
        addChild(hint,3);
    }
#elif(CC_TARGET_PLATFORM ==  CC_PLATFORM_IOS)
    //    if(!UserData::getInstance()->isInviteCodeBind()){
    //        InviteCodeLayer* lay = InviteCodeLayer::create();
    //        addChild(lay,6);
    //    }
    ChargeFangka* charge = ChargeFangka::create();
    addChild(charge,3);
#elif(CC_TARGET_PLATFORM ==  CC_PLATFORM_MAC)
    ChargeFangka* charge = ChargeFangka::create();
    addChild(charge,3);
#endif
}

void LobbyScene::exchangeLequan(){
    Audio::getInstance()->playSoundClick();
    LequanShop* shop = LequanShop::create();
    addChild(shop,3);
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getLequanChangeListCommand());
    
}

void LobbyScene::exchangeHuafei(){
    Audio::getInstance()->playSoundClick();
    HuafeiShop* shop = HuafeiShop::create();
    addChild(shop,3);
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendExchangeHuaFeiCommand());
}

void LobbyScene::showLoading(){
    Loading* loadLayer = Loading::create();
    loadLayer->setTag(1000);
    addChild(loadLayer,3);
}

void LobbyScene::showShiMing(){
    
    if(GAMEDATA::getInstance()->getCertification()){
        HintDialog* hd = HintDialog::create(ChineseWord("dialog_text_18"), nullptr);
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


void LobbyScene::spreadGoldRoom(){
    if(NULL != getChildByTag(1298)){
        getChildByTag(1298)->setVisible(!getChildByTag(1298)->isVisible());
    }
}

void LobbyScene::showCompetitionLayer(){
    CompeititionPlate* plate = CompeititionPlate::create();
    addChild(plate,1000);
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
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getGamePayType());
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getRoomListCommand("1"));
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getPlayerInfoCommand());
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getScrollTextCommand());
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getNoticeCommand());
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendLobbyPaiHangCommand());
    if(GAMEDATA::getInstance()->getNeedShowHongbaoResult() && !GAMEDATA::getInstance()->getHasShowHongbaoResult()){
        GAMEDATA::getInstance()->setNeedShowHongbaoResult(false);
        if(atof(GAMEDATA::getInstance()->getGameHongBaoPride2().sxlmfee.c_str())>0){
            HongbaoAnim2* ami = HongbaoAnim2::create();
            ami->initView(GAMEDATA::getInstance()->getGameHongBaoPride2().dyjfee, GAMEDATA::getInstance()->getGameHongBaoPride2().fzfee,1,true);
            addChild(ami,200);
        }else if(atof(GAMEDATA::getInstance()->getGameHongBaoPride2().dyjfee.c_str())>0 && atof(GAMEDATA::getInstance()->getGameHongBaoPride2().fzfee.c_str())>0){
            HongbaoAnim2* ami = HongbaoAnim2::create();
            ami->initView(GAMEDATA::getInstance()->getGameHongBaoPride2().dyjfee, GAMEDATA::getInstance()->getGameHongBaoPride2().fzfee,1,false);
            addChild(ami,200);
        }else if(atof(GAMEDATA::getInstance()->getGameHongBaoPride2().dsjfee.c_str())>0&& atof(GAMEDATA::getInstance()->getGameHongBaoPride2().fzfee.c_str()) >0){
            HongbaoAnim2* ami = HongbaoAnim2::create();
            ami->initView(GAMEDATA::getInstance()->getGameHongBaoPride2().dsjfee, GAMEDATA::getInstance()->getGameHongBaoPride2().fzfee,2,false);
            addChild(ami,200);
        }else if(atof(GAMEDATA::getInstance()->getGameHongBaoPride2().dsjfee.c_str())>0){
            HongbaoAnim* ami = HongbaoAnim::create();
            ami->initView(GAMEDATA::getInstance()->getGameHongBaoPride2().dsjfee,2);
            addChild(ami,200);
            
        }else if(atof(GAMEDATA::getInstance()->getGameHongBaoPride2().dyjfee.c_str())>0){
            HongbaoAnim* ami = HongbaoAnim::create();
            ami->initView(GAMEDATA::getInstance()->getGameHongBaoPride2().dyjfee,1);
            addChild(ami,200);
            
        }else if(atof(GAMEDATA::getInstance()->getGameHongBaoPride2().fzfee.c_str())>0){
            HongbaoAnim* ami = HongbaoAnim::create();
            ami->initView(GAMEDATA::getInstance()->getGameHongBaoPride2().fzfee,0);
            addChild(ami,200);
        }
    }
    if(GAMEDATA::getInstance()->getShowFangZhuDismiss()){
        HintDialog* hint  = HintDialog::create(ChineseWord("dialog_text_19"), nullptr);
        addChild(hint,50);
        GAMEDATA::getInstance()->setShowFangZhuDismiss(false);
    }else if(GAMEDATA::getInstance()->getShowRoomDismiss()){
        HintDialog* hint  = HintDialog::create(ChineseWord("dialog_text_25"), nullptr);
        addChild(hint,50);
        GAMEDATA::getInstance()->setShowRoomDismiss(false);
    }
    if(GAMEDATA::getInstance()->getShowTurnTableState() == 2 && !GAMEDATA::getInstance()->getHasShowTurnTable()){
        DailyPride* pride = DailyPride::create();
        addChild(pride,10);
        GAMEDATA::getInstance()->setHasShowTurnTable(true);
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
    Director::getInstance()->getEventDispatcher()->removeEventListener(gongGaoInfoListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(networkBreakListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(hzOpenFriendRoomListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(hzEnterFriendRoomListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(hzLobbyConncetAgainListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(coreLoginRespListener);
    
}

void LobbyScene::addEventListener(){
    //进入房间回复
    enterRoomListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_ENTER_ROOM_RESP, [=](EventCustom* event){
        removeLoading();
        GAMEDATA::getInstance()->setMyGameModel(GameModel::FOURPLAYER);
        EnterRoomResp* respData = static_cast<EnterRoomResp*>(event->getUserData());
        EnterRoomResp newRespData = *respData;
        if (newRespData.result == "1"){
            GAMEDATA::getInstance()->setIsCompetitionState(false);
            GAMEDATA::getInstance()->setIsCompetitionQueue(false);
            Director::getInstance()->replaceScene(TransitionFade::create(1, MjGameScene::create()));
        } else if(newRespData.result == "2"){
            for(auto var : GAMEDATA::getInstance()->getRoomList().rooms){
                if(GAMEDATA::getInstance()->getCurrentSelectRoomId() == var.roomId){
#if(CC_TARGET_PLATFORM ==  CC_PLATFORM_ANDROID)
                    if(UserData::getInstance()->isWeixinPayOpen()){
                        GoldNotEnoughDialog* gold = GoldNotEnoughDialog::create(newRespData,GAMEDATA::getInstance()->getCurrentSelectRoomId());
                        addChild(gold,4);
                    }else{
                        HintDialog* hint = HintDialog::create(ChineseWord("dialog_text_16"),NULL);
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
    enterFriendRoomListener =  Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_ENTER_FRIEND_ROOM_RESP, [=](EventCustom* event){
        char* buf = static_cast<char*>(event->getUserData());
        std::string result = buf;
        removeLoading();
        if (result == "1"){
            GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
            GAMEDATA::getInstance()->setGameType(1);
            GAMEDATA::getInstance()->setFangZhuId("");
            Director::getInstance()->replaceScene(TransitionFade::create(1.0f, MjGameScene::create()));
        } else if(result == "2")
        {
            RoomFullDialog* doo = RoomFullDialog::create();
            addChild(doo,200);
        }
        else if(result == "3")
        {
#if(CC_TARGET_PLATFORM ==  CC_PLATFORM_ANDROID)
            if(UserData::getInstance()->isWeixinPayOpen()){
                FangkaNotEnoughDialog* charge = FangkaNotEnoughDialog::create();
                addChild(charge,200);
                GAMEDATA::getInstance()->setShowDialogType(-1);
            }else{
                HintDialog* hint = HintDialog::create(ChineseWord("dialog_text_17"),NULL);
                addChild(hint,200);
            }
#elif(CC_TARGET_PLATFORM ==  CC_PLATFORM_IOS||CC_TARGET_PLATFORM ==  CC_PLATFORM_MAC)
            FangkaNotEnoughDialog* charge = FangkaNotEnoughDialog::create();
            addChild(charge,200);
#endif
        }
        else if(result == "4"){
            RoomIdErrorDialog* idd = RoomIdErrorDialog::create();
            addChild(idd,200);
        }
    });
    
    hzEnterFriendRoomListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_HZ_ENTER_FRIEND_ROOM_RESP, [=](EventCustom* event){
        char* buf = static_cast<char*>(event->getUserData());
        std::string result = buf;
        removeLoading();
        if (result == "1"){
            GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
            GAMEDATA::getInstance()->setGameType(3);
            Director::getInstance()->replaceScene(TransitionFade::create(1.0f, MjGameScene::create()));
        } else if(result == "2")
        {
            RoomFullDialog* doo = RoomFullDialog::create();
            addChild(doo,200);
        }
        else if(result == "3")
        {
#if(CC_TARGET_PLATFORM ==  CC_PLATFORM_ANDROID)
            if(UserData::getInstance()->isWeixinPayOpen()){
                FangkaNotEnoughDialog* charge = FangkaNotEnoughDialog::create();
                addChild(charge,200);
                GAMEDATA::getInstance()->setShowDialogType(-1);
            }else{
                HintDialog* hint = HintDialog::create(ChineseWord("dialog_text_17"),NULL);
                addChild(hint,200);
            }
#elif(CC_TARGET_PLATFORM ==  CC_PLATFORM_IOS||CC_TARGET_PLATFORM ==  CC_PLATFORM_MAC)
            FangkaNotEnoughDialog* charge = FangkaNotEnoughDialog::create();
            addChild(charge,200);
#endif
        }
        else if(result == "4"){
            RoomIdErrorDialog* idd = RoomIdErrorDialog::create();
            addChild(idd,200);
        }
    });
    
    
    //好友开房上海麻将
    openFriendRoomListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_FRIEND_OPEN_ROOM_RESP, [=](EventCustom* event){
        GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
        GAMEDATA::getInstance()->setGameType(1);
        FriendOpenRoomRespData resp = GAMEDATA::getInstance()->getFriendOpenRoomResp();
        if(resp.result == 1){
            GAMEDATA::getInstance()->setFangZhuId(UserData::getInstance()->getPoxiaoId());
            Director::getInstance()->replaceScene(TransitionFade::create(1, MjGameScene::create()));
        }else if(resp.result == 2){
#if(CC_TARGET_PLATFORM ==  CC_PLATFORM_ANDROID)
            if(UserData::getInstance()->isWeixinPayOpen()){
                FangkaNotEnoughDialog* charge = FangkaNotEnoughDialog::create();
                addChild(charge,14);
                GAMEDATA::getInstance()->setShowDialogType(-1);
            }else{
                HintDialog* hint = HintDialog::create(ChineseWord("dialog_text_17"),NULL);
                addChild(hint,14);
            }
#elif(CC_TARGET_PLATFORM ==  CC_PLATFORM_IOS||CC_TARGET_PLATFORM ==  CC_PLATFORM_MAC)
            FangkaNotEnoughDialog* charge = FangkaNotEnoughDialog::create();
            addChild(charge,14);
#endif
        }
    });
    
    //好友开房红中麻将
    hzOpenFriendRoomListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_ENTER_FRIEND_ROOM_HONGZHONG_RESP, [=](EventCustom* event){
        GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
        GAMEDATA::getInstance()->setGameType(3);
        FriendOpenRoomRespData resp = GAMEDATA::getInstance()->getFriendOpenRoomResp();
        if(resp.result == 1){
            GAMEDATA::getInstance()->setFangZhuId(UserData::getInstance()->getPoxiaoId());
            Director::getInstance()->replaceScene(TransitionFade::create(1, MjGameScene::create()));
        }else if(resp.result == 2){
#if(CC_TARGET_PLATFORM ==  CC_PLATFORM_ANDROID)
            if(UserData::getInstance()->isWeixinPayOpen()){
                FangkaNotEnoughDialog* charge = FangkaNotEnoughDialog::create();
                addChild(charge,14);
                GAMEDATA::getInstance()->setShowDialogType(-1);
            }else{
                HintDialog* hint = HintDialog::create(ChineseWord("dialog_text_17"),NULL);
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
        GAMEDATA::getInstance()->setGameType(1);
        Director::getInstance()->replaceScene(MjGameScene::create());
    });
    
    //断线续玩HZ
    hzLobbyConncetAgainListener=  Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_HZ_PLAYER_CONNECT_AGAIN, [=](EventCustom* event){
        GAMEDATA::getInstance()->setIsRecover(true);
        GAMEDATA::getInstance()->setGameType(3);
        Director::getInstance()->replaceScene(MjGameScene::create());
    });
    
    //登录地址变更
    loginReplaceListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_PLAYER_REPLACE_LOGIN, [=](EventCustom* event){
        HintDialog* hin = HintDialog::create(ChineseWord("dialog_text_20"),[=](Ref* ref){
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
            da->showText(ChineseWord("dialog_text_21"));
        }else{
            da->showText(ChineseWord("dialog_text_22"));
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
        FriendRoom* friendroom = FriendRoom::create();
        addChild(friendroom,10);
    });
    
    //进入房间询问
    enterRoomAskListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_LOBBY_ASK_ENTER_ROOM, [=](EventCustom* event){
        removeLoading();
        MahjongNumberKeypads* keypads = MahjongNumberKeypads::create();
        addChild(keypads,20);
    });
    
    //跑马灯
    scrollTetxListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_SCROLL_TEXT, [=](EventCustom* event){
        std::string msg = static_cast<char*>(event->getUserData());
        std::vector<std::string> showMsg = StringUtil::split(msg, "#$");
        if(nullptr != ((ScrollTextEx*)getChildByTag(9980))){
            ((ScrollTextEx*)getChildByTag(9980))->setScrollStrs(showMsg);
        }
        schedule([=](float dt){
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getScrollTextCommand());
        }, 0, 0, 300,"ask_tui_guang");
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
            nod->setContentImage(newData.imageUrl,newData.imageUrl2,newData.showTime);
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
        if(NULL != getChildByTag(904))
            getChildByTag(904)->setVisible(UserData::getInstance()->isWeixinPayOpen());
        if(NULL != getChildByTag(905))
            getChildByTag(905)->setVisible(UserData::getInstance()->isWeixinPayOpen());
        if(NULL != getChildByTag(1980)){
            getChildByTag(1980)->setVisible(UserData::getInstance()->isWeixinPayOpen());
            if(GAMEDATA::getInstance()->getShowTurnTableState() == 0){
                getChildByTag(1980)->setVisible(false);
            }
        }
        if(NULL != haufeiNum)
            haufeiNum->setVisible(UserData::getInstance()->isWeixinPayOpen());
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
        }else{
            firstMenu->setVisible(UserData::getInstance()->isWeixinPayOpen());
        }
#endif
    });
    
    showLoobyLoadingLayer = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_LOBBY_SHOW_LOADING_LAYER, [=](EventCustom* event){
        showLoading();
    });
    //游戏复盘
    gameFupanListener  = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_GAME_FU_PAN_NOTIFY, [=](EventCustom* event){
        if(GAMEDATA::getInstance()->getPlaybackInfo().result == 1){
            GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
            if(GAMEDATA::getInstance()->getPlaybackInfo().gameType == "0"){
                GAMEDATA::getInstance()->setGameType(2);
                Director::getInstance()->replaceScene(MjGameScene::create());
            }else{
                GAMEDATA::getInstance()->setGameType(4);
                Director::getInstance()->replaceScene(MjGameScene::create());
            }
        }
    });
    gameFupanListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_GET_TUI_GUANG_PRIDE, [=](EventCustom* event){
        std::string buf = static_cast<char*>(event->getUserData());
        ShopHintDialog* da = ShopHintDialog::create();
        if(buf == "1"){
            da->showText(ChineseWord("dialog_text_23"));
            ParticleUtil* par = ParticleUtil::create(MyParticleType::goldOnly);
            addChild(par,10);
            //刷新用户信息
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getTuiGuangCommand());
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getPlayerInfoCommand());
        }else{
            da->showText(ChineseWord("dialog_text_24"));
        }
        addChild(da,10);
    });
    
    
    //获取房间列表
    roomListRespListener = EventListenerCustom::create(MSG_ROOM_LIST_RESP, [=](EventCustom* event){
        RoomListData* data = static_cast<RoomListData*>(event->getUserData());
        RoomListData newData = *data;
        if(!isShowRoomlist){
            if(newData.matchList.size()>0 && UserData::getInstance()->isWeixinPayOpen()){
                auto competitionImg = MenuItemImage::create("mjlobby/com_btn_1.png", "mjlobby/com_btn_2.png", CC_CALLBACK_0(LobbyScene:: showCompetitionLayer,this));
                auto comMenu = Menu::create(competitionImg,NULL);
                comMenu->setPosition(1025,290);
                addChild(comMenu);
            }
            if(newData.rooms.size()>0 && getChildByTag(1298) == NULL){
                auto jinImg = MenuItemImage::create("mjlobby/gold_room_btn_1.png","mjlobby/gold_room_btn_1.png",CC_CALLBACK_0(LobbyScene:: spreadGoldRoom,this));
                auto jinMenu =  Menu ::create(jinImg,NULL);
                jinMenu->setPosition(1115,180);
                jinMenu->setTag(1297);
                addChild(jinMenu);
                GoldRoomPlate* plate = GoldRoomPlate::create(newData);
                plate->setTag(1298);
                plate->setVisible(false);
                addChild(plate,2);
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
                //支付审核
                jinMenu->setVisible(UserData::getInstance()->isWeixinPayOpen());
#endif
            }
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(roomListRespListener, 1);
    
    
    gongGaoInfoListener = EventListenerCustom::create(MSG_GET_WAN_JIA_GONG_GAO, [=](EventCustom* event){
        if(getChildByTag(1209)!=NULL){
            getChildByTag(1209)->removeFromParent();
        }
        GameGongGao* gonggaoData = static_cast<GameGongGao*>(event->getUserData());
        GameGongGaoLayer* gonggao = GameGongGaoLayer::create(*gonggaoData);
        addChild(gonggao,5);
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(gongGaoInfoListener, 1);
    
    
    networkBreakListener = EventListenerCustom::create(MSG_NETWORK_BREAK_INFO, [=](EventCustom* event){
        if(NetworkManage::getInstance()->reConnectSocket()){
            int  delayTime = 1.0f;
            schedule([=](float dt){
                if(UserData::getInstance()->getWxOpenId() ==  "unknow"){
                    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getVistorLoginAgain(UserData::getInstance()->getUserName(), UserData::getInstance()->getPassword()));
                }else{
                    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getThirdLoginCommand(UserData::getInstance()->getWxOpenId(), UserData::getInstance()->getWxUnionid(),UserData::getInstance()->getPicture(), StringUtils::format("%d",UserData::getInstance()->getGender()), UserData::getInstance()->getNickName(), UserData::getInstance()->getHsman(), UserData::getInstance()->getHstype(), UserData::getInstance()->getImsi(),UserData::getInstance()->getImei(),UserData::getInstance()->getAppVer(),true));                }
            }, 0, 0, delayTime, "socket_reconnect2000");
            NetworkManage::getInstance()->startSocketBeat(CommandManage::getInstance()->getHeartCommmand());
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(networkBreakListener, 1);
    
    coreLoginRespListener = EventListenerCustom::create(MSG_LOGIN_RESP, [=](EventCustom* event){
        if(GAMEDATA::getInstance()->getShareHongBaoFriendState() == 1){
            if(GAMEDATA::getInstance()->getIsTurnTableShare()){
                GAMEDATA::getInstance()->setIsTurnTableShare(false);
                schedule([=](float dt){
                    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendTurntableShareCommand());
                },0,0,2,"share_1314");
            }else{
                GAMEDATA::getInstance()->setShareHongBaoFriendState(0);
                schedule([=](float dt){
                    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendGetHongbaoPride());
                },0,0,2,"share_1314");
            }
            
        }else if(GAMEDATA::getInstance()->getShareHongBaoFriendState() == 2){
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendGiveupHongbaoPride());
            GAMEDATA::getInstance()->setShareHongBaoFriendState(0);
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(coreLoginRespListener, 1);
    
    //点击事件
    auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
        switch (code)
        {
            case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
            {
                HintDialog* hit = HintDialog::create(ChineseWord("dialog_text_24"),[=](Ref* ref){
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




