#include "mahjong/gameview/player/PlayerRight.h"
#include "mahjong/gameview/baseview/BaseView.h"
#include "mahjong/gameview/anim/HuaAnim.hpp"


bool PlayerRight::init(){
    if (!PlayerBase::init()){
        
        return false;
    }
    playerCpgRecords.clear();
    playerHandJongs.clear();
    playerPlayedJongs.clear();
    playerHuaJongs.clear();
    setClientSeat(ClientSeatId::right);
    return true;
}


void PlayerRight::drawHandJong(){
    for (int i = 0; i < this->jongNum; i++)
    {
        Jong* jong = Jong::create();
        jong->showJong(righthand, -1,false);
        jong->setPosition(Point(RIGHT_POS_X, RIGHT_POS_Y - 35 * i));
        this->addChild(jong, 2);
        playerHandJongs.pushBack(jong);
    }
}


void PlayerRight::drawRightPlayerTurn(){
    Jong* jong = Jong::create();
    jong->setTag(111);
    jong->showJong(righthand, -1,false);
    jong->setPosition(Point(RIGHT_POS_X, RIGHT_POS_Y + 45));
    addChild(jong, 1);
    playerHandJongs.pushBack(jong);
    MoveTo* move = MoveTo::create(0.2f, Point(RIGHT_POS_X, RIGHT_POS_Y + 35));
    ActionInterval* dou = EaseBackInOut::create(move);
    jong->runAction(dou);
}

void PlayerRight::drawRightPlayerTurnMingpai(int jongtype){
    Jong* jong = Jong::create();
    jong->setTag(111);
    jong->showJong(rightmingpai, jongtype,true);
    jong->setPosition(Point(RIGHT_POS_X, RIGHT_POS_Y + 45));
    addChild(jong, -1);
    playerHandJongs.pushBack(jong);
}

