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
    itemlight1->setPosition(Vec2(480,320));
    addChild(itemlight1);
    
    auto itemcontent1 = Sprite::create("mjitem/gold_stack.png");
    itemcontent1->setPosition(Vec2(480,320));
    addChild(itemcontent1);
    
    auto iteminfo1 = Sprite::create("relieve/relieve_image_2.png");
    iteminfo1->setPosition(Vec2(480,260));
    addChild(iteminfo1);
    
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
    itemlight2->setPosition(Vec2(810,320));
    addChild(itemlight2);
    
    auto itemcontent2 = Sprite::create("relieve/relieve_image_6.png");
    itemcontent2->setPosition(Vec2(810,320));
    addChild(itemcontent2);
    
    auto iteminfo2 = Sprite::create("relieve/relieve_image_2.png");
    iteminfo2->setPosition(Vec2(810,260));
    addChild(iteminfo2);
    
    
    return true;
}