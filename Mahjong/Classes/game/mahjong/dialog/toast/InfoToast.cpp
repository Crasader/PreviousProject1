//
//  InfoTaost.cpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/30.
//
//

#include "game/mahjong/dialog/toast/InfoToast.hpp"

InfoToast* InfoToast::_instance = NULL;

InfoToast* InfoToast::getInstance(){
    if (_instance == 0){
        _instance = new InfoToast();
    }
    return _instance;
}


void InfoToast::addToast(std::string msg){
    for(int i=0; i<cells.size();i++){
        cells.at(i)->runAction(MoveTo::create(0.3f,Point(cells.at(i)->getPositionX(),cells.at(i)->getPositionY()+70)));
    }
    schedule([=](float dt){
        ToastCell* cell = ToastCell::create(msg);
        cell->setPosition(640,300);
        addChild(cell);
        cells.push_back(cell);
    }, 0, 0, 0.32f,"toastdelay");
}


InfoToast::InfoToast(){
    
    
}


InfoToast::~InfoToast(){
    
    
}
