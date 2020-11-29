/***************************************************************************************************************************************************
 *                                                                                                                                                 *
 *                                                              DECLARATIONS                                                                       *
 *                                                                                                                                                 *
 * ************************************************************************************************************************************************/

#ifndef DECLARATIONS_H_
#define DECLARATIONS_H_

#define MAX_DATA 10

// valoare dintre doua semnale
volatile uint32_t timer = 0;
// valoarea timerului trecut
volatile uint32_t f_timer = 0;

// valoarea din timer pentru 5 grade
volatile uint32_t grade_timer = 0;

// number of overflows on current iteration
volatile uint32_t ovf_count = 0;
// number of overflows on last iteration
volatile uint32_t f_ovf_count = 0;

// data to show on the POV display
uint8_t data[MAX_DATA];

// index for USART read
uint8_t ind = 0;

// aux data for switch
uint8_t data_to_show;

// flag for Hall sensor
uint8_t flag = 0;

#endif


