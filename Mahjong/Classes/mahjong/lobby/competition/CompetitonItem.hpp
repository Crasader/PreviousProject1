//
//  CompetitonItem.hpp
//  Mahjong
//
//  Created by qiuzhong on 2017/5/19.
//
//

#ifndef CompetitonItem_hpp
#define CompetitonItem_hpp
#include "cocos2d.h"
#include "mahjong/common/state/GameData.h"
USING_NS_CC;



class CompetitonItem : public Sprite{
public:
    static CompetitonItem* create(CompetitionRoomId roomId,std::string haufei,std::string fangka,std::string rule);
    virtual bool init(CompetitionRoomId roomId,std::string haufei,std::string fangka,std::string rule);
private:
    void joinCompetition(Ref* ref);
    CC_SYNTHESIZE(CompetitionRoomId, roomId, RoomId);
    CC_SYNTHESIZE(std::string, huaFei, HuaFei);
    CC_SYNTHESIZE(std::string, fangka, Fangka);
    CC_SYNTHESIZE(std::string, rule, Rule);
};

#endif /* CompetitonItem_hpp */
