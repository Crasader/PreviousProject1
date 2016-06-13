#include "game/mahjong/dialog/shop/Redwallet.h"
#include "server/NetworkManage.h"
#include "game/loading/Loading.h"
#include "game/mahjong/state/GameData.h"
#include "game/mahjong/dialog/shop/LingHongbao.hpp"
#include "game/mahjong/dialog/shop/HongbaoPride.hpp"

bool Redwallet::init(){
    if (!Layer::init()){
        return false;
    }
    giveRedwalletLayer = NULL;
    getRedwalletLayer = NULL;
    tishiLayer = NULL;
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
    
    auto all_bg = Sprite::create("common/all_bg.jpg");
    all_bg->setPosition(640, 360);
    addChild(all_bg);
    
    auto dialog_bg = Sprite::create("shop/shop_bg.png");
    dialog_bg->setPosition(640,350);
    addChild(dialog_bg);
    
    auto title = Sprite::create("shop/redwallet_title.png");
    title->setPosition(654,650);
    addChild(title);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(Redwallet::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(1060, 610);
    addChild(closeMenu);
    
    if(GAMEDATA::getInstance()->getRedWalletRespData().needInit){
        drawDialog();
    }else{
        Loading* load = Loading::create(true);
        load->setTag(1001);
        addChild(load);
    }
    return true;
}

void Redwallet::onEnter(){
    Layer::onEnter();
    redWalletRespListener = EventListenerCustom::create(MSG_RED_WALLET_RESP_INFO, [=](EventCustom* event){
        if(NULL != getChildByTag(1001)){
            getChildByTag(1001)->removeFromParent();
        }
        drawDialog();
    });
    _eventDispatcher->addEventListenerWithFixedPriority(redWalletRespListener, 1);
    
    redWalletPushListener = EventListenerCustom::create(MSG_RECIVE_RED_WALLET_PSUH, [=](EventCustom* event){
        if(NULL != getChildByTag(1006)){
            getChildByTag(1006)->removeFromParent();
        }
        
    });
    _eventDispatcher->addEventListenerWithFixedPriority(redWalletPushListener, 1);
}

void Redwallet::onExit(){
    Layer::onExit();
    _eventDispatcher->removeEventListener(redWalletRespListener);
    _eventDispatcher->removeEventListener(redWalletPushListener);
}

void Redwallet::drawDialog(){
    
    
    //box1
    auto boxBg1 = Sprite::create("shop/red_box.png");
    boxBg1->setPosition(350,350);
    addChild(boxBg1);
    
    auto titlePiao1 = Sprite::create("shop/orange_title.png");
    titlePiao1->setPosition(350,552);
    addChild(titlePiao1);
    
    auto title1 = Sprite::create("shop/wallet_title_1.png");
    title1->setPosition(350,562);
    addChild(title1);
    
    auto jaingli = Sprite::create("shop/font_jiangli.png");
    jaingli->setPosition(350,470);
    addChild(jaingli);
    
    auto gold = Sprite::create("mjitem/gold_iocn.png");
    gold->setScale(0.8f);
    gold->setPosition(270,395);
    addChild(gold);
    
    LabelAtlas* goldNum = LabelAtlas::create(cocos2d::String::createWithFormat("%s",GAMEDATA::getInstance()->getRedWalletRespData().gold.c_str())->_string,"shop/prop_num.png",21,28,'0');
    goldNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    goldNum->setPosition(300,395);
    goldNum->setScale(0.9);
    addChild(goldNum);
    
    auto goldText = Sprite::create("shop/gold_text.png");
    goldText->setPosition(425,395);
    addChild(goldText);
    
    auto lequan = Sprite::create("mjitem/lequan_icon.png");
    lequan->setScale(0.8f);
    lequan->setPosition(270,335);
    addChild(lequan);
    
    LabelAtlas* lequanNum = LabelAtlas::create(cocos2d::String::createWithFormat("%s",GAMEDATA::getInstance()->getRedWalletRespData().lequan.c_str())->_string,"shop/prop_num.png",21,28,'0');
    lequanNum->setPosition(300,335);
    lequanNum->setScale(0.9);
    lequanNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(lequanNum);
    
    auto lequanText = Sprite::create("shop/lequan_text.png");
    lequanText->setPosition(425,335);
    addChild(lequanText);
    
    auto diamond = Sprite::create("mjitem/diamond.png");
    diamond->setPosition(270,275);
    diamond->setScale(0.8f);
    addChild(diamond);
    
    LabelAtlas* diamondNum = LabelAtlas::create(cocos2d::String::createWithFormat("%s",GAMEDATA::getInstance()->getRedWalletRespData().diamond.c_str())->_string,"shop/prop_num.png",21,28,'0');
    diamondNum->setPosition(300,275);
    diamondNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    diamondNum->setScale(0.9);
    addChild(diamondNum);
    
    auto diamondText = Sprite::create("shop/bangzhuan_text.png");
    diamondText->setPosition(425,275);
    addChild(diamondText);
    
    auto btnImage1 = MenuItemImage::create("shop/get_wallet_1.png","shop/get_wallet_2.png",CC_CALLBACK_0(Redwallet::getRedwallet,this));
    Menu* mymenu1 = Menu::create(btnImage1,NULL);
    mymenu1->setPosition(350,170);
    addChild(mymenu1);
    
    // box2
    auto boxBg2 = Sprite::create("shop/red_box.png");
    boxBg2->setPosition(640,350);
    addChild(boxBg2);
    
    auto titlePiao2 = Sprite::create("shop/orange_title.png");
    titlePiao2->setPosition(640,552);
    addChild(titlePiao2);
    
    auto title2 = Sprite::create("shop/new_red_wallet.png");
    title2->setPosition(640,562);
    addChild(title2);
    
    auto text2 = Sprite::create("shop/hit_info_1.png");
    text2->setPosition(640,465);
    addChild(text2);
    
    LabelAtlas* goldNum2 = LabelAtlas::create(cocos2d::String::createWithFormat("%s",GAMEDATA::getInstance()->getRedWalletRespData().gold2.c_str())->_string,"shop/prop_num.png",21,28,'0');
    goldNum2->setPosition(580,375);
    goldNum2->setScale(0.9f);
    goldNum2->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(goldNum2);
    
    auto goldText2 = Sprite::create("shop/gold_text.png");
    goldText2->setPosition(690,375);
    addChild(goldText2);
    
    
    LabelAtlas* lequanNum2 = LabelAtlas::create(cocos2d::String::createWithFormat("%s",GAMEDATA::getInstance()->getRedWalletRespData().lequan2.c_str())->_string,"shop/prop_num.png",21,28,'0');
    lequanNum2->setPosition(580,335);
    lequanNum2->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    lequanNum2->setScale(0.9f);
    addChild(lequanNum2);
    
    auto lequanText2 = Sprite::create("shop/gold_text.png");
    lequanText2->setPosition(690,335);
    addChild(lequanText2);
    
    
    LabelAtlas* diamondNum2 = LabelAtlas::create(cocos2d::String::createWithFormat("%s",GAMEDATA::getInstance()->getRedWalletRespData().diamond2.c_str())->_string,"shop/prop_num.png",21,28,'0');
    diamondNum2->setPosition(580,295);
    diamondNum2->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    diamondNum2->setScale(0.9f);
    addChild(diamondNum2);
    
    auto diamondText2 = Sprite::create("shop/gold_text.png");
    diamondText2->setPosition(690,295);
    addChild(diamondText2);
    
    auto extra_text = Sprite::create("shop/fahongbaokedejaingli.png");
    extra_text->setPosition(640,235);
    addChild(extra_text);
    
    auto btnImage2 = MenuItemImage::create("shop/free_red_wallet_1.png","shop/free_red_wallet_2.png",CC_CALLBACK_0(Redwallet::giveRedwallet,this));
    Menu* mymenu2 = Menu::create(btnImage2,NULL);
    mymenu2->setPosition(640,170);
    addChild(mymenu2);
    
    
    //box3
    auto boxBg3 = Sprite::create("shop/red_box.png");
    boxBg3->setPosition(930,350);
    addChild(boxBg3);
    
    auto titlePiao3 = Sprite::create("shop/orange_title.png");
    titlePiao3->setPosition(930,552);
    addChild(titlePiao3);
    
    auto title3 = Sprite::create("shop/get_friend_text.png");
    title3->setPosition(930,562);
    addChild(title3);
    
    tableView = TableView::create(this, Size(260, 220));
    tableView->setAnchorPoint(Point::ANCHOR_MIDDLE);
    tableView->setDirection(ScrollView::Direction::VERTICAL);
    tableView->setPosition(800, 310);
    tableView->setDelegate(this);
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    this->addChild(tableView);
    tableView->reloadData();
    
    auto text3 = Sprite::create("shop/every_one_text.png");
    text3->setPosition(930,250);
    addChild(text3);
    
    auto btnImage3 = MenuItemImage::create("shop/linqujiangquan_1.png","shop/linqujiangquan_2.png");
    Menu* mymenu3 = Menu::create(btnImage3,NULL);
    mymenu3->setPosition(930,170);
    addChild(mymenu3);
    
}


void Redwallet::tableCellTouched(TableView* table, TableViewCell* cell)
{
    
    
}

Size Redwallet::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    return Size(260, 110);
}

