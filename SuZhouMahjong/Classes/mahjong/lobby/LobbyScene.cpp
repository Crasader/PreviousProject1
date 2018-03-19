#include "mahjong/lobby/LobbyScene.h"
#include "mahjong/lobby/openroom/MahjongNumberKeypads.hpp"
#include "mahjong/lobby/openroom/dialog/RoomIdErrorDialog.hpp"
#include "mahjong/lobby/openroom/dialog/RoomFullDialog.hpp"
#include "mahjong/lobby/openroom/FriendOpenRoom.h"
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
#include "mahjong/lobby/share/ShareSelectLayer.hpp"
#include "mahjong/lobby/gongzhonghao/GongZhongHaoLayer.hpp"
#include "mahjong/lobby/collaborate/CollaborateDialog.hpp"
#include "mahjong/lobby/share/LaXinLayer.hpp"
#include "mahjong/lobby/agency/AgencyLayer.hpp"//代理开房管理界面
#include "mahjong/lobby/agency/AgencyResult.hpp"

bool LobbyScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    showDissolveDialog = false;
    initView();
    //add sprite to scene
    drawSceneTop();
    drawSceneMid();
    drawSceneBot();
    return true;
}


void LobbyScene::signUpdate(float dt){
    if(GAMEDATA::getInstance()->getAutoRoomId() != "" && GAMEDATA::getInstance()->getAutoRoomId().size() == 6){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getEnterRoomByIdCommand(GAMEDATA::getInstance()->getAutoRoomId()));
        GAMEDATA::getInstance()->setAutoRoomId("");
    }
    if(GAMEDATA::getInstance()->getShowDialogType() == 2){
        GoldNotEnoughDialog* gold = GoldNotEnoughDialog::create(GAMEDATA::getInstance()->getEnterRoomResp());
        addChild(gold,30);
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
    if(GAMEDATA::getInstance()->getShareHongBaoFriendState() == 1 && GAMEDATA::getInstance()->getIsTurnTableShare()){
        GAMEDATA::getInstance()->setIsTurnTableShare(false);
        GAMEDATA::getInstance()->setShareHongBaoFriendState(0);
        schedule([=](float dt){
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendTurntableShareCommand());
        },0,0,1,"share_1314");
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
    auto wawa = Sprite::create("shop/fangka_image.png");
    wawa->setScale(0.65);
    wawa->setPosition(1170,590);
    addChild(wawa);
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
    fangka_bg->setPosition(385, 687);
    addChild(fangka_bg);
    auto fangka_icon = Sprite::create("common/fangka_icon.png");
    fangka_icon->setPosition(325, 687);
    addChild(fangka_icon);
    fangkaNum = Label::createWithSystemFont(StringUtils::format("%0.1f",UserData::getInstance()->getFangkaNum()),"Arial",24);
    fangkaNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
    fangkaNum->setColor(Color3B(242,227,75));
    fangkaNum->setPosition(385, 687);
    addChild(fangkaNum);
    auto fangka_btn = MenuItemImage::create("mjlobby/plus_btn_1.png", "mjlobby/plus_btn_2.png", CC_CALLBACK_0(LobbyScene::chargeFangka, this));
    auto chargfangka = Menu::create(fangka_btn, NULL);
    chargfangka->setPosition(455, 687);
    addChild(chargfangka);
    
}

