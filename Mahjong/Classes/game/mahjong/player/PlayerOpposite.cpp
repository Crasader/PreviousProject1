#include "game/mahjong/player/PlayerOpposite.h"
#include "game/mahjong/core/MahjongView.h"
#include "game/mahjong/anim/HuaAnim.hpp"

bool PlayerOpposite::init(){
    if (!PlayerBase::init()){
        return false;
    }
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
    biaoji->setPosition(getPlayedJongPos(playerPlayedJongs.size() - 1).x, getPlayedJongPos(playerPlayedJongs.size() - 1).y + 20);
    biaoji->setVisible(isShow);
}

Point PlayerOpposite::getCpgShowPostion(int index){
    return Point(865 - index * 115, 678);
}


void PlayerOpposite::drawOppositePlayerTurn(){
    Jong* jong = Jong::create();
    jong->setTag(111);
    jong->showJong(oppositehand, -1);
    jong->setPosition(Point(OPPOSITE_POS_X - 40, OPPOSITE_POS_Y + 20));
    this->addChild(jong);
    playerHandJongs.pushBack(jong);
    MoveTo* move = MoveTo::create(0.2f, Point(OPPOSITE_POS_X - 40, OPPOSITE_POS_Y));
    ActionInterval* dou = EaseBackInOut::create(move);
    jong->runAction(dou);
}

void PlayerOpposite::drawPlayedJong(int ctype){
    Jong* lastPlayedJong = Jong::create();
    lastPlayedJong->showJong(oppositeplayed, ctype);
    lastPlayedJong->setPosition(Point(OPPOSITE_POS_X - 31, OPPOSITE_POS_Y));
    playerPlayedJongs.pushBack(lastPlayedJong);
    if (playerPlayedJongs.size() / 6 == 0){
        this->addChild(lastPlayedJong, 3);
    }
    else if (playerPlayedJongs.size() / 6 == 1){
        this->addChild(lastPlayedJong, 2);
    }
    else{
        this->addChild(lastPlayedJong, 1);
    }
    Point startPoint = Point(OPPOSITE_POS_X - 31, OPPOSITE_POS_Y);
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
            getChildByTag(111)->removeFromParent();}
        if(getStateCpg()){
            playerHandJongs.at(playerHandJongs.size() - 1)->removeFromParent();
            playerHandJongs.eraseObject(playerHandJongs.at(playerHandJongs.size() - 1));
            setStateCpg(false);
        }
    }), NULL) ,callback, NULL);
    lastPlayedJong->runAction(sequence);
    
}


void PlayerOpposite::drawHuaJong(){
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
        HuaAnim* huaAnim = HuaAnim::create(needReplace, ClientSeatId::opposite ,CallFunc::create([=](){
            setHuaNum(getHuaNum()+needReplace.size());
            showPlayerHua(Vec2(800,615),getHuaNum());
        }));
        addChild(huaAnim,100);
    }
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

void PlayerOpposite::drawOppositePlayerPlay(int type){
    drawPlayedJong(type);
    showCurrentBigJong(type, Vec2(640, 550));
}

void PlayerOpposite::removeLastJong(){
    playerPlayedJongs.at(playerPlayedJongs.size() - 1)->removeFromParent();
    playerPlayedJongs.popBack();
    biaoji->setVisible(false);
}

void PlayerOpposite::playerTurnReplace(PlayerTurnData data){
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
            HuaAnim* huaAnim = HuaAnim::create(needReplace, ClientSeatId::opposite,CallFunc::create([=](){
                setHuaNum(getHuaNum()+1);
                showPlayerHua(Vec2(800,615),getHuaNum());
            }));
            addChild(huaAnim,100);
            huaIndex++;
        }), DelayTime::create(2.0f),NULL),replace.size()-1));
    }
}

void PlayerOpposite::drawPlayerChi(PlayerCpgtData data, PlayerBase* playerBase){
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
        jong->showJong(oppositeplayed, atoi(chi.at(i).c_str()));
        jong->setPosition(Point(getCpgShowPostion(playerCpgRecords.size()).x - 35 * i, getCpgShowPostion(playerCpgRecords.size()).y));
        this->addChild(jong, 30 - playerCpgRecords.size());
        record.pokersRecord.pushBack(jong);
    }
    this->playerCpgRecords.push_back(record);
}


void PlayerOpposite::drawPlayerPeng(PlayerCpgtData data, PlayerBase* playerBase){
    setStateCpg(true);
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
    if (data.flag == 2){
        ((MahjongView*)getParent())->removeHeroPlayedIcon();
    }
    else{
        int size = playerHandJongs.size();
        for (int j = 1; j <= 3; j++){
            playerHandJongs.at(size - j)->removeFromParent();
            playerHandJongs.eraseObject(playerHandJongs.at(size - j));
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
                    jong->showJong(oppositeplayed, atoi(data.poker.c_str()));
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
                jong->showJong(oppositedeal, -1);
            }
            else{
                jong->showJong(oppositeplayed, atoi(gang.at(i).c_str()));
            }
            if (i == 3){
                jong->setPosition(Point(getCpgShowPostion(playerCpgRecords.size()).x - 35, getCpgShowPostion(playerCpgRecords.size()).y - 2));
                this->addChild(jong, 10);
            }
            else{
                jong->setPosition(Point(getCpgShowPostion(playerCpgRecords.size()).x - 35 * i, getCpgShowPostion(playerCpgRecords.size()).y));
                record.pokersRecord.pushBack(jong);
                this->addChild(jong, 5);
            }
        }
        this->playerCpgRecords.push_back(record);
    }
}

void PlayerOpposite::recoverHua(int hua){
    setHuaNum(hua);
    showPlayerHua(Vec2(800,615),getHuaNum());
}


void PlayerOpposite::updateHandJongs(std::string jongs){
    vector<std::string> pokers = StringUtil::split(jongs, ",");
    for (int i = 0; i < pokers.size(); i++)
    {
        Jong* jong = Jong::create();
        jong->showJong(oppositeplayed, atoi(pokers.at(i).c_str()));
        jong->setPosition(Point(OPPOSITE_POS_X + 32 * i, OPPOSITE_POS_Y));
        this->addChild(jong);
    }
    
}

void PlayerOpposite::recoverPlayed(std::string played){
    playerPlayedJongs.clear();
    vector<std::string>  playeds = StringUtil::split(played, ",");
    for (int i = 0; i < playeds.size(); i++){
        Jong* lastPlayedJong = Jong::create();
        lastPlayedJong->showJong(oppositeplayed, atoi(playeds.at(i).c_str()));
        lastPlayedJong->setPosition(getPlayedJongPos(playerPlayedJongs.size()));
        this->addChild(lastPlayedJong);
        playerPlayedJongs.pushBack(lastPlayedJong);
    }
}


void PlayerOpposite::recoverCpg(vector<PlayerChiData> chi,vector<PlayerPengData> peng,vector<PlayerGangData> gang,std::string angang){
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
                jong->showJong(leftplayed, atoi(gang.at(i).gang.c_str()));
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
    if(angang != ""){
        for(int i=0;i<gang.size();i++){
            PlayerCpgRecord record;
            record.type = CpgType::gang;
            for(int j=0;j<4;j++){
                Jong* jong = Jong::create();
                jong->showJong(oppositedeal, atoi(gang.at(i).gang.c_str()));
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