void PlayerRight::drawPlayedJong(int ctype){

    PlayerBase::showPlayedJong(ctype);
    Jong* lastPlayedJong = Jong::create();
    lastPlayedJong->showJong(rightplayed, ctype);
    lastPlayedJong->setPosition(Point(RIGHT_POS_X, RIGHT_POS_Y + 35));
    int tar = playerPlayedJongs.size() % 7;
    addChild(lastPlayedJong, 7 - tar);
    Point startPoint = Point(RIGHT_POS_X, RIGHT_POS_Y + 35);
    Point endPoint;
    if(ctype >= JongEnum::zhong&&(GAMEDATA::getInstance()->getGameType() == 1||GAMEDATA::getInstance()->getGameType()==2||(GAMEDATA::getInstance()->getGameType()==5 && lastPlayedJong->getJongType() != JongEnum::baida)||(GAMEDATA::getInstance()->getGameType()==6 && lastPlayedJong->getJongType() != JongEnum::baida))){
        lastPlayedJong->setScale(0.55f);
        lastPlayedJong->setLocalZOrder(10);
        endPoint = getHuaJongPos((int)playerHuaJongs.size());
        playerHuaJongs.pushBack(lastPlayedJong);
        showPlayerHua(playerHuaJongs.size());
        
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

void PlayerRight::drawPlayedJongMingpai(int ctype){
 Audio::getInstance()->playMahjongSound(UserData::getInstance()->isFangYan(),ctype,getPlayerInfo()->getGender());
    for(auto var : playerHandJongs){
        if(var->getJongType()== ctype){
            var->removeFromParent();
            playerHandJongs.eraseObject(var);
            break;
        }
    }
    Jong* lastPlayedJong = Jong::create();
    lastPlayedJong->showJong(rightplayed, ctype);
    lastPlayedJong->setPosition(Point(RIGHT_POS_X, RIGHT_POS_Y + 35));
    int tar = playerPlayedJongs.size() % 7;
    addChild(lastPlayedJong, 7 - tar);

    Point endPoint;
    if(ctype >= JongEnum::zhong&&(GAMEDATA::getInstance()->getGameType() == 1||GAMEDATA::getInstance()->getGameType()==2||(GAMEDATA::getInstance()->getGameType()==5 && lastPlayedJong->getJongType() != JongEnum::baida)||(GAMEDATA::getInstance()->getGameType()==6 && lastPlayedJong->getJongType() != JongEnum::baida))){
        lastPlayedJong->setScale(0.55f);
        lastPlayedJong->setLocalZOrder(10);
        endPoint = getHuaJongPos((int)playerHuaJongs.size());
        playerHuaJongs.pushBack(lastPlayedJong);
        showPlayerHua(playerHuaJongs.size());
    }else{
        endPoint = getPlayedJongPos((int)playerPlayedJongs.size());
        playerPlayedJongs.pushBack(lastPlayedJong);
    }
    lastPlayedJong->setPosition(endPoint);
    showPlayedBigJong(ctype);
    settleJongMingpai();
}

void PlayerRight::settleJongMingpai(){
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
        playerHandJongs.at(i)->setPosition(Point(RIGHT_POS_X, RIGHT_POS_Y - 35 * i));
        playerHandJongs.at(i)->setLocalZOrder(i);
    }
}

Point PlayerRight::getHuaJongPos(int number){
    return Point(1080, 670 - 18 * number);
}


Point PlayerRight::getPlayedJongPos(int count){
    int row = count / 7;
    int line = count % 7;
    Point originPos = Point(875, 325);
    if (row < 4) {
        return Point(originPos.x + 45*row, originPos.y + 30 * line);
    }
    else {
        return Point(originPos.x + 45 * 3, originPos.y + 30 * line);
    }
}


void PlayerRight:: showPlayedJongSign(bool show){
    if(playerPlayedJongs.size()>0)
        ((BaseView*)getParent())->setPlayPokerSignPosition(show,Point(getPlayedJongPos((int)playerPlayedJongs.size() - 1).x, getPlayedJongPos((int)playerPlayedJongs.size() - 1).y + 20));
}

void PlayerRight::showPlayedBigJong(int type){
    ((BaseView*)getParent())->setBigJongPosition(type,ClientSeatId::right);
}

Point PlayerRight::getCpgShowPostion(int index){
    return Point(RIGHT_POS_X,180 + index * 110);
}

void PlayerRight::hidePlayedBigJong(){
    ((BaseView*)getParent())->setBigJongEnable();
}

void PlayerRight::removeLastJong(){
    if(playerPlayedJongs.size()>0){
        playerPlayedJongs.at(playerPlayedJongs.size() - 1)->removeFromParent();
        playerPlayedJongs.popBack();
    }
}


void PlayerRight::drawPlayerPeng(PlayerCpgtData data, PlayerBase* playerBase){
    PlayerBase::showPlayerPeng(data, playerBase);
    setStateCpg(true);
    for (int j = 0; j < 2; j++){
        playerHandJongs.at(playerHandJongs.size() - 1)->removeFromParent();
        playerHandJongs.eraseObject(playerHandJongs.at(playerHandJongs.size() - 1));
    }
    playerBase->removeLastJong();
    PlayerCpgRecord record;
    record.type = CpgType::peng;
    Jong* jongpeng = Jong::create();
    int offsetY = 0;
    if(playerBase->getClientSeat() == ClientSeatId::opposite){
        offsetY = 0;
        jongpeng->showJong(rightcpgportrait, atoi(data.poker.c_str()));
        jongpeng->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x+4, getCpgShowPostion((int)playerCpgRecords.size()).y+60);
        jongpeng->setLocalZOrder(30 - (int)playerCpgRecords.size()*3-2);
    }else if(playerBase->getClientSeat() == ClientSeatId::left){
        offsetY = RIGHT_POKER_WIDTH;
        jongpeng->showJong(rightcpglandscape, atoi(data.poker.c_str()));
        jongpeng->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x, getCpgShowPostion((int)playerCpgRecords.size()).y);
        jongpeng->setLocalZOrder(30 - (int)playerCpgRecords.size()*3+1);
    }else{
        offsetY = 33;
        jongpeng->showJong(rightcpgportrait, atoi(data.poker.c_str()));
        jongpeng->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x+4, getCpgShowPostion((int)playerCpgRecords.size()).y);
        jongpeng->setLocalZOrder(30 - (int)playerCpgRecords.size()*3+1);
    }
    addChild(jongpeng);
    record.pokersRecord.pushBack(jongpeng);
    std::vector<std::string> peng = StringUtil::split(data.peng, ",");
    for (int i = 0; i < peng.size(); i++){
        Jong* jong = Jong::create();
        jong->showJong(rightcpglandscape, atoi(peng.at(i).c_str()));
        jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x, getCpgShowPostion((int)playerCpgRecords.size()).y + i * RIGHT_POKER_WIDTH+offsetY));
        addChild(jong, 30 - (int)playerCpgRecords.size()*3-i);
        record.pokersRecord.pushBack(jong);
    }
    playerCpgRecords.push_back(record);
}

