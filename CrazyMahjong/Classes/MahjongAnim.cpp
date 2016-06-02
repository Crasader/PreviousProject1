#include "MahjongAnim.h"
#include "Card.h"
#include "MahjongEvent.h"

MahjongAnim* MahjongAnim::instance = nullptr;

void MahjongAnim::playSound(SOUND sound)
{
	switch (sound)
	{
	case BGM:
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sound/bgm.mp3", true);
		break;
	case ADDCOIN:
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/AddCoins.ogg");
		break;
	case BUTTONDOWN:
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/ButtonDown.ogg");
		break;
	case FAIL:
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/Fail.ogg");
		break;
	case PENGGANG:
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/PengGang.wav");
		break;
	case PLAYCARD:
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/PlayCard.mp3");
		break;
	case SHAIZI:
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/ShaiZi.wav");
	default:
		break;
	}
}


bool MahjongAnim::init()
{
	auto audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();

	audioEngine->preloadBackgroundMusic("Sound/bgm.mp3");
	audioEngine->setBackgroundMusicVolume(.5f);
	audioEngine->preloadEffect("Sound/AddCoins.ogg");
	audioEngine->preloadEffect("Sound/ButtonDown.ogg");
	audioEngine->preloadEffect("Sound/Fail.ogg");
	audioEngine->preloadEffect("Sound/PengGang.wav");
	audioEngine->preloadEffect("Sound/PlayCard.mp3");
	audioEngine->preloadEffect("Sound/ShaiZi.wav");

	if (!Node::init())
	{
		return false;
	}

	if (!initAccountHuAnim())
	{
		return false;
	}
	if (!initDealAnim())
	{
		return false;
	}

	if (!initPlayPengGangFrames())
	{
		return false;
	}

	if (!initWordPengGangAnim())
	{
		return false;
	}


	if (!initAccountPanel())
	{
		return false;
	}

	return true;
}

MahjongAnim* MahjongAnim::getInstance()
{
	if (nullptr == instance)
	{
		instance = new (std::nothrow) MahjongAnim();
		instance->init();
	}
	
	return instance;
}

void MahjongAnim::updateInstance()
{
	if (nullptr != instance)
	{
		CC_SAFE_DELETE(instance);
	}
}

