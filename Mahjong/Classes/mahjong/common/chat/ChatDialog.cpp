//
//  ChatDialog.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/8/11.
//
//

#include "mahjong/common/chat/ChatDialog.hpp"
#include "mahjong/common/chat/QuickChatLayer.hpp"
#include "mahjong/common/chat/FaceChatLayer.hpp"
#include "mahjong/common/chat/PlayerChatManage.hpp"
#include "mahjong/common/utils/StringUtil.h"
#include "mahjong/common/widget/HeadImage.hpp"
#include "server/NetworkManage.h"
#include "userdata/UserData.h"

ChatDialog* ChatDialog::create(){
    ChatDialog* cell = new ChatDialog();
    if(cell&& cell->init()){
        cell->autorelease();
        return cell;
    }
    CC_SAFE_DELETE(cell);
    return NULL;
}

bool ChatDialog::init(){
    if(!Layer::init()){
        return false;
    }
    auto bg0 = LayerColor::create(Color4B(0, 0, 0, 100), 1280, 720);
    addChild(bg0);
    
    MenuItem* item = MenuItem::create();
    item->setContentSize(Size(1280, 720));
    Menu* bg = Menu::create(item, NULL);
    this->addChild(bg);
    
    auto  dialogBg = Sprite::create("chat/chat_big_bg.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(ChatDialog::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(1000, 680);
    addChild(closeMenu);
    
    auto inputText = ui::Scale9Sprite::create("mainlogin/bottom_bg.png");
    inputText->setContentSize(Size(720,500));
    inputText->setPosition(640,375);
    addChild(inputText);
    
    listView = ListView::create();
    listView->setDirection(ui::ScrollView::Direction::VERTICAL);//设置ListView布局方向
    listView->setTouchEnabled(true);//可触摸
    listView->setContentSize(Size(720,480));//设置ListView大小
    listView->ignoreContentAdaptWithSize(false);//开启锚点设置，false可更改锚点，true不可更改，Layer默认为point(0,0),其他Node为Point(0.5,0.5)
    listView->setAnchorPoint(Vec2(0.5, 0.5));//设置锚点，即锚点放在节点setPosition的位置，0，0：表示节点左下角；1，1：表示节点右上角；0.5，0.5表示节点中点
    listView->setPosition(Point(640,375));
    addChild(listView);
    
    auto inputBg =  ui::Scale9Sprite::create("mainlogin/bottom_bg.png");
    inputBg->setContentSize(Size(720,81));
    inputBg->setPosition(Point(640,85));
    addChild(inputBg);
    
    auto inputField =  ui::Scale9Sprite::create("chat/bottom_bg.png");
    inputField->setContentSize(Size(557,71));
    inputField->setPosition(Point(565,85));
    addChild(inputField);
    
    MenuItemImage* image = MenuItemImage::create("chat/quick_chat_btn_1.png","chat/quick_chat_btn_2.png",CC_CALLBACK_0(ChatDialog::showQuickChatList, this));
    auto quickChatBtn  = Menu::create(image,NULL);
    quickChatBtn->setPosition(805,85);
    addChild(quickChatBtn);
    if(GAMEDATA::getInstance()->getGameType() == 3 && !UserData::getInstance()->isFangYan()){
        quickChatBtn->setVisible(false);
    }
    
    MenuItemImage* face = MenuItemImage::create("chat/face_btn_1.png","chat/face_btn_2.png",CC_CALLBACK_0(ChatDialog::showFaceList, this));
    auto faceChatBtn  = Menu::create(face,NULL);
    faceChatBtn->setPosition(865,85);
    addChild(faceChatBtn);
    
    MenuItemImage* snd = MenuItemImage::create("chat/send_btn_1.png","chat/send_btn_2.png",CC_CALLBACK_0(ChatDialog::sendMessage, this));
    auto sendBtn  = Menu::create(snd,NULL);
    sendBtn->setPosition(942,85);
    addChild(sendBtn);
    
    ui::EditBox* field = ui::EditBox::create(Size(500,71), ui::Scale9Sprite::create());
    field->setTag(1001);
    field->setPosition(Point(545,85));
    addChild(field);
    
    showChatList();//显示聊天列表
    
    return true;
}



void ChatDialog::showChatList(){
    RoomChatMsgList list = GAMEDATA::getInstance()->getRoomChatMsgList();
    if(list.msgList.size()==0){
        return;
    }
    for(int i = 0;i<list.msgList.size();i++){
        showChatInfo(list.msgList.at(i));
    }
}



void ChatDialog::onEnter(){
    Layer::onEnter();
    roomChatListener =  EventListenerCustom::create(MSG_PLAYER_ROOM_CHAT_SHOW, [=](EventCustom* event){
        showChatInfo(GAMEDATA::getInstance()->getChatData());
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(roomChatListener, 1);
}


void ChatDialog::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(roomChatListener);
}

void ChatDialog:: showChatInfo(ChatData data){
    
    if(!data.mark){
        Layout *customItem = Layout::create();
        customItem->setLayoutType(Layout::Type::ABSOLUTE);
        customItem->setContentSize(Size(720,100));
        //显示聊天的头像
        HeadImage* iamge;
        bool find = false;
        for(auto player : GAMEDATA::getInstance()->getPlayersInfo()){
            if(data.poxiaoId == player->getPoxiaoId()){
                iamge = HeadImage::createByImage(player->getPicture(),Size(70,70));
                find = true;
            }
        }
        if(!find){
            iamge = HeadImage::createByImage("unknow",Size(70,70));
        }
        customItem->addChild(iamge);
        listView->pushBackCustomItem(customItem);
        listView->jumpToBottom();
        std::string content = data.content;
        if(content.size()>0){
            vector<std::string> msgs = PlayerChatManage::getInstance()->splitContentByFace(content);
            RichText* text = RichText ::create();
            text->setAnchorPoint(Point::ANCHOR_MIDDLE);
            for(auto var : msgs){
                if(!PlayerChatManage::getInstance()->isFaceImage(var)){
                    RichElementText* element1 = RichElementText::create(1, Color3B(255,255,255), 255, var, "arial", 20);
                    text->pushBackElement(element1);
                    text->formatText();
                }else{
                    RichElementImage* element2 = RichElementImage::create(1, Color3B(255,255,255), 255, PlayerChatManage::getInstance()->getFaceImageName(var));
                    text->pushBackElement(element2);
                    text->formatText();
                }
            }
            customItem->addChild(text,1);
            auto bob = ui::Scale9Sprite::create("chat/text_bob.png", Rect(0, 0, 66, 66), Rect(37, 0, 10, 0));
            bob->setContentSize(Size(text->getContentSize().width+20, 70));
            customItem->addChild(bob);
            
            if(data.poxiaoId == UserData::getInstance()->getPoxiaoId()){
                iamge->setPosition(Point(645,30));
                text->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
                bob->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
                text->setPosition(Point(580,40));
                bob->setFlippedX(true);
                bob->setPosition(Point(585,30));
            }else{
                iamge->setPosition(Point(80,30));
                text->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
                bob->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
                text->setPosition(Point(140,40));
                bob->setPosition(Point(135,30));
            }
            
        }
    }
}

void ChatDialog::closeView(){
    removeFromParent();
}


void ChatDialog::showQuickChatList(){
    QuickChatLayer* qc = QuickChatLayer::create();
    qc->setTag(100);
    addChild(qc);
}


void ChatDialog::showFaceList(){
    FaceChatLayer* fc = FaceChatLayer::create();
    addChild(fc);
}

void ChatDialog:: sendMessage(){
    if(NULL != getChildByTag(1001)){
        std::string msg = ((cocos2d::ui::EditBox*)getChildByTag(1001))->getText();
        if("" != msg){
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getPlayerChatMsgCommand(msg,chatPid,false));
        }
        ((cocos2d::ui::EditBox*)getChildByTag(1001))->setText("");
    }
}

void ChatDialog::sendFaceId(int id){
    if(NULL != getChildByTag(1001)){
        std::string msg = ((cocos2d::ui::EditBox*)getChildByTag(1001))->getText();
        std::string neeMsg = StringUtils::format("%s[face%d]",msg.c_str(),id);
        ((cocos2d::ui::EditBox*)getChildByTag(1001))->setText(neeMsg.c_str());
    }
    
}

void ChatDialog::sendQuickChat(std::string msg){
    if(NULL != getChildByTag(1001)){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getPlayerChatMsgCommand(msg,chatPid,false));
    }
}
