#include "game/mahjong/result/ResultLayer.h"
#include "game/mahjong/lobby/LobbyScene.h"
#include "game/mahjong/jong/Jong.h"
#include"game/mahjong/core/MjGameScene.h"
#include "game/mahjong/core/MahjongView.h"
#include "game/mahjong/lobby/EnterRoomDialog.hpp"
#include "game/mahjong/shop/GoldNotEnoughDialog.hpp"
#include "game/mahjong/shop/ChargeDiamond.hpp"
#include "game/mahjong/shop/ChargeGold.hpp"
#include "game/mahjong/dialog/prompt/HintDialog.hpp"
#include "game/utils/SeatIdUtil.h"
#include "game/utils/StringUtil.h"
#include "game/utils/Chinese.h"
#include "game/utils/ParticleUtil.hpp"
#include "server/NetworkManage.h"
#include "server/CommandManage.h"




bool ResultLayer::init(){
    if (!Layer::init()){
        return false;
    }
    initData();
    initView();
    return true;
}

void ResultLayer::onEnter(){
    Layer::onEnter();
    continueAgainLisetner =  EventListenerCustom::create(MSG_HERO_CONTINUE_RESP, [=](EventCustom* event){
        std::string result  = static_cast<char*>(event->getUserData());
        if (GAMEDATA::getInstance()->getEnterRoomResp().result == "0"){
            Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
        }else if (GAMEDATA::getInstance()->getEnterRoomResp().result == "1"){
            GAMEDATA::getInstance()->setContinueAgain(true);
            Director::getInstance()->replaceScene(TransitionFade::create(1, MjGameScene::create()));
        } else if(GAMEDATA::getInstance()->getEnterRoomResp().result == "2"){
            
            for(auto var : GAMEDATA::getInstance()->getRoomList().rooms){
                if(GAMEDATA::getInstance()->getCurrentSelectRoomId() == var.roomId){
                    GoldNotEnoughDialog* gold = GoldNotEnoughDialog::create(GAMEDATA::getInstance()->getCurrentSelectRoomId());
                    addChild(gold,30);
                }
            }
        }
        else if(GAMEDATA::getInstance()->getEnterRoomResp().result == "3"){
            if(atoi(GAMEDATA::getInstance()->getEnterRoomResp().rsid.c_str()) == ROOM_2){
                EnterRoomDialog* dia = EnterRoomDialog::create(EnterRoomDialogType::goldMoreLeve1);
                addChild(dia,30);
            }else if(atoi(GAMEDATA::getInstance()->getEnterRoomResp().rsid.c_str()) == ROOM_3){
                EnterRoomDialog* dia = EnterRoomDialog::create(EnterRoomDialogType::goldMoreLeve2);
                addChild(dia,30);
            }
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(continueAgainLisetner, 1);
    
    //登录地址变更
    playerReplaceLoginListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_PLAYER_REPLACE_LOGIN, [=](EventCustom* event){
        HintDialog* hin = HintDialog::create("你的账号在其他客户端登录",[=](Ref* ref){
            exit(0);
        });
        addChild(hin,5);
    });
}

void ResultLayer::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(continueAgainLisetner);
    Director::getInstance()->getEventDispatcher()->removeEventListener(playerReplaceLoginListener);
}

void ResultLayer::initData(){
    timeToatal = 20;
    setWinOrLose();
}

void ResultLayer::setWinOrLose(){
    vector<GameResultData> results = GAMEDATA::getInstance()->getGameResults();
    for (GameResultData data: results) {
        if(data.seatId==GAMEDATA::getInstance()->getHeroSeatId()){
            setheroData(data);
        }
    }
}



void ResultLayer::initView(){
    auto reslut_bg = Sprite::create("result/result_bg.jpg");
    reslut_bg->setPosition(640, 360);
    addChild(reslut_bg);
    //失败的玩家不播动画,分开实现
    if(getheroData().result==1||getheroData().result==3){
        showWinAnim();
    }else{
        showLoseAnim();
    }
    showHeroPropInfo();
}



void ResultLayer::showWinAnim(){
    auto title = Sprite::create();
    title->setPosition(640, 625);
    addChild(title);
    showCaidaiAnim(title);
    
    auto text = Sprite::create("result/you_win.png");
    text->setPosition(640, 625);
    text->setScale(2.0f);
    text->setOpacity(77);
    text->setVisible(false);
    addChild(text);
    text->runAction(Sequence::create(DelayTime::create(5.0f/24),CallFunc::create([=](){
        text->setVisible(true);
    }),Spawn::create(ScaleTo::create(4.0f/24, 1.0f), FadeTo::create(4.0f/24, 255),NULL),CallFunc::create([=](){
        auto icon = Sprite::create("result/you_win.png");
        icon->setPosition(640, 625);
        addChild(icon);
    }), Spawn::create(ScaleTo::create(6.0f/24, 2.5f), FadeTo::create(6.0f/24, 0),NULL),NULL));
    
    auto light = Sprite::create("result/yellow_light.png");
    light->setPosition(640, 625);
    addChild(light);
    light->setOpacity(90);
    light->setScale(0.4f);
    light->setVisible(false);
    light->runAction(Sequence::create(DelayTime::create(8.0f/24),CallFunc::create([=](){
        light->setVisible(true);
    }),Spawn::create(ScaleTo::create(3.0f/24, 6.0f), FadeTo::create(3.0f/24, 255),NULL), Spawn::create(ScaleTo::create(4.0f/24, 0.1f), FadeTo::create(4.0f/24, 0),NULL),NULL));
    
    auto infoBg = Sprite::create("result/player_info_bg.png");
    infoBg->setPosition(640, 360);
    infoBg->setOpacity(77);
    addChild(infoBg);
    infoBg->runAction(Sequence::create(DelayTime::create(24.0f/24),CallFunc::create([=](){
        infoBg->setVisible(true);
    }),FadeTo::create(5.0/24,255),NULL));
    //创建4个玩家的结算信息
    vector<PlayerInfoCell*> cells;
    vector<GameResultData> resultData = GAMEDATA::getInstance()->getGameResults();
    for(GameResultData resData : resultData){
        if(resData.seatId!=GAMEDATA::getInstance()->getHeroSeatId()){
            PlayerInfoCell* cell = PlayerInfoCell::create(resData);
            addChild(cell);
            cell->setVisible(false);
            cells.push_back(cell);
        }
        //更新玩家自己
        if (SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), resData.seatId) == ClientSeatId::hero){
            UserData::getInstance()->setDiamond(resData.diamond);
            UserData::getInstance()->setGold(resData.gold);
            UserData::getInstance()->setTicket(resData.lequan);
            UserData::getInstance()->setLockDiamond(resData.bangzuan);
            EventCustom ev(MSG_UPDATE_HERO_INFO);
            _eventDispatcher->dispatchEvent(&ev);
            //            vector<Player*> players = GAMEDATA::getInstance()->getPlayersInfo();
            //            for (int i = 0; i < players.size(); i++){
            //                if (SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), players.at(i)->getSeatId()) == ClientSeatId::hero){
            //                    players.at(i)->setDiamond(resData.diamond);
            //                    players.at(i)->setLockDiamond(resData.bangzuan);
            //                    players.at(i)->setGold(resData.gold);
            //                    players.at(i)->setTicket(resData.lequan);
            //                    players.at(i)->setScore(resData.jifen+players.at(i)->getScore());
            //                }
            //            }
        }else{
            vector<Player*> players = GAMEDATA::getInstance()->getPlayersInfo();
            for (int i = 0; i < players.size(); i++){
                if (players.at(i)->getSeatId() == resData.seatId){
                    players.at(i)->setDiamond(resData.diamond);
                    players.at(i)->setLockDiamond(resData.bangzuan);
                    players.at(i)->setGold(resData.gold);
                    players.at(i)->setTicket(resData.lequan);
                    players.at(i)->setScore(resData.jifen+players.at(i)->getScore());
                    
                }
            }
        }
    }
    PlayerInfoCell* hcell = PlayerInfoCell::create(getheroData());
    addChild(hcell);
    hcell->setVisible(false);
    cells.push_back(hcell);
    auto play = Sprite::create();
    addChild(play);
    play->runAction(Sequence::create(DelayTime::create(24.0/24),CallFunc::create([=](){
        cells.at(0)->setVisible(true);
        cells.at(0)->setOpacity(77);
        cells.at(0)->setCascadeOpacityEnabled(true);
        cells.at(0)->setPosition(840,360);
        cells.at(0)->runAction(Sequence::create(Spawn::create(MoveTo::create(5.0/25, Point(940,360)), FadeIn::create(5.0/25), NULL),MoveTo::create(2.0/25, Point(890,360)), NULL));
    }),DelayTime::create(4.0/25),CallFunc::create([=](){
        cells.at(1)->setVisible(true);
        cells.at(1)->setOpacity(77);
        cells.at(1)->setCascadeOpacityEnabled(true);
        cells.at(1)->setPosition(680,360);
        cells.at(1)->runAction(Sequence::create(Spawn::create(MoveTo::create(5.0/25, Point(770,360)), FadeIn::create(5.0/25), NULL),MoveTo::create(2.0/25, Point(730,360)), NULL));
        
    }), DelayTime::create(4.0/25),CallFunc::create([=](){
        cells.at(2)->setVisible(true);
        cells.at(2)->setOpacity(77);
        cells.at(2)->setCascadeOpacityEnabled(true);
        cells.at(2)->setPosition(455,360);
        cells.at(2)->runAction(Sequence::create(Spawn::create(MoveTo::create(5.0/25, Point(615,360)), FadeIn::create(5.0/25), NULL),MoveTo::create(2.0/25, Point(565,360)), NULL));
        
    }),DelayTime::create(4.0/25),CallFunc::create([=](){
        cells.at(3)->setVisible(true);
        cells.at(3)->setOpacity(77);
        cells.at(3)->setCascadeOpacityEnabled(true);
        cells.at(3)->setPosition(300,360);
        cells.at(3)->runAction(Sequence::create(Spawn::create(MoveTo::create(5.0/25, Point(450,360)), FadeIn::create(5.0/25), NULL),MoveTo::create(2.0/25, Point(400,360)), NULL));
        
    }),NULL));
    
    auto quitImage = MenuItemImage::create("result/quit_btn_1.png","result/quit_btn_2.png",CC_CALLBACK_0(ResultLayer::clickQuit, this));
    auto quitMenu = Menu::create(quitImage, NULL);
    quitMenu->setPosition(440, 170);
    this->addChild(quitMenu, 20);
    quitMenu->setVisible(false);
    quitImage->setOpacity(77);
    quitImage->runAction(Sequence::create(DelayTime::create(3.0f),CallFunc::create([=](){
        quitMenu->setVisible(true);
    }),FadeTo::create(3.0/24, 255), NULL));
    
    MenuItemImage* continu = MenuItemImage::create("result/continue_btn_1.png", "result/continue_btn_2.png",
                                                   CC_CALLBACK_0(ResultLayer::clickContinu, this));
    auto continuMenu = Menu::create(continu, NULL);
    continuMenu->setPosition(840, 170);
    addChild(continuMenu, 20);
    continuMenu->setVisible(false);
    continu->setOpacity(77);
    continu->runAction(Sequence::create(DelayTime::create(3.0f),CallFunc::create([=](){
        if(GAMEDATA::getInstance()->getIsGotoLobby()){
            GAMEDATA::getInstance()->setIsGotoLobby(false);
            Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
        }else{
            continuMenu->setVisible(true);
        }
        schedule(schedule_selector(ResultLayer::updateTime), 1.0f, kRepeatForever, 0);
    }),FadeTo::create(3.0/24, 255),CallFunc::create([=](){
        ClippingNode* cliper = ClippingNode::create();
        Sprite* stencil =  Sprite::create("result/continue_btn_1.png");
        Sprite* spark = Sprite::create("result/btn_light.png");
        spark->setPosition(stencil->getContentSize().width,0);
        cliper->setAlphaThreshold(0);
        cliper->setInverted(false);//设置底板可见
        cliper->setStencil(stencil);
        cliper->addChild(spark);
        this->addChild(cliper,30);
        cliper->setPosition(840, 170);
        spark->runAction(RepeatForever::create(Sequence::create(CallFunc::create([=](){
            spark->setPosition(128,0);
            spark->setVisible(true);
        }),MoveTo::create(20.0f/24,Point(-100,0)),CallFunc::create([=](){
            spark->setVisible(false);
        }),DelayTime::create(20.0f/24), NULL)));
    }), NULL));
    
    Sprite* pokers = Sprite::create();
    addChild(pokers);
    pokers->runAction(Sequence::create(DelayTime::create(34.0f/24),CallFunc::create([=](){
        drawPokerPad(getheroData().showPoker,getheroData().huType,getheroData().hua);
    }) ,NULL));
}



