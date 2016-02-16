#ifndef __musicNote__
#define __musicNote__

typedef struct MusicNote
{
	double frequency;
	long duration;
}music_notes;

#define rest 0
#define F_G 783.991
#define	F_F 698.456
#define F_E 659.255
#define F_D 587.330
#define F_C 523.251
#define F_B 493.883
#define F_A 440.000
#define F_GA 391.995
#define F_FA 349.228
#define F_EA 329.628
#define F_DA 293.655
#define F_CA 261.626
#define F_BA 246.942
#define F_AA 220.000

#define W 12000
#define T 9000
#define P 7500
#define H 6000
#define Q 3000
#define E 1500
#define S 750

void play_song(const music_notes *song, int num_notes);
void play_note(double freq, long dur);
double find_delay(double freq);


 #endif