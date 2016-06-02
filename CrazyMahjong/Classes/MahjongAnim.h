#ifndef __MAHJONG_ANIM_H__
#define __MAHJONG_ANIM_H__

#include "cocos2d.h"
USING_NS_CC;
#include "SimpleAudioEngine.h" 

using namespace std;

enum SOUND{
	BGM,
	ADDCOIN,
	BUTTONDOWN,
	FAIL,
	PENGGANG,
	PLAYCARD,
	SHAIZI
};

class MahjongAnim : public Node
{
public:
	CREATE_FUNC(MahjongAnim);
	
	void playSound(SOUND sound);

	static MahjongAnim* getInstance();
	static void updateInstance();


	void playDealShaiZi();

	void playPlayAnim(int type, Vec2 pos);	// �ƶ���
	void playPengAnim(int type, Vec2 pos);
	void playGangAnim(int type, Vec2 pos);

	void playWordGangAnim(Vec2 pos);		// ���ֶ���
	void playWordPengAnim(Vec2 pos);
	void hideWordAnim();

	void playAccountZiMoAnim();
	void playAccountHuAnim();	// ����������
	void playAccountGangKaiAnim();//���ܿ� || ����

	void playWordHuAnim(Vec2 pos);


	void playWinBanner();
	void hideWinBanner();

private:
	bool init();

	bool initDealAnim();
	bool initWordPengGangAnim();

	bool initAccountHuAnim();	// ����������

	bool initAccountPanel();

	bool initPlayPengGangFrames();

	// ���ܵ����ֶ�����d=
	Sprite* animPengGangNode = nullptr;		// ���������
	Animate* animPengGang = nullptr;
	float animPengGangInter = 0.3f;
	float animPengGangTime = .0f;
	float timeShanLight = .3f;						// �����ʱ��
	float timeWordShowWord = 0.4f;			// �ӿ�ʼ���⵽��ʾ���ֵ��¼�
	float timeWordScale = 0.3f;						// ���ַŴ��ʱ�䡣

	Sprite* framePlay = nullptr;				// ����ƵĿ�
	Sprite* framePengGang = nullptr;	// �����ƵĿ�
	static MahjongAnim* instance;

	//���������ܿ���
    Node*	nodeAccountGangKai;

	//������������
	Node* nodeAccountHu = nullptr;

	Sprite* huFlash = nullptr;
	Sprite* huLightPoints = nullptr;
	Sprite* huLightYellow = nullptr;
	Sprite* huCirclePurple = nullptr;
	Sprite* huLightPink = nullptr;
	Sprite* huRing = nullptr;
	Sprite* huShadowCircle = nullptr;
	Animate* animHuLightYellow = nullptr;
	Animate* animHuFlash = nullptr;
	Animate* animHuLightPoints = nullptr;

	//��������������

	// Ӯ����
	Node* nodeWinBanner = nullptr;

	Sprite* winBanner = nullptr;
	Sprite* winManyCoins = nullptr;

	Animate* animBanner = nullptr;
	Animate* animManyCoins = nullptr;

	// ��ɸ��
	Node* nodeDeal = nullptr;
	Sprite* dealShaiZi = nullptr;
	Sprite* dealShaiZiL = nullptr;
	Sprite* dealShaiZiR = nullptr;

	Animate* animShaiZi = nullptr;
	float timeShaiZi = 1.0f;
	float timeShow2ShaiZi = 0.8f;
};

#endif