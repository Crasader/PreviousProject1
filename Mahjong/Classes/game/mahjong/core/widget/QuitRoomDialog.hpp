//
//  QuitRoomDialog.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/5/31.
//
//

#ifndef QuitRoomDialog_hpp
#define QuitRoomDialog_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class QuitRoomDialog : public Layer {
public:
    virtual bool init();
    CREATE_FUNC(QuitRoomDialog);
private:
    void showDialog();
    void contiueGame();
    void quitRoom();
};
#endif /* QuitRoomDialog_hpp */
