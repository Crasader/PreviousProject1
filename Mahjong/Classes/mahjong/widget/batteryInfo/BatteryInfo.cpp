#include "mahjong/widget/batteryinfo/BatteryInfo.h"
#include "payment/android/CallAndroidMethod.h"

bool BatteryInfo::init() {
	Node::init();

	auto _vSize = Director::getInstance()->getVisibleSize();
//	auto difvec2 = _vSize / 2;
	Sprite* timerBg = Sprite::create("batteryInfo/timerBg.png");
	timerBg->setPosition(_vSize.width - 54, 57);
	addChild(timerBg);
	
	timerLabel = Label::createWithCharMap("batteryInfo/timerNumber.png", 14, 19, '0');
	timerLabel->setString("11:59");
	timerLabel->setPosition(Vec2(timerBg->getContentSize().width / 2, timerBg->getContentSize().height / 2));  //24
	timerBg->addChild(timerLabel);
	
	Sprite* batteryInfoBg = Sprite::create("batteryInfo/batterInfoBg.png");
	batteryInfoBg->setPosition(_vSize.width - 140, 58);
	addChild(batteryInfoBg);

	batteryItem = Sprite::create("batteryInfo/batteryItem.png");
	batteryItem->setAnchorPoint(Vec2(0, 0));
	batteryItem->setPosition(4, 4);
	batteryItem->setScaleX(10);
	batteryInfoBg->addChild(batteryItem);
	
	wifiInfo = Sprite::create("batteryInfo/wifi4.png");
	wifiInfo->setPosition(_vSize.width - 200, 60);
	addChild(wifiInfo);


	schedule(schedule_selector(BatteryInfo::updateInfo), 1.0f, CC_REPEAT_FOREVER, 0);
	return true;
}



std::string gettime()
{
	struct tm *ptm;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	struct timeval now;
	gettimeofday(&now, NULL);
	ptm = localtime(&now.tv_sec);
#endif

#if ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
	time_t timep;
	time(&timep);
	ptm = localtime(&timep);
#endif

	// Format: 2015-08-19 17:51:36
	char buffer[128] = { 0 };
	sprintf(buffer, "%02d:%02d:%02d",
		ptm->tm_hour, ptm->tm_min, ptm->tm_sec);

	return std::string(buffer);
}


void BatteryInfo::updateInfo(float delta)
{
	timerLabel->setString(gettime());

//	batteryItem->setScaleX(CallAndroidMethod::getInstance()->getBatteryPersent()/100.0f* (40.0f/2));
	
	int  netType, netLevel;
//	CallAndroidMethod::getInstance()->getNetInfo(netType, netLevel);
	switch (netType)
	{
	case -1:
		wifiInfo->setTexture("batteryInfo/signial1.png");
		break;
	case 1:
	{

		auto path = String::createWithFormat("mjlobby/batteryInfo/wifi%d.png", netLevel > 4 ? 4 : netLevel);
		wifiInfo->setTexture(path->getCString());
	}
	
		break;
	case 2:
	{
		auto path = String::createWithFormat("mjlobby/batteryInfo/signial%d.png", netLevel > 4 ? 4 : netLevel);
		wifiInfo->setTexture(path->getCString());
	}
		break;
	default:
		break;
	}

}
