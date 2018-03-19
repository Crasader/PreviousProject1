#include "mahjong/gameview/player/PlayerLeft.h"
#include "mahjong/gameview/baseview/BaseView.h"
#include "mahjong/gameview/anim/HuaAnim.hpp"

bool PlayerLeft::init(){
    if (!PlayerBase::init()){
        
        return false;
    }
    playerCpgRecords.clear();
    playerHandJongs.clear();
    playerPlayedJongs.clear();
    playerHuaJongs.clear();
    setClientSeat(ClientSeatId::left);
    return true;
}


void PlayerLeft::drawHandJong(){
    for (int i = 0; i < this->jongNum; i++)
    {
        Jong* jong = Jong::create();
        jong->showJong(lefthand, -1,false);
        jong->setPosition(Point(LEFT_POS_X, LEFT_POS_Y + 35 * i));
        playerHandJongs.pushBack(jong);
        this->addChild(jong,60-i);
    }
}


void PlayerLeft::drawLeftPlayerTurn(){
    Jong* jong = Jong::create();
    jong->setTag(111);
    jong->showJong(lefthand, -1,false);
    jong->setPosition(Point(LEFT_POS_X, LEFT_POS_Y - 32));
    addChild(jong,61);
    playerHandJongs.pushBack(jong);
    MoveTo* move = MoveTo::create(0.2f, Point(LEFT_POS_X, LEFT_POS_Y - 35));
    ActionInterval* dou = EaseBackInOut::create(move);
    jong->runAction(dou);
}

void PlayerLeft::drawLeftPlayerTurnMingpai(int jongtype){
    Jong* jong = Jong::create();
    jong->setTag(111);
    jong->showJong(leftmingpai, jongtype,true);
    jong->setPosition(Point(LEFT_POS_X, LEFT_POS_Y - 32));
    addChild(jong,61);
    playerHandJongs.pushBack(jong);
}

void PlayerLeft::drawPlayedJong(int ctype){
    PlayerBase::showPlayedJong(ctype);
    Jong* lastPlayedJong = Jong::create();
    lastPlayedJong->showJong(leftplayed, ctype);
    lastPlayedJong->setPosition(Point(LEFT_POS_X, LEFT_POS_Y - 35));
    addChild(lastPlayedJong);
    Point startPoint = Point(LEFT_POS_X, LEFT_POS_Y - 35);
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

void PlayerLeft::drawPlayedJongMingpai(int ctype){
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
    lastPlayedJong->showJong(leftplayed, ctype);
    lastPlayedJong->setPosition(Point(LEFT_POS_X, LEFT_POS_Y - 35));
    addChild(lastPlayedJong);
    Point endPoint ;
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

void PlayerLeft::settleJongMingpai(){
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
        playerHandJongs.at(i)->setPosition(Point(LEFT_POS_X, LEFT_POS_Y + 35 * i));
        playerHandJongs.at(i)->setLocalZOrder(30-i);
    }
}


Point PlayerLeft::getHuaJongPos(int number){
    return Point(200, 680 - 17 * number);
}




Point PlayerLeft::getPlayedJongPos(int count){
    int row = count / 7;
    int line = count % 7;
    Point originPos = Point(405, 465);
    if (row <4) {
        return Point(originPos.x- 45 * row, originPos.y - 30 * line);
    }
    else {
        return Point(originPos.x - 45 * 3, originPos.y - 30 * line);
    }
}



void PlayerLeft:: showPlayedJongSign(bool show){
    if(playerPlayedJongs.size()>0)
        ((BaseView*)getParent())->setPlayPokerSignPosition(show,Point(getPlayedJongPos((int)playerPlayedJongs.size() - 1).x, getPlayedJongPos((int)playerPlayedJongs.size() - 1).y + 20));
}

void PlayerLeft::showPlayedBigJong(int type){
    ((BaseView*)getParent())->setBigJongPosition(type,ClientSeatId::left);
}

void PlayerLeft::hidePlayedBigJong(){
    ((BaseView*)getParent())->setBigJongEnable();
}

Point PlayerLeft::getCpgShowPostion(int index){
    return Point(LEFT_POS_X, 690 - index * 110);
}

void PlayerLeft::removeLastJong(){
    if(playerPlayedJongs.size()>0){
        playerPlayedJongs.at(playerPlayedJongs.size() - 1)->removeFromParent();
        playerPlayedJongs.popBack();
    }
}

void PlayerLeft::drawPlayerPeng(PlayerCpgtData data, PlayerBase* playerBase){
    PlayerBase::showPlayerPeng(data, playerBase);
    setStateCpg(true);
    for (int j = 0; j < 2; j++)
    {
        playerHandJongs.at(playerHandJongs.size()-1)->removeFromParent();
        playerHandJongs.eraseObject(playerHandJongs.at(playerHandJongs.size()-1));
    }
    playerBase->removeLastJong();
    PlayerCpgRecord record;
    record.type = CpgType::peng;
    Jong* jongpeng = Jong::create();
    int offsetY = 0;
    if(playerBase->getClientSeat() == ClientSeatId::opposite){
        offsetY = 32;
        jongpeng->showJong(leftcpgportrait, atoi(data.poker.c_str()));
        jongpeng->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x-5, getCpgShowPostion((int)playerCpgRecords.size()).y);
        jongpeng->setLocalZOrder((int)playerCpgRecords.size()*4);
    }else if(playerBase->getClientSeat() == ClientSeatId::right){
        jongpeng->showJong(leftcpglandscape, atoi(data.poker.c_str()));//碰到对家的牌位置特殊一些
        jongpeng->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x, getCpgShowPostion((int)playerCpgRecords.size()).y);
        offsetY = LEFT_POKER_WIDTH;
        jongpeng->setLocalZOrder((int)playerCpgRecords.size()*4);
    }else{
        offsetY = 0;
        jongpeng->showJong(leftcpgportrait, atoi(data.poker.c_str()));
        jongpeng->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x-5, getCpgShowPostion((int)playerCpgRecords.size()).y-61);
        jongpeng->setLocalZOrder((int)playerCpgRecords.size()*4+1);
    }
    addChild(jongpeng);
    
    record.pokersRecord.pushBack(jongpeng);
    std::vector<std::string> peng = StringUtil::split(data.peng, ",");
    for (int i = 0; i < peng.size(); i++){
        Jong* jong = Jong::create();
        jong->showJong(leftcpglandscape, atoi(peng.at(i).c_str()));
        jong->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x, getCpgShowPostion((int)playerCpgRecords.size()).y - LEFT_POKER_WIDTH * i-offsetY);
        addChild(jong, (int)playerCpgRecords.size()*4);
        record.pokersRecord.pushBack(jong);
    }
    playerCpgRecords.push_back(record);
}

