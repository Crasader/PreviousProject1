#ifndef _AUDIO_H_
#define _AUDIO_H_
#include <string>


class Audio{
public:
    static Audio* getInstance();
    void playBGM();
    void pauseBGM();
    void playMahjong(int type);
    
    void playSoundWan1();
    void playSoundWan2();
    void playSoundWan3();
    void playSoundWan4();
    void playSoundWan5();
    void playSoundWan6();
    void playSoundWan7();
    void playSoundWan8();
    void playSoundWan9();
    
    void playSoundTong1();
    void playSoundTong2();
    void playSoundTong3();
    void playSoundTong4();
    void playSoundTong5();
    void playSoundTong6();
    void playSoundTong7();
    void playSoundTong8();
    void playSoundTong9();
    
    void playSoundTiao1();
    void playSoundTiao2();
    void playSoundTiao3();
    void playSoundTiao4();
    void playSoundTiao5();
    void playSoundTiao6();
    void playSoundTiao7();
    void playSoundTiao8();
    void playSoundTiao9();
    
    void playSoundEast();
    void playSoundWest();
    void playSoundNorth();
    void playSoundSouth();
    
    void playSoundChi(int type);
    void playSoundPeng();
    void playSoundGang();
    
    void prepare();
    void setBGMValue(float value);
    void setEffectValue(float value);
private:
    static Audio* m_instance;
};
#endif