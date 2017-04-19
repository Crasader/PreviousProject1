//
//  SoundRecordBtn.hpp
//  Mahjong
//
//  Created by qiuzhong on 2017/3/9.
//
//

#ifndef SoundRecordBtn_hpp
#define SoundRecordBtn_hpp

#include "cocos2d.h"
USING_NS_CC;

#define AUDIO_RECOR_PATH "mahjong_record.amr"

class SoundRecordBtn : public Layer{
    
public:
    virtual bool init() override;
    CREATE_FUNC(SoundRecordBtn);
private:
    Sprite* playBtn;
    float protectedTime =0;
    bool statProtected = false;
    bool startRecord = false;
    void update(float dt);
    bool onTouchBegan(Touch *touch, Event  *event) override;
    void onTouchMoved(Touch *touch, Event  *event) override;
    void onTouchEnded(Touch *touch, Event  *event) override;
    
};
#endif /* SoundRecordBtn_hpp */
