#include "game/mahjong/bill/BillDetailInfo.h"
#include "game/mahjong/state/GameData.h"
#include "game/utils/StringUtil.h"
#include "game/utils/Chinese.h"
#include "game/loading/Loading.h"
#include "userdata/UserData.h"

bool BillDetailInfo::init()
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
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(BillDetailInfo::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(980, 655);
    addChild(closeMenu);
    
    auto paodai = Sprite::create("common/piaodai_zi.png");
    paodai->setPosition(640, 660);
    this->addChild(paodai);
    auto icon = Sprite::create("bill/bill_deetial_title.png");
    icon->setPosition(640, 680);
    addChild(icon);
    
    auto bg3 = Sprite::create("bill/detail_bg.png");
    bg3->setPosition(640, 335);
    this->addChild(bg3);
    
    BillInfoData data = GAMEDATA::getInstance()->getBillInfoData();
    
    Label* date = Label::create(data.date,"Arial",22);
    date->setAnchorPoint(Point::ANCHOR_MIDDLE);
    date->setColor(Color3B(21,50,91));
    date->setPosition(640,585);
    addChild(date);
    
    Label* panshu = Label::create(ChineseWord("panshu"),"arial",20);
    panshu->setColor(Color3B(38,158,228));
    panshu->setPosition(330,535);
    addChild(panshu);
    
    std::vector<BillContent> conBill = sortBillInfo(data.content);
    for(int i=0;i<conBill.size();i++){
        Label* player1 = Label::create(conBill.at(i).nickName,"arial",20);
        player1->setPosition(460+160*i,535);
        if(conBill.at(i).nickName == UserData::getInstance()->getNickName()){
            player1->setColor(Color3B(91,220,168));
        }else{
            player1->setColor(Color3B(38,158,228));
        }

        addChild(player1);
    }
    
    Label* heji = Label::create(ChineseWord("heji"),"arial",20);
    heji->setColor(Color3B(38,158,228));
    heji->setPosition(330,157);
    addChild(heji);
    
    for(int i=0;i<4;i++){
        std::string imageName ="bill/yellow_num.png";
        int score =atoi(conBill.at(i).score.c_str());
        if(score<0){
            imageName="bill/purper_num.png";
        }
        std::string myScore =  ":"+StringUtil::itos(abs(score));
        LabelAtlas* playNum = LabelAtlas::create(myScore,imageName,20,30,'0');
        playNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
        playNum->setPosition(Vec2(455+i*150, 158));
        addChild(playNum);
    }
    
    tableView = TableView::create(this, Size(680, 320));
    tableView->setAnchorPoint(Point::ANCHOR_MIDDLE);
    tableView->setDirection(ScrollView::Direction::VERTICAL);
    tableView->setPosition(300, 185);
    tableView->setDelegate(this);
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    this->addChild(tableView);
    tableView->reloadData();
    
    if(GAMEDATA::getInstance()->getBillInfoDetailAll().needInit){
        Loading* load =Loading::create(true);
        load->setTag(1000);
        addChild(load);
    }
    return true;
}


void BillDetailInfo::tableCellTouched(TableView* table, TableViewCell* cell)
{
    log("cell touched at index: %ld", cell->getIdx());
}

Size BillDetailInfo::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    return Size(650, 40);
}

TableViewCell* BillDetailInfo::tableCellAtIndex(TableView *table, ssize_t idx)
{
    auto string = String::createWithFormat("%ld", idx);
    TableViewCell *cell = table->dequeueCell();
    BillInfoDetailAll detailAll = GAMEDATA::getInstance()->getBillInfoDetailAll();
    BillInfoDetail detail = detailAll.detail.at(idx);
    if (!cell) {
        cell = new (std::nothrow) TableViewCell();
        cell->autorelease();
        Label* panId = Label::create(cocos2d::String::createWithFormat("%ld",idx+1)->_string,"arial",20);
        panId->setTag(99);
        panId->setColor(Color3B(38,158,228));
        panId->setAnchorPoint(Point::ANCHOR_MIDDLE);
        panId->setPosition(15,15);
        cell->addChild(panId);
        std::vector<BillContent> conBill = sortBillInfo(detail.detail);
        for(int i=0;i<conBill.size();i++){
            std::string imageName ="bill/yellow_num.png";
            int score =atoi(conBill.at(i).score.c_str());
            if(score<0){
                imageName="bill/purper_num.png";
            }
            std::string myScore =  ":"+StringUtil::itos(abs(score));
            LabelAtlas* playerNum = LabelAtlas::create(myScore,imageName,20,30,'0');
            playerNum->setTag(100+i);
            playerNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
            playerNum->setPosition(Vec2(145+i*160, 15));
            cell->addChild(playerNum);
        }
    }else{
        
        if(NULL != getChildByTag(99)){
          ((Label*)getChildByTag(99))-> setString(cocos2d::String::createWithFormat("%ld",idx+1)->_string);
        }
        std::vector<BillContent> conBill = sortBillInfo(detail.detail);
        for(int i=0;i<conBill.size();i++){
            if(NULL !=getChildByTag(100+i)){
                std::string imageName ="bill/yellow_num.png";
                int score =atoi(conBill.at(i).score.c_str());
                if(score<0){
                    imageName="bill/purper_num.png";
                }
                std::string myScore =  ":"+StringUtil::itos(abs(score));
                ((Label*)getChildByTag(100+i)) -> setString(myScore);
            }
        }
    }
    return cell;
}

ssize_t BillDetailInfo::numberOfCellsInTableView(TableView *table)
{
    return GAMEDATA::getInstance()->getBillInfoDetailAll().detail.size();
}


void BillDetailInfo::closeView(){
    removeFromParent();
}


void BillDetailInfo::updateBillDetail(){
    if(NULL != getChildByTag(1000)){
        getChildByTag(1000)->removeFromParent();
    }

    tableView->reloadData();
}


void BillDetailInfo::setPrivatePostion(){
    setPosition(250,0);
}

std::vector<BillContent> BillDetailInfo::sortBillInfo(std::vector<BillContent> content){
    for (int i=1; i<content.size(); i++) {
        if(content.at(i).nickName == UserData::getInstance()->getNickName()){
            swap(content.at(i), content.at(0));
        }
    }
    return content;
}