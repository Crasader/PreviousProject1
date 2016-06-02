#include "MahjongDatas.h"

#include "cocos2d.h"
USING_NS_CC;

MahjongDatas* MahjongDatas::instance = nullptr;

MahjongDatas::MahjongDatas()
{
}

int MahjongDatas::getCardNum()
{
	return cardsTong.size() + cardsWan.size();
}

void MahjongDatas::initGoodType()
{
	goodCard = 1 > random<float>(0, 1) ? TONG : WAN;
}

// 初始化所有 麻将牌面
void MahjongDatas::initData()
{
	CCLOG("MahjongDatas : initData");
	// 添加牌，36筒，36万，每样4张
	if (0 < cardsTong.size())
	{
		cardsTong.clear();
	}
	vector<int> cardsRes;
	for (int i = 0; i < 4; i++)
	{
		cardsRes.push_back(1);
		cardsRes.push_back(2);
		cardsRes.push_back(3);
		cardsRes.push_back(4);
		cardsRes.push_back(5);
		cardsRes.push_back(6);
		cardsRes.push_back(7);
		cardsRes.push_back(8);
		cardsRes.push_back(9);
	}
	for (int i = 0; i < 36; i++)
	{
		int size = cardsRes.size() - 1;
		int index = random<int>(0, size);
		int type = cardsRes.at(index);
		cardsTong.push_back(type);
		cardsRes.erase( find(cardsRes.begin(), cardsRes.end(), type) );
	} 
	// 添加牌，36万，每样4张
	if (0 < cardsTong.size())
	{
		cardsWan.clear();
	}
	for (int i = 0; i < 4; i++)
	{
		cardsRes.push_back(-1);
		cardsRes.push_back(-2);
		cardsRes.push_back(-3);
		cardsRes.push_back(-4);
		cardsRes.push_back(-5);
		cardsRes.push_back(-6);
		cardsRes.push_back(-7);
		cardsRes.push_back(-8);
		cardsRes.push_back(-9);
	}
	for (int i = 0; i < 36; i++)
	{
		int type = cardsRes.at(random<int>(0, cardsRes.size() - 1));
		cardsWan.push_back(type);
		cardsRes.erase(find(cardsRes.begin(), cardsRes.end(), type));
	}

	initGoodType();


	// return ; // 假牌

	int cardsArray[] = {
		1, 2, 1, 6,
		1, 2, 3, 8,
		2, 8, 4, 9,
		3, 1, 5, 2,
		4, 4, 3, 2,
		4, 1, 7, 8,
		3, 1, 2, 1,
		6, 1, 8, 1,
		7, 1, 1, 7,
	};

	for (int i = 0; i < 36; i++)
	{
		playedCards.push_back(cardsArray[36 - i - 1]);
	}
}

/// 抽取一张牌,
//@return num表示花色，0表示无牌
int MahjongDatas::popACard()
{
	int t = playedCards.at(playedCards.size() - 1);
	playedCards.pop_back();
	return t;

	auto card = 0.5 > random<float>(0, 1) ? TONG : WAN;
	switch (card)
	{
	case TONG:
		if (cardsTong.empty())
		{
			return popWan();
		}
		return popTong();
		break;
	case WAN:
		if (cardsWan.empty())
		{
			return popTong();
		}
		return popWan();
		break;
	default:
		return 0;
		break;
	}
}
int MahjongDatas::popAGoodCard()
{
	int t = playedCards.at(playedCards.size() - 1);
	playedCards.pop_back();
	return t;

	switch (goodCard)
	{
	case TONG:
		return popTong();
		break;
	case WAN:
		return popWan();
		break;
	default:
		return 0;
		break;
	}
}



int MahjongDatas::popTong()
{
	if (0 == cardsTong.size())
	{
		return popWan();
	}
	int cardType = cardsTong.at(cardsTong.size() - 1);
	cardsTong.pop_back();
	return cardType;
}

int MahjongDatas::popWan()
{
	if (0 == cardsWan.size())
	{
		return popTong();
	}
	int cardType = cardsWan.at(cardsWan.size() - 1);
	cardsWan.pop_back();
	return cardType;
}


