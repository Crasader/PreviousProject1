//
//  PlayerResultCell.cpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/21.
//
//

#include "game/mahjong/result/special/GameResultCell.hpp"
#include "game/mahjong/widget/HeadImage.hpp"
#include "game/utils/Chinese.h"
#include "game/utils/StringUtil.h"
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
    bg->setTag(101);
    bg->setPosition(0, 0);
    this->addChild(bg, 5);
    
    auto headImage = HeadImage::createByImage(data.pic,Size(70,70));
    headImage->setPosition(-55, 105);
    addChild(headImage, 10);
    
    Label* nickname = Label::createWithSystemFont(data.nickName.c_str(), "Arial", 16);
    nickname->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    nickname->setPosition(-16,125);
    addChild(nickname, 11);
    
    Label* idNum = Label::createWithSystemFont(StringUtils::format("ID:%s",data.umark.c_str()), "Arial", 16);
    idNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    idNum->setPosition(-16,95);
    addChild(idNum, 11);
    
    
    LabelAtlas* win = LabelAtlas::create(data.win,"result/result_game_num.png", 14, 20, '0');
    win->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    win->setPosition(80,28);
    addChild(win,15);
    
    LabelAtlas* lost = LabelAtlas::create(data.lost,"result/result_game_num.png", 14, 20, '0');
    lost->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    lost->setPosition(80,-15);
    addChild(lost,15);
    
    LabelAtlas* even = LabelAtlas::create(data.even,"result/result_game_num.png", 14, 20, '0');
    even->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    even->setPosition(80,-58);
    addChild(even,15);
    
    auto resultNum = LabelAtlas::create("0", "result/fan_num.png", 17, 26, '0');
    resultNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
    resultNum->setPosition(0,-120);
    addChild(resultNum,20);
    
    if(data.poxiaoId == GAMEDATA::getInstance()->getFangZhuId()){
        auto title = Sprite::create("result/fangzhu_title.png");
        title->setPosition(-70,130);
        addChild(title,30);
    }
    
    if(data.jifen>0){
        bg->setTexture("result/win_game_bg.png");
        //        resultNum->setTexture(<#cocos2d::Texture2D *texture#>);
        resultNum->setString(StringUtils::format("%d",data.jifen));
    }else{
        bg->setTexture("result/lose_game_bg.png");
        //        resultNum->setTexture(<#cocos2d::Texture2D *texture#>);
        resultNum->setString(StringUtils::format("%d",data.jifen));
    }
    return true;
}
