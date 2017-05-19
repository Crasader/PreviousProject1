//
//  CompetitonLayer.hpp
//  Mahjong
//
//  Created by qiuzhong on 2017/5/19.
//
//

#ifndef CompetitonLayer_hpp
#define CompetitonLayer_hpp
#include "cocos2d.h"
#include "mahjong/common/state/GameData.h"
USING_NS_CC;


class CompetitonLayer : public Layer{
public:
    virtual bool init();
    void initView(CompetitionRoomId roomId,std::string huafei,std::string fangka,std::string rule);
    CREATE_FUNC(CompetitonLayer);
private:
    void closeView();

};
#endif /* CompetitonLayer_hpp */
