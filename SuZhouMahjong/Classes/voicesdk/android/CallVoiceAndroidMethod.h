#ifndef _VOICE_CallVoiceAndroidMethod_H_
#define _VOICE_CallVoiceAndroidMethod_H_

#include "cocos2d.h"
using namespace cocos2d;

class CallVoiceAndroidMethod{
public:
	void beginRecordAudio();
	void endRecordAudio();
	void deleteAudio();
	void playAudio();
	void prepare(std::string filename);
	void release();
	void cancel();
	void play(std::string filename);
	void stop();
	void getVoiceLevel();
	void setStorageDir(std::string dir);
    bool hasAudioPermission();

	static CallVoiceAndroidMethod* getInstance();
    std::string getSdCardDir();
	const char* getJniPath();
public:
	void getNetInfo(int &netType, int &netLevel);
	int  getBatteryPersent();
private:
	std::string _jniPath;
	CallVoiceAndroidMethod();
	static CallVoiceAndroidMethod* _instance;
};
#endif
