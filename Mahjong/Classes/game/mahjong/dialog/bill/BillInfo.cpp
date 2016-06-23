#include "BillInfo.h"
#include "BillDetailInfo.h"
#include "server/NetworkManage.h"
#include "userdata/UserData.h"
#include "game/utils/StringUtil.h"
#include "game/loading/Loading.h"
#include "game/utils/Chinese.h"

bool BillInfo::init()
{
    if (!Layer::init())
    {
        return false;
    }
    MenuItem* item = MenuItem::create();
    item->setContentSize(Size(1280, 720));
    Menu* bg = Menu::create(item, NULL);
    this->addChild(bg,-1);
    
    auto all_bg = Sprite::create("common/all_bg.jpg");
    all_bg->setTag(100);
    all_bg->setPosition(640, 360);
    addChild(all_bg);
    
    auto  dialogBg = Sprite::create("friend/dialog_bg.png");
    dialogBg->setTag(101);
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(BillInfo::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(980, 655);
    closeMenu->setTag(102);
    addChild(closeMenu);
    
    auto paodai = Sprite::create("common/piaodai_zi.png");
    paodai->setPosition(640, 660);
    paodai->setTag(103);
    this->addChild(paodai);
    
    auto icon = Sprite::create("bill/bill_title.png");
    icon->setPosition(640, 680);
    icon->setTag(104);
    addChild(icon);
    
    tableView = TableView::create(this, Size(722, 550));
    tableView->setAnchorPoint(Point::ANCHOR_MIDDLE);
    tableView->setDirection(ScrollView::Direction::VERTICAL);
    tableView->setPosition(275, 60);
    tableView->setTag(105);
    tableView->setDelegate(this);
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    this->addChild(tableView);
    tableView->reloadData();
    
    if(GAMEDATA::getInstance()->getBillInfoAll().needInit){
        Loading* load =Loading::create(true);
        load->setTag(1000);
        addChild(load);
    }else{
        showKongBill();
    }
    return true;
}

void BillInfo::onEnter(){
    Layer::onEnter();
    //刷新账单信息
    playerBillListener = EventListenerCustom::create(MSG_PLAYER_BILL, [=](EventCustom* event){
        updateBillInfo();
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(playerBillListener, 1);
    //显示账单详情
    detailBillListener = EventListenerCustom::create(MSG_PLAYER_BILL_DETAIL, [=](EventCustom* event){
        BillDetailInfo* detail =BillDetailInfo::create();
        if(getIsPrivateBill()){
            detail->setPrivatePostion();
        }
        addChild(detail);
    });
    _eventDispatcher->addEventListenerWithFixedPriority(detailBillListener, 1);
}

void BillInfo::onExit(){
    Layer::onExit();
    _eventDispatcher->removeEventListener(playerBillListener);
    _eventDispatcher->removeEventListener(detailBillListener);
}



void BillInfo::tableCellTouched(TableView* table, TableViewCell* cell)
{
    log("cell touched at index: %ld", cell->getIdx());
    BillInfoAll info = GAMEDATA::getInstance()->getBillInfoAll();
    string bId =cell->getName();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getBillDetailCommand(bId));
    for(int i=0;i<info.bills.size();i++){
        if(info.bills.at(i).billId == bId){
            GAMEDATA::getInstance()->setBillInfoData(info.bills.at(i));
        }
    }
}

Size BillInfo::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    return Size(722, 152);
}

TableViewCell* BillInfo::tableCellAtIndex(TableView *table, ssize_t idx)
{
    auto string = String::createWithFormat("%ld", idx);
    
    BillInfoAll info = GAMEDATA::getInstance()->getBillInfoAll();
    
    BillInfoData data = info.bills.at(idx);
    
    TableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new (std::nothrow) TableViewCell();
        cell->autorelease();
        auto sprite1 = Sprite::create("bill/bill_bg.png");
        sprite1->setAnchorPoint(Vec2::ZERO);
        sprite1->setPosition(Vec2(0, 0));
        cell->addChild(sprite1);
        
        Label* date = Label::create(data.date,"Arial",22);
        date->setTag(100);
        date->setColor(Color3B(21,50,91));
        date->setAnchorPoint(Vec2::ZERO);
        date->setPosition(Vec2(18, 115));
        cell->addChild(date);
        
        std::vector<BillContent> conBill = sortBillInfo(data.content);
        for (int i = 0; i < conBill.size(); i++){
            Label* name = Label::create(conBill.at(i).nickName, "Arial", 24);
            name->setTag(200+i);
            name->setAnchorPoint(Point::ANCHOR_MIDDLE);
            name->setPosition(Vec2(85+185*i, 80));
            if(conBill.at(i).nickName == UserData::getInstance()->getNickName()){
                name->setColor(Color3B(91,220,168));
            }else{
                name->setColor(Color3B(38,158,228));
            }
            cell->addChild(name);
            
            std::string imageName ="bill/yellow_num.png";
            int score =atoi(conBill.at(i).score.c_str());
            if(score<0){
                imageName="bill/purper_num.png";
            }
            std::string myScore =  ":"+StringUtil::itos(abs(score));
            
            LabelAtlas* playNum = LabelAtlas::create(myScore,imageName,20,30,'0');
            playNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
            playNum->setPosition(Vec2(85 + 185 * i, 30));
            playNum->setTag(300+i);
            cell->addChild(playNum);
        }
        
        MenuItemImage* detailImage = MenuItemImage::create("bill/arrows.png","bill/arrows.png",                                                           CC_CALLBACK_1(BillInfo::showDetailInfo, this));
        detailImage->setTag(idx);
        Menu* myMenu = Menu::create(detailImage,NULL);
        myMenu->setPosition(690,125);
        cell->addChild(myMenu);
        cell->setName(data.billId);
    }else{
        ((Label*)cell->getChildByTag(100))->setString(data.date);
        std::vector<BillContent> conBill = sortBillInfo(data.content);
        for (int i = 0; i < conBill.size(); i++){
            ((Label*)cell->getChildByTag(200+i))->setString(conBill.at(i).nickName);
            int score =atoi(conBill.at(i).score.c_str());
            std::string myScore =  ":"+StringUtil::itos(abs(score));
            if(score<0){
                Texture2D *texture = Director::getInstance()->getTextureCache()->addImage("bill/purper_num.png");
                ((LabelAtlas*)cell->getChildByTag(300+i))->setTexture(texture);
            }else{
                Texture2D *texture = Director::getInstance()->getTextureCache()->addImage("bill/yellow_num.png");
                ((LabelAtlas*)cell->getChildByTag(300+i))->setTexture(texture);
            }
            ((LabelAtlas*)cell->getChildByTag(300+i))->setString(myScore);
        }
        cell->setName(data.billId);
    }
    return cell;
}

