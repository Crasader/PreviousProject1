#include"game/mahjong/core/MjGameScene.h"
#include"game/mahjong/core/MahjongView.h"

bool MjGameScene::init(){
	if (!Scene::init()){
		return false;
	}
	MahjongView* mjView = MahjongView::create();
	this->addChild(mjView);
	return true;
}