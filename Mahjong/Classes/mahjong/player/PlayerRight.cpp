#include "mahjong/player/PlayerRight.h"
#include "mahjong/core/MahjongView.h"
#include "mahjong/anim/HuaAnim.hpp"


bool PlayerRight::init(){
    if (!PlayerBase::init()){
        
        return false;
    }
    playerCpgRecords.clear();
    playerHandJongs.clear();
    playerPlayedJongs.clear();
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
    this->addChild(jong, 1);
    playerHandJongs.pushBack(jong);
    MoveTo* move = MoveTo::create(0.2f, Point(RIGHT_POS_X, RIGHT_POS_Y + 35));
    ActionInterval* dou = EaseBackInOut::create(move);
    jong->runAction(dou);
}

void PlayerRight::drawPlayedJong(int ctype){
    Audio::getInstance()->playMahjong(ctype,getPlayerInfo()->getGender());
    Jong* lastPlayedJong = Jong::create();
    lastPlayedJong->showJong(rightplayed, ctype);
    lastPlayedJong->setPosition(Point(RIGHT_POS_X, RIGHT_POS_Y + 35));
    int tar = playerPlayedJongs.size() % 7;
    this->addChild(lastPlayedJong, 7 - tar);
    playerPlayedJongs.pushBack(lastPlayedJong);
    Point startPoint = Point(RIGHT_POS_X, RIGHT_POS_Y + 35);
    Point endPoint = getPlayedJongPos((int)playerPlayedJongs.size() - 1);
    ccBezierConfig bezier;
    bezier.controlPoint_1 = startPoint;
    bezier.controlPoint_2 = Point(startPoint.x + (endPoint.x - startPoint.x) * 0.5,
                                  startPoint.y + (endPoint.y - startPoint.x)*0.5);
    bezier.endPosition = endPoint;
    BezierTo *actionMove = BezierTo::create(0.5f, bezier);
    CallFunc* callback = CallFunc::create([=](){
        ((MahjongView*)getParent())->removeHeroPlayedIcon();
        showCurrentPlayedJongIcon(true);
    });
    if(NULL != getChildByTag(111)){
        playerHandJongs.eraseObject((Jong*)getChildByTag(111));
        getChildByTag(111)->removeFromParent();
    }
    if(getStateCpg()){
        playerHandJongs.at(playerHandJongs.size() - 1)->removeFromParent();
        playerHandJongs.eraseObject(playerHandJongs.at(playerHandJongs.size() - 1));
        setStateCpg(false);
    }
    Sequence* sequence = Sequence::create(actionMove, callback, NULL);
    lastPlayedJong->runAction(sequence);
    showCurrentBigJong(ctype);
}



Point PlayerRight::getHuaJongPos(int number){
    return Point(780, 220 + 25 * number);
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





void PlayerRight::showCurrentPlayedJongIcon(bool isShow){
    biaoji->setVisible(isShow);
    biaoji->setPosition(getPlayedJongPos((int)playerPlayedJongs.size() - 1).x, getPlayedJongPos((int)playerPlayedJongs.size()-1).y + 20);
}

Point PlayerRight::getCpgShowPostion(int index){
    return Point(1105,175 + index * 75);
}

void PlayerRight::removeLastJong(){
    if(playerPlayedJongs.size()>0){
        playerPlayedJongs.at(playerPlayedJongs.size() - 1)->removeFromParent();
        playerPlayedJongs.popBack();
    }
    biaoji->setVisible(false);
}



void PlayerRight::drawPlayerChi(PlayerCpgtData data, PlayerBase* playerBase){
    PlayerBase::showPlayerChi(data.chi.at(0), playerBase);
    setStateCpg(true);
    ((MahjongView*)getParent())->removeHeroPlayedIcon();
    for (int j = 0; j < 2; j++){
        playerHandJongs.at(playerHandJongs.size() - 1)->removeFromParent();
        playerHandJongs.eraseObject(playerHandJongs.at(playerHandJongs.size() - 1));
    }
    Jong* jongland = Jong::create();
    jongland->showJong(rightcpgportrait, atoi(data.poker.c_str()));
    jongland->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x+4,getCpgShowPostion((int)playerCpgRecords.size()).y);
    addChild(jongland,30 - (int)playerCpgRecords.size()*3);
    PlayerCpgRecord record;
    record.pokersRecord.pushBack(jongland);
    record.type = CpgType::chi;
    playerBase->removeLastJong();
    std::vector<std::string> chi = StringUtil::split(data.chi.at(0), ",");
    for (int i = 0; i < chi.size(); i++){
        Jong* jong = Jong::create();
        jong->showJong(rightcpglandscape, atoi(chi.at(i).c_str()));
        jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x, getCpgShowPostion((int)playerCpgRecords.size()).y + i * 22+24));
        addChild(jong, 30 - (int)playerCpgRecords.size()*3-i-1);
        record.pokersRecord.pushBack(jong);
    }
    playerCpgRecords.push_back(record);
}


