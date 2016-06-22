#include "DailyEvent.h"

bool DailyEvent::init(){
	if (!Layer::init()){
		return false;
	}
	return true;
}

void DailyEvent::onEnter(){
	Layer::onEnter();
	addEventCustom();
}

void DailyEvent::onExit(){
	Layer::onExit();
	_eventDispatcher->removeEventListener(dailyTaskListener);
    _eventDispatcher->removeEventListener(dailyWelfareListener);
    _eventDispatcher->removeEventListener(dailyPrideListener);
    _eventDispatcher->removeEventListener(dailySignListener);
}

void DailyEvent::showDailyEvent(DailyType type){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getDailySignCommand());//签到
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getDailyTaskCommand());//任务
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getWelfareCommand());//福利
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getDailyPrideCommand());//抽奖
    
	MenuItem* item1 = MenuItem::create();
	item1->setContentSize(Size(1280, 720));
	Menu* menu1 = Menu::create(item1, NULL);
	this->addChild(menu1,-1);

	auto all_bg = Sprite::create("common/all_bg.jpg");
	all_bg->setPosition(640, 360);
	addChild(all_bg);
	auto day_bg = Sprite::create("daily/daily_bg.png");
	day_bg->setPosition(640, 360);
	addChild(day_bg);

	//add close btn to layer
	auto close = MenuItemImage::create("daily/close_btn_1.png", "daily/close_btn_2.png",
		CC_CALLBACK_0(DailyEvent::closeView, this));
	auto closeMenu = Menu::create(close, NULL);
	closeMenu->setPosition(1050, 610);
	addChild(closeMenu,1);

	auto table_bg = Sprite::create("daily/tab_bg.png");
	table_bg->setPosition(560, 610);
	addChild(table_bg,1);

	auto day_task_normal = MenuItemImage::create("daily/tab_btn_1.png", "daily/tab_btn_1.png");
	auto day_task_selected = MenuItemImage::create("daily/tab_btn_2.png", "daily/tab_btn_2.png");
	taskToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(DailyEvent::showDailyTask, this), day_task_normal, day_task_selected, NULL);

	auto day_welfare_normal = MenuItemImage::create("daily/tab_btn_1.png", "daily/tab_btn_1.png");
	auto day_welfare_selected = MenuItemImage::create("daily/tab_btn_2.png", "daily/tab_btn_2.png");
	welfareToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(DailyEvent::showWelFare, this), day_welfare_normal, day_welfare_selected, NULL);

	auto day_pride_normal = MenuItemImage::create("daily/tab_btn_1.png", "daily/tab_btn_1.png");
	auto day_pride_selected = MenuItemImage::create("daily/tab_btn_2.png", "daily/tab_btn_2.png");
	prideToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(DailyEvent::showDailyPride, this), day_pride_normal, day_pride_selected, NULL);

	auto day_sign_normal = MenuItemImage::create("daily/tab_btn_1.png", "daily/tab_btn_1.png");
	auto day_sign_selected = MenuItemImage::create("daily/tab_btn_2.png", "daily/tab_btn_2.png");
	signToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(DailyEvent::showDailySign, this), day_sign_normal, day_sign_selected, NULL);

	auto menu = Menu::create(taskToggle, welfareToggle, prideToggle, signToggle, NULL);
	menu->alignItemsHorizontallyWithPadding(20);
	menu->setPosition(560, 610);
	addChild(menu,1);

	dailyTask = Sprite::create("daily/daily_task_1.png");
	dailyTask->setPosition(302, 610);
	addChild(dailyTask,1);
	dailyWelfare = Sprite::create("daily/daily_welfare_1.png");
	dailyWelfare->setPosition(479, 610);
	addChild(dailyWelfare,1);
	dailyPride = Sprite::create("daily/daily_pride_1.png");
	dailyPride->setPosition(650, 610);
	addChild(dailyPride,1);
	dailySign = Sprite::create("daily/daily_sign_1.png");
	dailySign->setPosition(823, 610);
	addChild(dailySign,1);

	dailyTaskLayer = DailyTask::create();
	dailyTaskLayer->setVisible(false);
	addChild(dailyTaskLayer);

	dailyWelfareLayer = DailyWelfare::create();
	dailyWelfareLayer->setVisible(false);
	addChild(dailyWelfareLayer);

	dailyPrideLayer = DailyPride::create();
	dailyPrideLayer->setVisible(false);
	addChild(dailyPrideLayer);

	dailySignLayer = DailySign::create();
	dailySignLayer->setVisible(false);
	addChild(dailySignLayer);



	if (type == task){
		taskToggle->setSelectedIndex(1);
		welfareToggle->setSelectedIndex(0);
		prideToggle->setSelectedIndex(0);
		signToggle->setSelectedIndex(0);
		dailyTask->setTexture("daily/daily_task_2.png");
		dailyTaskLayer->setVisible(true);
	}
	else if (type == welfare){
		taskToggle->setSelectedIndex(0);
		welfareToggle->setSelectedIndex(1);
		prideToggle->setSelectedIndex(0);
		signToggle->setSelectedIndex(0);
		dailyWelfare->setTexture("daily/daily_welfare_2.png");
		dailyWelfareLayer->setVisible(true);
	} else if(type == pride){
		taskToggle->setSelectedIndex(0);
		welfareToggle->setSelectedIndex(0);
		prideToggle->setSelectedIndex(1);
		signToggle->setSelectedIndex(0);
		dailyPride->setTexture("daily/daily_pride_2.png");
		dailyPrideLayer->setVisible(true);
	}
	else if (type == sign){
		taskToggle->setSelectedIndex(0);
		welfareToggle->setSelectedIndex(0);
		prideToggle->setSelectedIndex(0);
		signToggle->setSelectedIndex(1);
		dailySign->setTexture("daily/daily_sign_2.png");
		dailySignLayer->setVisible(true);
	}


}


