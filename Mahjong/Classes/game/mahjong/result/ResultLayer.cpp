#include "game/mahjong/result/ResultLayer.h"
#include "game/mahjong/lobby/LobbyScene.h"
#include "game/mahjong/jong/Jong.h"
#include"game/mahjong/core/MjGameScene.h"
#include "game/mahjong/core/MahjongView.h"
#include "game/utils/SeatIdUtil.h"
#include "game/utils/StringUtil.h"
#include "game/utils/Chinese.h"
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

void ResultLayer::initData(){
    timeToatal = 20;
    setWinOrLose();
}

void ResultLayer::initView(){
    auto reslut_bg = Sprite::create("result/result_bg.jpg");
    reslut_bg->setPosition(640, 360);
    addChild(reslut_bg);
    if(getheroData().result==1||getheroData().result==3){
        showWinAnim();
    }else{
        showLoseAnim();
    }
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
    auto goldIcon= Sprite::create();
    if(GAMEDATA::getInstance()->getIsPrivateRoom()){
        goldIcon->setTexture("mjitem/jifen_icon.png");
    }else{
        goldIcon->setTexture("mjitem/gold_iocn.png");
    }
    if(getheroData().lequandelta>0){
        goldIcon->setPosition(356, 525);
    }else{
        goldIcon->setPosition(530, 525);
    }
    addChild(goldIcon);
    goldIcon->setOpacity(77);
    goldIcon->setScale(2.0f);
    goldIcon->setVisible(false);
    goldIcon->runAction(Sequence::create(DelayTime::create(18.0f/24),CallFunc::create([=](){
        goldIcon->setVisible(true);
    }),Spawn::create(ScaleTo::create(3.0/24,1.0f),FadeTo::create(5.0/24,180), NULL),NULL));
    
    LabelAtlas* goldNum = LabelAtlas::create(cocos2d::String::createWithFormat(":%d",GAMEDATA::getInstance()->getIsPrivateRoom()?getheroData().jifendelta:getheroData().golddelta)->_string, "result/big_num_win.png", 52, 64, '0');
    if(getheroData().lequandelta>0){
        goldNum->setPosition(390, 505);
    }else{
        goldNum->setPosition(590, 505);
    }
    goldNum->setVisible(false);
    addChild(goldNum);
    goldNum->runAction(Sequence::create(DelayTime::create(23.0f/24),CallFunc::create([=](){
        goldNum->setVisible(true);
    }),NULL));
    
    auto lequanIcon= Sprite::create("mjitem/lequan_icon.png");
    addChild(lequanIcon);
    if(getheroData().lequandelta>0){
        lequanIcon->setPosition(701, 525);
        lequanIcon->setOpacity(77);
        lequanIcon->setScale(2.0f);
        lequanIcon->setVisible(false);
        lequanIcon->runAction(Sequence::create(DelayTime::create(27.0f/24),CallFunc::create([=](){
            lequanIcon->setVisible(true);
        }),Spawn::create(ScaleTo::create(3.0/24,1.0f),FadeTo::create(5.0/24,180), NULL),NULL));
        showLequanExplosion();
    }else{
        lequanIcon->setVisible(false);
        showGoldExplosion();
    }
    LabelAtlas* lequanNum = LabelAtlas::create(cocos2d::String::createWithFormat(":%d",getheroData().lequandelta )->_string, "result/big_num_win.png", 52, 64, '0');
    lequanNum->setVisible(false);
    if(getheroData().lequandelta>0){
        lequanNum->setPosition(735, 505);
        lequanNum->runAction(Sequence::create(DelayTime::create(32.0f/24),CallFunc::create([=](){
            lequanNum->setVisible(true);
        }),NULL));
    }
    addChild(lequanNum);
    
    
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
        if (SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), resData.seatId) == ClientSeatId::hero){
            UserData::getInstance()->setDiamond(resData.diamond);
            UserData::getInstance()->setGold(resData.gold);
            UserData::getInstance()->setTicket(resData.lequan);
            vector<Player*> players = GAMEDATA::getInstance()->getPlayersInfo();
            for (int i = 0; i < players.size(); i++){
                if (SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), players.at(i)->getSeatId()) == ClientSeatId::hero){
                    players.at(i)->setDiamond(resData.diamond);
                    players.at(i)->setGold(resData.gold);
                    players.at(i)->setTicket(resData.lequan);
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
    quitImage->runAction(Sequence::create(DelayTime::create(30.0/24),CallFunc::create([=](){
        quitMenu->setVisible(true);
    }),FadeTo::create(3.0/24, 255), NULL));
    
    MenuItemImage* continu = MenuItemImage::create("result/continue_btn_1.png", "result/continue_btn_2.png",
                                                   CC_CALLBACK_0(ResultLayer::clickContinu, this));
    auto continuMenu = Menu::create(continu, NULL);
    continuMenu->setPosition(840, 170);
    this->addChild(continuMenu, 20);
    continuMenu->setVisible(false);
    continu->setOpacity(77);
    continu->runAction(Sequence::create(DelayTime::create(33.0/24),CallFunc::create([=](){
        continuMenu->setVisible(true);
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
        drawTimeClock();
    }) ,NULL));
}



