#include "mahjong/lobby/friend/FriendRoom.h"
#include "mahjong/lobby/LobbyScene.h"
#include "server/NetworkManage.h"
#include "mahjong/common/state/GameData.h"



bool FriendRoom::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    auto dialog_bg = Sprite::create("openroom/open_room_bg.png");
    dialog_bg->setPosition(640,350);
    addChild(dialog_bg);
    
    
    auto title = Sprite::create("openroom/open_room_title.png");
    title->setPosition(640,640);
    addChild(title);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(FriendRoom::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(1170, 660);
    addChild(closeMenu);
    
    shangHai = Sprite::create("openroom/shang_hai_btn_1.png");
    shangHai->setPosition(225,535);
    addChild(shangHai);
    
    hongZhong = Sprite::create("openroom/hong_zhong_btn_2.png");
    hongZhong->setPosition(225,430);
    addChild(hongZhong);
    
    vertical = Sprite::create("openroom/vertical_line_1.png");
    vertical->setPosition(332,355);
    addChild(vertical);
    
    auto fangka8 = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(FriendRoom::selectFangka8, this));
    auto fangka8Menu = Menu::create(fangka8,NULL);
    fangka8Menu->setPosition(470,405);
    addChild(fangka8Menu);
    
    auto select8 = Sprite::create("openroom/icon_right.png");
    select8->setTag(1024);
    select8->setPosition(470,405);
    select8->setVisible(true);
    addChild(select8);
    
    auto fangka4 = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(FriendRoom::selectFangka4, this));
    auto fangka4Menu = Menu::create(fangka4,NULL);
    fangka4Menu->setPosition(705,405);
    addChild(fangka4Menu);
    
    auto select4 = Sprite::create("openroom/icon_right.png");
    select4->setTag(1025);
    select4->setPosition(705,405);
    select4->setVisible(false);
    addChild(select4);
    
    
    auto fangka16 = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(FriendRoom::selectFangka16, this));
    auto fangka16Menu = Menu::create(fangka16,NULL);
    fangka16Menu->setPosition(960,405);
    addChild(fangka16Menu);
    
    auto select16 = Sprite::create("openroom/icon_right.png");
    select16->setTag(1026);
    select16->setPosition(960,405);
    select16->setVisible(false);
    addChild(select16);
    
    
    
    /** -------------------------------上海麻将选择界面ui显示开始--------------------**/
    shangHaiRoomText = Sprite::create("openroom/shang_hai_text.png");
    shangHaiRoomText->setPosition(755,375);
    addChild(shangHaiRoomText);
    
    // 1/1无勒子
    auto leziwu11 = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(FriendRoom::selectLeziType1, this));
    auto leziwuMenu11 = Menu::create(leziwu11,NULL);
    leziwuMenu11->setTag(2023);
    leziwuMenu11->setPosition(470,320);
    addChild(leziwuMenu11);
    
    auto leziwuImg11 = Sprite::create("openroom/icon_right.png");
    leziwuImg11->setTag(2024);
    leziwuImg11->setPosition(470,320);
    leziwuImg11->setVisible(true);
    addChild(leziwuImg11);
    
    // 1/1 20勒子
    auto lezi1120 = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(FriendRoom::selectLeziType2, this));
    auto lezi1120Menu = Menu::create(lezi1120,NULL);
    lezi1120Menu->setTag(2025);
    lezi1120Menu->setPosition(705,320);
    addChild(lezi1120Menu);
    
    auto lezi1120Img = Sprite::create("openroom/icon_right.png");
    lezi1120Img->setTag(2026);
    lezi1120Img->setPosition(705,320);
    lezi1120Img->setVisible(false);
    addChild(lezi1120Img);
    
    // 1/1 50勒子
    
    auto lezi1150 = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(FriendRoom::selectLeziType3, this));
    auto lezi1150Menu = Menu::create(lezi1150,NULL);
    lezi1150Menu->setTag(2027);
    lezi1150Menu->setPosition(960,320);
    addChild(lezi1150Menu);
    
    auto lezi1150Img = Sprite::create("openroom/icon_right.png");
    lezi1150Img->setTag(2028);
    lezi1150Img->setPosition(960,320);
    lezi1150Img->setVisible(false);
    addChild(lezi1150Img);

    
    
    // 2/2 40勒子
    
    auto lezi2240 = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(FriendRoom::selectLeziType5, this));
    auto lezi2240Menu = Menu::create(lezi2240,NULL);
    lezi2240Menu->setTag(2031);
    lezi2240Menu->setPosition(470,240);
    addChild(lezi2240Menu);
    
    auto lezi2240Img = Sprite::create("openroom/icon_right.png");
    lezi2240Img->setTag(2032);
    lezi2240Img->setPosition(470,240);
    lezi2240Img->setVisible(false);
    addChild(lezi2240Img);
    
    // 2/2 100勒子
    auto lezi22100 = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(FriendRoom::selectLeziType6, this));
    auto lezi22100Menu = Menu::create(lezi22100,NULL);
    lezi22100Menu->setTag(2033);
    lezi22100Menu->setPosition(705,240);
    addChild(lezi22100Menu);
    
    auto lezi22100Img = Sprite::create("openroom/icon_right.png");
    lezi22100Img->setTag(2034);
    lezi22100Img->setPosition(705,240);
    lezi22100Img->setVisible(false);
    addChild(lezi22100Img);
    
    //无开宝
    auto wukaibao = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(FriendRoom::selectWukaibao, this));
    auto wukaibaoMenu = Menu::create(wukaibao,NULL);
    wukaibaoMenu->setTag(2035);
    wukaibaoMenu->setPosition(470,160);
    addChild(wukaibaoMenu);
    
    auto selectWukaibao = Sprite::create("openroom/icon_right.png");
    selectWukaibao->setTag(2036);
    selectWukaibao->setPosition(470,160);
    selectWukaibao->setVisible(false);
    addChild(selectWukaibao);
    
    //二摸三冲
    auto mo2chong3 = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(FriendRoom::select2mo3chong, this));
    auto mo2chong3Menu = Menu::create(mo2chong3,NULL);
    mo2chong3Menu->setPosition(705,160);
    mo2chong3Menu->setTag(2037);
    addChild(mo2chong3Menu);
    
    auto selectmo2chong3 = Sprite::create("openroom/icon_right.png");
    selectmo2chong3->setTag(2038);
    selectmo2chong3->setPosition(705,160);
    selectmo2chong3->setVisible(false);
    addChild(selectmo2chong3);
    /** --------------------------上海麻将选择界面ui显示结束-------------------------- **/
    
    /** --------------------------红中麻将选择界面ui显示开始-------------------------- **/
    hongZhongRoomText = Sprite::create("openroom/hong_zhong_text.png");
    hongZhongRoomText->setPosition(755,375);
    hongZhongRoomText->setVisible(false);
    addChild(hongZhongRoomText);
    
    auto ma159zh = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(FriendRoom::selectMa159zh, this));
    auto ma159zhMenu = Menu::create(ma159zh,NULL);
    ma159zhMenu->setTag(3023);
    ma159zhMenu->setPosition(470,317);
    addChild(ma159zhMenu);
    ma159zhMenu->setVisible(false);
    
    auto ma159zhImg = Sprite::create("openroom/icon_right.png");
    ma159zhImg->setTag(3024);
    ma159zhImg->setPosition(470,317);
    addChild(ma159zhImg);
    ma159zhImg->setVisible(false);
    
    auto ma159 = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(FriendRoom::selectMa159, this));
    auto ma159Menu = Menu::create(ma159,NULL);
    ma159Menu->setTag(3025);
    ma159Menu->setPosition(705,317);
    addChild(ma159Menu);
    ma159Menu->setVisible(false);
    
    auto ma159Img = Sprite::create("openroom/icon_right.png");
    ma159Img->setTag(3026);
    ma159Img->setPosition(705,317);
    addChild(ma159Img);
    ma159Img->setVisible(false);
    
    auto ma1 = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(FriendRoom::selectMa1, this));
    auto ma1Menu = Menu::create(ma1,NULL);
    ma1Menu->setTag(3027);
    ma1Menu->setPosition(960,317);
    addChild(ma1Menu);
    ma1Menu->setVisible(false);
    
    auto ma1Img = Sprite::create("openroom/icon_right.png");
    ma1Img->setTag(3028);
    ma1Img->setPosition(960,317);
    addChild(ma1Img);
    ma1Img->setVisible(false);
    
    auto di2 = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(FriendRoom::selectDifen2, this));
    auto di2Menu = Menu::create(di2,NULL);
    di2Menu->setTag(3029);
    di2Menu->setPosition(470,165);
    addChild(di2Menu);
    di2Menu->setVisible(false);
    
    auto di2Img = Sprite::create("openroom/icon_right.png");
    di2Img->setTag(3030);
    di2Img->setPosition(470,165);
    addChild(di2Img);
    di2Img->setVisible(false);
    
    auto di1 = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(FriendRoom::selectDifen1, this));
    auto di1Menu = Menu::create(di1,NULL);
    di1Menu->setTag(3031);
    di1Menu->setPosition(705,165);
    addChild(di1Menu);
    di1Menu->setVisible(false);
    
    auto di1Img = Sprite::create("openroom/icon_right.png");
    di1Img->setTag(3032);
    di1Img->setPosition(705,165);
    addChild(di1Img);
    di1Img->setVisible(false);
    
    
    auto di5 = MenuItemImage::create("openroom/select_box_normal.png","openroom/select_box_normal.png",CC_CALLBACK_0(FriendRoom::selectDifen5, this));
    auto di5Menu = Menu::create(di5,NULL);
    di5Menu->setTag(3033);
    di5Menu->setPosition(960,165);
    addChild(di5Menu);
    di5Menu->setVisible(false);
    
    auto di5Img = Sprite::create("openroom/icon_right.png");
    di5Img->setTag(3034);
    di5Img->setPosition(960,165);
    addChild(di5Img);
    di5Img->setVisible(false);
    
    
    /** --------------------------红中麻将选择界面ui显示结束-------------------------- **/
    
   
    
    auto openBtn = MenuItemImage::create("openroom/open_room_btn_img_1.png", "openroom/open_room_btn_img_2.png", CC_CALLBACK_0(FriendRoom::openRoom, this));
    auto openMenu = Menu::create(openBtn,NULL);
    openMenu->setPosition(640,85);
    addChild(openMenu);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(FriendRoom::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(FriendRoom::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(FriendRoom::onTouchEnded, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener,this);
    
    return true;
}


void FriendRoom::onEnter(){
    Layer::onEnter();
    
}


void FriendRoom::onExit(){
    Layer::onExit();
    
}

bool FriendRoom::onTouchBegan(Touch *touch, Event  *event){
    return true;
}


void FriendRoom::onTouchMoved(Touch *touch, Event  *event){
    
    
}



void FriendRoom::onTouchEnded(Touch *touch, Event  *event){
    if(shangHai->getBoundingBox().containsPoint(touch->getLocation())){
        shangHaiSelected = true;
        shangHai->setTexture("openroom/shang_hai_btn_1.png");
        hongZhong->setTexture("openroom/hong_zhong_btn_2.png");
        vertical->setTexture("openroom/vertical_line_1.png");
        shangHaiRoomText->setVisible(true);
        hongZhongRoomText->setVisible(false);
        getChildByTag(2023)->setVisible(true);
        getChildByTag(2024)->setVisible(true);
        getChildByTag(2025)->setVisible(true);
        getChildByTag(2026)->setVisible(false);
        getChildByTag(2027)->setVisible(true);
        getChildByTag(2028)->setVisible(false);
//        getChildByTag(2029)->setVisible(true);
//        getChildByTag(2030)->setVisible(false);
        getChildByTag(2031)->setVisible(true);
        getChildByTag(2032)->setVisible(false);
        getChildByTag(2033)->setVisible(true);
        getChildByTag(2034)->setVisible(false);
        getChildByTag(2035)->setVisible(true);
        getChildByTag(2036)->setVisible(false);
        getChildByTag(2037)->setVisible(true);
        getChildByTag(2038)->setVisible(false);
        getChildByTag(3023)->setVisible(false);
        getChildByTag(3024)->setVisible(false);
        getChildByTag(3025)->setVisible(false);
        getChildByTag(3026)->setVisible(false);
        getChildByTag(3027)->setVisible(false);
        getChildByTag(3028)->setVisible(false);
        getChildByTag(3029)->setVisible(false);
        getChildByTag(3030)->setVisible(false);
        getChildByTag(3031)->setVisible(false);
        getChildByTag(3032)->setVisible(false);
        getChildByTag(3033)->setVisible(false);
        getChildByTag(3034)->setVisible(false);
    }
    if(hongZhong->getBoundingBox().containsPoint(touch->getLocation())){
        shangHaiSelected = false;
        shangHai->setTexture("openroom/shang_hai_btn_2.png");
        hongZhong->setTexture("openroom/hong_zhong_btn_1.png");
        vertical->setTexture("openroom/vertical_line_2.png");
        shangHaiRoomText->setVisible(false);
        hongZhongRoomText->setVisible(true);
        getChildByTag(2023)->setVisible(false);
        getChildByTag(2024)->setVisible(false);
        getChildByTag(2025)->setVisible(false);
        getChildByTag(2026)->setVisible(false);
        getChildByTag(2027)->setVisible(false);
        getChildByTag(2028)->setVisible(false);
//        getChildByTag(2029)->setVisible(false);
//        getChildByTag(2030)->setVisible(false);
        getChildByTag(2031)->setVisible(false);
        getChildByTag(2032)->setVisible(false);
        getChildByTag(2033)->setVisible(false);
        getChildByTag(2034)->setVisible(false);
        getChildByTag(2035)->setVisible(false);
        getChildByTag(2036)->setVisible(false);
        getChildByTag(2037)->setVisible(false);
        getChildByTag(2038)->setVisible(false);
        getChildByTag(3023)->setVisible(true);
        getChildByTag(3024)->setVisible(true);
        getChildByTag(3025)->setVisible(true);
        getChildByTag(3026)->setVisible(false);
        getChildByTag(3027)->setVisible(true);
        getChildByTag(3028)->setVisible(false);
        getChildByTag(3029)->setVisible(true);
        getChildByTag(3030)->setVisible(true);
        getChildByTag(3031)->setVisible(true);
        getChildByTag(3032)->setVisible(false);
        getChildByTag(3033)->setVisible(true);
        getChildByTag(3034)->setVisible(false);
    }
}

void FriendRoom::openRoom(){
    std::string ftype = "1";//1表示8局，2表示4局，3表示16局
    if(NULL != getChildByTag(1024)&& NULL != getChildByTag(1025)&& NULL != getChildByTag(1026)){
        if(getChildByTag(1025)->isVisible()){
            ftype = "2";
        }else if(getChildByTag(1026)->isVisible()){
            ftype = "3";
        }else{
            ftype = "1";
        }
    }
    
    if(shangHaiSelected){
        int iflezi = 0;//0表示(1/1 无勒子),1表示(1/1 20勒子),2表示(1/1 50勒子),3表示(2/2 无勒子),4表示(2/2 40勒子),5表示(2/2 100勒子)
        std::string ifkb = "1";//0表示没有，1表示有
        std::string ifemsc = "0";//0表示没有，1表示有
        
        if(NULL != getChildByTag(2024)&&getChildByTag(2024)->isVisible()){
            iflezi = LeziType::type1100;
        }else if(NULL != getChildByTag(2026)&&getChildByTag(2026)->isVisible()){
            iflezi = LeziType::type1120;
        }else if(NULL != getChildByTag(2028)&&getChildByTag(2028)->isVisible()){
            iflezi = LeziType::type1150;
        }
//        else if(NULL != getChildByTag(2030)&&getChildByTag(2030)->isVisible()){
//            iflezi = LeziType::type2200;
//        }
        else if(NULL != getChildByTag(2032)&&getChildByTag(2032)->isVisible()){
            iflezi = LeziType::type2240;
        }else if(NULL != getChildByTag(2034)&&getChildByTag(2034)->isVisible()){
            iflezi = LeziType::type22100;
        }
        
        if(NULL != getChildByTag(2036)){
            if(getChildByTag(2036)->isVisible()){
                ifkb = "0";
            }else{
                ifkb = "1";
            }
        }
        if(NULL != getChildByTag(2038)){
            if(getChildByTag(2038)->isVisible()){
                ifemsc = "1";
            }else{
                ifemsc = "0";
            }
        }
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getOpenRoomCommand(ftype,StringUtils::format("%d",iflezi),ifkb,ifemsc,"4"));
    }else{
        std::string fanma = "0";//0表示没有159zhong,1表示有159,2表示1码
        std::string difen = "2";
        if(NULL != getChildByTag(3024)&&getChildByTag(3024)->isVisible()){
            fanma  = "4";
        }else if(NULL != getChildByTag(3026)&&getChildByTag(3026)->isVisible()){
            fanma  = "3";
        }else if(NULL != getChildByTag(3028)&&getChildByTag(3028)->isVisible()){
            fanma  = "1";
        }
        
        if(NULL != getChildByTag(3030)&&getChildByTag(3030)->isVisible()){
            difen = "2";
        }else if(NULL != getChildByTag(3032)&&getChildByTag(3032)->isVisible()){
            difen = "1";
        }else if(NULL != getChildByTag(3034)&&getChildByTag(3034)->isVisible()){
            difen = "5";
        }
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getEnterHongZhongCommand(ftype, fanma,difen));
    }
}



