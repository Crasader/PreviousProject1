//
//  AgencyRoom.cpp
//  SuZhouMahjong
//
//  Created by qiuzhong on 2017/11/27.
//

#include "mahjong/lobby/agency/AgencyRoom.hpp"
#include "mahjong/common/state/GameData.h"
#include "mahjong/common/utils/UrlEncode.hpp"
#include "mahjong/common/utils/StringUtil.h"
#include "wechat/android/CallAndroidMethod.h"
#include "wechat/ios/CallIOSMethod.h"
#include "server/NetworkManage.h"
#include "userdata/UserData.h"

bool AgencyRoom::init(){
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
    
    auto caozuo = Label::createWithSystemFont("操作","arial",28);
    caozuo->setColor(Color3B(169,107,11));
    caozuo->setPosition(980,581);
    addChild(caozuo);
    
    auto refresh  = MenuItemImage::create("agency/refresh_1.png", "agency/refresh_2.png",CC_CALLBACK_0(AgencyRoom::refreshRoomList, this));
    auto menu = Menu::create(refresh,NULL);
    menu->setPosition(1108,581);
    addChild(menu);
    
    roomTableView = TableView::create(this, Size(1068, 480));
    roomTableView->setAnchorPoint(Point::ANCHOR_MIDDLE);
    roomTableView->setDirection(ScrollView::Direction::VERTICAL);
    roomTableView->setPosition(105, 70);
    roomTableView->setDelegate(this);
    roomTableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    addChild(roomTableView);
    roomTableView->reloadData();
    
    return true;
}

void AgencyRoom::updateData(){
    roomTableView->reloadData();
}

void AgencyRoom::refreshRoomList(){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendAgencyInfo("0"));
}

void AgencyRoom::tableCellTouched(TableView* table, TableViewCell* cell){
    
}

Size AgencyRoom::tableCellSizeForIndex(TableView *table, ssize_t idx){
    return Size(1068, 142);
}


TableViewCell* AgencyRoom::tableCellAtIndex(TableView *table, ssize_t idx){
    TableViewCell *cell = table->dequeueCell();
    if (cell)
    {
        cell->removeFromParentAndCleanup(true);
        cell = nullptr;
    }
    AgencyRoomList roomList = GAMEDATA::getInstance()->getAgencyRoomList();
    AgencyRoomData roomData = roomList.roomlist.at(idx);
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
        roomid->setPosition(30,70);
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
        auto jiesan = MenuItemImage::create("agency/jiesan_1.png", "agency/jiesan_2.png",CC_CALLBACK_1(AgencyRoom::dissolveRoom, this));
        jiesan->setName(roomData.roomid);
        jiesan->setTag(atoi(roomData.type.c_str()));
        jiesan->setScale(0.6f);
        auto jiesanMenu = Menu::create(jiesan,NULL);
        jiesanMenu->setPosition(850,70);
        cell->addChild(jiesanMenu);
        
        auto yaoqing = MenuItemImage::create("agency/yaoqin_1.png", "agency/yaoqin_2.png",CC_CALLBACK_1(AgencyRoom::inviteRoom, this));
        yaoqing->setScale(0.6f);
        yaoqing->setTag((int)idx);
        auto yaoqingMenu = Menu::create(yaoqing,NULL);
        yaoqingMenu->setPosition(990,70);
        cell->addChild(yaoqingMenu);
    }
    return cell;
}

void AgencyRoom::dissolveRoom(Ref* ref){
    MenuItemImage* temp = ( MenuItemImage* )ref;
    if(temp->getTag() == 0){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getDissolveRoomCommand(temp->getName()));
    }else  if(temp->getTag() == 1){
          NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getHZDissolveRoomCommand(temp->getName()));
    }else  if(temp->getTag() == 2){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getBDDissovleRoomReq(temp->getName()));
    }else  if(temp->getTag() == 3){
       NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getFPDissovleRoomReq(temp->getName()));
    }
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendAgencyInfo("0"));
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getPlayerInfoCommand());
}

void AgencyRoom::inviteRoom(Ref* ref){
     MenuItemImage* temp = ( MenuItemImage* )ref;
    int index = temp->getTag();
    AgencyRoomList roomList = GAMEDATA::getInstance()->getAgencyRoomList();
    AgencyRoomData roomData = roomList.roomlist.at(index);
    UrlEncode* enco = new UrlEncode();
    std::string mag = roomData.gameInfo;
    for(int i=0;i<2;i++){
        int pos = (int)mag.find(",");
        if(pos>0){
            mag.replace(pos, 1, "");
        }
    }
    std::string rule = enco->encode(mag);
    std::string zhongwen = enco->encode("等待开始");
    std::string shareUrl = GAMEDATA::getInstance()->getMahjongShareData3().url;
    std::string gameName;
    if(roomData.type == "0"){
        gameName = "苏州麻将";
    }else if(roomData.type == "1"){
        gameName = "红中麻将";
    }else if(roomData.type == "2"){
        gameName = "百度麻将";
    }else if(roomData.type == "3"){
        gameName = "翻牌百搭";
    }
    std::string roomtype = roomData.gameInfo;//房间号,房间状态,局数,人数,游戏规则
    shareUrl = StringUtils::format("%s%s&fjh=%s&fjzt=%s&js=%s&rs=%s&yxgz=%s",shareUrl.c_str(),UserData::getInstance()->getPoxiaoId().c_str(),roomData.roomid.c_str(),zhongwen.c_str(),roomData.js.c_str(),roomData.rs.c_str(),rule.c_str());
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CallAndroidMethod::getInstance()->shareToWeChat(shareUrl,StringUtils::format("跳跳%s 房号:%s %s",gameName.c_str(),roomData.roomid.c_str(),GAMEDATA::getInstance()->getMahjongShareData3().head.c_str()),StringUtils::format("%s %s",roomtype.c_str(),GAMEDATA::getInstance()->getMahjongShareData3().head.c_str()),false);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CallIOSMethod::getInstance()->doWechatShareWeb(shareUrl,StringUtils::format("跳跳%s 房号:%s %s",gameName.c_str(),roomData.roomid.c_str(),GAMEDATA::getInstance()->getMahjongShareData3().head.c_str()),StringUtils::format("%s %s",roomtype.c_str(),GAMEDATA::getInstance()->getMahjongShareData3().head.c_str()),0);
#endif
}

ssize_t AgencyRoom::numberOfCellsInTableView(TableView *table){
    AgencyRoomList roomList = GAMEDATA::getInstance()->getAgencyRoomList();
    return roomList.roomlist.size();
}
