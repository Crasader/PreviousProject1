#include "game/utils/Audio.h"
#include "audio/include/AudioEngine.h"
#include "userdata/UserData.h"
#include "game/mahjong/jong/Jong.h"
using namespace experimental;

Audio* Audio::m_instance = nullptr;

Audio* Audio::getInstance(){
    if(m_instance == nullptr){
        m_instance = new Audio();
    }
    return m_instance;
}

void Audio::playBGM(){
    AudioEngine::play2d("audio/mahjong_bgm.mp3",true,UserData::getInstance()->getMusicValue());
}

void Audio::pauseBGM()
{
    AudioEngine::pauseAll();
}



void Audio::setBGMValue(float value)
{
    UserData::getInstance()->setMusicValue(value);
}

void Audio::setEffectValue(float value)
{
    UserData::getInstance()->setSoundValue(value);
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
    switch (type) {
        case 0:
            if(UserData::getInstance()->getGender()==1){
                AudioEngine::play2d("audio/male/chi_1.ogg",false,UserData::getInstance()->getSoundValue());}
            else{
                AudioEngine::play2d("audio/famale/chi_1.ogg",false,UserData::getInstance()->getSoundValue());}
            break;
        case 1:
            if(UserData::getInstance()->getGender()==1){
                AudioEngine::play2d("audio/male/chi_2.ogg",false,UserData::getInstance()->getSoundValue());}
            else{
                AudioEngine::play2d("audio/famale/chi_2.ogg",false,UserData::getInstance()->getSoundValue());}
            break;
        case 2:
            if(UserData::getInstance()->getGender()==1){
                AudioEngine::play2d("audio/male/chi_3.ogg",false,UserData::getInstance()->getSoundValue());}
            else{
                AudioEngine::play2d("audio/famale/chi_3.ogg",false,UserData::getInstance()->getSoundValue());}
            break;
        case 3:
            if(UserData::getInstance()->getGender()==1){
                AudioEngine::play2d("audio/male/chi_4.ogg",false,UserData::getInstance()->getSoundValue());}
            else{
                AudioEngine::play2d("audio/famale/chi_4.ogg",false,UserData::getInstance()->getSoundValue());}
            break;
        case 4:
            if(UserData::getInstance()->getGender()==1){
                AudioEngine::play2d("audio/male/chi_5.ogg",false,UserData::getInstance()->getSoundValue());}
            else{
                AudioEngine::play2d("audio/famale/chi_5.ogg",false,UserData::getInstance()->getSoundValue());}
            break;
        case 5:
            if(UserData::getInstance()->getGender()==1){
                AudioEngine::play2d("audio/male/chi_6.ogg",false,UserData::getInstance()->getSoundValue());}
            else{
                AudioEngine::play2d("audio/famale/chi_6.ogg",false,UserData::getInstance()->getSoundValue());}
            break;
        case 6:
            if(UserData::getInstance()->getGender()==1){
                AudioEngine::play2d("audio/male/chi_7.ogg",false,UserData::getInstance()->getSoundValue());}
            else{
                AudioEngine::play2d("audio/famale/chi_7.ogg",false,UserData::getInstance()->getSoundValue());}
            break;
        default:
            if(UserData::getInstance()->getGender()==1){
                AudioEngine::play2d("audio/male/chi_1.ogg",false,UserData::getInstance()->getSoundValue());}
            else{
                AudioEngine::play2d("audio/famale/chi_1.ogg",false,UserData::getInstance()->getSoundValue());}
            break;
    }
    
}

void Audio::playSoundPeng(){
    int ran = rand()%2;
    switch (ran) {
        case 0:
            if(UserData::getInstance()->getGender()==1){
                AudioEngine::play2d("audio/male/peng_1.ogg",false,UserData::getInstance()->getSoundValue());}
            else{
                AudioEngine::play2d("audio/famale/peng_1.ogg",false,UserData::getInstance()->getSoundValue());}
            break;
        case 1:
            if(UserData::getInstance()->getGender()==1){
                AudioEngine::play2d("audio/male/peng_2.ogg",false,UserData::getInstance()->getSoundValue());}
            else{
                AudioEngine::play2d("audio/famale/peng_2.ogg",false,UserData::getInstance()->getSoundValue());}
            break;
        default:
            if(UserData::getInstance()->getGender()==1){
                AudioEngine::play2d("audio/male/peng_1.ogg",false,UserData::getInstance()->getSoundValue());}
            else{
                AudioEngine::play2d("audio/famale/peng_1.ogg",false,UserData::getInstance()->getSoundValue());}
            break;
    }
}

