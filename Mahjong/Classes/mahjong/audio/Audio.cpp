#include "mahjong/audio/Audio.h"
#include "mahjong/jong/Jong.h"
#include "audio/include/AudioEngine.h"
#include "userdata/UserData.h"
using namespace experimental;

Audio* Audio::m_instance = nullptr;

Audio* Audio::getInstance(){
    if(m_instance == nullptr){
        m_instance = new Audio();
        m_instance->init();
    }
    return m_instance;
}

void Audio::init(){
    setIsFirstDong(true);
}

void Audio::playBGM(){
    int id = AudioEngine::play2d("audio/mahjong_bgm.mp3",true,UserData::getInstance()->getMusicValue());
    setBgmId(id);
}

void Audio::pauseBGM()
{
    AudioEngine::pauseAll();
}



void Audio::setBGMValue(float value)
{
    UserData::getInstance()->setMusicValue(value);
    AudioEngine::setVolume(getBgmId(), value);
}

void Audio::setEffectValue(float value)
{
    UserData::getInstance()->setSoundValue(value);
}

void Audio::playSoundTouzi(){
    AudioEngine::play2d("audio/tou_zi.mp3",false,UserData::getInstance()->getSoundValue());
}

void Audio::playSoundFapai(){
    AudioEngine::play2d("audio/snd_getdun.mp3",false,UserData::getInstance()->getSoundValue());
}


void Audio::playSoundHuMusic(int type){
    if(type == 0){
        AudioEngine::play2d("audio/hu_pai.mp3",false,UserData::getInstance()->getSoundValue()*0.6f);
    }else{
        AudioEngine::play2d("audio/zimo_gangkai.mp3",false,UserData::getInstance()->getSoundValue()*0.6f);
    }
}

void Audio::playSoundClick(){
    AudioEngine::play2d("audio/dian_ji_an_niu.mp3",false,UserData::getInstance()->getSoundValue());
}

void Audio::playSoundClosePage(){
    AudioEngine::play2d("audio/guan_bi_ye_mian.mp3",false,UserData::getInstance()->getSoundValue());
}

void Audio::playMahjong(int type,int gender){
    switch (type) {
        case JongEnum::wan_1:
            playSoundWan1(gender);
            break;
        case JongEnum::wan_2:
            playSoundWan2(gender);
            break;
        case JongEnum::wan_3:
            playSoundWan3(gender);
            break;
        case JongEnum::wan_4:
            playSoundWan4(gender);
            break;
        case JongEnum::wan_5:
            playSoundWan5(gender);
            break;
        case JongEnum::wan_6:
            playSoundWan6(gender);
            break;
        case JongEnum::wan_7:
            playSoundWan7(gender);
            break;
        case JongEnum::wan_8:
            playSoundWan8(gender);
            break;
        case JongEnum::wan_9:
            playSoundWan9(gender);
            break;
        case JongEnum::tiao_1:
            playSoundTiao1(gender);
            break;
        case JongEnum::tiao_2:
            playSoundTiao2(gender);
            break;
        case JongEnum::tiao_3:
            playSoundTiao3(gender);
            break;
        case JongEnum::tiao_4:
            playSoundTiao4(gender);
            break;
        case JongEnum::tiao_5:
            playSoundTiao5(gender);
            break;
        case JongEnum::tiao_6:
            playSoundTiao6(gender);
            break;
        case JongEnum::tiao_7:
            playSoundTiao7(gender);
            break;
        case JongEnum::tiao_8:
            playSoundTiao8(gender);
            break;
        case JongEnum::tiao_9:
            playSoundTiao9(gender);
            break;
        case JongEnum::tong_1:
            playSoundTong1(gender);
            break;
        case JongEnum::tong_2:
            playSoundTong2(gender);
            break;
        case JongEnum::tong_3:
            playSoundTong3(gender);
            break;
        case JongEnum::tong_4:
            playSoundTong4(gender);
            break;
        case JongEnum::tong_5:
            playSoundTong5(gender);
            break;
        case JongEnum::tong_6:
            playSoundTong6(gender);
            break;
        case JongEnum::tong_7:
            playSoundTong7(gender);
            break;
        case JongEnum::tong_8:
            playSoundTong8(gender);
            break;
        case JongEnum::tong_9:
            playSoundTong9(gender);
            break;
        case JongEnum::east :
            playSoundEast(gender);
            break;
        case JongEnum::west:
            playSoundWest(gender);
            break;
        case JongEnum::south:
            playSoundSouth(gender);
            break;
        case JongEnum::north:
            playSoundNorth(gender);
            break;
        default:
            break;
    }
}

