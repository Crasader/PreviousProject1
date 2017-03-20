//
//  QuickChatLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/8/16.
//
//
#include "mahjong/common/chat/QuickChatLayer.hpp"
#include "mahjong/common/chat/ChatDialog.hpp"


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
            chatInfo = "再打一盘我要走了拿慢慢叫白相";
            break;
        case 1:
            chatInfo = "今朝弄风头特好了";
            break;
        case 2:
            chatInfo = "今朝手气太忒班了";
            break;
        case 3:
            chatInfo = "弄打牌打的特老巨了";
            break;
        case 4:
            chatInfo = "勿要吵了，专心眼打";
            break;
        case 5:
            chatInfo = "我就等自摸了，那勿要出冲啊";
            break;
        case 6:
            chatInfo = "动作快眼，多想有啥想头";
            break;
        case 7:
            chatInfo = "今朝额骨头碰着天花板，想撒来撒";
            break;
        case 8:
            chatInfo = "辣末一盘，打好差路";
            break;
        case 9:
            chatInfo = "哪嫩意思啦，侬帮我豁大咯，侬帮我豁胖咯！";
            break;
        case 10:
            chatInfo = "朋友哪意思啦，掰种牌啊打得出来呃！";
            break;
        case 11:
            chatInfo = "哪特结棍了，放着码头跳跳啊。";
            break;
        case 12:
            chatInfo = "认得哪算我路道粗。";
            break;
        case 13:
            chatInfo = "唉，今朝霉头触到哈尔滨。";
            break;
        case 14:
            chatInfo = "今朝赢了噶西多，谢谢老板送米";
            break;
        case 15:
            chatInfo = "伐好意思，手滑打错了。";
            break;
        case 16:
            chatInfo = "桑活要弄弄清，勿能哈来来。";
            break;
        case 17:
            chatInfo = "伐弄伊三口，伐适意额。";
            break;
        case 18:
            chatInfo = "朋友，好叫，小麻将搞的的噶度组撒？";
            break;
        case 19:
            chatInfo = "伐好意思，我又要听张了";
            break;
        default:
            break;
    }
    return chatInfo;
}
