#include "mahjong/gameview/baseview/BaseView.h"
#include "mahjong/gameview/anim/DealJongAnim.h"
#include "mahjong/gameview/anim/HupaiAnim.hpp"
#include "mahjong/gameview/anim/PlayerCpgAnim.hpp"
#include "mahjong/gameview/anim/LiuJuAnim.hpp"
#include "mahjong/gameview/anim/OutFogAnim.hpp"
#include "mahjong/gameview/widget/QuitRoomDialog.hpp"
#include "mahjong/gameview/widget/SoundRecordBtn.hpp"
#include "mahjong/common/chat/ChatDialog.hpp"
#include "mahjong/common/state/GameData.h"
#include "mahjong/common/utils/SeatIdUtil.h"
#include "mahjong/common/dialog/prompt/HintDialog.hpp"
#include "mahjong/common/dialog/network/LostNetwork.hpp"
#include "mahjong/common/dialog/prompt/TextHintDialog.hpp"
#include "mahjong/common/widget/ScrollTextEx.h"
#include "mahjong/common/widget/batteryInfo/BatteryInfo.h"
#include "mahjong/common/utils/StringUtil.h"
#include "mahjong/common/dialog/dissolve/DissovleRoomDialog.hpp"
#include "mahjong/common/utils/Chinese.h"
#include "mahjong/lobby/LobbyScene.h"
#include "mahjong/result/ResultScene.hpp"
#include "server/SocketDataManage.h"
#include "server/NetworkManage.h"
#include "mahjong/common/dialog/ip/IPConflict.hpp"


bool BaseView::init(){
    if (!Layer::init())
    {
        return false;
    }
    showViewLayer();//初始化界面
    initGameData();//初始化数据
    return true;
}

