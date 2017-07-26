#include "mahjong/lobby/friend/FriendRoom.h"
#include "mahjong/lobby/LobbyScene.h"
#include "server/NetworkManage.h"
#include "mahjong/common/state/GameData.h"
#include "mahjong/lobby/friend/hongzhong/HongZhongSelectLayer.hpp"
#include "mahjong/lobby/friend/shanghai/ShangHaiSelectLayer.hpp"


bool FriendRoom::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    auto dialog_bg = Sprite::create("openroom/open_room_bg.png");
    dialog_bg->setPosition(640,350);
    addChild(dialog_bg);
    
    
    auto title = Sprite::create("openroom/open_room_title.png");
    title->setPosition(640,640);
    addChild(title);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(FriendRoom::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(1170, 660);
    addChild(closeMenu);
    
    
    
    shangHai = Sprite::create("openroom/shang_hai_btn_1.png");
    shangHai->setPosition(225,535);
    addChild(shangHai);
    
    hongZhong = Sprite::create("openroom/hong_zhong_btn_2.png");
    hongZhong->setPosition(225,430);
    addChild(hongZhong);
    
    vertical = Sprite::create("openroom/vertical_line_1.png");
    vertical->setPosition(332,355);
    addChild(vertical);
    //开房消耗显示
    
    auto fang8 = Label::createWithSystemFont(StringUtils::format("X%s",GAMEDATA::getInstance()->getKaiFangXiaoHao8().c_str()), "arial", 23);
    fang8->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    fang8->setColor(Color3B(124,37,7));
    fang8->setPosition(595,412);
    addChild(fang8);
    auto kuohao2 = Sprite::create("openroom/kuohao.png");
    kuohao2->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    kuohao2->setPosition(fang8->getPositionX()+fang8->getContentSize().width,412);
    addChild(kuohao2);
    
    auto fang4 = Label::createWithSystemFont(StringUtils::format("X%s",GAMEDATA::getInstance()->getKaiFangXiaoHao4().c_str()), "arial", 23);
    fang4->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    fang4->setColor(Color3B(124,37,7));
    fang4->setPosition(835,412);
    addChild(fang4);
    auto kuohao1 = Sprite::create("openroom/kuohao.png");
    kuohao1->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    kuohao1->setPosition(fang4->getPositionX()+fang4->getContentSize().width,412);
    addChild(kuohao1);
    
    auto fang16 = Label::createWithSystemFont(StringUtils::format("X%s",GAMEDATA::getInstance()->getKaiFangXiaoHao16().c_str()), "arial", 23);
    fang16->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    fang16->setColor(Color3B(124,37,7));
    fang16->setPosition(1100,412);
    addChild(fang16);
    
    auto kuohao3 = Sprite::create("openroom/kuohao.png");
    kuohao3->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    kuohao3->setPosition(fang16->getPositionX()+fang16->getContentSize().width,412);
    addChild(kuohao3);
    /* 房间人数选择 */
    
    auto erLen4 = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(FriendRoom::select4People, this));
    auto siLenMenu = Menu::create(erLen4,NULL);
    siLenMenu->setPosition(470,490);
    addChild(siLenMenu);
    
    auto select4Peo = Sprite::create("openroom/icon_right.png");
    select4Peo->setTag(1010);
    select4Peo->setPosition(470,490);
    select4Peo->setVisible(true);
    addChild(select4Peo);
    
    
    auto erLen2 = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(FriendRoom::select2People, this));
    auto erLenMenu = Menu::create(erLen2,NULL);
    erLenMenu->setPosition(705,495);
    addChild(erLenMenu);
    
    auto select2Peo = Sprite::create("openroom/icon_right.png");
    select2Peo->setTag(1011);
    select2Peo->setPosition(705,495);
    select2Peo->setVisible(false);
    addChild(select2Peo);
    
    
    /* 房间局数选择 */
    auto fangka8 = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(FriendRoom::selectFangka8, this));
    auto fangka8Menu = Menu::create(fangka8,NULL);
    fangka8Menu->setPosition(470,405);
    addChild(fangka8Menu);
    
    auto select8 = Sprite::create("openroom/icon_right.png");
    select8->setTag(1024);
    select8->setPosition(470,405);
    select8->setVisible(true);
    addChild(select8);
    
    auto fangka4 = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(FriendRoom::selectFangka4, this));
    auto fangka4Menu = Menu::create(fangka4,NULL);
    fangka4Menu->setPosition(705,405);
    addChild(fangka4Menu);
    
    auto select4 = Sprite::create("openroom/icon_right.png");
    select4->setTag(1025);
    select4->setPosition(705,405);
    select4->setVisible(false);
    addChild(select4);
    
    
    auto fangka16 = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(FriendRoom::selectFangka16, this));
    auto fangka16Menu = Menu::create(fangka16,NULL);
    fangka16Menu->setPosition(960,405);
    addChild(fangka16Menu);
    
    auto select16 = Sprite::create("openroom/icon_right.png");
    select16->setTag(1026);
    select16->setPosition(960,405);
    select16->setVisible(false);
    addChild(select16);
    
    
    ShangHaiSelectLayer* laye1 = ShangHaiSelectLayer::create();
    laye1->setTag(1000);
    addChild(laye1);
    
    HongZhongSelectLayer* laye2 = HongZhongSelectLayer::create();
    laye2->setVisible(false);
    laye2->setTag(1001);
    addChild(laye2);
    
    auto openBtn = MenuItemImage::create("openroom/open_room_btn_img_1.png", "openroom/open_room_btn_img_2.png", CC_CALLBACK_0(FriendRoom::openRoom, this));
    auto openMenu = Menu::create(openBtn,NULL);
    openMenu->setPosition(640,85);
    addChild(openMenu);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(FriendRoom::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(FriendRoom::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(FriendRoom::onTouchEnded, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener,this);
    
    return true;
}


void FriendRoom::onEnter(){
    Layer::onEnter();
    
}


void FriendRoom::onExit(){
    Layer::onExit();
    
}

bool FriendRoom::onTouchBegan(Touch *touch, Event  *event){
    return true;
}


void FriendRoom::onTouchMoved(Touch *touch, Event  *event){
    
    
}



void FriendRoom::onTouchEnded(Touch *touch, Event  *event){
    if(shangHai->getBoundingBox().containsPoint(touch->getLocation())){
        showShangHaiMahjong();
    }
    if(hongZhong->getBoundingBox().containsPoint(touch->getLocation())){
        showHongZhongMahjong();
    }
}


void FriendRoom::showShangHaiMahjong(){
    selectLayerIndex = 0;
    shangHai->setTexture("openroom/shang_hai_btn_1.png");
    hongZhong->setTexture("openroom/hong_zhong_btn_2.png");
    vertical->setTexture("openroom/vertical_line_1.png");
    if(NULL != getChildByTag(1000))
        getChildByTag(1000)->setVisible(true);
    if(NULL != getChildByTag(1001))
        getChildByTag(1001)->setVisible(false);
}

void FriendRoom::showHongZhongMahjong(){
    selectLayerIndex = 1;
    shangHai->setTexture("openroom/shang_hai_btn_2.png");
    hongZhong->setTexture("openroom/hong_zhong_btn_1.png");
    vertical->setTexture("openroom/vertical_line_2.png");
    if(NULL != getChildByTag(1000))
        getChildByTag(1000)->setVisible(false);
    if(NULL != getChildByTag(1001))
        getChildByTag(1001)->setVisible(true);
}
void FriendRoom::showChongMingMahjong(){
    
}

void FriendRoom::showNanHuiMahjong(){
    
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

void FriendRoom::select2People(){
    if(NULL != getChildByTag(1010)){
        getChildByTag(1010)->setVisible(false);
    }
    if(NULL != getChildByTag(1011)){
        getChildByTag(1011)->setVisible(true);
    }
}

void FriendRoom::select4People(){
    if(NULL != getChildByTag(1010)){
        getChildByTag(1010)->setVisible(true);
    }
    if(NULL != getChildByTag(1011)){
        getChildByTag(1011)->setVisible(false);
    }
}

void FriendRoom :: openRoom(){
    std::string size = "4";
    if(NULL != getChildByTag(1010)&& NULL != getChildByTag(1011)){
        if(getChildByTag(1011)->isVisible()){
            size = "2";
        }else{
            size = "4";
        }
    }
    
    std::string ftype = "1";//1表示8局，2表示4局，3表示16局
    if(NULL != getChildByTag(1024)&& NULL != getChildByTag(1025)&& NULL != getChildByTag(1026)){
        if(getChildByTag(1025)->isVisible()){
            ftype = "2";
        }else if(getChildByTag(1026)->isVisible()){
            ftype = "3";
        }else{
            ftype = "1";
        }
    }
    if(selectLayerIndex == 0){
        if(NULL != getChildByTag(1000)){
            std::string iflezi = ((ShangHaiSelectLayer*)getChildByTag(1000))->getLeizi();
            std::string ifemsc = ((ShangHaiSelectLayer*)getChildByTag(1000))->getEmsc();
            std::string ifkb = ((ShangHaiSelectLayer*)getChildByTag(1000))->getKaibao();
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getOpenRoomCommand(ftype,iflezi,ifkb,ifemsc,size));
        }
        
    }else if(selectLayerIndex == 1){
        std::string fanma = ((HongZhongSelectLayer*)getChildByTag(1001))->getFanMa();
        std::string difen = ((HongZhongSelectLayer*)getChildByTag(1001))->getDiFen();
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getEnterHongZhongCommand(ftype,fanma,difen,size));
    }
}

