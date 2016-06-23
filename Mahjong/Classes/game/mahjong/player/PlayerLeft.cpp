#include "PlayerLeft.h"
#include "game/mahjong/core/MahjongView.h"
#include "game/mahjong/anim/HuaAnim.hpp"

bool PlayerLeft::init(){
    if (!PlayerBase::init()){
        
        return false;
    }
    playerCpgRecords.clear();
    playerHandJongs.clear();
    playerPlayedJongs.clear();
    return true;
}


void PlayerLeft::drawHandJong(){
    for (int i = 0; i < this->jongNum; i++)
    {
        Jong* jong = Jong::create();
        jong->showJong(lefthand, -1);
        jong->setPosition(Point(LEFT_POS_X, LEFT_POS_Y + 35 * i));
        playerHandJongs.pushBack(jong);
        this->addChild(jong,60-i);
    }
}


void PlayerLeft::drawLeftPlayerTurn(){
    Jong* jong = Jong::create();
    jong->setTag(111);
    jong->showJong(lefthand, -1);
    jong->setPosition(Point(LEFT_POS_X, LEFT_POS_Y - 32));
    this->addChild(jong,61);
    playerHandJongs.pushBack(jong);
    MoveTo* move = MoveTo::create(0.2f, Point(LEFT_POS_X, LEFT_POS_Y - 35));
    ActionInterval* dou = EaseBackInOut::create(move);
    jong->runAction(dou);
}

void PlayerLeft::drawPlayedJong(int ctype){
    Jong* lastPlayedJong = Jong::create();
    lastPlayedJong->showJong(leftplayed, ctype);
    lastPlayedJong->setPosition(Point(LEFT_POS_X, LEFT_POS_Y - 35));
    this->addChild(lastPlayedJong);
    playerPlayedJongs.pushBack(lastPlayedJong);
    Point startPoint = Point(LEFT_POS_X, LEFT_POS_Y - 35);
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
    
}



void PlayerLeft::drawHuaJong(){
    ReplaceJong rejong = getReplacePoker();
    std::vector<Jong*> needReplace;
    for (int i = 0; i < rejong.poker.size(); i++){
        std::vector<std::string> pokerV = StringUtil::split(rejong.poker.at(i), ",");
        for (int j = 0; j < pokerV.size(); j++){
            Jong* jon = Jong::create();
            jon->showJong(leftplayed,atoi(pokerV.at(j).c_str()));
            needReplace.push_back(jon);
        }
    }
    if(needReplace.size()>0){
        
        HuaAnim* huaAnim = HuaAnim::create(needReplace, ClientSeatId::left,CallFunc::create([=](){
            setHuaNum(getHuaNum()+needReplace.size());
            showPlayerHua(Vec2(45,545),getHuaNum());
        }));
        addChild(huaAnim,100);
    }
}

void PlayerLeft::playerTurnReplace(PlayerTurnData data){
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
            HuaAnim* huaAnim = HuaAnim::create(needReplace, ClientSeatId::left,CallFunc::create([=](){
                setHuaNum(getHuaNum()+1);
                showPlayerHua(Vec2(45,545),getHuaNum());
            }));
            addChild(huaAnim,100);
            huaIndex++;
        }), DelayTime::create(2.0f),NULL),replace.size()-1));
    }
    
}

