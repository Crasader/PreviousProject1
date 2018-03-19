#include "mahjong/gameview/player/PlayerOpposite.h"
#include "mahjong/gameview/baseview/BaseView.h"
#include "mahjong/gameview/anim/HuaAnim.hpp"

bool PlayerOpposite::init(){
    if (!PlayerBase::init()){
        return false;
    }
    playerCpgRecords.clear();
    playerHandJongs.clear();
    playerHuaJongs.clear();
    playerPlayedJongs.clear();
    setClientSeat(ClientSeatId::opposite);
    return true;
}


void PlayerOpposite::drawHandJong(){
    for (int i = 0; i < this->jongNum; i++)
    {
        Jong* jong = Jong::create();
        jong->showJong(oppositehand, -1,false);
        jong->setPosition(Point(OPPOSITE_POS_X + 43 * i, OPPOSITE_POS_Y));
        this->addChild(jong);
        playerHandJongs.pushBack(jong);
    }
}



void PlayerOpposite:: showPlayedJongSign(bool show){
    if(playerPlayedJongs.size()>0)
        ((BaseView*)getParent())->setPlayPokerSignPosition(show,Point(getPlayedJongPos((int)playerPlayedJongs.size() - 1).x, getPlayedJongPos((int)playerPlayedJongs.size() - 1).y + 20));
}

void PlayerOpposite::showPlayedBigJong(int type){
    ((BaseView*)getParent())->setBigJongPosition(type,ClientSeatId::opposite);
}

void PlayerOpposite::hidePlayedBigJong(){
    ((BaseView*)getParent())->setBigJongEnable();
}

Point PlayerOpposite::getCpgShowPostion(int index){
    return Point(860 - index * 125, 648);
}


void PlayerOpposite::drawOppositePlayerTurn(){
    Jong* jong = Jong::create();
    jong->setTag(111);
    jong->showJong(oppositehand, -1,false);
    jong->setPosition(Point(OPPOSITE_POS_X - 43, OPPOSITE_POS_Y + 20));
    addChild(jong);
    playerHandJongs.pushBack(jong);
    MoveTo* move = MoveTo::create(0.2f, Point(OPPOSITE_POS_X - 43, OPPOSITE_POS_Y));
    ActionInterval* dou = EaseBackInOut::create(move);
    jong->runAction(dou);
}

void PlayerOpposite::drawOppositePlayerTurnMingpai(int jongtype){
    Jong* jong = Jong::create();
    jong->setTag(111);
    jong->showJong(oppositemingpai, jongtype,true);
    jong->setPosition(Point(OPPOSITE_POS_X - 43, OPPOSITE_POS_Y));
    addChild(jong);
    playerHandJongs.pushBack(jong);
}

void PlayerOpposite::drawPlayedJong(int ctype){
    PlayerBase::showPlayedJong(ctype);
    Jong* lastPlayedJong = Jong::create();
    lastPlayedJong->showJong(oppositeplayed, ctype);
    lastPlayedJong->setPosition(Point(OPPOSITE_POS_X - 43, OPPOSITE_POS_Y));
    int mu = 10;
    if(GAMEDATA::getInstance()->getMyGameModel() == GameModel::TWOPLAYER){
        mu = 13;
    }
    if (playerPlayedJongs.size() / mu == 0){
        addChild(lastPlayedJong, 4);
    }
    else if (playerPlayedJongs.size() / mu == 1){
        addChild(lastPlayedJong, 3);
    }
    else if (playerPlayedJongs.size() / mu == 2){
        addChild(lastPlayedJong, 2);
    }else{
        addChild(lastPlayedJong, 1);
    }
    Point startPoint = Point(OPPOSITE_POS_X - 43, OPPOSITE_POS_Y);
    Point endPoint;
    if(ctype >= JongEnum::zhong&&(GAMEDATA::getInstance()->getGameType() == 1||GAMEDATA::getInstance()->getGameType()==2||(GAMEDATA::getInstance()->getGameType()==5 && lastPlayedJong->getJongType() != JongEnum::baida)||(GAMEDATA::getInstance()->getGameType()==6 && lastPlayedJong->getJongType() != JongEnum::baida))){
        lastPlayedJong->setScale(0.55f);
        endPoint = getHuaJongPos((int)playerHuaJongs.size());
        playerHuaJongs.pushBack(lastPlayedJong);
        showPlayerHua((int)playerHuaJongs.size());
    }else{
        endPoint = getPlayedJongPos((int)playerPlayedJongs.size());
        playerPlayedJongs.pushBack(lastPlayedJong);
    }
    CallFunc* callback = CallFunc::create([=](){
        lastPlayedJong->setPosition(endPoint);
        if(!(ctype >= JongEnum::zhong&&(GAMEDATA::getInstance()->getGameType() == 1||GAMEDATA::getInstance()->getGameType()==2||(GAMEDATA::getInstance()->getGameType()==5 && ctype != JongEnum::baida)||(GAMEDATA::getInstance()->getGameType()==6 && ctype != JongEnum::baida)))){
            showPlayedJongSign(true);
        }
    });
    Sequence* sequence = Sequence::create(Spawn::create(CallFunc::create([=](){
        if(NULL!=getChildByTag(111)){
            playerHandJongs.eraseObject((Jong*)getChildByTag(111));
            getChildByTag(111)->removeFromParent();
        }
        if(getStateCpg()){
            playerHandJongs.at(playerHandJongs.size() - 1)->removeFromParent();
            playerHandJongs.eraseObject(playerHandJongs.at(playerHandJongs.size() - 1));
            setStateCpg(false);
        }
    }), NULL) ,callback, NULL);
    lastPlayedJong->runAction(sequence);
    showPlayedBigJong(ctype);
}


