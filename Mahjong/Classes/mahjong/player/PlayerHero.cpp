#include "mahjong/player/PlayerHero.h"
#include "mahjong/core/MahjongView.h"
#include "mahjong/utils/StringUtil.h"
#include "mahjong/anim/HuaAnim.hpp"
#include "mahjong/utils/GameConfig.h"
#include "server/NetworkManage.h"
#include "server/CommandManage.h"
#include "server/MsgConfig.h"
#include "server/SocketDataManage.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#import "payment/ios/IOSBridge.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "payment/android/CallAndroidMethod.h"
#endif


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
    if(NULL != getChildByTag(9998)){
        if(GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom && atoi(GAMEDATA::getInstance()->getFriendOpenRoomResp().prjucount.c_str())>0){
            getChildByTag(9998)->setVisible(false);
        }else{
            getChildByTag(9998)->setVisible(b);
        }
    }
}

bool PlayerHero::onTouchBegan(Touch *touch, Event *event) {
    if (!this->getIsAllowTouch() || GAMEDATA::getInstance()->getIsTingState()){
        return false;
    }
    selectJong = getTouchJong(touch);
    if(NULL != selectJong){
        updateSelectedInfo(selectJong);
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
                virtualJong->setPosition(touch->getLocation());
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
            updateSelectedInfo(selectJong);
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
        }
        else{
            if (doubleClickJong == getTouchJong(touch)){
                Jong* jong = Jong::create();
                jong->setPosition(doubleClickJong->getPosition());
                jong->showJong(herohand, doubleClickJong->getJongType());
                addChild(jong);
                playPokerByHand(jong);
                selectJong = doubleClickJong;
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
    BezierTo *actionMove = BezierTo::create(0.5f, bezier);
    ScaleTo* scale = ScaleTo::create(0.5f, 0.45f);
    Spawn* spa = Spawn::create(actionMove, scale, NULL);
    CallFunc* callback = CallFunc::create([=](){
        if (!GAMEDATA::getInstance()->getIsTingState()
            && !GAMEDATA::getInstance()->getIsTingProcess()
            && !GAMEDATA::getInstance()->getIsTrusteeship()){
            sendPokerRequest(jong->getJongType());
        }
        else if (GAMEDATA::getInstance()->getIsTingProcess()){
            sendTingRequest(jong->getJongType());
            GAMEDATA::getInstance()->setIsTingProcess(false);
        }
        jong->showJong(heroplayed, jong->getJongType());
        jong->setScale(1.0f);
        playerPlayedJongs.pushBack(jong);
        isAllowPlay = false;
        resetHandJongsY(jong);
        virtualJong = NULL;
    });
    CallFunc* callback2 = CallFunc::create([=](){
        showCurrentPlayedJongIcon(true);
    });
    
    Sequence* seq = Sequence::create(spa, callback, callback2, NULL);
    jong->runAction(seq);
}


void PlayerHero::drawPlayerHero() {
    std::vector<std::string> strvce = GAMEDATA::getInstance()->getHeroJongs();
    for (int t = 0; t < strvce.size(); t++) {
        if (t < -1){
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
        biaoji->setVisible(false);
        playedIcon->setPosition(biaoji->getPosition());
        playedIcon->setVisible(true);
    }
}

Vector<Jong*> PlayerHero::getSelfHandJongs(){
    return this->playerHandJongs;
}

void PlayerHero::resetHandJongsY(Jong* jong) {
    for (int i = 0; i < playerHandJongs.size(); i++) {
        if (playerHandJongs.at(i) != jong)
            playerHandJongs.at(i)->setPosition(
                                               Point(playerHandJongs.at(i)->getPositionX(), JONG_POS_Y));
    }
}

void PlayerHero::drawReady(bool ready){
    if (!ready){
        MenuItemImage* image = MenuItemImage::create("gameview/ready_1.png", "gameview/ready_2.png", CC_CALLBACK_0(PlayerHero::readyGo, this));
        auto start = Menu::create(image, NULL);
        start->setTag(888);
        start->setPosition(Point(640, 200));
        this->addChild(start);
    }else{
        if (NULL != getChildByTag(888)){
            getChildByTag(888)->setVisible(false);
        }
        if(GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom && atoi(GAMEDATA::getInstance()->getFriendOpenRoomResp().prjucount.c_str())==0 && !GAMEDATA::getInstance()->getIsPlaying()&&GAMEDATA::getInstance()->getFangZhuId()==UserData::getInstance()->getPoxiaoId()){
            MenuItemImage* inviteImage = MenuItemImage::create("gameview/invite_friend_1.png", "gameview/invite_friend_2.png", CC_CALLBACK_0(PlayerHero::inviteWechatFriend, this));
            auto invite = Menu::create(inviteImage, NULL);
            invite->setPosition(Point(640, 160));
            invite->setTag(9998);
            addChild(invite);
        }
        setIsReady(true);
    }
}


void PlayerHero::readyGo(){
    if (NULL != getChildByTag(888)){
        getChildByTag(888)->setVisible(false);
    }
    setIsReady(true);
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getReadyCommmand());
}


void PlayerHero::inviteWechatFriend(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CallAndroidMethod::getInstance()->shareToWeChat(WECHAT_SHARE_FRIEND_URL,StringUtils::format("房号%s就等侬了!",GAMEDATA::getInstance()->getFriendOpenRoomResp().prid.c_str()),SHARE_TEXT_3,false);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    IOSBridge::getInstance()->doWechatShareWeb(WECHAT_SHARE_FRIEND_URL,StringUtils::format("房号%s就等侬了!",GAMEDATA::getInstance()->getFriendOpenRoomResp().prid.c_str()),SHARE_TEXT_3,0);
#endif
}


void PlayerHero::sendPokerRequest(int poker){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getPlayPokerCommmand(poker));
}


Point PlayerHero::getHeroPlayedJongsPos(int index) {
    int row = index / 10;
    int line = index % 10;
    Point originPos = Point(475, 275);
    if (row == 0) {
        return Point(originPos.x + 35 * line, originPos.y);
    }
    else  {
        return Point(originPos.x + 35 * line, originPos.y - 42);
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
                    auto move = MoveTo::create(0.4f,
                                               Point(playerHandJongs.at(j)->getPositionX() - JONG_WIDTH,
                                                     JONG_POS_Y));
                    playerHandJongs.at(j)->runAction(move);
                }
            }
            if (!isMoved){
                isMoved = true;
                needBezier = false;
                auto move = MoveTo::create(0.4f,
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
                    auto move = MoveTo::create(0.4f,
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
        BezierTo *actionMove = BezierTo::create(0.5f, bezier);
        currentJong->runAction(actionMove);
    }
    
    setIsAllowPlay(false);
    selectJong->removeFromParent();
    eraseHeroJong(selectJong);
    auto delay = DelayTime::create(0.6f);
    auto callback = CallFunc::create([=](){
        sortHandJongs(getHandPosX(), true);
    });
    auto sequence = Sequence::create(delay, callback, NULL);
    this->runAction(sequence);
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
        //        SocketDataManage::getInstance()->resumeMsg();
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
        }, 0.8f, (int)rejong.poker.size()-1, 0,"huahuahua");
        
        schedule([=](float dt){
            int bankId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), GAMEDATA::getInstance()->getCurrentBank());
            if (bankId == ClientSeatId::hero){
                isAllowPlay = true;
            }
            sortHandJongs(this->getHandPosX(), true);
        }, 0, 0, 0.8f*rejong.poker.size(),"huadelay");
    }
}

