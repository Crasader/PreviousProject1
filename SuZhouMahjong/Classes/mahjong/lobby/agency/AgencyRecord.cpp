//
//  AgencyRecord.cpp
//  SuZhouMahjong
//
//  Created by qiuzhong on 2017/11/27.
//

#include "mahjong/lobby/agency/AgencyRecord.hpp"
#include "mahjong/common/state/GameData.h"
#include "mahjong/common/utils/UrlEncode.hpp"
#include "mahjong/common/utils/StringUtil.h"
#include "wechat/android/CallAndroidMethod.h"
#include "wechat/ios/CallIOSMethod.h"
#include "server/NetworkManage.h"
#include "userdata/UserData.h"

bool AgencyRecord::init(){
    if(!Layer::init()){
        return false;
    }
    auto fangjianhao = Label::createWithSystemFont("房间号","arial",28);
    fangjianhao->setColor(Color3B(169,107,11));
    fangjianhao->setPosition(176,581);
    addChild(fangjianhao);
    
    auto youxileixin = Label::createWithSystemFont("游戏类型","arial",28);
    youxileixin->setColor(Color3B(169,107,11));
    youxileixin->setPosition(345,581);
    addChild(youxileixin);
    
    auto time = Label::createWithSystemFont("创建时间","arial",28);
    time->setColor(Color3B(169,107,11));
    time->setPosition(530,581);
    addChild(time);
    
    auto player = Label::createWithSystemFont("玩家","arial",28);
    player->setColor(Color3B(169,107,11));
    player->setPosition(740,581);
    addChild(player);
    
    auto caozuo = Label::createWithSystemFont("牌局进度","arial",28);
    caozuo->setColor(Color3B(169,107,11));
    caozuo->setPosition(980,581);
    addChild(caozuo);
    
    auto refresh  = MenuItemImage::create("agency/refresh_1.png", "agency/refresh_2.png",CC_CALLBACK_0(AgencyRecord::refreshRoomList, this));
    auto menu = Menu::create(refresh,NULL);
    menu->setPosition(1108,581);
    addChild(menu);
    
    recordTableView = TableView::create(this, Size(1068, 480));
    recordTableView->setAnchorPoint(Point::ANCHOR_MIDDLE);
    recordTableView->setDirection(ScrollView::Direction::VERTICAL);
    recordTableView->setPosition(105, 70);
    recordTableView->setDelegate(this);
    recordTableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    addChild(recordTableView);
    recordTableView->reloadData();
    
    return true;
}

void AgencyRecord::updateData(){
      recordTableView->reloadData();
}

void AgencyRecord::refreshRoomList(){
     NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendAgencyInfo("1"));
}

void AgencyRecord::tableCellTouched(TableView* table, TableViewCell* cell){
    
}

Size AgencyRecord::tableCellSizeForIndex(TableView *table, ssize_t idx){
     return Size(1068, 142);
}


TableViewCell* AgencyRecord::tableCellAtIndex(TableView *table, ssize_t idx){
    TableViewCell *cell = table->dequeueCell();
    if (cell)
    {
        cell->removeFromParentAndCleanup(true);
        cell = nullptr;
    }
    AgencyRecordList roomList = GAMEDATA::getInstance()->getAgencyRecordList();
    AgencyRecordData roomData = roomList.roomlist.at(idx);
    if (!cell) {
        cell = new (std::nothrow) TableViewCell();
        cell->autorelease();
        
        auto roomBg = Sprite::create("agency/box.png");
        roomBg->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
        roomBg->setPosition(0,0);
        cell->addChild(roomBg);
        
        auto roomid = Label::createWithSystemFont(roomData.roomid, "arial", 24);
        roomid->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        roomid->setColor(Color3B(160,60,0));
        roomid->setPosition(40,70);
        cell->addChild(roomid);
        
        vector<std::string> roomInfo = StringUtil::split(roomData.gameInfo,",");
        for(int k =0; k<roomInfo.size();k++){
            auto gameType = Label::createWithSystemFont(roomInfo.at(roomInfo.size()-1-k), "arial", 24);
            gameType->setAnchorPoint(Point::ANCHOR_MIDDLE);
            gameType->setColor(Color3B(160,60,0));
            gameType->setPosition(240,(140-(roomInfo.size()-1)*30)/2+k*30);
            cell->addChild(gameType);
        }
        
        auto time = Label::createWithSystemFont(roomData.createtime, "arial", 24);
        time->setAnchorPoint(Point::ANCHOR_MIDDLE);
        time->setWidth(130);
        time->setColor(Color3B(160,60,0));
        time->setPosition(425,70);
        cell->addChild(time);
        vector<std::string> name = StringUtil::split(roomData.playername,",");
        for (int i=0; i<name.size(); i++) {
            auto user = Label::createWithSystemFont(name.at(i),"arial",24);
            user->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
            user->setColor(Color3B(160,60,0));
            user->setPosition(635,(140-(name.size()-1)*30)/2+i*30);
            cell->addChild(user);
        }
        auto loadProBg = Sprite::create("agency/agency_pro_bg.png");
        loadProBg->setPosition(915,90);
        cell->addChild(loadProBg);
        
        auto loadProgerss = ProgressTimer::create(Sprite::create("agency/agency_pro_con.png"));
        loadProgerss->setPosition(915,90);
        loadProgerss->setType(ProgressTimer::Type::BAR);
        loadProgerss->setBarChangeRate(Point(1,0));//设置进程条的变化速率
        loadProgerss->setMidpoint(Point(0,1));//设置进度的运动方向
        cell->addChild(loadProgerss,1);
        vector<std::string> progressInfo = StringUtil::split(roomData.progress,"/");
        float rate = atof(progressInfo.at(0).c_str())/atof(progressInfo.at(1).c_str());
        loadProgerss->setPercentage((int)100*rate);
        auto num = LabelAtlas::create(StringUtils::format("%s:%s",progressInfo.at(0).c_str(),progressInfo.at(1).c_str()), "agency/agency_num.png", 19, 36, '0');
        num->setPosition(895,40);
        cell->addChild(num);
    }
    return cell;
}



ssize_t AgencyRecord::numberOfCellsInTableView(TableView *table){
    AgencyRecordList roomList = GAMEDATA::getInstance()->getAgencyRecordList();
    return roomList.roomlist.size();
}