void BaseView::showViewLayer(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Sprite* view_bg = Sprite::create("gameview/game_bg.jpg");
    view_bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    addChild(view_bg, -1);
    
    //跑马灯
    if(UserData::getInstance()->isWeixinPayOpen()){
        ScrollTextEx* scroll = ScrollTextEx::create();
        scroll->setAutoScroll(true);
        scroll->setTag(9980);
        scroll->setPosition(600,600);
        addChild(scroll,2);
    }
    //Toast 消息
    myToast = InfoToast::create();
    addChild(myToast,50);
    
    //玩家出牌标记
    yellowSign = Sprite::create("gameview/arrows.png");
    addChild(yellowSign,50);
    bigJongBackground = Sprite::create("gameview/jong_show_bg_1.png");
    addChild(bigJongBackground, 50);
    bigJong = Jong::create();
    addChild(bigJong, 50);
    yellowSign->setVisible(false);
    bigJongBackground->setVisible(false);
    bigJong->setVisible(false);
    
    //时间,电量
    BatteryInfo* battery = BatteryInfo::create();
    battery->setPosition(0,0);
    addChild(battery,100);
    
    //显示玩家的方向和庄
    orientation = Orientation::create();
    orientation->showOrientation(GAMEDATA::getInstance()->getHeroSeatId());
    addChild(orientation);
    
    auto anwen = Sprite::create("gameview/game_name_hua_wen.png");
    anwen->setPosition(640,300);
    addChild(anwen);
    
    countdownTime = 10;
    countdown = LabelAtlas::create(StringUtils::format("%d",countdownTime),"gameview/time_num_mid.png",23,36,'0');
    countdown->setAnchorPoint(Point::ANCHOR_MIDDLE);
    countdown->setPosition(640,405);
    addChild(countdown);
    
    controllPad = Menu::create();
    controllPad->setAnchorPoint(Point(1, 0));
    controllPad->setPosition(Point(1100, 190));
    controllPad->setVisible(false);
    addChild(controllPad, 10);
    
    //房间号
    auto roomInfoBg = Sprite::create("gameview/top_bg.png");
    roomInfoBg->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    roomInfoBg->setPosition(640,720);
    addChild(roomInfoBg);
    
    auto roomId = Sprite::create("gameview/fang_hao.png");
    roomId->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(roomId);
    auto roomIdNum = LabelAtlas::create(GAMEDATA::getInstance()->getFriendOpenRoomResp().prid, "gameview/top_num.png", 12, 22, '0');
    roomIdNum->setTag(1088);
    roomIdNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(roomIdNum);
    
    auto jushu = Sprite::create("gameview/top_jushu.png");
    jushu->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(jushu);
    auto jushuNum = LabelAtlas::create("0;0", "gameview/top_num.png", 12, 22, '0');
    jushuNum->setTag(1089);
    jushuNum->setString(StringUtils::format("%s;%s",GAMEDATA::getInstance()->getFriendOpenRoomResp().prjucount.c_str(),GAMEDATA::getInstance()->getFriendOpenRoomResp().prjushu.c_str()));
    jushuNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(jushuNum);
    
    if(GAMEDATA::getInstance()->getGameType() == 1){
        //苏州麻将特有的内容
        roomId->setPosition(435,700);
        roomIdNum->setPosition(435+roomId->getContentSize().width,700);
        jushu->setPosition(575,700);
        jushuNum->setPosition(575+jushu->getContentSize().width,700);
        
        auto dilin = Sprite::create("gameview/diling_no.png");
        dilin->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        dilin->setTag(1090);
        dilin->setPosition(688,700);
        addChild(dilin);
        
        auto huang = Sprite::create("gameview/huangfan_no.png");
        huang->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        huang->setTag(1091);
        huang->setPosition(788,700);
        addChild(huang);
        
        auto split_1 = Sprite::create("gameview/top_split.png");
        split_1->setAnchorPoint(Point::ANCHOR_MIDDLE);
        split_1->setPosition(568,700);
        addChild(split_1);
        
        auto split_2 = Sprite::create("gameview/top_split.png");
        split_2->setAnchorPoint(Point::ANCHOR_MIDDLE);
        split_2->setPosition(677,700);
        addChild(split_2);
        
        auto split_3 = Sprite::create("gameview/top_split.png");
        split_3->setAnchorPoint(Point::ANCHOR_MIDDLE);
        split_3->setPosition(775,700);
        addChild(split_3);
    }else{
        roomId->setPosition(495,700);
        roomIdNum->setPosition(495+roomId->getContentSize().width,700);
        jushu->setPosition(685,700);
        jushuNum->setPosition(685+jushu->getContentSize().width,700);
        auto split_1 = Sprite::create("gameview/top_split.png");
        split_1->setAnchorPoint(Point::ANCHOR_MIDDLE);
        split_1->setPosition(640,700);
        addChild(split_1);
    }
    
    //剩余牌数
    auto shyu = Sprite::create("gameview/shen_yu_pai.png");
    shyu->setPosition(510,400);
    shyu->setTag(910);
    shyu->setVisible(false);
    addChild(shyu);
    auto alt = Label::createWithSystemFont(StringUtils::format("%d",0),"Arial",24);
    alt->setColor(Color3B(57,198,190));
    alt->setAnchorPoint(Point::ANCHOR_MIDDLE);
    alt->setPosition(530,370);
    alt->setTag(911);
    alt->setVisible(false);
    addChild(alt);
    
    //复盘界面不显示这些按钮
    if(GAMEDATA::getInstance()->getGameType() == 1 || GAMEDATA::getInstance()->getGameType() == 3
       ||GAMEDATA::getInstance()->getGameType() == 5||GAMEDATA::getInstance()->getGameType() == 7){
        //语音聊天
        SoundRecordBtn* soun = SoundRecordBtn::create();
        addChild(soun,5);
        auto settingButton = MenuItemImage::create("gameview/setting_btn_1.png", "gameview/setting_btn_2.png",
                                                   CC_CALLBACK_0(BaseView::settingButtonClick, this));
        Menu* setMenu = Menu::create(settingButton, NULL);
        setMenu->setPosition(1225,675);
        addChild(setMenu);
        
        auto chatButton = MenuItemImage::create("gameview/chat_btn_1.png", "gameview/chat_btn_2.png",
                                                CC_CALLBACK_0(BaseView::chatButtonClick, this));
        Menu* myMenu = Menu::create(chatButton, NULL);
        myMenu->setPosition(1225,600);
        myMenu->alignItemsVerticallyWithPadding(10);
        addChild(myMenu);
        
        auto quitBut = MenuItemImage::create("gameview/go_back_1.png", "gameview/go_back_2.png",
                                             CC_CALLBACK_0(BaseView::quitButtonClick, this));
        Menu* quit = Menu::create(quitBut, NULL);
        quit->setTag(1212);
        quit->setPosition(Point(55, 650));
        addChild(quit);
        if((atoi(GAMEDATA::getInstance()->getFriendOpenRoomResp().prjucount.c_str())>0&&GAMEDATA::getInstance()->getMahjongRoomType()== MahjongRoom::privateRoom)){
            quit->setVisible(false);
        }
        
        if (GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom){
            //解散牌局按钮
            if(atoi(GAMEDATA::getInstance()->getFriendOpenRoomResp().prjucount.c_str()) == 0 && UserData::getInstance()->getPoxiaoId()==GAMEDATA::getInstance()->getFangZhuId() && !GAMEDATA::getInstance()->getIsPlaying()){
                auto dissolveRoom = MenuItemImage::create("gameview/dissovle_room_btn_1.png","gameview/dissovle_room_btn_2.png",CC_CALLBACK_0(BaseView::dissovleRoom, this));
                auto disMenu = Menu::create(dissolveRoom,NULL);
                disMenu->setPosition(1140,85);
                disMenu->setTag(9999);
                addChild(disMenu);
            }
            
            if(!GAMEDATA::getInstance()->GAMEDATA::getInstance()->getIsRecover()||GAMEDATA::getInstance()->getLastGameDataBackup().result == 0){
                drawPlayerInvite();
            }
        }
    }
}


