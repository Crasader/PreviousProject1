
#include "mahjong/common/chat/chatIOS/CallRcordMecordios.h"
#include "mahjong/common/chat/chatIOS/AudioRecordManager.h"

CallRcordMecordios* CallRcordMecordios::_instance = NULL;

CallRcordMecordios* CallRcordMecordios::getInstance(){
    if (_instance == NULL){
        _instance = new CallRcordMecordios();
    }
    return _instance;
}

CallRcordMecordios::CallRcordMecordios(){}

/** 开始录音 */
void CallRcordMecordios::beginRecordAudio(){
    [[AudioRecordManager recordManager] beginRecordAudio];
}

/** 录音结束 */
void CallRcordMecordios::endRecordAudio(){
    [[AudioRecordManager recordManager]  endRecordAudio];
}

/** 取消录音 */
void CallRcordMecordios::cancelRecordAudio(){
    [[AudioRecordManager recordManager]  cancelRecordAudio];
    
}

/** 播放录音*/
void CallRcordMecordios::playAudio(float value){
    [[AudioRecordManager recordManager]  playAudio:value];
}

/** 删除录音*/
void CallRcordMecordios::deleltefile(){
    [[AudioRecordManager recordManager]  deleltefile];
}

/** 设置可以播放的路径*/
void CallRcordMecordios::setCallCanPlayFilepath(std::string path){
    NSString *str= [NSString stringWithCString:path.c_str() encoding:[NSString defaultCStringEncoding]];
//    NSLog(@"AudioRecordManager :: setCanPlayFilepath  === first = %@",str);
    [[AudioRecordManager recordManager]  setCanPlayFilepath:str];
}

/** 获取录音文件路径*/
std::string CallRcordMecordios::getRecordFilepath(){
    NSURL* path = [[AudioRecordManager recordManager]  getRecordFilepath];
    NSString *oldPath = [path absoluteString];
    NSLog(@"IOS Record oldPath = %@",oldPath);
    oldPath = [oldPath stringByReplacingOccurrencesOfString:@"file://" withString:@""];
    std::string newPath = std::string([oldPath UTF8String]);
    log("IOS Record newPath = %s",newPath.c_str());
    return newPath;
}

