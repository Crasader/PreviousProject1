#include "mahjong/lobby/friend/FriendRoom.h"
#include "mahjong/lobby/LobbyScene.h"
#include "server/NetworkManage.h"
#include "mahjong/common/state/GameData.h"
#include "mahjong/lobby/friend/hongzhong/HongZhongSelectLayer.hpp"
#include "mahjong/lobby/friend/shanghai/ShangHaiSelectLayer.hpp"
#include "mahjong/lobby/friend/chongming/ChongMingSelectLayer.hpp"


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
    shangHai->setPosition(215,535);
    addChild(shangHai);
    
    hongZhong = Sprite::create("openroom/hong_zhong_btn_2.png");
    hongZhong->setPosition(215,430);
    addChild(hongZhong);
    
    chongMing = Sprite::create("openroom/hong_zhong_btn_2.png");
    chongMing->setPosition(215,325);
    addChild(chongMing);
    
    vertical = Sprite::create("openroom/vertical_line_1.png");
    vertical->setPosition(322,355);
    addChild(vertical);
    
    
    /* 房间人数选择 */
    auto erLen4 = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(FriendRoom::select4People, this));
    auto siLenMenu = Menu::create(erLen4,NULL);
    siLenMenu->setPosition(455,305);
    addChild(siLenMenu);
    
    auto select4Peo = Sprite::create("openroom/circle_select.png");
    select4Peo->setTag(1010);
    select4Peo->setPosition(455,305);
    select4Peo->setVisible(true);
    addChild(select4Peo);
    
    auto erLen2 = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(FriendRoom::select2People, this));
    auto erLenMenu = Menu::create(erLen2,NULL);
    erLenMenu->setPosition(655,305);
    addChild(erLenMenu);
    
    auto select2Peo = Sprite::create("openroom/circle_select.png");
    select2Peo->setTag(1011);
    select2Peo->setPosition(655,305);
    select2Peo->setVisible(false);
    addChild(select2Peo);
    
    /* 房间局数选择 */
    auto fangka8 = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(FriendRoom::selectFangka8, this));
    auto fangka8Menu = Menu::create(fangka8,NULL);
    fangka8Menu->setPosition(455,230);
    addChild(fangka8Menu);
    
    auto select8 = Sprite::create("openroom/circle_select.png");
    select8->setTag(1024);
    select8->setPosition(455,230);
    select8->setVisible(true);
    addChild(select8);
    
    auto fangka4 = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(FriendRoom::selectFangka4, this));
    auto fangka4Menu = Menu::create(fangka4,NULL);
    fangka4Menu->setPosition(655,230);
    addChild(fangka4Menu);
    
    auto select4 = Sprite::create("openroom/circle_select.png");
    select4->setTag(1025);
    select4->setPosition(655,230);
    select4->setVisible(false);
    addChild(select4);
    
    auto fangka16 = MenuItemImage::create("openroom/select_box_normal_b.png","openroom/select_box_normal_b.png",CC_CALLBACK_0(FriendRoom::selectFangka16, this));
    auto fangka16Menu = Menu::create(fangka16,NULL);
    fangka16Menu->setPosition(845,230);
    addChild(fangka16Menu);
    
    auto select16 = Sprite::create("openroom/circle_select.png");
    select16->setTag(1026);
    select16->setPosition(845,230);
    select16->setVisible(false);
    addChild(select16);
    
    //开房消耗显示
    auto fangka = Label::createWithSystemFont(StringUtils::format("X%s",GAMEDATA::getInstance()->getKaiFangXiaoHao8().c_str()), "arial", 26);
    fangka->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    fangka->setColor(Color3B(124,37,7));
    fangka->setPosition(500,155);
    fangka->setTag(1314);
    addChild(fangka);
    auto xiaohao = Sprite::create("openroom/fang_fee_text.png");
    xiaohao->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    xiaohao->setTag(1315);
    xiaohao->setPosition(fangka->getPositionX()+fangka->getContentSize().width,157);
    addChild(xiaohao);
    
    
    ShangHaiSelectLayer* laye1 = ShangHaiSelectLayer::create();
    laye1->setTag(1000);
    addChild(laye1);
    
    HongZhongSelectLayer* laye2 = HongZhongSelectLayer::create();
    laye2->setVisible(false);
    laye2->setTag(1001);
    addChild(laye2);
    
    ChongMingSelectLayer* laye3 = ChongMingSelectLayer::create();
    laye3->setVisible(false);
    laye3->setTag(1002);
    addChild(laye3);
    
    
    
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
    
    //显示用户的日常习惯
    if(UserData::getInstance()->getLatelyMahjongType() == GameMahjongType::ShangHai){
        showShangHaiMahjong();
    }else if(UserData::getInstance()->getLatelyMahjongType() == GameMahjongType::HongZhong){
        showHongZhongMahjong();
    }
    if(UserData::getInstance()->getLatelyGameModel() == GameModel::TWOPLAYER){
        select2People();
    }else{
        select4People();
    }
    if(UserData::getInstance()->getLatelyGameJuShu()=="4"){
        selectFangka4();
    }else if(UserData::getInstance()->getLatelyGameJuShu()=="16"){
        selectFangka16();
    }else{
        selectFangka8();
    }
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
    if(chongMing->getBoundingBox().containsPoint(touch->getLocation())){
        showChongMingMahjong();
    }
}