void PlayerOpposite::drawPlayedJongMingpai(int ctype){
    Audio::getInstance()->playMahjongSound(UserData::getInstance()->isFangYan(),ctype,getPlayerInfo()->getGender());
    //移除手牌
    for(auto var : playerHandJongs){
        if(var->getJongType()== ctype){
            var->removeFromParent();
            playerHandJongs.eraseObject(var);
            break;
        }
    }
    
    Jong* lastPlayedJong = Jong::create();
    lastPlayedJong->showJong(oppositeplayed, ctype);
    lastPlayedJong->setPosition(Point(OPPOSITE_POS_X - 43, OPPOSITE_POS_Y));
    if (playerPlayedJongs.size() / 10 == 0){
        addChild(lastPlayedJong, 3);
    }
    else if (playerPlayedJongs.size() / 10 == 1){
        addChild(lastPlayedJong, 2);
    }
    else{
        addChild(lastPlayedJong, 1);
    }
    Point endPoint;
    if(ctype >= JongEnum::zhong&&(GAMEDATA::getInstance()->getGameType() == 1||GAMEDATA::getInstance()->getGameType()==2||(GAMEDATA::getInstance()->getGameType()==5 && lastPlayedJong->getJongType() != JongEnum::baida)||(GAMEDATA::getInstance()->getGameType()==6 && lastPlayedJong->getJongType() != JongEnum::baida))){
        lastPlayedJong->setScale(0.55f);
        endPoint = getHuaJongPos((int)playerHuaJongs.size());
        playerHuaJongs.pushBack(lastPlayedJong);
        showPlayerHua((int)playerHuaJongs.size());
    }else{
        endPoint = getPlayedJongPos((int)playerPlayedJongs.size());
        playerPlayedJongs.pushBack(lastPlayedJong);
    }
    lastPlayedJong->setPosition(endPoint);
    showPlayedBigJong(ctype);
    settleJongMingpai();
}


void PlayerOpposite::settleJongMingpai(){
    int size = (int)playerHandJongs.size();
    for (int i = 0; i < size - 1; i++) {
        for (int j = size - 1; j > i; j--) {
            if (playerHandJongs.at(j)->getJongType() < playerHandJongs.at(j - 1)->getJongType()) {
                playerHandJongs.swap(playerHandJongs.at(j), playerHandJongs.at(j - 1));
            }
        }
    }
    for (int i=0;i<playerHandJongs.size();i++)
    {
        playerHandJongs.at(i)->setPosition(Point(OPPOSITE_POS_X + 43 * i, OPPOSITE_POS_Y));
        playerHandJongs.at(i)->setLocalZOrder(30-i);
    }
}

Point PlayerOpposite::getHuaJongPos(int number){
    return Point(905 - 19 * number, 586);
}

