#include "game/mahjong/dialog/prompt/PromptDialog.h"
#include "game/mahjong/state/GameData.h"
#include "game/utils/Chinese.h"
#include "server/NetworkManage.h"
bool PromptDialog::init(){
	if (!BaseDialog::init()){
		return false;
	}
	setDialogType(-1);
	return true;
}

void PromptDialog::drawDialog(){
	auto dialogBg = Sprite::create("common/dialog_bg_small.png");
	dialogBg->setPosition(640, 360);
	this->addChild(dialogBg);

	auto title = Sprite::create("common/tishi_icon.png");
	title->setPosition(640, 500);
	this->addChild(title);

    auto thishiBg = Sprite::create("common/thishi_bg.png");
    thishiBg->setPosition(640, 375);
    addChild(thishiBg);
    
	auto close = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png",
		CC_CALLBACK_0(PromptDialog::closeView, this));
	auto closeMenu = Menu::create(close, NULL);
	closeMenu->setPosition(860, 490);
	this->addChild(closeMenu);

	auto confirm = MenuItemImage::create("common/user_box_confirm_a.png", "common/user_box_confirm_b.png",
		CC_CALLBACK_0(PromptDialog::clickComfirm, this));
	auto confirmMenu = Menu::create(confirm, NULL);
	confirmMenu->setPosition(640, 240);
	this->addChild(confirmMenu);
}


void PromptDialog::setTextInfo(int type){
	setDialogType(type);
	if (type == 0){
		FriendOpenRoomNotifyData data = GAMEDATA::getInstance()->getFriendOpenRoomNotify();
		std::string context = ChineseWord("haoyou") + data.nickname+ "," + ChineseWord("yaoqing") + "." + ChineseWord("tongyi") + "!";
		Label* text1 = Label::create(context, "Arial", 20);
		text1->setDimensions(240, 200);
		text1->setAlignment(TextHAlignment::CENTER);
		text1->setPosition(640, 300);
		text1->setAnchorPoint(Point::ANCHOR_MIDDLE);
		this->addChild(text1);
	}
	else if (type == 1){
		Label* text = Label::create(ChineseWord("zuoman") + "!", "Arial", 20);
		text->setPosition(640, 330);
		this->addChild(text);
	}
	else{
		Label* text = Label::create("socket lost connect", "Arial", 20);
		text->setPosition(640, 330);
		this->addChild(text);
	}
}

std::string PromptDialog::myWrap(std::string str, int length)
{
	unsigned int beginPos = 0;
	std::string resultStr;

	std::vector<std::string > str_vec;
	do
	{
		str_vec.push_back(str.substr(beginPos, length));
		if (beginPos + length > str.size())
		{
			break;
		}
		else
		{
			beginPos += length;
		}

	} while (true);

	for (unsigned int i = 0; i < str_vec.size(); ++i)
	{
		resultStr.append(str_vec.at(i)).append("\n");
	}
	resultStr.pop_back(); 
	return resultStr;
}


void PromptDialog::clickComfirm(){
	if (getDialogType() == 0){
		FriendOpenRoomNotifyData data = GAMEDATA::getInstance()->getFriendOpenRoomNotify();
		NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getEnterFriendRoomCommand(data.pid));
		removeFromParent();
	}
}