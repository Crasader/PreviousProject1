#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "game/mahjong/dialog/friend/SearchResult.h"
USING_NS_CC;
USING_NS_CC_EXT;


class FriendAddView : public Layer, public EditBoxDelegate{
public:
	virtual bool init();
	virtual void onEnter() override;
	virtual void onExit() override;
	CREATE_FUNC(FriendAddView);

private:
    Sprite* searchSprite;
    Sprite* quickSpite;
    Layer* tabLayer1;
    Layer* tabLayer2;
    Menu* wxMenu;
    Sprite* wxText;
    EditBox* _editName;
    EditBox* _number;
    Sprite* hintInfo;
    EventListenerCustom* friendSearchListener;
    MenuItemToggle* searchToggle;
    MenuItemToggle* quickToggle;
    EditBox* searchContent;

    
	void showDialog();
	void closeView();
	void clickTabBtn(Ref* ref);
    void clickSearch();
	void clickWeChat();
	void quickAdd();
	void addCustomEventlistener();

	virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox);

	virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox);

	virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text);

	virtual void editBoxReturn(cocos2d::extension::EditBox* editBox);
};