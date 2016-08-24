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

USING_NS_CC;

class InviteCell : public Sprite{
    public :
        static InviteCell* create(std::string filepath,std::string name);
        bool init(std::string filepath,std::string name);
    
};

#endif /* InviteCell_hpp */
