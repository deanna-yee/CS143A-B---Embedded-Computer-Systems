#include <stdio.h>
#include "simonSays.h"
#include "avr.h"
#include "lcd.h"
#include "musicNote.h"


unsigned char pattern[5];
unsigned int seed = 0;
unsigned int score = 0;
unsigned char press = 0;
int end[5] = {F_E, F_D, F_C, F_B, F_A};
unsigned char start = 0;


void set_start(unsigned char oneOrZero)
{
	start = oneOrZero;
}

unsigned char get_start()
{
	return start;
}


void play_sound(unsigned int p)
{
	if (pattern[p] == 0)
	{
		play_note(F_A, Q);
	}
	else if (pattern[p] == 1)
	{
		play_note(F_B, Q);
	}
	else if (pattern[p] == 2)
	{
		play_note(F_C, Q);
	}
	else if (pattern[p] == 3)
	{
		play_note(F_D, Q);
	}
	else if (pattern[p] == 4)
	{
		play_note(F_E, Q);
	}
}
//makes a randomized pattern 
void makePattern()
{
	srand(seed);
	
	for(unsigned int i = 0; i < 5; i++)
	{
		unsigned int litLed = 0;
		litLed = rand() % 5;
		pattern[i] = litLed;
		
	}
	seed++;
}

//goes through the randomized pattern made and plays it
void playPattern()
{
	for(int i = 0; i < 5; i++)
	{
		SET_BIT(PORTC, pattern[i]);
		//put_lcd('0' + pattern[i]);
		play_sound(i);
		wait_avr(20000);
		CLR_BIT(PORTC, pattern[i]);
		wait_avr(20000);	
	}
}

//Figures out which button was pressed
unsigned char pressedButton()
{
	unsigned char button = 5;
	if(!GET_BIT(PINA, 0))
	{
		button = 4;
		press = 1;
	}
	else if(!GET_BIT(PINA, 1))
	{
		button = 3;
		press = 1;
	}
	else if(!GET_BIT(PINA, 2))
	{
		button = 2;
		press = 1;
	}
	else if(!GET_BIT(PINA, 3))
	{
		button = 1;
		press = 1;
	}
	else if(!GET_BIT(PINA, 4))
	{
		button = 0;
		press = 1;
	}
	return button;
}

void print_score()
{
	char buf[15];
	sprintf(buf, "Score: %d", score);
	pos_lcd(0,0);
	put_str_lcd(buf);
}

//Checks to see if the correct button to the corresponding LED is pressed
void checkPattern()
{	
	unsigned char index = 0;
	unsigned char buttonNum = 0;
	while(index < 5)
	{
		press = 0;
		buttonNum = pressedButton();
		pos_lcd(0,8);
		
		if(press)
		{
			if(buttonNum == pattern[index])
			{
				play_sound(index);
				score++;
				wait_avr(50000);
				index++;
				print_score();
			}
			else
			{
				play_note(buzz, Q);
				wait_avr(10000);
				
				for(unsigned int i = 0; i < 5; i++)
				{
					play_note(end[i], Q);
				}
				
				pos_lcd(1,0);
				put_str_lcd("GAME OVER!");
				
				start = 0;
				score = 0;
				index = 5;
			}
			press = 0;
			
		}
		
	}
	
}



