//
//  InviteCodeLayer.hpp
//  Mahjong
//
//  Created by qiuzhong on 2017/5/4.
//
//

#ifndef InviteCodeLayer_hpp
#define InviteCodeLayer_hpp

#include "cocos2d.h"
USING_NS_CC;

class InviteCodeLayer : public Layer{
public:
    virtual bool init();
    void showText(std::string msg);
    void showImage(std::string image);
    CREATE_FUNC(InviteCodeLayer);
private:
    void showDialog();
    void confirm();
    void closeView();
};

#endif /* InviteCodeLayer_hpp */
