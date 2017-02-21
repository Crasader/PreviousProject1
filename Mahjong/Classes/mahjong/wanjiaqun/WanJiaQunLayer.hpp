//
//  WanJiaQunLayer.hpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/9.
//
//

#ifndef WanJiaQunLayer_hpp
#define WanJiaQunLayer_hpp
#include "cocos2d.h"

USING_NS_CC;

class WanJiaQunLayer : public Layer{
public:
    virtual bool init();
    CREATE_FUNC(WanJiaQunLayer);
private:
    MenuItemToggle* qunToggle;
    MenuItemToggle* fangkaToggle;
    Sprite* wanjia;
    Sprite* daili;
    Label* wanJiaLabel;
    Label* daiLiLanel;
    Sprite* image;
    Sprite* content;
    void closeView();
    void showWanJiaQun(Ref* ref);
    void showFangkaDai(Ref* ref);
};
#endif /* WanJiaQunLayer_hpp */
