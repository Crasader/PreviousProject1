#include "game/utils/Audio.h"
#include "SimpleAudioEngine.h"
#include "userdata/UserData.h"
#include "game/mahjong/jong/Jong.h"
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
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/mahjong_bgm.wav",true);
}

void Audio::pauseBGM()
{
//    AudioEngine::pauseAll();
}



void Audio::setBGMValue(float value)
{
    UserData::getInstance()->setMusicValue(value);
//    AudioEngine::setVolume(getBgmId(), value);
}

void Audio::setEffectValue(float value)
{
    UserData::getInstance()->setSoundValue(value);
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
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/male/chi_1.wav");}
            else{
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/famale/chi_1.wav");}
            break;
        case 1:
            if(gender==1){
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/male/chi_2.wav");}
            else{
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/famale/chi_2.wav");}
            break;
        case 2:
            if(gender==1){
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/male/chi_3.wav");}
            else{
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/famale/chi_3.wav");}
            break;
        case 3:
            if(gender==1){
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/male/chi_4.wav");}
            else{
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/famale/chi_4.wav");}
            break;
        case 4:
            if(gender==1){
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/male/chi_5.wav");}
            else{
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/famale/chi_5.wav");}
            break;
        case 5:
            if(gender==1){
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/male/chi_6.wav");}
            else{
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/famale/chi_6.wav");}
            break;
        case 6:
            if(gender==1){
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/male/chi_7.wav");}
            else{
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/famale/chi_7.wav");}
            break;
        default:
            if(gender==1){
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/male/chi_1.wav");}
            else{
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/famale/chi_1.wav");}
            break;
    }
    
}

void Audio::playSoundPeng(int gender){
    int ran = rand()%2;
    switch (ran) {
        case 0:
            if(gender==1){
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/male/peng_1.wav");}
            else{
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/famale/peng_1.wav");}
            break;
        case 1:
            if(gender==1){
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/male/peng_2.wav");}
            else{
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/famale/peng_2.wav");}
            break;
        default:
            if(gender==1){
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/male/peng_1.wav");}
            else{
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/famale/peng_1.wav");}
            break;
    }
}

void Audio::playSoundGang(int gender){
    if(gender==1){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/male/gang_1.wav");
    }
    else{
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/famale/gang_1.wav");
    }
}

void Audio::playSoundHu(int type,int gender){
    if(gender==1){
        if(type ==0){
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/male/zi_mo_1.wav");
        }else if(type ==1){
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/male/gang_kai_1.wav");
        }else if(type ==2){
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/male/qiang_gang_1.wav");
        }else {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/male/hu_pai_1.wav");
        }
    }
    else{
        if(type ==0){
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/famale/zi_mo_1.wav");
        }else if(type ==1){
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/famale/gang_kai_1.wav");
        }else if(type ==2){
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/famale/qiang_gang_1.wav");
        }else {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/famale/hu_pai_1.wav");
        }
    }
}

void Audio::playSoundHuaChi(int gender){
    if(gender==1){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/male/huachi_1.wav");
    }
    else{
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/famale/huachi_1.wav");
    }
}


void Audio::playSoundTing(int gender){
    int soundId = rand()%3+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/tingpai_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = StringUtils::format("audio/famale/tingpai_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}


void Audio::playSoundSlow(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/tingpai_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = StringUtils::format("audio/famale/tingpai_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundXiaGeng(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/gengpai_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = StringUtils::format("audio/famale/gengpai_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}


void Audio::playSoundGengShang(int gender){
    int soundId = 1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/gengshang_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = StringUtils::format("audio/famale/gengshang_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundWaitChi(int gender){
    int soundId = 1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/wait_chi_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = StringUtils::format("audio/famale/wait_chi_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundWaitPeng(int gender){
    int soundId = 1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/wait_peng_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = StringUtils::format("audio/famale/wait_peng_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundChi3(int gender){
    int soundId = rand()%3+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/chi_times_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = StringUtils::format("audio/famale/chi_times_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundChong(int gender){
    
    int soundId = rand()%3+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/chongpai_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = StringUtils::format("audio/famale/chongpai_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundLiuJu(int gender){
    if(gender==1){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/male/liuju_1.wav");
    }else{
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/famale/liuju_1.wav");
    }
}


void Audio::playSoundTouzi(){
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/tou_zi.wav");
}

void Audio::playSoundFapai(){
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/snd_getdun.wav");
}

void Audio::playSoundWan1(int gender){
    int soundId = rand()%3+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/1wan_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = StringUtils::format("audio/famale/1wan_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundWan2(int gender){
    int soundId = rand()%3+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/2wan_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = StringUtils::format("audio/famale/2wan_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
    
}

void Audio::playSoundWan3(int gender){
    int soundId = rand()%3+1;
    if(gender == 1){
        std::string soundName = StringUtils::format("audio/male/3wan_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = StringUtils::format("audio/famale/3wan_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundWan4(int gender){
    int soundId = rand()%3+1;
    if(gender == 1){
        std::string soundName = StringUtils::format("audio/male/4wan_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = StringUtils::format("audio/famale/4wan_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
    
}

void Audio::playSoundWan5(int gender){
    int soundId = rand()%2+1;
    if(gender == 1){
        std::string soundName = StringUtils::format("audio/male/5wan_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = StringUtils::format("audio/famale/5wan_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
    
}

void Audio::playSoundWan6(int gender){
    int soundId = rand()%2+1;
    if(gender == 1){
        std::string soundName = StringUtils::format("audio/male/6wan_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = StringUtils::format("audio/famale/6wan_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
    
}

void Audio::playSoundWan7(int gender){
    int soundId = rand()%3+1;
    if(gender == 1){
        std::string soundName = StringUtils::format("audio/male/7wan_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = StringUtils::format("audio/famale/7wan_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
    
}

void Audio::playSoundWan8(int gender){
    int soundId = rand()%3+1;
    if(gender == 1){
        std::string soundName = StringUtils::format("audio/male/8wan_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = StringUtils::format("audio/famale/8wan_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
    
}

void Audio::playSoundWan9(int gender){
    int soundId = rand()%2+1;
    if(gender == 1){
        std::string soundName = StringUtils::format("audio/male/9wan_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = StringUtils::format("audio/famale/9wan_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}


void Audio::playSoundTong1(int gender){
    int soundId = rand()%4+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/1tong_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = StringUtils::format("audio/famale/1tong_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundTong2(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/2tong_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = StringUtils::format("audio/famale/2tong_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundTong3(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/3tong_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = StringUtils::format("audio/famale/3tong_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundTong4(int gender){
    int soundId = 1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/4tong_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = StringUtils::format("audio/famale/4tong_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundTong5(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/5tong_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = StringUtils::format("audio/famale/5tong_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundTong6(int gender){
    int soundId = 1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/6tong_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = StringUtils::format("audio/famale/6tong_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundTong7(int gender){
    int soundId = 1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/7tong_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = StringUtils::format("audio/famale/7tong_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundTong8(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/8tong_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = StringUtils::format("audio/famale/8tong_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundTong9(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/9tong_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = StringUtils::format("audio/famale/9tong_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}


void Audio::playSoundTiao1(int gender){
    int soundId = rand()%3+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/1tiao_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = StringUtils::format("audio/famale/1tiao_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
    
}

void Audio::playSoundTiao2(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/2tiao_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = StringUtils::format("audio/famale/2tiao_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundTiao3(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/3tiao_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = StringUtils::format("audio/famale/3tiao_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundTiao4(int gender){
    int soundId = 1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/4tiao_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = StringUtils::format("audio/famale/4tiao_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundTiao5(int gender){
    int soundId = 1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/5tiao_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = StringUtils::format("audio/famale/5tiao_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundTiao6(int gender){
    int soundId = 1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/6tiao_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = StringUtils::format("audio/famale/6tiao_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundTiao7(int gender){
    int soundId = 1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/7tiao_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = StringUtils::format("audio/famale/7tiao_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundTiao8(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/8tiao_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = StringUtils::format("audio/famale/8tiao_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundTiao9(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/9tiao_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = StringUtils::format("audio/famale/9tiao_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}


void Audio::playSoundEast(int gender){
    if(getIsFirstDong()){
        if(gender==1){
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/male/dongfeng_2.wav");
        }else{
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/famale/dongfeng_2.wav");
        }
        setIsFirstDong(false);
    }else{
        if(gender==1){
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/male/dongfeng_1.wav");
        }else{
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/famale/dongfeng_1.wav");
        }
    }
}

void Audio::playSoundWest(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/xifeng_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = StringUtils::format("audio/famale/xifeng_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundSouth(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/nanfeng_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = StringUtils::format("audio/famale/nanfeng_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundNorth(int gender){
    int soundId = 1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/beifeng_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }else{
        std::string soundName = StringUtils::format("audio/famale/beifeng_%d.wav",soundId);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
    }
}

void Audio::playSoundHuMusic(int type){
    if(type == 0){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/hu_pai.wav");
    }else{
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/zimo_gangkai.wav");
    }
}

void Audio::playSoundClick(){
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/dian_ji_an_niu.wav");
}

void Audio::playSoundClosePage(){
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/guan_bi_ye_mian.wav");
}

void Audio::prepare(){
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/mahjong_bgm.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/chi_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/chi_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/chi_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/chi_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/chi_3.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/chi_3.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/chi_4.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/chi_4.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/chi_5.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/chi_5.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/chi_6.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/chi_6.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/chi_7.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/chi_7.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/peng_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/peng_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/peng_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/peng_2.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/gang_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/gang_1.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/zi_mo_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/gang_kai_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/qiang_gang_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/hu_pai_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/zi_mo_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/gang_kai_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/qiang_gang_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/hu_pai_1.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/huachi_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/huachi_1.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/tingpai_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/tingpai_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/tingpai_3.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/tingpai_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/tingpai_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/tingpai_3.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/gengpai_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/gengpai_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/gengpai_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/gengpai_2.wav");
   
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/gengshang_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/gengshang_1.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/wait_chi_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/wait_chi_1.wav");

    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/wait_peng_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/wait_peng_1.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/chi_times_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/chi_times_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/chi_times_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/chi_times_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/chi_times_3.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/chi_times_3.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/chongpai_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/chongpai_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/chongpai_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/chongpai_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/chongpai_3.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/chongpai_3.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/liuju_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/liuju_1.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/tou_zi.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/snd_getdun.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/1wan_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/1wan_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/1wan_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/1wan_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/1wan_3.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/1wan_3.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/2wan_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/2wan_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/2wan_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/2wan_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/2wan_3.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/2wan_3.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/3wan_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/3wan_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/3wan_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/3wan_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/3wan_3.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/3wan_3.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/4wan_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/4wan_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/4wan_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/4wan_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/4wan_3.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/4wan_3.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/5wan_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/5wan_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/5wan_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/5wan_2.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/6wan_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/6wan_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/6wan_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/6wan_2.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/7wan_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/7wan_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/7wan_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/7wan_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/7wan_3.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/7wan_3.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/8wan_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/8wan_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/8wan_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/8wan_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/8wan_3.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/8wan_3.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/9wan_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/9wan_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/9wan_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/9wan_2.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/1tong_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/1tong_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/1tong_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/1tong_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/1tong_3.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/1tong_3.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/1tong_4.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/1tong_4.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/2tong_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/2tong_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/2tong_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/2tong_2.wav");

    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/3tong_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/3tong_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/3tong_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/3tong_2.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/4tong_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/4tong_1.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/5tong_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/5tong_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/5tong_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/5tong_2.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/6tong_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/6tong_1.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/7tong_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/7tong_1.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/8tong_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/8tong_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/8tong_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/8tong_2.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/9tong_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/9tong_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/9tong_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/9tong_2.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/1tiao_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/1tiao_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/1tiao_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/1tiao_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/1tiao_3.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/1tiao_3.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/2tiao_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/2tiao_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/2tiao_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/2tiao_2.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/3tiao_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/3tiao_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/3tiao_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/3tiao_2.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/4tiao_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/4tiao_1.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/5tiao_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/5tiao_1.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/6tiao_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/6tiao_1.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/7tiao_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/7tiao_1.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/8tiao_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/8tiao_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/8tiao_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/8tiao_2.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/9tiao_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/9tiao_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/9tiao_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/9tiao_2.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/dongfeng_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/dongfeng_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/dongfeng_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/dongfeng_2.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/xifeng_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/xifeng_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/xifeng_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/xifeng_2.wav");

    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/nanfeng_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/nanfeng_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/nanfeng_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/nanfeng_2.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/male/beifeng_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/famale/beifeng_1.wav");

    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/hu_pai.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/zimo_gangkai.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/dian_ji_an_niu.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/guan_bi_ye_mian.wav");
    
}






