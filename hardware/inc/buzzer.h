/**
 * @file    buzzer.h
 * @brief   蜂鸣器驱动头文件。
 *          头文件放声明和宏，具体实现放在 buzzer.c。
 */
#ifndef BUZZER_H
#define BUZZER_H

#include "stm32h7xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 宏定义：给蜂鸣器使用的端口和引脚起一个容易记住的名字 */
/* H7 板：蜂鸣器接 PB0 */
#define BUZZER_GPIO_PORT GPIOB
#define BUZZER_PIN       GPIO_PIN_0

/* 函数声明（原型）：只声明函数存在，不写实现 */
void buzzer_init(void);
void buzzer_on(void);
void buzzer_off(void);

#ifdef __cplusplus
}
#endif

#endif /* BUZZER_H */