void ResultLayer::showLoseAnim(){
    
    auto title = Sprite::create();
    title->setPosition(640, 625);
    addChild(title);
    
    if (getheroData().result == 0){
        title->setTexture("result/da_jiang_you.png");
    }
    else{
        title->setTexture("result/you_lose.png");
    }
    
    auto players_bg = Sprite::create("result/player_info_bg.png");
    players_bg->setPosition(640, 360);
    addChild(players_bg);
    
    //创建4个玩家的结算信息
    vector<PlayerInfoCell*> cells;
    vector<GameResultData> resultData = GAMEDATA::getInstance()->getGameResults();
    int index=0;
    int maxGold = 0;
    GameResultData maxData;
    for(GameResultData resData : resultData){
        //其余3各玩家
        if(resData.seatId!=GAMEDATA::getInstance()->getHeroSeatId()){
            PlayerInfoCell* cell = PlayerInfoCell::create(resData);
            cell->setPosition(890-160*index,360);
            addChild(cell);
            index++;
        }
        //赢得最多的玩家
        if(GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom){
            if(resData.jifendelta>=maxGold){
                maxData = resData;
                maxGold = maxData.jifendelta;
            }
        }else{
            if(resData.golddelta>=maxGold){
                maxData = resData;
                maxGold = maxData.golddelta;
            }
        }
        //更新用户自己的信息
        if (SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), resData.seatId) == ClientSeatId::hero){
            UserData::getInstance()->setDiamond(resData.diamond);
            UserData::getInstance()->setGold(resData.gold);
            UserData::getInstance()->setTicket(resData.lequan);
            UserData::getInstance()->setLockDiamond(resData.bangzuan);
            EventCustom ev(MSG_UPDATE_HERO_INFO);
            _eventDispatcher->dispatchEvent(&ev);
            //            vector<Player*> players = GAMEDATA::getInstance()->getPlayersInfo();
            //            for (int i = 0; i < players.size(); i++){
            //                if (SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), players.at(i)->getSeatId()) == ClientSeatId::hero){
            //                    players.at(i)->setDiamond(resData.diamond);
            //                    players.at(i)->setGold(resData.gold);
            //                    players.at(i)->setTicket(resData.lequan);
            //                    players.at(i)->setLockDiamond(resData.bangzuan);
            //                    players.at(i)->setScore( players.at(i)->getScore()+resData.jifen);
            //                }
            //            }
            if(GAMEDATA::getInstance()->getIsLiuJu()){
                GAMEDATA::getInstance()->setIsLiuJu(false);
                maxData = resData;
            }
        }else{
            vector<Player*> players = GAMEDATA::getInstance()->getPlayersInfo();
            for (int i = 0; i < players.size(); i++){
                if (players.at(i)->getSeatId() == resData.seatId){
                    players.at(i)->setDiamond(resData.diamond);
                    players.at(i)->setGold(resData.gold);
                    players.at(i)->setTicket(resData.lequan);
                    players.at(i)->setLockDiamond(resData.bangzuan);
                    players.at(i)->setScore(players.at(i)->getScore()+resData.jifen);
                }
            }
        }
    }
    //自己
    PlayerInfoCell* hcell = PlayerInfoCell::create(getheroData());
    addChild(hcell);
    hcell->setPosition(410,360);
    
    
    MenuItemImage* quit = MenuItemImage::create("result/quit_btn_1.png", "result/quit_btn_2.png",
                                                CC_CALLBACK_0(ResultLayer::clickQuit, this));
    MenuItemImage* continu = MenuItemImage::create("result/continue_btn_1.png", "result/continue_btn_2.png",
                                                   CC_CALLBACK_0(ResultLayer::clickContinu, this));
    resultMenu = Menu::create(quit, continu, NULL);
    resultMenu->setPosition(640, 170);
    resultMenu->alignItemsHorizontallyWithPadding(60);
    addChild(resultMenu, 20);
    resultMenu->setVisible(false);
    schedule([=](float dt){
        
        if(GAMEDATA::getInstance()->getIsGotoLobby()){
            GAMEDATA::getInstance()->setIsGotoLobby(false);
            Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
        }else{
            resultMenu->setVisible(true);
        }
        
        schedule(schedule_selector(ResultLayer::updateTime), 1.0f, kRepeatForever, 0);
    }, 0, 0, 3.0f,"delayshowbtn");
    drawPokerPad(maxData.showPoker,maxData.huType,maxData.hua);
}

