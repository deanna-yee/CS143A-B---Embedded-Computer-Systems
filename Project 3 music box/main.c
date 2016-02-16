#include "avr.h"
#include "lcd.h"
#include "keypad.h"
#include "musicNote.h"

music_notes saria[85] = {{F_FA, E}, {F_A, E}, {F_B, Q}, {F_FA, E}, {F_A, E}, {F_B, Q},
	{F_FA, E}, {F_A, E}, {F_B, E}, {F_E, E}, {F_D, Q}, {F_B, E}, {F_C, E}, 
	{F_B, E}, {F_GA, E}, {F_EA, P}, {F_DA, E},
	{F_EA, E}, {F_GA, E}, {F_EA, T},
	{F_FA, E}, {F_A, E}, {F_B, Q}, {F_FA, E}, {F_A, E}, {F_B, Q},
	{F_FA, E}, {F_A, E}, {F_B, E}, {F_E, E}, {F_D, Q}, {F_B, E}, {F_C, E},
	{F_E, E}, {F_B, E}, {F_GA, P}, {F_B, E},
	{F_GA, E}, {F_DA, E}, {F_EA, T},
	{F_DA, E}, {F_EA, E}, {F_FA, Q}, {F_GA, E}, {F_A, E}, {F_B, Q}, 
	{F_C, E}, {F_B, E}, {F_EA, T},
	{F_FA, E}, {F_GA, E}, {F_A, Q}, {F_B, E}, {F_C, E}, {F_D, Q},
	{F_E, E}, {F_F, E}, {F_G, T},
	{F_DA, E}, {F_EA, E}, {F_FA, Q}, {F_GA, E}, {F_A, E}, {F_B, Q}, 
	{F_C, E}, {F_B, E}, {F_EA, T},
	{F_FA, E}, {F_EA, E}, {F_A, E}, {F_GA, E}, {F_B, E}, {F_A, E}, {F_C, E}, {F_B, E},
	{F_D, E}, {F_C, E}, {F_E, E}, {F_D, E}, {F_F, E}, {F_E, E}, {F_E, S}, {F_F, E}, {F_D, S},
	{F_E, W}};
	
music_notes mary[26] = {{F_EA, Q}, {F_DA, Q}, {F_CA, Q}, {F_DA, Q}, 
	{F_EA, Q}, {F_EA, Q}, {F_EA, H},
	{F_DA, Q}, {F_DA, Q}, {F_DA, H},
	{F_EA, Q}, {F_GA, Q}, {F_GA, H},
	{F_EA, Q}, {F_DA, Q}, {F_CA, Q}, {F_DA, Q}, 
	{F_EA, Q}, {F_EA, Q}, {F_EA, Q}, {F_CA, Q},
	{F_DA, Q}, {F_DA, Q}, {F_EA, Q}, {F_DA, Q},
	{F_CA, W}};



void main(){
	SET_BIT(DDRB, 0);
	ini_lcd();
	clr_lcd();
	for(;;){
	pos_lcd(0,0);
	put_str_lcd("Press 1. Saria's...");
	pos_lcd(1,0);
	put_str_lcd("Press 2. Mary...");
		if (get_key() == 16)
		{
			clr_lcd();
			pos_lcd(0,2);
			put_str_lcd("Saria's Song");
			pos_lcd(1, 0);
			put_str_lcd("Press B to stop.");
			play_song(saria, 85);
			clr_lcd();
		}
		else if (get_key() == 15)
		{
			clr_lcd();
			pos_lcd(0,2);
			put_str_lcd("Mary Had A");
			pos_lcd(1, 2);
			put_str_lcd("Little Lamb");
			play_song(mary, 26);
			clr_lcd();
		}	
		wait_avr(50);
	}
}