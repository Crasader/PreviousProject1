//
//  IPConflict.cpp
//  SuZhouMahjong
//
//  Created by qiuzhong on 2017/11/28.
//

#include "mahjong/common/dialog/ip/IPConflict.hpp"
#include "mahjong/common/state/GameData.h"
#include "server/NetworkManage.h"
#include "mahjong/lobby/LobbyScene.h"
#include "mahjong/common/widget/HeadImage.hpp"

bool IPConflict::init(){
    
    if(!Layer::init()){
        return false;
    }
//    IPConflictData data = GAMEDATA::getInstance()->getIPConflictData();
//    data.line  = "1,2,3";
//    data.IP1  = "1,2,3";
//    GAMEDATA::getInstance()->setIPConflictData(data);
    
    auto bg0 = LayerColor::create(Color4B(0, 0, 0, 180), 1280, 720);
    addChild(bg0);
    
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
    
//    auto  dialogBg = Sprite::create("common/dialog_bg_small.png");
//    dialogBg->setPosition(640, 360);
//    this->addChild(dialogBg);
    
//    auto zhuyi = Sprite::create("common/title_zhuyi.png");
//    zhuyi->setPosition(640, 505);
//    addChild(zhuyi);
    
    auto closeImage = MenuItemImage::create("common/tuichu_youxi_1.png", "common/tuichu_youxi_2.png", CC_CALLBACK_0(IPConflict::quitGame, this));
        closeImage->setScale(0.8);
    auto continueImage = MenuItemImage::create("common/jixu_youxi_1.png", "common/jixu_youxi_2.png", CC_CALLBACK_0(IPConflict::closeView, this));
     continueImage->setScale(0.8);
    auto closeMenu = Menu::create(continueImage,closeImage, NULL);
    closeMenu->alignItemsHorizontallyWithPadding(20);
    closeMenu->setPosition(640, 140);
    addChild(closeMenu);
    
//    auto nickname1 = Label::createWithSystemFont("", "arial",25);
//    nickname1->setPosition(510,475);
//    nickname1->setWidth(110);
//    nickname1->setHeight(30);
//    nickname1->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
//    nickname1->setAlignment(cocos2d::TextHAlignment::RIGHT);
//    nickname1->setColor(Color3B(0,0,0));
//    addChild(nickname1);
//    auto image1 = HeadImage::create(Size(65,65));
//    image1->setPosition(550,475);
//    addChild(image1);
//
//    auto nickname2 = Label::createWithSystemFont("", "arial",25);
//    nickname2->setPosition(760,475);
//    nickname2->setWidth(110);
//    nickname2->setHeight(30);
//    nickname2->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
//    nickname2->setAlignment(cocos2d::TextHAlignment::LEFT);
//    nickname2->setColor(Color3B(0,0,0));
//    addChild(nickname2);
//    auto image2 = HeadImage::create(Size(65,65));
//    image2->setPosition(730,475);
//    addChild(image2);
//
//    auto nickname3 = Label::createWithSystemFont("", "arial",25);
//    nickname3->setPosition(520,300);
//    nickname3->setWidth(110);
//    nickname3->setHeight(30);
//    nickname3->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
//    nickname3->setAlignment(cocos2d::TextHAlignment::RIGHT);
//    nickname3->setColor(Color3B(0,0,0));
//    addChild(nickname3);
//    auto image3 = HeadImage::create(Size(65,65));
//    image3->setPosition(550,320);
//    addChild(image3);
//
//    auto nickname4 = Label::createWithSystemFont("", "arial",25);
//    nickname4->setPosition(760,300);
//    nickname4->setWidth(110);
//    nickname4->setHeight(30);
//    nickname4->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
//    nickname4->setAlignment(cocos2d::TextHAlignment::LEFT);
//    nickname4->setColor(Color3B(0,0,0));
//    addChild(nickname4);
//    auto image4 = HeadImage::create(Size(65,65));
//    image4->setPosition(730,320);
//    addChild(image4);
//
//    for(int i=0;i<GAMEDATA::getInstance()->getPlayersInfo().size();i++){
//        if(GAMEDATA::getInstance()->getPlayersInfo().at(i)->getSeatId() == 1){
//            nickname1->setString(GAMEDATA::getInstance()->getPlayersInfo().at(i)->getNickname());
//            image1->updateImageByName(GAMEDATA::getInstance()->getPlayersInfo().at(i)->getPicture());
//        }else  if(GAMEDATA::getInstance()->getPlayersInfo().at(i)->getSeatId() == 2){
//            nickname2->setString(GAMEDATA::getInstance()->getPlayersInfo().at(i)->getNickname());
//             image2->updateImageByName(GAMEDATA::getInstance()->getPlayersInfo().at(i)->getPicture());
//        }else  if(GAMEDATA::getInstance()->getPlayersInfo().at(i)->getSeatId() == 3){
//            nickname3->setString(GAMEDATA::getInstance()->getPlayersInfo().at(i)->getNickname());
//             image3->updateImageByName(GAMEDATA::getInstance()->getPlayersInfo().at(i)->getPicture());
//        }else  if(GAMEDATA::getInstance()->getPlayersInfo().at(i)->getSeatId() == 4){
//            nickname4->setString(GAMEDATA::getInstance()->getPlayersInfo().at(i)->getNickname());
//             image4->updateImageByName(GAMEDATA::getInstance()->getPlayersInfo().at(i)->getPicture());
//        }
//    }
//
//    //
//    auto arrow1 = Sprite::create("gameview/jiantou_1.png");
//    arrow1->setPosition(640,475);
//    addChild(arrow1);
//    arrow1->setVisible(false);
//    auto text1 = Label::createWithSystemFont("<30m", "arial", 20);
//    text1->setColor(Color3B::RED);
//    text1->setPosition(640,495);
//    addChild(text1);
//    text1->setVisible(false);
//
//    auto arrow2 = Sprite::create("gameview/jiantou_2.png");
//    arrow2->setPosition(730,400);
//    addChild(arrow2);
//    arrow2->setVisible(false);
//    auto text2 = Label::createWithSystemFont("<30m", "arial", 20);
//    text2->setColor(Color3B::RED);
//    text2->setPosition(770,400);
//    addChild(text2);
//    text2->setVisible(false);
//
//    auto arrow3 = Sprite::create("gameview/jiantou_1.png");
//    arrow3->setPosition(640,325);
//    addChild(arrow3);
//    arrow3->setVisible(false);
//    auto text3 = Label::createWithSystemFont("<30m", "arial", 20);
//    text3->setColor(Color3B::RED);
//    text3->setPosition(640,305);
//    addChild(text3);
//    text3->setVisible(false);
//
//    auto arrow4 = Sprite::create("gameview/jiantou_2.png");
//    arrow4->setPosition(550,400);
//    addChild(arrow4);
//    arrow4->setVisible(false);
//    auto text4 = Label::createWithSystemFont("<30m", "arial", 20);
//    text4->setColor(Color3B::RED);
//    text4->setPosition(510,400);
//    addChild(text4);
//    text4->setVisible(false);
//
//    auto arrow5 = Sprite::create("gameview/jiantou_3.png");
//    arrow5->setPosition(640,400);
//    addChild(arrow5);
//    arrow5->setVisible(false);
//    auto text5 = Label::createWithSystemFont("<30m", "arial", 20);
//    text5->setColor(Color3B::RED);
//    text5->setPosition(640,440);
//    addChild(text5);
//    text5->setVisible(false);
//
//    auto arrow6 = Sprite::create("gameview/jiantou_4.png");
//    arrow6->setPosition(640,400);
//    addChild(arrow6);
//    arrow6->setVisible(false);
//    auto text6 = Label::createWithSystemFont("<30m", "arial", 20);
//    text6->setColor(Color3B::RED);
//    text6->setPosition(640,360);
//    addChild(text6);
//    text6->setVisible(false);
//
//    std::string msg = GAMEDATA::getInstance()->getIPConflictData().line;
//    if(msg.find("1")!=std::string::npos){
//        arrow1->setVisible(true);
//        text1->setVisible(true);
//    }
//    if(msg.find("2")!=std::string::npos){
//        arrow2->setVisible(true);
//        text2->setVisible(true);
//    }
//    if(msg.find("3")!=std::string::npos){
//        arrow3->setVisible(true);
//        text3->setVisible(true);
//    }
//    if(msg.find("4")!=std::string::npos){
//        arrow4->setVisible(true);
//        text4->setVisible(true);
//    }
//    if(msg.find("5")!=std::string::npos){
//        arrow5->setVisible(true);
//        text5->setVisible(true);
//    }
//    if(msg.find("6")!=std::string::npos){
//        arrow6->setVisible(true);
//        text6->setVisible(true);
//    }
    
//
    auto spr = Sprite::create();
    spr->setPosition(640,480);
    addChild(spr);
    
    auto animation = Animation::create();
    std::string index;
    for( int i=1;i<=24;i++)
    {
        std::string imageName = StringUtils::format ("fangzuobi/jiance_00%d.png",i);
        animation->addSpriteFrameWithFile(imageName);
    }
    // should last 1 seconds. And there are 24 frames.
    animation->setDelayPerUnit(1.0f / 12.0f);
    animation->setRestoreOriginalFrame(false);
    auto action = Animate::create(animation);
    spr->runAction(Repeat::create(action, 5));
    
    if(GAMEDATA::getInstance()->getIPConflictData().IP1 != ""){
        auto ipWarn = Sprite::create("fangzuobi/warn_bg.png");
        ipWarn->setPosition(640,300);
        addChild(ipWarn);
        std::vector<std::string> seat = StringUtil::split(GAMEDATA::getInstance()->getIPConflictData().IP1, ",");
        for (int i=0; i<seat.size(); i++) {
            auto image = HeadImage::create(Size(55,55));
            image->setPosition(520+i*70,300);
             for(int j=0;j<GAMEDATA::getInstance()->getPlayersInfo().size();j++){
                 if(atoi(seat.at(i).c_str()) == GAMEDATA::getInstance()->getPlayersInfo().at(j)->getSeatId()){
                     image->updateImageByName(GAMEDATA::getInstance()->getPlayersInfo().at(j)->getPicture());
                 }
             }
            addChild(image);
        }
        auto ipinfo = Label::createWithSystemFont("IP地址相同", "arial", 30);
        ipinfo->setPosition(700,300);
        ipinfo->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        ipinfo->setAlignment(cocos2d::TextHAlignment::LEFT);
        addChild(ipinfo);
    }

     if(GAMEDATA::getInstance()->getIPConflictData().line != ""){
         auto locationWarn = Sprite::create("fangzuobi/warn_bg.png");
         locationWarn->setPosition(640,220);
         addChild(locationWarn);
         std::vector<std::string> seat = StringUtil::split(GAMEDATA::getInstance()->getIPConflictData().line, ",");
         for (int i=0; i<seat.size(); i++) {
             auto image = HeadImage::create(Size(55,55));
             image->setPosition(520+i*70,220);
             for(int j=0;j<GAMEDATA::getInstance()->getPlayersInfo().size();j++){
                 if(atoi(seat.at(i).c_str()) == GAMEDATA::getInstance()->getPlayersInfo().at(j)->getSeatId()){
                     image->updateImageByName(GAMEDATA::getInstance()->getPlayersInfo().at(j)->getPicture());
                 }
             }
             addChild(image);
         }
         auto location = Label::createWithSystemFont("距离过近", "arial", 30);
         location->setPosition(700,220);
         location->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
         location->setAlignment(cocos2d::TextHAlignment::LEFT);
         addChild(location);
     }
    
    return true;
}

void IPConflict::closeView(){
    removeFromParent();
}
void IPConflict::quitGame(){
    GAMEDATA::getInstance()->clearPlayersInfo();
    if(GAMEDATA::getInstance()->getGameType() == 1){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getQuitRoomCommand());
    }else if (GAMEDATA::getInstance()->getGameType() == 3){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getHZQuitRoomCommand());
    }else if (GAMEDATA::getInstance()->getGameType() == 5){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getBDQuitRoomCommand());
    }
    Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
}
