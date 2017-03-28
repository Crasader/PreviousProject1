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
    //    MenuItem* item = MenuItem::create();
    //    item->setContentSize(Size(1280, 720));
    //    Menu* bg = Menu::create(item, NULL);
    //    addChild(bg);
    
    auto dialog_bg = Sprite::create("shop/shop_bg.png");
    dialog_bg->setPosition(640,350);
    addChild(dialog_bg);
    
    
    auto roomTitle = Sprite::create("friend/open_room_title.png");
    roomTitle->setPosition(640,650);
    addChild(roomTitle);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(FriendRoom::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(1050, 605);
    addChild(closeMenu);
    
    auto roomline = Sprite::create("openroom/across_line.png");
    roomline->setPosition(640,385);
    addChild(roomline);
    
    shangHai = Sprite::create("openroom/shang_hai_btn_1.png");
    shangHai->setPosition(303,505);
    addChild(shangHai);
    
    hongZhong = Sprite::create("openroom/hong_zhong_btn_2.png");
    hongZhong->setPosition(303,410);
    addChild(hongZhong);
    
    vertical = Sprite::create("openroom/vertical_line_1.png");
    vertical->setPosition(380,385);
    addChild(vertical);
    
    auto fangka8 = MenuItemImage::create("friend/select_box_normal.png","friend/select_box_normal.png",CC_CALLBACK_0(FriendRoom::selectFangka8, this));
    auto fangka8Menu = Menu::create(fangka8,NULL);
    fangka8Menu->setPosition(490,480);
    addChild(fangka8Menu);
    
    auto select8 = Sprite::create("friend/icon_right.png");
    select8->setTag(1024);
    select8->setPosition(490,480);
    select8->setVisible(true);
    addChild(select8);
    
    auto fangka4 = MenuItemImage::create("friend/select_box_normal.png","friend/select_box_normal.png","friend/select_box_gray.png",CC_CALLBACK_0(FriendRoom::selectFangka4, this));
    auto fangka4Menu = Menu::create(fangka4,NULL);
    fangka4Menu->setPosition(740,480);
    addChild(fangka4Menu);
    
    auto select4 = Sprite::create("friend/icon_right.png");
    select4->setTag(1025);
    select4->setPosition(740,480);
    select4->setVisible(false);
    addChild(select4);
    
    
    auto fangka16 = MenuItemImage::create("friend/select_box_normal.png","friend/select_box_normal.png","friend/select_box_gray.png",CC_CALLBACK_0(FriendRoom::selectFangka16, this));
    auto fangka16Menu = Menu::create(fangka16,NULL);
    fangka16Menu->setPosition(490,425);
    addChild(fangka16Menu);
    
    auto select16 = Sprite::create("friend/icon_right.png");
    select16->setTag(1026);
    select16->setPosition(490,425);
    select16->setVisible(false);
    addChild(select16);
    
    
    
    /** -------------------------------上海麻将选择界面ui显示开始--------------------**/
    shangHaiRoomText = Sprite::create("openroom/shang_hai_text.png");
    shangHaiRoomText->setPosition(725,420);
    addChild(shangHaiRoomText);
    
    
    auto leziwu = MenuItemImage::create("friend/select_box_normal.png","friend/select_box_normal.png",CC_CALLBACK_0(FriendRoom::selectWulezi, this));
    auto leziwuMenu = Menu::create(leziwu,NULL);
    leziwuMenu->setTag(2023);
    leziwuMenu->setPosition(490,360);
    addChild(leziwuMenu);
    
    auto leziwuImg = Sprite::create("friend/icon_right.png");
    leziwuImg->setTag(2024);
    leziwuImg->setPosition(490,360);
    leziwuImg->setVisible(true);
    addChild(leziwuImg);
    
    auto lezi40 = MenuItemImage::create("friend/select_box_normal.png","friend/select_box_normal.png","friend/select_box_gray.png",CC_CALLBACK_0(FriendRoom::selectLezi, this));
    auto lezi40Menu = Menu::create(lezi40,NULL);
    lezi40Menu->setTag(2025);
    lezi40Menu->setPosition(740,360);
    addChild(lezi40Menu);
    
    auto lezi40Img = Sprite::create("friend/icon_right.png");
    lezi40Img->setTag(2026);
    lezi40Img->setPosition(740,360);
    lezi40Img->setVisible(false);
    addChild(lezi40Img);
    
    auto wukaibao = MenuItemImage::create("friend/select_box_normal.png","friend/select_box_normal.png",CC_CALLBACK_0(FriendRoom::selectWukaibao, this));
    auto wukaibaoMenu = Menu::create(wukaibao,NULL);
    wukaibaoMenu->setTag(3023);
    wukaibaoMenu->setPosition(490,305);
    addChild(wukaibaoMenu);
    
    auto selectWukaibao = Sprite::create("friend/icon_right.png");
    selectWukaibao->setTag(3024);
    selectWukaibao->setPosition(490,305);
    selectWukaibao->setVisible(false);
    addChild(selectWukaibao);
    
    
    auto mo2chong3 = MenuItemImage::create("friend/select_box_normal.png","friend/select_box_normal.png","friend/select_box_gray.png",CC_CALLBACK_0(FriendRoom::select2mo3chong, this));
    auto mo2chong3Menu = Menu::create(mo2chong3,NULL);
    mo2chong3Menu->setPosition(740,305);
    mo2chong3Menu->setTag(3025);
    addChild(mo2chong3Menu);
    
    auto selectmo2chong3 = Sprite::create("friend/icon_right.png");
    selectmo2chong3->setTag(3026);
    selectmo2chong3->setPosition(740,305);
    selectmo2chong3->setVisible(false);
    addChild(selectmo2chong3);
    /** --------------------------上海麻将选择界面ui显示结束-------------------------- **/
    
    /** --------------------------红中麻将选择界面ui显示开始-------------------------- **/
    hongZhongRoomText = Sprite::create("openroom/hong_zhong_text.png");
    hongZhongRoomText->setPosition(708,388);
    hongZhongRoomText->setVisible(false);
    addChild(hongZhongRoomText);
    
    auto ma159zh = MenuItemImage::create("friend/select_box_normal.png","friend/select_box_normal.png",CC_CALLBACK_0(FriendRoom::selectMa159zh, this));
    auto ma159zhMenu = Menu::create(ma159zh,NULL);
    ma159zhMenu->setTag(4023);
    ma159zhMenu->setPosition(490,360);
    addChild(ma159zhMenu);
    ma159zhMenu->setVisible(false);
    
    auto ma159zhImg = Sprite::create("friend/icon_right.png");
    ma159zhImg->setTag(4024);
    ma159zhImg->setPosition(490,360);
    addChild(ma159zhImg);
    ma159zhImg->setVisible(false);
    
    auto ma159 = MenuItemImage::create("friend/select_box_normal.png","friend/select_box_normal.png","friend/select_box_gray.png",CC_CALLBACK_0(FriendRoom::selectMa159, this));
    auto ma159Menu = Menu::create(ma159,NULL);
    ma159Menu->setTag(4025);
    ma159Menu->setPosition(740,360);
    addChild(ma159Menu);
    ma159Menu->setVisible(false);
    
    auto ma159Img = Sprite::create("friend/icon_right.png");
    ma159Img->setTag(4026);
    ma159Img->setPosition(740,360);
    addChild(ma159Img);
    ma159Img->setVisible(false);
    
    auto ma1 = MenuItemImage::create("friend/select_box_normal.png","friend/select_box_normal.png",CC_CALLBACK_0(FriendRoom::selectMa1, this));
    auto ma1Menu = Menu::create(ma1,NULL);
    ma1Menu->setTag(4027);
    ma1Menu->setPosition(490,305);
    addChild(ma1Menu);
    ma1Menu->setVisible(false);
    
    auto ma1Img = Sprite::create("friend/icon_right.png");
    ma1Img->setTag(4028);
    ma1Img->setPosition(490,305);
    addChild(ma1Img);
    ma1Img->setVisible(false);
    
    auto di2 = MenuItemImage::create("friend/select_box_normal.png","friend/select_box_normal.png",CC_CALLBACK_0(FriendRoom::selectDifen2, this));
    auto di2Menu = Menu::create(di2,NULL);
    di2Menu->setTag(5023);
    di2Menu->setPosition(490,245);
    addChild(di2Menu);
    di2Menu->setVisible(false);
    
    auto di2Img = Sprite::create("friend/icon_right.png");
    di2Img->setTag(5024);
    di2Img->setPosition(490,245);
    addChild(di2Img);
    di2Img->setVisible(false);
    
    auto di10 = MenuItemImage::create("friend/select_box_normal.png","friend/select_box_normal.png",CC_CALLBACK_0(FriendRoom::selectDifen10, this));
    auto di10Menu = Menu::create(di10,NULL);
    di10Menu->setTag(5025);
    di10Menu->setPosition(740,245);
    addChild(di10Menu);
    di10Menu->setVisible(false);
    
    auto di10Img = Sprite::create("friend/icon_right.png");
    di10Img->setTag(5026);
    di10Img->setPosition(740,245);
    addChild(di10Img);
    di10Img->setVisible(false);
    
    /** --------------------------红中麻将选择界面ui显示结束-------------------------- **/
    
    auto fangZhuText = Sprite::create("friend/fang_zhu_jiang_li.png");
    fangZhuText->setPosition(580,175);
    addChild(fangZhuText);
    
    auto lequan = Sprite::create("common/lequan_icon.png");
    lequan->setPosition(660,175);
    addChild(lequan);
    
    auto leX = Sprite::create("friend/fangzhu_x.png");
    leX->setPosition(695,177);
    addChild(leX);
    
    LabelAtlas* lequanNum = LabelAtlas::create(GAMEDATA::getInstance()->getFangzhuLequan(),"shop/prop_num.png",21,28,'0');
    lequanNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    lequanNum->setPosition(705,177);
    addChild(lequanNum);
    
    auto openBtn = MenuItemImage::create("mjlobby/open_room_btn_img_1.png", "mjlobby/open_room_btn_img_2.png", CC_CALLBACK_0(FriendRoom::openRoom, this));
    auto openMenu = Menu::create(openBtn,NULL);
    openMenu->setPosition(640,120);
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
        getChildByTag(3023)->setVisible(true);
        getChildByTag(3025)->setVisible(true);
        getChildByTag(4023)->setVisible(false);
        getChildByTag(4024)->setVisible(false);
        getChildByTag(4025)->setVisible(false);
        getChildByTag(4026)->setVisible(false);
        getChildByTag(4027)->setVisible(false);
        getChildByTag(4028)->setVisible(false);
        getChildByTag(5023)->setVisible(false);
        getChildByTag(5024)->setVisible(false);
        getChildByTag(5025)->setVisible(false);
        getChildByTag(5026)->setVisible(false);
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
        getChildByTag(3023)->setVisible(false);
        getChildByTag(3024)->setVisible(false);
        getChildByTag(3025)->setVisible(false);
        getChildByTag(3026)->setVisible(false);
        getChildByTag(4023)->setVisible(true);
        getChildByTag(4024)->setVisible(true);
        getChildByTag(4025)->setVisible(true);
        getChildByTag(4027)->setVisible(true);
        getChildByTag(5023)->setVisible(true);
        getChildByTag(5024)->setVisible(true);
        getChildByTag(5025)->setVisible(true);
    }
}

