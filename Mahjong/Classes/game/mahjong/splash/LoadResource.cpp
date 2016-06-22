//
//  LoadResource.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/6.
//
//

#include "game/mahjong/splash/LoadResource.hpp"

bool LoadResource::init(){
    if(!Layer::init()){
    
        return false;
    }
    showLayer();
    return true;
}

void LoadResource::showLayer(){
    auto loadBg = Sprite::create("mainlogin/splah_bg_.png");
    loadBg->setPosition(640,360);
    addChild(loadBg);
    
    auto dragon = Sprite::create("mainlogin/loading_dragon.png");
    dragon->setPosition(640,360);
    addChild(dragon);

    auto mahjong = Sprite::create("mainlogin/loading_mahjong.png");
    mahjong->setPosition(640,360);
    addChild(mahjong);
    
    auto girl = Sprite::create("mainlogin/loading_image.png");
    girl->setPosition(640,360);
    addChild(girl);
    
    auto loadBotBg = Sprite::create("mainlogin/loading_bot_bg.png");
    loadBotBg->setPosition(640,360);
    addChild(loadBotBg);
   
    for(int i=1;i<11;i++){
        auto loadText = Sprite::create();
        loadText->setTag(100+i);
        int index =0;
        if(i>=8){
            index = 8;
        }else{
            index = i;
        }
        loadText->setTexture(cocos2d::String::createWithFormat("mainlogin/loading_text_%d.png",index)->_string);
        loadText->setPosition(120+i*45,130);
        addChild(loadText);
    }
    
    auto loadProBg = Sprite::create("mainlogin/loading_pro_bg.png");
    loadProBg->setPosition(640,60);
    addChild(loadProBg);
}