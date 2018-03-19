//
//  HuafeiChangeConfirm.hpp
//  Mahjong
//
//  Created by qiuzhong on 2017/5/31.
//
//

#ifndef HuafeiChangeConfirm_hpp
#define HuafeiChangeConfirm_hpp
#include "cocos2d.h"
USING_NS_CC;

class HuafeiChangeConfirm : public Layer{
public:
    static HuafeiChangeConfirm* create(std::string propId,std::string propName, std::string phone);
    bool init(std::string propId,std::string propName, std::string phone);
private:
    CC_SYNTHESIZE(std::string , itemPropId, ItemPropId);
    CC_SYNTHESIZE(std::string , phoneNum, PhoneNum);
    void confirm();
    void closeView();
};
#endif /* HuafeiChangeConfirm_hpp */
