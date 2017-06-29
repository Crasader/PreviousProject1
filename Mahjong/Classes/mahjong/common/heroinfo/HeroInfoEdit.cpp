#include "mahjong/common/heroinfo/HeroInfoEdit.h"
#include "mahjong/common/dialog/prompt/HintDialog.hpp"


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
    
    
    
    auto  dialogBg = Sprite::create("common/dialog_bg.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(HeroInfoEdit::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(990, 590);
    addChild(closeMenu);
    
    auto icon = Sprite::create("playerinfo/hero_info.png");
    icon->setPosition(640, 615);
    addChild(icon);
    
    userInfoLayer = UserInfo::create();
    addChild(userInfoLayer);
    
}


void HeroInfoEdit::closeView(){
    removeFromParent();
}
