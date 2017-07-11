//
//  PublicResultLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/21.
//
//

#include "mahjong/result/hongzhong/special/HZSpecialResultLayer.hpp"
#include "mahjong/result/hongzhong/special/HZGameResultCell.hpp"
#include "mahjong/lobby/LobbyScene.h"
#include "mahjong/lobby/dialog/EnterRoomDialog.hpp"
#include "mahjong/lobby/shop/gold/GoldNotEnoughDialog.hpp"
#include "mahjong/lobby/shop/gold/ChargeGold.hpp"
#include "mahjong/common/jong/Jong.h"
#include "mahjong/common/dialog/prompt/HintDialog.hpp"
#include "mahjong/common/dialog/network/LostNetwork2.hpp"
#include "mahjong/common/utils/SeatIdUtil.h"
#include "mahjong/common/utils/StringUtil.h"
#include "mahjong/common/utils/Chinese.h"
#include "mahjong/common/widget/ParticleUtil.hpp"
#include "mahjong/gameview/MjGameScene.h"
#include "mahjong/gameview/shanghai/normal/MahjongView.h"
#include "server/NetworkManage.h"
#include "server/CommandManage.h"
#include "wechat/android/CallAndroidMethod.h"
#include "wechat/ios/CallIOSMethod.h"
#include "mahjong/result/hongbao/HongbaoAnim.hpp"
#include "mahjong/result/hongbao/HongbaoAnim2.hpp"

bool HZSpecialResultLayer::init(){
    if(!Layer::init()){
        return false;
    }
    auto reslut_bg = Sprite::create("result/result_bg.jpg");
    reslut_bg->setPosition(640, 360);
    addChild(reslut_bg,-1);
    showResultTitle();//结算界面标题
    showGameReslut();
    scheduleUpdate();
    return true;
}

void HZSpecialResultLayer::showResultTitle(){
    auto resultTitle = Sprite::create();
    resultTitle->setTexture("result/game_result_title.png");
    resultTitle->setPosition(640,625);
    addChild(resultTitle);
}


