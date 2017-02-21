#include "mahjong/widget/batteryinfo/BatteryInfo.h"
#include "payment/android/CallAndroidMethod.h"
#import "payment/ios/IOSBridge.h"

bool BatteryInfo::init() {
	Node::init();

	auto _vSize = Director::getInstance()->getVisibleSize();
    
    Sprite* batteryInfoBg = Sprite::create("batteryInfo/batterInfoBg.png");
    batteryInfoBg->setPosition(30, _vSize.height-18);
    addChild(batteryInfoBg);
    
    batteryItem = Sprite::create("batteryInfo/batteryItem.png");
    batteryItem->setAnchorPoint(Vec2(0, 0));
    batteryItem->setPosition(8, 8);
    batteryInfoBg->addChild(batteryItem);
    
    Sprite* timerBg = Sprite::create("batteryInfo/timerBg.png");
	timerBg->setPosition(90, _vSize.height-18);
	addChild(timerBg);
	
	timerLabel = Label::createWithSystemFont("12:00","Arial",25);
    timerLabel->setColor(Color3B(171,186,183));
	timerLabel->setPosition(Vec2(timerBg->getContentSize().width / 2, timerBg->getContentSize().height / 2));  //24
	timerBg->addChild(timerLabel);
	
	wifiInfo = Sprite::create("batteryInfo/wifi4.png");
	wifiInfo->setPosition(150, _vSize.height-20);
    wifiInfo->setVisible(false);
	addChild(wifiInfo);


	schedule(schedule_selector(BatteryInfo::updateInfo), 10.0f, CC_REPEAT_FOREVER, 0);
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
	sprintf(buffer, "%02d:%02d",
		ptm->tm_hour, ptm->tm_min);

	return std::string(buffer);
}


void BatteryInfo::updateInfo(float delta)
{
	timerLabel->setString(gettime());
    
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	batteryItem->setScaleX(atoi(CallAndroidMethod::getInstance()->getBatteryPersent().c_str())/100.0f);
#endif

#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    batteryItem->setScaleX(atoi(IOSBridge::getInstance()->getBatteryPersent().c_str())/100.0f);
#endif
    
//	int  netType, netLevel;
//	CallAndroidMethod::getInstance()->getNetInfo(netType, netLevel);
//	switch (netType)
//	{
//	case -1:
//		wifiInfo->setTexture("batteryInfo/signial1.png");
//		break;
//	case 1:
//	{
//
//		auto path = StringUtils::format("mjlobby/batteryInfo/wifi%d.png", netLevel > 4 ? 4 : netLevel);
//		wifiInfo->setTexture(path.c_str());
//	}
//	
//		break;
//	case 2:
//	{
//		auto path = StringUtils::format("mjlobby/batteryInfo/signial%d.png", netLevel > 4 ? 4 : netLevel);
//		wifiInfo->setTexture(path.c_str());
//	}
//		break;
//	default:
//		break;
//	}

}
