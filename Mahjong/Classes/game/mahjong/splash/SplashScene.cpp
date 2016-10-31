#include "game/mahjong/splash/SplashScene.h"
#include "game/mahjong/lobby/LobbyScene.h"
#include "game/mahjong/result/ResultLayer.h"
#include "game/mahjong/splash/register/UserRegister.h"
#include "game/mahjong/splash/register/FindPassword.h"
#include "game/mahjong/splash/LoadResource.hpp"
#include "game/mahjong/dialog/prompt/HintDialog.hpp"
#include "game/mahjong/splash/dropdownlist/DropDownListBox.h"
#include "game/mahjong/splash/dropdownlist/LoginMannger.h"
#include "payment/android/CallAndroidMethod.h"
#include "game/mahjong/friend/dialog/RoomFullDialog.hpp"
#include "game/mahjong/shop/fangka/FangkaNotEnoughDialog.hpp"
#include "game/mahjong/friend/dialog/RoomIdErrorDialog.hpp"
#include "game/utils/Audio.h"
#include "game/utils/SeatIdUtil.h"
#include "server/NetworkManage.h"
#include "game/loading/Loading.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "payment/ios/IOSBridge.h"
#endif


Scene* SplashScene::createScene()
{
    auto scene = Scene::create();
    auto layer = SplashScene::create();
    scene->addChild(layer);
    return scene;
}

bool SplashScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    //draw scene
    drawLonginScene();
    showSplashAnim();
    //add event listener
    addTocuhListener();
    return true;
}

void SplashScene::onEnter(){
    Layer::onEnter();
    addCustomEventListener();
}


void SplashScene::onExit(){
    Layer::onExit();
    _eventDispatcher->removeEventListener(loginRespListener);
    _eventDispatcher->removeEventListener(roomRespListener);
    _eventDispatcher->removeEventListener(reConnectAgain);
    _eventDispatcher->removeEventListener(dropListListener);
    _eventDispatcher->removeEventListener(heroFirstPoke);
}


void SplashScene::drawLonginScene(){
    //add game bg to layer
    Sprite* splash_bg = Sprite::create("mainlogin/splah_bg_.jpg");
    splash_bg->setPosition(640,360);
    this->addChild(splash_bg, -1);
    
    auto girl = Sprite::create("mainlogin/login_girl.png");
    girl->setPosition(480,320);
    addChild(girl);
    
    auto feipai = Sprite::create("mainlogin/feipai.png");
    feipai->setPosition(490,400);
    addChild(feipai);
    
    auto desk = Sprite::create("mainlogin/login_desk.png");
    desk->setPosition(640,205);
    addChild(desk);
    
}


void SplashScene::loginByPass(){
    Audio::getInstance()->playSoundClick();
    std::string userName = _editName->getText();
    std::string password = _editPwd->getText();
    if (userName == ""&&password == ""){
        if (UserData::getInstance()->getUserName() != "unknow"&&UserData::getInstance()->getPassword() != "unknow"){
            NetworkManage::getInstance()->sendMsg(
                                                  CommandManage::getInstance()->getLoginCommmand(UserData::getInstance()->getUserName(), UserData::getInstance()->getPassword()));
            showLoading();
        }
    }
    else{
        NetworkManage::getInstance()->sendMsg(
                                              CommandManage::getInstance()->getLoginCommmand(userName, password));
        showLoading();
    }
}

void SplashScene::loginByVisitor(){
    Audio::getInstance()->playSoundClick();
    showLoading();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getThirdLoginCommand("oTIvfwnO4yCaBasG7qJedNbiGuG0", "http://wx.qlogo.cn/mmopen/iaS020Z6hznYwWiacdX0aia7ia9XANXWGKReDZYCjSM8Jt1MFqtnaPRL4ugpZK8cU2bhVmgHs24KB3LDicrQ1cxjeQngXmburObUM/0","1","泥沙爬虫"));
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    IOSBridge::getInstance()->doWechatLogin();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CallAndroidMethod::getInstance()->weChatLogin();
#endif
    
}


