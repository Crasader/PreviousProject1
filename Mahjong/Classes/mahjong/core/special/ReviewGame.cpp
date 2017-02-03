#include "mahjong/core/special/ReviewGame.h"
#include "mahjong/anim/DealJongAnim.h"
#include "mahjong/core/widget/Orientation.h"
#include "mahjong/core/widget/CardStack.hpp"
#include "mahjong/lobby/LobbyScene.h"
#include "mahjong/utils/SeatIdUtil.h"
#include "mahjong/utils/StringUtil.h"
#include "mahjong/anim/HupaiAnim.hpp"
#include "mahjong/anim/PlayerCpgAnim.hpp"
#include "mahjong/result/ResultScene.hpp"
#include "mahjong/anim/LiuJuAnim.hpp"
#include "mahjong/anim/OutFogAnim.hpp"
#include "mahjong/dialog/prompt/HintDialog.hpp"
#include "mahjong/friend/dialog/DissovleRoomDialog.hpp"
#include "mahjong/dialog/network/LostNetwork.hpp"
#include "mahjong/dialog/prompt/TextHintDialog.hpp"
#include "mahjong/widget/ScrollTextEx.h"
#include "mahjong/widget/batteryinfo/BatteryInfo.h"
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
    GAMEDATA::getInstance()->setIsPlaying(false);
    GAMEDATA::getInstance()->setIsLiuJu(false);
    GAMEDATA::getInstance()->setIsGotoLobby(false);
    GAMEDATA::getInstance()->setStartPaiAngang(false);
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
    //复盘功能只存在于私人房间
    auto wukaibao  = Sprite::create("gameview/wu_kaibao.png");
    wukaibao->setVisible(false);
    addChild(wukaibao);
    if(GAMEDATA::getInstance()->getPrivateKaibao() == "0"){
        wukaibao->setVisible(true);
    }
    auto lezi = Sprite::create();
    addChild(lezi);
    if(GAMEDATA::getInstance()->getPrivateLezi() == "1"){
        //有乐子
        lezi->setTexture("gameview/40_lezi.png");
    }else{
        lezi->setTexture("gameview/wu_lezi.png");
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
    
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    addChild(menu1,800);
    
}


