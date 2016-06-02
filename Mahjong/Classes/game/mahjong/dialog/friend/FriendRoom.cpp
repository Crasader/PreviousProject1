#include "game/mahjong/dialog/friend/FriendRoom.h"
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
    
    auto all_bg = Sprite::create("common/all_bg.jpg");
    all_bg->setPosition(640, 360);
    addChild(all_bg);
    
    auto  dialogBg = Sprite::create("friend/friend_room_bg.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(FriendRoom::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(980, 650);
    addChild(closeMenu);
    
    auto qiao = Sprite::create("friend/qiaoma.png");
    qiao->setPosition(410,600);
    addChild(qiao);
    
    auto dihua = Sprite::create("friend/1di1hua.png");
    dihua->setPosition(607,600);
    addChild(dihua);
    
    auto xiao = Sprite::create("friend/xiaohao.png");
    xiao->setPosition(800,600);
    addChild(xiao);
    
    
    auto xuanze = Sprite::create("friend/xuanze_text.png");
    xuanze->setPosition(883,523);
    addChild(xuanze);
    
    auto openImage = MenuItemImage::create("friend/open_room_btn.png","friend/open_room_btn.png",CC_CALLBACK_0(FriendRoom::openRoom, this));
    Menu* openBtn = Menu::create(openImage,NULL);
    openBtn->setPosition(883,470);
    addChild(openBtn);
    
    for(int i=0;i<4;i++){
        inviters[i]=NULL;
    }
    
    tableView = TableView::create(this, Size(660, 350));
    tableView->setAnchorPoint(Point::ANCHOR_MIDDLE);
    tableView->setDirection(ScrollView::Direction::VERTICAL);
    tableView->setPosition(300, 50);
    tableView->setDelegate(this);
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    this->addChild(tableView);
    tableView->reloadData();
    
    if(GAMEDATA::getInstance()->getFriendList().friends.size()==0){
        Loading* load = Loading::create(true);
        load->setTag(100);
        addChild(load);
    }

    return true;
}


void FriendRoom::onEnter(){
    Node::onEnter();
}


void FriendRoom::onExit(){
    Node::onExit();
}


void FriendRoom::tableCellTouched(TableView* table, TableViewCell* cell)
{
    log("cell touched at index: %ld", cell->getIdx());
    cell->getChildByTag(520)->setVisible(!cell->getChildByTag(520)->isVisible());
    
    FriendListData data = GAMEDATA::getInstance()->getFriendList();
    std::string pid = data.friends.at(cell->getIdx()).poxiaoId;
    if (cell->getChildByTag(520)->isVisible()){
        inviteFriends.push_back(data.friends.at(cell->getIdx()));
        InviteCell* sprite  = InviteCell::create("gameview/head_image_1.png", data.friends.at(cell->getIdx()).nickname);
        sprite->setName(data.friends.at(cell->getIdx()).poxiaoId);
        addChild(sprite);
        for(int i=0;i<4;i++){
            if(inviters[i]==NULL){
                sprite->setPosition(348+120*i,488);
                inviters[i] =sprite;
                break;
            }
        }
    }
    else{
        vector<FriendInfo>::iterator it;
        for (it = inviteFriends.begin(); it != inviteFriends.end();)
        {
            if (it->poxiaoId == pid)
                it = inviteFriends.erase(it);
            else
                ++it;
        }
        for(int i=0;i<4;i++){
            if(inviters[i]!=NULL){
                if(inviters[i]->getName()==pid){
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
        
        
        Sprite* head = Sprite::create("gameview/head_image_1.png");
        head->setAnchorPoint(Vec2::ZERO);
        head->setScale(0.6f);
        head->setPosition(Vec2(5, 5));
        cell->addChild(head);
        
        std::string nickname = GAMEDATA::getInstance()->getFriendList().friends.at(idx).nickname;
        auto label = Label::createWithSystemFont(nickname, "arial", 24);
        label->setTag(801);
        label->setColor(Color3B(69,131,172));
        label->setAnchorPoint(Vec2::ZERO);
        label->setPosition(Vec2(130, 25));
        cell->addChild(label);
        
        Sprite* circle = Sprite::create("friend/online_icon.png");
        circle->setPosition(350, 35);
        cell->addChild(circle);
        Sprite* text = Sprite::create("friend/online.png");
        text->setPosition(400,35);
        cell->addChild(text);
        
        auto box = Sprite::create("friend/select_box.png");
        box->setPosition(620,35);
        cell->addChild(box);
        
        auto select = Sprite::create("friend/selected.png");
        select->setPosition(620,35);
        select->setTag(520);
        select->setVisible(false);
        cell->addChild(select);
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
    tableView->reloadData();
}