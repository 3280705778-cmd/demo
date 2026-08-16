/**
 * @file    user_beep.c
 * @brief   8.7 作业：上电蜂鸣器“长-短-短”三声的实现。
 *          加入 Keil 工程后，复位即可听到效果。
 */
#include "user_beep.h"
#include "buzzer.h"
#include "stm32h7xx_hal.h"

#define USER_BEEP_LONG_MS   300U  /* 长音时长 */
#define USER_BEEP_SHORT_MS  100U  /* 短音时长 */
#define USER_BEEP_GAP_MS    100U  /* 两次叫声之间的间隔 */

void user_beep(void)
{
    /* 第一声：长音 */
    buzzer_on();
    HAL_Delay(USER_BEEP_LONG_MS);
    buzzer_off();
    HAL_Delay(USER_BEEP_GAP_MS);

    /* 第二声：短音 */
    buzzer_on();
    HAL_Delay(USER_BEEP_SHORT_MS);
    buzzer_off();
    HAL_Delay(USER_BEEP_GAP_MS);

    /* 第三声：短音 */
    buzzer_on();
    HAL_Delay(USER_BEEP_SHORT_MS);
    buzzer_off();
    HAL_Delay(USER_BEEP_GAP_MS);
}