void PlayerRight::drawPlayerGang(PlayerCpgtData data, PlayerBase* playerBase){
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
        for (int j = 0; j <3; j++){
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
        for (int i = 0; i < this->playerCpgRecords.size(); i++)
        {
            if (playerCpgRecords.at(i).type == CpgType::peng){
                if (playerCpgRecords.at(i).pokersRecord.at(0)->getJongType() == atoi(data.poker.c_str())){
                    Jong* jong = Jong::create();
                    jong->showJong(rightcpglandscape, atoi(data.poker.c_str()));
                    jong->setPosition(getCpgShowPostion(i).x-4,getCpgShowPostion(i).y+34);
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
                    jong->showJong(rightcpglandscape, atoi(gang.at(0).c_str()));
                    record.anGangFan = true;
                }else{
                    jong->showJong(rightangang, atoi(gang.at(0).c_str()),false);
                }
            }
            else{
                jong->showJong(rightcpglandscape, atoi(gang.at(0).c_str()));
            }
            if (i == 3){
                
                jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x-3, getCpgShowPostion((int)playerCpgRecords.size()).y +  34));
                addChild(jong, 30);
            }
            else{
                jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x, getCpgShowPostion((int)playerCpgRecords.size()).y + i * RIGHT_POKER_WIDTH));
                addChild(jong, 30 - (int)playerCpgRecords.size()*3-i);
            }
            record.pokersRecord.pushBack(jong);
        }
        if (data.playerGang.at(0).flag == 0){
            if(GAMEDATA::getInstance()->getGameType() == 3||GAMEDATA::getInstance()->getGameType() == 4){
                int clientId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), data.sId);
                if( clientId == ClientSeatId::left){
                    auto arrow = Sprite::create("gameview/hu_jong_hint.png");
                    arrow->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x-3, getCpgShowPostion((int)playerCpgRecords.size()).y +  34));
                    arrow->setRotation(90);
                    addChild(arrow,40);
                }else if( clientId == ClientSeatId::opposite){
                    auto arrow = Sprite::create("gameview/hu_jong_hint.png");
                    arrow->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x-3, getCpgShowPostion((int)playerCpgRecords.size()).y +  34));
                    arrow->setRotation(180);
                    addChild(arrow,40);
                }else if( clientId == ClientSeatId::hero){
                    auto arrow = Sprite::create("gameview/hu_jong_hint.png");
                    arrow->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x-3, getCpgShowPostion((int)playerCpgRecords.size()).y +  34));
                    //                    arrow->setRotation(270);
                    addChild(arrow,40);
                }
            }
        }
        playerCpgRecords.push_back(record);
    }
}

