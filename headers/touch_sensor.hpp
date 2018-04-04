#ifndef _TOUCH_SENSOR_HPP
#define _TOUCH_SENSOR_HPP

/**
 * @brief initialize touch sensor.
 */
void init_touch();

/**
 * @brief check if touch sensor is pressed.
 * @return (int) sensor_touch.pressed, pressumably 1 on pressed and 0 on not pressed. 
 */
int return_data();

#endif /* _TOUCH_SENSOR_HPP */
