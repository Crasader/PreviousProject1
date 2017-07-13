#include "mahjong/gameview/shanghai/special/ReviewGame.h"
#include "mahjong/gameview/widget/Orientation.h"
#include "mahjong/gameview/widget/CardStack.hpp"
#include "mahjong/gameview/anim/DealJongAnim.h"
#include "mahjong/gameview/anim/HupaiAnim.hpp"
#include "mahjong/gameview/anim/LiuJuAnim.hpp"
#include "mahjong/gameview/anim/OutFogAnim.hpp"
#include "mahjong/gameview/anim/PlayerCpgAnim.hpp"
#include "mahjong/common/utils/SeatIdUtil.h"
#include "mahjong/common/utils/StringUtil.h"
#include "mahjong/common/dialog/prompt/HintDialog.hpp"
#include "mahjong/common/dialog/prompt/TextHintDialog.hpp"
#include "mahjong/common/widget/ScrollTextEx.h"
#include "mahjong/common/widget/batteryInfo/BatteryInfo.h"
#include "mahjong/lobby/LobbyScene.h"
#include "mahjong/result/ResultScene.hpp"
#include "server/SocketDataManage.h"
#include "server/NetworkManage.h"
#include "json/document.h"
#include "json/rapidjson.h"




bool ReviewGame::init(){
    if (!Layer::init())
    {
        return false;
    }
    initData();
    loadView();
    return true;
}

void ReviewGame::onEnter(){
    Layer::onEnter();
    scheduleUpdate();
    addCoustomListener();
}


void ReviewGame::initData(){
    playing = true;
    playerHero = NULL;
    playerLeft = NULL;
    playerRight = NULL;
    playerOpposite = NULL;
    fupanStep = 0;
    currentMaxStep = 0;
    GAMEDATA::getInstance()->setIsPlaying(false);
    GAMEDATA::getInstance()->setIsLiuJu(false);
    GAMEDATA::getInstance()->setIsGotoLobby(false);
    Audio::getInstance()->setHasTingPlayer(false);
    GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
    
}

void ReviewGame::loadView(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Sprite* view_bg = Sprite::create("gameview/game_bg.jpg");
    view_bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    addChild(view_bg, -1);
    controllPad = Menu::create();
    controllPad->setAnchorPoint(Point(1, 0));
    controllPad->setVisible(false);
    addChild(controllPad, 10);
    guiLayer = GuiLayer::create();
    addChild(guiLayer, 150);
    choiceMenu = Sprite::create();
    choiceMenu->setAnchorPoint(Point(0, 0));
    choiceMenu->setPosition(Point(0, 0));
    addChild(choiceMenu, 100);
    //Toast 消息
    tao = InfoToast::create();
    addChild(tao,50);
    showOriention();
    //牌堆
    CardStack* stack = CardStack::create();
    stack->setTag(1129);
    stack->setVisible(false);
    addChild(stack);
    
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    addChild(menu1,800);
    
}


void ReviewGame::controlDown(){
    interval =0;
    playerHero->showCurrentPlayedJongIcon(false);
    if(fupanStep>=2 && myPlayMingpaiRecord.size()>0){
        image3->setEnabled(true);
        fupanStep -= 2;
        fupanStep  = fupanStep%2 == 0?fupanStep:(fupanStep-1);
        if(fupanStep/2>=myPlayMingpaiRecord.size())
            fupanStep = ((int)myPlayMingpaiRecord.size()-1)*2;
        PlayMingpaiRecord record = myPlayMingpaiRecord.at(fupanStep/2);
        for(auto var:record.record){
            if(var.seatId==ClientSeatId::left){
                playerLeft->setHuaNum(var.hua);
                playerLeft->showPlayerHua(var.hua);
                playerLeft->setPlayerTingState(var.isTing);
                playerLeft->updateMingpai(var.playerHandJongs, var.playerPlayedJongs,var.playerCpgRecords);
            }else if(var.seatId==ClientSeatId::opposite){
                playerOpposite->setHuaNum(var.hua);
                playerOpposite->showPlayerHua(var.hua);
                playerOpposite->setPlayerTingState(var.isTing);
                playerOpposite->updateMingpai(var.playerHandJongs, var.playerPlayedJongs,var.playerCpgRecords);
            }else if(var.seatId==ClientSeatId::right){
                playerRight->setHuaNum(var.hua);
                playerRight->showPlayerHua(var.hua);
                playerRight->setPlayerTingState(var.isTing);
                playerRight->updateMingpai(var.playerHandJongs, var.playerPlayedJongs,var.playerCpgRecords);
            }else if(var.seatId==ClientSeatId::hero){
                playerHero->setHuaNum(var.hua);
                playerHero->showPlayerHua(var.hua);
                playerHero->setPlayerTingState(var.isTing);
                playerHero->updateMingpai(var.playerHandJongs, var.playerPlayedJongs,var.playerCpgRecords);
            }
        }
    }else{
        image1->setEnabled(false);
    }
}

void ReviewGame::controlPause(){
    playing= !playing;
    if(NULL == getChildByTag(1088)||NULL == (getChildByTag(1088)->getChildByTag(1087)))
        return;
    if(playing){
        auto iamge001 = Sprite::create("fupan/pause_1.png");
        ((MenuItemImage*)(getChildByTag(1088)->getChildByTag(1087)))->setNormalImage(iamge001);
        auto iamge002 = Sprite::create("fupan/pause_2.png");
        ((MenuItemImage*)(getChildByTag(1088)->getChildByTag(1087)))->setSelectedImage(iamge002);
    }else{
        auto iamge001 = Sprite::create("fupan/play_1.png");
        ((MenuItemImage*)(getChildByTag(1088)->getChildByTag(1087)))->setNormalImage(iamge001);
        auto iamge002 = Sprite::create("fupan/play_2.png");
        ((MenuItemImage*)(getChildByTag(1088)->getChildByTag(1087)))->setSelectedImage(iamge002);
    }
}
void ReviewGame::controlUp(){
    if(fupanStep<GAMEDATA::getInstance()->getPlaybackInfo().playBackInfo.size()){
        image1->setEnabled(true);
        interval+=3.0;
    }else{
        image3 ->setEnabled(false);
    }
    
}
void ReviewGame::controlBack(){
    GAMEDATA::getInstance()->setGameType(1);
    GAMEDATA::getInstance()->clearPlayersInfo();
    Director::getInstance()->replaceScene(LobbyScene::create());
}

