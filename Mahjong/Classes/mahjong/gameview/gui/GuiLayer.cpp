#include "mahjong/gameview/gui/GuiLayer.h"
#include "mahjong/gameview/widget/QuitRoomDialog.hpp"
#include "mahjong/common/state/GameData.h"
#include "mahjong/common/bill/BillInfo.h"
#include "mahjong/common/dialog/prompt/HintDialog.hpp"
#include "mahjong/common/chat/ChatDialog.hpp"
#include "mahjong/common/audio/Audio.h"
#include "mahjong/common/utils/SeatIdUtil.h"
#include "mahjong/lobby/LobbyScene.h"
#include "mahjong/GameConfig.h"
#include "server/MsgHandler.h"
#include "server/NetworkManage.h"
#include "userdata/UserData.h"
#include "wechat/ios/CallIOSMethod.h"
#include "wechat/android/CallAndroidMethod.h"
#include "mahjong/common/utils/Chinese.h"
#include "wechat/android/CallAndroidMethod.h"
#include "wechat/ios/CallIOSMethod.h"
#include "mahjong/result/hongbao/HongbaoAnim2.hpp"
#include "mahjong/result/hongbao/HongbaoAnim.hpp"
#include "mahjong/common/competition/CompetitionResult.hpp"

bool GuiLayer::init(){
    if (!Layer::init()){
        return false;
    }
    initView();
    return true;
}

void GuiLayer::initView(){
    if(GAMEDATA::getInstance()->getGameType() == 1 || GAMEDATA::getInstance()->getGameType() == 3){
        drawGuiButton();//设置,账单,聊天，解散房间，退出
    }
    drawGameInfo(); //开宝，荒番，房间号的绘制
//    drawTestButton();
    scheduleUpdate();
}


void GuiLayer::drawGuiButton(){
    auto chatButton = MenuItemImage::create("gameview/chat_btn_1.png", "gameview/chat_btn_2.png",
                                            CC_CALLBACK_0(GuiLayer::chatButtonClick, this));
    if(GAMEDATA::getInstance()->getIsCompetitionState()||GAMEDATA::getInstance()->getIsCompetitionQueue()){
        chatButton->setVisible(false);
    }
    auto settingButton = MenuItemImage::create("gameview/setting_btn_1.png", "gameview/setting_btn_2.png",
                                               CC_CALLBACK_0(GuiLayer::settingButtonClick, this));
    Menu* myMenu = Menu::create(chatButton, settingButton, NULL);
    myMenu->setPosition(1225,285);
    myMenu->alignItemsVerticallyWithPadding(10);
    this->addChild(myMenu);
    
    auto quitBut = MenuItemImage::create("gameview/go_back_1.png", "gameview/go_back_2.png",
                                         CC_CALLBACK_0(GuiLayer::quitButtonClick, this));
    Menu* quit = Menu::create(quitBut, NULL);
    quit->setTag(1212);
    quit->setPosition(Point(55, 650));
    this->addChild(quit);
    if(GAMEDATA::getInstance()->getIsCompetitionState()||(atoi(GAMEDATA::getInstance()->getFriendOpenRoomResp().prjucount.c_str())>0&&GAMEDATA::getInstance()->getMahjongRoomType()== MahjongRoom::privateRoom)){
        quit->setVisible(false);
    }
    
    if (GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom){
        //解散牌局按钮
        if(atoi(GAMEDATA::getInstance()->getFriendOpenRoomResp().prjucount.c_str()) == 0 && UserData::getInstance()->getPoxiaoId()==GAMEDATA::getInstance()->getFangZhuId() && !GAMEDATA::getInstance()->getIsPlaying()){
            auto dissolveRoom = MenuItemImage::create("gameview/dissovle_room_btn_1.png","gameview/dissovle_room_btn_2.png",CC_CALLBACK_0(GuiLayer::dissovleRoom, this));
            auto disMenu = Menu::create(dissolveRoom,NULL);
            disMenu->setPosition(1140,85);
            disMenu->setTag(9999);
            addChild(disMenu);
        }
        
        if(!GAMEDATA::getInstance()->GAMEDATA::getInstance()->getIsRecover()||GAMEDATA::getInstance()->getLastGameDataBackup().result == 0){
            if(GAMEDATA::getInstance()->getGameType() == 1 || GAMEDATA::getInstance()->getGameType() == 3)
                drawPlayerInvite();
        }
        auto bill = MenuItemImage::create("gameview/bill_btn_1.png", "gameview/bill_btn_2.png",
                                          CC_CALLBACK_0(GuiLayer::showPlayerBill, this));
        if(GAMEDATA::getInstance()->getIsCompetitionState()||GAMEDATA::getInstance()->getIsCompetitionQueue()){
            bill->setVisible(false);
        }
        Menu* billMenu = Menu::create(bill, NULL);
        billMenu->setPosition(Point(1225, 165));
        addChild(billMenu);
        
    }
}


