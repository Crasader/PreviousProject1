#include "http/image/UrlImageMannger.h"
#include "http/HttpMannger.h"
#include "server/CommandManage.h"
#include "http/MD5/MD5.hpp"


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
        //发送刷新头像的请求
        
        Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(url);
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_listener2, 1);
    HttpMannger::getInstance()->httpToPostRequestToGetUrlImg(url);
    return "";
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

