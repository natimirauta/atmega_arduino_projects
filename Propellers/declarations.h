#ifndef DECLARATIONS_H_
#define DECLARATIONS_H_

// gyroscope
#define Register_ID 0
#define Register_2D 0x2D
#define Register_X0 0x32
#define Register_X1 0x33
#define Register_Y0 0x34
#define Register_Y1 0x35
#define Register_Z0 0x36
#define Register_Z1 0x37

#define USART_BAUDRATE 9600
#define MYUBRR (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

// PID
double kP = 3;
double kI = 0.027;
double kD = 1;

// Gyro & Accelerometer declarations:
int ADXAddress = 0x53;  //I2C address

int X0,X1,X_out;
int Y0,Y1,Y_out;
int Z1,Z0,Z_out;
double Xg,Yg,Zg;

double y_axis;
double val_ref_y_axis = 0;

int left_motor = 11;
int right_motor = 10;

// regulate just left motor
double speed_left_motor  = 180;
double speed_right_motor = 180;

double new_left_motor_speed  = 0;
double new_right_motor_speed = 0;
// PID errors
double current_error = 0; // P
double sum_error     = 0; // I
double deriv_error   = 0; // D

double last_error = 0;

int index_sum_error_reset = 0;


// bt vars
int aux = 0;
int v[3];
int counter = 0;

double number = 0;

int digit = 0;
int minus = 0;

double received;
double former_received_ref_value = val_ref_y_axis ;

#endif
