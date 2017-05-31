//
//  CompetitionResult.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/5/22.
//
//

#include "mahjong/common/competition/CompetitionResult.hpp"
#include "mahjong/common/competition/CompetitonLayer.hpp"
#include "mahjong/common/widget/ParticleUtil.hpp"
#include "mahjong/lobby/LobbyScene.h"
#include "server/NetworkManage.h"
#include "wechat/android/CallAndroidMethod.h"
#include "wechat/ios/CallIOSMethod.h"
#include "mahjong/lobby/shop/fangka/FangkaNotEnoughDialog.hpp"

bool CompetitionResult::init(){
    if(!Layer::init()){
        return false;
    }
    auto reslut_bg = Sprite::create("result/result_bg.jpg");
    reslut_bg->setPosition(640, 360);
    addChild(reslut_bg,-1);
    GAMEDATA::getInstance()->setIsCompetitionState(false);
    return true;
}

void CompetitionResult::showCompetiotionResult(std::string type,std::string rank,std::string pride,std::string score){
    if(rank == "1"){
        showWin(type, rank, pride, score);
    }else{
        showLose(type, rank, pride, score);
    }
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

void CompetitionResult::showWin(std::string type,std::string rank,std::string pride,std::string score){
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
    rankNum->setPosition(640,388);
    rankNum->setVisible(false);
    addChild(rankNum);
    auto setp03 = DelayTime::create(1.6f);
    auto setp04 = CallFunc::create([=](){rankNum->setVisible(true);});
    auto setp05 = ScaleTo::create(0.4, 1.0f);
    rankNum->runAction(Sequence::create(setp03,setp04,setp05,NULL));
    
    //    auto kuohao =Sprite::create("competition/kuohao.png");
    //    kuohao->setPosition(720,360);
    //    kuohao->setOpacity(0);
    //    addChild(kuohao);
    auto icon = Sprite::create("mjitem/jifen_icon.png");
    addChild(icon);
    icon->setPosition(680,360);
    icon->setScale(0.6f);
    icon->setOpacity(0);
    LabelAtlas* jifen;
    int sco = atoi(score.c_str());
    if(sco>=0){
        jifen = LabelAtlas::create(StringUtils::format(":%d",sco),"competition/score_num_1.png",22,30,'0');
        
    }else{
        jifen = LabelAtlas::create(StringUtils::format(":%d",abs(sco)),"competition/score_num_2.png",22,30,'0');
    }
    jifen->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    jifen->setPosition(690,360);
    jifen->setOpacity(0);
    addChild(jifen);
    auto setp06 = DelayTime::create(1.8f);
    //    auto setp07_1 = Spawn::create(MoveTo::create(0.3,Point(840,360)),FadeTo::create(0.3, 255) ,NULL);
    auto setp07_2 = Spawn::create(MoveTo::create(0.3,Point(800,360)),FadeTo::create(0.3, 255) ,NULL);
    auto setp07_3 = Spawn::create(MoveTo::create(0.3,Point(810,360)),FadeTo::create(0.3, 255) ,NULL);
    //    kuohao->runAction(Sequence::create(setp06,setp07_1, NULL));
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
    huaPride->setAnchorPoint(Point::ANCHOR_MIDDLE);
    huaPride->setScale(0.24);
    huaPride->setOpacity(0);
    huaPride->setPosition(640,190);
    addChild(huaPride,1);
    auto setp0_1 = DelayTime::create(2.3f);
    auto setp0_2 = Spawn::create(FadeTo::create(0.3f,255),ScaleTo::create(0.3f,1.2f),NULL);
    auto setp0_3 = ScaleTo::create(0.2f,1.0f);
    huaPride->runAction(Sequence::create(setp0_1,setp0_2,setp0_3, NULL));
    auto yuan = Sprite::create("competition/pride_quan_yuan.png");
    yuan->setScale(0.24);
    yuan->setOpacity(0);
    yuan->setPosition(730,170);
    addChild(yuan,2);
    auto setp0_4 = DelayTime::create(2.3f);
    auto setp0_5 = Spawn::create(FadeTo::create(0.3f,255),ScaleTo::create(0.3f,1.2f),NULL);
    auto setp0_6 = ScaleTo::create(0.2f,1.0f);
    yuan->runAction(Sequence::create(setp0_4,setp0_5,setp0_6, NULL));
    auto huaNum = LabelAtlas::create(pride,"competition/pride_quan_num.png",64,84,'0');
    huaNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
    huaNum->setScale(0.24);
    huaNum->setOpacity(0);
    huaNum->setPosition(645,190);
    addChild(huaNum,2);
    auto setp0_7 = DelayTime::create(2.3f);
    auto setp0_8 = Spawn::create(FadeTo::create(0.3f,255),ScaleTo::create(0.3f,1.2f),NULL);
    auto setp0_9 = ScaleTo::create(0.2f,1.0f);
    huaNum->runAction(Sequence::create(setp0_7,setp0_8,setp0_9, NULL));
}

void CompetitionResult::showLose(std::string type,std::string rank,std::string pride,std::string score){
    
    auto title1 = Sprite::create("competition/title_fail.png");
    title1->setPosition(640,600);
    addChild(title1,3);
    
    
    auto congratulation = Sprite::create("competition/yi_han.png");
    congratulation->setPosition(640,480);
    addChild(congratulation);
    
    auto name = Sprite::create();
    name->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    if(type == "1" ||type == "2" ){
        name->setTexture("competition/shanghai_qiaoma.png");
    }else{
        name->setTexture("competition/hongzhong.png");
    }
    addChild(name);
    
    auto num = LabelAtlas::create(pride, "competition/huafei_zhi.png", 26, 44, '0');
    num->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(num);
    auto huafei = Sprite::create("competition/haufei_text.png");
    huafei->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(huafei);
    int wid = name->getContentSize().width+num->getContentSize().width+huafei->getContentSize().width;
    name->setPosition(640-wid/2,482);
    num->setPosition(640-wid/2+name->getContentSize().width,482);
    huafei->setPosition(640-wid/2+name->getContentSize().width+num->getContentSize().width,482);
    
    auto rankText = Sprite::create("competition/rank_text.png");
    rankText->setPosition(640,375);
    addChild(rankText);
    
    auto rankNum = LabelAtlas::create(rank, "competition/rank_num.png", 98, 124, '0');
    rankNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
    rankNum->setPosition(640,388);
    addChild(rankNum);
    
    auto kuohao =Sprite::create("competition/kuohao.png");
    kuohao->setPosition(840,360);
    addChild(kuohao);
    auto icon = Sprite::create("mjitem/jifen_icon.png");
    icon->setPosition(800,360);
    icon->setScale(0.6f);
    addChild(icon);
    auto jifen = LabelAtlas::create(StringUtils::format(":%s",score.c_str()),"competition/score_num_1.png",22,30,'0');
    jifen->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    jifen->setPosition(810,360);
    addChild(jifen);
    
    auto light = Sprite::create("competition/light_bg.png");
    light->setPosition(640,240);
    addChild(light);
    
    auto prideText = Sprite::create("competition/wu_jiang_li.png");
    prideText->setPosition(640,260);
    addChild(prideText);
    
    auto huaPride = Sprite::create("competition/zai_jie_zai_li.png");
    huaPride->setAnchorPoint(Point::ANCHOR_MIDDLE);
    huaPride->setPosition(640,190);
    addChild(huaPride,1);
    
}

void CompetitionResult::continueCompetition(){
    GAMEDATA::getInstance()->setPrivateLezi(StringUtils::format("%d", LeziType::type55c));
    FriendOpenRoomRespData opdata;
    opdata.prjushu = "4";
    GAMEDATA::getInstance()->setFriendOpenRoomResp(opdata);
    //    CompetitonLayer* lay = CompetitonLayer::create();
    //    lay->initView((CompetitionRoomId)atoi(GAMEDATA::getInstance()->getCompetitionId().c_str()),GAMEDATA::getInstance()->getCompetitionPride(),GAMEDATA::getInstance()->getCompetitionRule(),GAMEDATA::getInstance()->getCompetitionFee());
    //    getParent()->addChild(lay,5);
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendJoinCompetiotnCommand(StringUtils::format("%s",GAMEDATA::getInstance()->getCompetitionId().c_str())));
    
}


