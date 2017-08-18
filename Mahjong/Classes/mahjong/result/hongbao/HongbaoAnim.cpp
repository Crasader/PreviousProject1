//
//  HongbaoAnim.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/5/27.
//
//

#include "mahjong/result/hongbao/HongbaoAnim.hpp"
#include "wechat/android/CallAndroidMethod.h"
#include "wechat/ios/CallIOSMethod.h"
#include "server/NetworkManage.h"
#include "mahjong/lobby/LobbyScene.h"
#include "mahjong/common/widget/HeadImage.hpp"
#include "http/image/UrlImageMannger.h"


bool HongbaoAnim::init(){
    if(!Layer::init()){
        return false;
    }
    auto anim = Sprite::create("hongbao/hongbao_amin_bg.png");
    anim->setPosition(640,360);
    addChild(anim);
    return true;
}


void HongbaoAnim::initView(std::string hongNum,int type){
    setHongBaoNum(hongNum);
    //红包主体
    auto hongbao = Sprite::create("hongbao/hongbao_1.png");
    hongbao->setPosition(640,910);
    addChild(hongbao,1);
    
    
    //    hongbao->addChild(myTitle);
    
    hongbao->setScaleY(0.9);
    hongbao->setRotation(10);
    
    auto step_1_1 = MoveTo::create(0.3f, Point(640,380));
    
    auto step_1_2_1 = Spawn::create(ScaleTo::create(0.1, 1),RotateTo::create(0.1,0), NULL);
    auto step_1_2_2 = Spawn::create(ScaleTo::create(0.1, 1.0,0.9),RotateTo::create(0.1,-10), NULL);
    auto step_1_2_3 = Spawn::create(ScaleTo::create(0.1, 1),RotateTo::create(0.1,5), NULL);
    auto step_1_2_4 = CallFunc::create([=](){
        hongbao->setScaleY(1);
        hongbao->setRotation(0);
    });
    auto setp_1_2 = Sequence::create(step_1_2_1,step_1_2_2,step_1_2_3,step_1_2_4, NULL);
    
    auto setp_1 = Spawn::create(step_1_1, setp_1_2,NULL);
    
    auto step_2_1 = ScaleTo::create(0.15, 1.0f,1.05f);
    auto step_2_2 = ScaleTo::create(0.15, 1.0f,0.9f);
    auto step_2_3 = ScaleTo::create(0.15, 1.0f,1.05f);
    auto step_2_4 = ScaleTo::create(0.15, 1.0f);
    
    auto step_2 = Sequence::create(step_2_1,step_2_2,step_2_3,step_2_4, NULL);
    
    auto fianlSetp = Sequence::create(setp_1,step_2, NULL);
    
    hongbao->runAction(fianlSetp);
    for (int i=0; i<1000; i++) {
        //飘带
        auto piao = Sprite::create();
        std::string name =StringUtils::format("hongbao/pao_%d.png",random(1,8));
        piao->setVisible(false);
        piao->setTexture(name);
        piao->setPosition(random(80,1200),random(680,720));
        addChild(piao,2);
        piao->runAction(Sequence::create(DelayTime::create(1.0f+random(0, 100)),CallFunc::create([=](){piao->setVisible(true);}),Spawn::create(MoveTo::create(0.5f,Point(piao->getPositionX(),piao->getPositionY()-150)),FadeTo::create(0.5f,0),NULL), NULL));
    }
    
    auto lightBg = Sprite::create("hongbao/hongbao_light_1.png");
    lightBg->setPosition(640,380);
    lightBg->setVisible(false);
    addChild(lightBg,2);
    lightBg->runAction(Sequence::create(DelayTime::create(1.0f),CallFunc::create([=](){lightBg->setVisible(true);}),Spawn::create(ScaleTo::create(0.5f, 2),FadeTo::create(0.5f,0),NULL), NULL));
    
    auto rotateLight = Sprite::create("hongbao/rotate_light.png");
    rotateLight->setPosition(640,360);
    addChild(rotateLight);
    rotateLight->runAction(Sequence::create(DelayTime::create(1.0f),CallFunc::create([=](){lightBg->setVisible(true);}),Repeat::create(RotateTo::create(100,3000), CC_REPEAT_FOREVER),NULL));
    
    auto circleBg = Sprite::create("hongbao/circle.png");
    circleBg->setPosition(640,380);
    circleBg->setVisible(false);
    circleBg->setScale(0.3);
    addChild(circleBg,3);
    circleBg->runAction(Sequence::create(DelayTime::create(1.0f),CallFunc::create([=](){circleBg->setVisible(true);}),Spawn::create(ScaleTo::create(0.5f, 2),FadeTo::create(0.5f,0),NULL), NULL));
    
    auto hongbao2 = Sprite::create("hongbao/hongbao_2.png");
    hongbao2->setPosition(640,380);
    hongbao2->setVisible(false);
    addChild(hongbao2,1);
    hongbao2->runAction(Sequence::create(DelayTime::create(1.0f),CallFunc::create([=](){hongbao2->setVisible(true);}),NULL));
    auto myTitle = Sprite::create();
    if(type == 1){
        myTitle->setTexture("hongbao/wz_dyj.png");
    }else if(type == 2){
        myTitle->setTexture("hongbao/wz_dsj.png");
    }else if(type == 3){
        myTitle->setTexture("hongbao/hui_gui_text.png");
    }else{
        myTitle->setTexture("hongbao/wz_fangzhu.png");
    }
    myTitle->setPosition(120,110);
    hongbao2->addChild(myTitle);
    
    int pos  = (int)hongNum.find(".");
    if(pos>=0){
        hongNum.replace(pos,1,":");
    }
    
    auto hongbaoNum = LabelAtlas::create(hongNum,"hongbao/shu_zi.png",34,49,'0');
    hongbaoNum->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    hongbaoNum->setPosition(690,450);
    hongbaoNum->setVisible(false);
    addChild(hongbaoNum,1);
    hongbaoNum->runAction(Sequence::create(DelayTime::create(1.0f),CallFunc::create([=](){hongbaoNum->setVisible(true);}),NULL));
    
    auto back = MenuItemImage::create("hongbao/hongbao_anim_back.png","hongbao/hongbao_anim_back.png",CC_CALLBACK_0(HongbaoAnim::goBack, this));
    if(true){
        auto imge = Sprite::create("hongbao/give_up_1.png");
        back->setNormalImage(imge);
        auto imge2 = Sprite::create("hongbao/give_up_2.png");
        back->setSelectedImage(imge2);
    }
    auto menu1 = Menu::create(back,NULL);
    menu1->setPosition(450,100);
    addChild(menu1);
    menu1->setVisible(false);
    menu1->runAction(Sequence::create(DelayTime::create(1.0f),CallFunc::create([=](){menu1->setVisible(true);}),NULL));
    
    auto sha = MenuItemImage::create("hongbao/share.png","hongbao/share.png",CC_CALLBACK_0(HongbaoAnim::share, this));
    if(true){
        auto imge3 = Sprite::create("hongbao/share_btn_1.png");
        sha->setNormalImage(imge3);
        auto imge4 = Sprite::create("hongbao/share_btn_2.png");
        sha->setSelectedImage(imge4);
    }
    auto menu2 = Menu::create(sha,NULL);
    menu2->setPosition(750,100);
    addChild(menu2);
    menu2->setVisible(false);
    menu2->runAction(Sequence::create(DelayTime::create(1.0f),CallFunc::create([=](){menu2->setVisible(true);}),NULL));
    
    auto title = Sprite::create();
    if(type == 1){
        title->setTexture("hongbao/da_yin_jia.png");
    }else if(type == 2){
        title->setTexture("hongbao/da_shu_jia.png");
    }else if(type == 3){
        title->setTexture("hongbao/hui_gui_title.png");
    }else{
        title->setTexture("hongbao/fang_zhu.png");
    }
    title->setPosition(-220,660);
    addChild(title);
    title->runAction(Sequence::create(DelayTime::create(2.0f),MoveTo::create(0.5, Point(640,660)), NULL));
    
}


