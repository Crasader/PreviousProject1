#include "game/mahjong/dialog/friend/FriendInvite.h"
#include "game/mahjong/lobby/LobbyScene.h"
#include "server/NetworkManage.h"

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
    
    auto  dialogBg = Sprite::create("friend/room_invite_bg.png");
    dialogBg->setPosition(1010, 360);
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
	return true;
}


void FriendInvite::onEnter(){
	Node::onEnter();
}


void FriendInvite::onExit(){
	Node::onExit();
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
        circle->setPosition(340, 35);
        cell->addChild(circle);
        Sprite* text = Sprite::create("friend/online.png");
        text->setPosition(390,35);
        cell->addChild(text);
        
        auto box = Sprite::create("friend/select_box.png");
        box->setPosition(455,35);
        cell->addChild(box);
        
        auto select = Sprite::create("friend/selected.png");
        select->setPosition(455,35);
        select->setTag(520);
        select->setVisible(false);
        cell->addChild(select);

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

//TODO

}


void FriendInvite::closeView(){
	this->removeFromParent();
}

void FriendInvite::updateFriendList(){
	tableView->reloadData();
}