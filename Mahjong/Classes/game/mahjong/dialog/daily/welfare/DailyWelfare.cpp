#include "game/mahjong/dialog/daily/welfare/DailyWelfare.h"
#include "game/mahjong/state/GameData.h"
#include "server/NetworkManage.h"

bool DailyWelfare::init(){
	if (!Layer::init()){
		return false;
	}
	showDailyWelfareLayer();
	return true;
}


void DailyWelfare::showDailyWelfareLayer(){
	for (int i = 0; i < 4; i++){
		auto task_bg = Sprite::create("daily/task/content_bg.png");
		task_bg->setPosition(307 + i * 222, 355);
		addChild(task_bg);

		std::string piaoName = cocos2d::String::createWithFormat("daily/task/piao_dai_%d.png", 1)->_string;
		auto piao_dai = Sprite::create(piaoName);
		piao_dai->setPosition(307 + i * 222, 520);
		addChild(piao_dai);

		std::string imageName = cocos2d::String::createWithFormat("daily/task/welfare_title_%d.png", i + 1)->_string;
		auto title = Sprite::create(imageName);
		title->setPosition(307 + i * 222, 525);
		addChild(title);

		std::string contentName;
		if (i == 0){
			contentName = "daily/task/gold_icon_1.png";
		}
		else if (i == 1){
			contentName = "daily/task/bangzhuan.png";
		}
		else if (i == 2){
			contentName = "daily/task/gold_icon_3.png";
		}
		else if (i == 3){
			contentName = "daily/task/gold_icon_2.png";
		}
		auto content = Sprite::create(contentName);
		content->setPosition(307 + i * 222, 430);
		addChild(content);

		std::string prideName;
		if (i == 0){
			prideName = "daily/task/less_than_1000_gold.png";
		}
		else if (i == 1){
			prideName = "daily/task/buzhu_bound_diamond.png";
		}
		else if (i == 2){
			prideName = "daily/task/pride_1w_20.png";
		}
		else if (i == 3){
			prideName = "daily/task/bound_phone_pride.png";
		}
		auto pride = Sprite::create(prideName);
		pride->setPosition(307 + i * 222, 300);
		addChild(pride);	
	}
   
	WelfareData data = GAMEDATA::getInstance()->getWelfareData();
    LabelAtlas* jjjNum = LabelAtlas::create(data.jjj_count,"daily/task/num.png",16,24,'0');
    jjjNum->setPosition(355,276);
    jjjNum->setTag(1000);
    addChild(jjjNum,6);
    if(data.jjj_count == "0"){
        auto text1 = Sprite::create("daily/task/wei_wan_chen.png");
        text1->setPosition(307, 210);
        addChild(text1);
    }else if (data.jjj_count > data.jjj_used){
		auto finish1 = MenuItemImage::create("daily/recieve_btn_1.png", "daily/recieve_btn_2.png", "daily/recieve_btn_3.png",
			CC_CALLBACK_1(DailyWelfare::recievePride, this));
		finish1->setTag(0);
		auto finishMenu1 = Menu::create(finish1, NULL);
		finishMenu1->setPosition(307 , 210);
		addChild(finishMenu1);
	}
	else{
		auto text1 = Sprite::create("daily/task/yilingqu.png");
		text1->setPosition(307, 210);
		addChild(text1);
	}
	if (data.bzjjj_count != data.bzjjj_used){
		auto finish2 = MenuItemImage::create("daily/recieve_btn_1.png", "daily/recieve_btn_2.png", "daily/recieve_btn_3.png",
			CC_CALLBACK_1(DailyWelfare::recievePride, this));
		finish2->setTag(1);
		auto finishMenu2 = Menu::create(finish2, NULL);
		finishMenu2->setPosition(307 + 1 * 222, 210);
		addChild(finishMenu2);
	}
	else{
		auto text2 = Sprite::create("daily/task/yilingqu.png");
		text2->setPosition(307 + 1 * 222, 210);
		addChild(text2);
	}
	if (true){
		auto finish3 = MenuItemImage::create("daily/recieve_btn_1.png", "daily/recieve_btn_2.png", "daily/recieve_btn_3.png",
			CC_CALLBACK_1(DailyWelfare::recievePride, this));
		finish3->setTag(2);
		auto finishMenu3 = Menu::create(finish3, NULL);
		finishMenu3->setPosition(307 + 2 * 222, 210);
		addChild(finishMenu3);
	}
	else{
		auto text3 = Sprite::create("daily/task/yilingqu.png");
		text3->setPosition(307 + 2 * 222, 210);
		addChild(text3);
	}
	if (true){
		auto finish4 = MenuItemImage::create("daily/recieve_btn_1.png", "daily/recieve_btn_2.png", "daily/recieve_btn_3.png",
			CC_CALLBACK_1(DailyWelfare::recievePride, this));
		finish4->setTag(3);
		auto finishMenu4 = Menu::create(finish4, NULL);
		finishMenu4->setPosition(307 + 3 * 222, 210);
		addChild(finishMenu4);
	}
	else{
		auto text4 = Sprite::create("daily/task/yilingqu.png");
		text4->setPosition(307 + 3 * 222, 210);
		addChild(text4);
	}
}

void DailyWelfare::recievePride(Ref* ref){
	MenuItemImage* temp = (MenuItemImage*)ref;
	if (temp->getTag() == 0){
		NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getWelfareJJJ());
	}
	else if (temp->getTag() == 1){
		NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getWelfareBZJJJ());
	}
	else if (temp->getTag() == 2){
		NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getWelfareWx());
	}
	else if (temp->getTag() == 3){
		NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getWelfareMobile());
	}
}

void DailyWelfare::updateData(){


}