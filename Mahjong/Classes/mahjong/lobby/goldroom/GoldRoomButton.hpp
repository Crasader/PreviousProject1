//
//  GoldRoomButton.hpp
//  Mahjong
//
//  Created by qiuzhong on 2016/12/20.
//
//

#ifndef GoldRoomButton_hpp
#define GoldRoomButton_hpp
#include "cocos2d.h"
USING_NS_CC;

#define ROOM_1 1001
#define ROOM_2 1002
#define ROOM_3 1003

class GoldRoomButton : public Sprite{
public:
    static GoldRoomButton* create(int roomid,int base,int hua);
    virtual bool init(int roomid,int base,int hua);
private:
    std::string getImageByRoomId(int roomId);
    void openGoldRoom(Ref* ref);
};
#endif /* GoldRoomButton_hpp */
