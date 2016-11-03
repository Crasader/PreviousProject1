#include "game/mahjong/anim/DealJongAnim.h"
#include "game/mahjong/core/MahjongView.h"
#include "game/mahjong/core/widget/Orientation.h"
#include "game/mahjong/lobby/LobbyScene.h"
#include "game/mahjong/result/ResultLayer.h"
#include "game/mahjong/state/GameData.h"
#include "game/utils/SeatIdUtil.h"
#include "game/utils/StringUtil.h"
#include "server/NetworkManage.h"
#include "server/CommandManage.h"
#include "game/mahjong/anim/HupaiAnim.hpp"
#include "game/mahjong/anim/PlayerCpgAnim.hpp"
#include "game/mahjong/result/ResultScene.hpp"
#include "game/mahjong/anim/LiuJuAnim.hpp"
#include "game/mahjong/anim/OutFogAnim.hpp"
#include "game/mahjong/dialog/prompt/HintDialog.hpp"
#include "game/mahjong/friend/dialog/DissovleRoomDialog.hpp"
#include "server/SocketDataManage.h"



bool MahjongView::init(){
    if (!Layer::init())
    {
        return false;
    }
    initData();
    loadView();
    if (GAMEDATA::getInstance()->getIsRecover()){
        recoverGame();
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getRoomListCommand("1"));
        GAMEDATA::getInstance()->setIsRecover(false);
    }
    else{
        if(GAMEDATA::getInstance()->getContinueAgain()){
            startGameAgain();
            GAMEDATA::getInstance()->setContinueAgain(false);
        }else{
            startGameFirst();
        }
        addPlayer2Room();
    }
    return true;
}

void MahjongView::onEnter(){
    Layer::onEnter();
    scheduleUpdate();
    addCoustomListener();
}

