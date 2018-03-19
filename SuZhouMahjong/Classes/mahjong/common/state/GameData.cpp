#include "mahjong/common/state/GameData.h"

GAMEDATA* GAMEDATA::_instance = 0;

GAMEDATA::GAMEDATA(){
    this->init();
}

void GAMEDATA::init(){
    setReplaceFlower(false);
    setOtherPlayed(false);
    setHeroturn(false);
    setIsPlaying(false);
    setIsTrusteeship(false);
    setIsRecover(false);
    setContinueAgain(false);
    setIsGotoLobby(false);
    setIsInPay(false);
    setIsInGameScene(false);
    setShowRoomDismiss(false);
    setIsPayWayAA(false);
    setHaveShowNotice(false);
    setHasShowTurnTable(false);
    setNeedShowLastResult(false);
    setShowFangZhuDismiss(false);
    setTurnHeroCpg(false);
    setShowFuPanBtn(true);
    setIsSelected(true);
    setFangzhuLequan("0");
    setShowDissolveDialog(false);
    setLogingGame(false);
    setShowDialogType(-1);
    setScore(0);
    setNeedShowHongbaoResult(false);
    setShareHongBaoFriendState(0);
    setHasShowHongbaoResult(false);
    setNeedShowShareBtn(false);
    setIsInGame(true);
    setMyGameModel(GameModel::FOURPLAYER);
    setIsTurnTableShare(false);
    setHuiGuiLiBao("");
    setShowTurnTableState(0);
    setDissovleDialogRemove(true);
}

GAMEDATA* GAMEDATA::getInstance(){
    if (_instance == 0){
        _instance = new GAMEDATA();
    }
    return _instance;
}

void GAMEDATA::addPlayersInfo(PlayerInfo* player){
    m_mutex.lock();
    for(auto var : playerVector){
        if(var->getPoxiaoId() == player->getPoxiaoId()){
            m_mutex.unlock();
            return;
        }
    }
    playerVector.push_back(player);
    log("add player room  %d",(int)playerVector.size());
    m_mutex.unlock();
}

void GAMEDATA::erasePlayersInfo(std::string poxiaoId){
    m_mutex.lock();
    vector<PlayerInfo*>::iterator it;
    for (it = playerVector.begin(); it != playerVector.end();)
    {
        PlayerInfo* pla = *it;
        if (pla->getPoxiaoId() == poxiaoId){
            it = playerVector.erase(it);
        }
        else{
            ++it;
        }
    }
    m_mutex.unlock();
}

void GAMEDATA::clearPlayersInfo(){
    m_mutex.lock();
    log("clear clear clear ");
    playerVector.clear();
    m_mutex.unlock();
}


vector<PlayerInfo*> GAMEDATA::getPlayersInfo(){
    return playerVector;
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