void GuiLayer::drawGameInfo(){
    auto roomInfoBg = Sprite::create("gameview/room_id_bg.png");
    roomInfoBg->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);
    roomInfoBg->setPosition(1275,710);
    addChild(roomInfoBg);
    if(GAMEDATA::getInstance()->getIsCompetitionQueue()||GAMEDATA::getInstance()->getIsCompetitionState()){
        roomInfoBg->setScaleY(0.6);
        auto name = Label::createWithSystemFont("", "arial", 25);
        if(GAMEDATA::getInstance()->getCompetitionId() == StringUtils::format("%d",CompetitionRoomId::Shanghai_High)||GAMEDATA::getInstance()->getCompetitionId() == StringUtils::format("%d",CompetitionRoomId::Shanghai_Normal)){
            name->setString("上海敲麻");
        }else{
            name->setString("红中麻将");
        }
        name->setPosition(1200,685);
        name->setColor(Color3B(233,209,112));
        addChild(name);
        
        auto matchname = Label::createWithSystemFont(StringUtils::format("%s元话费赛",GAMEDATA::getInstance()->getCompetitionPride().c_str()), "arial", 25);
        matchname->setPosition(1200,655);
        matchname->setColor(Color3B(233,209,112));
        addChild(matchname);
        
        if(!UserData::getInstance()->isWeixinPayOpen()){
            if(GAMEDATA::getInstance()->getCompetitionPride() == "36"){
                matchname->setString("8张房卡赛");
            }else{
                matchname->setString("2张房卡赛");
            }
        }
    }else{
        if(GAMEDATA::getInstance()->getGameType() == 1 || GAMEDATA::getInstance()->getGameType() == 2){
            auto kaibao = Sprite::create("gameview/kai_bao.png");
            addChild(kaibao);
            
            kaibaoNum = Label::createWithSystemFont("X "+GAMEDATA::getInstance()->getKaibao(),"Arial",25);
            kaibaoNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
            kaibaoNum->setColor(Color3B(233,209,112));
            addChild(kaibaoNum);
            
            auto huangfan = Sprite::create("gameview/huang_fan.png");
            addChild(huangfan);
            
            haungNum = Label::createWithSystemFont("X "+GAMEDATA::getInstance()->getHuangfan(), "Arial",25);
            haungNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
            haungNum->setColor(Color3B(233,209,112));
            addChild(haungNum);
            
            if(GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom){
                kaibao->setPosition(1160,640);
                kaibaoNum->setPosition(1200,638);
                huangfan->setPosition(1160, 610);
                haungNum->setPosition(1200, 608);
            }else{
                kaibao->setPosition(1170,680);
                kaibaoNum->setPosition(1210,678);
                huangfan->setPosition(1170, 650);
                haungNum->setPosition(1210, 648);
            }
        }
        
        if (GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom){
            //私人房间
            auto roomId = Sprite::create("gameview/fang_hao.png");
            addChild(roomId);
            auto roomIdNum = Label::createWithSystemFont(GAMEDATA::getInstance()->getFriendOpenRoomResp().prid,"Arial",25);
            roomIdNum->setTag(1088);
            roomIdNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
            roomIdNum->setColor(Color3B(233,209,112));
            addChild(roomIdNum);
            roomId->setPosition(1160,680);
            roomIdNum->setPosition(1185,678);
            if(GAMEDATA::getInstance()->getGameType() == 3 || GAMEDATA::getInstance()->getGameType() == 4){
                roomInfoBg->setScale(1.0f, 0.4f);
            }
        }else{
            roomInfoBg->setScale(0.95, 0.68);
        }
    }
}





void GuiLayer::chatButtonClick(){
    auto gameChat = ChatDialog::create();
    getParent()->addChild(gameChat,50);
}

void GuiLayer::settingButtonClick(){
    Audio::getInstance()->playSoundClick();
    UserSetting* setting = UserSetting::create();
    getParent()->addChild(setting,50);
}

void GuiLayer::quitButtonClick(){
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
                }
                Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
            });
            getParent()->addChild(dia,50);
        }else if(GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom){
            HintDialog* dia = HintDialog::create(ChineseWord("dialog_text_2"), [=](Ref* ref){
                GAMEDATA::getInstance()->clearPlayersInfo();
                if(GAMEDATA::getInstance()->getGameType() == 1){
                    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getQuitRoomCommand());
                }else if (GAMEDATA::getInstance()->getGameType() == 3){
                    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getHZQuitRoomCommand());
                }
                Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
            });
            getParent()->addChild(dia,50);
        }else{
            GAMEDATA::getInstance()->clearPlayersInfo();
            if(GAMEDATA::getInstance()->getGameType() == 1){
                NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getQuitRoomCommand());
            }else if (GAMEDATA::getInstance()->getGameType() == 3){
                NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getHZQuitRoomCommand());
            }
            Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
            
        }
    }else{
        QuitRoomDialog* dialog = QuitRoomDialog::create();
        getParent()->addChild(dialog,50);
    }
}


