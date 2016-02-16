#include "avr.h"
#include "lcd.h"
#include "keypad.h"

unsigned int c_tenths = 0;
unsigned int c_hundredths = 0;
unsigned int min_tenths = 0;
unsigned int min_hundredths = 0;
unsigned int max_tenths = 0;
unsigned int max_hundredths = 0;
unsigned int a_tenths = 0;
unsigned int a_hundredths = 0;

void print_initial()
{
	pos_lcd(0,0);
	put_str_lcd("____");
	pos_lcd(0,12);
	put_str_lcd("____");
	pos_lcd(1,0);
	put_str_lcd("____");
	pos_lcd(1,12);
	put_str_lcd("____");
}
void print_current(float voltage)
{
	pos_lcd(0,0);
	put_lcd('0' + voltage);
	
	pos_lcd(0,1);
	put_lcd('.');
			
	pos_lcd(0,2);
	c_tenths = ((int) (voltage * 10)) % 10;
	put_lcd('0' + c_tenths);
			
	pos_lcd(0,3);
	c_hundredths = ((int) (voltage * 100)) % 10;
	put_lcd('0' + c_hundredths);
}

void print_average(float average)
{
	pos_lcd(0,12);
	put_lcd('0' + average);
	
	pos_lcd(0,13);
	put_lcd('.');
			
	pos_lcd(0,14);
	a_tenths = ((int) (average * 10)) % 10;
	put_lcd('0' + a_tenths);
			
	pos_lcd(0,15);
	a_hundredths = ((int) (average * 100)) % 10;
	put_lcd('0' + a_hundredths);
}

void print_min(float min)
{
	pos_lcd(1,12);
	put_lcd('0' + min);
	
	pos_lcd(1,13);
	put_lcd('.');
			
	pos_lcd(1,14);
	min_tenths = ((int) (min * 10)) % 10;
	put_lcd('0' + min_tenths);
			
	pos_lcd(1,15);
	min_hundredths = ((int) (min * 100)) % 10;
	put_lcd('0' + min_hundredths);
}

void print_max(float max)
{
	pos_lcd(1,0);
	put_lcd('0' + max);
	
	pos_lcd(1,1);
	put_lcd('.');
			
	pos_lcd(1,2);
	max_tenths = ((int) (max * 10)) % 10;
	put_lcd('0' + max_tenths);
			
	pos_lcd(1,3);
	max_hundredths = ((int) (max * 100)) % 10;
	put_lcd('0' + max_hundredths);
}

void main(){
	float voltage = 0.00;
	float max = 0.00;
	float min = 10.00; // initialize to value that cannot be reached
	float average = 0.00;
	float total = 0.00;
	unsigned char start = 0;
	unsigned int count = 0;
	ini_lcd();
	clr_lcd();
	print_initial();

	for(;;)
	{
		// A = START
		if (get_key() == 13)
		{
			start = 1;
			while(start){
				//Voltage  for ADC: AVCC with external capacitor at AREF pin
				//Bit 7 (REFS1) = 0 , Bit 6 (REFS0) = 1
				//Make results in ADCH left adjusted
				//Bit 5 (ADLAR) = 1
				ADMUX = 0x60;
				
				//Enable ADC
				//Bit 7 (ADEN) = 1
				//Start ADC COnversion
				//Bit 6 (ADSC) = 1
				ADCSRA = 0xc0;
				count += 1;
				voltage = ((((float) ADCH) + 0.00) * 5.00) / 255.00;
				print_current(voltage);
				
				total = total + voltage;
				average = total/ count;
				print_average(average);
				
				if(voltage > max)
				{
					max = voltage;
					print_max(max);
				}
				if(voltage < min)
				{
					min = voltage;
					print_min(min);
					
				}
				
				//wait until flag goes high
				//clear flag by setting ADIF to 1
				if(!ADIF)
				{
					SET_BIT(ADCSRA, 4); //ADIF (AD Interrupt flag)
				}
				// C = STOP
				if(get_key() == 5)
				{
					start = 0;
				}
				// B = RESET
				else if(get_key() == 9)
				{
					start = 0;
					count = 0;
					total = 0.00;
					voltage = 0.00;
					max = 0.00;
					min = 6.00; 
					average = 0.00;
					c_tenths = 0;
					c_hundredths = 0;
					min_tenths = 0;
					min_hundredths = 0;
					max_tenths = 0;
					max_hundredths = 0;
					a_tenths = 0;
					a_hundredths = 0;
					clr_lcd();
					print_initial();
				}
				wait_avr(500);	
			}
		}
		else if (get_key() == 9) // B = CLEAR
		{
			start = 0;
			count = 0;
			total = 0.00;
			voltage = 0.00;
			max = 0.00;
			min = 6.00; 
			average = 0.00;
			c_tenths = 0;
			c_hundredths = 0;
			min_tenths = 0;
			min_hundredths = 0;
			max_tenths = 0;
			max_hundredths = 0;
			a_tenths = 0;
			a_hundredths = 0;
			clr_lcd();
			print_initial();
		}	
		wait_avr(50);
	}
}