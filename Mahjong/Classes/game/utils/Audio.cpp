#include "game/utils/Audio.h"
#include "SimpleAudioEngine.h"
#include "userdata/UserData.h"
#include "game/mahjong/jong/Jong.h"


Audio* Audio::m_instance = nullptr;

Audio* Audio::getInstance(){
	if(m_instance == nullptr){
		m_instance = new Audio();
	}
	return m_instance;
}

void Audio::playBGM(char* soundName){
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(soundName,true);

}

void Audio::pauseBGM()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void Audio::playSound(std::string soundName){
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
}

void Audio::setBGMValue(float value)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(value);
}

void Audio::setEffectValue(float value)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(value);
}

void Audio::prepare(){
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BACKGORUNDMUSIC);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_1WAN);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_2WAN);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_2WAN);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_4WAN);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_5WAN);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_6WAN);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_7WAN);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_8WAN);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_9WAN);

    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_1TONG);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_2TONG);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_2TONG);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_4TONG);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_5TONG);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_6TONG);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_7TONG);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_8TONG);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_9TONG);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_1TIAO);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_2TIAO);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_2TIAO);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_4TIAO);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_5TIAO);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_6TIAO);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_7TIAO);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_8TIAO);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_9TIAO);
}

void Audio::playMahjong(int type){
    switch (type) {
        case JongEnum::wan_1:
            playSound(SOUND_1WAN);
            break;
        case JongEnum::wan_2:
            playSound(SOUND_2WAN);
            break;
        case JongEnum::wan_3:
            playSound(SOUND_3WAN);
            break;
        case JongEnum::wan_4:
            playSound(SOUND_4WAN);
            break;
        case JongEnum::wan_5:
            playSound(SOUND_5WAN);
            break;
        case JongEnum::wan_6:
            playSound(SOUND_6WAN);
            break;
        case JongEnum::wan_7:
            playSound(SOUND_7WAN);
            break;
        case JongEnum::wan_8:
            playSound(SOUND_8WAN);
            break;
        case JongEnum::wan_9:
            playSound(SOUND_9WAN);
            break;
        case JongEnum::tiao_1:
            playSound(SOUND_1TIAO);
            break;
        case JongEnum::tiao_2:
            playSound(SOUND_2TIAO);
            break;
        case JongEnum::tiao_3:
            playSound(SOUND_3TIAO);
            break;
        case JongEnum::tiao_4:
            playSound(SOUND_4TIAO);
            break;
        case JongEnum::tiao_5:
            playSound(SOUND_5TIAO);
            break;
        case JongEnum::tiao_6:
            playSound(SOUND_6TIAO);
            break;
        case JongEnum::tiao_7:
            playSound(SOUND_7TIAO);
            break;
        case JongEnum::tiao_8:
            playSound(SOUND_8TIAO);
            break;
        case JongEnum::tiao_9:
            playSound(SOUND_9TIAO);
            break;
        case JongEnum::tong_1:
            playSound(SOUND_1TONG);
            break;
        case JongEnum::tong_2:
            playSound(SOUND_2TONG);
            break;
        case JongEnum::tong_3:
            playSound(SOUND_3TONG);
            break;
        case JongEnum::tong_4:
            playSound(SOUND_4TONG);
            break;
        case JongEnum::tong_5:
            playSound(SOUND_5TONG);
            break;
        case JongEnum::tong_6:
            playSound(SOUND_6TONG);
            break;
        case JongEnum::tong_7:
            playSound(SOUND_7TONG);
            break;
        case JongEnum::tong_8:
            playSound(SOUND_8TONG);
            break;
        case JongEnum::tong_9:
            playSound(SOUND_9TONG);
            break;
        default:
            break;
    }
}
