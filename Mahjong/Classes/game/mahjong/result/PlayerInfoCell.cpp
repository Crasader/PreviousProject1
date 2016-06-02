//
//  PlayerInfoCell.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/26.
//
//

#include "game/mahjong/result/PlayerInfoCell.hpp"


PlayerInfoCell* PlayerInfoCell::create(GameResultData data){
    PlayerInfoCell* cell = new PlayerInfoCell();
    if(cell && cell->init(data)){
        cell -> autorelease();
        return cell;
    }
    CC_SAFE_DELETE(cell);
    return NULL;
}

bool PlayerInfoCell::init(GameResultData data){
    if(!Sprite::init()){
        return false;
    }
    std::string bgImageName;
    if(GAMEDATA::getInstance()->getIsPrivateRoom()){
        //TODO
        if(data.result==1||data.result==3){
            bgImageName = "result/player_result_4.png";
        }else{
            bgImageName = "result/player_result_3.png";
        }
    }else{
        if(data.result==1||data.result==3){
            bgImageName = "result/player_result_1.png";
        }else{
            bgImageName = "result/player_result_2.png";
        }
    }
    auto headImage = Sprite::create("gameview/head_image_1.png");
    headImage->setPosition(0, 50);
    addChild(headImage, 21);
    
    Sprite* title = Sprite::create();
    title->setPosition(0, 0);
    this->addChild(title, 21);
    
    Sprite* bg = Sprite::create(bgImageName);
    bg->setTag(101);
    bg->setPosition(0, 0);
    this->addChild(bg, 20);
    
    auto mytitle = Sprite::create();
    mytitle->setPosition(-33,80);
    addChild(mytitle,100);
    std::string imagename;
    if(data.result==1){
        mytitle->setTexture("result/zi_mo.png");
    }else if(data.result==2){
        mytitle->setTexture("result/dian_pao.png");
    }
    
    Label* nickname = Label::create(data.nickName.c_str(), "Arial", 16);
    nickname->setPosition(0, -10);
    this->addChild(nickname, 20);
    
    LabelAtlas* goldNum = LabelAtlas::create("0", "result/result_num.png", 9, 13, '0');
    if(GAMEDATA::getInstance()->getIsPrivateRoom()){
        if (data.jifendelta < 0){
            goldNum->setString(cocos2d::String::createWithFormat(";%d", abs(data.jifendelta))->_string);
        }
        else{
            goldNum->setString(cocos2d::String::createWithFormat(":%d", data.jifendelta)->_string);
        }
        
    }else{
        if (data.golddelta < 0){
            goldNum->setString(cocos2d::String::createWithFormat(";%d", abs(data.golddelta))->_string);
        }
        else{
            goldNum->setString(cocos2d::String::createWithFormat(":%d", data.golddelta)->_string);
        }
    }
    goldNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    goldNum->setPosition(-10, -40);
    this->addChild(goldNum, 20);
    
    LabelAtlas* diamondNum = LabelAtlas::create("","result/result_num.png", 9, 13, '0');
    if (data.diamonddelta < 0){
        diamondNum->setString(cocos2d::String::createWithFormat(";%d", abs(data.diamonddelta))->_string);
    }
    else{
        diamondNum->setString(cocos2d::String::createWithFormat(":%d", data.diamonddelta)->_string);
    }
    diamondNum->setPosition(-10, -65);
    diamondNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    this->addChild(diamondNum, 20);
    
    LabelAtlas* lequanNum = LabelAtlas::create(cocos2d::String::createWithFormat(":%d", data.lequandelta)->_string,
                                               "result/result_num.png", 9, 13, '0');
    lequanNum->setPosition(-10, -90);
    lequanNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    this->addChild(lequanNum, 20);
    
    return true;
}
