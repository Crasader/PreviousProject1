#include "PlayerChat.h"
#include "SeatIdUtil.h"

bool PlayerChat::init(){
	if (!Layer::init()){
		return false;
	}
	return true;
}


void PlayerChat::showPlayerChat(PlayerChatType type, int seatId, int infoId){
	if (type == PlayerChatType::image){
		drawFaceImage(seatId, infoId);
	}
	else if (type == PlayerChatType::sound){
		drawSoundInfo(seatId, infoId);
	}
	else{
		drawTextInfo(seatId, infoId);
	}
}

void PlayerChat::drawFaceImage(int seatId, int id){

	auto bob = Sprite::create("chat/face_bob.png");
	this->addChild(bob);
	std::string imageName = cocos2d::String::createWithFormat("chat/face_%d.png", id)->_string;
	auto image = Sprite::create(imageName);
	this->addChild(image);
	if (seatId == ClientSeatId::right){
		bob->setPosition(830,365);
		image->setPosition(830, 367);
	}
	else if (seatId == ClientSeatId::opposite){
		bob->setPosition(830, 365);
		image->setPosition(830, 367);
	}
	else if (seatId == ClientSeatId::left){
		bob->setPosition(830, 365);
		image->setPosition(830, 367);
	}
	else{
		bob->setPosition(0, 0);
		image->setPosition(0, 0);
	}
}


void PlayerChat::drawTextInfo(int seatId, int id){

	auto text = Label::create("hello","Arial",20);
	text->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	this->addChild(text,1);
	auto bob = Scale9Sprite::create("chat/text_bob.png", Rect(0, 0, 31, 38), Rect(5, 0, 6, 38));
	bob->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	bob->setContentSize(Size(text->getBoundingBox().size.width + 10, 38));
	this->addChild(bob);
	if (seatId == ClientSeatId::right){
		bob->setPosition(830, 365);
		text->setPosition(825, 367);
	}
	else if (seatId == ClientSeatId::opposite){
		bob->setPosition(830, 365);
		text->setPosition(825, 367);
	}
	else if (seatId == ClientSeatId::left){
		bob->setPosition(830, 365);
		text->setPosition(825, 367);
	}
	else{
		bob->setPosition(0, 0);
		text->setPosition(0, 0);
	}
}


void PlayerChat::drawSoundInfo(int seatId, int id){


}