void MahjongView::onExit()
{
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(addOtherReadyListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(loginRespListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(addPlayersListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(replaceListener);
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
    Director::getInstance()->getEventDispatcher()->removeEventListener(playerRemoveListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(playerResumeListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(friendOpenRoomListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(playerReplaceLoginListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(inviteReplaceListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(dissovelRoomNotifyListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(dissovelRoomSelectNotifyListener);
}

void MahjongView::initData(){
    playerHero = NULL;
    playerLeft = NULL;
    playerRight = NULL;
    playerOpposite = NULL;
    GAMEDATA::getInstance()->setIsPlaying(false);
    GAMEDATA::getInstance()->setIsLiuJu(false);
    GAMEDATA::getInstance()->setIsGotoLobby(false);
    Audio::getInstance()->setHasTingPlayer(false);
}

void MahjongView::loadView(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Sprite* view_bg = Sprite::create("gameview/game_bg.jpg");
    view_bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    this->addChild(view_bg, -1);
    controllPad = Menu::create();
    controllPad->setAnchorPoint(Point(1, 0));
    controllPad->setVisible(false);
    this->addChild(controllPad, 10);
    guiLayer = GuiLayer::create();
    addChild(guiLayer, 150);
    choiceMenu = Sprite::create();
    choiceMenu->setAnchorPoint(Point(0, 0));
    choiceMenu->setPosition(Point(0, 0));
    this->addChild(choiceMenu, 100);
    trusteeship = Trusteeship::create();
    this->addChild(trusteeship, 160);
    trusteeship->setVisible(false);
}

void MahjongView::startGameFirst(){
    showOriention();
    GAMEDATA::getInstance()->setKaibao("0");
    GAMEDATA::getInstance()->setHuangfan("0");
    guiLayer->updateData();
    Player* info = new Player();
    info->setSeatId(GAMEDATA::getInstance()->getHeroSeatId());
    info->setPoxiaoId(UserData::getInstance()->getPoxiaoId());
    if(GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom){
        info->setIsReady(true);
    }else{
        info->setIsReady(false);
    }
    info->setGold(UserData::getInstance()->getGold());
    info->setDiamond(UserData::getInstance()->getDiamond());
    info->setLockDiamond(UserData::getInstance()->getLockDiamond());
    info->setScore(UserData::getInstance()->getScore());
    info->setGender(UserData::getInstance()->getGender());
    info->setNickname(UserData::getInstance()->getNickName());
    info->setPicture(UserData::getInstance()->getPicture());
    info->setFangka(UserData::getInstance()->getFangkaNum());
    GAMEDATA::getInstance()->addPlayersInfo(info);
}

void MahjongView::startGameAgain(){
    
    vector<Player*> players = GAMEDATA::getInstance()->getPlayersInfo();
    for (int i = 0; i < players.size(); i++){
        if(players.at(i)->getSeatId() ==  GAMEDATA::getInstance()->getHeroSeatId()){
            players.at(i)->setIsReady(true);
        }
    }
    showOriention();
    if(GAMEDATA::getInstance()->getEnterRoomResp().kb == "1"){
        GAMEDATA::getInstance()->setKaibao("1");
    }else{
        GAMEDATA::getInstance()->setKaibao("0");
    }
    GAMEDATA::getInstance()->setHuangfan("0");
    guiLayer->updateData();
    ((Orientation*)getChildByTag(123))->showOrientation(GAMEDATA::getInstance()->getHeroSeatId());
    ((Orientation*)getChildByTag(123))->resetBank();
    GAMEDATA::getInstance()->setIsTingProcess(false);
    GAMEDATA::getInstance()->setIsTingState(false);
    schedule([=](float dt){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getReadyCommmand());
    }, 0, 0, 1.0f,"continueGame");
}

void MahjongView::update(float dt){
    if (GAMEDATA::getInstance()->getNeedAddPlayer()){
        addPlayer2Room();
        GAMEDATA::getInstance()->setNeedAddPlayer(false);
    }
    if(GAMEDATA::getInstance()->getNeedAddPlayer()>0){
        playerHero->drawPlayedJong(GAMEDATA::getInstance()->getOtherPlayJong().poker);
        playerHero->stopTimeClockAnim();
        GAMEDATA::getInstance()->setNeedAddPlayer(-1);
    }
}


void MahjongView::updatePlayerView(int type, Player* playerInfo){
    if (GAMEDATA::getInstance()->getMahjongRoomType()==MahjongRoom::privateRoom){
        guiLayer->hideInvitePlayer(type);
    }
    if (type == ClientSeatId::hero){
        if (playerHero == NULL){
            playerHero = PlayerHero::create();
            playerHero->initPlayer(playerInfo);
            playerHero->drawReady(playerInfo->getIsReady());
            playerHero->setIsReady(playerInfo->getIsReady());
            playerHero->setIsAllowPlay(false);
            addChild(playerHero, 2);
        }
    }
    else if (type == ClientSeatId::left){
        if (playerLeft == NULL){
            playerLeft = PlayerLeft::create();
            playerLeft->initPlayer(playerInfo);
            playerLeft->setIsReady(playerInfo->getIsReady());
            addChild(playerLeft,1);
        }
    }
    else if (type == ClientSeatId::right){
        if (playerRight == NULL){
            playerRight = PlayerRight::create();
            playerRight->initPlayer(playerInfo);
            playerRight->setIsReady(playerInfo->getIsReady());
            addChild(playerRight,1);
        }
    }
    else if (type == ClientSeatId::opposite){
        if (playerOpposite == NULL){
            playerOpposite = PlayerOpposite::create();
            playerOpposite->initPlayer(playerInfo);
            playerOpposite->setIsReady(playerInfo->getIsReady());
            addChild(playerOpposite,1);
        }
    }
}




void MahjongView::addPlayer2Room(){
    vector<Player*> players = GAMEDATA::getInstance()->getPlayersInfo();
    for (int i = 0; i < players.size(); i++){
        updatePlayerView(SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), players.at(i)->getSeatId()), players.at(i));
    }
}






void MahjongView::drawCpgControllPad(){
    controllPad->removeAllChildrenWithCleanup(true);
    auto qi = MenuItemImage::create("gameview/mj_qi.png", "gameview/mj_qi.png", CC_CALLBACK_0(MahjongView::heroDoCpgQi,this));
    qi->setPosition(Point(0, 0));
    controllPad->addChild(qi);
    MenuItemImage* chi = nullptr;
    MenuItemImage* peng = nullptr;
    MenuItemImage* gang = nullptr;
    PlayerCpgtData cpg = GAMEDATA::getInstance()->getPlayerCpgt();
    int buttonCount = 1;
    if (cpg.chi.size() > 0){
        chi = MenuItemImage::create("gameview/mj_chi.png", "gameview/mj_chi.png", CC_CALLBACK_0(MahjongView::showHeroChiUi, this));
        chi->setPosition(Point(-buttonCount * 160, 0));
        controllPad->addChild(chi);
        buttonCount++;
    }
    if (cpg.peng != ""){
        peng = MenuItemImage::create("gameview/mj_peng.png", "gameview/mj_peng.png", CC_CALLBACK_0(MahjongView::heroDoPeng, this));
        peng->setPosition(Point(-buttonCount * 160, 0));
        controllPad->addChild(peng);
        buttonCount++;
    }
    if (cpg.gang != ""){
        gang = MenuItemImage::create("gameview/mj_gang.png", "gameview/mj_gang.png", CC_CALLBACK_0(MahjongView::heroDoGang, this));
        gang->setPosition(Point(-buttonCount * 160, 0));
        controllPad->addChild(gang);
    }
    controllPad->setPosition(Point(1100, 160));
    controllPad->setVisible(true);
}

void MahjongView::showTingGangControllPad(){
    playerHero->stopTimeClockAnim();
    controllPad->removeAllChildrenWithCleanup(true);
    auto qi = MenuItemImage::create("gameview/mj_qi.png", "gameview/mj_qi.png", CC_CALLBACK_0(MahjongView::heroDoTingQi, this));
    qi->setPosition(Point(0, 0));
    controllPad->addChild(qi);
    MenuItemImage* ting = nullptr;
    MenuItemImage* penggang = nullptr;
    int buttonCount = 1;
    PlayerCpgtData tingData = GAMEDATA::getInstance()->getPlayerCpgt();
    if (tingData.ting != ""){
        ting = MenuItemImage::create("gameview/mj_ting.png", "gameview/mj_ting.png", CC_CALLBACK_0(MahjongView::heroDoTing, this));
        ting->setPosition(Point(-buttonCount * 140, 0));
        controllPad->addChild(ting);
        buttonCount++;
    }
    if (tingData.gang != ""){
        penggang = MenuItemImage::create("gameview/mj_gang.png", "gameview/mj_gang.png", CC_CALLBACK_0(MahjongView::heroDoPengGangAndAGang, this));
        penggang->setPosition(Point(-buttonCount * 140, 0));
        controllPad->addChild(penggang);
        buttonCount++;
    }
    controllPad->setPosition(Point(1100, 160));
    controllPad->setVisible(true);
    playerHero->setIsAllowTouch(false);
    playerHero->setIsAllowPlay(true);
    playerHero->startTimeClockAnim(5, 2);
}

void MahjongView::hideTingGangControllPad(){
    controllPad->setVisible(false);
    choiceMenu->removeAllChildren();
    choiceMenu->setVisible(false);
    schedule([=](float dt){
        controllPad->removeAllChildrenWithCleanup(true);
    }, 0, 0, 1.0f,"dalayRemovepad");
}

void MahjongView::showGuiLayer(){
    guiLayer->setVisible(true);
}

void MahjongView::removeHeroPlayedIcon(){
    playerHero->removePlayedIcon();
}


void MahjongView::showHeroChiUi(){
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
                MenuItemImage* imageItem = MenuItemImage::create(imageName, imageName, CC_CALLBACK_1(MahjongView::heroDoChi, this));
                imageItem->setTag(i);
                imageItem->setPosition(1000 + j * 40 - i * 130, 160);
                imageItem->setScale(0.5f);
                choice->addChild(imageItem);
            }
            choice->setPosition(0, 0);
            choiceMenu->addChild(choice);
        }
        playerHero->startTimeClockAnim(5, 1);
    }
    else{
        //choiceMenu = NULL;
        MenuItemImage* imageItem = MenuItemImage::create();
        imageItem->setTag(0);
        heroDoChi(imageItem);
    }
}

void MahjongView::heroDoChi(Ref* psend){
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

void MahjongView::heroDoPeng(){
    controllPad->setVisible(false);
    playerHero->stopTimeClockAnim();
    PlayerCpgtData cpg = GAMEDATA::getInstance()->getPlayerCpgt();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getPengCommand(cpg.peng, atoi(cpg.poker.c_str())));
}

void MahjongView::heroDoGang(){
    controllPad->setVisible(false);
    playerHero->stopTimeClockAnim();
    PlayerCpgtData cpg = GAMEDATA::getInstance()->getPlayerCpgt();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getGangCommand(cpg.gang, atoi(cpg.poker.c_str()), cpg.flag));
}

void MahjongView::heroDoCpgQi(){
    controllPad->setVisible(false);
    playerHero->stopTimeClockAnim();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getGiveUpCpgCommmand());
}

void MahjongView::heroDoTing(){
    playerHero->stopTimeClockAnim();
    controllPad->setVisible(false);
    playerHero->actionTing();
}
void MahjongView::heroDoTingQi(){
    playerHero->stopTimeClockAnim();
    controllPad->setVisible(false);
    playerHero->actionQi();
    playerHero->startTimeClockAnim();
}

void MahjongView::heroDoPengGangAndAGang(){
    playerHero->stopTimeClockAnim();
    controllPad->setVisible(false);
    PlayerCpgtData tingData = GAMEDATA::getInstance()->getPlayerCpgt();
    std::vector<string> gangpai = StringUtil::split(tingData.gang, ",");
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getGangCommand(tingData.gang, atoi(gangpai.at(0).c_str()), tingData.flag));
}