void GuiLayer::updateData(){
    if(!GAMEDATA::getInstance()->getIsCompetitionQueue()&&!GAMEDATA::getInstance()->getIsCompetitionState()){
        if(GAMEDATA::getInstance()->getGameType() != 3 && GAMEDATA::getInstance()->getGameType() != 4){
            kaibaoNum->setString("X "+GAMEDATA::getInstance()->getKaibao());
            haungNum->setString("X "+GAMEDATA::getInstance()->getHuangfan());
        }
        if(NULL != getChildByTag(1088)){
            ((Label*)getChildByTag(1088))->setString(GAMEDATA::getInstance()->getFriendOpenRoomResp().prid);
        }
    }
}

void GuiLayer::hideInvitePlayer(int clientId){
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


void GuiLayer::showInvitePlayer(int clientId){
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


void GuiLayer::showPlayerBill(){
    Audio::getInstance()->playSoundClick();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getBillCommand());
    BillInfo* bill = BillInfo::create();
    bill->setShowPosition();
    getParent()->addChild(bill,50);
}

void GuiLayer::drawPlayerInvite(){
    MenuItemImage* left = MenuItemImage::create("headportrait/userbk.png", "headportrait/userbk.png",
                                                CC_CALLBACK_1(GuiLayer::invitePlayer, this));
    left->setTag(ClientSeatId::left);
    leftPlayerInvite = Menu::create(left, NULL);
    leftPlayerInvite->setPosition(Point(70, 455));
    addChild(leftPlayerInvite);
    MenuItemImage* right = MenuItemImage::create("headportrait/userbk.png", "headportrait/userbk.png",
                                                 CC_CALLBACK_1(GuiLayer::invitePlayer, this));
    right->setTag(ClientSeatId::right);
    rightPlayerInvite = Menu::create(right, NULL);
    rightPlayerInvite->setPosition(Point(1213, 455));
    addChild(rightPlayerInvite);
    MenuItemImage* opp = MenuItemImage::create("headportrait/userbk.png", "headportrait/userbk.png",
                                               CC_CALLBACK_1(GuiLayer::invitePlayer, this));
    opp->setTag(ClientSeatId::opposite);
    oppositePlayerInvite = Menu::create(opp, NULL);
    oppositePlayerInvite->setPosition(Point(945, 642));
    addChild(oppositePlayerInvite);
    
    //二人模式
    if(GAMEDATA::getInstance()->getMyGameModel() == GameModel::TWOPLAYER){
        leftPlayerInvite->setVisible(false);
        rightPlayerInvite->setVisible(false);
    }
}

void GuiLayer::invitePlayer(Ref* ref){
    //TODO
}


void GuiLayer::dissovleRoom(){
    HintDialog* dia = HintDialog::create(ChineseWord("dialog_text_3"), [=](Ref* ref){
        GAMEDATA::getInstance()->clearPlayersInfo();
        if(GAMEDATA::getInstance()->getGameType() == 3){
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getHZDissolveRoomCommand());
        }else{
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getDissolveRoomCommand());
        }
    });
    getParent()->addChild(dia,50);
}


void GuiLayer::hideDissovleBtn(){
    if(NULL != getChildByTag(9999)){
        getChildByTag(9999)->setVisible(false);
    }
}

void GuiLayer::update(float dt){
    if(getChildByTag(1212)!=NULL){
        if(GAMEDATA::getInstance()->getIsPlaying()&&GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom){
            if(getChildByTag(1212)->isVisible())
                getChildByTag(1212)->setVisible(false);
        }
    }
    //    updateData();
}


