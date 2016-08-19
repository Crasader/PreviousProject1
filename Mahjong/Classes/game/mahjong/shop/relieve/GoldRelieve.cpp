//
//  GoldRelieve.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/8/19.
//
//

#include "game/mahjong/shop/relieve/GoldRelieve.hpp"

bool GoldRelieve::init(){
    if(!Layer::init()){
        return false;
    }
    MenuItem* item = MenuItem::create();
    item->setContentSize(Size(1280, 720));
    Menu* bg = Menu::create(item, NULL);
    this->addChild(bg);
    
    auto dialogBg = Sprite::create("shop/shop_bg_2.png");
    dialogBg->setPosition(Vec2(640,360));
    addChild(dialogBg);
    
    auto closeBtnImage = MenuItemImage::create("common/close_btn_1.png","common/close_btn_1.png",CC_CALLBACK_0(GoldRelieve::closeView, this));
    auto closeBtn = Menu::create(closeBtnImage,NULL);
    closeBtn->setPosition(Vec2(980,580));
    addChild(closeBtn);
    
    auto dialogTitle = Sprite::create("relieve/relieve_image_5.png");
    dialogTitle->setPosition(Vec2(640,620));
    addChild(dialogTitle);
    
    auto number =  Sprite::create("relieve/relieve_image_7.png");
    number->setPosition(Vec2(640,530));
    addChild(number);
    
    auto itembg1 = Scale9Sprite::create("shop/red_box.png");
    itembg1->setContentSize(Size(285,315));
    itembg1->setPosition(Vec2(480,320));
    addChild(itembg1);
    
    auto itempiao1 = Sprite::create("daily/pride/piao_dai.png");
    itempiao1->setPosition(Vec2(480,430));
    addChild(itempiao1);
    
    auto itemtitle1 = Sprite::create("relieve/relieve_image_3.png");
    itemtitle1->setPosition(Vec2(480,460));
    addChild(itemtitle1);
    
    auto itemlight1 = Sprite::create("shop/gold_bg_light.png");
    itemlight1->setPosition(Vec2(480,340));
    addChild(itemlight1);
    
    auto itemcontent1 = Sprite::create("mjitem/gold_stack.png");
    itemcontent1->setPosition(Vec2(480,340));
    addChild(itemcontent1);
    
    auto iteminfo1 = Sprite::create("relieve/relieve_image_2.png");
    iteminfo1->setPosition(Vec2(480,280));
    addChild(iteminfo1);
    
    auto itembtnImage1 = MenuItemImage::create("relieve/linqu_btn_1.png","relieve/linqu_btn_2.png");
    auto itembtn1 = Menu::create(itembtnImage1,NULL);
    itembtn1->setPosition(Vec2(480,220));
    addChild(itembtn1);
    
    auto itembg2 = Scale9Sprite::create("shop/red_box.png");
    itembg2->setContentSize(Size(285,315));
    itembg2->setPosition(Vec2(810,320));
    addChild(itembg2);
    
    auto itempiao2 = Sprite::create("daily/pride/piao_dai.png");
    itempiao2->setPosition(Vec2(810,430));
    addChild(itempiao2);
    
    auto itemtitle2 = Sprite::create("relieve/relieve_image_4.png");
    itemtitle2->setPosition(Vec2(810,460));
    addChild(itemtitle2);
    
    auto itemlight2 = Sprite::create("shop/gold_bg_light.png");
    itemlight2->setPosition(Vec2(810,340));
    addChild(itemlight2);
    
    auto itemcontent2 = Sprite::create("relieve/relieve_image_6.png");
    itemcontent2->setPosition(Vec2(810,340));
    addChild(itemcontent2);
    
    auto iteminfo2 = Sprite::create("relieve/relieve_image_2.png");
    iteminfo2->setPosition(Vec2(810,280));
    addChild(iteminfo2);
    
    auto itembtnImage2 = MenuItemImage::create("relieve/charge_btn_1.png","relieve/charge_btn_2.png");
    auto itembtn2 = Menu::create(itembtnImage2,NULL);
    itembtn2->setPosition(Vec2(810,220));
    addChild(itembtn2);
    
    return true;
}

void GoldRelieve::closeView(){
    removeFromParent();
}