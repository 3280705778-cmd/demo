/**
 * @file    led.h
 * @brief   LED 驱动头文件。
 *          头文件放声明和宏，具体实现放在 led.c。
 */
#ifndef LED_H
#define LED_H

#include "stm32h7xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 宏定义：给 LED 使用的端口和引脚起名字 */
/* H7 板：4 颗 LED 依次接 PB3、PB4、PB5、PB6 */
#define LED_GPIO_PORT GPIOB
#define LED1_PIN      GPIO_PIN_3
#define LED2_PIN      GPIO_PIN_4
#define LED3_PIN      GPIO_PIN_5
#define LED4_PIN      GPIO_PIN_6

/* 函数声明：LED 编号约定为 1~4，分别对应 PB3~PB6 */
void led_on(uint8_t led_num);
void led_off(uint8_t led_num);

#ifdef __cplusplus
}
#endif

#endif /* LED_H */