void MahjongView::setCurrentJongVisible(int seatId){
    //TODO
}

void MahjongView::playerTingAnim(int seatId){
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


void MahjongView::clearRoomPlayer(){
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

void MahjongView::recoverGame(){
    LastGameData data = GAMEDATA::getInstance()->getLastGameDataBackup();
    GAMEDATA::getInstance()->setHeroSeatId(data.seatId);
    GAMEDATA::getInstance()->setCurrentBank(data.loard);
    GAMEDATA::getInstance()->setHuangfan(StringUtil::itos(data.hf));
    GAMEDATA::getInstance()->setKaibao(StringUtil::itos(data.kb));
    guiLayer->updateData();
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
        GAMEDATA::getInstance()->addPlayersInfo(info);
        recoverPlayer(player, SeatIdUtil::getClientSeatId(data.seatId, player.seatId), info);
    }
    showGamePaidui(atoi(data.rest.c_str()));
    //重新设置庄的位置
    showOriention();
    ((Orientation*)getChildByTag(123))->showWhoBank(GAMEDATA::getInstance()->getHeroSeatId(),GAMEDATA::getInstance()->getCurrentBank());
    GAMEDATA::getInstance()->setIsPlaying(true);
    int playturn = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), data.turn);
    if(playturn == ClientSeatId::hero){
        playerHero->startTimeClockAnim();
    }else if(playturn == ClientSeatId::left){
        playerLeft->startTimeClockAnim();
    }else if(playturn == ClientSeatId::opposite){
        playerOpposite->startTimeClockAnim();
    }else if(playturn == ClientSeatId::right){
        playerRight->startTimeClockAnim();
    }
}

void MahjongView::recoverPlayer(PlayerGameData data, int type, Player* playerInfo){
    if (type == ClientSeatId::hero){
        if (playerHero == NULL){
            playerHero = PlayerHero::create();
            playerHero->initPlayer(playerInfo);
            playerHero->setIsAllowPlay(false);
            playerHero->setPlayerTingState(data.status == 1?true:false);
            addChild(playerHero, 2);
            playerHero->recoverCpg(data.chiData ,data.pengData , data.gangData,data.angang);
            playerHero->recoverHand(data.hand);
            playerHero->recoverPlayed(data.outhand);
            playerHero->recoverHua(data.hua);
            if(data.tru == 1){
                trusteeship->setVisible(true);
                GAMEDATA::getInstance()->setIsTrusteeship(true);
            }
        }
    }
    else if (type == ClientSeatId::left){
        if (playerLeft == NULL){
            playerLeft = PlayerLeft::create();
            playerLeft->initPlayer(playerInfo);
            playerLeft->setPlayerTingState(data.status == 1?true:false);
            playerLeft->setIsOffLine(data.isOnline == 0?true:false);
            playerLeft->setIsTrustee(data.tru == 1?true:false);
            addChild(playerLeft);
            playerLeft->recoverCpg(data.chiData ,data.pengData , data.gangData,data.angang);
            playerLeft->recoverHand(data.hand);
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
            playerRight->setIsTrustee(data.tru == 1?true:false);
            addChild(playerRight);
            playerRight->recoverCpg(data.chiData ,data.pengData , data.gangData,data.angang);
            playerRight->recoverHand(data.hand);
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
            playerOpposite->setIsTrustee(data.tru == 1?true:false);
            addChild(playerOpposite);
            playerOpposite->recoverCpg(data.chiData ,data.pengData , data.gangData,data.angang);
            playerOpposite->recoverHand(data.hand);
            playerOpposite->recoverPlayed(data.outhand);
            playerOpposite->recoverHua(data.hua);
            
        }
    }
}

void MahjongView::resumePlayerUI(PlayerResumeData data,int type){
    if (type == ClientSeatId::hero){
        playerHero->setIsAllowPlay(false);
        playerHero->setPlayerTingState(data.status == 1?true:false);
        playerHero->recoverCpg(data.chiData ,data.pengData , data.gangData,data.angang);
        playerHero->recoverHand(data.hand);
        playerHero->recoverPlayed(data.outhand);
        playerHero->recoverHua(data.hua);
        if(data.tru == 1){
            trusteeship->setVisible(true);
            GAMEDATA::getInstance()->setIsTrusteeship(true);
        }
    }
    else if (type == ClientSeatId::left){
        playerLeft->setPlayerTingState(data.status == 1?true:false);
        playerLeft->recoverCpg(data.chiData ,data.pengData , data.gangData,data.angang);
        playerLeft->recoverHand(data.hand);
        playerLeft->recoverPlayed(data.outhand);
        playerLeft->recoverHua(data.hua);
    }
    else if (type == ClientSeatId::right){
        playerRight->setPlayerTingState(data.status == 1?true:false);
        playerRight->recoverCpg(data.chiData ,data.pengData , data.gangData,data.angang);
        playerRight->recoverHand(data.hand);
        playerRight->recoverPlayed(data.outhand);
        playerRight->recoverHua(data.hua);
    }
    else if (type == ClientSeatId::opposite){
        playerOpposite->setPlayerTingState(data.status == 1?true:false);
        playerOpposite->recoverCpg(data.chiData ,data.pengData , data.gangData,data.angang);
        playerOpposite->recoverHand(data.hand);
        playerOpposite->recoverPlayed(data.outhand);
        playerOpposite->recoverHua(data.hua);
    }
}

