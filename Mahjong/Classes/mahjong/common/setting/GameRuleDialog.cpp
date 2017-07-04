//
//  GameRuleDialog.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/7/6.
//
//

#include "mahjong/common/setting/GameRuleDialog.hpp"
#include "mahjong/common/utils/Chinese.h"

bool GameRuleDialog::init(){
    if(!Layer::init()){
        return false;
    }
    
    MenuItem* item = MenuItem::create();
    item->setContentSize(Size(1280, 720));
    Menu* bg = Menu::create(item, NULL);
    this->addChild(bg,-1);
    
    auto  dialogBg = Sprite::create("rule/dialog_bg.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(GameRuleDialog::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(1000, 670);
    addChild(closeMenu);
    
//    auto input_bg = Sprite::create("setting/text_bg.png");
//    input_bg->setPosition(640, 320);
//    addChild(input_bg);
//    
//    auto tabBg = Sprite::create("setting/tab_bg.png");
//    tabBg->setPosition(470,610);
//    addChild(tabBg);
//    
//    auto shnaghai = Sprite::create("setting/text_sh_1.png");
//    shnaghai->setTag(1024);
//    shnaghai->setPosition(390,610);
//    addChild(shnaghai,2);
//    
//    auto hongzhong = Sprite::create("setting/text_hz_2.png");
//    hongzhong->setTag(2024);
//    hongzhong->setPosition(555,610);
//    addChild(hongzhong,2);
//    
//    auto qun_normal = MenuItemImage::create("setting/tab_btn_1.png", "setting/tab_btn_1.png");
//    auto qun_selected = MenuItemImage::create("setting/tab_btn_2.png", "setting/tab_btn_2.png");
//    qunToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(GameRuleDialog::showShangHai, this), qun_normal, qun_selected, NULL);
//    qunToggle->setSelectedIndex(1);
//    auto fangka_normal = MenuItemImage::create("setting/tab_btn_1.png", "setting/tab_btn_1.png");
//    auto fangka_selected = MenuItemImage::create("setting/tab_btn_2.png", "setting/tab_btn_2.png");
//    fangkaToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(GameRuleDialog::showHongZhong, this), fangka_normal, fangka_selected, NULL);
//    
//    auto menu = Menu::create(qunToggle, fangkaToggle, NULL);
//    menu->alignItemsHorizontallyWithPadding(0);
//    menu->setPosition(470,610);
//    addChild(menu,1);
//    
//    
//    listView = ListView::create();
//    listView->setDirection(ui::ScrollView::Direction::VERTICAL);//设置ListView布局方向
//    listView->setTouchEnabled(true);//可触摸
//    listView->setContentSize(Size(720,470));//设置ListView大小
//    listView->ignoreContentAdaptWithSize(false);//开启锚点设置，false可更改锚点，true不可更改，Layer默认为point(0,0),其他Node为Point(0.5,0.5)
//    listView->setAnchorPoint(Vec2(0.5, 0.5));//设置锚点，即锚点放在节点setPosition的位置，0，0：表示节点左下角；1，1：表示节点右上角；0.5，0.5表示节点中点
//    listView->setPosition(Point(640,325));
//    addChild(listView);
//    
//    for(auto var: getGameRulesShangHai()){
//        Layout *customItem = Layout::create();
//        customItem->setLayoutType(Layout::Type::ABSOLUTE);
//        customItem->setContentSize(Size(720,40));
//        listView->pushBackCustomItem(customItem);
//        
//        auto text = Label::createWithSystemFont(var,"arial",26);
//        text->setColor(Color3B(255,255,255));
//        text->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
//        text->setPosition(40,30);
//        customItem->addChild(text);
//    }
//    
//    
//    
//    listViewHz = ListView::create();
//    listViewHz->setDirection(ui::ScrollView::Direction::VERTICAL);//设置ListView布局方向
//    listViewHz->setTouchEnabled(true);//可触摸
//    listViewHz->setContentSize(Size(720,470));//设置ListView大小
//    listViewHz->ignoreContentAdaptWithSize(false);//开启锚点设置，false可更改锚点，true不可更改，Layer默认为point(0,0),其他Node为Point(0.5,0.5)
//    listViewHz->setAnchorPoint(Vec2(0.5, 0.5));//设置锚点，即锚点放在节点setPosition的位置，0，0：表示节点左下角；1，1：表示节点右上角；0.5，0.5表示节点中点
//    listViewHz->setPosition(Point(640,325));
//    addChild(listViewHz);
//    listViewHz->setVisible(false);
//    
//    for(auto var: getGameRulesHongZhong()){
//        Layout *customItem = Layout::create();
//        customItem->setLayoutType(Layout::Type::ABSOLUTE);
//        customItem->setContentSize(Size(720,40));
//        listViewHz->pushBackCustomItem(customItem);
//        
//        auto text = Label::createWithSystemFont(var,"arial",26);
//        text->setColor(Color3B(255,255,255));
//        text->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
//        text->setPosition(40,30);
//        customItem->addChild(text);
//    }
    
    return true;
}


void GameRuleDialog::closeView(){
    removeFromParent();
}


void GameRuleDialog::showShangHai(Ref* ref){
    qunToggle->setSelectedIndex(1);
    fangkaToggle->setSelectedIndex(0);
    if(NULL != getChildByTag(1024)){
        ((Sprite*)getChildByTag(1024))->setTexture("setting/text_sh_1.png");
    }
    if(NULL != getChildByTag(2024)){
        ((Sprite*)getChildByTag(2024))->setTexture("setting/text_hz_2.png");
    }
    listView->setVisible(true);
    listViewHz->setVisible(false);
}

void GameRuleDialog::showHongZhong(Ref* ref){
    qunToggle->setSelectedIndex(0);
    fangkaToggle->setSelectedIndex(1);
    if(NULL != getChildByTag(1024)){
        ((Sprite*)getChildByTag(1024))->setTexture("setting/text_sh_2.png");
    }
    if(NULL != getChildByTag(2024)){
        ((Sprite*)getChildByTag(2024))->setTexture("setting/text_hz_1.png");
    }
    listView->setVisible(false);
    listViewHz->setVisible(true);
}

std::vector<std::string> GameRuleDialog::getGameRulesShangHai(){
    std::vector<std::string> rules;
    rules.push_back(ChineseWord("rule_text_1"));
    rules.push_back(ChineseWord("rule_text_2"));
    rules.push_back(ChineseWord("rule_text_3"));
    rules.push_back(ChineseWord("rule_text_4"));
    rules.push_back(ChineseWord("rule_text_5"));
    rules.push_back(ChineseWord("rule_text_6"));
    rules.push_back(ChineseWord("rule_text_7"));
    rules.push_back(ChineseWord("rule_text_8"));
    rules.push_back(ChineseWord("rule_text_9"));
    rules.push_back(ChineseWord("rule_text_10"));
    rules.push_back(ChineseWord("rule_text_11"));
    rules.push_back(ChineseWord("rule_text_12"));
    rules.push_back(ChineseWord("rule_text_13"));
    rules.push_back(ChineseWord("rule_text_14"));
    rules.push_back(ChineseWord("rule_text_15"));
    rules.push_back(ChineseWord("rule_text_16"));
    rules.push_back(ChineseWord("rule_text_17"));
    rules.push_back(ChineseWord("rule_text_18"));
    rules.push_back(ChineseWord("rule_text_19"));
    rules.push_back(ChineseWord("rule_text_20"));
    rules.push_back(ChineseWord("rule_text_21"));
    return rules;
}

std::vector<std::string> GameRuleDialog::getGameRulesHongZhong(){
    std::vector<std::string> rules;
    rules.push_back(ChineseWord("rule_text_22"));
    rules.push_back(ChineseWord("rule_text_23"));
    rules.push_back(ChineseWord("rule_text_24"));
    rules.push_back(ChineseWord("rule_text_25"));
    rules.push_back(ChineseWord("rule_text_26"));
    rules.push_back(ChineseWord("rule_text_27"));
    rules.push_back(ChineseWord("rule_text_28"));
    rules.push_back(ChineseWord("rule_text_29"));
    rules.push_back(ChineseWord("rule_text_30"));
    rules.push_back(ChineseWord("rule_text_31"));
    rules.push_back(ChineseWord("rule_text_32"));
    rules.push_back(ChineseWord("rule_text_33"));
    rules.push_back(ChineseWord("rule_text_34"));
    rules.push_back(ChineseWord("rule_text_35"));
    rules.push_back(ChineseWord("rule_text_36"));
    rules.push_back(ChineseWord("rule_text_37"));
    rules.push_back(ChineseWord("rule_text_38"));
    return rules;
}


