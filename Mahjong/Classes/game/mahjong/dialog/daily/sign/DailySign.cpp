#include "game/mahjong/dialog/daily/sign/DailySign.h"
#include "game/mahjong/dialog/daily/sign/DayCell.hpp"
#include "game/mahjong/state/GameData.h"
#include "server/NetworkManage.h"
#include "game/mahjong/dialog/shop/Huode.hpp"
#include "userdata/UserData.h"
#include "game/mahjong/lobby/LobbyScene.h"
#include "game/utils/ParticleUtil.hpp"

bool DailySign::init(){
    
    if (!Layer::init()){
        return false;
    }
    drawLayer();
    return true;
}

void DailySign::onEnter(){
    Layer::onEnter();
    signListener  = EventListenerCustom::create(MSG_PLAYER_DAILY_SIGN, [=](EventCustom* event){
        //TODO
    });
    _eventDispatcher->addEventListenerWithFixedPriority(signListener, 1);
    
    todaySignListener = EventListenerCustom::create(MSG_PLAYER_TODAY_SIGN, [=](EventCustom* event){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getDailySignCommand());//签到
        int gold =0;
        int diamond =0;
        int lequan =0;
        for(int i=0;i<atoi(GAMEDATA::getInstance()->getTodaySignData().day.c_str());i++){
            Sprite* sp = (Sprite*)getChildByTag(200+i);
            DayCell* cell = (DayCell*)sp->getChildByTag(300+i);
            cell->runAction(Sequence::create(DelayTime::create(4.0f),CallFunc::create([=](){
                cell->stopAllActions();
                cell->showPropResult(GAMEDATA::getInstance()->getTodaySignData().pride.at(i));
            }), NULL));
            if(GAMEDATA::getInstance()->getTodaySignData().pride.at(i).type==PrideType::gold){
                gold+=GAMEDATA::getInstance()->getTodaySignData().pride.at(i).number;
            }else if(GAMEDATA::getInstance()->getTodaySignData().pride.at(i).type==PrideType::lequan){
                lequan+=GAMEDATA::getInstance()->getTodaySignData().pride.at(i).number;
            }else if(GAMEDATA::getInstance()->getTodaySignData().pride.at(i).type==PrideType::lockDiammond){
                diamond+=GAMEDATA::getInstance()->getTodaySignData().pride.at(i).number;
            }
            auto an = Sprite::create();
            an->setPosition(sp->getPosition().x-10,sp->getPosition().y-100);
            addChild(an);
            an->runAction(Sequence::create(DelayTime::create(3.8f),CallFunc::create([=](){
                showLightAnim(an);
            }), DelayTime::create(1.0f),CallFunc::create([=](){
                if( gold > 0 && diamond ==0 && lequan == 0){
                    ParticleUtil* util = ParticleUtil::create(MyParticleType::goldOnly);
                    getParent()->addChild(util,5);
                }else if(gold == 0 && diamond >0 && lequan == 0){
                    ParticleUtil* util = ParticleUtil::create(MyParticleType::diamondOnly);
                    getParent()->addChild(util,5);
                }else if(gold == 0 && diamond ==0 && lequan > 0){
                    ParticleUtil* util = ParticleUtil::create(MyParticleType::lequanOnly);
                    getParent()->addChild(util,5);
                }else if(gold > 0 && diamond >0 && lequan == 0){
                    ParticleUtil* util = ParticleUtil::create(MyParticleType::goldAndDianmond);
                    getParent()->addChild(util,5);
                }else if(gold > 0 && diamond ==0 && lequan > 0){
                    ParticleUtil* util = ParticleUtil::create(MyParticleType::goldAndLequan);
                    getParent()->addChild(util,5);
                }else if(gold == 0 && diamond >0 && lequan > 0){
                    ParticleUtil* util = ParticleUtil::create(MyParticleType::lequanAndDiamond);
                    getParent()->addChild(util,5);
                }else{
                    ParticleUtil* util = ParticleUtil::create(MyParticleType::three);
                    getParent()->addChild(util,5);
                }
         }), NULL));
        }
        UserData::getInstance()->setGold(UserData::getInstance()->getGold()+gold);
        UserData::getInstance()->setLockDiamond(UserData::getInstance()->getLockDiamond()+diamond);
        UserData::getInstance()->setTicket(UserData::getInstance()->getTicket()+lequan);
        ((LobbyScene*)(getParent()->getParent()))->updateHeroInfo();
    });
    _eventDispatcher->addEventListenerWithFixedPriority(todaySignListener, 1);
}


void DailySign::onExit(){
    Layer::onExit();
    _eventDispatcher->removeEventListener(todaySignListener);
    _eventDispatcher->removeEventListener(signListener);
    
}

