//
//  WanJiaQunLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/9.
//
//

#include "mahjong/share/ShareToFriendLayer.hpp"
#include "mahjong/utils/GameConfig.h"
#include "mahjong/state/GameData.h"
#include "payment/android/CallAndroidMethod.h"
#import "payment/ios/IOSBridge.h"
#include "server/NetworkManage.h"

bool ShareToFriendLayer::init(){
    if(!Layer::init()){
        return false;
    }
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
    
    
    auto  dialogBg = Sprite::create("shop/shop_bg.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(ShareToFriendLayer::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(1050, 615);
    addChild(closeMenu);
    
    auto titleIcon = Sprite::create("share/share_to_friend_title.png");
    titleIcon->setPosition(640, 660);
    addChild(titleIcon);
    
    auto tabbg = Sprite::create("share/ye_qian_bg.png");
    tabbg->setPosition(420,560);
    addChild(tabbg);
    
    auto qun_normal = MenuItemImage::create("share/ye_qian_btn_1.png", "share/ye_qian_btn_1.png");
    auto qun_selected = MenuItemImage::create("share/ye_qian_btn_2.png", "share/ye_qian_btn_2.png");
    qunToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(ShareToFriendLayer::showWanJiaQun, this), qun_normal, qun_selected, NULL);
    
    auto fangka_normal = MenuItemImage::create("share/ye_qian_btn_1.png", "share/ye_qian_btn_1.png");
    auto fangka_selected = MenuItemImage::create("share/ye_qian_btn_2.png", "share/ye_qian_btn_2.png");
    fangkaToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(ShareToFriendLayer::showFangkaDai, this), fangka_normal, fangka_selected, NULL);
    
    auto menu = Menu::create(qunToggle, fangkaToggle, NULL);
    menu->alignItemsHorizontallyWithPadding(0);
    menu->setPosition(420,560);
    addChild(menu,1);
    
    fenxiang =  Sprite::create("share/fen_xiang_text_1.png");
    fenxiang->setPosition(310, 560);
    addChild(fenxiang,2);
    
    lingqu =  Sprite::create("share/ke_lin_qu_text_1.png");
    lingqu->setPosition(520, 560);
    addChild(lingqu,2);
    
    qunToggle->setSelectedIndex(0);
    fangkaToggle->setSelectedIndex(1);
    
    shareLayer =  Layer::create();
    addChild(shareLayer);
    
    //3个展示框
    auto box1 = Sprite::create("share/share_box_bg.png");
    box1->setPosition(Point(360,360));
    shareLayer->addChild(box1);
    
    auto boxTitle1 = Sprite::create("share/box_title_1.png");
    boxTitle1->setPosition(Point(360,480));
    shareLayer->addChild(boxTitle1);
    
    auto boxText1 = Sprite::create("share/box_text_1.png");
    boxText1->setPosition(Point(360,435));
    shareLayer->addChild(boxText1);
    
    auto boxImage1 = Sprite::create("share/box_image_1.png");
    boxImage1->setPosition(Point(360,330));
    shareLayer->addChild(boxImage1);
    
    auto box2 = Sprite::create("share/share_box_bg.png");
    box2->setPosition(Point(640,360));
    shareLayer->addChild(box2);
    
    auto boxTitle2 = Sprite::create("share/box_title_2.png");
    boxTitle2->setPosition(Point(640,480));
    shareLayer->addChild(boxTitle2);
    
    auto boxText2 = Sprite::create("share/box_text_2.png");
    boxText2->setPosition(Point(640,435));
    shareLayer->addChild(boxText2);
    
    auto boxImage2 = Sprite::create("share/box_image_2.png");
    boxImage2->setPosition(Point(640,330));
    shareLayer->addChild(boxImage2);
    
    auto box3 = Sprite::create("share/share_box_bg.png");
    box3->setPosition(Point(920,360));
    shareLayer->addChild(box3);
    
    auto boxTitle3 = Sprite::create("share/box_title_3.png");
    boxTitle3->setPosition(Point(920,480));
    shareLayer->addChild(boxTitle3);
    
    auto boxText3 = Sprite::create("share/box_text_3.png");
    boxText3->setPosition(Point(920,435));
    shareLayer->addChild(boxText3);
    
    auto boxImage3 = Sprite::create("share/box_image_3.png");
    boxImage3->setPosition(Point(920,330));
    shareLayer->addChild(boxImage3);
    
    auto boxText4 = Sprite::create("share/box_text_huode.png");
    boxText4->setPosition(Point(920,250));
    shareLayer->addChild(boxText4);
    
    Label* fangNum1 = Label::createWithSystemFont("0", "Arial", 20);
    fangNum1->setTag(1001);
    fangNum1->setColor(Color3B(220,180,60));
    fangNum1->setAnchorPoint(Point::ANCHOR_MIDDLE);
    fangNum1->setPosition(870,250);
    shareLayer->addChild(fangNum1);
    
    Label* goldNum1 = Label::createWithSystemFont("0", "Arial", 20);
    goldNum1->setTag(1002);
    goldNum1->setColor(Color3B(220,180,60));
    goldNum1->setAnchorPoint(Point::ANCHOR_MIDDLE);
    goldNum1->setPosition(972,250);
    shareLayer->addChild(goldNum1);
    
    auto shareText = Sprite::create("share/share_text.png");
    shareText->setPosition(Point(640,190));
    shareLayer->addChild(shareText);
    
    
    
    auto shareImage = MenuItemImage::create("share/share_btn_1.png","share/share_btn_2.png",
                                           CC_CALLBACK_0(ShareToFriendLayer::doFaHongBaoPerson, this));
    auto friendImage = MenuItemImage::create("share/friend_btn_1.png","share/friend_btn_2.png",
                                           CC_CALLBACK_0(ShareToFriendLayer::doFaHongBaoFriend, this));
    
    Menu* myMneu = Menu::create(shareImage,friendImage,NULL);
    myMneu->setPosition(640,125);
    myMneu->alignItemsHorizontallyWithPadding(50);
    shareLayer->addChild(myMneu);
    
    recordLayer =  Layer::create();
    recordLayer->setVisible(false);
    addChild(recordLayer);
    
    auto linQuBox = Sprite::create("share/lin_qu_box_bg.png");
    linQuBox->setPosition(640,410);
    recordLayer->addChild(linQuBox);
    
    auto linquText1 = Sprite::create("share/lin_qu_text_1.png");
    linquText1->setPosition(640,485);
    recordLayer->addChild(linquText1);
    
    auto diamondBG = Sprite::create("shop/gold_bg_light.png");
    diamondBG->setPosition(400,400);
    recordLayer->addChild(diamondBG);
    
    auto diamond = Sprite::create("shop/fangka_image.png");
    diamond->setPosition(400,400);
    recordLayer->addChild(diamond);
    
    LabelAtlas* fangNum = LabelAtlas::create(StringUtils::format("%d",0), "result/fan_num.png", 17, 26, '0');
    fangNum->setTag(2001);
    fangNum->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    fangNum->setPosition(370,335);
    recordLayer->addChild(fangNum);

    
    auto zuanshi = Sprite::create("shop/fangka_2.png");
    zuanshi->setPosition(410,335);
    recordLayer->addChild(zuanshi);
    
    auto plus1= Sprite::create("shop/plus.png");
    plus1->setPosition(510,400);
    recordLayer->addChild(plus1);
    
    auto goldBg = Sprite::create("shop/gold_bg_light.png");
    goldBg->setPosition(645,400);
    recordLayer->addChild(goldBg);
    
    auto goldIcon = Sprite::create("shop/gold_icon_1.png");
    goldIcon->setPosition(645,400);
    recordLayer->addChild(goldIcon);
    
    auto goldNum = LabelAtlas::create(StringUtils::format("%d",0),"shop/prop_num.png",21,28,'0');
    goldNum->setTag(2002);
    goldNum->setPosition(665,335);
    goldNum->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    recordLayer->addChild(goldNum);
    
    auto jinbi = Sprite::create("shop/gold_text.png");
    jinbi->setPosition(705,335);
    recordLayer->addChild(jinbi);

    
    auto recordBox = Sprite::create("share/record_box_bg.png");
    recordBox->setPosition(640,220);
    recordLayer->addChild(recordBox);
    
    auto linquText2 = Sprite::create("share/lin_qu_text_2.png");
    linquText2->setPosition(640,255);
    recordLayer->addChild(linquText2);
    
    auto content1 = Sprite::create("share/box2_content_1.png");
    content1->setPosition(640,130);
    recordLayer->addChild(content1);
    
    auto content2 = Sprite::create("share/box2_content_2.png");
    content2->setPosition(640,200);
    recordLayer->addChild(content2);
    
    auto fangkaNum2 = LabelAtlas::create(StringUtils::format("%d",0),"shop/prop_num.png",21,28,'0');
    fangkaNum2->setTag(3001);
    fangkaNum2->setPosition(520,200);
    fangkaNum2->setAnchorPoint(Point::ANCHOR_MIDDLE);
    recordLayer->addChild(fangkaNum2);
    
    auto goldNum2 = LabelAtlas::create(StringUtils::format("%d",0),"shop/prop_num.png",21,28,'0');
    goldNum2->setTag(3002);
    goldNum2->setPosition(780,200);
    goldNum2->setAnchorPoint(Point::ANCHOR_MIDDLE);
    recordLayer->addChild(goldNum2);
    
    auto getmypirde = MenuItemImage::create("share/linqu_btn_1.png","share/linqu_btn_2.png",
                                            CC_CALLBACK_0(ShareToFriendLayer::getTuiGuangPride, this));
    
    Menu* myPrideMneu = Menu::create(getmypirde,NULL);
    myPrideMneu->setPosition(900,410);
    recordLayer->addChild(myPrideMneu);

    
    schedule(schedule_selector(ShareToFriendLayer::updateUi), 1, CC_REPEAT_FOREVER, 0);
    
    return true;
}


