#include "game/mahjong/player/base/PlayerBase.h"
#include "game/mahjong/anim/PlayerCpgAnim.hpp"
#include "game/mahjong/heroinfo/OtherPlayerInfo.hpp"
#include "game/mahjong/anim/HuaAnim.hpp"
#include "game/mahjong/chat/PlayerChatManage.hpp"
#include "server/NetworkManage.h"
#include "userdata/UserData.h"
#include "ui/UIImageView.h"
#include "ui/UIRichText.h"

Sprite* PlayerBase::biaoji = NULL;
Sprite* PlayerBase::currentBigJongBg = NULL;
Jong* PlayerBase::currentBigJong = NULL;
set<int> PlayerBase:: playedPokers;

bool PlayerBase::init(){
    if (!Layer::init()){
        return false;
    }
    initData();
    chatShowLayer = Layer::create();
    addChild(chatShowLayer,20);
    return true;
}


void PlayerBase::initData(){
    mCDTime = 20;
    playerCpgRecords.clear();
    playerHandJongs.clear();
    playerPlayedJongs.clear();
    setHuaNum(0);
    setStateCpg(false);
    setIsPlayHuaChi(false);
}


void PlayerBase::onEnter(){
    Layer::onEnter();
    roomChatListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_PLAYER_CHAT_NOTIFY, [=](EventCustom* event){
        if(playerInfo->getSeatId() == GAMEDATA::getInstance()->getHeroSeatId()){
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MSG_PLAYER_ROOM_CHAT_SHOW);
            chatShowLayer->removeAllChildren();//清空界面
            ChatData data = GAMEDATA::getInstance()->getChatData();
            std::string content = data.content;
            vector<std::string> msgs =PlayerChatManage::getInstance()->splitContentByFace(content);
            
            RichText* text = RichText ::create();
            text->setAnchorPoint(Point::ANCHOR_MIDDLE);
            for(auto var : msgs){
                if(!PlayerChatManage::getInstance()->isFaceImage(var)){
                    RichElementText* element1 = RichElementText::create(1, Color3B(255,255,255), 255, var, "arial", 20);
                    text->pushBackElement(element1);
                    text->formatText();
                }else{
                    RichElementImage* element2 = RichElementImage::create(1, Color3B(255,255,255), 255, PlayerChatManage::getInstance()->getFaceImageName(var));
                    text->pushBackElement(element2);
                    text->formatText();
                }
            }
            int seatId = GAMEDATA::getInstance()->getHeroSeatId();
            for(auto play:GAMEDATA::getInstance()->getPlayersInfo()){
                if(play->getPoxiaoId() == data.poxiaoId){
                    seatId = play->getSeatId();
                }
            }
            text->setPosition(getVec2BySeatId(seatId));
            chatShowLayer->addChild(text,1);
            auto bob = Scale9Sprite::create("chat/text_bob.png", Rect(0, 0, 31, 38), Rect(20, 0, 6, 38));
            bob->setContentSize(Size(text->getContentSize().width+10, 65));
            bob->setPosition(getVec2BySeatId(seatId));
            chatShowLayer->addChild(bob);
            if(SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), seatId) == ClientSeatId::left
               || SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), seatId) == ClientSeatId::hero){
                text->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
                bob->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
            }else{
                text->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
                bob->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
                bob->setFlippedX(true);
            }
            schedule([=](float dt){
                chatShowLayer->removeAllChildren();
            },0,0,3.0,"removebob");
            
        }
    });
}

void PlayerBase::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(roomChatListener);
}


