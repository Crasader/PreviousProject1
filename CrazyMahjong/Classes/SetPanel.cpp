#include "SetPanel.h"
#include "MahjongAnim.h"

bool SetPanel::init()
{
	if (!Node::init())
	{
		return false;
	}
	this->setVisible(false);

	Sprite* frame = Sprite::create("SetSound/Frame.png");
	this->addChild(frame);

	Button* button = Button::create();
	button->loadTextures("SetSound/Close_0.png", "SetSound/Close_1.png");
	button->addTouchEventListener(this, toucheventselector(SetPanel::hidePanel));
	button->setPosition(Vec2(205.0f, 130.0f));
	this->addChild(button);

	// 滑动条
	Slider* slider = Slider::create();
	slider->loadBarTexture("SetSound/Slider_0.png");
	slider->loadProgressBarTexture("SetSound/Slider_1.png");
	slider->loadSlidBallTextures("SetSound/Block_0.png", "SetSound/Block_1.png");
	slider->addEventListenerSlider(this, sliderpercentchangedselector(SetPanel::slderEvent));
	slider->setPercent(50);
	this->addChild(slider);
	slider->setPosition(Vec2(45.0f, 50.0f));

	Sprite* yinLiang = Sprite::create("SetSound/Sound.png");
	yinLiang->setPosition(Vec2(-150.0f, 50.0f));
	this->addChild(yinLiang);

	// 4个选框
	CheckBox* boxes[4];
	Sprite* sprs[4];
	// 音效
	boxes[0] = CheckBox::create();
	boxes[0]->loadTextures("SetSound/BoxBkg.png", "SetSound/BoxBkg.png", "SetSound/BoxCross.png", "", "");
	boxes[0]->addEventListenerCheckBox(this, checkboxselectedeventselector(SetPanel::boxEventY));
	boxes[0]->setSelected(true);
	this->addChild(boxes[0]);
	sprs[0] = Sprite::create("SetSound/YinXiao.png");
	this->addChild(sprs[0]);

	// 背景音乐
	boxes[1] = CheckBox::create();
	boxes[1]->loadTextures("SetSound/BoxBkg.png", "SetSound/BoxBkg.png", "SetSound/BoxCross.png", "", "");
	boxes[1]->addEventListenerCheckBox(this, checkboxselectedeventselector(SetPanel::boxEventB));
	boxes[1]->setSelected(true);
	this->addChild(boxes[1]);
	sprs[1] = Sprite::create("SetSound/BkgSound.png");
	this->addChild(sprs[1]);

	// 震动
	boxes[2] = CheckBox::create();
	boxes[2]->loadTextures("SetSound/BoxBkg.png", "SetSound/BoxBkg.png", "SetSound/BoxCross.png", "", "");
	boxes[2]->addEventListenerCheckBox(this, checkboxselectedeventselector(SetPanel::boxEventZ));
	this->addChild(boxes[2]);
	sprs[2] = Sprite::create("SetSound/ZhenDong.png");
	this->addChild(sprs[2]);

	// 省电
	boxes[3] = CheckBox::create();
	boxes[3]->loadTextures("SetSound/BoxBkg.png", "SetSound/BoxBkg.png", "SetSound/BoxCross.png", "", "");
	boxes[3]->addEventListenerCheckBox(this, checkboxselectedeventselector(SetPanel::boxEventS));
	this->addChild(boxes[3]);
	sprs[3] = Sprite::create("SetSound/ShengDian.png");
	this->addChild(sprs[3]);

	float w = 180.0f;
	float h = 60.0f;
	Vec2 startPos = Vec2(-30.0f, -70.0f);

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			int index = i * 2 + j;
			Vec2 pos = Vec2(w * i, h * j) + startPos;
			boxes[index]->setPosition(pos);
			sprs[index]->setPosition(pos + Vec2(-80.0f, .0f));
		}
	}

	this->setPosition(400.0f, 240.0f);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(SetPanel::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void SetPanel::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (EventKeyboard::KeyCode::KEY_BACKSPACE == keyCode)
	{
		btn->setEnabled(true);
		this->runAction(Sequence::create(ScaleTo::create(time, .0f), [this](){
			this->setVisible(false);
		}, NULL));
	}
}

void SetPanel::slderEvent(Ref* pSender, SliderEventType type)
{
	if (type == SLIDER_PERCENTCHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(pSender);
		float percent = slider->getPercent();
		float volume = percent * .01f;
		CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volume);
		CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(volume);
	}
}

// 四个选择框，
void SetPanel::boxEventS(Ref* pSender, SliderEventType type)	//省电
{
	MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);

}

void SetPanel::boxEventB(Ref* pSender, SliderEventType type)	//背景音乐
{
	MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);
	switch (type)
	{
	case CHECKBOX_STATE_EVENT_SELECTED:
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();

		break;
	}
	case CHECKBOX_STATE_EVENT_UNSELECTED:
	{
											CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		break;
	}
	}
}

void SetPanel::boxEventY(Ref* pSender, SliderEventType type)	//音效
{
	MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);
	switch (type)
	{
	case CHECKBOX_STATE_EVENT_SELECTED:
	{
										  float volume = CocosDenshion::SimpleAudioEngine::getInstance()->getBackgroundMusicVolume();
										  CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(volume);
										  break;
	}
	case CHECKBOX_STATE_EVENT_UNSELECTED:
	{
											CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(.0f);
											break;
	}
	}
}

void SetPanel::boxEventZ(Ref* pSender, SliderEventType type)	// 震动
{
	MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);

}

//显示隐藏设置面板
void SetPanel::showPanel()
{

	this->setScale(.0f);
	this->setVisible(true);
	this->runAction(ScaleTo::create(time, 1.0f));
}
void SetPanel::hidePanel(Ref* pSender, TouchEventType type)
{
	btn->setEnabled(true);
	this->runAction(Sequence::create(ScaleTo::create(time, .0f), [this](){
		this->setVisible(false); 
	}, NULL));
}