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
    static InfoToast* create();
    void addToast(std::string msg);
    bool init();
private:
    std::vector<ToastCell*> cells;
};
#endif /* InfoTaost_hpp */