void ReviewGame::controlDown(){
    
    if(myPlayMingpaiRecord.size()>1){
        fupanStep -= 2;
        myPlayMingpaiRecord.pop_back();
        PlayMingpaiRecord record = myPlayMingpaiRecord.at(myPlayMingpaiRecord.size()-1);
        for(auto var:record.record){
            if(var.seatId==ClientSeatId::left){
                playerLeft->updateMingpai(var.playerHandJongs, var.playerPlayedJongs,var.playerCpgRecords);
            }else if(var.seatId==ClientSeatId::opposite){
                playerOpposite->updateMingpai(var.playerHandJongs, var.playerPlayedJongs,var.playerCpgRecords);
            }else if(var.seatId==ClientSeatId::right){
                playerRight->updateMingpai(var.playerHandJongs, var.playerPlayedJongs,var.playerCpgRecords);
            }else if(var.seatId==ClientSeatId::hero){
                playerHero->updateMingpai(var.playerHandJongs, var.playerPlayedJongs,var.playerCpgRecords);
            }
        }
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
    interval+=3.0;
}
void ReviewGame::controlBack(){
    GAMEDATA::getInstance()->setIsFuPan(false);
    GAMEDATA::getInstance()->clearPlayersInfo();
    Director::getInstance()->replaceScene(LobbyScene::create());
}

void ReviewGame::update(float dt){
    interval += dt;
    if(playing){
        if(interval>1.5){
            if(fupanStep<GAMEDATA::getInstance()->getPlaybackInfo().playBackInfo.size())
                NetworkManage::getInstance()->receiveMsg(GAMEDATA::getInstance()->getPlaybackInfo().playBackInfo.at(fupanStep));
            interval = interval-1.5;
            fupanStep++;
        }
    }else{
        interval=0;
    }
}

void ReviewGame::handlePlayBackData(){
    //已打牌为界限,拆分圈
    PlayBackInfo backInfo =  GAMEDATA::getInstance()->getPlaybackInfo();
    for(int i=0; i<backInfo.playBackInfo.size();i++){
        std::string msg = backInfo.playBackInfo.at(i);
        rapidjson::Document _mDoc;
        if(NULL == msg.c_str() || !msg.compare(""))
            return;
        _mDoc.Parse<0>(msg.c_str());
        if(_mDoc.HasParseError() || !_mDoc.IsObject())
            return;
        const rapidjson::Value &code = _mDoc["code"];
        if (code.IsInt() && code.GetInt() == 2005) {
            
        }
    }
}


void ReviewGame::drawCpgControllPad(){
    controllPad->removeAllChildrenWithCleanup(true);
    auto qi =MenuItemImage::create("gameview/mj_qi.png", "gameview/mj_qi.png", CC_CALLBACK_0(ReviewGame::heroDoCpgQi,this));
    qi->setPosition(Point(0, 0));
    controllPad->addChild(qi);
    MenuItemImage* chi = nullptr;
    MenuItemImage* peng = nullptr;
    MenuItemImage* gang = nullptr;
    PlayerCpgtData cpg = GAMEDATA::getInstance()->getPlayerCpgt();
    int buttonCount = 1;
    if (cpg.chi.size() > 0){
        chi = MenuItemImage::create("gameview/mj_chi.png", "gameview/mj_chi.png", CC_CALLBACK_0(ReviewGame::showHeroChiUi, this));
        chi->setPosition(Point(-buttonCount * 160, 0));
        controllPad->addChild(chi);
        buttonCount++;
    }
    if (cpg.peng != ""){
        peng = MenuItemImage::create("gameview/mj_peng.png", "gameview/mj_peng.png", CC_CALLBACK_0(ReviewGame::heroDoPeng, this));
        peng->setPosition(Point(-buttonCount * 160, 0));
        controllPad->addChild(peng);
        buttonCount++;
    }
    if (cpg.gang != ""){
        gang = MenuItemImage::create("gameview/mj_gang.png", "gameview/mj_gang.png", CC_CALLBACK_0(ReviewGame::heroDoGang, this));
        gang->setPosition(Point(-buttonCount * 160, 0));
        controllPad->addChild(gang);
    }
    controllPad->setPosition(Point(1100, 160));
    controllPad->setVisible(true);
}

void ReviewGame::showTingGangControllPad(){
    playerHero->stopTimeClockAnim();
    controllPad->removeAllChildrenWithCleanup(true);
    auto qi = MenuItemImage::create("gameview/mj_qi.png", "gameview/mj_qi.png", CC_CALLBACK_0(ReviewGame::heroDoTingQi, this));
    qi->setPosition(Point(0, 0));
    controllPad->addChild(qi);
    MenuItemImage* ting = nullptr;
    MenuItemImage* penggang = nullptr;
    int buttonCount = 1;
    PlayerCpgtData tingData = GAMEDATA::getInstance()->getPlayerCpgt();
    if (tingData.ting != ""){
        ting = MenuItemImage::create("gameview/mj_ting.png", "gameview/mj_ting.png", CC_CALLBACK_0(ReviewGame::heroDoTing, this));
        ting->setPosition(Point(-buttonCount * 140, 0));
        controllPad->addChild(ting);
        buttonCount++;
    }
    if (tingData.gang != ""){
        penggang = MenuItemImage::create("gameview/mj_gang.png", "gameview/mj_gang.png", CC_CALLBACK_0(ReviewGame::heroDoPengGangAndAGang, this));
        penggang->setPosition(Point(-buttonCount * 140, 0));
        controllPad->addChild(penggang);
        buttonCount++;
    }
    controllPad->setPosition(Point(1100, 160));
    controllPad->setVisible(true);
    playerHero->setIsAllowTouch(false);
    playerHero->setIsAllowPlay(true);
    playerHero->startTimeClockAnim(9, 2);
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


void ReviewGame::showHeroChiUi(){
    controllPad->setVisible(false);
    PlayerCpgtData cpg = GAMEDATA::getInstance()->getPlayerCpgt();
    //吃牌排序
    if (cpg.chi.size() > 1){
        for (int i = 0; i < cpg.chi.size(); i++){
            std::vector<string> pai = StringUtil::split(cpg.chi.at(cpg.chi.size()-1-i), ",");
            pai.push_back(cpg.poker);
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
        //choiceMenu = NULL;
        MenuItemImage* imageItem = MenuItemImage::create();
        imageItem->setTag(0);
        heroDoChi(imageItem);
    }
}

void ReviewGame::heroDoChi(Ref* psend){
    if (NULL != choiceMenu){
        choiceMenu->setVisible(false);
        choiceMenu->removeAllChildren();
    }
    PlayerCpgtData cpg = GAMEDATA::getInstance()->getPlayerCpgt();
    MenuItemImage* item = (MenuItemImage*)psend;
    selectedChi = cpg.chi.at(cpg.chi.size()-1-item->getTag());
    playerHero->stopTimeClockAnim();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getChiCommand(selectedChi, atoi(cpg.poker.c_str())));
}

void ReviewGame::heroDoPeng(){
    controllPad->setVisible(false);
    playerHero->stopTimeClockAnim();
    PlayerCpgtData cpg = GAMEDATA::getInstance()->getPlayerCpgt();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getPengCommand(cpg.peng, atoi(cpg.poker.c_str())));
}

void ReviewGame::heroDoGang(){
    controllPad->setVisible(false);
    playerHero->stopTimeClockAnim();
    PlayerCpgtData cpg = GAMEDATA::getInstance()->getPlayerCpgt();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getGangCommand(cpg.gang, atoi(cpg.poker.c_str()), cpg.flag));
}

