#include "mahjong/lobby/openroom/FriendOpenRoom.h"
#include "mahjong/lobby/openroom/suzhou/SuZhouLayer.hpp"
#include "mahjong/lobby/openroom/hongzhong/HongZhongLayer.hpp"
#include "mahjong/lobby/openroom/baida/BaiDaLayer.hpp"
#include "mahjong/lobby/openroom/fanpai/FanPaiBaiDaLayer.hpp"
#include "mahjong/lobby/LobbyScene.h"
#include "mahjong/common/state/GameData.h"
#include "server/NetworkManage.h"
//#import "baidu/ios/BaiDuLocationAPI.h"
//#include "baidu/android/CallBDAndroidMethod.h"


bool FriendOpenRoom::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    auto dialog_bg = Sprite::create("openroom/open_room_bg.png");
    dialog_bg->setPosition(640,350);
    addChild(dialog_bg);
    
    
    auto title = Sprite::create("openroom/open_room_title.png");
    title->setPosition(640,640);
    addChild(title);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(FriendOpenRoom::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(1170, 660);
    addChild(closeMenu);
    
    
    
    suZhou = Sprite::create("openroom/suzhou_btn_1.png");
    suZhou->setPosition(215,535);
    addChild(suZhou);
    
    hongZhong = Sprite::create("openroom/hong_zhong_btn_2.png");
    hongZhong->setPosition(215,430);
    addChild(hongZhong);
    
    baiDa = Sprite::create("openroom/baida_btn_2.png");
    baiDa->setPosition(215,325);
    addChild(baiDa);
    
    fanPaiBD = Sprite::create("openroom/fanpaibaida_btn_2.png");
    fanPaiBD->setPosition(215,220);
    addChild(fanPaiBD);
    
    vertical = Sprite::create("openroom/vertical_line_1.png");
    vertical->setPosition(322,355);
    addChild(vertical);
    
    
    SuZhouLayer* laye1 = SuZhouLayer::create();
    laye1->setTag(1000);
    addChild(laye1);
    
    HongZhongLayer* laye2 = HongZhongLayer::create();
    laye2->setVisible(false);
    laye2->setTag(1001);
    addChild(laye2);
    
    BaiDaLayer* laye3 = BaiDaLayer::create();
    laye3->setVisible(false);
    laye3->setTag(1002);
    addChild(laye3);
    
    FanPaiBaiDaLayer* laye4 = FanPaiBaiDaLayer::create();
    laye4->setVisible(false);
    laye4->setTag(1003);
    addChild(laye4);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(FriendOpenRoom::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(FriendOpenRoom::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(FriendOpenRoom::onTouchEnded, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener,this);
    
    //显示用户的日常习惯
        if(UserData::getInstance()->getLatelyMahjongType() == GameMahjongType::SuZhou){
            showSuZhouMahjong();
        }else if(UserData::getInstance()->getLatelyMahjongType() == GameMahjongType::HongZhong){
            showHongZhongMahjong();
        }else if(UserData::getInstance()->getLatelyMahjongType() == GameMahjongType::BaiDa){
            showBaiDaMahjong();
        }else if(UserData::getInstance()->getLatelyMahjongType() == GameMahjongType::FanPai){
            showFanPaiBaiDaMahjong();
        }
//#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
//    BaiDuLocationAPI::getInstance()->getPlayerLocation();
//#endif
//#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
//    CallBDAndroidMethod::getInstance()->updateLongitude();
//    CallBDAndroidMethod::getInstance()->updateLatitude();
//#endif
    return true;
}


void FriendOpenRoom::onEnter(){
    Layer::onEnter();
    
}


void FriendOpenRoom::onExit(){
    Layer::onExit();
    
}

bool FriendOpenRoom::onTouchBegan(Touch *touch, Event  *event){
    return true;
}


void FriendOpenRoom::onTouchMoved(Touch *touch, Event  *event){
    
    
}



void FriendOpenRoom::onTouchEnded(Touch *touch, Event  *event){
    if(suZhou->getBoundingBox().containsPoint(touch->getLocation())){
        showSuZhouMahjong();
    }
    if(hongZhong->getBoundingBox().containsPoint(touch->getLocation())){
        showHongZhongMahjong();
    }
    if(baiDa->getBoundingBox().containsPoint(touch->getLocation())){
        showBaiDaMahjong();
    }
    if(fanPaiBD->getBoundingBox().containsPoint(touch->getLocation())){
        showFanPaiBaiDaMahjong();
    }
}


void FriendOpenRoom::showSuZhouMahjong(){
    selectLayerIndex = 0;
    suZhou->setTexture("openroom/suzhou_btn_1.png");
    hongZhong->setTexture("openroom/hong_zhong_btn_2.png");
    baiDa->setTexture("openroom/baida_btn_2.png");
    fanPaiBD->setTexture("openroom/fanpaibaida_btn_2.png");
    vertical->setTexture("openroom/vertical_line_1.png");
    if(NULL != getChildByTag(1000))
        getChildByTag(1000)->setVisible(true);
    if(NULL != getChildByTag(1001))
        getChildByTag(1001)->setVisible(false);
    if(NULL != getChildByTag(1002))
        getChildByTag(1002)->setVisible(false);
    if(NULL != getChildByTag(1003))
        getChildByTag(1003)->setVisible(false);
}

void FriendOpenRoom::showHongZhongMahjong(){
    selectLayerIndex = 1;
    suZhou->setTexture("openroom/suzhou_btn_2.png");
    hongZhong->setTexture("openroom/hong_zhong_btn_1.png");
    baiDa->setTexture("openroom/baida_btn_2.png");
     fanPaiBD->setTexture("openroom/fanpaibaida_btn_2.png");
    vertical->setTexture("openroom/vertical_line_2.png");
    if(NULL != getChildByTag(1000))
        getChildByTag(1000)->setVisible(false);
    if(NULL != getChildByTag(1001))
        getChildByTag(1001)->setVisible(true);
    if(NULL != getChildByTag(1002))
        getChildByTag(1002)->setVisible(false);
    if(NULL != getChildByTag(1003))
        getChildByTag(1003)->setVisible(false);
}
void FriendOpenRoom::showBaiDaMahjong(){
    selectLayerIndex = 2;
    suZhou->setTexture("openroom/suzhou_btn_2.png");
    hongZhong->setTexture("openroom/hong_zhong_btn_2.png");
    baiDa->setTexture("openroom/baida_btn_1.png");
    fanPaiBD->setTexture("openroom/fanpaibaida_btn_2.png");
    vertical->setTexture("openroom/vertical_line_3.png");
    if(NULL != getChildByTag(1000))
        getChildByTag(1000)->setVisible(false);
    if(NULL != getChildByTag(1001))
        getChildByTag(1001)->setVisible(false);
    if(NULL != getChildByTag(1002))
        getChildByTag(1002)->setVisible(true);
    if(NULL != getChildByTag(1003))
        getChildByTag(1003)->setVisible(false);
}

void FriendOpenRoom::showFanPaiBaiDaMahjong(){
    selectLayerIndex = 3;
    suZhou->setTexture("openroom/suzhou_btn_2.png");
    hongZhong->setTexture("openroom/hong_zhong_btn_2.png");
    baiDa->setTexture("openroom/baida_btn_2.png");
    fanPaiBD->setTexture("openroom/fanpaibaida_btn_1.png");
    vertical->setTexture("openroom/vertical_line_4.png");
    if(NULL != getChildByTag(1000))
        getChildByTag(1000)->setVisible(false);
    if(NULL != getChildByTag(1001))
        getChildByTag(1001)->setVisible(false);
    if(NULL != getChildByTag(1002))
        getChildByTag(1002)->setVisible(false);
    if(NULL != getChildByTag(1003))
        getChildByTag(1003)->setVisible(true);
}



void FriendOpenRoom::closeView(){
    removeFromParent();
}


