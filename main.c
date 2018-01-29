/*
 * latest update on Jan. 5th 2018 by Yuwen
 */


#include "driverlib.h"
#include "led.h"
#include "IR_check.h"
#include "rs485.h"
#include "data_pack.h"
#include "flash.h"
#include "rtc.h"
#include "crc.h"


/*
 * IR transmiting frequency is determined by IR_TIMER_PERIOD on 38kHz
 */
#define IR_TIMER_PERIOD 210
#define IR_DUTY_CYCLE   50

#define COMPARE_VALUE 50000


#define IR_DELAY_LEVEL_1 40
#define IR_DELAY_LEVEL_2 20
#define IR_DELAY_LEVEL_3 10
#define IR_DELAY_LEVEL_4 5


//
#define UART_MODE_0                             0x00
#define UART_MODE_1                             0x01

#define USCI_A_UART_MULTIPROCESSOR_MODE_ADDRESS_H        0x41
#define USCI_A_UART_MULTIPROCESSOR_MODE_ADDRESS_C        0x30


//uint16_t blink_level = BLINK_LEVEL_2;
uint16_t brightness_level = BRIGHTNESS_LEVEL_6;
uint16_t IR_delay_level = 0x08;
uint8_t work_mode;
uint8_t flag_LED = 1;
uint8_t flag_IR = 0;
uint8_t flag_MODE = 1;
uint8_t flag_IR_TEMP = 0;
uint16_t flag_IR_DELAY = 0;
uint8_t flag_UART = 0;
uint8_t flag_minute = 0;
uint8_t flag_second = 0;
uint8_t flag_BLINK = 0;
uint8_t flag_odd_sec = 0;
uint8_t flag_30time = 0;

uint16_t status;

//variable declaration for rs485
uint8_t receivedData = 0x00;
uint8_t transmitData = 0x00;
uint8_t R_data[20] = {0x08,'5','7','3','2',0x11,0x0B,0x1A,0x02,0x10,0x21,0x3B,0xE7};
uint8_t i = 0x00;
uint8_t receiveData_flag = 0x00;
uint8_t crc8_reg = 0x00;

/*
 * variable declaration for capturing the check time
 */
uint8_t flag_cap = 0;
uint16_t over_flow = 0;
uint16_t temp_capture = 0;
uint32_t freq_count = 0;


//*****************************************************************************
//
//Dummy char array of 'calibration data' - to be stored in flash
//
//*****************************************************************************
uint8_t infoB_count = 0;
uint16_t REdge = 0;

Calendar newTime;

