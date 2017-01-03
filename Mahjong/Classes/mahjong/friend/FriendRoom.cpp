#include "mahjong/friend/FriendRoom.h"
#include "mahjong/lobby/LobbyScene.h"
#include "server/NetworkManage.h"



bool FriendRoom::init()
{
    if (!Layer::init())
    {
        return false;
    }
    MenuItem* item = MenuItem::create();
    item->setContentSize(Size(1280, 720));
    Menu* bg = Menu::create(item, NULL);
    this->addChild(bg);
    
    auto dialog_bg = Sprite::create("shop/first_chage_bg.png");
    dialog_bg->setScale(0.9f, 0.9f);
    dialog_bg->setPosition(640,350);
    addChild(dialog_bg);
    
    
    auto roomTitle = Sprite::create("friend/open_room_title.png");
    roomTitle->setPosition(640,590);
    addChild(roomTitle);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(FriendRoom::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(940, 545);
    addChild(closeMenu);
    
    
    auto roomInfo = Sprite::create("friend/qiaoma_hua_di.png");
    roomInfo->setPosition(640,475);
    addChild(roomInfo);
    
    auto xuanze = Sprite::create("friend/xuan_ze_ju_shu.png");
    xuanze->setPosition(640,335);
    addChild(xuanze);
    
    
    auto fangka8 = MenuItemImage::create("friend/select_box_normal.png","friend/select_box_normal.png",CC_CALLBACK_0(FriendRoom::selectFangka8, this));
    auto fangka8Menu = Menu::create(fangka8,NULL);
    fangka8Menu->setPosition(370,395);
    addChild(fangka8Menu);
    
    auto select8 = Sprite::create("friend/icon_right.png");
    select8->setTag(1024);
    select8->setPosition(370,395);
    select8->setVisible(true);
    addChild(select8);
    
    auto kaiju8 = Sprite::create("friend/8_ju.png");
    kaiju8->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    kaiju8->setPosition(400,395);
    addChild(kaiju8);
    
    
    auto fangka4 = MenuItemImage::create("friend/select_box_normal.png","friend/select_box_normal.png","friend/select_box_gray.png",CC_CALLBACK_0(FriendRoom::selectFangka4, this));
    auto fangka4Menu = Menu::create(fangka4,NULL);
    fangka4Menu->setPosition(635,395);
    addChild(fangka4Menu);
    
    auto select4 = Sprite::create("friend/icon_right.png");
    select4->setTag(1025);
    select4->setPosition(635,395);
    select4->setVisible(false);
    addChild(select4);
    
    auto kaiju4 = Sprite::create("friend/4_ju.png");
    kaiju4->setPosition(660,395);
    kaiju4->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(kaiju4);
    
    
    auto leziwu = MenuItemImage::create("friend/select_box_normal.png","friend/select_box_normal.png",CC_CALLBACK_0(FriendRoom::selectWulezi, this));
    auto leziwuMenu = Menu::create(leziwu,NULL);
    leziwuMenu->setPosition(370,335);
    addChild(leziwuMenu);
    
    auto leziwuImg = Sprite::create("friend/icon_right.png");
    leziwuImg->setTag(2024);
    leziwuImg->setPosition(370,335);
    leziwuImg->setVisible(true);
    addChild(leziwuImg);
    
    auto leziwuInfo = Sprite::create("friend/wu_le_zi.png");
    leziwuInfo->setPosition(400,335);
    leziwuInfo->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(leziwuInfo);
    
    
    auto lezi40 = MenuItemImage::create("friend/select_box_normal.png","friend/select_box_normal.png","friend/select_box_gray.png",CC_CALLBACK_0(FriendRoom::selectLezi, this));
    auto lezi40Menu = Menu::create(lezi40,NULL);
    lezi40Menu->setPosition(635,335);
    addChild(lezi40Menu);
    
    auto lezi40Img = Sprite::create("friend/icon_right.png");
    lezi40Img->setTag(2025);
    lezi40Img->setPosition(635,335);
    lezi40Img->setVisible(false);
    addChild(lezi40Img);
    
    auto lezi40Info = Sprite::create("friend/40_le_zi.png");
    lezi40Info->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    lezi40Info->setPosition(660,335);
    addChild(lezi40Info);
    
    
    auto wukaibao = MenuItemImage::create("friend/select_box_normal.png","friend/select_box_normal.png",CC_CALLBACK_0(FriendRoom::selectWukaibao, this));
    auto wukaibaoMenu = Menu::create(wukaibao,NULL);
    wukaibaoMenu->setPosition(370,275);
    addChild(wukaibaoMenu);
    
    auto selectWukaibao = Sprite::create("friend/icon_right.png");
    selectWukaibao->setTag(3024);
    selectWukaibao->setPosition(370,275);
    selectWukaibao->setVisible(false);
    addChild(selectWukaibao);
    
    auto wukaibaoIcon = Sprite::create("friend/wu_kaibao.png");
    wukaibaoIcon->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    wukaibaoIcon->setPosition(400,275);
    addChild(wukaibaoIcon);
    
    
    auto mo2chong3 = MenuItemImage::create("friend/select_box_normal.png","friend/select_box_normal.png","friend/select_box_gray.png",CC_CALLBACK_0(FriendRoom::select2mo3chong, this));
    auto mo2chong3Menu = Menu::create(mo2chong3,NULL);
    mo2chong3Menu->setPosition(635,275);
    addChild(mo2chong3Menu);
    
    auto selectmo2chong3 = Sprite::create("friend/icon_right.png");
    selectmo2chong3->setTag(3025);
    selectmo2chong3->setPosition(635,275);
    selectmo2chong3->setVisible(false);
    addChild(selectmo2chong3);

    auto mo2chong3Icon = Sprite::create("friend/2mo_3chong.png");
    mo2chong3Icon->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    mo2chong3Icon->setPosition(660,275);
    addChild(mo2chong3Icon);
    
    auto openBtn = MenuItemImage::create("mjlobby/open_room_btn_img_1.png", "mjlobby/open_room_btn_img_2.png", CC_CALLBACK_0(FriendRoom::openRoom, this));
    auto openMenu = Menu::create(openBtn,NULL);
    openMenu->setPosition(640,185);
    addChild(openMenu);
    
    return true;
}


void FriendRoom::onEnter(){
    Layer::onEnter();
    
}


void FriendRoom::onExit(){
    Layer::onExit();
    
}

void FriendRoom::openRoom(){
    std::string ftype = "1";//1表示8局，2表示4局
    std::string iflezi = "0";//0表示没有，1表示有
    std::string ifkb = "1";//0表示没有，1表示有
    std::string ifemsc = "0";//0表示没有，1表示有
    if(NULL != getChildByTag(1024)&& NULL != getChildByTag(1025)){
        if(getChildByTag(1024)->isVisible()){
            ftype = "1";
        }else{
            ftype = "2";
        }
    }
    if(NULL != getChildByTag(2024)&& NULL != getChildByTag(2025)){
        if(getChildByTag(2024)->isVisible()){
            iflezi = "0";
        }else{
            iflezi = "1";
        }
    }
    if(NULL != getChildByTag(3024)){
        if(getChildByTag(3024)->isVisible()){
            ifkb = "0";
        }else{
            ifkb = "1";
        }
    }
    if(NULL != getChildByTag(3025)){
        if(getChildByTag(3025)->isVisible()){
            ifemsc = "1";
        }else{
            ifemsc = "0";
        }
    }
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getOpenRoomCommand(ftype,iflezi,ifkb,ifemsc));
}



