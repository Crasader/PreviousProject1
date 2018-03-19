//
//  PlayerChatManage.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/8/18.
//
//

#ifndef PlayerChatManage_hpp
#define PlayerChatManage_hpp
#include "cocos2d.h"

USING_NS_CC;

class PlayerChatManage : public Ref{
public:
    static PlayerChatManage* getInstance();
    std::vector<std::string> getAllFaceList();
    std::string getFaceImageName(std::string name);
    std::vector<std::string> splitContentByFace(std::string content);
    bool isFaceImage(std::string con);
private:
    std::vector<std::string> allFaceName;
    PlayerChatManage();
    static PlayerChatManage* _instance;
    void init();
    void initAllFace();
};
#endif /* PlayerChatManage_hpp */
