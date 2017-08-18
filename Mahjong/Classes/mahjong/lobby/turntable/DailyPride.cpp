#include "mahjong/lobby/turntable/DailyPride.h"
#include "mahjong/lobby/turntable/PrideCell.h"
#include "mahjong/common/dialog/prompt/HintDialog.hpp"
#include "mahjong/common/utils/StringUtil.h"
#include "mahjong/common/widget/ParticleUtil.hpp"
#include "mahjong/common/utils/Chinese.h"
#include "http/image/UrlImageMannger.h"
#include "server/NetworkManage.h"
#include "userdata/UserData.h"
#include "wechat/android/CallAndroidMethod.h"
#include "wechat/ios/CallIOSMethod.h"
#include "math.h"


bool DailyPride::init(){
    if (!Layer::init()){
        return false;
    }
    showDailyPrideLayer();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendTurntableCommmand());
    return true;
}

void DailyPride::onEnter(){
    Layer::onEnter();
    
    prideCallBackListener1 = EventListenerCustom::create(MSG_PLAYER_TURNTABLE_PRIDE, [=](EventCustom* event){
        updateData();
    });
    _eventDispatcher->addEventListenerWithFixedPriority(prideCallBackListener1, 1);
    
    prideCallBackListener2 = EventListenerCustom::create(MSG_PLAYER_TURNTABLE_PRIDE_RESULT, [=](EventCustom* event){
        if(GAMEDATA::getInstance()->getTodayPrideData().result == "2"){
            HintDialog* hit = HintDialog::create(ChineseWord("dialog_text_11"), nullptr, nullptr);
            addChild(hit,10);
            m_turnBg->stopAllActions();
        }else{
            schedule([=](float dt){
                //刷新用户信息
                m_turnBg->stopAllActions();
                TurnTableData data = GAMEDATA::getInstance()->getTurnTableData();
                for (int i = 0; i < data.prides.size(); i++){
                    if( ((PrideCell*)m_turnBg->getChildByTag(100+i))->getPropId() == GAMEDATA::getInstance()->getTurnTablePrideData().pride.type && ((PrideCell*)m_turnBg->getChildByTag(100+i))->getPropNum() ==GAMEDATA::getInstance()->getTurnTablePrideData().pride.number){
                        m_turnBg->setRotation(-90+36*i-18);
                        showTurntableResult(GAMEDATA::getInstance()->getTurnTablePrideData().pride.type,GAMEDATA::getInstance()->getTurnTablePrideData().pride.number);
                    }
                }
            },0.0f,0,2.0f,"m_turnBg");
        }
    });
    _eventDispatcher->addEventListenerWithFixedPriority(prideCallBackListener2, 1);
}

void DailyPride::onExit(){
    Layer::onExit();
    _eventDispatcher->removeEventListener(prideCallBackListener1);
    _eventDispatcher->removeEventListener(prideCallBackListener2);
    
}

void DailyPride::onEnterTransitionDidFinish(){
    Layer::onEnterTransitionDidFinish();
}


void DailyPride::showDailyPrideLayer(){
    
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
    
    auto bg = LayerColor::create(Color4B(0, 0, 0, 204), 1280, 720);
    addChild(bg);
    
    auto rightGirl = Sprite::create("daily/right_girl.png");
    rightGirl->setPosition(810,380);
    addChild(rightGirl);
    
    
    
    auto close = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png",
                                       CC_CALLBACK_0(DailyPride::closeView, this));
    auto closeMenu = Menu::create(close, NULL);
    closeMenu->setPosition(1090, 372);
    this->addChild(closeMenu);
    
    auto luck_bg = Sprite::create("daily/luck_bg.png");
    luck_bg->setPosition(433, 325);
    addChild(luck_bg);
    
    m_turnBg = Sprite::create("daily/circle_bg.png");
    m_turnBg->setPosition(433, 332);
    addChild(m_turnBg);
    
    TurnTableData data = GAMEDATA::getInstance()->getTurnTableData();
    for (int i = 0; i < data.prides.size(); i++){
        PrideCell* cell = PrideCell::create(data.prides.at(i).type, data.prides.at(i).number);
        cell->setRotation(90-i*36+18);
        cell->setTag(100+i);
        cell->setPosition(getPosByRotation(Point(285,285), 150, i * 36-18));
        m_turnBg->addChild(cell);
    }
        auto itemImage = MenuItemImage::create("daily/go_btn_1.png", "daily/go_btn_2.png",
                                           CC_CALLBACK_1(DailyPride::beginPride, this));
    startMenu = Menu::create(itemImage, NULL);
    startMenu->setPosition(433, 360);
    addChild(startMenu);

    auto shareText = Sprite::create("daily/text_info.png");
    shareText->setTag(1000);
    shareText->setPosition(887,270);
    addChild(shareText);
    
    auto shareBtn = MenuItemImage::create("daily/share_pride_bnt_1.png", "daily/share_pride_bnt_2.png",CC_CALLBACK_0(DailyPride::shareTurntable, this));
    auto menu = Menu::create(shareBtn,NULL);
    menu->setTag(1001);
    menu->setPosition(880,180);
    addChild(menu);
