//
//  GameAudioManage.hpp
//  Mahjong
//
//  Created by tanweijiang on 2017/03/01.
//
//

#pragma once
#include "cocos2d.h"
USING_NS_CC;

class GameAudioManage{
public:
    static GameAudioManage* getInstance();

	void beginRecordAudio();

	void endRecordAudio();

	void deleteAudio();

	void playAudio();
    
    

private:
    GameAudioManage();
    static GameAudioManage* _instance;
};