void Audio::playSoundGang(){
    if(UserData::getInstance()->getGender()==1){
        AudioEngine::play2d("audio/male/gang_1.ogg",false,UserData::getInstance()->getSoundValue());
    }
    else{
        AudioEngine::play2d("audio/famale/gang_1.ogg",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundHua(){
//    if(UserData::getInstance()->getGender()==1){
//        AudioEngine::play2d("audio/male/gang_1.ogg",false,UserData::getInstance()->getSoundValue());
//    }
//    else{
//        AudioEngine::play2d("audio/famale/gang_1.ogg",false,UserData::getInstance()->getSoundValue());
//    }
}

void Audio::playSoundHuaChi(){
    if(UserData::getInstance()->getGender()==1){
        AudioEngine::play2d("audio/male/huachi_1.ogg",false,UserData::getInstance()->getSoundValue());
    }
    else{
        AudioEngine::play2d("audio/famale/huachi_1.ogg",false,UserData::getInstance()->getSoundValue());
    }
}


void Audio::playSoundTing(){
    int soundId = rand()%3+1;
    if(UserData::getInstance()->getGender()==1){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/tingpai_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/famale/tingpai_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}


void Audio::playSoudnSlow(){
    int soundId = rand()%2+1;
    if(UserData::getInstance()->getGender()==1){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/tingpai_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/famale/tingpai_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundWan1(){
    int soundId = rand()%3+1;
    if(UserData::getInstance()->getGender()==1){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/1wan_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/famale/1wan_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundWan2(){
    int soundId = rand()%3+1;
    if(UserData::getInstance()->getGender()==1){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/2wan_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/famale/2wan_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
    
}

void Audio::playSoundWan3(){
    int soundId = rand()%3+1;
    if(UserData::getInstance()->getGender()==1){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/3wan_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/famale/3wan_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundWan4(){
    int soundId = rand()%3+1;
    if(UserData::getInstance()->getGender()==1){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/4wan_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/famale/4wan_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
    
}

void Audio::playSoundWan5(){
    int soundId = rand()%3+1;
    if(UserData::getInstance()->getGender()==1){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/5wan_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/famale/5wan_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
    
}

void Audio::playSoundWan6(){
    int soundId = rand()%2+1;
    if(UserData::getInstance()->getGender()==1){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/6wan_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/famale/6wan_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
    
}

void Audio::playSoundWan7(){
    int soundId = rand()%3+1;
    if(UserData::getInstance()->getGender()==1){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/7wan_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/famale/7wan_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
    
}

void Audio::playSoundWan8(){
    int soundId = rand()%3+1;
    if(UserData::getInstance()->getGender()==1){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/8wan_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/famale/8wan_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
    
}

void Audio::playSoundWan9(){
    int soundId = rand()%2+1;
    if(UserData::getInstance()->getGender()==1){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/9wan_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/famale/9wan_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}


void Audio::playSoundTong1(){
    int soundId = rand()%4+1;
    if(UserData::getInstance()->getGender()==1){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/1tong_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/famale/1tong_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTong2(){
    int soundId = rand()%2+1;
    if(UserData::getInstance()->getGender()==1){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/2tong_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/famale/2tong_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTong3(){
    int soundId = rand()%2+1;
    if(UserData::getInstance()->getGender()==1){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/3tong_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/famale/3tong_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTong4(){
    int soundId = 1;
    if(UserData::getInstance()->getGender()==1){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/4tong_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/famale/4tong_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTong5(){
    int soundId = rand()%2+1;
    if(UserData::getInstance()->getGender()==1){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/5tong_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/famale/5tong_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTong6(){
    int soundId = 1;
    if(UserData::getInstance()->getGender()==1){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/6tong_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/famale/6tong_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTong7(){
    int soundId = 1;
    if(UserData::getInstance()->getGender()==1){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/7tong_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/famale/7tong_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTong8(){
    int soundId = rand()%2+1;
    if(UserData::getInstance()->getGender()==1){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/8tong_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/famale/8tong_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTong9(){
    int soundId = rand()%2+1;
    if(UserData::getInstance()->getGender()==1){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/9tong_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/famale/9tong_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}


void Audio::playSoundTiao1(){
    int soundId = rand()%3+1;
    if(UserData::getInstance()->getGender()==1){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/1tiao_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/famale/1tiao_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
    
}

void Audio::playSoundTiao2(){
    int soundId = rand()%2+1;
    if(UserData::getInstance()->getGender()==1){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/2tiao_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/famale/2tiao_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTiao3(){
    int soundId = rand()%2+1;
    if(UserData::getInstance()->getGender()==1){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/3tiao_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/famale/3tiao_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTiao4(){
    int soundId = 1;
    if(UserData::getInstance()->getGender()==1){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/4tiao_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/famale/4tiao_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTiao5(){
    int soundId = 1;
    if(UserData::getInstance()->getGender()==1){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/5tiao_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/famale/5tiao_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTiao6(){
    int soundId = 1;
    if(UserData::getInstance()->getGender()==1){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/6tiao_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/famale/6tiao_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTiao7(){
    int soundId = 1;
    if(UserData::getInstance()->getGender()==1){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/7tiao_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/famale/7tiao_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTiao8(){
    int soundId = rand()%2+1;
    if(UserData::getInstance()->getGender()==1){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/8tiao_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/famale/8tiao_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTiao9(){
    int soundId = rand()%2+1;
    if(UserData::getInstance()->getGender()==1){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/9tiao_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/famale/9tiao_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}


void Audio::playSoundEast(){
    int soundId = rand()%2+1;
    if(UserData::getInstance()->getGender()==1){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/dongfeng_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/famale/dongfeng_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundWest(){
    int soundId = rand()%2+1;
    if(UserData::getInstance()->getGender()==1){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/xifeng_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/famale/xifeng_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundSouth(){
    int soundId = rand()%2+1;
    if(UserData::getInstance()->getGender()==1){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/nanfeng_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/famale/nanfeng_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundNorth(){
    int soundId = 1;
    if(UserData::getInstance()->getGender()==1){
        std::string soundName = cocos2d::String::createWithFormat("audio/male/beifeng_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = cocos2d::String::createWithFormat("audio/famale/beifeng_%d.ogg",soundId)->_string;
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

