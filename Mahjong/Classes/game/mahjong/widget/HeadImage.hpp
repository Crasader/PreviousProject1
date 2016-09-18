//
//  HeadImage.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/9/18.
//
//

#ifndef HeadImage_hpp
#define HeadImage_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class HeadImage : public Sprite{

public:
    static HeadImage* create(Size size);
    bool init(Size size);
    void updateImage();
private:
    Size headSize;
};
#endif /* HeadImage_hpp */