void main(void)
{
    //Stop WDT
    WDT_A_hold(WDT_A_BASE);
    rtc_clock_initial();
    DCO_set_to_8MHz();

    led_enable(flag_LED);
    LDO_power_enable();                 //open LDO and wait for 75us to enable
    __delay_cycles(75);




//********************** IR initialization

    IR_port_initial();                  //port initial on IR sending and receiving port
//    timerA0_period_duty_cycle_set(IR_TIMER_PERIOD, IR_DUTY_CYCLE);
//    timerA1_capture_mode_initial();


//***********************

//***********************    UART MODE initialization
    set_rs485_as_receiver();
    usci_A_uart_initial();

    //Enable UART module for operation
    USCI_A_UART_enable(USCI_A1_BASE);

    //Set USCI UART in dormant/sleep mode
    USCI_A_UART_setDormant(USCI_A1_BASE);

    //Enable Receive Interrupt
    USCI_A_UART_clearInterrupt(USCI_A1_BASE,
                               USCI_A_UART_RECEIVE_INTERRUPT);
    USCI_A_UART_enableInterrupt(USCI_A1_BASE,
                                USCI_A_UART_RECEIVE_INTERRUPT);
//***********************

    for(infoB_count = 0; infoB_count < 20; infoB_count++)
        R_data[infoB_count] = ReadSegment_256(infoB_count);

    work_mode = R_data[1];              //work mode selection depending on bit 1
    if(work_mode == 0x00 || work_mode ==0xff)
        work_mode = 0x31;
/*
 * rtc initialization
 */
    rtc_interrupt_initial();

//***********************    Generate PWM - LED Timer runs in Up mode
    timer_b_initial(LED_TIMER_PERIOD);

    timer_A2_initial();
//***********************

    // Enable global oscillator fault flag
    SFR_clearInterrupt(SFR_OSCILLATOR_FAULT_INTERRUPT);
    SFR_enableInterrupt(SFR_OSCILLATOR_FAULT_INTERRUPT);

    __bis_SR_register(GIE);       // interrupts enabled
    while(1)
    {
        current_time_initial_set(R_data);
        //Start RTC Clock
        RTC_A_startClock(RTC_A_BASE);

        /*
         * crc8 У��
         */
        CRC_8(R_data, 13, &crc8_reg);
        if(crc8_reg != 0)
        {
            work_mode = '0';
            crc8_reg = 0;
        }
        else
        {
            work_mode = R_data[1];              //work mode selection depending on bit 1
            crc8_reg = 0;
        }


        WriteSegment(R_data, 20);

        switch(work_mode)
        {
        case '0':
            led1_stop();
            led2_stop();
            Timer_A_stop(TIMER_A2_BASE);
            __bis_SR_register(LPM0);       // Enter LPM0
            break;
        case '1':
            flag_UART = 0;
            flag_second = 0;
            flag_minute = 0;

            flag_BLINK = 0;
            led1_stop();
            led2_stop();
            led1_brightness_level_set(brightness_set(R_data[2]));
            while(!flag_second);

            TA2CTL |= TACLR;                                    //clear the TA2R to restart the caculation
            led_blink_freq(blink_level_set(R_data[4]));         //start blink timer A2 and set the frequency
            while(!flag_UART)
            {

                if(flag_minute)
                {
                    flag_minute = 0;
                    flag_second = 0;
                    while(!flag_second);

                    flag_BLINK = 0;
                    TA2CTL |= TACLR;                                    //clear the TA2R to restart the caculation
                    led_blink_freq(blink_level_set(R_data[4]));         //start blink timer A2 and set the frequency
                }
                if(!flag_BLINK)
                    led1_shinning();

                else
                    led1_stop();
                __bis_SR_register(LPM0);       // Enter LPM0
            }
            break;
        case '2':
            flag_UART = 0;
            flag_second = 0;
            flag_minute = 0;

            flag_BLINK = 0;
            led1_stop();
            led2_stop();
            led2_brightness_level_set(brightness_set(R_data[3]));
            while(!flag_second);

            TA2CTL |= TACLR;                                    //clear the TA2R to restart the caculation
            led_blink_freq(blink_level_set(R_data[4]));         //start blink timer A2 and set the frequency
            while(!flag_UART)
            {

                if(flag_minute)
                {
                    flag_minute = 0;
                    flag_second = 0;
                    while(!flag_second);

                    flag_BLINK = 0;
                    TA2CTL |= TACLR;                                    //clear the TA2R to restart the caculation
                    led_blink_freq(blink_level_set(R_data[4]));         //start blink timer A2 and set the frequency
                }
                if(!flag_BLINK)
                    led2_shinning();

                else
                    led2_stop();
                __bis_SR_register(LPM0);       // Enter LPM0
            }

            break;
        case '3':
            flag_UART = 0;
            Timer_A_stop(TIMER_A2_BASE);
            led2_stop();
            led1_brightness_level_set(brightness_set(R_data[2]));
            led1_shinning();
            __bis_SR_register(LPM0);       // Enter LPM0
            break;
        case '4':
            flag_UART = 0;
            Timer_A_stop(TIMER_A2_BASE);
            led1_stop();
            led2_brightness_level_set(brightness_set(R_data[3]));
            led2_shinning();
            __bis_SR_register(LPM0);       // Enter LPM0
            break;
        case '5':
            flag_UART = 0;
            flag_second = 0;
            flag_minute = 0;
            flag_BLINK = 0;
            flag_IR_TEMP = 1;
            flag_odd_sec = 1;
            flag_30time = blink_30time_judge(R_data[4]);

            led1_stop();
            led2_stop();

            timerA0_period_duty_cycle_set(IR_TIMER_PERIOD, IR_DUTY_CYCLE);
            timerA1_capture_mode_initial();

            led1_brightness_level_set(brightness_set(R_data[2]));
            led2_brightness_level_set(brightness_set(R_data[3]));
            flag_IR = 0;
            while(!flag_UART)
            {
                if(flag_30time == 1)
                {
                    if(flag_IR)
                    {
                        if(flag_IR != flag_IR_TEMP)             //��������жϣ�������״̬�仯��ʱ������ظ�����
                            {
                                flag_IR_TEMP = flag_IR;
                                led1_stop();
                            }
                        flag_IR = 0;
                        flag_second = 0;

                        IR_delay_level = IR_delay_level_set(freq_count, R_data[4])/2;
                        for(flag_IR_DELAY = 0;flag_IR_DELAY < IR_delay_level;flag_IR_DELAY++) //�����ʱ���ã����ݺ�����������趨��ʱ
                            {
                                while(!flag_second)
                                    if(flag_UART)break;             //work mode change TIMELY
                                if(flag_UART)break;             //work mode change TIMELY
                                led2_shinning();
                                flag_second = 0;

                                while(!flag_second)
                                    if(flag_UART)break;             //work mode change TIMELY
//                                led2_stop();
                                if(flag_UART)break;             //work mode change TIMELY
                                if(flag_IR)break;               //IR check TIMELY
                                flag_second = 0;
                            }
                    }
                    else
                    {
                        if(flag_IR != flag_IR_TEMP)             //��������жϣ�������״̬�仯��ʱ������ظ�����
                        {
                            flag_IR_TEMP = flag_IR;
                            led2_stop();
                        }

                        while(!flag_second)
                            if(flag_UART)break;             //work mode change TIMELY
                        led1_shinning();
                        flag_second = 0;

                        while(!flag_second)
                            if(flag_UART)break;             //work mode change TIMELY
                        led1_stop();
                        flag_second = 0;
                    }

                }
                else
                {
                    if(flag_IR)
                    {
                        if(flag_IR != flag_IR_TEMP)             //��������жϣ�������״̬�仯��ʱ������ظ�����
                            {
                                flag_IR_TEMP = flag_IR;
                                led1_stop();
                                flag_minute = 0;
                                flag_second = 0;
                                while(!flag_second);

                                flag_BLINK = 0;
                                TA2CTL |= TACLR;                                    //clear the TA2R to restart the caculation
                                led_blink_freq(blink_level_set(R_data[4]));         //start blink timer A2 and set the frequency
                            }
                        flag_IR = 0;

                        IR_delay_level = IR_delay_level_set(freq_count, R_data[4]);
                        for(flag_IR_DELAY = 0;flag_IR_DELAY < IR_delay_level;flag_IR_DELAY++) //�����ʱ���ã����ݺ�����������趨��ʱ
                            {
                                if(!flag_BLINK)
                                    led2_shinning();
//                                else
//                                    led2_stop();
                                __bis_SR_register(LPM0);        // Enter LPM0
                                if(flag_UART)break;             //work mode change TIMELY
                                if(flag_IR)break;               //IR check TIMELY
                            }
                    }
                    else
                    {
                        if(flag_IR != flag_IR_TEMP)             //��������жϣ�������״̬�仯��ʱ������ظ�����
                        {
                            flag_IR_TEMP = flag_IR;
                            led2_stop();
                            flag_second = 0;
                            while(!flag_second);

                            flag_BLINK = 0;
                            TA2CTL |= TACLR;                                    //clear the TA2R to restart the caculation
                            led_blink_freq(blink_level_set(R_data[4]));         //start blink timer A2 and set the frequency
                        }

                        if(!flag_BLINK)
                            led1_shinning();
                        else
                            led1_stop();
                        __bis_SR_register(LPM0);       // Enter LPM0
//                        TA1CCTL1 |= CCIE;
//                        TA1CTL |= TAIE;
                    }

                }
                TA1CCTL1 |= CCIE;
                TA1CTL |= TAIE;
            }
            Timer_A_stop(TIMER_A0_BASE);
            Timer_A_stop(TIMER_A1_BASE);
            break;
        default:
            led1_stop();
            led2_stop();
            Timer_A_stop(TIMER_A2_BASE);
            __bis_SR_register(LPM0);       // Enter LPM0
            break;

        }


    }

}


