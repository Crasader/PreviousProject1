//
//  QuickChatLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/8/16.
//
//
#include "mahjong/common/chat/QuickChatLayer.hpp"
#include "mahjong/common/chat/ChatDialog.hpp"
#include "mahjong/common/utils/Chinese.h"


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
    
    for(int i=0; i<20;i++){
        Button* chatbutton = Button::create();
        chatbutton->setTitleText(getQuickChatById(i));
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
            ((ChatDialog*)getParent())->sendQuickChat(getQuickChatById(listView->getCurSelectedIndex()));
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

std::string QuickChatLayer::getQuickChatById(int id){
    std::string chatInfo;
    switch (id) {
        case 0:
			chatInfo = ChineseWord("text_info_1");
            break;
        case 1:
			chatInfo = ChineseWord("text_info_2");
            break;
        case 2:
			chatInfo = ChineseWord("text_info_3");
            break;
        case 3:
			chatInfo = ChineseWord("text_info_4");
            break;
        case 4:
			chatInfo = ChineseWord("text_info_5");
            break;
        case 5:
			chatInfo = ChineseWord("text_info_6");
            break;
        case 6:
			chatInfo = ChineseWord("text_info_7");
            break;
        case 7:
			chatInfo = ChineseWord("text_info_8");
            break;
        case 8:
			chatInfo = ChineseWord("text_info_9");
            break;
        case 9:
			chatInfo = ChineseWord("text_info_10");
            break;
        case 10:
			chatInfo = ChineseWord("text_info_11");
            break;
        case 11:
			chatInfo = ChineseWord("text_info_12");
            break;
        case 12:
			chatInfo = ChineseWord("text_info_13");
            break;
        case 13:
			chatInfo = ChineseWord("text_info_14");
            break;
        case 14:
			chatInfo = ChineseWord("text_info_15");
            break;
        case 15:
			chatInfo = ChineseWord("text_info_16");
            break;
        case 16:
			chatInfo = ChineseWord("text_info_17");
            break;
        case 17:
			chatInfo = ChineseWord("text_info_18");
            break;
        case 18:
			chatInfo = ChineseWord("text_info_19");
            break;
        case 19:
			chatInfo = ChineseWord("text_info_20");
            break;
        default:
            break;
    }
    return chatInfo;
}
