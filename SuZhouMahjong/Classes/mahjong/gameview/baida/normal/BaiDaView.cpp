#include "mahjong/gameview/baida/normal/BaiDaView.h"
#include "mahjong/gameview/widget/SoundRecordBtn.hpp"
#include "mahjong/gameview/anim/DealJongAnim.h"
#include "mahjong/gameview/anim/PlayerCpgAnim.hpp"
#include "mahjong/gameview/anim/LiuJuAnim.hpp"
#include "mahjong/common/state/GameData.h"
#include "mahjong/common/utils/SeatIdUtil.h"
#include "mahjong/common/dialog/prompt/HintDialog.hpp"
#include "mahjong/common/dialog/prompt/TextHintDialog.hpp"
#include "mahjong/common/utils/StringUtil.h"
#include "mahjong/common/utils/Chinese.h"
#include "mahjong/lobby/LobbyScene.h"
#include "mahjong/result/ResultScene.hpp"
#include "mahjong/gameview/anim/HupaiAnim.hpp"

bool BaiDaView::init(){
    if (!BaseView::init())
    {
        return false;
    }
    
    initBaiDaMahjong();
    
    if (GAMEDATA::getInstance()->getIsRecover()){
        doRecoverGame();
    }else{
        addPlayerToRoom();
    }
    return true;
}

void BaiDaView::initBaiDaMahjong(){
    GAMEDATA::getInstance()->setIsPlaying(false);
    GAMEDATA::getInstance()->setIsLiuJu(false);
    GAMEDATA::getInstance()->setIsGotoLobby(false);
    
    auto gameName = Sprite::create("gameview/zi_baidamajiang.png");
    gameName->setPosition(640,300);
    addChild(gameName);
    //自摸和七对
    auto payModle = Sprite::create();
    if(GAMEDATA::getInstance()->getIsPayWayAA()){
        payModle->setTexture("gameview/aa_zhu_open.png");
    }else{
        payModle->setTexture("gameview/fang_zhu_open.png");
    }
    addChild(payModle);
    auto zimo  = Sprite::create("gameview/zi_zhinengzimo.png");
    addChild(zimo);
    if(GAMEDATA::getInstance()->getPrivateZiMo() == "1"){
        zimo->setVisible(true);
    }else{
        zimo->setVisible(false);
    }
    
    auto qidui = Sprite::create("gameview/zi_huqidui.png");
    addChild(qidui);
    if(GAMEDATA::getInstance()->getPrivateQiDui() == "1"){
        qidui->setVisible(true);
    }else{
        qidui->setVisible(false);
    }
    
    auto fanpai = Sprite::create();
    if(GAMEDATA::getInstance()->getPrivateFanPai() == "2"){
        fanpai->setTexture("gameview/zi_fan2.png");
    }else if(GAMEDATA::getInstance()->getPrivateFanPai() == "4"){
        fanpai->setTexture("gameview/zi_fan4.png");
    }else if(GAMEDATA::getInstance()->getPrivateFanPai() == "6"){
        fanpai->setTexture("gameview/zi_fan6.png");
    }else{
        fanpai->setTexture("gameview/zi_bufanpai.png");
    }
    addChild(fanpai);
    
    auto difen = Sprite::create("gameview/zi_di_5.png");
    addChild(difen);
    
    int wid =payModle->getContentSize().width +(zimo->isVisible()?zimo->getContentSize().width:0) + (qidui->isVisible()?qidui->getContentSize().width:0)+fanpai->getContentSize().width+difen->getContentSize().width;
    payModle->setPosition((Director::getInstance()->getVisibleSize().width-wid)/2,160);
    payModle->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    zimo->setPosition((Director::getInstance()->getVisibleSize().width-wid)/2+payModle->getContentSize().width,160);
    zimo->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    qidui->setPosition((Director::getInstance()->getVisibleSize().width-wid)/2+payModle->getContentSize().width+(zimo->isVisible()?zimo->getContentSize().width:0),160);
    qidui->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    fanpai->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    fanpai->setPosition((Director::getInstance()->getVisibleSize().width-wid)/2+payModle->getContentSize().width+(zimo->isVisible()?zimo->getContentSize().width:0)+(qidui->isVisible()?qidui->getContentSize().width:0),160);
    difen->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    difen->setPosition((Director::getInstance()->getVisibleSize().width-wid)/2+payModle->getContentSize().width+(zimo->isVisible()?zimo->getContentSize().width:0)+(qidui->isVisible()?qidui->getContentSize().width:0)+(fanpai->isVisible()?fanpai->getContentSize().width:0),160);
}

void BaiDaView::checkHeroHandPoker(){
    if(NULL != playerHero)
        playerHero->checkBaiDaHeroHandPoker();
}

void BaiDaView::dealJongFinish(MahjongFaPaiData data){
    BaseView::dealJongFinish(data);
    showGameBank(GAMEDATA::getInstance()->getHeroSeatId(),GAMEDATA::getInstance()->getCurrentBank());
    for (auto var : data.huas) {
        int seat = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), atoi(var.setaId.c_str()));
        if(seat == ClientSeatId::left){
            if(NULL != playerLeft){
                playerLeft->drawHandJong();
                playerLeft->recoverHua(var.hua);
                playerLeft->setIsReady(false);
                
            }
        }else if(seat == ClientSeatId::right){
            if(NULL != playerRight){
                playerRight->drawHandJong();
                playerRight->recoverHua(var.hua);
                playerRight->setIsReady(false);
            }
        }else if(seat == ClientSeatId::opposite){
            if(NULL != playerOpposite){
                playerOpposite->drawHandJong();
                playerOpposite->recoverHua(var.hua);
                playerOpposite->setIsReady(false);
            }
        }else if(seat == ClientSeatId::hero){
            if(NULL != playerHero){
                playerHero->drawPlayerHero(data.heroPokers);
                playerHero->recoverHua(var.hua);
                playerHero->setIsReady(false);
            }
        }
    }
    //判断是或自己出牌
    if(GAMEDATA::getInstance()->getCurrentBank() == GAMEDATA::getInstance()->getHeroSeatId()){
        //手牌检查
        checkHeroHandPoker();
        playerHero->setIsAllowPlay(true);
        if(data.mjHuData.hu == 1||data.hasGang){
            showBaiDaControllPad(data.mjHuData);
            playerHero->startTimeClockAnim(9, 2);
        }
    }
    startCountdown();
}

