#include "mahjong/bill/BillDetailInfo.h"
#include "mahjong/state/GameData.h"
#include "mahjong/utils/StringUtil.h"
#include "mahjong/utils/Chinese.h"
#include "mahjong/loading/Loading.h"
#include "userdata/UserData.h"
#include "server/NetworkManage.h"
#include "payment/android/CallAndroidMethod.h"
#import "payment/ios/IOSBridge.h"

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
    
    
    auto  dialogBg = Sprite::create("bill/bill_all_bg.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(BillDetailInfo::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(1040, 660);
    addChild(closeMenu);
    
    auto icon = Sprite::create("bill/bill_deetial_title.png");
    icon->setPosition(640, 668);
    addChild(icon);
    
    auto bg3 = Sprite::create("bill/detail_bg.png");
    bg3->setPosition(640, 370);
    this->addChild(bg3);
    
    BillInfoData data = GAMEDATA::getInstance()->getBillInfoData();
    
    Label* date = Label::createWithSystemFont(data.date,"Arial",22);
    date->setAnchorPoint(Vec2::ZERO);
    date->setColor(Color3B(93,182,215));
    date->setPosition(400,585);
    addChild(date);
    
    Label* fanghao = Label::createWithSystemFont("房号:","Arial",22);
    fanghao->setColor(Color3B(93,182,215));
    fanghao->setAnchorPoint(Vec2::ZERO);
    fanghao->setPosition(Vec2(600,585));
    addChild(fanghao);
    
    
    Label* prID = Label::createWithSystemFont(data.prid,"Arial",22);
    prID->setColor(Color3B(93,182,215));
    prID->setAnchorPoint(Vec2::ZERO);
    prID->setPosition(Vec2(650, 585));
    addChild(prID);
    
    Label* ju = Label::createWithSystemFont("局数:","Arial",22);
    ju->setColor(Color3B(93,182,215));
    ju->setAnchorPoint(Vec2::ZERO);
    ju->setPosition(Vec2(750, 585));
    addChild(ju);
    
    Label* jushu = Label::createWithSystemFont(data.atype == "0" ? "8": "4","Arial",22);
    jushu->setColor(Color3B(93,182,215));
    jushu->setAnchorPoint(Vec2::ZERO);
    jushu->setPosition(Vec2(800, 585));
    addChild(jushu);
    
    
    Label* panshu = Label::createWithSystemFont(ChineseWord("panshu"),"arial",20);
    panshu->setColor(Color3B(38,158,228));
    panshu->setPosition(270,560);
    addChild(panshu);
    
    std::vector<BillContent> conBill = sortBillInfo(data.content);
    for(int i=0;i<conBill.size();i++){
        Label* player1 = Label::createWithSystemFont(conBill.at(i).nickName,"arial",20);
        player1->setPosition(385+150*i,560);
        if(conBill.at(i).nickName == UserData::getInstance()->getNickName()){
            player1->setColor(Color3B(91,220,168));
        }else{
            player1->setColor(Color3B(38,158,228));
        }
        
        addChild(player1);
    }
    
    Label* heji = Label::createWithSystemFont(ChineseWord("heji"),"arial",20);
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
    
    tableView = TableView::create(this, Size(800, 360));
    tableView->setAnchorPoint(Point::ANCHOR_MIDDLE);
    tableView->setDirection(ScrollView::Direction::VERTICAL);
    tableView->setPosition(255, 175);
    tableView->setDelegate(this);
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    addChild(tableView);
    tableView->reloadData();
    
    MenuItemImage* share = MenuItemImage::create("bill/share_bill_1.png", "bill/share_bill_2.png",
                                                 CC_CALLBACK_0(BillDetailInfo::shareBill, this));
    MenuItemImage* goback = MenuItemImage::create("bill/return_btn_1.png", "bill/return_btn_2.png",
                                                  CC_CALLBACK_0(BillDetailInfo::goBack, this));
    auto billMenu = Menu::create(share,goback, NULL);
    billMenu->alignItemsHorizontallyWithPadding(50);
    billMenu->setPosition(640, 80);
    addChild(billMenu, 20);
    
    
    if(GAMEDATA::getInstance()->getBillInfoDetailAll().needInit){
        Loading* load =Loading::create(true);
        load->setTag(1000);
        addChild(load);
    }
    
    
    return true;
}