void PlayerRight::drawPlayerMingpaiPeng(PlayerCpgtData data, PlayerBase* playerBase){
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
        offsetY = 0;
        jongpeng->showJong(rightcpgportrait, atoi(data.poker.c_str()));
        jongpeng->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x+4, getCpgShowPostion((int)playerCpgRecords.size()).y+60);
        jongpeng->setLocalZOrder(30 - (int)playerCpgRecords.size()*3-2);
    }else if(playerBase->getClientSeat() == ClientSeatId::left){
        offsetY = RIGHT_POKER_WIDTH;
        jongpeng->showJong(rightcpglandscape, atoi(data.poker.c_str()));
        jongpeng->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x, getCpgShowPostion((int)playerCpgRecords.size()).y);
        jongpeng->setLocalZOrder(30 - (int)playerCpgRecords.size()*3+1);
    }else{
        offsetY = 33;
        jongpeng->showJong(rightcpgportrait, atoi(data.poker.c_str()));
        jongpeng->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x+4, getCpgShowPostion((int)playerCpgRecords.size()).y);
        jongpeng->setLocalZOrder(30 - (int)playerCpgRecords.size()*3+1);
    }
    addChild(jongpeng);
    record.pokersRecord.pushBack(jongpeng);
    std::vector<std::string> peng = StringUtil::split(data.peng, ",");
    for (int i = 0; i < peng.size(); i++){
        Jong* jong = Jong::create();
        jong->showJong(rightcpglandscape, atoi(peng.at(i).c_str()));
        jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x, getCpgShowPostion((int)playerCpgRecords.size()).y + i * RIGHT_POKER_WIDTH+offsetY));
        addChild(jong, 30 - (int)playerCpgRecords.size()*3-i);
        record.pokersRecord.pushBack(jong);
    }
    playerCpgRecords.push_back(record);
}

void PlayerRight::drawPlayerMingpaiGang(PlayerCpgtData data, PlayerBase* playerBase){
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
        for (int i = 0; i < this->playerCpgRecords.size(); i++)
        {
            if (playerCpgRecords.at(i).type == CpgType::peng){
                if (playerCpgRecords.at(i).pokersRecord.at(0)->getJongType() == atoi(data.poker.c_str())){
                    Jong* jong = Jong::create();
                    jong->showJong(rightcpglandscape, atoi(data.poker.c_str()));
                    jong->setPosition(getCpgShowPostion(i).x-4,getCpgShowPostion(i).y+34);
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
                    jong->showJong(rightcpglandscape, atoi(gang.at(0).c_str()));
                    record.anGangFan = true;
                }else{
                    jong->showJong(rightangang, atoi(gang.at(0).c_str()),false);
                }
            }
            else{
                jong->showJong(rightcpglandscape, atoi(gang.at(0).c_str()));
            }
            if (i == 3){
                
                jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x-3, getCpgShowPostion((int)playerCpgRecords.size()).y +  34));
                addChild(jong, 30);
            }
            else{
                jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x, getCpgShowPostion((int)playerCpgRecords.size()).y + i * RIGHT_POKER_WIDTH));
                addChild(jong, 30 - (int)playerCpgRecords.size()*3-i);
            }
            record.pokersRecord.pushBack(jong);
        }
        if (data.playerGang.at(0).flag == 0){
            if(GAMEDATA::getInstance()->getGameType() == 3||GAMEDATA::getInstance()->getGameType() == 4){
                int clientId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), data.sId);
                if( clientId == ClientSeatId::left){
                    auto arrow = Sprite::create("gameview/hu_jong_hint.png");
                    arrow->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x-3, getCpgShowPostion((int)playerCpgRecords.size()).y +  34));
                    arrow->setRotation(90);
                    addChild(arrow,40);
                }else if( clientId == ClientSeatId::opposite){
                    auto arrow = Sprite::create("gameview/hu_jong_hint.png");
                    arrow->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x-3, getCpgShowPostion((int)playerCpgRecords.size()).y +  34));
                    arrow->setRotation(180);
                    addChild(arrow,40);
                }else if( clientId == ClientSeatId::hero){
                    auto arrow = Sprite::create("gameview/hu_jong_hint.png");
                    arrow->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x-3, getCpgShowPostion((int)playerCpgRecords.size()).y +  34));
                    addChild(arrow,40);
                }
            }
        }
        playerCpgRecords.push_back(record);
    }
}


void PlayerRight::recoverHua(std::string hua){
    playerHuaJongs.clear();
    if(hua == ""){
        showPlayerHua(0);
        return;
    }
    vector<std::string>  playeds = StringUtil::split(hua, ",");
    for (int i = 0; i < playeds.size(); i++){
        Jong* lastPlayedJong = Jong::create();
        lastPlayedJong->showJong(rightplayed, atoi(playeds.at(i).c_str()));
        lastPlayedJong->setPosition(getHuaJongPos((int)playerHuaJongs.size()));
        lastPlayedJong->setScale(0.55f);
        addChild(lastPlayedJong, 10);
        playerHuaJongs.pushBack(lastPlayedJong);
    }
    showPlayerHua(playerHuaJongs.size());
}