void FriendRoom::closeView(){
    removeFromParent();
}

void FriendRoom::selectFangka8(){
    if(NULL != getChildByTag(1024)){
        getChildByTag(1024)->setVisible(true);
    }
    if(NULL != getChildByTag(1025)){
        getChildByTag(1025)->setVisible(false);
    }
    if(NULL != getChildByTag(1026)){
        getChildByTag(1026)->setVisible(false);
    }
}

void FriendRoom::selectFangka4(){
    if(NULL != getChildByTag(1024)){
        getChildByTag(1024)->setVisible(false);
    }
    if(NULL != getChildByTag(1025)){
        getChildByTag(1025)->setVisible(true);
    }
    if(NULL != getChildByTag(1026)){
        getChildByTag(1026)->setVisible(false);
    }
}

void FriendRoom::selectFangka16(){
    if(NULL != getChildByTag(1024)){
        getChildByTag(1024)->setVisible(false);
    }
    if(NULL != getChildByTag(1025)){
        getChildByTag(1025)->setVisible(false);
    }
    if(NULL != getChildByTag(1026)){
        getChildByTag(1026)->setVisible(true);
    }
}


void FriendRoom::selectLeziType1(){
    if(NULL != getChildByTag(2024)){
        getChildByTag(2024)->setVisible(true);
    }
    if(NULL != getChildByTag(2026)){
        getChildByTag(2026)->setVisible(false);
    }
    if(NULL != getChildByTag(2028)){
        getChildByTag(2028)->setVisible(false);
    }
//    if(NULL != getChildByTag(2030)){
//        getChildByTag(2030)->setVisible(false);
//    }
    if(NULL != getChildByTag(2032)){
        getChildByTag(2032)->setVisible(false);
    }
    if(NULL != getChildByTag(2034)){
        getChildByTag(2034)->setVisible(false);
    }
}

