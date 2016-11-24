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
USING_NS_CC;

class NoticeDialog : public Layer{
public:
    virtual bool init();
    void onEnter() override;
    void onExit() override ;
    CREATE_FUNC(NoticeDialog);
    void setContentImage(std::string fileName);
private:
    Sprite* content;
    EventListenerCustom* updateContentImg;
    void closeView();

};
#endif /* NoticeDialog_hpp */
