#include "game/mahjong/friend/FriendListView.h"
#include "game/mahjong/friend/FriendAddView.h"
#include "game/mahjong/state/GameData.h"
#include "game/mahjong/lobby/LobbyScene.h"
#include "game/mahjong/chat/ChatDialog.hpp"
#include "server/NetworkManage.h"

bool FriendListView::init()
{
    if (!Layer::init())
    {
        return false;
    }
    MenuItem* item = MenuItem::create();
    item->setContentSize(Size(1280, 720));
    Menu* bg = Menu::create(item, NULL);
    this->addChild(bg);
    
    auto  dialogBg = Sprite::create("friend/dialog_bg.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(FriendListView::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(980, 650);
    addChild(closeMenu);
    
    auto paodai = Sprite::create("common/piaodai_zi.png");
    paodai->setPosition(640, 660);
    this->addChild(paodai);
    auto icon = Sprite::create("friend/friend_title.png");
    icon->setPosition(640, 680);
    addChild(icon);
    
    MenuItemImage* image = MenuItemImage::create("friend/add_friend_btn_1.png", "friend/add_friend_btn_2.png",
                                                 CC_CALLBACK_0(FriendListView::addConfirm,this));
    Menu* addFriend = Menu::create(image,NULL);
    addFriend->setPosition(380,610);
    this->addChild(addFriend);
    
    tableView = TableView::create(this, Size(722, 520));
    tableView->setAnchorPoint(Point::ANCHOR_MIDDLE);
    tableView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);
    tableView->setPosition(280, 55);
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


void FriendListView::onEnter(){
    Layer::onEnter();
    friendLsitListener = EventListenerCustom::create(MSG_HERO_FRIEND_LIST, [=](EventCustom* event){
        updateFriendList();
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(friendLsitListener, 1);
    
    updateLsitListener= EventListenerCustom::create("update_friend_list_view", [=](EventCustom* event){
        tableView->reloadData();
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(updateLsitListener, 1);

}


void FriendListView::onExit(){
    Layer::onExit();
    _eventDispatcher->removeEventListener(friendLsitListener);
    _eventDispatcher->removeEventListener(updateLsitListener);
}

void FriendListView::tableCellTouched(TableView* table, TableViewCell* cell)
{
    log("cell touched at index: %ld", cell->getIdx());
}

Size FriendListView::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    return Size(722, 132);
}

TableViewCell* FriendListView::tableCellAtIndex(TableView *table, ssize_t idx)
{
    auto string = String::createWithFormat("%ld", idx);
    TableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new (std::nothrow) TableViewCell();
        cell->autorelease();
        
        auto sprite = Sprite::create("friend/friend_info_bg.png");
        sprite->setAnchorPoint(Vec2::ZERO);
        
        sprite->setPosition(Vec2(0, 0));
        cell->addChild(sprite);
        
        Sprite* head = Sprite::create();
        head->setTag(500);
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
        head->setAnchorPoint(Vec2::ZERO);
        head->setPosition(Vec2(21, 21));
        cell->addChild(head);
        
        std::string nickname = GAMEDATA::getInstance()->getFriendList().friends.at(idx).nickname;
        auto label = Label::createWithSystemFont(nickname, "arial", 24);
        label->setTag(801);
        label->setColor(Color3B(69,131,172));
        label->setAnchorPoint(Vec2::ZERO);
        label->setPosition(Vec2(130, 80));
        cell->addChild(label);
        
        Sprite* circle = Sprite::create("friend/offline_icon.png");
        circle->setPosition(350, 90);
        circle->setTag(900);
        cell->addChild(circle);
        Sprite* text = Sprite::create("friend/offline.png");
        text->setPosition(400,90);
        text->setTag(901);
        cell->addChild(text);
        
        if(GAMEDATA::getInstance()->getFriendList().friends.at(idx).isOnLine){
            circle->setTexture("friend/online_icon.png");
            text->setTexture("friend/online.png");
        }
        
        Sprite* info_bg1 = Sprite::create("friend/friend_info_num_bg.png");
        info_bg1->setPosition(205,33);
        cell->addChild(info_bg1);
        Sprite* gold = Sprite::create("common/gold_icon.png");
        gold->setPosition(145, 33);
        cell->addChild(gold);
        
        Label* goldNum = Label::create(cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getFriendList().friends.at(idx).gold)->_string, "arial", 20);
        goldNum->setPosition(180, 33);
        goldNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        goldNum->setColor(Color3B(69, 131, 172));
        goldNum->setTag(802);
        cell->addChild(goldNum);
        
        Sprite* info_bg2 = Sprite::create("friend/friend_info_num_bg.png");
        info_bg2->setPosition(380,33);
        cell->addChild(info_bg2);
        Sprite* lequan = Sprite::create("common/lequan_icon.png");
        lequan->setPosition(320, 33);
        
        cell->addChild(lequan);
        Label* lequanNum = Label::create(cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getFriendList().friends.at(idx).lequan)->_string, "arial", 20);
        lequanNum->setPosition(360, 33);
        lequanNum->setColor(Color3B(69, 131, 172));
        lequanNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        lequanNum->setTag(803);
        cell->addChild(lequanNum);
        
        MenuItemImage* chat = MenuItemImage::create("friend/friend_chat_btn.png", "friend/friend_chat_btn.png",
                                                    CC_CALLBACK_1(FriendListView::chatFriend, this));
        //		MenuItemImage* view = MenuItemImage::create("friend/friend_view_btn.png", "friend/friend_view_btn.png",
        //			CC_CALLBACK_1(FriendListView::viewFriend, this));
        MenuItemImage* dele = MenuItemImage::create("friend/friend_delete_btn.png", "friend/friend_delete_btn.png",
                                                    CC_CALLBACK_1(FriendListView::deleteFriend, this));
        Menu* menu = Menu::create(chat, dele, NULL);
        menu->setAnchorPoint(Vec2::ZERO);
        menu->alignItemsHorizontallyWithPadding(5);
        menu->setPosition(Vec2(590, 66));
        cell->addChild(menu);
        
        auto tanhao = Sprite::create("daily/tan_hao.png");
        tanhao->setPosition(Vec2(570, 100));
        tanhao->setTag(815);
        tanhao->setVisible(false);
        cell->addChild(tanhao);
        FriendChatMsgList list = GAMEDATA::getInstance()->getFriendChatMsgList();
        for(auto var : list.friendMsgList){
            if(var.poxiaoId == GAMEDATA::getInstance()->getFriendList().friends.at(idx).poxiaoId){
                std::vector<ChatData> msgList = var.msgList;
                bool find = false;
                if(!msgList.empty()){
                    for (auto msg : msgList) {
                        if(!msg.isRead){
                            find = true;
                        }
                    }
                }
                if(find){
                    tanhao->setVisible(true);
                }
            }
        }
        
    }
    else{
        auto sprite2 = (Sprite*)cell->getChildByTag(500);
        if(GAMEDATA::getInstance()->getFriendList().friends.at(idx).pic == "1"){
            sprite2->setTexture("gameview/head_image_1.png");
        }else if(GAMEDATA::getInstance()->getFriendList().friends.at(idx).pic == "2"){
            sprite2->setTexture("gameview/head_image_2.png");
        }else if(GAMEDATA::getInstance()->getFriendList().friends.at(idx).pic == "3"){
            sprite2->setTexture("gameview/head_image_3.png");
        }else if(GAMEDATA::getInstance()->getFriendList().friends.at(idx).pic == "4"){
            sprite2->setTexture("gameview/head_image_4.png");
        }else{
            log("服务器下发的头像图片不存在");
            sprite2->setTexture("gameview/head_image_1.png");
        }
        
        auto label = (Label*)cell->getChildByTag(801);
        label->setString(GAMEDATA::getInstance()->getFriendList().friends.at(idx).nickname);
        auto label2 = (Label*)cell->getChildByTag(802);
        label2->setString(cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getFriendList().friends.at(idx).gold)->_string);
        auto label3 = (Label*)cell->getChildByTag(803);
        label3->setString(cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getFriendList().friends.at(idx).lequan)->_string);
        auto  online = (Sprite*)cell->getChildByTag(900);
        auto onlinetext = (Sprite*)cell->getChildByTag(901);
        if(GAMEDATA::getInstance()->getFriendList().friends.at(idx).isOnLine){
            online->setTexture("friend/online_icon.png");
            onlinetext->setTexture("friend/online.png");
        }else{
            online->setTexture("friend/offline_icon.png");
            onlinetext->setTexture("friend/offline.png");
        }
        FriendChatMsgList list = GAMEDATA::getInstance()->getFriendChatMsgList();
        for(auto var : list.friendMsgList){
            if(var.poxiaoId == GAMEDATA::getInstance()->getFriendList().friends.at(idx).poxiaoId){
                std::vector<ChatData> msgList = var.msgList;
                bool find =false;
                if(!msgList.empty()){
                    for (auto msg : msgList) {
                        if(!msg.isRead){
                            find = true;
                        }
                    }
                }
                if(find){
                    if(NULL != cell->getChildByTag(815))
                        cell->getChildByTag(815)->setVisible(true);
                }else{
                    if(NULL != cell->getChildByTag(815))
                        cell->getChildByTag(815)->setVisible(false);
                }
            }
        }
    }
    return cell;
}

