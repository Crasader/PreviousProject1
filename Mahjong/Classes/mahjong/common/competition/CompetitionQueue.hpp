//
//  CompetitionQueue.hpp
//  Mahjong
//
//  Created by qiuzhong on 2017/5/17.
//
//

#ifndef CompetitionQueue_hpp
#define CompetitionQueue_hpp
#include "cocos2d.h"
USING_NS_CC;

class CompetitionQueue : public Layer{
public:
    bool init();
    void onEnter();
    void onExit();
    CREATE_FUNC(CompetitionQueue);
private:
    EventListenerCustom* quitResp;
    void quitCompetiton();
};
#endif /* CompetitionQueue_hpp */