Point PlayerOpposite::getPlayedJongPos(int count){
    int row ;
    int line;
    Point originPos;
    if(GAMEDATA::getInstance()->getMyGameModel() == GameModel::TWOPLAYER){
        row = count / 13;
        line = count % 13;
        originPos = Point(747, 504);
    }else{
        row = count / 10;
        line = count % 10;
        originPos = Point(800, 504);
    }
    if (row == 0) {
        return Point(originPos.x - 35 * line, originPos.y);
    }
    else {
        return Point(originPos.x - 35 * line, originPos.y + 40*row);
    }
}


void PlayerOpposite::removeLastJong(){
    if(playerPlayedJongs.size()>0){
        playerPlayedJongs.at(playerPlayedJongs.size() - 1)->removeFromParent();
        playerPlayedJongs.popBack();
    }
}


void PlayerOpposite::drawPlayerPeng(PlayerCpgtData data, PlayerBase* playerBase){
    PlayerBase::showPlayerPeng(data, playerBase);
    setStateCpg(true);
    for (int j = 0; j < 2; j++){
        playerHandJongs.at(playerHandJongs.size()-1)->removeFromParent();
        playerHandJongs.eraseObject(playerHandJongs.at(playerHandJongs.size()-1));
    }
    playerBase->removeLastJong();
    PlayerCpgRecord record;
    record.type = CpgType::peng;
    Jong* jongpeng = Jong::create();
    int offsetX = 0;
    if(playerBase->getClientSeat() == ClientSeatId::right){
        offsetX = 38;
        jongpeng->showJong(oppositecpglandscape, atoi(data.poker.c_str()));
        jongpeng->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x, getCpgShowPostion((int)playerCpgRecords.size()).y+5);
        jongpeng->setLocalZOrder(30 - (int)playerCpgRecords.size());
    }else if(playerBase->getClientSeat() == ClientSeatId::left){
        offsetX = 0;
        jongpeng->showJong(oppositecpglandscape, atoi(data.poker.c_str()));
        jongpeng->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x-73, getCpgShowPostion((int)playerCpgRecords.size()).y+5);
        jongpeng->setLocalZOrder(30 - (int)playerCpgRecords.size());
    }else{
        offsetX = OPPOSITE_POKER_WIDTH;
        jongpeng->showJong(oppositecpgportrait, atoi(data.poker.c_str()));
        jongpeng->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x, getCpgShowPostion((int)playerCpgRecords.size()).y);
        jongpeng->setLocalZOrder(30 - (int)playerCpgRecords.size()+1);
    }
    addChild(jongpeng);
    record.pokersRecord.pushBack(jongpeng);
    
    std::vector<std::string> peng = StringUtil::split(data.peng, ",");
    for (int i = 0; i < peng.size(); i++){
        Jong* jong = Jong::create();
        jong->showJong(oppositecpgportrait, atoi(peng.at(i).c_str()));
        jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x - OPPOSITE_POKER_WIDTH * i-offsetX, getCpgShowPostion((int)playerCpgRecords.size()).y));
        addChild(jong, 30 - (int)playerCpgRecords.size());
        record.pokersRecord.pushBack(jong);
    }
    playerCpgRecords.push_back(record);
}