//------------------------------------------ 初始打碰杠 -------------------------------------------------------------
bool MahjongAnim::initPlayPengGangFrames()
{
	CCLOG("initAnim : PengGang");

	framePlay = Sprite::create("MJAnim/PlayCard/CardFrame_0.png");
	if (nullptr == framePlay){ return false; }
	Card* PlayedCard = Card::createShowCard();
	PlayedCard->setTag(0);
	PlayedCard->setPosition(75.0f, 105.0f);
	framePlay->addChild(PlayedCard);
	framePlay->setVisible(false);
	this->addChild(framePlay);


	//
	framePengGang = Sprite::create("MJAnim/PlayCard/CardFrame_1.png");
	if (nullptr == framePengGang){ return false; }
	for (int index = 0; index < 4; ++index)
	{
		Card* pengGangCard = Card::createPengGangCard(); 
		pengGangCard->setTag(index);
		pengGangCard->setPositionY(55.0f);
		framePengGang->addChild(pengGangCard);
	}
	framePengGang->setVisible(false);
	this->addChild(framePengGang);
	// debug
	//playGangAnim(1, Vec2(300.0f, 300.0f));
	return true;
}
bool MahjongAnim::initWordPengGangAnim()
{
	CCLOG("initAnim : wordPengGang");

	// 创建图片

	animPengGangNode = Sprite::create("MJAnim/PengGang/light_6.png");
	animPengGangNode->setVisible(false);

	Sprite* wordSpr = Sprite::create("MJAnim/PengGang/word_gang.png");
	wordSpr->ignoreAnchorPointForPosition(true);
	wordSpr->setVisible(false);
	animPengGangNode->addChild(wordSpr);
	animPengGangNode->setPosition(200.0f, 200.0f);
	this->addChild(animPengGangNode);

	// 增加图片资源[碰][杠][6张light]
	CC_RETURNF_IF(!addToTextureCache("MJAnim/PengGang/", "light", 7));

	CC_RETURNF_IF(!addToTextureCache("MJAnim/PengGang/", "word_gang"));

	CC_RETURNF_IF(!addToTextureCache("MJAnim/PengGang/", "word_peng"));

	CC_RETURNF_IF(!addToTextureCache("", "menu_hu"));

	// 添加动画资源
	animPengGang = createAnimateFromTextureCache("light", 7, timeShanLight);
	return true;
}
//------------------------------------------ 播放打碰杠 -------------------------------------------------------------
//--------------打
void MahjongAnim::playPlayAnim(int type, Vec2 pos)
{
	auto card = framePlay->getChildByTag(0);
	((Card*)card)->changeCard(type);
	framePlay->setPosition(pos);
	framePlay->setVisible(true);
	framePlay->setScale(.2f);
	framePlay->runAction(Sequence::create(ScaleTo::create(.2f, 1.0f), 
		DelayTime::create(0.3f), 
		ScaleTo::create(.2f, .0f),
		NULL));
}
//--------------碰
void MahjongAnim::playPengAnim(int type, Vec2 pos)
{
	framePengGang->setScale(1.0f);
	framePengGang->setTexture("MJAnim/PlayCard/CardFrame_1.png");
	framePengGang->getChildByTag(3)->setVisible(false);
	for (int index = 0; index < 3; ++index)
	{
		auto pengGangCard = ((Card*)framePengGang->getChildByTag(index));
		pengGangCard->setPositionX(38.0f + index * 28.0f);
		pengGangCard->changeCard(type);
	}
	framePengGang->setPosition(pos);
	framePengGang->setVisible(true);
	framePengGang->runAction(Sequence::create(DelayTime::create(1.0f), ScaleTo::create(.15f, .0f), Hide::create(), NULL));

}
void MahjongAnim::playWordPengAnim(Vec2 pos)
{
	CCLOG("playAnim : wordPeng");
	playSound(SOUND::PENGGANG);

	if (animPengGangNode && animPengGang)
	{
		animPengGangNode->setVisible(true);
		animPengGangNode->setPosition(pos);
		animPengGangNode->runAction(animPengGang->clone());

		scheduleOnce([&](float dt){
			Texture2D* tex = getTexFromeCache("word_peng");
			if (!tex){ CCLOG("Error : get tex"); }
			auto sp = ((Sprite*)animPengGangNode->getChildren().at(0));
			sp->setTexture(tex);
			sp->setVisible(true);
			sp->setScale(3.0f); 

			//sp->setOpacity(0.0f);
			// 缩小放大
			auto scaleSmall = ScaleTo::create(timeWordScale * 0.7, 1.0f);
			auto scaleBig = ScaleTo::create(timeWordScale * 0.3, 1.3f);
			auto smallAndBig = Sequence::create(scaleSmall, scaleBig, NULL);
			
			// 透明变化
			auto opacity = FadeIn::create(timeWordScale * 0.5f);

			auto act = Spawn::create(opacity, smallAndBig, NULL);
			sp->runAction(act);
		}, timeWordShowWord, "wordpeng");
		scheduleOnce([&](float dt){this->hideWordAnim(); }, 1.0f, "hide");
	}
	else
	{
		CCLOG("Failed : playWordPengAnim ! \r\n");
	}
}
//--------------杠
void MahjongAnim::playGangAnim(int type, Vec2 pos)
{
	framePengGang->setScale(1.0f);
	framePengGang->setTexture("MJAnim/PlayCard/CardFrame_2.png");
	framePengGang->getChildByTag(3)->setVisible(true);
	for (int index = 0; index < 4; ++index)
	{
		auto card = ((Card*)framePengGang->getChildByTag(index));
		card->setPositionX(41.0f + index * 29.0f);
		card->changeCard(type);
	}
	framePengGang->setPosition(pos);
	framePengGang->setVisible(true);
	framePengGang->runAction(Sequence::create(DelayTime::create(3.0f), ScaleTo::create(.15f, .0f), Hide::create(), NULL));

}
void MahjongAnim::playWordGangAnim(Vec2 pos)
{
	playSound(SOUND::PENGGANG);

		if (animPengGangNode && animPengGang)
		{
			animPengGangNode->setVisible(true);
			animPengGangNode->setPosition(pos);
			animPengGangNode->runAction(animPengGang->clone());

			scheduleOnce([&](float dt){
				Texture2D* tex = getTexFromeCache("word_gang");
				if (!tex){ CCLOG("Error : get tex"); }
				auto sp = ((Sprite*)animPengGangNode->getChildren().at(0));
				sp->setTexture(tex);
				sp->setVisible(true);
				sp->setScale(3.0f);

				//sp->setOpacity(0.0f);
				// 缩小放大
				auto scaleSmall = ScaleTo::create(timeWordScale * 0.7, 1.0f);
				auto scaleBig = ScaleTo::create(timeWordScale * 0.3, 1.3f);
				auto smallAndBig = Sequence::create(scaleSmall, scaleBig, NULL);

				// 透明变化
				auto opacity = FadeIn::create(timeWordScale * 0.5f);

				auto act = Spawn::create(opacity, smallAndBig, NULL);
				sp->runAction(act);
			}, timeWordShowWord, "wordgang");
			scheduleOnce([&](float dt){this->hideWordAnim(); }, 1.0f, "hide");
		}
		else
		{
			CCLOG("Failed : playWordPengAnim ! \r\n");
		}
}

