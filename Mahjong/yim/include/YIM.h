#pragma once

#include <list>
#include <memory>
#include "YIMPlatformDefine.h"


#ifdef WIN32
    #ifdef YOUMEDLL_EXPORTS
        #define YOUMEDLL_API __declspec(dllexport)
    #else
        #define YOUMEDLL_API __declspec(dllimport)
    #endif
#else
    #define YOUMEDLL_API __attribute__ ((visibility("default")))
#endif


/************************************************************************/
/*								错误码									*/
/************************************************************************/
enum YIMErrorcode
{
	YIMErrorcode_Success = 0,
	YIMErrorcode_EngineNotInit = 1,
	YIMErrorcode_NotLogin = 2,	
	YIMErrorcode_ParamInvalid = 3,
	YIMErrorcode_TimeOut = 4,
	YIMErrorcode_StatusError = 5,
	YIMErrorcode_SDKInvalid = 6,
	YIMErrorcode_AlreadyLogin = 7,
	YIMErrorcode_ServerError = 8,
	YIMErrorcode_NetError = 9,
	YIMErrorcode_LoginSessionError = 10,
	YIMErrorcode_NotStartUp = 11,
	YIMErrorcode_FileNotExist = 12,
	YIMErrorcode_SendFileError = 13,
	YIMErrorcode_UploadFailed = 14,
	YIMErrorcode_UsernamePasswordError = 15,
	YIMErrorcode_UserStatusError = 16,
	YIMErrorcode_MessageTooLong = 17,	//消息太长
	YIMErrorcode_ReceiverTooLong = 18,	//接收方ID过长(检查房间名)
	YIMErrorcode_InvalidChatType = 19,	//无效聊天类型(私聊、聊天室)
	YIMErrorcode_InvalidReceiver = 20,	//无效用户ID
	YIMErrorcode_UnknowError = 21,
	YIMErrorcode_InvalidAppkey = 22,
	YIMErrorcode_ForbiddenSpeak = 23,
	YIMErrorcode_CreateFileFailed = 24,

	//服务器的错误码
	YIMErrorcode_ALREADYFRIENDS = 1000,
	YIMErrorcode_LoginInvalid = 1001,

    //语音部分错误码
    YIMErrorcode_PTT_Start = 2000,
    YIMErrorcode_PTT_Fail = 2001,
    YIMErrorcode_PTT_DownloadFail = 2002,
	YIMErrorcode_PTT_GetUploadTokenFail = 2003,
	YIMErrorcode_PTT_UploadFail = 2004,
    YIMErrorcode_PTT_NotSpeech = 2005,
	YIMErrorcode_PTT_DeviceStatusError = 2006,
	YIMErrorcode_PTT_IsSpeeching = 2007,
	YIMErrorcode_PTT_FileNotExist = 2008,
	YIMErrorcode_PTT_ReachMaxDuration = 2009,
	YIMErrorcode_PTT_SpeechTooShort = 2010,
	YIMErrorcode_PTT_StartAudioRecordFailed = 2011,
	YIMErrorcode_PTT_SpeechTimeout = 2012,

	YIMErrorcode_Fail = 10000
};

/************************************************************************/
/*                              服务器区域编码                          */
/************************************************************************/
enum ServerZone
{
	ServerZone_China = 0,		// 中国
	ServerZone_Singapore = 1,	// 新加坡
	ServerZone_America = 2,		// 美国
	ServerZone_HongKong = 3,	// 香港
	ServerZone_Korea = 4,		// 韩国
	ServerZone_Australia = 5,	// 澳洲
	ServerZone_Deutschland = 6,	// 德国
	ServerZone_Brazil = 7,		// 巴西
	ServerZone_India = 8,		// 印度
	ServerZone_Japan = 9,		// 日本
	ServerZone_Ireland = 10,	// 爱尔兰
};

/************************************************************************/
/*								登录 登出								*/
/************************************************************************/
class IYIMLoginCallback
{
public:
	//登录回调
	virtual void OnLogin(YIMErrorcode errorcode, const XCHAR* userID) = 0;
	//登出回调
	virtual void OnLogout(YIMErrorcode errorcode) = 0;
	//被踢下线
	virtual void OnKickOff() = 0;
};


/************************************************************************/
/*                              频道接口								*/
/************************************************************************/

