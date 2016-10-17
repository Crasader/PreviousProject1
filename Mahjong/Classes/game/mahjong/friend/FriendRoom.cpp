#include "game/mahjong/friend/FriendRoom.h"
#include "game/mahjong/lobby/LobbyScene.h"
#include "server/NetworkManage.h"
#include "game/mahjong/widget/HeadImage.hpp"



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
    dialog_bg->setScale(0.9f);
    dialog_bg->setPosition(640,350);
    addChild(dialog_bg);
    
    auto  dialogBg = Sprite::create("friend/friend_room_bg.jpg");
    dialogBg->setPosition(640, 330);
    this->addChild(dialogBg);
    
    auto roomTitle = Sprite::create("friend/friend_room_title.png");
    roomTitle->setPosition(640,610);
    addChild(roomTitle);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(FriendRoom::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(1000, 570);
    addChild(closeMenu);
    
    //    auto qiao = Sprite::create("friend/qiaoma.png");
    //    qiao->setPosition(410,590);
    //    addChild(qiao);
    //
    //    auto dihua = Sprite::create("friend/1di1hua.png");
    //    dihua->setPosition(607,590);
    //    addChild(dihua);
    //
    //    auto xiao = Sprite::create("friend/xiaohao.png");
    //    xiao->setPosition(800,585);
    //    addChild(xiao);
    
    
    //    auto xuanze = Sprite::create("friend/xuanze_text.png");
    //    xuanze->setPosition(883,523);
    //    addChild(xuanze);
    
    auto openImage = MenuItemImage::create("friend/open_room_btn_1.png","friend/open_room_btn_2.png",CC_CALLBACK_0(FriendRoom::openRoom, this));
    auto enterImage = MenuItemImage::create("friend/enter_room_btn_1.png","friend/enter_room_btn_2.png",CC_CALLBACK_0(FriendRoom::openRoom, this));
    Menu* openBtn = Menu::create(openImage,enterImage,NULL);
    openBtn->alignItemsVerticallyWithPadding(20);
    openBtn->setPosition(730,300);
    addChild(openBtn);
    
    //    InviteCell* hero  = InviteCell::create(HeadImage::create(Size(90,90)), UserData::getInstance()->getNickName());
    //    hero->setPosition(348,488);
    //    addChild(hero);
    //
    //    //邀请3个好友
    //    for(int i=0;i<3;i++){
    //        inviters[i]=NULL;
    //    }
    //
    //    myTableView2 = TableView::create(this, Size(660, 350));
    //    myTableView2->setAnchorPoint(Point::ANCHOR_MIDDLE);
    //    myTableView2->setDirection(ScrollView::Direction::VERTICAL);
    //    myTableView2->setPosition(300, 50);
    //    myTableView2->setDelegate(this);
    //    myTableView2->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    //    addChild(myTableView2);
    //    myTableView2->reloadData();
    //
    //    if(GAMEDATA::getInstance()->getFriendList().friends.size()==0){
    //        Loading* load = Loading::create(true);
    //        load->setTag(100);
    //        addChild(load);
    //    }
    
    return true;
}


