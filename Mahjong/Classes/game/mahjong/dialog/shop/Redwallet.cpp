#include "game/mahjong/dialog/shop/Redwallet.h"
#include "server/NetworkManage.h"

bool Redwallet::init(){
	if (!Layer::init()){
		return false;
	}
	giveRedwalletLayer = NULL;
	getRedwalletLayer = NULL;
	tishiLayer = NULL;
	drawDialog();
	return true;
}


void Redwallet::drawDialog(){
    
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
    gold->setPosition(275,395);
    addChild(gold);
    
    LabelAtlas* goldNum = LabelAtlas::create("999","shop/prop_num.png",21,28,'0');
    goldNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    goldNum->setPosition(305,395);
    goldNum->setScale(0.9);
    addChild(goldNum);
    
    auto goldText = Sprite::create("shop/gold_text.png");
    goldText->setPosition(415,395);
    addChild(goldText);
    
    auto lequan = Sprite::create("mjitem/lequan_icon.png");
    lequan->setScale(0.8f);
    lequan->setPosition(275,335);
    addChild(lequan);
    
    LabelAtlas* lequanNum = LabelAtlas::create("999","shop/prop_num.png",21,28,'0');
    lequanNum->setPosition(305,335);
    lequanNum->setScale(0.9);
    lequanNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(lequanNum);
    
    auto lequanText = Sprite::create("shop/lequan_text.png");
    lequanText->setPosition(415,335);
    addChild(lequanText);
    
    auto diamond = Sprite::create("mjitem/diamond.png");
    diamond->setPosition(275,275);
    diamond->setScale(0.8f);
    addChild(diamond);
    
    LabelAtlas* diamondNum = LabelAtlas::create("999","shop/prop_num.png",21,28,'0');
    diamondNum->setPosition(305,275);
    diamondNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    diamondNum->setScale(0.9);
    addChild(diamondNum);
    
    auto diamondText = Sprite::create("shop/bangzhuan_text.png");
    diamondText->setPosition(415,275);
    addChild(diamondText);
    
    auto btnImage1 = MenuItemImage::create("shop/get_wallet_1.png","shop/get_wallet_2.png");
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
    
    LabelAtlas* goldNum2 = LabelAtlas::create("999","shop/prop_num.png",21,28,'0');
    goldNum2->setPosition(580,375);
    goldNum2->setScale(0.9f);
    goldNum2->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(goldNum2);
    
    auto goldText2 = Sprite::create("shop/gold_text.png");
    goldText2->setPosition(690,375);
    addChild(goldText2);
    
    
    LabelAtlas* lequanNum2 = LabelAtlas::create("999","shop/prop_num.png",21,28,'0');
    lequanNum2->setPosition(580,335);
    lequanNum2->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    lequanNum2->setScale(0.9f);
    addChild(lequanNum2);
    
    auto lequanText2 = Sprite::create("shop/gold_text.png");
    lequanText2->setPosition(690,335);
    addChild(lequanText2);
    
    
    LabelAtlas* diamondNum2 = LabelAtlas::create("999","shop/prop_num.png",21,28,'0');
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
    
    auto btnImage2 = MenuItemImage::create("shop/free_red_wallet_1.png","shop/free_red_wallet_2.png");
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
        
        auto label = Label::createWithSystemFont("abc", "arial", 30);
        label->setTag(801);
        label->setColor(Color3B(69,131,172));
        label->setAnchorPoint(Vec2::ZERO);
        label->setPosition(Vec2(125, 65));
        cell->addChild(label);
        
    }
    return cell;
}

ssize_t Redwallet::numberOfCellsInTableView(TableView *table)
{
    return 2;
}


void Redwallet::drawGiveRedwallet(){
	if (getRedwalletLayer != NULL){
		getRedwalletLayer->removeFromParent();
		getRedwalletLayer = NULL;
	}
	if (giveRedwalletLayer != NULL){
		return;
	}

	giveRedwalletLayer = Layer::create();
	this->addChild(giveRedwalletLayer);
    
	auto kouling = Sprite::create("dialog/redwallet/redwalet_password.png");
	kouling->setPosition(480, 310);
	giveRedwalletLayer->addChild(kouling);

	auto miling = Label::create("123456", "Arial", 18);
	miling->setPosition(480, 265);
	giveRedwalletLayer->addChild(miling);

	auto jaingli = Sprite::create("dialog/redwallet/get_pride_text.png");
	jaingli->setPosition(480, 235);
	giveRedwalletLayer->addChild(jaingli);

	drawRedpride(giveRedwalletLayer, Point(365,205));

	auto person = Sprite::create("dialog/redwallet/redwalet_password_person.png");
	person->setPosition(480, 178);
	giveRedwalletLayer->addChild(person);
	auto personNum = LabelAtlas::create("1000", "dialog/redwallet/redwalet_password_num.png", 8, 12, '0');
	personNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
	personNum->setPosition(512, 178);
	giveRedwalletLayer->addChild(personNum);

	auto item = MenuItemImage::create("dialog/redwallet/share_redwallet_bnt_1.png", "dialog/redwallet/share_redwallet_bnt_2.png",
		CC_CALLBACK_0(Redwallet::giveRedwallet, this));
	auto giveMenu = Menu::create(item,NULL);
	giveMenu->setPosition(480,130);
	giveRedwalletLayer->addChild(giveMenu);
}

