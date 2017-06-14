//
//  CompetitonLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/5/19.
//
//

#include "mahjong/common/competition/CompetitonLayer.hpp"
#include "mahjong/common/loading/Loading.h"
#include"mahjong/gameview/MjGameScene.h"
#include "server/NetworkManage.h"
#include "mahjong/common/competition/CompetitionResult.hpp"
#include "mahjong/lobby/shop/fangka/FangkaNotEnoughDialog.hpp"
#include "mahjong/common/utils/StringUtil.h"
#include "mahjong/common/dialog/prompt/HintDialog.hpp"

bool CompetitonLayer::init(){
    
    if(!Layer::init()){
        return false;
    }
    MenuItem* item1 = MenuItem::create();
    Size visibileSize = Director::getInstance()->getVisibleSize();
    item1->setContentSize(visibileSize);
    Menu* menu1 = Menu::create(item1, NULL);
    addChild(menu1);
    
    auto comBg = Sprite::create("competition/competition_bg.png");
    comBg->setPosition(640,360);
    addChild(comBg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(CompetitonLayer::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(1150, 642);
    addChild(closeMenu);
    title = Sprite::create("competition/shanghai_text.png");
    title->setPosition(415,600);
    addChild(title);
    
    huafeiNum = LabelAtlas::create("0", "competition/huafei_num.png", 48, 76, '0');
    huafeiNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    huafeiNum->setPosition(530,606);
    addChild(huafeiNum);
    
    text = Sprite::create("competition/huafei_text.png");
    text->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    
    addChild(text);
    
    auto ruleTitle = Sprite::create("competition/competition_rule.png");
    ruleTitle->setPosition(380,460);
    addChild(ruleTitle);
    
    auto prideTitle = Sprite::create("competition/competition_pride.png");
    prideTitle->setPosition(780,460);
    addChild(prideTitle);
    
    prideNum = LabelAtlas::create("0", "competition/pride_num.png", 28, 46, '0');
    prideNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    prideNum->setPosition(865,465);
    addChild(prideNum);
    
    huatext = Sprite::create("competition/hua_fei_text.png");
    huatext->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(huatext);
    
    auto time = Label::createWithSystemFont("比赛时间:", "arial", 28);
    time->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    time->setPosition(845,400);
    addChild(time);
    
    auto time2 = Label::createWithSystemFont("满4人开赛", "arial", 28);
    time2->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    time2->setPosition(860,400);
    addChild(time2);
    
    auto fee1 = Label::createWithSystemFont("报", "arial", 28);
    fee1->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    fee1->setPosition(752,345);
    addChild(fee1);
    
    auto fee2 = Label::createWithSystemFont("名", "arial", 28);
    fee2->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    fee2->setPosition(793,345);
    addChild(fee2);
    
    auto fee3 = Label::createWithSystemFont("费:", "arial", 28);
    fee3->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    fee3->setPosition(845,345);
    addChild(fee3);
    
    fee4 = Label::createWithSystemFont("", "arial", 28);
    fee4->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    fee4->setPosition(860,345);
    addChild(fee4);
    
    
    auto difen = Label::createWithSystemFont("房间底分:", "arial", 28);
    difen->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    difen->setPosition(845,285);
    addChild(difen);
    
    difen2 = Label::createWithSystemFont("5/5无勒子", "arial", 28);
    difen2->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    difen2->setPosition(860,285);
    addChild(difen2);
    
    auto joinBtn = MenuItemImage::create("competition/competition_btn_1.png", "competition/competition_btn_2.png", CC_CALLBACK_1(CompetitonLayer::joinCompetiton,this));
    auto joinMenu = Menu::create(joinBtn, NULL);
    joinMenu->setPosition(640, 110);
    addChild(joinMenu);
    
    return  true;
}


void CompetitonLayer::initView(CompetitionRoomId roomId,std::string huafei,std::string fangka,std::string rule){
    if(roomId == CompetitionRoomId::Hongzhong_High||roomId == Hongzhong_Normal){
        title->setTexture("competition/hongzhong_text.png");
    }
    string newRule = "       "+rule;
    vector<std::string> rules = StringUtil::split(newRule,"|");
    for(int i= 0; i< rules.size();i++){
        ruleText = Label::createWithSystemFont("", "arial", 28);
        ruleText->setWidth(338);
        ruleText->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
        ruleText->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
        ruleText->setPosition(560,405-40*i);
        addChild(ruleText);
        ruleText->setString(StringUtils::format("%s",rules.at(i).c_str()));
    }
    
    huafeiNum->setString(huafei);
    prideNum->setString(huafei);
    fee4->setString(StringUtils::format("%s张房卡",fangka.c_str()));
    if(roomId == CompetitionRoomId::Hongzhong_Normal||roomId == CompetitionRoomId::Hongzhong_High){
        difen2->setString("5底分1码");
    }
    text->setPosition(huafeiNum->getPositionX()+huafeiNum->getContentSize().width,606);
    huatext->setPosition(prideNum->getPositionX()+prideNum->getContentSize().width,465);
}

void CompetitonLayer::onEnter(){
    Layer::onEnter();
    joinResp = EventListenerCustom::create(MSG_JOIN_COMPETITION_RESP, [=](EventCustom* event){
        JoinCompetitionData* result = static_cast<JoinCompetitionData*>(event->getUserData());
        JoinCompetitionData newData = *result;
        if(newData.result == 1){
            GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
            GAMEDATA::getInstance()->setCompetitionId(newData.roomId);
            GAMEDATA::getInstance()->setCompetitionText(newData.text);
            GAMEDATA::getInstance()->setCompetitionNumber(newData.num);
            if(atoi(newData.roomId.c_str()) == CompetitionRoomId::Shanghai_High||atoi(newData.roomId.c_str()) == CompetitionRoomId::Shanghai_Normal){
                GAMEDATA::getInstance()->setIsCompetitionQueue(true);
                GAMEDATA::getInstance()->setGameType(1);
                Director::getInstance()->replaceScene(TransitionFade::create(0.1, MjGameScene::create()));
            }else{
                GAMEDATA::getInstance()->setIsCompetitionQueue(true);
                GAMEDATA::getInstance()->setGameType(3);
                Director::getInstance()->replaceScene(TransitionFade::create(0.1, MjGameScene::create()));
            }
        }else  if(newData.result == 2||newData.result == 3){
            HintDialog* dialog = HintDialog::create(newData.tip != ""?newData.tip:"功能暂不可用",[=](Ref* ref){
                removeFromParent();
            },[=](Ref* ref){
                removeFromParent();
            });
            addChild(dialog,100);
        }else{
            if(NULL != getChildByTag(1024)){
                getChildByTag(1024)->removeFromParentAndCleanup(true);
            }
            FangkaNotEnoughDialog* da =  FangkaNotEnoughDialog::create();
            if(GAMEDATA::getInstance()->getCompetitionId() == StringUtils::format("%d",CompetitionRoomId::Shanghai_High)||
               GAMEDATA::getInstance()->getCompetitionId() == StringUtils::format("%d",CompetitionRoomId::Hongzhong_High)){
                da->initView(5,24);
                
            }else{
                da->initView(1,5);
            }
            addChild(da);
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(joinResp, 1);
}


void CompetitonLayer::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(joinResp);
}


void CompetitonLayer::closeView(){
    removeFromParent();
}

void CompetitonLayer::joinCompetiton(Ref* ref){
    if(NULL == getChildByTag(1024)){
        Loading* lod = Loading::create();
        lod->setTag(1024);
        addChild(lod);
    }
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendJoinCompetiotnCommand(StringUtils::format("%s",GAMEDATA::getInstance()->getCompetitionId().c_str())));
}
