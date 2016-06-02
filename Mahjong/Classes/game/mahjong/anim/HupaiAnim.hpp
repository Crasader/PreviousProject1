//
//  HupaiAnim.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/25.
//
//

#ifndef HupaiAnim_hpp
#define HupaiAnim_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class HupaiAnim : public Layer{
public:
    static HupaiAnim* create(int jongType,int seatId1,std::vector<int> seatId2);
    virtual bool init(int jongType,int seatId1,std::vector<int> seatId2);
private:
    void showPokersLight(int seatId);
    void showHuAnim(int seatid);
    void showDianpaoAnim(int seatId1,int seatId2,int jong);
    Point getPosbySeat(int seatId);
    void showLightAnim(Sprite* sprite);
    void showBgLight(Sprite* sprite);
    void showLighting(Sprite* lighting);
    
};

#endif /* HupaiAnim_hpp */