void BaseView::initGameData(){
    playerHero = NULL;
    playerLeft = NULL;
    playerRight = NULL;
    playerOpposite = NULL;
}

void BaseView::startCountdown(){
    unschedule(schedule_selector(BaseView::countDownUpdate));
    countdownTime = 10;
    countdown->setString(StringUtils::format("%d",countdownTime));
    schedule(schedule_selector(BaseView::countDownUpdate),1.0f, CC_REPEAT_FOREVER, 0.0f);
}

void BaseView::countDownUpdate(float dt){
    countdownTime--;
    if(countdownTime>=0){
        if(countdownTime == 4){
            Audio::getInstance()->playSoundDaoJiShi();
        }
        countdown->setString(StringUtils::format("%d",countdownTime));
    }
    
}

void BaseView::showPaiduiNum(int num){
    if(NULL != getChildByTag(910)){
        getChildByTag(910)->setVisible(true);
    }
    if(NULL != getChildByTag(911)){
        getChildByTag(911)->setVisible(true);
        ((Label*)getChildByTag(911)) ->setString(StringUtils::format("%d",num));
    }
}

void BaseView::showGameBank(int heroSeatId,int bankId){
    orientation->showWhoBank(heroSeatId,bankId);
    int clientBankId = SeatIdUtil::getClientSeatId(heroSeatId, bankId);
    if(clientBankId == ClientSeatId::left){
        if(NULL != playerLeft)
            playerLeft->showPlayerZhuang(true);
        if(NULL != playerRight)
            playerRight->showPlayerZhuang(false);
        if(NULL != playerOpposite)
            playerOpposite->showPlayerZhuang(false);
        if(NULL != playerHero)
            playerHero->showPlayerZhuang(false);
    }else  if(clientBankId == ClientSeatId::right){
        if(NULL != playerLeft)
            playerLeft->showPlayerZhuang(false);
        if(NULL != playerRight)
            playerRight->showPlayerZhuang(true);
        if(NULL != playerOpposite)
            playerOpposite->showPlayerZhuang(false);
        if(NULL != playerHero)
            playerHero->showPlayerZhuang(false);
    }else  if(clientBankId == ClientSeatId::opposite){
        if(NULL != playerLeft)
            playerLeft->showPlayerZhuang(false);
        if(NULL != playerRight)
            playerRight->showPlayerZhuang(false);
        if(NULL != playerOpposite)
            playerOpposite->showPlayerZhuang(true);
        if(NULL != playerHero)
            playerHero->showPlayerZhuang(false);
    }else  if(clientBankId == ClientSeatId::hero){
        if(NULL != playerLeft)
            playerLeft->showPlayerZhuang(false);
        if(NULL != playerRight)
            playerRight->showPlayerZhuang(false);
        if(NULL != playerOpposite)
            playerOpposite->showPlayerZhuang(false);
        if(NULL != playerHero)
            playerHero->showPlayerZhuang(true);
    }
}

void BaseView::showGameTurn(int heroSeatId, int setaId){
    orientation->showPlayerTurn(heroSeatId,setaId);
}

void BaseView::settingButtonClick(){
    Audio::getInstance()->playSoundClick();
    UserSetting* setting = UserSetting::create();
    addChild(setting,350);
}

void BaseView::chatButtonClick(){
    auto gameChat = ChatDialog::create();
    addChild(gameChat,350);
//    gameTest();
}

