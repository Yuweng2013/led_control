/*
 * IR_check.c
 *
 *  Created on: 2017Äê12ÔÂ11ÈÕ
 *      Author: yuwen
 */




#include "IR_check.h"

void LDO_power_enable()
{
    //ENABLE P7.4 as high output
    GPIO_setAsOutputPin(
        GPIO_PORT_P7,
        GPIO_PIN4
        );

    GPIO_setOutputHighOnPin(
        GPIO_PORT_P7,
        GPIO_PIN4
        );
}


void IR_port_initial()
{
    // Set P3.5 P3.6 to input direction
    GPIO_setAsInputPin(
        GPIO_PORT_P3,
        GPIO_PIN5 + GPIO_PIN6
        );
    //P2.0 set as capture input
//    GPIO_setAsPeripheralModuleFunctionOutputPin(
//        GPIO_PORT_P2,
//        GPIO_PIN0
//        );
    P2DIR &= ~BIT0;
    P2SEL |= BIT0;

    //P1.5 as PWM output
    GPIO_setAsPeripheralModuleFunctionOutputPin(
        GPIO_PORT_P1,
        GPIO_PIN5
        );
}

void timerA0_period_duty_cycle_set(uint16_t period, uint16_t duty_cycle)
{
    //Generate PWM - Timer runs in Up mode
    Timer_A_outputPWMParam param = {0};
    param.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
    param.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
    param.timerPeriod = period;
    param.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_4;// TB0CCRx SET
    param.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
    param.dutyCycle = duty_cycle;
    Timer_A_outputPWM(TIMER_A0_BASE, &param);
}

void timerA1_capture_mode_initial()
{
    Timer_A_initContinuousModeParam initContParam = {0};
    initContParam.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
    initContParam.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
    initContParam.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_DISABLE;
    initContParam.timerClear = TIMER_A_DO_CLEAR;
    Timer_A_initContinuousMode(TIMER_A1_BASE, &initContParam);

    Timer_A_startCounter(TIMER_A1_BASE,
                         TIMER_A_CONTINUOUS_MODE
                         );

    Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE,
                                         TIMER_A_CAPTURECOMPARE_REGISTER_1);

    Timer_A_initCaptureModeParam initCapParam = {0};
    initCapParam.captureRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;   //CCI1A input
    initCapParam.captureMode = TIMER_A_CAPTUREMODE_RISING_EDGE;
    initCapParam.captureInputSelect = TIMER_A_CAPTURE_INPUTSELECT_CCIxA;
    initCapParam.synchronizeCaptureSource = TIMER_A_CAPTURE_SYNCHRONOUS;
    initCapParam.captureInterruptEnable = TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE;
    initCapParam.captureOutputMode = TIMER_A_OUTPUTMODE_OUTBITVALUE;

    Timer_A_initCaptureMode(TIMER_A1_BASE, &initCapParam);
}