class YIMChatRoomManager
{
public:
	~YIMChatRoomManager();
	//加入频道
	virtual YIMErrorcode JoinChatRoom(const XCHAR* chatRoomID) = 0;
	//离开频道
	virtual YIMErrorcode LeaveChatRoom(const XCHAR* chatRoomID) = 0;
};

//频道回调
class IYIMChatRoomCallback
{
public:
	//加入频道回调
	virtual void OnJoinChatRoom(YIMErrorcode errorcode, const XCHAR* chatRoomID) = 0;
	//离开频道回调
	virtual void OnLeaveChatRoom(YIMErrorcode errorcode, const XCHAR* chatRoomID) = 0;
};


/************************************************************************/
/*								消息接口                                */
/************************************************************************/

//聊天类型
enum YIMChatType
{
	ChatType_Unknow = 0,
	ChatType_PrivateChat = 1,	//私聊
	ChatType_RoomChat = 2,		//聊天室
	ChatType_Multi = 3,
	ChatType_GroupChat = 4		//群组
};

//文件类型
enum YIMFileType
{
	FileType_Other = 0,
	FileType_Audio = 1,
	FileType_Image = 2,
	FileType_Video = 3
};

//消息类型
enum YIMMessageBodyType
{
	MessageBodyType_Unknow = 0,
	MessageBodyType_TXT = 1,
	MessageBodyType_CustomMesssage = 2,
    MessageBodyType_Emoji = 3,
    MessageBodyType_Image = 4,
    MessageBodyType_Voice = 5,
    MessageBodyType_Video = 6,
    MessageBodyType_File = 7,
	MessageBodyType_Gift = 8
};

//所有消息的基类
class IYIMMessageBodyBase
{
public:
	virtual ~IYIMMessageBodyBase();
	//获取消息类型
	virtual YIMMessageBodyType GetMessageType() = 0;
};

//自定义消息
class IYIMMessageBodyCustom :public IYIMMessageBodyBase
{
public:
	//消息内容
	virtual std::string GetCustomMessage() = 0;
};

//文本消息
class IYIMMessageBodyText :public IYIMMessageBodyBase
{
public:
	//消息内容
	virtual const XCHAR* GetMessageContent() = 0;
};

//语音消息
class IYIMMessageBodyAudio :public IYIMMessageBodyBase
{
public:
	//语音翻译文字
    virtual const XCHAR* GetText() = 0;
	//语音大小（单位：字节）
	virtual unsigned int GetFileSize() = 0;
	//语音时长（单位：秒）
	virtual unsigned int GetAudioTime() = 0;
	//发送语音附加信息（StopAudioMessage传入，格式及如何解析由调用方自定）
	virtual const XCHAR* GetExtraParam() = 0;
	//音频路径
	virtual const XCHAR* GetLocalPath() = 0;
};

//文件消息
class IYIMMessageBodyFile :public IYIMMessageBodyBase
{
public:
	//文件大小（单位：字节）
	virtual unsigned int GetFileSize() = 0;
	//原文件名
	virtual const XCHAR* GetFileName() = 0;
	//文件扩展名
	virtual const XCHAR* GetFileExtension() = 0;
	//文件类型
	virtual YIMFileType GetFileType() = 0;
	//发送文件附加信息（SendFile传入，格式及如何解析由调用方自定）
	virtual const XCHAR* GetExtraParam() = 0;
	//文件路径
	virtual const XCHAR* GetLocalPath() = 0;
};

//礼物
class IYIMMessageGift : public IYIMMessageBodyBase
{
public:
	//礼物ID
	virtual int GetGiftID() = 0;
	//数量
	virtual unsigned int GetGiftCount() = 0;
	//主播
	virtual const XCHAR* GetAnchor() = 0;
	//附加字段
	virtual const XCHAR* GetExtraParam() = 0;
};

//完整消息
class IYIMMessage
{
public:
	virtual ~IYIMMessage();
	//消息ID
	virtual XUINT64 GetMessageID() = 0;
	//聊天类型
	virtual YIMChatType GetChatType() = 0;
	//接收者(聊天室：频道ID)
	virtual const XCHAR* GetReceiveID() = 0;
	//发送者
	virtual const XCHAR* GetSenderID() = 0;
	//消息体
	virtual IYIMMessageBodyBase* GetMessageBody() = 0;
	//发送时间（秒）
	virtual unsigned int GetCreateTime() = 0;
};