Point PlayerLeft::getHuaJongPos(int number){
    return Point(180, 440 - 22 * number);
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

void PlayerLeft::drawLeftPlayerPlay(int type){
    Audio::getInstance()->playMahjong(type);
    drawPlayedJong(type);
    showCurrentBigJong(type,Vec2(300,400));
}


void PlayerLeft::showCurrentPlayedJongIcon(bool isShow){
    biaoji->setPosition(getPlayedJongPos(playerPlayedJongs.size() - 1).x, getPlayedJongPos(playerPlayedJongs.size() - 1).y + 20);
    biaoji->setVisible(isShow);
}


Point PlayerLeft::getCpgShowPostion(int index){
    return Point(170, 690 - index * 75);
}

void PlayerLeft::removeLastJong(){
    playerPlayedJongs.at(playerPlayedJongs.size() - 1)->removeFromParent();
    playerPlayedJongs.popBack();
    biaoji->setVisible(false);
}




void PlayerLeft::drawPlayerChi(PlayerCpgtData data, PlayerBase* playerBase){
    setStateCpg(true);
    Audio::getInstance()->playSoundChi(1);
    ((MahjongView*)getParent())->removeHeroPlayedIcon();
    for (int j = 0; j < 2; j++)
    {
        playerHandJongs.at(playerHandJongs.size()-1)->removeFromParent();
        playerHandJongs.eraseObject(playerHandJongs.at(playerHandJongs.size()-1));
    }
    std::vector<std::string> chi = StringUtil::split(data.chi.at(0), ",");
    chi.push_back(data.poker);
    sort(chi.begin(), chi.end());
    PlayerCpgRecord record;
    record.type = CpgType::chi;
    playerBase->removeLastJong();
    for (int i = 0; i < chi.size(); i++){
        Jong* jong = Jong::create();
        jong->setScale(0.8f);
        jong->showJong(leftplayed, atoi(chi.at(i).c_str()));
        jong->setPosition(getCpgShowPostion(playerCpgRecords.size()).x, getCpgShowPostion(playerCpgRecords.size()).y - 22 * i);
        this->addChild(jong,10);
        record.pokersRecord.pushBack(jong);
    }
    playerCpgRecords.push_back(record);
}

void PlayerLeft::drawPlayerPeng(PlayerCpgtData data, PlayerBase* playerBase){
    setStateCpg(true);
    Audio::getInstance()->playSoundPeng();
    ((MahjongView*)getParent())->removeHeroPlayedIcon();
    for (int j = 0; j < 2; j++)
    {
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
        jong->setScale(0.8f);
        jong->showJong(leftplayed, atoi(peng.at(i).c_str()));
        jong->setPosition(getCpgShowPostion(playerCpgRecords.size()).x, getCpgShowPostion(playerCpgRecords.size()).y - 22 * i);
        this->addChild(jong, 10);
        record.pokersRecord.pushBack(jong);
    }
    this->playerCpgRecords.push_back(record);
}

void PlayerLeft::drawPlayerGang(PlayerCpgtData data, PlayerBase* playerBase){
    Audio::getInstance()->playSoundGang();
    if (data.flag == 2){
        ((MahjongView*)getParent())->removeHeroPlayedIcon();
    }
    else{
        if(data.flag == 0){
            for (int j = 0; j < 3; j++)
            {
                playerHandJongs.at(playerHandJongs.size()-1)->removeFromParent();
                playerHandJongs.eraseObject(playerHandJongs.at(playerHandJongs.size()-1));
            }
        }else if(data.flag == 1){
            for (int j = 0; j < 4; j++)
            {
                playerHandJongs.at(playerHandJongs.size()-1)->removeFromParent();
                playerHandJongs.eraseObject(playerHandJongs.at(playerHandJongs.size()-1));
            }

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
                    jong->setScale(0.8f);
                    jong->showJong(leftplayed, atoi(data.poker.c_str()));
                    jong->setPosition(playerCpgRecords.at(i).pokersRecord.at(1)->getPosition());
                    this->addChild(jong, 10);
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
            jong->setScale(0.8f);
            if (data.flag == 1){
                jong->showJong(leftdeal, -1);
            }
            else{
                jong->showJong(leftplayed, atoi(gang.at(i).c_str()));
            }
            if (i == 3){
                jong->setPosition(getCpgShowPostion(playerCpgRecords.size()).x + 2, getCpgShowPostion(playerCpgRecords.size()).y - 16);
            }
            else{
                jong->setPosition(getCpgShowPostion(playerCpgRecords.size()).x, getCpgShowPostion(playerCpgRecords.size()).y - 22 * i);
            }
            this->addChild(jong, 10);
            record.pokersRecord.pushBack(jong);
        }
        this->playerCpgRecords.push_back(record);
    }
}


void PlayerLeft::recoverHua(int hua){
    setHuaNum(hua);
    showPlayerHua(Vec2(45,545),getHuaNum());
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
        lastPlayedJong->setPosition(getPlayedJongPos(playerPlayedJongs.size()));
        this->addChild(lastPlayedJong);
        playerPlayedJongs.pushBack(lastPlayedJong);
    }
}


