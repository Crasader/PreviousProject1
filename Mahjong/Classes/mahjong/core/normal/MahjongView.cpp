#include "mahjong/anim/DealJongAnim.h"
#include "mahjong/core/normal/MahjongView.h"
#include "mahjong/core/widget/Orientation.h"
#include "mahjong/core/widget/CardStack.hpp"
#include "mahjong/lobby/LobbyScene.h"
#include "mahjong/state/GameData.h"
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
#include "mahjong/chat/GameRecordAudioManage.h"
#include "mahjong/core/widget/SoundRecordBtn.hpp"


bool MahjongView::init(){
    if (!Layer::init())
    {
        return false;
    }
    initData();
    loadView();
    if (GAMEDATA::getInstance()->getIsRecover()){
        recoverGame();
    }else{
        if(GAMEDATA::getInstance()->getContinueAgain()){
            startGameAgain();
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


void MahjongView::initData(){
    playerHero = NULL;
    playerLeft = NULL;
    playerRight = NULL;
    playerOpposite = NULL;
    showRepeatDialog = false;
    GAMEDATA::getInstance()->setIsPlaying(false);
    GAMEDATA::getInstance()->setIsLiuJu(false);
    GAMEDATA::getInstance()->setIsGotoLobby(false);
    Audio::getInstance()->setHasTingPlayer(false);
    
}

void MahjongView::loadView(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Sprite* view_bg = Sprite::create("gameview/game_bg.jpg");
    view_bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    addChild(view_bg, -1);
    controllPad = Menu::create();
    controllPad->setAnchorPoint(Point(1, 0));
    controllPad->setPosition(Point(1100, 190));
    controllPad->setVisible(false);
    addChild(controllPad, 10);
    guiLayer = GuiLayer::create();
    addChild(guiLayer, 1);
    choiceMenu = Sprite::create();
    choiceMenu->setAnchorPoint(Point(0, 0));
    choiceMenu->setPosition(Point(0, 0));
    addChild(choiceMenu, 100);
    //跑马灯
    ScrollTextEx* scroll = ScrollTextEx::create();
    scroll->setAutoScroll(true);
    scroll->setTag(9980);
    scroll->setPosition(600,600);
    addChild(scroll,2);
    //Toast 消息
    tao = InfoToast::create();
    addChild(tao,50);
    showOriention();
    CardStack* stack = CardStack::create();
    stack->setTag(1129);
    stack->setVisible(false);
    addChild(stack);
    //时间,电量
    BatteryInfo* battery = BatteryInfo::create();
    battery->setPosition(0,0);
    addChild(battery,100);
    //语音聊天
//    SoundRecordBtn* soun = SoundRecordBtn::create();
//    addChild(soun,5);
    
    if(GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom){
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
    }
}

void MahjongView::startGameFirst(){
    if(getChildByTag(2000)!=NULL){
        getChildByTag(2000)->removeFromParent();
    }
    if(GAMEDATA::getInstance()->getFriendOpenRoomResp().kb == "1"){
        GAMEDATA::getInstance()->setKaibao("1");
    }else{
        GAMEDATA::getInstance()->setKaibao("0");
    }
    if(GAMEDATA::getInstance()->getFriendOpenRoomResp().huangfan == "1"){
        GAMEDATA::getInstance()->setHuangfan("1");
    }else{
        GAMEDATA::getInstance()->setHuangfan("0");
    }
}

void MahjongView::startGameAgain(){
    if(getChildByTag(2000)!=NULL){
        getChildByTag(2000)->removeFromParent();
    }
    vector<Player*> players = GAMEDATA::getInstance()->getPlayersInfo();
    for (int i = 0; i < players.size(); i++){
        for(auto var:GAMEDATA::getInstance()->getEnterRoomResp().playerReadys){
            if(var.poxiaoId == players.at(i)->getPoxiaoId()){
                players.at(i)->setIsReady(var.ifready ==1?true:false);
            }
        }
        if(players.at(i)->getSeatId() ==  GAMEDATA::getInstance()->getHeroSeatId()){
            players.at(i)->setIsReady(true);
        }
    }
    if(GAMEDATA::getInstance()->getEnterRoomResp().kb == "1"){
        GAMEDATA::getInstance()->setKaibao("1");
    }else{
        GAMEDATA::getInstance()->setKaibao("0");
    }
    if(GAMEDATA::getInstance()->getEnterRoomResp().huangfan == "1"){
        GAMEDATA::getInstance()->setHuangfan("1");
    }else{
        GAMEDATA::getInstance()->setHuangfan("0");
    }
    ((Orientation*)getChildByTag(123))->showOrientation(GAMEDATA::getInstance()->getHeroSeatId());
    ((Orientation*)getChildByTag(123))->resetBank();
    GAMEDATA::getInstance()->setIsTingProcess(false);
    GAMEDATA::getInstance()->setIsTingState(false);
}

void MahjongView::update(float dt){

    
    if(GAMEDATA::getInstance()->getShowProtected()){
        if(NULL == getChildByTag(2000)){
            LostNetwork* net = LostNetwork::create();
            net->setTag(2000);
            addChild(net,200);
        }
        GAMEDATA::getInstance()->setShowProtected(false);
    }
    if(GAMEDATA::getInstance()->getMahjongWaitNetwork()){
        if(NULL == getChildByTag(2000)){
            LostNetwork* net = LostNetwork::create();
            net->setTag(2000);
            addChild(net,200);
        }
        GAMEDATA::getInstance()->setMahjongWaitNetwork(false);
    }
    
    if (GAMEDATA::getInstance()->getNeedAddPlayer()){
        addPlayer2Room();
        GAMEDATA::getInstance()->setNeedAddPlayer(false);
    }
    if(GAMEDATA::getInstance()->getIsGotoLobby()){
        GAMEDATA::getInstance()->setIsGotoLobby(false);
        if(GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom){
            HintDialog* dialog = HintDialog::create("房间已经解散或游戏已经结束!", [=](Ref* ref){
                GAMEDATA::getInstance()->clearPlayersInfo();
                GAMEDATA::getInstance()->setIsPlaying(false);
                Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
            },[=](Ref* ref){
                GAMEDATA::getInstance()->clearPlayersInfo();
                GAMEDATA::getInstance()->setIsPlaying(false);
                Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
            });
            addChild(dialog,5);
        }
    }
    if(!GAMEDATA::getInstance()->getIsSelected()&& !GAMEDATA::getInstance()->getShowDissolveDialog()){
        DissovleRoomDialog* dis = DissovleRoomDialog::create();
        std::string name = GAMEDATA::getInstance()->getDissolveName();
        dis->setNickName(name);
        addChild(dis,1000);
        GAMEDATA::getInstance()->setShowDissolveDialog(true);
    }
    
    if(!GAMEDATA::getInstance()->getIsPlaying()){
        vector<Player*> players = GAMEDATA::getInstance()->getPlayersInfo();
        for (int i = 0; i < players.size(); i++){
            int seat_id = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(),players.at(i)->getSeatId() );
            if(seat_id == ClientSeatId::left){
                if(NULL != playerLeft){
                    playerLeft->setIsReady(players.at(i)->getIsReady());
                }
            }else if(seat_id == ClientSeatId::right){
                if(NULL != playerRight){
                    playerRight->setIsReady(players.at(i)->getIsReady());
                }
            }else if(seat_id == ClientSeatId::opposite){
                if(NULL != playerOpposite){
                    playerOpposite->setIsReady(players.at(i)->getIsReady());
                }
            }
        }
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
            //            ChatAndroidMethod::getInstance()->addMember(UserData::getInstance()->getPoxiaoId(), playerInfo->getPoxiaoId());
        }
    }
    else if (type == ClientSeatId::right){
        if (playerRight == NULL){
            playerRight = PlayerRight::create();
            playerRight->initPlayer(playerInfo);
            playerRight->setIsReady(playerInfo->getIsReady());
            addChild(playerRight,1);
            //            ChatAndroidMethod::getInstance()->addMember(UserData::getInstance()->getPoxiaoId(), playerInfo->getPoxiaoId());
        }
    }
    else if (type == ClientSeatId::opposite){
        if (playerOpposite == NULL){
            playerOpposite = PlayerOpposite::create();
            playerOpposite->initPlayer(playerInfo);
            playerOpposite->setIsReady(playerInfo->getIsReady());
            addChild(playerOpposite,1);
            //            ChatAndroidMethod::getInstance()->addMember(UserData::getInstance()->getPoxiaoId(), playerInfo->getPoxiaoId());
        }
    }
}




void MahjongView::addPlayer2Room(){
    vector<Player*> players = GAMEDATA::getInstance()->getPlayersInfo();
    //    checkPlayerIpRepetition();
    for (int i = 0; i < players.size(); i++){
        updatePlayerView(SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), players.at(i)->getSeatId()), players.at(i));
    }
}

