#include "game/mahjong/splash/SplashScene.h"
#include "game/mahjong/lobby/LobbyScene.h"
#include "game/mahjong/result/ResultLayer.h"
#include "game/mahjong/splash/register/UserRegister.h"
#include "game/mahjong/splash/register/FindPassword.h"
#include "server/NetworkManage.h"
#include "game/loading/Loading.h"
#include "game/mahjong/splash/LoadResource.hpp"
#include "game/mahjong/dialog/prompt/HintDialog.hpp"
#include "game/mahjong/splash/dropdownlist/DropDownListBox.h"
#include "game/mahjong/splash/dropdownlist/LoginMannger.h"



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
}


void SplashScene::drawLonginScene(){
    //add game bg to layer
    Sprite* splash_bg = Sprite::create("mainlogin/splah_bg_.png");
    splash_bg->setPosition(640,360);
    this->addChild(splash_bg, -1);
    
    auto lightOne = Sprite::create("mainlogin/splash_light_1.png");
    lightOne->setPosition(640,360);
    addChild(lightOne);
    lightOne->runAction(Repeat::create(Sequence::create(FadeTo::create(1.0f, 150),FadeTo::create(1.0f, 0), NULL), CC_REPEAT_FOREVER));
    
    auto lightTwo = Sprite::create("mainlogin/splash_light_2.png");
    lightTwo->setPosition(640,360);
    addChild(lightTwo);
    lightTwo->runAction(Repeat::create(Sequence::create(DelayTime::create(1.0f),FadeTo::create(1.0f, 150),FadeTo::create(1.0f, 0), NULL), CC_REPEAT_FOREVER));
    
    auto gameTitle = Sprite::create("mainlogin/splah_title.png");
    gameTitle->setPosition(875, 630);
    this->addChild(gameTitle);
    
    
    auto girlSprite = Sprite::create("mainlogin/girl_image.png");
    girlSprite->setPosition(220,360);
    addChild(girlSprite);
    //眨眼动画
    auto levelMidEye = Sprite::create();
    levelMidEye->setPosition(220,360);
    addChild(levelMidEye,2);
    levelMidEye->runAction(Repeat::create(Sequence::create(
                                                           CallFunc::create([=](){
        levelMidEye->setTexture("mainlogin/splash_eye_1.png");
    }),
                                                           DelayTime::create(2.0/24),
                                                           CallFunc::create([=](){
        levelMidEye->setTexture("mainlogin/splash_eye_2.png");
    }),
                                                           DelayTime::create(2.0/24),
                                                           CallFunc::create([=](){
        levelMidEye->setTexture("mainlogin/splash_eye_1.png");
    }),
                                                           DelayTime::create(2.0/24),
                                                           CallFunc::create([=](){
        levelMidEye->setTexture("");
    }),
                                                           DelayTime::create(96.0/24),
                                                           NULL), CC_REPEAT_FOREVER));
    
    auto shanghai = Sprite::create("mainlogin/splash_logo.png");
    shanghai->setPosition(420,120);
    addChild(shanghai);
    
    auto logoText = Sprite::create();
    logoText->setPosition(420, 120);
    addChild(logoText);
    auto animation2 = Animation::create();
    for( int j=1;j<5;j++)
    {
        std::string imageName = cocos2d::String::createWithFormat("mainlogin/splash_logo_%d.png",j)->_string;
        animation2->addSpriteFrameWithFile(imageName);
    }
    // should last 1 seconds. And there are 24 frames.
    animation2->setDelayPerUnit(3.0f / 24.0f);
    animation2->setRestoreOriginalFrame(true);
    auto action2 = Animate::create(animation2);
    logoText->runAction(Sequence::create(Repeat::create(Sequence::create(action2,DelayTime::create(48.0/24), NULL), CC_REPEAT_FOREVER), NULL));
    
    
    auto accountBg = Sprite::create("mainlogin/username_box.png");
    accountBg->setPosition(955, 475);
    addChild(accountBg);
    
    
    _editName = EditBox::create(Size(400, 81), Scale9Sprite::create());
    _editName->setPosition(Point(1010, 475));
    _editName->setFont("arial", 30);
    _editName->setTag(606);
    if (UserData::getInstance()->getPassword() != "unknow"){
        _editName->setText(UserData::getInstance()->getUserName().c_str());
    }
    _editName->setInputMode(EditBox::InputMode::SINGLE_LINE);
    _editName->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
    _editName->setDelegate(this);
    addChild(_editName,1);
    
    DropDownList* drop = DropDownList::create(Sprite::create(), Size(450,240),"splashCallBack");
    drop->setPosition(Point(508, 200));
    drop->setTouchAbleRect(_editName->getBoundingBox());
    addChild(drop,5);
    
    auto accountIcon = Sprite::create("mainlogin/password_box.png");
    accountIcon->setPosition(955, 350);
    this->addChild(accountIcon);
    
    _editPwd = EditBox::create(Size(400, 81), Scale9Sprite::create());
    _editPwd->setPosition(Point(1010, 352));
    _editPwd->setTag(607);
    _editPwd->setFont("arial", 30);
    if (UserData::getInstance()->getPassword() != "unknow"){
        _editPwd->setText(UserData::getInstance()->getPassword().c_str());
    }
    _editPwd->setInputFlag(EditBox::InputFlag::PASSWORD);
    _editPwd->setInputMode(EditBox::InputMode::SINGLE_LINE);
    _editPwd->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
    _editPwd->setDelegate(this);
    addChild(_editPwd,1);
    
    username_text = Sprite::create("mainlogin/username_text.png");
    username_text->setPosition(920, 475);
    addChild(username_text);
    password_text = Sprite::create("mainlogin/password_text.png");
    password_text->setPosition(920, 352);
    addChild(password_text);
    
    if (UserData::getInstance()->getUserName() != "unknow"&&UserData::getInstance()->getPassword() != "unknow"){
        password_text->setVisible(false);
        username_text->setVisible(false);
    }
    
    auto loginBtn = MenuItemImage::create("mainlogin/login_confirm.png", "mainlogin/login_confirm.png",
                                          CC_CALLBACK_0(SplashScene::loginByPass, this));
    auto visitorBtn = MenuItemImage::create("mainlogin/visitor_login_btn.png", "mainlogin/visitor_login_btn.png",
                                            CC_CALLBACK_0(SplashScene::loginByVisitor, this));
    auto loginMenu = Menu::create(loginBtn, visitorBtn, NULL);
    loginMenu->alignItemsHorizontallyWithPadding(5);
    loginMenu->setPosition(960, 228);
    this->addChild(loginMenu);
    
    auto confirmLight = Sprite::create("mainlogin/confirm_btn_light.png");
    confirmLight->setPosition(855,228);
    addChild(confirmLight);
    confirmLight->setOpacity(0);
    confirmLight->runAction(Repeat::create(Sequence::create(FadeTo::create(1.0f, 255),FadeTo::create(1.0f, 0), NULL), CC_REPEAT_FOREVER));
    
    auto bottom = Sprite::create("mainlogin/bottom_bg.png");
    bottom->setPosition(960, 94);
    addChild(bottom);
    
    auto registerBtn = MenuItemImage::create("mainlogin/register_btn.png", "mainlogin/register_btn.png",
                                             CC_CALLBACK_0(SplashScene::showUserRegister, this));
    auto registerMenu = Menu::create(registerBtn, NULL);
    registerMenu->setPosition(840, 94);
    this->addChild(registerMenu);
    
    auto findPwdBtn = MenuItemImage::create("mainlogin/find_pwd_btn.png", "mainlogin/find_pwd_btn.png",
                                            CC_CALLBACK_0(SplashScene::findbackPwd, this));
    auto findPwdMenu = Menu::create(findPwdBtn, NULL);
    findPwdMenu->setPosition(1080, 94);
    this->addChild(findPwdMenu);
}


