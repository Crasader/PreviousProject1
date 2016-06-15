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
	void LoadImgByUrl(std::string url);
	std::string getImgNameByUrl(std::string url);
    void uploadImage2Server(CallFunc* callBack);//上传图片到七牛的服务器
private:
	UrlImageMannger();
	static UrlImageMannger* _instance;


};