void PlayerHero::playerTurnReplace(PlayerTurnData data){
    huaIndex = 0;
    std::vector<std::string> replace = StringUtil::split(data.replace, ",");
    if (data.replace != "" && replace.size() > 0){
        Jong* turnJong = Jong::create();
        turnJong->setVisible(false);
        turnJong->showJong(herohand, data.poker);
        addChild(turnJong);
        playerHandJongs.pushBack(turnJong);
        schedule([=](float dt){
            std::vector<Jong*> needReplace;
            needReplace.clear();
            Jong* jong = Jong::create();
            jong->showJong(herohand, atoi(replace.at(huaIndex).c_str()));
            jong->setVisible(false);
            addChild(jong);
            needReplace.push_back(jong);
            HuaAnim* huaAnim = HuaAnim::create(needReplace, GAMEDATA::getInstance()->getHeroSeatId(),CallFunc::create([=](){
                setHuaNum(getHuaNum()+(int)needReplace.size());
                showPlayerHua(getHuaNum());
            }));
            addChild(huaAnim,100);
            huaIndex++;
        }, 0.8f, (int)replace.size()-1, 0,"hua2poker");
        schedule([=](float dt){
            turnJong->setVisible(true);
            settleHandJongs(getHandPosX());
            currentJong = turnJong;
            setIsAllowPlay(true);
            if(data.hastinggang){
                EventCustom tingEvent(MSG_HERO_TING_GANG);
                Director::getInstance()->getEventDispatcher()->dispatchEvent(&tingEvent);
            }
        }, 0, 0, 0.8f*replace.size(),"hua2pokerdelay");
    }
    else{
        Jong* jong = Jong::create();
        jong->showJong(herohand, data.poker);
        addChild(jong);
        playerHandJongs.pushBack(jong);
        currentJong = jong;
        settleHandJongs(getHandPosX());
        if(data.hastinggang){
            EventCustom tingEvent(MSG_HERO_TING_GANG);
            Director::getInstance()->getEventDispatcher()->dispatchEvent(&tingEvent);
        }
        if (!(GAMEDATA::getInstance()->getIsTingState())){
            setIsAllowPlay(true);
        }
    }
    doubleClickJong = NULL;
}

