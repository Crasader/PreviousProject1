//
//  FanMaAnim.hpp
//  Mahjong
//
//  Created by qiuzhong on 2017/4/12.
//
//

#ifndef CangYinAnim_hpp
#define CangYinAnim_hpp
#include "cocos2d.h"
USING_NS_CC;

class CangYinAnim : public Layer{
public:
    static CangYinAnim* create(std::string cang);
    bool init(std::string cang);
private:
    int index =0;
    void showFanPai(Sprite* sprite);
    void showTextAnim(Sprite* sprite);
};
#endif /* FanMaAnim_hpp */
