#include "mahjong/gameview/anim/DealJongAnim.h"
#include "mahjong/gameview/suzhou/normal/SuZhouView.h"
#include "mahjong/gameview/hongzhong/normal/HongZhongView.hpp"
#include "mahjong/gameview/baida/normal/BaiDaView.h"
#include "mahjong/gameview/fanpai/normal/FanPaiView.hpp"
#include "mahjong/common/jong/Jong.h"
#include "server/MsgConfig.h"

//整个动画时间大致在3.12秒
bool DealJongAnim::init(){
    if (!Layer::init()){
        
        return false;
    }
    paishuLayer = Layer::create();
    addChild(paishuLayer);
    initPosition();
    return true;
}

void DealJongAnim::showDealJong(int seatId, MahjongFaPaiData fapaiData){
    vector<string> dice =StringUtil::split(fapaiData.dice, ",") ;
    int dian1 = atoi(dice.at(0).c_str());
    int dian2 = atoi(dice.at(1).c_str());
    //step 1 播放发牌动画
    Sprite* fapa = Sprite::create();
    fapa->setPosition(640,360);
    addChild(fapa);
    fapa->runAction(Sequence::create(
                                     CallFunc::create([=](){showFapai(fapa);}),
                                     DelayTime::create(12.0/36),
                                     CallFunc::create([=](){
        auto paidui = Sprite::create("gameview/fapai_6.png");
        paidui->setTag(100);
        paidui->setPosition(640,370);
        paidui->setScale(1.2f);
        addChild(paidui);
    }),NULL));
    //step 2 骰子动画
    Sprite* base = Sprite::create();
    base->setPosition(640,340);
    addChild(base,1);
    base->runAction(Sequence::create(DelayTime::create(12.0f/36),CallFunc::create([=](){
        Audio::getInstance()->playSoundTouzi();
        showDiceAnim(base);
    }),DelayTime::create(6.0f/ 36),CallFunc::create([=](){
        base->setVisible(false);
        auto diec1 = Sprite::create(StringUtils::format("gameview/dice_%d.png",dian1));
        diec1->setPosition(640,320);
        diec1->setTag(200);
        addChild(diec1);
        diec1->setScale(0.6f);
        diec1->runAction(Sequence::create(ScaleTo::create(1.0/ 36*3,1.0f),ScaleTo::create(1.0/ 36*2,0.8f), NULL));
        auto diec2 = Sprite::create(StringUtils::format("gameview/dice_%d.png",dian2));
        diec2->setPosition(740,335);
        addChild(diec2);
        diec2->setScale(0.6f);
        diec2->setTag(300);
        diec2->runAction(Sequence::create(DelayTime::create(1.0/12),ScaleTo::create(1.0/ 36*3,1.0f),ScaleTo::create(1.0/ 36*2,0.8f),DelayTime::create(2.0/12.0),CallFunc::create([=](){
            auto spr = Sprite::create();
            spr->setTag(400);
            spr->setPosition(640,500);
            addChild(spr);
        }), NULL));
    }),DelayTime::create(18.0f/36),CallFunc::create([=](){
        if(getChildByTag(100)!=NULL){
            getChildByTag(100)->removeFromParent();
        }
        if(getChildByTag(200)!=NULL){
            getChildByTag(200)->removeFromParent();
        }
        if(getChildByTag(300)!=NULL){
            getChildByTag(300)->removeFromParent();
        }
        if(getChildByTag(400)!=NULL){
            getChildByTag(400)->removeFromParent();
        }
    }) ,NULL));
    //setp 3 牌开始展示
    auto lastStep = Sprite::create();
    addChild(lastStep);
    lastStep->runAction(Sequence::create(DelayTime::create(36.0/36), CallFunc::create([=](){
        if(GAMEDATA::getInstance()->getGameType() == 1){
            if(NULL != ((SuZhouView*)getParent())){
                ((SuZhouView*)getParent())->showPaiduiNum(99);
                ((SuZhouView*)getParent())->dealJongFinish(fapaiData);
            }
            
        }else if(GAMEDATA::getInstance()->getGameType() == 3){
            if(NULL != ((HongZhongView*)getParent())){
                ((HongZhongView*)getParent())->showPaiduiNum(91);
                ((HongZhongView*)getParent())->dealJongFinish(fapaiData);
            }
            
        }else if(GAMEDATA::getInstance()->getGameType() == 5){
            if(NULL != ((BaiDaView*)getParent())){
                ((BaiDaView*)getParent())->showPaiduiNum(99);
                ((BaiDaView*)getParent())->dealJongFinish(fapaiData);
            }
            
        }else if(GAMEDATA::getInstance()->getGameType() == 7){
            if(NULL != ((BaseView*)getParent())){
                ((FanPaiView*)getParent())->showPaiduiNum(91);
                ((FanPaiView*)getParent())->dealJongFinish(fapaiData);
            }
            
        }
        paishuLayer->removeFromParent();
    }), NULL));
}

void DealJongAnim::initPosition(){
    rounds = 0;
    heroStarPos = Point(300, 100);
    leftStarPos = Point(300, 100);
    rightStarPos = Point(300, 100);
    oppositeStarPos = Point(300, 100);
}


