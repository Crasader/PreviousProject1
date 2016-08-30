//
//  MahjongActivities.cpp
//  Mahjong
//  麻将活动
//  Created by qiuzhong on 16/8/30.
//
//

#include "game/mahjong/activities/MahjongActivities.hpp"

bool MahjongActivities::init(){
    if(!Layer::init()){
        return false;
    }
    initView();
    return true;
}

void MahjongActivities::initView(){
    //隔断点击事件
    auto menuItem = MenuItem::create();
    menuItem->setContentSize(Size(1280,760));
    auto menu = Menu::create(menuItem,NULL);
    menu->setPosition(640,360);
    addChild(menu);
    //绘制界面
    auto dialog_bg = Sprite::create("shop/shop_bg.png");
    dialog_bg->setPosition(640,340);
    addChild(dialog_bg);
    
    auto title = Sprite::create("activities/act_title.png");
    title->setPosition(654,640);
    addChild(title);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(MahjongActivities::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(1050, 590);
    addChild(closeMenu);
    
    auto tabMenuBg = Sprite::create("activities/act_tab_bg.png");
    tabMenuBg->setPosition(620,535);
    addChild(tabMenuBg);
    //页标签
    auto act_tab_image_a_1 = MenuItemImage::create("activities/act_tab_btn_1.png", "activities/act_tab_btn_1.png");
    auto act_tab_image_a_2 = MenuItemImage::create("activities/act_tab_btn_2.png", "activities/act_tab_btn_2.png");
    auto act_tab_1 = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MahjongActivities::showActiviyContent, this), act_tab_image_a_1, act_tab_image_a_2, NULL);
    act_tab_1->setSelectedIndex(1);
    
    auto act_tab_image_b_1 = MenuItemImage::create("activities/act_tab_btn_1.png", "activities/act_tab_btn_1.png");
    auto act_tab_image_b_2 = MenuItemImage::create("activities/act_tab_btn_2.png", "activities/act_tab_btn_2.png");
    auto act_tab_2 = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MahjongActivities::showActivityRank, this),
                                                        act_tab_image_b_1, act_tab_image_b_2, NULL);
    
    auto act_tab_image_c_1 = MenuItemImage::create("activities/act_tab_btn_1.png", "activities/act_tab_btn_1.png");
    auto act_tab_image_c_2 = MenuItemImage::create("activities/act_tab_btn_2.png", "activities/act_tab_btn_2.png");
    auto act_tab_3 = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MahjongActivities::showActivityPride, this), act_tab_image_c_1, act_tab_image_c_2, NULL);
    
    auto act_tab_image_d_1 = MenuItemImage::create("activities/act_tab_btn_1.png", "activities/act_tab_btn_1.png");
    auto act_tab_image_d_2 = MenuItemImage::create("activities/act_tab_btn_2.png", "activities/act_tab_btn_2.png");
    auto act_tab_4 = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MahjongActivities::showActivityRule, this),
                                                        act_tab_image_d_1, act_tab_image_d_2, NULL);
    
    auto tabmenu = Menu::create(act_tab_1, act_tab_2, act_tab_3, act_tab_4, NULL);
    tabmenu->alignItemsHorizontallyWithPadding(7);
    tabmenu->setPosition(620, 534);
    addChild(tabmenu,1);
    
//    auto 
    
}

void MahjongActivities::onEnter(){
    Layer::onEnter();
    
}


void MahjongActivities::onExit(){
    Layer::onExit();
}


void MahjongActivities::closeView(){
    removeFromParent();
}


void MahjongActivities::showActiviyContent(Ref* ref){
    
}


void MahjongActivities::showActivityRank(Ref* ref){
    
    
}

void MahjongActivities::showActivityPride(Ref* ref){
    
    
}

void MahjongActivities::showActivityRule(Ref* ref){
    
    
}
