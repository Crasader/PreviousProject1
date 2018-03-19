#include "mahjong/gameview/player/base/PlayerBase.h"
#include "mahjong/gameview/anim/PlayerCpgAnim.hpp"
#include "mahjong/gameview/anim/HuaAnim.hpp"
#include "mahjong/common/heroinfo/OtherPlayerInfo.hpp"
#include "mahjong/common/chat/PlayerChatManage.hpp"
#include "mahjong/common/widget/HeadImage.hpp"
#include "mahjong/common/utils/Chinese.h"
#include "server/NetworkManage.h"
#include "mahjong/common/audio/Audio.h"
#include "userdata/UserData.h"
#include "http/base64/Base64.h"
#include "ui/UIImageView.h"
#include "ui/UIRichText.h"
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "voicesdk/VoiceMgr.h"
#endif


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
    mCDTime = 15;
    playerCpgRecords.clear();
    playerHandJongs.clear();
    playerPlayedJongs.clear();
    setStateCpg(false);
    setIsPlayHuaChi(false);
}




void PlayerBase::initPlayer(PlayerInfo* playerInfo){
    setPlayerInfo(playerInfo);
    int clientSeatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), getPlayerInfo()->getSeatId());
    
    auto nicknameBg = Sprite::create("gameview/user_nicheng_bg.png");
    nicknameBg->setPosition(getPostionBySeat(clientSeatId).x, getPostionBySeat(clientSeatId).y-33.5);
    addChild(nicknameBg,1);
    
    nickName = Label::createWithSystemFont(playerInfo->getNickname(), "Arial", 19);
    nickName->setWidth(90);
    nickName->setHeight(20);
    nickName->setAlignment(cocos2d::TextHAlignment::CENTER);
    nickName->setPosition(getPostionBySeat(clientSeatId).x+3, getPostionBySeat(clientSeatId).y-33.5);
    this->addChild(nickName,1);
    
    auto  headBg = Sprite::create("gameview/user_bg.png");
    headBg->setPosition(getPostionBySeat(clientSeatId).x,getPostionBySeat(clientSeatId).y-17);
    addChild(headBg);
    
    HeadImage* headImage = HeadImage::createByImage(playerInfo->getPicture(),Size(84,84));
    headImage->setPosition(getPostionBySeat(clientSeatId));
    headImage->setTag(9876);
    addChild(headImage);
    
    auto image = MenuItem::create(CC_CALLBACK_0(PlayerBase::showPlayerInfo, this));
    headimage = Menu::create(image,NULL);
    image->setContentSize(Size(84,84));
    headimage->setPosition(getPostionBySeat(clientSeatId));
    addChild(headimage);
    
    auto money = Sprite::create();
    money->setScale(1.25f);
    addChild(money);
    moneyNumber = Label::createWithSystemFont(StringUtils::format("%d", 0),"Arial",24);
    moneyNumber->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    moneyNumber->setColor(Color3B(242,227,75));
    addChild(moneyNumber);
    
    if (GAMEDATA::getInstance()->getMahjongRoomType()==MahjongRoom::privateRoom){
        money->setTexture("gameview/score_small.png");
        if(playerInfo->getScore()<0){
            moneyNumber->setString(StringUtils::format("-%d",abs(playerInfo->getScore())));
        }else{
            moneyNumber->setString(StringUtils::format("%d",playerInfo->getScore()));
        }
    }
    else {
        money->setTexture("gameview/gold_small.png");
        moneyNumber->setString(StringUtils::format("%d", playerInfo->getGold()));
    }
    money->setPosition(getPostionBySeat(clientSeatId).x -(moneyNumber->getContentSize().width)/2-18, getPostionBySeat(clientSeatId).y - 64);
    moneyNumber->setPosition(getPostionBySeat(clientSeatId).x -(moneyNumber->getContentSize().width-money->getContentSize().width)/2, getPostionBySeat(clientSeatId).y - 66);
    
    auto readyTitle = Sprite::create("gameview/ready_title.png");
    readyTitle->setTag(1001);
    readyTitle->setPosition(getReadyPosBySeat(clientSeatId));
    this->addChild(readyTitle);
    if(playerInfo->getIsReady()&&!GAMEDATA::getInstance()->getIsPlaying()){
        readyTitle->setVisible(true);
    }else{
        readyTitle->setVisible(false);
    }
    
    auto offLineIcon = Sprite::create("trusteeship/offline_icon.png");
    offLineIcon->setTag(1002);
    offLineIcon->setVisible(false);
    offLineIcon->setPosition(getPostionBySeat(clientSeatId).x+22,getPostionBySeat(clientSeatId).y-12);
    this->addChild(offLineIcon);
    
    auto tuoGuanIcon = Sprite::create("trusteeship/trustee_icon.png");
    tuoGuanIcon->setTag(1003);
    tuoGuanIcon->setVisible(false);
    tuoGuanIcon->setPosition(getPostionBySeat(clientSeatId).x+22,getPostionBySeat(clientSeatId).y-32);
    this->addChild(tuoGuanIcon);
    
