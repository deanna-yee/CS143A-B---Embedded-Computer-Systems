#ifndef __musicNote__
#define __musicNote__

typedef struct MusicNote
{
	double frequency;
	long duration;
}music_notes;

#define buzz 100.00
#define F_E 659.255
#define F_D 587.330
#define F_C 523.251
#define F_B 493.883
#define F_A 440.000


#define Q 3000

void play_note(double freq, long dur);
double find_delay(double freq);


 #endif