//
//  OutFogAnim.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/1.
//
//

#ifndef OutFogAnim_hpp
#define OutFogAnim_hpp

#include "cocos2d.h"
USING_NS_CC;

class OutFogAnim : public Layer{
public:
    static OutFogAnim* create(Point pos);
    virtual bool init(Point pos);
private:
    void showFogAnim(Sprite* sprite);

};
#endif /* OutFogAnim_hpp */
