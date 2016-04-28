/****************************************************************************
 * Project developed as a simple Blink the LED's to 
 * demonstrate basic CodeWarrior functionality and capability.
 * Borrowed from Freedom Example Projects: Blinky
 * 
 * Date: 11 Sept 2012
 * Author: M. Ruthenbeck
 * Revision Level 1.0
 */
#ifndef RGB_LEDS_H                       /* To avoid double inclusion */
#define RGB_LEDS_H

typedef enum {
    LED_RED = 0,
    LED_GREEN,
    LED_BLUE,
    LED_CYAN,
    LED_MAGENTA,
    LED_YELLOW,
    LED_WHITE,
    LED_OFF
}COLOR;


void init_leds(void);
void app_rgb_led(void);
void app_rgb_led_fsm(void);
void test_pwm(void);
void set_color(COLOR,T_UBYTE);
void leds_off(void);

#endif /* RGB_LEDS_H */