Sprite* DealJongAnim::createJong4(){
    Sprite* paidui = Sprite::create();
    paidui->setAnchorPoint(Point(0, 0));
    for (int h = 0; h < 4; h++){
        Jong* jong = Jong::create();
        jong->showJong(JongViewType::herodeal, -1,false);
        jong->setPosition(getPosByDirection(ClientSeatId::hero, h));
        paidui->addChild(jong);
    }
    return paidui;
}

Sprite* DealJongAnim::createJong4(int seatId){
    Sprite* paidui = Sprite::create();
    //平铺的牌堆
    for(int i=0;i<4;i++){
        Jong* jong = Jong::create();
        if(seatId== ClientSeatId::left||seatId== ClientSeatId::right){
            jong->showJong(JongViewType::leftdeal, -1,false);
            jong->setPosition(0,32*i);
            jong->setLocalZOrder(4-i);
            
        }else if(seatId == ClientSeatId::opposite){
            jong->showJong(JongViewType::oppositedeal, -1,false);
            jong->setPosition(0+42*i,0);
        }else{
            jong->showJong(JongViewType::herodeal, -1,false);
            jong->setPosition(0+62*i,0);
        }
        paidui->addChild(jong);
    }
    return paidui;
}

int DealJongAnim::getTypeByDirection(int direction){
    int bType = -1;
    if (direction == ClientSeatId:: hero){
        bType = JongViewType::herodeal;
    }
    else if (direction == ClientSeatId::opposite){
        bType = JongViewType::oppositedeal;
    }
    else if (direction == ClientSeatId::left){
        bType = JongViewType::leftdeal;
    }
    else if (direction == ClientSeatId::right){
        bType = JongViewType::rightdeal;
    }
    else{
        log("DealJongAnim:createJong4 -> direction is error");
    }
    return bType;
}


Point DealJongAnim::getPosByDirection(int direction, int index){
    if (direction == ClientSeatId::hero){
        if (index == 0){
            return Point(0, 0);
        }
        else if (index == 1){
            return Point(60, 0);
        }
        else if (index == 2){
            return Point(0, 20);
        }
        else if (index == 3){
            return Point(60, 20);
        }
    }
    return Point(0, 0);
}


Point DealJongAnim::caluMove2Pos(int type){
    if (type == ClientSeatId::hero){
        return Point(heroStarPos.x + 100 * rounds, heroStarPos.y);
    }
    else if (type == ClientSeatId::left){
        
    }
    else if (type == ClientSeatId::right){
        
        
    }
    else if (type == ClientSeatId::opposite){
        
        
    }
    else{
        CCLOG("DealJongAnim -> caluMove2Pos : error");
    }
    return NULL;
}


void DealJongAnim::showDiceAnim(Sprite* sprite){
    auto animation = Animation::create();
    for( int i=1;i<12;i++)
    {
        std::string imageName = StringUtils::format("gameview/dice_seq_%d.png",i);
        animation->addSpriteFrameWithFile(imageName);
    }
    animation->setDelayPerUnit(1.0f / 36.0f);
    animation->setRestoreOriginalFrame(false);
    auto action = Animate::create(animation);
    sprite->runAction(Sequence::create(action,CallFunc::create([=](){
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(UPDATE_DICE_KAOBAO_STATE);
    }), NULL));
}



void DealJongAnim::showFapai(Sprite* sprite){
    auto animation = Animation::create();
    for( int i=1;i<13;i++)
    {
        std::string imageName = StringUtils::format("gameview/fapai_%d.png",i);
        animation->addSpriteFrameWithFile(imageName);
    }
    animation->setDelayPerUnit(1.0f / 36.0f);
    animation->setRestoreOriginalFrame(false);
    auto action = Animate::create(animation);
    sprite->runAction(Sequence::create(action, NULL));
}

void DealJongAnim::faPaiAction(int seatId,int round){
    auto th000 = createJong4();
    th000->setPosition(640,360);
    paishuLayer->addChild(th000);
    th000->runAction(Sequence::create(MoveTo::create(6.0/ 36, getPaiduiPos(seatId,round/4)),CallFunc::create([=](){
        th000->setVisible(false);
    }),CallFunc::create([=](){
        Sprite* sky = createJong4(seatId);
        paishuLayer->addChild(sky);
        if(seatId == ClientSeatId::left){
            sky->setPosition(145,550-130*round/4);
        }else if(seatId == ClientSeatId::opposite){
            sky->setPosition(200+167*round/4,650);
        }else if(seatId == ClientSeatId::right){
            sky->setPosition(1100,200+130*round/4);
            sky->setLocalZOrder(4-round);
        }else{
            sky->setPosition(200+ 367*round/4,70);
        }
        
    }) ,NULL));
}

//返回下一个的座位号
int  DealJongAnim::getNextSeatId(int seatId){
    if(seatId == ClientSeatId::left){
        return ClientSeatId::hero;
    }else if(seatId==ClientSeatId::hero){
        return ClientSeatId::right;
    }else if(seatId==ClientSeatId::right){
        return ClientSeatId::opposite;
    }else if(seatId == ClientSeatId::opposite){
        return ClientSeatId::left;
    }
    return 0;
}

Point DealJongAnim::getPaiduiPos(int seatId,int round){
    if(seatId == ClientSeatId::left){
        return Point(148,560-130*round);
        
    }else if(seatId == ClientSeatId::opposite){
        return Point(380+167*round,640);
    }else if(seatId == ClientSeatId::right){
        return Point(1100,300+130*round);
        
    }else{
        return Point(300+250*round,80);
    }
    
}

