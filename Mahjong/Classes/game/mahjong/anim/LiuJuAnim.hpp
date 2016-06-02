//
//  LiuJuAnim.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/5/24.
//
//

#ifndef LiuJuAnim_hpp
#define LiuJuAnim_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class LiuJuAnim : public Layer{

public:
    virtual bool init();
    CREATE_FUNC(LiuJuAnim);
private:
    void showLiuJuAnim();
};
#endif /* LiuJuAnim_hpp */
