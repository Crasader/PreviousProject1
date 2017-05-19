//
//  CompetitonLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/5/19.
//
//

#include "mahjong/lobby/competition/CompetitonLayer.hpp"



bool CompetitonLayer::init(){
    
    if(!Layer::init()){
        return false;
    }
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
    
    auto comBg = Sprite::create("competition/competition_bg.png");
    comBg->setPosition(640,360);
    addChild(comBg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(CompetitonLayer::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(1150, 642);
    addChild(closeMenu);
    
    return  true;
}


void CompetitonLayer::initView(CompetitionRoomId roomId,std::string huafei,std::string fangka,std::string rule){
    
    auto title = Sprite::create("competition/shanghai_text.png");
    if(roomId == CompetitionRoomId::Hongzhong_High||roomId == Hongzhong_Normal){
        title->setTexture("competition/hongzhong_text.png");
    }
    title->setPosition(415,600);
    addChild(title);

    auto huafeiNum = LabelAtlas::create(huafei, "competition/huafei_num.png", 48, 76, '0');
    huafeiNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    huafeiNum->setPosition(530,606);
    addChild(huafeiNum);
    
    auto text = Sprite::create("competition/huafei_text.png");
    text->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    text->setPosition(huafeiNum->getPositionX()+huafeiNum->getContentSize().width,606);
    addChild(text);
    
    auto ruleTitle = Sprite::create("competition/competition_rule.png");
    ruleTitle->setPosition(380,460);
    addChild(ruleTitle);
    
    auto prideTitle = Sprite::create("competition/competition_pride.png");
    prideTitle->setPosition(780,460);
    addChild(prideTitle);
    
    auto prideNum = LabelAtlas::create(huafei, "competition/pride_num.png", 28, 46, '0');
    prideNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    prideNum->setPosition(865,465);
    addChild(prideNum);

    auto huatext = Sprite::create("competition/hua_fei_text.png");
    huatext->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    huatext->setPosition(prideNum->getPositionX()+prideNum->getContentSize().width,465);
    addChild(huatext);
    
    auto time = Label::createWithSystemFont(<#const std::string &text#>, <#const std::string &font#>, <#float fontSize#>)
    
}


void CompetitonLayer::closeView(){
    removeFromParent();
}
