//
//  CompetitonLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/5/19.
//
//

#include "mahjong/lobby/competition/CompetitonLayer.hpp"
#include "mahjong/common/loading/Loading.h"
#include"mahjong/gameview/MjGameScene.h"
#include "server/NetworkManage.h"

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
    
    auto time = Label::createWithSystemFont("比赛时间:", "arial", 28);
    time->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    time->setPosition(845,400);
    addChild(time);
    
    auto time2 = Label::createWithSystemFont("满4人开赛", "arial", 28);
    time2->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    time2->setPosition(860,400);
    addChild(time2);
    
    auto fee = Label::createWithSystemFont("报 名 费:", "arial", 28);
    fee->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    fee->setPosition(845,345);
    addChild(fee);
    
    auto fee2 = Label::createWithSystemFont(StringUtils::format("%s张房卡",fangka.c_str()), "arial", 28);
    fee2->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    fee2->setPosition(860,345);
    addChild(fee2);
    
    
    auto difen = Label::createWithSystemFont("房间底分:", "arial", 28);
    difen->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    difen->setPosition(845,285);
    addChild(difen);
    
    auto difen2 = Label::createWithSystemFont("1/1无勒子", "arial", 28);
    difen2->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    difen2->setPosition(860,285);
    addChild(difen2);
    
    auto joinBtn = MenuItemImage::create("competition/competition_btn_1.png", "competition/competition_btn_2.png", CC_CALLBACK_1(CompetitonLayer::joinCompetiton,this));
    joinBtn->setTag((int)roomId);
    auto joinMenu = Menu::create(joinBtn, NULL);
    joinMenu->setPosition(640, 110);
    addChild(joinMenu);
    
}

void CompetitonLayer::onEnter(){
    Layer::onEnter();
    joinResp = EventListenerCustom::create(MSG_JOIN_COMPETITION_RESP, [=](EventCustom* event){
        JoinCompetitionData* result = static_cast<JoinCompetitionData*>(event->getUserData());
        JoinCompetitionData newData = *result;
        if(newData.result == 1){
            if(atoi(newData.roomId.c_str()) == CompetitionRoomId::Shanghai_High||atoi(newData.roomId.c_str()) == CompetitionRoomId::Shanghai_Normal){
                GAMEDATA::getInstance()->setIsCompetitionQueue(true);
                GAMEDATA::getInstance()->setGameType(1);
                Director::getInstance()->replaceScene(TransitionFade::create(1, MjGameScene::create()));
            }else{
                GAMEDATA::getInstance()->setIsCompetitionQueue(true);
                GAMEDATA::getInstance()->setGameType(3);
                Director::getInstance()->replaceScene(TransitionFade::create(1, MjGameScene::create()));
            }
        }else{
            removeFromParent();
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(joinResp, 1);
}


void CompetitonLayer::onExit(){
    Layer::onExit();
}


void CompetitonLayer::closeView(){
    removeFromParent();
}

void CompetitonLayer::joinCompetiton(Ref* ref){
    Loading* lod = Loading::create();
    addChild(lod);
    MenuItemImage* tem =  (MenuItemImage*) ref;
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendJoinCompetiotnCommand(StringUtils::format("%d",tem->getTag())));
}