void PlayerBase::initPlayer(Player* playerInfo){
    setPlayerInfo(playerInfo);
    
    
    int clientSeatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), playerInfo->getSeatId());
    
    auto head_bg = Sprite::create("gameview/head_image_bg.png");
    head_bg->setPosition(getPostionBySeat(clientSeatId));
    this->addChild(head_bg);
    
    nickName = Label::create(playerInfo->getNickname(), "Arial", 12);
    nickName->setPosition(getPostionBySeat(clientSeatId).x, getPostionBySeat(clientSeatId).y + 55);
    this->addChild(nickName);
    
    auto image = MenuItemImage::create(getHeadImageName(playerInfo->getPicture()),getHeadImageName(playerInfo->getPicture()),
                                       CC_CALLBACK_0(PlayerBase::showPlayerInfo, this));
    headimage = Menu::create(image,NULL);
    headimage->setPosition(getPostionBySeat(clientSeatId));
    this->addChild(headimage);
    
    auto diamond = Sprite::create();
    diamond->setPosition(getPostionBySeat(clientSeatId).x - 28, getPostionBySeat(clientSeatId).y - 55);
    this->addChild(diamond);
    diamondNum = LabelAtlas::create(cocos2d::String::createWithFormat("%d", 0)->_string,
                                    "result/result_num.png", 9, 13, '0');
    diamondNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    diamondNum->setPosition(getPostionBySeat(clientSeatId).x - 16, getPostionBySeat(clientSeatId).y - 55);
    addChild(diamondNum);
    if (GAMEDATA::getInstance()->getMahjongRoomType()==MahjongRoom::privateRoom){
        if(playerInfo->getLockDiamond()>0){
            diamond->setTexture("gameview/other_player_lockdiamond.png");
            diamondNum->setString(cocos2d::String::createWithFormat("%d",playerInfo->getLockDiamond())->_string);
        }else{
            diamond->setTexture("gameview/other_player_diamond.png");
            diamondNum->setString(cocos2d::String::createWithFormat("%d",playerInfo->getDiamond())->_string);
        }
        diamondNum->setPosition(getPostionBySeat(clientSeatId).x - 8, getPostionBySeat(clientSeatId).y - 55);
    }
    else {
        diamond->setTexture("gameview/gold_small.png");
        diamondNum->setString(cocos2d::String::createWithFormat("%d", playerInfo->getGold())->_string);
    }
    
    
    auto readyTitle = Sprite::create("gameview/ready_title.png");
    readyTitle->setTag(1001);
    readyTitle->setPosition(getPostionBySeat(clientSeatId));
    this->addChild(readyTitle);
    
    auto offLineIcon = Sprite::create("trusteeship/offline_icon.png");
    offLineIcon->setTag(1002);
    offLineIcon->setVisible(false);
    offLineIcon->setPosition(getPostionBySeat(clientSeatId).x+40,getPostionBySeat(clientSeatId).y-45);
    this->addChild(offLineIcon);
    
    auto trueeIcon = Sprite::create("trusteeship/trustee_icon.png");
    trueeIcon->setTag(1003);
    trueeIcon->setVisible(false);
    trueeIcon->setPosition(getPostionBySeat(clientSeatId).x+40,getPostionBySeat(clientSeatId).y-45);
    this->addChild(trueeIcon);
    
    tingTitle = Sprite::create("gameview/ting_icon.png");
    tingTitle->setPosition(getPostionBySeat(clientSeatId).x + 40, getPostionBySeat(clientSeatId).y + 50);
    this->addChild(tingTitle,101);
    
    Sprite* progressSprite = Sprite::create("gameview/time_clock_bg.png");
    mProgressTimer = ProgressTimer::create(progressSprite);
    mProgressTimer->setPosition(getPostionBySeat(clientSeatId));
    this->addChild(mProgressTimer, 100);
    
    timeClock = LabelAtlas::create(cocos2d::String::createWithFormat("%d", mCDTime)->_string, "headportrait/time_clock_num.png", 19, 25, '0');
    timeClock->setAnchorPoint(Point::ANCHOR_MIDDLE);
    timeClock->setPosition(getPostionBySeat(clientSeatId));
    this->addChild(timeClock, 101);
    
    biaoji = Sprite::create("gameview/arrows.png");
    addChild(biaoji, 200);
    currentBigJongBg = Sprite::create("gameview/jong_show_bg_1.png");
    addChild(currentBigJongBg, 201);;
    currentBigJong = Jong::create();
    addChild(currentBigJong, 201);;
    
    
    playerHua = Sprite::create("gameview/flower.png");
    addChild(playerHua);
    playerHuaCount = LabelAtlas::create("0","gameview/hua_num.png",17,24,'0');
    playerHuaCount->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(playerHuaCount);
    
    biaoji->setVisible(false);
    currentBigJongBg->setVisible(false);
    currentBigJong->setVisible(false);
    readyTitle->setVisible(false);
    tingTitle->setVisible(false);
    mProgressTimer->setVisible(false);
    timeClock->setVisible(false);
    playerHua->setVisible(false);
    playerHuaCount->setVisible(false);
}


