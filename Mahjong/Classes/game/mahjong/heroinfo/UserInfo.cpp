#include "game/mahjong/heroinfo/UserInfo.h"
#include "game/mahjong/heroinfo/NickNameDialog.h"
#include "game/mahjong/heroinfo/HeadImageDialog.h"
#include "game/mahjong/widget/HeadImage.hpp"
#include "game/mahjong/lobby/LobbyScene.h"
#include "game/mahjong/splash/SplashScene.h"
#include "payment/android/CallAndroidMethod.h"
#include "game/utils/Chinese.h"
#include "userdata/UserData.h"


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
    
    auto input_bg_1 = Scale9Sprite::create("common/input_box_bg.png");
    input_bg_1->setContentSize(Size(430,81));
    input_bg_1->setPosition(760, 500);
    addChild(input_bg_1);
    auto zhanghao = Sprite::create("playerinfo/account_text.png");
    zhanghao->setPosition(620,500);
    addChild(zhanghao);
    Label* accountLabel = Label::create(UserData::getInstance()->getMarkId(), "arial", 30);
    accountLabel->setColor(Color3B(93,172,221));
    accountLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    accountLabel->setPosition(680, 500);
    addChild(accountLabel);
    Sprite* account_icon = Sprite::create("playerinfo/account_iocn.png");
    account_icon->setPosition(935, 500);
    addChild(account_icon);
    
    
    auto input_bg_2 = Scale9Sprite::create("common/input_box_bg.png");
    input_bg_2->setContentSize(Size(430, 81));
    input_bg_2->setPosition(760, 405);
    addChild(input_bg_2);
    auto nicheng = Sprite::create("playerinfo/nickname_text.png");
    nicheng->setPosition(620, 405);
    addChild(nicheng);
    nickNameLabel = Label::create(UserData::getInstance()->getNickName(), "arial", 30);
    nickNameLabel->setColor(Color3B(93, 172, 221));
    nickNameLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    nickNameLabel->setPosition(680, 405);
    addChild(nickNameLabel);
    auto editBtn1 = MenuItemImage::create("playerinfo/edit_btn_1.png", "playerinfo/edit_btn_2.png",
                                          CC_CALLBACK_1(UserInfo::menuBtnClick,this));
    editBtn1->setTag(0);
    changeNickName = Menu::create(editBtn1, NULL);
    changeNickName->setPosition(935, 405);
    addChild(changeNickName);
    if (UserData::getInstance()->isChangeName()){
        changeNickName->setVisible(false);
    }
    auto input_bg_3 = Scale9Sprite::create("common/input_box_bg.png");
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
    auto fangka_bg = Sprite::create("common/room_info_bg.png");
    fangka_bg->setPosition(400, 230);
    addChild(fangka_bg);
    auto fangka_icon = Sprite::create("mjitem/fangka_icon.png");
    fangka_icon->setPosition(345, 225);
    addChild(fangka_icon);
    auto fangkaNum = LabelAtlas::create(StringUtils::format("%d", UserData::getInstance()->getFangkaNum()),
                                         "playerinfo/player_info_num.png", 13, 19, '0');
    fangkaNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    fangkaNum->setPosition(370, 230);
    addChild(fangkaNum);
    
    //gold
    auto gold_bg = Sprite::create("common/room_info_bg.png");
    gold_bg->setPosition(615, 230);
    addChild(gold_bg);
    auto gold_icon = Sprite::create("common/gold_icon.png");
    gold_icon->setPosition(560, 230);
    addChild(gold_icon);
    auto goldNum = LabelAtlas::create(cocos2d::String::createWithFormat("%d", UserData::getInstance()->getGold())->_string,
                                      "playerinfo/player_info_num.png", 13, 19, '0');
    goldNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    goldNum->setPosition(585, 230);
    addChild(goldNum);
    
    //lequan
    auto lequan_bg = Sprite::create("common/room_info_bg.png");
    lequan_bg->setPosition(850, 230);
    this->addChild(lequan_bg);
    auto lequan_icon = Sprite::create("common/lequan_icon.png");
    lequan_icon->setPosition(795, 230);
    this->addChild(lequan_icon);
    auto lequanNum = LabelAtlas::create(cocos2d::String::createWithFormat("%d", UserData::getInstance()->getTicket())->_string,
                                        "playerinfo/player_info_num.png", 13, 19, '0');
    lequanNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    lequanNum->setPosition(820, 230);
    this->addChild(lequanNum);
    
    auto accountquit = MenuItemImage::create("playerinfo/quit_account_1.png","playerinfo/quit_account_2.png",CC_CALLBACK_0(UserInfo::cleanAccountRercord, this));
    auto qutiMenu = Menu::create(accountquit,NULL);
    qutiMenu->setPosition(640,160);
    addChild(qutiMenu);
}

void UserInfo::editHeadImage(){
    HeadImageDialog* headImageDialog = HeadImageDialog::create();
    addChild(headImageDialog);
}


void UserInfo::menuBtnClick(Ref* ref){
    MenuItemImage* image = (MenuItemImage*) ref;
    if (image->getTag() == 0){
        NickNameDialog* dialog = NickNameDialog::create();
        addChild(dialog);
    }
}

void UserInfo::updateNickname(){
    nickNameLabel->setString(UserData::getInstance()->getNickName());
    EventCustom ev(MSG_UPDATE_HERO_INFO);
    _eventDispatcher->dispatchEvent(&ev);
    if (UserData::getInstance()->isChangeName()){
        changeNickName->setVisible(false);
    }
}

void UserInfo::updateGender(){
    std::string gen = UserData::getInstance()->getGender() == 0 ? "playerinfo/female.png" : "playerinfo/male.png";
    playerGender->setTexture(gen);
}

void UserInfo::updateHeadImage(){
   ((HeadImage*)getChildByTag(1000))->updateImage();
}

void UserInfo::cleanAccountRercord(){
    CallAndroidMethod::getInstance()->clearWechatOpenId();
    Director::getInstance()->replaceScene(TransitionFade::create(1, SplashScene::createScene()));
}