void ReviewGame::heroDoCpgQi(){
    controllPad->setVisible(false);
    playerHero->stopTimeClockAnim();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getGiveUpCpgCommmand());
}

void ReviewGame::heroDoTing(){
    playerHero->stopTimeClockAnim();
    controllPad->setVisible(false);
    playerHero->actionTing();
}
void ReviewGame::heroDoTingQi(){
    playerHero->stopTimeClockAnim();
    controllPad->setVisible(false);
    playerHero->actionQi();
    playerHero->startTimeClockAnim();
}

void ReviewGame::heroDoPengGangAndAGang(){
    playerHero->stopTimeClockAnim();
    controllPad->setVisible(false);
    PlayerCpgtData tingData = GAMEDATA::getInstance()->getPlayerCpgt();
    std::vector<string> gangpai = StringUtil::split(tingData.gang, ",");
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getGangCommand(tingData.gang, atoi(gangpai.at(0).c_str()), tingData.flag));
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
    ori->showOrientation(GAMEDATA::getInstance()->getHeroSeatId());
    addChild(ori);
}



PlayerBase* ReviewGame::getPlayerBySeatId(int sid){
    int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), sid);
    setCurrentJongVisible(GAMEDATA::getInstance()->getPlayerCpgt().sId);
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
    if (GAMEDATA::getInstance()->getIsRecover()){
        //重新设置庄的位置
        LastGameData data = GAMEDATA::getInstance()->getLastGameDataBackup();
        if(data.result == 1){
            ((Orientation*)getChildByTag(123))->showWhoBank(GAMEDATA::getInstance()->getHeroSeatId(),GAMEDATA::getInstance()->getCurrentBank());
            ((Orientation*)getChildByTag(123))->showPlayerTurn(GAMEDATA::getInstance()->getHeroSeatId(),data.turn);
            GAMEDATA::getInstance()->setIsPlaying(true);
            int lastplayerSeat = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(),data.pre);
            if(lastplayerSeat == ClientSeatId::hero){
                playerHero->showCurrentPlayedJongIcon(true);
            }else if(lastplayerSeat == ClientSeatId::left){
                playerLeft->showCurrentPlayedJongIcon(true);
            }else if(lastplayerSeat == ClientSeatId::opposite){
                playerOpposite->showCurrentPlayedJongIcon(true);
            }else if(lastplayerSeat == ClientSeatId::right){
                playerRight->showCurrentPlayedJongIcon(true);
            }
            
            int playturn = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), data.turn);
            if(playturn == ClientSeatId::hero){
                playerHero->startTimeClockAnim();
                playerHero->setIsAllowPlay(true);
            }else if(playturn == ClientSeatId::left){
                playerLeft->startTimeClockAnim();
            }else if(playturn == ClientSeatId::opposite){
                playerOpposite->startTimeClockAnim();
            }else if(playturn == ClientSeatId::right){
                playerRight->startTimeClockAnim();
            }
        }
        GAMEDATA::getInstance()->setIsRecover(false);
    }
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
        Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(coreLoginRespListener, 1);
    
    fupanPlayerInfoListener = EventListenerCustom::create(MSG_GAME_FU_PAN_PLAYER_NOTIFY, [=](EventCustom* event){
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
        guiLayer->updateData();
        auto controlbg = Sprite::create("fupan/bg.png");
        controlbg->setPosition(640,220);
        addChild(controlbg,100);
        
        MenuItemImage* image1 = MenuItemImage::create("fupan/down_1.png", "fupan/down_2.png",CC_CALLBACK_0(ReviewGame::controlDown, this));
        MenuItemImage* image2 = MenuItemImage::create("fupan/pause_1.png", "fupan/pause_2.png",CC_CALLBACK_0(ReviewGame::controlPause, this));
        image2->setTag(1087);
        MenuItemImage* image3 = MenuItemImage::create("fupan/up_1.png", "fupan/up_2.png",CC_CALLBACK_0(ReviewGame::controlUp, this));
        MenuItemImage* image4 = MenuItemImage::create("fupan/back_1.png", "fupan/back_2.png",CC_CALLBACK_0(ReviewGame::controlBack, this));
        auto menucontrol = Menu::create(image1,image2,image3,image4,NULL);
        menucontrol->alignItemsHorizontallyWithPadding(50);
        menucontrol->setPosition(640,220);
        menucontrol->setTag(1088);
        addChild(menucontrol,900);
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(fupanPlayerInfoListener, 1);
    
    
    turnListener = EventListenerCustom::create(MSG_PLAYER_TURN_WHO, [=](EventCustom* event){
        int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), GAMEDATA::getInstance()->getPlayerTurn().seatId);
        ((Orientation*)getChildByTag(123))->showPlayerTurn(GAMEDATA::getInstance()->getHeroSeatId(), GAMEDATA::getInstance()->getPlayerTurn().seatId);
        showPaiduiNum(atoi(GAMEDATA::getInstance()->getPlayerTurn().rest.c_str()));
        if (seatId == ClientSeatId::hero){
            playerHero->hideCurrentBigJong();
            playerHero->playerTurnReplace(GAMEDATA::getInstance()->getPlayerTurn());
            if (!GAMEDATA::getInstance()->getIsTingState()){
                playerHero->startTimeClockAnim();
            }
        }
        else if (seatId == ClientSeatId::left){
            playerLeft->replaceTurnHua(GAMEDATA::getInstance()->getPlayerTurn());
            playerLeft->drawLeftPlayerTurnMingpai(GAMEDATA::getInstance()->getPlayerTurn().poker);
            playerLeft->startTimeClockAnim();
        }
        else if (seatId == ClientSeatId::right){
            
            playerRight->replaceTurnHua(GAMEDATA::getInstance()->getPlayerTurn());
            playerRight->drawRightPlayerTurnMingpai(GAMEDATA::getInstance()->getPlayerTurn().poker);
            playerRight->startTimeClockAnim();
        }
        else if (seatId == ClientSeatId::opposite){
            playerOpposite->replaceTurnHua(GAMEDATA::getInstance()->getPlayerTurn());
            playerOpposite->drawOppositePlayerTurnMingpai(GAMEDATA::getInstance()->getPlayerTurn().poker);
            playerOpposite->startTimeClockAnim();
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(turnListener, 1);
    
    otherListener = EventListenerCustom::create(MSG_OTHER_PALYER_JONG, [=](EventCustom* event){
        
        int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), GAMEDATA::getInstance()->getOtherPlayJong().seatId);
        
        //记录玩家的手牌
        
        if (seatId == ClientSeatId::left){
            playerLeft->setIsOffLine(false);
            playerLeft->stopTimeClockAnim();
            playerLeft->drawPlayedJongMingpai(GAMEDATA::getInstance()->getOtherPlayJong().poker);
            if(GAMEDATA::getInstance()->getOtherPlayJong().poker == playerOpposite->getLastPoker()){
                Audio::getInstance()->playSoundGengShang(playerLeft->getPlayerInfo()->getGender());
            }else if(GAMEDATA::getInstance()->getOtherPlayJong().poker == playerHero->getLastPoker()){
                Audio::getInstance()->playSoundXiaGeng(playerLeft->getPlayerInfo()->getGender());
            }
        }
        else if (seatId == ClientSeatId::right){
            playerRight->setIsOffLine(false);
            playerRight->stopTimeClockAnim();
            playerRight->drawPlayedJongMingpai(GAMEDATA::getInstance()->getOtherPlayJong().poker);
            if(GAMEDATA::getInstance()->getOtherPlayJong().poker == playerHero->getLastPoker()){
                Audio::getInstance()->playSoundGengShang(playerRight->getPlayerInfo()->getGender());
            }else if(GAMEDATA::getInstance()->getOtherPlayJong().poker == playerOpposite->getLastPoker()){
                Audio::getInstance()->playSoundXiaGeng(playerRight->getPlayerInfo()->getGender());
            }
        }
        else if (seatId == ClientSeatId::opposite){
            playerOpposite->setIsOffLine(false);
            playerOpposite->stopTimeClockAnim();
            playerOpposite->drawPlayedJongMingpai(GAMEDATA::getInstance()->getOtherPlayJong().poker);
            if(GAMEDATA::getInstance()->getOtherPlayJong().poker == playerRight->getLastPoker()){
                Audio::getInstance()->playSoundGengShang(playerOpposite->getPlayerInfo()->getGender());
            }else if(GAMEDATA::getInstance()->getOtherPlayJong().poker == playerLeft->getLastPoker()){
                Audio::getInstance()->playSoundXiaGeng(playerOpposite->getPlayerInfo()->getGender());
            }
        }else if(seatId == ClientSeatId::hero){
            playerHero->stopTimeClockAnim();
            playerHero->drawPlayedJong(GAMEDATA::getInstance()->getOtherPlayJong().poker);
            if(GAMEDATA::getInstance()->getOtherPlayJong().poker == playerLeft->getLastPoker()){
                Audio::getInstance()->playSoundGengShang(playerHero->getPlayerInfo()->getGender());
            }else if(GAMEDATA::getInstance()->getOtherPlayJong().poker == playerRight->getLastPoker()){
                Audio::getInstance()->playSoundXiaGeng(playerHero->getPlayerInfo()->getGender());
            }
        }
        PlayMingpaiRecord record;
        record.step = fupanStep;
        PlayerMingpai leftpai;
        leftpai.seatId = ClientSeatId::left;
        leftpai.playerCpgRecords = playerLeft->playerCpgRecords;
        leftpai.playerHandJongs = playerLeft->playerHandJongs;
        leftpai.playerPlayedJongs =playerLeft->playerPlayedJongs;
        record.record.push_back(leftpai);
        PlayerMingpai oppsitepai;
        oppsitepai.seatId = ClientSeatId::opposite;
        oppsitepai.playerCpgRecords = playerOpposite->playerCpgRecords;
        oppsitepai.playerHandJongs = playerOpposite->playerHandJongs;
        oppsitepai.playerPlayedJongs =playerOpposite->playerPlayedJongs;
        record.record.push_back(oppsitepai);
        PlayerMingpai rightpai;
        rightpai.seatId = ClientSeatId::right;
        rightpai.playerCpgRecords = playerRight->playerCpgRecords;
        rightpai.playerHandJongs = playerRight->playerHandJongs;
        rightpai.playerPlayedJongs =playerRight->playerPlayedJongs;
        record.record.push_back(rightpai);
        PlayerMingpai heropai;
        heropai.seatId = ClientSeatId::hero;
        heropai.playerCpgRecords = playerHero->playerCpgRecords;
        heropai.playerHandJongs = playerHero->playerHandJongs;
        heropai.playerPlayedJongs =playerHero->playerPlayedJongs;
        record.record.push_back(heropai);
        myPlayMingpaiRecord.push_back(record);
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(otherListener, 1);
    
    othersChiListener = EventListenerCustom::create(MSG_OTHER_PLAYER_CHI, [=](EventCustom* event){
        int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), GAMEDATA::getInstance()->getPlayerCpgt().seatId);
        setCurrentJongVisible(GAMEDATA::getInstance()->getPlayerCpgt().sId);
        ((Orientation*)getChildByTag(123))->showPlayerTurn(GAMEDATA::getInstance()->getHeroSeatId(), GAMEDATA::getInstance()->getPlayerCpgt().seatId);
        if (seatId == ClientSeatId::left){
            playerLeft->drawPlayerMingpaiChi(GAMEDATA::getInstance()->getPlayerCpgt(), getPlayerBySeatId(GAMEDATA::getInstance()->getPlayerCpgt().sId));
            playerLeft->playerCpgAnim(CpgType::chi, ClientSeatId::left);
            playerLeft->startTimeClockAnim();
        }
        else if (seatId == ClientSeatId::right){
            playerRight->drawPlayerMingpaiChi(GAMEDATA::getInstance()->getPlayerCpgt(), getPlayerBySeatId(GAMEDATA::getInstance()->getPlayerCpgt().sId));
            playerRight->playerCpgAnim(CpgType::chi, ClientSeatId::right);
            playerRight->startTimeClockAnim();
        }
        else if (seatId == ClientSeatId::opposite){
            playerOpposite->drawPlayerMingpaiChi(GAMEDATA::getInstance()->getPlayerCpgt(), getPlayerBySeatId(GAMEDATA::getInstance()->getPlayerCpgt().sId));
            playerOpposite->playerCpgAnim(CpgType::chi, ClientSeatId::opposite);
            playerOpposite->startTimeClockAnim();
        }else if (seatId == ClientSeatId::hero){
            hideTingGangControllPad();
            HeroCpgRespData heroTingData;
            heroTingData.result =1;
            std::vector<string> chipai = StringUtil::split(GAMEDATA::getInstance()->getPlayerCpgt().chi.at(0), ",");
            playerHero->drawHeroChi(heroTingData,chipai, getPlayerBySeatId(GAMEDATA::getInstance()->getPlayerCpgt().sId));
            playerHero->playerCpgAnim(CpgType::peng, ClientSeatId::opposite);
            playerHero->startTimeClockAnim();
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(othersChiListener, 1);
    
    othersPengListener = EventListenerCustom::create(MSG_OTHER_PLAYER_PENG, [=](EventCustom* event){
        int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), GAMEDATA::getInstance()->getPlayerCpgt().seatId);
        setCurrentJongVisible(GAMEDATA::getInstance()->getPlayerCpgt().sId);
        ((Orientation*)getChildByTag(123))->showPlayerTurn(GAMEDATA::getInstance()->getHeroSeatId(), GAMEDATA::getInstance()->getPlayerCpgt().seatId);
        if (seatId == ClientSeatId::left){
            hideTingGangControllPad();
            playerLeft->drawPlayerMingpaiPeng(GAMEDATA::getInstance()->getPlayerCpgt(), getPlayerBySeatId(GAMEDATA::getInstance()->getPlayerCpgt().sId));
            playerLeft->playerCpgAnim(CpgType::peng, ClientSeatId::left);
            playerLeft->startTimeClockAnim();
        }
        else if (seatId == ClientSeatId::right){
            hideTingGangControllPad();
            playerRight->drawPlayerMingpaiPeng(GAMEDATA::getInstance()->getPlayerCpgt(), getPlayerBySeatId(GAMEDATA::getInstance()->getPlayerCpgt().sId));
            playerRight->playerCpgAnim(CpgType::peng, ClientSeatId::right);
            playerRight->startTimeClockAnim();
        }
        else if (seatId == ClientSeatId::opposite){
            hideTingGangControllPad();
            playerOpposite->drawPlayerMingpaiPeng(GAMEDATA::getInstance()->getPlayerCpgt(), getPlayerBySeatId(GAMEDATA::getInstance()->getPlayerCpgt().sId));
            playerOpposite->playerCpgAnim(CpgType::peng, ClientSeatId::opposite);
            playerOpposite->startTimeClockAnim();
        } else if (seatId == ClientSeatId::hero){
            hideTingGangControllPad();
            HeroCpgRespData heroCpgData;
            heroCpgData.result = 1;
            playerHero->drawHeroPeng(heroCpgData,GAMEDATA::getInstance()->getPlayerCpgt(), getPlayerBySeatId(GAMEDATA::getInstance()->getPlayerCpgt().sId));
            playerHero->playerCpgAnim(CpgType::peng, ClientSeatId::opposite);
            playerHero->startTimeClockAnim();
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(othersPengListener, 1);
    
    othersGangListener = EventListenerCustom::create(MSG_OTHER_PLAYER_GANG, [=](EventCustom* event){
        int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), GAMEDATA::getInstance()->getPlayerCpgt().seatId);
        setCurrentJongVisible(GAMEDATA::getInstance()->getPlayerCpgt().sId);
        ((Orientation*)getChildByTag(123))->showPlayerTurn(GAMEDATA::getInstance()->getHeroSeatId(), GAMEDATA::getInstance()->getPlayerCpgt().seatId);
        if (seatId == ClientSeatId::left){
            hideTingGangControllPad();
            playerLeft->drawPlayerMingpaiGang(GAMEDATA::getInstance()->getPlayerCpgt(), getPlayerBySeatId(GAMEDATA::getInstance()->getPlayerCpgt().sId));
            playerLeft->playerCpgAnim(CpgType::gang, ClientSeatId::left);
        }
        else if (seatId == ClientSeatId::right){
            hideTingGangControllPad();
            playerRight->drawPlayerMingpaiGang(GAMEDATA::getInstance()->getPlayerCpgt(), getPlayerBySeatId(GAMEDATA::getInstance()->getPlayerCpgt().sId));
            playerRight->playerCpgAnim(CpgType::gang, ClientSeatId::right);
        }
        else if (seatId == ClientSeatId::opposite){
            hideTingGangControllPad();
            playerOpposite->drawPlayerMingpaiGang(GAMEDATA::getInstance()->getPlayerCpgt(), getPlayerBySeatId(GAMEDATA::getInstance()->getPlayerCpgt().sId));
            playerOpposite->playerCpgAnim(CpgType::gang, ClientSeatId::opposite);
        }else if (seatId == ClientSeatId::hero){
            hideTingGangControllPad();
            HeroCpgRespData heroTingData;
            playerHero->drawHeroPeng(heroTingData,GAMEDATA::getInstance()->getPlayerCpgt(), getPlayerBySeatId(GAMEDATA::getInstance()->getPlayerCpgt().sId));
            playerHero->playerCpgAnim(CpgType::peng, ClientSeatId::opposite);
            playerHero->startTimeClockAnim();
        }
        
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(othersGangListener, 1);
    
    playerTingNotifyListener = EventListenerCustom::create(MSG_PLAYER_TING_NOTIFY, [=](EventCustom* event){
        int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), GAMEDATA::getInstance()->getCurrentTingSeatId());
        playerTingAnim(seatId);
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(playerTingNotifyListener, 1);
    
    tingNotifyListener = EventListenerCustom::create(MSG_HERO_TING_GANG, [=](EventCustom* event){
        if (GAMEDATA::getInstance()->getPlayerCpgt().seatId == GAMEDATA::getInstance()->getHeroSeatId()){
            showTingGangControllPad();
            playerHero->startTimeClockAnim(9, 2);
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
        playerHero->hideCurrentBigJong();
        std::vector<string> chipai = StringUtil::split(selectedChi, ",");
        playerHero->drawHeroChi(GAMEDATA::getInstance()->getHeroCpgResp(), chipai, playerLeft);
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(heroChiRespListener, 1);
    
    heroPengRespListener = EventListenerCustom::create(MSG_HERO_PENG_RESP, [=](EventCustom* event){
        PlayerCpgtData cpg = GAMEDATA::getInstance()->getPlayerCpgt();
        HeroCpgRespData resp = GAMEDATA::getInstance()->getHeroCpgResp();
        int clientSeatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), cpg.sId);
        playerHero->hideCurrentBigJong();
        if(resp.result == 1||resp.result == 2){
            if (clientSeatId == ClientSeatId::right){
                playerHero->drawHeroPeng(resp, cpg, playerRight);
            }
            else if (clientSeatId == ClientSeatId::opposite){
                playerHero->drawHeroPeng(resp, cpg, playerOpposite);
            }
            else{
                playerHero->drawHeroPeng(resp, cpg, playerLeft);
            }
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(heroPengRespListener, 1);
    
    heroGangRespListener = EventListenerCustom::create(MSG_HERO_GANG_RESP, [=](EventCustom* event){
        PlayerCpgtData cpg = GAMEDATA::getInstance()->getPlayerCpgt();
        HeroCpgRespData resp = GAMEDATA::getInstance()->getHeroCpgResp();
        playerHero->hideCurrentBigJong();
        int clientSeatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), cpg.sId);
        if (resp.result == 0){
            playerHero->stopTimeClockAnim();
        }
        else{
            
            if (clientSeatId == ClientSeatId::right){
                playerHero->drawHeroGang(resp, cpg, playerRight);
            }
            else if (clientSeatId == ClientSeatId::opposite){
                playerHero->drawHeroGang(resp, cpg, playerOpposite);
            }
            else{
                playerHero->drawHeroGang(resp, cpg, playerLeft);
            }
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(heroGangRespListener, 1);
    
    playerCpgListener = EventListenerCustom::create(MSG_PLAYER_CPG, [=](EventCustom* event){
        schedule([=](float dt){
            drawCpgControllPad();
            playerHero->startTimeClockAnim(9, 1);
        },0,0,0.5f,"nonohuang");
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

