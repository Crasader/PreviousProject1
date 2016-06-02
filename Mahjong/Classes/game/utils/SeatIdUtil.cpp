#include "game/utils/SeatIdUtil.h"

int SeatIdUtil::getClientSeatId(int heroId, int seatId){
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