void CompetitionResult::onEnter(){
    Layer::onEnter();
    joinResp = EventListenerCustom::create(MSG_JOIN_COMPETITION_RESP, [=](EventCustom* event){
        JoinCompetitionData* result = static_cast<JoinCompetitionData*>(event->getUserData());
        JoinCompetitionData newData = *result;
        if(newData.result == 1){
            GAMEDATA::getInstance()->setMahjongRoomType(MahjongRoom::privateRoom);
            GAMEDATA::getInstance()->setCompetitionId(newData.roomId);
            GAMEDATA::getInstance()->setCompetitionText(newData.text);
            GAMEDATA::getInstance()->setCompetitionNumber(newData.num);
            if(atoi(newData.roomId.c_str()) == CompetitionRoomId::Shanghai_High||atoi(newData.roomId.c_str()) == CompetitionRoomId::Shanghai_Normal){
                GAMEDATA::getInstance()->setIsCompetitionQueue(true);
                GAMEDATA::getInstance()->setGameType(1);
                Director::getInstance()->replaceScene(TransitionFade::create(0.1, MjGameScene::create()));
            }else{
                GAMEDATA::getInstance()->setIsCompetitionQueue(true);
                GAMEDATA::getInstance()->setGameType(3);
                Director::getInstance()->replaceScene(TransitionFade::create(0.1, MjGameScene::create()));
            }
        }else{
            if(NULL != getChildByTag(1024)){
                getChildByTag(1024)->removeFromParentAndCleanup(true);
            }
            FangkaNotEnoughDialog* da =  FangkaNotEnoughDialog::create();
            if(GAMEDATA::getInstance()->getCompetitionId() == StringUtils::format("%d",CompetitionRoomId::Shanghai_High)||
               GAMEDATA::getInstance()->getCompetitionId() == StringUtils::format("%d",CompetitionRoomId::Hongzhong_High)){
                da->initView(5,24);
                
            }else{
                da->initView(5,1);
            }
            addChild(da);
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(joinResp, 1);
    
}

void CompetitionResult::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(joinResp);
}

void CompetitionResult::quit(){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getQuitRoomCommand());
    Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::create()));
}


void CompetitionResult::share(){
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string path =StringUtils::format("%s/mahjong_screen_shot.png",CallAndroidMethod::getInstance()->getSdCardDir().c_str());
    log("screenShot path = %s",path.c_str());
    utils::captureScreen(CC_CALLBACK_2(CompetitionResult::afterCaptured, this) ,path);
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    std::string path =StringUtils::format("%smahjong_screen_shot.png",FileUtils::sharedFileUtils()->getWritablePath().c_str());
    log("screenShot path = %s",path.c_str());
    utils::captureScreen(CC_CALLBACK_2(CompetitionResult::afterCaptured, this) ,path);
#endif
}

void CompetitionResult::afterCaptured(bool succeed, const std::string &outputFile)
{
    if (succeed) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        CallAndroidMethod::getInstance()->shareImageToWeChat("mahjong_screen_shot.png", false);
#endif
        
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        CallIOSMethod::getInstance()->doWechatShareImg(outputFile, 0);
#endif
    }
}







