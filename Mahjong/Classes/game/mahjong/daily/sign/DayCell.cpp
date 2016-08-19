//
//  DayCell.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/20.
//
//

#include "game/mahjong/daily/sign/DayCell.hpp"


DayCell* DayCell::create(int propType){
    DayCell* cell = new DayCell();
    if(cell&& cell->init(propType)){
        cell->autorelease();
        return cell;
    }
    CC_SAFE_DELETE(cell);
    return NULL;
}


bool DayCell::init(int propType){
    if(!Sprite::init()){
        return false;
    }
    half =4;
    auto bgTop =Sprite::create("daily/sign/pride_bg.png");
    bgTop->setPosition(0,150);
    bgTop->setTag(101);
    addChild(bgTop);
    
    
    auto bgMid = Sprite::create("daily/sign/pride_bg.png");
    bgMid->setPosition(0,0);
    bgMid->setTag(102);
    addChild(bgMid);
    
    auto bgBot =Sprite::create("daily/sign/pride_bg.png");
    bgBot->setPosition(0,-150);
    bgBot->setTag(103);
    addChild(bgBot);
    
    auto light = Sprite::create("daily/sign/pride_light.png");
    light->setPosition(0,0);
    light->setTag(104);
    addChild(light);
    
    auto content = Sprite::create();
    content->setPosition(0, 0);
    content->setTag(105);
    addChild(content);
    content->setTexture("daily/sign/uknow_pride.png");
    Sprite* state = Sprite::create();
    state->setPosition(0,-95);
    state->setTag(106);
    addChild(state);
    
    return true;
}


void DayCell::setDayState(int type){
    Sprite* sp = (Sprite*)getChildByTag(106);
    if(NULL!= sp){
        if(type ==1){
            sp->setTexture("daily/sign/ke_chou_jiang.png");
        }else if(type ==2){
            
            sp->setTexture("daily/sign/yi_ling_qu.png");
        }else{
            sp->setTexture("daily/sign/wei_man_zhu.png");
            
        }
        
    }
    
}

void DayCell::startAnimate(){
    for(int i=1;i<7;i++){
        Sprite* sp = (Sprite*)getChildByTag(100+i);
        sp->setVisible(false);
    }
    //
    Sprite* content1 =Sprite::create("daily/sign/prop_list2.png");
    content1->setTag(601);
    content1->setPosition(0,75-150*1);
    addChild(content1);
    Sprite* content2 =Sprite::create("daily/sign/prop_list2.png");
    content2->setPosition(0,75-150*1+905);
    content2->setTag(602);
    addChild(content2);
    
    content1->runAction(Sequence::create(EaseSineIn::create(MoveBy::create(half, Vec2(0, -half * 1600))), CallFunc::create([=]{
        content1->runAction(Repeat::create(MoveBy::create(half, Vec2(0, -half * 1600)), CC_REPEAT_FOREVER));

    }), nullptr));
    content2->runAction(Sequence::create(EaseSineIn::create(MoveBy::create(half, Vec2(0, -half * 1600))), CallFunc::create([=]{
        
        content2->runAction(Repeat::create(MoveBy::create(half, Vec2(0, -half * 1600)), CC_REPEAT_FOREVER));
        
    }), nullptr));
    scheduleUpdate();
}


void DayCell::showPropResult(PrideData data){
    int m_curindex;
    if(data.type == PrideType::gold){
        m_curindex=0;
    }else if(data.type == PrideType::lequan){
        m_curindex=1;
    }else if(data.type == PrideType::lockDiammond){
        m_curindex=2;
    }else if(data.type == PrideType::diamond){
        m_curindex=3;
    }
      //道具数量
    LabelAtlas* label = LabelAtlas::create(cocos2d::String::createWithFormat("%d",data.number)->_string,"daily/sign/pride_num.png",16,24,'0');
    label->setAnchorPoint(Point::ANCHOR_MIDDLE);
    label->setPosition(0,-45);
    addChild(label);
    
    Sprite* content1 = (Sprite*)getChildByTag(601);
    Sprite* content2 = (Sprite*)getChildByTag(602);
    float posY = 75 - m_curindex * 150;
    posY = ((int)posY) % 905;
    content1->stopAllActions();
    content2->stopAllActions();
    content1->setPositionY(posY- 905);
    content2->setPositionY(posY );
    Sprite* state = Sprite::create("daily/sign/yi_ling_qu.png");
    state->setPosition(0,-95);
    addChild(state);
}



void DayCell::update(float dt){
    
    Sprite* content1 = (Sprite*)getChildByTag(601);
    Sprite* content2 = (Sprite*)getChildByTag(602);
    if (content1->getPositionY() + 905 <= 0)
    {
        content1->setPositionY(content2->getPositionY() + 905);
    }
    
    if (content2->getPositionY() + 905<=0)
    {
        content2->setPositionY(content1->getPositionY() + 905);
    }
}


