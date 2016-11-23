//
//  PlayerResultCell.cpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/21.
//
//

#include "game/mahjong/result/normal/PlayerResultCell.hpp"
#include "game/mahjong/widget/HeadImage.hpp"
#include "game/utils/Chinese.h"
#include "game/utils/StringUtil.h"
#include "userdata/UserData.h"

PlayerResultCell* PlayerResultCell::create(GameResultData data){
    PlayerResultCell* cell = new PlayerResultCell();
    if(cell && cell->init(data)){
        cell -> autorelease();
        return cell;
    }
    CC_SAFE_DELETE(cell);
    return NULL;
}

bool PlayerResultCell::init(GameResultData data){
    if(!Sprite::init()){
        return false;
    }
    //result0为平,1为自摸,2为放炮 3胡牌  4输
    auto spritebg = Sprite::create();
    addChild(spritebg);
    
    
    auto headImage = HeadImage::createByImage(data.pic,Size(90,90));
    headImage->setPosition(-420, 0);
    addChild(headImage, 10);
    
    auto nickName = Label::createWithSystemFont(data.nickName,"Arial",24);
    nickName->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    nickName->setPosition(-350,15);
    addChild(nickName);
    
    auto idNumber = Label::createWithSystemFont(StringUtils::format("ID:%s",data.umark.c_str()),"Arial",24);
    idNumber->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    idNumber->setPosition(-150,15);
    addChild(idNumber);
    
    
    auto fanNum = LabelAtlas::create(StringUtils::format("%s",data.fan.c_str()), "result/fan_num.png", 17, 26, '0');
    fanNum->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    fanNum->setPosition(220,0);
    addChild(fanNum);
    
    auto fanText = Sprite::create("result/fan_text.png");
    fanText->setPosition(240,0);
    addChild(fanText);
    
    if(GAMEDATA::getInstance()->getCurrentBank() ==  data.seatId){
        auto bank = Sprite::create("result/zhaung.png");
        bank->setPosition(-500,0);
        addChild(bank);
    }
    
    auto resultNum = LabelAtlas::create(StringUtils::format("%s","0"), "result/game_result_win_num.png", 40, 64, '0');
    resultNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
    resultNum->setPosition(360,0);
    addChild(resultNum);
    
    if(data.result == 1||data.result == 3){
        spritebg->setTexture("result/jie_suan_lan_suc.png");
        nickName->setColor(Color3B(230,215,30));
        idNumber->setColor(Color3B(230,215,30));
        Texture2D *texture = Director::getInstance()->getTextureCache()->addImage("result/game_result_win_num.png");
        resultNum->setTexture(texture);
        if(GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom){
            resultNum->setString(StringUtils::format(":%d",data.jifendelta));
        }else{
            resultNum->setString(StringUtils::format(":%d",data.golddelta));
        }
        auto hua = Label::createWithSystemFont(StringUtils::format("花X%d",data.hua),"Arial",24);
        hua->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
        hua->setColor(Color3B(230,215,30));
        hua->setPosition(0,15);
        addChild(hua);
        
        if (data.huType != ""){
            std::vector<std::string> hutypeInfo = StringUtil::split(data.huType, ",");
            std::string hu = "";
            for (int i = 0; i < hutypeInfo.size(); i++){
                hu += ChineseWord(hutypeInfo.at(i).c_str());
            }
            auto hutype = Label::createWithSystemFont(StringUtils::format("%s",hu.c_str()),"Arial",24);
            hutype->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
            hutype->setColor(Color3B(230,215,30));
            hutype->setPosition(100,15);
            addChild(hutype);
        }
        //胡的玩家需要单独排序
        std::vector<std::string> showPokers = StringUtil::split(data.showPoker, ",");
        for (int a = 0; a < showPokers.size(); a++){
            if(GAMEDATA::getInstance()->getDiaopao() == showPokers.at(a)){
                swap(showPokers.at(a), showPokers.at(showPokers.size()-1));
            }
        }
        for (int i = 0; i < showPokers.size(); i++){
            Jong* jong = Jong::create();
            jong->showJong(heroplayed, atoi(showPokers.at(i).c_str()));
            if(i == showPokers.size()-1){
                jong->setPosition(-330+i * 35+10, -20);
            }else{
                jong->setPosition(-330+i * 35, -20);
            }
            addChild(jong, 35 - i);
        }
        auto chuchong = Sprite::create("gameview/font_hu.png");
        chuchong->setScale(0.4f);
        chuchong->setPosition(500,0);
        addChild(chuchong);
        
    }else{
        spritebg->setTexture("result/jie_suan_lan_fai.png");
        Texture2D *texture = Director::getInstance()->getTextureCache()->addImage("result/game_result_lose_num.png");
        resultNum->setTexture(texture);
        if(GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom){
            resultNum->setString(StringUtils::format(":%d",data.jifendelta));
        }else{
            resultNum->setString(StringUtils::format(":%d",data.golddelta));
        }
        std::vector<std::string> showPokers = StringUtil::split(data.showPoker, ",");
        for (int i = 0; i < showPokers.size(); i++){
            Jong* jong = Jong::create();
            jong->showJong(heroplayed, atoi(showPokers.at(i).c_str()));
            jong->setPosition(-330+i * 35, -20);
            addChild(jong, 35 - i);
        }
        if(data.result == 2){
            auto chuchong = Sprite::create("result/chuchong.png");
            chuchong->setPosition(500,0);
            addChild(chuchong);
        }
    }
    
    
    return true;
}
