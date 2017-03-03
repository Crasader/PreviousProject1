#include "mahjong/heroinfo/HeadImageDialog.h"
#include "mahjong/heroinfo/UserInfo.h"
#include "server/NetworkManage.h"
#include "userdata/UserData.h"

bool HeadImageDialog::init(){
    if (!Layer::init()){
        
        return false;
    }
    showDialog();
    return true;
}

void HeadImageDialog::onEnter(){
    Layer::onEnter();
    changeImageListener = EventListenerCustom::create(MSG_PLAYER_CHANGE_HEAD_RESP, [=](EventCustom* event){
        char* buf = static_cast<char*>(event->getUserData());
        std::string result = buf;
        if (result == "1"){
            EventCustom ev0(MSG_UPDATE_HEAD_IMAGE);
            _eventDispatcher->dispatchEvent(&ev0);
        }
        removeFromParent();
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(changeImageListener, 1);
}

void HeadImageDialog::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(changeImageListener);
}

void HeadImageDialog::showDialog(){
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
    
    auto bg = Sprite::create("playerinfo/player_info_bg.png");
    bg->setPosition(640,360);
    addChild(bg);
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(HeadImageDialog::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(870, 495);
    addChild(closeMenu);
    
    auto title = Sprite::create("playerinfo/head_iamge_title.png");
    title->setPosition(640,495);
    addChild(title);
    
    for(int i=0; i < 4; i++){
        auto headBg =  Sprite::create("playerinfo/head_iamge_bg.png");
        headBg->setPosition(445+130*i,370);
        headBg->setTag(200+i);
        addChild(headBg);
    }
    
    auto headImage1 =  MenuItemImage::create("gameview/head_image_1.png","gameview/head_image_1.png",CC_CALLBACK_1(HeadImageDialog::selectedHeadImage, this));
    headImage1->setTag(100);
    auto headImage2 =  MenuItemImage::create("gameview/head_image_2.png","gameview/head_image_2.png",CC_CALLBACK_1(HeadImageDialog::selectedHeadImage, this));
    headImage2->setTag(101);
    auto headImage3 =  MenuItemImage::create("gameview/head_image_3.png","gameview/head_image_3.png",CC_CALLBACK_1(HeadImageDialog::selectedHeadImage, this));
    headImage3->setTag(102);
    auto headImage4 =  MenuItemImage::create("gameview/head_image_4.png","gameview/head_image_4.png",CC_CALLBACK_1(HeadImageDialog::selectedHeadImage, this));
    headImage4->setTag(103);
    
    auto headSelect = Menu::create(headImage1,headImage2,headImage3,headImage4,NULL);
    headSelect->alignItemsHorizontallyWithPadding(40);
    headSelect->setPosition(640,370);
    addChild(headSelect);
    
    auto confirm = MenuItemImage::create("common/confirm_btn_1.png", "common/confirm_btn_2.png",
                                         CC_CALLBACK_0(HeadImageDialog::confirmHead, this));
    auto confirmMenu = Menu::create(confirm, NULL);
    confirmMenu->setPosition(640, 240);
    this->addChild(confirmMenu);
}

void HeadImageDialog::closeView(){
    removeFromParent();
}

void HeadImageDialog::useCamara(){
    
}
void HeadImageDialog::usePhoto(){
    
}

void HeadImageDialog::selectedHeadImage(Ref* ref){
    MenuItemImage* temp = (MenuItemImage*) ref;
    temp->setScale(1.2f);
    ((Sprite*)getChildByTag(temp->getTag()+100))->setTexture("playerinfo/head_image_select.png");
    setSelectId(temp->getTag());
    if(temp->getTag() == 100){
        temp->getParent()->getChildByTag(101)->setScale(1.0f);
        ((Sprite*)getChildByTag(201))->setTexture("playerinfo/head_iamge_bg.png");
        temp->getParent()->getChildByTag(102)->setScale(1.0f);
        ((Sprite*)getChildByTag(202))->setTexture("playerinfo/head_iamge_bg.png");
        temp->getParent()->getChildByTag(103)->setScale(1.0f);
        ((Sprite*)getChildByTag(203))->setTexture("playerinfo/head_iamge_bg.png");
    } else  if(temp->getTag() == 101){
        temp->getParent()->getChildByTag(100)->setScale(1.0f);
        ((Sprite*)getChildByTag(200))->setTexture("playerinfo/head_iamge_bg.png");
        temp->getParent()->getChildByTag(102)->setScale(1.0f);
        ((Sprite*)getChildByTag(202))->setTexture("playerinfo/head_iamge_bg.png");
        temp->getParent()->getChildByTag(103)->setScale(1.0f);
        ((Sprite*)getChildByTag(203))->setTexture("playerinfo/head_iamge_bg.png");
    }else  if(temp->getTag() == 102){
        temp->getParent()->getChildByTag(101)->setScale(1.0f);
        ((Sprite*)getChildByTag(201))->setTexture("playerinfo/head_iamge_bg.png");
        temp->getParent()->getChildByTag(100)->setScale(1.0f);
        ((Sprite*)getChildByTag(200))->setTexture("playerinfo/head_iamge_bg.png");
        temp->getParent()->getChildByTag(103)->setScale(1.0f);
        ((Sprite*)getChildByTag(203))->setTexture("playerinfo/head_iamge_bg.png");
    }else  if(temp->getTag() == 103){
        temp->getParent()->getChildByTag(101)->setScale(1.0f);
        ((Sprite*)getChildByTag(201))->setTexture("playerinfo/head_iamge_bg.png");
        temp->getParent()->getChildByTag(102)->setScale(1.0f);
        ((Sprite*)getChildByTag(202))->setTexture("playerinfo/head_iamge_bg.png");
        temp->getParent()->getChildByTag(100)->setScale(1.0f);
        ((Sprite*)getChildByTag(200))->setTexture("playerinfo/head_iamge_bg.png");
    }
}


void HeadImageDialog::confirmHead(){
    if(getSelectId() == 100){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getChangeHeadCommand("1"));
    } else if(getSelectId() == 101){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getChangeHeadCommand("2"));
    }else if(getSelectId() == 102){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getChangeHeadCommand("3"));
    }else if(getSelectId() == 103){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getChangeHeadCommand("4"));
    }
}