void FriendRoom::openRoom(){
    if(shangHaiSelected){
        std::string ftype = "1";//1表示8局，2表示4局，3表示16局
        std::string iflezi = "0";//0表示没有，1表示有
        std::string ifkb = "1";//0表示没有，1表示有
        std::string ifemsc = "0";//0表示没有，1表示有
        if(NULL != getChildByTag(1024)&& NULL != getChildByTag(1025)&& NULL != getChildByTag(1026)){
            if(getChildByTag(1025)->isVisible()){
                ftype = "2";
            }else if(getChildByTag(1026)->isVisible()){
                ftype = "3";
            }else{
                ftype = "1";
            }
        }
        if(NULL != getChildByTag(2024)&& NULL != getChildByTag(2026)){
            if(getChildByTag(2024)->isVisible()){
                iflezi = "0";
            }else{
                iflezi = "1";
            }
        }
        if(NULL != getChildByTag(3024)){
            if(getChildByTag(3024)->isVisible()){
                ifkb = "0";
            }else{
                ifkb = "1";
            }
        }
        if(NULL != getChildByTag(3026)){
            if(getChildByTag(3026)->isVisible()){
                ifemsc = "1";
            }else{
                ifemsc = "0";
            }
        }
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getOpenRoomCommand(ftype,iflezi,ifkb,ifemsc));
    }else{
        
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


void FriendRoom::selectWulezi(){
    if(NULL != getChildByTag(2024)){
        getChildByTag(2024)->setVisible(true);
    }
    if(NULL != getChildByTag(2026)){
        getChildByTag(2026)->setVisible(false);
    }
}


void FriendRoom::selectLezi(){
    if(NULL != getChildByTag(2024)){
        getChildByTag(2024)->setVisible(false);
    }
    if(NULL != getChildByTag(2026)){
        getChildByTag(2026)->setVisible(true);
    }
}


void FriendRoom::selectWukaibao(){
    if(NULL != getChildByTag(3024)){
        getChildByTag(3024)->setVisible(!getChildByTag(3024)->isVisible());
    }
}

void FriendRoom::select2mo3chong(){
    if(NULL != getChildByTag(3026)){
        getChildByTag(3026)->setVisible(!getChildByTag(3026)->isVisible());
    }
}


void FriendRoom::selectMa159zh(){
    if(NULL != getChildByTag(4024)){
        getChildByTag(4024)->setVisible(true);
    }
    if(NULL != getChildByTag(4026)){
        getChildByTag(4026)->setVisible(false);
    }
    if(NULL != getChildByTag(4028)){
        getChildByTag(4028)->setVisible(false);
    }
}


void FriendRoom::selectMa159(){
    if(NULL != getChildByTag(4024)){
        getChildByTag(4024)->setVisible(false);
    }
    if(NULL != getChildByTag(4026)){
        getChildByTag(4026)->setVisible(true);
    }
    if(NULL != getChildByTag(4028)){
        getChildByTag(4028)->setVisible(false);
    }
}

void FriendRoom::selectMa1(){
    if(NULL != getChildByTag(4024)){
        getChildByTag(4024)->setVisible(false);
    }
    if(NULL != getChildByTag(4026)){
        getChildByTag(4026)->setVisible(false);
    }
    if(NULL != getChildByTag(4028)){
        getChildByTag(4028)->setVisible(true);
    }
}

void FriendRoom::selectDifen2(){
    if(NULL != getChildByTag(5024)){
        getChildByTag(5024)->setVisible(true);
    }
    if(NULL != getChildByTag(5026)){
        getChildByTag(5026)->setVisible(false);
    }
}


void FriendRoom::selectDifen10(){
    if(NULL != getChildByTag(5024)){
        getChildByTag(5024)->setVisible(false);
    }
    if(NULL != getChildByTag(5026)){
        getChildByTag(5026)->setVisible(true);
    }
}


