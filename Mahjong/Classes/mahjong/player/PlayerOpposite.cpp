#include "mahjong/player/PlayerOpposite.h"
#include "mahjong/core/MahjongView.h"
#include "mahjong/anim/HuaAnim.hpp"

bool PlayerOpposite::init(){
    if (!PlayerBase::init()){
        return false;
    }
    playerCpgRecords.clear();
    playerHandJongs.clear();
    playerPlayedJongs.clear();
    setClientSeat(ClientSeatId::opposite);
    return true;
}


void PlayerOpposite::drawHandJong(){
    for (int i = 0; i < this->jongNum; i++)
    {
        Jong* jong = Jong::create();
        jong->showJong(oppositehand, -1);
        jong->setPosition(Point(OPPOSITE_POS_X + 43 * i, OPPOSITE_POS_Y));
        this->addChild(jong);
        playerHandJongs.pushBack(jong);
    }
}


void PlayerOpposite::showCurrentPlayedJongIcon(bool isShow){
    biaoji->setPosition(getPlayedJongPos(playerPlayedJongs.size() - 1).x,getPlayedJongPos(playerPlayedJongs.size() - 1).y + 20);
    biaoji->setVisible(isShow);
}

Point PlayerOpposite::getCpgShowPostion(int index){
    return Point(865 - index * 90, 678);
}


void PlayerOpposite::drawOppositePlayerTurn(){
    Jong* jong = Jong::create();
    jong->setTag(111);
    jong->showJong(oppositehand, -1);
    jong->setPosition(Point(OPPOSITE_POS_X - 43, OPPOSITE_POS_Y + 20));
    addChild(jong);
    playerHandJongs.pushBack(jong);
    MoveTo* move = MoveTo::create(0.2f, Point(OPPOSITE_POS_X - 43, OPPOSITE_POS_Y));
    ActionInterval* dou = EaseBackInOut::create(move);
    jong->runAction(dou);
}