void PlayerLeft::drawPlayerGang(PlayerCpgtData data, PlayerBase* playerBase){
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
        for (int j = 0; j < 3; j++)
        {
            playerHandJongs.at(playerHandJongs.size()-1)->removeFromParent();
            playerHandJongs.eraseObject(playerHandJongs.at(playerHandJongs.size()-1));
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
                    jong->showJong(leftcpglandscape, atoi(data.poker.c_str()));
                    jong->setPosition(getCpgShowPostion(i).x+4,getCpgShowPostion(i).y-20);
                    addChild(jong, (int)playerCpgRecords.size()*4);
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
                    jong->showJong(leftcpglandscape, atoi(gang.at(0).c_str()));
                    record.anGangFan = true;
                }else{
                    jong->showJong(leftangang, atoi(gang.at(0).c_str()),false);
                }
            }
            else{
                jong->showJong(leftcpglandscape, atoi(gang.at(0).c_str()));
            }
            if (i == 3){
                jong->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x + 2, getCpgShowPostion((int)playerCpgRecords.size()).y - 16);
            }
            else{
                jong->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x, getCpgShowPostion((int)playerCpgRecords.size()).y - LEFT_POKER_WIDTH * i);
            }
            addChild(jong, (int)playerCpgRecords.size()*4);
            record.pokersRecord.pushBack(jong);
        }
        if (data.playerGang.at(0).flag == 0){
            if(GAMEDATA::getInstance()->getGameType() == 3||GAMEDATA::getInstance()->getGameType() == 4){
                int clientId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), data.sId);
                if( clientId == ClientSeatId::hero){
                    auto arrow = Sprite::create("gameview/hu_jong_hint.png");
                    arrow->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x + 2, getCpgShowPostion((int)playerCpgRecords.size()).y - 16);
                    addChild(arrow,20);
                }else if( clientId == ClientSeatId::opposite){
                    auto arrow = Sprite::create("gameview/hu_jong_hint.png");
                    arrow->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x + 2, getCpgShowPostion((int)playerCpgRecords.size()).y - 16);
                    arrow->setRotation(180);
                    addChild(arrow,20);
                }else if( clientId == ClientSeatId::right){
                    auto arrow = Sprite::create("gameview/hu_jong_hint.png");
                    arrow->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x + 2, getCpgShowPostion((int)playerCpgRecords.size()).y - 16);
                    arrow->setRotation(270);
                    addChild(arrow,20);
                }
            }
        }
        playerCpgRecords.push_back(record);
    }
}


