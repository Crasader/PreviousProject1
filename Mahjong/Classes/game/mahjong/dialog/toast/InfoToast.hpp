//
//  InfoTaost.hpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/30.
//
//

#ifndef InfoTaost_hpp
#define InfoTaost_hpp
#include "cocos2d.h"
#include "game/mahjong/dialog/toast/ToastCell.hpp"
USING_NS_CC;

class InfoToast : public Layer{
public:
    static InfoToast* getInstance();
    void addToast(std::string msg);
private:
    static InfoToast* _instance;
    std::vector<ToastCell*> cells;
    InfoToast();
    ~InfoToast();
};
#endif /* InfoTaost_hpp */
