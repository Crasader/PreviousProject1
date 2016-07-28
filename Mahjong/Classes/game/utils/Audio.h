#ifndef _AUDIO_H_
#define _AUDIO_H_
#include <string>
#include "cocos2d.h"

class Audio{
public:
    static Audio* getInstance();
    void init();
    void playBGM();
    void pauseBGM();
    void playMahjong(int type,int gender);
    
    void playSoundWan1(int gender);
    void playSoundWan2(int gender);
    void playSoundWan3(int gender);
    void playSoundWan4(int gender);
    void playSoundWan5(int gender);
    void playSoundWan6(int gender);
    void playSoundWan7(int gender);
    void playSoundWan8(int gender);
    void playSoundWan9(int gender);
    
    void playSoundTong1(int gender);
    void playSoundTong2(int gender);
    void playSoundTong3(int gender);
    void playSoundTong4(int gender);
    void playSoundTong5(int gender);
    void playSoundTong6(int gender);
    void playSoundTong7(int gender);
    void playSoundTong8(int gender);
    void playSoundTong9(int gender);
    
    void playSoundTiao1(int gender);
    void playSoundTiao2(int gender);
    void playSoundTiao3(int gender);
    void playSoundTiao4(int gender);
    void playSoundTiao5(int gender);
    void playSoundTiao6(int gender);
    void playSoundTiao7(int gender);
    void playSoundTiao8(int gender);
    void playSoundTiao9(int gender);
    
    void playSoundEast(int gender);
    void playSoundWest(int gender);
    void playSoundNorth(int gender);
    void playSoundSouth(int gender);
    
    void playSoundChi(int type,int gender);
    void playSoundPeng(int gender);
    void playSoundGang(int gender);
    void playSoundHua(int gender);
    void playSoundHuaChi(int gender);
    void playSoundTing(int gender);
    void playSoundSlow(int gender);
    void playSoundXiaGeng(int gender);
    void playSoundGengShang(int gender);
    void playSoundWaitChi(int gender);
    void playSoundWaitPeng(int gender);
    void playSoundChi3(int gender);
    void playSoundChong(int gender);
    void playSoundLiuJu(int gender);
    void playSoundTouzi();
    
    void playSoundClick();
    void playSoundHu(int type);
    
    
    void setBGMValue(float value);
    void setEffectValue(float value);
    
    CC_SYNTHESIZE(bool, hasTingPlayer, HasTingPlayer);//是否有玩家听牌(音效相关的状态)
    
private:
    static Audio* m_instance;
    CC_SYNTHESIZE(bool, isFirstDong, IsFirstDong);
    CC_SYNTHESIZE(int, bgmId, BgmId);

};
#endif