void PlayerLeft::recoverCpg(vector<PlayerChiData> chi,vector<PlayerPengData> peng,vector<PlayerGangData> gang,std::string angang){
    
    if(chi.size()>0){
        for(int i=0;i<chi.size();i++){
            PlayerCpgRecord record;
            record.type = CpgType::chi;
            vector<std::string> chiPoker  = StringUtil::split(chi.at(i).chi, ",");
            for (int j = 0; j < chiPoker.size();j++){
                Jong* jong = Jong::create();
                jong->setScale(0.8f);
                jong->showJong(leftplayed, atoi(chiPoker.at(j).c_str()));
                jong->setPosition(getCpgShowPostion(playerCpgRecords.size()).x, getCpgShowPostion(playerCpgRecords.size()).y - 22 * i);
                this->addChild(jong,10);
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
                jong->setScale(0.8f);
                jong->showJong(leftplayed, atoi(peng.at(i).peng.c_str()));
                jong->setPosition(getCpgShowPostion(playerCpgRecords.size()).x, getCpgShowPostion(playerCpgRecords.size()).y - 22 * j);
                this->addChild(jong,10);
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
                jong->setScale(0.8f);
                jong->showJong(leftplayed, atoi(gang.at(i).gang.c_str()));
                if (j == 3){
                    jong->setPosition(getCpgShowPostion(playerCpgRecords.size()).x + 2, getCpgShowPostion(playerCpgRecords.size()).y - 16);
                }
                else{
                    jong->setPosition(getCpgShowPostion(playerCpgRecords.size()).x, getCpgShowPostion(playerCpgRecords.size()).y - 22 * j);
                }
                this->addChild(jong,10);
                record.pokersRecord.pushBack(jong);
            }
            playerCpgRecords.push_back(record);
        }
    }
    if(angang != ""){
        PlayerCpgRecord record;
        record.type = CpgType::angang;
        for(int j=0;j<4;j++){
            Jong* jong = Jong::create();
            jong->setScale(0.8f);
            jong->showJong(leftdeal, atoi(angang.c_str()));
            if (j == 3){
                jong->setPosition(getCpgShowPostion(playerCpgRecords.size()).x + 2, getCpgShowPostion(playerCpgRecords.size()).y - 16);
            }
            else{
                jong->setPosition(getCpgShowPostion(playerCpgRecords.size()).x, getCpgShowPostion(playerCpgRecords.size()).y - 22 * j);
            }
            
            this->addChild(jong,10);
            record.pokersRecord.pushBack(jong);
        }
        playerCpgRecords.push_back(record);
    }
}


void PlayerLeft::recoverHand(std::string hand){
    playerHandJongs.clear();
    vector<std::string>  hands = StringUtil::split(hand, ",");
    for (int i = 0; i < hands.size(); i++)
    {
        Jong* jong = Jong::create();
        jong->showJong(lefthand, -1);
        jong->setPosition(Point(LEFT_POS_X, LEFT_POS_Y + 35 * i));
        playerHandJongs.pushBack(jong);
        this->addChild(jong,60-i);
    }
}

void PlayerLeft::updateHandJongs(std::string jongs){
    vector<std::string> pokers = StringUtil::split(jongs, ",");
    for (int i = 0; i < pokers.size(); i++)
    {
        Jong* jong = Jong::create();
        jong->showJong(leftplayed, atoi(pokers.at(i).c_str()));
        jong->setPosition(Point(LEFT_POS_X, LEFT_POS_Y + 30 * i));
        playerHandJongs.pushBack(jong);
        this->addChild(jong,60-i);
        
    }
    
}
