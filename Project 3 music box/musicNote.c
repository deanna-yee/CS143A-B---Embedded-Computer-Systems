#include "avr.h"
#include "musicNote.h"
#include "lcd.h"
#include "keypad.h"

void play_note(double freq, long dur)
{
	double delay = find_delay(freq);
	long duration = dur/(2.00*delay);
	int i;
	for(i = 0; i < duration; i++)
	{
		SET_BIT(PORTB, 0);
		wait_avr(delay);
		CLR_BIT(PORTB, 0);
		wait_avr(delay);
	}
}

double find_delay(double freq)
{
	double period = 1.00/freq;
	double delay = (period/2.00) * 10000;
	return delay;
}

void play_song(const music_notes *song, int num_notes)
{
	int i;
	for(i = 0; i < num_notes; i++)
	{
		play_note(song[i].frequency,song[i].duration);
		if (get_key() == 9)
		{
			i = num_notes;
			clr_lcd();
		}
	}
	
}