//    auto btnLight = Sprite::create("daily/btn_light.png");
//    menu->addChild(btnLight);
//    btnLight->runAction(Repeat::create(Sequence::create(ScaleTo::create(1.0, 1.2f),ScaleTo::create(1.0, 1.0f),NULL), CC_REPEAT_FOREVER));
    
    auto number = LabelAtlas::create("0", "daily/pride_num_red.png", 32, 46, '0');
    number->setPosition(837,240);
    number->setTag(1002);
    addChild(number);
    auto shareText2 = Sprite::create("daily/chance_text.png");
    shareText2->setPosition(887,240);
    shareText2->setTag(1003);
    addChild(shareText2);
    
    
    auto shareText3 = Sprite::create("daily/no_chance_text.png");
    shareText3->setPosition(887,240);
    shareText3->setTag(1004);
    addChild(shareText3);
    
    auto shou1 = Sprite::create("daily/shou.png");
    shou1->setPosition(880,130);
    addChild(shou1);
    shou1->setTag(1005);
    shou1->runAction(Repeat::create(Sequence::create(ScaleTo::create(1.0, 1.2f),ScaleTo::create(1.0, 1.0f),NULL), CC_REPEAT_FOREVER));
    
    auto tableLight = Sprite::create();
    tableLight->setPosition(432,328);
    addChild(tableLight);
    tableLight->runAction(Repeat::create(Sequence::create(CallFunc::create([=](){
        tableLight->setTexture("daily/btn_light_1.png");
    }),DelayTime::create(0.5f),CallFunc::create([=](){
        tableLight->setTexture("daily/btn_light_2.png");
    }),DelayTime::create(0.5f),NULL), CC_REPEAT_FOREVER));
    
    auto tableLight2 = Sprite::create();
    tableLight2->setPosition(432,328);
    addChild(tableLight2);
    tableLight2->runAction(Repeat::create(Sequence::create(CallFunc::create([=](){
        tableLight2->setTexture("daily/table_light_1.png");
    }),DelayTime::create(0.5f),CallFunc::create([=](){
        tableLight2->setTexture("daily/table_light_2.png");
    }),DelayTime::create(0.5f),NULL), CC_REPEAT_FOREVER));
    
    if(UserData::getInstance()->getTurntableNumber() == "0"){
        //需要分享获取次数
        shareText->setVisible(true);
        menu->setVisible(true);
        shou1->setVisible(true);
        number->setVisible(false);
        shareText2->setVisible(false);
        shareText3->setVisible(false);
        tableLight->setVisible(false);
        tableLight2->setVisible(false);

    }else if(UserData::getInstance()->getTurntableNumber() == "-1"){
        //次数已经用完了
        shareText->setVisible(false);
        menu->setVisible(false);
        shou1->setVisible(false);
        number->setVisible(false);
        shareText2->setVisible(false);
        shareText3->setVisible(true);
        tableLight->setVisible(false);
        tableLight2->setVisible(false);
    }else{
        //拥有次数
        shareText->setVisible(false);
        menu->setVisible(false);
        number->setVisible(true);
        shou1->setPosition(433, 312);
        shou1->setVisible(true);
        number->setString(UserData::getInstance()->getTurntableNumber());
        shareText2->setVisible(true);
        shareText3->setVisible(false);
        tableLight->setVisible(true);
        tableLight2->setVisible(true);
        
    }
    scheduleUpdate();
}


void DailyPride::shareTurntable(){
    GAMEDATA::getInstance()->setIsTurnTableShare(true);
    std::string shareUrl = GAMEDATA::getInstance()->getMahjongShareData2().url;
    if(GAMEDATA::getInstance()->getMahjongShareData2().type == "1"){
        shareUrl = StringUtils::format("%s%s",shareUrl.c_str(),UserData::getInstance()->getPoxiaoId().c_str());
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        CallAndroidMethod::getInstance()->shareToWeChat(shareUrl,GAMEDATA::getInstance()->getMahjongShareData2().head,GAMEDATA::getInstance()->getMahjongShareData2().content,true);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        CallIOSMethod::getInstance()->doWechatShareWeb(shareUrl,GAMEDATA::getInstance()->getMahjongShareData2().head,GAMEDATA::getInstance()->getMahjongShareData2().content,1);
#endif
    }else{
        UrlImageMannger::getInstance()->downloadShareImageByUrl(shareUrl);
    }

}

void DailyPride::updateData(){
    TurnTableData data = GAMEDATA::getInstance()->getTurnTableData();
    for (int i = 0; i < data.prides.size(); i++){
        PrideCell* cell = PrideCell::create(data.prides.at(i).type, data.prides.at(i).number);
        cell->setRotation(90-i*36+18);
        cell->setTag(100+i);
        cell->setPosition(getPosByRotation(Point(285,285), 150, i * 36-18));
        m_turnBg->addChild(cell);
    }
}


