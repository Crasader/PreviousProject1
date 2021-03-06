#include "mahjong/common/bill/BillDetailInfo.h"
#include "mahjong/common/bill/BillInfo.h"
#include "mahjong/common/state/GameData.h"
#include "mahjong/common/utils/StringUtil.h"
#include "mahjong/common/utils/Chinese.h"
#include "mahjong/common/loading/Loading.h"
#include "mahjong/GameConfig.h"
#include "userdata/UserData.h"
#include "server/NetworkManage.h"
#include "wechat/android/CallAndroidMethod.h"
#include "wechat/ios/CallIOSMethod.h"

bool BillDetailInfo::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    auto bg0 = LayerColor::create(Color4B(0, 0, 0, 150), 1280, 720);
    addChild(bg0);
    
    MenuItem* item = MenuItem::create();
    item->setContentSize(Size(1280, 720));
    Menu* bg = Menu::create(item, NULL);
    this->addChild(bg);
    
    
    
    auto  dialogBg = Sprite::create("bill/bill_all_bg.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(BillDetailInfo::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(1075, 672);
    addChild(closeMenu);
    
    auto icon = Sprite::create("bill/bill_deetial_title.png");
    icon->setTag(1116);
    icon->setPosition(640, 648);
    addChild(icon);
    
    auto bg3 = Sprite::create("bill/detail_bg.png");
    bg3->setPosition(640, 370);
    this->addChild(bg3);
    
    BillInfoData data = GAMEDATA::getInstance()->getBillInfoData();
    
    if(data.gameType == "2"){
        isMatch =true;
    }
    std::string gameName = "苏州麻将";
    if(data.gameType == "1"){
        gameName = "红中麻将";
    }else if(data.gameType == "3"){
        gameName = "百搭麻将";
    }else if(data.gameType == "4"){
        gameName = "翻牌百搭";
    }
    Label* gameType = Label::createWithSystemFont(gameName,"Arial",22);
    gameType->setTag(90);
    gameType->setColor(Color3B(120,111,8));
    gameType->setAnchorPoint(Vec2::ZERO);
    gameType->setPosition(Vec2(290, 585));
    addChild(gameType);
    if(isMatch){
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
    }

    
    Label* date = Label::createWithSystemFont(data.date,"Arial",22);
    date->setAnchorPoint(Vec2::ZERO);
    date->setColor(Color3B(120,111,8));
    date->setPosition(440,585);
    addChild(date);
    if(isMatch){
        date->setPosition(540,585);
    }
    
    Label* fanghao = Label::createWithSystemFont("房号:","Arial",22);
    fanghao->setColor(Color3B(120,111,8));
    fanghao->setAnchorPoint(Vec2::ZERO);
    fanghao->setPosition(Vec2(670,585));
    addChild(fanghao);
    if(isMatch){
        fanghao->setVisible(false);
    }
    
    
    Label* prID = Label::createWithSystemFont(data.prid,"Arial",22);
    prID->setColor(Color3B(120,111,8));
    prID->setAnchorPoint(Vec2::ZERO);
    prID->setPosition(Vec2(720, 585));
    addChild(prID);
    if(isMatch){
        prID->setVisible(false);
    }
    
    Label* ju = Label::createWithSystemFont("局数:","Arial",22);
    ju->setColor(Color3B(120,111,8));
    ju->setAnchorPoint(Vec2::ZERO);
    ju->setPosition(Vec2(850, 585));
    addChild(ju);
    
    std::string jushuNum = "8";
    if(data.atype == "1"){
        jushuNum = "4";
    }else if(data.atype == "2"){
        jushuNum = "16";
    }
    if(isMatch){
        jushuNum = "4";
    }

    Label* jushu = Label::createWithSystemFont(jushuNum,"Arial",22);
    jushu->setColor(Color3B(120,111,8));
    jushu->setAnchorPoint(Vec2::ZERO);
    jushu->setPosition(Vec2(900, 585));
    addChild(jushu);
    
    
    Label* panshu = Label::createWithSystemFont(ChineseWord("panshu"),"arial",20);
    panshu->setColor(Color3B(112,80,0));
    panshu->setPosition(270,560);
    addChild(panshu);
    
    std::vector<BillContent> conBill = sortBillInfo(data.content);
    for(int i=0;i<conBill.size();i++){
        Label* player1 = Label::createWithSystemFont(conBill.at(i).nickName,"arial",20);
        player1->setPosition(385+150*i,560);
        if(conBill.at(i).nickName == UserData::getInstance()->getNickName()){
            player1->setColor(Color3B(158,52,37));
        }else{
            player1->setColor(Color3B(112,80,0));
        }
        
        addChild(player1);
    }
    
    Label* heji = Label::createWithSystemFont(ChineseWord("heji"),"arial",20);
    heji->setColor(Color3B(112,80,0));
    heji->setPosition(270,150);
    addChild(heji);
    
    for(int i=0;i<conBill.size();i++){
        std::string imageName ="bill/yellow_num.png";
        int score =atoi(conBill.at(i).score.c_str());
        if(score<0){
            imageName="bill/purper_num.png";
        }
        std::string myScore =  ":"+StringUtil::itos(abs(score));
        LabelAtlas* playNum = LabelAtlas::create(myScore,imageName,14,22,'0');
        playNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
        playNum->setPosition(Vec2(385+i*150, 150));
        addChild(playNum);
    }
    
    
    MenuItemImage* share = MenuItemImage::create("bill/share_bill_1.png", "bill/share_bill_2.png",
                                                 CC_CALLBACK_0(BillDetailInfo::shareBill, this));
    auto billMenu = Menu::create(share, NULL);
    billMenu->setPosition(640, 80);
    addChild(billMenu, 20);
    
    
    if(GAMEDATA::getInstance()->getBillInfoDetailAll().needInit){
        Loading* load =Loading::create(true);
        load->setTag(1000);
        addChild(load);
    }
    
    
    return true;
}

