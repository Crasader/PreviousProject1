#include "game/splash/SplashScene.h"
#include "game/mahjong/lobby/LobbyScene.h"
#include "game/mahjong/result/ResultLayer.h"
#include "game/mahjong/dialog/register/UserRegister.h"
#include "game/mahjong/dialog/register/FindPassword.h"
#include "server/NetworkManage.h"
#include "game/loading/Loading.h"

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
    //add all  plsit
    loadResource();
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
}


void SplashScene::drawLonginScene(){
    //add game bg to layer
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Sprite* splash_bg = Sprite::create("mainlogin/splah_bg_.jpg");
    splash_bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    this->addChild(splash_bg, -1);
    
    auto gameTitle = Sprite::create("mainlogin/splah_title.png");
    gameTitle->setPosition(875, 630);
    this->addChild(gameTitle);
    
    auto accountBg = Sprite::create("mainlogin/username_box.png");
    accountBg->setPosition(955, 475);
    this->addChild(accountBg);
    auto accountIcon = Sprite::create("mainlogin/password_box.png");
    accountIcon->setPosition(955, 350);
    this->addChild(accountIcon);
    
    _editName = EditBox::create(Size(400, 81), Scale9Sprite::create());
    _editName->setPosition(Point(1010, 475));
    _editName->setTag(0);
    _editName->setFont("arial", 30);
    if (UserData::getInstance()->getPassword() != "unknow"){
        _editName->setPlaceHolder(UserData::getInstance()->getUserName().c_str());
    }
    _editName->setDelegate(this);
    addChild(_editName);
    
    _editPwd = EditBox::create(Size(400, 81), Scale9Sprite::create());
    _editPwd->setPosition(Point(1010, 352));
    _editPwd->setTag(1);
    _editPwd->setFont("arial", 30);
    if (UserData::getInstance()->getPassword() != "unknow"){
        std::string star = "";
        for (int i = 0; i < UserData::getInstance()->getPassword().size(); i++){
            star += "*";
        }
        _editPwd->setPlaceHolder(star.c_str());
        
    }
    _editPwd->setInputFlag(EditBox::InputFlag::PASSWORD);
    _editPwd->setInputMode(EditBox::InputMode::SINGLE_LINE);
    _editPwd->setDelegate(this);
    addChild(_editPwd);
    
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
        else{
            //Ã· æ”√ªß◊¢≤·
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


void SplashScene::setChangeNickName(std::string name){
    
}

void SplashScene::showUserRegister(){
    UserRegister* layer = UserRegister::create();
    this->addChild(layer);
}


void SplashScene::findbackPwd(){
    FindPassword* pass = FindPassword::create();
    this->addChild(pass);
}


void SplashScene::loadResource(){
    //TODO
}


void  SplashScene::addCustomEventListener(){
    loginRespListener = EventListenerCustom::create(MSG_LOGIN_RESP, [=](EventCustom* event){
        char* buf = static_cast<char*>(event->getUserData());
        std::string result = buf;
        
        if (result == LOGIN_SUCCESS){
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getRoomListCommand("1"));
            NetworkManage::getInstance()->heartbeat();
        }
        else{
            //TODO
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(loginRespListener, 1);
    
    roomRespListener = EventListenerCustom::create(MSG_ROOM_LIST_RESP, [=](EventCustom* event){
        removeLoading();
        Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(roomRespListener, 1);
    
    reConnectAgain = EventListenerCustom::create(MSG_PLAYER_CONNECT_AGAIN, [=](EventCustom* event){
        NetworkManage::getInstance()->heartbeat();
        GAMEDATA::getInstance()->setIsRecover(true);
        Director::getInstance()->replaceScene(TransitionFade::create(0.12f, MjGameScene::create()));
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(reConnectAgain, 1);
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
    this->addChild(loadLayer);
}



void SplashScene::removeLoading(){
    //TODO
}



void SplashScene::editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox){
    if (editBox->getTag() == 0){
        username_text->setVisible(false);
    }
    if (editBox->getTag() == 1){
        password_text->setVisible(false);
    }
    
}

void SplashScene::editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox){
    
    
}

void SplashScene::editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text){
    
    
}

void SplashScene::editBoxReturn(cocos2d::extension::EditBox* editBox){
    
    
}
