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
	std::string loadHeadImgByUrl(std::string url);//下载头像图片
    std::string loadNoticeImgByUrl(std::string url);//下载推广图片
    std::string loadShopImgByUrl(std::string url);//下载商城图片
    void uploadImage2Server(CallFunc* callBack);//上传图片到七牛的服务器
    std::string downloadQunImgByUrl(std::string url,bool recover = false);//下载图片到SD卡
    std::string downloadDailiImgByUrl(std::string url,bool recover = false);//下载图片到SD卡
    std::string downloadGongGaoImgByUrl(std::string url);
private:
	UrlImageMannger();
	static UrlImageMannger* _instance;
    std::string getImgNameByUrl(std::string url);
};

