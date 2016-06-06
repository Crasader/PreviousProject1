#pragma once
#include "cocos2d.h"
#include "game/mahjong/splash/SplashScene.h"
USING_NS_CC;


	class DropDownList : public CCLayer
	{
	public:

		DropDownList(Sprite* label, Size size);

		~DropDownList();


		static DropDownList* create(Sprite* label, Size size);
		 
		void onEnter();


		virtual bool onTouchBegan(CCTouch *touch, CCEvent *event);

		virtual bool emptyTouch(CCTouch *touch, CCEvent *event){ return true; };

		void addLabel(std::string label);


		void onSelected(Object* sender);


		void onClose();

		void setLoginscene(SplashScene*scene);
	private:
		CCMenu* mainMenu;

		Sprite* showLabel;

		std::vector<std::string> selectLabels;
		std::vector<Sprite*> selectSpriteFrame; 

		bool isShowMenu;

		Sprite*bgFrame; 
		int lastSelectedIndex; 
		SplashScene* _loginscene;
	};