void PlayerBase::replaceHandHua(JongViewType tpye){
    ReplaceJong rejong = getReplacePoker();
    std::vector<Jong*> needReplace;
    for (int i = 0; i < rejong.poker.size(); i++){
        
        std::vector<std::string> pokerV = StringUtil::split(rejong.poker.at(i), ",");
        for (int j = 0; j < pokerV.size(); j++){
            Jong* jon = Jong::create();
            jon->showJong(tpye,atoi(pokerV.at(j).c_str()));
            needReplace.push_back(jon);
        }
    }
    if(needReplace.size()>0){
        HuaAnim* huaAnim = HuaAnim::create(needReplace,getPlayerInfo()->getSeatId(),CallFunc::create([=](){
            setHuaNum(getHuaNum()+needReplace.size());
            showPlayerHua(getHuaNum());
        }));
        addChild(huaAnim,100);
    }
}

void PlayerBase::replaceTurnHua(PlayerTurnData data){
    if(data.replace==""){
        return;
    }
    std::vector<std::string> replace = StringUtil::split(data.replace, ",");
    if(replace.size()>0){
        huaIndex=0;
        Sprite* spr = Sprite::create();
        addChild(spr);
        spr->runAction(Repeat::create(Sequence::create(CallFunc::create([=](){
            needReplace.clear();
            Jong* jon = Jong::create();
            jon->showJong(leftplayed,atoi(replace.at(huaIndex).c_str()));
            needReplace.push_back(jon);
            HuaAnim* huaAnim = HuaAnim::create(needReplace, getPlayerInfo()->getSeatId(),CallFunc::create([=](){
                setHuaNum(getHuaNum()+needReplace.size());
                showPlayerHua(getHuaNum());
            }));
            addChild(huaAnim,100);
            huaIndex++;
        }), DelayTime::create(1.0f),NULL),replace.size()));
    }
    
}

void PlayerBase::showPlayedJong(int ctype){
    playedPokers.insert(ctype);
    setLastPoker(ctype);
    set<int>::iterator it =playedPokers.find(lastPoker);
    if(it == playedPokers.end() && Audio::getInstance()->getHasTingPlayer()){
        Audio::getInstance()->playSoundChong(getPlayerInfo()->getGender());//冲牌音效
    }else{
        Audio::getInstance()->playMahjong(ctype,getPlayerInfo()->getGender());//普通打牌音效
    }
    
}

void PlayerBase::showPlayerChi(string chiPoker, PlayerBase* playerBase){
    if(getChiNumber()==0){
        if(getPokerNumber()>10){
            Audio::getInstance()->playSoundChi(4,getPlayerInfo()->getGender());
        }else{
            if(chiPoker=="1,2"||chiPoker=="8,9"||chiPoker=="10,11"||chiPoker=="17,18"||chiPoker=="19,20"||chiPoker=="26,27"){
                //边一记
                Audio::getInstance()->playSoundChi(3,getPlayerInfo()->getGender());
            }else {
                std::vector<std::string> cha = StringUtil::split(chiPoker, ",");
                if(atoi(cha.at(1).c_str())-atoi(cha.at(0).c_str())>1){
                    //卡一记
                    Audio::getInstance()->playSoundChi(2,getPlayerInfo()->getGender());
                }else{
                    //吃
                    int ran = rand()%2;
                    Audio::getInstance()->playSoundChi(ran,getPlayerInfo()->getGender());
                }
            }
        }
    }else if(getChiNumber() == 1){
        //第二次吃牌
        int ran = rand()%2;
        Audio::getInstance()->playSoundChi(ran+5,getPlayerInfo()->getGender());
    }else if(getChiNumber() == 2){
        //第三次吃牌,上家说话
        Audio::getInstance()->playSoundChi3(getPlayerInfo()->getGender());
    }
    setChiNumber(getChiNumber()+1);
}

void PlayerBase::showPlayerPeng(PlayerCpgtData data,PlayerBase* playerBase){
    Audio::getInstance()->playSoundPeng(getPlayerInfo()->getGender());
}