//    Sprite* progressSprite = Sprite::create("gameview/time_clock_bg.png");
//    mProgressTimer = ProgressTimer::create(progressSprite);
//    mProgressTimer->setPosition(getPostionBySeat(clientSeatId));
//    this->addChild(mProgressTimer, 100);
//
//    timeClock = LabelAtlas::create(StringUtils::format("%d", mCDTime), "headportrait/time_clock_num.png", 19, 25, '0');
//    timeClock->setAnchorPoint(Point::ANCHOR_MIDDLE);
//    timeClock->setPosition(getPostionBySeat(clientSeatId));
//    this->addChild(timeClock, 101);
//    mProgressTimer->setVisible(false);
//    timeClock->setVisible(false);
    
    auto zhuang = Sprite::create("gameview/zhuang_icon.png");
    zhuang->setPosition(getZhuangPos(clientSeatId));
    zhuang->setTag(1314);
    zhuang->setVisible(false);
    addChild(zhuang);
    
    playerHua = Sprite::create("gameview/flower.png");
    addChild(playerHua);
    playerHuaCount = LabelAtlas::create(":0","gameview/num_hua_new.png",20,32,'0');
    playerHuaCount->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(playerHuaCount);
    Point pos = getHuaNumPos(SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), getPlayerInfo()->getSeatId()));
    playerHua->setPosition(pos);
    playerHuaCount->setPosition(pos.x + 28, pos.y);
    playerHua->setVisible(false);
    playerHuaCount->setVisible(false);
    

}
void PlayerBase::showPlayerZhuang(bool show){
    if(NULL != getChildByTag(1314)){
        getChildByTag(1314)->setVisible(show);
    }
}

void PlayerBase::showPlayerHua(int num){
    if(GAMEDATA::getInstance()->getGameType()==1||GAMEDATA::getInstance()->getGameType()==2
       ||GAMEDATA::getInstance()->getGameType()==5||GAMEDATA::getInstance()->getGameType()==6){
        playerHua->setVisible(true);
        playerHuaCount->setVisible(true);
        playerHuaCount->setString(StringUtils::format(":%d",num));
    }
}

void PlayerBase::replaceTurnHuaMingpai(PlayerTurnData data){
    if(data.replace==""){
        return;
    }
    std::vector<std::string> replace = StringUtil::split(data.replace, ",");
}

void PlayerBase::showPlayedJong(int ctype){
     setLastPoker(ctype);
     Audio::getInstance()->playMahjongSound(UserData::getInstance()->isFangYan(),ctype,getPlayerInfo()->getGender());
}

void PlayerBase::showPlayerPeng(PlayerCpgtData data,PlayerBase* playerBase){
     Audio::getInstance()->playSoundPeng(UserData::getInstance()->isFangYan(),getPlayerInfo()->getGender());
}

