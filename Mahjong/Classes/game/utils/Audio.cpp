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
    setEffectValue(1.0);
    setBGMValue(0.5);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BACKGORUNDMUSIC);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_MALE_1WAN);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_MALE_2WAN);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_MALE_2WAN);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_MALE_4WAN);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_MALE_5WAN);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_MALE_6WAN);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_MALE_7WAN);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_MALE_8WAN);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_MALE_9WAN);

    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_MALE_1TONG);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_MALE_2TONG);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_MALE_2TONG);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_MALE_4TONG);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_MALE_5TONG);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_MALE_6TONG);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_MALE_7TONG);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_MALE_8TONG);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_MALE_9TONG);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_MALE_1TIAO);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_MALE_2TIAO);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_MALE_2TIAO);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_MALE_4TIAO);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_MALE_5TIAO);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_MALE_6TIAO);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_MALE_7TIAO);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_MALE_8TIAO);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_MALE_9TIAO);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_MALE_DONGFENG);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_MALE_NANFENG);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_MALE_XIFENG);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_MALE_BEIFENG);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_MALE_BEIFENG);
}

void Audio::playMahjong(int type){
    switch (type) {
        case JongEnum::wan_1:
            playSound(SOUND_MALE_1WAN);
            break;
        case JongEnum::wan_2:
            playSound(SOUND_MALE_2WAN);
            break;
        case JongEnum::wan_3:
            playSound(SOUND_MALE_3WAN);
            break;
        case JongEnum::wan_4:
            playSound(SOUND_MALE_4WAN);
            break;
        case JongEnum::wan_5:
            playSound(SOUND_MALE_5WAN);
            break;
        case JongEnum::wan_6:
            playSound(SOUND_MALE_6WAN);
            break;
        case JongEnum::wan_7:
            playSound(SOUND_MALE_7WAN);
            break;
        case JongEnum::wan_8:
            playSound(SOUND_MALE_8WAN);
            break;
        case JongEnum::wan_9:
            playSound(SOUND_MALE_9WAN);
            break;
        case JongEnum::tiao_1:
            playSound(SOUND_MALE_1TIAO);
            break;
        case JongEnum::tiao_2:
            playSound(SOUND_MALE_2TIAO);
            break;
        case JongEnum::tiao_3:
            playSound(SOUND_MALE_3TIAO);
            break;
        case JongEnum::tiao_4:
            playSound(SOUND_MALE_4TIAO);
            break;
        case JongEnum::tiao_5:
            playSound(SOUND_MALE_5TIAO);
            break;
        case JongEnum::tiao_6:
            playSound(SOUND_MALE_6TIAO);
            break;
        case JongEnum::tiao_7:
            playSound(SOUND_MALE_7TIAO);
            break;
        case JongEnum::tiao_8:
            playSound(SOUND_MALE_8TIAO);
            break;
        case JongEnum::tiao_9:
            playSound(SOUND_MALE_9TIAO);
            break;
        case JongEnum::tong_1:
            playSound(SOUND_MALE_1TONG);
            break;
        case JongEnum::tong_2:
            playSound(SOUND_MALE_2TONG);
            break;
        case JongEnum::tong_3:
            playSound(SOUND_MALE_3TONG);
            break;
        case JongEnum::tong_4:
            playSound(SOUND_MALE_4TONG);
            break;
        case JongEnum::tong_5:
            playSound(SOUND_MALE_5TONG);
            break;
        case JongEnum::tong_6:
            playSound(SOUND_MALE_6TONG);
            break;
        case JongEnum::tong_7:
            playSound(SOUND_MALE_7TONG);
            break;
        case JongEnum::tong_8:
            playSound(SOUND_MALE_8TONG);
            break;
        case JongEnum::tong_9:
            playSound(SOUND_MALE_9TONG);
            break;
        case JongEnum::east :
            playSound(SOUND_MALE_DONGFENG);
            break;
        case JongEnum::west:
            playSound(SOUND_MALE_XIFENG);
            break;
        case JongEnum::south:
            playSound(SOUND_MALE_NANFENG);
            break;
        case JongEnum::north:
            playSound(SOUND_MALE_BEIFENG);
            break;
        default:
            break;
    }
}

void Audio::playSoundChi(){
    int ran = rand()%5;
    switch (ran) {
        case 0:
            playSound(SOUND_MALE_CHI_1);
            break;
        case 1:
            playSound(SOUND_MALE_CHI_2);
            break;
        case 2:
            playSound(SOUND_MALE_CHI_3);
            break;
        case 3:
            playSound(SOUND_MALE_CHI_4);
            break;
        case 4:
            playSound(SOUND_MALE_CHI_5);
            break;
        default:
            playSound(SOUND_MALE_CHI_1);
            break;
    }

}

void Audio::playSoundPeng(){
    int ran = rand()%2;
    switch (ran) {
        case 0:
            playSound(SOUND_MALE_PENG_1);
            break;
        case 1:
            playSound(SOUND_MALE_PENG_2);
            break;
        default:
            playSound(SOUND_MALE_PENG_1);
            break;
    }
}

void Audio::playSoundGang(){
    playSound(SOUND_MALE_GANG);
}
