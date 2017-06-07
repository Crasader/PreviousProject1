//
//  HongbaoAnim.hpp
//  Mahjong
//
//  Created by qiuzhong on 2017/5/27.
//
//

#ifndef HongbaoAnim_hpp
#define HongbaoAnim_hpp
#include "cocos2d.h"
USING_NS_CC;


class HongbaoAnim : public Layer{
    public :
    virtual bool init();
    CREATE_FUNC(HongbaoAnim);
    void initView(std::string hongNum,int type);
private:
    void goBack();
    void share();
    CC_SYNTHESIZE(std::string,hongBaoNum, HongBaoNum);
};
#endif /* HongbaoAnim_hpp */