void PlayerBase::showPlayerGang(PlayerCpgtData data, PlayerBase* playerBase){
    Audio::getInstance()->playSoundGang(UserData::getInstance()->isFangYan(),getPlayerInfo()->getGender());
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

void PlayerBase::setIsTrusteeship(bool b){
    if(NULL != getChildByTag(1003)){
        getChildByTag(1003)->setVisible(b);
    }
}

void PlayerBase::showPlayerInfo(){
    OtherPlayerInfo* dialog = OtherPlayerInfo::create(getPlayerInfo());
    getParent()->addChild(dialog,100);//添加到父场景,为了解决图层错位的问题
}

void PlayerBase::updatePlayerInfo(int num){
    moneyNumber->setString(StringUtils::format("%d", num));
}

void PlayerBase::startTimeClockAnim(){
//    mCDTime = 15;
//    this->setTag(-1);
//    timeClock->setString(StringUtils::format("%d", mCDTime));
//    mProgressTimer->setVisible(true);
//    mProgressTimer->setType(ProgressTimer::Type::RADIAL);
//    mProgressTimer->stopAllActions();
//    mProgressTimer->setReverseProgress(true);
//    ActionInterval* action_progress_to = Sequence::create(ProgressFromTo::create(mCDTime, 100, 0), nullptr);
//    mProgressTimer->runAction(Sequence::create(action_progress_to, NULL));
//    schedule(schedule_selector(PlayerBase::updateTime), 1);
//    timeClock->setVisible(true);
}

void PlayerBase::startTimeClockAnim(int time, int type){
//    timeClock->setString(StringUtils::format("%d", time));
//    this->setTag(type);
//    mCDTime = time;
//    mProgressTimer->setVisible(true);
//    mProgressTimer->setType(ProgressTimer::Type::RADIAL);
//    mProgressTimer->stopAllActions();
//    mProgressTimer->setReverseProgress(true);
//    ActionInterval* action_progress_to = Sequence::create(ProgressFromTo::create(time, 100, 0), nullptr);
//    mProgressTimer->runAction(Sequence::create(action_progress_to, NULL));
//    schedule(schedule_selector(PlayerBase::updateTime), 1);
//    timeClock->setVisible(true);
}


void  PlayerBase::stopTimeClockAnim(){
//    mProgressTimer->setVisible(false);
//    timeClock->setVisible(false);
//    mCDTime = 9876543210;
//    unschedule(schedule_selector(PlayerBase::updateTime));
}

void PlayerBase::playerCpgAnim(CpgType cpgType, ClientSeatId type){
    PlayerCpgAnim* anim = PlayerCpgAnim::create(cpgType, type);
    addChild(anim,100);
    
}


void PlayerBase::updateTime(float dt){
//    mCDTime--;
//    if (mCDTime > 0){
//        timeClock->setString(StringUtils::format("%d", mCDTime));
//        if(mCDTime == 5){
//            Audio::getInstance()->playSoundDaoJiShi();
//        }
//        if(mCDTime == 2){
//            Audio::getInstance()->playSoundDaoJiShi();
//        }
//    }
//    else{
//        timeClock->setVisible(false);
//        if (mCDTime <=0){
//            doEventTimeOver(this->getTag());
//            unschedule(schedule_selector(PlayerBase::updateTime));
//        }
//    }
}

Jong* PlayerBase::getCurrentJong(){
    return playerPlayedJongs.at(playerPlayedJongs.size()-1);
}


Point PlayerBase::getHuaNumPos(int seatId){
    if (seatId == ClientSeatId::hero){
        return Vec2(50,195);
    }
    else if (seatId == ClientSeatId::left){
        return Vec2(50,440);
    }
    else if (seatId == ClientSeatId::opposite){
        return Vec2(960,695);
    }
    else if (seatId == ClientSeatId::right){
        return Vec2(1175,440);
    }
    else{
        log("PlayerBase getHuaNumPos 传入参数有误");
        return Vec2(0, 0);
    }
}

Point PlayerBase::getZhuangPos(int seatId){
    if (seatId == ClientSeatId::hero){
        return Vec2(105,160);
    }
    else if (seatId == ClientSeatId::left){
        return Vec2(105,405);
    }
    else if (seatId == ClientSeatId::opposite){
        return Vec2(1015,660);
    }
    else if (seatId == ClientSeatId::right){
        return Vec2(1230,405);
    }
    else{
        log("PlayerBase getZhuangPos 传入参数有误");
        return Vec2(0, 0);
    }
}

Point PlayerBase::getPostionBySeat(int seatId){
    if (seatId == ClientSeatId::hero){
        return Vec2(75, 130);
    }
    else if (seatId == ClientSeatId::right){
        return Vec2(1200, 375);
    }
    else if (seatId == ClientSeatId::opposite){
        return Vec2(985, 632);
    }
    else if (seatId == ClientSeatId::left){
        return Vec2(75, 375);
    }
    else{
        log("PlayerBase getPostionBySeat 传入参数有误");
        return Vec2(0, 0);
    }
}

Point PlayerBase::getReadyPosBySeat(int seatId){
    if (seatId == ClientSeatId::hero){
        return Vec2(145, 95);
    }
    else if (seatId == ClientSeatId::right){
        return Vec2(1110, 315);
    }
    else if (seatId == ClientSeatId::opposite){
        return Vec2(910, 600);
    }
    else if (seatId == ClientSeatId::left){
        return Vec2(145, 315);
    }
    else{
        return Vec2(0, 0);
    }
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

void PlayerBase::recoverLastPlayJong(){
    
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

void PlayerBase::playSoundHuPai(){
    Audio::getInstance()->playSoundHu(UserData::getInstance()->isFangYan(),getPlayerInfo()->getGender());
}

void PlayerBase::updatePlayerHeadImage(){
    if(NULL != getChildByTag(9876)){
        ((HeadImage*)getChildByTag(9876))->updateImageByName(playerInfo->getPicture());
    }
}




void PlayerBase::onEnter(){
    Layer::onEnter();
    
    roomChatListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_PLAYER_CHAT_NOTIFY, [=](EventCustom* event){
        if(playerInfo->getSeatId() == GAMEDATA::getInstance()->getHeroSeatId()){
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MSG_PLAYER_ROOM_CHAT_SHOW);
            chatShowLayer->removeAllChildren();//清空界面
            ChatData data = GAMEDATA::getInstance()->getChatData();
            int seatId = GAMEDATA::getInstance()->getHeroSeatId();
            for(auto play:GAMEDATA::getInstance()->getPlayersInfo()){
                if(play->getPoxiaoId() == data.poxiaoId){
                    seatId = play->getSeatId();
                }
            }
            if(data.mark ){
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
                VoiceMgr::getInstance()->writeVoice("record.amr",data.content);
#endif
                auto sound = Sprite::create("gameview/sound_pop.png");
                sound->setPosition(getVec2BySeatId(seatId));
                chatShowLayer->addChild(sound);
                if(SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), seatId) == ClientSeatId::left
                   || SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), seatId) == ClientSeatId::hero){
                    sound->setFlippedX(false);
                }else{
                    sound->setFlippedX(true);
                    if(SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), seatId) == ClientSeatId::opposite){
                        sound->setPosition(getVec2BySeatId(seatId).x+30,getVec2BySeatId(seatId).y-20);
                    }else{
                        sound->setPosition(getVec2BySeatId(seatId).x-20,getVec2BySeatId(seatId).y-20);
                    }
                    
                }
            }else{
                std::string content = data.content;
                checkQuickChatSound(content);
                vector<std::string> msgs =PlayerChatManage::getInstance()->splitContentByFace(content);
                RichText* text = RichText ::create();
                text->setAnchorPoint(Point::ANCHOR_MIDDLE);
                for(auto var : msgs){
                    
                    if(!PlayerChatManage::getInstance()->isFaceImage(var)){
                        RichElementText* element1 = RichElementText::create(1, Color3B(255,255,255), 255, var, "arial", 24);
                        text->pushBackElement(element1);
                        text->formatText();
                    }else{
                        RichElementImage* element2 = RichElementImage::create(1, Color3B(255,255,255), 255, PlayerChatManage::getInstance()->getFaceImageName(var));
                        text->pushBackElement(element2);
                        text->formatText();
                    }
                }
                text->setPosition(getVec2BySeatId(seatId));
                chatShowLayer->addChild(text,1);
                
                auto bob = ui::Scale9Sprite::create("chat/text_bob.png", Rect(0, 0, 66, 66), Rect(37, 0, 10, 0));
                bob->setContentSize(Size(text->getContentSize().width+20, 70));
                bob->setPosition(getVec2BySeatId(seatId));
                chatShowLayer->addChild(bob);
                if(SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), seatId) == ClientSeatId::left
                   || SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), seatId) == ClientSeatId::hero){
                    text->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
                    text->setPosition(Point(text->getPosition().x+10,text->getPosition().y+10));
                    bob->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
                }else{
                    text->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
                    text->setPosition(Point(text->getPosition().x-10,text->getPosition().y+10));
                    bob->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
                    bob->setFlippedX(true);
                }
                
            }
            schedule([=](float dt){
                chatShowLayer->removeAllChildren();
            },0,0,4.0,"removebob");
            
        }
    });
    wechatImageListener  = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_UPDATE_PLAYER_WECHAT_IMAGE, [=](EventCustom* event){
        updatePlayerHeadImage();
    });
}

