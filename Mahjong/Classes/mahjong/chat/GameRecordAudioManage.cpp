//
//  GameAudioManage.cpp
//  Mahjong
//
//   Created by tanweijiang on 2017/03/01.
//

#include "mahjong/chat/GameRecordAudioManage.h"
#include "mahjong/chat/chatAndroid/ChatAndroidMethod.h"
#include "mahjong/chat/chatIOS/CallRcordMecordios.h"
#include "mahjong/chat/chatAndroid/ChatAndroidMethod.h"
#include "http/base64/base64.h"
#include "server/NetworkManage.h"
#include "mahjong/audio/Audio.h"

GameAudioManage* GameAudioManage::_instance = NULL;

GameAudioManage* GameAudioManage::getInstance(){
    
    if (_instance == NULL){
        _instance = new GameAudioManage();
    }
    return _instance;
}

void GameAudioManage::beginRecordAudio()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    CallRcordMecordios::getInstance()->beginRecordAudio();
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID 
	ChatAndroidMethod::getInstance()->beginRecordAudio();
#endif
}

void GameAudioManage::endRecordAudio()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CallRcordMecordios::getInstance()->endRecordAudio();
    auto file = FileUtils::getInstance();
    auto path = CallRcordMecordios::getInstance()->getRecordFilepath();
    ssize_t* size = new ssize_t();
    auto data = file->getFileData(path, "r", size);
    auto enbase64 = base64_encode(data, *size);
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getPlayerChatMsgCommand(enbase64,"",true));
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	ChatAndroidMethod::getInstance()->endRecordAudio();
    //向服务端发送录音文件
//    log("record path server");
    auto file = FileUtils::getInstance();
    auto path = ChatAndroidMethod::getInstance()->getRecordFilePath();
//    log("record path = %s",path.c_str());
    ssize_t* size = new ssize_t();
    auto data = file->getFileData(path, "r", size);
    auto enbase64 = base64_encode(data, *size);
//    log("enbase64  = %s",enbase64.c_str());
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getPlayerChatMsgCommand(enbase64,"",true));
#endif
}

void GameAudioManage::deleteAudio()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    CallRcordMecordios::getInstance()->deleltefile();
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID  
	ChatAndroidMethod::getInstance()->deleteAudio();
#endif
}

void GameAudioManage::playAudio(std::string content,std::string poxiaoId)
{
    auto file = FileUtils::getInstance();
    auto debase64 = base64_decode(content);
    auto path = file->getWritablePath()+StringUtils::format("%s.aac",poxiaoId.c_str());
    file->writeStringToFile(debase64, path);
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    CallRcordMecordios::getInstance()->deleltefile();
    CallRcordMecordios::getInstance()->setCallCanPlayFilepath(path);
    CallRcordMecordios::getInstance()->playAudio();
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    Audio::getInstance()->playNormalSound(path);
#endif
}

GameAudioManage::GameAudioManage() {  
}