//******************************************************************************
//
//This is the USCI_A1 interrupt vector service routine.
//
//******************************************************************************
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_A1_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(USCI_A0_VECTOR)))
#endif
void USCI_A1_ISR(void)
{
    switch(__even_in_range(UCA1IV,4))
    {
    //Vector 2 - RXIFG
    case 2:
        receivedData = USCI_A_UART_receiveData(USCI_A1_BASE);

        if(receiveData_flag)
        {
            R_data[i] = receivedData;
            i++;
            if(receivedData == 0x7E)
            {
//                rs485_data_package_sent(R_data,i);  //echo data back (also data processing for main.c)
//                work_mode = R_data[1];              //work mode selection depending on bit 1
                flag_UART = 1;
                //Set USCI module in dormant mode
                USCI_A_UART_setDormant(USCI_A1_BASE);
                receiveData_flag = 0x00;


                i=0;            //��λΪ0���Ա����½�������
                LPM0_EXIT;
            }
        }
        else
        {
            if(USCI_A_UART_MULTIPROCESSOR_MODE_ADDRESS_H == receivedData || USCI_A_UART_MULTIPROCESSOR_MODE_ADDRESS_C == receivedData)
            {
                //Wake up USCI module from dormant mode
                USCI_A_UART_resetDormant(USCI_A1_BASE);
                receiveData_flag = 0x01;
                i = 0;
            }
        }
        break;
    default: break;
    }
}