void SplashScene::loginByPass(){
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
    //std::string userName = _editName->getText();
    //std::string password = _editPwd->getText();
    //if (UserData::getInstance()->getUserName() != "unknow"&&UserData::getInstance()->getPassword() != "unknow"){
    //	if (userName == ""&&password == ""){
    //		NetworkManage::getInstance()->sendMsg(
    //			JsonManage::getInstance()->getLoginCommmand(UserData::getInstance()->getUserName(), UserData::getInstance()->getPassword()));
    //	}
    //	else{
    //		NetworkManage::getInstance()->sendMsg(
    //			JsonManage::getInstance()->getLoginCommmand(userName, password));
    //	}
    //showLoading();
    //}
    //else{
    //	NetworkManage::getInstance()->sendMsg(JsonManage::getInstance()->getVisitorLoginCommand());
    //}
    showLoading();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getVisitorLoginCommand());
}


void SplashScene::setChangeNickName(std::string name,std::string pwd){
    username_text->setVisible(false);
    _editName->setText(name.c_str());
    _editPwd->setText(pwd.c_str());
}

void SplashScene::showUserRegister(){
    UserRegister* layer = UserRegister::create();
    this->addChild(layer,6);
}


void SplashScene::findbackPwd(){
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
            HintDialog* hint = HintDialog::create("用户名或者密码错误",false);
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
            HintDialog* hint = HintDialog::create("注册失败",false);
            addChild(hint,6);
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(registerRespListener, 1);
    
    //用户名下拉列表
    dropListListener = EventListenerCustom::create("splashCallBack", [=](EventCustom* event){
        setChangeNickName(GAMEDATA::getInstance()->getLoginAccPwd().account,GAMEDATA::getInstance()->getLoginAccPwd().password);
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(dropListListener, 1);
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
