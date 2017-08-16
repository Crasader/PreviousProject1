//
//  LaXinLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/8/15.
//
//

#include "mahjong/lobby/share/LaXinLayer.hpp"
#include "userdata/UserData.h"
#include "wechat/android/CallAndroidMethod.h"
#include "wechat/ios/CallIOSMethod.h"
#include "mahjong/common/loading/Loading.h"
#include "server/NetworkManage.h"
#include "mahjong/common/widget/HeadImage.hpp"

bool LaXinLayer::init(){
    if(!Layer::init()){
        return false;
    }
    
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
    
    
    auto  dialogBg = Sprite::create("common/dialog_bg.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(LaXinLayer::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(990, 595);
    addChild(closeMenu);
    
    auto titile = Sprite::create("share/title_yaoqinghongbao.png");
    titile->setPosition(645,582);
    addChild(titile);
    
    
    auto yaoqingtext = Label::createWithSystemFont("", "arial", 24);
    yaoqingtext->setWidth(700);
    yaoqingtext->setAlignment(cocos2d::TextHAlignment::CENTER);
    yaoqingtext->setPosition(640,510);
    yaoqingtext->setColor(Color3B(196,106,22));
    yaoqingtext->setTag(1024);
    addChild(yaoqingtext);
    
    auto tabelViewBg = Sprite::create("share/yq_bg.png");
    tabelViewBg->setPosition(640,340);
    addChild(tabelViewBg);
    
    
    auto friendImg = MenuItemImage::create("share/share_btn_1.png", "share/share_btn_2.png",CC_CALLBACK_0(LaXinLayer::shareToFriend, this));
    auto quanImg = MenuItemImage::create("share/friend_btn_1.png", "share/friend_btn_2.png",CC_CALLBACK_0(LaXinLayer::shareToQuan, this));
    auto mymenu = Menu::create(friendImg,quanImg,NULL);
    mymenu->alignItemsHorizontallyWithPadding(30);
    mymenu->setPosition(640,165);
    addChild(mymenu);
    
    tableView = TableView::create(this, Size(720, 250));
    tableView->setAnchorPoint(Point::ANCHOR_MIDDLE);
    tableView->setDirection(ScrollView::Direction::VERTICAL);
    tableView->setPosition(285,215);
    tableView->setTag(105);
    tableView->setDelegate(this);
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    addChild(tableView);
    
    Loading* lod = Loading::create(true);
    lod->setTag(1000);
    addChild(lod);
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendLaXinDataCommand());
    
    return true;
}


void LaXinLayer::onEnter(){
    Layer::onEnter();
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_PLAYER_LA_XIN_DATA, [=](EventCustom* event){
        if(NULL != getChildByTag(1000)){
            getChildByTag(1000)->removeFromParent();
        }
        YongHuTuiGuang* heroData = static_cast<YongHuTuiGuang*>(event->getUserData());
        YongHuTuiGuang tempData = *heroData;
        if(NULL != getChildByTag(1024)){
            ((Label*)getChildByTag(1024))->setString(tempData.showText);
        }
        setYongHuTuiGuang(tempData);
        tableView->reloadData();
        
    });
}


void LaXinLayer::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(MSG_PLAYER_LA_XIN_DATA);
}

void LaXinLayer::closeView(){
    removeFromParent();
}

void LaXinLayer::shareToFriend(){
    std::string shareUrl = GAMEDATA::getInstance()->getMahjongShareData1().url;
    if(GAMEDATA::getInstance()->getMahjongShareData1().type == "1"){
        shareUrl = StringUtils::format("%s%s",shareUrl.c_str(),UserData::getInstance()->getPoxiaoId().c_str());
    }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CallAndroidMethod::getInstance()->shareToWeChat(shareUrl,GAMEDATA::getInstance()->getMahjongShareData1().phead,GAMEDATA::getInstance()->getMahjongShareData1().pcontent,false);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CallIOSMethod::getInstance()->doWechatShareWeb(shareUrl,GAMEDATA::getInstance()->getMahjongShareData1().phead,GAMEDATA::getInstance()->getMahjongShareData1().pcontent,0);
#endif
}