void Audio::playSoundChi(int type,int gender){
    switch (type) {
        case 0:
            if(gender == 1){
                AudioEngine::play2d("audio/male/chi_1.wav",false,UserData::getInstance()->getSoundValue());}
            else{
                AudioEngine::play2d("audio/famale/chi_1.wav",false,UserData::getInstance()->getSoundValue());}
            break;
        case 1:
            if(gender==1){
                AudioEngine::play2d("audio/male/chi_2.wav",false,UserData::getInstance()->getSoundValue());}
            else{
                AudioEngine::play2d("audio/famale/chi_2.wav",false,UserData::getInstance()->getSoundValue());}
            break;
        case 2:
            if(gender==1){
                AudioEngine::play2d("audio/male/chi_3.wav",false,UserData::getInstance()->getSoundValue());}
            else{
                AudioEngine::play2d("audio/famale/chi_3.wav",false,UserData::getInstance()->getSoundValue());}
            break;
        case 3:
            if(gender==1){
                AudioEngine::play2d("audio/male/chi_4.wav",false,UserData::getInstance()->getSoundValue());}
            else{
                AudioEngine::play2d("audio/famale/chi_4.wav",false,UserData::getInstance()->getSoundValue());}
            break;
        case 4:
            if(gender==1){
                AudioEngine::play2d("audio/male/chi_5.wav",false,UserData::getInstance()->getSoundValue());}
            else{
                AudioEngine::play2d("audio/famale/chi_5.wav",false,UserData::getInstance()->getSoundValue());}
            break;
        case 5:
            if(gender==1){
                AudioEngine::play2d("audio/male/chi_6.wav",false,UserData::getInstance()->getSoundValue());}
            else{
                AudioEngine::play2d("audio/famale/chi_6.wav",false,UserData::getInstance()->getSoundValue());}
            break;
        case 6:
            if(gender==1){
                AudioEngine::play2d("audio/male/chi_7.wav",false,UserData::getInstance()->getSoundValue());}
            else{
                AudioEngine::play2d("audio/famale/chi_7.wav",false,UserData::getInstance()->getSoundValue());}
            break;
        default:
            if(gender==1){
                AudioEngine::play2d("audio/male/chi_1.wav",false,UserData::getInstance()->getSoundValue());}
            else{
                AudioEngine::play2d("audio/famale/chi_1.wav",false,UserData::getInstance()->getSoundValue());}
            break;
    }
    
}

void Audio::playSoundPeng(int gender){
    int ran = rand()%2;
    switch (ran) {
        case 0:
            if(gender==1){
                AudioEngine::play2d("audio/male/peng_1.wav",false,UserData::getInstance()->getSoundValue());}
            else{
                AudioEngine::play2d("audio/famale/peng_1.wav",false,UserData::getInstance()->getSoundValue());}
            break;
        case 1:
            if(gender==1){
                AudioEngine::play2d("audio/male/peng_2.wav",false,UserData::getInstance()->getSoundValue());}
            else{
                AudioEngine::play2d("audio/famale/peng_2.wav",false,UserData::getInstance()->getSoundValue());}
            break;
        default:
            if(gender==1){
                AudioEngine::play2d("audio/male/peng_1.wav",false,UserData::getInstance()->getSoundValue());}
            else{
                AudioEngine::play2d("audio/famale/peng_1.wav",false,UserData::getInstance()->getSoundValue());}
            break;
    }
}

