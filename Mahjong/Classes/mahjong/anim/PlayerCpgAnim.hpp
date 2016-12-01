//
//  PlayerCpgAnim.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/22.
//
//

#ifndef PlayerCpgAnim_hpp
#define PlayerCpgAnim_hpp

#include "cocos2d.h"
#include "mahjong/state/GameData.h"

USING_NS_CC;

class PlayerCpgAnim : public Layer{

public:
    static PlayerCpgAnim* create(CpgType type,int seatId);

    virtual bool init(CpgType type,int seatId);
private:
    void showCpgAnim(CpgType type,int seatId);
    void showLight(Sprite* sp);
    Point getPosBySeatId(int seatId);
    std::string getImageNameByType(CpgType type);
};
#endif /* PlayerCpgAnim_hpp */
