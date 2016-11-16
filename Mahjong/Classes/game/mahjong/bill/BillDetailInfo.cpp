#include "game/mahjong/bill/BillDetailInfo.h"
#include "game/mahjong/state/GameData.h"
#include "payment/android/CallAndroidMethod.h"
#include "game/utils/StringUtil.h"
#include "game/utils/Chinese.h"
#include "game/mahjong/loading/Loading.h"
#include "userdata/UserData.h"
#include "server/NetworkManage.h"
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
    
    Label* date = Label::createWithSystemFont(data.date,"Arial",22);
    date->setAnchorPoint(Vec2::ZERO);
    date->setColor(Color3B(21,50,91));
    date->setPosition(400,575);
    addChild(date);
    
    Label* fanghao = Label::createWithSystemFont("房号:","Arial",22);
    fanghao->setColor(Color3B(21,50,91));
    fanghao->setAnchorPoint(Vec2::ZERO);
    fanghao->setPosition(Vec2(600,575));
    addChild(fanghao);
    
    
    Label* prID = Label::createWithSystemFont(data.prid,"Arial",22);
    prID->setColor(Color3B(21,50,91));
    prID->setAnchorPoint(Vec2::ZERO);
    prID->setPosition(Vec2(650, 575));
    addChild(prID);
    
    Label* ju = Label::createWithSystemFont("局数:","Arial",22);
    ju->setColor(Color3B(21,50,91));
    ju->setAnchorPoint(Vec2::ZERO);
    ju->setPosition(Vec2(750, 575));
    addChild(ju);
    
    Label* jushu = Label::createWithSystemFont(data.atype == "0" ? "8": "16","Arial",22);
    jushu->setColor(Color3B(21,50,91));
    jushu->setAnchorPoint(Vec2::ZERO);
    jushu->setPosition(Vec2(800, 575));
    addChild(jushu);

    
    Label* panshu = Label::createWithSystemFont(ChineseWord("panshu"),"arial",20);
    panshu->setColor(Color3B(38,158,228));
    panshu->setPosition(330,535);
    addChild(panshu);
    
    std::vector<BillContent> conBill = sortBillInfo(data.content);
    for(int i=0;i<conBill.size();i++){
        Label* player1 = Label::createWithSystemFont(conBill.at(i).nickName,"arial",20);
        player1->setPosition(460+160*i,535);
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
    
    tableView = TableView::create(this, Size(680, 320));
    tableView->setAnchorPoint(Point::ANCHOR_MIDDLE);
    tableView->setDirection(ScrollView::Direction::VERTICAL);
    tableView->setPosition(300, 185);
    tableView->setDelegate(this);
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    addChild(tableView);
    tableView->reloadData();
    
    MenuItemImage* share = MenuItemImage::create("bill/share_bill_1.png", "bill/share_bill_2.png",
                                                   CC_CALLBACK_0(BillDetailInfo::shareBill, this));
    MenuItemImage* goback = MenuItemImage::create("bill/return_btn_1.png", "bill/return_btn_2.png",
                                                 CC_CALLBACK_0(BillDetailInfo::goBack, this));
    auto billMenu = Menu::create(share,goback, NULL);
    billMenu->alignItemsHorizontallyWithPadding(10);
    billMenu->setPosition(640, 100);
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
    return Size(650, 42);
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
        Label* panId = Label::createWithSystemFont(StringUtils::format("%ld",idx+1),"arial",20);
        panId->setTag(99);
        panId->setColor(Color3B(38,158,228));
        panId->setAnchorPoint(Point::ANCHOR_MIDDLE);
        panId->setPosition(15,15);
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
            playerNum->setPosition(Vec2(145+i*160, 15));
            cell->addChild(playerNum);
        }
        
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

void BillDetailInfo::shareBill(){
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string path =StringUtils::format("%s/mahjong_screen_shot.png",CallAndroidMethod::getInstance()->getSdCardDir().c_str());
    log("screenShot path = %s",path.c_str());
    utils::captureScreen(NULL ,path);
    CallAndroidMethod::getInstance()->shareImageToWeChat("mahjong_screen_shot.png", false);
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    std::string path =StringUtils::format("%smahjong_screen_shot.png",FileUtils::sharedFileUtils()->getWritablePath().c_str());
    log("screenShot path = %s",path.c_str());
    utils::captureScreen(NULL ,path);
    IOSBridge::getInstance()->doWechatShareImg(path, 0);
#endif
}


void BillDetailInfo::goBack(){
    removeFromParent();
}