void HZSpecialResultLayer::showGameReslut(){
    
    //    auto fanghao = Sprite::create("result/fang_jian_hao.png");
    //    fanghao->setPosition(940,570);
    //    addChild(fanghao,1);
    //
    //    auto fanghaoNum = LabelAtlas::create(GAMEDATA::getInstance()->getFriendOpenRoomResp().prid, "result/ju_num.png",16,22,'0');
    //    fanghaoNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    //    fanghaoNum->setPosition(980,570);
    //    addChild(fanghaoNum);
    
    
    vector<GameResultData> results = GAMEDATA::getInstance()->getGameResults();
    for (int i=0; i<results.size();i++) {
        HZGameResultCell* cell = HZGameResultCell::create(results.at(i));
        cell->setPosition(215+285*i,340);
        addChild(cell);
    }
    
    if(UserData::getInstance()->isWeixinPayOpen()){
        if(atoi(GAMEDATA::getInstance()->getHuiGuiLiBao().c_str())>0){
            HongbaoAnim* ami = HongbaoAnim::create();
            ami->initView(GAMEDATA::getInstance()->getHuiGuiLiBao(),3);
            addChild(ami,10);
        }else if(GAMEDATA::getInstance()->getGameHongBaoPride().dyj == UserData::getInstance()->getPoxiaoId()&&GAMEDATA::getInstance()->getGameHongBaoPride().fzid == UserData::getInstance()->getPoxiaoId()&&atof(GAMEDATA::getInstance()->getGameHongBaoPride().dyjfee.c_str())>0&&atof(GAMEDATA::getInstance()->getGameHongBaoPride().fzfee.c_str())>0){
            //双喜临门
            if(atof(GAMEDATA::getInstance()->getGameHongBaoPride().sxlmfee.c_str())>0){
                schedule([=](float dt){
                    HongbaoAnim2* ami = HongbaoAnim2::create();
                    ami->initView(GAMEDATA::getInstance()->getGameHongBaoPride().dyjfee, GAMEDATA::getInstance()->getGameHongBaoPride().fzfee,1,true);
                    addChild(ami,10);
                }, 0, 0, 3, "zhe_li_shi_la_la_1");
                
            }else {
                schedule([=](float dt){
                    HongbaoAnim2* ami = HongbaoAnim2::create();
                    ami->initView(GAMEDATA::getInstance()->getGameHongBaoPride().dyjfee, GAMEDATA::getInstance()->getGameHongBaoPride().fzfee,1,false);
                    addChild(ami,10);
                }, 0, 0, 3, "zhe_li_shi_la_la_2");
                
            }
            
        }else if(GAMEDATA::getInstance()->getGameHongBaoPride().dsj == UserData::getInstance()->getPoxiaoId()&&GAMEDATA::getInstance()->getGameHongBaoPride().fzid == UserData::getInstance()->getPoxiaoId()&&atof(GAMEDATA::getInstance()->getGameHongBaoPride().dsjfee.c_str())>0&&atof(GAMEDATA::getInstance()->getGameHongBaoPride().fzfee.c_str())>0){
            schedule([=](float dt){
                HongbaoAnim2* ami = HongbaoAnim2::create();
                ami->initView(GAMEDATA::getInstance()->getGameHongBaoPride().dsjfee, GAMEDATA::getInstance()->getGameHongBaoPride().fzfee,2,false);
                addChild(ami,10);
                
            }, 0, 0, 3, "zhe_li_shi_la_la_3");
            
        }else if(GAMEDATA::getInstance()->getGameHongBaoPride().dsj == UserData::getInstance()->getPoxiaoId()&&atof(GAMEDATA::getInstance()->getGameHongBaoPride().dsjfee.c_str())>0){
            schedule([=](float dt){
                HongbaoAnim* ami = HongbaoAnim::create();
                ami->initView(GAMEDATA::getInstance()->getGameHongBaoPride().dsjfee,2);
                addChild(ami,10);
            }, 0, 0, 3, "zhe_li_shi_la_la_4");
            
            
        }else if(GAMEDATA::getInstance()->getGameHongBaoPride().dyj == UserData::getInstance()->getPoxiaoId()&&atof(GAMEDATA::getInstance()->getGameHongBaoPride().dyjfee.c_str())>0){
            schedule([=](float dt){
                HongbaoAnim* ami = HongbaoAnim::create();
                ami->initView(GAMEDATA::getInstance()->getGameHongBaoPride().dyjfee,1);
                addChild(ami,10);
            }, 0, 0, 3, "zhe_li_shi_la_la_4");
            
            
        }else if(GAMEDATA::getInstance()->getGameHongBaoPride().fzid == UserData::getInstance()->getPoxiaoId()&&atof(GAMEDATA::getInstance()->getGameHongBaoPride().fzfee.c_str())>0){
            schedule([=](float dt){
                HongbaoAnim* ami = HongbaoAnim::create();
                ami->initView(GAMEDATA::getInstance()->getGameHongBaoPride().fzfee,0);
                addChild(ami,10);
            }, 0, 0, 3, "zhe_li_shi_la_la_5");
            
        }else{
            showLayerBtn();
        }
    }else{
        showLayerBtn();
    }
    
    //大结算的时候获取玩家信息
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getPlayerInfoCommand());
}

void HZSpecialResultLayer::showLayerBtn(){
    
    auto helpImage = MenuItemImage::create("result/xuan_yao_btn_1.png","result/xuan_yao_btn_2.png",
                                           CC_CALLBACK_0(HZSpecialResultLayer::shareResult, this));
    auto golobby = MenuItemImage::create("result/go_lobby_btn_1.png","result/go_lobby_btn_2.png",
                                         CC_CALLBACK_0(HZSpecialResultLayer::gotoLobby, this));
    
    Menu* myMneu = Menu::create(helpImage,golobby,NULL);
    myMneu->setPosition(640,60);
    myMneu->alignItemsHorizontallyWithPadding(160);
    addChild(myMneu);
    
    auto info = Sprite::create();
    info->setPosition(1050,40);
    addChild(info);
    if(GAMEDATA::getInstance()->getPrivateRoomType() == "4"){
        info->setTexture("result/game_over_4.png");
    }else if(GAMEDATA::getInstance()->getPrivateRoomType() == "16"){
        info->setTexture("result/game_over_16.png");
    }else{
        info->setTexture("result/game_over_8.png");
    }
}

