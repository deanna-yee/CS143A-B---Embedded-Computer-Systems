//Deanna Yee 78807602
//Lanvi Nguyen 78047695
#include "avr.h"
#include "keypad.h"
#include "lcd.h"
#include <stdio.h>


	int col = 0;
	int row = 0;
	int index = 0;
	int normal[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int leapyear[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	unsigned int date[8];
	unsigned int time[6];
	unsigned char start = 1;
	unsigned char set_date = 0;
	unsigned char set_time = 0;
	unsigned int sec = 0;
	unsigned int min = 0;
	unsigned int hr = 1;
	unsigned int day = 1;
	unsigned int month = 1;
	unsigned long year = 1;
	unsigned char tens = 0;
	unsigned char ones = 0;

void setTime()
{
	unsigned int pre_hr = hr;
	unsigned int pre_min = min;
	unsigned int pre_sec = sec;
	hr = time[0] * 10 + time[1];
	min = time[2] * 10 + time[3];
	sec = time[4] * 10 + time[5];

	if(hr >= 24 || min > 59 || sec > 59){
		clr_lcd();
		pos_lcd(1,0);
		put_str_lcd("HHMMSS");
		pos_lcd(1,0);
		col = 0;
		index = 0;
		hr = pre_hr;
		min = pre_min;
		sec = pre_sec;
	}
	
	set_time = 0;
}

void setDate()
{
	unsigned int pre_m = month;
	unsigned int pre_d = day;
	unsigned int pre_y = year;
	month = date[0] * 10 + date[1];
	day = date[2] * 10 + date[3];
	year = date[4] * 1000 + date[5] * 100 + date[6] * 10 + date[7];
	
	if ((year%4 == 0 && year%100 != 0) || year%400 == 0)
	{
		if (month > 12 || day > leapyear[month-1])
		{
			clr_lcd();
			pos_lcd(0,0);
			put_str_lcd("MMDDYYYY");
			pos_lcd(0,0);
			col = 0;
			index = 0;
			month = pre_m;
			day = pre_d;
			year = pre_y;
		}
	}
	else
	{
		if (month > 12 || day > normal[month-1])
		{
			clr_lcd();
			pos_lcd(0,0);
			put_str_lcd("MMDDYYYY");
			pos_lcd(0,0);
			col = 0;
			index = 0;
			month = pre_m;
			day = pre_d;
			year = pre_y;
		}
	}
	set_date = 0;
}

void print()
{
	tens = '0' + (hr / 10);
	ones = '0' + (hr % 10);
	pos_lcd(1,0);
	put_lcd(tens);
	put_lcd(ones);
	
	pos_lcd(1,2);
	put_lcd(':');

	tens = '0' + (min / 10);
	ones = '0' + (min % 10);
	pos_lcd(1,3);
	put_lcd(tens);
	put_lcd(ones);
	
	pos_lcd(1,5);
	put_lcd(':');

	tens = '0' + (sec / 10);
	ones = '0' + (sec % 10);	
	pos_lcd(1,6);
	put_lcd(tens);
	put_lcd(ones);

	
	tens = '0' + (month / 10);
	ones = '0' + (month % 10);
	pos_lcd(0,0);
	put_lcd(tens);
	put_lcd(ones);
	
	pos_lcd(0,2);
	put_lcd('/');
	
	tens = '0' + (day / 10);
	ones = '0' + (day % 10);
	pos_lcd(0,3);
	put_lcd(tens);
	put_lcd(ones);

	pos_lcd(0,5);
	put_lcd('/');
	
	unsigned char thous = '0' + (year / 1000);
	unsigned char hund = '0' + ((year%1000) / 100);
	tens = '0' + ((year%100) / 10);
	ones = '0' + (year % 10);
	pos_lcd(0,6);
	put_lcd(thous);
	put_lcd(hund);
	put_lcd(tens);
	put_lcd(ones);
}

void increment()
{	
	sec++;
	if (sec == 60)
	{
		sec = 0;
		min++;
		if (min == 60)
		{
			min = 0;
			hr++;
			if (hr == 24) 
			{ 
				hr = 0;
				day++;
				if ((year%4 == 0 && year%100 != 0) || year%400 == 0)
				{
					if (day > leapyear[month-1])
					{
						day = 1;
						month++;
						if (month > 12)
						{
							month = 1;
							year++;
						}
					}	
				}
				else if (day > normal[month-1])
				{	
					day = 1;
					month++;
					if (month > 12)
					{
						month = 1;
						year++;
					}
				}
			}
		}
	}
	wait_avr(100);
}

int main(void){
	ini_lcd();
	ini_avr();

	for(;;)
	{
		if(get_key() == 13) // SET DATE
			{
				//put_lcd('A');
				row = 0;
				col = 0;
				clr_lcd();
				pos_lcd(0,0);
				put_str_lcd("MMDDYYYY");
				start = 0;
				pos_lcd(0,0);
				set_date = 1;
				set_time = 0;
				index = 0;
			}
			
			else if(get_key() == 9) // SET TIME
			{
				//put_lcd('B');
				row = 1;
				col = 0;
				clr_lcd();
				pos_lcd(1,0);
				put_str_lcd("HHMMSS");
				start = 0;
				pos_lcd(1,0);
				set_time = 1;
				set_date = 0;
				index = 0;
			}
		if (start == 1)
		{
			increment();
			print();
		}
		else 
		{
			if(get_key() == 2)
			{
				//put_lcd('#');
				if (set_date)	{setDate();}
				if (set_time)	{setTime();}
				start = 1;
			}
			else if(get_key() == 3){
				put_lcd('0');
				if(set_date){
					date[index] = 0;
				}
				else if(set_time){
					time[index] = 0;
				}
				index++;
				col++;
			}
			else if(get_key() == 4){
				//put_lcd('*');
				clr_lcd();
				col = 0;
				row = 0;
				set_time = 0;
				set_date = 0;
				start = 1;
				index = 0;
			}
			else if(get_key() == 6){
				put_lcd('9');
				if(set_date){
					date[index] = 9;
				}
				else if(set_time){
					time[index] = 9;
				}
				index++;
				col++;
			}
			else if(get_key() == 7){
				put_lcd('8');
				if(set_date){
					date[index] = 8;
				}
				else if(set_time){
					time[index] = 8;
				}
				index++;
				col++;
			}
			else if(get_key() == 8){
				put_lcd('7');
				if(set_date){
					date[index] = 7;
				}
				else if(set_time){
					time[index] = 7;
				}
				index++;
				col++;
			}
			else if(get_key() == 10){
				put_lcd('6');
				if(set_date){
					date[index] = 6;
				}
				else if(set_time){
					time[index] = 6;
				}
				index++;
				col++;
			}
			else if(get_key() == 11){
				put_lcd('5');
				if(set_date){
					date[index] = 5;
				}
				else if(set_time){
					time[index] = 5;
				}
				index++;
				col++;
			}
			else if(get_key() == 12){
				put_lcd('4');
				if(set_date){
					date[index] = 4;
				}
				else if(set_time){
					time[index] = 4;
				}
				index++;
				col++;
			}
			else if(get_key() == 14){
				put_lcd('3');
				if(set_date){
					date[index] = 3;
				}
				else if(set_time){
					time[index] = 3;
				}
				index++;
				col++;
			}
			else if(get_key() == 15){
				put_lcd('2');
				if(set_date){
					date[index] = 2;
				}
				else if(set_time){
					time[index] = 2;
				}
				index++;
				col++;
			}
			else if(get_key() == 16){
				put_lcd('1');
				if(set_date){
					date[index] = 1;
				}
				else if(set_time){
					time[index] = 1;
				}
				index++;
				col++;
			}
			if (set_time)
			{
				if (col > 5)
				{
					col = 0;
					pos_lcd(row, col);
				}
			}
			else if (set_date)
			{
				if (col > 7)
				{
					col = 0;
					pos_lcd(row, col);
				}
			}
		}
		wait_avr(25);
	}
	return 0;
}