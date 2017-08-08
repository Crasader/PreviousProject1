#include "mahjong/gameview/player/PlayerHero.h"
#include "mahjong/gameview/shanghai/normal/MahjongView.h"
#include "mahjong/gameview/hongzhong/normal/HongZhongView.hpp"
#include "mahjong/gameview/widget/HuPaiHintLayer.hpp"
#include "mahjong/gameview/anim/HuaAnim.hpp"
#include "mahjong/common/utils/StringUtil.h"
#include "mahjong/GameConfig.h"
#include "server/NetworkManage.h"
#include "server/CommandManage.h"
#include "server/MsgConfig.h"
#include "server/SocketDataManage.h"
#include "wechat/ios/CallIOSMethod.h"
#include "wechat/android/CallAndroidMethod.h"
#include "mahjong/common/utils/Chinese.h"
#include "mahjong/gameview/trusteeship/Trusteeship.h"

bool PlayerHero::init() {
    if (!PlayerBase::init()) {
        return false;
    }
    initData();
    return true;
}

void PlayerHero::initData() {
    doubleClickJong = NULL;
    virtualJong = NULL;
    setHandPosX(JONG_POS_START_X);
    setIsAllowPlay(false);
    setIsAllowTouch(true);
    playerHandJongs.clear();
    playedIcon = Sprite::create("gameview/arrows.png");
    playedIcon->setVisible(false);
    addChild(playedIcon, 666);
    setCpgPostionX(JONG_POS_START_X);
    Trusteeship* tru = Trusteeship::create();
    tru->setTag(1678);
    tru->setVisible(false);
    addChild(tru,100);
}

void PlayerHero::onEnter(){
    PlayerBase::onEnter();
    addTouchListener();
}

void PlayerHero::onExit()
{
    PlayerBase::onExit();
    GAMEDATA::getInstance()->setIsTingState(false);
}

void PlayerHero::removeLastJong(){
    biaoji->setVisible(false);
    if(playerPlayedJongs.size()>0){
        playerPlayedJongs.at(playerPlayedJongs.size() - 1)->removeFromParent();
        playerPlayedJongs.popBack();
    }
}

void PlayerHero::setIsReady(bool b){
    PlayerBase::setIsReady(b);
    
}

void PlayerHero::drawPlayerTrue(bool state){
    if(NULL != getChildByTag(1678)&&state){
        getChildByTag(1678)->setVisible(true);
    }
    
    if(NULL != getChildByTag(1678)&&!state){
        getChildByTag(1678)->setVisible(false);
    }
    if(!state){
        this->setIsAllowTouch(true);
    }
}

void PlayerHero::hideInviteButton(){
    if(NULL != getChildByTag(9998)){
        if(GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom && atoi(GAMEDATA::getInstance()->getFriendOpenRoomResp().prjucount.c_str())>0){
            getChildByTag(9998)->setVisible(false);
        }
    }
}

bool PlayerHero::onTouchBegan(Touch *touch, Event *event) {
    if (!this->getIsAllowTouch() || GAMEDATA::getInstance()->getIsTingState()){
        return false;
    }
    selectJong = getTouchJong(touch);
    if(NULL != selectJong&&!selectJong->getIsProtected()){
        updateSelectedInfo(selectJong);
        if(GAMEDATA::getInstance()->getIsTingProcess()){
            selectJong->setPosition(selectJong->getPositionX(),JONG_POS_Y+40);
            //其余的牌Y轴高度回落
            resetHandJongsY(selectJong);
            bool findPoker = false;
            for(auto var : heroHuData){
                if(var.poker == selectJong->getJongType()){
                    findPoker = true;
                    if(NULL != getChildByTag(6689)){
                        getChildByTag(6689)->removeFromParent();
                    }
                    HuPaiHintLayer* huPai =  HuPaiHintLayer::create(var,this);
                    huPai->setTag(6689);
                    addChild(huPai,5);
                    startTimeClockAnim(15, 2);
                }
            }
            if(!findPoker){
                if(NULL != getChildByTag(6689)){
                    getChildByTag(6689)->removeFromParent();
                }
            }
        }
    }else{
        selectJong = NULL;
    }
    if(NULL != virtualJong){
        virtualJong->removeFromParent();
        virtualJong = NULL;
    }
    
    return true;
}

void PlayerHero::onTouchMoved(Touch *touch, Event *event) {
    if (virtualJong == NULL){
        selectJong = getTouchJong(touch);
        if(NULL == selectJong||selectJong->getIsProtected()){
            selectJong = NULL;
        }
        resetHandJongsY(selectJong);
    }
    if (touch->getLocation().y >= JONG_SEL_POS_Y){
        if (isAllowPlay) {
            if (virtualJong == NULL&&selectJong != NULL) {
                virtualJong = Jong::create();
                virtualJong->setPosition(selectJong->getPosition());
                virtualJong->showJong(herohand, selectJong->getJongType());
                virtualJong->setOpacity(100);
                virtualJong->setCascadeColorEnabled(true);
                virtualJong->setCascadeOpacityEnabled(true);
                addChild(virtualJong);
            }
            if (virtualJong != NULL)
                virtualJong->setPosition(touch->getLocation() - touch->getPreviousLocation() + virtualJong->getPosition());
        }
    }
    else{
        if (selectJong != NULL){
            if (touch->getLocation().y >= 90){
                selectJong->setPosition(selectJong->getPositionX(), touch->getLocation().y);
            }
            else{
                selectJong->setPosition(selectJong->getPositionX(), JONG_POS_Y);
            }
            if(!selectJong->getIsProtected()){
                updateSelectedInfo(selectJong);
            }else{
                selectJong = NULL;
            }
        }
        if (virtualJong != NULL){
            virtualJong->removeFromParent();
            virtualJong = NULL;
        }
    }
}

void PlayerHero::onTouchEnded(Touch *touch, Event *event) {
    if (virtualJong != NULL&&selectJong != NULL){
        virtualJong->setOpacity(255);
        playPokerByHand(virtualJong);
        arrangeHandJongs();
    }
    if (isAllowPlay) {
        if (doubleClickJong == NULL){
            doubleClickJong = getTouchJong(touch);
            //保护中的牌，无法选中
            if(doubleClickJong!=NULL&&doubleClickJong->getIsProtected()){
                doubleClickJong = NULL;
            }
        }
        else{
            if (doubleClickJong == getTouchJong(touch)){
                Jong* jong = Jong::create();
                jong->setPosition(doubleClickJong->getPosition());
                jong->showJong(herohand, doubleClickJong->getJongType());
                addChild(jong);
                selectJong = doubleClickJong;
                playPokerByHand(jong);
                arrangeHandJongs();
                doubleClickJong = NULL;
            }else{
                doubleClickJong = getTouchJong(touch);
                if(NULL != doubleClickJong)
                    updateSelectedInfo(doubleClickJong);
            }
        }
    }
}


void PlayerHero::updateSelectedInfo(Jong* jong){
    for(auto var :playerHandJongs){
        if(jong == var){
            var->setJongSelectIcon(true);
        }else{
            var->setJongSelectIcon(false);
        }
    }
}

Jong* PlayerHero::getTouchJong(Touch *touch){
    for (int i = 0; i < playerHandJongs.size(); i++) {
        if (playerHandJongs.at(i)->getJongBoundingBox().containsPoint(touch->getLocation())) {
            return playerHandJongs.at(i);
        }
    }
    return NULL;
}


void PlayerHero::playPokerByHand(Jong* jong){
    if(NULL != virtualJong){
        virtualJong = NULL;
    }
    if(NULL != getChildByTag(6689)){
        getChildByTag(6689)->removeFromParent();
    }
    for(auto var:playerHandJongs){
        var->setTingJongHint(false);
    }
    updateSelectedInfo(NULL);
    stopTimeClockAnim();
    PlayerBase::showPlayedJong(jong->getJongType());
    Point startPoint = jong->getPosition();
    Point endPoint = getHeroPlayedJongsPos((int)playerPlayedJongs.size());
    float sx = startPoint.x;
    float sy = startPoint.y;
    float ex = endPoint.x;
    float ey = endPoint.y;
    ccBezierConfig bezier;
    bezier.controlPoint_1 = Point(sx, sy);
    bezier.controlPoint_2 = Point(sx + (ex - sx) * 0.5,
                                  sy + (ey - sy) * 0.5 + 200);
    bezier.endPosition = Point(endPoint.x, endPoint.y );
    BezierTo *actionMove = BezierTo::create(0.3f, bezier);
    ScaleTo* scale = ScaleTo::create(0.3f, 0.45f);
    Spawn* spa = Spawn::create(actionMove, scale, NULL);
    CallFunc* callback = CallFunc::create([=](){
        jong->showJong(heroplayed, jong->getJongType());
        jong->setScale(1.0f);
        playerPlayedJongs.pushBack(jong);
        isAllowPlay = false;
        virtualJong = NULL;
        if (!GAMEDATA::getInstance()->getIsTingState()
            && !GAMEDATA::getInstance()->getIsTingProcess()
            && !GAMEDATA::getInstance()->getIsTrusteeship()){
            sendPokerRequest(jong->getJongType());
        }
        else if (GAMEDATA::getInstance()->getIsTingProcess()){
            sendTingRequest(jong->getJongType());
            ((MahjongView*)getParent())->hideTingGangControllPad();
            GAMEDATA::getInstance()->setIsTingProcess(false);
        }
        resetHandJongsY(jong);
        
    });
    CallFunc* callback2 = CallFunc::create([=](){
        showCurrentPlayedJongIcon(true);
        if(GAMEDATA::getInstance()->getGameType() == 1){
            //打完牌后取消不可出牌的保护
            for(auto var:getSelfHandJongs()){
                var->showBackShadow(false);
            }
        }
    });
    
    Sequence* seq = Sequence::create(spa,callback,callback2,NULL);
    jong->runAction(seq);
}