void ShareToFriendLayer::closeView(){
    removeFromParent();
}

void ShareToFriendLayer::showWanJiaQun(Ref* ref){
    qunToggle->setSelectedIndex(0);
    fangkaToggle->setSelectedIndex(1);
    shareLayer->setVisible(true);
    recordLayer->setVisible(false);
    fenxiang->setTexture("share/fen_xiang_text_1.png");
    lingqu->setTexture("share/ke_lin_qu_text_2.png");
}


void ShareToFriendLayer::showFangkaDai(Ref* ref){
    qunToggle->setSelectedIndex(1);
    fangkaToggle->setSelectedIndex(0);
    shareLayer->setVisible(false);
    recordLayer->setVisible(true);
    fenxiang->setTexture("share/fen_xiang_text_2.png");
    lingqu->setTexture("share/ke_lin_qu_text_1.png");
}

void ShareToFriendLayer::doFaHongBaoPerson(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string url = StringUtils::format("%s?hbcode=%s",WECHAT_SHARE_HONGBAO_URL,GAMEDATA::getInstance()->getRedWalletRespData().hbcode.c_str());
    CallAndroidMethod::getInstance()->shareToWeChat(url,SHARE_TEXT_1, SHARE_TEXT_2,false);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    std::string url = StringUtils::format("%s?hbcode=%s",WECHAT_SHARE_HONGBAO_URL,GAMEDATA::getInstance()->getRedWalletRespData().hbcode.c_str());
    IOSBridge::getInstance()->doWechatShareWeb(url,SHARE_TEXT_1, SHARE_TEXT_2,0);
#endif
}