void BaseView::quitButtonClick(){
    Audio::getInstance()->playSoundClick();
    if(!GAMEDATA::getInstance()->getIsPlaying()){
        if(atoi(GAMEDATA::getInstance()->getFriendOpenRoomResp().prjucount.c_str())==0 && UserData::getInstance()->getPoxiaoId()==GAMEDATA::getInstance()->getFangZhuId() && !GAMEDATA::getInstance()->getIsPlaying()){
            HintDialog* dia = HintDialog::create(ChineseWord("dialog_text_1"), [=](Ref* ref){
                GAMEDATA::getInstance()->clearPlayersInfo();
                GAMEDATA::getInstance()->setIsPlaying(false);
                if(GAMEDATA::getInstance()->getGameType() == 1){
                    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getQuitRoomCommand());
                }else if (GAMEDATA::getInstance()->getGameType() == 3){
                    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getHZQuitRoomCommand());
                }else if (GAMEDATA::getInstance()->getGameType() == 5){
                    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getBDQuitRoomCommand());
                }else if (GAMEDATA::getInstance()->getGameType() == 7){
                    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getFPQuitRoomCommand());
                }
                Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
            });
            addChild(dia,350);
        }else if(GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom){
            HintDialog* dia = HintDialog::create(ChineseWord("dialog_text_2"), [=](Ref* ref){
                GAMEDATA::getInstance()->clearPlayersInfo();
                if(GAMEDATA::getInstance()->getGameType() == 1){
                    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getQuitRoomCommand());
                }else if (GAMEDATA::getInstance()->getGameType() == 3){
                    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getHZQuitRoomCommand());
                }else if (GAMEDATA::getInstance()->getGameType() == 5){
                    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getBDQuitRoomCommand());
                }else if (GAMEDATA::getInstance()->getGameType() == 7){
                    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getFPQuitRoomCommand());
                }
                Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
            });
            addChild(dia,350);
        }else{
            GAMEDATA::getInstance()->clearPlayersInfo();
            if(GAMEDATA::getInstance()->getGameType() == 1){
                NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getQuitRoomCommand());
            }else if (GAMEDATA::getInstance()->getGameType() == 3){
                NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getHZQuitRoomCommand());
            }else if (GAMEDATA::getInstance()->getGameType() == 5){
                NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getBDQuitRoomCommand());
            }else if (GAMEDATA::getInstance()->getGameType() == 7){
                NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getFPQuitRoomCommand());
            }
            Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
            
        }
    }else{
        QuitRoomDialog* dialog = QuitRoomDialog::create();
        addChild(dialog,350);
    }
}

void BaseView::showInvitePlayer(int clientId){
    if (clientId == ClientSeatId::left){
        if(NULL != leftPlayerInvite)
            leftPlayerInvite->setVisible(true);
    }
    else if (clientId == ClientSeatId::right){
        if(NULL != rightPlayerInvite)
            rightPlayerInvite->setVisible(true);
    }
    else if (clientId == ClientSeatId::opposite){
        if(NULL != oppositePlayerInvite)
            oppositePlayerInvite->setVisible(true);
    }
}

void BaseView::hideInvitePlayer(int clientId){
    if (clientId == ClientSeatId::left){
        if(NULL != leftPlayerInvite)
            leftPlayerInvite->setVisible(false);
    }
    else if (clientId == ClientSeatId::right){
        if(NULL != rightPlayerInvite)
            rightPlayerInvite->setVisible(false);
    }
    else if (clientId == ClientSeatId::opposite){
        if(NULL != oppositePlayerInvite)
            oppositePlayerInvite->setVisible(false);
    }
}

void BaseView::updateRoomInfo(){
    if(NULL != getChildByTag(1088)){
        ((LabelAtlas*)getChildByTag(1088))->setString(GAMEDATA::getInstance()->getFriendOpenRoomResp().prid);
    }
    if(NULL != getChildByTag(1089)){
        FriendOpenRoomRespData data = GAMEDATA::getInstance()->getFriendOpenRoomResp();
        ((LabelAtlas*)getChildByTag(1089)) ->setString(StringUtils::format("%s;%s",data.prjucount.c_str(),data.prjushu.c_str()));
    }
    if(NULL != getChildByTag(1090)){
        if(GAMEDATA::getInstance()->getPrivateDLNum() == "1")
            ((Sprite*)getChildByTag(1090))->setTexture("gameview/diling_yes.png");
        else
            ((Sprite*)getChildByTag(1090))->setTexture("gameview/diling_no.png");
    }
    if(NULL != getChildByTag(1091)){
        log("");
        if(GAMEDATA::getInstance()->getPrivateHFNum() == "1")
            ((Sprite*)getChildByTag(1091))->setTexture("gameview/huangfan_yes.png");
        else
            ((Sprite*)getChildByTag(1091))->setTexture("gameview/huangfan_no.png");
    }
}