void FriendRoom::selectLeziType2(){
    if(NULL != getChildByTag(2024)){
        getChildByTag(2024)->setVisible(false);
    }
    if(NULL != getChildByTag(2026)){
        getChildByTag(2026)->setVisible(true);
    }
    if(NULL != getChildByTag(2028)){
        getChildByTag(2028)->setVisible(false);
    }
//    if(NULL != getChildByTag(2030)){
//        getChildByTag(2030)->setVisible(false);
//    }
    if(NULL != getChildByTag(2032)){
        getChildByTag(2032)->setVisible(false);
    }
    if(NULL != getChildByTag(2034)){
        getChildByTag(2034)->setVisible(false);
    }
}

void FriendRoom::selectLeziType3(){
    if(NULL != getChildByTag(2024)){
        getChildByTag(2024)->setVisible(false);
    }
    if(NULL != getChildByTag(2026)){
        getChildByTag(2026)->setVisible(false);
    }
    if(NULL != getChildByTag(2028)){
        getChildByTag(2028)->setVisible(true);
    }
//    if(NULL != getChildByTag(2030)){
//        getChildByTag(2030)->setVisible(false);
//    }
    if(NULL != getChildByTag(2032)){
        getChildByTag(2032)->setVisible(false);
    }
    if(NULL != getChildByTag(2034)){
        getChildByTag(2034)->setVisible(false);
    }
}