void DailyPride::beginPride(Ref* ref){
    if(atoi(UserData::getInstance()->getTurntableNumber().c_str())>0){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendTurntableStartCommand());
        srand(unsigned(time(NULL)));
        float angleZ = rand() % 720 + 720;
        auto pAction = EaseExponentialIn::create(RotateBy::create(2, Vec3(0, 0, angleZ)));
        auto roate = RotateBy::create(2, Vec3(0, 0, angleZ));
        auto repeat = Repeat::create(roate, CC_REPEAT_FOREVER);
        auto sequence = Sequence::create(pAction, repeat,NULL);
        m_turnBg->runAction(sequence);
    }
}


Point DailyPride::getPosByRotation(Point pos, float r, float a){
    return Point(pos.x + cos(CC_DEGREES_TO_RADIANS(a))*r, pos.y + sin(CC_DEGREES_TO_RADIANS(a))*r);
}


void DailyPride::closeView(){
    removeFromParent();
}

void DailyPride::update(float dt){
    if(UserData::getInstance()->getTurntableNumber() == "0"){
        getChildByTag(1000)->setVisible(true);
        getChildByTag(1001)->setVisible(true);
        getChildByTag(1002)->setVisible(false);
        getChildByTag(1003)->setVisible(false);
        getChildByTag(1004)->setVisible(false);
        getChildByTag(1005)->setVisible(true);
    }else if(UserData::getInstance()->getTurntableNumber() == "-1"){
        getChildByTag(1000)->setVisible(false);
        getChildByTag(1001)->setVisible(false);
        getChildByTag(1002)->setVisible(false);
        getChildByTag(1003)->setVisible(false);
        getChildByTag(1004)->setVisible(true);
        getChildByTag(1005)->setVisible(false);
    }else{
        getChildByTag(1000)->setVisible(false);
        getChildByTag(1001)->setVisible(false);
        getChildByTag(1002)->setVisible(true);
        ((LabelAtlas*)getChildByTag(1002))->setString(UserData::getInstance()->getTurntableNumber());
        getChildByTag(1003)->setVisible(true);
        getChildByTag(1004)->setVisible(false);
        getChildByTag(1005)->setVisible(true);
        getChildByTag(1005)->setPosition(433, 312);
    }
}

void DailyPride::showTurntableResult(PrideType propId,std::string number){
    auto bg = LayerColor::create(Color4B(0, 0, 0, 204), 1280, 720);
    addChild(bg);
    
    auto gongxi = Sprite::create("daily/gongxi.png");
    gongxi->setPosition(640,520);
    addChild(gongxi);
    
    auto pridebg = Sprite::create("daily/pride_bg.png");
    pridebg->setPosition(640,360);
    addChild(pridebg);
    
    auto prop = Sprite::create(getImageNameById(propId));
    prop->setPosition(640, 360);
    addChild(prop);
    
    int pos  =  (int)number.find(".");
    if(pos>=0){
        number.replace(pos,1, ":");
    }
    LabelAtlas* num = LabelAtlas::create(number,"daily/pride_num.png", 19, 28, '0');
    num->setPosition(620,300);
    addChild(num);
    if(propId == PrideType::fangka){
        auto zhang = Sprite::create("daily/zhang_text.png");
        zhang->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        addChild(zhang);
        num->setPosition((640-(num->getContentSize().width/2+zhang->getContentSize().width/2)), 295);
        zhang->setPosition(num->getPositionX()+num->getContentSize().width,308);
    }else  if(propId == PrideType::fee){
        auto zhang = Sprite::create("daily/yuan_text.png");
        zhang->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        addChild(zhang);
        num->setPosition((640-(num->getContentSize().width/2+zhang->getContentSize().width/2)), 295);
        zhang->setPosition(num->getPositionX()+num->getContentSize().width,308);
    }else  if(propId == PrideType::prop){
        auto zhang = Sprite::create("daily/ge_text.png");
        zhang->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        addChild(zhang);
        num->setPosition((640-(num->getContentSize().width/2+zhang->getContentSize().width/2)),295);
        zhang->setPosition(num->getPositionX()+num->getContentSize().width,308);
    }else  if(propId == PrideType::nothing){
        num->setVisible(false);
    }
    
    
    auto getPride = MenuItemImage::create("daily/get_pride_btn_1.png", "daily/get_pride_btn_2.png", CC_CALLBACK_0(DailyPride::getTurnTablePride, this));
    auto menu = Menu::create(getPride,NULL);
    menu->setPosition(640,180);
    addChild(menu);
}

void DailyPride::getTurnTablePride(){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getPlayerInfoCommand());
    removeFromParent();
}

std::string DailyPride::getImageNameById(PrideType id){
    std::string imageName;
    switch (id)
    {
        case PrideType::gold:
            imageName = "common/gold_icon.png";
            break;
        case PrideType::lequan:
            imageName = "common/lequan_icon.png";
            break;
        case PrideType::fangka:
            imageName = "shop/fangka_image.png";
            break;
        case PrideType::prop:
            imageName = "daily/iphone.png";
            break;
        case PrideType::fee:
            imageName = "daily/hongbao.png";
            break;
        default:
            imageName = "daily/nothing.png";
            break;
    }
    return imageName;
}

