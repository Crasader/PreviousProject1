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
	ori_bg->setPosition(640, 390);
	addChild(ori_bg);
	left = Sprite::create();
	left->setRotation(90);
	left->setPosition(575, 395);
	addChild(left);
	right = Sprite::create();
	right->setPosition(710, 395);
	right->setRotation(270);
	addChild(right);
	opposite = Sprite::create();
	opposite->setPosition(640, 445);
	opposite->setRotation(180);
	addChild(opposite);
	hero = Sprite::create();
	hero->setPosition(640, 340);
	addChild(hero);
	light = Sprite::create("gameview/light.png");
	light->setVisible(false);
	addChild(light,2);
    auto time = LabelAtlas::create(StringUtils::format("%d",timeNumber), "gameview/time_num_mid.png", 23, 36, '0');
    time->setAnchorPoint(Point::ANCHOR_MIDDLE);
    time->setPosition(640,390);
    time->setTag(100);
    addChild(time,5);
    if(GAMEDATA::getInstance()->getIsCompetitionState()||GAMEDATA::getInstance()->getIsCompetitionQueue()){
        time->setVisible(true);
    }else{
        time->setVisible(false);
    }
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
    timeNumber = 15;
	int turnId = SeatIdUtil::getClientSeatId(heroSeatId, setaId);
	light->setVisible(true);
	if (turnId == ClientSeatId::hero){
        recoverTeture(left);
        recoverTeture(right);
        recoverTeture(opposite);
		changeTeture(hero);
        light->setScale(1.0f);
        light->setRotation(180);
		light->setPosition(640, 340);
	}
	else if (turnId == ClientSeatId::right){
        recoverTeture(left);
        recoverTeture(hero);
        recoverTeture(opposite);
		changeTeture(right);
		light->setRotation(90);
        light->setScaleX(0.80);
		light->setPosition(705, 393);
	}
	else if (turnId == ClientSeatId::opposite){
        recoverTeture(left);
        recoverTeture(hero);
        recoverTeture(right);
		changeTeture(opposite);
		light->setRotation(0);
        light->setScale(1.0f);
		light->setPosition(640, 445);
	}
	else if (turnId == ClientSeatId::left){
        recoverTeture(opposite);
        recoverTeture(hero);
        recoverTeture(right);
		changeTeture(left);
        light->setRotation(270);
        light->setScaleX(0.80);
		light->setPosition(575, 393);
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
    if(timeNumber>0){
        timeNumber--;
        if(NULL != getChildByTag(100)){
            ((LabelAtlas*)getChildByTag(100))->setString(StringUtils::format("%d",timeNumber));
        }
    }
}