void BaiDaView::showBaiDaControllPad(PlayerCpgtData newData){
    controllPad->removeAllChildrenWithCleanup(true);
    playerHero->setIsAllowPlay(false);
    MenuItemImage* peng = nullptr;
    MenuItemImage* gang = nullptr;
    MenuItemImage* hu = nullptr;
    int buttonCount = 0;
    if (newData.hu == 1){
        hu = MenuItemImage::create("gameview/mj_hu.png", "gameview/mj_hu.png", CC_CALLBACK_1(BaiDaView::doBaiDaHuAction, this));
        hu->setPosition(Point(-buttonCount * 160+10, 0));
        controllPad->addChild(hu);
        buttonCount++;
    }
    if (newData.playerGang.size()>0){
        gang = MenuItemImage::create("gameview/mj_gang.png", "gameview/mj_gang.png", CC_CALLBACK_1(BaiDaView::showBaiDaGangChoice, this));
        gang->setPosition(Point(-buttonCount * 160, 0));
        controllPad->addChild(gang);
        PlayerCpgtData* gangData = new PlayerCpgtData(newData);
        gang->setUserData(gangData);
        buttonCount++;
    }
    if (newData.peng != ""){
        peng = MenuItemImage::create("gameview/mj_peng.png", "gameview/mj_peng.png", CC_CALLBACK_1(BaiDaView::doBaiDaPengAction, this));
        peng->setPosition(Point(-buttonCount * 160, 0));
        controllPad->addChild(peng);
        peng->setName(newData.peng);
        peng->setTag(atoi(newData.poker.c_str()));
        buttonCount++;
    }
    auto qi = MenuItemImage::create("gameview/mj_qi.png", "gameview/mj_qi.png", CC_CALLBACK_1(BaiDaView::doBaiDaQiAction,this));
    qi->setPosition(Point(-buttonCount * 160, 0));
    controllPad->addChild(qi);
    controllPad->setVisible(true);
}

void BaiDaView::hideBaiDaControllPad(){
    controllPad->setVisible(false);
    playerHero->stopTimeClockAnim();//玩家停止倒计时
    if (NULL != getChildByTag(1892)){
        getChildByTag(1892)->setVisible(false);
        getChildByTag(1892)->removeAllChildren();
    }
    schedule([=](float dt){
        controllPad->removeAllChildrenWithCleanup(true);
    }, 0, 0, 0.2f,"dalayRemovepad");
}


void BaiDaView::doBaiDaQiAction(Ref* ref){
    if(turnHeroSelf|| playerHero->getSelfHandJongs().size() == 14){
        turnHeroSelf = false;
        playerHero->setIsAllowPlay(true);
    }else{
         playerHero->setIsAllowPlay(false);
    }
    controllPad->setVisible(false);
    playerHero->stopTimeClockAnim();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getBDGiveUpCommand());
}

void BaiDaView::doBaiDaHuAction(Ref* ref){
    controllPad->setVisible(false);
    playerHero->stopTimeClockAnim();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getBDHuActionCommand("1"));
}


void BaiDaView::doBaiDaPengAction(Ref* ref){
    controllPad->setVisible(false);
    playerHero->stopTimeClockAnim();
    MenuItemImage* temp = (MenuItemImage*)ref;
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getBDPengCommand(temp->getName(), temp->getTag()));
}

void BaiDaView::showBaiDaGangChoice(Ref* ref){
    controllPad->setVisible(false);
    MenuItemImage* temp = (MenuItemImage*)ref;
    PlayerCpgtData* data = static_cast<PlayerCpgtData*>(temp->getUserData());
    std::vector<std::string> allGangs;
    for (auto var : data->playerGang) {
        std::vector<std::string> temp = StringUtil::split(var.gang, ",");
        std::string temp2 = "";
        for(auto gang : temp){
            if(temp2 != gang){
                allGangs.push_back(gang);
                temp2 = gang;
            }
        }
    }
    if (allGangs.size()>1){
        //对杠牌的大小进行排序
        for (int j = (int)allGangs.size()-1; j > 0; j--) {
            for (int k = 0; k < j; k++) {
                if ( allGangs[k] <  allGangs[k + 1]) {
                    auto temp =  allGangs[k];
                    allGangs[k] = allGangs[k + 1];
                    allGangs[k + 1] = temp;
                }
            }
        }
        auto choiceMenu = Sprite::create();
        choiceMenu->setTag(1892);
        choiceMenu->setAnchorPoint(Point(0, 0));
        choiceMenu->setPosition(Point(0, 0));
        addChild(choiceMenu, 100);
        for (int i = 0; i < allGangs.size(); i++){
            if( allGangs.at(i) == ""){
                continue;
            }
            auto choice = Menu::create();
            choice->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
            for (int l = 0; l < 4; l++){
                Sprite* chibg = Sprite::create("jong/middle_2.png");
                chibg->setPosition(1000 + l * 40 - i * 170, 150);
                choiceMenu->setVisible(true);
                choiceMenu->addChild(chibg);
                std::string imageName = Jong::getContextImage(atoi(allGangs.at(i).c_str()));
                MenuItemImage* imageItem = MenuItemImage::create(imageName, imageName, CC_CALLBACK_1(BaiDaView::doBaiDaGangAction, this));
                imageItem->setTag(atoi(allGangs.at(i).c_str()));
                imageItem->setPosition(1000 + l * 40 - i * 170, 160);
                imageItem->setScale(0.5f);
                choice->addChild(imageItem);
                imageItem->setUserData(data);
            }
            choice->setPosition(0, 0);
            choiceMenu->addChild(choice);
        }
        playerHero->startTimeClockAnim(9, 1);
    }
    else{
        MenuItemImage* imageItem = MenuItemImage::create();
        imageItem->setTag(atoi(allGangs.at(0).c_str()));
        imageItem->setUserData(data);
        doBaiDaGangAction(imageItem);
    }
}
void BaiDaView::doBaiDaGangAction(Ref* ref){
    controllPad->setVisible(false);
    playerHero->stopTimeClockAnim();
    MenuItemImage* item = (MenuItemImage*)ref;
    PlayerCpgtData* data = static_cast<PlayerCpgtData*>(item->getUserData());
    int tag = item->getTag();
    GangData gangData;
    for (auto var : data->playerGang) {
        std::vector<std::string> temp = StringUtil::split(var.gang, ",");
        for(auto gang : temp){
            if(atoi(gang.c_str()) == tag){
                gangData = var;
            }
        }
    }
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getBDGangCommand(StringUtils::format("%d",tag),tag,gangData.flag));
    
    if (NULL != getChildByTag(1892)){
        getChildByTag(1892)->setVisible(false);
        getChildByTag(1892)->removeAllChildren();
    }
    CC_SAFE_DELETE(data);
}