void DailySign::drawLayer(){
    
    //add piaodai
    auto piaodai = Sprite::create("daily/sign/piaodai.png");
    piaodai->setPosition(640, 515);
    addChild(piaodai);
    //add title
    auto sign_title = Sprite::create("daily/sign/sign_title.png");
    sign_title->setPosition(640, 535);
    addChild(sign_title);
    
    //add confirm btn to layer
    auto confirm = MenuItemImage::create("daily/recieve_btn_1.png", "daily/recieve_btn_2.png","daily/recieve_btn_3.png",
                                         CC_CALLBACK_1(DailySign::confirmSign,this));
    auto confirmMenu = Menu::create(confirm, NULL);
    confirmMenu->setPosition(948,146);
    addChild(confirmMenu);
    DailySignData data = GAMEDATA::getInstance()->getDailySignData();
    if(data.result == "2"){
        confirm->setEnabled(false);
    }
    //add sing bg
    drawDayBgAndTitle();
    
    //add text info
    auto text = Sprite::create("daily/sign/explain_text.png");
    text->setPosition(540,146);
    addChild(text);
}

void DailySign::drawDayBgAndTitle(){
    DailySignData data = GAMEDATA::getInstance()->getDailySignData();
    int index = atoi(data.day.c_str());
    for (int i = 0; i < 7; i++){
        auto sign_bg = Sprite::create("daily/sign/sign_bg.png");
        sign_bg->setPosition(260+i*126, 335);
        addChild(sign_bg);
        std::string imageName = "daily/sign/di_x_tian_2.png";
        if (i <= index){
            imageName = "daily/sign/di_x_tian_1.png";
        }
        auto title = Sprite::create(imageName);
        title->setPosition(260 + i * 126, 445);
        addChild(title,2);
        bool normal = i <= index ? true : false;
        auto dayNum = Sprite::create(getImageNameById(i+1, normal));
        dayNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
        dayNum->setPosition(260 + i * 126, 450);
        addChild(dayNum,2);
        
        auto stencil = Sprite::create("daily/sign/stencil.png");
        auto clipper = ClippingNode::create();
        clipper->setStencil(stencil);//设置裁剪模板 //3
        clipper->setInverted(false);//设置底板可见
        clipper->setTag(200+i);
        clipper->setAlphaThreshold(0);//设置绘制底板的Alpha值为0
        this->addChild(clipper);//4
            
        DayCell* cell = DayCell::create(1);//被裁剪的内容
        cell->setTag(300+i);
        if(i<=index){
            if(data.result == "1"){
                cell->setDayState(1);
            }else{
                cell->setDayState(2);
            }
        }else{
            cell->setDayState(3);
        }
        clipper->addChild(cell);//5
        clipper->setPosition(260+i*126, 340);

    }
}

void DailySign::showLightAnim(Sprite* sprite){
    auto animation = Animation::create();
    for( int i=1;i<20;i++)
    {
        std::string imageName = cocos2d::String::createWithFormat("signanim/sing_%d.png",i+1)->_string;
        animation->addSpriteFrameWithFile(imageName);
    }
    // should last 1 seconds. And there are 24 frames.
    animation->setDelayPerUnit(1.5f / 20.0f);
    animation->setRestoreOriginalFrame(true);
    auto action = Animate::create(animation);
    sprite->runAction(Sequence::create(action, NULL));
}

std::string DailySign::getImageNameById(int id, bool normal){
    std::string dayImage = "bignum/zero_1.png";
    switch (id)
    {
        case 0:
            if (normal){
                dayImage = "bignum/zero_1.png";
            }
            else{
                dayImage = "bignum/zero_2.png";
            }
            break;
        case 1:
            if (normal){
                dayImage = "bignum/one_1.png";
            }
            else{
                dayImage = "bignum/one_2.png";
            }
            break;
        case 2:
            if (normal){
                dayImage = "bignum/two_1.png";
            }
            else{
                dayImage = "bignum/two_2.png";
            }
            break;
        case 3:
            if (normal){
                dayImage = "bignum/three_1.png";
            }
            else{
                dayImage = "bignum/three_2.png";
            }
            break;
        case 4:
            if (normal){
                dayImage = "bignum/four_1.png";
            }
            else{
                dayImage = "bignum/four_2.png";
            }
            break;
        case 5:
            if (normal){
                dayImage = "bignum/five_1.png";
            }
            else{
                dayImage = "bignum/five_2.png";
            }
            break;
        case 6:
            if (normal){
                dayImage = "bignum/six_1.png";
            }
            else{
                dayImage = "bignum/six_2.png";
            }
            break;
        case 7:
            if (normal){
                dayImage = "bignum/seven_1.png";
            }
            else{
                dayImage = "bignum/seven_2.png";
            }
            break;
    }
    return dayImage;
}

void DailySign::closeView(){
    
    removeFromParent();
}

void DailySign::confirmSign(Ref* ref){
    MenuItemImage* tem  = (MenuItemImage*)ref;
    tem->setEnabled(false);
     for(int i=0;i<=atoi(GAMEDATA::getInstance()->getDailySignData().day.c_str());i++){
        Sprite* sp = (Sprite*)getChildByTag(200+i);
        DayCell* cell = (DayCell*)sp->getChildByTag(300+i);
        cell->runAction(Sequence::create(CallFunc::create([=](){
            cell->startAnimate();
        }),NULL));
    }

    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getSignCommand());
}

void DailySign::showDialogAnim(){


}

void DailySign::updateData(){
    
    
}