//显示玩家的方向和庄
void MahjongView::showOriention(){
    Orientation* ori = Orientation::create();
    ori->setTag(123);
    ori->showOrientation(GAMEDATA::getInstance()->getHeroSeatId());
    addChild(ori);
}


void MahjongView::showGamePaidui(int num){
    DealJongAnim* del = DealJongAnim::create();
    addChild(del);
    del->setTag(1000);
    del->drawPaidui(num);
}


PlayerBase* MahjongView::getPlayerBySeatId(int sid){
    int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), sid);
    this->setCurrentJongVisible(GAMEDATA::getInstance()->getPlayerCpgt().sId);
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


void MahjongView::addOthersReadyListener(){
    addOtherReadyListener = EventListenerCustom::create(MSG_READY_NOTIFY, [=](EventCustom* event){
        char* buf = static_cast<char*>(event->getUserData());
        currentReadyPlayer = atoi(buf);
        int type = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), currentReadyPlayer);
        if (type == ClientSeatId::left){
            if(NULL != playerLeft){
                playerLeft->setIsReady(true);
            }
        }
        else if (type == ClientSeatId::right){
            if(NULL != playerRight){
                playerRight->setIsReady(true);
            }
        }
        else if (type == ClientSeatId::opposite){
            if(NULL != playerOpposite){
                playerOpposite->setIsReady(true);
            }
        }
        else{
            playerHero->drawReady(false);
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(addOtherReadyListener, 1);
}

void MahjongView::addCoustomReplaceFlower() {
    replaceListener = EventListenerCustom::create(MSG_GAME_REPLACE_FLOWER, [=](EventCustom* event){
        SocketDataManage::getInstance()->pauseMsg();
        if(!GAMEDATA::getInstance()->getIsResume()){
            ReplaceJongVec vec = GAMEDATA::getInstance()->getReplaceJongVec();
            ((DealJongAnim*)getChildByTag(1000))->updateRest(vec.rest);
            for (int i = 0; i < vec.times.size(); i++){
                int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), vec.times.at(i).seatId);
                if (seatId == ClientSeatId::hero){
                    playerHero->setReplacePoker(vec.times.at(i));
                    playerHero->replaceFlower();
                }
                else if (seatId == ClientSeatId::left){
                    playerLeft->setReplacePoker(vec.times.at(i));
                    playerLeft->replaceHandHua(leftplayed);
                }
                else if (seatId == ClientSeatId::right){
                    playerRight->setReplacePoker(vec.times.at(i));
                    playerRight->replaceHandHua(rightplayed);
                }
                else if (seatId == ClientSeatId::opposite){
                    playerOpposite->setReplacePoker(vec.times.at(i));
                    playerOpposite->replaceHandHua(oppositeplayed);
                }
            }
        }
        int bankId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), GAMEDATA::getInstance()->getCurrentBank());
        SocketDataManage::getInstance()->resumeMsg();
        if (bankId == ClientSeatId::hero){
            
            playerHero->startTimeClockAnim();
        }
        else if (bankId == ClientSeatId::left){
            playerLeft->startTimeClockAnim();
        }
        else if (bankId == ClientSeatId::right){
            playerRight->startTimeClockAnim();
        }
        else if (bankId == ClientSeatId::opposite){
            playerOpposite->startTimeClockAnim();
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(replaceListener, 1);
}

void MahjongView::addDealJongListener(){
    dealJongsListener = EventListenerCustom::create(MSG_GAME_START_NOTIFY, [=](EventCustom* event){
        GAMEDATA::getInstance()->setIsPlaying(true);
        SocketDataManage::getInstance()->pauseMsg();
        playerHero->setIsReady(false);
        if(NULL != playerRight)
            playerRight->setIsReady(false);
        if(NULL != playerOpposite)
            playerOpposite->setIsReady(false);
        if(NULL != playerLeft)
            playerLeft->setIsReady(false);
        ((Orientation*)getChildByTag(123))->showWhoBank(GAMEDATA::getInstance()->getHeroSeatId(),GAMEDATA::getInstance()->getCurrentBank());
        guiLayer->hideDissovleBtn();
        vector<string> dd =StringUtil::split(GAMEDATA::getInstance()->getDice(), ",") ;
        DealJongAnim* anim = DealJongAnim::create();
        anim->setTag(1000);
        anim->showDealJong(SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), GAMEDATA::getInstance()->getCurrentBank()) ,atoi(dd.at(0).c_str()),atoi(dd.at(1).c_str()));
        addChild(anim);
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(dealJongsListener, 1);
}

void MahjongView::dealJongFinish(){
    playerHero->drawPlayerHero();
    playerRight->drawHandJong();
    playerOpposite->drawHandJong();
    playerLeft->drawHandJong();
    SocketDataManage::getInstance()->resumeMsg();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getStartHuaCommand());
}

