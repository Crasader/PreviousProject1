
#pragma once
#include "cocos2d.h"
USING_NS_CC;

class CallRcordMecordios{
public:
    static CallRcordMecordios* getInstance();

    /** 开始录音 */
    void beginRecordAudio();
    
    /** 录音结束 */
    void endRecordAudio();
    
    /** 取消录音 */
    void cancelRecordAudio();
    
    /** 播放录音*/
    void playAudio(float value);
    
    /** 删除录音*/
    void deleltefile();
    
    /** 设置可以播放的路径*/
    void setCallCanPlayFilepath(std::string path);
    
    /** 获取录音文件路径*/
    std::string getRecordFilepath();
private:
    CallRcordMecordios();
    static CallRcordMecordios* _instance;
};
