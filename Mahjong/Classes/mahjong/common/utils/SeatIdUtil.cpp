#include "mahjong/common/utils/SeatIdUtil.h"
#include "mahjong/common/state/GameData.h"

int SeatIdUtil::getClientSeatId(int heroId, int seatId){
    if(GAMEDATA::getInstance()->getMyGameModel() == GameModel::TWOPLAYER){
        if(heroId == seatId){
            return 1;
        }else{
            return 3;
        }
    }else{
        if(seatId == 0){
            return 0;
        }
        if(heroId == seatId){
            return 1;
        }
        if (heroId == 2){
            int result = (seatId + 3) % 4;
            if (result == 0){
                result = 4;
            }
            return result;
        }
        else if (heroId == 4){
            int result = (seatId + 1) % 4;
            if (result == 0){
                result = 4;
            }
            return result;
        }else{
            int result = (seatId + abs(heroId - hero)) % 4;
            if (result == 0){
                result = 4;
            }
            return result;
        }
    }
}


int SeatIdUtil::getServerPreSeatId(int current){
    return (current-1)==0?4:(current-1);
}
