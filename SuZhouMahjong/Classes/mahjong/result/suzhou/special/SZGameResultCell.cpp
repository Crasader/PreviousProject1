//
//  PlayerResultCell.cpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/21.
//
//

#include "mahjong/result/suzhou/special/SZGameResultCell.hpp"
#include "mahjong/common/widget/HeadImage.hpp"
#include "mahjong/common/utils/Chinese.h"
#include "mahjong/common/utils/StringUtil.h"
#include "userdata/UserData.h"


SZGameResultCell* SZGameResultCell::create(GameResultData data){
    SZGameResultCell* cell = new SZGameResultCell();
    if(cell && cell->init(data)){
        cell -> autorelease();
        return cell;
    }
    CC_SAFE_DELETE(cell);
    return NULL;
}

bool SZGameResultCell::init(GameResultData data){
    if(!Sprite::init()){
        return false;
    }
    Sprite* bg = Sprite::create();
    bg->setTexture("result/lose_game_bg.png");
    bg->setTag(101);
    bg->setPosition(0, 0);
    this->addChild(bg, 5);
    
    auto headImage = HeadImage::createByImage(data.pic,Size(70,70));
    headImage->setPosition(-80, 155);
    addChild(headImage, 10);
    
    Label* nickname = Label::createWithSystemFont(data.nickName.c_str(), "Arial", 16);
    nickname->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    nickname->setPosition(-41,175);
    addChild(nickname, 11);
    
    Label* idNum = Label::createWithSystemFont(StringUtils::format("ID:%s",data.umark.c_str()), "Arial", 16);
    idNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    idNum->setPosition(-41,145);
    addChild(idNum, 11);
    
    
    Label* zimo = Label::createWithSystemFont(data.zimocount, "arial", 20);
    zimo->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    zimo->setPosition(100,90);
    addChild(zimo,15);
    
    Label* jiepao = Label::createWithSystemFont(data.jiepaocount, "arial", 20);
    jiepao->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    jiepao->setPosition(100,40);
    addChild(jiepao,15);
    
    Label* dianpao = Label::createWithSystemFont(data.dianpaocount,"arial",20);
    dianpao->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    dianpao->setPosition(100,-10);
    addChild(dianpao,15);
    
    Label* angang = Label::createWithSystemFont(data.angangcount, "arial", 20);
    angang->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    angang->setPosition(100,-55);
    addChild(angang,15);
    
    Label* minggang = Label::createWithSystemFont(data.minggangcount,"arial",20);
    minggang->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    minggang->setPosition(100,-105);
    addChild(minggang,15);
    
    auto resultNum = LabelAtlas::create("0", "result/spe_number_1.png", 29, 50, '0');
    resultNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
    resultNum->setPosition(0,-160);
    addChild(resultNum,20);
    
    if(data.poxiaoId == GAMEDATA::getInstance()->getResultFangzhuId()){
        auto title = Sprite::create("result/fangzhu_title.png");
        title->setPosition(-98,178);
        addChild(title,30);
    }
    
    if(GAMEDATA::getInstance()->getGameHongBaoPride().dyj == data.poxiaoId){
        auto winTitle = Sprite::create("result/win_title.png");
        winTitle->setPosition(100,220);
        addChild(winTitle,30);
    }else if(GAMEDATA::getInstance()->getGameHongBaoPride().dsj == data.poxiaoId){
        auto loseTitle = Sprite::create("result/lose_titile.png");
        loseTitle->setPosition(100,220);
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
