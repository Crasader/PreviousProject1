#include "http/image/UrlImageMannger.h"
#include "http/HttpMannger.h"
#include "server/NetworkManage.h"
#include "http/MD5/MD5.hpp"
#include "game/utils/GameConfig.h"
#include "game/mahjong/state/GameData.h"
#include "payment/android/CallAndroidMethod.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#endif

UrlImageMannger* UrlImageMannger::_instance = NULL;

UrlImageMannger::UrlImageMannger(){
    
}


UrlImageMannger* UrlImageMannger::getInstance(){
    if (_instance == NULL){
        _instance = new UrlImageMannger();
    }
    return _instance;
}

std::string UrlImageMannger::loadImgByUrl(std::string url)
{
    std::string path = getImgNameByUrl(url);
    if (FileUtils::getInstance()->isFileExist(path))
    {
        return path;
    }
    EventListenerCustom* _listener2 = EventListenerCustom::create(url, [=](EventCustom* event){
        std::vector<char>*buffer = static_cast<std::vector<char>*>(event->getUserData());
        std::string buff(buffer->begin(), buffer->end());
        FILE *fp = fopen(path.c_str(), "wb+");
        fwrite(buff.c_str(), 1, buffer->size(), fp);
        fclose(fp);
        //发送刷新头像的事件
        EventCustom imageEvent(MSG_UPDATE_PLAYER_WECHAT_IMAGE);
        Director::getInstance()->getEventDispatcher()->dispatchEvent(&imageEvent);
        Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(url);
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_listener2, 1);
    HttpMannger::getInstance()->httpToPostRequestToGetUrlImg(url);
    return IAMGE_LOADING;
}

std::string UrlImageMannger::downloadQunImgByUrl(std::string url){
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string path =StringUtils::format("%s/wanjiaquan.png",CallAndroidMethod::getInstance()->getSdCardDir().c_str());
    if (FileUtils::getInstance()->isFileExist(path))
    {
        return path;
    }
    EventListenerCustom* _listener2 = EventListenerCustom::create(url, [=](EventCustom* event){
        std::vector<char>*buffer = static_cast<std::vector<char>*>(event->getUserData());
        std::string buff(buffer->begin(), buffer->end());
        FILE *fp = fopen(path.c_str(), "wb+");
        fwrite(buff.c_str(), 1, buffer->size(), fp);
        fclose(fp);
        UserData::getInstance()->setWanJiaQunVersion(GAMEDATA::getInstance()->getWanJiaQunVer());
        Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(url);
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_listener2, 1);
    HttpMannger::getInstance()->httpToPostRequestToGetUrlImg(url);
    return IAMGE_LOADING;
#endif
}

std::string UrlImageMannger::downloadDailiImgByUrl(std::string url){
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string path =StringUtils::format("%s/dailiqun.png",CallAndroidMethod::getInstance()->getSdCardDir().c_str());
    if (FileUtils::getInstance()->isFileExist(path))
    {
        return path;
    }
    EventListenerCustom* _listener2 = EventListenerCustom::create(url, [=](EventCustom* event){
        std::vector<char>*buffer = static_cast<std::vector<char>*>(event->getUserData());
        std::string buff(buffer->begin(), buffer->end());
        FILE *fp = fopen(path.c_str(), "wb+");
        fwrite(buff.c_str(), 1, buffer->size(), fp);
        fclose(fp);
        UserData::getInstance()->setDailiQunVersion(GAMEDATA::getInstance()->getDailiQunVer());
        Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(url);
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_listener2, 1);
    HttpMannger::getInstance()->httpToPostRequestToGetUrlImg(url);
    return IAMGE_LOADING;
#endif
}

void UrlImageMannger::uploadImage2Server(CallFunc* callBack){
    //TODO 调用七牛SDK(android或者ios)
    
}

std::string UrlImageMannger::getImgNameByUrl(std::string url)
{
    MD5 md5;
    md5.update(url.c_str(), url.size());
    std::string temp = FileUtils::sharedFileUtils()->getWritablePath() + md5.toString().c_str();
    md5.reset();
    return temp;
}

