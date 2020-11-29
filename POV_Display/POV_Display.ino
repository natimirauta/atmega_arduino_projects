#include "declarations.h"
#include "functions.h"
#include "letters.h"

#define USART_BAUDRATE 9600
#define MYUBRR (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

volatile uint32_t index_local = 0;

void setup() {

  // all leds on PORTC (1-6)
  // D2 hall int
  // D3 LED7
  
  DDRD = 0xF8;
  DDRC = 0xFF;
  
  PORTC = 0x00;
  PORTD = 0x00;

  USART_Init(MYUBRR);
  setup_timer1();
  init_INT0();
  
}

ISR(USART_RX_vect)
{
   eeprom_write_byte((uint8_t*)ind, UDR0);
   ind++;

   if(ind >= MAX_DATA)
   {
      ind = 0;
   }
}

ISR(TIMER1_COMPA_vect)
{
  ovf_count++;
}

ISR(INT0_vect)
{
  timer = TCNT1 + ovf_count * 0xFFFF - f_timer;
  f_timer = TCNT1 + ovf_count * 0xFFFF;
  
  grade_timer = timer/72; // one writing sequence per 5 degrees

  flag = 1;
}

void loop() {

  // parse the data from EEPROM from last to first
  if(flag == 1)
  {
    
    for(uint32_t index = 0; index < MAX_DATA; index++)
    {
      data_to_show = eeprom_read_byte((uint8_t*)index);

      switch(data_to_show) {

        case 'A': show_letter(vectorA, 4);
                  show_letter(vectorSpace, 1);
                  break;
        case 'B': show_letter(vectorB, 4);
                  show_letter(vectorSpace, 1);
                  break;
        case 'C': show_letter(vectorC, 4);
                  show_letter(vectorSpace, 1);
                  break;
        case 'D': show_letter(vectorD, 4);
                  show_letter(vectorSpace, 1);
                  break;
        case 'E': show_letter(vectorE, 4);
                  show_letter(vectorSpace, 1);
                  break;
        case 'F': show_letter(vectorF, 4);
                  show_letter(vectorSpace, 1);
                  break;
        case 'G': show_letter(vectorG, 4);
                  show_letter(vectorSpace, 1);
                  break;
        case 'H': show_letter(vectorH, 4);
                  show_letter(vectorSpace, 1);
                  break;
        case 'I': show_letter(vectorI, 1);
                  show_letter(vectorSpace, 1);
                  break;
        case 'J': show_letter(vectorJ, 4);
                  show_letter(vectorSpace, 1);
                  break;
        case 'K': show_letter(vectorK, 4);
                  show_letter(vectorSpace, 1);
                  break;
        case 'L': show_letter(vectorL, 4);
                  show_letter(vectorSpace, 1);
                  break;
        case 'M': show_letter(vectorM, 5);
                  show_letter(vectorSpace, 1);
                  break;
        case 'N': show_letter(vectorN, 5);
                  show_letter(vectorSpace, 1);
                  break;
        case 'O': show_letter(vectorO, 4);
                  show_letter(vectorSpace, 1);
                  break;
        case 'P': show_letter(vectorP, 4);
                  show_letter(vectorSpace, 1);
                  break;
        case 'Q': show_letter(vectorQ, 5);
                  show_letter(vectorSpace, 1);
                  break;
        case 'R': show_letter(vectorR, 4);
                  show_letter(vectorSpace, 1);
                  break;
        case 'S': show_letter(vectorS, 4);
                  show_letter(vectorSpace, 1);
                  break;
        case 'T': show_letter(vectorT, 5);
                  show_letter(vectorSpace, 1);
                  break;
        case 'U': show_letter(vectorU, 4);
                  show_letter(vectorSpace, 1);
                  break;
        case 'V': show_letter(vectorV, 5);
                  show_letter(vectorSpace, 1);
                  break;
        case 'W': show_letter(vectorW, 5);
                  show_letter(vectorSpace, 1);
                  break;
        case 'X': show_letter(vectorX, 5);
                  show_letter(vectorSpace, 1);
                  break;
        case 'Y': show_letter(vectorY, 5);
                  show_letter(vectorSpace, 1);
                  break;
        case 'Z': show_letter(vectorZ, 5);
                  show_letter(vectorSpace, 1);
                  break;
        case '_': show_letter(vectorSpace, 1);
                  break;
        case '0': show_letter(vector0, 4);
                  show_letter(vectorSpace, 1);
                  break;
        case '1': show_letter(vector1, 3);
                  show_letter(vectorSpace, 1);
                  break;
        case '2': show_letter(vector2, 4);
                  show_letter(vectorSpace, 1);
                  break;
        case '3': show_letter(vector3, 4);
                  show_letter(vectorSpace, 1);
                  break;
        case '4': show_letter(vector4, 4);
                  show_letter(vectorSpace, 1);
                  break;
        case '5': show_letter(vector5, 4);
                  show_letter(vectorSpace, 1);
                  break;
        case '6': show_letter(vector6, 4);
                  show_letter(vectorSpace, 1);
                  break;
        case '7': show_letter(vector7, 4);
                  show_letter(vectorSpace, 1);
                  break;
        case '8': show_letter(vector8, 4);
                  show_letter(vectorSpace, 1);
                  break;
        case '9': show_letter(vector9, 4);
                  show_letter(vectorSpace, 1);
                  break;                                                      
        case '*': break;
      }
    }

    flag = 0;
  }
  
}