void ResultLayer::showLoseAnim(){
    
    auto title = Sprite::create();
    title->setPosition(640, 625);
    addChild(title);
    auto goldIcon = Sprite::create();
    if(GAMEDATA::getInstance()->getIsPrivateRoom()){
        goldIcon->setTexture("mjitem/jifen_icon.png");
    }else{
        goldIcon->setTexture("mjitem/gold_iocn.png");
    }

    addChild(goldIcon);
    auto lequanIcon = Sprite::create("mjitem/lequan_icon.png");
    addChild(lequanIcon);
    LabelAtlas* goldNum = LabelAtlas::create(cocos2d::String::createWithFormat(":%d", abs(GAMEDATA::getInstance()->getIsPrivateRoom()?getheroData().jifendelta:getheroData().golddelta))->_string,
                                             "result/big_num_lose.png", 52, 64, '0');
    goldNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(goldNum);
    LabelAtlas* lequanNum = LabelAtlas::create(cocos2d::String::createWithFormat(":%d", abs(getheroData().lequandelta))->_string,
                                               "result/big_num_lose.png", 52, 64, '0');
    lequanNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(lequanNum);
 if (getheroData().result == 0){
        title->setTexture("result/da_jiang_you.png");
    }
    else{
        title->setTexture("result/you_lose.png");
    }
    if (getheroData().lequandelta > 0){
        goldIcon->setPosition(356, 525);
        goldNum->setPosition(390, 525);
        lequanIcon->setPosition(701, 525);
        lequanNum->setPosition(735, 525);
    }
    else{
        goldIcon->setPosition(530, 525);
        goldNum->setPosition(590, 525);
        lequanIcon->setVisible(false);
        lequanNum->setVisible(false);
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
        if(GAMEDATA::getInstance()->getIsPrivateRoom()){
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
            vector<Player*> players = GAMEDATA::getInstance()->getPlayersInfo();
            for (int i = 0; i < players.size(); i++){
                if (SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), players.at(i)->getSeatId()) == ClientSeatId::hero){
                    players.at(i)->setDiamond(resData.diamond);
                    players.at(i)->setGold(resData.gold);
                    players.at(i)->setTicket(resData.lequan);
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
    this->addChild(resultMenu, 20);
    resultMenu->setVisible(false);
    scheduleOnce(schedule_selector(ResultLayer::showContinueButton), 1.0f);
    drawPokerPad(maxData.showPoker,maxData.huType,maxData.hua);
    drawTimeClock();
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
    createPokersSprite(showPokers);
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


void ResultLayer::createPokersSprite(std::vector<std::string> showPokers){
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



void ResultLayer::drawTimeClock(){
    timeLable = LabelAtlas::create(cocos2d::String::createWithFormat("%d", timeToatal)->_string,
                                   "result/result_num.png", 9, 13, '0');
    timeLable->setAnchorPoint(Point::ANCHOR_MIDDLE);
    timeLable->setPosition(680, 165);
    this->addChild(timeLable, 20);
    timeLable->setVisible(false);
}


void ResultLayer::updateTime(float dt){
    if (isVisible()){
        timeToatal--;
        if (timeToatal > 0){
            timeLable->setString(cocos2d::String::createWithFormat("%d", timeToatal)->_string);
        }
        else if (timeToatal == 0){
            clickContinu();
        }
    }
}


void ResultLayer::clickContinu(){
    GAMEDATA::getInstance()->setContinueAgain(true);
    Director::getInstance()->replaceScene(TransitionFade::create(1, MjGameScene::create()));
}

void ResultLayer::clickQuit(){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getQuitRoomCommand());
    Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
}


void ResultLayer::showContinueButton(float dt){
    resultMenu->setVisible(true);
    timeLable->setVisible(true);
    schedule(schedule_selector(ResultLayer::updateTime), 1.0f, kRepeatForever, 0);
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

void ResultLayer::showLequanExplosion(){
    ParticleExplosion* effect = ParticleExplosion::create();
    effect->setTexture(Director::getInstance()->getTextureCache()->addImage("mjitem/lequan_icon.png"));
    effect->setTotalParticles(500);
    effect->setStartColor(Color4F(255, 255, 255, 255));
    effect->setStartColorVar(Color4F(0, 0, 0, 0));
    effect->setEndColor(Color4F(255, 255, 255, 255));
    effect->setEndColorVar(Color4F(0, 0, 0, 0));
    effect->setStartSize(40.0f);	// 初始化粒子元素的尺寸
    effect->setGravity(Point(0, -400));
    effect->setDuration(0.2f);
    effect->setLife(2.0f);
    effect->setSpeed(300.0f);
    effect->setSpeedVar(20);
    effect->setPosition(640,600);
    addChild(effect);
    //
    ParticleExplosion* effect2 = ParticleExplosion::create();
    effect2->setTexture(Director::getInstance()->getTextureCache()->addImage("result/gold_1.png"));
    effect2->setTotalParticles(500);
    effect2->setStartColor(Color4F(255, 255, 255, 255));
    effect2->setStartColorVar(Color4F(0, 0, 0, 0));
    effect2->setEndColor(Color4F(255, 255, 255, 255));
    effect2->setEndColorVar(Color4F(0, 0, 0, 0));
    effect2->setStartSize(40.0f);	// 初始化粒子元素的尺寸
    effect2->setGravity(Point(0, -400));
    effect2->setDuration(0.2f);
    effect2->setLife(2.0f);
    effect2->setSpeed(300.0f);
    effect2->setSpeedVar(20);
    effect2->setPosition(640,600);
    addChild(effect2);
    
}

void ResultLayer::showGoldExplosion(){
    ParticleExplosion* effect = ParticleExplosion::create();
    effect->setTexture(Director::getInstance()->getTextureCache()->addImage("result/gold_1.png"));
    effect->setTotalParticles(1000);
    effect->setStartColor(Color4F(255, 255, 255, 255));
    effect->setStartColorVar(Color4F(0, 0, 0, 0));
    effect->setEndColor(Color4F(255, 255, 255, 255));
    effect->setEndColorVar(Color4F(0, 0, 0, 0));
    effect->setStartSize(40.0f);	// 初始化粒子元素的尺寸
    effect->setGravity(Point(0, -400));
    effect->setDuration(0.2f);
    effect->setLife(2.0f);
    effect->setSpeed(300.0f);
    effect->setSpeedVar(20);
    effect->setPosition(640,600);
    addChild(effect);
}

void ResultLayer::setWinOrLose(){
    vector<GameResultData> results = GAMEDATA::getInstance()->getGameResults();
    for (GameResultData data: results) {
        if(data.seatId==GAMEDATA::getInstance()->getHeroSeatId()){
            setheroData(data);
        }
    }
}