//
//  GongGaoItem.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/3/6.
//
//

#include "mahjong/gonggao/GongGaoItem.hpp"
#include "mahjong/GameConfig.h"
#include "http/image/UrlImageMannger.h"


GongGaoItem* GongGaoItem::create(GameActivityData gonggaoData){
    auto gongGao = new GongGaoItem();
    if(nullptr != gongGao && gongGao->init(gonggaoData)){
        gongGao->autorelease();
        return gongGao;
    }else{
        CC_SAFE_DELETE(gongGao);
        return nullptr;
    }
}

bool GongGaoItem::init(GameActivityData gonggaoData){
    if(!Layer::init()){
        return false;
    }
    myData = gonggaoData;
    content = Sprite::create();
    content->setPosition(640,360);
    addChild(content);
    
    std::string path = UrlImageMannger::getInstance()->downloadGongGaoImgByUrl(gonggaoData.imageUrl);
    if(path != IAMGE_LOADING){
        content->setTexture(path);
        if("" != gonggaoData.jumpUrl){
            MenuItem* clickUrl = MenuItem::create([=](Ref* ref){
                Application::getInstance()->openURL(gonggaoData.jumpUrl);
            });
            clickUrl->setContentSize(content->getContentSize());
            Menu* myMenu = Menu::create(clickUrl,NULL);
            myMenu->setPosition(640,360);
            addChild(myMenu);
        }
    }
    return true;
}

void GongGaoItem::onEnter(){
    Layer::onEnter();
    gongGaoImgListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(StringUtils::format("MSG_UPDATE_GONG_GAO_IMG_%s",myData.imageUrl.c_str()), [=](EventCustom* event){
        if(NULL != content){
            std::string filepath = UrlImageMannger::getInstance()->downloadGongGaoImgByUrl(myData.imageUrl);
            content->setTexture(filepath);
        }
    });
}


void GongGaoItem::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(gongGaoImgListener);
}