void PlayerLeft::drawPlayerMingpaiPeng(PlayerCpgtData data, PlayerBase* playerBase){
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
    int offsetY = 0;
    if(playerBase->getClientSeat() == ClientSeatId::opposite){
        offsetY = 32;
        jongpeng->showJong(leftcpgportrait, atoi(data.poker.c_str()));
        jongpeng->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x-5, getCpgShowPostion((int)playerCpgRecords.size()).y);
        jongpeng->setLocalZOrder((int)playerCpgRecords.size()*4);
    }else if(playerBase->getClientSeat() == ClientSeatId::right){
        jongpeng->showJong(leftcpglandscape, atoi(data.poker.c_str()));//碰到对家的牌位置特殊一些
        jongpeng->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x, getCpgShowPostion((int)playerCpgRecords.size()).y);
        offsetY = LEFT_POKER_WIDTH;
        jongpeng->setLocalZOrder((int)playerCpgRecords.size()*4);
    }else{
        offsetY = 0;
        jongpeng->showJong(leftcpgportrait, atoi(data.poker.c_str()));
        jongpeng->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x-5, getCpgShowPostion((int)playerCpgRecords.size()).y-61);
        jongpeng->setLocalZOrder((int)playerCpgRecords.size()*4+1);
    }
    addChild(jongpeng);
    record.pokersRecord.pushBack(jongpeng);
    std::vector<std::string> peng = StringUtil::split(data.peng, ",");
    for (int i = 0; i < peng.size(); i++){
        Jong* jong = Jong::create();
        jong->showJong(leftcpglandscape, atoi(peng.at(i).c_str()));
        jong->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x, getCpgShowPostion((int)playerCpgRecords.size()).y - LEFT_POKER_WIDTH * i-offsetY);
        addChild(jong, (int)playerCpgRecords.size()*4);
        record.pokersRecord.pushBack(jong);
    }
    playerCpgRecords.push_back(record);
}

void PlayerLeft::drawPlayerMingpaiGang(PlayerCpgtData data, PlayerBase* playerBase){
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
                    jong->showJong(leftcpglandscape, atoi(data.poker.c_str()));
                    jong->setPosition(getCpgShowPostion(i).x+4,getCpgShowPostion(i).y-20);
                    addChild(jong, (int)playerCpgRecords.size()*4);
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
                    jong->showJong(leftcpglandscape, atoi(gang.at(0).c_str()));
                    record.anGangFan = true;
                }else{
                    jong->showJong(leftangang, atoi(gang.at(0).c_str()),false);
                }
            }
            else{
                jong->showJong(leftcpglandscape, atoi(gang.at(0).c_str()));
            }
            if (i == 3){
                jong->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x + 2, getCpgShowPostion((int)playerCpgRecords.size()).y - 16);
            }
            else{
                jong->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x, getCpgShowPostion((int)playerCpgRecords.size()).y - LEFT_POKER_WIDTH * i);
            }
            addChild(jong, (int)playerCpgRecords.size()*4);
            record.pokersRecord.pushBack(jong);
        }
        if (data.playerGang.at(0).flag == 0){
            if(GAMEDATA::getInstance()->getGameType() == 3||GAMEDATA::getInstance()->getGameType() == 4){
                int clientId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), data.sId);
                if( clientId == ClientSeatId::hero){
                    auto arrow = Sprite::create("gameview/hu_jong_hint.png");
                    arrow->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x + 2, getCpgShowPostion((int)playerCpgRecords.size()).y - 16);
                    addChild(arrow,20);
                }else if( clientId == ClientSeatId::opposite){
                    auto arrow = Sprite::create("gameview/hu_jong_hint.png");
                    arrow->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x + 2, getCpgShowPostion((int)playerCpgRecords.size()).y - 16);
                    arrow->setRotation(180);
                    addChild(arrow,20);
                }else if( clientId == ClientSeatId::right){
                    auto arrow = Sprite::create("gameview/hu_jong_hint.png");
                    arrow->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x + 2, getCpgShowPostion((int)playerCpgRecords.size()).y - 16);
                    arrow->setRotation(270);
                    addChild(arrow,20);
                }
            }
        }
        playerCpgRecords.push_back(record);
    }
}