void ReviewGame::update(float dt){
    interval += dt;
    if(playing){
        if(interval>1.5){
            if(fupanStep<GAMEDATA::getInstance()->getPlaybackInfo().playBackInfo.size()){
                NetworkManage::getInstance()->receiveMsg(GAMEDATA::getInstance()->getPlaybackInfo().playBackInfo.at(fupanStep));
                fupanStep++;
            }
            interval = interval-1.5;
            if(fupanStep>currentMaxStep)
                currentMaxStep = fupanStep;
        }
    }else{
        interval=0;
    }
}

void ReviewGame::drawCpgControllPad(PlayerCpgtData newData){
    shmjPlayerCpgtData = newData;
    controllPad->removeAllChildrenWithCleanup(true);
    auto qi = MenuItemImage::create("gameview/mj_qi.png", "gameview/mj_qi.png", CC_CALLBACK_0(ReviewGame::heroDoCpgQi,this));
    qi->setPosition(Point(0, 0));
    controllPad->addChild(qi);
    MenuItemImage* chi = nullptr;
    MenuItemImage* peng = nullptr;
    MenuItemImage* gang = nullptr;
    int buttonCount = 1;
    if (newData.chi[0] != ""){
        chi = MenuItemImage::create("gameview/mj_chi.png","gameview/mj_chi.png", CC_CALLBACK_1(ReviewGame::showHeroChiUi, this));
        chi->setPosition(Point(-buttonCount * 160, 0));
        controllPad->addChild(chi);
        buttonCount++;
        
    }
    if (newData.peng != ""){
        peng = MenuItemImage::create("gameview/mj_peng.png", "gameview/mj_peng.png", CC_CALLBACK_1(ReviewGame::heroDoPeng, this));
        peng->setPosition(Point(-buttonCount * 160, 0));
        controllPad->addChild(peng);
        buttonCount++;
    }
    if (newData.playerGang.size()>0){
        gang = MenuItemImage::create("gameview/mj_gang.png","gameview/mj_gang.png", CC_CALLBACK_1(ReviewGame::showHeroGangUi, this));
        gang->setPosition(Point(-buttonCount * 160, 0));
        controllPad->addChild(gang);
    }
    controllPad->setVisible(true);
}

void ReviewGame::showTingGangControllPad(PlayerCpgtData tingData){
    playerHero->stopTimeClockAnim();
    controllPad->removeAllChildrenWithCleanup(true);
    auto qi = MenuItemImage::create("gameview/mj_qi.png", "gameview/mj_qi.png", CC_CALLBACK_0(ReviewGame::heroDoTingQi, this));
    qi->setPosition(Point(0, 0));
    controllPad->addChild(qi);
    MenuItemImage* ting = nullptr;
    MenuItemImage* penggang = nullptr;
    int buttonCount = 1;
    if (tingData.ting != ""){
        ting = MenuItemImage::create("gameview/mj_ting.png", "gameview/mj_ting.png", CC_CALLBACK_0(ReviewGame::heroDoTing, this));
        ting->setPosition(Point(-buttonCount * 140, 0));
        controllPad->addChild(ting);
        buttonCount++;
    }
    if (tingData.playerGang.size()>0){
        penggang = MenuItemImage::create("gameview/mj_gang.png", "gameview/mj_gang.png", CC_CALLBACK_1(ReviewGame::showHeroGangUi, this));
        penggang->setPosition(Point(-buttonCount * 140, 0));
        controllPad->addChild(penggang);
        buttonCount++;
    }
    controllPad->setPosition(Point(1100, 160));
    controllPad->setVisible(true);
    playerHero->setIsAllowTouch(false);
    playerHero->setIsAllowPlay(true);
    
}

void ReviewGame::hideTingGangControllPad(){
    controllPad->setVisible(false);
    choiceMenu->removeAllChildren();
    choiceMenu->setVisible(false);
    playerHero->stopTimeClockAnim();//玩家停止倒计时
    schedule([=](float dt){
        controllPad->removeAllChildrenWithCleanup(true);
    }, 0, 0, 0.2f,"dalayRemovepad");
}

void ReviewGame::showGuiLayer(){
    guiLayer->setVisible(true);
}

void ReviewGame::removeHeroPlayedIcon(){
    playerHero->removePlayedIcon();
}


void ReviewGame::showHeroChiUi(Ref* ref){
    controllPad->setVisible(false);
    controllPad->setVisible(false);
    //吃牌排序
    if (shmjPlayerCpgtData.chi[0] != "" && shmjPlayerCpgtData.chi[1] != ""){
        //对吃牌的大小进行排序
        for (int j = 2; j > 0; j--) {
            for (int k = 0; k < j; k++) {
                if (shmjPlayerCpgtData.chi[k] < shmjPlayerCpgtData.chi[k + 1]) {
                    auto temp = shmjPlayerCpgtData.chi[k];
                    shmjPlayerCpgtData.chi[k] = shmjPlayerCpgtData.chi[k + 1];
                    shmjPlayerCpgtData.chi[k + 1] = temp;
                }
            }
        }
        for (int i = 0; i < 3; i++){
            if(shmjPlayerCpgtData.chi[i] == ""){
                continue;
            }
            std::vector<string> pai = StringUtil::split(shmjPlayerCpgtData.chi[i], ",");
            pai.push_back(shmjPlayerCpgtData.poker);
            sort(pai.begin(), pai.end());
            auto choice = Menu::create();
            choice->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
            for (int j = 0; j < pai.size(); j++){
                Sprite* chibg = Sprite::create("jong/middle_2.png");
                chibg->setPosition(1000 + j * 40 - i * 130, 150);
                choiceMenu->setVisible(true);
                choiceMenu->addChild(chibg);
                std::string imageName = Jong::getContextImage(atoi(pai.at(j).c_str()));
                MenuItemImage* imageItem = MenuItemImage::create(imageName, imageName, CC_CALLBACK_1(ReviewGame::heroDoChi, this));
                imageItem->setTag(i);
                imageItem->setPosition(1000 + j * 40 - i * 130, 160);
                imageItem->setScale(0.5f);
                choice->addChild(imageItem);
            }
            choice->setPosition(0, 0);
            choiceMenu->addChild(choice);
        }
        playerHero->startTimeClockAnim(9, 1);
    }
    else{
        MenuItemImage* imageItem = MenuItemImage::create();
        imageItem->setTag(0);
        heroDoChi(imageItem);
    }
}