class IAudioSpeechInfo
{
public:
	//requestID(StartAudioSpeech返回)
	virtual XUINT64 GetRequestID() = 0;
	//语音翻译文字
	virtual const XCHAR* GetText() = 0;
	//语音大小（单位：字节）
	virtual unsigned int GetFileSize() = 0;
	//语音时长（单位：秒）
	virtual unsigned int GetAudioTime() = 0;
	//语音本地路径
	virtual const XCHAR* GetLocalPath() = 0;
	//语音下载路径
	virtual const XCHAR* GetDownloadURL() = 0;
};

//消息回调
class IYIMMessageCallback
{
public:
	//发送消息回调
	virtual void OnSendMessageStatus(XUINT64 requestID, YIMErrorcode errorcode) = 0;
	//发送语音消息回调
	virtual void OnSendAudioMessageStatus(XUINT64 requestID, YIMErrorcode errorcode, const XCHAR* text, const XCHAR* audioPath, unsigned int audioTime) = 0;
	//收到消息
	virtual void OnRecvMessage(IYIMMessage* message) = 0;
	//获取消息历史纪录回调
	virtual void OnQueryHistoryMessage(YIMErrorcode errorcode, const XCHAR* targetID, int remain, std::list<IYIMMessage*> messageList) = 0;
	//获取房间历史纪录回调
	virtual void OnQueryRoomHistoryMessage(YIMErrorcode errorcode, std::list<IYIMMessage*> messageList) = 0;
	//语音上传后回调
	virtual void OnStopAudioSpeechStatus(YIMErrorcode errorcode, IAudioSpeechInfo* audioSpeechInfo) = 0;

	//新消息通知（只有SetReceiveMessageSwitch设置为不自动接收消息，才会收到该回调）
	virtual void OnReceiveMessageNotify() = 0;
};

//下载回调
class IYIMDownloadCallback
{
public:
	virtual void OnDownload(XUINT64 messageID, YIMErrorcode errorcode, const XCHAR* savePath) = 0;
};

class IYIMContactCallback
{
public:
	//获取最近联系人回调
	virtual void OnGetRecentContacts(YIMErrorcode errorcode, std::list<const XCHAR*>& contactList) = 0;
	//获取用户信息回调(用户信息为JSON格式)
	virtual void OnGetUserInfo(YIMErrorcode errorcode, const XCHAR* userInfo) = 0;
};

//消息管理器
class YIMMessageManager
{
public:
    virtual ~YIMMessageManager();
	//发送文本消息
	virtual YIMErrorcode SendTextMessage(const XCHAR* receiverID, YIMChatType chatType, const XCHAR* text, XUINT64* requestID) = 0;
	//群发文本消息 receivers:接收方ID JSON数组 "["xx","xx","xx"]"
	virtual YIMErrorcode MultiSendTextMessage(const char* receivers, const XCHAR* text) = 0;
	//发送自定义消息
	virtual YIMErrorcode SendCustomMessage(const XCHAR* receiverID, YIMChatType chatType, const char* content, unsigned int size, XUINT64* requestID) = 0;
	//发送文件
	virtual YIMErrorcode SendFile(const XCHAR* receiverID, YIMChatType chatType, const XCHAR* filePath, XUINT64* requestID, const XCHAR* extraParam, YIMFileType fileType = FileType_Other) = 0;
    //发送语音消息（语音转文字）
	virtual YIMErrorcode SendAudioMessage(const XCHAR* receiverID, YIMChatType chatType, XUINT64* requestID) = 0;
	//发送语音消息（语音不转文字）
	virtual YIMErrorcode SendOnlyAudioMessage(const XCHAR* receiverID, YIMChatType chatType, XUINT64* requestID) = 0;
	//停止语音
	virtual YIMErrorcode StopAudioMessage(const XCHAR* extraParam) = 0;
	//取消语音
    virtual YIMErrorcode CancleAudioMessage() =0;
	//送礼物
	//extraParam:附加参数 格式为json {"nickname":"","server_area":"","location":"","score":"","level":"","vip_level":"","extra":""}
	virtual YIMErrorcode SendGift(const XCHAR* anchorID, const XCHAR* channel, int giftId, int giftCount, const char* extraParam, XUINT64* requestID) = 0;
	//下载语音
	virtual YIMErrorcode DownloadFile(XUINT64 messageID, const XCHAR* savePath) = 0;

