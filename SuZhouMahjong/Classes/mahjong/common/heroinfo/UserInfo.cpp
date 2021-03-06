#include "mahjong/common/heroinfo/UserInfo.h"
#include "mahjong/common/heroinfo/HeadImageDialog.h"
#include "mahjong/common/widget/HeadImage.hpp"
#include "mahjong/common/utils/Chinese.h"
#include "mahjong/lobby/LobbyScene.h"
#include "mahjong/splash/SplashScene.h"
#include "userdata/UserData.h"
#include "wechat/android/CallAndroidMethod.h"


bool UserInfo::init(){
    if (!Layer::init()){
        return false;
    }
    showUserInfo();
    return true;
}

void UserInfo::onEnter(){
    Layer::onEnter();
    updateImageListener =  EventListenerCustom::create(MSG_UPDATE_HEAD_IMAGE, [=](EventCustom* event){
        updateHeadImage();
        updateGender();
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(updateImageListener, 1);
}


void UserInfo::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(updateImageListener);
}

void UserInfo::showUserInfo(){

    
    auto headBg = Sprite::create("playerinfo/head_bg.png");
    headBg->setPosition(415,405);
    addChild(headBg);
    
    auto headImage =  HeadImage::create(Size(180,180));
    headImage->setTag(1000);
    headImage->setPosition(415,435);
    addChild(headImage);
    
    auto itemImage = MenuItemImage::create("playerinfo/head_iamge_edit_1.png","playerinfo/head_iamge_edit_2.png",
                                           CC_CALLBACK_0(UserInfo::editHeadImage,this));
    Menu* myMenu = Menu::create(itemImage,NULL);
    myMenu->setPosition(415,308);
    addChild(myMenu);
    
    auto input_bg_1 = ui::Scale9Sprite::create("playerinfo/input_box_bg.png");
    input_bg_1->setContentSize(Size(430,81));
    input_bg_1->setPosition(760, 490);
    addChild(input_bg_1);
    auto zhanghao = Sprite::create("playerinfo/account_text.png");
    zhanghao->setPosition(620,490);
    addChild(zhanghao);
    Label* accountLabel = Label::createWithSystemFont(UserData::getInstance()->getMarkId(), "arial", 30);
    accountLabel->setColor(Color3B(127, 37, 7));
    accountLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    accountLabel->setPosition(680, 490);
    addChild(accountLabel);
    Sprite* account_icon = Sprite::create("playerinfo/account_iocn.png");
    account_icon->setPosition(935, 490);
    addChild(account_icon);
    
    
    auto input_bg_2 = ui::Scale9Sprite::create("playerinfo/input_box_bg.png");
    input_bg_2->setContentSize(Size(430, 81));
    input_bg_2->setPosition(760, 395);
    addChild(input_bg_2);
    auto nicheng = Sprite::create("playerinfo/nickname_text.png");
    nicheng->setPosition(620, 395);
    addChild(nicheng);
    auto nickNameLabel = Label::createWithSystemFont(UserData::getInstance()->getNickName(), "arial", 30);
    nickNameLabel->setColor(Color3B(127, 37, 7));
    nickNameLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    nickNameLabel->setPosition(680, 395);
    addChild(nickNameLabel);

    auto input_bg_3 = ui::Scale9Sprite::create("playerinfo/input_box_bg.png");
    input_bg_3->setContentSize(Size(430, 81));
    input_bg_3->setPosition(760, 315);
    addChild(input_bg_3);
    auto gender = Sprite::create("playerinfo/gender_text.png");
    gender->setPosition(620, 315);
    addChild(gender);
    std::string gen = UserData::getInstance()->getGender() == 0 ? "playerinfo/female.png" : "playerinfo/male.png";
    playerGender = Sprite::create(gen);
    playerGender->setPosition(755,315);
    addChild(playerGender);
    
    
    //fangka
    auto fangka_bg = Sprite::create("playerinfo/room_info_bg.png");
    fangka_bg->setPosition(420, 230);
    addChild(fangka_bg);
    auto fangka_icon = Sprite::create("common/fangka_icon.png");
    fangka_icon->setPosition(355, 227);
    addChild(fangka_icon);
    auto fangkaNum = Label::createWithSystemFont(StringUtils::format("%0.1f",UserData::getInstance()->getFangkaNum()),"Arial",25);
    fangkaNum->setColor(Color3B(127, 37, 7));
    fangkaNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    fangkaNum->setPosition(390, 230);
    addChild(fangkaNum);
    
    auto accountquit = MenuItemImage::create("playerinfo/quit_account_1.png","playerinfo/quit_account_2.png",CC_CALLBACK_0(UserInfo::cleanAccountRercord, this));
    auto qutiMenu = Menu::create(accountquit,NULL);
    qutiMenu->setPosition(640,170);
    addChild(qutiMenu);
}

void UserInfo::editHeadImage(){
    HeadImageDialog* headImageDialog = HeadImageDialog::create();
    addChild(headImageDialog);
}


void UserInfo::updateGender(){
    std::string gen = UserData::getInstance()->getGender() == 0 ? "playerinfo/female.png" : "playerinfo/male.png";
    playerGender->setTexture(gen);
}

void UserInfo::updateHeadImage(){
    ((HeadImage*)getChildByTag(1000))->updateImage();
}

void UserInfo::cleanAccountRercord(){
    UserData::getInstance()->setWxOpenId("unknow");
    UserData::getInstance()->setWxUnionid("unknow");
    Director::getInstance()->replaceScene(TransitionFade::create(1, SplashScene::createScene()));
}