void ReviewGame::showHeroGangUi(Ref* ref){
    controllPad->setVisible(false);
    std::vector<std::string> allGangs;
    for (auto var : shmjHeroCpgtData.playCpgt.playerGang) {
        std::vector<std::string> temp = StringUtil::split(var.gang, ",");
        std::string temp2 = "";
        for(auto gang : temp){
            if(temp2 != gang){
                allGangs.push_back(gang);
                temp2 = gang;
            }
        }
    }
    
    if (allGangs.size()>1){
        //对杠牌的大小进行排序
        for (int j = (int)allGangs.size()-1; j > 0; j--) {
            for (int k = 0; k < j; k++) {
                if ( allGangs.at(k) <  allGangs.at(k+1)) {
                    auto temp =  allGangs.at(k) ;
                    allGangs.at(k)= allGangs.at(k+1);
                    allGangs.at(k+1) = temp;
                }
            }
        }
        for (int i = 0; i < allGangs.size(); i++){
            if( allGangs.at(i) == ""){
                continue;
            }
            auto choice = Menu::create();
            choice->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
            for (int l = 0; l < 4; l++){
                Sprite* chibg = Sprite::create("jong/middle_2.png");
                chibg->setPosition(1000 + l * 40 - i * 170, 150);
                choiceMenu->setVisible(true);
                choiceMenu->addChild(chibg);
                std::string imageName = Jong::getContextImage(atoi(allGangs.at(i).c_str()));
                MenuItemImage* imageItem = MenuItemImage::create(imageName, imageName, CC_CALLBACK_1(ReviewGame::heroDoGang, this));
                imageItem->setTag(atoi(allGangs.at(i).c_str()));
                imageItem->setPosition(1000 + l * 40 - i * 170, 160);
                imageItem->setScale(0.5f);
                choice->addChild(imageItem);
            }
            choice->setPosition(0, 0);
            choiceMenu->addChild(choice);
        }
        playerHero->startTimeClockAnim(9, 1);
    }
    else{
        MenuItemImage* imageItem = MenuItemImage::create();
        imageItem->setTag(atoi(allGangs.at(0).c_str()));
        heroDoGang(imageItem);
    }
}


void ReviewGame::heroDoChi(Ref* psend){
    if (NULL != choiceMenu){
        choiceMenu->setVisible(false);
        choiceMenu->removeAllChildren();
    }
    MenuItemImage* item = (MenuItemImage*)psend;
    selectedChi = shmjPlayerCpgtData.chi[item->getTag()];
    playerHero->stopTimeClockAnim();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getChiCommand(selectedChi, atoi(shmjPlayerCpgtData.poker.c_str())));
}

void ReviewGame::heroDoPeng(Ref* ref){
    controllPad->setVisible(false);
    playerHero->stopTimeClockAnim();
    PlayerCpgtData* cpg = static_cast<PlayerCpgtData*>(((MenuItemImage*)ref)->getUserData());
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getPengCommand(cpg->peng, atoi(cpg->poker.c_str())));
}

void ReviewGame::heroDoGang(Ref* ref){
    MenuItemImage* item = (MenuItemImage*)ref;
    int tag = item->getTag();
    GangData gangData;
    for (auto var : shmjHeroCpgtData.playCpgt.playerGang) {
        std::vector<std::string> temp = StringUtil::split(var.gang, ",");
        for(auto gang : temp){
            if(atoi(gang.c_str()) == tag){
                gangData = var;
            }
        }
    }
    controllPad->setVisible(false);
    playerHero->stopTimeClockAnim();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getGangCommand(StringUtils::format("%d",tag), tag, gangData.flag));
}

void ReviewGame::heroDoCpgQi(){
    controllPad->setVisible(false);
    playerHero->stopTimeClockAnim();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getGiveUpCpgCommmand());
}

void ReviewGame::heroDoTing(){
    playerHero->stopTimeClockAnim();
    controllPad->setVisible(false);
    playerHero->actionTing(shmjHeroCpgtData);
}
void ReviewGame::heroDoTingQi(){
    playerHero->stopTimeClockAnim();
    controllPad->setVisible(false);
    playerHero->actionQi();
    
}


void ReviewGame::setCurrentJongVisible(int seatId){
    //TODO
}

void ReviewGame::playerTingAnim(int seatId){
    PlayerCpgAnim* anim = PlayerCpgAnim::create(CpgType::ting, seatId);
    addChild(anim,121);
    schedule([=](float t){
        if (seatId == ClientSeatId::left){
            playerLeft->setPlayerTingState(true);
        }
        else if (seatId == ClientSeatId::right){
            playerRight->setPlayerTingState(true);
        }
        else if (seatId == ClientSeatId::opposite){
            playerOpposite->setPlayerTingState(true);
        }
        else
        {
            playerHero->setPlayerTingState(true);
        }
        
    },0,0,1.5f,"delay");
    
}


void ReviewGame::clearRoomPlayer(){
    for (int i = 0; i < GAMEDATA::getInstance()->getPlayersInfo().size(); i++){
        if (GAMEDATA::getInstance()->getPlayersInfo().at(i)->getPoxiaoId()
            == UserData::getInstance()->getPoxiaoId()){
            GAMEDATA::getInstance()->getPlayersInfo().at(i)->setIsReady(true);
        }
    }
    playerHero->removeFromParent();
    playerHero = NULL;
    if (NULL != playerLeft){
        playerLeft->removeFromParent();
        playerLeft = NULL;
    }
    if (NULL != playerRight){
        playerRight->removeFromParent();
        playerRight = NULL;
    }
    if (NULL != playerOpposite){
        playerOpposite->removeFromParent();
        playerOpposite = NULL;
    }
    guiLayer->setVisible(false);
}


//显示玩家的方向和庄
void ReviewGame::showOriention(){
    Orientation* ori = Orientation::create();
    ori->setTag(123);
    
    addChild(ori);
}



PlayerBase* ReviewGame::getPlayerBySeatId(int sid){
    int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), sid);
    if (seatId == ClientSeatId::left){
        return playerLeft;
    }
    else if (seatId == ClientSeatId::right){
        return playerRight;
    }
    else if (seatId == ClientSeatId::opposite){
        return playerOpposite;
    }
    else{
        return playerHero;
    }
}




void ReviewGame::showPaiduiNum(int num){
    if(NULL != getChildByTag(1129)){
        ((CardStack*)getChildByTag(1129))->setVisible(true);
        ((CardStack*)getChildByTag(1129))->setShowNum(num);
    }
}