void PlayerOpposite::drawPlayerGang(PlayerCpgtData data, PlayerBase* playerBase){
    PlayerBase::showPlayerGang(data,playerBase);
    if(data.playerGang.at(0).flag == 1){
        for (int j = 0; j < 4; j++){
            playerHandJongs.at(playerHandJongs.size() - 1)->removeFromParent();
            playerHandJongs.eraseObject(playerHandJongs.at(playerHandJongs.size() - 1));
        }
    }else if (data.playerGang.at(0).flag == 2){
        playerHandJongs.at(playerHandJongs.size()-1)->removeFromParent();
        playerHandJongs.eraseObject(playerHandJongs.at(playerHandJongs.size()-1));
    }
    else{
        for (int j = 0; j < 3; j++){
            playerHandJongs.at(playerHandJongs.size() - 1)->removeFromParent();
            playerHandJongs.eraseObject(playerHandJongs.at(playerHandJongs.size() - 1));
        }
    }
    std::vector<std::string> gang = StringUtil::split(data.playerGang.at(0).gang, ",");
    gang.push_back(data.poker);
    sort(gang.begin(), gang.end());
    PlayerCpgRecord record;
    if(data.playerGang.at(0).flag ==1){
        record.type = CpgType::angang;
    }else{
        record.type = CpgType::gang;
    }
    record.gangValue = atoi(gang.at(0).c_str());
    if (data.playerGang.at(0).flag == 2){
        for (int i = 0; i < playerCpgRecords.size(); i++)
        {
            if (playerCpgRecords.at(i).type == CpgType::peng){
                if (playerCpgRecords.at(i).pokersRecord.at(0)->getJongType() == atoi(data.poker.c_str())){
                    Jong* jong = Jong::create();
                    jong->showJong(oppositecpgportrait, atoi(data.poker.c_str()));
                    jong->setPosition(getCpgShowPostion(i).x-OPPOSITE_POKER_WIDTH-2,getCpgShowPostion(i).y-3);
                    addChild(jong, 35);
                    playerCpgRecords.at(i).type = CpgType::penggang;
                    playerCpgRecords.at(i).pokersRecord.pushBack(jong);
                }
            }
        }
    }
    else{
        if (data.playerGang.at(0).flag == 0){
            playerBase->removeLastJong();
        }
        for (int i = 0; i < 4; i++){
            Jong* jong = Jong::create();
            if (data.playerGang.at(0).flag == 1){
                if(i==3){
                    record.anGangFan = true;
                    jong->showJong(oppositecpgportrait, atoi(gang.at(0).c_str()));
                }else{
                    jong->showJong(oppositeangang, atoi(gang.at(0).c_str()),false);
                }
            }
            else{
                jong->showJong(oppositecpgportrait, atoi(gang.at(0).c_str()));
            }
            if (i == 3){
                jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x - 34, getCpgShowPostion((int)playerCpgRecords.size()).y - 2));
                addChild(jong, 10);
            }
            else{
                jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x - OPPOSITE_POKER_WIDTH * i, getCpgShowPostion((int)playerCpgRecords.size()).y));
                addChild(jong, 5);
            }
            record.pokersRecord.pushBack(jong);
        }
        if (data.playerGang.at(0).flag == 0){
            if(GAMEDATA::getInstance()->getGameType() == 3||GAMEDATA::getInstance()->getGameType() == 4){
                int clientId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), data.sId);
                if( clientId == ClientSeatId::left){
                    auto arrow = Sprite::create("gameview/hu_jong_hint.png");
                    arrow->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x - 34, getCpgShowPostion((int)playerCpgRecords.size()).y - 2));
                    arrow->setRotation(90);
                    addChild(arrow,20);
                }else if( clientId == ClientSeatId::hero){
                    auto arrow = Sprite::create("gameview/hu_jong_hint.png");
                    arrow->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x - 34, getCpgShowPostion((int)playerCpgRecords.size()).y - 2));
                    addChild(arrow,20);
                }else if( clientId == ClientSeatId::right){
                    auto arrow = Sprite::create("gameview/hu_jong_hint.png");
                    arrow->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x - 34, getCpgShowPostion((int)playerCpgRecords.size()).y - 2));
                    arrow->setRotation(270);
                    addChild(arrow,20);
                }
            }
        }
        playerCpgRecords.push_back(record);
    }
}


void PlayerOpposite::drawPlayerMingpaiPeng(PlayerCpgtData data, PlayerBase* playerBase){
    PlayerBase::showPlayerPeng(data, playerBase);
    setStateCpg(true);
    std::vector<string> chipai =  StringUtil::split(data.peng, ",");
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < playerHandJongs.size(); j++){
            if (atoi(chipai.at(0).c_str()) == playerHandJongs.at(j)->getJongType()){
                playerHandJongs.at(j)->removeFromParent();
                playerHandJongs.eraseObject(playerHandJongs.at(j));
                break;
            }
        }
    }
    settleJongMingpai();
    playerBase->removeLastJong();
    PlayerCpgRecord record;
    record.type = CpgType::peng;
    Jong* jongpeng = Jong::create();
    jongpeng->showJong(oppositecpglandscape, atoi(data.poker.c_str()));
    int offsetX = 0;
    if(playerBase->getClientSeat() == ClientSeatId::right){
        offsetX = 38;
        jongpeng->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x, getCpgShowPostion((int)playerCpgRecords.size()).y+5);
        jongpeng->setLocalZOrder(30 - (int)playerCpgRecords.size());
    }else if(playerBase->getClientSeat() == ClientSeatId::left){
        offsetX = 0;
        jongpeng->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x-73, getCpgShowPostion((int)playerCpgRecords.size()).y+5);
        jongpeng->setLocalZOrder(30 - (int)playerCpgRecords.size());
    }else{
        offsetX = OPPOSITE_POKER_WIDTH;
        jongpeng->showJong(oppositecpgportrait, atoi(data.poker.c_str()));
        jongpeng->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x, getCpgShowPostion((int)playerCpgRecords.size()).y);
        jongpeng->setLocalZOrder(30 - (int)playerCpgRecords.size()+1);
    }
    addChild(jongpeng);
    record.pokersRecord.pushBack(jongpeng);
    
    std::vector<std::string> peng = StringUtil::split(data.peng, ",");
    for (int i = 0; i < peng.size(); i++){
        Jong* jong = Jong::create();
        jong->showJong(oppositecpgportrait, atoi(peng.at(i).c_str()));
        jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x - OPPOSITE_POKER_WIDTH * i-offsetX, getCpgShowPostion((int)playerCpgRecords.size()).y));
        addChild(jong, 30 - (int)playerCpgRecords.size());
        record.pokersRecord.pushBack(jong);
    }
    playerCpgRecords.push_back(record);
}