void BaiDaView::doRecoverGame(){
    //重绘制场景
    GAMEDATA::getInstance()->clearPlayersInfo();
    LastGameData data = GAMEDATA::getInstance()->getLastGameDataBackup();
    GAMEDATA::getInstance()->setIsPlaying(true);
    if(data.result == 1){
        GAMEDATA::getInstance()->setHeroSeatId(data.seatId);
        GAMEDATA::getInstance()->setCurrentBank(data.loard);
        updateRoomInfo();
        for (int i = 0; i < data.players.size(); i++)
        {
            PlayerGameData player = data.players.at(i);
            PlayerInfo* info = new PlayerInfo();
            info->setSeatId(player.seatId);
            info->setScore(player.jifen);
            info->setPoxiaoId(player.poxiaoId);
            info->setIsReady(true);
            info->setGold(player.gold);
            info->setDiamond(player.diamond);
            info->setNickname(player.nickname);
            info->setPicture(player.pic);
            info->setGender(player.gender);
            info->setTicket(player.lequan);
            info->setLockDiamond(player.bangzuan);
            info->setFangka(player.fangka);
            info->setIP(player.ip);
            info->setUmark(player.umark);
            GAMEDATA::getInstance()->addPlayersInfo(info);
            doRecoverPlayer(player, SeatIdUtil::getClientSeatId(data.seatId, player.seatId), info);
        }
        showPaiduiNum(atoi(data.rest.c_str()));
    }else{
        for (int i = 0; i < data.players.size(); i++)
        {
            PlayerGameData player = data.players.at(i);
            PlayerInfo* info = new PlayerInfo();
            info->setSeatId(player.seatId);
            info->setGold(player.gold);
            info->setDiamond(player.diamond);
            info->setNickname(player.nickname);
            info->setPicture(player.pic);
            info->setGender(player.gender);
            info->setScore(player.jifen);
            info->setTicket(player.lequan);
            info->setLockDiamond(player.bangzuan);
            info->setPoxiaoId(player.poxiaoId);
            info->setFangka(player.fangka);
            info->setIsReady(true);
            info->setIP(player.ip);
            info->setUmark(player.umark);
            GAMEDATA::getInstance()->addPlayersInfo(info);
        }
        addPlayerToRoom();
    }
}

void BaiDaView::doRecoverPlayer(PlayerGameData data, int type, PlayerInfo* playerInfo){
    if (type == ClientSeatId::hero){
        if (playerHero == NULL){
            playerHero = PlayerHero::create();
            playerHero->initPlayer(playerInfo);
            playerHero->setIsAllowPlay(false);
            addChild(playerHero, 2);
            playerHero->recoverCpg(data.chiData ,data.pengData , data.gangData,data.angang);
            playerHero->recoverHand(data.hand,data.lastpoker);
            playerHero->recoverPlayed(data.outhand);
            playerHero->recoverHua(data.hua);
        }
    }
    else if (type == ClientSeatId::left){
        if (playerLeft == NULL){
            playerLeft = PlayerLeft::create();
            playerLeft->initPlayer(playerInfo);
            playerLeft->setIsOffLine(data.isOnline == 0?true:false);
            addChild(playerLeft);
            playerLeft->recoverCpg(data.chiData ,data.pengData , data.gangData,data.angang);
            playerLeft->recoverHand(data.hand);
            playerLeft->recoverPlayed(data.outhand);
            playerLeft->recoverHua(data.hua);
            
        }
    }
    else if (type == ClientSeatId::right){
        if (playerRight == NULL){
            playerRight = PlayerRight::create();
            playerRight->initPlayer(playerInfo);
            playerRight->setIsOffLine(data.isOnline == 0?true:false);
            addChild(playerRight);
            playerRight->recoverCpg(data.chiData ,data.pengData , data.gangData,data.angang);
            playerRight->recoverHand(data.hand);
            playerRight->recoverPlayed(data.outhand);
            playerRight->recoverHua(data.hua);
            
        }
    }
    else if (type == ClientSeatId::opposite){
        if (playerOpposite == NULL){
            playerOpposite = PlayerOpposite::create();
            playerOpposite->initPlayer(playerInfo);
            playerOpposite->setIsOffLine(data.isOnline == 0?true:false);
            addChild(playerOpposite);
            playerOpposite->recoverCpg(data.chiData ,data.pengData , data.gangData,data.angang);
            playerOpposite->recoverHand(data.hand);
            playerOpposite->recoverPlayed(data.outhand);
            playerOpposite->recoverHua(data.hua);
            
        }
    }
}


