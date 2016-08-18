//
//  PlayerChatManage.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/8/18.
//
//

#include "game/mahjong/chat/PlayerChatManage.hpp"

PlayerChatManage* PlayerChatManage::_instance = 0;

PlayerChatManage::PlayerChatManage(){
    this->init();
}

void PlayerChatManage::init(){
    initAllFace();
}

PlayerChatManage* PlayerChatManage::getInstance(){
    if (_instance == 0){
        _instance = new PlayerChatManage();
    }
    return _instance;
}

void PlayerChatManage::initAllFace(){
    allFaceName.clear();
    allFaceName.push_back("[face1]");
    allFaceName.push_back("[face2]");
    allFaceName.push_back("[face3]");
    allFaceName.push_back("[face4]");
    allFaceName.push_back("[face5]");
    allFaceName.push_back("[face6]");
    allFaceName.push_back("[face7]");
    allFaceName.push_back("[face8]");
    allFaceName.push_back("[face9]");
    allFaceName.push_back("[face10]");
    allFaceName.push_back("[face11]");
    allFaceName.push_back("[face12]");
    allFaceName.push_back("[face13]");
    allFaceName.push_back("[face14]");
    allFaceName.push_back("[face15]");
    allFaceName.push_back("[face16]");
    allFaceName.push_back("[face17]");
    allFaceName.push_back("[face18]");
    allFaceName.push_back("[face19]");
    allFaceName.push_back("[face20]");
    allFaceName.push_back("[face21]");
    allFaceName.push_back("[face22]");
    allFaceName.push_back("[face23]");
}

bool PlayerChatManage::isFaceImage(std::string con){
    for(auto var: PlayerChatManage::getInstance()->getAllFaceList()){
        if(con == var){
            return true;
        }
    }
    return false;
}


std::string PlayerChatManage::getFaceImageName(std::string name){
    for(int i=0; i<PlayerChatManage::getInstance()->getAllFaceList().size();i++){
        if(name == PlayerChatManage::getInstance()->getAllFaceList().at(i)){
            return StringUtils::format("chat/face_%d.png",i+1);
        }
    }
    return "chat/face_1.png";
}

std::vector<std::string> PlayerChatManage::splitContentByFace(std::string content){
    std::vector<std::string> msgs;
    
    const char* mark1 = "[";
    const char* mark2 = "]";
    int pos1 = content.find(mark1);
    int pos2 = content.find(mark2);
    std::string part1 = "";
    std::string part2 ="";
    std::string part3 = "";
    if(pos1>=0 && pos2>=0){
        part1 = content.substr(0,pos1);
        part2 = content.substr(pos1,pos2-pos1+1);
        part3 = content.substr(pos2+1,content.size()-1);
        if(part1 != "")
            msgs.push_back(part1);
        if(part2 != "")
            msgs.push_back(part2);
        if(part3 != "")
            msgs.push_back(part3);
    }else{
        msgs.push_back(content);
    }
    return msgs;
}

std::vector<std::string> PlayerChatManage::getAllFaceList(){
    return allFaceName;
}