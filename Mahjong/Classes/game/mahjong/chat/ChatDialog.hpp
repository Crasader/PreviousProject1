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
#include "cocos-ext.h"
#include "ui/UIListView.h"

USING_NS_CC;
USING_NS_CC_EXT;

class ChatDialog : public Layer{
public:
    virtual bool init();
    CREATE_FUNC(ChatDialog);
private:
    void closeView();
    cocos2d::ui::ListView* listView;
};
#endif /* ChatDialog_hpp */
