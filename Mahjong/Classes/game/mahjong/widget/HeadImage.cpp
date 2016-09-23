//
//  HeadImage.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/9/18.
//
//

#include "game/mahjong/widget/HeadImage.hpp"
#include "userdata/UserData.h"
#include "http/image/UrlImageMannger.h"

HeadImage* HeadImage::create(cocos2d::Size size){
    return createByImage("null",size);
}

HeadImage* HeadImage::createByImage(std::string image,Size size){
    HeadImage* temp = new HeadImage();
    if(NULL != temp && temp->init(image,size)){
        temp->autorelease();
    }else{
        CC_SAFE_DELETE(temp);
        temp = NULL;
    }
    return temp;
}

bool HeadImage::init(std::string image,cocos2d::Size size){
    headSize = size;
    initWithFile("gameview/head_image_1.png");
    updateImageByName(image);
    return true;
}

void HeadImage::updateImage(){
    this->updateImageByName("null");
}

void HeadImage::updateImageByName(std::string image){
    if(image == "null"){
        if(UserData::getInstance()->getPicture() == "1"){
            setTexture("gameview/head_image_1.png");
        }else if(UserData::getInstance()->getPicture() == "2"){
            setTexture("gameview/head_image_2.png");
        }else if(UserData::getInstance()->getPicture() == "3"){
            setTexture("gameview/head_image_3.png");
        }else if(UserData::getInstance()->getPicture() == "4"){
            setTexture("gameview/head_image_4.png");
        }else{
            std::string path = UrlImageMannger::getInstance()->loadImgByUrl(UserData::getInstance()->getPicture());
            setTexture(path);
            setScale(headSize.width/getContentSize().width,headSize.height/getContentSize().height);
        }
    }else{
        if(image == ""){
         setTexture("gameview/head_image_1.png");
        }
        else if(image == "1"){
            setTexture("gameview/head_image_1.png");
        }else if(image == "2"){
            setTexture("gameview/head_image_2.png");
        }else if(image == "3"){
            setTexture("gameview/head_image_3.png");
        }else if(image == "4"){
            setTexture("gameview/head_image_4.png");
        }else{
            std::string path = UrlImageMannger::getInstance()->loadImgByUrl(image);
            setTexture(path);
            setScale(headSize.width/getContentSize().width,headSize.height/getContentSize().height);
        }
        
    }
}
