#include "youmi/MyIM.h"
#include "mahjong/audio/Audio.h"

YIMManager* MyIM::_instance = NULL;
MyIM* MyIM::myim = new MyIM();
#define AUDIO_PATH  String::createWithFormat((FileUtils::getInstance()->getWritablePath()+"xxx%d.wav").c_str(),MyIM::getlocationPathIndex())->getCString()


#if (CC_PLATFORM_WIN32==CC_TARGET_PLATFORM)
#define STRINGTOXCHAR(_sstr) StringToWString(_sstr).c_str()
#else
#define STRINGTOXCHAR(_sstr) _sstr

#endif


YIMManager * MyIM::Inst()
{
    
    if (NULL == _instance)
    {
        _instance = YIMManager::CreateInstance();
        MyIM::init(_instance);
    }
    return _instance;
    
}
void MyIM::init(YIMManager*psend)
{
    psend->Init(STRINGTOXCHAR(strAppKey), STRINGTOXCHAR(strSecrect), STRINGTOXCHAR(packageName));
    psend->SetLoginCallback(myim);
    psend->SetMessageCallback(myim);
    psend->SetChatRoomCallback(myim);
    psend->SetDownloadCallback(myim);
    //    psend->SetContactCallback(myim);
}

YIMErrorcode MyIM::login(std::string username, std::string password)
{
    YIMErrorcode ymErrorcode = MyIM::Inst()->Login(STRINGTOXCHAR(username.c_str()), STRINGTOXCHAR(password.c_str()), STRINGTOXCHAR(""));
    return ymErrorcode;
}
YIMErrorcode MyIM::joinRoom(std::string roomid)
{
    YIMErrorcode ymErrorcode;
    ymErrorcode = MyIM::Inst()->GetChatRoomManager()->JoinChatRoom(STRINGTOXCHAR(roomid.c_str()));
    
    return ymErrorcode;
}
YIMErrorcode MyIM::leaveRoom(std::string roomid)
{
    YIMErrorcode ymErrorcode;
    ymErrorcode = MyIM::Inst()->GetChatRoomManager()->LeaveChatRoom(STRINGTOXCHAR(roomid.c_str()));
    return ymErrorcode;
}

YIMErrorcode MyIM::Logout()
{
    YIMErrorcode ymErrorcode = MyIM::Inst()->Logout();
    return ymErrorcode;
}


YIMErrorcode MyIM::beginRecord(int roomid)
{
    XUINT64 iRequestID = 0;
    YIMErrorcode ymErrorcode = MyIM::Inst()->GetMessageManager()->SendOnlyAudioMessage(STRINGTOXCHAR(Value(roomid).asString().c_str()), ChatType_RoomChat, &iRequestID);
    return ymErrorcode;
}
YIMErrorcode MyIM::endRecord()
{
    YIMErrorcode ymErrorcode = MyIM::Inst()->GetMessageManager()->StopAudioMessage(nullptr);
    return ymErrorcode;
}
YIMErrorcode MyIM::cancelRecord()
{
    YIMErrorcode ymErrorcode = MyIM::Inst()->GetMessageManager()->CancleAudioMessage();
    return ymErrorcode;
}

void MyIM::OnLogin(YIMErrorcode errorcode, const XCHAR* userID){
    if (errorcode != YIMErrorcode_Success)
    {
        log("[YOUMILOG] OnLogin()  fail,errorcode is %d", (int)errorcode);
    }else{
        log("[YOUMILOG] OnLogin()  success");
    }
}

void MyIM::OnLogout(YIMErrorcode errorcode){
    if (errorcode != YIMErrorcode_Success)
    {
        log("[YOUMILOG] OnLogout()  fail,errorcode is %d", (int)errorcode);
    }else{
        log("[YOUMILOG] OnLogout()  success");
    }
}

