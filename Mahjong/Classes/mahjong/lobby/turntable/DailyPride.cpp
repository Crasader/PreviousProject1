#include "mahjong/lobby/turntable/DailyPride.h"
#include "mahjong/lobby/turntable/PrideCell.h"
#include "mahjong/common/dialog/prompt/HintDialog.hpp"
#include "mahjong/common/state/GameData.h"
#include "mahjong/common/utils/StringUtil.h"
#include "mahjong/common/widget/ParticleUtil.hpp"
#include "mahjong/common/utils/Chinese.h"
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
    
    prideCallBackListener2 = EventListenerCustom::create(MSG_PLAYER_TODAY_PRIDE, [=](EventCustom* event){
        if(GAMEDATA::getInstance()->getTodayPrideData().result == "2"){
            HintDialog* hit = HintDialog::create(ChineseWord("dialog_text_11"), nullptr, nullptr);
            addChild(hit,10);
            m_turnBg->stopAllActions();
        }else{
            schedule([=](float dt){
                //刷新用户信息
                NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getPlayerInfoCommand());
                m_turnBg->stopAllActions();
                DailyPrideData data = GAMEDATA::getInstance()->getDailyPrideData();
                for (int i = 0; i < data.prides.size(); i++){
                    if( ((PrideCell*)m_turnBg->getChildByTag(100+i))->getPropId() == GAMEDATA::getInstance()->getTodayPrideData().pride.type && ((PrideCell*)m_turnBg->getChildByTag(100+i))->getPropNum() ==GAMEDATA::getInstance()->getTodayPrideData().pride.number){
                        m_turnBg->setRotation(-90+45*i);
                        startMenu->setEnabled(true);
                        if(GAMEDATA::getInstance()->getTodayPrideData().pride.type == PrideType::gold){
                            ParticleUtil* util = ParticleUtil::create(MyParticleType::goldOnly);
                            this->getParent()->addChild(util,5);
                        }else if(GAMEDATA::getInstance()->getTodayPrideData().pride.type == PrideType::fangka){
                            ParticleUtil* util = ParticleUtil::create(MyParticleType::fangkaOnly);
                            this->getParent()->addChild(util, 5);
                        }else if(GAMEDATA::getInstance()->getTodayPrideData().pride.type == PrideType::lequan){
                            ParticleUtil* util = ParticleUtil::create(MyParticleType::lequanOnly);
                            this->getParent()->addChild(util, 5);
                        }
                        if(NULL != getChildByTag(1000)){
                            ((LabelAtlas*)getChildByTag(1000))->setString(StringUtils::format("%d",GAMEDATA::getInstance()->getTodayPrideData().rest));
                        }
                    }
                }
                data.count = StringUtils::format("%d",atoi(data.count.c_str())-1);
                GAMEDATA::getInstance()->setDailyPrideData(data);
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
    
    auto bg = LayerColor::create(Color4B(0, 0, 0, 80), 1280, 720);
    addChild(bg);
    
    auto rightGirl = Sprite::create("daily/right_girl.png");
    rightGirl->setPosition(780,380);
    addChild(rightGirl);
    
    auto shareText = Sprite::create("daily/text_info.png");
    shareText->setPosition(857,270);
    addChild(shareText);
    
    auto shareBtn = MenuItemImage::create("daily/share_pride_bnt_1.png", "daily/share_pride_bnt_2.png",CC_CALLBACK_0(DailyPride::shareTurntable, this));
    auto menu = Menu::create(shareBtn,NULL);
    menu->setPosition(850,180);
    addChild(menu);
    
    auto luck_bg = Sprite::create("daily/luck_bg.png");
    luck_bg->setPosition(463, 325);
    addChild(luck_bg);
    
    m_turnBg = Sprite::create("daily/circle_bg.png");
    m_turnBg->setPosition(463, 332);
    addChild(m_turnBg);
    
    TurnTableData data = GAMEDATA::getInstance()->getTurnTableData();
    for (int i = 0; i < data.prides.size(); i++){
        PrideCell* cell = PrideCell::create(data.prides.at(i).type, data.prides.at(i).number);
        cell->setRotation(90-i*36+18);
        cell->setTag(100+i);
        cell->setPosition(getPosByRotation(Point(219,219), 100, i * 36-18));
        m_turnBg->addChild(cell);
    }
    auto itemImage = MenuItemImage::create("daily/go_btn_1.png", "daily/go_btn_2.png",
                                           CC_CALLBACK_1(DailyPride::beginPride, this));
    startMenu = Menu::create(itemImage, NULL);
    startMenu->setPosition(463, 340);
    addChild(startMenu);
}


void DailyPride::shareTurntable(){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendTurntableShareCommand());
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    CallAndroidMethod::getInstance()->shareToWeChat(GAMEDATA::getInstance()->getMahjongShareData2().url,GAMEDATA::getInstance()->getMahjongShareData2().head,GAMEDATA::getInstance()->getMahjongShareData2().content,true);
//#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    CallIOSMethod::getInstance()->doWechatShareWeb(GAMEDATA::getInstance()->getMahjongShareData2().url,GAMEDATA::getInstance()->getMahjongShareData2().head,GAMEDATA::getInstance()->getMahjongShareData2().content,1);
//#endif
}

void DailyPride::updateData(){
    TurnTableData data = GAMEDATA::getInstance()->getTurnTableData();
    for (int i = 0; i < data.prides.size(); i++){
        PrideCell* cell = PrideCell::create(data.prides.at(i).type, data.prides.at(i).number);
        cell->setRotation(90-i*36+18);
        cell->setTag(100+i);
        cell->setPosition(getPosByRotation(Point(219,219), 100, i * 36-18));
        m_turnBg->addChild(cell);
    }
}


void DailyPride::beginPride(Ref* ref){
    
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendTurntableStartCommand());
    startMenu->setEnabled(false);
    srand(unsigned(time(NULL)));
    float angleZ = rand() % 720 + 720;
    auto pAction = EaseExponentialIn::create(RotateBy::create(2, Vec3(0, 0, angleZ)));
    auto roate = RotateBy::create(2, Vec3(0, 0, angleZ));
    auto repeat = Repeat::create(roate, CC_REPEAT_FOREVER);
    auto sequence = Sequence::create(pAction, repeat,NULL);
    m_turnBg->runAction(sequence);
}


Point DailyPride::getPosByRotation(Point pos, float r, float a){
    return Point(pos.x + cos(CC_DEGREES_TO_RADIANS(a))*r, pos.y + sin(CC_DEGREES_TO_RADIANS(a))*r);
}
