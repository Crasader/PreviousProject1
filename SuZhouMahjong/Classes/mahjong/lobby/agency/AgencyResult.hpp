//
//  AgencyResult.hpp
//  SuZhouMahjong
//
//  Created by qiuzhong on 2017/11/30.
//

#ifndef AgencyResult_hpp
#define AgencyResult_hpp
#include "cocos2d.h"
USING_NS_CC;

class AgencyResult : public Layer{
public:
    bool init() override;
    CREATE_FUNC(AgencyResult);
private:
    Layer* dataLayer;
    LabelAtlas* pageNum;
    int index=0;
    int totalPage = 0;
    void closeView();
    void shareImage();
    void afterCaptured(bool succeed, const std::string &outputFile);
    void pageUp();
    void pageDown();
    void updateLayerData();
};
#endif /* AgencyResult_hpp */
