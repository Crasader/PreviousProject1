//
//  RankLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/7/6.
//
//

#include "mahjong/lobby/rank/RankLayer.hpp"
#include "server/NetworkManage.h"
#include "server/MsgConfig.h"

RankLayer* RankLayer::create(LobbyPaiHangData data){
    RankLayer* cell = new RankLayer();
    if(cell && cell->init(data)){
        cell -> autorelease();
        return cell;
    }
    CC_SAFE_DELETE(cell);
    return NULL;
}


bool RankLayer::init(LobbyPaiHangData data){

    auto rank_bg = Sprite::create("mjlobby/rank_bg.png");
    rank_bg->setPosition(280,360);
    addChild(rank_bg);
    
    auto yeqian = Sprite::create("mjlobby/tab_bg.png");
    yeqian->setPosition(280,547);
    addChild(yeqian);
    
    auto fen1 = Sprite::create("mjlobby/fen_ge.png");
    fen1->setPosition(200,547);
    addChild(fen1);
    
    auto fen2 = Sprite::create("mjlobby/fen_ge.png");
    fen2->setPosition(362,547);
    addChild(fen2);
    
    tab1 = MenuItemImage::create("mjlobby/rank_btn_1.png", "mjlobby/rank_btn_1.png", CC_CALLBACK_0(RankLayer::showRank1,this));
    auto tabMenu = Menu::create(tab1,NULL);
    tab1->setOpacity(0);
    tabMenu->setPosition(125,545);
    addChild(tabMenu);
    
    tab2 = MenuItemImage::create("mjlobby/rank_btn_1.png", "mjlobby/rank_btn_1.png", CC_CALLBACK_0(RankLayer::showRank2,this));
    tab2->setOpacity(0);
    auto tabMenu2 = Menu::create(tab2,NULL);
    tabMenu2->setPosition(280,545);
    addChild(tabMenu2);
    
    tab3 = MenuItemImage::create("mjlobby/rank_btn_1.png", "mjlobby/rank_btn_1.png", CC_CALLBACK_0(RankLayer::showRank3,this));
    tab3->setOpacity(0);
    auto tabMenu3 = Menu::create(tab3,NULL);
    tabMenu3->setPosition(435,545);
    addChild(tabMenu3);
    
    rankName1 = Label::createWithSystemFont(data.name1, "arial", 25);
    rankName1->setColor(Color3B(177,88,8));
    rankName1->setPosition(125,545);
    addChild(rankName1,1);
    
    rankName2 = Label::createWithSystemFont(data.name2, "arial", 25);
    rankName2->setColor(Color3B(255,252,248));
    rankName2->setPosition(280,545);
    addChild(rankName2,1);
    
    rankName3 = Label::createWithSystemFont(data.name3, "arial", 25);
    rankName3->setColor(Color3B(255,252,248));
    rankName3->setPosition(435,545);
    addChild(rankName3,1);
    
    ranA = RankList::create();
    ranA->updateRankLayer(data.content1);
    addChild(ranA);
    
    auto peng = MenuItemImage::create("mjlobby/send_haoyou.png", "mjlobby/send_quan.png", CC_CALLBACK_0(RankLayer::shareToFriend,this));
    auto quan = MenuItemImage::create("mjlobby/send_quan.png", "mjlobby/send_quan.png", CC_CALLBACK_0(RankLayer::shareToSocial,this));
    auto  menu = Menu::create(peng,quan,NULL);
    menu->setPosition(375,167);
    menu->alignItemsHorizontallyWithPadding(10);
    addChild(menu);
    return true;
}

void RankLayer::onEnterTransitionDidFinish(){
    Layer::onEnterTransitionDidFinish();
}

