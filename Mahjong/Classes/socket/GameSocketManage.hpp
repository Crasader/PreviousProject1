//
//  GameSocketManage.hpp
//  Mahjong
//
//  Created by qiuzhong on 2016/12/13.
//
//

#ifndef GameSocketManage_hpp
#define GameSocketManage_hpp

class GameSocketManage{
public:
    static GameSocketManage* getInstance();
    void socketConnect();
    void sendScoketData(std::string msg);
    std::string receiveScoketData();
private:
    GameSocketManage();
    static GameSocketManage* _instance;
};
#endif /* GameSocketManage_hpp */
