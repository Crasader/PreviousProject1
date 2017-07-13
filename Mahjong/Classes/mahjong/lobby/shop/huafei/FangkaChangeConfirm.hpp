//
//  HuafeiChangeConfirm.hpp
//  Mahjong
//
//  Created by qiuzhong on 2017/5/31.
//
//

#ifndef FangkaChangeConfirm_hpp
#define FangkaChangeConfirm_hpp
#include "cocos2d.h"
USING_NS_CC;

class FangkaChangeConfirm : public Layer{
public:
    static FangkaChangeConfirm* create(std::string fee);
    bool init(std::string fee);
private:
    CC_SYNTHESIZE(std::string, propFee, PropFee);
    void confirm();
    void closeView();
};
#endif /* HuafeiChangeConfirm_hpp */