void PlayerHero::drawPlayerHero() {
    std::vector<std::string> strvce = GAMEDATA::getInstance()->getHeroJongs();
    for (int t = 0; t < strvce.size(); t++) {
        if (t < -3){
            Jong* jong = Jong::create();
            jong->showJong(herohand, 1);
            playerHandJongs.pushBack(jong);
        }
        else{
            Jong* jong = Jong::create();
            jong->showJong(herohand, atoi(strvce.at(t).c_str()));
            playerHandJongs.pushBack(jong);
        }
    }
    for (int i = 0; i < playerHandJongs.size(); i++) {
        if (i == MAX_JONG_NUM - 1){
            playerHandJongs.at(i)->setPosition(Point(NEW_JONG_POS_X, JONG_POS_Y));
        }
        else{
            playerHandJongs.at(i)->setPosition(Point(JONG_POS_START_X + JONG_WIDTH * i, JONG_POS_Y));
        }
        addChild(playerHandJongs.at(i));
    }
    currentJong = playerHandJongs.at(playerHandJongs.size()-1);
    
}


void PlayerHero::updateHandJongs(std::string jongs,bool hu){
    if(jongs.size()>0){
        vector<std::string> pokers = StringUtil::split(jongs, ",");
        if(hu){
            vector<std::string>::iterator itor;
            for(itor=pokers.begin();itor!=pokers.end();)
            {
                if(GAMEDATA::getInstance()->getDiaopao()==*itor)
                {
                    itor=pokers.erase(itor);
                    break;
                }
                else
                {
                    itor++;
                }
            }
            pokers.push_back(GAMEDATA::getInstance()->getDiaopao());
        }
        for (int i = 0; i < pokers.size(); i++)
        {
            if(pokers.at(i) != ""){
                Jong* jong = Jong::create();
                jong->showJong(herocpgportrait, atoi(pokers.at(i).c_str()));
                if(hu&&i==pokers.size()-1){
                    jong->setPosition(Point(playerHandJongs.at(0)->getPosition().x + 60 * i+10, JONG_POS_Y));
                }else{
                    if(playerHandJongs.size()>0)
                        jong->setPosition(Point(playerHandJongs.at(0)->getPosition().x + 60 * i, JONG_POS_Y));
                }
                addChild(jong);
            }
        }
    }
}

void PlayerHero::showCurrentPlayedJongIcon(bool isShow){
    if(playerPlayedJongs.size()>0){
        biaoji->setPosition(playerPlayedJongs.at(playerPlayedJongs.size() - 1)->getPosition().x,
                            playerPlayedJongs.at(playerPlayedJongs.size() - 1)->getPosition().y + 20);
        biaoji->setVisible(isShow);
        playedIcon->setPosition(biaoji->getPosition());
        playedIcon->setVisible(isShow);
    }
}

Vector<Jong*> PlayerHero::getSelfHandJongs(){
    return this->playerHandJongs;
}

void PlayerHero::resetHandJongsY(Jong* jong){
    for (int i = 0; i < playerHandJongs.size(); i++) {
        if (playerHandJongs.at(i) != jong)
            playerHandJongs.at(i)->setPosition(
                                               Point(playerHandJongs.at(i)->getPositionX(), JONG_POS_Y));
    }
}

void PlayerHero::drawReady(bool ready){
    if(GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom && atoi(GAMEDATA::getInstance()->getFriendOpenRoomResp().prjucount.c_str())==0 && !GAMEDATA::getInstance()->getIsPlaying()&&GAMEDATA::getInstance()->getFangZhuId()==UserData::getInstance()->getPoxiaoId()){
        MenuItemImage* inviteImage = MenuItemImage::create("gameview/invite_friend_1.png", "gameview/invite_friend_2.png", CC_CALLBACK_0(PlayerHero::inviteWechatFriend, this));
        auto invite = Menu::create(inviteImage, NULL);
        invite->setPosition(Point(640, 235));
        invite->setTag(9998);
        addChild(invite);
        if(GAMEDATA::getInstance()->getIsCompetitionState()||GAMEDATA::getInstance()->getIsCompetitionQueue()){
            invite->setVisible(false);
        }
    }
    if (!ready){
        MenuItemImage* image = MenuItemImage::create("gameview/ready_1.png", "gameview/ready_2.png", CC_CALLBACK_0(PlayerHero::readyGo, this));
        auto start = Menu::create(image, NULL);
        start->setTag(888);
        start->setPosition(Point(640, 100));
        this->addChild(start);
    }else{
        if (NULL != getChildByTag(888)){
            getChildByTag(888)->setVisible(false);
        }
        setIsReady(true);
    }
}


void PlayerHero::readyGo(){
    if (NULL != getChildByTag(888)){
        getChildByTag(888)->setVisible(false);
    }
    setIsReady(true);
    if(GAMEDATA::getInstance()->getGameType() == 1){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getReadyCommmand());
    }else if (GAMEDATA::getInstance()->getGameType() == 3){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getHZPlayerReadyCommand());
    }else if(GAMEDATA::getInstance()->getGameType() == 5){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendCmReadyCommand());
    }
}


void PlayerHero::inviteWechatFriend(){
    std::string gameName = "上海敲麻";
    std::string roomtype = ChineseWord("room_info_0");
    if(GAMEDATA::getInstance()->getGameType() == 1 || GAMEDATA::getInstance()->getGameType() == 2){
        roomtype += ChineseWord("game_type_1");
    }else{
        roomtype += ChineseWord("game_type_2");
    }
    if(GAMEDATA::getInstance()->getMyGameModel() == GameModel::TWOPLAYER){
        roomtype += ChineseWord("room_info_17");
    }
    roomtype += ChineseWord("room_info_1");
    roomtype += GAMEDATA::getInstance()->getFriendOpenRoomResp().prjushu;
    if(GAMEDATA::getInstance()->getGameType() == 1 || GAMEDATA::getInstance()->getGameType() == 2){
        if(GAMEDATA::getInstance()->getPrivateKaibao()=="0"){
            roomtype += ChineseWord("room_info_2");
        }else{
            roomtype += ChineseWord("room_info_3");
        }
        if(GAMEDATA::getInstance()->getPrivateDihua()=="0"){
            roomtype += ",1/1";
        }else if(GAMEDATA::getInstance()->getPrivateDihua()=="1"){
            roomtype += ",2/2";
        }else if(GAMEDATA::getInstance()->getPrivateDihua()=="2"){
            roomtype += ",6/2";
        }else if(GAMEDATA::getInstance()->getPrivateDihua()=="3"){
            roomtype += ",5/5";
        }
        if(GAMEDATA::getInstance()->getPrivateLezi()=="0"){
            roomtype += ChineseWord("room_info_7");
        }else if(GAMEDATA::getInstance()->getPrivateLezi()=="1"){
            roomtype += ChineseWord("room_info_8");
        }
        else if(GAMEDATA::getInstance()->getPrivateLezi()=="2"){
            roomtype += ChineseWord("room_info_9");
        }else if(GAMEDATA::getInstance()->getPrivateLezi()=="3"){
            roomtype += ChineseWord("room_info_10");
        }
        if(GAMEDATA::getInstance()->getPrivateEmsc()=="1"){
            roomtype += ChineseWord("room_info_6");
        }
        if(GAMEDATA::getInstance()->getPrivateFcy()=="1"){
            roomtype += "飞苍蝇";
        }
    }else if(GAMEDATA::getInstance()->getGameType() == 3 || GAMEDATA::getInstance()->getGameType() == 4){
        gameName = "红中麻将";
        if(GAMEDATA::getInstance()->getFanMaType() == "4"){
            roomtype += ChineseWord("room_info_13");
        }else if(GAMEDATA::getInstance()->getFanMaType() == "3"){
            roomtype += ChineseWord("room_info_14");
        }else if (GAMEDATA::getInstance()->getFanMaType() == "1"){
            roomtype += ChineseWord("room_info_15");
        }
        roomtype += ChineseWord("room_info_16");
        roomtype += StringUtils::format("%s",GAMEDATA::getInstance()->getHZDiFen().c_str());
        
    }
    std::string shareUrl = GAMEDATA::getInstance()->getMahjongShareData1().url;
    if(GAMEDATA::getInstance()->getMahjongShareData1().type == "1"){
        shareUrl = StringUtils::format("%s%s",shareUrl.c_str(),UserData::getInstance()->getPoxiaoId().c_str());
    }
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CallAndroidMethod::getInstance()->shareToWeChat(shareUrl,StringUtils::format("小白相%s 房号:%s %s",gameName.c_str(),GAMEDATA::getInstance()->getFriendOpenRoomResp().prid.c_str(),GAMEDATA::getInstance()->getMahjongShareData3().head.c_str()),StringUtils::format("%s %s",roomtype.c_str(),GAMEDATA::getInstance()->getMahjongShareData3().head.c_str()),false);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CallIOSMethod::getInstance()->doWechatShareWeb(shareUrl,StringUtils::format("小白相%s 房号:%s %s",gameName.c_str(),GAMEDATA::getInstance()->getFriendOpenRoomResp().prid.c_str(),GAMEDATA::getInstance()->getMahjongShareData3().head.c_str()),StringUtils::format("%s %s",roomtype.c_str(),GAMEDATA::getInstance()->getMahjongShareData3().head.c_str()),0);
#endif
}


void PlayerHero::sendPokerRequest(int poker){
    log("向服务端发送出牌请求 %d",poker);
    if(GAMEDATA::getInstance()->getGameType() == 1){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getPlayPokerCommmand(poker));
    }else{
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getHZPlayPokerCommand(StringUtils::format("%d",poker)));
    }
}


Point PlayerHero::getHeroPlayedJongsPos(int index) {
    int row = index / 10;
    int line = index % 10;
    Point originPos = Point(475, 275);
    if (row == 0) {
        return Point(originPos.x + 35 * line, originPos.y);
    }
    else  {
        return Point(originPos.x + 35 * line, originPos.y - 42*row);
    }
    
}