void BaiDaView::showHuPaiXing(std::string paixing){
    if(paixing==""){
        return;
    }
    vector<string> pais = StringUtil::split(paixing, ",");
    //    bool hasPaiXing = false;
    //    for(auto type:pais){
    //        if(type == "3"||type == "12"||type == "13"||type == "14"){
    //            hasPaiXing = true;
    //        }
    //    }
    //    if(!hasPaiXing){
    //        return;
    //    }
    float posY = 260;
    //判断是不是自己胡了
    vector<GameResultData> results = GAMEDATA::getInstance()->getGameResults();
    for(auto var : results){
        if(var.seatId == GAMEDATA::getInstance()->getHeroSeatId()){
            if(var.result == 1||var.result == 3){
                posY=520;
            }
        }
    }
    auto paixinBg = Sprite::create("result/second_bg.png");
    paixinBg->setScaleY(1.4f);
    paixinBg->setPosition(640,posY);
    addChild(paixinBg,999);
    paixinBg->setOpacity(77);
    paixinBg->runAction(Sequence::create(FadeTo::create(3.0/24, 255), NULL));
    
    std::vector<int> hutemp;
    for(auto var:pais){
        hutemp.push_back(atoi(var.c_str()));
    }
    sort(hutemp.begin(), hutemp.end());
    
    for(int i =((int)hutemp.size()-1); i>=0;i--){
        auto xing = Sprite::create(StringUtils::format("result/paixing_%d.png",atoi(pais.at(i).c_str())));
        addChild(xing,999);
        xing->setOpacity(77);
        xing->setScale(3.0f);
        xing->setPosition(640 - 100*(hutemp.size()-1)+(hutemp.size()-1-i)*200,posY);
        xing->runAction(Sequence::create(DelayTime::create(i*(5.0f/24)),Spawn::create(ScaleTo::create(3.0/24, 0.8f),FadeTo::create(3.0f/24, 255), NULL),ScaleTo::create(2.0/24, 1.0f), NULL));
    }
    //光效动画
    Point pos1 = Point(200,posY);
    Point pos2 = Point(1000,posY);
    Sprite* guangXiao1 = Sprite::create("result/hupai_light.png");
    guangXiao1->setPosition(pos1);
    guangXiao1->setOpacity(77);
    addChild(guangXiao1,999);
    guangXiao1->runAction(Sequence::create(DelayTime::create(12.0f/24),Spawn::create(ScaleTo::create(5.0/24, 2.0f,1.2f),MoveTo::create(5.0/24, pos2),FadeTo::create(5.0/24, 200),NULL),Spawn::create(ScaleTo::create(5.0/24, 1.0f,1.0f),MoveTo::create(5.0/24, pos2), FadeTo::create(5.0/24, 0), NULL),NULL));
    
    
}

void BaiDaView::showHandPokerOver(int seatId){
    vector<GameResultData> results = GAMEDATA::getInstance()->getGameResults();
    string leftJongs="";
    string rightJongs="";
    string oppositeJongs="";
    string heroJongs="";
    int max =0;
    string maxHuType="";
    for (GameResultData data: results) {
        int seat = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), data.seatId);
        if(seat == ClientSeatId::left){
            leftJongs =data.showPoker;
        }else if(seat == ClientSeatId::opposite){
            oppositeJongs =data.showPoker;
        }else if(seat == ClientSeatId::right){
            rightJongs =data.showPoker;
        }else{
            heroJongs =data.showPoker;
        }
        //获取一炮多响情况下胡的最大的数据
        if(GAMEDATA::getInstance()->getMahjongRoomType()==MahjongRoom::privateRoom){
            if(data.jifendelta >= max){
                maxHuType = data.huType;
                max = data.jifendelta;
            }
        }else{
            if(data.golddelta >= max){
                maxHuType = data.huType;
                max =data.golddelta;
            }
        }
    }
    //翻牌
    if(seatId == ClientSeatId::left){
        if(NULL != playerLeft){
            playerLeft->hideHandJongs();
            playerLeft->updateHandJongs(leftJongs,true);
        }
        showHuPaiXing(maxHuType);
        schedule([=](float dt){
            if(NULL != playerRight){
                playerRight->hideHandJongs();
                playerRight->updateHandJongs(rightJongs,false);
            }
            if(NULL != playerOpposite){
                playerOpposite->hideHandJongs();
                playerOpposite->updateHandJongs(oppositeJongs,false);
            }
            playerHero->hideHandJongs();
            playerHero->updateHandJongs(heroJongs,false);
        }, 0, 0, 15.0f/24,"fanpai");
    }else if(seatId == ClientSeatId::opposite){
        if(NULL != playerOpposite){
            playerOpposite->hideHandJongs();
            playerOpposite->updateHandJongs(oppositeJongs,true);
        }
        showHuPaiXing(maxHuType);
        schedule([=](float dt){
            if(NULL != playerRight){
                playerRight->hideHandJongs();
                playerRight->updateHandJongs(rightJongs,false);
            }
            if(NULL != playerLeft){
                playerLeft->hideHandJongs();
                playerLeft->updateHandJongs(leftJongs,false);
            }
            playerHero->hideHandJongs();
            playerHero->updateHandJongs(heroJongs,false);
        }, 0, 0, 15.0f/24,"fanpai");
    }else if(seatId == ClientSeatId::right){
        if(NULL != playerRight){
            playerRight->hideHandJongs();
            playerRight->updateHandJongs(rightJongs,true);
        }
        showHuPaiXing(maxHuType);
        schedule([=](float dt){
            if(NULL != playerOpposite){
                playerOpposite->hideHandJongs();
                playerOpposite->updateHandJongs(oppositeJongs,false);
            }
            if(NULL != playerLeft){
                playerLeft->hideHandJongs();
                playerLeft->updateHandJongs(leftJongs,false);
            }
            playerHero->hideHandJongs();
            playerHero->updateHandJongs(heroJongs,false);
        }, 0, 0, 15.0f/24,"fanpai");
    }else{
        playerHero->hideHandJongs();
        if(GAMEDATA::getInstance()->getIsLiuJu()){
            playerHero->updateHandJongs(heroJongs,false);
        }else{
            playerHero->updateHandJongs(heroJongs,true);
        }
        showHuPaiXing(maxHuType);
        schedule([=](float dt){
            if(NULL != playerOpposite){
                playerOpposite->hideHandJongs();
                playerOpposite->updateHandJongs(oppositeJongs,false);
            }
            if(NULL != playerRight){
                playerRight->hideHandJongs();
                playerRight->updateHandJongs(rightJongs,false);
            }
            if(NULL != playerLeft){
                playerLeft->hideHandJongs();
                playerLeft->updateHandJongs(leftJongs,false);
            }
        }, 0, 0, 15.0f/24,"fanpai");
    }
}


