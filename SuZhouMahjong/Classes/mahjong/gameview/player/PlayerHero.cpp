#include "mahjong/gameview/player/PlayerHero.h"
#include "mahjong/gameview/suzhou/normal/SuZhouView.h"
#include "mahjong/gameview/hongzhong/normal/HongZhongView.hpp"
#include "mahjong/gameview/baida/normal/BaiDaView.h"
#include "mahjong/gameview/fanpai/normal/FanPaiView.hpp"
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
#include "mahjong/common/utils/UrlEncode.hpp"
#include "mahjong/common/dialog/prompt/HintDialog.hpp"

bool PlayerHero::init() {
    if (!PlayerBase::init()) {
        return false;
    }
    initData();
    return true;
}

void PlayerHero::initData() {
    setHandPosX(JONG_POS_START_X);
    setIsAllowPlay(false);
    setIsAllowTouch(true);
    playerHandJongs.clear();
    playerHuaJongs.clear();
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
}

void PlayerHero::removeLastJong(){
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


bool PlayerHero::onTouchBegan(Touch *touch, Event *event) {
    if (getIsAllowTouch() && getIsAllowPlay()){
        selectJong = getTouchJong(touch);
        if(NULL != selectJong&&(!selectJong->getIsProtected()||GAMEDATA::getInstance()->getGameType()==7)){
            //选中了手牌，记录选中的位置
            preTouchPosition = touch->getLocation();
            updateSelectedInfo(selectJong);
            if(isAllowPlay){
                selectJong->setPositionY(120);
                for(auto var : heroHuData){
                    if(var.poker == selectJong->getJongType()){
                        if(NULL != getChildByTag(6689)){
                            getChildByTag(6689)->removeFromParent();
                        }
                        HuPaiHintLayer* huPai =  HuPaiHintLayer::create(var,this);
                        huPai->setTag(6689);
                        addChild(huPai,5);
                        startTimeClockAnim(15, 2);
                    }
                }
            }
        }else{
            selectJong = NULL;
        }
        return true;
    }
    return false;
}

void PlayerHero::onTouchMoved(Touch *touch, Event *event) {
    //选中的牌根据手指移动,Y轴需要加40
    if(NULL != selectJong && getIsAllowPlay()){
        selectJong->setPosition(Point(touch->getLocation().x,touch->getLocation().y+JONG_SEL_POS_Y-JONG_POS_Y));
    }
    
}

void PlayerHero::onTouchEnded(Touch *touch, Event *event) {
    //更具y轴移动的距离来判断用户是否出牌
    if (getIsAllowPlay()) {
        //滑动出牌
        if(NULL != selectJong && selectJong->getIsProtected()){
            //询问是否要出牌
            HintDialog* dia = HintDialog::create("打出百搭牌后本局无法胡牌,是否要打出", [=](Ref* ref){
                playPokerByHand(selectJong);
                arrangeHandJongs();
                if(NULL != getChildByTag(1024)){
                    getChildByTag(1024)->removeFromParent();
                }
            },[=](Ref* ref){
                sortHandJongs(getHandPosX(), true);
                if(NULL != getChildByTag(1024)){
                   getChildByTag(1024)->removeFromParent();
                }
            });
            dia->setTag(1024);
            addChild(dia,350);
        }else if(NULL != selectJong && selectJong->getJongType() >= JongEnum::zhong&&(GAMEDATA::getInstance()->getGameType() == 1||GAMEDATA::getInstance()->getGameType()==2||(GAMEDATA::getInstance()->getGameType()==5 && selectJong->getJongType() != JongEnum::baida)||(GAMEDATA::getInstance()->getGameType()==6 && selectJong->getJongType() != JongEnum::baida))){
            playPokerByHand(selectJong);
        }else if(NULL != selectJong && selectJong->getPositionY()>=(JONG_SEL_POS_Y+12)){
            playPokerByHand(selectJong);
            arrangeHandJongs();
        }else{
            //双击出牌
            resetHandJongsX(selectJong);
            if(NULL == doubleClickJong){
                //第一次点击
                if(NULL != selectJong){
                    if(selectJong->getIsProtected()){
                        //在保护中的牌，不可以选中
                        doubleClickJong = NULL;
                    }else{
                        doubleClickJong = selectJong;
                        selectJong->setPositionY(JONG_SEL_POS_Y);
                    }
                }
            }else{
                //牌已经点击过一次
                if(doubleClickJong == getTouchJong(touch)){
                    playPokerByHand(doubleClickJong);
                    arrangeHandJongs();
                    doubleClickJong = NULL;
                }else{
                    doubleClickJong = getTouchJong(touch);
                }
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





void PlayerHero::drawPlayerHero(std::string hand) {
    std::vector<std::string> strvce = StringUtil::split(hand, ",");
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

Vector<Jong*> PlayerHero::getSelfHandJongs(){
    return this->playerHandJongs;
}

void PlayerHero::resetHandJongsY(Jong* jong){
    for (int i = 0; i < playerHandJongs.size(); i++) {
        if (playerHandJongs.at(i) != jong){
            float x = getHandPosX()+JONG_WIDTH*i;
            playerHandJongs.at(i)->setPosition(Point(x>=JONG_POS_13_X?NEW_JONG_POS_X:x, JONG_POS_Y));
        }
    }
}

void PlayerHero::resetHandJongsX(Jong* jong){
    for (int i = 0; i < playerHandJongs.size(); i++) {
        float x = getHandPosX()+JONG_WIDTH*i;
        if (playerHandJongs.at(i) != jong){
            playerHandJongs.at(i)->setPosition(Point(x>=JONG_POS_13_X?NEW_JONG_POS_X:x,JONG_POS_Y));
        }else{
            playerHandJongs.at(i)->setPosition(Point(x>=JONG_POS_13_X?NEW_JONG_POS_X:x,JONG_SEL_POS_Y));
        }
        
    }
}

void PlayerHero:: showInviteButton(){
    if(GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom && atoi(GAMEDATA::getInstance()->getFriendOpenRoomResp().prjucount.c_str())==0 && !GAMEDATA::getInstance()->getIsPlaying()&&GAMEDATA::getInstance()->getFangZhuId()==UserData::getInstance()->getPoxiaoId()){
        MenuItemImage* inviteImage = MenuItemImage::create("gameview/invite_friend_1.png", "gameview/invite_friend_2.png", CC_CALLBACK_0(PlayerHero::inviteWechatFriend, this));
        auto invite = Menu::create(inviteImage, NULL);
        invite->setPosition(Point(640, 235));
        invite->setTag(9998);
        addChild(invite);
    }
}

void PlayerHero::hideInviteButton(){
    if(NULL != getChildByTag(9998)){
        if(GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom && atoi(GAMEDATA::getInstance()->getFriendOpenRoomResp().prjucount.c_str())>0){
            getChildByTag(9998)->setVisible(false);
        }
    }
}

void PlayerHero::drawReady(bool ready){
  
    if (!ready && !GAMEDATA::getInstance()->getContinueAgain()){
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
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendBDReadyCommand());
    }else if(GAMEDATA::getInstance()->getGameType() == 7){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendFPReadyCommand());
    }
}


void PlayerHero::inviteWechatFriend(){
    std::string gameName = "";
    std::string roomtype = ChineseWord("room_info_0");
    std::string gameRule = "";
    roomtype += ChineseWord("room_info_1");
    roomtype += GAMEDATA::getInstance()->getFriendOpenRoomResp().prjushu;
    if(GAMEDATA::getInstance()->getGameType() == 1 || GAMEDATA::getInstance()->getGameType() == 2){
        gameName = "苏州麻将";
        gameRule = "苏州麻将";
        if(GAMEDATA::getInstance()->getPrivateDiLing() == "1"){
            roomtype += ChineseWord("room_info_2");
            gameRule += " 滴零";
        }
        if(GAMEDATA::getInstance()->getPrivateHaoQi() == "1"){
            roomtype += ChineseWord("room_info_3");
            gameRule += " 豪七";
        }
    }else if(GAMEDATA::getInstance()->getGameType() == 3 || GAMEDATA::getInstance()->getGameType() == 4){
        gameName = "红中麻将";
        gameRule = "红中麻将";
        if(GAMEDATA::getInstance()->getFanMaType() == "4"){
            roomtype += ChineseWord("room_info_13");
            gameRule += " 159红中算码";
        }else if(GAMEDATA::getInstance()->getFanMaType() == "3"){
            roomtype += ChineseWord("room_info_14");
            gameRule += " 159码";
        }else if (GAMEDATA::getInstance()->getFanMaType() == "1"){
            roomtype += ChineseWord("room_info_15");
            gameRule += " 1码";
        }
        roomtype += ChineseWord("room_info_16");
        roomtype += StringUtils::format("%s",GAMEDATA::getInstance()->getHZDiFen().c_str());
    }else  if(GAMEDATA::getInstance()->getGameType() == 5 || GAMEDATA::getInstance()->getGameType() == 6){
        gameName = "百搭麻将";
        gameRule = "百搭麻将";
        if(GAMEDATA::getInstance()->getPrivateZiMo() == "1"){
            roomtype += ChineseWord("room_info_4");
            gameRule += " 只能自摸胡";
        }
        if(GAMEDATA::getInstance()->getPrivateQiDui() == "1"){
            roomtype += ChineseWord("room_info_5");
            gameRule += " 可以胡七对";
        }
        if(GAMEDATA::getInstance()->getPrivateFanPai() == "2"){
            roomtype += ChineseWord("room_info_7");
            gameRule += " 翻2个";
        }else if(GAMEDATA::getInstance()->getPrivateFanPai() == "4"){
            roomtype += ChineseWord("room_info_8");
            gameRule += " 翻4个";
        }else if(GAMEDATA::getInstance()->getPrivateFanPai() == "6"){
            roomtype += ChineseWord("room_info_9");
            gameRule += " 翻6个";
        }else{
            roomtype += ChineseWord("room_info_6");
            gameRule += " 不翻牌";
        }
    }else  if(GAMEDATA::getInstance()->getGameType() == 7 || GAMEDATA::getInstance()->getGameType() == 8){
        gameName = "翻牌百搭";
        gameRule = "翻牌麻将";
        roomtype += ChineseWord("room_info_16");
        roomtype += StringUtils::format("%s",GAMEDATA::getInstance()->getFPDiFen().c_str());
    }
    if(GAMEDATA::getInstance()->getIsPayWayAA()){
        roomtype += ",AA支付房卡";
    }else{
        roomtype += ",房主支付房卡";
    }
    UrlEncode* enco = new UrlEncode();
    std::string rule = enco->encode(gameRule);
    std::string zhongwen = enco->encode("等待开始");
    roomtype += StringUtils::format(",缺%d人",4-(int)GAMEDATA::getInstance()->getPlayersInfo().size());
    std::string shareUrl = GAMEDATA::getInstance()->getMahjongShareData3().url;
    shareUrl = StringUtils::format("%s%s&fjh=%s&fjzt=%s&js=%s&rs=%s&yxgz=%s",shareUrl.c_str(),UserData::getInstance()->getPoxiaoId().c_str(),GAMEDATA::getInstance()->getFriendOpenRoomResp().prid.c_str(),zhongwen.c_str(),GAMEDATA::getInstance()->getFriendOpenRoomResp().prjushu.c_str(),StringUtils::format("%d",(int)GAMEDATA::getInstance()->getPlayersInfo().size()).c_str(),rule.c_str());
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CallAndroidMethod::getInstance()->shareToWeChat(shareUrl,StringUtils::format("跳跳%s 房号:%s %s",gameName.c_str(),GAMEDATA::getInstance()->getFriendOpenRoomResp().prid.c_str(),GAMEDATA::getInstance()->getMahjongShareData3().head.c_str()),StringUtils::format("%s %s",roomtype.c_str(),GAMEDATA::getInstance()->getMahjongShareData3().head.c_str()),false);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CallIOSMethod::getInstance()->doWechatShareWeb(shareUrl,StringUtils::format("跳跳%s 房号:%s %s",gameName.c_str(),GAMEDATA::getInstance()->getFriendOpenRoomResp().prid.c_str(),GAMEDATA::getInstance()->getMahjongShareData3().head.c_str()),StringUtils::format("%s %s",roomtype.c_str(),GAMEDATA::getInstance()->getMahjongShareData3().head.c_str()),0);
#endif
    
}


void PlayerHero::sendPokerRequest(int poker){
    //    log("向服务端发送出牌请求 %d",poker);
    if(GAMEDATA::getInstance()->getGameType() == 1){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getPlayPokerCommmand(poker));
    }else if(GAMEDATA::getInstance()->getGameType() == 3){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getHZPlayPokerCommand(StringUtils::format("%d",poker)));
    }else if(GAMEDATA::getInstance()->getGameType() == 5){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getBDPlayPokeCommand(poker));
    }else if(GAMEDATA::getInstance()->getGameType() == 7){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getFPPlayPokeCommand(poker));
    }
}


