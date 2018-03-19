//
//  IPConflict.hpp
//  SuZhouMahjong
//
//  Created by qiuzhong on 2017/11/28.
//

#ifndef IPConflict_hpp
#define IPConflict_hpp

#include "cocos2d.h"
USING_NS_CC;

class IPConflict:public Layer{
public:
    bool init() override;
    CREATE_FUNC(IPConflict);
private:
    void closeView();
    void quitGame();
};

#endif /* IPConflict_hpp */
