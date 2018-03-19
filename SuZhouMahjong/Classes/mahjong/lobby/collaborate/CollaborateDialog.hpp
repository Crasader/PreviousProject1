//
//  NoticeDialog.hpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/24.
//
//

#ifndef CollaborateDialog_hpp
#define CollaborateDialog_hpp

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
USING_NS_CC;

class CollaborateDialog : public Layer{
public:
    virtual bool init() override;
    void onEnter() override;
    void onExit() override ;
    CREATE_FUNC(CollaborateDialog);
    void setContentImage(std::string url);
private:
    Sprite* content;
    EventListenerCustom* updateContentImg;
    void closeView();
};
#endif /* NoticeDialog_hpp */
