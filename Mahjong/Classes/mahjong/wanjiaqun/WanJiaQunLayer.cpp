//
//  WanJiaQunLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/9.
//
//

#include "mahjong/wanjiaqun/WanJiaQunLayer.hpp"
#include "mahjong/utils/GameConfig.h"
#include "http/image/UrlImageMannger.h"
#include "mahjong/state/GameData.h"

bool WanJiaQunLayer::init(){
    if(!Layer::init()){
        return false;
    }
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
    
    
    auto  dialogBg = Sprite::create("common/dialog_bg.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(WanJiaQunLayer::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(980, 580);
    addChild(closeMenu);
    
    auto titleIcon = Sprite::create("wanjiaqun/wj_title.png");
    titleIcon->setPosition(640, 590);
    addChild(titleIcon);
    
    auto tabbg = Sprite::create("wanjiaqun/tab_bg.png");
    tabbg->setScaleX(0.52f);
    tabbg->setPosition(480,500);
    addChild(tabbg);
    
    auto qun_normal = MenuItemImage::create("wanjiaqun/tab_btn_1.png", "wanjiaqun/tab_btn_1.png");
    auto qun_selected = MenuItemImage::create("wanjiaqun/tab_btn_2.png", "wanjiaqun/tab_btn_2.png");
    qunToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(WanJiaQunLayer::showWanJiaQun, this), qun_normal, qun_selected, NULL);
    
    auto fangka_normal = MenuItemImage::create("wanjiaqun/tab_btn_1.png", "wanjiaqun/tab_btn_1.png");
    auto fangka_selected = MenuItemImage::create("wanjiaqun/tab_btn_2.png", "wanjiaqun/tab_btn_2.png");
    fangkaToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(WanJiaQunLayer::showFangkaDai, this), fangka_normal, fangka_selected, NULL);
    
    auto menu = Menu::create(qunToggle, fangkaToggle, NULL);
    menu->alignItemsHorizontallyWithPadding(0);
    menu->setPosition(480, 500);
    addChild(menu,1);
    
    wanjia =  Sprite::create("wanjiaqun/wj_text_1.png");
    wanjia->setPosition(390, 500);
    addChild(wanjia,2);
    
    wanJiaLabel = Label::createWithSystemFont("", "Arial", 30);
    wanJiaLabel->setColor(Color3B(93,172,221));
    wanJiaLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    wanJiaLabel->setPosition(710, 265);
    addChild(wanJiaLabel,2);
    
    daili =  Sprite::create("wanjiaqun/daili_text_2.png");
    daili->setPosition(570, 500);
    addChild(daili,2);
    
    daiLiLanel = Label::createWithSystemFont("", "Arial", 30);
    daiLiLanel->setColor(Color3B(93,172,221));
    daiLiLanel->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    daiLiLanel->setPosition(725, 285);
    daiLiLanel->setVisible(false);
    addChild(daiLiLanel,2);

    
    auto bigbg = Sprite::create("wanjiaqun/wj_big_box_bg.png");
    bigbg->setPosition(640,310);
    addChild(bigbg);
    
    auto mabg = Sprite::create("wanjiaqun/ma_bg.png");
    mabg->setPosition(440,310);
    addChild(mabg);
    
    image =  Sprite::create();
    image->setContentSize(Size(168,168));
    image->setPosition(440,310);
    addChild(image);
    
    content= Sprite::create("wanjiaqun/wj_qun_text.png");
    content->setPosition(740,310);
    addChild(content);
    
    qunToggle->setSelectedIndex(0);
    fangkaToggle->setSelectedIndex(1);
    std::string path = UrlImageMannger::getInstance()->downloadQunImgByUrl(WECHAT_WAN_JIA_QUN_URL,false);
    if(path != IAMGE_LOADING){
        image->setTexture(path);
    }
    return true;
}


void WanJiaQunLayer::closeView(){
    removeFromParent();
}

void WanJiaQunLayer::showWanJiaQun(Ref* ref){
    qunToggle->setSelectedIndex(0);
    fangkaToggle->setSelectedIndex(1);
    wanjia->setTexture("wanjiaqun/wj_text_1.png");
    daili->setTexture("wanjiaqun/daili_text_2.png");
    content->setTexture("wanjiaqun/wj_qun_text.png");
    wanJiaLabel->setVisible(true);
    daiLiLanel->setVisible(false);
    wanJiaLabel->setString(GAMEDATA::getInstance()->getWanJiaQun());
    std::string path = UrlImageMannger::getInstance()->downloadQunImgByUrl(WECHAT_WAN_JIA_QUN_URL,false);
    if(path != IAMGE_LOADING){
        image->setTexture(path);
    }
}


void WanJiaQunLayer::showFangkaDai(Ref* ref){
    qunToggle->setSelectedIndex(1);
    fangkaToggle->setSelectedIndex(0);
    wanjia->setTexture("wanjiaqun/wj_text_2.png");
    daili->setTexture("wanjiaqun/daili_text_1.png");
    content->setTexture("wanjiaqun/wj_qun_text.png");
    content->setTexture("wanjiaqun/daili_text.png");
    wanJiaLabel->setVisible(false);
    daiLiLanel->setVisible(true);
    daiLiLanel->setString(GAMEDATA::getInstance()->getDaiLiQun());
    std::string path = UrlImageMannger::getInstance()->downloadDailiImgByUrl(WECHAT_DAI_LI_QUN_URL,false);
    if(path != IAMGE_LOADING){
        image->setTexture(path);
    }
}

