#include"MjGameScene.h"
#include"MahjongView.h"

bool MjGameScene::init(){
	if (!Scene::init()){
		return false;
	}
	MahjongView* mjView = MahjongView::create();
	this->addChild(mjView);
	return true;
}