void BaseView::hideDissovleBtn(){
    if(NULL != getChildByTag(9999)){
        getChildByTag(9999)->setVisible(false);
    }
}

void BaseView::dissovleRoom(){
    HintDialog* dia = HintDialog::create(ChineseWord("dialog_text_3"), [=](Ref* ref){
        GAMEDATA::getInstance()->clearPlayersInfo();
        if(GAMEDATA::getInstance()->getGameType() == 3){
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getHZDissolveRoomCommand(""));
        }else if(GAMEDATA::getInstance()->getGameType() == 5){
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getBDDissovleRoomReq(""));
        }else if(GAMEDATA::getInstance()->getGameType() == 7){
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getFPDissovleRoomReq(""));
        }else{
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getDissolveRoomCommand(""));
        }
    });
    getParent()->addChild(dia,350);
}

void BaseView::drawPlayerInvite(){
    MenuItemImage* left = MenuItemImage::create("headportrait/userbk.png", "headportrait/userbk.png",
                                                CC_CALLBACK_1(BaseView::invitePlayer, this));
    left->setTag(ClientSeatId::left);
    leftPlayerInvite = Menu::create(left, NULL);
    leftPlayerInvite->setPosition(Point(70, 375));
    addChild(leftPlayerInvite);
    
    MenuItemImage* right = MenuItemImage::create("headportrait/userbk.png", "headportrait/userbk.png",
                                                 CC_CALLBACK_1(BaseView::invitePlayer, this));
    right->setTag(ClientSeatId::right);
    rightPlayerInvite = Menu::create(right, NULL);
    rightPlayerInvite->setPosition(Point(1213, 375));
    addChild(rightPlayerInvite);
    
    MenuItemImage* opp = MenuItemImage::create("headportrait/userbk.png", "headportrait/userbk.png",
                                               CC_CALLBACK_1(BaseView::invitePlayer, this));
    opp->setTag(ClientSeatId::opposite);
    oppositePlayerInvite = Menu::create(opp, NULL);
    oppositePlayerInvite->setPosition(Point(985, 642));
    addChild(oppositePlayerInvite);
    
    //二人模式
    if(GAMEDATA::getInstance()->getMyGameModel() == GameModel::TWOPLAYER){
        leftPlayerInvite->setVisible(false);
        rightPlayerInvite->setVisible(false);
    }
}

void BaseView::invitePlayer(Ref* ref){
    //TODO
}

PlayerBase* BaseView::getPlayerBySeatId(int sid){
    int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), sid);
    if (seatId == ClientSeatId::left){
        return playerLeft;
    }
    else if (seatId == ClientSeatId::right){
        return playerRight;
    }
    else if (seatId == ClientSeatId::opposite){
        return playerOpposite;
    }
    else{
        return playerHero;
    }
}

void BaseView::setPlayPokerSignPosition(bool show,Point pos){
    yellowSign->setVisible(show);
    yellowSign->setPosition(pos);
}

void BaseView::setBigJongPosition(int poker,ClientSeatId seatId){
    if(poker >= JongEnum::zhong&&(GAMEDATA::getInstance()->getGameType() == 1||GAMEDATA::getInstance()->getGameType()==2||(GAMEDATA::getInstance()->getGameType()==5 && poker != JongEnum::baida)||(GAMEDATA::getInstance()->getGameType()==6 && poker != JongEnum::baida))){
        
    }else{
        bigJongBackground->setVisible(true);
        bigJong->setVisible(true);
        Point postion = getBigJongPos(seatId);
        bigJongBackground->setPosition(postion);
        bigJong->showJong(playedshow,poker);
        bigJongBackground->setPosition(postion);
        bigJong->setPosition(postion.x,postion.y+15);
    }
}

void BaseView::setBigJongEnable(){
    bigJongBackground->setVisible(false);
    bigJong->setVisible(false);
}