void PlayerOpposite::drawPlayedJong(int ctype){
    Audio::getInstance()->playMahjong(ctype,getPlayerInfo()->getGender());
    Jong* lastPlayedJong = Jong::create();
    lastPlayedJong->showJong(oppositeplayed, ctype);
    lastPlayedJong->setPosition(Point(OPPOSITE_POS_X - 43, OPPOSITE_POS_Y));
    playerPlayedJongs.pushBack(lastPlayedJong);
    if (playerPlayedJongs.size() / 10 == 0){
        addChild(lastPlayedJong, 3);
    }
    else if (playerPlayedJongs.size() / 10 == 1){
        addChild(lastPlayedJong, 2);
    }
    else{
        addChild(lastPlayedJong, 1);
    }
    Point startPoint = Point(OPPOSITE_POS_X - 43, OPPOSITE_POS_Y);
    Point endPoint = getPlayedJongPos(playerPlayedJongs.size() - 1);
    ccBezierConfig bezier;
    bezier.controlPoint_1 = startPoint;
    bezier.controlPoint_2 = Point(startPoint.x + (endPoint.x - startPoint.x) * 0.5,
                                  startPoint.y + (endPoint.y - startPoint.y)*0.5);
    bezier.endPosition = endPoint;
    BezierTo *actionMove = BezierTo::create(0.5f, bezier);
    CallFunc* callback = CallFunc::create([=](){
        ((MahjongView*)getParent())->removeHeroPlayedIcon();
        showCurrentPlayedJongIcon(true);
    });
    Sequence* sequence = Sequence::create(Spawn::create(actionMove,CallFunc::create([=](){
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
    showCurrentBigJong(ctype);
}


Point PlayerOpposite::getHuaJongPos(int number){
    return Point(780 - 25 * number, 465);
}

Point PlayerOpposite::getPlayedJongPos(int count){
    int row = count / 10;
    int line = count % 10;
    Point originPos = Point(800, 520);
    if (row == 0) {
        return Point(originPos.x - 35 * line, originPos.y);
    }
    else {
        return Point(originPos.x - 35 * line, originPos.y + 40);
    }
}


void PlayerOpposite::removeLastJong(){
    if(playerPlayedJongs.size()>0){
        playerPlayedJongs.at(playerPlayedJongs.size() - 1)->removeFromParent();
        playerPlayedJongs.popBack();
    }
    biaoji->setVisible(false);
}


void PlayerOpposite::drawPlayerChi(PlayerCpgtData data, PlayerBase* playerBase){
    PlayerBase::showPlayerChi(data.chi.at(0), playerBase);
    setStateCpg(true);
    ((MahjongView*)getParent())->removeHeroPlayedIcon();
    for (int j = 0; j < 2; j++){
        playerHandJongs.at(playerHandJongs.size() - 1)->removeFromParent();
        playerHandJongs.eraseObject(playerHandJongs.at(playerHandJongs.size() - 1));
    }
    Jong* jongland = Jong::create();
    jongland->showJong(oppositecpglandscape, atoi(data.poker.c_str()));
    jongland->setPosition(getCpgShowPostion((int)playerCpgRecords.size()).x-5,getCpgShowPostion((int)playerCpgRecords.size()).y+6);
    addChild(jongland,10);
    PlayerCpgRecord record;
    record.pokersRecord.pushBack(jongland);
    record.type = CpgType::chi;
    playerBase->removeLastJong();
    std::vector<std::string> chi = StringUtil::split(data.chi.at(0), ",");
    for (int i = 0; i < chi.size(); i++){
        Jong* jong = Jong::create();
        jong->showJong(oppositecpgportrait, atoi(chi.at(i).c_str()));
        jong->setPosition(Point(getCpgShowPostion(playerCpgRecords.size()).x - 27 * i-34, getCpgShowPostion(playerCpgRecords.size()).y));
        addChild(jong, 30 - playerCpgRecords.size());
        record.pokersRecord.pushBack(jong);
    }
    playerCpgRecords.push_back(record);
}


void PlayerOpposite::drawPlayerPeng(PlayerCpgtData data, PlayerBase* playerBase){
    PlayerBase::showPlayerPeng(data, playerBase);
    setStateCpg(true);
    Audio::getInstance()->playSoundPeng(getPlayerInfo()->getGender());
    ((MahjongView*)getParent())->removeHeroPlayedIcon();
    for (int j = 0; j < 2; j++){
        playerHandJongs.at(playerHandJongs.size()-1)->removeFromParent();
        playerHandJongs.eraseObject(playerHandJongs.at(playerHandJongs.size()-1));
    }
    std::vector<std::string> peng = StringUtil::split(data.peng, ",");
    peng.push_back(data.poker);
    sort(peng.begin(), peng.end());
    PlayerCpgRecord record;
    record.type = CpgType::peng;
    playerBase->removeLastJong();
    for (int i = 0; i < peng.size(); i++){
        Jong* jong = Jong::create();
        jong->showJong(oppositeplayed, atoi(peng.at(i).c_str()));
        jong->setPosition(Point(getCpgShowPostion(playerCpgRecords.size()).x - 35 * i, getCpgShowPostion(playerCpgRecords.size()).y));
        this->addChild(jong, 30 - playerCpgRecords.size());
        record.pokersRecord.pushBack(jong);
    }
    this->playerCpgRecords.push_back(record);
}


void PlayerOpposite::drawPlayerGang(PlayerCpgtData data, PlayerBase* playerBase){
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
        for (int j = 0; j < 3; j++){
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
        for (int i = 0; i < playerCpgRecords.size(); i++)
        {
            if (playerCpgRecords.at(i).type == CpgType::peng){
                if (playerCpgRecords.at(i).pokersRecord.at(0)->getJongType() == atoi(data.poker.c_str())){
                    Jong* jong = Jong::create();
                    jong->showJong(oppositeplayed, atoi(data.poker.c_str()));
                    jong->setPosition(playerCpgRecords.at(i).pokersRecord.at(1)->getPosition().x,playerCpgRecords.at(i).pokersRecord.at(1)->getPosition().y-5);
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
                    record.anGangFan = true;
                    jong->showJong(oppositeplayed, atoi(gang.at(0).c_str()));
                }else{
                    jong->showJong(oppositeangang, -1);
                }
            }
            else{
                jong->showJong(oppositeplayed, atoi(gang.at(0).c_str()));
            }
            if (i == 3){
                jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x - 35, getCpgShowPostion((int)playerCpgRecords.size()).y - 5));
                addChild(jong, 10);
            }
            else{
                jong->setPosition(Point(getCpgShowPostion((int)playerCpgRecords.size()).x - 35 * i, getCpgShowPostion((int)playerCpgRecords.size()).y));
                record.pokersRecord.pushBack(jong);
                addChild(jong, 5);
            }
        }
        playerCpgRecords.push_back(record);
    }
}

void PlayerOpposite::recoverHua(int hua){
    setHuaNum(hua);
    showPlayerHua(getHuaNum());
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

void PlayerOpposite::recoverPlayed(std::string played){
    playerPlayedJongs.clear();
    if(played == ""){
        return;
    }
    vector<std::string>  playeds = StringUtil::split(played, ",");
    for (int i = 0; i < playeds.size(); i++){
        Jong* lastPlayedJong = Jong::create();
        lastPlayedJong->showJong(oppositeplayed, atoi(playeds.at(i).c_str()));
        lastPlayedJong->setPosition(getPlayedJongPos(playerPlayedJongs.size()));
        if (playerPlayedJongs.size() / 10 == 0){
            this->addChild(lastPlayedJong, 3);
        }
        else if (playerPlayedJongs.size() / 10 == 1){
            this->addChild(lastPlayedJong, 2);
        }
        else{
            this->addChild(lastPlayedJong, 1);
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
            for (int j = 0; j < chiPoker.size();j++){
                Jong* jong = Jong::create();
                jong->showJong(oppositeplayed, atoi(chiPoker.at(j).c_str()));
                jong->setPosition(Point(getCpgShowPostion(playerCpgRecords.size()).x - 35 * j, getCpgShowPostion(playerCpgRecords.size()).y));
                this->addChild(jong, 30 - playerCpgRecords.size());
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
                jong->showJong(oppositeplayed, atoi(peng.at(i).peng.c_str()));
                jong->setPosition(Point(getCpgShowPostion(playerCpgRecords.size()).x - 35 * j, getCpgShowPostion(playerCpgRecords.size()).y));
                this->addChild(jong, 30 - playerCpgRecords.size());
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
                jong->showJong(oppositeplayed, atoi(gang.at(i).gang.c_str()));
                if (j == 3){
                    jong->setPosition(Point(getCpgShowPostion(playerCpgRecords.size()).x - 35, getCpgShowPostion(playerCpgRecords.size()).y - 2));
                    this->addChild(jong, 10);
                }
                else{
                    jong->setPosition(Point(getCpgShowPostion(playerCpgRecords.size()).x - 35 * j, getCpgShowPostion(playerCpgRecords.size()).y));
                    record.pokersRecord.pushBack(jong);
                    this->addChild(jong, 5);
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
                    jong->showJong(oppositeplayed, atoi(anganglist.at(0).c_str()));
                    record.anGangFan = true;
                }else{
                    jong->showJong(oppositeangang, -1);
                }
                
                if (i == 3){
                    jong->setPosition(Point(getCpgShowPostion(playerCpgRecords.size()).x - 35, getCpgShowPostion(playerCpgRecords.size()).y - 2));
                    this->addChild(jong, 10);
                }
                else{
                    jong->setPosition(Point(getCpgShowPostion(playerCpgRecords.size()).x - 35 * j, getCpgShowPostion(playerCpgRecords.size()).y));
                    record.pokersRecord.pushBack(jong);
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
        jong->showJong(oppositehand, -1);
        jong->setPosition(Point(OPPOSITE_POS_X + 43 * i, OPPOSITE_POS_Y));
        this->addChild(jong);
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