void FriendRoom::onEnter(){
    Layer::onEnter();
    friendLsitListener2 = EventListenerCustom::create(MSG_HERO_FRIEND_LIST, [=](EventCustom* event){
        updateFriendList();
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(friendLsitListener2, 1);
    
}


void FriendRoom::onExit(){
    Layer::onExit();
    _eventDispatcher->removeEventListener(friendLsitListener2);
}

void FriendRoom::tableCellTouched(TableView* table, TableViewCell* cell)
{
    log("cell touched at index: %ld", cell->getIdx());
    //    cell->getChildByTag(520)->setVisible(!cell->getChildByTag(520)->isVisible());
    //
    //    FriendListData data = GAMEDATA::getInstance()->getFriendList();
    //    FriendInfo info ;
    //    for(auto var : data.friends){
    //        if(var.poxiaoId ==  cell->getName()){
    //            info = var;
    //        }
    //    }
    //
    //    if (cell->getChildByTag(520)->isVisible()){
    //        inviteFriends.push_back(info);
    //        HeadImage* headImgae = HeadImage::createByImage(info.image, Size(90,90));
    //        InviteCell* sprite  = InviteCell::create(headImgae, info.nickname);
    //        sprite->setName(info.poxiaoId);
    //        addChild(sprite);
    //        for(int i=0;i<3;i++){
    //            if(inviters[i]==NULL){
    //                sprite->setPosition(468+120*i,488);
    //                inviters[i] =sprite;
    //                break;
    //            }
    //        }
    //    }
    //    else{
    //        vector<FriendInfo>::iterator it;
    //        for (it = inviteFriends.begin(); it != inviteFriends.end();)
    //        {
    //            if (it->poxiaoId == info.poxiaoId)
    //                it = inviteFriends.erase(it);
    //            else
    //                ++it;
    //        }
    //        for(int i=0;i<3;i++){
    //            if(inviters[i]!=NULL){
    //                if(inviters[i]->getName()==info.poxiaoId){
    //                    inviters[i]->removeFromParent();
    //                    inviters[i]=NULL;
    //                }
    //            }
    //        }
    //
    //    }
}

Size FriendRoom::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    return Size(660, 65);
}

TableViewCell* FriendRoom::tableCellAtIndex(TableView *table, ssize_t idx)
{
    auto string = String::createWithFormat("%ld", idx);
    TableViewCell *cell = table->dequeueCell();
    if (!cell) {
        //        cell = new (std::nothrow) TableViewCell();
        //        cell->autorelease();
        //        cell->setName(GAMEDATA::getInstance()->getFriendList().friends.at(idx).poxiaoId);
        //
        //        HeadImage* head = HeadImage::createByImage(GAMEDATA::getInstance()->getFriendList().friends.at(idx).pic,Size(90,90));
        //        head->setTag(500);
        //        head->setAnchorPoint(Vec2::ZERO);
        //        head->setScale(0.6f);
        //        head->setPosition(Vec2(5, 5));
        //        cell->addChild(head);
        //
        //        std::string nickname = GAMEDATA::getInstance()->getFriendList().friends.at(idx).nickname;
        //        auto label = Label::createWithSystemFont(nickname, "arial", 24);
        //        label->setTag(501);
        //        label->setColor(Color3B(69,131,172));
        //        label->setAnchorPoint(Vec2::ZERO);
        //        label->setPosition(Vec2(130, 25));
        //        cell->addChild(label);
        //
        //        Sprite* circle = Sprite::create("friend/offline_icon.png");
        //        circle->setPosition(350, 35);
        //        circle->setTag(502);
        //        cell->addChild(circle);
        //        Sprite* text = Sprite::create("friend/offline.png");
        //        text->setPosition(400,35);
        //        text->setTag(503);
        //        cell->addChild(text);
        //
        //        if(GAMEDATA::getInstance()->getFriendList().friends.at(idx).isOnLine){
        //            circle->setTexture("friend/online_icon.png");
        //            text->setTexture("friend/online.png");
        //        }
        //        auto box = Sprite::create("friend/select_box.png");
        //        box->setPosition(620,35);
        //        cell->addChild(box);
        //
        //        auto select = Sprite::create("friend/selected.png");
        //        select->setPosition(620,35);
        //        select->setTag(520);
        //        select->setVisible(false);
        //        cell->addChild(select);
    }else{
        //        cell->setName(GAMEDATA::getInstance()->getFriendList().friends.at(idx).poxiaoId);
        //        auto sprite1 = (HeadImage*)cell->getChildByTag(500);
        //        sprite1->updateImageByName(GAMEDATA::getInstance()->getFriendList().friends.at(idx).pic);
        //
        //        ((Label*)cell->getChildByTag(501))->setString(GAMEDATA::getInstance()->getFriendList().friends.at(idx).nickname);
        //        if(GAMEDATA::getInstance()->getFriendList().friends.at(idx).isOnLine){
        //            ((Sprite*)cell->getChildByTag(502))->setTexture("friend/online_icon.png");
        //        }else{
        //            ((Sprite*)cell->getChildByTag(502))->setTexture("friend/offline_icon.png");
        //        }
        //        if(GAMEDATA::getInstance()->getFriendList().friends.at(idx).isOnLine){
        //            ((Sprite*)cell->getChildByTag(503))->setTexture("friend/online.png");
        //        }else{
        //            ((Sprite*)cell->getChildByTag(503))->setTexture("friend/offline.png");
        //        }
        
    }
    return cell;
}

ssize_t FriendRoom::numberOfCellsInTableView(TableView *table)
{
    int size = GAMEDATA::getInstance()->getFriendList().friends.size();
    if (size < 0){
        size = 0;
    }
    return size;
}



void FriendRoom::openRoom(){
    std::string pid = "";
    for (int i = 0; i < inviteFriends.size(); i++){
        
        if (i == inviteFriends.size() - 1){
            pid += inviteFriends.at(i).poxiaoId;
        }
        else{
            pid += inviteFriends.at(i).poxiaoId + ",";
        }
    }
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getOpenRoomCommand(pid));
    this->removeFromParent();
}


void FriendRoom::closeView(){
    this->removeFromParent();
}

void FriendRoom::updateFriendList(){
    if(NULL != getChildByTag(100)){
        getChildByTag(100)->removeFromParent();
    }
    myTableView2->reloadData();
}