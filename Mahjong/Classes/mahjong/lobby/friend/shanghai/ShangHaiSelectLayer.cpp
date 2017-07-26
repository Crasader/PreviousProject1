//
//  ShangHaiSelectLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/7/26.
//
//

#include "mahjong/lobby/friend/shanghai/ShangHaiSelectLayer.hpp"
#include "server/NetworkManage.h"
#include "mahjong/common/state/GameData.h"


bool ShangHaiSelectLayer::init(){
    if(!Layer::init()){
        return false;
    }
    
    
    auto shangHaiRoomText = Sprite::create("openroom/shang_hai_text.png");
    shangHaiRoomText->setPosition(755,375);
    addChild(shangHaiRoomText);
    
    // 1/1无勒子
    auto leziwu11 = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(ShangHaiSelectLayer::selectLeziType1, this));
    auto leziwuMenu11 = Menu::create(leziwu11,NULL);
    leziwuMenu11->setTag(2023);
    leziwuMenu11->setPosition(470,320);
    addChild(leziwuMenu11);
    
    auto leziwuImg11 = Sprite::create("openroom/icon_right.png");
    leziwuImg11->setTag(2024);
    leziwuImg11->setPosition(470,320);
    leziwuImg11->setVisible(true);
    addChild(leziwuImg11);
    
    // 1/1 20勒子
    auto lezi1120 = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(ShangHaiSelectLayer::selectLeziType2, this));
    auto lezi1120Menu = Menu::create(lezi1120,NULL);
    lezi1120Menu->setTag(2025);
    lezi1120Menu->setPosition(705,320);
    addChild(lezi1120Menu);
    
    auto lezi1120Img = Sprite::create("openroom/icon_right.png");
    lezi1120Img->setTag(2026);
    lezi1120Img->setPosition(705,320);
    lezi1120Img->setVisible(false);
    addChild(lezi1120Img);
    
    // 1/1 50勒子
    
    auto lezi1150 = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(ShangHaiSelectLayer::selectLeziType3, this));
    auto lezi1150Menu = Menu::create(lezi1150,NULL);
    lezi1150Menu->setTag(2027);
    lezi1150Menu->setPosition(960,320);
    addChild(lezi1150Menu);
    
    auto lezi1150Img = Sprite::create("openroom/icon_right.png");
    lezi1150Img->setTag(2028);
    lezi1150Img->setPosition(960,320);
    lezi1150Img->setVisible(false);
    addChild(lezi1150Img);
    
    
    
    // 2/2 40勒子
    
    auto lezi2240 = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(ShangHaiSelectLayer::selectLeziType5, this));
    auto lezi2240Menu = Menu::create(lezi2240,NULL);
    lezi2240Menu->setTag(2031);
    lezi2240Menu->setPosition(470,240);
    addChild(lezi2240Menu);
    
    auto lezi2240Img = Sprite::create("openroom/icon_right.png");
    lezi2240Img->setTag(2032);
    lezi2240Img->setPosition(470,240);
    lezi2240Img->setVisible(false);
    addChild(lezi2240Img);
    
    // 2/2 100勒子
    auto lezi22100 = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(ShangHaiSelectLayer::selectLeziType6, this));
    auto lezi22100Menu = Menu::create(lezi22100,NULL);
    lezi22100Menu->setTag(2033);
    lezi22100Menu->setPosition(705,240);
    addChild(lezi22100Menu);
    
    auto lezi22100Img = Sprite::create("openroom/icon_right.png");
    lezi22100Img->setTag(2034);
    lezi22100Img->setPosition(705,240);
    lezi22100Img->setVisible(false);
    addChild(lezi22100Img);
    
    //无开宝
    auto wukaibao = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(ShangHaiSelectLayer::selectWukaibao, this));
    auto wukaibaoMenu = Menu::create(wukaibao,NULL);
    wukaibaoMenu->setTag(2035);
    wukaibaoMenu->setPosition(470,160);
    addChild(wukaibaoMenu);
    
    auto selectWukaibao = Sprite::create("openroom/icon_right.png");
    selectWukaibao->setTag(2036);
    selectWukaibao->setPosition(470,160);
    selectWukaibao->setVisible(false);
    addChild(selectWukaibao);
    
    //二摸三冲
    auto mo2chong3 = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(ShangHaiSelectLayer::select2mo3chong, this));
    auto mo2chong3Menu = Menu::create(mo2chong3,NULL);
    mo2chong3Menu->setPosition(705,160);
    mo2chong3Menu->setTag(2037);
    addChild(mo2chong3Menu);
    
    auto selectmo2chong3 = Sprite::create("openroom/icon_right.png");
    selectmo2chong3->setTag(2038);
    selectmo2chong3->setPosition(705,160);
    selectmo2chong3->setVisible(false);
    addChild(selectmo2chong3);
    
    return true;
}

void ShangHaiSelectLayer::selectLeziType1(){
    if(NULL != getChildByTag(2024)){
        getChildByTag(2024)->setVisible(true);
    }
    if(NULL != getChildByTag(2026)){
        getChildByTag(2026)->setVisible(false);
    }
    if(NULL != getChildByTag(2028)){
        getChildByTag(2028)->setVisible(false);
    }
    if(NULL != getChildByTag(2032)){
        getChildByTag(2032)->setVisible(false);
    }
    if(NULL != getChildByTag(2034)){
        getChildByTag(2034)->setVisible(false);
    }
}