void MyIM::OnJoinChatRoom(YIMErrorcode errorcode, const XCHAR* chatRoomID){
    if (errorcode != YIMErrorcode_Success)
    {
        log("[YOUMILOG] OnJoinChatRoom()  fail,errorcode is %d", (int)errorcode);
    }else{
        log("[YOUMILOG] OnJoinChatRoom()  success");
    }
}

void MyIM::OnLeaveChatRoom(YIMErrorcode errorcode, const XCHAR* chatRoomID){
    if (errorcode != YIMErrorcode_Success)
    {
        log("[YOUMILOG] OnLeaveChatRoom()  fail,errorcode is %d", (int)errorcode);
    }else{
        log("[YOUMILOG] OnLeaveChatRoom()  success");
    }
}

void MyIM::OnRecvMessage(IYIMMessage* pMessage)
{
    YIMMessageBodyType msgType = pMessage->GetMessageBody()->GetMessageType();
    if (msgType == YIMMessageBodyType::MessageBodyType_Voice)
    {
        IYIMMessageBodyAudio * pMsgVoice = (IYIMMessageBodyAudio*)pMessage->GetMessageBody();
        log("[YOUMILOG] RecvMessage text is %s ,messageid is %llu ,param is %s ,audio time is %d",
            pMsgVoice->GetText(),
            pMessage->GetMessageID(),
            pMsgVoice->GetExtraParam(),
            pMsgVoice->GetAudioTime());
        MyIM::Inst()->GetMessageManager()->DownloadFile(pMessage->GetMessageID(), STRINGTOXCHAR(AUDIO_PATH));
    }
    
}

void MyIM::OnDownload(XUINT64 messageID, YIMErrorcode errorcode, const XCHAR* savePath)
{
    log("[YOUMILOG] OnDownload ,messageid is %llu ,errorcode is %d ,savePath is %s",messageID,(int)errorcode,savePath);
    Audio::getInstance()->playNormalSound(XcharToString(savePath));
}

//IYIMMessageCallback
void MyIM::OnSendAudioMessageStatus(XUINT64 requestID, YIMErrorcode errorcode, const XCHAR* text, const XCHAR* audioPath, unsigned int audioTime)
{
    log("[YOUMILOG] MyIM::OnSendAudioMessageStatus requestID=%d,errorcode=%d,audioPath=%s,audioTime=%d", (int)requestID, (int)errorcode, XcharToString(audioPath).c_str(), audioTime);
}

int MyIM::getlocationPathIndex()
{
    UserDefault::getInstance()->setIntegerForKey("YIMINDEX", UserDefault::getInstance()->getIntegerForKey("YIMINDEX", 0) + 1);
    return UserDefault::getInstance()->getIntegerForKey("YIMINDEX", 0);
}

std::wstring  MyIM::StringToWString(std::string _str)
{
    
#if(CC_TARGET_PLATFORM==CC_PLATFORM_WIN32)
    int nLength = MultiByteToWideChar(CP_ACP, 0, _str.c_str(), -1, NULL, NULL);
    std::wstring wszStr;
    wszStr.resize(nLength);
    LPWSTR lpwszStr = new wchar_t[nLength];
    MultiByteToWideChar(CP_ACP, 0, _str.c_str(), -1, lpwszStr, nLength);
    wszStr = lpwszStr;
    return wszStr;
#else
    return std::wstring();
#endif
}
std::string MyIM::XcharToString(XCHAR* _xstr)
{
    
#if(CC_TARGET_PLATFORM==CC_PLATFORM_WIN32)
    return std::string(std::wstring(_xstr).begin(), std::wstring(_xstr).end());
#else
    return _xstr;
#endif
}
std::string MyIM::XcharToString(const XCHAR* _xstr)
{
    
#if(CC_TARGET_PLATFORM==CC_PLATFORM_WIN32)
    XCHAR* wstr;
    wcscpy(wstr, _xstr);
    return std::string(std::wstring(wstr).begin(), std::wstring(wstr).end());
#else
    return _xstr;
#endif
}
