#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>

//prescale CLK/8, 8Mz clock and div8 prescale -> 1MHz tick -> appropx 10kHz output with top=99
const unsigned char prescaleTimer = (1<<CS12);

void setPWM()
{
	//setup timer1 with PWM. Will be using both A and B compare outputs.
	// both compares will be the same but only B will have dead time applied
	OCR1B = 128;
	GTCCR = (1<<PWM1B) | (1<<COM1B0); //Compare B PWM mode with complement outputs
 
	//PLLCSR is not set so the PLL will not be used (are using system clock directly - "synchonous mode")
	//OCR1C determines the "top" counter value if CTC1 in TCCR1 is set. Otherwise "top" is normal: 0xFF
	OCR1C = 255;
	TCCR1 |= (1<<CTC1);
	TCCR1 |= prescaleTimer; 
}

int main(void) 
{
	DDRB = 0xFF;
	PORTB = 0xFF;
	_delay_ms(500);
	PORTB = 0x00;

	setPWM();
	OCR1B = 100;

	while(1)
	{
		PORTB |= (1<<PB2);
		_delay_ms(50);
		PORTB &= ~(1<<PB2);
		_delay_ms(50);
	}
}
