#include "avr.h"
#include "lcd.h"
#include "simonSays.h"


void main()
{
	ini_avr();
	ini_lcd();
	clr_lcd();
	
	SET_BIT(DDRB, 0);
	
	for(;;)
	{
		pos_lcd(0,3);
		put_str_lcd("Simon Says");
		pos_lcd(1,0);
		put_str_lcd("Press any button");
		
		if(GET_BIT(PINA, 0) && GET_BIT(PINA, 1) && GET_BIT(PINA, 2) && GET_BIT(PINA, 3) && GET_BIT(PINA, 4))
		{	
		}
		else
		{
			set_start(1);
		}
		
		while(get_start())
		{
			clr_lcd();
			print_score();
			
			makePattern();
			playPattern();
			
			//check to see if correct button is pressed in correct order
			checkPattern();
			wait_avr(50000);
			clr_lcd();
		}
	}	
}

/*
		*/