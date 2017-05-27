//
//  HongbaoAnim.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/5/27.
//
//

#include "mahjong/result/hongbao/HongbaoAnim2.hpp"


bool HongbaoAnim2::init(){
    if(!Layer::init()){
        return false;
    }
    auto anim = Sprite::create("hongbao/hongbao_amin_bg.png");
    anim->setPosition(640,360);
    addChild(anim);
    initView("0.9","0.9");
    return true;
}


void HongbaoAnim2::initView(std::string hongNum,std::string hongNum2){
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
    
    
    //红包主体
    auto hongbao = Sprite::create("hongbao/hongbao_1.png");
    hongbao->setPosition(320,910);
    addChild(hongbao,1);
    
    hongbao->setScaleY(0.9);
    hongbao->setRotation(10);
    
    auto step_1_1 = MoveTo::create(0.3f, Point(320,380));
    
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
    
    auto lightBg = Sprite::create("hongbao/hongbao_light_1.png");
    lightBg->setPosition(320,380);
    lightBg->setVisible(false);
    addChild(lightBg,2);
    lightBg->runAction(Sequence::create(DelayTime::create(1.0f),CallFunc::create([=](){lightBg->setVisible(true);}),Spawn::create(ScaleTo::create(0.5f, 2),FadeTo::create(0.5f,0),NULL), NULL));
    
    auto rotateLight = Sprite::create("hongbao/rotate_light.png");
    rotateLight->setPosition(320,360);
    addChild(rotateLight);
    rotateLight->runAction(Sequence::create(DelayTime::create(1.0f),CallFunc::create([=](){lightBg->setVisible(true);}),Repeat::create(RotateTo::create(100,3000), CC_REPEAT_FOREVER),NULL));
    
    auto circleBg = Sprite::create("hongbao/circle.png");
    circleBg->setPosition(320,380);
    circleBg->setVisible(false);
    circleBg->setScale(0.3);
    addChild(circleBg,3);
    circleBg->runAction(Sequence::create(DelayTime::create(1.0f),CallFunc::create([=](){circleBg->setVisible(true);}),Spawn::create(ScaleTo::create(0.5f, 2),FadeTo::create(0.5f,0),NULL), NULL));
    
    auto hongbao2 = Sprite::create("hongbao/hongbao_2.png");
    hongbao2->setPosition(320,380);
    hongbao2->setVisible(false);
    addChild(hongbao2,1);
    hongbao2->runAction(Sequence::create(DelayTime::create(1.0f),CallFunc::create([=](){hongbao2->setVisible(true);}),NULL));
    
    int pos  =   hongNum.find(".");
    hongNum.replace(pos, pos, ":");
    auto hongbaoNum = LabelAtlas::create(hongNum,"hongbao/shu_zi.png",34,49,'0');
    hongbaoNum->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    hongbaoNum->setPosition(370,450);
    hongbaoNum->setVisible(false);
    addChild(hongbaoNum,1);
    hongbaoNum->runAction(Sequence::create(DelayTime::create(1.0f),CallFunc::create([=](){hongbaoNum->setVisible(true);}),NULL));
    
    //红包主体2
    auto hongbao3 = Sprite::create("hongbao/hongbao_1.png");
    hongbao3->setPosition(960,910);
    addChild(hongbao3,1);
    
    hongbao3->setScaleY(0.9);
    hongbao3->setRotation(10);
    
    auto step_1_10 = MoveTo::create(0.3f, Point(960,380));
    
    auto step_1_2_10 = Spawn::create(ScaleTo::create(0.1, 1),RotateTo::create(0.1,0), NULL);
    auto step_1_2_20 = Spawn::create(ScaleTo::create(0.1, 1.0,0.9),RotateTo::create(0.1,-10), NULL);
    auto step_1_2_30 = Spawn::create(ScaleTo::create(0.1, 1),RotateTo::create(0.1,5), NULL);
    auto step_1_2_40 = CallFunc::create([=](){
        hongbao3->setScaleY(1);
        hongbao3->setRotation(0);
    });
    auto setp_1_20 = Sequence::create(step_1_2_10,step_1_2_20,step_1_2_30,step_1_2_40, NULL);
    
    auto setp_10 = Spawn::create(step_1_10, setp_1_20,NULL);
    
    auto step_2_10 = ScaleTo::create(0.15, 1.0f,1.05f);
    auto step_2_20 = ScaleTo::create(0.15, 1.0f,0.9f);
    auto step_2_30 = ScaleTo::create(0.15, 1.0f,1.05f);
    auto step_2_40 = ScaleTo::create(0.15, 1.0f);
    
    auto step_20 = Sequence::create(step_2_10,step_2_20,step_2_30,step_2_40, NULL);
    
    auto fianlSetp0 = Sequence::create(setp_10,step_20, NULL);
    
    hongbao3->runAction(fianlSetp0);
    
    auto lightBg0 = Sprite::create("hongbao/hongbao_light_1.png");
    lightBg0->setPosition(960,380);
    lightBg0->setVisible(false);
    addChild(lightBg0,2);
    lightBg0->runAction(Sequence::create(DelayTime::create(1.0f),CallFunc::create([=](){lightBg0->setVisible(true);}),Spawn::create(ScaleTo::create(0.5f, 2),FadeTo::create(0.5f,0),NULL), NULL));
    
    auto rotateLight0 = Sprite::create("hongbao/rotate_light.png");
    rotateLight0->setPosition(960,360);
    addChild(rotateLight0);
    rotateLight0->runAction(Sequence::create(DelayTime::create(1.0f),CallFunc::create([=](){lightBg0->setVisible(true);}),Repeat::create(RotateTo::create(100,3000), CC_REPEAT_FOREVER),NULL));
    
    auto circleBg0 = Sprite::create("hongbao/circle.png");
    circleBg0->setPosition(960,380);
    circleBg0->setVisible(false);
    circleBg0->setScale(0.3);
    addChild(circleBg0,3);
    circleBg0->runAction(Sequence::create(DelayTime::create(1.0f),CallFunc::create([=](){circleBg0->setVisible(true);}),Spawn::create(ScaleTo::create(0.5f, 2),FadeTo::create(0.5f,0),NULL), NULL));
    
    auto hongbao20 = Sprite::create("hongbao/hongbao_2.png");
    hongbao20->setPosition(960,380);
    hongbao20->setVisible(false);
    addChild(hongbao20,1);
    hongbao20->runAction(Sequence::create(DelayTime::create(1.0f),CallFunc::create([=](){hongbao20->setVisible(true);}),NULL));
    
    int pos0  =   hongNum2.find(".");
    hongNum2.replace(pos0, pos0, ":");
    auto hongbaoNum0 = LabelAtlas::create(hongNum2,"hongbao/shu_zi.png",34,49,'0');
    hongbaoNum0->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    hongbaoNum0->setPosition(1010,450);
    hongbaoNum0->setVisible(false);
    addChild(hongbaoNum0,1);
    hongbaoNum0->runAction(Sequence::create(DelayTime::create(1.0f),CallFunc::create([=](){hongbaoNum0->setVisible(true);}),NULL));
    
    
    if(hongNum2 == hongNum){
        auto title = Sprite::create("hongbao/shuang_xi.png");
        title->setPosition(-220,660);
        addChild(title);
        title->runAction(MoveTo::create(0.5, Point(640,660)));
        
        auto text = Sprite::create("hongbao/shuang_xi_text.png");
        text->setPosition(-200,600);
        addChild(text);
        text->runAction(MoveTo::create(0.5, Point(640,600)));
        
    }
    
    auto back = MenuItemImage::create("hongbao/hongbao_anim_back.png","hongbao/hongbao_anim_back.png",CC_CALLBACK_0(HongbaoAnim2::goBack, this));
    auto menu1 = Menu::create(back,NULL);
    menu1->setPosition(450,100);
    addChild(menu1);
    menu1->setVisible(false);
     menu1->runAction(Sequence::create(DelayTime::create(1.0f),CallFunc::create([=](){menu1->setVisible(true);}),NULL));
    
    auto sha = MenuItemImage::create("hongbao/share.png","hongbao/share.png",CC_CALLBACK_0(HongbaoAnim2::share, this));
    auto menu2 = Menu::create(sha,NULL);
    menu2->setPosition(750,100);
    addChild(menu2);
    menu2->setVisible(false);
    menu2->runAction(Sequence::create(DelayTime::create(1.0f),CallFunc::create([=](){menu2->setVisible(true);}),NULL));

}


void HongbaoAnim2::goBack(){
    removeFromParent();
    
}


void HongbaoAnim2::share(){
    
    
}