void ShangHaiSelectLayer::selectLeziType2(){
    if(NULL != getChildByTag(2024)){
        getChildByTag(2024)->setVisible(false);
    }
    if(NULL != getChildByTag(2026)){
        getChildByTag(2026)->setVisible(true);
    }
    if(NULL != getChildByTag(2028)){
        getChildByTag(2028)->setVisible(false);
    }
    if(NULL != getChildByTag(2032)){
        getChildByTag(2032)->setVisible(false);
    }
    if(NULL != getChildByTag(2034)){
        getChildByTag(2034)->setVisible(false);
    }
}

void ShangHaiSelectLayer::selectLeziType3(){
    if(NULL != getChildByTag(2024)){
        getChildByTag(2024)->setVisible(false);
    }
    if(NULL != getChildByTag(2026)){
        getChildByTag(2026)->setVisible(false);
    }
    if(NULL != getChildByTag(2028)){
        getChildByTag(2028)->setVisible(true);
    }
    if(NULL != getChildByTag(2032)){
        getChildByTag(2032)->setVisible(false);
    }
    if(NULL != getChildByTag(2034)){
        getChildByTag(2034)->setVisible(false);
    }
}

void ShangHaiSelectLayer::selectLeziType4(){
    if(NULL != getChildByTag(2024)){
        getChildByTag(2024)->setVisible(false);
    }
    if(NULL != getChildByTag(2026)){
        getChildByTag(2026)->setVisible(false);
    }
    if(NULL != getChildByTag(2028)){
        getChildByTag(2028)->setVisible(false);
    }
    if(NULL != getChildByTag(2032)){
        getChildByTag(2032)->setVisible(false);
    }
    if(NULL != getChildByTag(2034)){
        getChildByTag(2034)->setVisible(false);
    }
}

void ShangHaiSelectLayer::selectLeziType5(){
    if(NULL != getChildByTag(2024)){
        getChildByTag(2024)->setVisible(false);
    }
    if(NULL != getChildByTag(2026)){
        getChildByTag(2026)->setVisible(false);
    }
    if(NULL != getChildByTag(2028)){
        getChildByTag(2028)->setVisible(false);
    }
    if(NULL != getChildByTag(2032)){
        getChildByTag(2032)->setVisible(true);
    }
    if(NULL != getChildByTag(2034)){
        getChildByTag(2034)->setVisible(false);
    }
}

void ShangHaiSelectLayer::selectLeziType6(){
    if(NULL != getChildByTag(2024)){
        getChildByTag(2024)->setVisible(false);
    }
    if(NULL != getChildByTag(2026)){
        getChildByTag(2026)->setVisible(false);
    }
    if(NULL != getChildByTag(2028)){
        getChildByTag(2028)->setVisible(false);
    }
    if(NULL != getChildByTag(2032)){
        getChildByTag(2032)->setVisible(false);
    }
    if(NULL != getChildByTag(2034)){
        getChildByTag(2034)->setVisible(true);
    }
}


void ShangHaiSelectLayer::selectWukaibao(){
    if(NULL != getChildByTag(2036)){
        getChildByTag(2036)->setVisible(!getChildByTag(2036)->isVisible());
    }
}

void ShangHaiSelectLayer::select2mo3chong(){
    if(NULL != getChildByTag(2038)){
        getChildByTag(2038)->setVisible(!getChildByTag(2038)->isVisible());
    }
}

std::string ShangHaiSelectLayer::getLeizi(){
    int iflezi = 0;//0表示(1/1 无勒子),1表示(1/1 20勒子),2表示(1/1 50勒子),3表示(2/2 无勒子),4表示(2/2 40勒子),5表示(2/2 100勒子)
    if(NULL != getChildByTag(2024)&&getChildByTag(2024)->isVisible()){
        iflezi = LeziType::type1100;
    }else if(NULL != getChildByTag(2026)&&getChildByTag(2026)->isVisible()){
        iflezi = LeziType::type1120;
    }else if(NULL != getChildByTag(2028)&&getChildByTag(2028)->isVisible()){
        iflezi = LeziType::type1150;
    }
    else if(NULL != getChildByTag(2032)&&getChildByTag(2032)->isVisible()){
        iflezi = LeziType::type2240;
    }else if(NULL != getChildByTag(2034)&&getChildByTag(2034)->isVisible()){
        iflezi = LeziType::type22100;
    }
    return StringUtils::format("%d",iflezi) ;
}


std::string ShangHaiSelectLayer::getEmsc(){
    std::string ifemsc = "0";//0表示没有，1表示有
    if(NULL != getChildByTag(2038)){
        if(getChildByTag(2038)->isVisible()){
            ifemsc = "1";
        }else{
            ifemsc = "0";
        }
    }
    return ifemsc;
}


std::string ShangHaiSelectLayer::getKaibao(){
    std::string ifkb = "1";//0表示没有，1表示有
    if(NULL != getChildByTag(2036)){
        if(getChildByTag(2036)->isVisible()){
            ifkb = "0";
        }else{
            ifkb = "1";
        }
    }
    return ifkb;
}