void FriendRoom::showShangHaiMahjong(){
    selectLayerIndex = 0;
    shangHai->setTexture("openroom/shang_hai_btn_1.png");
    hongZhong->setTexture("openroom/hong_zhong_btn_2.png");
    chongMing->setTexture("openroom/chong_ming_btn_2.png");
    vertical->setTexture("openroom/vertical_line_1.png");
    if(NULL != getChildByTag(1000))
        getChildByTag(1000)->setVisible(true);
    if(NULL != getChildByTag(1001))
        getChildByTag(1001)->setVisible(false);
    if(NULL != getChildByTag(1002))
        getChildByTag(1002)->setVisible(false);
}

void FriendRoom::showHongZhongMahjong(){
    selectLayerIndex = 1;
    shangHai->setTexture("openroom/shang_hai_btn_2.png");
    hongZhong->setTexture("openroom/hong_zhong_btn_1.png");
    chongMing->setTexture("openroom/chong_ming_btn_2.png");
    vertical->setTexture("openroom/vertical_line_2.png");
    if(NULL != getChildByTag(1000))
        getChildByTag(1000)->setVisible(false);
    if(NULL != getChildByTag(1001))
        getChildByTag(1001)->setVisible(true);
    if(NULL != getChildByTag(1002))
        getChildByTag(1002)->setVisible(false);
}
void FriendRoom::showChongMingMahjong(){
    selectLayerIndex = 2;
    shangHai->setTexture("openroom/shang_hai_btn_2.png");
    hongZhong->setTexture("openroom/hong_zhong_btn_2.png");
    chongMing->setTexture("openroom/chong_ming_btn_1.png");
    vertical->setTexture("openroom/vertical_line_3.png");
    if(NULL != getChildByTag(1000))
        getChildByTag(1000)->setVisible(false);
    if(NULL != getChildByTag(1001))
        getChildByTag(1001)->setVisible(false);
    if(NULL != getChildByTag(1002))
        getChildByTag(1002)->setVisible(true);
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
    ((Label*)getChildByTag(1314))->setString(StringUtils::format("X%s",GAMEDATA::getInstance()->getKaiFangXiaoHao8().c_str()));
    getChildByTag(1315)->setPosition(getChildByTag(1314)->getPositionX()+getChildByTag(1314)->getContentSize().width,157);
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
    ((Label*)getChildByTag(1314))->setString(StringUtils::format("X%s",GAMEDATA::getInstance()->getKaiFangXiaoHao4().c_str()));
    getChildByTag(1315)->setPosition(getChildByTag(1314)->getPositionX()+getChildByTag(1314)->getContentSize().width,157);
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
    ((Label*)getChildByTag(1314))->setString(StringUtils::format("X%s",GAMEDATA::getInstance()->getKaiFangXiaoHao16().c_str()));
    getChildByTag(1315)->setPosition(getChildByTag(1314)->getPositionX()+getChildByTag(1314)->getContentSize().width,157);
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
            std::string dihua = ((ShangHaiSelectLayer*)getChildByTag(1000))->getDiHua();
            std::string lezi = ((ShangHaiSelectLayer*)getChildByTag(1000))->getLeizi();
            std::string fcy = ((ShangHaiSelectLayer*)getChildByTag(1000))->getFeiChangYin();
            std::string ifemsc = ((ShangHaiSelectLayer*)getChildByTag(1000))->getEmsc();
            std::string ifkb = ((ShangHaiSelectLayer*)getChildByTag(1000))->getKaibao();
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getOpenRoomCommand(ftype,dihua,lezi,fcy,ifkb,ifemsc,size));
        }
        
    }else if(selectLayerIndex == 1){
        std::string fanma = ((HongZhongSelectLayer*)getChildByTag(1001))->getFanMa();
        std::string difen = ((HongZhongSelectLayer*)getChildByTag(1001))->getDiFen();
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getEnterHongZhongCommand(ftype,fanma,difen,size));
    }
    else if(selectLayerIndex == 2){
        std::string dihua = ((ChongMingSelectLayer*)getChildByTag(1002))->getDiHua();
        std::string lezi = ((ChongMingSelectLayer*)getChildByTag(1002))->getLeizi();
        std::string fcy = ((ChongMingSelectLayer*)getChildByTag(1002))->getFeiChangYin();
        std::string ifkb = ((ChongMingSelectLayer*)getChildByTag(1002))->getKaibao();
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getCMOpenRoomCommand(ftype,dihua,lezi,fcy,ifkb,size));
    }
}