float PlayerHero::distance(Point pos1, Point pos2) {
    return sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));
}

void PlayerHero::settleHandJongs(int posx){
    int size = (int)playerHandJongs.size();
    for (int k = 0; k < size; k++){
        if (posx + JONG_WIDTH * k>JONG_POS_13_X){
            playerHandJongs.at(k)->setPosition(Point(NEW_JONG_POS_X, JONG_POS_Y));
        }
        else{
            playerHandJongs.at(k)->setPosition(Point(posx + JONG_WIDTH * k, JONG_POS_Y));
        }
    }
}

void PlayerHero::sortHandJongs(int posx, bool isTurn){
    int size = (int)playerHandJongs.size();
    for (int i = 0; i < size - 1; i++) {
        for (int j = size - 1; j > i; j--) {
            if (playerHandJongs.at(j)->getJongType() < playerHandJongs.at(j - 1)->getJongType()) {
                playerHandJongs.swap(playerHandJongs.at(j), playerHandJongs.at(j - 1));
            }
        }
    }
    for (int k = 0; k < size; k++){
        if (posx + JONG_WIDTH * k>JONG_POS_13_X){
            playerHandJongs.at(k)->setPosition(Point(NEW_JONG_POS_X, JONG_POS_Y));
        }
        else{
            playerHandJongs.at(k)->setPosition(Point(posx + JONG_WIDTH * k, JONG_POS_Y));
        }
    }
    if (isTurn){
        currentJong = playerHandJongs.at(playerHandJongs.size() - 1);
    }
}


Vector<Jong*> PlayerHero::upsetJongs(Vector<Jong*> jongs) {
    Vector<Jong*> newJongs;
    for (int i = 0; i < (int)jongs.size(); i++) {
        int current = rand() % ((int)jongs.size());
        newJongs.pushBack(jongs.at(current));
        jongs.erase(current);
    }
    return newJongs;
}


Vector<Jong*>  PlayerHero::sortJongs(Vector<Jong*> jongs){
    for (int i = 0; i < (int)jongs.size() - 1; i++) {
        for (int j = (int)jongs.size() - 1; j > i; j--) {
            if (jongs.at(j)->getJongType() < jongs.at(j - 1)->getJongType()) {
                jongs.swap(jongs.at(j), jongs.at(j - 1));
            }
        }
    }
    return jongs;
}

void PlayerHero::arrangeHandJongs() {
    if (currentJong == selectJong) {
        isAllowPlay = false;
        selectJong->removeFromParent();
        eraseHeroJong(selectJong);
        return;
    }
    
    Point needMovePos;
    bool needBezier = true;
    if (currentJong->getJongType() == selectJong->getJongType()) {
        needMovePos = selectJong->getPosition();
    }
    else {
        Point pos = selectJong->getPosition();
        int index = 0;
        for (int i = 0; i < playerHandJongs.size(); i++) {
            if (selectJong == playerHandJongs.at(i)) {
                index = i;
            }
        }
        bool isMoved = false;
        bool moveLeft = true;
        
        
        if (currentJong->getJongType() >= selectJong->getJongType()) {
            moveLeft = true;
            for (int j = index + 1; j < playerHandJongs.size(); j++) {
                if (currentJong->getJongType()<playerHandJongs.at(j)->getJongType()) {
                    if (!isMoved) {
                        needMovePos = Point(
                                            playerHandJongs.at(j)->getPositionX(),
                                            JONG_POS_Y);
                        isMoved = true;
                    }
                }
                else {
                    auto move = MoveTo::create(0.2f,
                                               Point(playerHandJongs.at(j)->getPositionX() - JONG_WIDTH,
                                                     JONG_POS_Y));
                    playerHandJongs.at(j)->runAction(move);
                }
            }
            if (!isMoved){
                isMoved = true;
                needBezier = false;
                auto move = MoveTo::create(0.2f,
                                           Point(getHandPosX() + JONG_WIDTH * (playerHandJongs.size() - 1), JONG_POS_Y));
                playerHandJongs.at(playerHandJongs.size() - 1)->runAction(move);
            }
        }
        else {
            moveLeft = false;
            for (int k = index - 1; k >= 0; k--) {
                if (currentJong->getJongType()>playerHandJongs.at(k)->getJongType()) {
                    if (!isMoved) {
                        needMovePos = Point(
                                            playerHandJongs.at(k)->getPositionX() + JONG_WIDTH,
                                            JONG_POS_Y);
                        isMoved = true;
                    }
                }
                else {
                    auto move = MoveTo::create(0.2f,
                                               Point(playerHandJongs.at(k)->getPositionX() + JONG_WIDTH,
                                                     JONG_POS_Y));
                    playerHandJongs.at(k)->runAction(move);
                }
            }
            if (!isMoved){
                needMovePos = Point(
                                    playerHandJongs.at(0)->getPositionX(),
                                    JONG_POS_Y);
                isMoved = true;
            }
        }
    }
    if (needBezier){
        ccBezierConfig bezier;
        bezier.controlPoint_1 = currentJong->getPosition();
        bezier.controlPoint_2 = Point(
                                      needMovePos.x + (currentJong->getPositionX() - needMovePos.x) * 0.5,
                                      JONG_POS_Y + 50);
        bezier.endPosition = Point(needMovePos.x, JONG_POS_Y);
        BezierTo *actionMove = BezierTo::create(0.2f, bezier);
        currentJong->runAction(actionMove);
    }
    
    setIsAllowPlay(false);
    selectJong->removeFromParent();
    eraseHeroJong(selectJong);
    auto delay = DelayTime::create(0.25f);
    auto callback = CallFunc::create([=](){
        sortHandJongs(getHandPosX(), true);
    });
    auto sequence = Sequence::create(delay, callback, NULL);
    runAction(sequence);
}


void PlayerHero::addTouchListener() {
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(PlayerHero::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(PlayerHero::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(PlayerHero::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);
}

void PlayerHero::replaceFlower(){
    log("执行杠花流程");
    isAllowPlay = false;
    ReplaceJong rejong = getReplacePoker();
    if (rejong.poker.size() == 0){
        //没有花的情况
        int bankId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), GAMEDATA::getInstance()->getCurrentBank());
        if (bankId == ClientSeatId::hero){
            isAllowPlay = true;
        }
        showPlayerHua(getHuaNum());
    }else{
        //有花的情况
        huaIndex = 0;
        schedule([=](float dt){
            if(rejong.poker.at(huaIndex)!="" && rejong.replace.at(huaIndex)!=""){
                pokerV = StringUtil::split(rejong.poker.at(huaIndex), ",");
                replaceV = StringUtil::split(rejong.replace.at(huaIndex), ",");
                huaIndex++;
                std::vector<Jong*> needReplace;
                needReplace.clear();
                for (int i = 0; i < pokerV.size(); i++){
                    Jong* jon = Jong::create();
                    jon->showJong(herohand,atoi(pokerV.at(i).c_str()));
                    needReplace.push_back(jon);
                }
                for (int j = 0; j < pokerV.size(); j++){
                    for (int k = 0; k < playerHandJongs.size(); k++){
                        if (atoi(pokerV.at(j).c_str()) == playerHandJongs.at(k)->getJongType()){
                            playerHandJongs.at(k)->showJong(herohand, atoi(replaceV.at(j).c_str()));
                            break;
                        }
                    }
                }
                HuaAnim* huaAnim = HuaAnim::create(needReplace, GAMEDATA::getInstance()->getHeroSeatId(),CallFunc::create([=](){
                    setHuaNum(getHuaNum()+(int)needReplace.size());
                    showPlayerHua(getHuaNum());
                }));
                addChild(huaAnim,100);
            }
        }, 0.6f, (int)rejong.poker.size()-1, 0,"huahuahua");
        
        schedule([=](float dt){
            int bankId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), GAMEDATA::getInstance()->getCurrentBank());
            if (bankId == ClientSeatId::hero){
                isAllowPlay = true;
            }
            sortHandJongs(getHandPosX(), true);
        }, 0, 0, 0.6f*rejong.poker.size(),"huadelay");
    }
}

void PlayerHero::playerTurnReplace(PlayerTurnData data){
    huaIndex = 0;
    std::vector<std::string> replace = StringUtil::split(data.replace, ",");
    PlayerCpgtData cpgData = data.cpgData;
    if (data.replace != "" && replace.size() > 0 && data.handNum>getSelfHandJongs().size()){
        Jong* turnJong = Jong::create();
        turnJong->showJong(herohand, data.poker);
        turnJong->setPosition(NEW_JONG_POS_X,JONG_POS_Y);
        addChild(turnJong);
        playerHandJongs.pushBack(turnJong);
        schedule([=](float dt){
            std::vector<Jong*> needReplace;
            needReplace.clear();
            Jong* jong = Jong::create();
            jong->showJong(herohand, atoi(replace.at(huaIndex).c_str()));
            needReplace.push_back(jong);
            HuaAnim* huaAnim = HuaAnim::create(needReplace, GAMEDATA::getInstance()->getHeroSeatId(),CallFunc::create([=](){
                setHuaNum(getHuaNum()+(int)needReplace.size());
                showPlayerHua(getHuaNum());
            }));
            addChild(huaAnim,100);
            huaIndex++;
        }, 0.6f, (int)replace.size()-1, 0,"hua2poker");
        schedule([=](float dt){
            currentJong = turnJong;
            settleHandJongs(getHandPosX());
            setIsAllowPlay(true);
            if(data.hastinggang){
                ((MahjongView*)getParent())->showTingGangControllPad(cpgData);
            }
        }, 0, 0, 0.6f*replace.size(),"hua2pokerdelay");
    }
    else{
        if(data.poker>=0 && data.handNum>getSelfHandJongs().size()){
            Jong* jong = Jong::create();
            jong->showJong(herohand, data.poker);
            addChild(jong);
            playerHandJongs.pushBack(jong);
            currentJong = jong;
            settleHandJongs(getHandPosX());
        }
        
        if(GAMEDATA::getInstance()->getGameType() == 1 && data.hastinggang){
            ((MahjongView*)getParent())->showTingGangControllPad(cpgData);
        }
        
        if(GAMEDATA::getInstance()->getGameType() == 3 && (data.cpgData.hu == 1 ||data.hastinggang)){
            ((HongZhongView*)getParent())->showHuGangControllPad(cpgData);
        }
        
        if (!(GAMEDATA::getInstance()->getIsTingState())){
            setIsAllowPlay(true);
        }
    }
    doubleClickJong = NULL;
}