void ResultLayer::showHeroPropInfo(){
    //金币显示
    auto goldIcon= Sprite::create();
    if(GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom){
        goldIcon->setTexture("mjitem/jifen_icon.png");
    }else{
        goldIcon->setTexture("mjitem/gold_iocn.png");
    }
    goldIcon->setOpacity(77);
    goldIcon->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    goldIcon->setScale(2.0f);
    goldIcon->setVisible(false);
    addChild(goldIcon);
    goldIcon->runAction(Sequence::create(DelayTime::create(18.0f/24),CallFunc::create([=](){
        goldIcon->setVisible(true);
    }),Spawn::create(ScaleTo::create(3.0/24,1.0f),FadeTo::create(5.0/24,180), NULL),NULL));
    
    LabelAtlas* goldNum;
    if(getheroData().result == 1 || getheroData().result == 3){
        goldNum = LabelAtlas::create(cocos2d::String::createWithFormat(":%d",GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom?getheroData().jifendelta:getheroData().golddelta)->_string, "result/big_num_win.png", 52, 64, '0');
    }else{
        goldNum = LabelAtlas::create("0","result/big_num_lose.png", 52, 64, '0');
        if(GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom){
            if(getheroData().jifendelta<0){
                goldNum->setString(cocos2d::String::createWithFormat(":%d", abs(getheroData().jifendelta))->_string);
            }else{
                goldNum->setString(cocos2d::String::createWithFormat("%d", abs(getheroData().jifendelta))->_string);
            }
        }else{
            if(getheroData().golddelta<0){
                goldNum->setString(cocos2d::String::createWithFormat(":%d", abs(getheroData().golddelta))->_string);
            }else{
                goldNum->setString(cocos2d::String::createWithFormat("%d", abs(getheroData().golddelta))->_string);
            }
        }
        
    }
    goldNum->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    goldNum->setVisible(false);
    addChild(goldNum);
    goldNum->runAction(Sequence::create(DelayTime::create(23.0f/24),CallFunc::create([=](){
        goldNum->setVisible(true);
    }),NULL));
    //乐券显示
    auto lequanIcon= Sprite::create("mjitem/lequan_icon.png");
    addChild(lequanIcon);
    if(getheroData().lequandelta>0){
        lequanIcon->setOpacity(77);
        lequanIcon->setScale(2.0f);
        lequanIcon->setVisible(false);
        lequanIcon->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        lequanIcon->runAction(Sequence::create(DelayTime::create(27.0f/24),CallFunc::create([=](){
            lequanIcon->setVisible(true);
        }),Spawn::create(ScaleTo::create(3.0/24,1.0f),FadeTo::create(5.0/24,180), NULL),NULL));
        if(getheroData().result == 1 || getheroData().result == 3){
            auto par = ParticleUtil::create(MyParticleType::goldAndLequan);
            addChild(par);
        }
    }else{
        lequanIcon->setVisible(false);
        if(getheroData().result == 1 || getheroData().result == 3){
            auto par = ParticleUtil::create(MyParticleType::goldOnly);
            addChild(par);
        }
    }
    LabelAtlas* lequanNum = LabelAtlas::create(cocos2d::String::createWithFormat(":%d",getheroData().lequandelta )->_string, "result/big_num_win.png", 52, 64, '0');
    lequanNum->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    lequanNum->setVisible(false);
    if(getheroData().lequandelta>0){
        lequanNum->runAction(Sequence::create(DelayTime::create(32.0f/24),CallFunc::create([=](){
            lequanNum->setVisible(true);
        }),NULL));
    }
    addChild(lequanNum);
    //更具数字区域大小设定位置
    if(getheroData().lequandelta>0){
        float width = goldIcon->getBoundingBox().size.width+ goldNum->getBoundingBox().size.width
        + lequanIcon->getBoundingBox().size.width+lequanNum->getBoundingBox().size.width;
        goldIcon->setPosition((1280-width)/2, 535);
        goldNum->setPosition((1280-width)/2+goldIcon->getBoundingBox().size.width/2, 505);
        lequanIcon->setPosition((1280-width)/2+goldIcon->getBoundingBox().size.width+goldNum->getBoundingBox().size.width, 535);
        lequanNum->setPosition((1280-width)/2+goldIcon->getBoundingBox().size.width+goldNum->getBoundingBox().size.width
                               + lequanIcon->getBoundingBox().size.width/2, 505);
    }else{
        goldNum->setPosition(600, 505);
        goldIcon->setPosition(530, 535);
    }
}


