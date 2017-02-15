//
//  WanJiaQunLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/9.
//
//

#include "mahjong/share/ShareToFriendLayer.hpp"
#include "mahjong/utils/GameConfig.h"
#include "http/image/UrlImageMannger.h"

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
    
    auto tabbg = Sprite::create("wanjiaqun/tab_bg.png");
    tabbg->setScaleX(0.52f);
    tabbg->setPosition(480,500);
    addChild(tabbg);
    
    auto qun_normal = MenuItemImage::create("wanjiaqun/tab_btn_1.png", "wanjiaqun/tab_btn_1.png");
    auto qun_selected = MenuItemImage::create("wanjiaqun/tab_btn_2.png", "wanjiaqun/tab_btn_2.png");
    qunToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(ShareToFriendLayer::showWanJiaQun, this), qun_normal, qun_selected, NULL);
    
    auto fangka_normal = MenuItemImage::create("wanjiaqun/tab_btn_1.png", "wanjiaqun/tab_btn_1.png");
    auto fangka_selected = MenuItemImage::create("wanjiaqun/tab_btn_2.png", "wanjiaqun/tab_btn_2.png");
    fangkaToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(ShareToFriendLayer::showFangkaDai, this), fangka_normal, fangka_selected, NULL);
    
    auto menu = Menu::create(qunToggle, fangkaToggle, NULL);
    menu->alignItemsHorizontallyWithPadding(0);
    menu->setPosition(480, 500);
    addChild(menu,1);
    
    wanjia =  Sprite::create("wanjiaqun/wj_text_1.png");
    wanjia->setPosition(390, 500);
    addChild(wanjia,2);
    
    daili =  Sprite::create("wanjiaqun/daili_text_2.png");
    daili->setPosition(570, 500);
    addChild(daili,2);
    

    
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
    std::string path = UrlImageMannger::getInstance()->downloadQunImgByUrl(WECHAT_WAN_JIA_QUN_URL);
    if(path != IAMGE_LOADING){
        image->setTexture(path);
    }
    return true;
}


void ShareToFriendLayer::closeView(){
    removeFromParent();
}

void ShareToFriendLayer::showWanJiaQun(Ref* ref){
    qunToggle->setSelectedIndex(0);
    fangkaToggle->setSelectedIndex(1);
    wanjia->setTexture("wanjiaqun/wj_text_1.png");
    daili->setTexture("wanjiaqun/daili_text_2.png");
    content->setTexture("wanjiaqun/wj_qun_text.png");
    std::string path = UrlImageMannger::getInstance()->downloadQunImgByUrl(WECHAT_WAN_JIA_QUN_URL);
    if(path != IAMGE_LOADING){
        image->setTexture(path);
    }
}


void ShareToFriendLayer::showFangkaDai(Ref* ref){
    qunToggle->setSelectedIndex(1);
    fangkaToggle->setSelectedIndex(0);
    wanjia->setTexture("wanjiaqun/wj_text_2.png");
    daili->setTexture("wanjiaqun/daili_text_1.png");
    content->setTexture("wanjiaqun/wj_qun_text.png");
    content->setTexture("wanjiaqun/daili_text.png");
    std::string path = UrlImageMannger::getInstance()->downloadDailiImgByUrl(WECHAT_DAI_LI_QUN_URL);
    if(path != IAMGE_LOADING){
        image->setTexture(path);
    }
}

