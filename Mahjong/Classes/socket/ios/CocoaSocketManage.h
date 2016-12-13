//
//  CocoaSocketManage.hpp
//  Mahjong
//
//  Created by qiuzhong on 2016/12/13.
//
//

#ifndef CocoaSocketManage_hpp
#define CocoaSocketManage_hpp

class CocoaSocketManage{
public:
    static CocoaSocketManage* getInstance();
    void connectSocket();
private:
    CocoaSocketManage();
    static CocoaSocketManage* _instance;
};

#endif /* CocoaSocketManage_hpp */
