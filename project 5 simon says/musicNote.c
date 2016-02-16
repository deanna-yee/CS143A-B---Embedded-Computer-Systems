#include "avr.h"
#include "musicNote.h"
#include "lcd.h"

void play_note(double freq, long dur)
{
	double delay = find_delay(freq);
	long duration = dur/(2.00*delay);
	for(unsigned int i = 0; i < duration; i++)
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




