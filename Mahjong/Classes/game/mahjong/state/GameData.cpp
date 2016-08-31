#include "game/mahjong/state/GameData.h"

GAMEDATA* GAMEDATA::_instance = 0;

GAMEDATA::GAMEDATA(){
	this->init();
}

void GAMEDATA::init(){
	setReplaceFlower(false);
	setOtherPlayed(false);
	setHeroturn(false);
	setIsPlaying(false);
	setIsTingProcess(false);
	setIsTingState(false);
	setIsTrusteeship(false);
	setIsRecover(false);
	setNeedAddPlayer(false);
    setContinueAgain(false);
    setIsResume(false);
    setIsGotoLobby(false);
    setNeedShowDiamondNotEnough(false);
    setHuangfan("0");
    setKaibao("0");
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
    log("add player room  %d",playerVector.size());
	m_mutex.unlock();
}

void GAMEDATA::erasePlayersInfo(std::string poxiaoId){
	m_mutex.lock();
	vector<Player*>::iterator it;
    for (it = playerVector.begin(); it != playerVector.end();)
	{
		Player* pla = *it;
        if (pla->getPoxiaoId() == poxiaoId){
            it = playerVector.erase(it);
        }
		else
			++it;
	}
	m_mutex.unlock();
}

void GAMEDATA::clearPlayersInfo(){
	m_mutex.lock();
    log("clear clear clear ");
	playerVector.clear();
	m_mutex.unlock();
}


vector<Player*> GAMEDATA::getPlayersInfo(){
	return playerVector;
}

std::vector<std::string> GAMEDATA::getHeroJongs(){
	return heroJongs;
}

void GAMEDATA::setHeroJongs(std::vector<std::string> jongs){
	heroJongs = jongs;
}

vector<GameResultData> GAMEDATA::getGameResults(){
	return gameResults;
}

void GAMEDATA::setGameResults(vector<GameResultData> results){
	gameResults.clear();
	gameResults = results;
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
