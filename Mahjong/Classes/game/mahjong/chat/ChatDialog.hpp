//
//  ChatDialog.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/8/11.
//
//

#ifndef ChatDialog_hpp
#define ChatDialog_hpp
#include "cocos2d.h"

USING_NS_CC;

class ChatDialog : public Layer{
public:
    virtual bool init();
    CREATE_FUNC(ChatDialog);
private:
    void closeView();
};
#endif /* ChatDialog_hpp */
