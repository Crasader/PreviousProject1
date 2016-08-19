//
//  ShopHintDialog.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/5/31.
//
//

#ifndef ShopHintDialog_hpp
#define ShopHintDialog_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class ShopHintDialog : public Layer{
public:
    virtual bool init();
    void showText(std::string msg);
    void showImage(std::string image);
    CREATE_FUNC(ShopHintDialog);
private:
    void showDialog();
    void confirm();
};
#endif /* ShopHintDialog_hpp */
