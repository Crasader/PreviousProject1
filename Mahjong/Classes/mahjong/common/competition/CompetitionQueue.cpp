//
//  CompetitionQueue.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/5/17.
//
//

#include "mahjong/common/competition/CompetitionQueue.hpp"
#include "mahjong/common/loading/Loading.h"
#include "mahjong/lobby/LobbyScene.h"
#include "server/NetworkManage.h"


//competition_queue_bg.png

bool CompetitionQueue::init(){
    if(!Layer::init()){
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Sprite* view_bg = Sprite::create("gameview/game_bg.jpg");
    view_bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    addChild(view_bg, -1);
    
    auto queueBg = Sprite::create("competition/competition_queue_bg.png");
    queueBg->setPosition(640,360);
    addChild(queueBg);
    
    auto queueTitle = Sprite::create("competition/queue_title_bg.png");
    queueTitle->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    queueTitle->setPosition(640,720);
    addChild(queueTitle);
    
    auto prideNum = LabelAtlas::create(GAMEDATA::getInstance()->getCompetitionPride(), "competition/huafei_num.png", 48, 76, '0');
    prideNum->setScale(0.8);
    prideNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(prideNum);
    
    auto huatext = Sprite::create("competition/huafei_text.png");
    huatext->setScale(0.8f);
    huatext->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(huatext);
    
    int wid = prideNum->getContentSize().width+huatext->getContentSize().width;
    prideNum->setPosition(640-wid/2*0.8f,685);
    huatext->setPosition(640-wid/2*0.8f+prideNum->getContentSize().width*0.8f,685);
    
    auto title = Sprite::create();
    if(atoi(GAMEDATA::getInstance()->getCompetitionId().c_str()) == CompetitionRoomId::Shanghai_High || atoi(GAMEDATA::getInstance()->getCompetitionId().c_str()) == CompetitionRoomId::Shanghai_Normal){
        title->setTexture("competition/shanghai_title.png");
    }else{
        title->setTexture("competition/hongzhong_title.png");
    }
    addChild(title);
    title->setPosition(640,635);
    
    auto wait = Sprite::create("competition/wait_text.png");
    wait->setPosition(640,455);
    addChild(wait);
    
    
    auto info = Label::createWithSystemFont(GAMEDATA::getInstance()->getCompetitionText(), "arial", 30);
    info->setAnchorPoint(Point::ANCHOR_MIDDLE);
    info->setColor(Color3B(153,226,220));
    info->setPosition(640,210);
    addChild(info);
    
    auto quitBtn = MenuItemImage::create("competition/qiut_competition_1.png", "competition/qiut_competition_2.png", CC_CALLBACK_0(CompetitionQueue::quitCompetiton,this));
    auto quitMenu = Menu::create(quitBtn, NULL);
    quitMenu->setPosition(640, 125);
    addChild(quitMenu);

    for (int i=0; i<4; i++) {
        auto waitPlayer = Sprite::create("competition/player_wait.png");
        waitPlayer->setPosition(375+i*165,350);
        addChild(waitPlayer);
    }

    auto playerReady = Sprite::create("gameview/head_image_3.png");
    playerReady->setScale(1.3778);
    playerReady->setPosition(375,350);
    addChild(playerReady);
    
    auto playerLight = Sprite::create("competition/head_white.png");
    playerLight->setPosition(375,350);
    addChild(playerLight);
    
    return true;
}

void CompetitionQueue::quitCompetiton(){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendQuitCompetitionCommand(GAMEDATA::getInstance()->getCompetitionId()));
}

void CompetitionQueue::onEnter(){
    Layer::onEnter();
    quitResp = EventListenerCustom::create(MSG_QUIT_COMPETITON_RESP, [=](EventCustom* event){
        std::string reslut = static_cast<char*>(event -> getUserData());
        if(reslut == "1"){
            Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
            GAMEDATA::getInstance()->setIsCompetitionQueue(false);
        }else{
            //TODO 退出房间失败
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(quitResp, 1);
    
}


void CompetitionQueue::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(quitResp);
}
