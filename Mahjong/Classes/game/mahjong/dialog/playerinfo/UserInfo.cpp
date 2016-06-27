#include "game/mahjong/dialog/playerinfo/UserInfo.h"
#include "game/mahjong/dialog/playerinfo/NickNameDialog.h"
#include "game/mahjong/dialog/playerinfo/HeadImageDialog.h"
#include "game/mahjong/dialog/playerinfo/GenderDialog.h"
#include "userdata/UserData.h"
#include "game/utils/Chinese.h"
#include "image/UrlImageMannger.h"
#include "game/mahjong/lobby/LobbyScene.h"

bool UserInfo::init(){
    if (!Layer::init()){
        return false;
    }
    showUserInfo();
    return true;
}

void UserInfo::onEnter(){
    Layer::onEnter();
    changeGenderListener = EventListenerCustom::create(MSG_CHANGE_GENDER_RESP, [=](EventCustom* event){
        char* buf = static_cast<char*>(event->getUserData());
        std::string result = buf;
        if (result == "1"){
            updateGender();
            if(NULL!=getChildByTag(123)){
                getChildByTag(123)->removeFromParent();
            }
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(changeGenderListener, 1);
    
}


void UserInfo::onExit(){
    Layer::onExit();
    _eventDispatcher->removeEventListener(changeGenderListener);
}

void UserInfo::showUserInfo(){
    auto headBg = Sprite::create("playerinfo/head_bg.png");
    headBg->setPosition(415,350);
    addChild(headBg);
    
    auto headImage =  Sprite::create();
    headImage->setTag(1000);
    headImage->setPosition(415,380);
    headImage->setScale(1.9f);
    headImage->setTexture(UserData::getInstance()->getPicture());
    addChild(headImage);
    
    auto itemImage = MenuItemImage::create("playerinfo/head_iamge_edit_1.png","playerinfo/head_iamge_edit_2.png",
                                           CC_CALLBACK_0(UserInfo::editHeadImage,this));
    Menu* myMenu = Menu::create(itemImage,NULL);
    myMenu->setPosition(415,253);
    addChild(myMenu);
    
    auto input_bg_1 = Scale9Sprite::create("common/input_box_bg.png");
    input_bg_1->setContentSize(Size(430,81));
    input_bg_1->setPosition(760, 445);
    addChild(input_bg_1);
    auto zhanghao = Sprite::create("playerinfo/account_text.png");
    zhanghao->setPosition(620,445);
    addChild(zhanghao);
    Label* accountLabel = Label::create(UserData::getInstance()->getUserName(), "arial", 30);
    accountLabel->setColor(Color3B(93,172,221));
    accountLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    accountLabel->setPosition(680, 445);
    addChild(accountLabel);
    Sprite* account_icon = Sprite::create("playerinfo/account_iocn.png");
    account_icon->setPosition(935, 445);
    addChild(account_icon);
    
    
    auto input_bg_2 = Scale9Sprite::create("common/input_box_bg.png");
    input_bg_2->setContentSize(Size(430, 81));
    input_bg_2->setPosition(760, 350);
    addChild(input_bg_2);
    auto nicheng = Sprite::create("playerinfo/nickname_text.png");
    nicheng->setPosition(620, 350);
    addChild(nicheng);
    nickNameLabel = Label::create(UserData::getInstance()->getNickName(), "arial", 30);
    nickNameLabel->setColor(Color3B(93, 172, 221));
    nickNameLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    nickNameLabel->setPosition(680, 350);
    addChild(nickNameLabel);
    auto editBtn1 = MenuItemImage::create("playerinfo/edit_btn_1.png", "playerinfo/edit_btn_2.png",
                                          CC_CALLBACK_1(UserInfo::menuBtnClick,this));
    editBtn1->setTag(0);
    changeNickName = Menu::create(editBtn1, NULL);
    changeNickName->setPosition(935, 350);
    addChild(changeNickName);
    if (UserData::getInstance()->isChangeName()){
        changeNickName->setVisible(false);
    }
    auto input_bg_3 = Scale9Sprite::create("common/input_box_bg.png");
    input_bg_3->setContentSize(Size(430, 81));
    input_bg_3->setPosition(760, 260);
    addChild(input_bg_3);
    auto gender = Sprite::create("playerinfo/gender_text.png");
    gender->setPosition(620, 260);
    addChild(gender);
    std::string gen = UserData::getInstance()->getGender() == 0 ? "playerinfo/female.png" : "playerinfo/male.png";
    playerGender = Sprite::create(gen);
    playerGender->setPosition(755,260);
    addChild(playerGender);
    auto editBtn2 = MenuItemImage::create("playerinfo/edit_btn_1.png", "playerinfo/edit_btn_2.png",
                                          CC_CALLBACK_1(UserInfo::menuBtnClick, this));
    editBtn2->setTag(1);
    Menu* menu2 = Menu::create(editBtn2, NULL);
    menu2->setPosition(935, 260);
    addChild(menu2);
    
    //diamond
    auto diamond_bg = Sprite::create("common/room_info_bg.png");
    diamond_bg->setPosition(410, 165);
    addChild(diamond_bg);
    auto diamond_icon = Sprite::create("common/diamond_icon.png");
    diamond_icon->setPosition(355, 160);
    addChild(diamond_icon);
    auto diamondNum = LabelAtlas::create(cocos2d::String::createWithFormat("%d", UserData::getInstance()->getDiamond())->_string,
                                         "playerinfo/player_info_num.png", 13, 19, '0');
    diamondNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    diamondNum->setPosition(380, 165);
    addChild(diamondNum);
    
    //lock diamond
    auto lock_diamond_bg = Scale9Sprite::create("common/room_info_bg.png");
    lock_diamond_bg->setContentSize(Size(120, 47));
    lock_diamond_bg->setPosition(560, 165);
    this->addChild(lock_diamond_bg);
    auto lock_diamond_icon = Sprite::create("common/lock_diamond_icon.png");
    lock_diamond_icon->setPosition(525, 160);
    addChild(lock_diamond_icon);
    auto lockDiamondNum = LabelAtlas::create(cocos2d::String::createWithFormat("%d", UserData::getInstance()->getLockDiamond())->_string,
                                             "playerinfo/player_info_num.png", 13, 19, '0');
    lockDiamondNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    lockDiamondNum->setPosition(550, 165);
    addChild(lockDiamondNum);
    
    //gold
    auto gold_bg = Sprite::create("common/room_info_bg.png");
    gold_bg->setPosition(715, 165);
    addChild(gold_bg);
    auto gold_icon = Sprite::create("common/gold_icon.png");
    gold_icon->setPosition(660, 165);
    addChild(gold_icon);
    auto goldNum = LabelAtlas::create(cocos2d::String::createWithFormat("%d", UserData::getInstance()->getGold())->_string,
                                      "playerinfo/player_info_num.png", 13, 19, '0');
    goldNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    goldNum->setPosition(685, 165);
    addChild(goldNum);
    
    //lequan
    auto lequan_bg = Sprite::create("common/room_info_bg.png");
    lequan_bg->setPosition(900, 165);
    this->addChild(lequan_bg);
    auto lequan_icon = Sprite::create("common/lequan_icon.png");
    lequan_icon->setPosition(845, 165);
    this->addChild(lequan_icon);
    auto lequanNum = LabelAtlas::create(cocos2d::String::createWithFormat("%d", UserData::getInstance()->getTicket())->_string,
                                        "playerinfo/player_info_num.png", 13, 19, '0');
    lequanNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    lequanNum->setPosition(870, 165);
    this->addChild(lequanNum);
}

void UserInfo::editHeadImage(){
    HeadImageDialog* headImageDialog = HeadImageDialog::create();
    addChild(headImageDialog);
    //    UrlImageMannger::getInstance()->uploadImage2Server(CallFunc::create([=](){
    //
    //
    //    }));
}


void UserInfo::menuBtnClick(Ref* ref){
    MenuItemImage* image = (MenuItemImage*) ref;
    if (image->getTag() == 0){
        NickNameDialog* dialog = NickNameDialog::create();
        addChild(dialog);
    }if (image->getTag() == 1){
        GenderDialog* dialog = GenderDialog::create();
        dialog->setTag(123);
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
    ((Sprite*)getChildByTag(1000))->setTexture(UserData::getInstance()->getPicture());
}