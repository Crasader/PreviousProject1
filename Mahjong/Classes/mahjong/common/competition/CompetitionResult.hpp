//
//  CompetitionResult.hpp
//  Mahjong
//
//  Created by qiuzhong on 2017/5/22.
//
//

#ifndef CompetitionResult_hpp
#define CompetitionResult_hpp

#include "cocos2d.h"
#include "mahjong/common/state/GameData.h"
USING_NS_CC;


class CompetitionResult : public Layer{
public:
    virtual bool init();
    void onEnter() override;
    void onExit() override;
    void showCompetiotionResult(std::string type,std::string rank,std::string pride,std::string score);
    CREATE_FUNC(CompetitionResult);
private:
    void share();
    void showWin(std::string type,std::string rank,std::string pride,std::string score);
    void showLose(std::string type,std::string rank,std::string pride,std::string score);
    void quit();
    void continueCompetition();
    void afterCaptured(bool succeed, const std::string &outputFile);
    EventListenerCustom* joinResp;
};

#endif /* CompetitionResult_hpp */
