#include "main.h"

void de_in_crement_value(u8 *val, u8 min_val, u8 max_val, buttons direction);


void de_in_crement_value(u8 *val, u8 min_val, u8 max_val, buttons direction){
	s16 v=*val+(s8)direction;
	if(v==max_val+1){
		*val=min_val;
		return;
	}
	if(v==min_val-1){
		*val=max_val;
		return;
	}
	*val=(u8)v;
}
