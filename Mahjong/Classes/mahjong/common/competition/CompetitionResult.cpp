//
//  CompetitionResult.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/5/22.
//
//

#include "mahjong/common/competition/CompetitionResult.hpp"
#include "mahjong/common/widget/ParticleUtil.hpp"

bool CompetitionResult::init(){
    if(!Layer::init()){
        return false;
    }
    auto reslut_bg = Sprite::create("result/result_bg.jpg");
    reslut_bg->setPosition(640, 360);
    addChild(reslut_bg,-1);
    return true;
}

void CompetitionResult::showCompetiotionResult(std::string type,std::string rank,std::string pride,std::string score){
    
    auto title1 = Sprite::create("competition/shi_dai_1.png");
    title1->setPosition(640,600);
    addChild(title1,3);
    title1->setOpacity(77);
    title1->setScale(0.8);
    auto step1 = Spawn::create(FadeTo::create(0.1f, 255),ScaleTo::create(0.1f, 1.44f,1.0f),NULL);
    auto step2 = ScaleTo::create(0.1f, 0.8f,1.0f);
    auto step3 = ScaleTo::create(0.1f, 1.0f);
    title1 -> runAction(Sequence::create(step1,step2,step3, NULL));
    
    auto title2 = Sprite::create("competition/shi_dai_2.png");
    title2->setPosition(640,600);
    addChild(title2,2);
    title2->setOpacity(77);
    title2->setScale(0.8);
    title2->setVisible(false);
    auto step2_1 = DelayTime::create(0.1f);
    auto step2_2 = CallFunc::create([=](){
        title2->setVisible(true);
    });
    auto step2_3 = Spawn::create(FadeTo::create(0.1f, 255),ScaleTo::create(0.1f, 1.44f,1.0f),NULL);
    auto step2_4 = ScaleTo::create(0.1f, 0.8f,1.0f);
    auto step2_5 = ScaleTo::create(0.1f, 1.0f);
    title2->runAction(Sequence::create(step2_1,step2_2,step2_3,step2_4,step2_5, NULL));
    
    auto title3 = Sprite::create("competition/shi_dai_3.png");
    title3->setPosition(640,600);
    addChild(title3,1);
    title3->setOpacity(77);
    title3->setVisible(false);
    auto step3_1 = DelayTime::create(0.3f);
    auto step3_2 =  CallFunc::create([=](){
        title3->setVisible(true);
        auto gold = ParticleUtil::create(MyParticleType::goldOnly);
        addChild(gold,7);
    });
    auto step3_3 = FadeTo::create(0.1f, 255);
    title3 -> runAction(Sequence::create(step3_1,step3_2,step3_3, NULL));
    
    auto winText = Sprite::create("competition/win_text_1.png");
    winText->setPosition(640,600);
    addChild(winText,5);
    winText->setVisible(false);
    winText->setScale(1.5f);
    winText->setOpacity(77);
    auto step4_1 = DelayTime::create(0.2f);
    auto step4_2 =  CallFunc::create([=](){winText->setVisible(true);});
    auto step4_3 = Spawn::create(FadeTo::create(0.1f, 255),ScaleTo::create(0.1f,0.8),NULL);
    auto step4_4 = ScaleTo::create(0.1f, 1.0f);
    winText -> runAction(Sequence::create(step4_1,step4_2,step4_3,step4_4, NULL));
    
    auto winText2 = Sprite::create("competition/win_text_1.png");
    winText2->setPosition(640,600);
    addChild(winText2,6);
    winText2->setVisible(false);
    winText2->setScale(1.16f);
    winText2->setColor(Color3B(125,125,125));
    auto step5_1 = DelayTime::create(0.4f);
    auto step5_2 =  CallFunc::create([=](){winText2->setVisible(true);});
    auto step5_3 = Spawn::create(TintTo::create(0.2f, 255, 255, 255),ScaleTo::create(0.2f,2.37),NULL);
    auto step5_4 = CallFunc::create([=](){winText2->setVisible(false);});
    winText2 -> runAction(Sequence::create(step5_1,step5_2,step5_3,step5_4, NULL));
    
    auto congratulation = Sprite::create("competition/congratulation_text.png");
    congratulation->setPosition(640,480);
    addChild(congratulation);
    congratulation->setVisible(false);
    congratulation->setOpacity(0);
    auto setp6_1 = DelayTime::create(1.0f);
    auto setp6_2 = CallFunc::create([=](){congratulation->setVisible(true);});
    auto setp6_3 = FadeTo::create(0.2, 255);
    congratulation->runAction(Sequence::create(setp6_1,setp6_2,setp6_3,NULL));
    
    auto name = Sprite::create();
    name->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    if(type == "1" ||type == "2" ){
        name->setTexture("competition/shanghai_qiaoma.png");
    }else{
        name->setTexture("competition/hongzhong.png");
    }
    name->setOpacity(0);
    name->setScale(0.64);
    addChild(name);
    auto num = LabelAtlas::create(pride, "competition/huafei_zhi.png", 26, 44, '0');
    num->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    num->setOpacity(0);
    num->setScale(0.64);
    addChild(num);
    auto huafei = Sprite::create("competition/haufei_text.png");
    huafei->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    huafei->setOpacity(0);
    huafei->setScale(0.64);
    addChild(huafei);
    int wid = name->getContentSize().width+num->getContentSize().width+huafei->getContentSize().width;
    name->setPosition(640-wid/2*0.64,528);
    num->setPosition(640-wid/2*0.64+name->getContentSize().width*0.64,528);
    huafei->setPosition(640-wid/2*0.64+name->getContentSize().width*0.64+num->getContentSize().width*0.64,528);
    auto setp01 = DelayTime::create(1.2);
    auto setp02_0 = Spawn::create(ScaleTo::create(0.3, 1.0f),FadeTo::create(0.3,255),MoveTo::create(0.3, Point(640-wid/2,482)),NULL);
    auto setp02_1 = Spawn::create(ScaleTo::create(0.3, 1.0f),FadeTo::create(0.3,255),MoveTo::create(0.3, Point(640-wid/2+name->getContentSize().width,482)),NULL);
    auto setp02_2 = Spawn::create(ScaleTo::create(0.3, 1.0f),FadeTo::create(0.3, 255),MoveTo::create(0.3, Point(640-wid/2+name->getContentSize().width+num->getContentSize().width,482)),NULL);
    name->runAction(Sequence::create(setp01, setp02_0,NULL));
    num->runAction(Sequence::create(setp01, setp02_1,NULL));
    huafei->runAction(Sequence::create(setp01, setp02_2,NULL));
    
    auto rankText = Sprite::create("competition/rank_text.png");
    rankText->setPosition(640,375);
    addChild(rankText);
    rankText->setVisible(false);
    rankText->setOpacity(0);
    auto setp7_1 = DelayTime::create(1.5f);
    auto setp7_2 = CallFunc::create([=](){rankText->setVisible(true);});
    auto setp7_3 = FadeTo::create(0.1, 255);
    rankText->runAction(Sequence::create(setp7_1,setp7_2,setp7_3,NULL));
    
    auto rankNum = LabelAtlas::create(rank, "competition/rank_num.png", 98, 124, '0');
    rankNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
    rankNum->setScale(1.54);
    rankNum->setVisible(false);
    addChild(rankNum);
    auto setp03 = DelayTime::create(1.6f);
    auto setp04 = CallFunc::create([=](){rankNum->setVisible(true);});
    auto setp05 = ScaleTo::create(0.4, 1.0f);
    rankNum->runAction(Sequence::create(setp03,setp04,setp05,NULL));
    
    auto kuohao =Sprite::create("competition/kuohao.png");
    kuohao->setPosition(720,360);
    kuohao->setOpacity(0);
    addChild(kuohao);
    auto icon = Sprite::create("mjitem/jifen_icon.png");
    addChild(icon);
    icon->setPosition(680,360);
    icon->setScale(0.6f);
    icon->setOpacity(0);
    auto jifen = LabelAtlas::create(":1000","competition/score_num_1.png",22,30,'0');
    jifen->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    jifen->setPosition(690,360);
    jifen->setOpacity(0);
    addChild(jifen);
    auto setp06 = DelayTime::create(1.8f);
    auto setp07_1 = Spawn::create(MoveTo::create(0.3,Point(840,360)),FadeTo::create(0.3, 255) ,NULL);
    auto setp07_2 = Spawn::create(MoveTo::create(0.3,Point(800,360)),FadeTo::create(0.3, 255) ,NULL);
    auto setp07_3 = Spawn::create(MoveTo::create(0.3,Point(810,360)),FadeTo::create(0.3, 255) ,NULL);
    kuohao->runAction(Sequence::create(setp06,setp07_1, NULL));
    icon->runAction(Sequence::create(setp06,setp07_2, NULL));
    jifen->runAction(Sequence::create(setp06,setp07_3, NULL));
    
    auto light = Sprite::create("competition/light_bg.png");
    addChild(light);
    light->setPosition(640,240);
    light->setVisible(false);
    auto setp8_1 = DelayTime::create(2.7f);
    auto setp8_2 = CallFunc::create([=](){light->setVisible(true);});
    auto rota = Repeat::create(Sequence::create(CallFunc::create([=](){
        light->setRotation(15);
    }),DelayTime::create(0.5f),CallFunc::create([=](){
        light->setRotation(0);
    }),DelayTime::create(0.5f),NULL),CC_REPEAT_FOREVER);
    light->runAction(Sequence::create(setp8_1,setp8_2,rota,NULL));
    
    auto prideText = Sprite::create("competition/pride_text.png");
    prideText->setPosition(640,260);
    addChild(prideText);
    prideText->setVisible(false);
    prideText->setOpacity(0);
    auto setp9_1 = DelayTime::create(2.0f);
    auto setp9_2 = CallFunc::create([=](){prideText->setVisible(true);});
    auto setp9_3 = Spawn::create(FadeTo::create(0.3f,255),MoveTo::create(0.3f,Point(640,290)),NULL);
    prideText->runAction(Sequence::create(setp9_1,setp9_2,setp9_3,NULL));
    
    auto huaPride = Sprite::create("competition/pride_quan_bg.png");
    huaPride->setScale(0.24);
    huaPride->setOpacity(0);
    huaPride->setPosition(640,210);
    auto setp0_1 = DelayTime::create(2.3f);
    auto setp0_2 = Spawn::create(FadeTo::create(0.3f,255),ScaleTo::create(0.3f,1.2f),NULL);
    auto setp0_3 = ScaleTo::create(0.2f,1.2f);
    huaPride->runAction(Sequence::create(setp0_1,setp0_2,setp0_3, NULL));
    
    auto quitImage = MenuItemImage::create("result/quit_btn_1.png","result/quit_btn_1.png",CC_CALLBACK_0(CompetitionResult::quit,this));
    
    auto helpImage = MenuItemImage::create("result/xuan_yao_btn_1.png","result/xuan_yao_btn_2.png",
                                           CC_CALLBACK_0(CompetitionResult::share, this));
    auto feedImage = MenuItemImage::create("competition/continiue_btn_1.png","competition/continiue_btn_2.png",
                                           CC_CALLBACK_0(CompetitionResult::continueCompetition, this));
    auto menu = Menu::create(quitImage,helpImage,feedImage,NULL);
    menu->alignItemsHorizontallyWithPadding(60);
    menu->setPosition(640,60);
    addChild(menu);
    
}

void CompetitionResult::share(){
    
}


void CompetitionResult::quit(){
    
}

void CompetitionResult::continueCompetition(){
    
}







