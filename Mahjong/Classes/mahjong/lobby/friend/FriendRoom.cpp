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
    closeMenu->setPosition(1050, 605);
    addChild(closeMenu);
    
    auto roomline = Sprite::create("openroom/across_line.png");
    roomline->setPosition(640,385);
    addChild(roomline);
    
    auto  shangHai = Sprite::create("openroom/shang_hai_btn_1.png");
    shangHai->setPosition(303,514);
    addChild(shangHai);
    
    auto hongZhong = Sprite::create("openroom/hong_zhong_btn_2.png");
    hongZhong->setPosition(303,405);
    addChild(hongZhong);
    
    auto vertical = Sprite::create("openroom/vertical_line_1.png");
    vertical->setPosition(380,385);
    addChild(vertical);
    
    auto roomText = Sprite::create("openroom/shang_hai_text.png");
    roomText->setPosition(725,420);
    addChild(roomText);
    
    auto fangka8 = MenuItemImage::create("friend/select_box_normal.png","friend/select_box_normal.png",CC_CALLBACK_0(FriendRoom::selectFangka8, this));
    auto fangka8Menu = Menu::create(fangka8,NULL);
    fangka8Menu->setPosition(490,480);
    addChild(fangka8Menu);
    
    auto select8 = Sprite::create("friend/icon_right.png");
    select8->setTag(1024);
    select8->setPosition(490,480);
    select8->setVisible(true);
    addChild(select8);
    
    auto fangka4 = MenuItemImage::create("friend/select_box_normal.png","friend/select_box_normal.png","friend/select_box_gray.png",CC_CALLBACK_0(FriendRoom::selectFangka4, this));
    auto fangka4Menu = Menu::create(fangka4,NULL);
    fangka4Menu->setPosition(740,480);
    addChild(fangka4Menu);
    
    auto select4 = Sprite::create("friend/icon_right.png");
    select4->setTag(1025);
    select4->setPosition(740,480);
    select4->setVisible(false);
    addChild(select4);
    
    
    auto fangka16 = MenuItemImage::create("friend/select_box_normal.png","friend/select_box_normal.png","friend/select_box_gray.png",CC_CALLBACK_0(FriendRoom::selectFangka16, this));
    auto fangka16Menu = Menu::create(fangka16,NULL);
    fangka16Menu->setPosition(490,425);
    addChild(fangka16Menu);
    
    auto select16 = Sprite::create("friend/icon_right.png");
    select16->setTag(1026);
    select16->setPosition(490,425);
    select16->setVisible(false);
    addChild(select16);
    
    auto leziwu = MenuItemImage::create("friend/select_box_normal.png","friend/select_box_normal.png",CC_CALLBACK_0(FriendRoom::selectWulezi, this));
    auto leziwuMenu = Menu::create(leziwu,NULL);
    leziwuMenu->setPosition(490,360);
    addChild(leziwuMenu);
    
    auto leziwuImg = Sprite::create("friend/icon_right.png");
    leziwuImg->setTag(2024);
    leziwuImg->setPosition(490,360);
    leziwuImg->setVisible(true);
    addChild(leziwuImg);
    
    auto lezi40 = MenuItemImage::create("friend/select_box_normal.png","friend/select_box_normal.png","friend/select_box_gray.png",CC_CALLBACK_0(FriendRoom::selectLezi, this));
    auto lezi40Menu = Menu::create(lezi40,NULL);
    lezi40Menu->setPosition(740,360);
    addChild(lezi40Menu);
    
    auto lezi40Img = Sprite::create("friend/icon_right.png");
    lezi40Img->setTag(2025);
    lezi40Img->setPosition(740,360);
    lezi40Img->setVisible(false);
    addChild(lezi40Img);
    
    auto wukaibao = MenuItemImage::create("friend/select_box_normal.png","friend/select_box_normal.png",CC_CALLBACK_0(FriendRoom::selectWukaibao, this));
    auto wukaibaoMenu = Menu::create(wukaibao,NULL);
    wukaibaoMenu->setPosition(490,305);
    addChild(wukaibaoMenu);
    
    auto selectWukaibao = Sprite::create("friend/icon_right.png");
    selectWukaibao->setTag(3024);
    selectWukaibao->setPosition(490,305);
    selectWukaibao->setVisible(false);
    addChild(selectWukaibao);
    
    
    auto mo2chong3 = MenuItemImage::create("friend/select_box_normal.png","friend/select_box_normal.png","friend/select_box_gray.png",CC_CALLBACK_0(FriendRoom::select2mo3chong, this));
    auto mo2chong3Menu = Menu::create(mo2chong3,NULL);
    mo2chong3Menu->setPosition(740,305);
    addChild(mo2chong3Menu);
    
    auto selectmo2chong3 = Sprite::create("friend/icon_right.png");
    selectmo2chong3->setTag(3025);
    selectmo2chong3->setPosition(740,305);
    selectmo2chong3->setVisible(false);
    addChild(selectmo2chong3);
    
    auto fangZhuText = Sprite::create("friend/fang_zhu_jiang_li.png");
    fangZhuText->setPosition(580,175);
    addChild(fangZhuText);
    
    auto lequan = Sprite::create("common/lequan_icon.png");
    lequan->setPosition(660,175);
    addChild(lequan);
    
    auto leX = Sprite::create("friend/fangzhu_x.png");
    leX->setPosition(695,177);
    addChild(leX);
    
    LabelAtlas* lequanNum = LabelAtlas::create(GAMEDATA::getInstance()->getFangzhuLequan(),"shop/prop_num.png",21,28,'0');
    lequanNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    lequanNum->setPosition(705,177);
    addChild(lequanNum);
    
    auto openBtn = MenuItemImage::create("mjlobby/open_room_btn_img_1.png", "mjlobby/open_room_btn_img_2.png", CC_CALLBACK_0(FriendRoom::openRoom, this));
    auto openMenu = Menu::create(openBtn,NULL);
    openMenu->setPosition(640,120);
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
