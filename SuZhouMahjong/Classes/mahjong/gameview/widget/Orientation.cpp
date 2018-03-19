#include "mahjong/gameview/widget/Orientation.h"
#include "mahjong/common/utils/SeatIdUtil.h"
#include "mahjong/common/state/GameData.h"

bool Orientation::init(){
    if (!Node::init()){
        return false;
    }
    initView();
    return true;
}

void Orientation::initView(){
    auto ori_bg = Sprite::create("gameview/ori_bg.png");
    ori_bg->setPosition(640, 405);
    addChild(ori_bg);
    left = Sprite::create();
    left->setRotation(90);
    left->setPosition(595, 410);
    addChild(left);
    right = Sprite::create();
    right->setPosition(685, 410);
    right->setRotation(270);
    addChild(right);
    opposite = Sprite::create();
    opposite->setPosition(640, 450);
    opposite->setRotation(180);
    addChild(opposite);
    hero = Sprite::create();
    hero->setPosition(640, 360);
    addChild(hero);
    light = Sprite::create();
    light->setPosition(640, 405);
    light->setVisible(false);
    addChild(light,2);
}


void Orientation::showOrientation(int heroSeatId){
    
    if (heroSeatId == 1){
        hero->setTexture("gameview/ori_east_1.png");
        hero->setTag(1);
        right->setTexture("gameview/ori_south_1.png");
        right->setTag(2);
        opposite->setTexture("gameview/ori_west_1.png");
        opposite->setTag(3);
        left->setTexture("gameview/ori_north_1.png");
        left->setTag(4);
    }
    else if (heroSeatId == 2){
        hero->setTexture("gameview/ori_south_1.png");
        hero->setTag(2);
        right->setTexture("gameview/ori_west_1.png");
        right->setTag(3);
        opposite->setTexture("gameview/ori_north_1.png");
        opposite->setTag(4);
        left->setTexture("gameview/ori_east_1.png");
        left->setTag(1);
    }
    else if (heroSeatId == 3){
        hero->setTexture("gameview/ori_west_1.png");
        hero->setTag(3);
        right->setTexture("gameview/ori_north_1.png");
        right->setTag(4);
        opposite->setTexture("gameview/ori_east_1.png");
        opposite->setTag(1);
        left->setTexture("gameview/ori_south_1.png");
        left->setTag(2);
    }
    else if (heroSeatId == 4){
        hero->setTexture("gameview/ori_north_1.png");
        hero->setTag(4);
        right->setTexture("gameview/ori_east_1.png");
        right->setTag(1);
        opposite->setTexture("gameview/ori_south_1.png");
        opposite->setTag(2);
        left->setTexture("gameview/ori_west_1.png");
        left->setTag(3);
    }
}

void Orientation::showWhoBank(int heroSeatId,int bankId){
    
    int clientBankId = SeatIdUtil::getClientSeatId(heroSeatId, bankId);
    if (clientBankId == ClientSeatId::hero){
        hero->setTexture("gameview/ori_bank_1.png");
        hero->setTag(5);
    }
    else if (clientBankId == ClientSeatId::right){
        right->setTexture("gameview/ori_bank_1.png");
        right->setTag(5);
    }
    else if (clientBankId == ClientSeatId::opposite){
        opposite->setTexture("gameview/ori_bank_1.png");
        opposite->setTag(5);
    }
    else if (clientBankId == ClientSeatId::left){
        left->setTexture("gameview/ori_bank_1.png");
        left->setTag(5);
    }
    schedule(schedule_selector(Orientation::updateTime), 1, CC_REPEAT_FOREVER, 0);
}


void Orientation::showPlayerTurn(int heroSeatId, int setaId){
    int turnId = SeatIdUtil::getClientSeatId(heroSeatId, setaId);
    light->setVisible(true);
    if (turnId == ClientSeatId::hero){
        recoverTeture(left);
        recoverTeture(right);
        recoverTeture(opposite);
        changeTeture(hero);
        light->setTexture("gameview/light_xia.png");
    }
    else if (turnId == ClientSeatId::right){
        recoverTeture(left);
        recoverTeture(hero);
        recoverTeture(opposite);
        changeTeture(right);
        light->setTexture("gameview/light_you.png");
    }
    else if (turnId == ClientSeatId::opposite){
        recoverTeture(left);
        recoverTeture(hero);
        recoverTeture(right);
        changeTeture(opposite);
        light->setTexture("gameview/light_shang.png");
    }
    else if (turnId == ClientSeatId::left){
        recoverTeture(opposite);
        recoverTeture(hero);
        recoverTeture(right);
        changeTeture(left);
        light->setTexture("gameview/light_zuo.png");
    }
}

void Orientation::resetBank(){
    recoverTeture(left);
    recoverTeture(right);
    recoverTeture(opposite);
    recoverTeture(hero);
    light->setVisible(false);
}

void Orientation::changeTeture(Sprite* node){
    int tag = node->getTag();
    if (tag == 1){
        node->setTexture("gameview/ori_east_2.png");
    }
    else if (tag == 2){
        node->setTexture("gameview/ori_south_2.png");
    }
    else if (tag == 3){
        node->setTexture("gameview/ori_west_2.png");
    }
    else if (tag == 4){
        node->setTexture("gameview/ori_north_2.png");
    }
    else if (tag == 5){
        node->setTexture("gameview/ori_bank_2.png");
    }
}

void Orientation::recoverTeture(Sprite* node){
    int tag = node->getTag();
    if (tag == 1){
        node->setTexture("gameview/ori_east_1.png");
    }
    else if (tag == 2){
        node->setTexture("gameview/ori_south_1.png");
    }
    else if (tag == 3){
        node->setTexture("gameview/ori_west_1.png");
    }
    else if (tag == 4){
        node->setTexture("gameview/ori_north_1.png");
    }
    else if (tag == 5){
        node->setTexture("gameview/ori_bank_1.png");
    }
    
}

void Orientation::updateTime(float dt){

}