void PlayerRight::recoverPlayed(std::string played){
    playerPlayedJongs.clear();
    if(played == ""){
        return;
    }
    vector<std::string>  playeds = StringUtil::split(played, ",");
    for (int i = 0; i < playeds.size(); i++){
        Jong* lastPlayedJong = Jong::create();
        lastPlayedJong->showJong(rightplayed, atoi(playeds.at(i).c_str()));
        lastPlayedJong->setPosition(getPlayedJongPos((int)playerPlayedJongs.size()));
        int tar = playerPlayedJongs.size() % 7;
        this->addChild(lastPlayedJong, 7 - tar);
        playerPlayedJongs.pushBack(lastPlayedJong);
    }
}


void PlayerRight::recoverCpg(vector<PlayerChiData> chi,vector<PlayerPengData> peng,vector<PlayerGangData> gang,std::string angang){
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
                jong->showJong(j==0?rightcpgportrait:rightcpglandscape, atoi(chiPoker.at(j).c_str()));
                jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x+ (j==0? 4:0), getCpgShowPostion((int)playerCpgRecords.size()).y+ (j==0? 0:(RIGHT_POKER_WIDTH * j+6))));
                addChild(jong, 30 - (int)playerCpgRecords.size()*3-j);
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
                jong->setLocalZOrder(30 - (int)playerCpgRecords.size()*3-j);
                int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), atoi(peng.at(i).peId.c_str()));
                if(seatId == ClientSeatId::opposite){
                    jong->showJong(j==0?rightcpgportrait:rightcpglandscape, atoi(peng.at(i).peng.c_str()));
                    jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x+(j==0?4:0),getCpgShowPostion((int)playerCpgRecords.size()).y+(j==0?60:(RIGHT_POKER_WIDTH * (j-1)))));
                    if(j==0)
                        jong->setLocalZOrder(30 - (int)playerCpgRecords.size()*3-j-2);
                }else if(seatId == ClientSeatId::left){
                    jong->showJong(rightcpglandscape, atoi(peng.at(i).peng.c_str()));
                    jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x,getCpgShowPostion((int)playerCpgRecords.size()).y+(j==0?0:(RIGHT_POKER_WIDTH * j))));
                }else {
                     jong->showJong(j==0?rightcpgportrait:rightcpglandscape, atoi(peng.at(i).peng.c_str()));
                    jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x+(j==0?4:0),getCpgShowPostion((int)playerCpgRecords.size()).y+(j==0? 0:(RIGHT_POKER_WIDTH * j+6))));
                }
                addChild(jong);
                record.pokersRecord.pushBack(jong);
            }            playerCpgRecords.push_back(record);
        }
    }
    if(gang.size()>0){
        for(int i=0;i<gang.size();i++){
            PlayerCpgRecord record;
            record.type = CpgType::gang;
            for(int j=0;j<4;j++){
                Jong* jong = Jong::create();
                jong->showJong(rightcpglandscape, atoi(gang.at(i).gang.c_str()));
                if (j == 3){
                    record.pokersRecord.pushBack(jong);
                    jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x-2, getCpgShowPostion((int)playerCpgRecords.size()).y +  RIGHT_POKER_WIDTH));
                    addChild(jong, 30);
                }
                else{
                    jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x, getCpgShowPostion((int)playerCpgRecords.size()).y + j * RIGHT_POKER_WIDTH));
                    addChild(jong, 30 - (int)playerCpgRecords.size()*3-j);
                }
                record.pokersRecord.pushBack(jong);
            }
            if(atoi(gang.at(i).gaId.c_str()) != 0){
                if(GAMEDATA::getInstance()->getGameType() == 3||GAMEDATA::getInstance()->getGameType() == 4){
                    int clientId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), atoi(gang.at(i).gaId.c_str()));
                    if( clientId == ClientSeatId::left){
                        auto arrow = Sprite::create("gameview/hu_jong_hint.png");
                        arrow->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x-3, getCpgShowPostion((int)playerCpgRecords.size()).y +  34));
                        arrow->setRotation(90);
                        addChild(arrow,40);
                    }else if( clientId == ClientSeatId::opposite){
                        auto arrow = Sprite::create("gameview/hu_jong_hint.png");
                        arrow->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x-3, getCpgShowPostion((int)playerCpgRecords.size()).y +  34));
                        arrow->setRotation(180);
                        addChild(arrow,40);
                    }else if( clientId == ClientSeatId::hero){
                        auto arrow = Sprite::create("gameview/hu_jong_hint.png");
                        arrow->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x-3, getCpgShowPostion((int)playerCpgRecords.size()).y +  34));
                        //                    arrow->setRotation(270);
                        addChild(arrow,40);
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
                    jong->showJong(rightcpglandscape, atoi(anganglist.at(0).c_str()));
                    record.anGangFan = true;
                }else{
                    jong->showJong(rightangang, atoi(anganglist.at(0).c_str()),false);
                }
                
                if (j == 3){
                    jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x-2, getCpgShowPostion((int)playerCpgRecords.size()).y +  RIGHT_POKER_WIDTH));
                    addChild(jong, 30);
                }
                else{
                    jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x, getCpgShowPostion((int)playerCpgRecords.size()).y + i * RIGHT_POKER_WIDTH));
                    addChild(jong, 30 - (int)playerCpgRecords.size()*3-j);
                }
                record.pokersRecord.pushBack(jong);
            }
            playerCpgRecords.push_back(record);
        }
    }
}

