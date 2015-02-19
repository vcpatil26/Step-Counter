/* led.h --- 
 * 
 * Filename: led.h
 * Description: 
 * Author: 
 * Maintainer: 
 * Created: Thu Jan 10 10:56:56 2013
 * Last-Updated: 
 *           By: 
 *     Update #: 0
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change log:
 * 
 * 
 */

/* Code: */
#include <stm32f30x.h>

void f3d_led_init(void);
void f3d_led_on(int led); 
void f3d_led_off(int led); 
void f3d_led_all_on(void);
void f3d_led_all_off(void);

/* led.h ends here */