void LobbyScene::drawSceneMid(){
    
    auto sharefriend = MenuItemImage::create("mjlobby/hongbao_1.png", "mjlobby/hongbao_1.png",
                                             CC_CALLBACK_0(LobbyScene::showLaXinLayer, this));
    auto shareMenu = Menu::create(sharefriend, NULL);
    shareMenu->alignItemsHorizontallyWithPadding(15);
    shareMenu->setPosition(630, 535);
    shareMenu->setTag(1981);
    addChild(shareMenu);
    shareMenu->setVisible(false);
    if(UserData::getInstance()->getNeedShowYaoQingButton()&&UserData::getInstance()->isWeixinPayOpen()){
        shareMenu->setVisible(true);
    }
    
    auto jizhanItem = MenuItemImage::create("mjlobby/share_1.png", "mjlobby/share_1.png",
                                            CC_CALLBACK_0(LobbyScene::showRedWallet, this));
    auto jizhanMenu = Menu::create(jizhanItem, NULL);
    jizhanMenu->alignItemsHorizontallyWithPadding(15);
    
    jizhanMenu->setTag(1982);
    
    addChild(jizhanMenu);
    if(shareMenu->isVisible()){
        jizhanMenu->setPosition(630, 435);
    }else{
        jizhanMenu->setPosition(630, 535);
    }
    jizhanMenu->setVisible(false);
    if(UserData::getInstance()->getNeedShowJiZanButton()&&UserData::getInstance()->isWeixinPayOpen()){
        jizhanMenu->setVisible(true);
    }
    
    auto huodong = MenuItemImage::create("mjlobby/red_wallet_1.png","mjlobby/red_wallet_2.png",CC_CALLBACK_0(LobbyScene::showHotActivity, this));
    auto mymenu = Menu::create(huodong,NULL);
    mymenu->setPosition(630,335);
    mymenu->setTag(1983);
    
    addChild(mymenu);
    if(shareMenu->isVisible()&&jizhanMenu->isVisible()){
        mymenu->setPosition(630, 335);
    }else if((shareMenu->isVisible()&&!jizhanMenu->isVisible())||(!shareMenu->isVisible()&&jizhanMenu->isVisible())){
        mymenu->setPosition(630, 435);
    }else{
        mymenu->setPosition(630, 535);
    }
    mymenu->setVisible(false);
    if(UserData::getInstance()->isWeixinPayOpen()&&GAMEDATA::getInstance()->getShowTurnTableState() != 0){
        mymenu->setVisible(true);
    }
    
    if(GAMEDATA::getInstance()->getBottomText() != "" && UserData::getInstance()->isWeixinPayOpen()&&shareMenu->isVisible()){
        auto textbg = Sprite::create("mjlobby/ti_shi_2.png");
        textbg->setPosition(730,570);
        addChild(textbg);
        auto text = Label::createWithSystemFont("分享有钱拿!", "arial", 20);
        text->setAnchorPoint(Point::ANCHOR_MIDDLE);
        text->setColor(Color3B(255,247,217));
        text->setPosition(90,30);
        textbg->addChild(text);
        textbg->runAction(Repeat::create(Sequence::create(MoveTo::create(0.92f,Point(730,580)),MoveTo::create(0.92f,Point(730,570)),NULL), CC_REPEAT_FOREVER));
    }
    
    //跑马灯
   
    if(UserData::getInstance()->isWeixinPayOpen()){
        ScrollTextEx* scroll = ScrollTextEx::create();
        scroll->setAutoScroll(true);
        scroll->setTag(9980);
        scroll->setPosition(600,620);
        addChild(scroll,2);
    }
    
    RankLayer* rlayer = RankLayer::create(GAMEDATA::getInstance()->getLobbyPaiHangData());
    addChild(rlayer);
    
    
    auto btn_open = MenuItemImage::create("mjlobby/open_room_btn_1.png", "mjlobby/open_room_btn_2.png", CC_CALLBACK_0(LobbyScene::openRoom, this));
    auto btn_enter = MenuItemImage::create("mjlobby/enter_room_btn_1.png", "mjlobby/enter_room_btn_2.png", CC_CALLBACK_0(LobbyScene::joinRoom, this));
    auto gameMenu = Menu::create(btn_open,btn_enter, NULL);
    gameMenu->alignItemsVerticallyWithPadding(2);
    gameMenu->setPosition(1025, 425);
    addChild(gameMenu);
    if(atoi(GAMEDATA::getInstance()->getPrivateGameNum().c_str())>0||GAMEDATA::getInstance()->getFangZhuId() == UserData::getInstance()->getPoxiaoId()){
        Sprite* frame = Sprite::create("mjlobby/go_to_friend_room_1.png");
        btn_open->setNormalImage(frame);
        Sprite* frame2 = Sprite::create("mjlobby/go_to_friend_room_2.png");
        btn_open->setSelectedImage(frame2);
    }
    RoomListData newData = GAMEDATA::getInstance()->getRoomList();
}

