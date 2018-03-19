#include "mahjong/common/audio/Audio.h"
#include "mahjong/common/jong/Jong.h"
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
    setBgmId(-999);
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

void Audio::playMahjongSound(bool fangyan,int type,int gender){
    if(fangyan){
        playMahjongSuZhou(type, gender);
    }else{
        playMahjongNormal(type, gender);
    }
}
void Audio::playSoundPeng(bool fangyan,int gender){
    if(fangyan){
        playSoundPengSuZhou(gender);
    }else{
        playSoundPengNormal(gender);
    }
}
void Audio::playSoundGang(bool fangyan,int gender){
    if(fangyan){
        playSoundGangSuZhou(gender);
    }else{
        playSoundGangNormal(gender);
    }
}

void Audio::playSoundHu(bool fangyan,int gender){
    if(fangyan){
        playSoundHuSuZhou(gender);
    }else{
        playSoundHuNormal(gender);
    }
}

void Audio::playMahjongNormal(int type,int gender){
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
        case JongEnum::east:
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
        case JongEnum::zhong:
            playSoundZhong(gender);
            break;
        case JongEnum::fa:
            playSoundFa(gender);
            break;
        case JongEnum::bai:
            playSoundBai(gender);
            break;
        case JongEnum::mei:
            playSoundHua(gender);
            break;
        case JongEnum::lan:
            playSoundHua(gender);
            break;
        case JongEnum::zhu:
            playSoundHua(gender);
            break;
        case JongEnum::ju:
            playSoundHua(gender);
            break;
        case JongEnum::spring:
            playSoundHua(gender);
            break;
        case JongEnum::summer:
            playSoundHua(gender);
            break;
        case JongEnum::autumn:
            playSoundHua(gender);
            break;
        case JongEnum::winter:
            playSoundHua(gender);
            break;
        case JongEnum::shu:
            playSoundHua(gender);
            break;
        case JongEnum::mao:
            playSoundHua(gender);
            break;
        case JongEnum::bao:
            playSoundHua(gender);
            break;
        case JongEnum::cai:
            playSoundHua(gender);
            break;
        case JongEnum::baida:
            playSoundHua(gender);
            break;
        default:
            break;
    }
}



