//
//  WanJiaQunLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/9.
//
//

#include "mahjong/lobby/share/ShareActivityLayer.hpp"
#include "mahjong/GameConfig.h"
#include "mahjong/common/state/GameData.h"
#include "wechat/android/CallAndroidMethod.h"
#include "wechat/ios/CallIOSMethod.h"
#include "server/NetworkManage.h"
#include "mahjong/common/widget/HeadImage.hpp"

bool ShareActivityLayer::init(){
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
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(ShareActivityLayer::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(1050, 615);
    addChild(closeMenu);
    
    auto titleIcon = Sprite::create("share/activity_titile.png");
    titleIcon->setPosition(640, 645);
    addChild(titleIcon);
    
    auto titleNum = LabelAtlas::create(GAMEDATA::getInstance()->getShareActivityData().num,"share/zan_number.png",36,55,'0');
    titleNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
    titleNum->setPosition(615,585);
    addChild(titleNum);
    
    auto keng = Sprite::create("share/keng.png");
    keng->setPosition(640,360);
    addChild(keng);
    
    auto zanTetx = Sprite::create("share/zan_text.png");
    zanTetx->setPosition(640,585);
    addChild(zanTetx);
    
    
    auto hbback = Sprite::create("share/activity_hb.png");
    hbback->setPosition(410,360);
    addChild(hbback);
    
    auto hbNum = LabelAtlas::create(GAMEDATA::getInstance()->getShareActivityData().prize, "share/hb_number.png", 36, 57, '0');
    hbNum->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    hbNum->setPosition(390,310);
    addChild(hbNum);
    
    auto yuan = Sprite::create("share/yuna_hb.png");
    yuan->setPosition(450,310);
    addChild(yuan);
    
    auto guanwei = Label::createWithSystemFont("加官方客服微信号领取红包奖励","arial",30);
    guanwei->setPosition(815,410);
    addChild(guanwei);
    
    auto text = Label::createWithSystemFont(StringUtils::format("分享并集%s个赞可获得",GAMEDATA::getInstance()->getShareActivityData().num.c_str()), "arial", 26);
    text->setPosition(410,215);
    text->setColor(Color3B::BLACK);
    addChild(text);
    
    auto inputbg = Sprite::create("share/support_bg.png");
    inputbg->setPosition(815,315);
    addChild(inputbg);
    
    
    auto kefu = Label::createWithSystemFont(GAMEDATA::getInstance()->getShareActivityData().wx,"arial",35);
    kefu->setAnchorPoint(Point::ANCHOR_MIDDLE);
    kefu->setColor(Color3B(182,204,155));
    kefu->setPosition(735,315);
    addChild(kefu);
    
    auto copyWxImg  = MenuItemImage::create("share/copy_1.png", "share/copy_2.png", CC_CALLBACK_0(ShareActivityLayer::copyText,this));
    auto copyMenu = Menu::create(copyWxImg,NULL);
    copyMenu->setPosition(945,315);
    addChild(copyMenu);
    
    
    
    auto shareBtnImg = MenuItemImage::create("share/fx_pyq_1.png", "share/fx_pyq_2.png", CC_CALLBACK_0(ShareActivityLayer::shareToFriend,this));
    auto shareMenu = Menu::create(shareBtnImg,NULL);
    shareMenu->setPosition(640,125);
    addChild(shareMenu);
    
    return true;
}


void ShareActivityLayer::closeView(){
    removeFromParent();
}

void ShareActivityLayer::shareToFriend(){
    auto hbLayer = Layer::create();
    
    auto hongbaobg = Sprite::create("result/result_bg.jpg");
    hongbaobg->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    hongbaobg->setPosition(0,0);
    hbLayer->addChild(hongbaobg);
    
    auto hong = Sprite::create("share/new_hong_bao.png");
    hong->setPosition(335,360);
    hbLayer->addChild(hong);
    
    auto bao = Label::createWithSystemFont("小白相话费红包","arial",26);
    bao->setColor(Color3B(246,226,176));
    bao->setAnchorPoint(Point::ANCHOR_MIDDLE);
    bao->setPosition(335,600);
    hbLayer->addChild(bao);
    
    auto headImage = HeadImage::createByImage(UserData::getInstance()->getPicture(),Size(140,140));
    headImage->setPosition(335, 480);
    hbLayer->addChild(headImage, 10);
    
    auto nick = Label::createWithSystemFont(UserData::getInstance()->getNickName(),"arial",26);
    nick->setColor(Color3B::BLACK);
    nick->setPosition(330,384);
    hbLayer->addChild(nick);
    
    auto pride = Label::createWithSystemFont("36元话费","arial",80);
    pride->setColor(Color3B(170,44,0));
    pride->setAnchorPoint(Point::ANCHOR_MIDDLE);
    pride->setPosition(335,320);
    hbLayer->addChild(pride);
    
    
    auto guan = Sprite::create("competition/huang_guan.png");
    guan->setPosition(420,150);
    hbLayer->addChild(guan);
    
    auto pride2 = Label::createWithSystemFont("36元话费赛","arial",26);
    pride2->setColor(Color3B::BLACK);
    pride2->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    pride2->setPosition(425,190);
    hbLayer->addChild(pride2);
    
    auto shui = Label::createWithSystemFont("水平最高","arial",26);
    shui->setColor(Color3B(255,183,64));
    shui->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    shui->setPosition(445,150);
    
    hbLayer->addChild(shui);
    
    auto ma = Sprite::create("competition/er_wei_ma.png");
    ma->setPosition(920,360);
    hbLayer->addChild(ma);
    
    auto renderTexture = RenderTexture::create(1280, 720, Texture2D::PixelFormat::RGBA8888);
    //清空并开始获取
    renderTexture->beginWithClear(0.0f, 0.0f, 0.0f, 0.0f);
    //遍历场景节点对象，填充纹理到RenderTexture中
    hbLayer->visit();
    //结束获取
    renderTexture->end();
    //保存文件
    std::string outputFile =StringUtils::format("%smahjong_screen_shot.png",FileUtils::getInstance()->getWritablePath().c_str());
    renderTexture->saveToFile("mahjong_screen_shot.png",Image::Format::PNG);
    schedule([=](float dt){
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        CallAndroidMethod::getInstance()->shareSDCardImageToWeChat(outputFile, true);
#endif
        
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        CallIOSMethod::getInstance()->doWechatShareImg(outputFile, 1);
#endif
    }, 0, 0, 0.2f, "mmp");}


void ShareActivityLayer::copyText(){

}