void LaXinLayer::shareToQuan(){
    std::string shareUrl = GAMEDATA::getInstance()->getMahjongShareData1().url;
    if(GAMEDATA::getInstance()->getMahjongShareData1().type == "1"){
        shareUrl = StringUtils::format("%s%s",shareUrl.c_str(),UserData::getInstance()->getPoxiaoId().c_str());
    }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CallAndroidMethod::getInstance()->shareToWeChat(shareUrl,GAMEDATA::getInstance()->getMahjongShareData1().head,GAMEDATA::getInstance()->getMahjongShareData1().content,true);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CallIOSMethod::getInstance()->doWechatShareWeb(shareUrl,GAMEDATA::getInstance()->getMahjongShareData1().head,GAMEDATA::getInstance()->getMahjongShareData1().content,1);
#endif
}

ssize_t LaXinLayer::numberOfCellsInTableView(TableView *table)
{
    return getYongHuTuiGuang().datas.size();
}
void LaXinLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    
}

Size LaXinLayer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    return Size(720, 90);
}

TableViewCell* LaXinLayer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    TableViewCell *cell = table->dequeueCell();
    if (cell)
    {
        cell->removeFromParentAndCleanup(true);
        cell = nullptr;
    }
    if (!cell) {
        auto data = getYongHuTuiGuang().datas.at(idx);
        
        cell = new (std::nothrow) TableViewCell();
        cell->autorelease();
        
        auto pro_bg = Sprite::create("share/jdt_bg.png");
        pro_bg->setPosition(360,45);
        cell->addChild(pro_bg);
        
        auto pro = Sprite::create("share/jdt.png");
        pro->setPosition(65,45);
        pro->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        pro->setScale(atof(data.count.c_str())/atof(data.total.c_str()), 1.0f);
        cell->addChild(pro);
        
        auto hed = Sprite::create("share/yqhy.png");
        hed->setPosition(50,45);
        cell->addChild(hed);
        
        //需要进行一次裁剪
        auto holesClipper = ClippingNode::create();
        holesClipper->setPosition(50,45);
        cell->addChild(holesClipper);
        holesClipper->setInverted(false);        //倒置显示，未被裁剪下来的剩余部分
        holesClipper->setAlphaThreshold(0.5f);  //设置alpha透明度闸值
        //[3].创建模板 : holesStencil
        auto holesStencil = Node::create();
        holesClipper->setStencil(holesStencil); //设置模板节点
        //添加一个模板遮罩 ball
        holesStencil->addChild(Sprite::create("share/yqhy.png"), -1);
        //[4].创建底板 : holes
        auto holes = HeadImage::createByImage(data.pic, Size(74,74));
        holesClipper->addChild(holes); //设置底板
        
        
        auto touzi = Sprite::create("share/tz.png");
        touzi->setPosition(230,62);
        cell->addChild(touzi);
        
        auto text1 = Label::createWithSystemFont(StringUtils::format("参加好友开房%s次(8局或以上房间)",data.count.c_str()), "arial", 13);
        text1->setWidth(104);
        text1->setColor(Color3B(126,97,55));
        text1->setPosition(230,20);
        cell->addChild(text1);
        
        auto hongbao = Sprite::create("share/hb.png");
        hongbao->setPosition(460,62);
        cell->addChild(hongbao);
        
        auto text2 = Label::createWithSystemFont(StringUtils::format("已获得现金%s元",data.money.c_str()), "arial", 13);
        text2->setWidth(104);
        text2->setColor(Color3B(126,97,55));
        text2->setPosition(460,20);
        cell->addChild(text2);
        
        auto result = Sprite::create();
        result->setPosition(660,45);
        cell->addChild(result);
        if(atoi(data.money.c_str())>0){
            result->setTexture("share/ld.png");
        }else{
            result->setTexture("share/ad.png");
        }
        
        if(atoi(data.money.c_str()) == 5){
            auto daoZhang = Sprite::create("share/ydz.png");
            daoZhang->setPosition(660,45);
            cell->addChild(daoZhang);
        }else{
            auto num = LabelAtlas::create(StringUtils::format("%s:%s",data.money.c_str(),data.total.c_str()),"share/jd_sz.png",15,21,'0');
            num->setAnchorPoint(Point::ANCHOR_MIDDLE);
            num->setPosition(660,45);
            cell->addChild(num);
        }
        
    }
    return cell;
}
