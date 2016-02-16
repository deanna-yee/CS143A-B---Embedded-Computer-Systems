#include "avr.h"
#include "keypad.h"

unsigned char pressed(int l, int k){
	for(int j = 0; j < 4; j++){
		CLR_BIT(DDRC, j); //input
		SET_BIT(PORTC, j); //initialized columns to 0
	}
	
	//Rows
	for(int i = 4; i < 8; i++){
		SET_BIT(DDRC, i); //output
		SET_BIT(PORTC, i);
	}
	
	CLR_BIT(PORTC, k); //set row k to low
	
	if(GET_BIT(PINC, l) || GET_BIT(PINC, k)){ 
		return 0; //not pressed
	}
	else{
		return 1; //pressed
	}
	
}

int get_key(void){
	int i;
	int j;
	int k = 0;
	for(i = 0; i < 4; i++) //row
	{
		k = i + 4;
		
		for(j = 0; j < 4; j++){ //column
	
			if(pressed(j,k)){
				return (i * 4) + j + 1;
			}
		}
	}
	return 0;
}