void MahjongView::checkPlayerIpRepetition(){
    vector<Player*> players = GAMEDATA::getInstance()->getPlayersInfo();
    for(int i=0;i<players.size();i++){
        for(int j=i+1;j<players.size();j++){
            if(players.at(i)->getIP()==players.at(j)->getIP()){
                //发现有相同的IP,发出通知
                if(!showRepeatDialog){
                    HintDialog* hint3 = HintDialog::create(StringUtils::format("%s和%sIP相同",players.at(i)->getNickname().c_str(),players.at(j)->getNickname().c_str()),nullptr);
                    addChild(hint3,100);
                    showRepeatDialog = true;
                }
            }
        }
    }
}


int  MahjongView::getNumbersByPoker(string pokers){
    std::vector<std::string> myPokers = StringUtil::split(pokers, ",");
    int sum = myPokers.size()*4;
    Vector<Jong*> allKnowPokers;//玩家已知的牌
    for (auto  hero: playerHero->playerHandJongs) {
        allKnowPokers.pushBack(hero);
    }
    for (auto  left: playerLeft->playerPlayedJongs) {
        allKnowPokers.pushBack(left);
    }
    for (auto  opposite: playerOpposite->playerPlayedJongs) {
        allKnowPokers.pushBack(opposite);
    }
    for (auto  right: playerRight->playerPlayedJongs) {
        allKnowPokers.pushBack(right);
    }
    for (auto  leftCpg: playerLeft->playerCpgRecords) {
        for(auto poke1:leftCpg.pokersRecord){
            allKnowPokers.pushBack(poke1);
        }
    }
    for (auto  oppsiteCpg: playerOpposite->playerCpgRecords) {
        for(auto poke2:oppsiteCpg.pokersRecord){
            allKnowPokers.pushBack(poke2);
        }
    }
    for (auto rightCpg: playerRight->playerCpgRecords) {
        for(auto poke3:rightCpg.pokersRecord){
            allKnowPokers.pushBack(poke3);
        }
    }
    for (auto  heroCpg: playerHero->playerCpgRecords) {
        for(auto poke4:heroCpg.pokersRecord){
            allKnowPokers.pushBack(poke4);
        }
    }
    for (int i =0 ; i< myPokers.size(); i++) {
        for (auto var: allKnowPokers) {
            if(atoi(myPokers.at(i).c_str()) == var->getJongType()){
                sum--;
            }
        }
    }
    return sum;
}


void MahjongView::drawCpgControllPad(PlayerCpgtData newData){
    shmjHeroCpgtData.playCpgt = newData;
    controllPad->removeAllChildrenWithCleanup(true);
    auto qi = MenuItemImage::create("gameview/mj_qi.png", "gameview/mj_qi.png", CC_CALLBACK_0(MahjongView::heroDoCpgQi,this));
    qi->setPosition(Point(0, 0));
    controllPad->addChild(qi);
    MenuItemImage* chi = nullptr;
    MenuItemImage* peng = nullptr;
    MenuItemImage* gang = nullptr;
    int buttonCount = 1;
    if (newData.chi[0] != ""){
        chi = MenuItemImage::create("gameview/mj_chi.png", "gameview/mj_chi.png", CC_CALLBACK_1(MahjongView::showHeroChiUi, this));
        chi->setPosition(Point(-buttonCount * 160, 0));
        controllPad->addChild(chi);
        buttonCount++;
        
    }
    if (newData.peng != ""){
        peng = MenuItemImage::create("gameview/mj_peng.png", "gameview/mj_peng.png", CC_CALLBACK_1(MahjongView::heroDoPeng, this));
        peng->setPosition(Point(-buttonCount * 160, 0));
        controllPad->addChild(peng);
        buttonCount++;
    }
    if (newData.playerGang.size()>0){
        gang = MenuItemImage::create("gameview/mj_gang.png", "gameview/mj_gang.png", CC_CALLBACK_1(MahjongView::showHeroGangUi, this));
        gang->setPosition(Point(-buttonCount * 160, 0));
        controllPad->addChild(gang);
    }
    controllPad->setVisible(true);
}

