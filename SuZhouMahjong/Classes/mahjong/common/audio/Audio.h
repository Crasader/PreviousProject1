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
    void playMahjongSound(bool fangyan,int type,int gender);
    void playSoundPeng(bool fangyan,int gender);
    void playSoundGang(bool fangyan,int gender);
    void playSoundHu(bool fangyan,int gender);
    void playSoundTouzi();
    void playSoundClosePage();//关闭页面
    void playSoundClick();//点击按钮
    void playSoundQuickChat(bool fangyan,int gender,int chatId);//快速聊天
    void playSoundDaoJiShi();//倒计时
    void setBGMValue(float value);//设置背景音
    void setEffectValue(float value);//音效
    CC_SYNTHESIZE(int, bgmId, BgmId);
private:
    
    static Audio* m_instance;
    void playMahjongSuZhou(int type,int gender);//苏州话报牌
    void playMahjongNormal(int type,int gender);//普通话报牌
    void playSoundPengSuZhou(int gender);
    void playSoundPengNormal(int gender);
    void playSoundGangSuZhou(int gender);
    void playSoundGangNormal(int gender);
    void playSoundHuSuZhou(int gender);
    void playSoundHuNormal(int gender);
    
    //普通话
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
    void playSoundZhong(int gender);
    void playSoundFa(int gender);
    void playSoundBai(int gender);
    void playSoundHua(int gender);
    //方言
    void playSoundLocalWan1(int gender);
    void playSoundLocalWan2(int gender);
    void playSoundLocalWan3(int gender);
    void playSoundLocalWan4(int gender);
    void playSoundLocalWan5(int gender);
    void playSoundLocalWan6(int gender);
    void playSoundLocalWan7(int gender);
    void playSoundLocalWan8(int gender);
    void playSoundLocalWan9(int gender);
    
    void playSoundLocalTong1(int gender);
    void playSoundLocalTong2(int gender);
    void playSoundLocalTong3(int gender);
    void playSoundLocalTong4(int gender);
    void playSoundLocalTong5(int gender);
    void playSoundLocalTong6(int gender);
    void playSoundLocalTong7(int gender);
    void playSoundLocalTong8(int gender);
    void playSoundLocalTong9(int gender);
    
    void playSoundLocalTiao1(int gender);
    void playSoundLocalTiao2(int gender);
    void playSoundLocalTiao3(int gender);
    void playSoundLocalTiao4(int gender);
    void playSoundLocalTiao5(int gender);
    void playSoundLocalTiao6(int gender);
    void playSoundLocalTiao7(int gender);
    void playSoundLocalTiao8(int gender);
    void playSoundLocalTiao9(int gender);
    
    void playSoundLocalEast(int gender);
    void playSoundLocalWest(int gender);
    void playSoundLocalNorth(int gender);
    void playSoundLocalSouth(int gender);
    
    void playSoundLocalCunHua(int gender);
    void playSoundLocalXiaHua(int gender);
    void playSoundLocalQiuHua(int gender);
    void playSoundLocalDongHua(int gender);
    
    void playSoundLocalMeiHua(int gender);
    void playSoundLocalLanHua(int gender);
    void playSoundLocalZhuHua(int gender);
    void playSoundLocalJuHua(int gender);
    
    void playSoundLocalZhong(int gender);
    void playSoundLocalFa(int gender);
    void playSoundLocalBai(int gender);
    void playSoundLocalHua(int gender);
    void playSoundLocalBaiDa(int gender);

};
#endif