void PlayerHero::playerTurnReplaceMingpai(PlayerTurnData data){
    if(data.replace != ""){
        std::vector<std::string> replace = StringUtil::split(data.replace, ",");
        if((int)replace.size()>0)
            setHuaNum(getHuaNum()+(int)replace.size());
        showPlayerHua(getHuaNum());
    }
    Jong* jong = Jong::create();
    jong->showJong(herohand, data.poker);
    addChild(jong);
    playerHandJongs.pushBack(jong);
    currentJong = jong;
    settleHandJongs(getHandPosX());
    if (!(GAMEDATA::getInstance()->getIsTingState())){
        setIsAllowPlay(true);
    }
    doubleClickJong = NULL;
}

void PlayerHero:: drawPlayedJong(int type){
    PlayerBase::showPlayedJong(type);
    if(NULL != getChildByTag(6689)){
        getChildByTag(6689)->removeFromParent();
    }
    for(auto var:playerHandJongs){
        var->setTingJongHint(false);
    }
    if (virtualJong != NULL){
        virtualJong->setVisible(false);
        virtualJong->removeFromParent();
        virtualJong = NULL;
    }
    resetHandJongsY(NULL);
    bool find = false;
    for(int i=(int)playerHandJongs.size()-1;i>=0;i--){
        if(playerHandJongs.at(i)->getJongType()==type){
            find = true;
            Jong* spJong = Jong::create();
            spJong->showJong(herohand, playerHandJongs.at(i)->getJongType());
            spJong->setPosition(playerHandJongs.at(i)->getPosition());
            addChild(spJong);
            playerHandJongs.at(i)->removeFromParent();
            playerHandJongs.eraseObject(playerHandJongs.at(i));//从手牌队列中移除
            Point startPoint = spJong->getPosition();
            Point endPoint = getHeroPlayedJongsPos((int)playerPlayedJongs.size());
            float sx = startPoint.x;
            float sy = startPoint.y;
            float ex = endPoint.x;
            float ey = endPoint.y;
            ccBezierConfig bezier;
            bezier.controlPoint_1 = Point(sx, sy);
            bezier.controlPoint_2 = Point(sx + (ex - sx) * 0.5,
                                          sy + (ey - sy) * 0.5 + 200);
            bezier.endPosition = Point(endPoint.x , endPoint.y);
            BezierTo *actionMove = BezierTo::create(0.3f, bezier);
            ScaleTo* scale = ScaleTo::create(0.3f, 0.45f);
            Spawn* spa = Spawn::create(actionMove, scale, NULL);
            CallFunc* callback = CallFunc::create([=](){
                spJong->showJong(heroplayed, spJong->getJongType());
                spJong->setScale(1.0f);
                playerPlayedJongs.pushBack(spJong);
                isAllowPlay = false;
            });
            Sequence* seq = Sequence::create(spa, callback, CallFunc::create([=](){
                sortHandJongs(getHandPosX(), false);
            }), NULL);
            spJong->runAction(seq);
            break;
        }
    }
    if(find){
        log("手牌中有这张牌 == %d",type);
    }else{
        log("手牌中并没有这张牌== %d",type);
    }
}

int PlayerHero::getNumbersByPoker(string pokers){
    return ((MahjongView*)getParent())->getNumbersByPoker(pokers);
}


void PlayerHero::drawPlayedJongMingpai(int type){
    PlayerBase::showPlayedJong(type);
    if (virtualJong != NULL){
        virtualJong->setVisible(false);
        virtualJong->removeFromParent();
        virtualJong = NULL;
    }
    resetHandJongsY(NULL);
    bool find = false;
    for(int i=(int)playerHandJongs.size()-1;i>=0;i--){
        if(playerHandJongs.at(i)->getJongType()==type){
            find = true;
            Jong* spJong = Jong::create();
            spJong->showJong(herohand, playerHandJongs.at(i)->getJongType());
            spJong->setPosition(playerHandJongs.at(i)->getPosition());
            addChild(spJong);
            playerHandJongs.at(i)->removeFromParent();
            playerHandJongs.eraseObject(playerHandJongs.at(i));//从手牌队列中移除
            Point endPoint = getHeroPlayedJongsPos((int)playerPlayedJongs.size());
            spJong->showJong(heroplayed, spJong->getJongType());
            spJong->setPosition(endPoint);
            playerPlayedJongs.pushBack(spJong);
            isAllowPlay = false;
            sortHandJongs(getHandPosX(), false);
            break;
        }
    }
    if(find){
        log("手牌中有这张牌 == %d",type);
    }else{
        log("手牌中并没有这张牌== %d",type);
    }
}


void PlayerHero::eraseHeroJong(Jong* jong){
    playerHandJongs.eraseObject(jong);
}

void PlayerHero::removePlayedIcon(){
    if(NULL!= playedIcon){
        playedIcon->setVisible(false);
    }
}

void PlayerHero::doEventTimeOver(int type){
    if(GAMEDATA::getInstance()->getIsCompetitionState()){
        setIsAllowPlay(false);
        if(virtualJong != NULL){
            virtualJong->removeFromParent();
            virtualJong = NULL;
        }
    }
}


void PlayerHero::actionTing(HeroCpgRespData tingData){
    setIsAllowTouch(true);
    GAMEDATA::getInstance()->setIsTingProcess(true);
    heroHuData = tingData.playCpgt.heroHu;
    //对heroHuData进行自动排序
    int max = 1;
    for(int k=0;k<heroHuData.size();k++){
        if(getNumbersByPoker(heroHuData.at(k).hu) > max){
            max = getNumbersByPoker(heroHuData.at(k).hu);
        }
    }
    for (int i = 0; i < playerHandJongs.size(); i++){
        for (int j=0; j<tingData.playCpgt.heroHu.size(); j++) {
            if(playerHandJongs.at(i)->getJongType() == tingData.playCpgt.heroHu.at(j).poker){
                if(getNumbersByPoker(tingData.playCpgt.heroHu.at(j).hu) == max){
                    playerHandJongs.at(i)->setTingJongHint(true,"gameview/hu_jong_hint_2.png");
                }else{
                    playerHandJongs.at(i)->setTingJongHint(true);
                }
            }
        }
    }
}

void PlayerHero::sendTingRequest(int poker){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getTingCommand(poker));
    this->stopTimeClockAnim();
}

void PlayerHero::actionQi(){
    if(NULL != getChildByTag(6689)){
        getChildByTag(6689)->removeFromParent();
    }
    for(auto var:playerHandJongs){
        var->setTingJongHint(false);
    }
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getGiveUpTingCommand());
    setIsAllowTouch(true);
    resetHandJongsY(NULL);
    GAMEDATA::getInstance()->setIsTingProcess(false);
}


void PlayerHero::drawHeroChi(HeroCpgRespData cpgResp, std::vector<string> chipai, PlayerBase* playerBase){
    updateSelectedInfo(NULL);
    if (cpgResp.result == 1 || cpgResp.result == 2){
        if(chipai.size() == 2){
            PlayerBase::showPlayerChi(chipai.at(0)+","+chipai.at(1), playerBase);
            Vector<Jong*> chiVector;
            //根据吃牌的位置显示,显示吃牌堆得形状
            Jong* jon = Jong::create();
            jon->showJong(herocpglandscape, playerBase->getCurrentJong()->getJongType());
            jon->setPosition(playerBase->getCurrentJong()->getPosition());
            this->addChild(jon, 3);
            chiVector.pushBack(jon);
            
            for (int i = 0; i < chipai.size(); i++){
                for (int j = 0; j < getSelfHandJongs().size(); j++){
                    if (atoi(chipai.at(i).c_str()) == getSelfHandJongs().at(j)->getJongType()){
                        getSelfHandJongs().at(j)->showJong(herocpgportrait, getSelfHandJongs().at(j)->getJongType());
                        chiVector.pushBack(getSelfHandJongs().at(j));
                        eraseHeroJong(getSelfHandJongs().at(j));
                        break;
                    }
                }
            }
            
            playerBase->removeLastJong();
            for (int k = 0; k < chiVector.size(); k++){
                MoveTo* mv = MoveTo::create(0.15f, Point(580 + (k==0?0:3+38 * k), 195));
                ScaleTo* scale = ScaleTo::create(0.15f, 0.6f);
                Spawn* sp = Spawn::create(mv, scale, NULL);
                chiVector.at(k)->setLocalZOrder(5);
                chiVector.at(k)->runAction(sp);
            }
            CallFunc* callFuc0 = CallFunc::create([=](){
                this->setHandPosX(this->getHandPosX() + JONG_WIDTH * 3);
                this->sortHandJongs(this->getHandPosX(), true);
            });
            DelayTime* delay = DelayTime::create(0.25f);
            PlayerCpgRecord record;
            record.type = CpgType::chi;
            record.pokersRecord = chiVector;
            this->playerCpgRecords.push_back(record);
            CallFunc* callFuc1 = CallFunc::create([=](){
                for (int k = 0; k < chiVector.size(); k++){
                    chiVector.at(k)->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
                    MoveTo* mv = MoveTo::create(0.15f, Point(getCpgPostionX() + (k==0? 0:(5+48 * k)), k==0?35:45));
                    ScaleTo* scale = ScaleTo::create(0.15f, 0.75f);
                    Spawn* sp = Spawn::create(mv, scale, NULL);
                    chiVector.at(k)->runAction(sp);
                }
                setCpgPostionX(getCpgPostionX()+170);
            });
            Sequence* mySe = Sequence::create(callFuc0, delay, callFuc1, NULL);
            runAction(mySe);
            
            //屏蔽不允许出的牌
            for(auto var:getSelfHandJongs()){
                if(var->getJongType() == atoi(cpgResp.forbit.c_str())){
                    var->showBackShadow(true);
                }
            }
            
        }
        //吃完后触发听牌
        if (cpgResp.result == 2 && cpgResp.playCpgt.ting != ""){
            log("吃听的牌: %s",cpgResp.playCpgt.ting.c_str());
            ((MahjongView*)getParent())->showTingGangControllPad(cpgResp.playCpgt);
        }else{
            setIsAllowPlay(true);
            startTimeClockAnim();
        }
    }
    else{
        stopTimeClockAnim();
    }
}