void Audio::playSoundWan1(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/male/1wan.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/female/1wan.mp3",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundWan2(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/male/2wan.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/female/2wan.mp3",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundWan3(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/male/3wan.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/female/3wan.mp3",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundWan4(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/male/4wan.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/female/4wan.mp3",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundWan5(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/male/5wan.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/female/5wan.mp3",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundWan6(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/male/6wan.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/female/6wan.mp3",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundWan7(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/male/7wan.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/female/7wan.mp3",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundWan8(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/male/8wan.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/female/8wan.mp3",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundWan9(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/male/9wan.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/female/9wan.mp3",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTong1(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/male/1tong.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/female/1tong.mp3",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTong2(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/male/2tong.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/female/2tong.mp3",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTong3(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/male/3tong.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/female/3tong.mp3",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTong4(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/male/4tong.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/female/4tong.mp3",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTong5(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/male/5tong.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/female/5tong.mp3",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTong6(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/male/6tong.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/female/6tong.mp3",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTong7(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/male/7tong.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/female/7tong.mp3",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTong8(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/male/8tong.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/female/8tong.mp3",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTong9(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/male/9tong.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/female/9tong.mp3",false,UserData::getInstance()->getSoundValue());
    }
}


void Audio::playSoundTiao1(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/male/1tiao.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/female/1tiao.mp3",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTiao2(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/male/2tiao.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/female/2tiao.mp3",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTiao3(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/male/3tiao.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/female/3tiao.mp3",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTiao4(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/male/4tiao.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/female/4tiao.mp3",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTiao5(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/male/5tiao.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/female/5tiao.mp3",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTiao6(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/male/6tiao.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/female/6tiao.mp3",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTiao7(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/male/7tiao.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/female/7tiao.mp3",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTiao8(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/male/8tiao.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/female/8tiao.mp3",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTiao9(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/male/9tiao.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/female/9tiao.mp3",false,UserData::getInstance()->getSoundValue());
    }
}


void Audio::playSoundEast(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/male/dong_feng.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/female/dong_feng.mp3",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundWest(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/male/xi_feng.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/female/xi_feng.mp3",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundSouth(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/male/nan_feng.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/female/nan_feng.mp3",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundNorth(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/male/bei_feng.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/female/bei_feng.mp3",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundZhong(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/male/zhong_1.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/female/zhong_1.mp3",false,UserData::getInstance()->getSoundValue());
    }
}
void Audio::playSoundFa(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/male/fa_cai.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/female/fa_cai.wav",false,UserData::getInstance()->getSoundValue());
    }
}
void Audio::playSoundBai(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/male/bai.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/female/bai.mp3",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundHua(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/male/hua.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/female/hua.mp3",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playMahjongSuZhou(int type,int gender){
    switch (type) {
        case JongEnum::wan_1:
            playSoundLocalWan1(gender);
            break;
        case JongEnum::wan_2:
            playSoundLocalWan2(gender);
            break;
        case JongEnum::wan_3:
            playSoundLocalWan3(gender);
            break;
        case JongEnum::wan_4:
            playSoundLocalWan4(gender);
            break;
        case JongEnum::wan_5:
            playSoundLocalWan5(gender);
            break;
        case JongEnum::wan_6:
            playSoundLocalWan6(gender);
            break;
        case JongEnum::wan_7:
            playSoundLocalWan7(gender);
            break;
        case JongEnum::wan_8:
            playSoundLocalWan8(gender);
            break;
        case JongEnum::wan_9:
            playSoundLocalWan9(gender);
            break;
        case JongEnum::tiao_1:
            playSoundLocalTiao1(gender);
            break;
        case JongEnum::tiao_2:
            playSoundLocalTiao2(gender);
            break;
        case JongEnum::tiao_3:
            playSoundLocalTiao3(gender);
            break;
        case JongEnum::tiao_4:
            playSoundLocalTiao4(gender);
            break;
        case JongEnum::tiao_5:
            playSoundLocalTiao5(gender);
            break;
        case JongEnum::tiao_6:
            playSoundLocalTiao6(gender);
            break;
        case JongEnum::tiao_7:
            playSoundLocalTiao7(gender);
            break;
        case JongEnum::tiao_8:
            playSoundLocalTiao8(gender);
            break;
        case JongEnum::tiao_9:
            playSoundLocalTiao9(gender);
            break;
        case JongEnum::tong_1:
            playSoundLocalTong1(gender);
            break;
        case JongEnum::tong_2:
            playSoundLocalTong2(gender);
            break;
        case JongEnum::tong_3:
            playSoundLocalTong3(gender);
            break;
        case JongEnum::tong_4:
            playSoundLocalTong4(gender);
            break;
        case JongEnum::tong_5:
            playSoundLocalTong5(gender);
            break;
        case JongEnum::tong_6:
            playSoundLocalTong6(gender);
            break;
        case JongEnum::tong_7:
            playSoundLocalTong7(gender);
            break;
        case JongEnum::tong_8:
            playSoundLocalTong8(gender);
            break;
        case JongEnum::tong_9:
            playSoundLocalTong9(gender);
            break;
        case JongEnum::east :
            playSoundLocalEast(gender);
            break;
        case JongEnum::west:
            playSoundLocalWest(gender);
            break;
        case JongEnum::south:
            playSoundLocalSouth(gender);
            break;
        case JongEnum::north:
            playSoundLocalNorth(gender);
            break;
        case JongEnum::zhong:
            playSoundLocalZhong(gender);
            break;
        case JongEnum::fa:
            playSoundLocalFa(gender);
            break;
        case JongEnum::bai:
            playSoundLocalBai(gender);
            break;
        case JongEnum::mei:
            playSoundLocalMeiHua(gender);
            break;
        case JongEnum::lan:
            playSoundLocalLanHua(gender);
            break;
        case JongEnum::zhu:
            playSoundLocalZhuHua(gender);
            break;
        case JongEnum::ju:
            playSoundLocalJuHua(gender);
            break;
        case JongEnum::spring:
            playSoundLocalCunHua(gender);
            break;
        case JongEnum::summer:
            playSoundLocalXiaHua(gender);
            break;
        case JongEnum::autumn:
            playSoundLocalQiuHua(gender);
            break;
        case JongEnum::winter:
            playSoundLocalDongHua(gender);
            break;
        case JongEnum::shu:
            playSoundLocalHua(gender);
            break;
        case JongEnum::mao:
            playSoundLocalHua(gender);
            break;
        case JongEnum::bao:
            playSoundLocalHua(gender);
            break;
        case JongEnum::cai:
            playSoundLocalHua(gender);
            break;
        case JongEnum::baida:
            playSoundLocalBaiDa(gender);
            break;
        default:
            break;
    }
}



void Audio::playSoundLocalWan1(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/localism_male/1wan_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/localism_female/1wan_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundLocalWan2(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/localism_male/2wan_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/localism_female/2wan_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
    
}

void Audio::playSoundLocalWan3(int gender){
    int soundId = rand()%3+1;
    if(gender == 1){
        std::string soundName = StringUtils::format("audio/localism_male/3wan_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/localism_female/3wan_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundLocalWan4(int gender){
    int soundId = rand()%2+1;
    if(gender == 1){
        std::string soundName = StringUtils::format("audio/localism_male/4wan_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/localism_female/4wan_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
    
}

void Audio::playSoundLocalWan5(int gender){
    int soundId = rand()%3+1;
    if(gender == 1){
        std::string soundName = StringUtils::format("audio/localism_male/5wan_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/localism_female/5wan_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
    
}

void Audio::playSoundLocalWan6(int gender){
    int soundId = rand()%2+1;
    if(gender == 1){
        std::string soundName = StringUtils::format("audio/localism_male/6wan_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/localism_female/6wan_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
    
}

void Audio::playSoundLocalWan7(int gender){
    int soundId = rand()%3+1;
    if(gender == 1){
        std::string soundName = StringUtils::format("audio/localism_male/7wan_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/localism_female/7wan_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
    
}

void Audio::playSoundLocalWan8(int gender){
    int soundId = rand()%2+1;
    if(gender == 1){
        std::string soundName = StringUtils::format("audio/localism_male/8wan_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/localism_female/8wan_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
    
}

void Audio::playSoundLocalWan9(int gender){
    int soundId = rand()%3+1;
    if(gender == 1){
        std::string soundName = StringUtils::format("audio/localism_male/9wan_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/localism_female/9wan_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}


void Audio::playSoundLocalTong1(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/localism_male/1tong_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/localism_female/1tong_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundLocalTong2(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/localism_male/2tong_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/localism_female/2tong_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundLocalTong3(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/localism_male/3tong_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/localism_female/3tong_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundLocalTong4(int gender){
    int soundId = rand()%3+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/localism_male/4tong_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/localism_female/4tong_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundLocalTong5(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/localism_male/5tong_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/localism_female/5tong_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundLocalTong6(int gender){
    int soundId = rand()%3+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/localism_male/6tong_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/localism_female/6tong_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundLocalTong7(int gender){
    int soundId = rand()%3+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/localism_male/7tong_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/localism_female/7tong_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundLocalTong8(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/localism_male/8tong_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/localism_female/8tong_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundLocalTong9(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/localism_male/9tong_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/localism_female/9tong_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}


void Audio::playSoundLocalTiao1(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/localism_male/1tiao_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/localism_female/1tiao_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
    
}

void Audio::playSoundLocalTiao2(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/localism_male/2tiao_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/localism_female/2tiao_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundLocalTiao3(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/localism_male/3tiao_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/localism_female/3tiao_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundLocalTiao4(int gender){
    int soundId = rand()%3+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/localism_male/4tiao_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/localism_female/4tiao_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundLocalTiao5(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/localism_male/5tiao_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/localism_female/5tiao_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundLocalTiao6(int gender){
    int soundId = rand()%3+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/localism_male/6tiao_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/localism_female/6tiao_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundLocalTiao7(int gender){
    int soundId = rand()%3+1;;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/localism_male/7tiao_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/localism_female/7tiao_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundLocalTiao8(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/localism_male/8tiao_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/localism_female/8tiao_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundLocalTiao9(int gender){
    int soundId = rand()%3+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/localism_male/9tiao_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/localism_female/9tiao_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}


void Audio::playSoundLocalEast(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/localism_male/dong_feng.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/localism_female/dong_feng.mp3",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundLocalWest(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/localism_male/xi_feng.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/localism_female/xi_feng.mp3",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundLocalSouth(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/localism_male/nan_feng.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/localism_female/nan_feng.mp3",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundLocalNorth(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/localism_male/bei_feng.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/localism_female/bei_feng.mp3",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundLocalCunHua(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/localism_male/chun_hua.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/localism_female/chun_hua.mp3",false,UserData::getInstance()->getSoundValue());
    }
}
void Audio::playSoundLocalXiaHua(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/localism_male/xia_hua.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/localism_female/xia_hua.mp3",false,UserData::getInstance()->getSoundValue());
    }
}
void Audio::playSoundLocalQiuHua(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/localism_male/qiu_hua.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/localism_female/qiu_hua.mp3",false,UserData::getInstance()->getSoundValue());
    }
}
void Audio::playSoundLocalDongHua(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/localism_male/dong_hua.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/localism_female/dong_hua.mp3",false,UserData::getInstance()->getSoundValue());
    }
}
void Audio::playSoundLocalMeiHua(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/localism_male/mei_hua.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/localism_female/mei_hua.mp3",false,UserData::getInstance()->getSoundValue());
    }
}
void Audio::playSoundLocalLanHua(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/localism_male/lan_hua.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/localism_female/lan_hua.mp3",false,UserData::getInstance()->getSoundValue());
    }
}
void Audio::playSoundLocalZhuHua(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/localism_male/zhu_hua.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/localism_female/zhu_hua.mp3",false,UserData::getInstance()->getSoundValue());
    }
}
void Audio::playSoundLocalJuHua(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/localism_male/ju_hua.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/flocalism_emale/ju_hua.mp3",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundLocalZhong(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/localism_male/hong_zhong.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/localism_female/hong_zhong.mp3",false,UserData::getInstance()->getSoundValue());
    }
}
void Audio::playSoundLocalFa(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/localism_male/fa_cai.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/localism_female/fa_cai.mp3",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundLocalBai(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/localism_male/bai_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/localism_female/bai_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundLocalBaiDa(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/localism_male/bai_da.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/localism_female/bai_da.mp3",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundLocalHua(int gender){
    if(gender==1){
        AudioEngine::play2d("audio/localism_male/hua.mp3",false,UserData::getInstance()->getSoundValue());
    }else{
        AudioEngine::play2d("audio/localism_female/hua.mp3",false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundPengSuZhou(int gender){
    if(gender==1){
        int soundId = rand()%3+1;
        std::string soundName = StringUtils::format("audio/localism_male/peng_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        int soundId = 1;
        std::string soundName = StringUtils::format("audio/localism_female/peng_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundPengNormal(int gender){
    int soundId = rand()%2+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/male/peng_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/female/peng_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundGangSuZhou(int gender){
    int soundId = rand()%4+1;
    if(gender==1){
        std::string soundName = StringUtils::format("audio/localism_male/gang_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        std::string soundName = StringUtils::format("audio/localism_female/gang_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundGangNormal(int gender){
    if(gender==1){
        int soundId = rand()%2+1;
        std::string soundName = StringUtils::format("audio/male/gang_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        int soundId = rand()%3+1;
        std::string soundName = StringUtils::format("audio/female/gang_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}


void Audio::playSoundHuSuZhou(int gender){
    if(gender==1){
        int soundId = 1;
        std::string soundName = StringUtils::format("audio/localism_male/hu_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        int soundId = 1;
        std::string soundName = StringUtils::format("audio/localism_female/hu_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}
void Audio::playSoundHuNormal(int gender){
    if(gender==1){
        int soundId = rand()%3+1;
        std::string soundName = StringUtils::format("audio/male/hu_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }else{
        int soundId = rand()%3+1;
        std::string soundName = StringUtils::format("audio/female/hu_%d.mp3",soundId);
        AudioEngine::play2d(soundName.c_str(),false,UserData::getInstance()->getSoundValue());
    }
}

void Audio::playSoundTouzi(){
    AudioEngine::play2d("audio/dice.mp3",false,UserData::getInstance()->getSoundValue());
}

void Audio::playSoundClick(){
    
}

void Audio::playSoundDaoJiShi(){
    AudioEngine::play2d("audio/timeup.mp3",false,UserData::getInstance()->getSoundValue());
}

void Audio::playSoundClosePage(){
    
}

void Audio::playSoundQuickChat(bool fangyan,int gender,int chatId){
    if(fangyan){
        if(gender==1){
            if(chatId == 1){
                AudioEngine::play2d("audio/localism_male/new_game_talk_1.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 2){
                AudioEngine::play2d("audio/localism_male/new_game_talk_2.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 3){
                AudioEngine::play2d("audio/localism_male/new_game_talk_3.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 4){
                AudioEngine::play2d("audio/localism_male/new_game_talk_4.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 5){
                AudioEngine::play2d("audio/localism_male/new_game_talk_5.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 6){
                AudioEngine::play2d("audio/localism_male/new_game_talk_6.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 7){
                AudioEngine::play2d("audio/localism_male/new_game_talk_7.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 8){
                AudioEngine::play2d("audio/localism_male/new_game_talk_8.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 9){
                AudioEngine::play2d("audio/localism_male/new_game_talk_9.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 10){
                AudioEngine::play2d("audio/localism_male/new_game_talk_10.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 11){
                AudioEngine::play2d("audio/localism_male/new_game_talk_11.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 12){
                AudioEngine::play2d("audio/localism_male/new_game_talk_12.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 13){
                AudioEngine::play2d("audio/localism_male/new_game_talk_13.mp3",false,UserData::getInstance()->getSoundValue());
            }
        }else{
            if(chatId == 1){
                AudioEngine::play2d("audio/localism_female/new_game_talk_1.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 2){
                AudioEngine::play2d("audio/localism_female/new_game_talk_2.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 3){
                AudioEngine::play2d("audio/localism_female/new_game_talk_3.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 4){
                AudioEngine::play2d("audio/localism_female/new_game_talk_4.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 5){
                AudioEngine::play2d("audio/localism_female/new_game_talk_5.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 6){
                AudioEngine::play2d("audio/localism_female/new_game_talk_6.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 7){
                AudioEngine::play2d("audio/localism_female/new_game_talk_7.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 8){
                AudioEngine::play2d("audio/localism_female/new_game_talk_8.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 9){
                AudioEngine::play2d("audio/localism_female/new_game_talk_9.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 10){
                AudioEngine::play2d("audio/localism_female/new_game_talk_10.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 11){
                AudioEngine::play2d("audio/localism_female/new_game_talk_11.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 12){
                AudioEngine::play2d("audio/localism_female/new_game_talk_12.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 13){
                AudioEngine::play2d("audio/localism_female/new_game_talk_13.mp3",false,UserData::getInstance()->getSoundValue());
            }
        }
    }else{
        if(gender==1){
            if(chatId == 1){
                AudioEngine::play2d("audio/male/new_game_talk_1.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 2){
                AudioEngine::play2d("audio/male/new_game_talk_2.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 3){
                AudioEngine::play2d("audio/male/new_game_talk_3.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 4){
                AudioEngine::play2d("audio/male/new_game_talk_4.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 5){
                AudioEngine::play2d("audio/male/new_game_talk_5.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 6){
                AudioEngine::play2d("audio/male/new_game_talk_6.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 7){
                AudioEngine::play2d("audio/male/new_game_talk_7.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 8){
                AudioEngine::play2d("audio/male/new_game_talk_8.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 9){
                AudioEngine::play2d("audio/male/new_game_talk_9.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 10){
                AudioEngine::play2d("audio/male/new_game_talk_10.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 11){
                AudioEngine::play2d("audio/male/new_game_talk_11.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 12){
                AudioEngine::play2d("audio/male/new_game_talk_12.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 13){
                AudioEngine::play2d("audio/male/new_game_talk_13.mp3",false,UserData::getInstance()->getSoundValue());
            }
        }else{
            if(chatId == 1){
                AudioEngine::play2d("audio/female/new_game_talk_1.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 2){
                AudioEngine::play2d("audio/female/new_game_talk_2.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 3){
                AudioEngine::play2d("audio/female/new_game_talk_3.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 4){
                AudioEngine::play2d("audio/female/new_game_talk_4.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 5){
                AudioEngine::play2d("audio/female/new_game_talk_5.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 6){
                AudioEngine::play2d("audio/female/new_game_talk_6.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 7){
                AudioEngine::play2d("audio/female/new_game_talk_7.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 8){
                AudioEngine::play2d("audio/female/new_game_talk_8.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 9){
                AudioEngine::play2d("audio/female/new_game_talk_9.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 10){
                AudioEngine::play2d("audio/female/new_game_talk_10.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 11){
                AudioEngine::play2d("audio/female/new_game_talk_11.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 12){
                AudioEngine::play2d("audio/female/new_game_talk_12.mp3",false,UserData::getInstance()->getSoundValue());
            }else if(chatId == 13){
                AudioEngine::play2d("audio/female/new_game_talk_13.mp3",false,UserData::getInstance()->getSoundValue());
            }
        }
    }
}