void Audio::playSoundGang(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/male/gang_1.wav",false,UserData::getInstance()->getSoundValue());
    }
    else{
        AudioEngine::play2d("audio/famale/gang_1.wav",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundHu(int type,int gender){
    if(gender==1){
        if(type ==0){
            AudioEngine::play2d("audio/male/zi_mo_1.wav",false,UserData::getInstance()->getSoundValue()*1.5);
        }else if(type ==1){
            AudioEngine::play2d("audio/male/gang_kai_1.wav",false,UserData::getInstance()->getSoundValue()*1.5);
        }else if(type ==2){
            AudioEngine::play2d("audio/male/qiang_gang_1.wav",false,UserData::getInstance()->getSoundValue()*1.5);
        }else {
            AudioEngine::play2d("audio/male/hu_pai_1.wav",false,UserData::getInstance()->getSoundValue()*1.5);
        }
    }
    else{
        if(type ==0){
            AudioEngine::play2d("audio/famale/zi_mo_1.wav",false,UserData::getInstance()->getSoundValue()*1.5);
        }else if(type ==1){
            AudioEngine::play2d("audio/famale/gang_kai_1.wav",false,UserData::getInstance()->getSoundValue()*1.5);
        }else if(type ==2){
            AudioEngine::play2d("audio/famale/qiang_gang_1.wav",false,UserData::getInstance()->getSoundValue()*1.5);
        }else {
            AudioEngine::play2d("audio/famale/hu_pai_1.wav",false,UserData::getInstance()->getSoundValue()*1.5);
        }
    }
}

void Audio::playSoundHuaChi(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/male/huachi_1.wav",false,UserData::getInstance()->getSoundValue());
    }
    else{
        AudioEngine::play2d("audio/famale/huachi_1.wav",false,UserData::getInstance()->getSoundValue());
    }
}


void Audio::playSoundTing(int gender){
    int soundId = rand()%3+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/tingpai_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/famale/tingpai_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}


void Audio::playSoundSlow(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/tingpai_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/famale/tingpai_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundXiaGeng(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/gengpai_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/famale/gengpai_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}


void Audio::playSoundGengShang(int gender){
    int soundId = 1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/gengshang_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/famale/gengshang_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundWaitChi(int gender){
    int soundId = 1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/wait_chi_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/famale/wait_chi_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundWaitPeng(int gender){
    int soundId = 1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/wait_peng_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/famale/wait_peng_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundChi3(int gender){
    int soundId = rand()%3+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/chi_times_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/famale/chi_times_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundChong(int gender){
    
    int soundId = rand()%3+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/chongpai_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/famale/chongpai_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundLiuJu(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/male/liuju_1.wav",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/famale/liuju_1.wav",false,UserData::getInstance()->getSoundValue());
    }
}




void Audio::playSoundWan1(int gender){
    int soundId = rand()%3+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/1wan_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/famale/1wan_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundWan2(int gender){
    int soundId = rand()%3+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/2wan_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/famale/2wan_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
    
}

void Audio::playSoundWan3(int gender){
    int soundId = rand()%3+1;
    if(gender == 1){
        std::string soundName = StringUtils::format("audio/male/3wan_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/famale/3wan_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundWan4(int gender){
    int soundId = rand()%3+1;
    if(gender == 1){
        std::string soundName = StringUtils::format("audio/male/4wan_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/famale/4wan_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
    
}

void Audio::playSoundWan5(int gender){
    int soundId = rand()%2+1;
    if(gender == 1){
        std::string soundName = StringUtils::format("audio/male/5wan_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/famale/5wan_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
    
}

void Audio::playSoundWan6(int gender){
    int soundId = rand()%2+1;
    if(gender == 1){
        std::string soundName = StringUtils::format("audio/male/6wan_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/famale/6wan_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
    
}

void Audio::playSoundWan7(int gender){
    int soundId = rand()%3+1;
    if(gender == 1){
        std::string soundName = StringUtils::format("audio/male/7wan_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/famale/7wan_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
    
}

void Audio::playSoundWan8(int gender){
    int soundId = rand()%3+1;
    if(gender == 1){
        std::string soundName = StringUtils::format("audio/male/8wan_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/famale/8wan_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
    
}

void Audio::playSoundWan9(int gender){
    int soundId = rand()%2+1;
    if(gender == 1){
        std::string soundName = StringUtils::format("audio/male/9wan_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/famale/9wan_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}


void Audio::playSoundTong1(int gender){
    int soundId = rand()%4+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/1tong_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/famale/1tong_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTong2(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/2tong_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/famale/2tong_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTong3(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/3tong_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/famale/3tong_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTong4(int gender){
    int soundId = 1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/4tong_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/famale/4tong_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTong5(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/5tong_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/famale/5tong_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTong6(int gender){
    int soundId = 1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/6tong_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/famale/6tong_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTong7(int gender){
    int soundId = 1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/7tong_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/famale/7tong_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTong8(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/8tong_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/famale/8tong_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTong9(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/9tong_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/famale/9tong_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}


void Audio::playSoundTiao1(int gender){
    int soundId = rand()%3+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/1tiao_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/famale/1tiao_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
    
}

void Audio::playSoundTiao2(int gender){
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/2tiao_1.wav");
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/famale/2tiao_1.wav");
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTiao3(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/3tiao_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/famale/3tiao_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTiao4(int gender){
    int soundId = 1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/4tiao_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/famale/4tiao_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTiao5(int gender){
    int soundId = 1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/5tiao_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/famale/5tiao_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTiao6(int gender){
    int soundId = 1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/6tiao_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/famale/6tiao_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTiao7(int gender){
    int soundId = 1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/7tiao_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/famale/7tiao_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTiao8(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/8tiao_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/famale/8tiao_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTiao9(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/9tiao_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/famale/9tiao_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}


void Audio::playSoundEast(int gender){
    if(getIsFirstDong()){
        if(gender==1){
            AudioEngine::play2d("audio/male/dongfeng_2.wav",false,UserData::getInstance()->getSoundValue());
        }else{
            AudioEngine::play2d("audio/famale/dongfeng_2.wav",false,UserData::getInstance()->getSoundValue());
        }
        setIsFirstDong(false);
    }else{
        if(gender==1){
            AudioEngine::play2d("audio/male/dongfeng_1.wav",false,UserData::getInstance()->getSoundValue());
        }else{
            AudioEngine::play2d("audio/famale/dongfeng_1.wav",false,UserData::getInstance()->getSoundValue());
        }
    }
}

void Audio::playSoundWest(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/xifeng_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/famale/xifeng_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundSouth(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/nanfeng_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/famale/nanfeng_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundNorth(int gender){
    int soundId = 1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/beifeng_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/famale/beifeng_%d.wav",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playNormalSound(std::string filePath){
    int id = AudioEngine::play2d(filePath.c_str(),false,UserData::getInstance()->getSoundValue());
    AudioEngine::setFinishCallback(id, [&](int id, const std::string& filePath){
        bool result = FileUtils::getInstance()->removeFile(filePath);
    });
}






