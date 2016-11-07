#include "game/mahjong/loading/Loading.h"


Loading* Loading::create(){
	Loading* loding = new Loading();
	if (loding&&loding->init(Point(640,360),false)){
		loding->autorelease();
	}
	else{
		delete loding;
		loding = NULL;
	}
	return loding;
}

Loading* Loading::create(bool touchAble){
    Loading* loding = new Loading();
    if (loding&&loding->init(Point(640,360),touchAble)){
        loding->autorelease();
    }
    else{
        delete loding;
        loding = NULL;
    }
    return loding;
}


static Loading* create(Point pos,bool touchAble){
    Loading* loding = new Loading();
    if (loding&&loding->init(pos,touchAble)){
        loding->autorelease();
    }
    else{
        delete loding;
        loding = NULL;
    }
    return loding;
}


bool Loading::init(Point pos,bool touchAble){

	if (!Layer::init()){

		return false;
	}
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(!touchAble);
	touchListener->onTouchBegan = CC_CALLBACK_2(Loading::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,
		this);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto bg = LayerColor::create(Color4B(0, 0, 0, 0), visibleSize.width, visibleSize.height);
	this->addChild(bg, 20);
	craeteAnimate(pos);
    schedule(schedule_selector(Loading::update), 1.0f, CC_REPEAT_FOREVER, 0);
	return true;
}

void Loading::craeteAnimate(Point pos){
	auto animation = Animation::create();
	for (int i = 1; i < 15; i++)
	{
		char szName[100] = { 0 };
		sprintf(szName, "loading/loding_%d.png", i);
		animation->addSpriteFrameWithFile(szName);
	}
	// should last 2.8 seconds. And there are 14 frames.
	animation->setDelayPerUnit(1.0f / 12.0f);
	animation->setRestoreOriginalFrame(false);
	auto action = Animate::create(animation);
	Sprite* parentSprite = Sprite::create();
    parentSprite->setTag(100);
	parentSprite->setPosition(pos);
	this->addChild(parentSprite);
	auto repeatForever = RepeatForever::create(action);
	parentSprite->runAction(repeatForever);
   
}

void Loading::update(float dt){
    connectOutTime--;
    if(connectOutTime<0){
        connectOutTime = 100000;
        Label* leb = Label::createWithSystemFont("请求超时", "arial", 30);
        leb->setColor(Color3B(66,149,250));
        leb->setPosition(640,320);
        addChild(leb);
        schedule([=](float dt){
            removeFromParent();
        }, 0, 0, 2.0f,"rotk");
    }
}

bool Loading::onTouchBegan(Touch *touch, Event  *event){
	return true;
}