void LobbyScene::drawSceneBot(){
    auto bottomBg = Sprite::create("mjlobby/open_room_bg_bot.png");
    bottomBg->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    bottomBg->setScale(1.1f);
    bottomBg->setPosition(640,0);
    addChild(bottomBg);
    
    
    auto btn_1 = MenuItemImage::create("mjlobby/sm_btn_1.png", "mjlobby/sm_btn_2.png", CC_CALLBACK_0(LobbyScene::showShiMing, this));
    auto gameMenu1 = Menu::create(btn_1, NULL);
    gameMenu1->setPosition(240, 50);
    addChild(gameMenu1);
    
    auto btn_2 = MenuItemImage::create("mjlobby/hezuo_1.png", "mjlobby/hezuo_2.png", CC_CALLBACK_0(LobbyScene::showTeamwork, this));
    auto gameMenu2 = Menu::create(btn_2, NULL);
    gameMenu2->setPosition(400, 50);
    addChild(gameMenu2);
    
    auto gongzh = MenuItemImage::create("mjlobby/gzh_btn1.png","mjlobby/gzh_btn2.png",CC_CALLBACK_0(LobbyScene::showGongZhongHao, this));
    auto mymenu2 = Menu::create(gongzh,NULL);
    mymenu2->setPosition(560,50);
    addChild(mymenu2);
    
    auto btn_bill = MenuItemImage::create("mjlobby/bill_btn_1.png", "mjlobby/bill_btn_1.png", CC_CALLBACK_0(LobbyScene::showPlayerBill, this));
    auto billMenu = Menu::create(btn_bill, NULL);
    
    billMenu->setPosition(720,50);
    addChild(billMenu);
    
    auto btn_3 = MenuItemImage::create("mjlobby/wan_jia_quan_1.png", "mjlobby/wan_jia_quan_2.png", CC_CALLBACK_0(LobbyScene::showWanJiaQun, this));
    auto gameMenu3 = Menu::create(btn_3, NULL);
    gameMenu3->alignItemsHorizontallyWithPadding(5);
    gameMenu3->setPosition(880, 50);
    addChild(gameMenu3);
    
    auto btn_setting = MenuItemImage::create("mjlobby/setting_btn_1.png", "mjlobby/setting_btn_1.png", CC_CALLBACK_0(LobbyScene::showGameSetting, this));
    auto settingMenu = Menu::create(btn_setting, NULL);
    settingMenu->setPosition(1040,50);
    addChild(settingMenu);
    
    if(!UserData::getInstance()->isWeixinPayOpen()){
        gameMenu1->setPosition(340, 50);
        gameMenu2->setVisible(false);
        mymenu2->setVisible(false);
        billMenu->setPosition(640,50);
        gameMenu3->setVisible(false);
        settingMenu->setPosition(940,50);
    }
    
    //显示公告小信息
    if(GAMEDATA::getInstance()->getBottomText() != ""&& UserData::getInstance()->isWeixinPayOpen()){
        auto textbg = Sprite::create("mjlobby/ti_shi_kuang.png");
        textbg->setPosition(862,107);
        addChild(textbg);
        auto text = Label::createWithSystemFont(GAMEDATA::getInstance()->getBottomText(), "arial", 20);
        text->setAnchorPoint(Point::ANCHOR_MIDDLE);
        text->setColor(Color3B(255,247,217));
        text->setPosition(220,40);
        textbg->addChild(text);
        textbg->runAction(Repeat::create(Sequence::create(MoveTo::create(0.9f,Point(862,117)),MoveTo::create(0.9f,Point(862,107)),NULL), CC_REPEAT_FOREVER));
    }
}

//刷新显示的用户信息
void LobbyScene::updateHeroInfo(){
    ((HeadImage*)getChildByTag(962))->updateImage();
    nickName->setString(UserData::getInstance()->getNickName());
    fangkaNum->setString(StringUtils::format("%0.1f",UserData::getInstance()->getFangkaNum()));
}