void FriendRoom::closeView(){
    removeFromParent();
}

void FriendRoom::selectFangka8(){
    if(NULL != getChildByTag(1024)){
        getChildByTag(1024)->setVisible(true);
    }
    if(NULL != getChildByTag(1025)){
        getChildByTag(1025)->setVisible(false);
    }
}

void FriendRoom::selectFangka4(){
    if(NULL != getChildByTag(1024)){
        getChildByTag(1024)->setVisible(false);
    }
    if(NULL != getChildByTag(1025)){
        getChildByTag(1025)->setVisible(true);
    }
}


void FriendRoom::selectWulezi(){
    if(NULL != getChildByTag(2024)){
        getChildByTag(2024)->setVisible(true);
    }
    if(NULL != getChildByTag(2025)){
        getChildByTag(2025)->setVisible(false);
    }
}


void FriendRoom::selectLezi(){
    if(NULL != getChildByTag(2024)){
        getChildByTag(2024)->setVisible(false);
    }
    if(NULL != getChildByTag(2025)){
        getChildByTag(2025)->setVisible(true);
    }
}


void FriendRoom::selectWukaibao(){
    if(NULL != getChildByTag(3024)){
        getChildByTag(3024)->setVisible(!getChildByTag(3024)->isVisible());
    }
}

void FriendRoom::select2mo3chong(){
    if(NULL != getChildByTag(3025)){
        getChildByTag(3025)->setVisible(!getChildByTag(3025)->isVisible());
    }}
