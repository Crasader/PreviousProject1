//
//  ShareSelectlayer.hpp
//  Mahjong
//
//  Created by qiuzhong on 2017/7/9.
//
//

#ifndef ShareSelectlayer_hpp
#define ShareSelectlayer_hpp

#include "cocos2d.h"
USING_NS_CC;


class ShareSelectLayer :public Layer{
public:
    virtual bool init();
    CREATE_FUNC(ShareSelectLayer);
private:
    void shareToQuan();
    void shareToFriend();
    void closeView();
};

#endif /* ShareSelectlayer_hpp */
