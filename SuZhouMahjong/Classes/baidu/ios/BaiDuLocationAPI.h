//
//  BaiDuLocationAPI.h
//  SuZhouMahjong-mobile
//

#ifndef BaiDuLocationAPI_h
#define BaiDuLocationAPI_h

class BaiDuLocationAPI{
public:
    static BaiDuLocationAPI* getInstance();
    void getPlayerLocation();
    void checkPermisionWithKey();
private:
    BaiDuLocationAPI();
    static BaiDuLocationAPI* _instance;
    void init();
};
#endif /* BaiDuLocationAPI_h */