void MahjongAnim::playWordHuAnim(Vec2 pos)
{
		if (animPengGangNode && animPengGang)
		{
			animPengGangNode->setVisible(true);
			animPengGangNode->setPosition(pos);
			animPengGangNode->runAction(animPengGang->clone());

			scheduleOnce([&](float dt){
				Texture2D* tex = getTexFromeCache("menu_hu");
				if (!tex){ CCLOG("Error : get tex"); }
				auto sp = ((Sprite*)animPengGangNode->getChildren().at(0));
				sp->setTexture(tex);
				sp->setVisible(true);
				sp->setScale(3.0f);

				//sp->setOpacity(0.0f);
				// 缩小放大
				auto scaleSmall = ScaleTo::create(timeWordScale * 0.7, 1.0f);
				auto scaleBig = ScaleTo::create(timeWordScale * 0.3, 1.3f);
				auto smallAndBig = Sequence::create(scaleSmall, scaleBig, NULL);

				// 透明变化
				auto opacity = FadeIn::create(timeWordScale * 0.5f);

				auto act = Spawn::create(opacity, smallAndBig, NULL);
				sp->runAction(act);
			}, timeWordShowWord, "menu_hu");
			scheduleOnce([&](float dt){this->hideWordAnim(); }, 3.0f, "hide");
		}
		else
		{
			CCLOG("Failed : playWordHuAnim ! \r\n");
		}
}

//--------------Hide
void MahjongAnim::hideWordAnim()
{
	CCLOG("----------HIde-------------");
	animPengGangNode->runAction(FadeOut::create(0.3f));
	animPengGangNode->getChildren().at(0)->runAction(FadeOut::create(0.3f));
}


