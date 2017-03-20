#include "mahjong/lobby/daily/pride/DailyPride.h"
#include "mahjong/lobby/daily/pride/PrideCell.h"
#include "mahjong/dialog/prompt/HintDialog.hpp"
#include "mahjong/state/GameData.h"
#include "mahjong/utils/StringUtil.h"
#include "mahjong/widget/ParticleUtil.hpp"
#include "server/NetworkManage.h"
#include "userdata/UserData.h"
#include "math.h"

bool DailyPride::init(){
    if (!Layer::init()){
        return false;
    }
    showDailyPrideLayer();
    return true;
    
}

void DailyPride::onEnter(){
    Layer::onEnter();
    
    prideCallBackListener1 = EventListenerCustom::create(MSG_PLAYER_DAILY_PRIDE, [=](EventCustom* event){
        updateData();
    });
    _eventDispatcher->addEventListenerWithFixedPriority(prideCallBackListener1, 1);
    
    prideCallBackListener2 = EventListenerCustom::create(MSG_PLAYER_TODAY_PRIDE, [=](EventCustom* event){
        if(GAMEDATA::getInstance()->getTodayPrideData().result == "2"){
            HintDialog* hit = HintDialog::create("正在游戏中,无法抽奖", nullptr);
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
                            getParent()->addChild(util,5);
                        }else if(GAMEDATA::getInstance()->getTodayPrideData().pride.type == PrideType::fangka){
                            ParticleUtil* util = ParticleUtil::create(MyParticleType::fangkaOnly);
                            getParent()->addChild(util,5);
                        }else if(GAMEDATA::getInstance()->getTodayPrideData().pride.type == PrideType::lequan){
                            ParticleUtil* util = ParticleUtil::create(MyParticleType::lequanOnly);
                            getParent()->addChild(util,5);
                        }
                        if(NULL != getChildByTag(1000)){
                            ((Sprite*)getChildByTag(1000))->setTexture(getImageNameById(GAMEDATA::getInstance()->getTodayPrideData().rest));
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


void DailyPride::showDailyPrideLayer(){
    auto bigtitle = Sprite::create("daily/every_day_pride.png");
    bigtitle->setPosition(640,650);
    addChild(bigtitle);
    
    auto text_bg = Sprite::create("daily/pride/text_info_bg.png");
    text_bg->setPosition(850, 370);
    addChild(text_bg);
    
    auto piao = Sprite::create("daily/pride/piao_dai.png");
    piao->setPosition(900, 480);
    addChild(piao);
    
    auto title = Sprite::create("daily/pride/god_text.png");
    title->setPosition(900, 500);
    addChild(title);
    
    auto hint = Sprite::create("daily/pride/chance_text.png");
    hint->setPosition(900, 420);
    addChild(hint);
    
    auto num = Sprite::create(getImageNameById(atoi(GAMEDATA::getInstance()->getDailyPrideData().count.c_str())));
    num->setPosition(910,425);
    num->setTag(1000);
    addChild(num);
    
    auto text = Sprite::create("daily/pride/text_info.png");
    text->setPosition(890, 320);
    addChild(text);
    
    auto luck_bg = Sprite::create("daily/pride/luck_bg.png");
    luck_bg->setPosition(463, 325);
    addChild(luck_bg);
    
    m_turnBg = Sprite::create("daily/pride/circle_bg.png");
    m_turnBg->setPosition(463, 325);
    addChild(m_turnBg);
    
    DailyPrideData data = GAMEDATA::getInstance()->getDailyPrideData();
    for (int i = 0; i < data.prides.size(); i++){
        PrideCell* cell = PrideCell::create(data.prides.at(i).type, data.prides.at(i).number);
        cell->setRotation(90-i*45);
        cell->setTag(100+i);
        cell->setPosition(getPosByRotation(Point(219,219), 100, i * 45));
        m_turnBg->addChild(cell);
    }
    
    auto arrows = Sprite::create("daily/pride/arrows.png");
    arrows->setPosition(463, 335);
    addChild(arrows);
    
    auto itemImage = MenuItemImage::create("daily/pride/go_btn_1.png", "daily/pride/go_btn_2.png",
                                           CC_CALLBACK_0(DailyPride::beginPride, this));
    startMenu = Menu::create(itemImage, NULL);
    startMenu->setPosition(463, 325);
    addChild(startMenu);
    
    
}

void DailyPride::updateData(){
    ((Sprite*)getChildByTag(1000))->setTexture(getImageNameById(atoi(GAMEDATA::getInstance()->getDailyPrideData().count.c_str())));
    DailyPrideData data = GAMEDATA::getInstance()->getDailyPrideData();
    for (int i = 0; i < data.prides.size(); i++){
        PrideCell* cell = PrideCell::create(data.prides.at(i).type, data.prides.at(i).number);
        cell->setRotation(90-i*45);
        cell->setTag(100+i);
        cell->setPosition(getPosByRotation(Point(219,219), 100, i * 45));
        m_turnBg->addChild(cell);
    }
}


void DailyPride::beginPride(){
    
    if(atoi(GAMEDATA::getInstance()->getDailyPrideData().count.c_str())>0){
        if(UserData::getInstance()->getGold()<50000){
            HintDialog* hit = HintDialog::create("金币不足,请充值",NULL);
            addChild(hit);
        }else{
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getTodayPrideCommand());
            startMenu->setEnabled(false);
            srand(unsigned(time(NULL)));
            float angleZ = rand() % 720 + 720;
            auto pAction = EaseExponentialIn::create(RotateBy::create(2, Vec3(0, 0, angleZ)));
            auto roate = RotateBy::create(2, Vec3(0, 0, angleZ));
            auto repeat = Repeat::create(roate, CC_REPEAT_FOREVER);
            auto sequence = Sequence::create(pAction, repeat,NULL);
            m_turnBg->runAction(sequence);
        }
    }else{
        HintDialog* hit = HintDialog::create("未达成抽奖条件",NULL);
        addChild(hit);
    }
}

std::string DailyPride::getImageNameById(int id){
    std::string dayImage = "bignum/zero_1.png";
    switch (id)
    {
        case 0:
            dayImage = "bignum/zero_1.png";
            
            break;
        case 1:
            
            dayImage = "bignum/one_1.png";
            
            break;
        case 2:
            
            dayImage = "bignum/two_1.png";
            
            break;
        case 3:
            
            dayImage = "bignum/three_1.png";
            
            break;
        case 4:
            
            dayImage = "bignum/four_1.png";
            
            break;
        case 5:
            
            dayImage = "bignum/five_1.png";
            
            break;
        case 6:
            
            dayImage = "bignum/six_1.png";
            
            break;
        case 7:
            
            dayImage = "bignum/seven_1.png";
            
            break;
        case 8:
            
            dayImage = "bignum/eight_1.png";
            
            break;
        case 9:
            
            dayImage = "bignum/nine_1.png";
            
            break;
    }
    return dayImage;
}

Point DailyPride::getPosByRotation(Point pos, float r, float a){
    return Point(pos.x + cos(CC_DEGREES_TO_RADIANS(a))*r, pos.y + sin(CC_DEGREES_TO_RADIANS(a))*r);
}