	//查询消息记录(direction 查询方向 0：向前查找	1：向后查找)
	virtual YIMErrorcode QueryHistoryMessage(const XCHAR* targetID, XUINT64 startMessageID = 0, int count = 30, int direction = 0) = 0;
	/*清理消息记录
	messageID:删除指定消息
	time:删除指定时间之前的消息	*/
	virtual YIMErrorcode DeleteHistoryMessage(XUINT64 messageID = 0, XUINT64 time = 0) = 0;
	//查询房间历史消息(房间最近N条聊天记录)
	virtual YIMErrorcode QueryRoomHistoryMessageFromServer(const XCHAR* roomID) = 0;

	//开始语音（不通过游密发送该语音消息，由调用方发送，调用StopAudioSpeech完成语音及上传后会回调OnStopAudioSpeechStatus）
	virtual YIMErrorcode StartAudioSpeech(XUINT64* requestID, bool translate = true) = 0;
	//停止语音（不通过游密发送该语音消息，由调用方发送，完成语音及上传后会回调OnStopAudioSpeechStatus）
	virtual YIMErrorcode StopAudioSpeech() = 0;
	//转换AMR格式到WAV格式
	virtual YIMErrorcode ConvertAMRToWav(const XCHAR* amrFilePath, const XCHAR* wavFielPath = NULL) = 0;

	//是否自动接收消息(true:自动接收(默认)	false:不自动接收消息，有新消息达到时，SDK会发出OnReceiveMessageNotify回调，调用方需要调用GetMessage获取新消息)
	virtual void SetReceiveMessageSwitch(bool receive) = 0;
	//获取新消息（只有SetReceiveMessageSwitch设置为不自动接收消息，才需要在收到OnReceiveMessageNotify回调时调用该函数）
	virtual YIMErrorcode GetNewMessage() = 0;
};


class YOUMEDLL_API YIMManager
{
public:
	virtual ~YIMManager();

	/******************下面函数可在启动引擎和初始化之前调用******************/
	//获取SDK版本号
	static int GetSDKVersion();
	//设置服务器区域
	static void SetServerZone(ServerZone zone);
    static void SetMode(int mode);
	//设置语言缓存目录
	static void SetAudioCacheDir(const XCHAR* audioCacheDir);
	/************************************************************************/
    
	//创建实例
	static YIMManager* CreateInstance();
	//销毁实例
	static void DestroyInstance();
	//初始化
	virtual YIMErrorcode Init(const XCHAR* appKey, const XCHAR* appSecurity, const XCHAR* packageName) = 0;
	//反初始化
	virtual void UnInit() = 0;
    
	//设置登陆和登出回调
	virtual void SetLoginCallback(IYIMLoginCallback* pCallback) = 0;
    //设置消息回调
    virtual void SetMessageCallback(IYIMMessageCallback* pCallback) = 0;
    //设置群组回调
    virtual void SetChatRoomCallback(IYIMChatRoomCallback* pCallback) = 0;
	//设置下载回调
	virtual void SetDownloadCallback(IYIMDownloadCallback* pCallback) =0;
	//设置联系人回调
	virtual void SetContactCallback(IYIMContactCallback* pCallback) = 0;

	//获取聊天室管理器
	virtual YIMChatRoomManager* GetChatRoomManager() = 0;
	//获取消息管理器
	virtual YIMMessageManager* GetMessageManager() = 0;

	//登录
	virtual YIMErrorcode Login(const XCHAR* userID, const XCHAR* password, const XCHAR* token) = 0;
	//登出
	virtual YIMErrorcode Logout() = 0;

	//获取最近联系人(最大100条)
	virtual YIMErrorcode GetRecentContacts() = 0;
	//设置用户信息 格式为json {"nickname":"","server_area":"","location":"","level":"","vip_level":""} (以上五个必填，可以添加其他字段)
	virtual YIMErrorcode SetUserInfo(const XCHAR* userInfo) = 0;
	//查询用户信息
	virtual YIMErrorcode GetUserInfo(const XCHAR* userID) = 0;

	//关键词过滤
	static XString FilterKeyword(const XCHAR* text);

	//程序切到后台运行
	virtual void OnPause() = 0;
	//程序切到前台运行
	virtual void OnResume() = 0;
};