void MahjongView::addPlayerTurnListener(){
    turnListener = EventListenerCustom::create(MSG_PLAYER_TURN_WHO, [=](EventCustom* event){
        int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), GAMEDATA::getInstance()->getPlayerTurn().seatId);
        ((Orientation*)getChildByTag(123))->showPlayerTurn(GAMEDATA::getInstance()->getHeroSeatId(), GAMEDATA::getInstance()->getPlayerTurn().seatId);
        ((DealJongAnim*)getChildByTag(1000))->updateRest(GAMEDATA::getInstance()->getPlayerTurn().rest);
        if (seatId == ClientSeatId::hero){
            playerHero->hideCurrentBigJong();
            playerHero->playerTurnReplace(GAMEDATA::getInstance()->getPlayerTurn());
            if (!GAMEDATA::getInstance()->getIsTrusteeship() || !GAMEDATA::getInstance()->getIsTingState()){
                playerHero->startTimeClockAnim();
            }
        }
        else if (seatId == ClientSeatId::left){
            playerLeft->drawLeftPlayerTurn();
            playerLeft->replaceTurnHua(GAMEDATA::getInstance()->getPlayerTurn());
            playerLeft->startTimeClockAnim();
        }
        else if (seatId == ClientSeatId::right){
            playerRight->drawRightPlayerTurn();
            playerRight->replaceTurnHua(GAMEDATA::getInstance()->getPlayerTurn());
            playerRight->startTimeClockAnim();
        }
        else if (seatId == ClientSeatId::opposite){
            playerOpposite->drawOppositePlayerTurn();
            playerOpposite->replaceTurnHua(GAMEDATA::getInstance()->getPlayerTurn());
            playerOpposite->startTimeClockAnim();
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(turnListener, 1);
}

void MahjongView::addJongPlayedListener(){
    otherListener = EventListenerCustom::create(MSG_OTHER_PALYER_JONG, [=](EventCustom* event){
        int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), GAMEDATA::getInstance()->getOtherPlayJong().seatId);
        if (seatId == ClientSeatId::left){
            playerLeft->drawPlayedJong(GAMEDATA::getInstance()->getOtherPlayJong().poker);
            playerLeft->stopTimeClockAnim();
            if(GAMEDATA::getInstance()->getOtherPlayJong().poker == playerOpposite->getLastPoker()){
                Audio::getInstance()->playSoundGengShang(playerLeft->getPlayerInfo()->getGender());
            }else if(GAMEDATA::getInstance()->getOtherPlayJong().poker == playerHero->getLastPoker()){
                Audio::getInstance()->playSoundXiaGeng(playerLeft->getPlayerInfo()->getGender());
            }
        }
        else if (seatId == ClientSeatId::right){
            playerRight->drawPlayedJong(GAMEDATA::getInstance()->getOtherPlayJong().poker);
            playerRight->stopTimeClockAnim();
            if(GAMEDATA::getInstance()->getOtherPlayJong().poker == playerHero->getLastPoker()){
                Audio::getInstance()->playSoundGengShang(playerRight->getPlayerInfo()->getGender());
            }else if(GAMEDATA::getInstance()->getOtherPlayJong().poker == playerOpposite->getLastPoker()){
                Audio::getInstance()->playSoundXiaGeng(playerRight->getPlayerInfo()->getGender());
            }
        }
        else if (seatId == ClientSeatId::opposite){
            playerOpposite->drawPlayedJong(GAMEDATA::getInstance()->getOtherPlayJong().poker);
            playerOpposite->stopTimeClockAnim();
            if(GAMEDATA::getInstance()->getOtherPlayJong().poker == playerRight->getLastPoker()){
                Audio::getInstance()->playSoundGengShang(playerOpposite->getPlayerInfo()->getGender());
            }else if(GAMEDATA::getInstance()->getOtherPlayJong().poker == playerLeft->getLastPoker()){
                Audio::getInstance()->playSoundXiaGeng(playerOpposite->getPlayerInfo()->getGender());
            }
        }
        else{
            playerHero->drawPlayedJong(GAMEDATA::getInstance()->getOtherPlayJong().poker);
            playerHero->stopTimeClockAnim();
            if(GAMEDATA::getInstance()->getOtherPlayJong().poker == playerLeft->getLastPoker()){
                Audio::getInstance()->playSoundGengShang(playerHero->getPlayerInfo()->getGender());
            }else if(GAMEDATA::getInstance()->getOtherPlayJong().poker == playerRight->getLastPoker()){
                Audio::getInstance()->playSoundXiaGeng(playerHero->getPlayerInfo()->getGender());
            }
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(otherListener, 1);
}



void MahjongView::addHeroCpgListener(){
    
    playerCpgListener = EventListenerCustom::create(MSG_PLAYER_CPG, [=](EventCustom* event){
        drawCpgControllPad();
        playerHero->startTimeClockAnim(5, 1);
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(playerCpgListener, 1);
    
}

void MahjongView::addGameResultListener(){
    GAMEDATA::getInstance()->setIsResume(false);
    gameResultListener = EventListenerCustom::create(MSG_GAME_RESULT, [=](EventCustom* event){
        trusteeship->setVisible(false);
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
                //自摸
                seatId1 =   SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), data.seatId);
                zimoState=true;
                isliuju =false;
            }else if(data.result==2){
                //点炮
                seatId1 = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), data.seatId);
                isliuju =false;
            }else if(data.result==3){
                //普通赢
                isliuju =false;
                if(data.huType=="3"){
                    gangkaiState = true;
                    seatId3 =SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), data.seatId);
                }else if(data.huType=="12"){
                    qianggangState = true;
                    seatId3 =SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), data.seatId);
                }else{
                    seatId2.push_back(SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), data.seatId));
                }
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
        }
        else if(!isliuju){
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
        schedule([=](float dt){
            clearRoomPlayer();
            Director::getInstance()->replaceScene(TransitionFade::create(0.8f, ResultScene::create()));
        },0,0,72.0f/24,"go2Result");
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(gameResultListener, 1);
}

