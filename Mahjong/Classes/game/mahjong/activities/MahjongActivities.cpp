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
    showActiviyContent();
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
    act_tab_1 = MenuItemToggle::createWithCallback(CC_CALLBACK_0(MahjongActivities::showActiviyContent, this), act_tab_image_a_1, act_tab_image_a_2, NULL);
    
    auto act_tab_image_b_1 = MenuItemImage::create("activities/act_tab_btn_1.png", "activities/act_tab_btn_1.png");
    auto act_tab_image_b_2 = MenuItemImage::create("activities/act_tab_btn_2.png", "activities/act_tab_btn_2.png");
    act_tab_2 = MenuItemToggle::createWithCallback(CC_CALLBACK_0(MahjongActivities::showActivityRank, this),
                                                   act_tab_image_b_1, act_tab_image_b_2, NULL);
    
    auto act_tab_image_c_1 = MenuItemImage::create("activities/act_tab_btn_1.png", "activities/act_tab_btn_1.png");
    auto act_tab_image_c_2 = MenuItemImage::create("activities/act_tab_btn_2.png", "activities/act_tab_btn_2.png");
    act_tab_3 = MenuItemToggle::createWithCallback(CC_CALLBACK_0(MahjongActivities::showActivityPride, this), act_tab_image_c_1, act_tab_image_c_2, NULL);
    
    auto act_tab_image_d_1 = MenuItemImage::create("activities/act_tab_btn_1.png", "activities/act_tab_btn_1.png");
    auto act_tab_image_d_2 = MenuItemImage::create("activities/act_tab_btn_2.png", "activities/act_tab_btn_2.png");
    act_tab_4 = MenuItemToggle::createWithCallback(CC_CALLBACK_0(MahjongActivities::showActivityRule, this),
                                                   act_tab_image_d_1, act_tab_image_d_2, NULL);
    
    auto tabmenu = Menu::create(act_tab_1, act_tab_2, act_tab_3, act_tab_4, NULL);
    tabmenu->alignItemsHorizontallyWithPadding(7);
    tabmenu->setPosition(620, 534);
    addChild(tabmenu);
    
     tabLabel_1 = Sprite::create();
    tabLabel_1->setPosition(320, 534);
    tabLabel_1->setTag(100);
    addChild(tabLabel_1);
    
     tabLabel_2 = Sprite::create();
    tabLabel_2->setPosition(530, 534);
    tabLabel_2->setTag(101);
    addChild(tabLabel_2);
    
     tabLabel_3 = Sprite::create();
    tabLabel_3->setPosition(720, 534);
    tabLabel_3->setTag(102);
    addChild(tabLabel_3);
    
     tabLabel_4 = Sprite::create();
    tabLabel_4->setPosition(920, 534);
    tabLabel_4->setTag(103);
    addChild(tabLabel_4);
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


void MahjongActivities::showActiviyContent(){
    act_tab_1->setSelectedIndex(1);
    act_tab_2->setSelectedIndex(0);
    act_tab_3->setSelectedIndex(0);
    act_tab_4->setSelectedIndex(0);
    tabLabel_1->setTexture("activities/btn_text_a_2.png");
    tabLabel_2->setTexture("activities/btn_text_b_1.png");
    tabLabel_3->setTexture("activities/btn_text_c_1.png");
    tabLabel_4->setTexture("activities/btn_text_d_1.png");
}


void MahjongActivities::showActivityRank(){
    act_tab_1->setSelectedIndex(0);
    act_tab_2->setSelectedIndex(1);
    act_tab_3->setSelectedIndex(0);
    act_tab_4->setSelectedIndex(0);
    tabLabel_1->setTexture("activities/btn_text_a_1.png");
    tabLabel_2->setTexture("activities/btn_text_b_2.png");
    tabLabel_3->setTexture("activities/btn_text_c_1.png");
    tabLabel_4->setTexture("activities/btn_text_d_1.png");
}

void MahjongActivities::showActivityPride(){
    act_tab_1->setSelectedIndex(0);
    act_tab_2->setSelectedIndex(0);
    act_tab_3->setSelectedIndex(1);
    act_tab_4->setSelectedIndex(0);
    tabLabel_1->setTexture("activities/btn_text_a_1.png");
    tabLabel_2->setTexture("activities/btn_text_b_1.png");
    tabLabel_3->setTexture("activities/btn_text_c_2.png");
    tabLabel_4->setTexture("activities/btn_text_d_1.png");
}

void MahjongActivities::showActivityRule(){
    act_tab_1->setSelectedIndex(0);
    act_tab_2->setSelectedIndex(0);
    act_tab_3->setSelectedIndex(0);
    act_tab_4->setSelectedIndex(1);
    tabLabel_1->setTexture("activities/btn_text_a_1.png");
    tabLabel_2->setTexture("activities/btn_text_b_1.png");
    tabLabel_3->setTexture("activities/btn_text_c_1.png");
    tabLabel_4->setTexture("activities/btn_text_d_2.png");
}