void BaiDaView::onEnterTransitionDidFinish(){
    BaseView::onEnterTransitionDidFinish();
    scheduleUpdate();
    if(GAMEDATA::getInstance()->getContinueAgain()){
        GAMEDATA::getInstance()->setContinueAgain(false);
        schedule([=](float dt){
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendBDReadyCommand());
        }, 0, 0, 0.5f,"continueGame");
    }
    
    if (GAMEDATA::getInstance()->getIsRecover()){
        //重新设置庄的位置
        LastGameData data = GAMEDATA::getInstance()->getLastGameDataBackup();
        if(data.result == 1){
            checkHeroHandPoker();
            showGameBank(GAMEDATA::getInstance()->getHeroSeatId(),GAMEDATA::getInstance()->getCurrentBank());
            showGameTurn(GAMEDATA::getInstance()->getHeroSeatId(),data.turn);
            showMahjongDiec(GAMEDATA::getInstance()->getMahjongDice());
            int lastplayerSeat = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(),data.pre);
            if(lastplayerSeat == ClientSeatId::hero){
                playerHero->showPlayedJongSign(true);
            }else if(lastplayerSeat == ClientSeatId::left){
                playerLeft->showPlayedJongSign(true);
            }else if(lastplayerSeat == ClientSeatId::opposite){
                playerOpposite->showPlayedJongSign(true);
            }else if(lastplayerSeat == ClientSeatId::right){
                playerRight->showPlayedJongSign(true);
            }
            int playturn = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), data.turn);
            if(playturn == ClientSeatId::hero){
                if(!GAMEDATA::getInstance()->getIsTrusteeship()){
                    playerHero->startTimeClockAnim();
                }
                if(!GAMEDATA::getInstance()->getTurnHeroCpg()){
                    playerHero->setIsAllowPlay(true);
                }
            }else if(playturn == ClientSeatId::left){
                playerLeft->startTimeClockAnim();
            }else if(playturn == ClientSeatId::opposite){
                playerOpposite->startTimeClockAnim();
            }else if(playturn == ClientSeatId::right){
                playerRight->startTimeClockAnim();
            }
            startCountdown();
        }
        GAMEDATA::getInstance()->setIsRecover(false);
    }
    GAMEDATA::getInstance()->setIsInGameScene(true);
}


