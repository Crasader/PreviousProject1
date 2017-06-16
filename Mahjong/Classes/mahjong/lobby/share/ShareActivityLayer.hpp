//
//  WanJiaQunLayer.hpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/9.
//
//

#ifndef ShareActivityLayer_hpp
#define ShareActivityLayer_hpp
#include "cocos2d.h"

USING_NS_CC;

class ShareActivityLayer : public Layer{
public:
    virtual bool init();
    CREATE_FUNC(ShareActivityLayer);
private:
    Label* kefu;
    void closeView();
    void shareToFriend();
    void copyText();
    void toast();
};
#endif /* WanJiaQunLayer_hpp */
