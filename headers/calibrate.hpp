#ifndef _GP_2018_TI_AUTONOMOUS_ROBOT_CALIBRATE_HPP
#define _GP_2018_TI_AUTONOMOUS_ROBOT_CALIBRATE_HPP

// saves the new calibration to file
bool save_calibration(int max_color, int min_color, int max_light, int min_light);

// calibrates the sensors and saves it using save_calibration
void calibrate_line_sensors();

#endif /* _GP_2018_TI_AUTONOMOUS_ROBOT_CALIBRATE_HPP */
