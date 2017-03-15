#pragma once
#include "cocos2d.h"
#include "YIM.h"
USING_NS_CC;


#define  strAppKey  "YOUME19751F8F92ECA1F248E259B7627992ED456B03BE"
#define  strSecrect  "uwok2Bp624NQ3YDHQneud/MmSGONuJILdcOujS+y/h0J9Nbh3h1/+rTtEwG9QOF8JvanCOEot/rgTSbyudnG6mCY21qU+elOsIlHDcORlWop3iD9z71rP/0st9s9nK9CEPx/ZkQx7J5Zjlo1uqsh6sYPqm/VvG8G7xzErvL5SRsBAAE="
#define  packageName ""



class MyIM : public IYIMLoginCallback, IYIMMessageCallback, IYIMChatRoomCallback, IYIMDownloadCallback{
public:

	static YIMManager* Inst();
    
    static YIMErrorcode login(std::string username, std::string password);
    static YIMErrorcode Logout();
    static YIMErrorcode joinRoom(std::string roomid);
    static YIMErrorcode leaveRoom(std::string roomid);
    
    static YIMErrorcode beginRecord(int roomid);
    static YIMErrorcode endRecord();
    static YIMErrorcode cancelRecord();
    
private:
	static void init(YIMManager* psend);
	static YIMManager* _instance;
	static MyIM* myim;
	
private:
	//IYIMDownloadCallback
	virtual void OnDownload(XUINT64 messageID, YIMErrorcode errorcode, const XCHAR* savePath);
private:
	///IYIMLoginCallback

	virtual void OnLogin(YIMErrorcode errorcode, const XCHAR* userID);

	virtual void OnLogout(YIMErrorcode errorcode);

	virtual void OnKickOff(){};
private:
	//IYIMMessageCallback

	virtual void OnSendMessageStatus(XUINT64 requestID, YIMErrorcode errorcode){};

	virtual void OnSendAudioMessageStatus(XUINT64 requestID, YIMErrorcode errorcode, const XCHAR* text, const XCHAR* audioPath, unsigned int audioTime);

	virtual void OnRecvMessage(IYIMMessage* message);

	virtual void OnQueryHistoryMessage(YIMErrorcode errorcode, const XCHAR* targetID, int remain, std::list<IYIMMessage*> messageList){};

	virtual void OnQueryRoomHistoryMessage(YIMErrorcode errorcode, std::list<IYIMMessage*> messageList){};

	virtual void OnStopAudioSpeechStatus(YIMErrorcode errorcode, IAudioSpeechInfo* audioSpeechInfo) {};

	virtual void OnReceiveMessageNotify(){};
private:
	//IYIMChatRoomCallback

	virtual void OnJoinChatRoom(YIMErrorcode errorcode, const XCHAR* chatRoomID);

	virtual void OnLeaveChatRoom(YIMErrorcode errorcode, const XCHAR* chatRoomID);
private: //utill
	static std::string XcharToString(const XCHAR* _xstr);
	static std::string XcharToString(XCHAR* _xstr);


	static std::wstring StringToWString(std::string _str);

};

