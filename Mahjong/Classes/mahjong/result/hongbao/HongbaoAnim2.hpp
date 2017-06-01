//
//  HongbaoAnim.hpp
//  Mahjong
//
//  Created by qiuzhong on 2017/5/27.
//
//

#ifndef HongbaoAnim2_hpp
#define HongbaoAnim2_hpp
#include "cocos2d.h"
USING_NS_CC;


class HongbaoAnim2 : public Layer{
public :
    virtual bool init();
    CREATE_FUNC(HongbaoAnim2);
    void initView(std::string hongNum,std::string hongNum2,int type,bool shuang);
private:
    void goBack();
    void share();
    void afterCaptured(bool succeed, const std::string &outputFile);
};
#endif /* HongbaoAnim_hpp */