void MahjongView::showTingGangControllPad(PlayerCpgtData tingData){
    shmjHeroCpgtData.playCpgt = tingData;
    playerHero->stopTimeClockAnim();
    controllPad->removeAllChildrenWithCleanup(true);
    auto qi = MenuItemImage::create("gameview/mj_qi.png", "gameview/mj_qi.png", CC_CALLBACK_0(MahjongView::heroDoTingQi, this));
    qi->setPosition(Point(0, 0));
    controllPad->addChild(qi);
    MenuItemImage* ting = nullptr;
    MenuItemImage* penggang = nullptr;
    int buttonCount = 1;
    if (tingData.ting != ""){
        ting = MenuItemImage::create("gameview/mj_ting.png", "gameview/mj_ting.png", CC_CALLBACK_0(MahjongView::heroDoTing, this));
        ting->setPosition(Point(-buttonCount * 140, 0));
        controllPad->addChild(ting);
        buttonCount++;
    }
    if (tingData.playerGang.size()>0){
        penggang = MenuItemImage::create("gameview/mj_gang.png", "gameview/mj_gang.png", CC_CALLBACK_1(MahjongView::showHeroGangUi, this));
        penggang->setPosition(Point(-buttonCount * 140, 0));
        controllPad->addChild(penggang);
        buttonCount++;
    }
    controllPad->setVisible(true);
    playerHero->setIsAllowTouch(false);
    playerHero->setIsAllowPlay(true);
    playerHero->startTimeClockAnim(9, 2);
}

void MahjongView::hideTingGangControllPad(){
    controllPad->setVisible(false);
    choiceMenu->removeAllChildren();
    choiceMenu->setVisible(false);
    playerHero->stopTimeClockAnim();//玩家停止倒计时
    schedule([=](float dt){
        controllPad->removeAllChildrenWithCleanup(true);
    }, 0, 0, 0.2f,"dalayRemovepad");
}

void MahjongView::showGuiLayer(){
    guiLayer->setVisible(true);
}

void MahjongView::removeHeroPlayedIcon(){
    if(NULL != playerHero)
        playerHero->removePlayedIcon();
}


void MahjongView::showHeroChiUi(Ref* ref){
    controllPad->setVisible(false);
    //吃牌排序
    if ( shmjHeroCpgtData.playCpgt.chi[0] != "" &&  shmjHeroCpgtData.playCpgt.chi[1] != ""){
        //对吃牌的大小进行排序
        for (int j = 2; j > 0; j--) {
            for (int k = 0; k < j; k++) {
                if ( shmjHeroCpgtData.playCpgt.chi[k] <  shmjHeroCpgtData.playCpgt.chi[k + 1]) {
                    auto temp =  shmjHeroCpgtData.playCpgt.chi[k];
                    shmjHeroCpgtData.playCpgt.chi[k] = shmjHeroCpgtData.playCpgt.chi[k + 1];
                    shmjHeroCpgtData.playCpgt.chi[k + 1] = temp;
                }
            }
        }
        for (int i = 0; i < 3; i++){
            if( shmjHeroCpgtData.playCpgt.chi[i] == ""){
                continue;
            }
            std::vector<string> pai = StringUtil::split( shmjHeroCpgtData.playCpgt.chi[i], ",");
            pai.push_back( shmjHeroCpgtData.playCpgt.poker);
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
        playerHero->startTimeClockAnim(9, 1);
    }
    else{
        MenuItemImage* imageItem = MenuItemImage::create();
        imageItem->setTag(0);
        heroDoChi(imageItem);
    }
}

void MahjongView::showHeroGangUi(Ref* ref){
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
        for (int j = allGangs.size()-1; j > 0; j--) {
            for (int k = 0; k < j; k++) {
                if ( allGangs[k] <  allGangs[k + 1]) {
                    auto temp =  allGangs[k];
                    allGangs[k] = allGangs[k + 1];
                    allGangs[k + 1] = temp;
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
                MenuItemImage* imageItem = MenuItemImage::create(imageName, imageName, CC_CALLBACK_1(MahjongView::heroDoGang, this));
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

void MahjongView::heroDoChi(Ref* psend){
    if (NULL != choiceMenu){
        choiceMenu->setVisible(false);
        choiceMenu->removeAllChildren();
    }
    MenuItemImage* item = (MenuItemImage*)psend;
    selectedChi =  shmjHeroCpgtData.playCpgt.chi[item->getTag()];
    playerHero->stopTimeClockAnim();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getChiCommand(selectedChi, atoi( shmjHeroCpgtData.playCpgt.poker.c_str())));
}

void MahjongView::heroDoPeng(Ref* psend){
    controllPad->setVisible(false);
    playerHero->stopTimeClockAnim();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getPengCommand(shmjHeroCpgtData.playCpgt.peng, atoi(shmjHeroCpgtData.playCpgt.poker.c_str())));
}

void MahjongView::heroDoGang(Ref* psend){
    if (NULL != choiceMenu){
        choiceMenu->setVisible(false);
        choiceMenu->removeAllChildren();
    }
    MenuItemImage* item = (MenuItemImage*)psend;
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

void MahjongView::heroDoCpgQi(){
    controllPad->setVisible(false);
    playerHero->stopTimeClockAnim();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getGiveUpCpgCommmand());
}

void MahjongView::heroDoTing(){
    playerHero->stopTimeClockAnim();
    controllPad->setVisible(false);
    playerHero->actionTing(shmjHeroCpgtData);
    controllPad->removeAllChildrenWithCleanup(true);
    auto qi = MenuItemImage::create("gameview/mj_qi.png", "gameview/mj_qi.png", CC_CALLBACK_0(MahjongView::heroDoTingQi, this));
    qi->setPosition(Point(0, 50));
    qi->setScale(0.8f);
    controllPad->addChild(qi);
    controllPad->setVisible(true);
}
void MahjongView::heroDoTingQi(){
    playerHero->stopTimeClockAnim();
    controllPad->setVisible(false);
    playerHero->actionQi();
    playerHero->startTimeClockAnim();
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
            if(playerLeft->playerPlayedJongs.size()>0)
                playerLeft->playerPlayedJongs.at(playerLeft->playerPlayedJongs.size()-1)->showTingIcon(leftplayed);
        }
        else if (seatId == ClientSeatId::right){
            playerRight->setPlayerTingState(true);
            if(playerRight->playerPlayedJongs.size()>0)
                playerRight->playerPlayedJongs.at(playerRight->playerPlayedJongs.size()-1)->showTingIcon(rightplayed);
        }
        else if (seatId == ClientSeatId::opposite){
            playerOpposite->setPlayerTingState(true);
            if(playerRight->playerPlayedJongs.size()>0)
                playerOpposite->playerPlayedJongs.at(playerOpposite->playerPlayedJongs.size()-1)->showTingIcon(oppositeplayed);
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
    if(getChildByTag(2000)!=NULL){
        getChildByTag(2000)->removeFromParent();
    }
    //重绘制场景
    GAMEDATA::getInstance()->clearPlayersInfo();
    LastGameData data = GAMEDATA::getInstance()->getLastGameDataBackup();
    if(data.result == 1){
        GAMEDATA::getInstance()->setHeroSeatId(data.seatId);
        GAMEDATA::getInstance()->setCurrentBank(data.loard);
        GAMEDATA::getInstance()->setHuangfan(StringUtil::itos(data.hf));
        GAMEDATA::getInstance()->setKaibao(StringUtil::itos(data.kb));
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
            recoverPlayer(player, SeatIdUtil::getClientSeatId(data.seatId, player.seatId), info);
        }
        showPaiduiNum(atoi(data.rest.c_str()));
    }else{
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
            info->setIsReady(player.ifready==0?false:true);
            info->setIP(player.ip);
            info->setUmark(player.umark);
            GAMEDATA::getInstance()->addPlayersInfo(info);
        }
        addPlayer2Room();
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
            addChild(playerOpposite);
            playerOpposite->recoverCpg(data.chiData ,data.pengData , data.gangData,data.angang);
            playerOpposite->recoverHand(data.hand);
            playerOpposite->recoverPlayed(data.outhand);
            playerOpposite->recoverHua(data.hua);
            
        }
    }
}