TableViewCell* Redwallet::tableCellAtIndex(TableView *table, ssize_t idx)
{
    auto string = String::createWithFormat("%ld", idx);
    TableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new (std::nothrow) TableViewCell();
        cell->autorelease();
        Sprite* head = Sprite::create("gameview/head_image_1.png");
        head->setAnchorPoint(Vec2::ZERO);
        head->setPosition(Vec2(25, 5));
        cell->addChild(head);
        
        auto label = Label::createWithSystemFont(GAMEDATA::getInstance()->getRedWalletRespData().friends.at(idx).nickname, "arial", 30);
        label->setColor(Color3B(69,131,172));
        label->setAnchorPoint(Vec2::ZERO);
        label->setPosition(Vec2(125, 65));
        cell->addChild(label);
        cell->setName(GAMEDATA::getInstance()->getRedWalletRespData().friends.at(idx).pId);
        
        if(GAMEDATA::getInstance()->getRedWalletRespData().friends.at(idx).status == "0"){
            //TODO 可以领取
            
        }
    }else{
        //TODO
        
    }
    return cell;
}

ssize_t Redwallet::numberOfCellsInTableView(TableView *table)
{
    return GAMEDATA::getInstance()->getRedWalletRespData().friends.size();
}




void Redwallet::giveRedwallet(){
    
    HongbaoPride* pride = HongbaoPride::create();
    addChild(pride);
}


void Redwallet::getRedwallet(){
    LingHongbao* bao = LingHongbao::create();
    addChild(bao);
}

void Redwallet::getPushPride(){
    if(GAMEDATA::getInstance()->getRedWalletRespData().friends.size()>0){
        Loading* lod = Loading::create();
        lod->setTag(1006);
        addChild(lod);
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getRedWalletPushCommand());
    }
    
}

void Redwallet::closeView(){
    this->removeFromParent();
}

void Redwallet::closeTishiView(){
    if (NULL != tishiLayer){
        tishiLayer->removeFromParent();
        tishiLayer = NULL;
    }
    if (NULL == getRedwalletLayer){
        getRedwalletLayer = Layer::create();
        this->addChild(getRedwalletLayer);
        auto info = Label::create("helle world!", "Arial", 20);
        info->setPosition(480, 300);
        getRedwalletLayer->addChild(info);
    }
}