//------------------------------------------ 结算【胡】【自摸】【抢杠】 -------------------------------------------------------------
//------------------------------------------ 胡&&点炮 -------------------------------------------------------------
bool MahjongAnim::initAccountHuAnim()	
{// flash_6, lightPoints_2, lightYellow_2, circlePurple, lightPink, ring, shadowCircle
	nodeAccountHu = Node::create();
	nodeAccountHu->setVisible(false);
	this->addChild(nodeAccountHu);

	std::string path = "MJAnim/Account/Hu/";
	//huShadowCircle = addAnimNoAnimte(*nodeAccountHu, path, "shadowCircle");

	huFlash = addAnimWithAnimate(*nodeAccountHu, animHuFlash, path, "flash", 7, timeShanLight);
	huCirclePurple = addAnimNoAnimte(*nodeAccountHu, path, "circlePurple");

	huLightPink = addAnimNoAnimte(*nodeAccountHu, path, "lightPink");
	huLightYellow = addAnimWithAnimate(*nodeAccountHu, animHuLightYellow, path, "lightYellow", 3, timeShanLight);

	huRing = addAnimNoAnimte(*nodeAccountHu, path, "ring");
	huLightPoints = addAnimWithAnimate(*nodeAccountHu, animHuLightPoints, path, "lightPoints", 3, timeShanLight);

	CCLOG("Finish InitAccount : Hu \r\n");
	return true;
}
void MahjongAnim::playAccountHuAnim()
{
	nodeAccountHu->setVisible(true);
	nodeAccountHu->setPosition(Vec2(400.0f, 400.0f));

	huFlash->runAction( animHuFlash->clone());

	huLightPink->runAction(ScaleTo::create(0.5f, 1.3f));
	huCirclePurple->runAction(ScaleTo::create(0.5f, 1.3f));
	huLightYellow->runAction(ScaleTo::create(0.5f, 1.3f));
	huLightPoints->runAction(ScaleTo::create(0.5f, 1.3f));
	huRing->runAction(ScaleTo::create(0.5f, 1.3f));

	huLightPoints->runAction(RepeatForever::create(animHuLightPoints->clone()));
	huLightYellow->runAction(RepeatForever::create(animHuLightYellow->clone()));

	playWordHuAnim(Vec2(413.0f, 400.0f));
	nodeAccountHu->runAction(Sequence::create(DelayTime::create(3.0f), ScaleTo::create(.3f, .0f), RemoveSelf::create(), NULL));
}
void MahjongAnim::playAccountZiMoAnim()
{
	nodeAccountHu->setVisible(true);
	nodeAccountHu->setPosition(Vec2(400.0f, 400.0f));

	huFlash->runAction(animHuFlash->clone());

	huLightPink->runAction(ScaleTo::create(0.5f, 1.3f));
	huCirclePurple->runAction(ScaleTo::create(0.5f, 1.3f));
	huLightYellow->runAction(ScaleTo::create(0.5f, 1.3f));
	huLightPoints->runAction(ScaleTo::create(0.5f, 1.3f));
	huRing->runAction(ScaleTo::create(0.5f, 1.3f));

	huLightPoints->runAction(RepeatForever::create(animHuLightPoints->clone()));
	huLightYellow->runAction(RepeatForever::create(animHuLightYellow->clone()));

	playWordHuAnim(Vec2(413.0f, 400.0f));
	nodeAccountHu->runAction(Sequence::create(DelayTime::create(3.0f), ScaleTo::create(.3f, .0f), RemoveSelf::create(), NULL));
}
void MahjongAnim::playAccountGangKaiAnim()
{
	nodeAccountHu->setVisible(true);
	nodeAccountHu->setPosition(Vec2(400.0f, 400.0f));

	huFlash->runAction(animHuFlash->clone());

	huLightPink->runAction(ScaleTo::create(0.5f, 1.3f));
	huCirclePurple->runAction(ScaleTo::create(0.5f, 1.3f));
	huLightYellow->runAction(ScaleTo::create(0.5f, 1.3f));
	huLightPoints->runAction(ScaleTo::create(0.5f, 1.3f));
	huRing->runAction(ScaleTo::create(0.5f, 1.3f));

	huLightPoints->runAction(RepeatForever::create(animHuLightPoints->clone()));
	huLightYellow->runAction(RepeatForever::create(animHuLightYellow->clone()));

	playWordHuAnim(Vec2(413.0f, 400.0f));
	nodeAccountHu->runAction(Sequence::create(DelayTime::create(3.0f), ScaleTo::create(.3f, .0f), RemoveSelf::create(), NULL));
}

