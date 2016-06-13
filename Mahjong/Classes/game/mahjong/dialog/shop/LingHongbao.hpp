//
//  LingHongbao.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/21.
//
//

#ifndef LingHongbao_hpp
#define LingHongbao_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class LingHongbao : public Layer{
public:
    virtual bool init();
    void onEnter() override;
    void onExit() override;
    CREATE_FUNC(LingHongbao);
private:
    EditBox* _editPwd;
    EventListenerCustom* redWalletReciveListener;
    void showLingHongbao();
    void closeView();
    void confirmHongbao();
    
};
#endif /* LingHongbao_hpp */