void BillDetailInfo::setIsAgencyBill(bool isAgency){
    if(NULL != getChildByTag(1116) && isAgency){
        ((Sprite*)getChildByTag(1116))->setTexture("agency/daikai_detial.png");
    }
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
        panId->setColor(Color3B(112,80,0));
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
            LabelAtlas* playerNum = LabelAtlas::create(myScore,imageName,14,22,'0');
            playerNum->setTag(100+i);
            playerNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
            playerNum->setPosition(Vec2(130+i*150, 30));
            cell->addChild(playerNum);
        }
        MenuItemImage* fengxiang = MenuItemImage::create("bill/fengxiang_1.png", "bill/fengxiang_2.png",
                                                     CC_CALLBACK_1(BillDetailInfo::shareFupan, this));
        MenuItemImage* fupan = MenuItemImage::create("bill/fupan_1.png", "bill/fupan_2.png",
                                                      CC_CALLBACK_1(BillDetailInfo::showFupan, this));
        auto fupanMenu = Menu::create();
        fupanMenu->addChild(fengxiang);
        if(GAMEDATA::getInstance()->getShowFuPanBtn()){
            fupanMenu->addChild(fupan);
        }
        if(isMatch){
            fengxiang->setVisible(false);
            fupan->setVisible(false);
        }
        fupanMenu->setTag(1001);
        fupanMenu->setName(detail.recordId);
        fupanMenu->alignItemsHorizontallyWithPadding(0);
        fupanMenu->setPosition(725, 30);
        cell->addChild(fupanMenu, 20);
        
    }else{
        
        if(NULL != cell->getChildByTag(99)){
            ((Label*)(cell->getChildByTag(99)))-> setString(StringUtils::format("%ld",idx+1));
        }
        if(NULL != cell->getChildByTag(1001)){
            ((Menu*)(cell->getChildByTag(1001)))-> setName(detail.recordId);
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
    tableView = TableView::create(this, Size(800, 360));
    tableView->setAnchorPoint(Point::ANCHOR_MIDDLE);
    tableView->setDirection(ScrollView::Direction::VERTICAL);
    tableView->setPosition(255, 175);
    tableView->setDelegate(this);
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    addChild(tableView);
    tableView->reloadData();
}


void BillDetailInfo::setPrivatePostion(){
    
//    setPosition(250,0);
}

std::vector<BillContent> BillDetailInfo::sortBillInfo(std::vector<BillContent> content){
    for (int i=1; i<content.size(); i++) {
        if(content.at(i).nickName == UserData::getInstance()->getNickName()){
            swap(content.at(i), content.at(0));
        }
    }
    return content;
}


void BillDetailInfo::shareFupan(Ref* ref){
    MenuItemImage* temp = (MenuItemImage*)ref;
    std::string fupanid = temp->getParent()->getName();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string url = StringUtils::format("%s?hbcode=%s",WECHAT_SHARE_BILL_DETAIL,GAMEDATA::getInstance()->getRedWalletRespData().hbcode.c_str());
    CallAndroidMethod::getInstance()->shareToWeChat(url,"我在跳跳苏州麻将搓麻将了，输复盘码看回放.",StringUtils::format("复盘码:%s",fupanid.c_str()) ,false);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    std::string url = StringUtils::format("%s?hbcode=%s",WECHAT_SHARE_BILL_DETAIL,GAMEDATA::getInstance()->getRedWalletRespData().hbcode.c_str());
    CallIOSMethod::getInstance()->doWechatShareWeb(url,"我在跳跳苏州麻将搓麻将了，输复盘码看回放.", StringUtils::format("复盘码:%s",fupanid.c_str()),0);
#endif
}


void BillDetailInfo::showFupan(Ref* ref){
    MenuItemImage* temp = (MenuItemImage*)ref;
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getFupanInfo(temp->getParent()->getName().c_str()));
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
        CallAndroidMethod::getInstance()->shareImageToWeChat(outputFile, false);
#endif
        
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        CallIOSMethod::getInstance()->doWechatShareImg(outputFile, 0);
#endif
    }
}


void BillDetailInfo::goBack(){
    setVisible(false);
}