//******************************************************************************
//
//This is the Timer1_A1 interrupt vector service routine.
//
//******************************************************************************
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER1_A1_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(TIMER1_A1_VECTOR)))
#endif
void TIMER1_A1_ISR(void)
{

//    flag_IR = 1;
    switch(__even_in_range(TA1IV,14))
    {
    case 0:break;
    case 2:
        flag_cap++;
        if(flag_cap == 1)
        {
//            flag_IR = 1;
            over_flow = 0;
            TA1CTL |= TACLR; //�嶨ʱ������
        }
        else if(flag_cap == 2)
        {
            flag_IR = 1;
            temp_capture = TA1CCR1;
            freq_count = over_flow * 65536 + temp_capture;
            flag_cap = 0;
            TA1CCTL1 &= ~CCIFG; //����жϱ�־λ
        }
//        TA1CCTL1 &= ~CCIFG; //����жϱ�־λ
        break;

    case 14:
        over_flow++;
        break;

    default:break;
    }

}

//******************************************************************************
//
//This is the RTC_A interrupt vector service routine.
//
//******************************************************************************
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=RTC_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(RTC_VECTOR)))
#endif
void RTC_A_ISR(void)
{
    switch(__even_in_range(RTCIV,16))
    {
    case 0: break;      //No interrupts
    case 2:             //RTCRDYIFG
        flag_second = 1;
        break;
    case 4:             //RTCEVIFG
        //Interrupts every minute
        flag_minute = 1;
        //Read out New Time a Minute Later BREAKPOINT HERE
//        newTime = RTC_A_getCalendarTime(RTC_A_BASE);
        break;
    case 6:             //RTCAIFG
        //Interrupts 5:00pm on 5th day of week
        __no_operation();
        break;
    case 8: break;      //RT0PSIFG
    case 10: break;     //RT1PSIFG
    case 12: break;     //Reserved
    case 14: break;     //Reserved
    case 16: break;     //Reserved
    default: break;
    }
//    LPM0_EXIT;
}


//******************************************************************************
//
//This is the TIMER2_A0 interrupt vector service routine.
//
//******************************************************************************
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER2_A0_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(TIMER1_A0_VECTOR)))
#endif
void TIMER2_A0_ISR(void)
{
    uint16_t compVal = Timer_A_getCaptureCompareCount(TIMER_A2_BASE,
                                                      TIMER_A_CAPTURECOMPARE_REGISTER_0)
                       + blink_level_set(R_data[4]);
    if(flag_BLINK)
        flag_BLINK = 0;
    else
        flag_BLINK = 1;

    //Add Offset to CCR0
    Timer_A_setCompareValue(TIMER_A2_BASE,
                            TIMER_A_CAPTURECOMPARE_REGISTER_0,
                            compVal
                            );
    LPM0_EXIT;
}

//******************************************************************************
//
//This is the flag_failure interrupt vector service routine.
//
//******************************************************************************
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=UNMI_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(UNMI_VECTOR)))
#endif
void NMI_ISR(void)
{
    do
    {
        // If it still can't clear the oscillator fault flags after the timeout,
        // trap and wait here.
        status = UCS_clearAllOscFlagsWithTimeout(1000);
    }
    while(status != 0);
}
