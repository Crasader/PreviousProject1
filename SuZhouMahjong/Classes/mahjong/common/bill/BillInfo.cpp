#include "mahjong/common/bill/BillInfo.h"
#include "mahjong/common/bill/BillDetailInfo.h"
#include "mahjong/common/bill/fpdialog/FupanDialog.hpp"
#include "mahjong/common/loading/Loading.h"
#include "mahjong/common/utils/StringUtil.h"
#include "mahjong/common/utils/Chinese.h"
#include "mahjong/common/dialog/prompt/HintDialog.hpp"
#include "server/NetworkManage.h"
#include "userdata/UserData.h"
#include "wechat/android/CallAndroidMethod.h"
#include "wechat/ios/CallIOSMethod.h"

bool BillInfo::init()
{
    if (!Layer::init())
    {
        return false;
    }
    auto bg0 = LayerColor::create(Color4B(0, 0, 0, 204), 1280, 720);
    addChild(bg0);
    
    MenuItem* item = MenuItem::create();
    item->setContentSize(Size(1280, 720));
    Menu* bg = Menu::create(item, NULL);
    this->addChild(bg,-1);
    
    auto  dialogBg = Sprite::create("bill/bill_all_bg.png");
    dialogBg->setTag(101);
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(BillInfo::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(1075, 672);
    closeMenu->setTag(102);
    addChild(closeMenu);
    
    auto icon = Sprite::create("bill/bill_title.png");
    icon->setPosition(640, 648);
    icon->setTag(104);
    addChild(icon);
    auto xuanyao = MenuItemImage::create("bill/share_bill_1.png","bill/share_bill_2.png",CC_CALLBACK_0(BillInfo::screenShot, this));
    auto fupan = MenuItemImage::create("bill/chakan_fupan_1.png","bill/chakan_fupan_2.png",CC_CALLBACK_0(BillInfo::checkFupan, this));
    auto shareBtn = Menu::create(fupan,xuanyao,NULL);
    shareBtn->alignItemsHorizontallyWithPadding(40);
    shareBtn->setTag(2016);
    shareBtn->setPosition(640,80);
    addChild(shareBtn);
    
    tableView = TableView::create(this, Size(832, 485));
    tableView->setAnchorPoint(Point::ANCHOR_MIDDLE);
    tableView->setDirection(ScrollView::Direction::VERTICAL);
    tableView->setPosition(225, 120);
    tableView->setTag(105);
    tableView->setDelegate(this);
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    addChild(tableView);
    tableView->reloadData();
    
    if(UserData::getInstance()->getIsAgency()){
        shareBtn->setPositionX(510);
        auto daikaibill = MenuItemImage::create("agency/daikai_btn_1.png","agency/daikai_btn_2.png",CC_CALLBACK_0(BillInfo::showAgencyBill, this));
        auto agencyBtn = Menu::create(daikaibill,NULL);
        agencyBtn->setPosition(920,80);
        agencyBtn->setTag(2017);
        addChild(agencyBtn);
    }
    
    if(GAMEDATA::getInstance()->getBillInfoAll().needInit){
        Loading* load =Loading::create(true);
        load->setTag(1000);
        addChild(load);
    }else{
        showKongBill();
    }
    return true;
}

void BillInfo::setIsAgencyBill(bool isAgency){
    setAgency(isAgency);
    if(NULL != getChildByTag(104) && isAgency){
        ((Sprite*)getChildByTag(104))->setTexture("agency/daikai_bill.png");
        if(NULL != getChildByTag(2016)){
            getChildByTag(2016)->setPositionX(640);
        }
        if(NULL != getChildByTag(2017)){
            getChildByTag(2017)->setVisible(false);
        }
    }else{
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getBillCommand());
    }
}

void BillInfo::showAgencyBill(){
     NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendAgencyBill());
}