void PlayerHero::drawHeroPeng(HeroCpgRespData resp, PlayerBase* playerBase){
    
    if((GAMEDATA::getInstance()->getGameType() == 3 ||GAMEDATA::getInstance()->getGameType() == 4) && !UserData::getInstance()->isFangYan()){
        Audio::getInstance()->playSoundPengNormal(UserData::getInstance()->getGender());
        
    }else{
        Audio::getInstance()->playSoundPeng(UserData::getInstance()->getGender());
        
    }
    
    updateSelectedInfo(NULL);
    std::vector<string> pengpai = StringUtil::split(resp.playCpgt.peng, ",");
    if(pengpai.size() == 2){
        Vector<Jong*> pengVector;
        for (int i = 0; i < pengpai.size(); i++){
            for (int j = 0; j < getSelfHandJongs().size(); j++){
                if (atoi(pengpai.at(i).c_str()) == getSelfHandJongs().at(j)->getJongType()){
                    getSelfHandJongs().at(j)->showJong(herocpgportrait, getSelfHandJongs().at(j)->getJongType());
                    getSelfHandJongs().at(j)->setLocalZOrder(2);
                    pengVector.pushBack(getSelfHandJongs().at(j));
                    eraseHeroJong(getSelfHandJongs().at(j));
                    break;
                }
            }
        }
        Jong* jon = Jong::create();
        jon->showJong(herocpglandscape, playerBase->getCurrentJong()->getJongType());
        jon->setPosition(playerBase->getCurrentJong()->getPosition());
        this->addChild(jon, 1);
        //判断被碰牌玩家的位置
        pengVector.insert(0, jon);
        PlayerCpgRecord record;
        record.type = CpgType::peng;
        record.pokersRecord = pengVector;
        if(playerBase->getClientSeat()==ClientSeatId::left){
            record.pengDir = 0;
        }else if(playerBase->getClientSeat()==ClientSeatId::opposite){
            record.pengDir = 1;
        }else{
            record.pengDir = 2;
        }
        playerCpgRecords.push_back(record);
        CallFunc* action1 = CallFunc::create([=](){
            playerBase->removeLastJong();
            for (int m = 0; m < pengVector.size(); m++){
                MoveTo* mv;
                if(playerBase->getClientSeat()==ClientSeatId::left){
                    mv= MoveTo::create(0.15f, Point(580 + (m==0?0:3+38 * m), 195));
                    
                }else if(playerBase->getClientSeat()==ClientSeatId::opposite){
                    mv= MoveTo::create(0.15f, Point(580 + (m==0?20:3+38 * (m-1)), 195+(m==0?40:0)));
                }else{
                    mv= MoveTo::create(0.15f, Point(580 + (m==0?80:3+38 * (m-1)), 195));
                }
                ScaleTo* scale = ScaleTo::create(0.15f, 0.6f);
                Spawn* sp = Spawn::create(mv, scale, NULL);
                pengVector.at(m)->runAction(sp);
            }
            setHandPosX(getHandPosX() + JONG_WIDTH * 3);
            sortHandJongs(getHandPosX(), true);
        });
        DelayTime* delay = DelayTime::create(0.25f);
        CallFunc* action2 = CallFunc::create([=](){
            for (int k = 0; k < pengVector.size(); k++){
                MoveTo* mv;
                if(playerBase->getClientSeat()==ClientSeatId::left){
                    mv = MoveTo::create(0.15f, Point(getCpgPostionX() + (k==0? 0:(5+48 * k)), k==0?35:45));
                }else if(playerBase->getClientSeat()==ClientSeatId::opposite){
                    mv = MoveTo::create(0.15f, Point(getCpgPostionX() + (k==0? 32:(-48+48 * k)), k==0?90:45));
                }else{
                    mv = MoveTo::create(0.15f, Point(getCpgPostionX()+ (k==0? 105:(5+48 * (k-1))), k==0?35:45));
                }
                ScaleTo* scale = ScaleTo::create(0.15f, 0.75f);
                Spawn* sp = Spawn::create(mv, scale, NULL);
                pengVector.at(k)->runAction(sp);
            }
            if(playerBase->getClientSeat()==ClientSeatId::opposite){
                setCpgPostionX(getCpgPostionX()+115);
            }else{
                setCpgPostionX(getCpgPostionX()+170);
            }
        });
        Sequence* mySe = Sequence::create(action1, delay, action2, NULL);
        runAction(mySe);
    }
    if (resp.result == 2 && resp.playCpgt.ting != ""){
        log("碰听的牌: %s",resp.playCpgt.ting.c_str());
        ((MahjongView*)getParent())->showTingGangControllPad(resp.playCpgt);
    }else{
        setIsAllowPlay(true);
        startTimeClockAnim();
    }
}