//显示玩家的方向和庄
void MahjongView::showOriention(){
    Orientation* ori = Orientation::create();
    ori->setTag(123);
    ori->showOrientation(GAMEDATA::getInstance()->getHeroSeatId());
    addChild(ori);
}



PlayerBase* MahjongView::getPlayerBySeatId(int sid){
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

void MahjongView::firstReplaceFlower(ReplaceJongVec vec,PlayerCpgtData data) {
    showPaiduiNum(atoi(vec.rest.c_str()));
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
    for(auto player : GAMEDATA::getInstance()->getPlayersInfo()){
        if(player->getSeatId() == GAMEDATA::getInstance()->getCurrentBank()){
            int clientId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), player->getSeatId());
            if(clientId == ClientSeatId::left){
                playerLeft->startTimeClockAnim();
            }else if(clientId == ClientSeatId::opposite){
                playerOpposite->startTimeClockAnim();
            }else if(clientId == ClientSeatId::right){
                playerRight->startTimeClockAnim();
            }else if(clientId == ClientSeatId::hero){
                if(data.playerGang.size()>0||data.ting!=""){
                    if (data.seatId == GAMEDATA::getInstance()->getHeroSeatId()){
                        showTingGangControllPad(data);
                        playerHero->startTimeClockAnim(9, 2);
                    }
                }else{
                    playerHero->startTimeClockAnim();
                }
            }
        }
    }
}

void MahjongView::showPaiduiNum(int num){
    if(NULL != getChildByTag(1129)){
        ((CardStack*)getChildByTag(1129))->setVisible(true);
        ((CardStack*)getChildByTag(1129))->setShowNum(num);
    }
}

void MahjongView::dealJongFinish(ReplaceJongVec vec,PlayerCpgtData data){
    if(NULL != playerHero)
        playerHero->drawPlayerHero();
    if(NULL != playerRight)
        playerRight->drawHandJong();
    if(NULL != playerOpposite)
        playerOpposite->drawHandJong();
    if(NULL != playerLeft)
        playerLeft->drawHandJong();
    if(NULL != playerHero && NULL != playerRight && NULL != playerOpposite && NULL != playerLeft)
        firstReplaceFlower(vec,data);
    if(NULL != playerRight)
        playerRight->setIsReady(false);
    if(NULL != playerOpposite)
        playerOpposite->setIsReady(false);
    if(NULL != playerLeft)
        playerLeft->setIsReady(false);
    if(NULL != playerHero)
        playerHero->setIsReady(false);
}


void MahjongView::heroPlayPokerAuto(int poker){
    
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
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(addOtherReadyListener, 1);
}