ssize_t BillInfo::numberOfCellsInTableView(TableView *table)
{
    BillInfoAll info = GAMEDATA::getInstance()->getBillInfoAll();
    return info.bills.size();
}


void BillInfo::showDetailInfo(Ref* ref){
//    MenuItemImage* image = (MenuItemImage*)ref;
//    BillInfoAll info = GAMEDATA::getInstance()->getBillInfoAll();
}

void BillInfo::closeView(){
    this->removeFromParent();
}


void BillInfo::updateBillInfo(){
    if(NULL != getChildByTag(1000)){
        getChildByTag(1000)->removeFromParent();
    }
    showKongBill();
    tableView->reloadData();
}


void BillInfo::showKongBill(){
    if(GAMEDATA::getInstance()->getBillInfoAll().bills.size()==0){
        Label* lalala = Label::create(ChineseWord("kongzhangdan"),"arial",20);
        lalala -> setTag(1001);
        lalala->setPosition(640,360);
        addChild(lalala);
    }else{
        if(NULL != getChildByTag(1001)){
            getChildByTag(1001)->removeFromParent();
        }
    }
}

std::vector<BillContent> BillInfo::sortBillInfo(std::vector<BillContent> content){
    for (int i=1; i<content.size(); i++) {
        if(content.at(i).nickName == UserData::getInstance()->getNickName()){
            swap(content.at(i), content.at(0));
        }
    }
    return content;
}

void BillInfo::setShowPosition(){
    setIsPrivateBill(true);
    getChildByTag(100)->setVisible(false);
    getChildByTag(101)->setPositionX(890);
    getChildByTag(102)->setPositionX(1230);
    getChildByTag(103)->setPositionX(890);
    getChildByTag(104)->setPositionX(890);
    getChildByTag(105)->setPositionX(525);
}