void PlayerHero:: drawPlayedJong(int type){
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
            BezierTo *actionMove = BezierTo::create(0.5f, bezier);
            ScaleTo* scale = ScaleTo::create(0.5f, 0.45f);
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


void PlayerHero::eraseHeroJong(Jong* jong){
    this->playerHandJongs.eraseObject(jong);
}

void PlayerHero::removePlayedIcon(){
    playedIcon->setVisible(false);
}

void PlayerHero::doEventTimeOver(int type){
    ((MahjongView*)getParent())->hideTingGangControllPad();
    //type 吃碰杠倒计时
    if (type == 1){
        if(GAMEDATA::getInstance()->getPlayerTurn().seatId == GAMEDATA::getInstance()->getHeroSeatId()){
            startTimeClockAnim();
            setIsAllowPlay(true);
        }
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getGiveUpCpgCommmand());
    }
    //听牌倒计时
    else if (type == 2){
        //是否听牌选择界面倒计时结束
        if (!GAMEDATA::getInstance()->getIsTingProcess()){
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getGiveUpTingCommand());
            setIsAllowTouch(true);
            setIsAllowPlay(true);
            if(SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(),
                                           GAMEDATA::getInstance()->getPlayerTurn().seatId)  ==
               ClientSeatId::hero){
                startTimeClockAnim();
                setIsAllowPlay(true);
            }
        }
        
    }
}


void PlayerHero::actionTing(){
    setIsAllowTouch(true);
    GAMEDATA::getInstance()->setIsTingProcess(true);
    HeroCpgRespData tingData = GAMEDATA::getInstance()->getHeroCpgResp();
    std::vector<string> tingpai = StringUtil::split(tingData.ting, ",");
    log("提示玩家可以听的牌:%s",tingData.ting.c_str());
    for (int i = 0; i < tingpai.size(); i++){
        for (int j = 0; j < playerHandJongs.size(); j++){
            if (atoi(tingpai.at(i).c_str()) == playerHandJongs.at(j)->getJongType()){
                playerHandJongs.at(j)->setPosition(playerHandJongs.at(j)->getPosition().x, playerHandJongs.at(j)->getPosition().y + 40);
            }
        }
    }
    startTimeClockAnim(20, 2);
}

void PlayerHero::sendTingRequest(int poker){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getTingCommand(poker));
    this->stopTimeClockAnim();
}

void PlayerHero::actionQi(){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getGiveUpTingCommand());
    setIsAllowTouch(true);
}


