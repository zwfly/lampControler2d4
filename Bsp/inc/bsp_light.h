/*
 * bsp_light.h
 *
 *  Created on: 2017Äê8ÔÂ18ÈÕ
 *      Author: fly
 */

#ifndef BSP_INC_BSP_LIGHT_H_
#define BSP_INC_BSP_LIGHT_H_

void Light_InitHard(void);
void Light_Red_set(uint8_t duty);
void Light_Green_set(uint8_t duty);
void Light_Blue_set(uint8_t duty);
void Light_RGB_set(uint8_t r, uint8_t g, uint8_t b);

#endif /* BSP_INC_BSP_LIGHT_H_ */
