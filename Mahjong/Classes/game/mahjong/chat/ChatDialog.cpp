//
//  ChatDialog.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/8/11.
//
//

#include "game/mahjong/chat/ChatDialog.hpp"
#include "server/NetworkManage.h"
#include "userdata/UserData.h"
#include "game/mahjong/chat/QuickChatLayer.hpp"
#include "game/mahjong/chat/FaceChatLayer.hpp"
#include "game/utils/StringUtil.h"
#include "game/mahjong/chat/PlayerChatManage.hpp"

ChatDialog* ChatDialog::create(std::string poxiaoId){
    ChatDialog* cell = new ChatDialog();
    if(cell&& cell->init(poxiaoId)){
        cell->autorelease();
        return cell;
    }
    CC_SAFE_DELETE(cell);
    return NULL;
}

bool ChatDialog::init(std::string poxiaoId){
    if(!Layer::init()){
        return false;
    }
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
    listView->setSize(Size(720,480));//设置ListView大小
    listView->ignoreContentAdaptWithSize(false);//开启锚点设置，false可更改锚点，true不可更改，Layer默认为point(0,0),其他Node为Point(0.5,0.5)
    listView->setAnchorPoint(Vec2(0.5, 0.5));//设置锚点，即锚点放在节点setPosition的位置，0，0：表示节点左下角；1，1：表示节点右上角；0.5，0.5表示节点中点
    listView->setPosition(Point(640,375));
    addChild(listView);
    
    auto inputBg =  Scale9Sprite::create("mainlogin/bottom_bg.png");
    inputBg->setContentSize(Size(720,81));
    inputBg->setPosition(Point(640,85));
    addChild(inputBg);
    
    auto inputField =  Scale9Sprite::create("mainlogin/bottom_bg.png");
    inputField->setContentSize(Size(560,71));
    inputField->setPosition(Point(565,85));
    addChild(inputField);
    
    MenuItemImage* image = MenuItemImage::create("chat/quick_chat_btn_1.png","chat/quick_chat_btn_2.png",CC_CALLBACK_0(ChatDialog::showQuickChatList, this));
    auto quickChatBtn  = Menu::create(image,NULL);
    quickChatBtn->setPosition(805,85);
    addChild(quickChatBtn);
    
    MenuItemImage* face = MenuItemImage::create("chat/face_btn_1.png","chat/face_btn_2.png",CC_CALLBACK_0(ChatDialog::showFaceList, this));
    auto faceChatBtn  = Menu::create(face,NULL);
    faceChatBtn->setPosition(865,85);
    addChild(faceChatBtn);
    
    MenuItemImage* snd = MenuItemImage::create("chat/send_btn_1.png","chat/send_btn_2.png",CC_CALLBACK_0(ChatDialog::sendMessage, this));
    auto sendBtn  = Menu::create(snd,NULL);
    sendBtn->setPosition(942,85);
    addChild(sendBtn);
    
    EditBox* field = EditBox::create(Size(500,71), Scale9Sprite::create());
    field->setTag(1001);
    field->setPosition(Point(545,85));
    addChild(field);
    
    showChatList(poxiaoId);
    
    return true;
}



void ChatDialog::showChatList(std::string poxiaoId){
    std::vector<ChatData> msgList;
    if(poxiaoId == "" || poxiaoId.size()<10){
        chatPid = "";
        RoomChatMsgList list = GAMEDATA::getInstance()->getRoomChatMsgList();
        msgList = list.msgList;
    }else{
        chatPid = poxiaoId;
        FriendChatMsgList list = GAMEDATA::getInstance()->getFriendChatMsgList();
        for(auto msg : list.friendMsgList){
            if(msg.poxiaoId == poxiaoId){
                msgList = msg.msgList;
            }
        }
    }
    if(msgList.size()==0){
        return;
    }
    for(int i = 0;i<msgList.size();i++){
        showChatInfo(msgList.at(i));
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
    Layout *customItem = Layout::create();
    customItem->setLayoutType(Layout::Type::ABSOLUTE);
    customItem->setContentSize(Size(720,100));
    //显示聊天的头像
    Sprite* iamge = Sprite::create();
    if(chatPid == ""){
        for(auto player : GAMEDATA::getInstance()->getPlayersInfo()){
            if(data.poxiaoId == player->getPoxiaoId()){
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
    }else{
        for(auto player : GAMEDATA::getInstance()->getFriendList().friends){
            if(data.poxiaoId == player.poxiaoId){
                if(player.pic == "1"){
                    iamge->setTexture("gameview/head_image_1.png");
                }else if(player.pic== "2"){
                    iamge->setTexture("gameview/head_image_2.png");
                }else if(player.pic == "3"){
                    iamge->setTexture("gameview/head_image_3.png");
                }else if(player.pic == "4"){
                    iamge->setTexture("gameview/head_image_4.png");
                }else{
                    log("服务器下发的头像图片不存在");
                    iamge->setTexture("gameview/head_image_1.png");
                }
            }
        }
        if(data.poxiaoId == UserData::getInstance()->getPoxiaoId()){
            if(UserData::getInstance()->getPicture() == "1"){
                iamge->setTexture("gameview/head_image_1.png");
            }else if(UserData::getInstance()->getPicture()== "2"){
                iamge->setTexture("gameview/head_image_2.png");
            }else if(UserData::getInstance()->getPicture() == "3"){
                iamge->setTexture("gameview/head_image_3.png");
            }else if(UserData::getInstance()->getPicture() == "4"){
                iamge->setTexture("gameview/head_image_4.png");
            }else{
                log("服务器下发的头像图片不存在");
                iamge->setTexture("gameview/head_image_1.png");
            }
        }
    }
    customItem->addChild(iamge);
    listView->pushBackCustomItem(customItem);
    
    std::string content = data.content;
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
    auto bob = Scale9Sprite::create("chat/text_bob.png", Rect(0, 0, 31, 38), Rect(5, 0, 6, 38));
    bob->setContentSize(Size(text->getContentSize().width+20, 65));
    customItem->addChild(bob);
    
    if(data.poxiaoId == UserData::getInstance()->getPoxiaoId()){
        iamge->setPosition(Point(645,30));
        text->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
        bob->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
        text->setPosition(Point(580,40));
        bob->setPosition(Point(585,30));
    }else{
        iamge->setPosition(Point(80,30));
        text->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        bob->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        text->setPosition(Point(140,40));
        bob->setPosition(Point(135,30));
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
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getPlayerChatMsgCommand(msg,chatPid));
        }
        ((cocos2d::ui::EditBox*)getChildByTag(1001))->setText("");
    }
}

void ChatDialog::sendFaceId(int id){
    if(NULL != getChildByTag(1001)){
        std::string msg = ((cocos2d::ui::EditBox*)getChildByTag(1001))->getText();
        std::string neeMsg = msg+ StringUtils::format("[face%d]",id);
        ((cocos2d::ui::EditBox*)getChildByTag(1001))->setText(neeMsg.c_str());
    }
    
}

void ChatDialog::sendQuickChat(std::string msg){
    if(NULL != getChildByTag(1001)){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getPlayerChatMsgCommand(msg,chatPid));
    }
}
