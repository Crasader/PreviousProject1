//
//  HintDialog.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/7.
//
//

#ifndef TextHintDialog_hpp
#define TextHintDialog_hpp

#include "cocos2d.h"
USING_NS_CC;

#define CLOSE_HINT_DIALOG "close_hint_dialog"

class TextHintDialog : public Layer{
public:
    static TextHintDialog* create(std::string msg);
    bool init(std::string msg);
};
#endif /* HintDialog_hpp */