void ShareToFriendLayer:: doFaHongBaoFriend(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string url = StringUtils::format("%s?hbcode=%s",WECHAT_SHARE_HONGBAO_URL,GAMEDATA::getInstance()->getRedWalletRespData().hbcode.c_str());
    CallAndroidMethod::getInstance()->shareToWeChat(url,SHARE_TEXT_1, SHARE_TEXT_2,true);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    std::string url = StringUtils::format("%s?hbcode=%s",WECHAT_SHARE_HONGBAO_URL,GAMEDATA::getInstance()->getRedWalletRespData().hbcode.c_str());
    IOSBridge::getInstance()->doWechatShareWeb(url, SHARE_TEXT_1, SHARE_TEXT_2,1);
#endif
}

void ShareToFriendLayer::getTuiGuangPride(){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getTuiGuangPrideCommand());
}

void ShareToFriendLayer::updateUi(float dt){
    if(shareLayer->isVisible()){
        if(NULL!=shareLayer->getChildByTag(1001)){
            ((Label*)shareLayer->getChildByTag(1001))->setString(StringUtils::format("%d",GAMEDATA::getInstance()->getTuiGuangReward().fangka));
        }
        if(NULL!=shareLayer->getChildByTag(1002)){
            ((Label*)shareLayer->getChildByTag(1002))->setString(StringUtils::format("%d",GAMEDATA::getInstance()->getTuiGuangReward().gold/10000));
        }
    }
    if(recordLayer->isVisible()){
        if(NULL!=recordLayer->getChildByTag(2001)){
            ((LabelAtlas*)recordLayer->getChildByTag(2001))->setString(StringUtils::format("%d",GAMEDATA::getInstance()->getTuiGuangPride().fangka));
        }
        if(NULL!=recordLayer->getChildByTag(2002)){
            ((LabelAtlas*)recordLayer->getChildByTag(2002))->setString(StringUtils::format("%d",GAMEDATA::getInstance()->getTuiGuangPride().gold));
        }
        if(NULL!=recordLayer->getChildByTag(3001)){
            ((LabelAtlas*)recordLayer->getChildByTag(3001))->setString(StringUtils::format("%d",GAMEDATA::getInstance()->getTuiGuangRecord().fangka));
        }
        if(NULL!=recordLayer->getChildByTag(3002)){
            ((LabelAtlas*)recordLayer->getChildByTag(3002))->setString(StringUtils::format("%d",GAMEDATA::getInstance()->getTuiGuangRecord().gold));
        }

    }

}