void PlayerBase::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(roomChatListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(wechatImageListener);
    
}

void PlayerBase::checkQuickChatSound(std::string msg){
    if(strcmp(msg.c_str(), ChineseWord("text_info_1").c_str())== 0){
        Audio::getInstance()->playSoundQuickChat(UserData::getInstance()->isFangYan(),UserData::getInstance()->getGender(),1);
    }else if(strcmp(msg.c_str(), ChineseWord("text_info_2").c_str())== 0){
        Audio::getInstance()->playSoundQuickChat(UserData::getInstance()->isFangYan(),UserData::getInstance()->getGender(),2);
    }else if(strcmp(msg.c_str(), ChineseWord("text_info_3").c_str())== 0){
        Audio::getInstance()->playSoundQuickChat(UserData::getInstance()->isFangYan(),UserData::getInstance()->getGender(),3);
    }else if(strcmp(msg.c_str(), ChineseWord("text_info_4").c_str())== 0){
        Audio::getInstance()->playSoundQuickChat(UserData::getInstance()->isFangYan(),UserData::getInstance()->getGender(),4);
    }else if(strcmp(msg.c_str(), ChineseWord("text_info_5").c_str())== 0){
        Audio::getInstance()->playSoundQuickChat(UserData::getInstance()->isFangYan(),UserData::getInstance()->getGender(),5);
    }else if(strcmp(msg.c_str(), ChineseWord("text_info_6").c_str())== 0){
        Audio::getInstance()->playSoundQuickChat(UserData::getInstance()->isFangYan(),UserData::getInstance()->getGender(),6);
    }else if(strcmp(msg.c_str(), ChineseWord("text_info_7").c_str())== 0){
        Audio::getInstance()->playSoundQuickChat(UserData::getInstance()->isFangYan(),UserData::getInstance()->getGender(),7);
    }else if(strcmp(msg.c_str(), ChineseWord("text_info_8").c_str())== 0){
        Audio::getInstance()->playSoundQuickChat(UserData::getInstance()->isFangYan(),UserData::getInstance()->getGender(),8);
    }else if(strcmp(msg.c_str(), ChineseWord("text_info_9").c_str())== 0){
        Audio::getInstance()->playSoundQuickChat(UserData::getInstance()->isFangYan(),UserData::getInstance()->getGender(),9);
    }else if(strcmp(msg.c_str(), ChineseWord("text_info_10").c_str())== 0){
        Audio::getInstance()->playSoundQuickChat(UserData::getInstance()->isFangYan(),UserData::getInstance()->getGender(),10);
    }else if(strcmp(msg.c_str(), ChineseWord("text_info_11").c_str())== 0){
        Audio::getInstance()->playSoundQuickChat(UserData::getInstance()->isFangYan(),UserData::getInstance()->getGender(),11);
    }else if(strcmp(msg.c_str(), ChineseWord("text_info_12").c_str())== 0){
        Audio::getInstance()->playSoundQuickChat(UserData::getInstance()->isFangYan(),UserData::getInstance()->getGender(),12);
    }else if(strcmp(msg.c_str(), ChineseWord("text_info_13").c_str())== 0){
        Audio::getInstance()->playSoundQuickChat(UserData::getInstance()->isFangYan(),UserData::getInstance()->getGender(),13);
    }
}