void PlayerHero::drawHeroChi(HeroCpgRespData cpgResp, std::vector<string> chipai, PlayerBase* playerBase){
    updateSelectedInfo(NULL);
    if (cpgResp.result == 1 || cpgResp.result == 2){
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
            MoveTo* mv = MoveTo::create(0.2f, Point(580 + (k==0?0:3+38 * k), 195));
            ScaleTo* scale = ScaleTo::create(0.2f, 0.6f);
            Spawn* sp = Spawn::create(mv, scale, NULL);
            chiVector.at(k)->setLocalZOrder(5);
            chiVector.at(k)->runAction(sp);
        }
        CallFunc* callFuc0 = CallFunc::create([=](){
            this->setHandPosX(this->getHandPosX() + JONG_WIDTH * 3);
            this->sortHandJongs(this->getHandPosX(), true);
        });
        DelayTime* delay = DelayTime::create(0.5f);
        PlayerCpgRecord record;
        record.type = CpgType::chi;
        record.pokersRecord = chiVector;
        this->playerCpgRecords.push_back(record);
        CallFunc* callFuc1 = CallFunc::create([=](){
            for (int k = 0; k < chiVector.size(); k++){
                chiVector.at(k)->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
                MoveTo* mv = MoveTo::create(0.2f, Point(getCpgPostionX() + (k==0? 0:(5+48 * k)), k==0?35:45));
                ScaleTo* scale = ScaleTo::create(0.2f, 0.75f);
                Spawn* sp = Spawn::create(mv, scale, NULL);
                chiVector.at(k)->runAction(sp);
            }
            setCpgPostionX(getCpgPostionX()+170);
        });
        Sequence* mySe = Sequence::create(callFuc0, delay, callFuc1, NULL);
        runAction(mySe);
        //吃完后触发听牌
        if (cpgResp.result == 2 && cpgResp.ting != ""){
            log("吃听的牌: %s",cpgResp.ting.c_str());
            PlayerCpgtData tingData;
            tingData.ting = cpgResp.ting;
            GAMEDATA::getInstance()->setPlayerCpgt(tingData);
            ((MahjongView*)getParent())->showTingGangControllPad();
        }else{
            setIsAllowPlay(true);
            startTimeClockAnim();
        }
    }
    else{
        stopTimeClockAnim();
    }
}


