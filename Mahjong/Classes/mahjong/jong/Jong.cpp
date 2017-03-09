#include "mahjong/jong/Jong.h"


bool Jong::init(){
    if (!Node::init()){
        return false;
    }
    background = Sprite::create();
    addChild(background);
    contentSprite = Sprite::create();
    addChild(contentSprite);
    protectedIcon = Sprite::create("gameview/poker_protected.png");
    protectedIcon->setVisible(false);
    addChild(protectedIcon);
    setIsProtected(false);
    selcetedIcon = Sprite::create("gameview/poker_select.png");
    selcetedIcon->setVisible(false);
    addChild(selcetedIcon);
    tingPaiArrow  = Sprite::create("gameview/hu_jong_hint.png");
    tingPaiArrow->setVisible(false);
    addChild(tingPaiArrow);
    return true;
}

void Jong::showJong(int bType, int cType,bool show){
    background->setTexture(getBackgroundImage(bType));
    background->setScale(getBackgroundScaleByType(bType));
    setFlipByType(background, bType);
    setJongType(cType);
    //根据给定的牌的内容来显示
    if (show){
        contentSprite->setTexture(getContextImage(cType));
        contentSprite->setRotation(getRotationByType(bType));
        contentSprite->setScale(getContentScaleByType(bType));
        contentSprite->setPosition(getContentPosition(bType, background->getPosition()));
        contentSprite->setVisible(true);
        selcetedIcon->setScale(getContentScaleByType(bType));
        tingPaiArrow->setPosition(getContentPosition(bType, background->getPosition()).x,getContentPosition(bType, background->getPosition()).y+85);
    }
    else{
        contentSprite->setVisible(false);
    }
}

Rect Jong::getJongBoundingBox(){
    Rect rect;
    if (nullptr != contentSprite){
        rect.setRect(this->getPositionX() - contentSprite->getBoundingBox().size.width / 2,
                     this->getPositionY() - contentSprite->getBoundingBox().size.height / 2,
                     contentSprite->getBoundingBox().size.width,
                     contentSprite->getBoundingBox().size.height);
    }
    return rect;
}

void Jong::setJongSelectIcon(bool show){
    selcetedIcon->setVisible(show);
}

void Jong::setTingJongHint(bool show,std::string texure){
    if("" != texure){
        tingPaiArrow->setTexture(texure);
    }
    tingPaiArrow ->setVisible(show);
    if(show){
        tingPaiArrow->runAction(Repeat::create(Sequence::create(MoveTo::create(0.5f, Point(tingPaiArrow->getPositionX(),tingPaiArrow->getPositionY()+10)), MoveTo::create(0.5f, Point(tingPaiArrow->getPositionX(),tingPaiArrow->getPositionY()-10)),NULL), CC_REPEAT_FOREVER));
    }else{
        tingPaiArrow->stopAllActions();
    }
}

void Jong::showTingIcon(int bType){
    auto icon = Sprite::create("gameview/game_ting_hint.png");
    icon->setPosition(getContentPosition(bType, background->getPosition()).x,getContentPosition(bType, background->getPosition()).y);
    icon->setScale(0.98);
    icon->setRotation(getRotationByType(bType));
    addChild(icon);
}


void Jong::showBackShadow(bool show){
    protectedIcon->setVisible(show);
    setIsProtected(show);
}


float Jong::getContentScaleByType(int bType){
    if (bType == leftplayed|| bType == leftangang||bType ==leftcpgportrait||bType == leftcpglandscape||bType == leftmingpai
        || bType == oppositeplayed || bType == oppositeangang||bType ==oppositecpgportrait||bType == oppositecpglandscape
        || bType == rightplayed||bType == rightangang||bType == rightangang||bType ==rightcpgportrait||bType == rightcpglandscape||bType ==rightmingpai||bType ==oppositemingpai
        || bType == heroplayed ){
        return 0.41f;
    }
    else if (bType == herocpgportrait){
        return 0.7f;
    }
    else if (bType == herocpglandscape){
        return 0.8f;
    }
    else{
        return 1.0f;
    }
}

float Jong::getBackgroundScaleByType(int bType){
    return 1.0f;
}


void Jong::setFlipByType(Sprite* sprite, int bType){
    if (bType == righthand){
        sprite->setFlippedX(true);
    }
}

float Jong::getRotationByType(int bType){
    if (bType == leftplayed || bType == leftcpglandscape|| bType == oppositecpglandscape||bType == leftmingpai){
        return 90;
    }
    else if (bType == oppositeplayed||bType == oppositecpgportrait
             ||bType ==rightcpgportrait|bType ==oppositemingpai){
        return 180;
    }
    else if (bType == rightplayed||bType==herocpglandscape
             ||bType == rightcpglandscape||bType ==rightmingpai){
        return 270;
    }
    else{
        return 0;
    }
}


