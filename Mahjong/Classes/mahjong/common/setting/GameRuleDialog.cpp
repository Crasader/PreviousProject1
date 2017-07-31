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
    auto bg0 = LayerColor::create(Color4B(0, 0, 0, 150), 1280, 720);
    addChild(bg0);
    
    auto dialog_bg = Sprite::create("openroom/open_room_bg.png");
    dialog_bg->setPosition(640,350);
    addChild(dialog_bg);
    
    
    auto title = Sprite::create("setting/rule_info.png");
    title->setPosition(640,640);
    addChild(title);
    
    auto guizheBg = Sprite::create("rule/text_bg.png");
    guizheBg->setPosition(754,290);
    addChild(guizheBg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(GameRuleDialog::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(1170, 660);
    addChild(closeMenu);
    
    shangHai = Sprite::create("openroom/shang_hai_btn_1.png");
    shangHai->setPosition(225,535);
    addChild(shangHai);
    
    hongZhong = Sprite::create("openroom/hong_zhong_btn_2.png");
    hongZhong->setPosition(225,430);
    addChild(hongZhong);
    
    chongMing =  Sprite::create("openroom/chong_ming_btn_2.png");
    chongMing->setPosition(225,325);
    addChild(chongMing);
    
    auto gz_normal = MenuItemImage::create("rule/tab_btn_1.png", "rule/tab_btn_1.png");
    auto gz_selected = MenuItemImage::create("rule/tab_btn_2.png", "rule/tab_btn_2.png");
    gzToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(GameRuleDialog::showJiBenGuiZhe, this), gz_normal, gz_selected, NULL);
    
    auto px_normal = MenuItemImage::create("rule/tab_btn_1.png", "rule/tab_btn_1.png");
    auto px_selected = MenuItemImage::create("rule/tab_btn_2.png", "rule/tab_btn_2.png");
    pxToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(GameRuleDialog::showJiBenPaiXing, this), px_normal, px_selected, NULL);
    pxToggle->setSelectedIndex(1);
    
    auto ts_normal = MenuItemImage::create("rule/tab_btn_1.png", "rule/tab_btn_1.png");
    auto ts_selected = MenuItemImage::create("rule/tab_btn_2.png", "rule/tab_btn_2.png");
    tsToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(GameRuleDialog::showTeShuPaiXing, this), ts_normal, ts_selected, NULL);
    tsToggle->setSelectedIndex(1);
    
    auto js_normal = MenuItemImage::create("rule/tab_btn_1.png", "rule/tab_btn_1.png");
    auto js_selected = MenuItemImage::create("rule/tab_btn_2.png", "rule/tab_btn_2.png");
    jsToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(GameRuleDialog::showYouXiJieSuan, this), js_normal, js_selected, NULL);
    jsToggle->setSelectedIndex(1);
    
    auto menu = Menu::create(gzToggle, pxToggle,tsToggle,jsToggle, NULL);
    menu->alignItemsHorizontallyWithPadding(0);
    menu->setPosition(680,565);
    addChild(menu,1);
    
    guizhe1 = Sprite::create("rule/btn_gz_1.png");
    guizhe1->setPosition(416,560);
    addChild(guizhe1,2);
    
    guizhe2 = Sprite::create("rule/btn_px_2.png");
    guizhe2->setPosition(591,560);
    addChild(guizhe2,2);
    
    guizhe3 = Sprite::create("rule/btn_ts_2.png");
    guizhe3->setPosition(767,560);
    addChild(guizhe3,2);
    
    guizhe4 = Sprite::create("rule/btn_js_2.png");
    guizhe4->setPosition(940,560);
    addChild(guizhe4,2);
    
    auto framesize = guizheBg->getContentSize();
    contentView = ListView::create();
    contentView->setDirection(ui::ScrollView::Direction::VERTICAL);
    contentView->setTouchEnabled(true);
    contentView->setContentSize(framesize+Size(0,-30));
    contentView->ignoreContentAdaptWithSize(false);
    contentView->setAnchorPoint(Vec2(0.5, 0.5));
    contentView->setPosition(Point(754,292));
    addChild(contentView);
    
    auto text = Sprite::create("rule/rule_sh_1.png");
    text->setPosition(435,(text->getContentSize().height+50)/2);
    Layout *customItem = Layout::create();
    customItem->setLayoutType(Layout::Type::ABSOLUTE);
    customItem->setContentSize(Size(850, text->getContentSize().height+50));
    contentView->pushBackCustomItem(customItem);
    customItem->addChild(text);
    
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(GameRuleDialog::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameRuleDialog::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameRuleDialog::onTouchEnded, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener,this);
    
    return true;
}


void GameRuleDialog::closeView(){
    removeFromParent();
}