ssize_t FriendListView::numberOfCellsInTableView(TableView *table)
{
    int size = GAMEDATA::getInstance()->getFriendList().friends.size();
    if (size < 0){
        size = 0;
    }
    return size;
}

void FriendListView::updateFriendList(){
    if(NULL != getChildByTag(100)){
        getChildByTag(100)->removeFromParent();
    }
    tableView->reloadData();
}

void FriendListView::addConfirm(){
    FriendAddView* search = FriendAddView::create();
    this->addChild(search);
}

void FriendListView::chatFriend(Ref* ref){
    MenuItemImage* temp = (MenuItemImage*)ref;
    int id = ((TableViewCell*)temp->getParent()->getParent())->getIdx();
    FriendListData data = GAMEDATA::getInstance()->getFriendList();
    std::string pid = data.friends.at(id).poxiaoId;
    ChatDialog* chat = ChatDialog::create(pid);
    addChild(chat);
}

void FriendListView::viewFriend(Ref* ref){
    //TODO
}

void FriendListView::deleteFriend(Ref* ref){
    //TODO需要重新处理,否则删除的时候会删错好友
    MenuItemImage* temp = (MenuItemImage*)ref;
    int id = ((TableViewCell*)temp->getParent()->getParent())->getIdx();
    FriendListData data = GAMEDATA::getInstance()->getFriendList();
    std::string pid = data.friends.at(id).poxiaoId;
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getDeleteFriendCommand(pid));
    vector<FriendInfo>::iterator it;
    for (it = data.friends.begin(); it != data.friends.end();)
    {
        if (it->poxiaoId == pid)
            it = data.friends.erase(it);
        else
            ++it;
    }
    GAMEDATA::getInstance()->setFriendList(data);
    tableView->reloadData();
}

void FriendListView::closeView(){
    this->removeFromParent();
}