void ReviewGame::showHuPaiXing(std::string paixing){
    if(paixing==""){
        return;
    }
    
    float posY = 260;
    //判断是不是自己胡了
    vector<GameResultData> results = GAMEDATA::getInstance()->getGameResults();
    for(auto var : results){
        if(var.seatId == GAMEDATA::getInstance()->getHeroSeatId()){
            if(var.result == 1||var.result == 3){
                posY=520;
            }
        }
    }
    auto paixinBg = Sprite::create("result/second_bg.png");
    paixinBg->setScaleY(1.4f);
    paixinBg->setPosition(640,posY);
    addChild(paixinBg,999);
    paixinBg->setOpacity(77);
    paixinBg->runAction(Sequence::create(FadeTo::create(3.0/24, 255), NULL));
    
    
    vector<string> pais = StringUtil::split(paixing, ",");
    std::vector<int> hutemp;
    for(auto var:pais){
        hutemp.push_back(atoi(var.c_str()));
    }
    sort(hutemp.begin(), hutemp.end());
    
    for(int i =((int)hutemp.size()-1); i>=0;i--){
        auto xing = Sprite::create(StringUtils::format("result/paixing_%d.png",atoi(pais.at(i).c_str())));
        addChild(xing,999);
        xing->setOpacity(77);
        xing->setScale(3.0f);
        xing->setPosition(640 - 100*(hutemp.size()-1)+(hutemp.size()-1-i)*200,posY);
        xing->runAction(Sequence::create(DelayTime::create(i*(5.0f/24)),Spawn::create(ScaleTo::create(3.0/24, 0.8f),FadeTo::create(3.0f/24, 255), NULL),ScaleTo::create(2.0/24, 1.0f), NULL));
    }
    //光效动画
    Point pos1 = Point(200,posY);
    Point pos2 = Point(1000,posY);
    Sprite* guangXiao1 = Sprite::create("result/hupai_light.png");
    guangXiao1->setPosition(pos1);
    guangXiao1->setOpacity(77);
    addChild(guangXiao1,999);
    guangXiao1->runAction(Sequence::create(DelayTime::create(12.0f/24),Spawn::create(ScaleTo::create(5.0/24, 2.0f,1.2f),MoveTo::create(5.0/24, pos2),FadeTo::create(5.0/24, 200),NULL),Spawn::create(ScaleTo::create(5.0/24, 1.0f,1.0f),MoveTo::create(5.0/24, pos2), FadeTo::create(5.0/24, 0), NULL),NULL));
    
    
}

void ReviewGame::createPlayer(PlayerGameData data, int type, Player* playerInfo){
    if (type == ClientSeatId::hero){
        if (playerHero == NULL){
            playerHero = PlayerHero::create();
            playerHero->initPlayer(playerInfo);
            playerHero->setIsAllowPlay(false);
            playerHero->setPlayerTingState(data.status == 1?true:false);
            addChild(playerHero, 2);
            playerHero->recoverCpg(data.chiData ,data.pengData , data.gangData,data.angang);
            playerHero->recoverHand(data.hand,data.lastpoker);
            playerHero->recoverPlayed(data.outhand);
            playerHero->recoverHua(data.hua);
        }
    }
    else if (type == ClientSeatId::left){
        if (playerLeft == NULL){
            playerLeft = PlayerLeft::create();
            playerLeft->initPlayer(playerInfo);
            playerLeft->setPlayerTingState(data.status == 1?true:false);
            playerLeft->setIsOffLine(data.isOnline == 0?true:false);
            addChild(playerLeft);
            playerLeft->recoverCpg(data.chiData ,data.pengData , data.gangData,data.angang);
            playerLeft->drawMingPai(data.hand);
            playerLeft->recoverPlayed(data.outhand);
            playerLeft->recoverHua(data.hua);
            
        }
    }
    else if (type == ClientSeatId::right){
        if (playerRight == NULL){
            playerRight = PlayerRight::create();
            playerRight->initPlayer(playerInfo);
            playerRight->setPlayerTingState(data.status == 1?true:false);
            playerRight->setIsOffLine(data.isOnline == 0?true:false);
            addChild(playerRight);
            playerRight->recoverCpg(data.chiData ,data.pengData , data.gangData,data.angang);
            playerRight->drawMingPai(data.hand);
            playerRight->recoverPlayed(data.outhand);
            playerRight->recoverHua(data.hua);
            
        }
    }
    else if (type == ClientSeatId::opposite){
        if (playerOpposite == NULL){
            playerOpposite = PlayerOpposite::create();
            playerOpposite->initPlayer(playerInfo);
            playerOpposite->setPlayerTingState(data.status == 1?true:false);
            playerOpposite->setIsOffLine(data.isOnline == 0?true:false);
            addChild(playerOpposite);
            playerOpposite->recoverCpg(data.chiData ,data.pengData , data.gangData,data.angang);
            playerOpposite->drawMingPai(data.hand);
            playerOpposite->recoverPlayed(data.outhand);
            playerOpposite->recoverHua(data.hua);
            
        }
    }
}



void ReviewGame::onEnterTransitionDidFinish(){
    GAMEDATA::getInstance()->setIsInGameScene(true);
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getScrollTextCommand());
}