void RankLayer::onEnter(){
    Layer::onEnter();
    updateRank =  EventListenerCustom::create(MSG_UPDATE_LOBBY_RANK, [=](EventCustom* event){
        LobbyPaiHangData data = GAMEDATA::getInstance()->getLobbyPaiHangData();
        
        tab1->setOpacity(255);
        rankName1->setString(data.name1);
        rankName2->setString(data.name2);
        rankName3->setString(data.name3);
        ranA->updateRankLayer(data.content1);
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(updateRank, 1);
}


void RankLayer::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(updateRank);
}

void RankLayer::shareToFriend(){
//    auto hbLayer = Layer::create();
//    
//    auto hongbaobg = Sprite::create("result/result_bg.jpg");
//    hongbaobg->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
//    hongbaobg->setPosition(0,0);
//    hbLayer->addChild(hongbaobg);
//    
//    auto hong = Sprite::create("competition/hongbao_bg.png");
//    hong->setPosition(335,360);
//    hbLayer->addChild(hong);
//    
//    auto bao = Label::createWithSystemFont("小白相话费红包","arial",26);
//    bao->setColor(Color3B(246,226,176));
//    bao->setAnchorPoint(Point::ANCHOR_MIDDLE);
//    bao->setPosition(335,600);
//    hbLayer->addChild(bao);
//    
//    auto headImage = HeadImage::createByImage(UserData::getInstance()->getPicture(),Size(140,140));
//    headImage->setPosition(335, 480);
//    hbLayer->addChild(headImage, 10);
//    
//    auto nick = Label::createWithSystemFont(UserData::getInstance()->getNickName(),"arial",26);
//    nick->setColor(Color3B::BLACK);
//    nick->setPosition(330,384);
//    hbLayer->addChild(nick);
//    
//    auto pride = Label::createWithSystemFont(StringUtils::format("%s元话费",getMyPride().c_str()),"arial",80);
//    pride->setColor(Color3B(170,44,0));
//    pride->setAnchorPoint(Point::ANCHOR_MIDDLE);
//    pride->setPosition(335,320);
//    hbLayer->addChild(pride);
//    
//    
//    
//    auto headImage2 = HeadImage::createByImage(UserData::getInstance()->getPicture(),Size(68,68));
//    headImage2->setPosition(145, 170);
//    hbLayer->addChild(headImage2, 10);
//    
//    auto nick2 = Label::createWithSystemFont(UserData::getInstance()->getNickName(),"arial",20);
//    nick2->setColor(Color3B::BLACK);
//    nick2->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
//    nick2->setPosition(185,185);
//    hbLayer->addChild(nick2);
//    
//    auto guan = Sprite::create("competition/huang_guan.png");
//    guan->setPosition(420,150);
//    hbLayer->addChild(guan);
//    
//    auto pride2 = Label::createWithSystemFont(StringUtils::format("%s元话费赛",getMyPride().c_str()),"arial",26);
//    pride2->setColor(Color3B::BLACK);
//    pride2->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
//    pride2->setPosition(445,190);
//    hbLayer->addChild(pride2);
//    
//    auto shui = Label::createWithSystemFont("水平最高","arial",26);
//    shui->setColor(Color3B(255,183,64));
//    shui->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
//    shui->setPosition(445,150);
//    
//    hbLayer->addChild(shui);
//    
//    auto ma = Sprite::create("competition/er_wei_ma.png");
//    ma->setPosition(920,360);
//    hbLayer->addChild(ma);
//    
//    if(getMyRank() != "1"){
//        guan->setTexture("competition/dog_img.png");
//        shui->setString("虐成狗");
//        shui->setColor(Color3B(87,87,86));
//        auto cha = Sprite::create("competition/cha_cha.png");
//        cha->setPosition(335,320);
//        hbLayer->addChild(cha);
//    }
//    
//    auto renderTexture = RenderTexture::create(1280, 720, Texture2D::PixelFormat::RGBA8888);
//    //清空并开始获取
//    renderTexture->beginWithClear(0.0f, 0.0f, 0.0f, 0.0f);
//    //遍历场景节点对象，填充纹理到RenderTexture中
//    hbLayer->visit();
//    //结束获取
//    renderTexture->end();
//    //保存文件
//    std::string outputFile =StringUtils::format("%smahjong_screen_shot.png",FileUtils::getInstance()->getWritablePath().c_str());
//    renderTexture->saveToFile("mahjong_screen_shot.png",Image::Format::PNG);
//    schedule([=](float dt){
//#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//        CallAndroidMethod::getInstance()->shareSDCardImageToWeChat(outputFile, true);
//#endif
//        
//#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//        CallIOSMethod::getInstance()->doWechatShareImg(outputFile, 1);
//#endif
//    }, 0, 0, 0.2f, "mmp");
}


void RankLayer::shareToSocial(){
//    auto hbLayer = Layer::create();
//    
//    auto hongbaobg = Sprite::create("result/result_bg.jpg");
//    hongbaobg->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
//    hongbaobg->setPosition(0,0);
//    hbLayer->addChild(hongbaobg);
//    
//    auto hong = Sprite::create("competition/hongbao_bg.png");
//    hong->setPosition(335,360);
//    hbLayer->addChild(hong);
//    
//    auto bao = Label::createWithSystemFont("小白相话费红包","arial",26);
//    bao->setColor(Color3B(246,226,176));
//    bao->setAnchorPoint(Point::ANCHOR_MIDDLE);
//    bao->setPosition(335,600);
//    hbLayer->addChild(bao);
//    
//    auto headImage = HeadImage::createByImage(UserData::getInstance()->getPicture(),Size(140,140));
//    headImage->setPosition(335, 480);
//    hbLayer->addChild(headImage, 10);
//    
//    auto nick = Label::createWithSystemFont(UserData::getInstance()->getNickName(),"arial",26);
//    nick->setColor(Color3B::BLACK);
//    nick->setPosition(330,384);
//    hbLayer->addChild(nick);
//    
//    auto pride = Label::createWithSystemFont(StringUtils::format("%s元话费",getMyPride().c_str()),"arial",80);
//    pride->setColor(Color3B(170,44,0));
//    pride->setAnchorPoint(Point::ANCHOR_MIDDLE);
//    pride->setPosition(335,320);
//    hbLayer->addChild(pride);
//    
//    
//    
//    auto headImage2 = HeadImage::createByImage(UserData::getInstance()->getPicture(),Size(68,68));
//    headImage2->setPosition(145, 170);
//    hbLayer->addChild(headImage2, 10);
//    
//    auto nick2 = Label::createWithSystemFont(UserData::getInstance()->getNickName(),"arial",20);
//    nick2->setColor(Color3B::BLACK);
//    nick2->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
//    nick2->setPosition(185,185);
//    hbLayer->addChild(nick2);
//    
//    auto guan = Sprite::create("competition/huang_guan.png");
//    guan->setPosition(420,150);
//    hbLayer->addChild(guan);
//    
//    auto pride2 = Label::createWithSystemFont(StringUtils::format("%s元话费赛",getMyPride().c_str()),"arial",26);
//    pride2->setColor(Color3B::BLACK);
//    pride2->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
//    pride2->setPosition(445,190);
//    hbLayer->addChild(pride2);
//    
//    auto shui = Label::createWithSystemFont("水平最高","arial",26);
//    shui->setColor(Color3B(255,183,64));
//    shui->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
//    shui->setPosition(445,150);
//    
//    hbLayer->addChild(shui);
//    
//    auto ma = Sprite::create("competition/er_wei_ma.png");
//    ma->setPosition(920,360);
//    hbLayer->addChild(ma);
//    
//    if(getMyRank() != "1"){
//        guan->setTexture("competition/dog_img.png");
//        shui->setString("虐成狗");
//        shui->setColor(Color3B(87,87,86));
//        auto cha = Sprite::create("competition/cha_cha.png");
//        cha->setPosition(335,320);
//        hbLayer->addChild(cha);
//    }
//    
//    auto renderTexture = RenderTexture::create(1280, 720, Texture2D::PixelFormat::RGBA8888);
//    //清空并开始获取
//    renderTexture->beginWithClear(0.0f, 0.0f, 0.0f, 0.0f);
//    //遍历场景节点对象，填充纹理到RenderTexture中
//    hbLayer->visit();
//    //结束获取
//    renderTexture->end();
//    //保存文件
//    std::string outputFile =StringUtils::format("%smahjong_screen_shot.png",FileUtils::getInstance()->getWritablePath().c_str());
//    renderTexture->saveToFile("mahjong_screen_shot.png",Image::Format::PNG);
//    schedule([=](float dt){
//#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//        CallAndroidMethod::getInstance()->shareSDCardImageToWeChat(outputFile, true);
//#endif
//        
//#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//        CallIOSMethod::getInstance()->doWechatShareImg(outputFile, 1);
//#endif
//    }, 0, 0, 0.2f, "mmp");
    
}

void RankLayer::showRank1(){
    tab1->setOpacity(255);
    tab2->setOpacity(0);
    tab3->setOpacity(0);
    rankName1->setColor(Color3B(177,88,8));
    rankName2->setColor(Color3B(255,252,248));
    rankName3->setColor(Color3B(255,252,248));
    ranA->updateRankLayer(GAMEDATA::getInstance()->getLobbyPaiHangData().content1);
}
void RankLayer::showRank2(){
    tab1->setOpacity(0);
    tab2->setOpacity(255);
    tab3->setOpacity(0);
    rankName2->setColor(Color3B(177,88,8));
    rankName1->setColor(Color3B(255,252,248));
    rankName3->setColor(Color3B(255,252,248));
    ranA->updateRankLayer(GAMEDATA::getInstance()->getLobbyPaiHangData().content2);
}
void RankLayer::showRank3(){
    tab1->setOpacity(0);
    tab2->setOpacity(0);
    tab3->setOpacity(255);
    rankName3->setColor(Color3B(177,88,8));
    rankName2->setColor(Color3B(255,252,248));
    rankName1->setColor(Color3B(255,252,248));
    ranA->updateRankLayer(GAMEDATA::getInstance()->getLobbyPaiHangData().content3);
}
