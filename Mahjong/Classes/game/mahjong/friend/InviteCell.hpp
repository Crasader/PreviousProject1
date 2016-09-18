//
//  InviteCell.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/19.
//
//

#ifndef InviteCell_hpp
#define InviteCell_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "game/mahjong/widget/HeadImage.hpp"

USING_NS_CC;

class InviteCell : public Sprite{
    public :
        static InviteCell* create(HeadImage* headImgae,std::string name);
        bool init(HeadImage* headImgae,std::string name);
    
};

#endif /* InviteCell_hpp */