void PlayerOpposite::drawPlayerMingpaiGang(PlayerCpgtData data, PlayerBase* playerBase){
    PlayerBase::showPlayerGang(data,playerBase);
    std::vector<string> chipai =  StringUtil::split(data.playerGang.at(0).gang, ",");
    for (int j = 0; j < playerHandJongs.size(); j++){
        if (atoi(chipai.at(0).c_str()) == playerHandJongs.at(j)->getJongType()){
            playerHandJongs.at(j)->removeFromParent();
            playerHandJongs.eraseObject(playerHandJongs.at(j));
            j--;
        }
    }
    settleJongMingpai();
    std::vector<std::string> gang = StringUtil::split(data.playerGang.at(0).gang, ",");
    gang.push_back(data.poker);
    sort(gang.begin(), gang.end());
    PlayerCpgRecord record;
    if(data.playerGang.at(0).flag ==1){
        record.type = CpgType::angang;
    }else{
        record.type = CpgType::gang;
    }
    record.gangValue = atoi(gang.at(0).c_str());
    if (data.playerGang.at(0).flag == 2){
        for (int i = 0; i < playerCpgRecords.size(); i++)
        {
            if (playerCpgRecords.at(i).type == CpgType::peng){
                if (playerCpgRecords.at(i).pokersRecord.at(0)->getJongType() == atoi(data.poker.c_str())){
                    Jong* jong = Jong::create();
                    jong->showJong(oppositecpgportrait, atoi(data.poker.c_str()));
                    jong->setPosition(getCpgShowPostion(i).x-OPPOSITE_POKER_WIDTH-2,getCpgShowPostion(i).y-3);
                    addChild(jong, 35);
                    playerCpgRecords.at(i).type = CpgType::penggang;
                    playerCpgRecords.at(i).pokersRecord.pushBack(jong);
                }
            }
        }
    }
    else{
        if (data.playerGang.at(0).flag == 0){
            playerBase->removeLastJong();
        }
        for (int i = 0; i < 4; i++){
            Jong* jong = Jong::create();
            if (data.playerGang.at(0).flag == 1){
                if(i==3){
                    record.anGangFan = true;
                    jong->showJong(oppositecpgportrait, atoi(gang.at(0).c_str()));
                }else{
                    jong->showJong(oppositeangang, atoi(gang.at(0).c_str()),false);
                }
            }
            else{
                jong->showJong(oppositecpgportrait, atoi(gang.at(0).c_str()));
            }
            if (i == 3){
                jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x - 34, getCpgShowPostion((int)playerCpgRecords.size()).y - 2));
                addChild(jong, 10);
            }
            else{
                jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x - OPPOSITE_POKER_WIDTH * i, getCpgShowPostion((int)playerCpgRecords.size()).y));
                addChild(jong, 5);
            }
            record.pokersRecord.pushBack(jong);
        }
        if (data.playerGang.at(0).flag == 0){
            if(GAMEDATA::getInstance()->getGameType() == 3||GAMEDATA::getInstance()->getGameType() == 4){
                int clientId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), data.sId);
                if( clientId == ClientSeatId::left){
                    auto arrow = Sprite::create("gameview/hu_jong_hint.png");
                    arrow->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x - 34, getCpgShowPostion((int)playerCpgRecords.size()).y - 2));
                    arrow->setRotation(90);
                    addChild(arrow,20);
                }else if( clientId == ClientSeatId::hero){
                    auto arrow = Sprite::create("gameview/hu_jong_hint.png");
                    arrow->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x - 34, getCpgShowPostion((int)playerCpgRecords.size()).y - 2));
                    addChild(arrow,20);
                }else if( clientId == ClientSeatId::right){
                    auto arrow = Sprite::create("gameview/hu_jong_hint.png");
                    arrow->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x - 34, getCpgShowPostion((int)playerCpgRecords.size()).y - 2));
                    arrow->setRotation(270);
                    addChild(arrow,20);
                }
            }
        }
        playerCpgRecords.push_back(record);
    }
}