void PlayerHero::drawHeroPeng(HeroCpgRespData resp, PlayerCpgtData cpg, PlayerBase* playerBase){
    Audio::getInstance()->playSoundPeng(UserData::getInstance()->getGender());
    updateSelectedInfo(NULL);
    std::vector<string> pengpai = StringUtil::split(cpg.peng, ",");
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
                mv= MoveTo::create(0.2f, Point(580 + (m==0?0:3+38 * m), 195));
                
            }else if(playerBase->getClientSeat()==ClientSeatId::opposite){
                mv= MoveTo::create(0.2f, Point(580 + (m==0?20:3+38 * (m-1)), 195+(m==0?40:0)));
            }else{
                mv= MoveTo::create(0.2f, Point(580 + (m==0?80:3+38 * (m-1)), 195));
            }
            ScaleTo* scale = ScaleTo::create(0.2f, 0.6f);
            Spawn* sp = Spawn::create(mv, scale, NULL);
            pengVector.at(m)->runAction(sp);
        }
        setHandPosX(getHandPosX() + JONG_WIDTH * 3);
        sortHandJongs(getHandPosX(), true);
    });
    DelayTime* delay = DelayTime::create(0.4f);
    CallFunc* action2 = CallFunc::create([=](){
        for (int k = 0; k < pengVector.size(); k++){
            MoveTo* mv;
            if(playerBase->getClientSeat()==ClientSeatId::left){
                mv = MoveTo::create(0.2f, Point(getCpgPostionX() + (k==0? 0:(5+48 * k)), k==0?35:45));
            }else if(playerBase->getClientSeat()==ClientSeatId::opposite){
                mv = MoveTo::create(0.2f, Point(getCpgPostionX() + (k==0? 32:(-48+48 * k)), k==0?90:45));
            }else{
                mv = MoveTo::create(0.2f, Point(getCpgPostionX()+ (k==0? 105:(5+48 * (k-1))), k==0?35:45));
            }
            ScaleTo* scale = ScaleTo::create(0.2f, 0.75f);
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
    
    if (resp.result == 2 && resp.ting != ""){
        PlayerCpgtData tingData;
        tingData.ting = resp.ting;
        GAMEDATA::getInstance()->setPlayerCpgt(tingData);
        ((MahjongView*)getParent())->showTingGangControllPad();
    }else{
        setIsAllowPlay(true);
        startTimeClockAnim();
    }
}

void PlayerHero::drawHeroGang(HeroCpgRespData resp, PlayerCpgtData cpg, PlayerBase* playerBase){
    Audio::getInstance()->playSoundGang(UserData::getInstance()->getGender());
    updateSelectedInfo(NULL);
    if(cpg.flag == 0){
        std::vector<string> gangpai = StringUtil::split(cpg.gang, ",");
        Vector<Jong*> gangVector;
        for (int i = 0; i < gangpai.size(); i++){
            for (int j = 0; j < getSelfHandJongs().size(); j++){
                if (atoi(gangpai.at(i).c_str()) == getSelfHandJongs().at(j)->getJongType()){
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
        CallFunc* action1 = CallFunc::create([=](){
            playerBase->removeLastJong();
            for (int m = 0; m < gangVector.size(); m++){
                MoveTo* mv = MoveTo::create(0.2f, Point(400 + 28 * m, 150));
                ScaleTo* scale = ScaleTo::create(0.2f, 0.6f);
                Spawn* sp = Spawn::create(mv, scale, NULL);
                gangVector.at(m)->runAction(sp);
            }
            setHandPosX(getHandPosX() + JONG_WIDTH * 3);
            sortHandJongs(getHandPosX(), true);
        });
        DelayTime* delay = DelayTime::create(0.4f);
        CallFunc* action2 = CallFunc::create([=](){
            for (int k = 0; k < gangVector.size(); k++){
                if (k != 3){
                    MoveTo* mv = MoveTo::create(0.2f, Point(getCpgPostionX() + 47 * k, 45));
                    ScaleTo* scale = ScaleTo::create(0.2f, 0.75f);
                    Spawn* sp = Spawn::create(mv, scale, NULL);
                    gangVector.at(k)->runAction(sp);
                }
                else{
                    MoveTo* mv = MoveTo::create(0.2f, Point(getCpgPostionX() + 47, 55));
                    ScaleTo* scale = ScaleTo::create(0.2f, 0.75f);
                    Spawn* sp = Spawn::create(mv, scale, NULL);
                    gangVector.at(k)->setLocalZOrder(4);
                    gangVector.at(k)->runAction(sp);
                }
            }
            setCpgPostionX(getCpgPostionX()+170);
        });
        auto spriteAnim = Sprite::create();
        addChild(spriteAnim);
        spriteAnim->runAction(Sequence::create(action1, delay, action2, NULL));
        if (resp.result == 2 && resp.ting != ""){
            PlayerCpgtData tingData;
            tingData.ting = resp.ting;
            GAMEDATA::getInstance()->setPlayerCpgt(tingData);
            ((MahjongView*)getParent())->showTingGangControllPad();
        }
        
    }else{
        std::vector<string> gangpai = StringUtil::split(cpg.gang, ",");
        Vector<Jong*> gangVector;
        if (cpg.flag == 2){
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
                        MoveTo* mv = MoveTo::create(0.3f, Point(pos.x, pos.y + 10));
                        ScaleTo* sc = ScaleTo::create(0.3f, 0.75f);
                        Spawn* spawn = Spawn::create(mv, sc, NULL);
                        gangVector.at(0)->setLocalZOrder(4);
                        gangVector.at(0)->runAction(Sequence::create(spawn, CallFunc::create([=](){
                            this->sortHandJongs(this->getHandPosX(), false);
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
                    MoveTo* mv = MoveTo::create(0.2f, Point(400 + 28 * m, 150));
                    ScaleTo* scale = ScaleTo::create(0.2f, 0.6f);
                    Spawn* sp = Spawn::create(mv, scale, NULL);
                    gangVector.at(m)->runAction(sp);
                }
                this->setHandPosX(this->getHandPosX() + JONG_WIDTH * 3);
                this->sortHandJongs(this->getHandPosX(), true);
            });
            DelayTime* delay = DelayTime::create(0.3f);
            CallFunc* action2 = CallFunc::create([=](){
                for (int k = 0; k < gangVector.size(); k++){
                    if (k != 3){
                        MoveTo* mv = MoveTo::create(0.2f, Point(getCpgPostionX()+ 47 * k, 45));
                        ScaleTo* scale = ScaleTo::create(0.2f, 0.75f);
                        Spawn* sp = Spawn::create(mv, scale, NULL);
                        gangVector.at(k)->runAction(sp);
                    }
                    else{
                        MoveTo* mv = MoveTo::create(0.2f, Point(getCpgPostionX() + 47, 55));
                        ScaleTo* scale = ScaleTo::create(0.2f, 0.75f);
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
            this->runAction(mySe);
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
}
