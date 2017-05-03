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
    void playMahjong(int type,int gender);//报牌
    void playMahjongNormal(int type,int gender);//普通话报牌
    void playSoundPengNormal(int gender);//碰
    void playSoundGangNormal(int gender);//杠
    void playSoundHuNormal(int gender);//胡牌语音
    void playSoundChi(int type,int gender);//吃
    void playSoundPeng(int gender);//碰
    void playSoundGang(int gender);//杠
    void playSoundHu(int type,int gender);//胡牌语音
    void playSoundHuaChi(int gender);//花痴
    void playSoundTing(int gender);//听
    void playSoundSlow(int gender);//出牌慢
    void playSoundXiaGeng(int gender);//下家跟牌
    void playSoundGengShang(int gender);//跟上家牌
    void playSoundWaitChi(int gender);//等吃
    void playSoundWaitPeng(int gender);//等碰
    void playSoundChi3(int gender);//吃3手
    void playSoundChong(int gender);//冲牌
    void playSoundLiuJu(int gender);//流句
    void playSoundTouzi();//骰子
    void playSoundFapai();//发牌
    void playSoundClosePage();//关闭页面
    void playSoundClick();//点击按钮
    void playSoundHuMusic(int type);//胡牌音效
    
    void setBGMValue(float value);//设置音效
    void setEffectValue(float value);
    
    
    CC_SYNTHESIZE(bool, hasTingPlayer, HasTingPlayer);//是否有玩家听牌(音效相关的状态)
    
private:
    
    static Audio* m_instance;
    CC_SYNTHESIZE(bool, isFirstDong, IsFirstDong);
    CC_SYNTHESIZE(int, bgmId, BgmId);
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

};
#endif