void PlayerLeft::recoverHua(std::string hua){
    playerHuaJongs.clear();
    if(hua == ""){
        showPlayerHua(0);
        return;
    }
    vector<std::string>  playeds = StringUtil::split(hua, ",");
    for (int i = 0; i < playeds.size(); i++){
        Jong* lastPlayedJong = Jong::create();
        lastPlayedJong->showJong(leftplayed, atoi(playeds.at(i).c_str()));
        lastPlayedJong->setPosition(getHuaJongPos((int)playerHuaJongs.size()));
        lastPlayedJong->setScale(0.55f);
        addChild(lastPlayedJong);
        playerHuaJongs.pushBack(lastPlayedJong);
    }
    showPlayerHua(playerHuaJongs.size());
}


void PlayerLeft::recoverPlayed(std::string played){
    playerPlayedJongs.clear();
    if(played == ""){
        return;
    }
    vector<std::string>  playeds = StringUtil::split(played, ",");
    for (int i = 0; i < playeds.size(); i++){
        Jong* lastPlayedJong = Jong::create();
        lastPlayedJong->showJong(leftplayed, atoi(playeds.at(i).c_str()));
        lastPlayedJong->setPosition(getPlayedJongPos((int)playerPlayedJongs.size()));
        addChild(lastPlayedJong);
        playerPlayedJongs.pushBack(lastPlayedJong);
    }
}


void PlayerLeft::recoverCpg(vector<PlayerChiData> chi,vector<PlayerPengData> peng,vector<PlayerGangData> gang,std::string angang){
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
                jong->showJong(j==0?leftcpgportrait:leftcpglandscape, atoi(chiPoker.at(j).c_str()));
                jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x- (j==0? 5:0), getCpgShowPostion((int)playerCpgRecords.size()).y- (j==0? 0:(LEFT_POKER_WIDTH * j+6))));
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
                if(seatId == ClientSeatId::opposite){
                    jong->showJong(j==0?leftcpgportrait:leftcpglandscape, atoi(peng.at(i).peng.c_str()));
                    jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x-(j==0?5:0),getCpgShowPostion((int)playerCpgRecords.size()).y-(j==0? 0:(LEFT_POKER_WIDTH * j+6))));
                    
                }else if(seatId == ClientSeatId::right){
                    jong->showJong(leftcpglandscape, atoi(peng.at(i).peng.c_str()));//碰到对家的牌位置特殊一些
                    jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x,getCpgShowPostion((int)playerCpgRecords.size()).y-(j==0?0:(27 * j))));
                }else {
                    jong->showJong(j==0?leftcpgportrait:leftcpglandscape, atoi(peng.at(i).peng.c_str()));
                    jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x-(j==0?5:0),getCpgShowPostion((int)playerCpgRecords.size()).y-(j==0?61:(LEFT_POKER_WIDTH * (j-1)))));
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
            record.gangValue = atoi(gang.at(0).gang.c_str());
            for(int j=0;j<4;j++){
                Jong* jong = Jong::create();
                jong->showJong(leftcpglandscape, atoi(gang.at(i).gang.c_str()));
                if (j == 3){
                    jong->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x + 2, getCpgShowPostion((int)playerCpgRecords.size()).y - LEFT_POKER_WIDTH);
                }
                else{
                    jong->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x, getCpgShowPostion((int)playerCpgRecords.size()).y - LEFT_POKER_WIDTH * j);
                }
                addChild(jong,10);
                record.pokersRecord.pushBack(jong);
            }
            if(atoi(gang.at(i).gaId.c_str()) != 0){
                if(GAMEDATA::getInstance()->getGameType() == 3||GAMEDATA::getInstance()->getGameType() == 4){
                    int clientId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), atoi(gang.at(i).gaId.c_str()));
                    if( clientId == ClientSeatId::hero){
                        auto arrow = Sprite::create("gameview/hu_jong_hint.png");
                        arrow->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x + 2, getCpgShowPostion((int)playerCpgRecords.size()).y - 16);
                        addChild(arrow,20);
                    }else if( clientId == ClientSeatId::opposite){
                        auto arrow = Sprite::create("gameview/hu_jong_hint.png");
                        arrow->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x + 2, getCpgShowPostion((int)playerCpgRecords.size()).y - 16);
                        arrow->setRotation(180);
                        addChild(arrow,20);
                    }else if( clientId == ClientSeatId::right){
                        auto arrow = Sprite::create("gameview/hu_jong_hint.png");
                        arrow->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x + 2, getCpgShowPostion((int)playerCpgRecords.size()).y - 16);
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
                    jong->showJong(leftcpglandscape, atoi(anganglist.at(0).c_str()));
                    record.anGangFan = true;
                }else{
                    jong->showJong(leftangang, atoi(anganglist.at(0).c_str()),false);
                }
                if (j == 3){
                    jong->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x + 2, getCpgShowPostion((int)playerCpgRecords.size()).y - LEFT_POKER_WIDTH);
                }
                else{
                    jong->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x, getCpgShowPostion((int)playerCpgRecords.size()).y - LEFT_POKER_WIDTH * j);
                }
                addChild(jong,10);
                record.pokersRecord.pushBack(jong);
                
            }
            playerCpgRecords.push_back(record);
        }
    }
}