void HZSpecialResultLayer::shareResult(){
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string path =StringUtils::format("%s/mahjong_screen_shot.png",CallAndroidMethod::getInstance()->getSdCardDir().c_str());
    log("screenShot path = %s",path.c_str());
    utils::captureScreen(CC_CALLBACK_2(HZSpecialResultLayer::afterCaptured, this) ,path);
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    std::string path =StringUtils::format("%smahjong_screen_shot.png",FileUtils::sharedFileUtils()->getWritablePath().c_str());
    log("screenShot path = %s",path.c_str());
    utils::captureScreen(CC_CALLBACK_2(HZSpecialResultLayer::afterCaptured, this) ,path);
#endif
}


void HZSpecialResultLayer::afterCaptured(bool succeed, const std::string &outputFile)
{
    if (succeed) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        CallAndroidMethod::getInstance()->shareImageToWeChat(outputFile, false);
#endif
        
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        CallIOSMethod::getInstance()->doWechatShareImg(outputFile, 0);
#endif
    }
}

void HZSpecialResultLayer::onEnter(){
    Layer::onEnter();
    myCoreLoginRespListener = EventListenerCustom::create(MSG_LOGIN_RESP, [=](EventCustom* event){
        if(GAMEDATA::getInstance()->getShareHongBaoFriendState() == 1){
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendGetHongbaoPride());
            GAMEDATA::getInstance()->setShareHongBaoFriendState(0);
        }else if(GAMEDATA::getInstance()->getShareHongBaoFriendState() == 2){
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendGiveupHongbaoPride());
            GAMEDATA::getInstance()->setShareHongBaoFriendState(0);
        }
        Director::getInstance()->replaceScene(TransitionFade::create(0.3, LobbyScene::create()));
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(myCoreLoginRespListener, 1);
    networkBreakListener = EventListenerCustom::create(MSG_NETWORK_BREAK_INFO, [=](EventCustom* event){
        if(NULL == getChildByTag(2000)){
            LostNetwork2* net = LostNetwork2::create();
            net->setTag(2000);
            addChild(net,200);
        }
        if(NetworkManage::getInstance()->reConnectSocket()){
            int  delayTime = 1.0f;
            schedule([=](float dt){
                if(UserData::getInstance()->getWxOpenId() ==  "unknow"){
                    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getVistorLoginAgain(UserData::getInstance()->getUserName(), UserData::getInstance()->getPassword()));
                }else{
                    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getThirdLoginCommand(UserData::getInstance()->getWxOpenId(), UserData::getInstance()->getWxUnionid(),UserData::getInstance()->getPicture(), StringUtils::format("%d",UserData::getInstance()->getGender()), UserData::getInstance()->getNickName(), UserData::getInstance()->getHsman(), UserData::getInstance()->getHstype(), UserData::getInstance()->getImsi(),UserData::getInstance()->getImei(),UserData::getInstance()->getAppVer(),true));
                }
            }, 0, 0, delayTime, "socket_reconnect2000");
            NetworkManage::getInstance()->startSocketBeat(CommandManage::getInstance()->getHeartCommmand());
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(networkBreakListener, 1);
    
}

void HZSpecialResultLayer::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(myCoreLoginRespListener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(networkBreakListener);
}

void HZSpecialResultLayer::gotoLobby(){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getQuitRoomCommand());
    Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
}

void HZSpecialResultLayer::update(float dt){
    if(GAMEDATA::getInstance()->getShowProtected()){
        if(NULL == getChildByTag(2000)){
            LostNetwork2* net = LostNetwork2::create();
            net->setTag(2000);
            addChild(net,200);
        }
        GAMEDATA::getInstance()->setShowProtected(false);
    }
}
