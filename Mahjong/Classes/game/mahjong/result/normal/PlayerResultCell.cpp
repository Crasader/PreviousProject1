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
    headImage->setPosition(-440, 0);
    addChild(headImage, 10);
    
    auto nickName = Label::createWithSystemFont(data.nickName,"Arial",20);
    nickName->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    nickName->setPosition(-375,15);
    addChild(nickName);
    
    auto idNumber = Label::createWithSystemFont(StringUtils::format("ID:%s",data.umark.c_str()),"Arial",20);
    idNumber->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    idNumber->setPosition(-200,15);
    addChild(idNumber);
    
    if(data.lz == "0"){
        auto fanNum = LabelAtlas::create(StringUtils::format("%s",data.fan.c_str()), "result/fan_num.png", 17, 26, '0');
        fanNum->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
        fanNum->setPosition(170,-15);
        addChild(fanNum);
        auto fanText = Sprite::create("result/fan_text.png");
        fanText->setPosition(190,-15);
        addChild(fanText);
    }else if(data.lz == "1"){
        auto lezi = Sprite::create("result/1beilezi.png");
        lezi->setPosition(190,-15);
        addChild(lezi);
    }else if(data.lz == "2"){
        auto lezi = Sprite::create("result/2beilezi.png");
        lezi->setPosition(190,-15);
        addChild(lezi);
    }else if(data.lz == "4"){
        auto lezi = Sprite::create("result/4beilezi.png");
        lezi->setPosition(190,-15);
        addChild(lezi);
    }
    if(GAMEDATA::getInstance()->getCurrentBank() ==  data.seatId){
        auto bank = Sprite::create("result/zhaung.png");
        bank->setPosition(-520,0);
        addChild(bank);
    }
    
    auto resultNum = LabelAtlas::create(StringUtils::format("%s","0"), "result/game_result_win_num.png", 40, 64, '0');
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
        
        auto huaIcon = Sprite::create("gameview/flower.png");
        huaIcon->setScale(0.7f);
        huaIcon->setPosition(-18, 28);
        addChild(huaIcon);
        auto hua = Label::createWithSystemFont(StringUtils::format("X%d",data.hua),"Arial",20);
        hua->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
        hua->setColor(Color3B(230,215,30));
        hua->setPosition(0,15);
        addChild(hua);
        
        if (data.huType != ""){
            std::vector<std::string> hutypeInfo = StringUtil::split(data.huType, ",");
            sort(hutypeInfo.begin(), hutypeInfo.end());
            std::string hu = "";
            for (int i = 0; i < hutypeInfo.size(); i++){
                if(i!=0){
                    hu += ","+ChineseWord(hutypeInfo.at(i).c_str());
                }else{
                    hu += ChineseWord(hutypeInfo.at(i).c_str());
                }
            }
            auto hutype = Label::createWithSystemFont(StringUtils::format("%s",hu.c_str()),"Arial",20);
            hutype->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
            hutype->setColor(Color3B(230,215,30));
            hutype->setPosition(60,15);
            addChild(hutype);
        }
        //胡的玩家需要单独排序
        std::vector<std::string> showPokers = StringUtil::split(data.showPoker, ",");
        vector<std::string>::iterator itor;
        for(itor=showPokers.begin();itor!=showPokers.end();)
        {
            if(GAMEDATA::getInstance()->getDiaopao()==*itor)
            {
                itor=showPokers.erase(itor);
                break;
            }
            else
            {
                itor++;
            }
        }
        showPokers.push_back(GAMEDATA::getInstance()->getDiaopao());

        for (int i = 0; i < showPokers.size(); i++){
            Jong* jong = Jong::create();
            jong->showJong(heroplayed, atoi(showPokers.at(i).c_str()));
            if(i == showPokers.size()-1){
                jong->setPosition(-350+i * 35+10, -20);
            }else{
                jong->setPosition(-350+i * 35, -20);
            }
            addChild(jong, 35 - i);
        }
        auto chuchong = Sprite::create("gameview/font_hu.png");
        chuchong->setScale(0.4f);
        chuchong->setPosition(550,-10);
        addChild(chuchong);
        
    }else{
        spritebg->setTexture("result/jie_suan_lan_fai.png");
        Texture2D *texture = Director::getInstance()->getTextureCache()->addImage("result/game_result_lose_num.png");
        resultNum->setTexture(texture);
        if(GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom){
            resultNum->setString(StringUtils::format(":%d",abs(data.jifendelta)));
        }else{
            resultNum->setString(StringUtils::format(":%d",abs(data.golddelta)));
        }
        std::vector<std::string> showPokers = StringUtil::split(data.showPoker, ",");
        for (int i = 0; i < showPokers.size(); i++){
            Jong* jong = Jong::create();
            jong->showJong(heroplayed, atoi(showPokers.at(i).c_str()));
            jong->setPosition(-350+i * 35, -20);
            addChild(jong, 35 - i);
        }
        if(data.result == 2){
            auto chuchong = Sprite::create("result/chuchong.png");
            chuchong->setPosition(550,-10);
            addChild(chuchong);
        }
    }
    if(GAMEDATA::getInstance()->getMahjongRoomType() != MahjongRoom::privateRoom){
        
        auto goldIcon =  Sprite::create("mjlobby/gold_icon.png");
        goldIcon->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        goldIcon->setPosition(240,-10);
        addChild(goldIcon);
        resultNum->setPosition(300,-10);
        resultNum->setScale(0.7f);
        resultNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        if(data.lequandelta>0){
            goldIcon->setPositionY(20);
            resultNum->setPositionY(20);
            auto lequanIcon =  Sprite::create("mjlobby/lequan_icon.png");
            lequanIcon->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
            lequanIcon->setPosition(240,-25);
            addChild(lequanIcon);
            auto lequanNum = LabelAtlas::create(StringUtils::format(":%d",data.lequandelta), "result/game_result_win_num.png", 40, 64, '0');
            lequanNum->setScale(0.7f);
            lequanNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
            lequanNum->setPosition(300,-25);
            addChild(lequanNum);
            
        }
    }else{
        auto jifenIcon =  Sprite::create("mjitem/jifen_icon.png");
        jifenIcon->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        jifenIcon->setPosition(230,-10);
        addChild(jifenIcon);

        resultNum->setScale(1.0f);
        resultNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        resultNum->setPosition(300,-10);
    }
    
    return true;
}