void MahjongView::addPlayerTurnListener(){
    turnListener = EventListenerCustom::create(MSG_PLAYER_TURN_WHO, [=](EventCustom* event){
        PlayerTurnData* turnData = static_cast<PlayerTurnData*>(event->getUserData());
        PlayerTurnData newData = *turnData;
        int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), newData.seatId);
        ((Orientation*)getChildByTag(123))->showPlayerTurn(GAMEDATA::getInstance()->getHeroSeatId(), newData.seatId);
        showPaiduiNum(atoi(newData.rest.c_str()));
        if (seatId == ClientSeatId::hero){
            playerHero->hideCurrentBigJong();
            playerHero->playerTurnReplace(newData);
            if (!GAMEDATA::getInstance()->getIsTingState()){
                playerHero->startTimeClockAnim();
            }
        }
        else if (seatId == ClientSeatId::left){
            playerLeft->drawLeftPlayerTurn();
            playerLeft->replaceTurnHua(newData);
            playerLeft->startTimeClockAnim();
        }
        else if (seatId == ClientSeatId::right){
            playerRight->drawRightPlayerTurn();
            playerRight->replaceTurnHua(newData);
            playerRight->startTimeClockAnim();
        }
        else if (seatId == ClientSeatId::opposite){
            playerOpposite->drawOppositePlayerTurn();
            playerOpposite->replaceTurnHua(newData);
            playerOpposite->startTimeClockAnim();
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(turnListener, 1);
}

void MahjongView::addJongPlayedListener(){
    otherListener = EventListenerCustom::create(MSG_OTHER_PALYER_JONG, [=](EventCustom* event){
        std::string result = static_cast<char*>(event->getUserData());
        vector<string> res =  StringUtil::split(result, ",");
        int seat = atoi(res.at(0).c_str());
        int poker =atoi(res.at(1).c_str());
        int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), seat);
        
        if (seatId == ClientSeatId::left){
            playerLeft->setIsOffLine(false);
            playerLeft->stopTimeClockAnim();
            playerLeft->drawPlayedJong(poker);
            if(poker == playerOpposite->getLastPoker()){
                Audio::getInstance()->playSoundGengShang(playerLeft->getPlayerInfo()->getGender());
            }else if(poker == playerHero->getLastPoker()){
                Audio::getInstance()->playSoundXiaGeng(playerLeft->getPlayerInfo()->getGender());
            }
        }
        else if (seatId == ClientSeatId::right){
            playerRight->setIsOffLine(false);
            playerRight->stopTimeClockAnim();
            playerRight->drawPlayedJong(poker);
            if(poker == playerHero->getLastPoker()){
                Audio::getInstance()->playSoundGengShang(playerRight->getPlayerInfo()->getGender());
            }else if(poker == playerOpposite->getLastPoker()){
                Audio::getInstance()->playSoundXiaGeng(playerRight->getPlayerInfo()->getGender());
            }
        }
        else if (seatId == ClientSeatId::opposite){
            playerOpposite->setIsOffLine(false);
            playerOpposite->stopTimeClockAnim();
            playerOpposite->drawPlayedJong(poker);
            if(poker == playerRight->getLastPoker()){
                Audio::getInstance()->playSoundGengShang(playerOpposite->getPlayerInfo()->getGender());
            }else if(poker == playerLeft->getLastPoker()){
                Audio::getInstance()->playSoundXiaGeng(playerOpposite->getPlayerInfo()->getGender());
            }
        }else if(seatId == ClientSeatId::hero){
            schedule([=](float dt){
                log("听牌后,系统提玩家出的牌是: %d",poker);
                playerHero->stopTimeClockAnim();
                playerHero->drawPlayedJong(poker);
                if(poker == playerLeft->getLastPoker()){
                    Audio::getInstance()->playSoundGengShang(playerHero->getPlayerInfo()->getGender());
                }else if(poker == playerRight->getLastPoker()){
                    Audio::getInstance()->playSoundXiaGeng(playerHero->getPlayerInfo()->getGender());
                }
            },0,0,0.6f,"delay_play_poker_auto");
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(otherListener, 1);
}



void MahjongView::addHeroCpgListener(){
    
    playerCpgListener = EventListenerCustom::create(MSG_PLAYER_CPG, [=](EventCustom* event){
        HeroCpgRespData* cpgData = static_cast<HeroCpgRespData*>(event->getUserData());
        HeroCpgRespData mewCpgData = *cpgData;
        drawCpgControllPad(mewCpgData.playCpgt);
        playerHero->startTimeClockAnim(9, 1);
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(playerCpgListener, 1);
    
}

void MahjongView::addGameResultListener(){
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
            schedule([=](float dt){
                PlayerCpgRecShow showRec;
                CpgPokerRec pokerRecL;
                pokerRecL.clientseatid =  ClientSeatId::left;
                for(auto left:playerLeft->playerCpgRecords){
                    std::vector<int> p;
                    for(auto pokers : left.pokersRecord){
                        p.push_back(pokers->getJongType());
                    }
                    pokerRecL.cpg.push_back(p);
                }
                showRec.playercpg.push_back(pokerRecL);
                
                CpgPokerRec pokerRecO;
                pokerRecO.clientseatid =  ClientSeatId::opposite;
                for(auto oppsite:playerOpposite->playerCpgRecords){
                    std::vector<int> p1;
                    for(auto pokers : oppsite.pokersRecord){
                        p1.push_back(pokers->getJongType());
                    }
                    pokerRecO.cpg.push_back(p1);
                }
                showRec.playercpg.push_back(pokerRecO);
                
                CpgPokerRec pokerRecR;
                pokerRecR.clientseatid =  ClientSeatId::right;
                for(auto right:playerRight->playerCpgRecords){
                    std::vector<int> p2;
                    for(auto pokers : right.pokersRecord){
                        p2.push_back(pokers->getJongType());
                    }
                    pokerRecR.cpg.push_back(p2);
                }
                showRec.playercpg.push_back(pokerRecR);
                
                CpgPokerRec pokerRecH;
                pokerRecH.clientseatid =  ClientSeatId::hero;
                for(auto hero:playerHero->playerCpgRecords){
                    std::vector<int> p3;
                    for(auto pokers : hero.pokersRecord){
                        p3.push_back(pokers->getJongType());
                    }
                    pokerRecH.cpg.push_back(p3);
                }
                showRec.playercpg.push_back(pokerRecH);
                
                GAMEDATA::getInstance()->setPlayerCpgRecShow(showRec);
                
                clearRoomPlayer();
                if(flag == "2"){
                    GAMEDATA::getInstance()->setResultFangzhuId(GAMEDATA::getInstance()->getFangZhuId());
                    GAMEDATA::getInstance()->setFangZhuId("");
                    GAMEDATA::getInstance()->setNeedShowLastResult(true);
                    GAMEDATA::getInstance()->setPrivateGameNum("0");
                    GAMEDATA::getInstance()->clearPlayersInfo();
                }else{
                    GAMEDATA::getInstance()->setNeedShowLastResult(false);
                }
                Director::getInstance()->replaceScene(TransitionFade::create(0.8f,ResultScene::createScene(0)));
            },0,0,6.0f,"go2Result");
        }else{
            clearRoomPlayer();
            GAMEDATA::getInstance()->setResultFangzhuId(GAMEDATA::getInstance()->getFangZhuId());
            GAMEDATA::getInstance()->setFangZhuId("");
            GAMEDATA::getInstance()->setPrivateGameNum("0");
            GAMEDATA::getInstance()->clearPlayersInfo();
            Director::getInstance()->replaceScene(TransitionFade::create(0.8f, LobbyScene::create()));
        }
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

void MahjongView::showHandPokerOver(int seatId){
    vector<GameResultData> results = GAMEDATA::getInstance()->getGameResults();
    string leftJongs="";
    string rightJongs="";
    string oppositeJongs="";
    string heroJongs="";
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
        playerLeft->updateHandJongs(leftJongs,true);
        showHuPaiXing(maxHuType);
        schedule([=](float dt){
            playerRight->hideHandJongs();
            playerRight->updateHandJongs(rightJongs,false);
            playerOpposite->hideHandJongs();
            playerOpposite->updateHandJongs(oppositeJongs,false);
            playerHero->hideHandJongs();
            playerHero->updateHandJongs(heroJongs,false);
        }, 0, 0, 15.0f/24,"fanpai");
    }else if(seatId == ClientSeatId::opposite){
        playerOpposite->hideHandJongs();
        playerOpposite->updateHandJongs(oppositeJongs,true);
        showHuPaiXing(maxHuType);
        schedule([=](float dt){
            playerRight->hideHandJongs();
            playerRight->updateHandJongs(rightJongs,false);
            playerLeft->hideHandJongs();
            playerLeft->updateHandJongs(leftJongs,false);
            playerHero->hideHandJongs();
            playerHero->updateHandJongs(heroJongs,false);
        }, 0, 0, 15.0f/24,"fanpai");
    }else if(seatId == ClientSeatId::right){
        playerRight->hideHandJongs();
        playerRight->updateHandJongs(rightJongs,true);
        showHuPaiXing(maxHuType);
        schedule([=](float dt){
            playerOpposite->hideHandJongs();
            playerOpposite->updateHandJongs(oppositeJongs,false);
            playerLeft->hideHandJongs();
            playerLeft->updateHandJongs(leftJongs,false);
            playerHero->hideHandJongs();
            playerHero->updateHandJongs(heroJongs,false);
        }, 0, 0, 15.0f/24,"fanpai");
    }else{
        playerHero->hideHandJongs();
        if(GAMEDATA::getInstance()->getIsLiuJu()){
            playerHero->updateHandJongs(heroJongs,false);
        }else{
            playerHero->updateHandJongs(heroJongs,true);
        }
        showHuPaiXing(maxHuType);
        schedule([=](float dt){
            playerOpposite->hideHandJongs();
            playerOpposite->updateHandJongs(oppositeJongs,false);
            playerRight->hideHandJongs();
            playerRight->updateHandJongs(rightJongs,false);
            playerLeft->hideHandJongs();
            playerLeft->updateHandJongs(leftJongs,false);
        }, 0, 0, 15.0f/24,"fanpai");
    }
    
}


void MahjongView::onEnterTransitionDidFinish(){
    if(GAMEDATA::getInstance()->getContinueAgain()){
        GAMEDATA::getInstance()->setContinueAgain(false);
        schedule([=](float dt){
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getReadyCommmand());
        }, 0, 0, 0.3f,"continueGame");
    }
    
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
                if(!GAMEDATA::getInstance()->getTurnHeroCpg()){
                    playerHero->setIsAllowPlay(true);
                }
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

void MahjongView::onExit()
{
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(gameFaPaiListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(addOtherReadyListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(loginRespListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(addPlayersListener);
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
    Director::getInstance()->getEventDispatcher()->removeEventListener(playerReplaceLoginListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(dissovelRoomSelectNotifyListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(viewIntnetListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(scrollTetxListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(coreOpenFriendRoomListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(coreLoginRespListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(playerOffLineListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(fangZhuLeaveListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(enterFriendRoomListener);
    
}



void MahjongView::addCoustomListener(){
    addOthersReadyListener();
    addPlayerTurnListener();
    addJongPlayedListener();
    addHeroCpgListener();
    addGameResultListener();
    addOthersChiListener();
    addOthersPengListener();
    addOthersGangListener();
    addPlayerTingNotifyListener();
    addHeroTingNotifyListener();
    addHeroTingRespListener();
    addHeroChiRespListener();
    addHeroPengRespListener();
    addHeroGangRespListener();
    addPlayerRemoveListener();
    addPlayerResumeListener();
    addPlayerOffLineListener();
    //登录地址变更
    playerReplaceLoginListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_PLAYER_REPLACE_LOGIN, [=](EventCustom* event){
        HintDialog* hin = HintDialog::create("你的账号在其他客户端登录",[=](Ref* ref){
            exit(0);
        });
        addChild(hin,5);
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
            tao->addToast(StringUtils::format("%s不同意解散房间",name.c_str()));
        }else{
            tao->addToast(StringUtils::format("%s同意解散房间",name.c_str()));
        }
    });
    
    //断线续玩
    lobbyConncetAgainListener=  Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_PLAYER_CONNECT_AGAIN, [=](EventCustom* event){
        //重新绘制玩家的牌和话
        GAMEDATA::getInstance()->setIsRecover(true);
        Director::getInstance()->replaceScene(MjGameScene::create());
        
    });
    
    scrollTetxListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_SCROLL_TEXT, [=](EventCustom* event){
        std::string msg = static_cast<char*>(event->getUserData());
        if(nullptr != ((ScrollTextEx*)getChildByTag(9980))){
            ((ScrollTextEx*)getChildByTag(9980))->setScrollStr(msg);
        }
    });
    
    //好友房间游戏未开始重新连接
    coreOpenFriendRoomListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_FRIEND_OPEN_ROOM_RESP, [=](EventCustom* event){
        GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
        FriendOpenRoomRespData resp = GAMEDATA::getInstance()->getFriendOpenRoomResp();
        for(auto var: GAMEDATA::getInstance()->getPlayersInfo()){
            if(var->getPoxiaoId() == UserData::getInstance()->getPoxiaoId()){
                var->setIsReady(false);
            }
        }
        if(resp.result == 1){
            schedule([=](float dt){
                GAMEDATA::getInstance()->setFangZhuId(UserData::getInstance()->getPoxiaoId());
                Director::getInstance()->replaceScene(TransitionFade::create(0.8f, MjGameScene::create()));
            }, 0, 0, 2.0f,"continueGame223");
        }
    });
    
    enterFriendRoomListener=  Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_ENTER_FRIEND_ROOM_RESP, [=](EventCustom* event){
        char* buf = static_cast<char*>(event->getUserData());
        std::string result = buf;
        for(auto var: GAMEDATA::getInstance()->getPlayersInfo()){
            if(var->getPoxiaoId() == UserData::getInstance()->getPoxiaoId()){
                var->setIsReady(false);
            }
        }
        if (result == "1"){
            schedule([=](float dt){
                GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
                Director::getInstance()->replaceScene(TransitionFade::create(0.8f, MjGameScene::create()));
            }, 0, 0, 2.0f,"continueGame223");
        }
    });
    
    
    coreLoginRespListener = EventListenerCustom::create(MSG_LOGIN_RESP, [=](EventCustom* event){
        Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(coreLoginRespListener, 1);
    fangZhuLeaveListener = EventListenerCustom::create(MSG_GAME_FANG_ZHU_LEAVE, [=](EventCustom* event){
        std::string msg = static_cast<char*>(event->getUserData());
        //        int seat_id = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), atoi(msg.c_str()));
        vector<Player*> players = GAMEDATA::getInstance()->getPlayersInfo();
        for (auto var: players) {
            if(var->getSeatId() == atoi(msg.c_str())){
                var->setIsReady(false);
            }
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(fangZhuLeaveListener, 1);
    
    gameFaPaiListener = EventListenerCustom::create(MSG_GAME_START_FAPAI_NOTIFY, [=](EventCustom* event){
        log("执行发牌,开始播放动画");
        if(GAMEDATA::getInstance()->getIsPlaying()){
            log("已经在游戏中了,不在发牌");
            return;
        }
        MahjongFaPaiData* msgData = static_cast<MahjongFaPaiData*>(event->getUserData());
        MahjongFaPaiData newMsgData = *msgData;
        GAMEDATA::getInstance()->setKaibao(newMsgData.kaibao);
        GAMEDATA::getInstance()->setHuangfan(newMsgData.huangfan);
        GAMEDATA::getInstance()->setCurrentBank(newMsgData.start);
        FriendOpenRoomRespData data = GAMEDATA::getInstance()->getFriendOpenRoomResp();
        data.prjucount = StringUtils::format("%d",newMsgData.prjucount);
        GAMEDATA::getInstance()->setFriendOpenRoomResp(data);
        GAMEDATA::getInstance()->setIsPlaying(true);//游戏状态改为游戏中
        if(NULL != playerHero){
            playerHero->setIsReady(false);//关闭准备的显示
            std::vector<std::string> strvce = StringUtil::split(newMsgData.heroPokers, ",");
            GAMEDATA::getInstance()->setHeroJongs(strvce);
        }
        if(NULL != playerRight)
            playerRight->setIsReady(false);
        if(NULL != playerOpposite)
            playerOpposite->setIsReady(false);
        if(NULL != playerLeft)
            playerLeft->setIsReady(false);
        playerHero->hideInviteButton();//隐藏玩家的邀请按钮45
        guiLayer->hideDissovleBtn();//隐藏房主的解散按钮
        ((Orientation*)getChildByTag(123))->showWhoBank(GAMEDATA::getInstance()->getHeroSeatId(),GAMEDATA::getInstance()->getCurrentBank());
        vector<string> dice2 =StringUtil::split(newMsgData.dice, ",") ;
        DealJongAnim* anim = DealJongAnim::create();
        anim->setTag(1000);
        anim->showDealJong(SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), GAMEDATA::getInstance()->getCurrentBank()) ,atoi(dice2.at(0).c_str()),atoi(dice2.at(1).c_str()),newMsgData.mjReplaceVec,newMsgData.mjTingData);
        addChild(anim);
        log("执行发牌,播放动画结束");
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(gameFaPaiListener, 1);
    
}

void MahjongView::addOthersChiListener(){
    othersChiListener = EventListenerCustom::create(MSG_OTHER_PLAYER_CHI, [=](EventCustom* event){
        PlayerCpgtData* data = static_cast<PlayerCpgtData*>(event->getUserData());
        PlayerCpgtData newData = *data;
        int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(),newData.seatId);
        setCurrentJongVisible(data->sId);
        ((Orientation*)getChildByTag(123))->showPlayerTurn(GAMEDATA::getInstance()->getHeroSeatId(),newData.seatId);
        if (seatId == ClientSeatId::left){
            playerLeft->drawPlayerChi(newData, getPlayerBySeatId(data->sId));
            playerLeft->playerCpgAnim(CpgType::chi, ClientSeatId::left);
            playerLeft->startTimeClockAnim();
        }
        else if (seatId == ClientSeatId::right){
            playerRight->drawPlayerChi(newData, getPlayerBySeatId(data->sId));
            playerRight->playerCpgAnim(CpgType::chi, ClientSeatId::right);
            playerRight->startTimeClockAnim();
        }
        else if (seatId == ClientSeatId::opposite){
            playerOpposite->drawPlayerChi(newData, getPlayerBySeatId(data->sId));
            playerOpposite->playerCpgAnim(CpgType::chi, ClientSeatId::opposite);
            playerOpposite->startTimeClockAnim();
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(othersChiListener, 1);
}

void MahjongView::addOthersPengListener(){
    othersPengListener = EventListenerCustom::create(MSG_OTHER_PLAYER_PENG, [=](EventCustom* event){
        PlayerCpgtData* data = static_cast<PlayerCpgtData*>(event->getUserData());
        PlayerCpgtData newData = *data;
        int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), newData.seatId);
        setCurrentJongVisible(newData.sId);
        ((Orientation*)getChildByTag(123))->showPlayerTurn(GAMEDATA::getInstance()->getHeroSeatId(),newData.seatId);
        if (seatId == ClientSeatId::left){
            hideTingGangControllPad();
            playerLeft->drawPlayerPeng(newData, getPlayerBySeatId(data->sId));
            playerLeft->playerCpgAnim(CpgType::peng, ClientSeatId::left);
            playerLeft->startTimeClockAnim();
        }
        else if (seatId == ClientSeatId::right){
            hideTingGangControllPad();
            playerRight->drawPlayerPeng(newData, getPlayerBySeatId(data->sId));
            playerRight->playerCpgAnim(CpgType::peng, ClientSeatId::right);
            playerRight->startTimeClockAnim();
        }
        else if (seatId == ClientSeatId::opposite){
            hideTingGangControllPad();
            playerOpposite->drawPlayerPeng(newData, getPlayerBySeatId(data->sId));
            playerOpposite->playerCpgAnim(CpgType::peng, ClientSeatId::opposite);
            playerOpposite->startTimeClockAnim();
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(othersPengListener, 1);
}

void MahjongView::addOthersGangListener(){
    othersGangListener = EventListenerCustom::create(MSG_OTHER_PLAYER_GANG, [=](EventCustom* event){
        PlayerCpgtData* data = static_cast<PlayerCpgtData*>(event->getUserData());
        PlayerCpgtData newData = *data;
        int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), newData.seatId);
        setCurrentJongVisible(newData.sId);
        ((Orientation*)getChildByTag(123))->showPlayerTurn(GAMEDATA::getInstance()->getHeroSeatId(), newData.seatId);
        if (seatId == ClientSeatId::left){
            hideTingGangControllPad();
            playerLeft->drawPlayerGang(newData, getPlayerBySeatId(data->sId));
            playerLeft->playerCpgAnim(CpgType::gang, ClientSeatId::left);
        }
        else if (seatId == ClientSeatId::right){
            hideTingGangControllPad();
            playerRight->drawPlayerGang(newData, getPlayerBySeatId(data->sId));
            playerRight->playerCpgAnim(CpgType::gang, ClientSeatId::right);
        }
        else if (seatId == ClientSeatId::opposite){
            hideTingGangControllPad();
            playerOpposite->drawPlayerGang(newData, getPlayerBySeatId(data->sId));
            playerOpposite->playerCpgAnim(CpgType::gang, ClientSeatId::opposite);
        }
        
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(othersGangListener, 1);
}

void MahjongView::addPlayerTingNotifyListener(){
    playerTingNotifyListener = EventListenerCustom::create(MSG_PLAYER_TING_NOTIFY, [=](EventCustom* event){
        std::string currentSeatId = static_cast<char*>(event->getUserData());
        int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), atoi(currentSeatId.c_str()));
        playerTingAnim(seatId);
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(playerTingNotifyListener, 1);
}

void MahjongView::addHeroTingNotifyListener(){
    tingNotifyListener = EventListenerCustom::create(MSG_HERO_TING_GANG, [=](EventCustom* event){
        HeroCpgRespData* cpgtData = static_cast<HeroCpgRespData*>(event->getUserData());
        HeroCpgRespData newData = *cpgtData;
        if (newData.playCpgt.seatId == GAMEDATA::getInstance()->getHeroSeatId()){
            showTingGangControllPad(newData.playCpgt);
            playerHero->startTimeClockAnim(9, 2);
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(tingNotifyListener, 1);
}

void MahjongView::addHeroTingRespListener(){
    tingRespListener = EventListenerCustom::create(MSG_PLAYER_TING_RESP, [=](EventCustom* event){
        char* buf = static_cast<char*>(event->getUserData());
        if (atoi(buf) == 1){
            GAMEDATA::getInstance()->setIsTingState(true);
            if(playerHero->playerPlayedJongs.size()>0)
                playerHero->playerPlayedJongs.at(playerHero->playerPlayedJongs.size()-1)->showTingIcon(heroplayed);
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(tingRespListener, 1);
}


void MahjongView::addHeroChiRespListener(){
    heroChiRespListener = EventListenerCustom::create(MSG_HERO_CHI_RESP, [=](EventCustom* event){
        HeroCpgRespData* heroData = static_cast<HeroCpgRespData*>(event->getUserData());
        HeroCpgRespData newHeroData = *heroData;
        shmjHeroCpgtData.playCpgt.heroHu =  newHeroData.playCpgt.heroHu;
        shmjHeroCpgtData.playCpgt.ting = newHeroData.playCpgt.ting;
        newHeroData.playCpgt = shmjHeroCpgtData.playCpgt;
        playerHero->hideCurrentBigJong();
        std::vector<string> chipai = StringUtil::split(selectedChi, ",");
        playerHero->drawHeroChi(newHeroData, chipai, playerLeft);
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(heroChiRespListener, 1);
    
}

void MahjongView::addHeroPengRespListener(){
    heroPengRespListener = EventListenerCustom::create(MSG_HERO_PENG_RESP, [=](EventCustom* event){
        HeroCpgRespData* cpgRespData  = static_cast<HeroCpgRespData*>(event->getUserData());
        HeroCpgRespData newCpgRespData = *cpgRespData;
        shmjHeroCpgtData.playCpgt.heroHu =  newCpgRespData.playCpgt.heroHu;
        shmjHeroCpgtData.playCpgt.ting = newCpgRespData.playCpgt.ting;
        newCpgRespData.playCpgt = shmjHeroCpgtData.playCpgt;
        int clientSeatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), newCpgRespData.playCpgt.sId);
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
    
}

void MahjongView::addHeroGangRespListener(){
    heroGangRespListener = EventListenerCustom::create(MSG_HERO_GANG_RESP, [=](EventCustom* event){
        HeroCpgRespData* resp = static_cast<HeroCpgRespData*>(event->getUserData());
        HeroCpgRespData newResp = *resp;
        playerHero->hideCurrentBigJong();
        int clientSeatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), newResp.playCpgt.sId);
        if (newResp.result == 0){
            playerHero->stopTimeClockAnim();
        }
        else{
            if (clientSeatId == ClientSeatId::right){
                playerHero->drawHeroGang(newResp, playerRight);
            }
            else if (clientSeatId == ClientSeatId::opposite){
                playerHero->drawHeroGang(newResp, playerOpposite);
            }
            else{
                playerHero->drawHeroGang(newResp, playerLeft);
            }
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(heroGangRespListener, 1);
    
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
            if(players.at(i)->getSeatId() ==  atoi(buf.c_str())){
                int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(),players.at(i)->getSeatId());
                if(seatId == ClientSeatId::left){
                    playerLeft->setIsOffLine(true);
                }else if(seatId == ClientSeatId::opposite){
                    playerOpposite->setIsOffLine(true);
                }else if(seatId == ClientSeatId::right){
                    playerRight->setIsOffLine(true);
                }
            }
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(playerOffLineListener, 1);
}


void MahjongView::addPlayerResumeListener(){
    playerResumeListener = EventListenerCustom::create(MSG_PLAYER_RESUME_GAME, [=](EventCustom* event){
        NetworkManage::getInstance()->startSocketBeat(CommandManage::getInstance()->getHeartCommmand());
        GAMEDATA::getInstance()->setIsRecover(true);
        Director::getInstance()->replaceScene(MjGameScene::create());
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(playerResumeListener, 1);
}


//void MahjongView::touchEvent(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
//{
//    Button* tem = (Button*)pSender;
//    switch (type)
//    {
//        case Widget::TouchEventType::BEGAN:{
//            if(NULL == getChildByTag(1789)){
//                statRecordSound = true;
//                GameAudioManage::getInstance()->beginRecordAudio();
//                auto soudn = Sprite::create("gameview/record_sound_ing.png");
//                soudn->setPosition(640,320);
//                soudn->setTag(1789);
//                addChild(soudn,5);
//            }
//        }
//            break;
//        case Widget::TouchEventType::MOVED:
//            break;
//        case Widget::TouchEventType::ENDED:
//            if(statRecordSound){
//                GameAudioManage::getInstance()->endRecordAudio();
//                if(NULL != getChildByTag(1789)){
//                    getChildByTag(1789)->removeFromParent();
//                }
//                tem->setTouchEnabled(false);
//            }
//            break;
//        case Widget::TouchEventType::CANCELED:
//            if(NULL != getChildByTag(1789)){
//                getChildByTag(1789)->removeFromParent();
//            }
//            break;
//        default:
//            break;
//    }
//}
