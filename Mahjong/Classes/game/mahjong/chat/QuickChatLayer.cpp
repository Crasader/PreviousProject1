//
//  QuickChatLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/8/16.
//
//
#include "game/mahjong/chat/QuickChatLayer.hpp"


bool QuickChatLayer::init(){
    if(!Layer::init()){
        return false;
    }
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(QuickChatLayer::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(QuickChatLayer::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(QuickChatLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);
    
    auto quickChatBg = Sprite::create("chat/quick_chat_bg.png");
    quickChatBg->setTag(1001);
    quickChatBg->setPosition(Vec2(605,295));
    addChild(quickChatBg);
    
    ListView* listView = ListView::create();
    listView->setDirection(ui::ScrollView::Direction::VERTICAL);//设置ListView布局方向
    listView->setTouchEnabled(true);//可触摸
    listView->setContentSize(Size(620,360));//设置ListView大小
    listView->setPosition(Vec2(610,295));
    listView->setAnchorPoint(Point::ANCHOR_MIDDLE);
    listView->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(QuickChatLayer::selectedItemEvent, this));
    addChild(listView);
    
    for(int i=0; i<10;i++){
        Button* chatbutton = Button::create();
        chatbutton->setTitleText("quick chat index");
        chatbutton->setTitleFontSize(35);
        chatbutton->setTitleColor(Color3B(255,255,255));
        listView->pushBackCustomItem(chatbutton);
    }
    
    return true;
}

void QuickChatLayer::selectedItemEvent(Ref *pSender, ListView::EventType type){
    switch (type)
    {
        case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_START:
        {
            ListView* listView = static_cast<ListView*>(pSender);
            CC_UNUSED_PARAM(listView);
            CCLOG("select child start index = %ld", listView->getCurSelectedIndex());
            break;
        }
        case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END:
        {
            ListView* listView = static_cast<ListView*>(pSender);
            CC_UNUSED_PARAM(listView);
            CCLOG("select child end index = %ld", listView->getCurSelectedIndex());
            break;
        }
        default:
            break;
    }
}

bool QuickChatLayer::onTouchBegan(Touch *touch, Event  *event){
    return true;
}

void QuickChatLayer:: onTouchMoved(Touch *touch, Event  *event){
    
}

void QuickChatLayer:: onTouchEnded(Touch *touch, Event  *event){
    Rect rect = ((Sprite*)getChildByTag(1001))->getBoundingBox();
    if(!rect.containsPoint(touch->getLocation())){
        removeFromParent();
    }
}