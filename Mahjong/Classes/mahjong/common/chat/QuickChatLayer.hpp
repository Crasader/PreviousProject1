//
//  QuickChatLayer.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/8/16.
//
//

#ifndef QuickChatLayer_hpp
#define QuickChatLayer_hpp
#include "cocos2d.h"
#include "ui/UIListView.h"
#include "ui/UIButton.h"
USING_NS_CC;
using namespace cocos2d::ui;

class QuickChatLayer : public Layer{
public:
    virtual bool init();
    CREATE_FUNC(QuickChatLayer);
private:
    bool onTouchBegan(Touch *touch, Event  *event) override;
    void onTouchMoved(Touch *touch, Event  *event) override;
    void onTouchEnded(Touch *touch, Event  *event) override;
    void selectedItemEvent(Ref *pSender, ListView::EventType type);
    std::string getQuickChatById(int id);
};
#endif /* QuickChatLayer_hpp */
