#include "declarations.h"
#include <Wire.h> 
#include <SoftwareSerial.h>
SoftwareSerial mySerial(8,9);

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

/*************************************************************************
 *                           Calculate duty cycle                        *
 *************************************************************************/
inline uint8_t duty_cycle(uint8_t percentage) {
  return (percentage * 0xFFFF) / 100;
}

/*************************************************************************
 *                           PWM init                                    *
 *************************************************************************/
void PWM_init(){}
inline void PWM_Init() {
  // Clear Timer/Counter Control Registers
  TCCR1A = 0;
  TCCR1B = 0;

  // Set non-inverting mode
  TCCR1A |= (1 << COM1A1);

  // Set fast PWM Mode 14
  TCCR1A |= (1 << WGM11);
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << WGM13);

  // Set PWM frequency/top value
  //TOP value to 0xFFFF
  //65535 = ffff = 100%
  //16363 = 3ffff = 25%
  //32767 = 7ffff = 50%
  ICR1 = 0xFFFF;
  OCR1A = 0x7FFF; //100% DC

  // Set prescaler to 64 and starts PWM
  TCCR1B |= (1 << CS10);
  TCCR1B |= (1 << CS11); //no prescaler
}

/*************************************************************************
 *                           USART init                                  *
 *************************************************************************/
inline void USART_Init(unsigned int ubrr) {
   cli(); //disable global interrupts in case another code was loaded on the board

   UCSR0A = 0;
   UCSR0B = 0;
   UCSR0C = 0;
   
   UCSR0B = (1 << RXEN0) | (1 << TXEN0);   // Turn on the transmission and reception circuitry
   UCSR0C = (1 << UCSZ00) | (1 << UCSZ01); // Use 8-bit character sizes

   UBRR0H = (ubrr >> 8); // Load upper 8-bits of the baud rate value into the high byte of the UBRR register
   UBRR0L = ubrr; // Load lower 8-bits of the baud rate value into the low byte of the UBRR register

   UCSR0B |= (1 << RXCIE0); // Enable the USART Recieve Complete interrupt (USART_RXC)
   
   sei(); // Enable the Global Interrupt Enable flag so that interrupts can be processed  
}

/*************************************************************************
 *                           USART send                                  *
 *************************************************************************/
inline void USART_Transmit(unsigned char data) {
  /* Wait for empty transmit buffer */
  while ( !( UCSR0A & (1<<UDRE0)) );
  /* Put data into buffer, sends the data */
  UDR0 = data;
}

/*************************************************************************
 *                           Serial init                                 *
 *************************************************************************/
void usart_init() {
  mySerial.begin(9600);
  Serial.begin(9600);
  delay(100);
}
 
/*************************************************************************
 *                           OY read                                     *
 *************************************************************************/
double read_OY_axis() {
  Wire.beginTransmission(ADXAddress);
  Wire.write(Register_Y0);
  Wire.write(Register_Y1);
  Wire.endTransmission();
  Wire.requestFrom(ADXAddress,2);
  
  if(Wire.available() <= 2) {
    Y0 = Wire.read();
    Y1 = Wire.read();
    Y1 = Y1<<8;
    Y_out = Y0+Y1;
  }
  
  Yg = Y_out/256.00;

  return Yg * 100;
}

/*************************************************************************
 *                           Accel init                                  *
 *************************************************************************/
void gyro_init() {
  Wire.begin();
  Wire.beginTransmission(ADXAddress);
  Wire.write(Register_2D);
  Wire.write(8);
  Wire.endTransmission(); 
  
}

/*************************************************************************
 *                           Filter axis vals                            *
 ************************************************************************/
double filter_axis(double value) {
  if(-1 < value < 1)
    return 0;

  if(value > 99)
    return 100;

  if(value < -99)
    return -100;
    
  return value;
}

/*************************************************************************
 *                           Filter PWM                                  *
 ************************************************************************/
double filter_pwm(double value) {
  if(value > 255)
    return 255;

  return value;
}


/*************************************************************************
 *                           PWM to motor                                *
 *************************************************************************/
void send_pwm_to_motor(int motor_pin, double motor_speed) {
  analogWrite(motor_pin, motor_speed);
  
}

/*************************************************************************
 *                           Print axis value                            *
 *************************************************************************/
void print_axis_value_USART(double axis) {
  Serial.print(axis);
  Serial.print("\n");  
}

/*************************************************************************
 *                           Print string                                *
 *************************************************************************/
void print_string(char *string) {
  Serial.print(string);  
}

/*************************************************************************
 *                                PID                                    *
 *************************************************************************/
double PID() {
  return kP * (current_error)  + kI * (sum_error) +  kD * (deriv_error);  
    
}

/*************************************************************************
 *                                BT                                     *
 *************************************************************************/
double read_blutooth() {
  double final_value;
  if (mySerial.available() > 0) {
    aux = mySerial.read();
    
    if(aux == 45) {
      minus = 1;
    } else {
      digit = aux - 48;
      v[counter] = digit;
      number = number * 10 + v[counter];
      counter++;
    }
    
    if((minus == 0) && (counter == 2)) {
      final_value = number;
      
      counter = 0;   
      number  = 0; 
      minus   = 0;
    }
    
    if((minus == 1) && (counter == 2)) {
      number *= -1;

      final_value = number;

      counter = 0;     
      number  = 0;
      minus   = 0;

    }
   
  }

  return final_value;
}

/*************************************************************************
 *                          CONVERT ANGLES                               *
 *************************************************************************/
double convert_angles_to_ref_vals(double angle) {
  return 1.1 * angle;  
}
#endif

