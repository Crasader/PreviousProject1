#include "game/mahjong/dialog/friend/SearchResult.h"
#include "game/mahjong/state/GameData.h"
#include "server/NetworkManage.h"
#include "game/mahjong/dialog/prompt/HintDialog.hpp"
bool SearchResult::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto input_bg_1 = Sprite::create("friend/searchResult.png");
	input_bg_1->setPosition(640, 255);
	addChild(input_bg_1);
	tableView = TableView::create(this, Size(625, 220));
	tableView->setAnchorPoint(Point::ANCHOR_MIDDLE);
	tableView->setDirection(ScrollView::Direction::VERTICAL);
	tableView->setPosition(335, 140);
	tableView->setDelegate(this);
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	this->addChild(tableView);
	tableView->reloadData();
	return true;
}


void SearchResult::onEnter(){
    Layer::onEnter();
    
    addFriendRespListener = EventListenerCustom::create(MSG_ADD_FRIEND_RESP, [=](EventCustom* event){
        char* buf = static_cast<char*>(event->getUserData());
        std::string result = buf;
        if (result == "1"){
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getFriendListCommand());
            HintDialog* hint = HintDialog::create("添加好友成功",false);
            addChild(hint);
        }else{
            HintDialog* hint = HintDialog::create("添加好友失败",false);
            addChild(hint);
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(addFriendRespListener, 1);
}


void SearchResult::onExit(){
    Layer::onExit();
    _eventDispatcher->removeEventListener(addFriendRespListener);
}

void SearchResult::tableCellTouched(TableView* table, TableViewCell* cell)
{
	log("cell touched at index: %ld", cell->getIdx());
}

Size SearchResult::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
	return Size(625, 110);
}

TableViewCell* SearchResult::tableCellAtIndex(TableView *table, ssize_t idx)
{
	auto stringId = String::createWithFormat("%ld", idx);
	TableViewCell *cell = table->dequeueCell();
	if (!cell) {
		cell = new (std::nothrow) TableViewCell();
		cell->autorelease();
        
		auto head = Sprite::create("gameview/head_image_1.png");
		head->setAnchorPoint(Vec2::ZERO);
		head->setPosition(Vec2(19, 19));
		cell->addChild(head);

		auto label = Label::createWithSystemFont(GAMEDATA::getInstance()->getFriendSearch().friends.at(idx*2).nickname, "arial", 28);
		label->setAnchorPoint(Vec2::ZERO);
		label->setPosition(Vec2(115, 75));
		label->setTag(123);
		label->setColor(Color3B(100, 168, 215));
		cell->addChild(label);

		MenuItemImage* addfriend = MenuItemImage::create("common/add_friend_btn_1.png", "common/add_friend_btn_2.png",
			CC_CALLBACK_1(SearchResult::addFriend, this));
		auto menu = Menu::create(addfriend, NULL);
		menu->setAnchorPoint(Vec2::ZERO);
		menu->setPosition(Vec2(185, 40));
		menu->setScale(0.8f);
        menu->setTag(124);
        menu->setName(GAMEDATA::getInstance()->getFriendSearch().friends.at(idx*2).poxiaoId);
		cell->addChild(menu);
        
		if (idx * 2 + 1 < GAMEDATA::getInstance()->getFriendSearch().friends.size()){

			Sprite* head2 = Sprite::create("gameview/head_image_1.png");
			head2->setAnchorPoint(Vec2::ZERO);
			head2->setPosition(Vec2(320, 19));
			cell->addChild(head2);

			auto label2 = Label::createWithSystemFont(GAMEDATA::getInstance()->getFriendSearch().friends.at(idx * 2 + 1).nickname, "arial", 28);
			label2->setAnchorPoint(Vec2::ZERO);
			label2->setPosition(Vec2(415, 75));
			label2->setTag(321);
			label2->setColor(Color3B(100, 168, 215));
			cell->addChild(label2);

			MenuItemImage* addfriend2 = MenuItemImage::create("common/add_friend_btn_1.png", "common/add_friend_btn_2.png",
				CC_CALLBACK_1(SearchResult::addFriend, this));
			Menu* menu2 = Menu::create(addfriend2, NULL);
			menu2->setAnchorPoint(Vec2::ZERO);
			menu2->setPosition(Vec2(485, 40));
			menu2->setScale(0.8f);
            menu2->setTag(320);
            menu2->setName(GAMEDATA::getInstance()->getFriendSearch().friends.at(idx * 2 + 1).poxiaoId);
			cell->addChild(menu2);
		}
	}
	else{

		((Label*)cell->getChildByTag(123))->setString(GAMEDATA::getInstance()->getFriendSearch().friends.at(idx*2).nickname);
        
        ((Menu*)cell->getChildByTag(124))->setName(GAMEDATA::getInstance()->getFriendSearch().friends.at(idx * 2).poxiaoId);
        
		if (idx * 2 + 1 < GAMEDATA::getInstance()->getFriendSearch().friends.size()){
            if (NULL != getChildByTag(321)){
                ((Label*)cell->getChildByTag(321))->setString(GAMEDATA::getInstance()->getFriendSearch().friends.at(idx * 2 + 1).nickname);}
            if (NULL != getChildByTag(320)){
                ((Menu*)cell->getChildByTag(320))->setName(GAMEDATA::getInstance()->getFriendSearch().friends.at(idx * 2 + 1).poxiaoId);
            }
		}
	}
	return cell;
}

ssize_t SearchResult::numberOfCellsInTableView(TableView *table)
{
	int size = GAMEDATA::getInstance()->getFriendSearch().friends.size() / 2
		+ GAMEDATA::getInstance()->getFriendSearch().friends.size() % 2;
	if (size < 0){
		size = 0;
	}
	return size;
}


void SearchResult::updateResultList(){
    
	tableView->reloadData();
}

void SearchResult::addFriend(Ref* ref){
	MenuItemImage* temp = (MenuItemImage*)ref;
	temp->setVisible(false);
	string id = temp->getParent()->getName();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getAddFriendCommand(id));
    for(FriendInfo info: GAMEDATA::getInstance()->getFriendSearch().friends){
        if(info.poxiaoId==id){
         GAMEDATA::getInstance()->setFriendInfoData(info);
        }
    };
}


void SearchResult::closeView(){
	FriendSearchData info = GAMEDATA::getInstance()->getFriendSearch();
	info.friends.clear();
	GAMEDATA::getInstance()->setFriendSearch(info);
	this->removeFromParent();
}