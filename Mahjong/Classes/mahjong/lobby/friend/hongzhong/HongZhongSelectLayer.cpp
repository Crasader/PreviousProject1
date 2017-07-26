//
//  HongZhongSelectLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/7/26.
//
//

#include "mahjong/lobby/friend/hongzhong/HongZhongSelectLayer.hpp"
#include "server/NetworkManage.h"
#include "mahjong/common/state/GameData.h"

bool HongZhongSelectLayer::init(){
    if(!Layer::init()){
        return false;
    }
    
    auto hongZhongRoomText = Sprite::create("openroom/hong_zhong_text.png");
    hongZhongRoomText->setPosition(755,375);
    addChild(hongZhongRoomText);
    
    auto ma159zh = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(HongZhongSelectLayer::selectMa159zh, this));
    auto ma159zhMenu = Menu::create(ma159zh,NULL);
    ma159zhMenu->setTag(3023);
    ma159zhMenu->setPosition(470,317);
    addChild(ma159zhMenu);
    
    auto ma159zhImg = Sprite::create("openroom/icon_right.png");
    ma159zhImg->setTag(3024);
    ma159zhImg->setPosition(470,317);
    addChild(ma159zhImg);
    
    auto ma159 = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(HongZhongSelectLayer::selectMa159, this));
    auto ma159Menu = Menu::create(ma159,NULL);
    ma159Menu->setTag(3025);
    ma159Menu->setPosition(705,317);
    addChild(ma159Menu);
    
    auto ma159Img = Sprite::create("openroom/icon_right.png");
    ma159Img->setTag(3026);
    ma159Img->setPosition(705,317);
    ma159Img->setVisible(false);
    addChild(ma159Img);
    
    auto ma1 = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(HongZhongSelectLayer::selectMa1, this));
    auto ma1Menu = Menu::create(ma1,NULL);
    ma1Menu->setTag(3027);
    ma1Menu->setPosition(960,317);
    addChild(ma1Menu);
    
    auto ma1Img = Sprite::create("openroom/icon_right.png");
    ma1Img->setTag(3028);
    ma1Img->setPosition(960,317);
    ma1Img->setVisible(false);
    addChild(ma1Img);
    
    auto di2 = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(HongZhongSelectLayer::selectDifen2, this));
    auto di2Menu = Menu::create(di2,NULL);
    di2Menu->setTag(3029);
    di2Menu->setPosition(470,165);
    addChild(di2Menu);
    
    auto di2Img = Sprite::create("openroom/icon_right.png");
    di2Img->setTag(3030);
    di2Img->setPosition(470,165);
    addChild(di2Img);
    
    auto di1 = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(HongZhongSelectLayer::selectDifen1, this));
    auto di1Menu = Menu::create(di1,NULL);
    di1Menu->setTag(3031);
    di1Menu->setPosition(705,165);
    addChild(di1Menu);
    
    auto di1Img = Sprite::create("openroom/icon_right.png");
    di1Img->setTag(3032);
    di1Img->setPosition(705,165);
    di1Img->setVisible(false);
    addChild(di1Img);
    
    auto di5 = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(HongZhongSelectLayer::selectDifen5, this));
    auto di5Menu = Menu::create(di5,NULL);
    di5Menu->setTag(3033);
    di5Menu->setPosition(960,165);
    addChild(di5Menu);
    
    auto di5Img = Sprite::create("openroom/icon_right.png");
    di5Img->setTag(3034);
    di5Img->setPosition(960,165);
    di5Img->setVisible(false);
    addChild(di5Img);
    
    
    return true;
}

void HongZhongSelectLayer::selectMa159zh(){
    if(NULL != getChildByTag(3024)){
        getChildByTag(3024)->setVisible(true);
    }
    if(NULL != getChildByTag(3026)){
        getChildByTag(3026)->setVisible(false);
    }
    if(NULL != getChildByTag(3028)){
        getChildByTag(3028)->setVisible(false);
    }
}


void HongZhongSelectLayer::selectMa159(){
    if(NULL != getChildByTag(3024)){
        getChildByTag(3024)->setVisible(false);
    }
    if(NULL != getChildByTag(3026)){
        getChildByTag(3026)->setVisible(true);
    }
    if(NULL != getChildByTag(3028)){
        getChildByTag(3028)->setVisible(false);
    }
}

void HongZhongSelectLayer::selectMa1(){
    if(NULL != getChildByTag(3024)){
        getChildByTag(3024)->setVisible(false);
    }
    if(NULL != getChildByTag(3026)){
        getChildByTag(3026)->setVisible(false);
    }
    if(NULL != getChildByTag(3028)){
        getChildByTag(3028)->setVisible(true);
    }
}

void HongZhongSelectLayer::selectDifen2(){
    if(NULL != getChildByTag(3030)){
        getChildByTag(3030)->setVisible(true);
    }
    if(NULL != getChildByTag(3032)){
        getChildByTag(3032)->setVisible(false);
    }
    if(NULL != getChildByTag(3034)){
        getChildByTag(3034)->setVisible(false);
    }
}


void HongZhongSelectLayer::selectDifen1(){
    if(NULL != getChildByTag(3030)){
        getChildByTag(3030)->setVisible(false);
    }
    if(NULL != getChildByTag(3032)){
        getChildByTag(3032)->setVisible(true);
    }
    if(NULL != getChildByTag(3034)){
        getChildByTag(3034)->setVisible(false);
    }
}

void HongZhongSelectLayer::selectDifen5(){
    if(NULL != getChildByTag(3030)){
        getChildByTag(3030)->setVisible(false);
    }
    if(NULL != getChildByTag(3032)){
        getChildByTag(3032)->setVisible(false);
    }
    if(NULL != getChildByTag(3034)){
        getChildByTag(3034)->setVisible(true);
    }
}

std::string HongZhongSelectLayer::getFanMa(){
    std::string fanma = "0";//0表示没有159zhong,1表示有159,2表示1码
    
    if(NULL != getChildByTag(3024)&&getChildByTag(3024)->isVisible()){
        fanma  = "4";
    }else if(NULL != getChildByTag(3026)&&getChildByTag(3026)->isVisible()){
        fanma  = "3";
    }else if(NULL != getChildByTag(3028)&&getChildByTag(3028)->isVisible()){
        fanma  = "1";
    }
    return fanma;
}
std::string HongZhongSelectLayer::getDiFen(){
    std::string difen = "2";
    if(NULL != getChildByTag(3030)&&getChildByTag(3030)->isVisible()){
        difen = "2";
    }else if(NULL != getChildByTag(3032)&&getChildByTag(3032)->isVisible()){
        difen = "1";
    }else if(NULL != getChildByTag(3034)&&getChildByTag(3034)->isVisible()){
        difen = "5";
    }
    return difen;
}