void FriendRoom::selectLeziType4(){
    if(NULL != getChildByTag(2024)){
        getChildByTag(2024)->setVisible(false);
    }
    if(NULL != getChildByTag(2026)){
        getChildByTag(2026)->setVisible(false);
    }
    if(NULL != getChildByTag(2028)){
        getChildByTag(2028)->setVisible(false);
    }
//    if(NULL != getChildByTag(2030)){
//        getChildByTag(2030)->setVisible(true);
//    }
    if(NULL != getChildByTag(2032)){
        getChildByTag(2032)->setVisible(false);
    }
    if(NULL != getChildByTag(2034)){
        getChildByTag(2034)->setVisible(false);
    }
}

void FriendRoom::selectLeziType5(){
    if(NULL != getChildByTag(2024)){
        getChildByTag(2024)->setVisible(false);
    }
    if(NULL != getChildByTag(2026)){
        getChildByTag(2026)->setVisible(false);
    }
    if(NULL != getChildByTag(2028)){
        getChildByTag(2028)->setVisible(false);
    }
//    if(NULL != getChildByTag(2030)){
//        getChildByTag(2030)->setVisible(false);
//    }
    if(NULL != getChildByTag(2032)){
        getChildByTag(2032)->setVisible(true);
    }
    if(NULL != getChildByTag(2034)){
        getChildByTag(2034)->setVisible(false);
    }
}