void BaiDaView::onExit()
{
    BaseView::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(faPaiNotifyListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(turnListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(otherPlayerPlayedListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(gameResultListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(playerCpgListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(othersPengListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(othersGangListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(trusteeshipCancelListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(heroPengRespListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(heroGangRespListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(openFriendRoomListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(enterFriendRoomListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(trusteeshipNotifyListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(conncetAgainListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(playeHuActionListener);
    
}

void BaiDaView::onEnter(){
    BaseView::onEnter();
    faPaiNotifyListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_GAME_BD_START_FAPAI_NOTIFY, [=](EventCustom* event){
        if(GAMEDATA::getInstance()->getIsPlaying()){
            return;
        }
        playerHero->drawReady(true);
        float delay = 0;
        MahjongFaPaiData newMsgData = GAMEDATA::getInstance()->getMahjongFaPaiData();
        GAMEDATA::getInstance()->setCurrentBank(newMsgData.start);
        FriendOpenRoomRespData data = GAMEDATA::getInstance()->getFriendOpenRoomResp();
        data.prjucount = StringUtils::format("%d",newMsgData.prjucount);
        GAMEDATA::getInstance()->setFriendOpenRoomResp(data);
        GAMEDATA::getInstance()->setIsPlaying(true);//游戏状态改为游戏中
        updateRoomInfo();
        if(NULL != playerHero){
            playerHero->setIsReady(false);//关闭准备的显示
            playerHero->hideInviteButton();//隐藏玩家的邀请按钮45
        }
        if(NULL != playerRight){
            playerRight->setIsReady(false);
        }
        if(NULL != playerOpposite){
            playerOpposite->setIsReady(false);
        }
        if(NULL != playerLeft){
            playerLeft->setIsReady(false);
        }
        hideDissovleBtn();//隐藏房主的解散按钮
        schedule([=](float dt){
            DealJongAnim* anim = DealJongAnim::create();
            anim->setTag(1000);
            anim->showDealJong(SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), GAMEDATA::getInstance()->getCurrentBank()) ,newMsgData);
            addChild(anim);
        },0,0,delay,"hi_jim");
        
    });
    //断线续玩
    conncetAgainListener=  Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_PLAYER_CM_CONNECT_AGAIN, [=](EventCustom* event){
        //重新绘制玩家的牌和话
        GAMEDATA::getInstance()->setIsRecover(true);
        Director::getInstance()->replaceScene(MjGameScene::create());
        
    });
    
    //好友房间游戏未开始重新连接
    openFriendRoomListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_CM_FRIEND_OPEN_ROOM_RESP, [=](EventCustom* event){
        GAMEDATA::getInstance()->setGameType(5);
        GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
        FriendOpenRoomRespData resp = GAMEDATA::getInstance()->getFriendOpenRoomResp();
        for(auto var: GAMEDATA::getInstance()->getPlayersInfo()){
            if(var->getPoxiaoId() == UserData::getInstance()->getPoxiaoId()){
                var->setIsReady(false);
            }
        }
        if(resp.result == 1){
            schedule([=](float dt){
                GAMEDATA::getInstance()->setFangZhuId(UserData::getInstance()->getPoxiaoId());
                Director::getInstance()->replaceScene(MjGameScene::create());
            }, 0, 0, 1.0f,"continueGame223");
        }
    });
    
    enterFriendRoomListener=  Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_CM_ENTER_FRIEND_ROOM_RESP, [=](EventCustom* event){
        int result = GAMEDATA::getInstance()->getFriendOpenRoomResp().result;
        for(auto var: GAMEDATA::getInstance()->getPlayersInfo()){
            if(var->getPoxiaoId() == UserData::getInstance()->getPoxiaoId()){
                var->setIsReady(false);
            }
        }
        if (result == 1){
            schedule([=](float dt){
                GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
                Director::getInstance()->replaceScene(TransitionFade::create(1.0f, MjGameScene::create()));
            }, 0, 0, 2.0f,"continueGame223");
        }
    });
    
    heroGangRespListener = EventListenerCustom::create(MSG_HERO_GANG_RESP, [=](EventCustom* event){
        HeroCpgRespData* resp = static_cast<HeroCpgRespData*>(event->getUserData());
        HeroCpgRespData newResp = *resp;
        playerHero->hidePlayedBigJong();
        int clientSeatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), newResp.playCpgt.sId);
        if (newResp.result == 0){
            playerHero->stopTimeClockAnim();
        }
        else{
            if (clientSeatId == ClientSeatId::right){
                playerHero->drawHeroGang(newResp, playerRight);
            }
            else if (clientSeatId == ClientSeatId::opposite){
                playerHero->drawHeroGang(newResp, playerOpposite);
            }
            else{
                playerHero->drawHeroGang(newResp, playerLeft);
            }
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(heroGangRespListener, 1);
    
    othersPengListener = EventListenerCustom::create(MSG_OTHER_PLAYER_PENG, [=](EventCustom* event){
        PlayerCpgtData* data = static_cast<PlayerCpgtData*>(event->getUserData());
        PlayerCpgtData newData = *data;
        int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), newData.seatId);
        showGameTurn(GAMEDATA::getInstance()->getHeroSeatId(),newData.seatId);
        setPlayPokerSignPosition(false,Point(0,0));
        if (seatId == ClientSeatId::left){
            hideBaiDaControllPad();
            playerLeft->drawPlayerPeng(newData, getPlayerBySeatId(data->sId));
            playerLeft->playerCpgAnim(CpgType::peng, ClientSeatId::left);
            playerLeft->startTimeClockAnim();
        }
        else if (seatId == ClientSeatId::right){
            hideBaiDaControllPad();
            playerRight->drawPlayerPeng(newData, getPlayerBySeatId(data->sId));
            playerRight->playerCpgAnim(CpgType::peng, ClientSeatId::right);
            playerRight->startTimeClockAnim();
        }
        else if (seatId == ClientSeatId::opposite){
            hideBaiDaControllPad();
            playerOpposite->drawPlayerPeng(newData, getPlayerBySeatId(data->sId));
            playerOpposite->playerCpgAnim(CpgType::peng, ClientSeatId::opposite);
            playerOpposite->startTimeClockAnim();
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(othersPengListener, 1);
    
    othersGangListener = EventListenerCustom::create(MSG_OTHER_PLAYER_GANG, [=](EventCustom* event){
        PlayerCpgtData* data = static_cast<PlayerCpgtData*>(event->getUserData());
        PlayerCpgtData newData = *data;
        int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), newData.seatId);
        showGameTurn(GAMEDATA::getInstance()->getHeroSeatId(),newData.seatId);
        setPlayPokerSignPosition(false,Point(0,0));
        if (seatId == ClientSeatId::left){
            hideBaiDaControllPad();
            playerLeft->drawPlayerGang(newData, getPlayerBySeatId(data->sId));
            playerLeft->playerCpgAnim(CpgType::gang, ClientSeatId::left);
        }
        else if (seatId == ClientSeatId::right){
            hideBaiDaControllPad();
            playerRight->drawPlayerGang(newData, getPlayerBySeatId(data->sId));
            playerRight->playerCpgAnim(CpgType::gang, ClientSeatId::right);
        }
        else if (seatId == ClientSeatId::opposite){
            hideBaiDaControllPad();
            playerOpposite->drawPlayerGang(newData, getPlayerBySeatId(data->sId));
            playerOpposite->playerCpgAnim(CpgType::gang, ClientSeatId::opposite);
        }
        
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(othersGangListener, 1);
    
    
    heroPengRespListener = EventListenerCustom::create(MSG_HERO_PENG_RESP, [=](EventCustom* event){
        HeroCpgRespData* cpgRespData  = static_cast<HeroCpgRespData*>(event->getUserData());
        HeroCpgRespData newCpgRespData = *cpgRespData;
        int clientSeatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), newCpgRespData.playCpgt.sId);
        playerHero->hidePlayedBigJong();
        if(cpgRespData->result == 1||cpgRespData->result == 2){
            if (clientSeatId == ClientSeatId::right){
                playerHero->drawHeroPeng(newCpgRespData, playerRight);
            }
            else if (clientSeatId == ClientSeatId::opposite){
                playerHero->drawHeroPeng(newCpgRespData, playerOpposite);
            }
            else if (clientSeatId == ClientSeatId::left){
                playerHero->drawHeroPeng(newCpgRespData, playerLeft);
            }
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(heroPengRespListener, 1);
    
    turnListener = EventListenerCustom::create(MSG_CM_PLAYER_TURN_WHO, [=](EventCustom* event){
        //收到出牌通知,手里没牌
        if(playerHero->getSelfHandJongs().size() == 0){
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MSG_NETWORK_BREAK_INFO);
        }
        PlayerTurnData* turnData = static_cast<PlayerTurnData*>(event->getUserData());
        PlayerTurnData newData = *turnData;
        int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), newData.seatId);
        showGameTurn(GAMEDATA::getInstance()->getHeroSeatId(), newData.seatId);
        showPaiduiNum(atoi(newData.rest.c_str()));
        startCountdown();
        if (seatId == ClientSeatId::hero){
            turnHeroSelf = true;
//            playerHero->hidePlayedBigJong();
            playerHero->playerTurnToPlay(newData);
            playerHero->startTimeClockAnim();
        }
        else if (seatId == ClientSeatId::left){
            turnHeroSelf = false;
            playerLeft->drawLeftPlayerTurn();
            playerLeft->startTimeClockAnim();
        }
        else if (seatId == ClientSeatId::right){
            turnHeroSelf = false;
            playerRight->drawRightPlayerTurn();
            playerRight->startTimeClockAnim();
        }
        else if (seatId == ClientSeatId::opposite){
            turnHeroSelf = false;
            playerOpposite->drawOppositePlayerTurn();
            playerOpposite->startTimeClockAnim();
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(turnListener, 1);
    
    otherPlayerPlayedListener = EventListenerCustom::create(MSG_OTHER_PALYER_JONG, [=](EventCustom* event){
        
        std::string result = static_cast<char*>(event->getUserData());
        vector<string> res =  StringUtil::split(result, ",");
        int seat = atoi(res.at(0).c_str());
        int poker =atoi(res.at(1).c_str());
        int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), seat);
        
        if (seatId == ClientSeatId::left){
            playerLeft->setIsOffLine(false);
            playerLeft->stopTimeClockAnim();
            playerLeft->drawPlayedJong(poker);
        }
        else if (seatId == ClientSeatId::right){
            playerRight->setIsOffLine(false);
            playerRight->stopTimeClockAnim();
            playerRight->drawPlayedJong(poker);
        }
        else if (seatId == ClientSeatId::opposite){
            playerOpposite->setIsOffLine(false);
            playerOpposite->stopTimeClockAnim();
            playerOpposite->drawPlayedJong(poker);
        }else if(seatId == ClientSeatId::hero){
            schedule([=](float dt){
                playerHero->stopTimeClockAnim();
                playerHero->drawPlayedJong(poker);
            },0,0,0.6f,"delay_play_poker_auto");
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(otherPlayerPlayedListener, 1);
    
    playerCpgListener = EventListenerCustom::create(MSG_CM_PLAYER_CPG, [=](EventCustom* event){
        HeroCpgRespData* cpgData = static_cast<HeroCpgRespData*>(event->getUserData());
        HeroCpgRespData mewCpgData = *cpgData;
        showBaiDaControllPad(mewCpgData.playCpgt);
        playerHero->startTimeClockAnim(9, 1);
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(playerCpgListener, 1);
    
    
    playeHuActionListener = EventListenerCustom::create(MSG_CM_GAME_HU_ACTION, [=](EventCustom* event){
        PlayerCpgtData* data = static_cast<PlayerCpgtData*>(event->getUserData());
        PlayerCpgtData temp = *data;
        schedule([=](float dt){
            showBaiDaControllPad(temp);
        },0,0,1.2f,"showHuText");
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(playeHuActionListener, 1);
    
    gameResultListener = EventListenerCustom::create(MSG_GAME_RESULT, [=](EventCustom* event){
        string flag = static_cast<char*>(event->getUserData());
        if(flag == "1"||flag == "2"||flag == "3"){
            GAMEDATA::getInstance()->setIsTrusteeship(false);
            //播放动画
            //step检测胡牌类型
            int seatId1 = -1;
            std::vector<int> seatId2;
            int seatId3 =-1;
            seatId2.clear();
            bool zimoState = false;
            bool gangkaiState = false;
            bool qianggangState = false;
            bool isliuju = true;
            vector<GameResultData> results = GAMEDATA::getInstance()->getGameResults();
            for (GameResultData data: results) {
                if(data.result==1){
                    bool find = true;
                    vector<std::string> hu = StringUtil::split(data.huType, ",");
                    for(auto var:hu){
                        if(var == "3"){
                            seatId1 =SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), data.seatId);
                            gangkaiState = true;
                            find = false;
                        }
                    }
                    //自摸
                    if(find){
                        seatId1 =   SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), data.seatId);
                        zimoState=true;
                    }
                    isliuju = false;
                }else if(data.result==2){
                    //点炮
                    isliuju = false;
                    seatId1 = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), data.seatId);
                }else if(data.result==3){
                    //普通赢
                    isliuju = false;
                    vector<std::string> hu = StringUtil::split(data.huType, ",");
                    for(auto var:hu){
                        if(var == "12"){
                            qianggangState = true;
                            seatId3 =SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), data.seatId);
                            break;
                        }
                    }
                    seatId2.push_back(SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(),data.seatId));
                }
                if(data.seatId == GAMEDATA::getInstance()->getHeroSeatId()){
                    GAMEDATA::getInstance()->setCompetitionScore(StringUtils::format("%d",data.jifen));
                }
            }
            if(!isliuju){
                if(seatId1 == ClientSeatId::left){
                    playerLeft->playSoundHuPai();
                }else if(seatId1 == ClientSeatId::opposite){
                    playerOpposite->playSoundHuPai();
                }else if(seatId1 == ClientSeatId::right){
                    playerRight->playSoundHuPai();
                }else {
                    playerHero->playSoundHuPai();
                }
            }
            if(zimoState){
                HupaiAnim* hupai = HupaiAnim::create(MahjongHuType::zimoHu,atoi(GAMEDATA::getInstance()->getDiaopao().c_str()),seatId1,seatId2);
                addChild(hupai,999);
            }else if(gangkaiState){
                HupaiAnim* hupai = HupaiAnim::create(MahjongHuType::gangkaiHu,atoi(GAMEDATA::getInstance()->getDiaopao().c_str()),seatId1,seatId2);
                addChild(hupai,999);
            }else if(qianggangState){
                HupaiAnim* hupai = HupaiAnim::create(MahjongHuType::qianggangHu,atoi(GAMEDATA::getInstance()->getDiaopao().c_str()),seatId1,seatId2);
                addChild(hupai,999);
            }else  if(!isliuju){
                //判断胡牌的类型
                HupaiAnim* hupai = HupaiAnim::create(MahjongHuType::putongHu,atoi(GAMEDATA::getInstance()->getDiaopao().c_str()),seatId1,seatId2);
                addChild(hupai,999);
            }else{
                //流局动画
                LiuJuAnim* liuju = LiuJuAnim::create();
                addChild(liuju,3);
                GAMEDATA::getInstance()->setIsLiuJu(true);
            }
            schedule([=](float dt){
                PlayerCpgRecShow showRec;
                if(NULL!= playerLeft){
                    CpgPokerRec pokerRecL;
                    pokerRecL.clientseatid =  ClientSeatId::left;
                    for(auto left:playerLeft->playerCpgRecords){
                        std::vector<int> p;
                        for(auto pokers : left.pokersRecord){
                            p.push_back(pokers->getJongType());
                        }
                        pokerRecL.cpg.push_back(p);
                    }
                    showRec.playercpg.push_back(pokerRecL);
                    
                }
                CpgPokerRec pokerRecO;
                pokerRecO.clientseatid =  ClientSeatId::opposite;
                for(auto oppsite:playerOpposite->playerCpgRecords){
                    std::vector<int> p1;
                    for(auto pokers : oppsite.pokersRecord){
                        p1.push_back(pokers->getJongType());
                    }
                    pokerRecO.cpg.push_back(p1);
                }
                showRec.playercpg.push_back(pokerRecO);
                if(NULL!= playerRight){
                    CpgPokerRec pokerRecR;
                    pokerRecR.clientseatid =  ClientSeatId::right;
                    for(auto right:playerRight->playerCpgRecords){
                        std::vector<int> p2;
                        for(auto pokers : right.pokersRecord){
                            p2.push_back(pokers->getJongType());
                        }
                        pokerRecR.cpg.push_back(p2);
                    }
                    showRec.playercpg.push_back(pokerRecR);
                }
                CpgPokerRec pokerRecH;
                pokerRecH.clientseatid =  ClientSeatId::hero;
                for(auto hero:playerHero->playerCpgRecords){
                    std::vector<int> p3;
                    for(auto pokers : hero.pokersRecord){
                        p3.push_back(pokers->getJongType());
                    }
                    pokerRecH.cpg.push_back(p3);
                }
                showRec.playercpg.push_back(pokerRecH);
                
                GAMEDATA::getInstance()->setPlayerCpgRecShow(showRec);
                
                clearRoomPlayer();
                if(flag == "2"){
                    GAMEDATA::getInstance()->setResultFangzhuId(GAMEDATA::getInstance()->getFangZhuId());
                    GAMEDATA::getInstance()->setFangZhuId("");
                    GAMEDATA::getInstance()->setNeedShowLastResult(true);
                    GAMEDATA::getInstance()->setPrivateGameNum("0");
                    GAMEDATA::getInstance()->clearPlayersInfo();
                    if(GAMEDATA::getInstance()->getIsInGame()){
                        GAMEDATA::getInstance()->setIsPlaying(false);
                        Director::getInstance()->replaceScene(TransitionFade::create(1.0f,ResultScene::createScene(0)));
                    }
                }else if(flag == "3"){
                    GAMEDATA::getInstance()->setResultFangzhuId(GAMEDATA::getInstance()->getFangZhuId());
                    GAMEDATA::getInstance()->setFangZhuId("");
                    GAMEDATA::getInstance()->setNeedShowLastResult(true);
                    GAMEDATA::getInstance()->setPrivateGameNum("0");
                    GAMEDATA::getInstance()->clearPlayersInfo();
                    if(GAMEDATA::getInstance()->getIsInGame()){
                        GAMEDATA::getInstance()->setIsPlaying(false);
                        Director::getInstance()->replaceScene(TransitionFade::create(1.0f,ResultScene::createScene(3)));
                    }
                }
                else{
                    GAMEDATA::getInstance()->setNeedShowLastResult(false);
                    if(GAMEDATA::getInstance()->getIsInGame()){
                        GAMEDATA::getInstance()->setIsPlaying(false);
                        Director::getInstance()->replaceScene(TransitionFade::create(1.0f,ResultScene::createScene(0)));
                    }
                }
                
            },0,0,2,"go2Result");
        }else{
            schedule([=](float dt){
                clearRoomPlayer();
                GAMEDATA::getInstance()->setResultFangzhuId(GAMEDATA::getInstance()->getFangZhuId());
                GAMEDATA::getInstance()->setFangZhuId("");
                GAMEDATA::getInstance()->setPrivateGameNum("0");
                GAMEDATA::getInstance()->clearPlayersInfo();
                GAMEDATA::getInstance()->setIsPlaying(false);
                Director::getInstance()->replaceScene(TransitionFade::create(0.8f, LobbyScene::create()));
            }, 0, 0, 2,"CCKKFF");
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(gameResultListener, 1);
    
    trusteeshipNotifyListener  = EventListenerCustom::create(MSG_PLAYER_TRU_NOTIFY, [=](EventCustom* event){
        TruStateData* tru_seatid = static_cast<TruStateData*>(event->getUserData());
        TruStateData data = *tru_seatid;
        int clientId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), atoi(data.seatId.c_str()));
        if(clientId == ClientSeatId::left){
            playerLeft->setIsTrusteeship(data.flag == "1"?true:false);
        }else if(clientId == ClientSeatId::opposite){
            playerOpposite->setIsTrusteeship(data.flag == "1"?true:false);
        }else if(clientId == ClientSeatId::right){
            playerRight->setIsTrusteeship(data.flag == "1"?true:false);
        }else if(clientId == ClientSeatId::hero){
            hideBaiDaControllPad();
            bool result = (data.flag == "1"?true:false);
            GAMEDATA::getInstance()->setIsTrusteeship(result);
            playerHero->drawPlayerTrue(result);
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(trusteeshipNotifyListener, 1);
    
}

