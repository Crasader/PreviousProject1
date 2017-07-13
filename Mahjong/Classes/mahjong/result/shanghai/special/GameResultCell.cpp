//
//  PlayerResultCell.cpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/21.
//
//

#include "mahjong/result/shanghai/special/GameResultCell.hpp"
#include "mahjong/common/widget/HeadImage.hpp"
#include "mahjong/common/utils/Chinese.h"
#include "mahjong/common/utils/StringUtil.h"
#include "userdata/UserData.h"


GameResultCell* GameResultCell::create(GameResultData data){
    GameResultCell* cell = new GameResultCell();
    if(cell && cell->init(data)){
        cell -> autorelease();
        return cell;
    }
    CC_SAFE_DELETE(cell);
    return NULL;
}

bool GameResultCell::init(GameResultData data){
    if(!Sprite::init()){
        return false;
    }
    Sprite* bg = Sprite::create();
    bg->setTexture("result/lose_game_bg.png");
    bg->setTag(101);
    bg->setPosition(0, 0);
    this->addChild(bg, 5);
    
    auto headImage = HeadImage::createByImage(data.pic,Size(70,70));
    headImage->setPosition(-80, 135);
    addChild(headImage, 10);
    
    Label* nickname = Label::createWithSystemFont(data.nickName.c_str(), "Arial", 16);
    nickname->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    nickname->setPosition(-41,155);
    addChild(nickname, 11);
    
    Label* idNum = Label::createWithSystemFont(StringUtils::format("ID:%s",data.umark.c_str()), "Arial", 16);
    idNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    idNum->setPosition(-41,125);
    addChild(idNum, 11);
    
    
    Label* win = Label::createWithSystemFont(data.win, "arial", 20);
    win->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    win->setPosition(100,50);
    addChild(win,15);
    
    Label* lost = Label::createWithSystemFont(data.lost, "arial", 20);
    lost->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    lost->setPosition(100,0);
    addChild(lost,15);
    
    Label* even = Label::createWithSystemFont(data.even,"arial",20);
    even->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    even->setPosition(100,-50);
    addChild(even,15);
    
    auto resultNum = LabelAtlas::create("0", "result/spe_number_1.png", 29, 50, '0');
    resultNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
    resultNum->setPosition(0,-120);
    addChild(resultNum,20);
    
    if(data.poxiaoId == GAMEDATA::getInstance()->getResultFangzhuId()){
        auto title = Sprite::create("result/fangzhu_title.png");
        title->setPosition(-98,158);
        addChild(title,30);
    }
    
    if(GAMEDATA::getInstance()->getGameHongBaoPride().dyj == data.poxiaoId){
        auto winTitle = Sprite::create("result/win_title.png");
        winTitle->setPosition(100,200);
        addChild(winTitle,30);
    }else if(GAMEDATA::getInstance()->getGameHongBaoPride().dsj == data.poxiaoId){
        auto loseTitle = Sprite::create("result/lose_titile.png");
        loseTitle->setPosition(100,200);
        addChild(loseTitle,30);
    }

    if(data.jifen>0){
        bg->setTexture("result/win_game_bg.png");
        Texture2D *texture = Director::getInstance()->getTextureCache()->addImage("result/spe_number_2.png");
        resultNum->setTexture(texture);
        resultNum->setString(StringUtils::format(":%d",data.jifen));
    }else{
        bg->setTexture("result/lose_game_bg.png");
        Texture2D *texture = Director::getInstance()->getTextureCache()->addImage("result/spe_number_1.png");
        resultNum->setTexture(texture);
        resultNum->setString(StringUtils::format(":%d",abs(data.jifen)));
    }
    return true;
}
