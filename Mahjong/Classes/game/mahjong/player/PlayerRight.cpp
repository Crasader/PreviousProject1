#include "game/mahjong/player/PlayerRight.h"
#include "game/mahjong/core/MahjongView.h"
#include "game/mahjong/anim/HuaAnim.hpp"


bool PlayerRight::init(){
    if (!PlayerBase::init()){
        
        return false;
    }
    
    return true;
}


void PlayerRight::drawHandJong(){
    for (int i = 0; i < this->jongNum; i++)
    {
        Jong* jong = Jong::create();
        jong->showJong(righthand, -1);
        jong->setPosition(Point(RIGHT_POS_X, RIGHT_POS_Y - 35 * i));
        this->addChild(jong, 2);
        playerHandJongs.pushBack(jong);
    }
}


void PlayerRight::drawRightPlayerTurn(){
    Jong* jong = Jong::create();
    jong->setTag(111);
    jong->showJong(righthand, -11);
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
    Point endPoint = getPlayedJongPos(playerPlayedJongs.size() - 1);
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
    showCurrentBigJong(ctype, Vec2(980, 400));
}



void PlayerRight::drawHuaJong(){
    ReplaceJong rejong = getReplacePoker();
    std::vector<Jong*> needReplace;
    needReplace.clear();
    for (int i = 0; i < rejong.poker.size(); i++){
        std::vector<std::string> pokerV = StringUtil::split(rejong.poker.at(i), ",");
        for (int j = 0; j < pokerV.size(); j++){
            Jong* jon = Jong::create();
            jon->showJong(leftplayed,atoi(pokerV.at(j).c_str()));
            needReplace.push_back(jon);
        }
    }
    if(needReplace.size()>0){
        
        HuaAnim* huaAnim = HuaAnim::create(needReplace, ClientSeatId::right,CallFunc::create([=](){
            setHuaNum(getHuaNum()+needReplace.size());
            showPlayerHua(Vec2(1200,545),getHuaNum());
        }));
        addChild(huaAnim,100);
    }
}

void PlayerRight::playerTurnReplace(PlayerTurnData data){
    if(data.replace==""){
        return;
    }
    std::vector<std::string> replace = StringUtil::split(data.replace, ",");
    if(replace.size()>0){
        huaIndex=0;
        Sprite* ss = Sprite::create();
        addChild(ss);
        ss->runAction(Repeat::create(Sequence::create(CallFunc::create([=](){
            needReplace.clear();
            Jong* jon = Jong::create();
            jon->showJong(leftplayed,atoi(replace.at(huaIndex).c_str()));
            needReplace.push_back(jon);
            HuaAnim* huaAnim = HuaAnim::create(needReplace, ClientSeatId::right,CallFunc::create([=](){
                setHuaNum(getHuaNum()+1);
                showPlayerHua(Vec2(1200,545),getHuaNum());
            }));
            addChild(huaAnim,100);
            huaIndex++;
        }), DelayTime::create(2.0f),NULL),replace.size()-1));
    }
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
    biaoji->setPosition(getPlayedJongPos(playerPlayedJongs.size() - 1).x, getPlayedJongPos(playerPlayedJongs.size() - 1).y + 20);
}

Point PlayerRight::getCpgShowPostion(int index){
    return Point(1100,175 + index * 95);
}

void PlayerRight::removeLastJong(){
    playerPlayedJongs.at(playerPlayedJongs.size() - 1)->removeFromParent();
    playerPlayedJongs.popBack();
    biaoji->setVisible(false);
}



void PlayerRight::drawPlayerChi(PlayerCpgtData data, PlayerBase* playerBase){
    PlayerBase::drawPlayerChi(data.chi.at(0), playerBase);
    setStateCpg(true);
    ((MahjongView*)getParent())->removeHeroPlayedIcon();
    for (int j = 0; j < 2; j++){
        playerHandJongs.at(playerHandJongs.size() - 1)->removeFromParent();
        playerHandJongs.eraseObject(playerHandJongs.at(playerHandJongs.size() - 1));
    }
    std::vector<std::string> chi = StringUtil::split(data.chi.at(0), ",");
    chi.push_back(data.poker);
    sort(chi.begin(), chi.end());
    PlayerCpgRecord record;
    record.type = CpgType::chi;
    playerBase->removeLastJong();
    for (int i = 0; i < chi.size(); i++){
        Jong* jong = Jong::create();
        jong->showJong(rightplayed, atoi(chi.at(i).c_str()));
        jong->setPosition(Point(getCpgShowPostion(playerCpgRecords.size()).x, getCpgShowPostion(playerCpgRecords.size()).y + i * 28));
        this->addChild(jong, 30 - playerCpgRecords.size()*3-i);
        record.pokersRecord.pushBack(jong);
    }
    this->playerCpgRecords.push_back(record);
}


void PlayerRight::drawPlayerPeng(PlayerCpgtData data, PlayerBase* playerBase){
    PlayerBase::drawPlayerPeng(data, playerBase);
    setStateCpg(true);
    Audio::getInstance()->playSoundPeng(getPlayerInfo()->getGender());
    ((MahjongView*)getParent())->removeHeroPlayedIcon();
    for (int j = 0; j < 2; j++){
        playerHandJongs.at(playerHandJongs.size() - 1)->removeFromParent();
        playerHandJongs.eraseObject(playerHandJongs.at(playerHandJongs.size() - 1));
    }
    std::vector<std::string> peng = StringUtil::split(data.peng, ",");
    peng.push_back(data.poker);
    sort(peng.begin(), peng.end());
    PlayerCpgRecord record;
    record.type = CpgType::peng;
    playerBase->removeLastJong();
    for (int i = 0; i < peng.size(); i++){
        Jong* jong = Jong::create();
        jong->showJong(rightplayed, atoi(peng.at(i).c_str()));
        jong->setPosition(Point(getCpgShowPostion(playerCpgRecords.size()).x, getCpgShowPostion(playerCpgRecords.size()).y + i * 28));
        this->addChild(jong, 30 - playerCpgRecords.size()*3-i);
        record.pokersRecord.pushBack(jong);
    }
    this->playerCpgRecords.push_back(record);
}

