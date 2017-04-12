//
//  FanMaAnim.hpp
//  Mahjong
//
//  Created by qiuzhong on 2017/4/12.
//
//

#ifndef FanMaAnim_hpp
#define FanMaAnim_hpp
#include "cocos2d.h"
USING_NS_CC;

class FanMaAnim : public Layer{
public:
    static FanMaAnim* create(std::vector<std::string> mas);
    bool init(std::vector<std::string> mas);
private:
    void showTextAnim(Sprite* sprite);
    void showFanPai(Sprite* sprite);
};
#endif /* FanMaAnim_hpp */