void SplashScene::setChangeNickName(std::string name,std::string pwd){
    username_text->setVisible(false);
    _editName->setText(name.c_str());
    _editPwd->setText(pwd.c_str());
}

void SplashScene::showUserRegister(){
    Audio::getInstance()->playSoundClick();
    UserRegister* layer = UserRegister::create();
    this->addChild(layer,6);
}


void SplashScene::findbackPwd(){
    Audio::getInstance()->playSoundClick();
    FindPassword* pass = FindPassword::create();
    this->addChild(pass,6);
}


void  SplashScene::addCustomEventListener(){
    loginRespListener = EventListenerCustom::create(MSG_LOGIN_RESP, [=](EventCustom* event){
        char* buf = static_cast<char*>(event->getUserData());
        std::string result = buf;
        
        if (result == LOGIN_SUCCESS){
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getRoomListCommand("1"));//房间列表
            NetworkManage::getInstance()->heartbeat();//心跳
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getDailySignCommand());//签到
            LoginMannger::getInstance()->addMemoryNickname(UserData::getInstance()->getUserName().c_str(), UserData::getInstance()->getPassword().c_str());
        }
        else{
            removeLoading();
            HintDialog* hint = HintDialog::create("用户名或者密码错误",NULL);
            addChild(hint,6);
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(loginRespListener, 1);
    
    //获取房间列表
    roomRespListener = EventListenerCustom::create(MSG_ROOM_LIST_RESP, [=](EventCustom* event){
        removeLoading();
        Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(roomRespListener, 1);
    
    //断线续玩
    reConnectAgain = EventListenerCustom::create(MSG_PLAYER_CONNECT_AGAIN, [=](EventCustom* event){
        NetworkManage::getInstance()->heartbeat();
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getFriendListCommand());
        GAMEDATA::getInstance()->setIsRecover(true);
        Director::getInstance()->replaceScene(MjGameScene::create());
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(reConnectAgain, 1);
    
    //注册结果返回
    registerRespListener = EventListenerCustom::create(MSG_PLAYER_REGISTER_RESP, [=](EventCustom* event){
        std::string result = static_cast<char*>(event->getUserData());
        if(result == "1"){
            username_text->setVisible(false);
            password_text->setVisible(false);
            _editName->setText(UserData::getInstance()->getUserName().c_str());
            _editPwd->setText(UserData::getInstance()->getPassword().c_str());
            LoginMannger::getInstance()->addMemoryNickname(UserData::getInstance()->getUserName().c_str(), UserData::getInstance()->getPassword().c_str());
            
        }else{
            HintDialog* hint = HintDialog::create("注册失败",NULL);
            addChild(hint,6);
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(registerRespListener, 1);
    
    //用户名下拉列表
    dropListListener = EventListenerCustom::create("splashCallBack", [=](EventCustom* event){
        setChangeNickName(GAMEDATA::getInstance()->getLoginAccPwd().account,GAMEDATA::getInstance()->getLoginAccPwd().password);
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(dropListListener, 1);
    
    //断线续玩第一张牌
    heroFirstPoke = EventListenerCustom::create(MSG_OTHER_PALYER_JONG, [=](EventCustom* event){
        
        int seatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), GAMEDATA::getInstance()->getOtherPlayJong().seatId);
        if (seatId == ClientSeatId::hero){
            GAMEDATA::getInstance()->setNeedRemovePoker(GAMEDATA::getInstance()->getOtherPlayJong().poker);
        }
        
    });
    
    //进入好友房间回复
    reEnterFriendRoomListener =  Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_ENTER_FRIEND_ROOM_RESP, [=](EventCustom* event){
        char* buf = static_cast<char*>(event->getUserData());
        std::string result = buf;
        if (result == "1"){
            NetworkManage::getInstance()->heartbeat();
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getFriendListCommand());
            GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
            Director::getInstance()->replaceScene(TransitionFade::create(1, MjGameScene::create()));
        } else if(result == "2")
        {
            RoomFullDialog* doo = RoomFullDialog::create();
            addChild(doo);
        }
        else if(result == "3")
        {
            FangkaNotEnoughDialog* dialog = FangkaNotEnoughDialog::create();
            addChild(dialog,4);
        }
        else if(result == "4"){
            RoomIdErrorDialog* idd = RoomIdErrorDialog::create();
            addChild(idd,4);
        }
    });

    
    reOpenFriendRoomListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_FRIEND_OPEN_ROOM_RESP, [=](EventCustom* event){
        GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
        FriendOpenRoomRespData resp = GAMEDATA::getInstance()->getFriendOpenRoomResp();
        if(resp.result == 1){
            NetworkManage::getInstance()->heartbeat();
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getFriendListCommand());
            Director::getInstance()->replaceScene(TransitionFade::create(1, MjGameScene::create()));
        }else if(resp.result == 2){
            FangkaNotEnoughDialog* dia =FangkaNotEnoughDialog::create();
            addChild(dia,4);
        }
        
    });
}

void SplashScene::addTocuhListener(){
    auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
        switch (code)
        {
            case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
                break;
            case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
                Director::getInstance()->end();
                break;
                
            default:
                break;
        }
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void SplashScene::showLoading(){
    Loading* loadLayer = Loading::create();
    loadLayer->setTag(1000);
    this->addChild(loadLayer);
}



void SplashScene::removeLoading(){
    if(NULL != getChildByTag(1000)){
        getChildByTag(1000)->removeFromParent();
    }
}



void SplashScene::editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox){
    if (editBox->getTag() == 606){
        username_text->setVisible(false);
        _editName->setText("");
    }
    if (editBox->getTag() == 607){
        password_text->setVisible(false);
        _editPwd->setText("");
    }
}

void SplashScene::editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox){
    
}

void SplashScene::editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text){
    
    
}

void SplashScene::editBoxReturn(cocos2d::extension::EditBox* editBox){
    
}


void SplashScene::showSplashAnim(){
    
    auto gameTitle = Sprite::create("mjlobby/game_icon.png");
    gameTitle->setPosition(1070, 640);
    this->addChild(gameTitle);
    //眨眼动画
    auto levelMidEye = Sprite::create();
    levelMidEye->setPosition(480,320);
    addChild(levelMidEye,3);
    auto yepoint = Sprite::create("mainlogin/yellow_point.png");
    yepoint->setVisible(false);
    yepoint->setPosition(420,540);
    addChild(yepoint);
    levelMidEye->runAction(Repeat::create(Sequence::create(
                                                           CallFunc::create([=](){
        levelMidEye->setTexture("mainlogin/loading_eye_1.png");
    }),
                                                           DelayTime::create(2.0/24),
                                                           CallFunc::create([=](){
        levelMidEye->setTexture("mainlogin/loading_eye_2.png");
    }),
                                                           DelayTime::create(2.0/24),
                                                           CallFunc::create([=](){
        levelMidEye->setTexture("mainlogin/loading_eye_1.png");
    }),
                                                           DelayTime::create(2.0/24),
                                                           CallFunc::create([=](){
        levelMidEye->setTexture("");
    }),
                                                           DelayTime::create(2.0/24),
                                                           CallFunc::create([=](){
        levelMidEye->setTexture("mainlogin/loading_eye_1.png");
    }),
                                                           DelayTime::create(2.0/24),
                                                           CallFunc::create([=](){
        levelMidEye->setTexture("mainlogin/loading_eye_2.png");
    }),
                                                           DelayTime::create(2.0/24),
                                                           CallFunc::create([=](){
        levelMidEye->setTexture("mainlogin/loading_eye_1.png");
    }),
                                                           DelayTime::create(2.0/24),
                                                           CallFunc::create([=](){
        levelMidEye->setTexture("");
    }),
                                                           CallFunc::create([=](){
        yepoint->setVisible(true);
        yepoint->setScale(0.1f);
        yepoint->setOpacity(70);
        yepoint->runAction(Sequence::create(Spawn::create(FadeTo::create(4.0/24, 200),ScaleTo::create(4.0/24, 1.2f),RotateTo::create(6.0f/24, 144), NULL),CallFunc::create([=](){yepoint->setRotation(144);}), RotateTo::create(6.0f/24, 216),Spawn::create(FadeTo::create(4.0/24, 70),ScaleTo::create(4.0/24, 0.5f), NULL),CallFunc::create([=](){yepoint->setVisible(false);yepoint->setRotation(0);}), NULL));
    }),
                                                           DelayTime::create(96.0/24),
                                                           NULL), CC_REPEAT_FOREVER));
    
    
    //logo光效
    auto logoLight = Sprite::create();
    logoLight->setPosition(1070, 645);
    addChild(logoLight);
    auto animation = Animation::create();
    for( int i=1;i<4;i++)
    {
        std::string imageName = cocos2d::String::createWithFormat("mjlobby/lobby_logo_light_%d.png",i)->_string;
        animation->addSpriteFrameWithFile(imageName);
    }
    // should last 1 seconds. And there are 24 frames.
    animation->setDelayPerUnit(4.0f/ 24.0f);
    animation->setRestoreOriginalFrame(true);
    auto action = Animate::create(animation);
    logoLight->runAction(Sequence::create(Repeat::create(Sequence::create(action,DelayTime::create(12.0f/24), NULL), CC_REPEAT_FOREVER), NULL));
    
    //文字光效
    auto logoText = Sprite::create();
    logoText->setPosition(1070, 645);
    addChild(logoText);
    auto animation2 = Animation::create();
    for( int j=1;j<5;j++)
    {
        std::string imageName = cocos2d::String::createWithFormat("mjlobby/lobby_logo_text_%d.png",j)->_string;
        animation2->addSpriteFrameWithFile(imageName);
    }
    // should last 1 seconds. And there are 24 frames.
    animation2->setDelayPerUnit(3.0f / 24.0f);
    animation2->setRestoreOriginalFrame(true);
    auto action2 = Animate::create(animation2);
    logoText->runAction(Sequence::create(Repeat::create(Sequence::create(action2,DelayTime::create(24.0/24), NULL), CC_REPEAT_FOREVER), NULL));
    
    //光效
    auto lobbyLight_1 = Sprite::create("mjlobby/lobby_light_1.png");
    lobbyLight_1->setPosition(640, 360);
    addChild(lobbyLight_1);
    lobbyLight_1->runAction(Sequence::create(Repeat::create(Sequence::create(FadeTo::create(1.0f, 0),FadeTo::create(1.0f, 255),NULL), CC_REPEAT_FOREVER),NULL));
    
    auto lobbyLight_2 = Sprite::create("mjlobby/lobby_light_2.png");
    lobbyLight_2->setPosition(640, 360);
    addChild(lobbyLight_2);
    lobbyLight_2->runAction(Sequence::create(Repeat::create(Sequence::create(FadeTo::create(1.0f, 0),FadeTo::create(1.0f, 255),NULL), CC_REPEAT_FOREVER),NULL));
    
    auto lobbyLight_3 = Sprite::create("mjlobby/lobby_light_3.png");
    lobbyLight_3->setPosition(640, 360);
    addChild(lobbyLight_3);
    lobbyLight_3->runAction(Sequence::create(Repeat::create(Sequence::create(FadeTo::create(1.0f, 0),FadeTo::create(1.0f, 255),NULL), CC_REPEAT_FOREVER),NULL));
    
    //光斑
    auto lightSpot1 = Sprite::create("mjlobby/light_spot.png");
    lightSpot1->setPosition(640,360);
    lightSpot1->setTag(602);
    addChild(lightSpot1);
    auto lightSpot = Sprite::create("mjlobby/light_spot.png");
    lightSpot->setPosition(-640,360);
    lightSpot1->setTag(603);
    addChild(lightSpot);
    schedule(schedule_selector(SplashScene:: scrollLightSpot), 0, CC_REPEAT_FOREVER, 0);
    
    //按钮光效
    auto btnlight = Sprite::create("mainlogin/login_btn_light.png");
    btnlight->setPosition(640,111);
    addChild(btnlight,5);
    btnlight->runAction(Sequence::create(Repeat::create(Sequence::create(FadeTo::create(1.0f, 30),FadeTo::create(1.0f, 200),DelayTime::create(3.0f), NULL), CC_REPEAT_FOREVER),NULL));
    auto btnpoint = Sprite::create("mainlogin/yellow_point.png");
    btnpoint->setPosition(495,160);
    addChild(btnpoint,7);
    btnpoint->setVisible(false);
    btnpoint->runAction(Repeat::create(Sequence::create(CallFunc::create([=](){
        btnpoint->setScale(0.1f);
        btnpoint->setOpacity(70);
        btnpoint->setVisible(true);
    }), Spawn::create(FadeTo::create(4.0/24, 200),ScaleTo::create(4.0/24, 1.2f),RotateTo::create(6.0f/24, 144), NULL),
                                                        CallFunc::create([=](){yepoint->setRotation(144);}),
                                                        RotateTo::create(6.0f/24, 216),
                                                        Spawn::create(FadeTo::create(4.0/24, 70),ScaleTo::create(4.0/24, 0.5f), NULL),
                                                        CallFunc::create([=](){yepoint->setVisible(false);yepoint->setRotation(0);}),DelayTime::create(96.0/24), NULL), CC_REPEAT_FOREVER));
    
    
    auto visitorBtn = MenuItemImage::create("mainlogin/we_chat_btn_1.png", "mainlogin/we_chat_btn_2.png",
                                            CC_CALLBACK_0(SplashScene::loginByVisitor, this));
    loginMenu = Menu::create(visitorBtn, NULL);
    loginMenu->setPosition(0, 0);
    
    //获取尺寸大小
    Size clipSize = loginMenu->getContentSize();
    
    //[3].创建底板的发光图片 : spark
    Sprite* spark = Sprite::create("mainlogin/shua_light.png");
    spark->setRotation(80);
    spark->setPosition(-clipSize.width+20, 15);
    
    //[4].创建裁剪节点 : clippingNode
    ClippingNode* clippingNode = ClippingNode::create();
    clippingNode->setPosition(640,88);
    addChild(clippingNode,10);
    
    clippingNode->setAlphaThreshold(0.05f); //设置alpha闸值
    clippingNode->setContentSize(clipSize); //设置尺寸大小
    
    clippingNode->setStencil(loginMenu);   //设置模板stencil
    clippingNode->addChild(loginMenu, 1);  //先添加标题,会完全显示出来,因为跟模板一样大小
    spark->setScale(0.70);
    clippingNode->addChild(spark,2);       //会被裁减
    
    //[5].左右移动spark
    MoveTo* moveAction = MoveTo::create(5.0f, Vec2(clipSize.width-20, 15));
    spark->runAction(RepeatForever::create(Sequence::create(moveAction,CallFunc::create([=](){
        spark->setPosition(-clipSize.width, 15);
    }), NULL)));
}

void SplashScene :: scrollLightSpot(float dt){
    if(NULL!=getChildByTag(602)){
        if(getChildByTag(602)->getPositionX()>1920){
            getChildByTag(602)->setPosition(-640,360);
        }else{
            getChildByTag(602)->setPosition(getChildByTag(602)->getPosition().x+1,getChildByTag(602)->getPosition().y);
        }
    }
    if(NULL!=getChildByTag(603)){
        if(getChildByTag(603)->getPositionX()>1920){
            getChildByTag(603)->setPosition(-640,360);
        }
        getChildByTag(603)->setPosition(getChildByTag(603)->getPosition().x+1,getChildByTag(603)->getPosition().y);
    }
}