void FriendRoom::selectLeziType6(){
    if(NULL != getChildByTag(2024)){
        getChildByTag(2024)->setVisible(false);
    }
    if(NULL != getChildByTag(2026)){
        getChildByTag(2026)->setVisible(false);
    }
    if(NULL != getChildByTag(2028)){
        getChildByTag(2028)->setVisible(false);
    }
//    if(NULL != getChildByTag(2030)){
//        getChildByTag(2030)->setVisible(false);
//    }
    if(NULL != getChildByTag(2032)){
        getChildByTag(2032)->setVisible(false);
    }
    if(NULL != getChildByTag(2034)){
        getChildByTag(2034)->setVisible(true);
    }
}


void FriendRoom::selectWukaibao(){
    if(NULL != getChildByTag(2036)){
        getChildByTag(2036)->setVisible(!getChildByTag(2036)->isVisible());
    }
}

void FriendRoom::select2mo3chong(){
    if(NULL != getChildByTag(2038)){
        getChildByTag(2038)->setVisible(!getChildByTag(2038)->isVisible());
    }
}


void FriendRoom::selectMa159zh(){
    if(NULL != getChildByTag(3024)){
        getChildByTag(3024)->setVisible(true);
    }
    if(NULL != getChildByTag(3026)){
        getChildByTag(3026)->setVisible(false);
    }
    if(NULL != getChildByTag(3028)){
        getChildByTag(3028)->setVisible(false);
    }
}


