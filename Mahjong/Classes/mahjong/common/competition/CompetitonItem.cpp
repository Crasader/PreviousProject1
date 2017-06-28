//
//  CompetitonItem.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/5/19.
//
//

#include "mahjong/common/competition/CompetitonItem.hpp"
#include "mahjong/common/competition/CompetitonLayer.hpp"
#include "userdata/UserData.h"

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
    if(roomId ==  CompetitionRoomId::Shanghai_High||roomId ==  CompetitionRoomId::Shanghai_Normal){
        auto image1 = Sprite::create("mjlobby/competition_2_1.png");
        room_1->setNormalImage(image1);
        auto image2 = Sprite::create("mjlobby/competition_2_2.png");
        room_1->setSelectedImage(image2);
    }
    room_1->setTag(roomId);
    auto roomSelect = Menu::create(room_1,NULL);
    roomSelect->setPosition(0,0);
    addChild(roomSelect);
    
    auto huafeiNum = LabelAtlas::create(haufei, "mjlobby/huafei_num_y.png", 22,40, '0');
    huafeiNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    huafeiNum->setPosition(-105,50);
    addChild(huafeiNum);
    
    auto content = Sprite::create("mjlobby/huafei_text_y.png");
    content->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    content->setPosition(huafeiNum->getPositionX()+huafeiNum->getContentSize().width-5,50);
    addChild(content);
    
    //    if(!UserData::getInstance()->isWeixinPayOpen()){
    //        huafeiNum->setVisible(false);
    //        content->setTexture("mjlobby/check_fangka_2.png");
    //        if(roomId ==  CompetitionRoomId::Shanghai_High||roomId ==  CompetitionRoomId::Hongzhong_High){
    //            content->setTexture("mjlobby/check_fangka_8.png");
    //        }
    //
    //    }
    
    auto title = Sprite::create();
    if(roomId ==  CompetitionRoomId::Shanghai_Normal||roomId ==  CompetitionRoomId::Shanghai_High){
        title->setTexture("mjlobby/shanghai_y.png");
    }else if(roomId ==  CompetitionRoomId::Hongzhong_Normal||roomId ==  CompetitionRoomId::Hongzhong_High){
        title->setTexture("mjlobby/hongzhong_y.png");
    }
    title->setPosition(-105,10);
    title->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(title);
    
    auto feeLabel = Label::createWithSystemFont(StringUtils::format("房卡X%s",fangka.c_str()), "arial", 25);
    feeLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    feeLabel->setColor(Color3B(235,203,72));
    feeLabel->setPosition(-100,-30);
    addChild(feeLabel);
    
    auto title2 = Sprite::create();
    if(roomId ==  CompetitionRoomId::Shanghai_Normal||roomId ==  CompetitionRoomId::Shanghai_High){
        title2->setTexture("mjlobby/man_4_ren_sh.png");
    }else if(roomId ==  CompetitionRoomId::Hongzhong_Normal||roomId ==  CompetitionRoomId::Hongzhong_High){
        title2->setTexture("mjlobby/man_4_ren_hz.png");
    }
    title2->setPosition(70,-50);
    title2->setAnchorPoint(Point::ANCHOR_MIDDLE);
    addChild(title2);
    
    return true;
}

void CompetitonItem::joinCompetition(Ref* ref){
    GAMEDATA::getInstance()->setCompetitionId(StringUtils::format("%d",getRoomId()));
    GAMEDATA::getInstance()->setCompetitionPride(getHuaFei());
    GAMEDATA::getInstance()->setCompetitionRule(getFangka());
    GAMEDATA::getInstance()->setCompetitionFee(getRule());
    GAMEDATA::getInstance()->setPrivateKaibao("0");
    GAMEDATA::getInstance()->setPrivateLezi(StringUtils::format("%d", LeziType::type55c));
    GAMEDATA::getInstance()->setFanMaType("1");
    GAMEDATA::getInstance()->setHZDiFen("5");
    FriendOpenRoomRespData opdata = GAMEDATA::getInstance()->getFriendOpenRoomResp();
    opdata.prjushu = "4";
    GAMEDATA::getInstance()->setFriendOpenRoomResp(opdata);
    CompetitonLayer* lay = CompetitonLayer::create();
    lay->initView(getRoomId(),getHuaFei(),getFangka(),getRule());
    getParent()->addChild(lay,5);
}
