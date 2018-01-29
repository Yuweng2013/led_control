/*
 * led.c
 *
 *  Created on: 2017Äê11ÔÂ9ÈÕ
 *      Author: yuwen
 */


#include "led.h"


void delay(uint16_t ms)
{
    uint16_t i;
    for(i=0;i<ms;i++)
        __delay_cycles(1000);

}


void timer_b_initial(uint16_t TIMER_PERIOD)
{
    //Start timer
    Timer_B_initUpModeParam initUpParam = {0};
    initUpParam.clockSource = TIMER_B_CLOCKSOURCE_SMCLK;
    initUpParam.clockSourceDivider = TIMER_B_CLOCKSOURCE_DIVIDER_1;
    initUpParam.timerPeriod = TIMER_PERIOD;
    initUpParam.timerInterruptEnable_TBIE = TIMER_B_TBIE_INTERRUPT_DISABLE;
    initUpParam.captureCompareInterruptEnable_CCR0_CCIE =
        TIMER_B_CCIE_CCR0_INTERRUPT_DISABLE;
    initUpParam.timerClear = TIMER_B_DO_CLEAR;
    initUpParam.startTimer = false;
    Timer_B_initUpMode(TIMER_B0_BASE, &initUpParam);

    Timer_B_startCounter(TIMER_B0_BASE,
                         TIMER_B_UP_MODE
                         );
}

void led1_brightness_level_set(uint16_t brightness_level)
{
    //Initialize compare mode to generate PWM1
    Timer_B_initCompareModeParam initComp1Param = {0};
    initComp1Param.compareRegister = TIMER_B_CAPTURECOMPARE_REGISTER_4; //CCR1 P7.6
    initComp1Param.compareInterruptEnable = TIMER_B_CAPTURECOMPARE_INTERRUPT_DISABLE;
    initComp1Param.compareOutputMode = TIMER_B_OUTPUTMODE_RESET_SET;
    initComp1Param.compareValue = brightness_level;
    Timer_B_initCompareMode(TIMER_B0_BASE, &initComp1Param);
}

void led2_brightness_level_set(uint16_t brightness_level)
{
    //Initialize compare mode to generate PWM2
    Timer_B_initCompareModeParam initComp2Param = {0};
    initComp2Param.compareRegister = TIMER_B_CAPTURECOMPARE_REGISTER_1; //CCR4 P5.7
    initComp2Param.compareInterruptEnable = TIMER_B_CAPTURECOMPARE_INTERRUPT_DISABLE;
    initComp2Param.compareOutputMode = TIMER_B_OUTPUTMODE_RESET_SET;
    initComp2Param.compareValue = brightness_level;
    Timer_B_initCompareMode(TIMER_B0_BASE, &initComp2Param);
}

void led_enable(uint8_t flag)
{
    //ENABLE P7.5 as high output
    GPIO_setAsOutputPin(
        GPIO_PORT_P7,
        GPIO_PIN5
        );
    // Set P5.6 to input direction
    GPIO_setAsInputPin(
        GPIO_PORT_P5,
        GPIO_PIN6
        );

    if (flag)
    {
        GPIO_setOutputHighOnPin(
            GPIO_PORT_P7,
            GPIO_PIN5
            );
    }
    else
    {
        GPIO_setOutputLowOnPin(
            GPIO_PORT_P7,
            GPIO_PIN5
            );
    }
    __delay_cycles(75);

}

void led1_blink(uint16_t freq1_blink)
{
    GPIO_setAsPeripheralModuleFunctionOutputPin(
        GPIO_PORT_P7,
        GPIO_PIN6
        );

    delay(freq1_blink);

    // OPERATION ON P7.6
    GPIO_setAsOutputPin(
        GPIO_PORT_P7,
        GPIO_PIN6
        );

    GPIO_setOutputLowOnPin(
        GPIO_PORT_P7,
        GPIO_PIN6
        );

    delay(freq1_blink);
}

void led1_stop()
{
    GPIO_setAsOutputPin(
        GPIO_PORT_P7,
        GPIO_PIN6
        );

    GPIO_setOutputLowOnPin(
        GPIO_PORT_P7,
        GPIO_PIN6
        );
}

void led2_blink(uint16_t freq2_blink)
{

    GPIO_setAsPeripheralModuleFunctionOutputPin(
        GPIO_PORT_P5,
        GPIO_PIN7
        );

    delay(freq2_blink);

    // OPERATION ON P5.7
    GPIO_setAsOutputPin(
        GPIO_PORT_P5,
        GPIO_PIN7
        );

    GPIO_setOutputLowOnPin(
        GPIO_PORT_P5,
        GPIO_PIN7
        );

    delay(freq2_blink);
}

void led2_stop()
{
    GPIO_setAsOutputPin(
        GPIO_PORT_P5,
        GPIO_PIN7
        );

    GPIO_setOutputLowOnPin(
        GPIO_PORT_P5,
        GPIO_PIN7
        );
}

void led1_shinning()
{
    GPIO_setAsPeripheralModuleFunctionOutputPin(
        GPIO_PORT_P7,
        GPIO_PIN6
        );
}

void led2_shinning()
{
    GPIO_setAsPeripheralModuleFunctionOutputPin(
        GPIO_PORT_P5,
        GPIO_PIN7
        );
}

void timer_A2_initial()
{
    //Start timer in continuous mode sourced by ACLK
    Timer_A_initContinuousModeParam initContParam = {0};
    initContParam.clockSource = TIMER_A_CLOCKSOURCE_ACLK;
    initContParam.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
    initContParam.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_DISABLE;
    initContParam.timerClear = TIMER_A_DO_CLEAR;
    initContParam.startTimer = false;
    Timer_A_initContinuousMode(TIMER_A2_BASE, &initContParam);

}

void led_blink_freq(uint16_t freq)
{
    //Initiaze compare mode
    Timer_A_clearCaptureCompareInterrupt(TIMER_A2_BASE,
                                         TIMER_A_CAPTURECOMPARE_REGISTER_0
                                         );

    Timer_A_initCompareModeParam initCompParam = {0};
    initCompParam.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_0;
    initCompParam.compareInterruptEnable = TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE;
    initCompParam.compareOutputMode = TIMER_A_OUTPUTMODE_OUTBITVALUE;
    initCompParam.compareValue = freq;
    Timer_A_initCompareMode(TIMER_A2_BASE, &initCompParam);

    Timer_A_startCounter(TIMER_A2_BASE,
                         TIMER_A_CONTINUOUS_MODE
                         );
}