void PlayerHero::drawHeroGang(HeroCpgRespData resp, PlayerBase* playerBase){
    if((GAMEDATA::getInstance()->getGameType() == 3 ||GAMEDATA::getInstance()->getGameType() == 4) && !UserData::getInstance()->isFangYan()){
        Audio::getInstance()->playSoundGangNormal(UserData::getInstance()->getGender());
        
    }else{
        Audio::getInstance()->playSoundGang(UserData::getInstance()->getGender());
        
    }
    updateSelectedInfo(NULL);
    if(resp.playCpgt.playerGang.at(0).flag == 0){
        //明杠
        std::vector<string> gangpai = StringUtil::split(resp.playCpgt.playerGang.at(0).gang, ",");
        Vector<Jong*> gangVector;
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < getSelfHandJongs().size(); j++){
                if (atoi(gangpai.at(0).c_str()) == getSelfHandJongs().at(j)->getJongType()){
                    getSelfHandJongs().at(j)->showJong(herocpgportrait, getSelfHandJongs().at(j)->getJongType());
                    gangVector.pushBack(getSelfHandJongs().at(j));
                    eraseHeroJong(getSelfHandJongs().at(j));
                    break;
                }
            }
        }
        Jong* jon = Jong::create();
        jon->showJong(herocpgportrait, playerBase->getCurrentJong()->getJongType());
        jon->setPosition(playerBase->getCurrentJong()->getPosition());
        addChild(jon, 5);
        gangVector.pushBack(jon);
        PlayerCpgRecord record;
        record.type = CpgType::gang;
        record.pokersRecord = gangVector;
        playerCpgRecords.push_back(record);
        CallFunc* action1 = CallFunc::create([=](){
            playerBase->removeLastJong();
            for (int m = 0; m < gangVector.size(); m++){
                MoveTo* mv = MoveTo::create(0.15f, Point(400 + 28 * m, 150));
                ScaleTo* scale = ScaleTo::create(0.15f, 0.6f);
                Spawn* sp = Spawn::create(mv, scale, NULL);
                gangVector.at(m)->runAction(sp);
            }
            setHandPosX(getHandPosX() + JONG_WIDTH * 3);
            sortHandJongs(getHandPosX(), true);
        });
        DelayTime* delay = DelayTime::create(0.25f);
        CallFunc* action2 = CallFunc::create([=](){
            for (int k = 0; k < gangVector.size(); k++){
                if (k != 3){
                    MoveTo* mv = MoveTo::create(0.15f, Point(getCpgPostionX() + 47 * k, 45));
                    ScaleTo* scale = ScaleTo::create(0.15f, 0.75f);
                    Spawn* sp = Spawn::create(mv, scale, NULL);
                    gangVector.at(k)->runAction(sp);
                }
                else{
                    MoveTo* mv = MoveTo::create(0.15f, Point(getCpgPostionX() + 47, 55));
                    ScaleTo* scale = ScaleTo::create(0.15f, 0.75f);
                    Spawn* sp = Spawn::create(mv, scale, NULL);
                    gangVector.at(k)->setLocalZOrder(4);
                    gangVector.at(k)->runAction(sp);
                }
            }
            setCpgPostionX(getCpgPostionX()+170);
        });
        
        DelayTime* delay2 = DelayTime::create(0.3f);
        
        CallFunc* action3 = CallFunc::create([=](){
            if(GAMEDATA::getInstance()->getGameType() == 3||GAMEDATA::getInstance()->getGameType() == 4){
                int clientId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), resp.playCpgt.sId);
                if( clientId == ClientSeatId::left){
                    auto arrow = Sprite::create("gameview/hu_jong_hint.png");
                    arrow->setPosition(gangVector.at(0)->getPosition().x+40,gangVector.at(0)->getPosition().y+15);
                    arrow->setRotation(90);
                    addChild(arrow,20);
                }else if( clientId == ClientSeatId::opposite){
                    auto arrow = Sprite::create("gameview/hu_jong_hint.png");
                    arrow->setPosition(gangVector.at(0)->getPosition().x+40,gangVector.at(0)->getPosition().y+15);
                    arrow->setRotation(180);
                    addChild(arrow,20);
                }else if( clientId == ClientSeatId::right){
                    auto arrow = Sprite::create("gameview/hu_jong_hint.png");
                    arrow->setPosition(gangVector.at(0)->getPosition().x+40,gangVector.at(0)->getPosition().y+15);
                    arrow->setRotation(270);
                    addChild(arrow,20);
                }
            }
        });
        
        auto spriteAnim = Sprite::create();
        addChild(spriteAnim);
        spriteAnim->runAction(Sequence::create(action1, delay, action2,delay2,action3, NULL));
        
        
        if (resp.result == 2 && resp.playCpgt.ting != ""){
            PlayerCpgtData tingData;
            tingData.ting = resp.playCpgt.ting;
            ((MahjongView*)getParent())->showTingGangControllPad(tingData);
        }
        
    }else{
        std::vector<string> gangpai = StringUtil::split(resp.playCpgt.playerGang.at(0).gang, ",");
        Vector<Jong*> gangVector;
        if (resp.playCpgt.playerGang.at(0).flag == 2){
            for(int j=0; j<playerHandJongs.size();j++){
                if(playerHandJongs.at(j)->getJongType() == atoi(gangpai.at(0).c_str())){
                    gangVector.pushBack(playerHandJongs.at(j));
                    eraseHeroJong(playerHandJongs.at(j));
                }
            }
            for (int i = 0; i < this->playerCpgRecords.size(); i++){
                if (playerCpgRecords.at(i).type == CpgType::peng){
                    if (atoi(gangpai.at(0).c_str()) == playerCpgRecords.at(i).pokersRecord.at(0)->getJongType()){
                        playerCpgRecords.at(i).type = penggang;
                        playerCpgRecords.at(i).pokersRecord.pushBack(gangVector);
                        gangVector.at(0)->showJong(herocpgportrait, gangVector.at(0)->getJongType());
                        Point pos;
                        if(playerCpgRecords.at(i).pengDir ==0){
                            pos = playerCpgRecords.at(i).pokersRecord.at(1)->getPosition();
                        }else if(playerCpgRecords.at(i).pengDir ==0){
                            pos = Point((playerCpgRecords.at(i).pokersRecord.at(1)->getPosition().x+playerCpgRecords.at(i).pokersRecord.at(2)->getPosition().x)/2,playerCpgRecords.at(i).pokersRecord.at(1)->getPosition().y);
                        }else{
                            pos = playerCpgRecords.at(i).pokersRecord.at(2)->getPosition();
                        }
                        MoveTo* mv = MoveTo::create(0.2f, Point(pos.x, pos.y + 10));
                        ScaleTo* sc = ScaleTo::create(0.2f, 0.75f);
                        Spawn* spawn = Spawn::create(mv, sc, NULL);
                        gangVector.at(0)->setLocalZOrder(4);
                        gangVector.at(0)->runAction(Sequence::create(spawn, CallFunc::create([=](){
                            sortHandJongs(getHandPosX(), false);
                        }), NULL) );
                    }
                }
            }
        }
        else{
            for (int j = 0; j < getSelfHandJongs().size(); j++){
                if (atoi(gangpai.at(0).c_str()) == getSelfHandJongs().at(j)->getJongType()){
                    gangVector.pushBack(getSelfHandJongs().at(j));
                }
            }
            for (int i = 0; i < gangVector.size(); i++){
                eraseHeroJong(gangVector.at(i));
            }
            PlayerCpgRecord record;
            record.type = CpgType::angang;
            record.pokersRecord = gangVector;
            playerCpgRecords.push_back(record);
            CallFunc* action1 = CallFunc::create([=](){
                for (int m = 0; m < gangVector.size(); m++){
                    gangVector.at(m)->showJong(herocpgportrait, gangVector.at(m)->getJongType());
                    MoveTo* mv = MoveTo::create(0.15f, Point(400 + 28 * m, 150));
                    ScaleTo* scale = ScaleTo::create(0.15f, 0.6f);
                    Spawn* sp = Spawn::create(mv, scale, NULL);
                    gangVector.at(m)->runAction(sp);
                }
                setHandPosX(getHandPosX() + JONG_WIDTH * 3);
                sortHandJongs(getHandPosX(), true);
            });
            DelayTime* delay = DelayTime::create(0.25f);
            CallFunc* action2 = CallFunc::create([=](){
                for (int k = 0; k < gangVector.size(); k++){
                    if (k != 3){
                        MoveTo* mv = MoveTo::create(0.15f, Point(getCpgPostionX()+ 47 * k, 45));
                        ScaleTo* scale = ScaleTo::create(0.15f, 0.75f);
                        Spawn* sp = Spawn::create(mv, scale, NULL);
                        gangVector.at(k)->runAction(sp);
                    }
                    else{
                        MoveTo* mv = MoveTo::create(0.15f, Point(getCpgPostionX() + 47, 55));
                        ScaleTo* scale = ScaleTo::create(0.15f, 0.75f);
                        Spawn* sp = Spawn::create(mv, scale, NULL);
                        gangVector.at(k)->runAction(sp);
                        gangVector.at(k)->setLocalZOrder(4);
                    }
                }
                setCpgPostionX(getCpgPostionX()+170);
            });
            CallFunc* action3 = CallFunc::create([=](){
                for (int k = 0; k < gangVector.size() - 1; k++){
                    gangVector.at(k)->showJong(herodeal, gangVector.at(k)->getJongType(),false);
                    gangVector.at(k)->setScale(0.8);
                }
            });
            Sequence* mySe = Sequence::create(action1, delay, action2, delay, action3, NULL);
            runAction(mySe);
        }
        setIsAllowTouch(true);
    }
}

void PlayerHero::drawHeroChiMingpai(HeroCpgRespData cpgResp, std::vector<string> chipai, PlayerBase* playerBase){
    updateSelectedInfo(NULL);
    if (cpgResp.result == 1 || cpgResp.result == 2){
        PlayerBase::showPlayerChi(chipai.at(0)+","+chipai.at(1), playerBase);
        Vector<Jong*> chiVector;
        //根据吃牌的位置显示,显示吃牌堆得形状
        Jong* jon = Jong::create();
        jon->showJong(herocpglandscape, playerBase->getCurrentJong()->getJongType());
        jon->setPosition(playerBase->getCurrentJong()->getPosition());
        addChild(jon, 3);
        chiVector.pushBack(jon);
        
        for (int i = 0; i < chipai.size(); i++){
            for (int j = 0; j < getSelfHandJongs().size(); j++){
                if (atoi(chipai.at(i).c_str()) == getSelfHandJongs().at(j)->getJongType()){
                    getSelfHandJongs().at(j)->showJong(herocpgportrait, getSelfHandJongs().at(j)->getJongType());
                    chiVector.pushBack(getSelfHandJongs().at(j));
                    eraseHeroJong(getSelfHandJongs().at(j));
                    break;
                }
            }
        }
        
        playerBase->removeLastJong();
        
        setHandPosX(getHandPosX() + JONG_WIDTH * 3);
        sortHandJongs(getHandPosX(), true);
        
        PlayerCpgRecord record;
        record.type = CpgType::chi;
        record.pokersRecord = chiVector;
        playerCpgRecords.push_back(record);
        for (int k = 0; k < chiVector.size(); k++){
            chiVector.at(k)->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
            Point mv = Point(getCpgPostionX() + (k==0? 0:(5+48 * k)), k==0?35:45);
            chiVector.at(k)->setScale(0.75f);
            chiVector.at(k)->setPosition(mv);
        }
        setCpgPostionX(getCpgPostionX()+170);
        
        //屏蔽不允许出的牌
        for(auto var:getSelfHandJongs()){
            if(var->getJongType() == atoi(cpgResp.forbit.c_str())){
                var->showBackShadow(true);
            }
        }
        //吃完后触发听牌
        if (cpgResp.result == 2 && cpgResp.playCpgt.ting != ""){
            log("吃听的牌: %s",cpgResp.playCpgt.ting.c_str());
            PlayerCpgtData tingData;
            tingData.ting = cpgResp.playCpgt.ting;
            ((MahjongView*)getParent())->showTingGangControllPad(tingData);
        }else{
            setIsAllowPlay(true);
        }
    }
    else{
        stopTimeClockAnim();
    }
}


