//
//  ChatDialog.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/8/11.
//
//

#include "game/mahjong/chat/ChatDialog.hpp"
#include "server/NetworkManage.h"
#include "game/mahjong/state/GameData.h"
#include "userdata/UserData.h"

bool ChatDialog::init(){
    if(!Layer::init()){
        return false;
    }
    testData();
    
    MenuItem* item = MenuItem::create();
    item->setContentSize(Size(1280, 720));
    Menu* bg = Menu::create(item, NULL);
    this->addChild(bg);
    
    auto  dialogBg = Sprite::create("friend/dialog_bg.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(ChatDialog::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(980, 660);
    addChild(closeMenu);
    
    auto inputText = Scale9Sprite::create("mainlogin/bottom_bg.png");
    inputText->setContentSize(Size(720,500));
    inputText->setPosition(640,375);
    addChild(inputText);
    
    listView = ListView::create();
    listView->setDirection(ui::ScrollView::Direction::VERTICAL);//设置ListView布局方向
    listView->setTouchEnabled(true);//可触摸
    listView->setSize(Size(720,500));//设置ListView大小
    listView->ignoreContentAdaptWithSize(false);//开启锚点设置，false可更改锚点，true不可更改，Layer默认为point(0,0),其他Node为Point(0.5,0.5)
    listView->setAnchorPoint(Vec2(0.5, 0.5));//设置锚点，即锚点放在节点setPosition的位置，0，0：表示节点左下角；1，1：表示节点右上角；0.5，0.5表示节点中点
    listView->setPosition(Point(640,375));
    addChild(listView);
    
    auto inputBg =  Scale9Sprite::create("mainlogin/bottom_bg.png");
    inputBg->setContentSize(Size(720,81));
    inputBg->setPosition(Point(640,85));
    addChild(inputBg);
    
    auto inputField =  Scale9Sprite::create("mainlogin/bottom_bg.png");
    inputField->setContentSize(Size(650,71));
    inputField->setPosition(Point(610,85));
    addChild(inputField);
    
    MenuItemImage* image = MenuItemImage::create("chat/quick_chat_btn_1.png","chat/quick_chat_btn_2.png");
    auto quickChatBtn  = Menu::create(image,NULL);
    quickChatBtn->setPosition(895,85);
    addChild(quickChatBtn);
    
    MenuItemImage* face = MenuItemImage::create("chat/face_btn_1.png","chat/face_btn_2.png");
    auto faceChatBtn  = Menu::create(face,NULL);
    faceChatBtn->setPosition(960,85);
    addChild(faceChatBtn);
    
    //TODO
    
    showChatList();
    
    return true;
}

void ChatDialog::showChatList(){
    std::vector<ChatData> msgList = GAMEDATA::getInstance()->getChatMsgList().msgList;
    for(int i = 0;i<msgList.size();i++){
        Layout *customItem = Layout::create();
        customItem->setLayoutType(Layout::Type::ABSOLUTE);
        customItem->setContentSize(Size(720,100));
        //显示聊天的头像
        Sprite* iamge = Sprite::create();
        for(auto player : GAMEDATA::getInstance()->getPlayersInfo()){
            if(msgList.at(i).poxiaoId == player->getPoxiaoId()){
                if(player->getPicture() == "1"){
                    iamge->setTexture("gameview/head_image_1.png");
                }else if(player->getPicture() == "2"){
                    iamge->setTexture("gameview/head_image_2.png");
                }else if(player->getPicture() == "3"){
                    iamge->setTexture("gameview/head_image_3.png");
                }else if(player->getPicture() == "4"){
                    iamge->setTexture("gameview/head_image_4.png");
                }else{
                    log("服务器下发的头像图片不存在");
                    iamge->setTexture("gameview/head_image_1.png");
                }
            }
        }
        customItem->addChild(iamge);
        listView->pushBackCustomItem(customItem);
        
        std::string content = msgList.at(i).content;
        RichElementText* element = RichElementText::create(1, Color3B(255,255,255), 200, content, "arial", 20);
        RichText* text = RichText ::create();
        text->insertElement(element, 0);
        customItem->addChild(text);
        
        if(msgList.at(i).poxiaoId != UserData::getInstance()->getPoxiaoId()){
            iamge->setPosition(Point(645,30));
            text->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
            text->setPosition(Point(580,30));
        }else{
            iamge->setPosition(Point(80,30));
            text->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
            text->setPosition(Point(140,30));
        }
    }
    
}



void ChatDialog::onEnter(){
    Layer::onEnter();
    roomChatListener =  EventListenerCustom::create(MSG_PLAYER_CHAT_NOTIFY, [=](EventCustom* event){
        updateShowUI();
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(roomChatListener, 1);
}


void ChatDialog::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(roomChatListener);
}

void ChatDialog:: updateShowUI(){
    
}

void ChatDialog::closeView(){
    removeFromParent();
}


void ChatDialog::showQuickChatList(){
    

}


void ChatDialog::showFaceList(){


}


void ChatDialog::testData(){
    ChatData chatData;
    chatData.content = "hello world";
    chatData.poxiaoId = "201608151556445526C6";
    std::vector<ChatData> data = GAMEDATA::getInstance()->getChatMsgList().msgList;
    data.push_back(chatData);
    ChatMsgList list;
    list.msgList =  data;
    GAMEDATA::getInstance()->setChatMsgList(list);
}

