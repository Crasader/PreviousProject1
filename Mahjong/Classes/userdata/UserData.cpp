#include "userdata/UserData.h"

UserData* UserData::_instance = 0;

UserData::UserData(){
    this->init();
}

void UserData::init(){
    //TODO
}

UserData* UserData::getInstance(){
    if (_instance == 0){
        _instance = new UserData();
    }
    return _instance;
}


std::string UserData::getPoxiaoId(){
    return UserDefault::getInstance()->getStringForKey("user_poxiao_id", "unknow");
}

void UserData::setPoxiaoId(std::string poxiaoId){
    UserDefault::getInstance()->setStringForKey("user_poxiao_id", poxiaoId);
}

int UserData::getGold(){
    return UserDefault::getInstance()->getIntegerForKey("user_gold", 0);
}

void UserData::setGold(int gold){
    UserDefault::getInstance()->setIntegerForKey("user_gold", gold);
}


float UserData::getFangkaNum(){
    return UserDefault::getInstance()->getFloatForKey("user_fangka", 0);
}


void UserData::setFangkaNum(float num){
    UserDefault::getInstance()->setFloatForKey("user_fangka", num);
}

int UserData::getDiamond(){
    return UserDefault::getInstance()->getIntegerForKey("user_diamond", 0);
}

void UserData::setDiamond(int num){
    UserDefault::getInstance()->setIntegerForKey("user_diamond", num);
}

int UserData::getLockDiamond(){
    return UserDefault::getInstance()->getIntegerForKey("user_lock_diamond", 0);
}

void UserData::setLockDiamond(int num){
    UserDefault::getInstance()->setIntegerForKey("user_lock_diamond", num);
}


int UserData::getTicket(){
    return UserDefault::getInstance()->getIntegerForKey("user_ticket", 0);
}

void UserData::setTicket(int num){
    UserDefault::getInstance()->setIntegerForKey("user_ticket", num);
}

float UserData::getHuafeiQuan(){
    return UserDefault::getInstance()->getDoubleForKey("user_huafei_quan", 0);
}


void UserData::setHuafeiQuan(float num){
    UserDefault::getInstance()->setDoubleForKey("user_huafei_quan", num);
}

std::string UserData::getUserName(){
    return UserDefault::getInstance()->getStringForKey("user_name", "unknow");
}

void UserData::setUserName(std::string name){
    UserDefault::getInstance()->setStringForKey("user_name", name);
}

std::string UserData::getNickName(){
    return UserDefault::getInstance()->getStringForKey("user_nick_name", "unknow");
}

void UserData::setNickName(std::string name){
    UserDefault::getInstance()->setStringForKey("user_nick_name", name);
}
std::string UserData::getPassword(){
    return UserDefault::getInstance()->getStringForKey("user_password", "unknow");
}

void UserData::setPassword(std::string pwd){
    UserDefault::getInstance()->setStringForKey("user_password", pwd);
}

int UserData::getGender(){
    return UserDefault::getInstance()->getIntegerForKey("user_gender", 0);
}

void UserData::setGender(int gender){
    UserDefault::getInstance()->setIntegerForKey("user_gender", gender);
}

std::string UserData::getBoundPhone(){
    return UserDefault::getInstance()->getStringForKey("bound_phone", "unknow");
}

void UserData::setBoundPhone(std::string phone){
    UserDefault::getInstance()->setStringForKey("bound_phone", phone);
}

std::string UserData::getPicture(){
    return UserDefault::getInstance()->getStringForKey("picture", "gameview/head_image_1.png");
}

void UserData::setPicture(std::string pic){
    UserDefault::getInstance()->setStringForKey("picture", pic);
}

bool UserData::isFirstCharge(){
    return UserDefault::getInstance()->getBoolForKey("firstcharge",false);
}

void UserData::setFirstCharge(bool firstcharge){
    UserDefault::getInstance()->setBoolForKey("firstcharge", firstcharge);
}

bool UserData::isChangeName(){
    return UserDefault::getInstance()->getBoolForKey("changename", false);
}

void UserData::setChangeName(bool change){
    UserDefault::getInstance()->setBoolForKey("changename", change);
}


float UserData::getMusicValue(){
    return UserDefault::getInstance()->getFloatForKey("music_value", 50);
}

void UserData::setMusicValue(float value){
    UserDefault::getInstance()->setFloatForKey("music_value", value);
}

float UserData::getSoundValue(){
    return UserDefault::getInstance()->getFloatForKey("sound_value", 50);
}

void UserData::setSoundValue(float value){
    UserDefault::getInstance()->setFloatForKey("sound_value", value);
}


std::string UserData::getWxOpenId(){
    return UserDefault::getInstance()->getStringForKey("wchat_openid", "unknow");
}

void UserData::setWxOpenId(std::string openId){
    UserDefault::getInstance()->setStringForKey("wchat_openid", openId);
}

std::string UserData::getWxUnionid(){
    return UserDefault::getInstance()->getStringForKey("wchat_unionid", "unknow");
}
void UserData::setWxUnionid(std::string unionid){
    UserDefault::getInstance()->setStringForKey("wchat_unionid", unionid);
}

