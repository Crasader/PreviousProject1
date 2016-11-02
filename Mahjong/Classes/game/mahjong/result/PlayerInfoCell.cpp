//
//  PlayerInfoCell.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/26.
//
//

#include "game/mahjong/result/PlayerInfoCell.hpp"
#include "game/mahjong/widget/HeadImage.hpp"
#include "userdata/UserData.h"


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
    auto headImage = HeadImage::createByImage(data.pic,Size(90,90));
    headImage->setPosition(0, 30);
    addChild(headImage, 21);
    
    Sprite* title = Sprite::create();
    title->setPosition(0, 0);
    this->addChild(title, 21);
    
    Sprite* bg = Sprite::create();
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
    
    Label* nickname = Label::createWithSystemFont(data.nickName.c_str(), "Arial", 16);
    nickname->setPosition(0, -30);
    this->addChild(nickname, 20);

    
    if(GAMEDATA::getInstance()->getMahjongRoomType()==MahjongRoom::privateRoom){
        if(data.result==1||data.result==3){
            bg->setTexture("result/player_result_4.png");
        }else{
            bg->setTexture("result/player_result_3.png");
        }
        LabelAtlas* jifeng = LabelAtlas::create("","result/result_num.png", 9, 13, '0');
        if (data.jifendelta < 0){
            jifeng->setString(StringUtils::format(";%d", abs(data.jifendelta)));
        }
        else{
            jifeng->setString(StringUtils::format(":%d", data.jifendelta));
        }
        jifeng->setAnchorPoint(Point::ANCHOR_MIDDLE);
        jifeng->setPosition(10, -66);
        this->addChild(jifeng, 20);
    }else{
        if(data.result==1||data.result==3){
              bg->setTexture("result/player_result_1.png");
        }else{
             bg->setTexture("result/player_result_2.png");
        }
        LabelAtlas* goldNum = LabelAtlas::create("0", "result/result_num.png", 9, 13, '0');
        if (data.golddelta < 0){
            goldNum->setString(StringUtils::format(";%d", abs(data.golddelta)));
        }
        else{
            goldNum->setString(StringUtils::format(":%d", data.golddelta));
        }
        goldNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
        goldNum->setPosition(10, -56);
        this->addChild(goldNum, 20);
        
        LabelAtlas* lequanNum = LabelAtlas::create(StringUtils::format(":%d", data.lequandelta),
                                                   "result/result_num.png", 9, 13, '0');
        lequanNum->setPosition(10, -87);
        lequanNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
        this->addChild(lequanNum, 20);

    }
    
    
    return true;
}
