#ifndef _AUDIO_H_
#define _AUDIO_H_
#include <string>

#define BACKGORUNDMUSIC "audio/mahjong_bgm.mp3"
#define SOUND_1WAN "audio/1wan.ogg"
#define SOUND_2WAN "audio/2wan.ogg"
#define SOUND_3WAN "audio/3wan.ogg"
#define SOUND_4WAN "audio/4wan.ogg"
#define SOUND_5WAN "audio/5wan.ogg"
#define SOUND_6WAN "audio/6wan.ogg"
#define SOUND_7WAN "audio/7wan.ogg"
#define SOUND_8WAN "audio/8wan.ogg"
#define SOUND_9WAN "audio/9wan.ogg"
#define SOUND_1TIAO "audio/1tiao.ogg"
#define SOUND_2TIAO "audio/2tiao.ogg"
#define SOUND_3TIAO "audio/3tiao.ogg"
#define SOUND_4TIAO "audio/4tiao.ogg"
#define SOUND_5TIAO "audio/5tiao.ogg"
#define SOUND_6TIAO "audio/6tiao.ogg"
#define SOUND_7TIAO "audio/7tiao.ogg"
#define SOUND_8TIAO "audio/8tiao.ogg"
#define SOUND_9TIAO "audio/9tiao.ogg"
#define SOUND_1TONG "audio/1tong.ogg"
#define SOUND_2TONG "audio/2tong.ogg"
#define SOUND_3TONG "audio/3tong.ogg"
#define SOUND_4TONG "audio/4tong.ogg"
#define SOUND_5TONG "audio/5tong.ogg"
#define SOUND_6TONG "audio/6tong.ogg"
#define SOUND_7TONG "audio/7tong.ogg"
#define SOUND_8TONG "audio/8tong.ogg"
#define SOUND_9TONG "audio/9tong.ogg"


class Audio{
public:
	static Audio* getInstance();
	void playBGM(char* soundName);
	void playSound(std::string soundName);
    void playMahjong(int type);
	void pauseBGM();
	void prepare();
	void setBGMValue(float value);
	void setEffectValue(float value);
private:
	static Audio* m_instance;
};
#endif