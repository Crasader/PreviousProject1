//
//  CompetitonItem.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/5/19.
//
//

#include "mahjong/common/competition/CompetitonItem.hpp"
#include "mahjong/common/competition/CompetitonLayer.hpp"

CompetitonItem* CompetitonItem::create(CompetitionRoomId roomId,std::string haufei,std::string fangka,std::string rule){
    CompetitonItem* cell = new CompetitonItem();
    if(cell && cell->init(roomId,haufei,fangka,rule)){
        cell -> autorelease();
        return cell;
    }
    CC_SAFE_DELETE(cell);
    return NULL;
}

bool CompetitonItem::init(CompetitionRoomId roomId,std::string haufei,std::string fangka,std::string rule){
    if(!Sprite::init()){
        return false;
    }
    setRoomId(roomId);
    setFangka(fangka);
    setHuaFei(haufei);
    setRule(rule);
    auto room_1 = MenuItemImage::create("mjlobby/competition_1_1.png", "mjlobby/competition_1_2.png", CC_CALLBACK_1(CompetitonItem::joinCompetition, this));
    if(roomId ==  CompetitionRoomId::Shanghai_High||roomId ==  CompetitionRoomId::Hongzhong_High){
        auto image1 = Sprite::create("mjlobby/competition_2_1.png");
        room_1->setNormalImage(image1);
        auto image2 = Sprite::create("mjlobby/competition_2_2.png");
        room_1->setSelectedImage(image2);
    }
    room_1->setTag(roomId);
    auto roomSelect = Menu::create(room_1,NULL);
    roomSelect->setPosition(0,0);
    addChild(roomSelect);
    
    auto huafeiNum = LabelAtlas::create(haufei, "mjlobby/huafei_num_g.png", 27,48, '0');
    if(roomId ==  CompetitionRoomId::Shanghai_High||roomId ==  CompetitionRoomId::Hongzhong_High){
        auto textu = Director::getInstance()->getTextureCache()->addImage("mjlobby/huafei_num_y.png");
        huafeiNum->setTexture(textu);
    }
    huafeiNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
    huafeiNum->setPosition(-125,20);
    addChild(huafeiNum);
    
    auto content = Sprite::create("mjlobby/huafei_text_g.png");
    if(roomId ==  CompetitionRoomId::Shanghai_High||roomId ==  CompetitionRoomId::Hongzhong_High){
        content->setTexture("mjlobby/huafei_text_y.png");
    }
    content->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    content->setPosition(huafeiNum->getPositionX()+huafeiNum->getContentSize().width/2-10,20);
    addChild(content);
    
    auto title = Sprite::create();
    if(roomId ==  CompetitionRoomId::Shanghai_Normal){
        title->setTexture("mjlobby/shanghai_g.png");
    }else if(roomId ==  CompetitionRoomId::Shanghai_High){
        title->setTexture("mjlobby/shanghai_y.png");
    }else if(roomId ==  CompetitionRoomId::Hongzhong_Normal){
        title->setTexture("mjlobby/hongzhong_g.png");
    }else if(roomId ==  CompetitionRoomId::Hongzhong_High){
        title->setTexture("mjlobby/hongzhong_y.png");
    }
    title->setPosition(-80,-25);
    addChild(title);
    
    
    auto feeLabel = Label::createWithSystemFont(StringUtils::format("(%s张房卡)",fangka.c_str()), "arial", 20);
    feeLabel->setAnchorPoint(Point::ANCHOR_MIDDLE);
    if(roomId ==  CompetitionRoomId::Shanghai_High||roomId ==  CompetitionRoomId::Hongzhong_High){
        feeLabel->setColor(Color3B(252,232,192));
    }else{
        feeLabel->setColor(Color3B(193,255,203));
    }
    feeLabel->setPosition(102,15);
    addChild(feeLabel);
    
    return true;
}
#include "mahjong/common/competition/CompetitionResult.hpp"
void CompetitonItem::joinCompetition(Ref* ref){
    GAMEDATA::getInstance()->setCompetitionId(StringUtils::format("%d",getRoomId()));
    GAMEDATA::getInstance()->setCompetitionPride(getHuaFei());
    CompetitonLayer* lay = CompetitonLayer::create();
    lay->initView(getRoomId(),getHuaFei(),getFangka(),getRule());
    getParent()->addChild(lay,5);
}
