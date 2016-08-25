#include "game/mahjong/friend/FriendRoom.h"
#include "game/mahjong/lobby/LobbyScene.h"
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
    
    
    auto  dialogBg = Sprite::create("friend/friend_room_bg.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(FriendRoom::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(980, 650);
    addChild(closeMenu);
    
    auto qiao = Sprite::create("friend/qiaoma.png");
    qiao->setPosition(410,590);
    addChild(qiao);
    
    auto dihua = Sprite::create("friend/1di1hua.png");
    dihua->setPosition(607,590);
    addChild(dihua);
    
    auto xiao = Sprite::create("friend/xiaohao.png");
    xiao->setPosition(800,585);
    addChild(xiao);
    
    
    auto xuanze = Sprite::create("friend/xuanze_text.png");
    xuanze->setPosition(883,523);
    addChild(xuanze);
    
    auto openImage = MenuItemImage::create("friend/open_room_btn.png","friend/open_room_btn.png",CC_CALLBACK_0(FriendRoom::openRoom, this));
    Menu* openBtn = Menu::create(openImage,NULL);
    openBtn->setPosition(883,470);
    addChild(openBtn);
    
    InviteCell* hero  = InviteCell::create("gameview/head_image_1.png", UserData::getInstance()->getNickName());
    hero->setPosition(348,488);
    addChild(hero);
    
    //邀请3个好友
    for(int i=0;i<3;i++){
        inviters[i]=NULL;
    }
    
    myTableView2 = TableView::create(this, Size(660, 350));
    myTableView2->setAnchorPoint(Point::ANCHOR_MIDDLE);
    myTableView2->setDirection(ScrollView::Direction::VERTICAL);
    myTableView2->setPosition(300, 50);
    myTableView2->setDelegate(this);
    myTableView2->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    addChild(myTableView2);
    myTableView2->reloadData();
    
    if(GAMEDATA::getInstance()->getFriendList().friends.size()==0){
        Loading* load = Loading::create(true);
        load->setTag(100);
        addChild(load);
    }
    
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
    cell->getChildByTag(520)->setVisible(!cell->getChildByTag(520)->isVisible());
    
    FriendListData data = GAMEDATA::getInstance()->getFriendList();
    FriendInfo info ;
    for(auto var : data.friends){
        if(var.poxiaoId ==  cell->getName()){
            info = var;
        }
    }
    
    if (cell->getChildByTag(520)->isVisible()){
        inviteFriends.push_back(info);
        std::string imageName;
        if(info.pic == "1"){
            imageName= "gameview/head_image_1.png";
        }else if(info.pic == "2"){
            imageName = "gameview/head_image_2.png";
        }else if(info.pic == "3"){
            imageName = "gameview/head_image_3.png";
        }else if(info.pic == "4"){
            imageName = "gameview/head_image_4.png";
        }else{
            log("服务器下发的头像图片不存在");
            imageName= "gameview/head_image_1.png";
        }
        InviteCell* sprite  = InviteCell::create(imageName, info.nickname);
        sprite->setName(info.poxiaoId);
        addChild(sprite);
        for(int i=0;i<3;i++){
            if(inviters[i]==NULL){
                sprite->setPosition(468+120*i,488);
                inviters[i] =sprite;
                break;
            }
        }
    }
    else{
        vector<FriendInfo>::iterator it;
        for (it = inviteFriends.begin(); it != inviteFriends.end();)
        {
            if (it->poxiaoId == info.poxiaoId)
                it = inviteFriends.erase(it);
            else
                ++it;
        }
        for(int i=0;i<3;i++){
            if(inviters[i]!=NULL){
                if(inviters[i]->getName()==info.poxiaoId){
                    inviters[i]->removeFromParent();
                    inviters[i]=NULL;
                }
            }
        }
        
    }
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
        cell = new (std::nothrow) TableViewCell();
        cell->autorelease();
        cell->setName(GAMEDATA::getInstance()->getFriendList().friends.at(idx).poxiaoId);
        
        Sprite* head = Sprite::create();
        if(GAMEDATA::getInstance()->getFriendList().friends.at(idx).pic == "1"){
            head->setTexture("gameview/head_image_1.png");
        }else if(GAMEDATA::getInstance()->getFriendList().friends.at(idx).pic == "2"){
            head->setTexture("gameview/head_image_2.png");
        }else if(GAMEDATA::getInstance()->getFriendList().friends.at(idx).pic == "3"){
            head->setTexture("gameview/head_image_3.png");
        }else if(GAMEDATA::getInstance()->getFriendList().friends.at(idx).pic == "4"){
            head->setTexture("gameview/head_image_4.png");
        }else{
            log("服务器下发的头像图片不存在");
            head->setTexture("gameview/head_image_1.png");
        }
        head->setTag(500);
        head->setAnchorPoint(Vec2::ZERO);
        head->setScale(0.6f);
        head->setPosition(Vec2(5, 5));
        cell->addChild(head);
        
        std::string nickname = GAMEDATA::getInstance()->getFriendList().friends.at(idx).nickname;
        auto label = Label::createWithSystemFont(nickname, "arial", 24);
        label->setTag(501);
        label->setColor(Color3B(69,131,172));
        label->setAnchorPoint(Vec2::ZERO);
        label->setPosition(Vec2(130, 25));
        cell->addChild(label);
        
        Sprite* circle = Sprite::create("friend/offline_icon.png");
        circle->setPosition(350, 35);
        circle->setTag(502);
        cell->addChild(circle);
        Sprite* text = Sprite::create("friend/offline.png");
        text->setPosition(400,35);
        text->setTag(503);
        cell->addChild(text);
        
        if(GAMEDATA::getInstance()->getFriendList().friends.at(idx).isOnLine){
            circle->setTexture("friend/online_icon.png");
            text->setTexture("friend/online.png");
        }
        auto box = Sprite::create("friend/select_box.png");
        box->setPosition(620,35);
        cell->addChild(box);
        
        auto select = Sprite::create("friend/selected.png");
        select->setPosition(620,35);
        select->setTag(520);
        select->setVisible(false);
        cell->addChild(select);
    }else{
        cell->setName(GAMEDATA::getInstance()->getFriendList().friends.at(idx).poxiaoId);
        auto sprite1 = (Sprite*)cell->getChildByTag(500);
        if(GAMEDATA::getInstance()->getFriendList().friends.at(idx).pic == "1"){
            sprite1->setTexture("gameview/head_image_1.png");
        }else if(GAMEDATA::getInstance()->getFriendList().friends.at(idx).pic == "2"){
            sprite1->setTexture("gameview/head_image_2.png");
        }else if(GAMEDATA::getInstance()->getFriendList().friends.at(idx).pic == "3"){
            sprite1->setTexture("gameview/head_image_3.png");
        }else if(GAMEDATA::getInstance()->getFriendList().friends.at(idx).pic == "4"){
            sprite1->setTexture("gameview/head_image_4.png");
        }else{
            log("服务器下发的头像图片不存在");
            sprite1->setTexture("gameview/head_image_1.png");
        }
        ((Label*)cell->getChildByTag(501))->setString(GAMEDATA::getInstance()->getFriendList().friends.at(idx).nickname);
        if(GAMEDATA::getInstance()->getFriendList().friends.at(idx).isOnLine){
            ((Sprite*)cell->getChildByTag(502))->setTexture("friend/online_icon.png");
        }else{
            ((Sprite*)cell->getChildByTag(502))->setTexture("friend/offline_icon.png");
        }
        if(GAMEDATA::getInstance()->getFriendList().friends.at(idx).isOnLine){
            ((Sprite*)cell->getChildByTag(503))->setTexture("friend/online.png");
        }else{
            ((Sprite*)cell->getChildByTag(503))->setTexture("friend/offline.png");
        }
        
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