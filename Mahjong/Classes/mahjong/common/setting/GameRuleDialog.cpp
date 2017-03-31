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
    
    auto  dialogBg = Sprite::create("friend/dialog_bg.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(GameRuleDialog::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(980, 650);
    addChild(closeMenu);
    
    auto paodai = Sprite::create("common/piaodai_zi.png");
    paodai->setPosition(640, 660);
    this->addChild(paodai);
    auto icon = Sprite::create("setting/rule_info.png");
    icon->setPosition(640, 680);
    addChild(icon);
    
    auto input_bg = ui::Scale9Sprite::create("common/input_box_bg.png");
    input_bg->setContentSize(Size(700,560));
    input_bg->setPosition(640, 340);
    addChild(input_bg);
    
    listView = ListView::create();
    listView->setDirection(ui::ScrollView::Direction::VERTICAL);//设置ListView布局方向
    listView->setTouchEnabled(true);//可触摸
    listView->setContentSize(Size(720,480));//设置ListView大小
    listView->ignoreContentAdaptWithSize(false);//开启锚点设置，false可更改锚点，true不可更改，Layer默认为point(0,0),其他Node为Point(0.5,0.5)
    listView->setAnchorPoint(Vec2(0.5, 0.5));//设置锚点，即锚点放在节点setPosition的位置，0，0：表示节点左下角；1，1：表示节点右上角；0.5，0.5表示节点中点
    listView->setPosition(Point(640,350));
    addChild(listView);
    
    for(auto var: getGameRules()){
        Layout *customItem = Layout::create();
        customItem->setLayoutType(Layout::Type::ABSOLUTE);
        customItem->setContentSize(Size(720,40));
        listView->pushBackCustomItem(customItem);
        
        auto text = Label::createWithSystemFont(var,"arial",26);
        text->setColor(Color3B(255,255,255));
        text->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        text->setPosition(40,30);
        customItem->addChild(text);
    }
    
    return true;
}


void GameRuleDialog::closeView(){
    removeFromParent();
}

std::vector<std::string> GameRuleDialog::getGameRules(){
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