void PlayerOpposite::recoverHua(std::string hua){
    playerHuaJongs.clear();
    if(hua == ""){
        showPlayerHua(0);
        return;
    }
    vector<std::string>  playeds = StringUtil::split(hua, ",");
    for (int i = 0; i < playeds.size(); i++){
        Jong* lastPlayedJong = Jong::create();
        lastPlayedJong->showJong(oppositeplayed, atoi(playeds.at(i).c_str()));
        lastPlayedJong->setScale(0.55f);
        lastPlayedJong->setPosition(getHuaJongPos((int)playerHuaJongs.size()));
        int mu = 10;
        if(GAMEDATA::getInstance()->getMyGameModel() == GameModel::TWOPLAYER){
            mu = 13;
        }
        if (playerHuaJongs.size() / mu == 0){
            addChild(lastPlayedJong, 4);
        }
        else if (playerHuaJongs.size() / mu == 1){
            addChild(lastPlayedJong, 3);
        }
        else if (playerHuaJongs.size() / mu == 2){
            addChild(lastPlayedJong, 2);
        }else{
            addChild(lastPlayedJong, 1);
        }
        playerHuaJongs.pushBack(lastPlayedJong);
    }
    showPlayerHua(playerHuaJongs.size());
}


void PlayerOpposite::updateHandJongs(std::string jongs,bool hu){
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
                jong->showJong(oppositeplayed, atoi(pokers.at(i).c_str()));
                if(hu&&i==pokers.size()-1){
                    jong->setPosition(Point(OPPOSITE_POS_X + 32 * i+8, OPPOSITE_POS_Y));
                }else{
                    jong->setPosition(Point(OPPOSITE_POS_X + 32 * i, OPPOSITE_POS_Y));
                }
                addChild(jong);
            }
        }
    }
}

void PlayerOpposite::recoverPlayed(std::string played){
    playerPlayedJongs.clear();
    if(played == ""){
        return;
    }
    vector<std::string>  playeds = StringUtil::split(played, ",");
    for (int i = 0; i < playeds.size(); i++){
        Jong* lastPlayedJong = Jong::create();
        lastPlayedJong->showJong(oppositeplayed, atoi(playeds.at(i).c_str()));
        lastPlayedJong->setPosition(getPlayedJongPos((int)playerPlayedJongs.size()));
        int mu = 10;
        if(GAMEDATA::getInstance()->getMyGameModel() == GameModel::TWOPLAYER){
            mu = 13;
        }
        if (playerPlayedJongs.size() / mu == 0){
            addChild(lastPlayedJong, 4);
        }
        else if (playerPlayedJongs.size() / mu == 1){
            addChild(lastPlayedJong, 3);
        }
        else if (playerPlayedJongs.size() / mu == 2){
            addChild(lastPlayedJong, 2);
        }else{
            addChild(lastPlayedJong, 1);
        }
        playerPlayedJongs.pushBack(lastPlayedJong);
    }
}


