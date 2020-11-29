#include "functions.h"
#include "declarations.h"

void setup() {

  PWM_init();
  usart_init();
  gyro_init();
  
}

void loop() {
  received = read_blutooth();

  if(received != former_received_ref_value) {
      val_ref_y_axis = convert_angles_to_ref_vals(received);
  }
  
  // print_axis_value_USART(val_ref_y_axis);

  index_sum_error_reset++;

  // reset sum_error every 100 loops
  if(index_sum_error_reset > 100) {
      sum_error = 0;
      index_sum_error_reset = 0;
  }
  
  y_axis = filter_axis(read_OY_axis());
  
  // calculate errors on each loop
  last_error = current_error;
  
  current_error = val_ref_y_axis - y_axis;
  sum_error     = sum_error + current_error;
  deriv_error   = last_error - current_error;
  
  // left side motor needs adjustment => + power
  new_left_motor_speed  = speed_left_motor - PID();
  new_right_motor_speed = speed_right_motor + PID();

  send_pwm_to_motor(left_motor, filter_pwm(new_left_motor_speed));
  send_pwm_to_motor(right_motor, filter_pwm(new_right_motor_speed));
}