void BillInfo::onEnter(){
    Layer::onEnter();
    //刷新账单信息
    playerBillListener = EventListenerCustom::create(MSG_PLAYER_BILL, [=](EventCustom* event){
        updateBillInfo();
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(playerBillListener, 1);

}

void BillInfo::onExit(){
    Layer::onExit();
    _eventDispatcher->removeEventListener(playerBillListener);
    
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
    BillDetailInfo* detail = BillDetailInfo::create();
    detail->setIsAgencyBill(getAgency());
    addChild(detail);
}

Size BillInfo::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    return Size(832, 138);
}

TableViewCell* BillInfo::tableCellAtIndex(TableView *table, ssize_t idx)
{
    BillInfoAll info = GAMEDATA::getInstance()->getBillInfoAll();
    TableViewCell *cell = table->dequeueCell();
    if (cell)
    {
        cell->removeFromParentAndCleanup(true);
        cell = nullptr;
    }
    if (!cell) {
        cell = new (std::nothrow) TableViewCell();
        cell->autorelease();
        BillInfoData data = info.bills.at(idx);
        std::vector<BillContent> conBill = sortBillInfo(data.content);
        
        auto sprite1 = Sprite::create("bill/bill_bg.png");
        sprite1->setAnchorPoint(Vec2::ZERO);
        sprite1->setPosition(Vec2(0, 0));
        cell->addChild(sprite1);
        
        std::string gameName = "苏州麻将";
        if(data.gameType == "1"){
            gameName = "红中麻将";
        }else if(data.gameType == "3"){
            gameName = "百搭麻将";
        }else if(data.gameType == "4"){
            gameName = "翻牌百搭";
        }
        Label* gameType = Label::createWithSystemFont(gameName,"Arial",24);
        gameType->setTag(90);
        gameType->setColor(Color3B(120,111,8));
        gameType->setAnchorPoint(Vec2::ZERO);
        gameType->setPosition(Vec2(65, 105));
        cell->addChild(gameType);
        
        Label* date = Label::createWithSystemFont(data.date,"Arial",24);
        date->setTag(100);
        date->setColor(Color3B(120,111,8));
        date->setAnchorPoint(Vec2::ZERO);
        date->setPosition(Vec2(230, 105));
        cell->addChild(date);
        
        Label* fanghao = Label::createWithSystemFont("房号:","Arial",24);
        fanghao->setColor(Color3B(120,111,8));
        fanghao->setAnchorPoint(Vec2::ZERO);
        fanghao->setPosition(Vec2(450, 105));
        fanghao->setTag(600);
        cell->addChild(fanghao);
        
        Label* prID = Label::createWithSystemFont(data.prid,"Arial",24);
        prID->setTag(400);
        prID->setColor(Color3B(120,111,8));
        prID->setAnchorPoint(Vec2::ZERO);
        prID->setPosition(Vec2(515, 105));
        cell->addChild(prID);
        
        Label* ju = Label::createWithSystemFont("局数:","Arial",24);
        ju->setColor(Color3B(120,111,8));
        ju->setAnchorPoint(Vec2::ZERO);
        ju->setPosition(Vec2(640, 105));
        cell->addChild(ju);
        
        for (int i = 0; i < conBill.size(); i++){
            Label* name = Label::createWithSystemFont(conBill.at(i).nickName, "Arial", 24);
            name->setTag(200+i);
            name->setAnchorPoint(Point::ANCHOR_MIDDLE);
            name->setPosition(Vec2(100+205*i, 70));
            if(conBill.at(i).nickName == UserData::getInstance()->getNickName()){
                name->setColor(Color3B(158,52,37));
            }else{
                name->setColor(Color3B(112,80,0));
            }
            cell->addChild(name);
            
            std::string imageName ="bill/yellow_num.png";
            int score =atoi(conBill.at(i).score.c_str());
            if(score<0){
                imageName="bill/purper_num.png";
            }
            std::string myScore =  ":"+StringUtil::itos(abs(score));
            
            LabelAtlas* playNum = LabelAtlas::create(myScore,imageName,14,22,'0');
            playNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
            playNum->setPosition(Vec2(100 + 205 * i, 35));
            playNum->setTag(300+i);
            cell->addChild(playNum);
        }
        
        MenuItemImage* detailImage = MenuItemImage::create("bill/arrows.png","bill/arrows.png",                                                           CC_CALLBACK_1(BillInfo::showDetailInfo, this));
        detailImage->setTag((int)idx);
        Menu* myMenu = Menu::create(detailImage,NULL);
        myMenu->setPosition(800,115);
        cell->addChild(myMenu);
        cell->setName(data.billId);
        
        //客户端写死de值
        std::string jushuNum = "8";
        if(data.atype == "1"){
            jushuNum = "4";
        }else if(data.atype == "2"){
            jushuNum = "16";
        }
        if(data.gameType == "2"){
            if(!UserData::getInstance()->isWeixinPayOpen()){
                int pos1 = (int)data.atype.find("8元话费");
                if(pos1>=0){
                    data.atype.replace(pos1, 10, "2张房卡");
                }
                int pos2 = (int)data.atype.find("36元话费");
                if(pos2>=0){
                    data.atype.replace(pos2, 11, "8张房卡");
                    
                }
            }
            gameType->setString(data.atype);
            date->setPosition(Vec2(330, 105));
            fanghao->setVisible(false);
            prID->setVisible(false);
            jushuNum = "4";
        }
        
        Label* jushu = Label::createWithSystemFont(StringUtils::format("%s局",jushuNum.c_str()),"Arial",24);
        jushu->setTag(401);
        jushu->setColor(Color3B(120,111,8));
        jushu->setAnchorPoint(Vec2::ZERO);
        jushu->setPosition(Vec2(695, 105));
        cell->addChild(jushu);
        
    }
//    else{
//        BillInfoData data = info.bills.at(idx);
//        std::string gameName = "苏州麻将";
//        if(data.gameType == "1"){
//            gameName = "红中麻将";
//        }else if(data.gameType == "3"){
//            gameName = "百搭麻将";
//        }else if(data.gameType == "4"){
//            gameName = "翻牌百搭";
//        }
//        ((Label*)cell->getChildByTag(90))->setString(gameName);
//        ((Label*)cell->getChildByTag(100))->setString(data.date);
//        ((Label*)cell->getChildByTag(400))->setString(data.prid);
//        std::vector<BillContent> conBill = sortBillInfo(data.content);
//        for (int i = 0; i < conBill.size(); i++){
//            if(cell->getChildByTag(200+i) != NULL )
//                ((Label*)cell->getChildByTag(200+i))->setString(conBill.at(i).nickName);
//            int score =atoi(conBill.at(i).score.c_str());
//            std::string myScore =  ":"+StringUtil::itos(abs(score));
//            Texture2D *texture;
//            if(score<0){
//                texture = Director::getInstance()->getTextureCache()->addImage("bill/purper_num.png");
//            }else{
//                texture = Director::getInstance()->getTextureCache()->addImage("bill/yellow_num.png");
//            }
//            if(NULL != cell->getChildByTag(300+i)){
//                ((LabelAtlas*)cell->getChildByTag(300+i))->setTexture(texture);
//                ((LabelAtlas*)cell->getChildByTag(300+i))->setString(myScore);
//            }
//        }
//        cell->setName(data.billId);
//        std::string jushuNum = "8";
//        if(data.atype == "1"){
//            jushuNum = "4";
//        }else if(data.atype == "2"){
//            jushuNum = "16";
//        }
//        if(data.gameType == "2"){
//            if(!UserData::getInstance()->isWeixinPayOpen()){
//                int pos1 = (int)data.atype.find("8元话费");
//                if(pos1>=0){
//                    data.atype.replace(pos1, 10, "2张房卡");
//                }
//                int pos2 = (int)data.atype.find("36元话费");
//                if(pos2>=0){
//                    data.atype.replace(pos2, 11, "8张房卡");
//                }
//            }
//            ((Label*)cell->getChildByTag(90))->setString(data.atype);
//            ((Label*)cell->getChildByTag(100))->setPosition(Vec2(330, 105));
//            ((Label*)cell->getChildByTag(600))->setVisible(false);
//            ((Label*)cell->getChildByTag(400))->setVisible(false);
//            jushuNum = "4";
//        }
//        ((Label*)cell->getChildByTag(401))->setString(jushuNum);
//    }
    return cell;
}

ssize_t BillInfo::numberOfCellsInTableView(TableView *table)
{
    BillInfoAll info = GAMEDATA::getInstance()->getBillInfoAll();
    return info.bills.size();
}


void BillInfo::showDetailInfo(Ref* ref){
    
}

void BillInfo::closeView(){
    GAMEDATA::getInstance()->setShowFuPanBtn(true);
    this->removeFromParentAndCleanup(true);
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
        if(getChildByTag(1001)==NULL){
            Label* lalala = Label::createWithSystemFont(ChineseWord("kongzhangdan"),"arial",20);
            lalala -> setTag(1001);
            if(getIsPrivateBill()){
                lalala->setPosition(900,360);
            }else{
                lalala->setPosition(640,360);
            }
            addChild(lalala);
        }
    }else{
        if(NULL != getChildByTag(1001)){
            getChildByTag(1001)->removeFromParent();
        }
        if(NULL != getChildByTag(2016)){
            if(GAMEDATA::getInstance()->getShowFuPanBtn()){
                getChildByTag(2016)->setVisible(true);
            }
            
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
    GAMEDATA::getInstance()->setShowFuPanBtn(false);
    getChildByTag(2016)->setVisible(false);
    auto xuanyao = MenuItemImage::create("bill/share_bill_1.png","bill/share_bill_2.png",CC_CALLBACK_0(BillInfo::screenShot, this));
    auto shareBtn = Menu::create(xuanyao,NULL);
    shareBtn->alignItemsHorizontallyWithPadding(50);
    shareBtn->setPosition(640,80);
    addChild(shareBtn);
}


void BillInfo::checkFupan(){
    FupanDialog* da = FupanDialog::create();
    addChild(da,10);
}

void BillInfo::screenShot(){
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string path =StringUtils::format("%s/mahjong_screen_shot.png",CallAndroidMethod::getInstance()->getSdCardDir().c_str());
    log("screenShot path = %s",path.c_str());
    utils::captureScreen(CC_CALLBACK_2(BillInfo::afterCaptured, this) ,path);
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    std::string path =StringUtils::format("%smahjong_screen_shot.png",FileUtils::getInstance()->getWritablePath().c_str());
    log("screenShot path = %s",path.c_str());
    utils::captureScreen(CC_CALLBACK_2(BillInfo::afterCaptured, this) ,path);
#endif
}

void BillInfo::afterCaptured(bool succeed, const std::string &outputFile)
{
    if (succeed) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        CallAndroidMethod::getInstance()->shareImageToWeChat(outputFile, false);
#endif
        
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        CallIOSMethod::getInstance()->doWechatShareImg(outputFile, 1);
#endif
    }
}
