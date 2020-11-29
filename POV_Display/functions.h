/***************************************************************************************************************************************************
 *                                                                                                                                                 *
 *                                                              FUNCTIONS                                                                          *
 *                                                                                                                                                 *
 * ************************************************************************************************************************************************/
#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "declarations.h"
/*************************************************************************
 *                        pow function from math.h                        *
 *************************************************************************/
inline int power(int number, int power ){
  int result = 1;
  int i = 0;

  if (!power){
    return 1;
  }
  for (i = 0; i < power; i++){
    result *= number;
  }

  return result;
}

/*************************************************************************
 *                            Timer1 init                                 *
 *************************************************************************/
inline void setup_timer1() {
  // turn off other interruptions
  cli();

  //clear registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  // prescaler set to 1024
  // interruption appears at 1 second: (x * 1024)/16 * 10^6 hz = 1 000 000 micro.s
  // x is OCR1A
  // 5 seconds
  OCR1A = 15625;//32050; //15625 pt o secunda => 32050 pt 2 secunde

  // prescaler set to 1024 and CTC mode 
  // clear timer on compare match; TCNT1 is set to 0 when timer is equal to OCR1A
  TCCR1B |= (1 << CS10) | (1 << CS12);// | (1 << WGM12);

  // enables timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  // enable interruptions
  sei();
}

/*************************************************************************
 *                           USART init                                  *
 *************************************************************************/
inline void USART_Init(unsigned int ubrr) {
   cli(); // disable global interrupts in case another code was loaded on the board

   UCSR0A = 0;
   UCSR0B = 0;
   UCSR0C = 0;
   
   UCSR0B = (1 << RXEN0) | (1 << TXEN0);   // turn on the transmission and reception circuitry
   UCSR0C = (1 << UCSZ00) | (1 << UCSZ01); // use 8-bit character sizes

   UBRR0H = (ubrr >> 8); // load upper 8-bits of the baud rate value into the high byte of the UBRR register
   UBRR0L = ubrr; // load lower 8-bits of the baud rate value into the low byte of the UBRR register

   UCSR0B |= (1 << RXCIE0); // enable the USART Recieve Complete interrupt (USART_RXC)
   
   sei(); // enable the Global Interrupt Enable flag so that interrupts can be processed  
}

/*************************************************************************
 *                           USART send                                  *
 *************************************************************************/
inline void USART_Transmit( unsigned char data ) {
  // Wait for empty transmit buffer
  while (!( UCSR0A & (1<<UDRE0)));
  // Put data into buffer; this sends the data
  UDR0 = data;
}

/*************************************************************************
 *                           USART receive                               *
 *************************************************************************/
inline char USART_Receive(void) {
 // Wait for data to be received
 while (!(UCSR0A & (1<<RXC0)));
 // Get and return received data from buffer
 return UDR0;
}

/*************************************************************************
 *                           USART send string                           *
 *************************************************************************/
void USART_Putstring(char* StringPtr){
  //Here we check if there are still more chars to send
  while(*StringPtr != 0x00) {
    
    USART_Transmit(*StringPtr); // sending one char at a time
    StringPtr++;
  }
}

/*************************************************************************
 *                           INT0/PD2 init                               *
 *************************************************************************/
void init_INT0() {
    cli();
    DDRD &= ~(1 << DDD2);     // clear the PD2 pin
    // PD2 (PCINT0 pin) is now an input

    PORTD |= (1 << PORTD2);    // turn On the Pull-up
    // PD2 is now an input with pull-up enabled

    EICRA |= (1 << ISC00) | (1<<ISC01); // set INT0 to trigger on ANY logic change
    EIMSK |= (1 << INT0); // turns on INT0

    sei(); // turn on interrupts 
}

/*************************************************************************
 *                           WRITE N step letter                         *
 *************************************************************************/
void show_letter(uint8_t letter_vector[], uint8_t steps)
{
  uint8_t master_index = 0;
  uint8_t letter_vector_index = 0;
  
  uint8_t write_value = 0;
  
  uint8_t first_value = 0;
  uint8_t final_value = 7;

  uint8_t time_tcnt = 0;

  for(master_index = 0; master_index < steps; master_index++)
  {
    timer = TCNT1 + ovf_count * 0xFFFF;
    
    for(letter_vector_index = first_value; letter_vector_index < final_value; letter_vector_index++)
    {
      write_value += letter_vector[letter_vector_index] * power(2, letter_vector_index - first_value);
    }
    
    // use value for 5 degrees of circle
    while((TCNT1 + ovf_count * 0xFFFF) - timer < grade_timer)
    {
      PORTD = write_value;
      PORTC = write_value;
    }

    write_value = 0;
    
    first_value = final_value;
    final_value += 7;
  }
  
}
#endif