//---------------------------------------------------------------------------
bool MahjongAnim::initAccountPanel()
{
	// Banner[15], CoinAnim[29]
	nodeWinBanner = Node::create();
	nodeWinBanner->setVisible(false);
	this->addChild(nodeWinBanner);

	std::string path = "MJAnim/AccountPanel/";

	winBanner = addAnimWithAnimate(*nodeWinBanner, animBanner, path, "Banner", 15, 1.0f);
	winBanner->ignoreAnchorPointForPosition(true);
	winBanner->setPosition(160.0f, 330.0f);

	winManyCoins = addAnimNoAnimte(*nodeWinBanner, path, "CoinOne");
	winManyCoins->ignoreAnchorPointForPosition(true);
	winManyCoins->setPosition(0.0f, 0.0f);
	CCLOG("Finish InitAccount : AccountPanel \r\n");
	return true;
}
void MahjongAnim::playWinBanner()
{
	nodeWinBanner->setVisible(true);

	winBanner->runAction(animBanner->clone());
	winManyCoins->runAction(Sequence::create(DelayTime::create(2.0f), Hide::create(),  NULL));
}

void MahjongAnim::hideWinBanner()
{
	nodeWinBanner->setVisible(false);
}


//------------------------发牌筛子
bool MahjongAnim::initDealAnim()
{//ShaiZiAnim_10, ShaiZi_5
	nodeDeal = Node::create();
	nodeDeal->setVisible(false);
	this->addChild(nodeDeal);

	std::string path = "MJAnim/DealCard/";

	dealShaiZi = addAnimWithAnimate(*nodeDeal, animShaiZi, path, "ShaiZiAnim", 11, timeShaiZi);
	dealShaiZi->setPosition(400.0f, 240.0f);

	addToTextureCache(path, "ShaiZi", 6);
	
	dealShaiZiL = Sprite::create();
	dealShaiZiL->setPosition(365.0f, 180.0f);
	dealShaiZiL->setOpacity(.0f);
	nodeDeal->addChild(dealShaiZiL);

	dealShaiZiR = Sprite::create();
	dealShaiZiR->setPosition(435.0f, 180.0f);
	dealShaiZiR->setOpacity(.0f);
	nodeDeal->addChild(dealShaiZiR);

	CCLOG("Finish InitDeal : ShaiZi \r\n");
	return true;
}
void MahjongAnim::playDealShaiZi()
{
	playSound(SOUND::SHAIZI);
	nodeDeal->setVisible(true);

	dealShaiZi->setVisible(true);
	dealShaiZi->runAction(animShaiZi->clone());
	std::string name = "MJAnim/DealCard/ShaiZi_";

	std::string strL = name + String::createWithFormat("%d", random<int>(0, 5))->_string + ".png";
	dealShaiZiL->setTexture(strL);
	dealShaiZiL->setOpacity(.0f);

	std::string strR = name + String::createWithFormat("%d", random<int>(0, 5))->_string + ".png";
	dealShaiZiR->setTexture(strR);
	dealShaiZiR->setOpacity(.0f);
	
	scheduleOnce([&](float dt){
		dealShaiZiL->runAction(FadeIn::create(0.2f));
		dealShaiZiR->runAction(FadeIn::create(0.2f));
		dealShaiZi->setVisible(false);
	}, 0.9f, "hee");

	scheduleOnce([&](float dt){nodeDeal->setVisible(false); }, 1.3f, "hideeee");
}