void BillDetailInfo::onEnter(){
    Layer::onEnter();
    //显示账单详情
    detailBillListener = EventListenerCustom::create(MSG_PLAYER_BILL_DETAIL, [=](EventCustom* event){
        updateBillDetail();
    });
    _eventDispatcher->addEventListenerWithFixedPriority(detailBillListener, 1);
}


void BillDetailInfo::onExit(){
    Layer::onExit();
    _eventDispatcher->removeEventListener(detailBillListener);
}

void BillDetailInfo::tableCellTouched(TableView* table, TableViewCell* cell)
{
    log("cell touched at index: %ld", cell->getIdx());
}

Size BillDetailInfo::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    return Size(600, 60);
}

TableViewCell* BillDetailInfo::tableCellAtIndex(TableView *table, ssize_t idx)
{
    auto string = StringUtils::format("%ld", idx);
    BillInfoDetailAll detailAll = GAMEDATA::getInstance()->getBillInfoDetailAll();
    BillInfoDetail detail = detailAll.detail.at(idx);
    std::vector<BillContent> conBill = sortBillInfo(detail.detail);
    TableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new (std::nothrow) TableViewCell();
        cell->autorelease();
        Label* panId = Label::createWithSystemFont(StringUtils::format("%ld",idx+1),"arial",28);
        panId->setTag(99);
        panId->setColor(Color3B(38,158,228));
        panId->setAnchorPoint(Point::ANCHOR_MIDDLE);
        panId->setPosition(15,30);
        cell->addChild(panId);
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
            playerNum->setPosition(Vec2(130+i*150, 30));
            cell->addChild(playerNum);
        }
        MenuItemImage* fengxiang = MenuItemImage::create("bill/fengxiang_1.png", "bill/fengxiang_2.png",
                                                     CC_CALLBACK_0(BillDetailInfo::shareBill, this));
        MenuItemImage* fupan = MenuItemImage::create("bill/fupan_1.png", "bill/fupan_2.png",
                                                      CC_CALLBACK_0(BillDetailInfo::goBack, this));
        auto fupanMenu = Menu::create(fengxiang,fupan, NULL);
        fupanMenu->alignItemsHorizontallyWithPadding(0);
        fupanMenu->setPosition(725, 30);
        cell->addChild(fupanMenu, 20);
        
    }else{
        
        if(NULL != cell->getChildByTag(99)){
            ((Label*)(cell->getChildByTag(99)))-> setString(StringUtils::format("%ld",idx+1));
        }
        for(int i=0;i<conBill.size();i++){
            if(NULL != cell->getChildByTag(100+i)){
                std::string imageName ="bill/yellow_num.png";
                int score =atoi(conBill.at(i).score.c_str());
                if(score<0){
                    imageName="bill/purper_num.png";
                }
                Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(imageName);
                ((LabelAtlas*)cell->getChildByTag(100+i)) ->setTexture(texture);
                std::string myScore =  ":"+StringUtil::itos(abs(score));
                ((LabelAtlas*)cell->getChildByTag(100+i)) -> setString(myScore);
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


void BillDetailInfo::shareFupan(){

}


void BillDetailInfo::showFupan(){

}

void BillDetailInfo::shareBill(){
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string path =StringUtils::format("%s/mahjong_screen_shot.png",CallAndroidMethod::getInstance()->getSdCardDir().c_str());
    log("screenShot path = %s",path.c_str());
    utils::captureScreen(CC_CALLBACK_2(BillDetailInfo::afterCaptured, this) ,path);
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    std::string path =StringUtils::format("%smahjong_screen_shot.png",FileUtils::sharedFileUtils()->getWritablePath().c_str());
    log("screenShot path = %s",path.c_str());
    utils::captureScreen(CC_CALLBACK_2(BillDetailInfo::afterCaptured, this) ,path);
#endif
}

void BillDetailInfo::afterCaptured(bool succeed, const std::string &outputFile)
{
    if (succeed) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        CallAndroidMethod::getInstance()->shareImageToWeChat("mahjong_screen_shot.png", false);
#endif
        
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        IOSBridge::getInstance()->doWechatShareImg(outputFile, 0);
#endif
    }
}


void BillDetailInfo::goBack(){
    removeFromParent();
}