void DailyEvent::showDailyTask(Ref* ref){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getDailyTaskCommand());//任务
	MenuItemToggle* temp = (MenuItemToggle*)ref;
	taskToggle->setSelectedIndex(1);
	welfareToggle->setSelectedIndex(0);
	prideToggle->setSelectedIndex(0);
	signToggle->setSelectedIndex(0);
	dailyTask->setTexture("daily/daily_task_2.png");
	dailyWelfare->setTexture("daily/daily_welfare_1.png");
	dailyPride->setTexture("daily/daily_pride_1.png");
	dailySign->setTexture("daily/daily_sign_1.png");
	dailyTaskLayer->setVisible(true);
	dailyWelfareLayer->setVisible(false);
	dailySignLayer->setVisible(false);
	dailyPrideLayer->setVisible(false);
}

void DailyEvent::showWelFare(Ref* ref){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getWelfareCommand());//福利
	MenuItemToggle* temp = (MenuItemToggle*)ref;
	taskToggle->setSelectedIndex(0);
	welfareToggle->setSelectedIndex(1);
	prideToggle->setSelectedIndex(0);
	signToggle->setSelectedIndex(0);
	dailyTask->setTexture("daily/daily_task_1.png");
	dailyWelfare->setTexture("daily/daily_welfare_2.png");
	dailyPride->setTexture("daily/daily_pride_1.png");
	dailySign->setTexture("daily/daily_sign_1.png");
	dailyTaskLayer->setVisible(false);
	dailyWelfareLayer->setVisible(true);
	dailyPrideLayer->setVisible(false);
	dailySignLayer->setVisible(false);
}

void DailyEvent::showDailyPride(Ref* ref){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getDailyPrideCommand());//抽奖
	MenuItemToggle* temp = (MenuItemToggle*)ref;
	taskToggle->setSelectedIndex(0);
	welfareToggle->setSelectedIndex(0);
	prideToggle->setSelectedIndex(1);
	signToggle->setSelectedIndex(0);
	dailyTask->setTexture("daily/daily_task_1.png");
	dailyWelfare->setTexture("daily/daily_welfare_1.png");
	dailyPride->setTexture("daily/daily_pride_2.png");
	dailySign->setTexture("daily/daily_sign_1.png");
	dailyTaskLayer->setVisible(false);
	dailyWelfareLayer->setVisible(false);
	dailyPrideLayer->setVisible(true);
	dailySignLayer->setVisible(false);
}

void DailyEvent::showDailySign(Ref* ref){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getDailySignCommand());//签到
	MenuItemToggle* temp = (MenuItemToggle*)ref;
	taskToggle->setSelectedIndex(0);
	welfareToggle->setSelectedIndex(0);
	prideToggle->setSelectedIndex(0);
	signToggle->setSelectedIndex(1);
	dailyTask->setTexture("daily/daily_task_1.png");
	dailyWelfare->setTexture("daily/daily_welfare_1.png");
	dailyPride->setTexture("daily/daily_pride_1.png");
	dailySign->setTexture("daily/daily_sign_2.png");
	dailyTaskLayer->setVisible(false);
	dailyWelfareLayer->setVisible(false);
	dailyPrideLayer->setVisible(false);
	dailySignLayer->setVisible(true);
}

void DailyEvent::closeView(){
	removeFromParent();
}


void DailyEvent::addEventCustom(){
	dailyTaskListener = EventListenerCustom::create(MSG_PLAYER_DAILY_TASK, [=](EventCustom* event){
		if (dailyTaskLayer->isVisible()){
			dailyTaskLayer->updateData();
		}	
	});
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(dailyTaskListener, 1);

    dailyWelfareListener = EventListenerCustom::create(MSG_PLAYER_WELFARE_INFO, [=](EventCustom* event){
        if (dailyWelfareLayer->isVisible()){
            dailyWelfareLayer->updateData();
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(dailyWelfareListener, 1);
    
    dailyPrideListener = EventListenerCustom::create(MSG_PLAYER_DAILY_PRIDE, [=](EventCustom* event){
        if (dailyPrideLayer->isVisible()){
            dailyPrideLayer->updateData();
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(dailyPrideListener, 1);
    
    dailySignListener = EventListenerCustom::create(MSG_PLAYER_DAILY_SIGN, [=](EventCustom* event){
        if (dailySignLayer->isVisible()){
            dailySignLayer->updateData();
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(dailySignListener, 1);
}