void LobbyScene::showLobbyAnim(){
    
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
    
    // 星星闪烁
    if(NULL != getChildByTag(1981) && getChildByTag(1981)->isVisible()){
        auto star1 = Sprite::create("mjlobby/star.png");
        star1->setPosition(615,550);
        star1->setOpacity(0);
        addChild(star1,1);
        star1->runAction(Repeat::create(Sequence::create(DelayTime::create(1),FadeTo::create(0.5, 255),FadeTo::create(0.5,0),DelayTime::create(11), NULL),CC_REPEAT_FOREVER));
        
        auto star2 = Sprite::create("mjlobby/star.png");
        star2->setPosition(610,525);
        star2->setOpacity(0);
        star2->setScale(0.5f);
        addChild(star2,1);
        star2->runAction(Repeat::create(Sequence::create(DelayTime::create(2),FadeTo::create(0.5, 255),FadeTo::create(0.5,0),DelayTime::create(10), NULL),CC_REPEAT_FOREVER));
        
        auto star3 = Sprite::create("mjlobby/star.png");
        star3->setPosition(675,550);
        star3->setOpacity(0);
        addChild(star3,1);
        star3->runAction(Repeat::create(Sequence::create(DelayTime::create(1),FadeTo::create(0.5, 255),FadeTo::create(0.5,0),DelayTime::create(11), NULL),CC_REPEAT_FOREVER));
        
        auto star4 = Sprite::create("mjlobby/star.png");
        star4->setPosition(615,550);
        star4->setOpacity(0);
        addChild(star4,1);
        star4->runAction(Repeat::create(Sequence::create(DelayTime::create(3),FadeTo::create(0.5, 255),FadeTo::create(0.5,0),DelayTime::create(9), NULL),CC_REPEAT_FOREVER));
    }
    
    if(NULL != getChildByTag(1982) && getChildByTag(1982)->isVisible()){
        auto star5 = Sprite::create("mjlobby/star.png");
        star5->setPosition(612,461);
        star5->setOpacity(0);
        addChild(star5,1);
        star5->runAction(Repeat::create(Sequence::create(DelayTime::create(4),FadeTo::create(0.5, 255),FadeTo::create(0.5,0),DelayTime::create(8), NULL),CC_REPEAT_FOREVER));
        
        auto star6 = Sprite::create("mjlobby/star.png");
        star6->setPosition(609,434);
        star6->setOpacity(0);
        star6->setScale(0.5f);
        addChild(star6,1);
        star6->runAction(Repeat::create(Sequence::create(DelayTime::create(6),FadeTo::create(0.5, 255),FadeTo::create(0.5,0),DelayTime::create(6), NULL),CC_REPEAT_FOREVER));
        
        auto star7 = Sprite::create("mjlobby/star.png");
        star7->setPosition(666,468);
        star7->setOpacity(0);
        addChild(star7,1);
        star7->runAction(Repeat::create(Sequence::create(DelayTime::create(5),FadeTo::create(0.5, 255),FadeTo::create(0.5,0),DelayTime::create(7), NULL),CC_REPEAT_FOREVER));
        
        auto star8 = Sprite::create("mjlobby/star.png");
        star8->setPosition(615,461);
        star8->setOpacity(0);
        addChild(star8,1);
        star8->runAction(Repeat::create(Sequence::create(DelayTime::create(7),FadeTo::create(0.5, 255),FadeTo::create(0.5,0),DelayTime::create(5), NULL),CC_REPEAT_FOREVER));
        
    }
    if(NULL != getChildByTag(1983) && getChildByTag(1983)->isVisible()){
        auto star5 = Sprite::create("mjlobby/star.png");
        star5->setPosition(612,361);
        star5->setOpacity(0);
        addChild(star5,1);
        star5->runAction(Repeat::create(Sequence::create(DelayTime::create(4),FadeTo::create(0.5, 255),FadeTo::create(0.5,0),DelayTime::create(8), NULL),CC_REPEAT_FOREVER));
        
        auto star6 = Sprite::create("mjlobby/star.png");
        star6->setPosition(609,334);
        star6->setOpacity(0);
        star6->setScale(0.5f);
        addChild(star6,1);
        star6->runAction(Repeat::create(Sequence::create(DelayTime::create(6),FadeTo::create(0.5, 255),FadeTo::create(0.5,0),DelayTime::create(6), NULL),CC_REPEAT_FOREVER));
        
        auto star7 = Sprite::create("mjlobby/star.png");
        star7->setPosition(666,368);
        star7->setOpacity(0);
        addChild(star7,1);
        star7->runAction(Repeat::create(Sequence::create(DelayTime::create(5),FadeTo::create(0.5, 255),FadeTo::create(0.5,0),DelayTime::create(7), NULL),CC_REPEAT_FOREVER));
        
        auto star8 = Sprite::create("mjlobby/star.png");
        star8->setPosition(615,361);
        star8->setOpacity(0);
        addChild(star8,1);
        star8->runAction(Repeat::create(Sequence::create(DelayTime::create(7),FadeTo::create(0.5, 255),FadeTo::create(0.5,0),DelayTime::create(5), NULL),CC_REPEAT_FOREVER));
        
    }
    
    
    //    auto btnlight1 = Sprite::create("mjlobby/light_btn_anim_1.png");
    //    btnlight1->setPosition(1023,534);
    //    addChild(btnlight1,1);
    //    btnlight1->runAction(Repeat::create(Sequence::create(DelayTime::create(1),CallFunc::create([=](){
    //        btnlight1->setVisible(true);
    //    }),Blink::create(1,1),CallFunc::create([=](){
    //        btnlight1->setVisible(false);
    //    }),DelayTime::create(6), NULL),CC_REPEAT_FOREVER));
    //
    //    auto btnlight2 = Sprite::create("mjlobby/light_btn_anim_1.png");
    //    btnlight2->setPosition(1024,409);
    //    addChild(btnlight2,1);
    //    btnlight2->runAction(Repeat::create(Sequence::create(DelayTime::create(2),CallFunc::create([=](){
    //        btnlight2->setVisible(true);
    //    }),Blink::create(1, 1),CallFunc::create([=](){
    //        btnlight2->setVisible(false);
    //    }),DelayTime::create(5), NULL),CC_REPEAT_FOREVER));
    //
    //    auto blink = Sprite::create("mjlobby/light_btn_anim.png");
    //    blink->setPosition(1031,530);
    //    addChild(blink,1);
    //    blink->setVisible(false);
    //    blink->runAction(Repeat::create(Sequence::create(DelayTime::create(3),CallFunc::create([=](){
    //        blink->setVisible(true);
    //        blink->setPosition(831,530);
    //    }),MoveTo::create(1.5,Point(1131,530)),CallFunc::create([=](){
    //        blink->setVisible(false);
    //    }),DelayTime::create(3.5), NULL),CC_REPEAT_FOREVER));
    //
    //    auto blink2 = Sprite::create("mjlobby/light_btn_anim.png");
    //    blink2->setPosition(1031,405);
    //    addChild(blink2,1);
    //    blink2->setVisible(false);
    //    blink2->runAction(Repeat::create(Sequence::create(DelayTime::create(4.5f),CallFunc::create([=](){
    //        blink2->setPosition(831,405);
    //        blink2->setVisible(true);
    //    }),MoveTo::create(1.5,Point(1131,405)),CallFunc::create([=](){
    //        blink2->setVisible(false);
    //    }),DelayTime::create(2), NULL),CC_REPEAT_FOREVER));
    
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

void LobbyScene::showLaXinLayer(){
    LaXinLayer* lay = LaXinLayer::create();
    addChild(lay,50);
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


void LobbyScene::showTeamwork(){
    CollaborateDialog* dia = CollaborateDialog::create();
    addChild(dia,5);
}

void LobbyScene::showPlayerBill(){
    Audio::getInstance()->playSoundClick();
    BillInfo* billInfoView = BillInfo::create();
    billInfoView->setTag(1117);
    billInfoView->setIsAgencyBill(false);
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
        ChargeFangka* charge = ChargeFangka::create();
        addChild(charge,3);
    }else{
        HintDialog* hint = HintDialog::create(ChineseWord("dialog_text_17"),NULL);
        addChild(hint,3);
    }
#elif(CC_TARGET_PLATFORM ==  CC_PLATFORM_IOS)
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
    Director::getInstance()->getEventDispatcher()->removeEventListener(openRoomAskListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(enterRoomAskListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(scrollTetxListener);
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
    Director::getInstance()->getEventDispatcher()->removeEventListener(cmOpenRoomListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(cmEnterFriendRoomListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(cmLobbyConncetAgainListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(fpOpenRoomListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(fpEnterFriendRoomListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(agencyRoomListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(agencyBillListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(agencyResultListener);
    
    
}

void LobbyScene::addEventListener(){
    //进入房间回复
    enterRoomListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_ENTER_ROOM_RESP, [=](EventCustom* event){
        removeLoading();
        GAMEDATA::getInstance()->setMyGameModel(GameModel::FOURPLAYER);
        EnterRoomResp* respData = static_cast<EnterRoomResp*>(event->getUserData());
        EnterRoomResp newRespData = *respData;
        if (newRespData.result == "1"){
            Director::getInstance()->replaceScene(TransitionFade::create(1, MjGameScene::create()));
        } else if(newRespData.result == "2"){
            GoldNotEnoughDialog* gold = GoldNotEnoughDialog::create(newRespData);
            addChild(gold,4);        }
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
        int result = GAMEDATA::getInstance()->getFriendOpenRoomResp().result;
        removeLoading();
        log("允许进入好友创建的房间 %d",result);
        if (result == 1){
            GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
            GAMEDATA::getInstance()->setGameType(1);
            GAMEDATA::getInstance()->setFangZhuId("");
            Director::getInstance()->replaceScene(TransitionFade::create(1.0f, MjGameScene::create()));
        } else if(result == 2)
        {
            RoomFullDialog* doo = RoomFullDialog::create();
            addChild(doo,200);
        }
        else if(result == 3)
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
        else if(result == 4){
            RoomIdErrorDialog* idd = RoomIdErrorDialog::create();
            addChild(idd,200);
        }
    });
    
    hzEnterFriendRoomListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_HZ_ENTER_FRIEND_ROOM_RESP, [=](EventCustom* event){
        int result = GAMEDATA::getInstance()->getFriendOpenRoomResp().result;
        removeLoading();
        if (result == 1){
            GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
            GAMEDATA::getInstance()->setGameType(3);
            Director::getInstance()->replaceScene(TransitionFade::create(1.0f, MjGameScene::create()));
        } else if(result == 2)
        {
            RoomFullDialog* doo = RoomFullDialog::create();
            addChild(doo,200);
        }
        else if(result == 3)
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
        else if(result == 4){
            RoomIdErrorDialog* idd = RoomIdErrorDialog::create();
            addChild(idd,200);
        }
    });
    
    //进入好友房间回复
    cmEnterFriendRoomListener =  Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_CM_ENTER_FRIEND_ROOM_RESP, [=](EventCustom* event){
        int result = GAMEDATA::getInstance()->getFriendOpenRoomResp().result;
        removeLoading();
        if (result == 1){
            GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
            GAMEDATA::getInstance()->setGameType(5);
            GAMEDATA::getInstance()->setFangZhuId("");
            Director::getInstance()->replaceScene(TransitionFade::create(1.0f, MjGameScene::create()));
        } else if(result == 2)
        {
            RoomFullDialog* doo = RoomFullDialog::create();
            addChild(doo,200);
        }
        else if(result == 3)
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
        else if(result == 4){
            RoomIdErrorDialog* idd = RoomIdErrorDialog::create();
            addChild(idd,200);
        }
    });
    
    
    
    //好友开房上海麻将
    openFriendRoomListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_FRIEND_OPEN_ROOM_RESP, [=](EventCustom* event){
        FriendOpenRoomRespData resp = GAMEDATA::getInstance()->getFriendOpenRoomResp();
        if(resp.agency){
            if(NULL != getChildByTag(1116)){
                ((AgencyLayer*)getChildByTag(1116))->updateData();
            }else{
                AgencyLayer* layer = AgencyLayer::create();
                layer->setTag(1116);
                addChild(layer,100);
            }
        }else{
            GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
            GAMEDATA::getInstance()->setGameType(1);
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
        }
    });
    
    agencyRoomListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_AGENCY_LIST, [=](EventCustom* event){
        if(NULL != getChildByTag(1116)){
            ((AgencyLayer*)getChildByTag(1116))->updateData();
        }else{
            AgencyLayer* layer = AgencyLayer::create();
            layer->setTag(1116);
            addChild(layer,100);
        }
    });
    
    //好友开房红中麻将
    hzOpenFriendRoomListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_ENTER_FRIEND_ROOM_HONGZHONG_RESP, [=](EventCustom* event){

        FriendOpenRoomRespData resp = GAMEDATA::getInstance()->getFriendOpenRoomResp();
        if(resp.agency){
            if(NULL != getChildByTag(1116)){
                ((AgencyLayer*)getChildByTag(1116))->updateData();
            }else{
                AgencyLayer* layer = AgencyLayer::create();
                layer->setTag(1116);
                addChild(layer,100);
            }
        }else{
            GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
            GAMEDATA::getInstance()->setGameType(3);
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
        }
    });
    
    
    //进入好友房间回复
    fpEnterFriendRoomListener =  Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_FP_ENTER_FRIEND_ROOM_RESP, [=](EventCustom* event){
        int result = GAMEDATA::getInstance()->getFriendOpenRoomResp().result;
        removeLoading();
        if (result == 1){
            GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
            GAMEDATA::getInstance()->setGameType(7);
            GAMEDATA::getInstance()->setFangZhuId("");
            Director::getInstance()->replaceScene(TransitionFade::create(1.0f, MjGameScene::create()));
        } else if(result == 2)
        {
            RoomFullDialog* doo = RoomFullDialog::create();
            addChild(doo,200);
        }
        else if(result == 3)
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
        else if(result == 4){
            RoomIdErrorDialog* idd = RoomIdErrorDialog::create();
            addChild(idd,200);
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
    
    //断线续玩CM
    cmLobbyConncetAgainListener=  Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_PLAYER_CM_CONNECT_AGAIN, [=](EventCustom* event){
        GAMEDATA::getInstance()->setIsRecover(true);
        GAMEDATA::getInstance()->setGameType(5);
        Director::getInstance()->replaceScene(MjGameScene::create());
    });
    
    //断线续玩CM
    cmLobbyConncetAgainListener=  Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_PLAYER_FP_CONNECT_AGAIN, [=](EventCustom* event){
        GAMEDATA::getInstance()->setIsRecover(true);
        GAMEDATA::getInstance()->setGameType(7);
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
    
    //开房询问
    openRoomAskListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_LOBBY_ASK_OPEN_ROOM, [=](EventCustom* event){
        removeLoading();
        FriendOpenRoom* friendroom = FriendOpenRoom::create();
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
    
    //游戏广告
    noticeUrlLitener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_WAN_JIA_GONG_GAO, [=](EventCustom* event){
        GameActivityData* data = static_cast<GameActivityData*>(event->getUserData());
        GameActivityData newData = *data;
        GAMEDATA::getInstance()->setGameActivityData(newData);
        if(!GAMEDATA::getInstance()->getHaveShowNotice() && UserData::getInstance()->isWeixinPayOpen()){
#if CC_TARGET_PLATFORM != CC_PLATFORM_MAC
            NoticeDialog* nod = NoticeDialog::create();
            nod->setContentImage(newData.imageUrl,newData.imageUrl2,newData.showTime);
            addChild(nod,100);
            GAMEDATA::getInstance()->setHaveShowNotice(true);
#endif
        }
    });
    
    upateLequanShopLitener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_UPDATE_LEQUAN_SHANG_CHEN_SHOW, [=](EventCustom* event){
        if(NULL != getChildByTag(901))
            getChildByTag(901)->setVisible(UserData::getInstance()->isWeixinPayOpen());
        if(NULL != getChildByTag(902))
            getChildByTag(902)->setVisible(UserData::getInstance()->isWeixinPayOpen());
        if(NULL != getChildByTag(903))
            getChildByTag(903)->setVisible(UserData::getInstance()->isWeixinPayOpen());
        if(NULL != getChildByTag(904))
            getChildByTag(904)->setVisible(UserData::getInstance()->isWeixinPayOpen());
        if(NULL != getChildByTag(905))
            getChildByTag(905)->setVisible(UserData::getInstance()->isWeixinPayOpen());
        if(NULL != getChildByTag(906))
            getChildByTag(906)->setVisible(UserData::getInstance()->isWeixinPayOpen());
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        if(NULL != getChildByTag(801))
            getChildByTag(801)->setVisible(UserData::getInstance()->isWeixinPayOpen());
        if(NULL != getChildByTag(802))
            getChildByTag(802)->setVisible(UserData::getInstance()->isWeixinPayOpen());
        if(NULL != getChildByTag(803))
            getChildByTag(803)->setVisible(UserData::getInstance()->isWeixinPayOpen());
        if(NULL != getChildByTag(1298)){
            getChildByTag(1298)->setVisible(UserData::getInstance()->isWeixinPayOpen());
        }
        if(NULL != getChildByTag(6656)){
            getChildByTag(6656)->setVisible(UserData::getInstance()->isWeixinPayOpen());
        }
#endif
        showLobbyAnim();
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
            }else if(GAMEDATA::getInstance()->getPlaybackInfo().gameType == "1"){
                GAMEDATA::getInstance()->setGameType(4);
                Director::getInstance()->replaceScene(MjGameScene::create());
            }else if(GAMEDATA::getInstance()->getPlaybackInfo().gameType == "3"){
                GAMEDATA::getInstance()->setGameType(6);
                Director::getInstance()->replaceScene(MjGameScene::create());
            }else if(GAMEDATA::getInstance()->getPlaybackInfo().gameType == "4"){
                GAMEDATA::getInstance()->setGameType(8);
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
    
    agencyBillListener  = EventListenerCustom::create(DAIKAI_FRIEND_GAME_BILL_REQUEST, [=](EventCustom* event){
        if(NULL != getChildByTag(1117)){
            getChildByTag(1117)->removeFromParent();
        }
        BillInfo* info = BillInfo::create();
        info->setTag(1117);
        info->setIsAgencyBill(true);
        addChild(info,300);
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(agencyBillListener, 1);
    //获取房间列表
    roomListRespListener = EventListenerCustom::create(MSG_ROOM_LIST_RESP, [=](EventCustom* event){
        
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
        //断线后直接重新连接
        if(NetworkManage::getInstance()->connect()){
            if(UserData::getInstance()->getWxOpenId() ==  "unknow"){
                NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getVistorLoginAgain(UserData::getInstance()->getUserName(), UserData::getInstance()->getPassword()));
            }else{
                NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getThirdLoginCommand(UserData::getInstance()->getWxOpenId(), UserData::getInstance()->getWxUnionid(),UserData::getInstance()->getPicture(), StringUtils::format("%d",UserData::getInstance()->getGender()), UserData::getInstance()->getNickName(), UserData::getInstance()->getHsman(), UserData::getInstance()->getHstype(), UserData::getInstance()->getImsi(),UserData::getInstance()->getImei(),UserData::getInstance()->getAppVer(),UserData::getInstance()->getLongitude(),UserData::getInstance()->getLatitude(),true));
            }
            NetworkManage::getInstance()->startSocketBeat(CommandManage::getInstance()->getHeartCommmand());
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(networkBreakListener, 1);
    
    coreLoginRespListener = EventListenerCustom::create(MSG_LOGIN_RESP, [=](EventCustom* event){
        if(GAMEDATA::getInstance()->getShareHongBaoFriendState() == 1){
            if(GAMEDATA::getInstance()->getIsTurnTableShare()){
                GAMEDATA::getInstance()->setIsTurnTableShare(false);
                GAMEDATA::getInstance()->setShareHongBaoFriendState(0);
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
    
    cmOpenRoomListener  = EventListenerCustom::create(MSG_CM_FRIEND_OPEN_ROOM_RESP, [=](EventCustom* event){
        

        FriendOpenRoomRespData resp = GAMEDATA::getInstance()->getFriendOpenRoomResp();
        if(resp.agency){
            if(NULL != getChildByTag(1116)){
                ((AgencyLayer*)getChildByTag(1116))->updateData();
            }else{
                AgencyLayer* layer = AgencyLayer::create();
                layer->setTag(1116);
                addChild(layer,100);
            }
        }else{
            GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
            GAMEDATA::getInstance()->setGameType(5);
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
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(cmOpenRoomListener, 1);
    
    agencyResultListener = EventListenerCustom::create(MSG_RESULT_MSG, [=](EventCustom* event){
        AgencyResult* re = AgencyResult::create();
        addChild(re,310);
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(agencyResultListener, 1);
    
    
    fpOpenRoomListener  = EventListenerCustom::create(MSG_FP_FRIEND_OPEN_ROOM_RESP, [=](EventCustom* event){
        
     
        FriendOpenRoomRespData resp = GAMEDATA::getInstance()->getFriendOpenRoomResp();
        if(resp.agency){
            if(NULL != getChildByTag(1116)){
                ((AgencyLayer*)getChildByTag(1116))->updateData();
            }else{
                AgencyLayer* layer = AgencyLayer::create();
                layer->setTag(1116);
                addChild(layer,100);
            }
        }else{
            GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
            GAMEDATA::getInstance()->setGameType(7);
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
        }
       
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(fpOpenRoomListener, 1);
    
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