void PlayerRight::drawPlayerPeng(PlayerCpgtData data, PlayerBase* playerBase){
    PlayerBase::showPlayerPeng(data, playerBase);
    setStateCpg(true);
    Audio::getInstance()->playSoundPeng(getPlayerInfo()->getGender());
    ((MahjongView*)getParent())->removeHeroPlayedIcon();
    for (int j = 0; j < 2; j++){
        playerHandJongs.at(playerHandJongs.size() - 1)->removeFromParent();
        playerHandJongs.eraseObject(playerHandJongs.at(playerHandJongs.size() - 1));
    }
    playerBase->removeLastJong();
    PlayerCpgRecord record;
    record.type = CpgType::peng;
    Jong* jongpeng = Jong::create();
    jongpeng->showJong(rightcpgportrait, atoi(data.poker.c_str()));
    int offsetY = 0;
    if(playerBase->getClientSeat() == ClientSeatId::opposite){
        offsetY = 0;
        jongpeng->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x+4, getCpgShowPostion((int)playerCpgRecords.size()).y+45);
        jongpeng->setLocalZOrder(30 - (int)playerCpgRecords.size()*3-2);
    }else if(playerBase->getClientSeat() == ClientSeatId::left){
        offsetY = 12;
        jongpeng->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x-27, getCpgShowPostion((int)playerCpgRecords.size()).y+20);
        jongpeng->setLocalZOrder(30 - (int)playerCpgRecords.size()*3);
    }else{
        offsetY = 25;
        jongpeng->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x+4, getCpgShowPostion((int)playerCpgRecords.size()).y);
        jongpeng->setLocalZOrder(30 - (int)playerCpgRecords.size()*3+1);
    }
    addChild(jongpeng);
    record.pokersRecord.pushBack(jongpeng);
    std::vector<std::string> peng = StringUtil::split(data.peng, ",");
    for (int i = 0; i < peng.size(); i++){
        Jong* jong = Jong::create();
        jong->showJong(rightcpglandscape, atoi(peng.at(i).c_str()));
        jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x, getCpgShowPostion((int)playerCpgRecords.size()).y + i * 21+offsetY));
        addChild(jong, 30 - (int)playerCpgRecords.size()*3-i);
        record.pokersRecord.pushBack(jong);
    }
    playerCpgRecords.push_back(record);
}

