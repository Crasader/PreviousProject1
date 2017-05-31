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
    void afterCaptured(bool succeed, const std::string &outputFile);
    
};
#endif /* HongbaoAnim_hpp */