void Redwallet::drawGetRedwallet(){
    
	if (giveRedwalletLayer != NULL){
		giveRedwalletLayer->removeFromParent();
		giveRedwalletLayer = NULL;
	}
	if (getRedwalletLayer != NULL){
		return;
	}
	getRedwalletLayer = Layer::create();
	this->addChild(getRedwalletLayer);
	auto kouling = Sprite::create("dialog/redwallet/redwalet_password_input.png");
	kouling->setPosition(480, 310);
	getRedwalletLayer->addChild(kouling);

	_editPwd = EditBox::create(Size(257, 40), Scale9Sprite::create("dialog/user_input_box.png"));
	_editPwd->setPosition(Point(480, 270));
	_editPwd->setFont("American Typewriter", 24);
	getRedwalletLayer->addChild(_editPwd);

	auto jaingli = Sprite::create("dialog/redwallet/get_pride_text.png");
	jaingli->setPosition(480, 235);
	getRedwalletLayer->addChild(jaingli);

	drawRedpride(getRedwalletLayer, Point(477, 205));

	auto item = MenuItemImage::create("dialog/redwallet/confirm_redwallet_btn_1.png", "dialog/redwallet/confirm_redwallet_btn_2.png",
		CC_CALLBACK_0(Redwallet::getRedwallet, this));
	auto giveMenu = Menu::create(item, NULL);
	giveMenu->setPosition(480, 130);
	getRedwalletLayer->addChild(giveMenu);
}

void Redwallet::drawTishiLayer(){
	if (getRedwalletLayer != NULL){
		getRedwalletLayer->removeFromParent();
		getRedwalletLayer = NULL;
	}
	if (tishiLayer == NULL){
		tishiLayer = Layer::create();
		this->addChild(tishiLayer);

		auto dialogBg = Sprite::create("dialog/dialog_bg_small.png");
		dialogBg->setPosition(480, 270);
		tishiLayer->addChild(dialogBg);

		auto title = Sprite::create("dialog/tishi_icon.png");
		title->setPosition(480, 365);
		tishiLayer->addChild(title);

		auto info = Label::create("helle world!","Arial",20);
		info->setPosition(480,312);
		tishiLayer->addChild(info);

		drawRedpride(tishiLayer, Point(365, 250));

		auto close = MenuItemImage::create("dialog/dialog_close_a.png", "dialog/dialog_close_b.png",
			CC_CALLBACK_0(Redwallet::closeTishiView, this));
		auto closeMenu = Menu::create(close, NULL);
		closeMenu->setPosition(640, 370);
		tishiLayer->addChild(closeMenu);

		auto confirm = MenuItemImage::create("dialog/user_box_confirm_a.png", "dialog/user_box_confirm_b.png",
			CC_CALLBACK_0(Redwallet::closeTishiView, this));
		auto confirmMenu = Menu::create(confirm, NULL);
		confirmMenu->setPosition(480, 190);
		tishiLayer->addChild(confirmMenu);
	}
}

void Redwallet::drawRedpride(Layer* layer, Point startpos){

	auto godNum = LabelAtlas::create("1000", "dialog/redwallet/pride_num.png", 14, 19, '0');
	godNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
	godNum->setPosition(365, startpos.y);
	layer->addChild(godNum);
	auto goldIcon = Sprite::create("dialog/redwallet/gold_icon.png");
	goldIcon->setPosition(416, startpos.y);
	layer->addChild(goldIcon);
	auto plusIcon1 = Sprite::create("dialog/redwallet/plus.png");
	plusIcon1->setPosition(448, startpos.y);
	layer->addChild(plusIcon1);

	auto lequanNum = LabelAtlas::create("100", "dialog/redwallet/pride_num.png", 14, 19, '0');
	lequanNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
	lequanNum->setPosition(477, startpos.y);
	layer->addChild(lequanNum);
	auto lequanIcon = Sprite::create("dialog/redwallet/lequan_icon.png");
	lequanIcon->setPosition(520, startpos.y);
	layer->addChild(lequanIcon);
	auto plusIcon2 = Sprite::create("dialog/redwallet/plus.png");
	plusIcon2->setPosition(558, startpos.y);
	layer->addChild(plusIcon2);

	auto diamondNum = LabelAtlas::create("100", "dialog/redwallet/pride_num.png", 14, 19, '0');
	diamondNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
	diamondNum->setPosition(591, startpos.y);
	layer->addChild(diamondNum);
	auto diamondIcon = Sprite::create("dialog/redwallet/diamond.png");
	diamondIcon->setPosition(625, startpos.y);
	layer->addChild(diamondIcon);
}


void Redwallet::giveRedwallet(){
	NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getSendRedWalletCommand());
}


void Redwallet::getRedwallet(){
	NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getReciveRedWalletCommand());
	drawTishiLayer();
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
		drawRedpride(getRedwalletLayer, Point(365, 205));
	}
}

