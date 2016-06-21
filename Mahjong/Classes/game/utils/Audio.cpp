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

void Audio::playBGM(){
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/mahjong_bgm.mp3",true);
    
}

void Audio::pauseBGM()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}



void Audio::setBGMValue(float value)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(value);
}

void Audio::setEffectValue(float value)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(value);
}



void Audio::playMahjong(int type){
    switch (type) {
        case JongEnum::wan_1:
            playSoundWan1();
            break;
        case JongEnum::wan_2:
            playSoundWan2();
            break;
        case JongEnum::wan_3:
            playSoundWan3();
            break;
        case JongEnum::wan_4:
            playSoundWan4();
            break;
        case JongEnum::wan_5:
            playSoundWan5();
            break;
        case JongEnum::wan_6:
            playSoundWan6();
            break;
        case JongEnum::wan_7:
            playSoundWan7();
            break;
        case JongEnum::wan_8:
            playSoundWan8();
            break;
        case JongEnum::wan_9:
            playSoundWan9();
            break;
        case JongEnum::tiao_1:
            playSoundTiao1();
            break;
        case JongEnum::tiao_2:
            playSoundTiao2();
            break;
        case JongEnum::tiao_3:
            playSoundTiao3();
            break;
        case JongEnum::tiao_4:
            playSoundTiao4();
            break;
        case JongEnum::tiao_5:
            playSoundTiao5();
            break;
        case JongEnum::tiao_6:
            playSoundTiao6();
            break;
        case JongEnum::tiao_7:
            playSoundTiao7();
            break;
        case JongEnum::tiao_8:
            playSoundTiao8();
            break;
        case JongEnum::tiao_9:
            playSoundTiao9();
            break;
        case JongEnum::tong_1:
            playSoundTong1();
            break;
        case JongEnum::tong_2:
            playSoundTong2();
            break;
        case JongEnum::tong_3:
            playSoundTong3();
            break;
        case JongEnum::tong_4:
            playSoundTong4();
            break;
        case JongEnum::tong_5:
            playSoundTong5();
            break;
        case JongEnum::tong_6:
            playSoundTong6();
            break;
        case JongEnum::tong_7:
            playSoundTong7();
            break;
        case JongEnum::tong_8:
            playSoundTong8();
            break;
        case JongEnum::tong_9:
            playSoundTong9();
            break;
        case JongEnum::east :
            playSoundEast();
            break;
        case JongEnum::west:
            playSoundWest();
            break;
        case JongEnum::south:
            playSoundSouth();
            break;
        case JongEnum::north:
            playSoundNorth();
            break;
        default:
            break;
    }
}