void HongbaoAnim::goBack(){
    GAMEDATA::getInstance()->setHasShowHongbaoResult(true);
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendGiveupHongbaoPride());
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, LobbyScene::create()));
    
}


void HongbaoAnim::share(){
    GAMEDATA::getInstance()->setHasShowHongbaoResult(true);
    auto hbLayer = Layer::create();
    
    if(GAMEDATA::getInstance()->getDaYingJiaPic()== ""){
        int num = random(0,3);
        if(num ==0){
            auto hongbaobg = Sprite::create("share/share_bg_1.jpg");
            hongbaobg->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
            hongbaobg->setPosition(0,0);
            hbLayer->addChild(hongbaobg);
            
            auto headImage = HeadImage::createByImage(UserData::getInstance()->getPicture(),Size(150,150));
            headImage->setPosition(360, 530);
            hbLayer->addChild(headImage, 10);
            
            auto nick = Label::createWithSystemFont(UserData::getInstance()->getNickName(),"arial",36);
            nick->setPosition(360,425);
            hbLayer->addChild(nick);
            
            std::string number = getHongBaoNum();
            int pos  =  (int)number.find(".");
            if(pos>=0){
                number.replace(pos,1, ":");
            }
            
            LabelAtlas* hongnum = LabelAtlas::create(number, "share/hongbao_num.png",54,94, '0');
            hongnum->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
            hongnum->setPosition(455,730);
            hbLayer->addChild(hongnum);
            
        }
        else if(num == 1){
            auto hongbaobg = Sprite::create("share/share_bg_2.jpg");
            hongbaobg->setPosition(360,640);
            hbLayer->addChild(hongbaobg);
            
            auto headImage = HeadImage::createByImage(UserData::getInstance()->getPicture(),Size(150,150));
            headImage->setPosition(165, 635);
            hbLayer->addChild(headImage, 10);
            
            auto nick = Label::createWithSystemFont(UserData::getInstance()->getNickName(),"arial",40);
            nick->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
            nick->setColor(Color3B(5,90,107));
            nick->setPosition(255,590);
            hbLayer->addChild(nick);
            
            Label* hongnum = Label::createWithSystemFont(getHongBaoNum(), "arial",100);
            hongnum->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
            hongnum->setColor(Color3B(237,82,86));
            hongnum->setPosition(370,440);
            hbLayer->addChild(hongnum);
            
        }else if(num == 2){
            auto hongbaobg = Sprite::create("share/share_bg_3.jpg");
            hongbaobg->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
            hongbaobg->setPosition(0,0);
            hbLayer->addChild(hongbaobg);
            
            Label* hongnum = Label::createWithSystemFont(getHongBaoNum(), "arial",90);
            hongnum->setAnchorPoint(Point::ANCHOR_MIDDLE);
            hongnum->setColor(Color3B(255,90,84));
            hongnum->setPosition(360,420);
            hbLayer->addChild(hongnum);
            
        }else {
            auto hongbaobg = Sprite::create("share/share_bg_4.jpg");
            hongbaobg->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
            hongbaobg->setPosition(0,0);
            hbLayer->addChild(hongbaobg);
            
            auto gongxi = Label::createWithSystemFont(StringUtils::format("恭喜%s在",UserData::getInstance()->getNickName().c_str()),"arial",36);
            gongxi->setColor(Color3B::WHITE);
            gongxi->setAnchorPoint(Point::ANCHOR_MIDDLE);
            gongxi->setPosition(360,590);
            hbLayer->addChild(gongxi);
            
            auto pride = Label::createWithSystemFont(StringUtils::format("好友房游戏中成为大赢家,奖励"),"arial",36);
            pride->setColor(Color3B::WHITE);
            pride->setAnchorPoint(Point::ANCHOR_MIDDLE);
            pride->setPosition(360,530);
            hbLayer->addChild(pride);
            
            Label* hongnum = Label::createWithSystemFont(getHongBaoNum(), "arial",50);
            hongnum->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
            hongnum->setColor(Color3B::WHITE);
            hongnum->setPosition(395,360);
            hbLayer->addChild(hongnum);
        }
        
        auto renderTexture = RenderTexture::create(720,1280, Texture2D::PixelFormat::RGBA8888);
        //清空并开始获取
        renderTexture->beginWithClear(0.0f, 0.0f, 0.0f, 0.0f);
        //遍历场景节点对象，填充纹理到RenderTexture中
        hbLayer->visit();
        //结束获取
        renderTexture->end();
        //保存文件
        std::string outputFile =StringUtils::format("%smahjong_screen_shot.png",FileUtils::getInstance()->getWritablePath().c_str());
        renderTexture->saveToFile("mahjong_screen_shot.png",Image::Format::PNG);
        schedule([=](float dt){
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            CallAndroidMethod::getInstance()->shareSDCardImageToWeChat(outputFile, true);
#endif
            
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            CallIOSMethod::getInstance()->doWechatShareImg(outputFile, 1);
#endif
        }, 0, 0, 0.2f, "mmp");
    }else{
       UrlImageMannger::getInstance()->downloadShareImageByUrl(GAMEDATA::getInstance()->getDaYingJiaPic(),true);
    }
    setVisible(false);
}




