#include "game/mahjong/playerinfo/HeroInfoEdit.h"
#include "game/mahjong/dialog/prompt/HintDialog.hpp"


HeroInfoEdit* HeroInfoEdit::create(int type){
    HeroInfoEdit* ret = new HeroInfoEdit();
    if (ret && ret->init(type)){
        ret->autorelease();
        return ret;
    }
    else{
        delete ret;
        ret = NULL;
        return NULL;
    }
}

bool HeroInfoEdit::init(int type){
    if (!Layer::init()){
        return false;
    }
    drawHeroInfoEdit(type);
    return true;
}

void HeroInfoEdit::onEnter(){
    Layer::onEnter();
    
    closeDialogListener = EventListenerCustom::create(CLOSE_HINT_DIALOG, [=](EventCustom* event){
        removeFromParent();
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(closeDialogListener, 1);
}

void HeroInfoEdit::onExit(){
    Layer::onExit();
    _eventDispatcher->removeEventListener(closeDialogListener);
}

void HeroInfoEdit::drawHeroInfoEdit(int type){
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
    
    auto all_bg = Sprite::create("common/all_bg.jpg");
    all_bg->setPosition(640, 360);
    addChild(all_bg);
    
    
    auto  dialogBg = Sprite::create("common/dialog_bg.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(HeroInfoEdit::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(980, 580);
    addChild(closeMenu);
    
    auto paodai = Sprite::create("common/piaodai_zi.png");
    paodai->setPosition(640, 590);
    this->addChild(paodai);
    auto icon = Sprite::create("playerinfo/hero_info.png");
    icon->setPosition(640, 615);
    addChild(icon);
    
    Scale9Sprite* tabBg = Scale9Sprite::create("common/tab_bg.png");
    tabBg->setContentSize(Size(540,71));
    tabBg->setPosition(550,525);
    addChild(tabBg);
    
    auto heroInfoImage1 = MenuItemImage::create("common/tab_btn_1.png", "common/tab_btn_1.png");
    auto heroInfoImage2 = MenuItemImage::create("common/tab_btn_2.png", "common/tab_btn_2.png");
    heroInfoImage = MenuItemToggle::createWithCallback(CC_CALLBACK_1(HeroInfoEdit::clickTabBtn, this), heroInfoImage1, heroInfoImage2, NULL);
    heroInfoImage->setTag(0);
    heroInfoImage->setSelectedIndex(1);
    
    auto boundPhoneImage1 = MenuItemImage::create("common/tab_btn_1.png", "common/tab_btn_1.png");
    auto boundPhoneImage2 = MenuItemImage::create("common/tab_btn_2.png", "common/tab_btn_2.png");
    boundPhoneImage = MenuItemToggle::createWithCallback(CC_CALLBACK_1(HeroInfoEdit::clickTabBtn, this), boundPhoneImage1, boundPhoneImage2, NULL);
    boundPhoneImage->setTag(1);
    
    auto editPasswordImage1 = MenuItemImage::create("common/tab_btn_1.png", "common/tab_btn_1.png");
    auto editPasswordImage2 = MenuItemImage::create("common/tab_btn_2.png", "common/tab_btn_2.png");
    editPasswordImage = MenuItemToggle::createWithCallback(CC_CALLBACK_1(HeroInfoEdit::clickTabBtn, this), editPasswordImage1, editPasswordImage2, NULL);
    editPasswordImage->setTag(2);
    
    auto menu = Menu::create(heroInfoImage, boundPhoneImage, editPasswordImage, NULL);
    menu->alignItemsHorizontallyWithPadding(10);
    menu->setPosition(545, 523);
    addChild(menu);
    
    heroInfo = Sprite::create("playerinfo/hero_info_edit_2.png");
    heroInfo->setPosition(380,525);
    addChild(heroInfo);
    
    boundPhone = Sprite::create("playerinfo/bound_phone_1.png");
    boundPhone->setPosition(552, 525);
    addChild(boundPhone);
    
    editPassword = Sprite::create("playerinfo/edit_password_1.png");
    editPassword->setPosition(725, 525);
    addChild(editPassword);
    
    userInfoLayer = UserInfo::create();
    addChild(userInfoLayer);
    
    boundPhoneLayer = BoundPhone::create();
    boundPhoneLayer->setVisible(false);
    addChild(boundPhoneLayer);
    
    changePasswordLayer = ChangePassword::create();
    changePasswordLayer->setVisible(false);
    addChild(changePasswordLayer);
    
    if(type == 1){
        showTabelLayer1();
    }else if(type ==2){
        showTabelLayer2();
    }else if(type ==3){
        showTabelLayer3();    }
}


void HeroInfoEdit::closeView(){
    removeFromParent();
}

void HeroInfoEdit::clickTabBtn(Ref* ref){
    MenuItemToggle* temp = (MenuItemToggle*)ref;
    if (temp->getTag() == 0){
        showTabelLayer1();
    }
    else if (temp->getTag() == 1){
        showTabelLayer2();
    }
    else if (temp->getTag() == 2){
        showTabelLayer3();
    }
    
}

void HeroInfoEdit::showTabelLayer1(){
    heroInfoImage->setSelectedIndex(1);
    boundPhoneImage->setSelectedIndex(0);
    editPasswordImage->setSelectedIndex(0);
    heroInfo->setTexture("playerinfo/hero_info_edit_2.png");
    boundPhone->setTexture("playerinfo/bound_phone_1.png");
    editPassword->setTexture("playerinfo/edit_password_1.png");
    userInfoLayer->setVisible(true);
    boundPhoneLayer->setVisible(false);
    changePasswordLayer->setVisible(false);
}

void HeroInfoEdit::showTabelLayer2(){
    heroInfoImage->setSelectedIndex(0);
    boundPhoneImage->setSelectedIndex(1);
    editPasswordImage->setSelectedIndex(0);
    heroInfo->setTexture("playerinfo/hero_info_edit_1.png");
    boundPhone->setTexture("playerinfo/bound_phone_2.png");
    editPassword->setTexture("playerinfo/edit_password_1.png");
    userInfoLayer->setVisible(false);
    boundPhoneLayer->setVisible(true);
    changePasswordLayer->setVisible(false);
}

void HeroInfoEdit::showTabelLayer3(){
    heroInfoImage->setSelectedIndex(0);
    boundPhoneImage->setSelectedIndex(0);
    editPasswordImage->setSelectedIndex(1);
    heroInfo->setTexture("playerinfo/hero_info_edit_1.png");
    boundPhone->setTexture("playerinfo/bound_phone_1.png");
    editPassword->setTexture("playerinfo/edit_password_2.png");
    userInfoLayer->setVisible(false);
    boundPhoneLayer->setVisible(false);
    changePasswordLayer->setVisible(true);
}