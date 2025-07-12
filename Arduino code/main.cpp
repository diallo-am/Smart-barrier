#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#define TRIG_PIN PD2
#define ECHO_PIN PD3
#define SERVO_PIN PB1 // OC1A (Arduino D9)

void USART_init(unsigned int ubrr) {
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1 << TXEN0); // Enable transmitter
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8-bit data
}

void USART_send(char data) {
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

void USART_print(const char* str) {
	while (*str) {
		USART_send(*str++);
	}
}

void init_ultrasonic() {
	DDRD |= (1 << TRIG_PIN);  // Trigger en sortie
	DDRD &= ~(1 << ECHO_PIN); // Echo en entrée
}

void init_pwm_servo() {
	// OC1A en sortie
	DDRB |= (1 << SERVO_PIN);

	// Mode 14 Fast PWM: TOP=ICR1
	TCCR1A = (1 << COM1A1) | (1 << WGM11);
	TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11) | (1 << CS10); // Prescaler 64

	ICR1 = 4999; // Pour 50Hz (20ms)
	OCR1A = 97;  // Position initiale: 0°
}

void servo_open() {
	OCR1A = 374; // 1.5 ms (90°)
}

void servo_close() {
	OCR1A = 97; // 0.5 ms (0°)
}

uint16_t measure_distance_cm() {
	uint16_t count = 0;

	PORTD &= ~(1 << TRIG_PIN);
	_delay_us(2);
	PORTD |= (1 << TRIG_PIN);
	_delay_us(10);
	PORTD &= ~(1 << TRIG_PIN);

	while (!(PIND & (1 << ECHO_PIN)));
	while ((PIND & (1 << ECHO_PIN)) && count < 30000) {
		_delay_us(1);
		count++;
	}

	return count / 58;
}

int main(void) {
	char buffer[10];

	USART_init(103); // 9600 bps @ 16MHz
	init_ultrasonic();
	init_pwm_servo();

	// Initialisation des LEDs
	DDRD |= (1 << PD4) | (1 << PD5); // PD4 = verte, PD5 = rouge

	USART_print("System ready...\r\n");

	while (1) {
		uint16_t distance = measure_distance_cm();

		// Affichage sur terminal
		itoa(distance, buffer, 10);
		USART_print("Distance: ");
		USART_print(buffer);
		USART_print(" cm\r\n");

		if (distance < 40) {
			servo_open();
			PORTD |= (1 << PD5);  // Allume LED rouge
			PORTD &= ~(1 << PD4); // Éteint LED verte
			_delay_ms(2000);
			servo_close();
			} else {
			servo_close();
			PORTD |= (1 << PD4);  // Allume LED verte
			PORTD &= ~(1 << PD5); // Éteint LED rouge
		}

		_delay_ms(500);
	}
}