Point Jong::getContentPosition(int bType, Point bpos){
    if (bType == leftplayed){
        return Point(bpos.x, bpos.y + 5);
    }
    else if (bType == rightplayed){
        return Point(bpos.x, bpos.y + 5);
    }
    else if (bType == oppositeplayed){
        return Point(bpos.x, bpos.y + 5);
    }
    else if (bType == heroplayed){
        return Point(bpos.x, bpos.y + 5);
    }
    else if (bType == herocpgportrait){
        return Point(bpos.x, bpos.y + 15);
    }
    else if (bType == playedshow){
        return Point(bpos.x, bpos.y-10);
    }
    else if (bType == herocpglandscape){
        return Point(bpos.x, bpos.y+15);
    }
    else if (bType == leftcpglandscape){
        return Point(bpos.x, bpos.y+5);
    }else if (bType == leftcpgportrait){
        return Point(bpos.x, bpos.y+5);
    }    else if (bType == oppositecpglandscape){
        return Point(bpos.x, bpos.y+5);
    }else if (bType == oppositecpgportrait){
        return Point(bpos.x, bpos.y+5);
    }else if(bType ==rightcpgportrait){
        return Point(bpos.x, bpos.y+5);
    }else if(bType ==rightcpglandscape){
        return Point(bpos.x, bpos.y+5);
    }
    else if(bType ==leftmingpai){
        return Point(bpos.x, bpos.y+10);
    }else if (bType ==rightmingpai){
        return Point(bpos.x, bpos.y+10);
    }else if (bType ==oppositemingpai){
        return Point(bpos.x, bpos.y+10);
    }
    else {
        return Point(bpos.x, bpos.y - 10);
    }
    
}



std::string Jong::getBackgroundImage(int btype){
    std::string imageName;
    switch (btype)
    {
            //玩家自己
        case herohand:
            imageName = "jong/big_1.png";
            break;
        case herocpgportrait:
            imageName = "jong/big_2.png";
            break;
        case herocpglandscape:
            imageName = "jong/big_4.png";
            break;
        case heroplayed:
            imageName = "jong/small_2.png";
            break;
        case herodeal:
            imageName = "jong/big_3.png";
            break;
            //右边的玩家
        case righthand:
            imageName = "jong/middle_1.png";
            break;
        case rightmingpai:
            imageName = "jong/middle_4.png";
            break;
        case rightplayed:
            imageName = "jong/small_4.png";
            break;
        case rightdeal:
            imageName = "jong/middle_5.png";
            break;
        case rightangang:
            imageName= "jong/small_5.png";
            break;
        case rightcpgportrait:
            imageName= "jong/small_2.png";
            break;
        case rightcpglandscape:
            imageName="jong/small_4.png";
            break;
            //对面的玩家
        case oppositehand:
            imageName = "jong/middle_3.png";
            break;
        case oppositemingpai:
            imageName = "jong/middle_2.png";
            break;
        case oppositeplayed:
            imageName = "jong/small_2.png";
            break;
        case oppositedeal:
            imageName = "jong/middle_6.png";
            break;
        case oppositeangang:
            imageName = "jong/small_6.png";
            break;
        case oppositecpgportrait:
            imageName= "jong/small_2.png";
            break;
        case oppositecpglandscape:
            imageName="jong/small_4.png";
            break;
            //左边的玩家
        case lefthand:
            imageName = "jong/middle_1.png";
            break;
        case leftmingpai:
            imageName = "jong/middle_4.png";
            break;
        case leftplayed:
            imageName = "jong/small_4.png";
            break;
        case leftdeal:
            imageName = "jong/middle_5.png";
            break;
        case leftangang:
            imageName= "jong/small_5.png";
            break;
        case leftcpgportrait:
            imageName= "jong/small_2.png";
            break;
        case leftcpglandscape:
            imageName="jong/small_4.png";
            break;
            //大牌显示
        case playedshow:
            imageName = "jong/big_1.png";
            break;
        default:
            break;
    }
    return imageName;
}


