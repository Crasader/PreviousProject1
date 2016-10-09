#include "game/mahjong/friend/FriendInvite.h"
#include "game/mahjong/lobby/LobbyScene.h"
#include "server/NetworkManage.h"
#include "game/utils/GameConfig.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#import "payment/ios/IOSBridge.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "payment/android/CallAndroidMethod.h"
#endif


bool FriendInvite::init()
{
    if (!Layer::init())
    {
        return false;
    }
    MenuItem* item = MenuItem::create();
    item->setContentSize(Size(1280, 720));
    Menu* bg = Menu::create(item, NULL);
    this->addChild(bg);
    
    MenuItem* item2 = MenuItem::create(CC_CALLBACK_0(FriendInvite::closeView, this));
    item2->setContentSize(Size(720, 720));
    Menu* bg2 = Menu::create(item2, NULL);
    bg2->setPosition(360,360);
    this->addChild(bg2);
    
    auto  dialogBg = Sprite::create("friend/room_invite_bg.png");
    dialogBg->setPosition(1010, 360);
    dialogBg->setTag(824);
    this->addChild(dialogBg);
    
    auto wxBtnImage = MenuItemImage::create("friend/room_invite_wx.png","friend/room_invite_wx.png",
                                            CC_CALLBACK_0(FriendInvite::inviteWxFriend, this));
    auto menuWx = Menu::create(wxBtnImage,NULL);
    menuWx->setPosition(1010,596);
    addChild(menuWx);
    tableView = TableView::create(this, Size(490, 400));
    tableView->setAnchorPoint(Point::ANCHOR_MIDDLE);
    tableView->setDirection(ScrollView::Direction::VERTICAL);
    tableView->setPosition(780, 90);
    tableView->setDelegate(this);
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    this->addChild(tableView);
    //tableView->reloadData();
    
    
    auto openImage = MenuItemImage::create("friend/open_room_btn.png","friend/open_room_btn.png",CC_CALLBACK_0(FriendInvite::addConfirm, this));
    Menu* openBtn = Menu::create(openImage,NULL);
    openBtn->setPosition(1010,70);
    addChild(openBtn);
    
    auto myInvitetouchListener = EventListenerTouchOneByOne::create();
    myInvitetouchListener->onTouchBegan = CC_CALLBACK_2(FriendInvite::onTouchBegan, this);
    myInvitetouchListener->onTouchEnded = CC_CALLBACK_2(FriendInvite::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(myInvitetouchListener,this);

    return true;
}


void FriendInvite::onEnter(){
    Layer::onEnter();
    
    friendLsitListener3 = EventListenerCustom::create(MSG_HERO_FRIEND_LIST, [=](EventCustom* event){
        updateFriendList();
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(friendLsitListener3, 1);
    
}


void FriendInvite::onExit(){
    Layer::onExit();
    _eventDispatcher->removeEventListener(friendLsitListener3);
}


void FriendInvite::tableCellTouched(TableView* table, TableViewCell* cell)
{
    cell->getChildByTag(520)->setVisible(!cell->getChildByTag(520)->isVisible());
    
    FriendListData data = GAMEDATA::getInstance()->getFriendList();
    std::string pid = data.friends.at(cell->getIdx()).poxiaoId;
    if (cell->getChildByTag(520)->isVisible()){
        inviteFriends.push_back(data.friends.at(cell->getIdx()));
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
    }
}

Size FriendInvite::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    return Size(490, 60);
}

TableViewCell* FriendInvite::tableCellAtIndex(TableView *table, ssize_t idx)
{
    auto string = String::createWithFormat("%ld", idx);
    TableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new (std::nothrow) TableViewCell();
        cell->autorelease();
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
        circle->setPosition(340, 35);
        circle->setTag(802);
        cell->addChild(circle);
        Sprite* text = Sprite::create("friend/online.png");
        text->setPosition(390,35);
        text->setTag(803);
        cell->addChild(text);
        
        if(!GAMEDATA::getInstance()->getFriendList().friends.at(idx).isOnLine){
            circle->setTexture("friend/offline_icon.png");
            text->setTexture("friend/offline.png");
        }
        
        auto box = Sprite::create("friend/select_box.png");
        box->setPosition(455,35);
        cell->addChild(box);
        
        auto select = Sprite::create("friend/selected.png");
        select->setPosition(455,35);
        select->setTag(520);
        select->setVisible(false);
        cell->addChild(select);
        
    }else{
        std::string nickname = GAMEDATA::getInstance()->getFriendList().friends.at(idx).nickname;
        ((Label*)cell->getChildByTag(801))->setString(nickname);
        if(!GAMEDATA::getInstance()->getFriendList().friends.at(idx).isOnLine){
            ((Sprite*)cell->getChildByTag(802))->setTexture("friend/offline_icon.png");
            ((Sprite*)cell->getChildByTag(803))->setTexture("friend/offline.png");
        }else{
            ((Sprite*)cell->getChildByTag(802))->setTexture("friend/online_icon.png");
            ((Sprite*)cell->getChildByTag(803))->setTexture("friend/online.png");
        }
    }
    return cell;
}

ssize_t FriendInvite::numberOfCellsInTableView(TableView *table)
{
    int size = GAMEDATA::getInstance()->getFriendList().friends.size();
    if (size < 0){
        size = 0;
    }
    return size;
}

void FriendInvite::addConfirm(){
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


void FriendInvite::inviteWxFriend(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CallAndroidMethod::getInstance()->shareToWeChat(WECHAT_SHARE_FRIEND_URL,"房间开好，就等侬了！", "来来来，房间开好了，麻将搓起来，手慢位置就要没了。",false);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    IOSBridge::getInstance()->doWechatShareWeb(WECHAT_SHARE_FRIEND_URL,"房间开好，就等侬了！", "来来来，房间开好了，麻将搓起来，手慢位置就要没了。");
#endif
}


void FriendInvite::closeView(){
    this->removeFromParent();
}

void FriendInvite::updateFriendList(){
    tableView->reloadData();
}

bool FriendInvite::onTouchBegan(Touch *touch, Event  *event){
    return true;
}


void FriendInvite::onTouchEnded(Touch *touch, Event  *event){
    if(NULL != getChildByTag(824)){
        if(!((Sprite*)getChildByTag(824))->getBoundingBox().containsPoint(touch->getLocation())){
            removeFromParent();
        }
    }
}