Point BaseView::getBigJongPos(int type){
    
    if (type == ClientSeatId::left){
        return Vec2(300,400);
    }
    else if (type == ClientSeatId::opposite){
        return Vec2(640, 550);
    }
    else if (type == ClientSeatId::right){
        return Vec2(980, 400);
    }
    else{
        log("BaseView getBigJongPos 传入参数有误");
        return Vec2(0, 0);
    }
}

void BaseView::addPlayerToRoom(){
    vector<PlayerInfo*> players = GAMEDATA::getInstance()->getPlayersInfo();
    for (int i = 0; i < players.size(); i++){
        updatePlayerView(SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(),players.at(i)->getSeatId()),players.at(i));
    }
}

void BaseView::updatePlayerView(int type , PlayerInfo* playerInfo){
    if (GAMEDATA::getInstance()->getMahjongRoomType()==MahjongRoom::privateRoom){
        hideInvitePlayer(type);
    }
    if (type == ClientSeatId::hero){
        if (playerHero == NULL){
            playerHero = PlayerHero::create();
            playerHero->initPlayer(playerInfo);
            playerHero->drawReady(playerInfo->getIsReady());
            playerHero->showInviteButton();
            if(GAMEDATA::getInstance()->getContinueAgain()){
                playerHero->setIsReady(false);
            }else{
                playerHero->setIsReady(playerInfo->getIsReady());
            }
            playerHero->setIsAllowPlay(false);
            addChild(playerHero, 2);
        }
    }
    else if (type == ClientSeatId::left){
        if (playerLeft == NULL){
            playerLeft = PlayerLeft::create();
            playerLeft->initPlayer(playerInfo);
            if(GAMEDATA::getInstance()->getContinueAgain()){
                playerLeft->setIsReady(false);
            }else{
                playerLeft->setIsReady(playerInfo->getIsReady());
            }
            addChild(playerLeft,1);
        }
    }
    else if (type == ClientSeatId::right){
        if (playerRight == NULL){
            playerRight = PlayerRight::create();
            playerRight->initPlayer(playerInfo);
            if(GAMEDATA::getInstance()->getContinueAgain()){
                playerRight->setIsReady(false);
            }else{
                playerRight->setIsReady(playerInfo->getIsReady());
            }
            addChild(playerRight,1);
        }
    }
    else if (type == ClientSeatId::opposite){
        if (playerOpposite == NULL){
            playerOpposite = PlayerOpposite::create();
            playerOpposite->initPlayer(playerInfo);
            if(GAMEDATA::getInstance()->getContinueAgain()){
                playerOpposite->setIsReady(false);
            }else{
                playerOpposite->setIsReady(playerInfo->getIsReady());
            }
            addChild(playerOpposite,1);
        }
    }
}

void BaseView::dealJongFinish(MahjongFaPaiData data){
    showMahjongDiec(data.dice);
}

void BaseView::showMahjongDiec(std::string dian){
    vector<string> dice =StringUtil::split(dian, ",") ;
    int dian1 = atoi(dice.at(0).c_str());
    int dian2 = atoi(dice.at(1).c_str());
    auto diec1 = Sprite::create(StringUtils::format("gameview/dice_%d.png",dian1));
    diec1->setPosition(490,416);
    diec1->setScale(0.3f);
    addChild(diec1);
    auto diec2 = Sprite::create(StringUtils::format("gameview/dice_%d.png",dian2));
    diec2->setPosition(525,406);
    diec2->setScale(0.3f);
    addChild(diec2);
}

void BaseView::clearRoomPlayer(){
    if(NULL != playerHero){
        playerHero->removeFromParent();
        playerHero = NULL;
    }
    if (NULL != playerLeft){
        playerLeft->removeFromParent();
        playerLeft = NULL;
    }
    if (NULL != playerRight){
        playerRight->removeFromParent();
        playerRight = NULL;
    }
    if (NULL != playerOpposite){
        playerOpposite->removeFromParent();
        playerOpposite = NULL;
    }
}

void BaseView::update(float dt){
    if(getChildByTag(1212)!=NULL){
        if(GAMEDATA::getInstance()->getIsPlaying()&&GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom){
            if(getChildByTag(1212)->isVisible())
                getChildByTag(1212)->setVisible(false);
        }
    }
}

void BaseView::onEnterTransitionDidFinish(){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getScrollTextCommand());//获取跑马灯
}