void PlayerHero::drawHeroPengMingpai(HeroCpgRespData resp, PlayerBase* playerBase){
    
    if((GAMEDATA::getInstance()->getGameType() == 3 ||GAMEDATA::getInstance()->getGameType() == 4) && !UserData::getInstance()->isFangYan()){
        Audio::getInstance()->playSoundPengNormal(UserData::getInstance()->getGender());
        
    }else{
        Audio::getInstance()->playSoundPeng(UserData::getInstance()->getGender());
        
    }
    updateSelectedInfo(NULL);
    std::vector<string> pengpai = StringUtil::split(resp.playCpgt.peng, ",");
    Vector<Jong*> pengVector;
    for (int i = 0; i < pengpai.size(); i++){
        for (int j = 0; j < getSelfHandJongs().size(); j++){
            if (atoi(pengpai.at(i).c_str()) == getSelfHandJongs().at(j)->getJongType()){
                getSelfHandJongs().at(j)->showJong(herocpgportrait, getSelfHandJongs().at(j)->getJongType());
                getSelfHandJongs().at(j)->setLocalZOrder(2);
                pengVector.pushBack(getSelfHandJongs().at(j));
                eraseHeroJong(getSelfHandJongs().at(j));
                break;
            }
        }
    }
    Jong* jon = Jong::create();
    jon->showJong(herocpglandscape, playerBase->getCurrentJong()->getJongType());
    jon->setPosition(playerBase->getCurrentJong()->getPosition());
    this->addChild(jon, 1);
    //判断被碰牌玩家的位置
    pengVector.insert(0, jon);
    PlayerCpgRecord record;
    record.type = CpgType::peng;
    record.pokersRecord = pengVector;
    if(playerBase->getClientSeat()==ClientSeatId::left){
        record.pengDir = 0;
    }else if(playerBase->getClientSeat()==ClientSeatId::opposite){
        record.pengDir = 1;
    }else{
        record.pengDir = 2;
    }
    playerCpgRecords.push_back(record);
    CallFunc* action1 = CallFunc::create([=](){
        playerBase->removeLastJong();
        for (int m = 0; m < pengVector.size(); m++){
            MoveTo* mv;
            if(playerBase->getClientSeat()==ClientSeatId::left){
                mv= MoveTo::create(0.15f, Point(580 + (m==0?0:3+38 * m), 195));
                
            }else if(playerBase->getClientSeat()==ClientSeatId::opposite){
                mv= MoveTo::create(0.15f, Point(580 + (m==0?20:3+38 * (m-1)), 195+(m==0?40:0)));
            }else{
                mv= MoveTo::create(0.15f, Point(580 + (m==0?80:3+38 * (m-1)), 195));
            }
            ScaleTo* scale = ScaleTo::create(0.15f, 0.6f);
            Spawn* sp = Spawn::create(mv, scale, NULL);
            pengVector.at(m)->runAction(sp);
        }
        setHandPosX(getHandPosX() + JONG_WIDTH * 3);
        sortHandJongs(getHandPosX(), true);
    });
    DelayTime* delay = DelayTime::create(0.25f);
    CallFunc* action2 = CallFunc::create([=](){
        for (int k = 0; k < pengVector.size(); k++){
            MoveTo* mv;
            if(playerBase->getClientSeat()==ClientSeatId::left){
                mv = MoveTo::create(0.15f, Point(getCpgPostionX() + (k==0? 0:(5+48 * k)), k==0?35:45));
            }else if(playerBase->getClientSeat()==ClientSeatId::opposite){
                mv = MoveTo::create(0.15f, Point(getCpgPostionX() + (k==0? 32:(-48+48 * k)), k==0?90:45));
            }else{
                mv = MoveTo::create(0.15f, Point(getCpgPostionX()+ (k==0? 105:(5+48 * (k-1))), k==0?35:45));
            }
            ScaleTo* scale = ScaleTo::create(0.15f, 0.75f);
            Spawn* sp = Spawn::create(mv, scale, NULL);
            pengVector.at(k)->runAction(sp);
        }
        if(playerBase->getClientSeat()==ClientSeatId::opposite){
            setCpgPostionX(getCpgPostionX()+115);
        }else{
            setCpgPostionX(getCpgPostionX()+170);
        }
    });
    Sequence* mySe = Sequence::create(action1, delay, action2, NULL);
    runAction(mySe);
    
    if (resp.result == 2 && resp.playCpgt.ting != ""){
        log("碰听的牌: %s",resp.playCpgt.ting.c_str());
        ((MahjongView*)getParent())->showTingGangControllPad(resp.playCpgt);
    }else{
        setIsAllowPlay(true);
        startTimeClockAnim();
    }
}

void PlayerHero::drawHeroGangMingpai(HeroCpgRespData resp, PlayerBase* playerBase){
    if((GAMEDATA::getInstance()->getGameType() == 3 ||GAMEDATA::getInstance()->getGameType() == 4) && !UserData::getInstance()->isFangYan()){
        Audio::getInstance()->playSoundGangNormal(UserData::getInstance()->getGender());
        
    }else{
        Audio::getInstance()->playSoundGang(UserData::getInstance()->getGender());
        
    }
    updateSelectedInfo(NULL);
    if(resp.playCpgt.playerGang.at(0).flag == 0){
        std::vector<string> gangpai = StringUtil::split(resp.playCpgt.playerGang.at(0).gang, ",");
        Vector<Jong*> gangVector;
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < getSelfHandJongs().size(); j++){
                if (atoi(gangpai.at(0).c_str()) == getSelfHandJongs().at(j)->getJongType()){
                    getSelfHandJongs().at(j)->showJong(herocpgportrait, getSelfHandJongs().at(j)->getJongType());
                    gangVector.pushBack(getSelfHandJongs().at(j));
                    eraseHeroJong(getSelfHandJongs().at(j));
                    break;
                }
            }
        }
        Jong* jon = Jong::create();
        jon->showJong(herocpgportrait, playerBase->getCurrentJong()->getJongType());
        jon->setPosition(playerBase->getCurrentJong()->getPosition());
        this->addChild(jon, 5);
        gangVector.pushBack(jon);
        PlayerCpgRecord record;
        record.type = CpgType::gang;
        record.pokersRecord = gangVector;
        playerCpgRecords.push_back(record);
        setHandPosX(getHandPosX() + JONG_WIDTH * 3);
        sortHandJongs(getHandPosX(), true);
        for (int k = 0; k < gangVector.size(); k++){
            if (k != 3){
                gangVector.at(k)->setPosition(Point(getCpgPostionX() + 47 * k, 45));
                gangVector.at(k)->setScale( 0.75f);
            }
            else{
                gangVector.at(k)->setLocalZOrder(4);
                gangVector.at(k)->setPosition(Point(getCpgPostionX() + 47, 55));
                gangVector.at(k)->setScale( 0.75f);
            }
        }
        if(GAMEDATA::getInstance()->getGameType() == 3||GAMEDATA::getInstance()->getGameType() == 4){
            int clientId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), resp.playCpgt.sId);
            if( clientId == ClientSeatId::left){
                auto arrow = Sprite::create("gameview/hu_jong_hint.png");
                arrow->setPosition(gangVector.at(0)->getPosition().x+40,gangVector.at(0)->getPosition().y+15);
                arrow->setRotation(90);
                addChild(arrow,20);
            }else if( clientId == ClientSeatId::opposite){
                auto arrow = Sprite::create("gameview/hu_jong_hint.png");
                arrow->setPosition(gangVector.at(0)->getPosition().x+40,gangVector.at(0)->getPosition().y+15);
                arrow->setRotation(180);
                addChild(arrow,20);
            }else if( clientId == ClientSeatId::right){
                auto arrow = Sprite::create("gameview/hu_jong_hint.png");
                arrow->setPosition(gangVector.at(0)->getPosition().x+40,gangVector.at(0)->getPosition().y+15);
                arrow->setRotation(270);
                addChild(arrow,20);
            }
        }
        
        setCpgPostionX(getCpgPostionX()+170);
        
        if (resp.result == 2 && resp.playCpgt.ting != ""){
            PlayerCpgtData tingData;
            tingData.ting = resp.playCpgt.ting;
            ((MahjongView*)getParent())->showTingGangControllPad(tingData);
        }
        
    }else{
        std::vector<string> gangpai = StringUtil::split(resp.playCpgt.playerGang.at(0).gang, ",");
        Vector<Jong*> gangVector;
        if (resp.playCpgt.playerGang.at(0).flag == 2){
            for(int j=0; j<playerHandJongs.size();j++){
                if(playerHandJongs.at(j)->getJongType() == atoi(gangpai.at(0).c_str())){
                    gangVector.pushBack(playerHandJongs.at(j));
                    eraseHeroJong(playerHandJongs.at(j));
                }
            }
            for (int i = 0; i < this->playerCpgRecords.size(); i++){
                if (playerCpgRecords.at(i).type == CpgType::peng){
                    if (atoi(gangpai.at(0).c_str()) == playerCpgRecords.at(i).pokersRecord.at(0)->getJongType()){
                        playerCpgRecords.at(i).type = penggang;
                        playerCpgRecords.at(i).pokersRecord.pushBack(gangVector);
                        gangVector.at(0)->showJong(herocpgportrait, gangVector.at(0)->getJongType());
                        Point pos;
                        if(playerCpgRecords.at(i).pengDir ==0){
                            pos = playerCpgRecords.at(i).pokersRecord.at(1)->getPosition();
                        }else if(playerCpgRecords.at(i).pengDir ==0){
                            pos = Point((playerCpgRecords.at(i).pokersRecord.at(1)->getPosition().x+playerCpgRecords.at(i).pokersRecord.at(2)->getPosition().x)/2,playerCpgRecords.at(i).pokersRecord.at(1)->getPosition().y);
                        }else{
                            pos = playerCpgRecords.at(i).pokersRecord.at(2)->getPosition();
                        }
                        gangVector.at(0)->setLocalZOrder(4);
                        gangVector.at(0)->setPosition(Point(pos.x, pos.y + 10));
                        gangVector.at(0)->setScale(0.75f);
                        sortHandJongs(getHandPosX(), false);
                    }
                }
            }
        }
        else{
            for (int j = 0; j < getSelfHandJongs().size(); j++){
                if (atoi(gangpai.at(0).c_str()) == getSelfHandJongs().at(j)->getJongType()){
                    gangVector.pushBack(getSelfHandJongs().at(j));
                }
            }
            for (int i = 0; i < gangVector.size(); i++){
                eraseHeroJong(gangVector.at(i));
            }
            PlayerCpgRecord record;
            record.type = CpgType::angang;
            record.pokersRecord = gangVector;
            playerCpgRecords.push_back(record);
            setHandPosX(getHandPosX() + JONG_WIDTH * 3);
            sortHandJongs(getHandPosX(), true);
            for (int k = 0; k < gangVector.size(); k++){
                if (k != 3){
                    gangVector.at(k)->setPosition(Point(getCpgPostionX()+ 47 * k, 45));
                    gangVector.at(k)->setScale(0.75f);
                }
                else{
                    gangVector.at(k)->setLocalZOrder(4);
                    gangVector.at(k)->setPosition(Point(getCpgPostionX() + 47, 55));
                    gangVector.at(k)->setScale(0.75f);
                }
            }
            setCpgPostionX(getCpgPostionX()+170);
            for (int k = 0; k < gangVector.size() - 1; k++){
                gangVector.at(k)->showJong(herodeal, gangVector.at(k)->getJongType(),false);
                gangVector.at(k)->setScale(0.8);
            }
        }
        setIsAllowTouch(true);
    }
}


void PlayerHero::recoverHua(int hua){
    setHuaNum(hua);
    showPlayerHua(getHuaNum());
}

