#include "mahjong/common/setting/UserSetting.h"
#include "mahjong/common/setting/GameFeedDialog.hpp"
#include "mahjong/common/setting/GameRuleDialog.hpp"
#include "mahjong/common/state/GameData.h"
#include "mahjong/common/audio/Audio.h"
#include "userdata/UserData.h"
#include "server/NetworkManage.h"
#include "mahjong/common/dialog/dissolve/DissovleRoomDialog.hpp"

bool UserSetting::init(){
    if (!BaseDialog::init()){
        return false;
    }
    return true;
}

void UserSetting::drawDialog(){
    auto bg0 = LayerColor::create(Color4B(0, 0, 0, 204), 1280, 720);
    addChild(bg0);
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
    
    
    auto  dialogBg = Sprite::create("common/dialog_bg.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(UserSetting::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(990, 590);
    addChild(closeMenu);
 
    auto titleIcon = Sprite::create("setting/settting_title.png");
    titleIcon->setPosition(640, 575);
    addChild(titleIcon);
    
    auto musicBg = Sprite::create("setting/setting_bg.png");
    musicBg->setPosition(640,385);
    addChild(musicBg);
    
    
    auto peiying = Sprite::create("setting/pei_ying.png");
    addChild(peiying);
    peiying->setPosition(385,470);
    
    auto putong = Sprite::create("setting/pu_tong_hua.png");
    addChild(putong);
    putong->setPosition(570,470);
    
    auto shanghai = Sprite::create("setting/shang_hai_hua.png");
    addChild(shanghai);
    shanghai->setPosition(810,470);
    
    auto quan_normal_1 = MenuItemImage::create("setting/yuan_hui.png", "setting/yuan_hui.png");
    auto quan_selected_1 = MenuItemImage::create("setting/yuan_lv.png", "setting/yuan_lv.png");
    putongToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(UserSetting::useSoundPuTong, this), quan_normal_1, quan_selected_1, NULL);
    
    auto quan_normal_2 = MenuItemImage::create("setting/yuan_hui.png", "setting/yuan_hui.png");
    auto quan_selected_2 = MenuItemImage::create("setting/yuan_lv.png", "setting/yuan_lv.png");
    shanghaikaToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(UserSetting::useSoundShangHai, this), quan_normal_2, quan_selected_2, NULL);
    if(UserData::getInstance()->isFangYan()){
        putongToggle->setSelectedIndex(0);
        shanghaikaToggle->setSelectedIndex(1);
    }else{
        putongToggle->setSelectedIndex(1);
        shanghaikaToggle->setSelectedIndex(0);
    }
    
    auto menu = Menu::create(putongToggle, shanghaikaToggle, NULL);
    menu->alignItemsHorizontallyWithPadding(180);
    menu->setPosition(595,470);
    addChild(menu,1);
    
    
    //音效条
    auto soudnText = Sprite::create("setting/sound.png");
    soudnText->setPosition(385,380);
    addChild(soudnText);
    
    ControlSlider* slide_control = ControlSlider::create("setting/progress_1.png", "setting/progress_2.png",
                                                         "setting/slide_btn_1.png");
    slide_control->setMinimumValue(0.0f);//设置最小值
    slide_control->setMaximumValue(100.0f);//设置最大值
    slide_control->setValue(UserData::getInstance()->getSoundValue()*90+5);//设置初始值
    slide_control->setTag(20);
    slide_control->addTargetWithActionForControlEvents(this,cccontrol_selector(UserSetting::slideCallback),Control::EventType::VALUE_CHANGED);//设置拖动回调
    slide_control->setPosition(720,380);
    addChild(slide_control);
    
    
    //音乐条
    auto musicText = Sprite::create("setting/music.png");
    musicText->setPosition(385,290);
    addChild(musicText);
    
    
    ControlSlider* slide_control2 = ControlSlider::create("setting/progress_1.png", "setting/progress_2.png",
                                                          "setting/slide_btn_1.png");
    slide_control2->setMinimumValue(0.0f);//设置最小值
    slide_control2->setMaximumValue(100.0f);//设置最大值
    slide_control2->setValue(UserData::getInstance()->getMusicValue()*90+5);//设置初始值
    slide_control2->setTag(30);
    slide_control2->addTargetWithActionForControlEvents(this,cccontrol_selector(UserSetting::slideCallback),Control::EventType::VALUE_CHANGED);//设置拖动回调
    slide_control2->setPosition(720,290);
    addChild(slide_control2);
    
    auto helpImage = MenuItemImage::create("setting/game_help_btn_1.png","setting/game_help_btn_2.png",
                                           CC_CALLBACK_0(UserSetting::showGameHelp, this));
    auto feedImage = MenuItemImage::create("setting/feedback_btn_1.png","setting/feedback_btn_2.png",
                                           CC_CALLBACK_0(UserSetting::feedBack, this));
    
    Menu* myMneu = Menu::create(helpImage,feedImage,NULL);
    myMneu->setPosition(600,185);
    myMneu->alignItemsHorizontallyWithPadding(20);
    addChild(myMneu);
    
    if (GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom){
        if(atoi(GAMEDATA::getInstance()->getFriendOpenRoomResp().prjucount.c_str())>=1){
            auto dissolve = MenuItemImage::create("setting/dissolve_room_1.png","setting/dissolve_room_2.png",CC_CALLBACK_0(UserSetting::dissolveRoom, this));
            auto dissolveMenu = Menu::create(dissolve,NULL);
            dissolveMenu->setPosition(930,185);
            addChild(dissolveMenu);
        }
    }
}