void GameRuleDialog::showJiBenGuiZhe(Ref* ref){
    guizhe1->setTexture("rule/btn_gz_1.png");
    guizhe2->setTexture("rule/btn_px_2.png");
    guizhe3->setTexture("rule/btn_ts_2.png");
    guizhe4->setTexture("rule/btn_js_2.png");
    gzToggle->setSelectedIndex(0);
    pxToggle->setSelectedIndex(1);
    tsToggle->setSelectedIndex(1);
    jsToggle->setSelectedIndex(1);
    selcetIndex = 1;
    updateRuleImage(ruleSelected,1);
}

void GameRuleDialog::showJiBenPaiXing(Ref* ref){
    guizhe1->setTexture("rule/btn_gz_2.png");
    guizhe2->setTexture("rule/btn_px_1.png");
    guizhe3->setTexture("rule/btn_ts_2.png");
    guizhe4->setTexture("rule/btn_js_2.png");
    gzToggle->setSelectedIndex(1);
    pxToggle->setSelectedIndex(0);
    tsToggle->setSelectedIndex(1);
    jsToggle->setSelectedIndex(1);
    selcetIndex = 2;
    updateRuleImage(ruleSelected,2);
}


void GameRuleDialog::showTeShuPaiXing(Ref* ref){
    guizhe1->setTexture("rule/btn_gz_2.png");
    guizhe2->setTexture("rule/btn_px_2.png");
    guizhe3->setTexture("rule/btn_ts_1.png");
    guizhe4->setTexture("rule/btn_js_2.png");
    gzToggle->setSelectedIndex(1);
    pxToggle->setSelectedIndex(1);
    tsToggle->setSelectedIndex(0);
    jsToggle->setSelectedIndex(1);
    selcetIndex = 3;
    updateRuleImage(ruleSelected,3);
}


void GameRuleDialog::showYouXiJieSuan(Ref* ref){
    guizhe1->setTexture("rule/btn_gz_2.png");
    guizhe2->setTexture("rule/btn_px_2.png");
    guizhe3->setTexture("rule/btn_ts_2.png");
    guizhe4->setTexture("rule/btn_js_1.png");
    gzToggle->setSelectedIndex(1);
    pxToggle->setSelectedIndex(1);
    tsToggle->setSelectedIndex(1);
    jsToggle->setSelectedIndex(0);
    selcetIndex = 4;
    updateRuleImage(ruleSelected,4);
}

bool GameRuleDialog::onTouchBegan(Touch *touch, Event  *event){
    return true;
}


void GameRuleDialog::onTouchMoved(Touch *touch, Event  *event){
    
    
}

void GameRuleDialog::onTouchEnded(Touch *touch, Event  *event){
    if(shangHai->getBoundingBox().containsPoint(touch->getLocation())){
        ruleSelected = 0;
        shangHai->setTexture("openroom/shang_hai_btn_1.png");
        hongZhong->setTexture("openroom/hong_zhong_btn_2.png");
        chongMing->setTexture("openroom/chong_ming_btn_2.png");
        updateRuleImage(ruleSelected,selcetIndex);
    }
    if(hongZhong->getBoundingBox().containsPoint(touch->getLocation())){
        ruleSelected = 1;
        shangHai->setTexture("openroom/shang_hai_btn_2.png");
        hongZhong->setTexture("openroom/hong_zhong_btn_1.png");
        chongMing->setTexture("openroom/chong_ming_btn_2.png");
        updateRuleImage(ruleSelected,selcetIndex);
    }
    if(chongMing->getBoundingBox().containsPoint(touch->getLocation())){
        ruleSelected = 2;
        shangHai->setTexture("openroom/shang_hai_btn_2.png");
        hongZhong->setTexture("openroom/hong_zhong_btn_2.png");
        chongMing->setTexture("openroom/chong_ming_btn_1.png");
        updateRuleImage(ruleSelected,selcetIndex);
    }
}


void GameRuleDialog::updateRuleImage(int indexSelect,int index){
    contentView->removeAllItems();
    auto text = Sprite::create();
    if(indexSelect == 0){
        text->setTexture(StringUtils::format("rule/rule_sh_%d.png",index));
    }else if(indexSelect == 1){
        text->setTexture(StringUtils::format("rule/rule_hz_%d.png",index));
    }else if(indexSelect == 2){
        if(index == 1){
            text->setTexture(StringUtils::format("rule/rule_sh_%d.png",index));
        }else{
            text->setTexture(StringUtils::format("rule/rule_cm_%d.png",index));
        }
        
    }
    text->setPosition(435,(text->getContentSize().height+50)/2);
    Layout *customItem = Layout::create();
    customItem->setLayoutType(Layout::Type::ABSOLUTE);
    customItem->setContentSize(Size(850, text->getContentSize().height+50));
    contentView->pushBackCustomItem(customItem);
    customItem->addChild(text);
}
