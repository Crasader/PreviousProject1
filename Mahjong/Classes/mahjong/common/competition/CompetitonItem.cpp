//
//  CompetitonItem.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/5/19.
//
//

#include "mahjong/common/competition/CompetitonItem.hpp"
#include "mahjong/common/competition/CompetitonLayer.hpp"
#include "mahjong/common/dialog/prompt/HintDialog.hpp"
#include "mahjong/common/competition/CompetitionResult.hpp"
#include "mahjong/lobby/shop/fangka/FangkaNotEnoughDialog.hpp"
#include "mahjong/common/dialog/prompt/HintDialog.hpp"
#include "userdata/UserData.h"
#include "server/NetworkManage.h"
#include"mahjong/gameview/MjGameScene.h"

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
    
    auto room_1 = Sprite::create("competition/item_bg.png");
    room_1->setTag(roomId);
    room_1->setPosition(0,0);
    addChild(room_1);
    
    auto quan = Sprite::create("competition/com_hau_fei.png");
    quan->setPosition(-350,0);
    addChild(quan);
    
    auto huafeiNum = LabelAtlas::create(haufei, "competition/huafei_num_mj.png", 18,30, '0');
    huafeiNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    huafeiNum->setPosition(-280,25);
    addChild(huafeiNum);
    
    auto content = Sprite::create("competition/huafei_text_mj.png");
    content->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    content->setPosition(huafeiNum->getPositionX()+huafeiNum->getContentSize().width-5,25);
    addChild(content);
    
    auto title = Sprite::create();
    if(roomId ==  CompetitionRoomId::Shanghai_Normal||roomId ==  CompetitionRoomId::Shanghai_High){
        title->setTexture("competition/com_text_sh.png");
    }else if(roomId ==  CompetitionRoomId::Hongzhong_Normal||roomId ==  CompetitionRoomId::Hongzhong_High){
        title->setTexture("competition/com_text_hz.png");
    }
    title->setPosition(-280,-25);
    title->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(title);
    
    auto jiangli = Sprite::create("competition/jiangli_text.png");
    jiangli->setPosition(-70,-25);
    addChild(jiangli);
    
    auto joinImg = MenuItemImage::create("competition/btn_bao_ming_1.png", "competition/btn_bao_ming_2.png",CC_CALLBACK_1(CompetitonItem::joinCompetition, this));
    auto joinMenu = Menu::create(joinImg,NULL);
    joinMenu->setPosition(300,0);
    addChild(joinMenu);
    
    auto feeLabel = Label::createWithSystemFont(StringUtils::format("X%s",fangka.c_str()), "arial", 25);
    feeLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    feeLabel->setColor(Color3B(255,255,255));
    feeLabel->setPosition(350,-2);
    addChild(feeLabel);
    
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
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendJoinCompetiotnCommand(StringUtils::format("%s",GAMEDATA::getInstance()->getCompetitionId().c_str())));
}
