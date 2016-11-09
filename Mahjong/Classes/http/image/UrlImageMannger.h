//
//  UrlImageMannger.h
//  图片上传下载工具类
//
//
//

#pragma once
#include "cocos2d.h"
using namespace cocos2d;


class UrlImageMannger{
public:
	static UrlImageMannger* getInstance();
	std::string loadImgByUrl(std::string url);
    void uploadImage2Server(CallFunc* callBack);//上传图片到七牛的服务器
    std::string downloadQunImgByUrl(std::string url);//下载图片到SD卡
    std::string downloadDailiImgByUrl(std::string url);//下载图片到SD卡
private:
	UrlImageMannger();
	static UrlImageMannger* _instance;
    std::string getImgNameByUrl(std::string url);
};

