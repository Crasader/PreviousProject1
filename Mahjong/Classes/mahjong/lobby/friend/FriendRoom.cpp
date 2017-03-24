#include "mahjong/lobby/friend/FriendRoom.h"
#include "mahjong/lobby/LobbyScene.h"
#include "server/NetworkManage.h"
#include "mahjong/common/state/GameData.h"



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
    
    auto dialog_bg = Sprite::create("shop/shop_bg.png");
    dialog_bg->setPosition(640,350);
    addChild(dialog_bg);
    
    
    auto roomTitle = Sprite::create("friend/open_room_title.png");
    roomTitle->setPosition(640,650);
    addChild(roomTitle);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(FriendRoom::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(1050, 600);
    addChild(closeMenu);
    
    auto roomline = Sprite::create("openroom/across_line.png");
    roomline->setPosition(640,380);
    addChild(roomline);
    
    auto  shangHai = Sprite::create("openroom/shang_hai_btn_1.png");
    shangHai->setPosition(303,509);
    addChild(shangHai);
    
    auto hongZhong = Sprite::create("openroom/hong_zhong_btn_2.png");
    hongZhong->setPosition(303,400);
    addChild(hongZhong);
    
    auto vertical = Sprite::create("openroom/vertical_line_1.png");
    vertical->setPosition(380,380);
    addChild(vertical);
    
    auto roomText = Sprite::create("openroom/shang_hai_text.png");
    roomText->setPosition(725,415);
    addChild(roomText);
    
    auto fangka8 = MenuItemImage::create("friend/select_box_normal.png","friend/select_box_normal.png",CC_CALLBACK_0(FriendRoom::selectFangka8, this));
    auto fangka8Menu = Menu::create(fangka8,NULL);
    fangka8Menu->setPosition(330,420);
    addChild(fangka8Menu);
    
    auto select8 = Sprite::create("friend/icon_right.png");
    select8->setTag(1024);
    select8->setPosition(330,420);
    select8->setVisible(true);
    addChild(select8);

    
    
    auto fangka4 = MenuItemImage::create("friend/select_box_normal.png","friend/select_box_normal.png","friend/select_box_gray.png",CC_CALLBACK_0(FriendRoom::selectFangka4, this));
    auto fangka4Menu = Menu::create(fangka4,NULL);
    fangka4Menu->setPosition(555,420);
    addChild(fangka4Menu);
    
    auto select4 = Sprite::create("friend/icon_right.png");
    select4->setTag(1025);
    select4->setPosition(555,420);
    select4->setVisible(false);
    addChild(select4);

    
    auto fangka16 = MenuItemImage::create("friend/select_box_normal.png","friend/select_box_normal.png","friend/select_box_gray.png",CC_CALLBACK_0(FriendRoom::selectFangka16, this));
    auto fangka16Menu = Menu::create(fangka16,NULL);
    fangka16Menu->setPosition(785,420);
    addChild(fangka16Menu);
    
    auto select16 = Sprite::create("friend/icon_right.png");
    select16->setTag(1026);
    select16->setPosition(785,420);
    select16->setVisible(false);
    addChild(select16);

    auto openBtn = MenuItemImage::create("mjlobby/open_room_btn_img_1.png", "mjlobby/open_room_btn_img_2.png", CC_CALLBACK_0(FriendRoom::openRoom, this));
    auto openMenu = Menu::create(openBtn,NULL);
    openMenu->setPosition(640,150);
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
    std::string ftype = "1";//1表示8局，2表示4局，3表示16局
    std::string iflezi = "0";//0表示没有，1表示有
    std::string ifkb = "1";//0表示没有，1表示有
    std::string ifemsc = "0";//0表示没有，1表示有
    if(NULL != getChildByTag(1024)&& NULL != getChildByTag(1025)&& NULL != getChildByTag(1026)){
        if(getChildByTag(1025)->isVisible()){
            ftype = "2";
        }else if(getChildByTag(1026)->isVisible()){
            ftype = "3";
        }else{
            ftype = "1";
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
    if(NULL != getChildByTag(1026)){
        getChildByTag(1026)->setVisible(false);
    }
}

void FriendRoom::selectFangka4(){
    if(NULL != getChildByTag(1024)){
        getChildByTag(1024)->setVisible(false);
    }
    if(NULL != getChildByTag(1025)){
        getChildByTag(1025)->setVisible(true);
    }
    if(NULL != getChildByTag(1026)){
        getChildByTag(1026)->setVisible(false);
    }
}

void FriendRoom::selectFangka16(){
    if(NULL != getChildByTag(1024)){
        getChildByTag(1024)->setVisible(false);
    }
    if(NULL != getChildByTag(1025)){
        getChildByTag(1025)->setVisible(false);
    }
    if(NULL != getChildByTag(1026)){
        getChildByTag(1026)->setVisible(true);
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