void PlayerOpposite::recoverCpg(vector<PlayerChiData> chi,vector<PlayerPengData> peng,vector<PlayerGangData> gang,std::string angang){
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
                jong->showJong(j==0?oppositecpglandscape:oppositecpgportrait, atoi(chiPoker.at(j).c_str()));
                jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x- (j==0? 0:(OPPOSITE_POKER_WIDTH * j+5)), getCpgShowPostion((int)playerCpgRecords.size()).y+ (j==0? 6:0)));
                addChild(jong,10);
                record.pokersRecord.pushBack(jong);
            }
            playerCpgRecords.push_back(record);
        }
    }
    if(peng.size()>0){
        for(int i=0;i<peng.size();i++){
            PlayerCpgRecord record;
            record.type = CpgType::peng;
            for(int j=0;j<3;j++){
                Jong* jong = Jong::create();
                jong->setLocalZOrder(10);
                int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), atoi(peng.at(i).peId.c_str()));
                if(seatId == ClientSeatId::left){
                     jong->showJong(j==0?oppositecpglandscape:oppositecpgportrait, atoi(peng.at(i).peng.c_str()));
                    jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x- (j==0? 73:(OPPOSITE_POKER_WIDTH *(j-1))), getCpgShowPostion((int)playerCpgRecords.size()).y+ (j==0? 6:0)));
                }else if(seatId == ClientSeatId::right){
                     jong->showJong(j==0?oppositecpglandscape:oppositecpgportrait, atoi(peng.at(i).peng.c_str()));
                    jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x- (j==0? 0:(OPPOSITE_POKER_WIDTH * j+5)), getCpgShowPostion((int)playerCpgRecords.size()).y+ (j==0? 6:0)));
                }else {
                    jong->showJong(oppositecpgportrait, atoi(peng.at(i).peng.c_str()));
                    jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x- (j==0? 0:(OPPOSITE_POKER_WIDTH * j)), getCpgShowPostion((int)playerCpgRecords.size()).y));
                    if(j==0)
                        jong->setLocalZOrder(12);
                }
                addChild(jong);
                record.pokersRecord.pushBack(jong);
            }
            playerCpgRecords.push_back(record);
        }
    }
    if(gang.size()>0){
        for(int i=0;i<gang.size();i++){
            PlayerCpgRecord record;
            record.type = CpgType::gang;
            for(int j=0;j<4;j++){
                Jong* jong = Jong::create();
                jong->showJong(oppositecpgportrait, atoi(gang.at(i).gang.c_str()));
                if (j == 3){
                    jong->setPosition(Point(getCpgShowPostion(playerCpgRecords.size()).x - OPPOSITE_POKER_WIDTH, getCpgShowPostion((int)playerCpgRecords.size()).y - 2));
                    this->addChild(jong, 10);
                }
                else{
                    jong->setPosition(Point(getCpgShowPostion(playerCpgRecords.size()).x - OPPOSITE_POKER_WIDTH * j, getCpgShowPostion((int)playerCpgRecords.size()).y));
                    addChild(jong, 5);
                }
                record.pokersRecord.pushBack(jong);
            }
            if(atoi(gang.at(i).gaId.c_str()) != 0){
                if(GAMEDATA::getInstance()->getGameType() == 3||GAMEDATA::getInstance()->getGameType() == 4){
                    int clientId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), atoi(gang.at(i).gaId.c_str()));
                    if( clientId == ClientSeatId::left){
                        auto arrow = Sprite::create("gameview/hu_jong_hint.png");
                        arrow->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x - 34, getCpgShowPostion((int)playerCpgRecords.size()).y - 2));
                        arrow->setRotation(90);
                        addChild(arrow,20);
                    }else if( clientId == ClientSeatId::hero){
                        auto arrow = Sprite::create("gameview/hu_jong_hint.png");
                        arrow->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x - 34, getCpgShowPostion((int)playerCpgRecords.size()).y - 2));
                        addChild(arrow,20);
                    }else if( clientId == ClientSeatId::right){
                        auto arrow = Sprite::create("gameview/hu_jong_hint.png");
                        arrow->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x - 34, getCpgShowPostion((int)playerCpgRecords.size()).y - 2));
                        arrow->setRotation(270);
                        addChild(arrow,20);
                    }
                }
            }
            playerCpgRecords.push_back(record);
        }
    }
    if(angang != ""){
        vector<std::string> anganglist  = StringUtil::split(angang, ",");
        for(int i=0;i<anganglist.size();i++){
            PlayerCpgRecord record;
            record.type = CpgType::angang;
            record.gangValue = atoi(anganglist.at(0).c_str());
            for(int j=0;j<4;j++){
                Jong* jong = Jong::create();
                if(j==3){
                    jong->showJong(oppositecpgportrait, atoi(anganglist.at(0).c_str()));
                    record.anGangFan = true;
                }else{
                    jong->showJong(oppositeangang, atoi(anganglist.at(0).c_str()),false);
                }
                
                if (j == 3){
                    jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x - OPPOSITE_POKER_WIDTH, getCpgShowPostion((int)playerCpgRecords.size()).y - 2));
                    this->addChild(jong, 10);
                }
                else{
                    jong->setPosition(Point(getCpgShowPostion(playerCpgRecords.size()).x - OPPOSITE_POKER_WIDTH * j, getCpgShowPostion((int)playerCpgRecords.size()).y));
                    this->addChild(jong, 5);
                }
                record.pokersRecord.pushBack(jong);
            }
            playerCpgRecords.push_back(record);
        }
    }
}

