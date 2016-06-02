#include "BalanceScene.h"

#include "GameScene.h"
#include "HeadPortrait.h"

Scene* BalanceScene::createScene()
{
	Scene* scene = Scene::create();
	Layer* layer = Layer::create();
	BalanceScene* node = BalanceScene::create();

	scene->addChild(layer);
	layer->addChild(node);
	return scene;
}

// MahjongScene::create�����init����ʼ���Լ�
bool BalanceScene::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	// ���汳��
	Sprite* bkg = Sprite::create("GameBkg.jpg");
	bkg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(bkg);
	
	//// ͷ��
	//Node* headPortraitNode = HeadPortrait::createHeadProtrait();
	//this->addChild(headPortraitNode);

	// run
	if (nullptr == _director->getRunningScene())
	{
		_director->runWithScene(GameScene::createScene());
	}
	else
	{
		_director->replaceScene(GameScene::createScene());
	}

	return true;
}