void FriendRoom::selectMa159(){
    if(NULL != getChildByTag(3024)){
        getChildByTag(3024)->setVisible(false);
    }
    if(NULL != getChildByTag(3026)){
        getChildByTag(3026)->setVisible(true);
    }
    if(NULL != getChildByTag(3028)){
        getChildByTag(3028)->setVisible(false);
    }
}

void FriendRoom::selectMa1(){
    if(NULL != getChildByTag(3024)){
        getChildByTag(3024)->setVisible(false);
    }
    if(NULL != getChildByTag(3026)){
        getChildByTag(3026)->setVisible(false);
    }
    if(NULL != getChildByTag(3028)){
        getChildByTag(3028)->setVisible(true);
    }
}

void FriendRoom::selectDifen2(){
    if(NULL != getChildByTag(3030)){
        getChildByTag(3030)->setVisible(true);
    }
    if(NULL != getChildByTag(3032)){
        getChildByTag(3032)->setVisible(false);
    }
    if(NULL != getChildByTag(3034)){
        getChildByTag(3034)->setVisible(false);
    }
}


void FriendRoom::selectDifen1(){
    if(NULL != getChildByTag(3030)){
        getChildByTag(3030)->setVisible(false);
    }
    if(NULL != getChildByTag(3032)){
        getChildByTag(3032)->setVisible(true);
    }
    if(NULL != getChildByTag(3034)){
        getChildByTag(3034)->setVisible(false);
    }
}

void FriendRoom::selectDifen5(){
    if(NULL != getChildByTag(3030)){
        getChildByTag(3030)->setVisible(false);
    }
    if(NULL != getChildByTag(3032)){
        getChildByTag(3032)->setVisible(false);
    }
    if(NULL != getChildByTag(3034)){
        getChildByTag(3034)->setVisible(true);
    }}


