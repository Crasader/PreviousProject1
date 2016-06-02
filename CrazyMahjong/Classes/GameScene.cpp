#include "GameScene.h"
#include "BalanceScene.h"

#include "GameFlow.h"
#include "SystemUI.h"

Scene* GameScene::createScene()
{
	Scene* scene = Scene::create();
	Layer* layer = Layer::create();
	GameScene* mahjongScene = GameScene::create();
	CCLOG("Create Scene");
	layer->addChild(mahjongScene);
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 centerPoint = Vec2(visibleSize.width/2, visibleSize.height/2);

	// ×ÀÃæ±³¾°
	Sprite* bkg = Sprite::create("GameBkg.jpg");
	bkg->setPosition(centerPoint);
	this->addChild(bkg);

	// ÓÎÏ·
	GameFlow* gameFlow = GameFlow::create();
	this->addChild(gameFlow);

	return true;
}

void GameScene::GameOver()
{
	_director->replaceScene(GameScene::createScene());
}

