//
//  BaiDuLocationAPI.m
//  SuZhouMahjong-mobile
//
//

#import "baidu/ios/BaiDuLocationAPI.h"
#import "baidu/ios/BDApiManager.h"

BaiDuLocationAPI* BaiDuLocationAPI::_instance = 0;

BaiDuLocationAPI::BaiDuLocationAPI(){
    this->init();
}

void BaiDuLocationAPI::init(){
    [[BDApiManager sharedManager] initLocation];
    [[BDApiManager sharedManager] initBlock];
}

BaiDuLocationAPI* BaiDuLocationAPI::getInstance(){
    if (_instance == 0){
        _instance = new BaiDuLocationAPI();
    }
    return _instance;
}

void BaiDuLocationAPI::checkPermisionWithKey(){
    [[BDApiManager sharedManager] checkPermisionWithKey];
}

void BaiDuLocationAPI::getPlayerLocation(){
    [[BDApiManager sharedManager] getMapLoction];
}