void PlayerBase::showPlayerGang(PlayerCpgtData data, PlayerBase* playerBase){
    Audio::getInstance()->playSoundGang(getPlayerInfo()->getGender());
}


void PlayerBase::showCurrentBigJong(int cType){
    currentBigJongBg->setVisible(true);
    currentBigJong->setVisible(true);
    currentBigJong->showJong(playedshow,cType);
    Point pos = getBigJongPos(SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(),getPlayerInfo()->getSeatId()));
    currentBigJongBg->setPosition(pos);
    currentBigJong->setPosition(pos.x,pos.y+15);
    
}

void PlayerBase::hideCurrentBigJong(){
    currentBigJongBg->setVisible(false);
    currentBigJong->setVisible(false);
}


void PlayerBase::setIsReady(bool b){
    if(NULL != getChildByTag(1001)){
        getChildByTag(1001)->setVisible(b);
    }
}

void PlayerBase::setIsOffLine(bool b){
    if(NULL != getChildByTag(1002)){
        getChildByTag(1002)->setVisible(b);
    }
}

void PlayerBase::setIsTrustee(bool b){
    if(NULL != getChildByTag(1003)){
        getChildByTag(1003)->setVisible(b);
    }
}

void PlayerBase::showPlayerInfo(){
    OtherPlayerInfo* dialog = OtherPlayerInfo::create(getPlayerInfo());
    getParent()->addChild(dialog,100);//添加到父场景,为了解决图层错位的问题
}

void PlayerBase::updatePlayerInfo(int num){
    diamondNum->setString(cocos2d::String::createWithFormat("%d", num)->_string);
}


void PlayerBase::showPlayerHua(int num){
    if(num>5 && !getIsPlayHuaChi()){
        Audio::getInstance()->playSoundHuaChi(getPlayerInfo()->getGender());
        setIsPlayHuaChi(true);
    }
    playerHua->setVisible(true);
    playerHuaCount->setVisible(true);
    Point pos = getHuaNumPos(SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), playerInfo->getSeatId()));
    playerHua->setPosition(pos);
    playerHuaCount->setPosition(pos.x + 30, pos.y);
    playerHuaCount->setString(cocos2d::String::createWithFormat(":%d",num)->_string);
    playerHuaCount->setScale(2.0f);
    playerHuaCount->setOpacity(77);
    playerHuaCount->runAction(Sequence::create(Spawn::create(FadeTo::create(4.0/24, 255),ScaleTo::create(4.0f/24, 1.0f), NULL), NULL));
}





void PlayerBase::startTimeClockAnim(){
    timeClock->setString(cocos2d::String::createWithFormat("%d", 20)->_string);
    this->setTag(-1);
    mCDTime = 20;
    mProgressTimer->setVisible(true);
    mProgressTimer->setType(ProgressTimer::Type::RADIAL);
    mProgressTimer->stopAllActions();
    mProgressTimer->setReverseProgress(true);
    ActionInterval* action_progress_to = Sequence::create(ProgressFromTo::create(20, 100, 0), nullptr);
    mProgressTimer->runAction(Sequence::create(action_progress_to, NULL));
    schedule(schedule_selector(PlayerBase::updateTime), 1);
    timeClock->setVisible(true);
}

void PlayerBase::startTimeClockAnim(int time, int type){
    timeClock->setString(cocos2d::String::createWithFormat("%d", time)->_string);
    this->setTag(type);
    mCDTime = time;
    mProgressTimer->setVisible(true);
    mProgressTimer->setType(ProgressTimer::Type::RADIAL);
    mProgressTimer->stopAllActions();
    mProgressTimer->setReverseProgress(true);
    ActionInterval* action_progress_to = Sequence::create(ProgressFromTo::create(time, 100, 0), nullptr);
    mProgressTimer->runAction(Sequence::create(action_progress_to, NULL));
    schedule(schedule_selector(PlayerBase::updateTime), 1);
    timeClock->setVisible(true);
}


void  PlayerBase::stopTimeClockAnim(){
    mProgressTimer->setVisible(false);
    timeClock->setVisible(false);
    mCDTime = 1000000;
    unschedule(schedule_selector(PlayerBase::updateTime));
}