void PlayerRight::drawPlayerGang(PlayerCpgtData data, PlayerBase* playerBase){
    PlayerBase::showPlayerGang(data,playerBase);
    if(data.flag == 1){
        for (int j = 0; j < 4; j++){
            playerHandJongs.at(playerHandJongs.size() - 1)->removeFromParent();
            playerHandJongs.eraseObject(playerHandJongs.at(playerHandJongs.size() - 1));
        }
    }else if (data.flag == 2){
        ((MahjongView*)getParent())->removeHeroPlayedIcon();
        playerHandJongs.at(playerHandJongs.size()-1)->removeFromParent();
        playerHandJongs.eraseObject(playerHandJongs.at(playerHandJongs.size()-1));
    }
    else{
        for (int j = 0; j <3; j++){
            playerHandJongs.at(playerHandJongs.size() - 1)->removeFromParent();
            playerHandJongs.eraseObject(playerHandJongs.at(playerHandJongs.size() - 1));
        }
    }
    std::vector<std::string> gang = StringUtil::split(data.gang, ",");
    gang.push_back(data.poker);
    sort(gang.begin(), gang.end());
    PlayerCpgRecord record;
    if(data.flag ==1){
        record.type = CpgType::angang;
    }else{
        record.type = CpgType::gang;
    }
    record.gangValue = atoi(gang.at(0).c_str());
    if (data.flag == 2){
        for (int i = 0; i < this->playerCpgRecords.size(); i++)
        {
            if (playerCpgRecords.at(i).type == CpgType::peng){
                if (playerCpgRecords.at(i).pokersRecord.at(0)->getJongType() == atoi(data.poker.c_str())){
                    Jong* jong = Jong::create();
                    jong->showJong(rightcpglandscape, atoi(data.poker.c_str()));
                    jong->setPosition(playerCpgRecords.at(i).pokersRecord.at(1)->getPosition());
                    addChild(jong, 30);
                }
            }
        }
    }
    else{
        if (data.flag == 0){
            playerBase->removeLastJong();
        }
        for (int i = 0; i < 4; i++){
            Jong* jong = Jong::create();
            if (data.flag == 1){
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
                record.pokersRecord.pushBack(jong);
                jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x-2, getCpgShowPostion((int)playerCpgRecords.size()).y +  21));
                this->addChild(jong, 30);
            }
            else{
                jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x, getCpgShowPostion((int)playerCpgRecords.size()).y + i * 21));
                addChild(jong, 30 - (int)playerCpgRecords.size()*3-i);
            }
        }
        playerCpgRecords.push_back(record);
    }
}


void PlayerRight::recoverHua(int hua){
    setHuaNum(hua);
    showPlayerHua(getHuaNum());
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
                jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x+ (j==0? 4:0), getCpgShowPostion((int)playerCpgRecords.size()).y+ (j==0? 0:(21 * j+3))));
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
                jong->showJong(j==0?rightcpgportrait:rightcpglandscape, atoi(peng.at(i).peng.c_str()));
                int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), atoi(peng.at(i).peId.c_str()));
                if(seatId == ClientSeatId::opposite){
                    jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x+(j==0?4:0),getCpgShowPostion((int)playerCpgRecords.size()).y+(j==0?45:(21 * (j-1)))));
                    if(j==0)
                        jong->setLocalZOrder(30 - (int)playerCpgRecords.size()*3-j-2);
                }else if(seatId == ClientSeatId::left){
                    jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x-(j==0?28:0),getCpgShowPostion((int)playerCpgRecords.size()).y+(j==0?18:(21 * (j-1)+10))));
                }else {
                    jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x+(j==0?4:0),getCpgShowPostion((int)playerCpgRecords.size()).y+(j==0? 0:(21 * j+3))));
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
                jong->showJong(rightplayed, atoi(gang.at(i).gang.c_str()));
                if (j == 3){
                    record.pokersRecord.pushBack(jong);
                    jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x-2, getCpgShowPostion((int)playerCpgRecords.size()).y +  28));
                    addChild(jong, 30);
                }
                else{
                    jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x, getCpgShowPostion((int)playerCpgRecords.size()).y + j * 28));
                    addChild(jong, 30 - (int)playerCpgRecords.size()*3-j);
                }
                record.pokersRecord.pushBack(jong);
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
                    jong->showJong(rightplayed, atoi(anganglist.at(0).c_str()));
                    record.anGangFan = true;
                }else{
                    jong->showJong(rightdeal, atoi(anganglist.at(0).c_str()),false);
                    jong->setScale(0.86f);
                }
                
                if (i == 3){
                    record.pokersRecord.pushBack(jong);
                    jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x-2, getCpgShowPostion((int)playerCpgRecords.size()).y +  28));
                    this->addChild(jong, 30);
                }
                else{
                    jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x, getCpgShowPostion((int)playerCpgRecords.size()).y + i * 28));
                    this->addChild(jong, 30 - (int)playerCpgRecords.size()*3-j);
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