std::string Jong::getContextImage(int cType){
    std::string imageName;
    switch (cType)
    {
        case JongEnum::wan_1:
            imageName = "jong/wan_1.png";
            break;
        case JongEnum::wan_2:
            imageName = "jong/wan_2.png";
            break;
        case JongEnum::wan_3:
            imageName = "jong/wan_3.png";
            break;
        case JongEnum::wan_4:
            imageName = "jong/wan_4.png";
            break;
        case JongEnum::wan_5:
            imageName = "jong/wan_5.png";
            break;
        case JongEnum::wan_6:
            imageName = "jong/wan_6.png";
            break;
        case JongEnum::wan_7:
            imageName = "jong/wan_7.png";
            break;
        case JongEnum::wan_8:
            imageName = "jong/wan_8.png";
            break;
        case JongEnum::wan_9:
            imageName = "jong/wan_9.png";
            break;
        case JongEnum::tong_1:
            imageName = "jong/tong_1.png";
            break;
        case JongEnum::tong_2:
            imageName = "jong/tong_2.png";
            break;
        case JongEnum::tong_3:
            imageName = "jong/tong_3.png";
            break;
        case JongEnum::tong_4:
            imageName = "jong/tong_4.png";
            break;
        case JongEnum::tong_5:
            imageName = "jong/tong_5.png";
            break;
        case JongEnum::tong_6:
            imageName = "jong/tong_6.png";
            break;
        case JongEnum::tong_7:
            imageName = "jong/tong_7.png";
            break;
        case JongEnum::tong_8:
            imageName = "jong/tong_8.png";
            break;
        case JongEnum::tong_9:
            imageName = "jong/tong_9.png";
            break;
        case JongEnum::tiao_1:
            imageName = "jong/tiao_1.png";
            break;
        case JongEnum::tiao_2:
            imageName = "jong/tiao_2.png";
            break;
        case JongEnum::tiao_3:
            imageName = "jong/tiao_3.png";
            break;
        case JongEnum::tiao_4:
            imageName = "jong/tiao_4.png";
            break;
        case JongEnum::tiao_5:
            imageName = "jong/tiao_5.png";
            break;
        case JongEnum::tiao_6:
            imageName = "jong/tiao_6.png";
            break;
        case JongEnum::tiao_7:
            imageName = "jong/tiao_7.png";
            break;
        case JongEnum::tiao_8:
            imageName = "jong/tiao_8.png";
            break;
        case JongEnum::tiao_9:
            imageName = "jong/tiao_9.png";
            break;
        case JongEnum::east:
            imageName = "jong/east.png";
            break;
        case JongEnum::south:
            imageName = "jong/south.png";
            break;
        case JongEnum::west:
            imageName = "jong/west.png";
            break;
        case JongEnum::north:
            imageName = "jong/north.png";
            break;
        case JongEnum::zhong:
            imageName = "jong/zhong.png";
            break;
        case JongEnum::fa:
            imageName = "jong/fa.png";
            break;
        case JongEnum::bai:
            imageName = "jong/bai.png";
            break;
        case JongEnum::spring:
            imageName = "jong/spring.png";
            break;
        case JongEnum::summer:
            imageName = "jong/summer.png";
            break;
        case JongEnum::autumn:
            imageName = "jong/autumn.png";
            break;
        case JongEnum::winter:
            imageName = "jong/winter.png";
            break;
        case JongEnum::ju:
            imageName = "jong/ju.png";
            break;
        case JongEnum::mei:
            imageName = "jong/mei.png";
            break;
        case JongEnum::zhu:
            imageName = "jong/zhu.png";
            break;
        case JongEnum::lan:
            imageName = "jong/lan.png";
            break;
        default:
            break;
    }
    return imageName;
}

std::string Jong::getJongName(int type){
    switch (type){
        case wan_1:
            return "1W";
        case wan_2:
            return "2W";
        case wan_3:
            return "3W";
        case wan_4:
            return "4W";
        case wan_5:
            return "5W";
        case wan_6:
            return "6W";
        case wan_7:
            return "7W";
        case wan_8:
            return "8W";
        case wan_9:
            return "9W";
        case tong_1:
            return "1T";
        case tong_2:
            return "2T";
        case tong_3:
            return "3T";
        case tong_4:
            return "4T";
        case tong_5:
            return "5T";
        case tong_6:
            return "6T";
        case tong_7:
            return "7T";
        case tong_8:
            return "8T";
        case tong_9:
            return "9T";
        case tiao_1:
            return "1S";
        case tiao_2:
            return "2S";
        case tiao_3:
            return "3S";
        case tiao_4:
            return "4S";
        case tiao_5:
            return "5S";
        case tiao_6:
            return "6S";
        case tiao_7:
            return "7S";
        case tiao_8:
            return "8S";
        case tiao_9:
            return "9S";
        case east:
            return "DO";
        case south:
            return "NA";
        case  west:
            return "XI";
        case  north:
            return "BE";
        case zhong:
            return "H0";
        case fa:
            return "H1";
        case bai:
            return "H2";
        case spring:
            return "H3";
        case summer:
            return "H4";
        case autumn:
            return "H5";
        case winter:
            return "H6";
        case ju:
            return "H7";
        case mei:
            return "H8";
        case zhu:
            return "H9";
        case lan:
            return "H@";
        default:
            return "E@";
    }
}