void PlayerBase::setPlayerTingState(bool b){
    if(b){
        Audio::getInstance()->playSoundTing(getPlayerInfo()->getGender());//听牌音效
        Audio::getInstance()->setHasTingPlayer(true);
    }
    tingTitle->setVisible(b);
}

void PlayerBase::playerCpgAnim(CpgType cpgType, ClientSeatId type){
    hideCurrentBigJong();
    PlayerCpgAnim* anim = PlayerCpgAnim::create(cpgType, type);
    addChild(anim,100);
    
}


void PlayerBase::updateTime(float dt){
    mCDTime--;
    if (mCDTime > 0){
        timeClock->setString(cocos2d::String::createWithFormat("%d", mCDTime)->_string);
    }
    else{
        timeClock->setVisible(false);
        if(mCDTime == 0){
            doEventTimeOverUi();
        }
        if (mCDTime <=-1){
            mCDTime = 1000000;
            doEventTimeOver(this->getTag());
        }
    }
}

Jong* PlayerBase::getCurrentJong(){
    return playerPlayedJongs.at(playerPlayedJongs.size()-1);
}


Point PlayerBase::getBigJongPos(int type){
    
    if (type == ClientSeatId::left){
        return Vec2(300,400);
    }
    else if (type == ClientSeatId::opposite){
        return Vec2(640, 550);
    }
    else if (type == ClientSeatId::right){
        return Vec2(980, 400);
    }
    else{
        log("PlayerBase getBigJongPos 传入参数有误");
        return Vec2(0, 0);
    }
}

Point PlayerBase::getHuaNumPos(int seatId){
    if (seatId == ClientSeatId::hero){
        return Vec2(288,185);
    }
    else if (seatId == ClientSeatId::left){
        return Vec2(45,545);
    }
    else if (seatId == ClientSeatId::opposite){
        return Vec2(800,615);
    }
    else if (seatId == ClientSeatId::right){
        return Vec2(1200,545);
    }
    else{
        log("PlayerBase getHuaNumPos 传入参数有误");
        return Vec2(0, 0);
    }
}

Point PlayerBase::getPostionBySeat(int seatId){
    if (seatId == ClientSeatId::hero){
        return Vec2(70, 157);
    }
    else if (seatId == ClientSeatId::right){
        return Vec2(1213, 455);
    }
    else if (seatId == ClientSeatId::opposite){
        return Vec2(945, 642);
    }
    else if (seatId == ClientSeatId::left){
        return Vec2(70, 455);
    }
    else{
        log("PlayerBase getPostionBySeat 传入参数有误");
        return Vec2(0, 0);
    }
}

std::string PlayerBase::getHeadImageName(std::string id){
    std::string imageName = "gameview/head_image_1.png";
    if (id == "1"){
        imageName = "gameview/head_image_1.png";
    }
    else if (id == "2"){
        imageName = "gameview/head_image_2.png";
    }
    else if (id == "3"){
        imageName = "gameview/head_image_3.png";
    }
    else if (id == "4"){
        imageName = "gameview/head_image_4.png";
    }
    return imageName;
}

void PlayerBase::hideHandJongs(){
    for(int i=0;i<playerHandJongs.size();i++){
        playerHandJongs.at(i)->setVisible(false);
    }
}

void PlayerBase::recoverHua(std::string hua){
    //
    
}


void PlayerBase::recoverPlayed(std::string played){
    //
    
}


void PlayerBase::recoverCpg(vector<PlayerChiData> chi,vector<PlayerPengData> peng,vector<PlayerGangData> gang,std::string angang){
    //
    
    
}

void PlayerBase::recoverHand(std::string hand){
    //
}

Point PlayerBase::getVec2BySeatId(int seatId){
    int seatID = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), seatId);
    if(seatID == ClientSeatId::left){
        return Vec2(150,470);
    }else if(seatID == ClientSeatId::opposite){
        return Vec2(850,670);
    }else if(seatID == ClientSeatId::right){
        return Vec2(1150,470);
    }else{
        return Vec2(150,200);
    }
}

void PlayerBase::playSoundHuPai(int type){
    Audio::getInstance()->playSoundHu(type, getPlayerInfo()->getGender());
}