void MahjongView::showHuPaiXing(std::string paixing){
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
    for(int i =0; i<pais.size();i++){
        auto xing = Sprite::create(StringUtils::format("result/paixing_%d.png",atoi(pais.at(i).c_str())));
        addChild(xing,999);
        xing->setOpacity(77);
        xing->setScale(3.0f);
        xing->setPosition(640 - 60*(pais.size()-1)+i*120,posY);
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

void MahjongView::showHandPokerOver(int seatId){
    vector<GameResultData> results = GAMEDATA::getInstance()->getGameResults();
    string leftJongs;
    string rightJongs;
    string oppositeJongs;
    string heroJongs;
    int max =0;
    string maxHuType="";
    for (GameResultData data: results) {
        int seat = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), data.seatId);
        if(seat == ClientSeatId::left){
            leftJongs =data.showPoker;
        }else if(seat == ClientSeatId::opposite){
            oppositeJongs =data.showPoker;
        }else if(seat == ClientSeatId::right){
            rightJongs =data.showPoker;
        }else{
            heroJongs =data.showPoker;
        }
        //获取一炮多响情况下胡的最大的数据
        if(GAMEDATA::getInstance()->getMahjongRoomType()==MahjongRoom::privateRoom){
            if(data.jifendelta >= max){
                maxHuType = data.huType;
                max = data.jifendelta;
            }
        }else{
            if(data.golddelta >= max){
                maxHuType = data.huType;
                max =data.golddelta;
            }
        }
    }
    //翻牌
    if(seatId == ClientSeatId::left){
        playerLeft->hideHandJongs();
        playerLeft->updateHandJongs(leftJongs);
        showHuPaiXing(maxHuType);
        schedule([=](float dt){
            playerRight->hideHandJongs();
            playerRight->updateHandJongs(rightJongs);
            playerOpposite->hideHandJongs();
            playerOpposite->updateHandJongs(oppositeJongs);
            playerHero->hideHandJongs();
            playerHero->updateHandJongs(heroJongs);
        }, 0, 0, 15.0f/24,"fanpai");
    }else if(seatId == ClientSeatId::opposite){
        playerOpposite->hideHandJongs();
        playerOpposite->updateHandJongs(oppositeJongs);
        showHuPaiXing(maxHuType);
        schedule([=](float dt){
            playerRight->hideHandJongs();
            playerRight->updateHandJongs(rightJongs);
            playerLeft->hideHandJongs();
            playerLeft->updateHandJongs(leftJongs);
            playerHero->hideHandJongs();
            playerHero->updateHandJongs(heroJongs);
        }, 0, 0, 15.0f/24,"fanpai");
    }else if(seatId == ClientSeatId::right){
        playerRight->hideHandJongs();
        playerRight->updateHandJongs(rightJongs);
        showHuPaiXing(maxHuType);
        schedule([=](float dt){
            playerOpposite->hideHandJongs();
            playerOpposite->updateHandJongs(oppositeJongs);
            playerLeft->hideHandJongs();
            playerLeft->updateHandJongs(leftJongs);
            playerHero->hideHandJongs();
            playerHero->updateHandJongs(heroJongs);
        }, 0, 0, 15.0f/24,"fanpai");
    }else{
        playerHero->hideHandJongs();
        playerHero->updateHandJongs(heroJongs);
        showHuPaiXing(maxHuType);
        schedule([=](float dt){
            playerOpposite->hideHandJongs();
            playerOpposite->updateHandJongs(oppositeJongs);
            playerRight->hideHandJongs();
            playerRight->updateHandJongs(rightJongs);
            playerHero->hideHandJongs();
            playerHero->updateHandJongs(heroJongs);
        }, 0, 0, 15.0f/24,"fanpai");
    }
    
}