void PlayerRight::drawPlayerGang(PlayerCpgtData data, PlayerBase* playerBase){
    PlayerBase::drawPlayerGang(data,playerBase);
    if (data.flag == 2){
        ((MahjongView*)getParent())->removeHeroPlayedIcon();
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
    record.type = CpgType::gang;
    if (data.flag == 2){
        for (int i = 0; i < this->playerCpgRecords.size(); i++)
        {
            if (playerCpgRecords.at(i).type == CpgType::peng){
                if (playerCpgRecords.at(i).pokersRecord.at(0)->getJongType() == atoi(data.poker.c_str())){
                    Jong* jong = Jong::create();
                    jong->showJong(rightplayed, atoi(data.poker.c_str()));
                    jong->setPosition(playerCpgRecords.at(i).pokersRecord.at(1)->getPosition());
                    this->addChild(jong, 30);
                }
            }
        }
    }
    else{
        if (data.flag == 0){
            playerBase->removeLastJong();
        }
        for (int i = 0; i < gang.size(); i++){
            Jong* jong = Jong::create();
            if (data.flag == 1){
                jong->showJong(rightdeal, -1);
            }
            else{
                jong->showJong(rightplayed, atoi(gang.at(i).c_str()));
            }
            if (i == 3){
                record.pokersRecord.pushBack(jong);
                jong->setPosition(Point(getCpgShowPostion(playerCpgRecords.size()).x-2, getCpgShowPostion(playerCpgRecords.size()).y +  28));
                this->addChild(jong, 30);
            }
            else{
                jong->setPosition(Point(getCpgShowPostion(playerCpgRecords.size()).x, getCpgShowPostion(playerCpgRecords.size()).y + i * 28));
                addChild(jong, 30 - playerCpgRecords.size()*3-i);
            }
        }
        playerCpgRecords.push_back(record);
    }
}

void PlayerRight::recoverHua(int hua){
    setHuaNum(hua);
    showPlayerHua(Vec2(1200,545),getHuaNum());
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
        lastPlayedJong->setPosition(getPlayedJongPos(playerPlayedJongs.size()));
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
            for (int j = 0; j < chiPoker.size();j++){
                Jong* jong = Jong::create();
                jong->showJong(rightplayed, atoi(chiPoker.at(j).c_str()));
                jong->setPosition(Point(getCpgShowPostion(playerCpgRecords.size()).x, getCpgShowPostion(playerCpgRecords.size()).y + j* 28));
                addChild(jong, 30 - playerCpgRecords.size()*3-j);
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
                jong->showJong(rightplayed, atoi(peng.at(i).peng.c_str()));
                jong->setPosition(Point(getCpgShowPostion(playerCpgRecords.size()).x, getCpgShowPostion(playerCpgRecords.size()).y + j * 28));
                addChild(jong, 30 - playerCpgRecords.size()*3-j);
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
                jong->showJong(rightplayed, atoi(gang.at(i).gang.c_str()));
                if (j == 3){
                    record.pokersRecord.pushBack(jong);
                    jong->setPosition(Point(getCpgShowPostion(playerCpgRecords.size()).x-2, getCpgShowPostion(playerCpgRecords.size()).y +  28));
                    this->addChild(jong, 30);
                }
                else{
                    jong->setPosition(Point(getCpgShowPostion(playerCpgRecords.size()).x, getCpgShowPostion(playerCpgRecords.size()).y + j * 28));
                    this->addChild(jong, 30 - playerCpgRecords.size()*3-j);
                }
                record.pokersRecord.pushBack(jong);
            }
            playerCpgRecords.push_back(record);
        }
    }
    if(angang != ""){
        for(int i=0;i<gang.size();i++){
            PlayerCpgRecord record;
            record.type = CpgType::gang;
            for(int j=0;j<4;j++){
                Jong* jong = Jong::create();
                jong->showJong(rightdeal, -1);
                if (i == 3){
                    record.pokersRecord.pushBack(jong);
                    jong->setPosition(Point(getCpgShowPostion(playerCpgRecords.size()).x-2, getCpgShowPostion(playerCpgRecords.size()).y +  28));
                    this->addChild(jong, 30);
                }
                else{
                    jong->setPosition(Point(getCpgShowPostion(playerCpgRecords.size()).x, getCpgShowPostion(playerCpgRecords.size()).y + i * 28));
                    this->addChild(jong, 30 - playerCpgRecords.size()*3-j);
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
        jong->showJong(righthand, -1);
        jong->setPosition(Point(RIGHT_POS_X, RIGHT_POS_Y - 35 * i));
        this->addChild(jong, 2);
        playerHandJongs.pushBack(jong);
    }
}

void PlayerRight::updateHandJongs(std::string jongs){
    vector<std::string> pokers = StringUtil::split(jongs, ",");
    for (int i = 0; i < pokers.size(); i++)
    {
        Jong* jong = Jong::create();
        jong->showJong(rightplayed, atoi(pokers.at(i).c_str()));
        jong->setPosition(Point(RIGHT_POS_X, RIGHT_POS_Y - 30 * i));
        this->addChild(jong, 2);
    }
    
}