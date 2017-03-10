#include "mahjong/friend/FriendRoom.h"
#include "mahjong/lobby/LobbyScene.h"
#include "server/NetworkManage.h"
#include "mahjong/state/GameData.h"



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
    dialog_bg->setPosition(640,350);
    addChild(dialog_bg);
    
    
    auto roomTitle = Sprite::create("friend/open_room_title.png");
    roomTitle->setPosition(640,620);
    addChild(roomTitle);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(FriendRoom::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(980, 570);
    addChild(closeMenu);
    
    
    auto roomInfo = Sprite::create("friend/qiaoma_hua_di.png");
    roomInfo->setPosition(640,500);
    addChild(roomInfo);
    
    
    auto kaiFangJuShu = Sprite::create("friend/kai_fang_ju_shu_bg.png");
    kaiFangJuShu->setPosition(640,420);
    addChild(kaiFangJuShu);
    
    auto fangka8 = MenuItemImage::create("friend/select_box_normal.png","friend/select_box_normal.png",CC_CALLBACK_0(FriendRoom::selectFangka8, this));
    auto fangka8Menu = Menu::create(fangka8,NULL);
    fangka8Menu->setPosition(330,420);
    addChild(fangka8Menu);
    
    auto select8 = Sprite::create("friend/icon_right.png");
    select8->setTag(1024);
    select8->setPosition(330,420);
    select8->setVisible(true);
    addChild(select8);
    
    auto kaiju8 = Sprite::create("friend/8_ju.png");
    kaiju8->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    kaiju8->setPosition(360,420);
    addChild(kaiju8);
    
    
    auto fangka4 = MenuItemImage::create("friend/select_box_normal.png","friend/select_box_normal.png","friend/select_box_gray.png",CC_CALLBACK_0(FriendRoom::selectFangka4, this));
    auto fangka4Menu = Menu::create(fangka4,NULL);
    fangka4Menu->setPosition(555,420);
    addChild(fangka4Menu);
    
    auto select4 = Sprite::create("friend/icon_right.png");
    select4->setTag(1025);
    select4->setPosition(555,420);
    select4->setVisible(false);
    addChild(select4);
    
    auto kaiju4 = Sprite::create("friend/4_ju.png");
    kaiju4->setPosition(580,420);
    kaiju4->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(kaiju4);
    
    auto fangka16 = MenuItemImage::create("friend/select_box_normal.png","friend/select_box_normal.png","friend/select_box_gray.png",CC_CALLBACK_0(FriendRoom::selectFangka16, this));
    auto fangka16Menu = Menu::create(fangka16,NULL);
    fangka16Menu->setPosition(785,420);
    addChild(fangka16Menu);
    
    auto select16 = Sprite::create("friend/icon_right.png");
    select16->setTag(1026);
    select16->setPosition(785,420);
    select16->setVisible(false);
    addChild(select16);
    
    auto kaiju16 = Sprite::create("friend/16_ju.png");
    kaiju16->setPosition(810,420);
    kaiju16->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(kaiju16);
    
    auto xuanze = Sprite::create("friend/xuan_ze_ju_shu.png");
    xuanze->setPosition(640,302);
    addChild(xuanze);
    
    auto leziwu = MenuItemImage::create("friend/select_box_normal.png","friend/select_box_normal.png",CC_CALLBACK_0(FriendRoom::selectWulezi, this));
    auto leziwuMenu = Menu::create(leziwu,NULL);
    leziwuMenu->setPosition(330,332);
    addChild(leziwuMenu);
    
    auto leziwuImg = Sprite::create("friend/icon_right.png");
    leziwuImg->setTag(2024);
    leziwuImg->setPosition(330,332);
    leziwuImg->setVisible(true);
    addChild(leziwuImg);
    
    auto leziwuInfo = Sprite::create("friend/wu_le_zi.png");
    leziwuInfo->setPosition(360,332);
    leziwuInfo->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(leziwuInfo);
    
    
    auto lezi40 = MenuItemImage::create("friend/select_box_normal.png","friend/select_box_normal.png","friend/select_box_gray.png",CC_CALLBACK_0(FriendRoom::selectLezi, this));
    auto lezi40Menu = Menu::create(lezi40,NULL);
    lezi40Menu->setPosition(655,332);
    addChild(lezi40Menu);
    
    auto lezi40Img = Sprite::create("friend/icon_right.png");
    lezi40Img->setTag(2025);
    lezi40Img->setPosition(655,332);
    lezi40Img->setVisible(false);
    addChild(lezi40Img);
    
    auto lezi40Info = Sprite::create("friend/40_le_zi.png");
    lezi40Info->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    lezi40Info->setPosition(680,332);
    addChild(lezi40Info);
    
    
    auto wukaibao = MenuItemImage::create("friend/select_box_normal.png","friend/select_box_normal.png",CC_CALLBACK_0(FriendRoom::selectWukaibao, this));
    auto wukaibaoMenu = Menu::create(wukaibao,NULL);
    wukaibaoMenu->setPosition(330,267);
    addChild(wukaibaoMenu);
    
    auto selectWukaibao = Sprite::create("friend/icon_right.png");
    selectWukaibao->setTag(3024);
    selectWukaibao->setPosition(330,267);
    selectWukaibao->setVisible(false);
    addChild(selectWukaibao);
    
    auto wukaibaoIcon = Sprite::create("friend/wu_kaibao.png");
    wukaibaoIcon->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    wukaibaoIcon->setPosition(360,267);
    addChild(wukaibaoIcon);
    
    
    auto mo2chong3 = MenuItemImage::create("friend/select_box_normal.png","friend/select_box_normal.png","friend/select_box_gray.png",CC_CALLBACK_0(FriendRoom::select2mo3chong, this));
    auto mo2chong3Menu = Menu::create(mo2chong3,NULL);
    mo2chong3Menu->setPosition(655,267);
    addChild(mo2chong3Menu);
    
    auto selectmo2chong3 = Sprite::create("friend/icon_right.png");
    selectmo2chong3->setTag(3025);
    selectmo2chong3->setPosition(655,267);
    selectmo2chong3->setVisible(false);
    addChild(selectmo2chong3);

    auto mo2chong3Icon = Sprite::create("friend/2mo_3chong.png");
    mo2chong3Icon->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    mo2chong3Icon->setPosition(680,267);
    addChild(mo2chong3Icon);
    
    auto fangZhuText = Sprite::create("friend/fang_zhu_jiang_li.png");
    fangZhuText->setPosition(580,205);
    addChild(fangZhuText);
    
    auto lequan = Sprite::create("common/lequan_icon.png");
    lequan->setPosition(660,205);
    addChild(lequan);
    
    auto leX = Sprite::create("friend/fangzhu_x.png");
    leX->setPosition(695,207);
    addChild(leX);
    
    LabelAtlas* lequanNum = LabelAtlas::create(GAMEDATA::getInstance()->getFangzhuLequan(),"shop/prop_num.png",21,28,'0');
    lequanNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    lequanNum->setPosition(705,207);
    addChild(lequanNum);

    
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