void MahjongView::addOthersChiListener(){
    othersChiListener = EventListenerCustom::create(MSG_OTHER_PLAYER_CHI, [=](EventCustom* event){
        int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), GAMEDATA::getInstance()->getPlayerCpgt().seatId);
        setCurrentJongVisible(GAMEDATA::getInstance()->getPlayerCpgt().sId);
        ((Orientation*)getChildByTag(123))->showPlayerTurn(GAMEDATA::getInstance()->getHeroSeatId(), GAMEDATA::getInstance()->getPlayerCpgt().seatId);
        if (seatId == ClientSeatId::left){
            playerLeft->drawPlayerChi(GAMEDATA::getInstance()->getPlayerCpgt(), getPlayerBySeatId(GAMEDATA::getInstance()->getPlayerCpgt().sId));
            playerLeft->playerCpgAnim(CpgType::chi, ClientSeatId::left);
            playerLeft->startTimeClockAnim();
        }
        else if (seatId == ClientSeatId::right){
            playerRight->drawPlayerChi(GAMEDATA::getInstance()->getPlayerCpgt(), getPlayerBySeatId(GAMEDATA::getInstance()->getPlayerCpgt().sId));
            playerRight->playerCpgAnim(CpgType::chi, ClientSeatId::right);
            playerRight->startTimeClockAnim();
        }
        else if (seatId == ClientSeatId::opposite){
            playerOpposite->drawPlayerChi(GAMEDATA::getInstance()->getPlayerCpgt(), getPlayerBySeatId(GAMEDATA::getInstance()->getPlayerCpgt().sId));
            playerOpposite->playerCpgAnim(CpgType::chi, ClientSeatId::opposite);
            playerOpposite->startTimeClockAnim();
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(othersChiListener, 1);
}

void MahjongView::addOthersPengListener(){
    othersPengListener = EventListenerCustom::create(MSG_OTHER_PLAYER_PENG, [=](EventCustom* event){
        int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), GAMEDATA::getInstance()->getPlayerCpgt().seatId);
        setCurrentJongVisible(GAMEDATA::getInstance()->getPlayerCpgt().sId);
        ((Orientation*)getChildByTag(123))->showPlayerTurn(GAMEDATA::getInstance()->getHeroSeatId(), GAMEDATA::getInstance()->getPlayerCpgt().seatId);
        if (seatId == ClientSeatId::left){
            hideTingGangControllPad();
            playerLeft->drawPlayerPeng(GAMEDATA::getInstance()->getPlayerCpgt(), getPlayerBySeatId(GAMEDATA::getInstance()->getPlayerCpgt().sId));
            playerLeft->playerCpgAnim(CpgType::peng, ClientSeatId::left);
            playerLeft->startTimeClockAnim();
        }
        else if (seatId == ClientSeatId::right){
            hideTingGangControllPad();
            playerRight->drawPlayerPeng(GAMEDATA::getInstance()->getPlayerCpgt(), getPlayerBySeatId(GAMEDATA::getInstance()->getPlayerCpgt().sId));
            playerRight->playerCpgAnim(CpgType::peng, ClientSeatId::right);
            playerRight->startTimeClockAnim();
        }
        else if (seatId == ClientSeatId::opposite){
            hideTingGangControllPad();
            playerOpposite->drawPlayerPeng(GAMEDATA::getInstance()->getPlayerCpgt(), getPlayerBySeatId(GAMEDATA::getInstance()->getPlayerCpgt().sId));
            playerOpposite->playerCpgAnim(CpgType::peng, ClientSeatId::opposite);
            playerOpposite->startTimeClockAnim();
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(othersPengListener, 1);
}

void MahjongView::addOthersGangListener(){
    othersGangListener = EventListenerCustom::create(MSG_OTHER_PLAYER_GANG, [=](EventCustom* event){
        int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), GAMEDATA::getInstance()->getPlayerCpgt().seatId);
        setCurrentJongVisible(GAMEDATA::getInstance()->getPlayerCpgt().sId);
        ((Orientation*)getChildByTag(123))->showPlayerTurn(GAMEDATA::getInstance()->getHeroSeatId(), GAMEDATA::getInstance()->getPlayerCpgt().seatId);
        if (seatId == ClientSeatId::left){
            hideTingGangControllPad();
            playerLeft->drawPlayerGang(GAMEDATA::getInstance()->getPlayerCpgt(), getPlayerBySeatId(GAMEDATA::getInstance()->getPlayerCpgt().sId));
            playerLeft->playerCpgAnim(CpgType::gang, ClientSeatId::left);
        }
        else if (seatId == ClientSeatId::right){
            hideTingGangControllPad();
            playerRight->drawPlayerGang(GAMEDATA::getInstance()->getPlayerCpgt(), getPlayerBySeatId(GAMEDATA::getInstance()->getPlayerCpgt().sId));
            playerRight->playerCpgAnim(CpgType::gang, ClientSeatId::right);
        }
        else if (seatId == ClientSeatId::opposite){
            hideTingGangControllPad();
            playerOpposite->drawPlayerGang(GAMEDATA::getInstance()->getPlayerCpgt(), getPlayerBySeatId(GAMEDATA::getInstance()->getPlayerCpgt().sId));
            playerOpposite->playerCpgAnim(CpgType::gang, ClientSeatId::opposite);
        }
        
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(othersGangListener, 1);
}

void MahjongView::addPlayerTingNotifyListener(){
    playerTingNotifyListener = EventListenerCustom::create(MSG_PLAYER_TING_NOTIFY, [=](EventCustom* event){
        int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), GAMEDATA::getInstance()->getCurrentTingSeatId());
        playerTingAnim(seatId);
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(playerTingNotifyListener, 1);
}

void MahjongView::addHeroTingNotifyListener(){
    tingNotifyListener = EventListenerCustom::create(MSG_HERO_TING_GANG, [=](EventCustom* event){
        if (GAMEDATA::getInstance()->getPlayerCpgt().seatId == GAMEDATA::getInstance()->getHeroSeatId()){
            this->showTingGangControllPad();
            playerHero->startTimeClockAnim(5, 2);
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(tingNotifyListener, 1);
}
void MahjongView::addHeroTingRespListener(){
    tingRespListener = EventListenerCustom::create(MSG_PLAYER_TING_RESP, [=](EventCustom* event){
        char* buf = static_cast<char*>(event->getUserData());
        if (atoi(buf) == 1){
            GAMEDATA::getInstance()->setIsTingState(true);
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(tingRespListener, 1);
}

void MahjongView::addTrusteeShipRespListener(){
    trusteeshipRespListener = EventListenerCustom::create(MSG_TRUSTEESHIP_RESP, [=](EventCustom* event){
        trusteeship->setVisible(true);
        GAMEDATA::getInstance()->setIsTrusteeship(true);
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(trusteeshipRespListener, 1);
}

void MahjongView::addTrusteeShipNotifyListener(){
    trusteeshipNotifyListener = EventListenerCustom::create(MSG_TRUSTEESHIP_NOTIFY, [=](EventCustom* event){
        std::string pid = static_cast<char*>(event->getUserData());
        for(auto var: GAMEDATA::getInstance()->getPlayersInfo()){
            if( UserData::getInstance()->getPoxiaoId()== pid){
                trusteeship->setVisible(true);
                GAMEDATA::getInstance()->setIsTrusteeship(true);
            }else if(var->getPoxiaoId() == pid){
                int seatID = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), var->getSeatId());
                if(seatID == ClientSeatId::left){
                    playerLeft->setIsTrustee(true);
                }else if(seatID == ClientSeatId::opposite){
                    playerOpposite->setIsTrustee(true);
                }else if(seatID == ClientSeatId::right){
                    playerRight->setIsTrustee(true);
                }
            }
        }
        
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(trusteeshipNotifyListener, 1);
}

void MahjongView::addTrusteeShipCancelListener(){
    trusteeshipCancelListener = EventListenerCustom::create(MSG_CANCEL_TRUSTEESHIP_RESP, [=](EventCustom* event){
        std::string pid = static_cast<char*>(event->getUserData());
        for(auto var: GAMEDATA::getInstance()->getPlayersInfo()){
            if( UserData::getInstance()->getPoxiaoId()== pid){
                trusteeship->setVisible(false);
                GAMEDATA::getInstance()->setIsTrusteeship(false);
                if(GAMEDATA::getInstance()->getPlayerTurn().seatId == GAMEDATA::getInstance()->getHeroSeatId()){
                    playerHero->setIsAllowPlay(true);
                }
            }else if(var->getPoxiaoId() == pid){
                int seatID = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), var->getSeatId());
                if(seatID == ClientSeatId::left){
                    playerLeft->setIsTrustee(false);
                }else if(seatID == ClientSeatId::opposite){
                    playerOpposite->setIsTrustee(false);
                }else if(seatID == ClientSeatId::right){
                    playerRight->setIsTrustee(false);
                }
            }
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(trusteeshipCancelListener, 1);
}


void MahjongView::addHeroChiRespListener(){
    heroChiRespListener = EventListenerCustom::create(MSG_HERO_CHI_RESP, [=](EventCustom* event){
        playerHero->hideCurrentBigJong();
        std::vector<string> chipai = StringUtil::split(selectedChi, ",");
        playerHero->drawHeroChi(GAMEDATA::getInstance()->getHeroCpgResp(), chipai, playerLeft);
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(heroChiRespListener, 1);
    
}

void MahjongView::addHeroPengRespListener(){
    heroPengRespListener = EventListenerCustom::create(MSG_HERO_PENG_RESP, [=](EventCustom* event){
        PlayerCpgtData cpg = GAMEDATA::getInstance()->getPlayerCpgt();
        HeroCpgRespData resp = GAMEDATA::getInstance()->getHeroCpgResp();
        int clientSeatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), cpg.sId);
        playerHero->hideCurrentBigJong();
        if (clientSeatId == ClientSeatId::right){
            playerHero->drawHeroPeng(resp, cpg, playerRight);
        }
        else if (clientSeatId == ClientSeatId::opposite){
            playerHero->drawHeroPeng(resp, cpg, playerOpposite);
        }
        else{
            playerHero->drawHeroPeng(resp, cpg, playerLeft);
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(heroPengRespListener, 1);
    
}

void MahjongView::addHeroGangRespListener(){
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
    
}

void MahjongView::addFriendInviteMeListener(){
    friendOpenRoomListener=Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_FRIEND_OPEN_ROOM_NOTIFY, [=](EventCustom* event){
        FriendOpenRoomNotifyData data = GAMEDATA::getInstance()->getFriendOpenRoomNotify();
        HintDialog* invite = HintDialog::create("好友"+data.nickname+"邀请你一起打牌",[=](Ref* ref){
            FriendOpenRoomNotifyData data = GAMEDATA::getInstance()->getFriendOpenRoomNotify();
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getEnterFriendRoomCommand(data.pid));
            auto item = (MenuItemImage*)ref;
            item->getParent()->getParent()->removeFromParent();
        });
        addChild(invite,4);
    });
}


void MahjongView::addPlayerRemoveListener(){
    playerRemoveListener = EventListenerCustom::create(MSG_PLAYER_REMOVE, [=](EventCustom* event){
        if(!GAMEDATA::getInstance()->getIsPlaying()){
            if(playerLeft !=NULL&&playerLeft->getPlayerInfo()->getPoxiaoId()==GAMEDATA::getInstance()->getRemovePlayer().pid){
                playerLeft->removeFromParent();
                playerLeft =NULL;
                OutFogAnim* out1 = OutFogAnim::create(Point(70, 455));
                addChild(out1);
            }else if(playerRight !=NULL&&playerRight->getPlayerInfo()->getPoxiaoId()==GAMEDATA::getInstance()->getRemovePlayer().pid){
                playerRight->removeFromParent();
                playerRight =NULL;
                OutFogAnim* out2 = OutFogAnim::create(Point(1213, 455));
                addChild(out2);
            }else if(playerOpposite !=NULL&&playerOpposite->getPlayerInfo()->getPoxiaoId()==GAMEDATA::getInstance()->getRemovePlayer().pid){
                playerOpposite->removeFromParent();
                playerOpposite =NULL;
                OutFogAnim* out3 = OutFogAnim::create(Point(945, 642));
                addChild(out3);
            }else if(GAMEDATA::getInstance()->getRemovePlayer().pid == UserData::getInstance()->getPoxiaoId()){
                Director::getInstance()->replaceScene(LobbyScene::create());
            }
            if(GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom){
                guiLayer->showInvitePlayer(SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), GAMEDATA::getInstance()->getRemovePlayer().setaId));
            }
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(playerRemoveListener, 1);
    
}

void MahjongView::addPlayerOffLineListener(){
    playerOffLineListener = EventListenerCustom::create(MSG_PLAYER_OFF_LINE_NOTIFY, [=](EventCustom* event){
        string buf = static_cast<char*>(event->getUserData());
        vector<Player*> players = GAMEDATA::getInstance()->getPlayersInfo();
        for (int i = 0; i < players.size(); i++){
            if(players.at(i)->getPoxiaoId() ==  buf){
                int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(),players.at(i)->getSeatId());
                if(seatId == ClientSeatId::left){
                    playerLeft->setPlayerTingState(true);
                }else if(seatId == ClientSeatId::opposite){
                    playerOpposite->setPlayerTingState(true);
                }else if(seatId == ClientSeatId::right){
                    playerRight->setPlayerTingState(true);
                }
            }
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(playerOffLineListener, 1);
}


void MahjongView::addPlayerResumeListener(){
    playerResumeListener = EventListenerCustom::create(MSG_PLAYER_RESUME_GAME, [=](EventCustom* event){
        string buf = static_cast<char*>(event->getUserData());
        GameResumeData  data =  GAMEDATA::getInstance()->getGameResumeData();
        GAMEDATA::getInstance()->setIsResume(true);
        //重新绘制手牌和花
        for (int i = 0; i < data.players.size(); i++)
        {
            PlayerResumeData player = data.players.at(i);
            resumePlayerUI(player, SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), player.seatId));
        }
        //设置牌数
        if(NULL != getChildByTag(1000)){
            getChildByTag(1000)->removeFromParent();
        }
        showGamePaidui(atoi(data.rest.c_str()));
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(playerResumeListener, 1);
}


void MahjongView::addCoustomListener(){
    this->addOthersReadyListener();
    this->addDealJongListener();
    this->addCoustomReplaceFlower();
    this->addPlayerTurnListener();
    this->addJongPlayedListener();
    this->addHeroCpgListener();
    this->addGameResultListener();
    this->addOthersChiListener();
    this->addOthersPengListener();
    this->addOthersGangListener();
    this->addPlayerTingNotifyListener();
    this->addHeroTingNotifyListener();
    this->addHeroTingRespListener();
    this->addTrusteeShipRespListener();
    this->addTrusteeShipNotifyListener();
    this->addTrusteeShipCancelListener();
    this->addHeroChiRespListener();
    this->addHeroPengRespListener();
    this->addHeroGangRespListener();
    this->addFriendInviteMeListener();
    this->addPlayerRemoveListener();
    this->addPlayerResumeListener();
    //登录地址变更
    playerReplaceLoginListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_PLAYER_REPLACE_LOGIN, [=](EventCustom* event){
        HintDialog* hin = HintDialog::create("你的账号在其他客户端登录",[=](Ref* ref){
            exit(0);
        });
        addChild(hin,5);
    });
    
    inviteReplaceListener =  Director::getInstance()->getEventDispatcher()->addCustomEventListener(FRIEND_IS_PLAYING_GAME, [=](EventCustom* event){
        InviteRespData inv = GAMEDATA::getInstance()->getInviteRespData();
        if(inv.result == "1"){
            HintDialog* hin = HintDialog::create(StringUtils::format("你的好友%s不在线",inv.nickname.c_str()),NULL);
            addChild(hin,5);
        }else if(inv.result == "2"){
            HintDialog* hin = HintDialog::create(StringUtils::format("你的好友%s正在游戏",inv.nickname.c_str()),NULL);
            addChild(hin,5);
        }
        
    });
    
    dissovelRoomNotifyListener  = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_DISSOVLE_ROOM_NOTIFY, [=](EventCustom* event){
        DissovleRoomDialog* dis = DissovleRoomDialog::create();
        addChild(dis,1000);
    });
    
    dissovelRoomSelectNotifyListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_DISSOVLE_ROOM_SELECTED_NOTIFY, [=](EventCustom* event){
        DissolveData data = GAMEDATA::getInstance()->getDissolveData();
        std::string  name ="";
        for(auto var :GAMEDATA::getInstance()->getPlayersInfo()){
            if(data.pid == var->getPoxiaoId()){
                name =var->getNickname();
            }
        }
        if(data.agree == "0"){
            HintDialog* dia = HintDialog::create(StringUtils::format("%s不同意解散房间",name.c_str()), NULL);
            addChild(dia,5);
        }else{
            HintDialog* dia = HintDialog::create(StringUtils::format("%s同意解散房间",name.c_str()), NULL);
            addChild(dia,5);
        }
    });

}

