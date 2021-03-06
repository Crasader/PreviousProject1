//
//  HeadImage.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/9/18.
//
//

#ifndef HeadImage_hpp
#define HeadImage_hpp

#include "cocos2d.h"
USING_NS_CC;

class HeadImage : public Sprite{

public:
    static HeadImage* create(Size size);
    static HeadImage* createByImage(std::string image,Size size);
    bool init(std::string image,Size size);
    void updateImage();
    void updateImageByName(std::string image);
    void showImageBySex();
private:
    Size headSize;
};
#endif /* HeadImage_hpp */