void ResultLayer::drawPokerPad(std::string pokers, std::string hutype, int hua){
    if(pokers==""){
        return;
    }
    std::vector<std::string> showPokers = StringUtil::split(pokers, ",");
    
    if (hutype != ""){
        std::vector<std::string> hutypeInfo = StringUtil::split(hutype, ",");
        std::string hu = "";
        for (int i = 0; i < hutypeInfo.size(); i++){
            hu += ChineseWord(hutypeInfo.at(i).c_str());
        }
        drawHuType(hu);
    }
    drawHuaNum(hua);
    auto pad = Sprite::create();
    for (int i = 0; i < showPokers.size(); i++){
        Jong* jong = Jong::create();
        jong->showJong(heroplayed, atoi(showPokers.at(i).c_str()));
        jong->setPosition(i * 35, 0);
        pad->addChild(jong, 35 - i);
    }
    pad->setAnchorPoint(Point::ANCHOR_MIDDLE);
    pad->setPosition(640-showPokers.size()*35/2,45);
    addChild(pad,20);
}



void ResultLayer::drawHuType(std::string hutype){
    Label* huType = Label::create(hutype, "Arial", 16);
    this->addChild(huType, 22);
    huType->setPosition(575, 90);
}

void ResultLayer::drawHuaNum(int hua){
    auto huaSprite = Sprite::create("gameview/flower.png");
    auto huaNum = LabelAtlas::create(cocos2d::String::createWithFormat(":%d", hua)->_string,
                                     "gameview/hua_num.png", 17, 24, '0');
    huaNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
    huaSprite->setPosition(460, 90);
    huaNum->setPosition(500, 90);
    this->addChild(huaSprite, 25);
    this->addChild(huaNum, 25);
}

void ResultLayer::updateTime(float dt){
    if (isVisible()){
        timeToatal--;
        if (timeToatal <= 0){
            clickContinu();
            timeToatal = 10000000000;//填一个极大值
        }
    }
}

void ResultLayer::clickContinu(){
    schedule([=](float dt){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getContinueGameCommand());
    }, 0.0f, 0.0f, 1.0f,"delayGame");
}

void ResultLayer::clickQuit(){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getQuitRoomCommand());
    Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
}


void ResultLayer::showCaidaiAnim(Sprite* sprite){
    auto animation = Animation::create();
    for( int i=1;i<16;i++)
    {
        std::string imageName = cocos2d::String::createWithFormat("result/caidai_%d.png",i)->_string;
        animation->addSpriteFrameWithFile(imageName);
    }
    // should last 1 seconds. And there are 24 frames.
    animation->setDelayPerUnit(1.0f / 24.0f);
    animation->setRestoreOriginalFrame(false);
    auto action = Animate::create(animation);
    sprite->runAction(action);
    
}