void ReviewGame::onExit()
{
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(dealJongsListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(turnListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(otherListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(gameResultListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(playerCpgListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(othersPengListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(othersGangListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(othersChiListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(tingNotifyListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(tingRespListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(trusteeshipRespListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(trusteeshipNotifyListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(trusteeshipCancelListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(heroChiRespListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(heroPengRespListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(heroGangRespListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(playerTingNotifyListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(viewIntnetListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(coreOpenFriendRoomListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(coreLoginRespListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(fupanPlayerInfoListener);
    
}



void ReviewGame::addCoustomListener(){
    
    //好友房间游戏未开始重新连接
    coreOpenFriendRoomListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_FRIEND_OPEN_ROOM_RESP, [=](EventCustom* event){
        GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
        FriendOpenRoomRespData resp = GAMEDATA::getInstance()->getFriendOpenRoomResp();
        if(resp.result == 1){
            GAMEDATA::getInstance()->setFangZhuId(UserData::getInstance()->getPoxiaoId());
            Director::getInstance()->replaceScene(TransitionFade::create(1, MjGameScene::create()));
        }
    });
    
    coreLoginRespListener = EventListenerCustom::create(MSG_LOGIN_RESP, [=](EventCustom* event){
        //  TODO
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(coreLoginRespListener, 1);
    
    fupanPlayerInfoListener = EventListenerCustom::create(MSG_GAME_FU_PAN_PLAYER_NOTIFY, [=](EventCustom* event){
        //复盘功能只存在于私人房间
        auto wukaibao  = Sprite::create("gameview/wu_kaibao.png");
        wukaibao->setVisible(false);
        addChild(wukaibao);
        if(GAMEDATA::getInstance()->getPrivateKaibao() == "0"){
            wukaibao->setVisible(true);
        }
        auto lezi = Sprite::create();
        addChild(lezi);
        if(GAMEDATA::getInstance()->getPrivateLezi() == StringUtils::format("%d",LeziType::type1100)){
            lezi->setTexture("gameview/lezi_1100.png");
        }else if(GAMEDATA::getInstance()->getPrivateLezi() == StringUtils::format("%d",LeziType::type1120)){
            lezi->setTexture("gameview/lezi_1120.png");
        }else if(GAMEDATA::getInstance()->getPrivateLezi() == StringUtils::format("%d",LeziType::type1150)){
            lezi->setTexture("gameview/lezi_1150.png");
        }else if(GAMEDATA::getInstance()->getPrivateLezi() == StringUtils::format("%d",LeziType::type2200)){
            lezi->setTexture("gameview/lezi_2200.png");
        }else if(GAMEDATA::getInstance()->getPrivateLezi() == StringUtils::format("%d",LeziType::type2240)){
            lezi->setTexture("gameview/lezi_2240.png");
        }else if(GAMEDATA::getInstance()->getPrivateLezi() == StringUtils::format("%d",LeziType::type22100)){
            lezi->setTexture("gameview/lezi_22100.png");
        }else if(GAMEDATA::getInstance()->getPrivateLezi() == StringUtils::format("%d",LeziType::type55c)){
            lezi->setTexture("competition/55wulezi_1.png");
        }
        auto emsc =  Sprite::create("gameview/2mo3chong.png");
        emsc->setVisible(false);
        addChild(emsc);
        if(GAMEDATA::getInstance()->getPrivateEmsc() == "1"){
            emsc->setVisible(true);
        }
        int wid = lezi->getContentSize().width +(wukaibao->isVisible()?(wukaibao->getContentSize().width):0)+(emsc->isVisible()?(emsc->getContentSize().width):0);
        wukaibao->setPosition((Director::getInstance()->getVisibleSize().width-wid)/2,160);
        wukaibao->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        lezi->setPosition((Director::getInstance()->getVisibleSize().width-wid)/2+(wukaibao->isVisible()?(wukaibao->getContentSize().width):0),160);
        lezi->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        emsc->setPosition((Director::getInstance()->getVisibleSize().width-wid)/2+lezi->getContentSize().width+(wukaibao->isVisible()?(wukaibao->getContentSize().width):0),160);
        emsc->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        ((Orientation*)getChildByTag(123))->showOrientation(GAMEDATA::getInstance()->getHeroSeatId());
        ((Orientation*)getChildByTag(123))->showWhoBank(GAMEDATA::getInstance()->getHeroSeatId(),GAMEDATA::getInstance()->getCurrentBank());
        guiLayer->updateData();
        FupanGameData data = GAMEDATA::getInstance()->getFupanGameData();
        for (int i = 0; i < data.players.size(); i++)
        {
            PlayerGameData player = data.players.at(i);
            Player* info = new Player();
            info->setSeatId(player.seatId);
            info->setGold(player.gold);
            info->setDiamond(player.diamond);
            info->setNickname(player.nickname);
            info->setPicture(player.pic);
            info->setGender(player.gender);
            info->setScore(player.jifen);
            info->setTicket(player.lequan);
            info->setLockDiamond(player.bangzuan);
            info->setPoxiaoId(player.poxiaoId);
            info->setFangka(player.fangka);
            info->setIP(player.ip);
            info->setIsReady(true);
            info->setUmark(player.umark);
            GAMEDATA::getInstance()->addPlayersInfo(info);
            createPlayer(player,SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), player.seatId),info);
        }
        
        showPaiduiNum(91);
        auto controlbg = Sprite::create("fupan/bg.png");
        controlbg->setPosition(640,220);
        addChild(controlbg,100);
        
        //记录玩家的手牌
        PlayMingpaiRecord record;
        record.step = fupanStep;
        if(GAMEDATA::getInstance()->getMyGameModel() == GameModel::FOURPLAYER){
            PlayerMingpai leftpai;
            leftpai.seatId = ClientSeatId::left;
            leftpai.playerCpgRecords = playerLeft->playerCpgRecords;
            leftpai.playerHandJongs = playerLeft->playerHandJongs;
            leftpai.playerPlayedJongs =playerLeft->playerPlayedJongs;
            leftpai.hua = playerLeft->getHuaNum();
            leftpai.isTing =  false;
            record.record.push_back(leftpai);
            
            PlayerMingpai rightpai;
            rightpai.seatId = ClientSeatId::right;
            rightpai.playerCpgRecords = playerRight->playerCpgRecords;
            rightpai.playerHandJongs = playerRight->playerHandJongs;
            rightpai.playerPlayedJongs =playerRight->playerPlayedJongs;
            rightpai.hua = playerRight->getHuaNum();
            rightpai.isTing =  false;
            record.record.push_back(rightpai);
            
        }
        PlayerMingpai oppsitepai;
        oppsitepai.seatId = ClientSeatId::opposite;
        oppsitepai.playerCpgRecords = playerOpposite->playerCpgRecords;
        oppsitepai.playerHandJongs = playerOpposite->playerHandJongs;
        oppsitepai.playerPlayedJongs =playerOpposite->playerPlayedJongs;
        oppsitepai.hua = playerOpposite->getHuaNum();
        oppsitepai.isTing =  false;
        record.record.push_back(oppsitepai);
        PlayerMingpai heropai;
        heropai.seatId = ClientSeatId::hero;
        heropai.playerCpgRecords = playerHero->playerCpgRecords;
        heropai.playerHandJongs = playerHero->playerHandJongs;
        heropai.playerPlayedJongs =playerHero->playerPlayedJongs;
        heropai.hua = playerHero->getHuaNum();
        heropai.isTing =  false;
        record.record.push_back(heropai);
        myPlayMingpaiRecord.push_back(record);
        
        image1= MenuItemImage::create("fupan/down_1.png", "fupan/down_2.png","fupan/down_3.png",CC_CALLBACK_0(ReviewGame::controlDown, this));
        auto image2 = MenuItemImage::create("fupan/pause_1.png", "fupan/pause_2.png",CC_CALLBACK_0(ReviewGame::controlPause, this));
        image2->setTag(1087);
        image3 = MenuItemImage::create("fupan/up_1.png", "fupan/up_2.png","fupan/up_3.png",CC_CALLBACK_0(ReviewGame::controlUp, this));
        MenuItemImage* image4 = MenuItemImage::create("fupan/back_1.png", "fupan/back_2.png",CC_CALLBACK_0(ReviewGame::controlBack, this));
        auto menucontrol = Menu::create(image1,image2,image3,image4,NULL);
        menucontrol->alignItemsHorizontallyWithPadding(50);
        menucontrol->setPosition(640,220);
        menucontrol->setTag(1088);
        addChild(menucontrol,900);
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(fupanPlayerInfoListener, 1);
    
    
    turnListener = EventListenerCustom::create(MSG_PLAYER_TURN_WHO, [=](EventCustom* event){
        PlayerTurnData* data = static_cast<PlayerTurnData*>(event->getUserData());
        PlayerTurnData newData = *data;
        int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(),newData.seatId);
        ((Orientation*)getChildByTag(123))->showPlayerTurn(GAMEDATA::getInstance()->getHeroSeatId(), newData.seatId);
        showPaiduiNum(atoi(data->rest.c_str()));
        if (seatId == ClientSeatId::hero){
            playerHero->hideCurrentBigJong();
            playerHero->playerTurnReplaceMingpai(newData);
        }
        else if (seatId == ClientSeatId::left){
            playerLeft->replaceTurnHuaMingpai(newData);
            playerLeft->drawLeftPlayerTurnMingpai(newData.poker);
        }
        else if (seatId == ClientSeatId::right){
            
            playerRight->replaceTurnHuaMingpai(newData);
            playerRight->drawRightPlayerTurnMingpai(newData.poker);
        }
        else if (seatId == ClientSeatId::opposite){
            playerOpposite->replaceTurnHuaMingpai(newData);
            playerOpposite->drawOppositePlayerTurnMingpai(newData.poker);
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(turnListener, 1);
    
    otherListener = EventListenerCustom::create(MSG_OTHER_PALYER_JONG, [=](EventCustom* event){
        
        std::string result = static_cast<char*>(event->getUserData());
        vector<string> res =  StringUtil::split(result, ",");
        int seat = atoi(res.at(0).c_str());
        int poker =atoi(res.at(1).c_str());
        int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), seat);
        if (seatId == ClientSeatId::left){
            playerLeft->setIsOffLine(false);
            playerLeft->stopTimeClockAnim();
            playerLeft->drawPlayedJongMingpai(poker);
            if(poker == playerOpposite->getLastPoker()){
                Audio::getInstance()->playSoundGengShang(playerLeft->getPlayerInfo()->getGender());
            }else if(poker == playerHero->getLastPoker()){
                Audio::getInstance()->playSoundXiaGeng(playerLeft->getPlayerInfo()->getGender());
            }
        }
        else if (seatId == ClientSeatId::right){
            playerRight->setIsOffLine(false);
            playerRight->stopTimeClockAnim();
            playerRight->drawPlayedJongMingpai(poker);
            if(poker == playerHero->getLastPoker()){
                Audio::getInstance()->playSoundGengShang(playerRight->getPlayerInfo()->getGender());
            }else if(poker== playerOpposite->getLastPoker()){
                Audio::getInstance()->playSoundXiaGeng(playerRight->getPlayerInfo()->getGender());
            }
        }
        else if (seatId == ClientSeatId::opposite){
            playerOpposite->setIsOffLine(false);
            playerOpposite->stopTimeClockAnim();
            playerOpposite->drawPlayedJongMingpai(poker);
            if(poker == playerRight->getLastPoker()){
                Audio::getInstance()->playSoundGengShang(playerOpposite->getPlayerInfo()->getGender());
            }else if(poker == playerLeft->getLastPoker()){
                Audio::getInstance()->playSoundXiaGeng(playerOpposite->getPlayerInfo()->getGender());
            }
        }else if(seatId == ClientSeatId::hero){
            playerHero->stopTimeClockAnim();
            playerHero->drawPlayedJongMingpai(poker);
            if(poker == playerLeft->getLastPoker()){
                Audio::getInstance()->playSoundGengShang(playerHero->getPlayerInfo()->getGender());
            }else if(poker == playerRight->getLastPoker()){
                Audio::getInstance()->playSoundXiaGeng(playerHero->getPlayerInfo()->getGender());
            }
        }
        if(fupanStep>= currentMaxStep){
            //记录玩家的手牌
            PlayMingpaiRecord record;
            record.step = fupanStep;
            PlayerMingpai leftpai;
            leftpai.seatId = ClientSeatId::left;
            leftpai.playerCpgRecords = playerLeft->playerCpgRecords;
            leftpai.playerHandJongs = playerLeft->playerHandJongs;
            leftpai.playerPlayedJongs =playerLeft->playerPlayedJongs;
            leftpai.hua = playerLeft->getHuaNum();
            leftpai.isTing =  playerLeft->getPlayerTingState();
            record.record.push_back(leftpai);
            PlayerMingpai oppsitepai;
            oppsitepai.seatId = ClientSeatId::opposite;
            oppsitepai.playerCpgRecords = playerOpposite->playerCpgRecords;
            oppsitepai.playerHandJongs = playerOpposite->playerHandJongs;
            oppsitepai.playerPlayedJongs =playerOpposite->playerPlayedJongs;
            oppsitepai.hua = playerOpposite->getHuaNum();
            oppsitepai.isTing =  playerOpposite->getPlayerTingState();
            record.record.push_back(oppsitepai);
            PlayerMingpai rightpai;
            rightpai.seatId = ClientSeatId::right;
            rightpai.playerCpgRecords = playerRight->playerCpgRecords;
            rightpai.playerHandJongs = playerRight->playerHandJongs;
            rightpai.playerPlayedJongs =playerRight->playerPlayedJongs;
            rightpai.hua = playerRight->getHuaNum();
            rightpai.isTing =  playerRight->getPlayerTingState();
            record.record.push_back(rightpai);
            PlayerMingpai heropai;
            heropai.seatId = ClientSeatId::hero;
            heropai.playerCpgRecords = playerHero->playerCpgRecords;
            heropai.playerHandJongs = playerHero->playerHandJongs;
            heropai.playerPlayedJongs =playerHero->playerPlayedJongs;
            heropai.hua = playerHero->getHuaNum();
            heropai.isTing =   playerHero->getPlayerTingState();
            record.record.push_back(heropai);
            myPlayMingpaiRecord.push_back(record);
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(otherListener, 1);
    
    othersChiListener = EventListenerCustom::create(MSG_OTHER_PLAYER_CHI, [=](EventCustom* event){
        PlayerCpgtData* data = static_cast<PlayerCpgtData*>(event->getUserData());
        PlayerCpgtData newData = *data;
        int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(),newData.seatId);
        setCurrentJongVisible(newData.sId);
        ((Orientation*)getChildByTag(123))->showPlayerTurn(GAMEDATA::getInstance()->getHeroSeatId(),newData.seatId);
        if (seatId == ClientSeatId::left){
            playerLeft->drawPlayerMingpaiChi(newData, getPlayerBySeatId(newData.sId));
            playerLeft->playerCpgAnim(CpgType::chi, ClientSeatId::left);
        }
        else if (seatId == ClientSeatId::right){
            playerRight->drawPlayerMingpaiChi(newData, getPlayerBySeatId(newData.sId));
            playerRight->playerCpgAnim(CpgType::chi, ClientSeatId::right);
            
        }
        else if (seatId == ClientSeatId::opposite){
            playerOpposite->drawPlayerMingpaiChi(newData, getPlayerBySeatId(newData.sId));
            playerOpposite->playerCpgAnim(CpgType::chi, ClientSeatId::opposite);
            
        }else if (seatId == ClientSeatId::hero){
            hideTingGangControllPad();
            HeroCpgRespData heroTingData;
            heroTingData.result =1;
            std::vector<string> chipai = StringUtil::split(newData.chi[0], ",");
            playerHero->drawHeroChiMingpai(heroTingData,chipai,getPlayerBySeatId(newData.sId));
            playerHero->playerCpgAnim(CpgType::chi, ClientSeatId::hero);
            
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(othersChiListener, 1);
    
    othersPengListener = EventListenerCustom::create(MSG_OTHER_PLAYER_PENG, [=](EventCustom* event){
        PlayerCpgtData* data = static_cast<PlayerCpgtData*>(event->getUserData());
        PlayerCpgtData newData = *data;
        int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), newData.seatId);
        setCurrentJongVisible(newData.sId);
        ((Orientation*)getChildByTag(123))->showPlayerTurn(GAMEDATA::getInstance()->getHeroSeatId(),newData.seatId);
        if (seatId == ClientSeatId::left){
            hideTingGangControllPad();
            playerLeft->drawPlayerMingpaiPeng(newData, getPlayerBySeatId(newData.sId));
            playerLeft->playerCpgAnim(CpgType::peng, ClientSeatId::left);
            
        }
        else if (seatId == ClientSeatId::right){
            hideTingGangControllPad();
            playerRight->drawPlayerMingpaiPeng(newData, getPlayerBySeatId(newData.sId));
            playerRight->playerCpgAnim(CpgType::peng, ClientSeatId::right);
            
        }
        else if (seatId == ClientSeatId::opposite){
            hideTingGangControllPad();
            playerOpposite->drawPlayerMingpaiPeng(newData, getPlayerBySeatId(newData.sId));
            playerOpposite->playerCpgAnim(CpgType::peng, ClientSeatId::opposite);
            
        } else if (seatId == ClientSeatId::hero){
            hideTingGangControllPad();
            HeroCpgRespData heroCpgData;
            heroCpgData.result = 1;
            heroCpgData.playCpgt = newData;
            playerHero->drawHeroPengMingpai(heroCpgData, getPlayerBySeatId(newData.sId));
            playerHero->playerCpgAnim(CpgType::peng, ClientSeatId::hero);
            
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(othersPengListener, 1);
    
    othersGangListener = EventListenerCustom::create(MSG_OTHER_PLAYER_GANG, [=](EventCustom* event){
        PlayerCpgtData* data = static_cast<PlayerCpgtData*>(event->getUserData());
        PlayerCpgtData newData = *data;
        int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), newData.seatId);
        setCurrentJongVisible(newData.sId);
        ((Orientation*)getChildByTag(123))->showPlayerTurn(GAMEDATA::getInstance()->getHeroSeatId(), newData.seatId);
        if (seatId == ClientSeatId::left){
            hideTingGangControllPad();
            playerLeft->drawPlayerMingpaiGang(newData, getPlayerBySeatId(data->sId));
            playerLeft->playerCpgAnim(CpgType::gang, ClientSeatId::left);
        }
        else if (seatId == ClientSeatId::right){
            hideTingGangControllPad();
            playerRight->drawPlayerMingpaiGang(newData, getPlayerBySeatId(data->sId));
            playerRight->playerCpgAnim(CpgType::gang, ClientSeatId::right);
        }
        else if (seatId == ClientSeatId::opposite){
            hideTingGangControllPad();
            playerOpposite->drawPlayerMingpaiGang(newData, getPlayerBySeatId(data->sId));
            playerOpposite->playerCpgAnim(CpgType::gang, ClientSeatId::opposite);
        }else if (seatId == ClientSeatId::hero){
            hideTingGangControllPad();
            HeroCpgRespData heroTingData;
            heroTingData.result = 1;
            heroTingData.playCpgt = newData;
            playerHero->drawHeroGangMingpai(heroTingData, getPlayerBySeatId(newData.sId));
            playerHero->playerCpgAnim(CpgType::gang, ClientSeatId::hero);
        }
        
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(othersGangListener, 1);
    
    playerTingNotifyListener = EventListenerCustom::create(MSG_PLAYER_TING_NOTIFY, [=](EventCustom* event){
        std::string currentSeatId = static_cast<char*>(event->getUserData());
        int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), atoi(currentSeatId.c_str()));
        playerTingAnim(seatId);
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(playerTingNotifyListener, 1);
    
    tingNotifyListener = EventListenerCustom::create(MSG_HERO_TING_GANG, [=](EventCustom* event){
        PlayerCpgtData* cpgtData = static_cast<PlayerCpgtData*>(cpgtData);
        PlayerCpgtData newCpgtData = *cpgtData;
        if (newCpgtData.seatId == GAMEDATA::getInstance()->getHeroSeatId()){
            showTingGangControllPad(newCpgtData);
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(tingNotifyListener, 1);
    
    tingRespListener = EventListenerCustom::create(MSG_PLAYER_TING_RESP, [=](EventCustom* event){
        char* buf = static_cast<char*>(event->getUserData());
        if (atoi(buf) == 1){
            GAMEDATA::getInstance()->setIsTingState(true);
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(tingRespListener, 1);
    
    heroChiRespListener = EventListenerCustom::create(MSG_HERO_CHI_RESP, [=](EventCustom* event){
        HeroCpgRespData* heroData = static_cast<HeroCpgRespData*>(event->getUserData());
        HeroCpgRespData newHeroData = *heroData;
        shmjHeroCpgtData = *heroData;
        playerHero->hideCurrentBigJong();
        std::vector<string> chipai = StringUtil::split(selectedChi, ",");
        playerHero->drawHeroChi(newHeroData, chipai, playerLeft);
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(heroChiRespListener, 1);
    
    heroPengRespListener = EventListenerCustom::create(MSG_HERO_PENG_RESP, [=](EventCustom* event){
        HeroCpgRespData* cpgRespData  = static_cast<HeroCpgRespData*>(event->getUserData());
        shmjHeroCpgtData = *cpgRespData;
        HeroCpgRespData newCpgRespData = *cpgRespData;
        int clientSeatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), shmjPlayerCpgtData.sId);
        playerHero->hideCurrentBigJong();
        if(cpgRespData->result == 1||cpgRespData->result == 2){
            if (clientSeatId == ClientSeatId::right){
                playerHero->drawHeroPeng(newCpgRespData, playerRight);
            }
            else if (clientSeatId == ClientSeatId::opposite){
                playerHero->drawHeroPeng(newCpgRespData, playerOpposite);
            }
            else{
                playerHero->drawHeroPeng(newCpgRespData, playerLeft);
            }
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(heroPengRespListener, 1);
    
    heroGangRespListener = EventListenerCustom::create(MSG_HERO_GANG_RESP, [=](EventCustom* event){
        HeroCpgRespData* resp = static_cast<HeroCpgRespData*>(event->getUserData());
        shmjHeroCpgtData = *resp;
        playerHero->hideCurrentBigJong();
        int clientSeatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), shmjPlayerCpgtData.sId);
        if (resp->result == 0){
            playerHero->stopTimeClockAnim();
        }
        else{
            
            if (clientSeatId == ClientSeatId::right){
                playerHero->drawHeroGang(shmjHeroCpgtData, playerRight);
            }
            else if (clientSeatId == ClientSeatId::opposite){
                playerHero->drawHeroGang(shmjHeroCpgtData, playerOpposite);
            }
            else{
                playerHero->drawHeroGang(shmjHeroCpgtData, playerLeft);
            }
        }
        
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(heroGangRespListener, 1);
    
    playerCpgListener = EventListenerCustom::create(MSG_PLAYER_CPG, [=](EventCustom* event){
        HeroCpgRespData* cpgData = static_cast<HeroCpgRespData*>(event->getUserData());
        HeroCpgRespData newCpgData = *cpgData;
        drawCpgControllPad(newCpgData.playCpgt);
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(playerCpgListener, 1);
    
    gameResultListener = EventListenerCustom::create(MSG_GAME_RESULT, [=](EventCustom* event){
        string flag = static_cast<char*>(event->getUserData());
        if(flag == "1"||flag == "2"){
            GAMEDATA::getInstance()->setIsTrusteeship(false);
            //播放动画
            //step检测胡牌类型
            int seatId1 = -1;
            std::vector<int> seatId2;
            int seatId3 =-1;
            seatId2.clear();
            bool zimoState = false;
            bool gangkaiState = false;
            bool qianggangState = false;
            bool isliuju = true;
            vector<GameResultData> results = GAMEDATA::getInstance()->getGameResults();
            for (GameResultData data: results) {
                if(data.result==1){
                    bool find = true;
                    vector<std::string> hu = StringUtil::split(data.huType, ",");
                    for(auto var:hu){
                        if(var == "3"){
                            seatId1 =SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), data.seatId);
                            gangkaiState = true;
                            find = false;
                        }
                    }
                    //自摸
                    if(find){
                        seatId1 =   SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), data.seatId);
                        zimoState=true;
                    }
                    isliuju = false;
                }else if(data.result==2){
                    //点炮
                    isliuju = false;
                    seatId1 = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), data.seatId);
                }else if(data.result==3){
                    //普通赢
                    isliuju = false;
                    vector<std::string> hu = StringUtil::split(data.huType, ",");
                    for(auto var:hu){
                        if(var == "12"){
                            qianggangState = true;
                            seatId3 =SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), data.seatId);
                            break;
                        }
                    }
                    seatId2.push_back(SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(),data.seatId));
                }
            }
            if(zimoState){
                Audio::getInstance()->playSoundHuMusic(1);
                if(seatId1 == ClientSeatId::left){
                    playerLeft->playSoundHuPai(0);
                }else if(seatId1 == ClientSeatId::opposite){
                    playerOpposite->playSoundHuPai(0);
                }else if(seatId1 == ClientSeatId::right){
                    playerRight->playSoundHuPai(0);
                }else {
                    playerHero->playSoundHuPai(0);
                }
                HupaiAnim* hupai = HupaiAnim::create(MahjongHuType::zimoHu,atoi(GAMEDATA::getInstance()->getDiaopao().c_str()),seatId1,seatId2);
                addChild(hupai,999);
            }else if(gangkaiState){
                Audio::getInstance()->playSoundHuMusic(1);
                if(seatId1 == ClientSeatId::left){
                    playerLeft->playSoundHuPai(1);
                }else if(seatId1 == ClientSeatId::opposite){
                    playerOpposite->playSoundHuPai(1);
                }else if(seatId1 == ClientSeatId::right){
                    playerRight->playSoundHuPai(1);
                }else {
                    playerHero->playSoundHuPai(1);
                }
                HupaiAnim* hupai = HupaiAnim::create(MahjongHuType::gangkaiHu,atoi(GAMEDATA::getInstance()->getDiaopao().c_str()),seatId1,seatId2);
                addChild(hupai,999);
            }else if(qianggangState){
                Audio::getInstance()->playSoundHuMusic(1);
                if(seatId1 == ClientSeatId::left){
                    playerLeft->playSoundHuPai(2);
                }else if(seatId1 == ClientSeatId::opposite){
                    playerOpposite->playSoundHuPai(2);
                }else if(seatId1 == ClientSeatId::right){
                    playerRight->playSoundHuPai(2);
                }else {
                    playerHero->playSoundHuPai(2);
                }
                HupaiAnim* hupai = HupaiAnim::create(MahjongHuType::qianggangHu,atoi(GAMEDATA::getInstance()->getDiaopao().c_str()),seatId1,seatId2);
                addChild(hupai,999);
            }else  if(!isliuju){
                //判断胡牌的类型
                Audio::getInstance()->playSoundHuMusic(0);
                if(seatId1 == ClientSeatId::left){
                    playerLeft->playSoundHuPai(3);
                }else if(seatId1 == ClientSeatId::opposite){
                    playerOpposite->playSoundHuPai(3);
                }else if(seatId1 == ClientSeatId::right){
                    playerRight->playSoundHuPai(3);
                }else {
                    playerHero->playSoundHuPai(3);
                }
                HupaiAnim* hupai = HupaiAnim::create(MahjongHuType::putongHu,atoi(GAMEDATA::getInstance()->getDiaopao().c_str()),seatId1,seatId2);
                addChild(hupai,999);
            }else{
                //流局动画
                Audio::getInstance()->playSoundLiuJu(UserData::getInstance()->getGender());
                LiuJuAnim* liuju = LiuJuAnim::create();
                addChild(liuju,3);
                GAMEDATA::getInstance()->setIsLiuJu(true);
            }
        }
        GAMEDATA::getInstance()->setPrivateGameNum("0");
        GAMEDATA::getInstance()->setFangZhuId("");
        GAMEDATA::getInstance()->clearPlayersInfo();
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(gameResultListener, 1);
    
}