void UserSetting::slideCallback(Ref *sender, Control::EventType controlEvent)
{
    auto slide_control = (ControlSlider*)sender;//通过回调参数sender 获得ControlSlider
    int current_value = slide_control->getValue();//获取slide当前的值
    if(current_value<5){
        slide_control->setValue(5);
    }else if(current_value>95){
        slide_control->setValue(95);
    }
    int current_value2 = slide_control->getValue();
    if(slide_control->getTag() == 30){
        Audio::getInstance()->setBGMValue((current_value2-5)/90.0f);
    }
    
    if(slide_control->getTag() == 20){
        Audio::getInstance()->setEffectValue((current_value2-5)/90.0f);
    }
    
}


void UserSetting::showGameHelp(){
    GameRuleDialog* rule = GameRuleDialog::create();
    addChild(rule,2);
}


void UserSetting::feedBack(){
    GameFeedDialog* feed = GameFeedDialog::create();
    addChild(feed,2);
}

void UserSetting::dissolveRoom(){
    if(GAMEDATA::getInstance()->getGameType() == 1){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getDissolveRoomRequestCommand());
    }else if(GAMEDATA::getInstance()->getGameType() == 3){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getHZDissolveRoomInGameCommand());
    }else if(GAMEDATA::getInstance()->getGameType() == 5){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendBDDissovleRoomRequest());
    }else if(GAMEDATA::getInstance()->getGameType() == 7){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendFPDissovleRoomRequest());
    }
    
    GAMEDATA::getInstance()->setDissolveName(UserData::getInstance()->getNickName());
    DissovleRoomDialog* dia = DissovleRoomDialog::create();
    getParent()->addChild(dia,200);
    removeFromParent();
}

void UserSetting::useSoundPuTong(Ref* ref){
    putongToggle->setSelectedIndex(1);
    shanghaikaToggle->setSelectedIndex(0);
    UserData::getInstance()->setFangYan(false);
}

//配音设置只对红中麻将生效
void UserSetting::useSoundShangHai(Ref* ref){
    putongToggle->setSelectedIndex(0);
    shanghaikaToggle->setSelectedIndex(1);
    UserData::getInstance()->setFangYan(true);
}

