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
    static CompetitonItem* create(CompetitionRoomId roomId,std::string haufei,std::string fangka);
    virtual bool init(CompetitionRoomId roomId,std::string haufei,std::string fangka);
private:
    void joinCompetition(Ref* ref);
};

#endif /* CompetitonItem_hpp */
