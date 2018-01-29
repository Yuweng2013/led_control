/*
 * rs485.c
 *
 *  Created on: 2017��11��18��
 *      Author: yuwen
 */




#include "rs485.h"

void usci_A_uart_initial()
{
    //P4.4,5 = USCI_A1 TXD/RXD
    GPIO_setAsPeripheralModuleFunctionInputPin(
        GPIO_PORT_P4,
        GPIO_PIN4 + GPIO_PIN5
        );

    //Initialize USCI UART module

       //Baudrate = 9600, clock freq = 8MHz
       //UCBRx = 833, UCBRFx = 0, UCBRSx = 2, UCOS16 = 0
       USCI_A_UART_initParam param = {0};
       param.selectClockSource = USCI_A_UART_CLOCKSOURCE_SMCLK;
       param.clockPrescalar = 833;
       param.firstModReg = 0;
       param.secondModReg = 2;
       param.parity = USCI_A_UART_NO_PARITY;
       param.msborLsbFirst = USCI_A_UART_LSB_FIRST;
       param.numberofStopBits = USCI_A_UART_ONE_STOP_BIT;
       param.uartMode = USCI_A_UART_IDLE_LINE_MULTI_PROCESSOR_MODE;
       param.overSampling = USCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION;

        // //Baudrate = 9600, clock freq = 1.048MHz
        // //UCBRx = 6, UCBRFx = 13, UCBRSx = 0, UCOS16 = 1
        // USCI_A_UART_initParam param = {0};
        // param.selectClockSource = USCI_A_UART_CLOCKSOURCE_SMCLK;
        // param.clockPrescalar = 6;
        // param.firstModReg = 13;
        // param.secondModReg = 0;
        // param.parity = USCI_A_UART_NO_PARITY;
        // param.msborLsbFirst = USCI_A_UART_LSB_FIRST;
        // param.numberofStopBits = USCI_A_UART_ONE_STOP_BIT;
        // param.uartMode = USCI_A_UART_IDLE_LINE_MULTI_PROCESSOR_MODE;
        // param.overSampling = USCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION;


    if(STATUS_FAIL == USCI_A_UART_init(USCI_A1_BASE, &param))
    {
        return;
    }

}

void set_rs485_as_driver()
{
    //ENABLE P1.7 as high output
        GPIO_setAsOutputPin(
            GPIO_PORT_P1,
            GPIO_PIN6 + GPIO_PIN7
            );

        GPIO_setOutputHighOnPin(
            GPIO_PORT_P1,
            GPIO_PIN6 + GPIO_PIN7
            );

}


void set_rs485_as_receiver()
{
    //ENABLE P1.6 as low output
        GPIO_setAsOutputPin(
            GPIO_PORT_P1,
            GPIO_PIN6 + GPIO_PIN7
            );

        GPIO_setOutputLowOnPin(
            GPIO_PORT_P1,
            GPIO_PIN6 + GPIO_PIN7
            );

}

void rs485_data_package_sent(uint8_t data_package[20],uint8_t count)
{
    uint8_t j=0;            //��λΪ0����0λ�ÿ�ʼ��������

    __delay_cycles(1000);   //������ʱȷ������״̬���������߿��У��ٸı�����״̬
    set_rs485_as_driver();
    while(j<count-1)
    {
        USCI_A_UART_transmitData(USCI_A1_BASE,
                                 data_package[j++]);
        __delay_cycles(75);
    }
    __delay_cycles(2000);   //������ʱȷ������״̬���������߿��У��ٸı�����״̬
    set_rs485_as_receiver();
}