std::string UserData::getMarkId(){
    return UserDefault::getInstance()->getStringForKey("mark_id", "unknow");
}

void UserData::setMarkId(std::string markid){
    UserDefault::getInstance()->setStringForKey("mark_id", markid);
}

int UserData::getWanJiaQunVersion(){
    return UserDefault::getInstance()->getIntegerForKey("wan_jia_qun_version", 0);
}

void UserData::setWanJiaQunVersion(int ver){
    UserDefault::getInstance()->setIntegerForKey("wan_jia_qun_version", ver);
}

int UserData::getDailiQunVersion(){
    return UserDefault::getInstance()->getIntegerForKey("daili_qun_version", 0);
}

void UserData::setDailiQunVersion(int ver){
    UserDefault::getInstance()->setIntegerForKey("daili_qun_version", ver);
}

bool UserData::isWeixinPayOpen(){
    return UserDefault::getInstance()->getBoolForKey("weixin_pay_state",false);
}

void UserData::setWeixinPayOpen(bool open){
    UserDefault::getInstance()->setBoolForKey("weixin_pay_state",open);
}


bool UserData::isFangYan(){
    return UserDefault::getInstance()->getBoolForKey("sound_is_fangyan",false);
}


void UserData::setFangYan(bool open){
    UserDefault::getInstance()->setBoolForKey("sound_is_fangyan",open);
}


bool UserData::isInviteCodeBind(){
    return UserDefault::getInstance()->getBoolForKey("isInviteCodeBind",false);
}

void UserData::setInviteCodeBind(bool bind){
    UserDefault::getInstance()->setBoolForKey("isInviteCodeBind",bind);
}


bool UserData::isClickShare(){
    return UserDefault::getInstance()->getBoolForKey("isClickShare",false);
}

void UserData::setIsClickShare(bool bind){
    UserDefault::getInstance()->setBoolForKey("isClickShare",bind);
}


std::string UserData::getInvitePropMoney(){
    return UserDefault::getInstance()->getStringForKey("InvitePropMoney","48");
}

void UserData::setInvitePropMoney(std::string money){
    UserDefault::getInstance()->getStringForKey("InvitePropMoney",money);
}

std::string UserData::getInvitePropType(){
    return UserDefault::getInstance()->getStringForKey("InvitePropType","1");
}

void UserData::setInvitePropType(std::string type){
    UserDefault::getInstance()->setStringForKey("InvitePropType",type);
}

std::string UserData::getInvitePropNum(){
    return UserDefault::getInstance()->getStringForKey("InvitePropNum","0");
}

void UserData::setInvitePropNum(std::string num){
    UserDefault::getInstance()->setStringForKey("InvitePropNum",num);
}

std::string UserData::getHsman(){
    return UserDefault::getInstance()->getStringForKey("Android_Hsman","android");
}

void UserData::setHsman(std::string hsm){
    UserDefault::getInstance()->setStringForKey("Android_Hsman",hsm);
}

std::string UserData::getHstype(){
    return UserDefault::getInstance()->getStringForKey("Android_Hstype","android");
}

void UserData::setHstype(std::string hstype){
    UserDefault::getInstance()->setStringForKey("Android_Hstype",hstype);
}


std::string UserData::getImsi(){
    return UserDefault::getInstance()->getStringForKey("Android_imsi","11111111111");
}

void UserData::setImsi(std::string imsi){
    return UserDefault::getInstance()->setStringForKey("Android_imsi",imsi);
}

std::string UserData::getImei(){
    return UserDefault::getInstance()->getStringForKey("Android_Imei","11111111111");
}

void UserData::setImei(std::string imei){
    UserDefault::getInstance()->setStringForKey("Android_Imei",imei);
}

std::string UserData::getAppVer(){
    return UserDefault::getInstance()->getStringForKey("Android_AppVer","1.0.0");
}
void UserData::setAppVer(std::string ver){
    UserDefault::getInstance()->setStringForKey("Android_AppVer",ver);
}

std::string UserData::getShareTextContent(){
    return UserDefault::getInstance()->getStringForKey("share_text","");
}
void UserData::setShareTextContent(std::string num){
    UserDefault::getInstance()->setStringForKey("share_text",num);
}


std::string UserData::getShareTextContentNum(){
    return UserDefault::getInstance()->getStringForKey("share_text_num","0");
}
void UserData::setShareTextContentNum(std::string msg){
    UserDefault::getInstance()->setStringForKey("share_text_num",msg);
}

std::string UserData::getTurntableNumber(){
    return UserDefault::getInstance()->getStringForKey("share_turntable_num","0");
}
void UserData::setTurntableNumber(std::string msg){
    UserDefault::getInstance()->setStringForKey("share_turntable_num",msg);
}

std::string UserData::getGongZhongHao(){
    return UserDefault::getInstance()->getStringForKey("gong_zhong_hao","");
}
void UserData::setGongZhongHao(std::string msg){
    UserDefault::getInstance()->setStringForKey("gong_zhong_hao",msg);
}