void PlayerRight::recoverHand(std::string hand){
    for(auto var:playerHandJongs){
        var->removeFromParent();
    }
    playerHandJongs.clear();
    vector<std::string>  hands = StringUtil::split(hand, ",");
    for (int i = 0; i < hands.size(); i++)
    {
        Jong* jong = Jong::create();
        jong->showJong(righthand, -1,false);
        jong->setPosition(Point(RIGHT_POS_X, RIGHT_POS_Y - 35 * i));
        addChild(jong, 2);
        playerHandJongs.pushBack(jong);
    }
}

void PlayerRight::drawMingPai(std::string hand){
    for(auto var:playerHandJongs){
        var->removeFromParent();
    }
    playerHandJongs.clear();
    vector<std::string>  hands = StringUtil::split(hand, ",");
    for (int i = 0; i < hands.size(); i++)
    {
        Jong* jong = Jong::create();
        jong->showJong(rightmingpai, atoi(hands.at(i).c_str()),true);
        jong->setPosition(Point(RIGHT_POS_X, RIGHT_POS_Y - 35 * i));
        addChild(jong);
        playerHandJongs.pushBack(jong);
    }
}

void PlayerRight::updateHandJongs(std::string jongs,bool hu){
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
                jong->showJong(rightplayed, atoi(pokers.at(i).c_str()));
                if(hu&&i==pokers.size()-1){
                    jong->setPosition(Point(RIGHT_POS_X, RIGHT_POS_Y - 30 * i-8));
                }else{
                    jong->setPosition(Point(RIGHT_POS_X, RIGHT_POS_Y - 30 * i));
                }
                addChild(jong, 2);
            }
        }
    }
}


void PlayerRight::doEventTimeOver(int type){
    if (type == -1){
        schedule([=](float dt){
            setIsOffLine(true);
        }, 0, 0, 7.0f, "xiaoxiao");
    }
}

void PlayerRight::updateMingpai(Vector<Jong*> myPlayerHandJongs,Vector<Jong*> myPlayerPlayedJongs,Vector<Jong*> myPlayerHuaJongs,std::vector<PlayerCpgRecord> myPlayerCpgRecords){
    for(int i=0;i< playerHandJongs.size();i++){
        playerHandJongs.at(i)->removeFromParent();
    }
    playerHandJongs = myPlayerHandJongs;
    for(int i=0;i< playerHandJongs.size();i++){
        addChild(playerHandJongs.at(i),i);
        playerHandJongs.at(i)->setPosition(Point(RIGHT_POS_X, RIGHT_POS_Y - 35 * i));
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