void GuiLayer::onEnter(){
    Layer::onEnter();
    kaibaoListener = EventListenerCustom::create(UPDATE_DICE_KAOBAO_STATE, [=](EventCustom* event){
        updateData();
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(kaibaoListener, 1);
};


void GuiLayer::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(kaibaoListener);
};


void GuiLayer::drawTestButton(){
    auto testIamge = MenuItemImage::create("gameview/setting_btn_1.png", "gameview/setting_btn_2.png",
                                           CC_CALLBACK_0(GuiLayer::testButtonClick, this));
    Menu* testMenu = Menu::create(testIamge, NULL);
    testMenu->setPosition(640,390);
    addChild(testMenu);
}

//测试方法
void GuiLayer::testButtonClick(){
    
//#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    CallAndroidMethod::getInstance()->requestEvent(UserData::getInstance()->getPoxiaoId(),"0");//从2开始
//#endif
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    CallIOSMethod::getInstance()->doPayEvent(UserData::getInstance()->getPoxiaoId(),0);
//#endif
    //    PlayerCpgtData cpgData;
    //    cpgData.poker = "23";
    //    cpgData.seatId = 3;
    //    cpgData.sId = 2;
    //    GangData gangData;
    //    gangData.gang = "4,5,9";
    //    gangData.flag = 0;
    //    cpgData.playerGang.push_back(gangData);
    //    _eventDispatcher->dispatchCustomEvent(MSG_HZ_PLAYER_GANG,&cpgData);
    //            EventCustom event2(MSG_OTHER_PLAYER_CHI);
    //            _eventDispatcher->dispatchEvent(&event2);
    
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
        resultData.huType = "3,4,13";
        resultData.gangfen = 10;
        resultData.nickName = StringUtils::format("这里是装电视台%d",i+1);
        gameResults.push_back(resultData);
    }
    GAMEDATA::getInstance()->setDiaopao("8");
    GAMEDATA::getInstance()->setGameResults(gameResults);
    GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
    GAMEDATA::getInstance()->setHeroSeatId(1);
    GAMEDATA::getInstance()->setPrivateLezi("0");
    GAMEDATA::getInstance()->setPrivateKaibao("0");
    GAMEDATA::getInstance()->setPrivateEmsc("1");
    GAMEDATA::getInstance()->setCurrentBank(1);
    GAMEDATA::getInstance()->setFanMa("1,2");
    GAMEDATA::getInstance()->setFanMaType("1");
    GAMEDATA::getInstance()->setHZDiFen("10");
    GAMEDATA::getInstance()->setHZMaShu("4");
//    GAMEDATA::getInstance()->setGameType(3);
    FriendOpenRoomRespData opendata;
    opendata.prjushu ="8";
    opendata.prjucount ="2";
    GAMEDATA::getInstance()->setFriendOpenRoomResp(opendata);
    char* buf = const_cast<char*>("2");
//    _eventDispatcher->dispatchCustomEvent(MSG_HZ_GAME_RESULT,buf);
    _eventDispatcher->dispatchCustomEvent(MSG_GAME_RESULT,buf);
    
    
    //    PlayerTurnData playerTurnData;
    //    playerTurnData.seatId = GAMEDATA::getInstance()->getHeroSeatId();
    //    PlayerCpgtData tingData;
    //    tingData.seatId = GAMEDATA::getInstance()->getHeroSeatId();
    //    tingData.ting ="1";
    //    playerTurnData.hastinggang = true;
    //    HeroHuPaiData huPaiData;
    //    huPaiData.poker = 1;
    //    huPaiData.hu = "2";
    //    tingData.heroHu.push_back(huPaiData);
    //    HeroHuPaiData huPaiData2;
    //    huPaiData2.poker = 8;
    //    huPaiData2.hu = "2,5,6,7";
    //    tingData.heroHu.push_back(huPaiData2);
    //    playerTurnData.cpgData = tingData;
    //    _eventDispatcher->dispatchCustomEvent(MSG_PLAYER_TURN_WHO, &playerTurnData);
    //    ChatAndroidMethod::getInstance()->sendChatInfo(UserData::getInstance()->getPoxiaoId(), "hello word");
    
    //    PlayerCpgtData cpgData;
    //    cpgData.hu = 1;
    //    if(_mDoc.HasMember("angang")){
    //        const rapidjson::Value &angang = _mDoc["angang"];
    //        GangData gangData;
    //        gangData.gang = angang.GetString();
    //        gangData.flag = 1;
    //        cpgData.playerGang.push_back(gangData);
    //        cpgData.seatId = GAMEDATA::getInstance()->getHeroSeatId();
    //    }
    //    if(_mDoc.HasMember("penggang")){
    //        const rapidjson::Value &angang = _mDoc["penggang"];
    //        GangData gangData;
    //        gangData.gang = angang.GetString();
    //        gangData.flag = 2;
    //        cpgData.playerGang.push_back(gangData);
    //        cpgData.seatId = GAMEDATA::getInstance()->getHeroSeatId();
    //    }
    //    _eventDispatcher->dispatchCustomEvent(MSG_HZ_GAME_HU_ACTION,&cpgData);
    
//    HongbaoAnim* ami = HongbaoAnim::create();
//    ami->initView("0.37",3);
//    ami->initView("0.37","0.37",1,false);
//    addChild(ami,100);
    CompetitionResult* result = CompetitionResult::create();
    result->showCompetiotionResult("1","1","36","30");
    getParent()->addChild(result,100);
}
