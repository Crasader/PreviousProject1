#include "game/mahjong/player/base/PlayerBase.h"
#include "game/mahjong/anim/PlayerCpgAnim.hpp"
#include "game/mahjong/dialog/playerinfo/OtherPlayerInfo.hpp"

Sprite* PlayerBase::biaoji = NULL;
Sprite* PlayerBase::currentBigJongBg = NULL;
Jong* PlayerBase::currentBigJong = NULL;

bool PlayerBase::init(){
	if (!Layer::init()){
		return false;
	}
	initData();
	return true;
}


void PlayerBase::initData(){
	mCDTime = 20;
	playerCpgRecords.clear();
	playerHandJongs.clear();
	playerPlayedJongs.clear();
	setHuaNum(0);
	setPlayerEnable(false);
    setStateCpg(false);
}


void PlayerBase::initPlayer(Player* playerInfo, int clientSeatId){
    setPlayerInfo(playerInfo);
	playerJongLayer = Layer::create();
	addChild(playerJongLayer);
    setClientSeat(clientSeatId);
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
	this->addChild(diamondNum);
    if (GAMEDATA::getInstance()->getIsPrivateRoom()){
		diamond->setTexture("gameview/score_small.png");
        if(playerInfo->getScore()>=0){
            diamondNum->setString(cocos2d::String::createWithFormat("%d", playerInfo->getScore())->_string);
        }else{
            diamondNum->setString(cocos2d::String::createWithFormat(";%d", abs(playerInfo->getScore()))->_string);
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
	setPlayerEnable(true);
}


void PlayerBase::showPlayerInfo(){
    OtherPlayerInfo* dialog = OtherPlayerInfo::create(getPlayerInfo());
    getParent()->addChild(dialog,100);//添加到父场景,解决图层错位的问题
}

void PlayerBase::updatePlayerInfo(int num){
    diamondNum->setString(cocos2d::String::createWithFormat("%d", num)->_string);
}


void PlayerBase::showPlayerHua(Point pos, int num){
	if (!getPlayerEnable()){
		return;
	}
	playerHua->setVisible(true);
	playerHuaCount->setVisible(true);
	playerHua->setPosition(pos);
	playerHuaCount->setPosition(pos.x + 30, pos.y);
	playerHuaCount->setString(cocos2d::String::createWithFormat(":%d",num)->_string);
    playerHuaCount->setScale(2.0f);
    playerHuaCount->setOpacity(77);
    playerHuaCount->runAction(Sequence::create(Spawn::create(FadeTo::create(4.0/24, 255),ScaleTo::create(4.0f/24, 1.0f), NULL), NULL));
}

void PlayerBase::showCurrentBigJong(int cType, Vec2 pos){
	currentBigJongBg->setVisible(true);
	currentBigJong->setVisible(true);
	currentBigJongBg->setPosition(pos);
	currentBigJong->showJong(playedshow,cType);
	currentBigJong->setPosition(pos.x,pos.y+15);
}

void PlayerBase::hideCurrentBigJong(){
	currentBigJongBg->setVisible(false);
	currentBigJong->setVisible(false);
}



void PlayerBase::startTimeClockAnim(){
	if (!getPlayerEnable()){
		return;
	}
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
	if (!getPlayerEnable()){
		return;
	}
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
	if (!getPlayerEnable()){
		return;
	}
	mProgressTimer->setVisible(false);
    timeClock->setVisible(false);
    mCDTime = 1000000;
	unschedule(schedule_selector(PlayerBase::updateTime));
}


void PlayerBase::setIsReady(bool b){
	if (!getPlayerEnable()){
		return;
	}
    if(NULL != getChildByTag(1001)){
        getChildByTag(1001)->setVisible(b);
    }
}

void PlayerBase::setIsTing(bool b){
	if (!getPlayerEnable()){
		return;
	}
	tingTitle->setVisible(b);
}

void PlayerBase::playerCpgAnim(CpgType cpgType, ClientSeatId type){
	if (!getPlayerEnable()){
		return;
	}
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
	if (!getPlayerEnable()){
		return NULL;
	}
	return playerPlayedJongs.at(playerPlayedJongs.size()-1);
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
		log("PlayerBase getPostionBySeat parameter seatId is error");
		return Vec2(0, 0);
	}
}

std::string PlayerBase::getHeadImageName(std::string id){
	std::string imageName = "gameview/head_image_1.png";
	if (!getPlayerEnable()){
		return imageName;
	}
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
	//TODO

}


void PlayerBase::recoverPlayed(std::string played){
	//TODO

}


void PlayerBase::recoverCpg(vector<PlayerChiData> chi,vector<PlayerPengData> peng,vector<PlayerGangData> gang,std::string angang){
	//TODO


}

void PlayerBase::recoverHand(std::string hand){
	//TODO
}


void PlayerBase::cleanPlayerUI(){

}