void PlayerOpposite::recoverHand(std::string hand){
    for(auto var:playerHandJongs){
        var->removeFromParent();
    }
    playerHandJongs.clear();
    vector<std::string>  hands = StringUtil::split(hand, ",");
    for (int i = 0; i < hands.size(); i++)
    {
        Jong* jong = Jong::create();
        jong->showJong(oppositehand, -1,false);
        jong->setPosition(Point(OPPOSITE_POS_X + 43 * i, OPPOSITE_POS_Y));
        addChild(jong);
        playerHandJongs.pushBack(jong);
    }
}

void PlayerOpposite::drawMingPai(std::string hand){
    for(auto var:playerHandJongs){
        var->removeFromParent();
    }
    playerHandJongs.clear();
    vector<std::string>  hands = StringUtil::split(hand, ",");
    for (int i = 0; i < hands.size(); i++)
    {
        Jong* jong = Jong::create();
        jong->showJong(oppositemingpai, atoi(hands.at(i).c_str()),true);
        jong->setPosition(Point(OPPOSITE_POS_X + 43 * i, OPPOSITE_POS_Y));
        addChild(jong);
        playerHandJongs.pushBack(jong);
    }
}

void PlayerOpposite::doEventTimeOver(int type){
    if (type == -1){
        schedule([=](float dt){
            setIsOffLine(true);
        }, 0, 0, 7.0f, "xiaoxiao");
    }
}

void PlayerOpposite::updateMingpai(Vector<Jong*> myPlayerHandJongs,Vector<Jong*> myPlayerPlayedJongs,Vector<Jong*> myPlayerHuaJongs,std::vector<PlayerCpgRecord> myPlayerCpgRecords){
    for(int i=0;i< playerHandJongs.size();i++){
        playerHandJongs.at(i)->removeFromParent();
    }
    playerHandJongs = myPlayerHandJongs;
    for(int i=0;i< playerHandJongs.size();i++){
        addChild(playerHandJongs.at(i),30-i);
        playerHandJongs.at(i)->setPosition(Point(OPPOSITE_POS_X + 43 * i, OPPOSITE_POS_Y));
    }
    for(int j=0; j< playerPlayedJongs.size();j++){
        playerPlayedJongs.at(j)->removeFromParent();
    }
    playerPlayedJongs = myPlayerPlayedJongs;
    for(int a = 0;a<myPlayerPlayedJongs.size();a++){
        addChild(myPlayerPlayedJongs.at(a));
        myPlayerPlayedJongs.at(a)->setPosition(getPlayedJongPos(a));
    }
    for(int b = 0;b<playerCpgRecords.size();b++){
        for(int c=0;c<playerCpgRecords.at(b).pokersRecord.size();c++){
            playerCpgRecords.at(b).pokersRecord.at(c)->removeFromParent();
        }
    }
    for(int m=0;m<playerHuaJongs.size();m++){
        playerHuaJongs.at(m)->removeFromParent();
    }
    playerHuaJongs = myPlayerHuaJongs;
    for (int i = 0; i < myPlayerHuaJongs.size(); i++){
        myPlayerHuaJongs.at(i)->setPosition(getHuaJongPos(i));
        addChild(myPlayerHuaJongs.at(i));
    }
    playerCpgRecords = myPlayerCpgRecords;
    for(int e = 0;e<myPlayerCpgRecords.size();e++){
        for(int f=0;f<myPlayerCpgRecords.at(e).pokersRecord.size();f++){
            myPlayerCpgRecords.at(e).pokersRecord.at(f)->removeFromParent();
            addChild(myPlayerCpgRecords.at(e).pokersRecord.at(f));
        }
    }
    showPlayedJongSign(false);
    hidePlayedBigJong();
}
