#ifndef _AUDIO_H_
#define _AUDIO_H_
#include <string>

#define BACKGORUNDMUSIC "audio/mahjong_bgm.mp3"
#define SOUND_MALE_1WAN "audio/male/1wan.ogg"
#define SOUND_MALE_2WAN "audio/male/2wan.ogg"
#define SOUND_MALE_3WAN "audio/male/3wan.ogg"
#define SOUND_MALE_4WAN "audio/male/4wan.ogg"
#define SOUND_MALE_5WAN "audio/male/5wan.ogg"
#define SOUND_MALE_6WAN "audio/male/6wan.ogg"
#define SOUND_MALE_7WAN "audio/male/7wan.ogg"
#define SOUND_MALE_8WAN "audio/male/8wan.ogg"
#define SOUND_MALE_9WAN "audio/male/9wan.ogg"
#define SOUND_MALE_1TIAO "audio/male/1tiao.ogg"
#define SOUND_MALE_2TIAO "audio/male/2tiao.ogg"
#define SOUND_MALE_3TIAO "audio/male/3tiao.ogg"
#define SOUND_MALE_4TIAO "audio/male/4tiao.ogg"
#define SOUND_MALE_5TIAO "audio/male/5tiao.ogg"
#define SOUND_MALE_6TIAO "audio/male/6tiao.ogg"
#define SOUND_MALE_7TIAO "audio/male/7tiao.ogg"
#define SOUND_MALE_8TIAO "audio/male/8tiao.ogg"
#define SOUND_MALE_9TIAO "audio/male/9tiao.ogg"
#define SOUND_MALE_1TONG "audio/male/1tong.ogg"
#define SOUND_MALE_2TONG "audio/male/2tong.ogg"
#define SOUND_MALE_3TONG "audio/male/3tong.ogg"
#define SOUND_MALE_4TONG "audio/male/4tong.ogg"
#define SOUND_MALE_5TONG "audio/male/5tong.ogg"
#define SOUND_MALE_6TONG "audio/male/6tong.ogg"
#define SOUND_MALE_7TONG "audio/male/7tong.ogg"
#define SOUND_MALE_8TONG "audio/male/8tong.ogg"
#define SOUND_MALE_9TONG "audio/male/9tong.ogg"
#define SOUND_MALE_DONGFENG "audio/male/dongfeng.ogg"
#define SOUND_MALE_NANFENG "audio/male/xifeng.ogg"
#define SOUND_MALE_XIFENG "audio/male/nanfeng.ogg"
#define SOUND_MALE_BEIFENG "audio/male/beifeng.ogg"
#define SOUND_MALE_CHI_1 "audio/male/chi_1.ogg"
#define SOUND_MALE_CHI_2 "audio/male/chi_2.ogg"
#define SOUND_MALE_CHI_3 "audio/male/chi_3.ogg"
#define SOUND_MALE_CHI_4 "audio/male/chi_4.ogg"
#define SOUND_MALE_CHI_5 "audio/male/chi_5.ogg"
#define SOUND_MALE_PENG_1 "audio/male/peng_1.ogg"
#define SOUND_MALE_PENG_2 "audio/male/peng_2.ogg"
#define SOUND_MALE_GANG "audio/male/gang_1.ogg"

#define SOUND_FAMEL_1WAN "audio/male/1wan.ogg"
#define SOUND_FAMEL_2WAN "audio/male/2wan.ogg"
#define SOUND_FAMEL_3WAN "audio/male/3wan.ogg"
#define SOUND_FAMEL_4WAN "audio/male/4wan.ogg"
#define SOUND_FAMEL_5WAN "audio/male/5wan.ogg"
#define SOUND_FAMEL_6WAN "audio/male/6wan.ogg"
#define SOUND_FAMEL_7WAN "audio/male/7wan.ogg"
#define SOUND_FAMEL_8WAN "audio/male/8wan.ogg"
#define SOUND_FAMEL_9WAN "audio/male/9wan.ogg"
#define SOUND_FAMEL_1TIAO "audio/male/1tiao.ogg"
#define SOUND_FAMEL_2TIAO "audio/male/2tiao.ogg"
#define SOUND_FAMEL_3TIAO "audio/male/3tiao.ogg"
#define SOUND_FAMEL_4TIAO "audio/male/4tiao.ogg"
#define SOUND_FAMEL_5TIAO "audio/male/5tiao.ogg"
#define SOUND_FAMEL_6TIAO "audio/male/6tiao.ogg"
#define SOUND_FAMEL_7TIAO "audio/male/7tiao.ogg"
#define SOUND_FAMEL_8TIAO "audio/male/8tiao.ogg"
#define SOUND_FAMEL_9TIAO "audio/male/9tiao.ogg"
#define SOUND_FAMEL_1TONG "audio/male/1tong.ogg"
#define SOUND_FAMEL_2TONG "audio/male/2tong.ogg"
#define SOUND_FAMEL_3TONG "audio/male/3tong.ogg"
#define SOUND_FAMEL_4TONG "audio/male/4tong.ogg"
#define SOUND_FAMEL_5TONG "audio/male/5tong.ogg"
#define SOUND_FAMEL_6TONG "audio/male/6tong.ogg"
#define SOUND_FAMEL_7TONG "audio/male/7tong.ogg"
#define SOUND_FAMEL_8TONG "audio/male/8tong.ogg"
#define SOUND_FAMEL_9TONG "audio/male/9tong.ogg"
#define SOUND_FEMALE_DONGFENG "audio/female/dongfeng.ogg"
#define SOUND_FEMALE_NANFENG "audio/female/xifeng.ogg"
#define SOUND_FEMALE_XIFENG "audio/female/nanfeng.ogg"
#define SOUND_FEMALE_BEIFENG "audio/female/beifeng.ogg"



class Audio{
public:
	static Audio* getInstance();
    void playBGM(char* soundName);
	void pauseBGM();
    void playMahjong(int type);
    
    void playSoundChi();
    void playSoundPeng();
    void playSoundGang();
    
	void prepare();
	void setBGMValue(float value);
	void setEffectValue(float value);
private:
	static Audio* m_instance;
    void playSound(std::string soundName);
};
#endif