void PlayerHero::recoverPlayed(std::string played){
    playerPlayedJongs.clear();
    if(played == ""){
        return;
    }
    vector<std::string>  playeds = StringUtil::split(played, ",");
    for (int i = 0; i < playeds.size(); i++){
        Jong* jong = Jong::create();
        jong->showJong(heroplayed, atoi(playeds.at(i).c_str()));
        jong->setScale(1.0f);
        jong->setPosition(getHeroPlayedJongsPos((int)playerPlayedJongs.size()));
        addChild(jong);
        playerPlayedJongs.pushBack(jong);
    }
}


void PlayerHero::recoverCpg(vector<PlayerChiData> chi,vector<PlayerPengData> peng,vector<PlayerGangData> gang,std::string angang){
    setCpgPostionX(JONG_POS_START_X);
    setHandPosX(JONG_POS_START_X);
    for(auto var:playerCpgRecords){
        for(auto poker:var.pokersRecord){
            poker->removeFromParent();
        }
    }
    playerCpgRecords.clear();
    if(chi.size()>0){
        for(int i=0;i<chi.size();i++){
            PlayerCpgRecord record;
            record.type = CpgType::chi;
            vector<std::string> chiPoker  = StringUtil::split(chi.at(i).chi, ",");
            for(int m=0;m<chiPoker.size();m++){
                if(m != 0){
                    if(chiPoker.at(m)==chi.at(i).poker){
                        swap(chiPoker.at(m), chiPoker.at(0));
                    }
                }
            }
            for (int j = 0; j < chiPoker.size();j++){
                Jong* jong = Jong::create();
                jong->setScale(0.75f);
                jong->showJong(j==0?herocpglandscape:herocpgportrait, atoi(chiPoker.at(j).c_str()));
                jong->setPosition(Point(getCpgPostionX() + (j==0? 0:(5+48 * j)), j==0?35:45));
                this->addChild(jong,10);
                record.pokersRecord.pushBack(jong);
            }
            playerCpgRecords.push_back(record);
            setHandPosX(getHandPosX() + JONG_WIDTH * 3);
            setCpgPostionX(getCpgPostionX()+170);
        }
    }
    if(peng.size()>0){
        for(int i=0;i<peng.size();i++){
            PlayerCpgRecord record;
            record.type = CpgType::peng;
            for(int j=0;j<3;j++){
                Jong* jong = Jong::create();
                jong->setScale(0.75f);
                jong->showJong(j==0?herocpglandscape:herocpgportrait, atoi(peng.at(i).peng.c_str()));
                int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), atoi(peng.at(i).peId.c_str()));
                if(seatId == ClientSeatId::left){
                    jong->setPosition(Point(getCpgPostionX() + (j==0? 0:(5+48 * j)), j==0?35:45));
                }else if(seatId == ClientSeatId::opposite){
                    jong->setPosition(Point(getCpgPostionX() + (j==0? 32:(-48+48 * j)), j==0?90:45));
                }else if(seatId == ClientSeatId::right){
                    jong->setPosition(Point(getCpgPostionX()+ (j==0? 105:(5+48 * (j-1))), j==0?35:45));
                }
                addChild(jong,10);
                record.pokersRecord.pushBack(jong);
            }
            playerCpgRecords.push_back(record);
            setHandPosX(getHandPosX() + JONG_WIDTH * 3);
            setCpgPostionX(getCpgPostionX()+170);
        }
    }
    if(gang.size()>0){
        for(int i=0;i<gang.size();i++){
            PlayerCpgRecord record;
            record.type = CpgType::gang;
            for(int j=0;j<4;j++){
                Jong* jong = Jong::create();
                jong->setScale(0.75f);
                jong->showJong(herocpgportrait, atoi(gang.at(i).gang.c_str()));
                if (j == 3){
                    jong->setPosition(Point(getCpgPostionX() + 47, 55));
                }
                else{
                    jong->setPosition(Point(getCpgPostionX() + 47*j, 45));
                }
                this->addChild(jong,10);
                record.pokersRecord.pushBack(jong);
            }
            if(atoi(gang.at(i).gaId.c_str()) != 0){
                if(GAMEDATA::getInstance()->getGameType() == 3||GAMEDATA::getInstance()->getGameType() == 4){
                    int clientId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(),atoi(gang.at(i).gaId.c_str()));
                    if( clientId == ClientSeatId::left){
                        auto arrow = Sprite::create("gameview/hu_jong_hint.png");
                        arrow->setPosition(getCpgPostionX()+47,55);
                        arrow->setRotation(90);
                        addChild(arrow,20);
                    }else if( clientId == ClientSeatId::opposite){
                        auto arrow = Sprite::create("gameview/hu_jong_hint.png");
                        arrow->setPosition(getCpgPostionX()+47,55);
                        arrow->setRotation(180);
                        addChild(arrow,20);
                    }else if( clientId == ClientSeatId::right){
                        auto arrow = Sprite::create("gameview/hu_jong_hint.png");
                        arrow->setPosition(getCpgPostionX()+47,55);
                        arrow->setRotation(270);
                        addChild(arrow,20);
                    }
                }
            }
            playerCpgRecords.push_back(record);
            setHandPosX(getHandPosX() + JONG_WIDTH * 3);
            setCpgPostionX(getCpgPostionX()+170);
        }
    }
    if(angang.size()>0){
        PlayerCpgRecord record;
        record.type = CpgType::angang;
        std::vector<std::string> gangpai = StringUtil::split(angang, ",");
        for(auto var : gangpai){
            for(int j=0;j<4;j++){
                Jong* jong = Jong::create();
                jong->setScale(0.75f);
                if (j == 3){
                    jong->showJong(herocpgportrait,atoi(var.c_str()));
                    jong->setPosition(Point(getCpgPostionX() + 47, 55));
                }
                else{
                    jong->showJong(herodeal,atoi(var.c_str()),false);
                    jong->setPosition(Point(getCpgPostionX() + 47*j, 45));
                }
                this->addChild(jong,10);
                record.pokersRecord.pushBack(jong);
            }
            playerCpgRecords.push_back(record);
            setHandPosX(getHandPosX() + JONG_WIDTH * 3);
            setCpgPostionX(getCpgPostionX()+170);
        }
    }
}

void PlayerHero::recoverHand(std::string hand,std::string lastpoker){
    
    for(auto var:playerHandJongs){
        var->removeFromParent();
    }
    playerHandJongs.clear();
    vector<std::string>  hands = StringUtil::split(hand, ",");
    for (int i = 0; i < hands.size(); i++)
    {
        Jong* jong = Jong::create();
        jong->showJong(herohand, atoi(hands.at(i).c_str()));
        if(GAMEDATA::getInstance()->getLastGameDataBackup().turn ==GAMEDATA::getInstance()->getHeroSeatId()&&getHandPosX() + JONG_WIDTH * i>JONG_POS_13_X){
            jong->setPosition(Point(getHandPosX() + JONG_WIDTH * i+10, JONG_POS_Y));
            setIsAllowPlay(true);
            startTimeClockAnim();
        }else{
            jong->setPosition(Point(getHandPosX() + JONG_WIDTH * i, JONG_POS_Y));
        }
        addChild(jong);
        playerHandJongs.pushBack(jong);
    }
    currentJong = playerHandJongs.at(playerHandJongs.size()-1);
    //    for(auto protect:playerHandJongs){
    //        if(protect->getJongType() == JongEnum::hz){
    //            protect->showBackShadow(true);
    //        }
    //    }
}

void PlayerHero::updateMingpai(Vector<Jong*> myPlayerHandJongs,Vector<Jong*> myPlayerPlayedJongs,std::vector<PlayerCpgRecord> myPlayerCpgRecords){
    for(int j=0; j< playerPlayedJongs.size();j++){
        playerPlayedJongs.at(j)->removeFromParent();
    }
    playerPlayedJongs = myPlayerPlayedJongs;
    for(int a = 0;a<myPlayerPlayedJongs.size();a++){
        addChild(myPlayerPlayedJongs.at(a));
        myPlayerPlayedJongs.at(a)->setPosition(getHeroPlayedJongsPos(a));
    }
    for(int b = 0;b<playerCpgRecords.size();b++){
        for(int c=0;c<playerCpgRecords.at(b).pokersRecord.size();c++){
            playerCpgRecords.at(b).pokersRecord.at(c)->removeFromParent();
        }
    }
    playerCpgRecords.clear();
    playerCpgRecords = myPlayerCpgRecords;
    for(int e = 0;e<myPlayerCpgRecords.size();e++){
        for(int f=0;f<myPlayerCpgRecords.at(e).pokersRecord.size();f++){
            myPlayerCpgRecords.at(e).pokersRecord.at(f)->removeFromParent();
            addChild(myPlayerCpgRecords.at(e).pokersRecord.at(f));
        }
    }
    
    setCpgPostionX((int)myPlayerCpgRecords.size()*170+JONG_POS_START_X);
    setHandPosX(myPlayerCpgRecords.size()*JONG_WIDTH*3+JONG_POS_START_X);
    for(int k=0; k< playerHandJongs.size();k++){
        playerHandJongs.at(k)->removeFromParent();
    }
    playerHandJongs = myPlayerHandJongs;
    for (int i = 0; i < playerHandJongs.size(); i++) {
        playerHandJongs.at(i)->showJong(herohand, playerHandJongs.at(i)->getJongType());
        playerHandJongs.at(i)->setScale(1.0f);
        addChild(playerHandJongs.at(i));
        if (i == MAX_JONG_NUM - 1){
            playerHandJongs.at(i)->setPosition(Point(getHandPosX(), JONG_POS_Y));
        }
        else{
            playerHandJongs.at(i)->setPosition(Point(getHandPosX() + JONG_WIDTH * i, JONG_POS_Y));
        }
    }
    showCurrentPlayedJongIcon(false);
    hideCurrentBigJong();
}
