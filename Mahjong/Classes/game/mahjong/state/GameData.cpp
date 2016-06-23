#include "game/mahjong/state/GameData.h"

GAMEDATA* GAMEDATA::_instance = 0;

GAMEDATA::GAMEDATA(){
	this->init();
}

void GAMEDATA::init(){
	this->setReplaceFlower(false);
	this->setOtherPlayed(false);
	this->setHeroturn(false);
	this->setIsPlaying(false);
	this->setIsTingProcess(false);
	this->setIsTingState(false);
	this->setIsTrusteeship(false);
	this->setIsRecover(false);
	this->setNeedAddPlayer(false);
    this->setContinueAgain(false);
    this->setHuangfan("0");
    this->setKaibao("0");
}

GAMEDATA* GAMEDATA::getInstance(){
	if (_instance == 0){
		_instance = new GAMEDATA();
	}
	return _instance;
}

void GAMEDATA::setSoundState(bool state) {
	UserDefault::getInstance()->setBoolForKey("soundState", state);
}

bool GAMEDATA::getSoundState() {
	return UserDefault::getInstance()->getBoolForKey("soundState", true);
}

void GAMEDATA::setMusicState(bool state) {
	UserDefault::getInstance()->setBoolForKey("musicState", state);
}

bool GAMEDATA::getMusicState() {
	return UserDefault::getInstance()->getBoolForKey("musicState", true);
}


void GAMEDATA::addPlayersInfo(Player* player){
	m_mutex.lock();
	playerVector.push_back(player);
	m_mutex.unlock();
}

void GAMEDATA::erasePlayersInfo(std::string poxiaoId){
	m_mutex.lock();
	vector<Player*>::iterator it;
	for (it = playerVector.begin(); it != playerVector.end();)
	{
		Player* pla = *it;
		if (pla->getPoxiaoId() == poxiaoId)
			it = playerVector.erase(it);
		else
			++it;
	}
	m_mutex.unlock();
}

void GAMEDATA::clearPlayersInfo(){
	m_mutex.lock();
	playerVector.clear();
	m_mutex.unlock();
}


vector<Player*> GAMEDATA::getPlayersInfo(){
	return playerVector;
}

std::vector<std::string> GAMEDATA::getHeroJongs(){
	return heroJongs;
}

void GAMEDATA::setHeroJongs(std::vector<std::string> heroJongs){
	this->heroJongs = heroJongs;
}

vector<GameResultData> GAMEDATA::getGameResults(){
	return gameResults;
}

void GAMEDATA::setGameResults(vector<GameResultData> results){
	this->gameResults.clear();
	this->gameResults = results;
}


FriendListData GAMEDATA::sortFriendList(FriendListData data){
    std::vector<FriendInfo> tempList;
    for (auto iter = data.friends.cbegin(); iter != data.friends.cend();)
    {
        FriendInfo info = *iter;
        if(!info.isOnLine){
            tempList.push_back(info);
            data.friends.erase(iter);
        }else{
            iter++;
        }
    }
    for(auto var:tempList){
        data.friends.push_back(var);
    }
    return data;
}