void PlayerLeft::recoverHand(std::string hand){
    for(auto var:playerHandJongs){
        var->removeFromParent();
    }
    playerHandJongs.clear();
    vector<std::string>  hands = StringUtil::split(hand, ",");
    for (int i = 0; i < hands.size(); i++)
    {
        Jong* jong = Jong::create();
        jong->showJong(lefthand, -1,false);
        jong->setPosition(Point(LEFT_POS_X, LEFT_POS_Y + 35 * i));
        playerHandJongs.pushBack(jong);
        this->addChild(jong,60-i);
    }
}

void PlayerLeft::drawMingPai(std::string hand){
    
    for(auto var:playerHandJongs){
        var->removeFromParent();
    }
    playerHandJongs.clear();
    vector<std::string>  hands = StringUtil::split(hand, ",");
    for (int i = 0; i < hands.size(); i++)
    {
        Jong* jong = Jong::create();
        jong->showJong(leftmingpai, atoi(hands.at(i).c_str()),true);
        jong->setPosition(Point(LEFT_POS_X, LEFT_POS_Y + 35 * i));
        playerHandJongs.pushBack(jong);
        this->addChild(jong,60-i);
    }
}

void PlayerLeft::updateHandJongs(std::string jongs,bool hu){
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
                jong->showJong(leftplayed, atoi(pokers.at(i).c_str()));
                if(hu&&i==pokers.size()-1){
                    jong->setPosition(Point(LEFT_POS_X, LEFT_POS_Y + 30 * i+8));
                }else{
                    jong->setPosition(Point(LEFT_POS_X, LEFT_POS_Y + 30 * i));
                }
                playerHandJongs.pushBack(jong);
                addChild(jong,60-i);
            }
        }
    }
}

void PlayerLeft::doEventTimeOver(int type){
    if (type == -1){
        schedule([=](float dt){
            setIsOffLine(true);
        }, 0, 0, 7.0f, "xiaoxiao");
    }
}


void PlayerLeft::updateMingpai(Vector<Jong*> myPlayerHandJongs,Vector<Jong*> myPlayerPlayedJongs,Vector<Jong*> myPlayerHuaJongs,std::vector<PlayerCpgRecord> myPlayerCpgRecords){
    for(int i=0; i< playerHandJongs.size();i++){
        playerHandJongs.at(i)->removeFromParent();
    }
    playerHandJongs = myPlayerHandJongs;
    for(int i=0; i< playerHandJongs.size();i++){
        addChild(playerHandJongs.at(i),60-i);
        playerHandJongs.at(i)->setPosition(Point(LEFT_POS_X, LEFT_POS_Y + 35 * i));
    }
    for(int j=0; j< playerPlayedJongs.size();j++){
        playerPlayedJongs.at(j)->removeFromParent();
    }
    playerPlayedJongs = myPlayerPlayedJongs;
    for(int a = 0;a<myPlayerPlayedJongs.size();a++){
        addChild(myPlayerPlayedJongs.at(a));
        myPlayerPlayedJongs.at(a)->setPosition(getPlayedJongPos(a));
    }
    for(int m=0;m<playerHuaJongs.size();m++){
         playerHuaJongs.at(m)->removeFromParent();
    }
    playerHuaJongs = myPlayerHuaJongs;
    for (int i = 0; i < myPlayerHuaJongs.size(); i++){
        myPlayerHuaJongs.at(i)->setPosition(getHuaJongPos(i));
        addChild(myPlayerHuaJongs.at(i));
    }
    
    for(int b = 0;b<playerCpgRecords.size();b++){
        for(int c=0;c<playerCpgRecords.at(b).pokersRecord.size();c++){
            playerCpgRecords.at(b).pokersRecord.at(c)->removeFromParent();
        }
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