Point PlayerHero::getHeroPlayedNormalPos(int index) {
    int row;
    int line;
    Point originPos;
    if(GAMEDATA::getInstance()->getMyGameModel() == GameModel::TWOPLAYER){
        row = index / 13;
        line = index % 13;
        originPos = Point(422, 275);
    }else{
        row = index / 10;
        line = index % 10;
        originPos = Point(475, 275);
    }
    if (row == 0) {
        return Point(originPos.x + 35 * line, originPos.y);
    }
    else  {
        return Point(originPos.x + 35 * line, originPos.y - 42*row);
    }
    
}


Point PlayerHero::getHeroPlayedHuaPos(int index){
    
    int row = index / 9;
    int line = index % 9;
    Point originPos = Point(195, 165);
    if (row == 0) {
        return Point(originPos.x + 19 * line, originPos.y);
    }
    else  {
        return Point(originPos.x + 19 * line, originPos.y + 23*row);
    }
    
}

Point  PlayerHero::getMultiplePosition(Point p1,Point p2,float xi){
    float dis1 =  distance(p1, p2);//计算2点间的距离
    float dis2 = dis1*xi;//根据倍率计算新的距离
    float new_x = p1.x + dis2*(p2.x-p1.x)/dis1;
    float new_y = p1.y + dis2*(p2.y-p1.y)/dis1;
    return Point(new_x,new_y);
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
    if(GAMEDATA::getInstance()->getGameType() == 5||GAMEDATA::getInstance()->getGameType() == 7){
        //将队列中符合要求的牌移除队列
        int baida = JongEnum::baida;
        if(GAMEDATA::getInstance()->getGameType() == 7){
            baida = atoi(GAMEDATA::getInstance()->getBaiDaPoker().c_str());
        }
        Vector<Jong*> temp1;//临时队列
        vector<Jong*>::iterator it;
        for (it = playerHandJongs.begin(); it != playerHandJongs.end();)
        {
            Jong* pla = *it;
            if (pla->getJongType() == baida){
                temp1.pushBack(pla);
                it = playerHandJongs.erase(it);
            }
            else{
                ++it;
            }
        }
        for (int i = 0; i < playerHandJongs.size() - 1; i++) {
            for (int j = (int)playerHandJongs.size() - 1; j > i; j--) {
                if (playerHandJongs.at(j)->getJongType() < playerHandJongs.at(j - 1)->getJongType()) {
                    playerHandJongs.swap(playerHandJongs.at(j), playerHandJongs.at(j - 1));
                }
            }
        }
        for (auto var :temp1) {
            playerHandJongs.insert(0, var);
        }
    }else{
        for (int i = 0; i < size - 1; i++) {
            for (int j = size - 1; j > i; j--) {
                if (playerHandJongs.at(j)->getJongType() < playerHandJongs.at(j - 1)->getJongType()) {
                    playerHandJongs.swap(playerHandJongs.at(j), playerHandJongs.at(j - 1));
                }
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

void PlayerHero::arrangeHandJongs() {
    setIsAllowPlay(false);
    sortHandJongs(getHandPosX(), true);
}


void PlayerHero::addTouchListener() {
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(PlayerHero::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(PlayerHero::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(PlayerHero::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);
}

void PlayerHero::checkSuZhouHeroHandPoker(){
    //判断有无花牌
    bool hua = false;
    for(int i=0; i<playerHandJongs.size();i++){
        if(playerHandJongs.at(i)->getJongType() >= (int)JongEnum::zhong){
            hua = true;
        }
    }
    //锁住非花手牌
    if(hua){
        for(int i=0; i<playerHandJongs.size();i++){
            if(playerHandJongs.at(i)->getJongType()<(int)JongEnum::zhong){
                playerHandJongs.at(i)->showBackShadow(true);
            }
        }
    }else{
        for(int i=0; i<playerHandJongs.size();i++){
            playerHandJongs.at(i)->showBackShadow(false);
        }
    }
}

void PlayerHero::checkHongZhongHeroHandPoker(){
    for(int i=0; i<playerHandJongs.size();i++){
        if(playerHandJongs.size() == 2 && playerHandJongs.at(0)->getJongType() ==(int)JongEnum::hz && playerHandJongs.at(1)->getJongType() ==(int)JongEnum::hz){
            playerHandJongs.at(i)->showBackShadow(false);
        }else{
            if(playerHandJongs.at(i)->getJongType()==(int)JongEnum::hz ){
                playerHandJongs.at(i)->showBackShadow(true);
            }else{
                playerHandJongs.at(i)->showBackShadow(false);
            }
        }
    }
}

void PlayerHero::checkBaiDaHeroHandPoker(){
    //判断有无花牌
    bool hua = false;
    for(int i=0; i<playerHandJongs.size();i++){
        if(playerHandJongs.at(i)->getJongType() >= (int)JongEnum::zhong && playerHandJongs.at(i)->getJongType()!=(int)JongEnum::baida){
            hua = true;
        }
    }
    //锁住非花手牌
    if(hua){
        for(int i=0; i<playerHandJongs.size();i++){
            if(playerHandJongs.at(i)->getJongType()<(int)JongEnum::zhong || playerHandJongs.at(i)->getJongType()==(int)JongEnum::baida){
                playerHandJongs.at(i)->showBackShadow(true);
            }
        }
    }else{
        for(int i=0; i<playerHandJongs.size();i++){
            if(playerHandJongs.size() == 2 && playerHandJongs.at(0)->getJongType() ==(int)JongEnum::baida && playerHandJongs.at(1)->getJongType() ==(int)JongEnum::baida){
                playerHandJongs.at(i)->showBackShadow(false);
            }else{
                if(playerHandJongs.at(i)->getJongType()==(int)JongEnum::baida ){
                    playerHandJongs.at(i)->showBackShadow(true);
                }else{
                    playerHandJongs.at(i)->showBackShadow(false);
                }
            }
        }
    }
}

void PlayerHero::checkFanPaiHeroHandPoker(int poker){
    for(int i=0; i<playerHandJongs.size();i++){
        if(playerHandJongs.size() == 2 && playerHandJongs.at(0)->getJongType() ==poker && playerHandJongs.at(1)->getJongType() ==poker){
            playerHandJongs.at(i)->showBackShadow(false);
        }else{
            if(playerHandJongs.at(i)->getJongType()== poker ){
                playerHandJongs.at(i)->showBackShadow(true);
            }else{
                playerHandJongs.at(i)->showBackShadow(false);
            }
        }
    }
}

void PlayerHero::playerTurnToPlay(PlayerTurnData data){
    setIsAllowPlay(true);
    PlayerCpgtData cpgData = data.cpgData;
    if(data.poker>=0 && data.handNum>getSelfHandJongs().size()){
        Jong* jong = Jong::create();
        jong->showJong(herohand, data.poker);
        addChild(jong);
        playerHandJongs.pushBack(jong);
        currentJong = jong;
        settleHandJongs(getHandPosX());
    }
    showHuPaiTiShi(data.cpgData.heroHu);
    if(GAMEDATA::getInstance()->getGameType() == 1 && (data.cpgData.hu == 1 || data.hastinggang)){
        ((SuZhouView*)getParent())->showSuZHouControllPad(cpgData);
    }else if(GAMEDATA::getInstance()->getGameType() == 3 && (data.cpgData.hu == 1 || data.hastinggang)){
        ((HongZhongView*)getParent())->showHongZhongControllPad(cpgData);
    }else if(GAMEDATA::getInstance()->getGameType() == 5 && (data.cpgData.hu == 1 || data.hastinggang)){
        ((BaiDaView*)getParent())->showBaiDaControllPad(cpgData);
    }else if(GAMEDATA::getInstance()->getGameType() == 7 && (data.cpgData.hu == 1 || data.hastinggang)){
        ((FanPaiView*)getParent())->showBaiDaControllPad(cpgData);
    }
    if(GAMEDATA::getInstance()->getGameType() == 1){
        checkSuZhouHeroHandPoker();
    }else if(GAMEDATA::getInstance()->getGameType() == 3){
        checkHongZhongHeroHandPoker();
    }else if(GAMEDATA::getInstance()->getGameType() == 5){
        checkBaiDaHeroHandPoker();
    }else if(GAMEDATA::getInstance()->getGameType() == 7){
        checkFanPaiHeroHandPoker(atoi(GAMEDATA::getInstance()->getBaiDaPoker().c_str()));
    }
}

void PlayerHero::playerTurnReplaceMingpai(PlayerTurnData data){
    Jong* jong = Jong::create();
    jong->showJong(herohand, data.poker);
    addChild(jong);
    playerHandJongs.pushBack(jong);
    currentJong = jong;
    settleHandJongs(getHandPosX());
    setIsAllowPlay(true);
    if(GAMEDATA::getInstance()->getGameType() == 1 && (data.cpgData.hu == 1 || data.hastinggang)){
        ((SuZhouView*)getParent())->showSuZHouControllPad(data.cpgData);
    }else if(GAMEDATA::getInstance()->getGameType() == 3 && (data.cpgData.hu == 1 || data.hastinggang)){
        ((HongZhongView*)getParent())->showHongZhongControllPad(data.cpgData);
    }else if(GAMEDATA::getInstance()->getGameType() == 5 && (data.cpgData.hu == 1 || data.hastinggang)){
        ((BaiDaView*)getParent())->showBaiDaControllPad(data.cpgData);
    }
    if(GAMEDATA::getInstance()->getGameType() == 1){
        checkSuZhouHeroHandPoker();
    }else if(GAMEDATA::getInstance()->getGameType() == 3){
        checkHongZhongHeroHandPoker();
    }else if(GAMEDATA::getInstance()->getGameType() == 5){
        checkBaiDaHeroHandPoker();
    }
}

void PlayerHero:: drawPlayedJong(int type){
    PlayerBase::showPlayedJong(type);
    for(auto var:playerHandJongs){
        var->setTingJongHint(false);
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
            Point endPoint;
            if(type >= JongEnum::zhong && GAMEDATA::getInstance()->getGameType() != 7 && GAMEDATA::getInstance()->getGameType() != 8){
                if(playerHuaJongs.size()/9 == 0){
                    spJong->setLocalZOrder(4);
                }else if(playerHuaJongs.size()/9 == 1){
                    spJong->setLocalZOrder(3);
                }else if(playerHuaJongs.size()/9 == 2){
                    spJong->setLocalZOrder(2);
                }else if(playerHuaJongs.size()/9 == 3){
                    spJong->setLocalZOrder(1);
                }
                endPoint = getHeroPlayedHuaPos((int)playerHuaJongs.size());
            }else{
                endPoint = getHeroPlayedNormalPos((int)playerPlayedJongs.size());
            }
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
            ScaleTo* scale = ScaleTo::create(0.3f, 0.55f);
            Spawn* spa = Spawn::create(actionMove, scale, NULL);
            CallFunc* callback = CallFunc::create([=](){
                spJong->showJong(heroplayed, spJong->getJongType());
                if(type >= JongEnum::zhong){
                    playerHuaJongs.pushBack(spJong);
                    showPlayerHua((int)playerHuaJongs.size());
                }else{
                    spJong->setScale(1.0f);
                    playerPlayedJongs.pushBack(spJong);
                }
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


void PlayerHero::playPokerByHand(Jong* jong){
    PlayerBase::showPlayedJong(jong->getJongType());
    //如果打出牌是允许胡的牌,继续显示胡牌提示,否则取消显示
    bool huEnable = false;
    for (int i=0; i<heroHuData.size(); i++) {
        if(heroHuData.at(i).poker == jong->getJongType()){
            huEnable = true;
        }
    }
    if(!huEnable){
        if(NULL != getChildByTag(6689)){
            getChildByTag(6689)->removeFromParent();
        }
    }
    for(auto var:playerHandJongs){
        var->setTingJongHint(false);
    }
    updateSelectedInfo(NULL);
    stopTimeClockAnim();
    Point startPoint = jong->getPosition();
    Point endPoint;
    if(jong->getJongType() >= JongEnum::zhong&&(GAMEDATA::getInstance()->getGameType() == 1||GAMEDATA::getInstance()->getGameType()==2||(GAMEDATA::getInstance()->getGameType()==5 && jong->getJongType() != JongEnum::baida)||(GAMEDATA::getInstance()->getGameType()==6 && jong->getJongType() != JongEnum::baida))){
        if(playerHuaJongs.size()/9 == 0){
            jong->setLocalZOrder(4);
        }else if(playerHuaJongs.size()/9 == 1){
            jong->setLocalZOrder(3);
        }else if(playerHuaJongs.size()/9 == 2){
            jong->setLocalZOrder(2);
        }else if(playerHuaJongs.size()/9 == 3){
            jong->setLocalZOrder(1);
        }
        endPoint = getHeroPlayedHuaPos((int)playerHuaJongs.size());
    }else{
        endPoint = getHeroPlayedNormalPos((int)playerPlayedJongs.size());
    }
    CallFunc* callback = CallFunc::create([=](){
        eraseHeroJong(jong);
        jong->showJong(heroplayed, jong->getJongType());
        if(jong->getJongType() >= JongEnum::zhong&&(GAMEDATA::getInstance()->getGameType() == 1||GAMEDATA::getInstance()->getGameType()==2||(GAMEDATA::getInstance()->getGameType()==5 && jong->getJongType() != JongEnum::baida)||(GAMEDATA::getInstance()->getGameType()==6 && jong->getJongType() != JongEnum::baida))){
            playerHuaJongs.pushBack(jong);
            showPlayerHua((int)playerHuaJongs.size());
            jong->setScale(0.55f);
        }else{
            jong->setScale(1.0f);
            playerPlayedJongs.pushBack(jong);
            jong->setLocalZOrder((int)playerPlayedJongs.size());
        }
        jong->setPosition(endPoint);
        isAllowPlay = false;
        if (!GAMEDATA::getInstance()->getIsTrusteeship()){
            sendPokerRequest(jong->getJongType());
            hidePlayedBigJong();
        }
        resetHandJongsY(jong);
        
    });
    CallFunc* callback2 = CallFunc::create([=](){
        if(!(jong->getJongType() >= JongEnum::zhong&&(GAMEDATA::getInstance()->getGameType() == 1||GAMEDATA::getInstance()->getGameType()==2||(GAMEDATA::getInstance()->getGameType()==5 && jong->getJongType() != JongEnum::baida)||(GAMEDATA::getInstance()->getGameType()==6 && jong->getJongType() != JongEnum::baida)))){
            showPlayedJongSign(true);
        }
        if(GAMEDATA::getInstance()->getGameType() == 1){
            checkSuZhouHeroHandPoker();
        }else if(GAMEDATA::getInstance()->getGameType() == 3){
            checkHongZhongHeroHandPoker();
        }else if(GAMEDATA::getInstance()->getGameType() == 5){
            checkBaiDaHeroHandPoker();
        }
    });
    
    Sequence* seq = Sequence::create(callback,callback2,NULL);
    jong->runAction(seq);
}

void PlayerHero::drawPlayedJongMingpai(int type){
    PlayerBase::showPlayedJong(type);
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
            Point endPoint;
            if(type >= JongEnum::zhong&&(GAMEDATA::getInstance()->getGameType() == 1||GAMEDATA::getInstance()->getGameType()==2||(GAMEDATA::getInstance()->getGameType()==5 && type != JongEnum::baida)||(GAMEDATA::getInstance()->getGameType()==6 && type != JongEnum::baida))){
                spJong->setScale(0.55f);
                if(playerHuaJongs.size()/9 == 0){
                    spJong->setLocalZOrder(4);
                }else if(playerHuaJongs.size()/9 == 1){
                    spJong->setLocalZOrder(3);
                }else if(playerHuaJongs.size()/9 == 2){
                    spJong->setLocalZOrder(2);
                }else if(playerHuaJongs.size()/9 == 3){
                    spJong->setLocalZOrder(1);
                }
                endPoint = getHeroPlayedHuaPos((int)playerHuaJongs.size());
                playerHuaJongs.pushBack(spJong);
                showPlayerHua((int)playerHuaJongs.size());
            }else{
                endPoint = getHeroPlayedNormalPos((int)playerPlayedJongs.size());
                playerPlayedJongs.pushBack(spJong);
            }
            spJong->showJong(heroplayed, spJong->getJongType());
            spJong->setPosition(endPoint);
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


void PlayerHero::doEventTimeOver(int type){
    
}


void PlayerHero::actionTing(HeroCpgRespData tingData){
    setIsAllowTouch(true);
    showHuPaiTiShi(tingData.playCpgt.heroHu);
}

void PlayerHero::showHuPaiTiShi(std::vector<HeroHuPaiData> heroHu){
    //对heroHuData进行自动排序
    heroHuData = heroHu;
    if(heroHu.size() == 0){
        return ;
    }
    int max = 1;
    for(int k=0;k<heroHu.size();k++){
        int total = 0;
        for (int l=0; l<heroHu.at(k).data.size(); l++) {
            total += atoi(heroHu.at(k).data.at(l).num.c_str());
        }
        if(total> max){
            max = total;
        }
        
    }
    for (int i = 0; i < playerHandJongs.size(); i++){
        for (int j=0; j<heroHu.size(); j++) {
            if(playerHandJongs.at(i)->getJongType() == heroHu.at(j).poker){
                int total2 = 0;
                for (int m=0; m<heroHu.at(j).data.size(); m++) {
                    total2 += atoi(heroHu.at(j).data.at(m).num.c_str());
                }
                if(total2 == max){
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
    setIsAllowTouch(true);
    resetHandJongsY(NULL);
}

void PlayerHero::drawHeroPeng(HeroCpgRespData resp, PlayerBase* playerBase){
    Audio::getInstance()->playSoundPeng(UserData::getInstance()->isFangYan(),getPlayerInfo()->getGender());
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
        jon->setPosition(playerBase->getCurrentJong()->getPosition());
        this->addChild(jon, 1);
        //判断被碰牌玩家的位置
        pengVector.insert(0, jon);
        PlayerCpgRecord record;
        record.type = CpgType::peng;
        record.pokersRecord = pengVector;
        if(playerBase->getClientSeat()==ClientSeatId::left){
            jon->showJong(herocpglandscape, playerBase->getCurrentJong()->getJongType());
            record.pengDir = 0;
        }else if(playerBase->getClientSeat()==ClientSeatId::opposite){
            jon->showJong(herocpgportrait, playerBase->getCurrentJong()->getJongType());
            record.pengDir = 1;
        }else{
            jon->showJong(herocpglandscape, playerBase->getCurrentJong()->getJongType());
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
                    mv= MoveTo::create(0.15f, Point(580 + (m==0?3:3+38 * m), 195));
                }else{
                    mv= MoveTo::create(0.15f, Point(580 + (m==0?80:3+38 * (m-1)), 195));
                }
                ScaleTo* scale = ScaleTo::create(0.15f, 0.6f);
                Spawn* sp = Spawn::create(mv, scale, NULL);
                pengVector.at(m)->showBackShadow(false);
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
                    mv = MoveTo::create(0.15f, Point(getCpgPostionX() + 48 * k, 45));
                }else{
                    mv = MoveTo::create(0.15f, Point(getCpgPostionX()+ (k==0? 105:(5+48 * (k-1))), k==0?35:45));
                }
                ScaleTo* scale = ScaleTo::create(0.15f, 0.75f);
                Spawn* sp = Spawn::create(mv, scale, NULL);
                pengVector.at(k)->runAction(sp);
            }
            setCpgPostionX(getCpgPostionX()+170);
        });
        Sequence* mySe = Sequence::create(action1, delay, action2, NULL);
        runAction(mySe);
    }
    if(GAMEDATA::getInstance()->getGameType() == 1){
        checkSuZhouHeroHandPoker();
    }else if(GAMEDATA::getInstance()->getGameType() == 3){
        checkHongZhongHeroHandPoker();
    }else if(GAMEDATA::getInstance()->getGameType() == 5){
        checkBaiDaHeroHandPoker();
    }else if(GAMEDATA::getInstance()->getGameType() == 7){
        checkFanPaiHeroHandPoker(atoi(GAMEDATA::getInstance()->getBaiDaPoker().c_str()));
    }
    setIsAllowPlay(true);
    startTimeClockAnim();
    showHuPaiTiShi(resp.playCpgt.heroHu);
}

void PlayerHero::drawHeroGang(HeroCpgRespData resp, PlayerBase* playerBase){
    Audio::getInstance()->playSoundGang(UserData::getInstance()->isFangYan(),getPlayerInfo()->getGender());
    for(auto var:playerHandJongs){
        var->setTingJongHint(false);
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
                gangVector.at(k)->showBackShadow(false);
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


void PlayerHero::drawHeroPengMingpai(HeroCpgRespData resp, PlayerBase* playerBase){
    
    Audio::getInstance()->playSoundPeng(UserData::getInstance()->isFangYan(),getPlayerInfo()->getGender());
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
    jon->setPosition(playerBase->getCurrentJong()->getPosition());
    this->addChild(jon, 1);
    //判断被碰牌玩家的位置
    pengVector.insert(0, jon);
    PlayerCpgRecord record;
    record.type = CpgType::peng;
    record.pokersRecord = pengVector;
    if(playerBase->getClientSeat()==ClientSeatId::left){
        record.pengDir = 0;
        jon->showJong(herocpglandscape, playerBase->getCurrentJong()->getJongType());
    }else if(playerBase->getClientSeat()==ClientSeatId::opposite){
        record.pengDir = 1;
        jon->showJong(herocpgportrait, playerBase->getCurrentJong()->getJongType());
    }else{
        record.pengDir = 2;
        jon->showJong(herocpglandscape, playerBase->getCurrentJong()->getJongType());
    }
    playerCpgRecords.push_back(record);
    playerBase->removeLastJong();
    setHandPosX(getHandPosX() + JONG_WIDTH * 3);
    sortHandJongs(getHandPosX(), true);
    for (int k = 0; k < pengVector.size(); k++){
        if(playerBase->getClientSeat()==ClientSeatId::left){
            pengVector.at(k)->setPosition(Point(getCpgPostionX() + (k==0? 0:(5+48 * k)), k==0?35:45));
        }else if(playerBase->getClientSeat()==ClientSeatId::opposite){
            pengVector.at(k)->setPosition(Point(getCpgPostionX() + 48 * k, 45));
        }else{
            pengVector.at(k)->setPosition(Point(getCpgPostionX()+ (k==0? 105:(5+48 * (k-1))), k==0?35:45));
        }
        pengVector.at(k)->setScale(0.75f);
    }
    setCpgPostionX(getCpgPostionX()+170);
    setIsAllowPlay(true);
    startTimeClockAnim();
}

void PlayerHero::drawHeroGangMingpai(HeroCpgRespData resp, PlayerBase* playerBase){
    Audio::getInstance()->playSoundGang(UserData::getInstance()->isFangYan(),getPlayerInfo()->getGender());
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
                    gangVector.at(k)->showJong(herocpgportrait, gangVector.at(k)->getJongType(),true);
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


void PlayerHero::recoverHua(std::string hua){
    playerHuaJongs.clear();
    if(hua == ""){
        showPlayerHua(0);
        return;
    }
    vector<std::string>  playeds = StringUtil::split(hua, ",");
    for (int i = 0; i < playeds.size(); i++){
        Jong* jong = Jong::create();
        jong->showJong(heroplayed, atoi(playeds.at(i).c_str()));
        jong->setScale(0.55f);
        jong->setPosition(getHeroPlayedHuaPos((int)playerHuaJongs.size()));
        if(playerHuaJongs.size()/9 == 0){
            jong->setLocalZOrder(4);
        }else if(playerHuaJongs.size()/9 == 1){
            jong->setLocalZOrder(3);
        }else if(playerHuaJongs.size()/9 == 2){
            jong->setLocalZOrder(2);
        }else if(playerHuaJongs.size()/9 == 3){
            jong->setLocalZOrder(1);
        }
        addChild(jong);
        playerHuaJongs.pushBack(jong);
    }
    showPlayerHua(playerHuaJongs.size());
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
        jong->setPosition(getHeroPlayedNormalPos((int)playerPlayedJongs.size()));
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
                int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), atoi(peng.at(i).peId.c_str()));
                if(seatId == ClientSeatId::left){
                    jong->showJong(j==0?herocpglandscape:herocpgportrait, atoi(peng.at(i).peng.c_str()));
                    jong->setPosition(Point(getCpgPostionX() + (j==0? 0:(5+48 * j)), j==0?35:45));
                }else if(seatId == ClientSeatId::opposite){
                    jong->showJong(herocpgportrait, atoi(peng.at(i).peng.c_str()));
                    jong->setPosition(Point(getCpgPostionX() + 48 * j,45));
                }else if(seatId == ClientSeatId::right){
                    jong->showJong(j==0?herocpglandscape:herocpgportrait, atoi(peng.at(i).peng.c_str()));
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
            if(GAMEDATA::getInstance()->getGameType() == 1){
                checkSuZhouHeroHandPoker();
            }else if(GAMEDATA::getInstance()->getGameType() == 3){
                checkHongZhongHeroHandPoker();
            }else if(GAMEDATA::getInstance()->getGameType() == 5){
                checkBaiDaHeroHandPoker();
            }
            setIsAllowPlay(true);
            startTimeClockAnim();
        }else{
            jong->setPosition(Point(getHandPosX() + JONG_WIDTH * i, JONG_POS_Y));
        }
        addChild(jong);
        playerHandJongs.pushBack(jong);
    }
    currentJong = playerHandJongs.at(playerHandJongs.size()-1);
    if(GAMEDATA::getInstance()->getGameType() == 1){
        checkSuZhouHeroHandPoker();
    }else if(GAMEDATA::getInstance()->getGameType() == 3){
        checkHongZhongHeroHandPoker();
    }else if(GAMEDATA::getInstance()->getGameType() == 5){
        checkBaiDaHeroHandPoker();
    }
}

void PlayerHero::updateMingpai(Vector<Jong*> myPlayerHandJongs,Vector<Jong*> myPlayerPlayedJongs,Vector<Jong*> myPlayerHuaJongs,std::vector<PlayerCpgRecord> myPlayerCpgRecords){
    for(int j=0; j< playerPlayedJongs.size();j++){
        playerPlayedJongs.at(j)->removeFromParent();
    }
    playerPlayedJongs = myPlayerPlayedJongs;
    for(int a = 0;a<myPlayerPlayedJongs.size();a++){
        addChild(myPlayerPlayedJongs.at(a));
        myPlayerPlayedJongs.at(a)->setPosition(getHeroPlayedNormalPos(a));
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
    for(int m=0;m<playerHuaJongs.size();m++){
        playerHuaJongs.at(m)->removeFromParent();
    }
    playerHuaJongs = myPlayerHuaJongs;
    for (int i = 0; i < myPlayerHuaJongs.size(); i++){
        myPlayerHuaJongs.at(i)->setPosition(getHeroPlayedHuaPos(i));
        addChild(myPlayerHuaJongs.at(i));
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
    showPlayedJongSign(false);
    hidePlayedBigJong();
}

void PlayerHero:: showPlayedJongSign(bool show){
    if(playerPlayedJongs.size()>0)
        ((BaseView*)getParent())->setPlayPokerSignPosition(show,Point(getHeroPlayedNormalPos((int)playerPlayedJongs.size() - 1).x, getHeroPlayedNormalPos((int)playerPlayedJongs.size() - 1).y + 20));
}

void PlayerHero::hidePlayedBigJong(){
    ((BaseView*)getParent())->setBigJongEnable();
}