void Audio::playSoundChi(int type){
    int ran = rand()%5;
    switch (ran) {
        case 0:
            if(UserData::getInstance()->getGender()==0){
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/male/chi_1.ogg");}
            else{
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/female/chi_1.ogg");}
            break;
        case 1:
            if(UserData::getInstance()->getGender()==0){
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/male/chi_2.ogg");}
            else{
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/female/chi_2.ogg");}            break;
        case 2:
            if(UserData::getInstance()->getGender()==0){
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/male/chi_3.ogg");}
            else{
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/female/chi_3.ogg");}
            break;
        case 3:
            if(UserData::getInstance()->getGender()==0){
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/male/chi_4.ogg");}
            else{
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/female/chi_4.ogg");}
            break;
        case 4:
            if(UserData::getInstance()->getGender()==0){
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/male/chi_5.ogg");}
            else{
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/female/chi_5.ogg");}
            break;
        default:
            if(UserData::getInstance()->getGender()==0){
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/male/chi_1.ogg");}
            else{
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/female/chi_1.ogg");}
            break;
    }
    
}

void Audio::playSoundPeng(){
    int ran = rand()%2;
    switch (ran) {
        case 0:
            if(UserData::getInstance()->getGender()==0){
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/male/peng_1.ogg");}
            else{
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/female/peng_1.ogg");}
            break;
        case 1:
            if(UserData::getInstance()->getGender()==0){
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/male/peng_2.ogg");}
            else{
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/female/peng_2.ogg");}
            break;
        default:
            if(UserData::getInstance()->getGender()==0){
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/male/peng_1.ogg");}
            else{
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/female/peng_1.ogg");}
            break;
    }
}

void Audio::playSoundGang(){
    
    if(UserData::getInstance()->getGender()==0){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/male/gang_1.ogg");}
    else{
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/female/gang_1.ogg");}
}


void Audio::playSoundWan1(){
    int soundId = rand()%3+1;
    if(UserData::getInstance()->getGender()==0){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/1wan_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/female/1wan_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundWan2(){
    int soundId = rand()%3+1;
    if(UserData::getInstance()->getGender()==0){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/2wan_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/female/2wan_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
    
}

void Audio::playSoundWan3(){
    int soundId = rand()%3+1;
    if(UserData::getInstance()->getGender()==0){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/3wan_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/female/3wan_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
    
}

void Audio::playSoundWan4(){
    int soundId = rand()%3+1;
    if(UserData::getInstance()->getGender()==0){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/4wan_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/female/4wan_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
    
}

void Audio::playSoundWan5(){
    int soundId = rand()%3+1;
    if(UserData::getInstance()->getGender()==0){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/5wan_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/female/5wan_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
    
}

void Audio::playSoundWan6(){
    int soundId = rand()%2+1;
    if(UserData::getInstance()->getGender()==0){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/6wan_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/female/6wan_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
    
}

void Audio::playSoundWan7(){
    int soundId = rand()%3+1;
    if(UserData::getInstance()->getGender()==0){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/7wan_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/female/7wan_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
    
}

void Audio::playSoundWan8(){
    int soundId = rand()%3+1;
    if(UserData::getInstance()->getGender()==0){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/8wan_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/female/8wan_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
    
}

void Audio::playSoundWan9(){
    int soundId = rand()%2+1;
    if(UserData::getInstance()->getGender()==0){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/9wan_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/female/9wan_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}


void Audio::playSoundTong1(){
    int soundId = rand()%4+1;
    if(UserData::getInstance()->getGender()==0){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/1tong_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/female/1tong_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundTong2(){
    int soundId = rand()%2+1;
    if(UserData::getInstance()->getGender()==0){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/2tong_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/female/2tong_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundTong3(){
    int soundId = rand()%2+1;
    if(UserData::getInstance()->getGender()==0){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/3tong_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/female/3tong_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundTong4(){
    int soundId = 1;
    if(UserData::getInstance()->getGender()==0){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/4tong_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/female/4tong_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundTong5(){
    int soundId = rand()%2+1;
    if(UserData::getInstance()->getGender()==0){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/5tong_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/female/5tong_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundTong6(){
    int soundId = 1;
    if(UserData::getInstance()->getGender()==0){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/6tong_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/female/6tong_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundTong7(){
    int soundId = 1;
    if(UserData::getInstance()->getGender()==0){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/7tong_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/female/7tong_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundTong8(){
    int soundId = rand()%2+1;
    if(UserData::getInstance()->getGender()==0){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/8tong_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/female/8tong_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundTong9(){
    int soundId = rand()%2+1;
    if(UserData::getInstance()->getGender()==0){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/9tong_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/female/9tong_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}


void Audio::playSoundTiao1(){
    int soundId = rand()%3+1;
    if(UserData::getInstance()->getGender()==0){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/1tiao_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/female/1tiao_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
    
}

void Audio::playSoundTiao2(){
    int soundId = rand()%2+1;
    if(UserData::getInstance()->getGender()==0){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/2tiao_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/female/2tiao_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundTiao3(){
    int soundId = rand()%2+1;
    if(UserData::getInstance()->getGender()==0){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/3tiao_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/female/3tiao_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundTiao4(){
    int soundId = 1;
    if(UserData::getInstance()->getGender()==0){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/4tiao_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/female/4tiao_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundTiao5(){
    int soundId = 1;
    if(UserData::getInstance()->getGender()==0){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/5tiao_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/female/5tiao_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundTiao6(){
    int soundId = 1;
    if(UserData::getInstance()->getGender()==0){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/6tiao_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/female/6tiao_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundTiao7(){
    int soundId = 1;
    if(UserData::getInstance()->getGender()==0){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/7tiao_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/female/7tiao_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundTiao8(){
    int soundId = rand()%2+1;
    if(UserData::getInstance()->getGender()==0){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/8tiao_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/female/8tiao_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundTiao9(){
    int soundId = rand()%2+1;
    if(UserData::getInstance()->getGender()==0){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/9tiao_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/female/9tiao_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}


void Audio::playSoundEast(){
    int soundId = rand()%2+1;
    if(UserData::getInstance()->getGender()==0){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/dongfeng_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/female/dongfeng_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundWest(){
    int soundId = rand()%2+1;
    if(UserData::getInstance()->getGender()==0){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/xifeng_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/female/xifeng_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundNorth(){
    int soundId = rand()%2+1;
    if(UserData::getInstance()->getGender()==0){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/nanfeng_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/female/nanfeng_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundSouth(){
    int soundId = 1;
    if(UserData::getInstance()->getGender()==0){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/beifeng_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/female/beifeng_%d.ogg",soundId)->_string;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}


void Audio::prepare(){
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/mahjong_bgm.mp3");
    
    //male
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/1wan_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/1wan_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/1wan_3.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/2wan_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/2wan_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/2wan_3.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/3wan_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/3wan_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/3wan_3.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/4wan_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/4wan_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/4wan_3.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/5wan_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/5wan_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/5wan_3.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/6wan_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/6wan_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/7wan_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/7wan_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/7wan_3.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/8wan_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/9wan_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/9wan_3.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/9wan_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/9wan_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/1tiao_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/1tiao_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/1tiao_3.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/2tiao_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/2tiao_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/3tiao_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/3tiao_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/4tiao_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/5tiao_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/6tiao_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/7tiao_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/8tiao_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/8tiao_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/9tiao_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/9tiao_2.ogg");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/1tong_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/1tong_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/1tong_3.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/1tong_4.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/2tong_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/2tong_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/3tong_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/3tong_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/4tong_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/5tong_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/5tong_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/6tong_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/7tong_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/8tong_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/8tong_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/9tong_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/9tong_2.ogg");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/chi_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/chi_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/chi_3.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/chi_4.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/chi_5.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/peng_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/peng_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/gang_1.ogg");
    
    //famale
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/1wan_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/1wan_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/1wan_3.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/2wan_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/2wan_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/2wan_3.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/3wan_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/3wan_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/3wan_3.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/4wan_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/4wan_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/4wan_3.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/5wan_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/5wan_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/5wan_3.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/6wan_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/6wan_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/7wan_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/7wan_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/7wan_3.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/8wan_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/9wan_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/9wan_3.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/9wan_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/9wan_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/1tiao_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/1tiao_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/1tiao_3.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/2tiao_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/2tiao_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/3tiao_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/3tiao_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/4tiao_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/5tiao_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/6tiao_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/7tiao_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/8tiao_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/8tiao_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/9tiao_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/9tiao_2.ogg");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/1tong_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/1tong_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/1tong_3.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/1tong_4.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/2tong_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/2tong_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/3tong_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/3tong_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/4tong_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/5tong_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/5tong_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/6tong_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/7tong_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/8tong_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/8tong_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/9tong_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/9tong_2.ogg");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/chi_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/chi_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/chi_3.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/chi_4.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/chi_5.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/peng_1.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/peng_2.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/female/gang_1.ogg");
}

