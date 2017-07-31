//
//  NoticeDialog.hpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/24.
//
//

#ifndef NoticeDialog_hpp
#define NoticeDialog_hpp

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
USING_NS_CC;

class NoticeDialog : public Layer{
public:
    virtual bool init() override;
    void onEnter() override;
    void onExit() override ;
    CREATE_FUNC(NoticeDialog);
    void setContentImage(std::string url1,std::string url2,std::string showTime);
private:
    Sprite* content;
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::experimental::ui::WebView* contentWebView;
#endif
    EventListenerCustom* updateContentImg;
    void closeView();
    void download();
};
#endif /* NoticeDialog_hpp */