void BaseView::onEnter(){
    Layer::onEnter();
    
    //登录地址变更
    playerReplaceLoginListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_PLAYER_REPLACE_LOGIN, [=](EventCustom* event){
        HintDialog* hin = HintDialog::create(ChineseWord("dialog_text_5"),[=](Ref* ref){
            exit(0);
        });
        addChild(hin,5);
    });
    
    networkBreakListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_NETWORK_BREAK_INFO, [=](EventCustom* event){
        if(NULL == getChildByTag(2000)){
            LostNetwork* net = LostNetwork::create();
            net->setTag(2000);
            addChild(net,200);
        }
        if(NetworkManage::getInstance()->connect()){
            if(UserData::getInstance()->getWxOpenId() ==  "unknow"){
                NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getVistorLoginAgain(UserData::getInstance()->getUserName(), UserData::getInstance()->getPassword()));
            }else{
                NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getThirdLoginCommand(UserData::getInstance()->getWxOpenId(), UserData::getInstance()->getWxUnionid(),UserData::getInstance()->getPicture(), StringUtils::format("%d",UserData::getInstance()->getGender()), UserData::getInstance()->getNickName(), UserData::getInstance()->getHsman(), UserData::getInstance()->getHstype(), UserData::getInstance()->getImsi(),UserData::getInstance()->getImei(),UserData::getInstance()->getAppVer(),UserData::getInstance()->getLongitude(),UserData::getInstance()->getLatitude(),true));
            }
            NetworkManage::getInstance()->startSocketBeat(CommandManage::getInstance()->getHeartCommmand());
        }
    });
    
    scrollTetxListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_SCROLL_TEXT, [=](EventCustom* event){
        std::string msg = static_cast<char*>(event->getUserData());
        std::vector<std::string> showMsg = StringUtil::split(msg, "#$");
        if(nullptr != ((ScrollTextEx*)getChildByTag(9980))){
            ((ScrollTextEx*)getChildByTag(9980))->setScrollStrs(showMsg);
        }
        schedule([=](float dt){
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getScrollTextCommand());
        }, 0, 0, 300,"ask_tui_guang");
    });
    
    dissovelRoomSelectNotifyListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_DISSOVLE_ROOM_SELECTED_NOTIFY_NEW, [=](EventCustom* event){
        DissovleRoomDialog* dialog = DissovleRoomDialog::create();
        addChild(dialog,200);
    });
    
    playerRemoveListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_PLAYER_REMOVE, [=](EventCustom* event){
        if(!GAMEDATA::getInstance()->getIsPlaying()){
            if(playerLeft !=NULL&&playerLeft->getPlayerInfo()->getPoxiaoId()==GAMEDATA::getInstance()->getRemovePlayer().pid){
                playerLeft->removeFromParent();
                playerLeft =NULL;
                OutFogAnim* out1 = OutFogAnim::create(Point(70, 455));
                addChild(out1);
            }else if(playerRight !=NULL&&playerRight->getPlayerInfo()->getPoxiaoId()==GAMEDATA::getInstance()->getRemovePlayer().pid){
                playerRight->removeFromParent();
                playerRight =NULL;
                OutFogAnim* out2 = OutFogAnim::create(Point(1213, 455));
                addChild(out2);
            }else if(playerOpposite !=NULL&&playerOpposite->getPlayerInfo()->getPoxiaoId()==GAMEDATA::getInstance()->getRemovePlayer().pid){
                playerOpposite->removeFromParent();
                playerOpposite =NULL;
                OutFogAnim* out3 = OutFogAnim::create(Point(945, 642));
                addChild(out3);
            }else if(GAMEDATA::getInstance()->getRemovePlayer().pid == UserData::getInstance()->getPoxiaoId()){
                //房主自己解散,回到大厅
                Director::getInstance()->replaceScene(LobbyScene::create());
            }
            if(GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom){
                showInvitePlayer(SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), GAMEDATA::getInstance()->getRemovePlayer().setaId));
            }
        }
    });
    
    addOtherReadyListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_READY_NOTIFY, [=](EventCustom* event){
        char* buf = static_cast<char*>(event->getUserData());
        int currentReadyPlayer = atoi(buf);
        int type = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), currentReadyPlayer);
        if (type == ClientSeatId::left){
            if(NULL != playerLeft){
                playerLeft->setIsReady(true);
            }
        }
        else if (type == ClientSeatId::right){
            if(NULL != playerRight){
                playerRight->setIsReady(true);
            }
        }
        else if (type == ClientSeatId::opposite){
            if(NULL != playerOpposite){
                playerOpposite->setIsReady(true);
            }
        }
    });
    
    addPlayersListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_PALYER_ENTER_GAME, [=](EventCustom* event){
        addPlayerToRoom();
    });
    
    
    goLobbyRespListener = EventListenerCustom::create(MSG_LOGIN_RESP, [=](EventCustom* event){
        Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(goLobbyRespListener, 1);
    
    
    fangZhuLeaveListener = EventListenerCustom::create(MSG_GAME_FANG_ZHU_LEAVE, [=](EventCustom* event){
        std::string msg = static_cast<char*>(event->getUserData());
        vector<PlayerInfo*> players = GAMEDATA::getInstance()->getPlayersInfo();
        for (auto var: players) {
            if(var->getSeatId() == atoi(msg.c_str())){
                var->setIsReady(false);
            }
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(fangZhuLeaveListener, 1);
    
    playerOffLineListener = EventListenerCustom::create(MSG_PLAYER_OFF_LINE_NOTIFY, [=](EventCustom* event){
        string buf = static_cast<char*>(event->getUserData());
        vector<PlayerInfo*> players = GAMEDATA::getInstance()->getPlayersInfo();
        for (int i = 0; i < players.size(); i++){
            if(players.at(i)->getSeatId() ==  atoi(buf.c_str())){
                int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(),players.at(i)->getSeatId());
                if(seatId == ClientSeatId::left){
                    playerLeft->setIsOffLine(true);
                }else if(seatId == ClientSeatId::opposite){
                    playerOpposite->setIsOffLine(true);
                }else if(seatId == ClientSeatId::right){
                    playerRight->setIsOffLine(true);
                }
            }
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(playerOffLineListener, 1);
    
    ipConflictListener = EventListenerCustom::create(MSG_IP_CONFLICT, [=](EventCustom* event){
        if(NULL == getChildByTag(1116)){
            IPConflict* con = IPConflict::create();
            con->setTag(1116);
            addChild(con,100);
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(ipConflictListener, 1);
}


void BaseView::gameTest(){
    vector<GameResultData> gameResults;
    for (int i = 0; i < 4; i++){
        GameResultData resultData;
        if(i == 0){
            resultData.result = 3;
        }else if(i==1){
            resultData.result = 3;
        }
        else if(i==2){
            resultData.result = 2;
        }else{
            resultData.result = 0;
        }
        resultData.zimocount = "10";
        resultData.jiepaocount = "10";
        resultData.dianpaocount = "10";
        resultData.angangcount = "10";
        resultData.minggangcount = "10";
        resultData.gold = 100;
        resultData.diamond = 100;
        resultData.jifen = -10;
        resultData.lequan = 10;
        resultData.golddelta = 200000;
        resultData.diamonddelta =2;
        resultData.jifendelta = 4000000;
        resultData.lequandelta = 222220;
        resultData.seatId = i+1;
        resultData.umark ="100010000";
        resultData.hua = 3;
        resultData.lz = "2";
        resultData.fan = "10";
        resultData.showPoker = "1,2,3,4,5,6,7,8";
        if(i==0){
            resultData.huType = "2,13";
        }else if(i==1){
            resultData.huType = "20,13";
        }
        resultData.gangfen = 10;
        resultData.nickName = StringUtils::format("这里是装电视台%d",i+1);
        gameResults.push_back(resultData);
    }
    GAMEDATA::getInstance()->setDiaopao("8");
    GAMEDATA::getInstance()->setGameResults(gameResults);
    GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
    GAMEDATA::getInstance()->setHeroSeatId(1);
    GAMEDATA::getInstance()->setCurrentBank(1);
    GAMEDATA::getInstance()->setFanMa("1,2");
    GAMEDATA::getInstance()->setFanMaType("1");
    GAMEDATA::getInstance()->setHZDiFen("10");
    GAMEDATA::getInstance()->setHZMaShu("4");
    FriendOpenRoomRespData opendata;
    opendata.prjushu ="8";
    opendata.prjucount ="2";
    GAMEDATA::getInstance()->setFriendOpenRoomResp(opendata);
    char* buf = const_cast<char*>("2");
    _eventDispatcher->dispatchCustomEvent(MSG_GAME_RESULT,buf);
    
}

void BaseView::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(networkBreakListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(scrollTetxListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(playerRemoveListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(dissovelRoomSelectNotifyListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(addPlayersListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(addOtherReadyListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(playerReplaceLoginListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(goLobbyRespListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(fangZhuLeaveListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(playerOffLineListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(ipConflictListener);
    
    
}
