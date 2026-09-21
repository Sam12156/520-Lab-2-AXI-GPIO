/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xgpio.h"

#define LED_DELAY (50000000)

int main()
{
	XGpio LEDs, RGB, SWS;
    int Status;
    int SWS_status;
    int prev_SWS_status = -1;
    volatile int delay;

    init_platform();

    xil_printf("Hello World\r\n");

    // Refer to xparameters.h
    Status = XGpio_Initialize(&LEDs, XPAR_AXI_GPIO_0_DEVICE_ID);


    if (Status != XST_SUCCESS)
    {
        xil_printf("LEDs Initialization Failed.\r\n");
        return XST_FAILURE;
    }

    xil_printf("LEDs has successfully initialized.\r\n");

    Status = XGpio_Initialize(&RGB, XPAR_AXI_GPIO_1_DEVICE_ID);


    if (Status != XST_SUCCESS)
    {
        xil_printf("RGB Initialization Failed.\r\n");
        return XST_FAILURE;
    }

    xil_printf("RGB has successfully initialized.\r\n");

    Status = XGpio_Initialize(&SWS, XPAR_AXI_GPIO_2_DEVICE_ID);


    if (Status != XST_SUCCESS)
    {
        xil_printf("SWS Initialization Failed.\r\n");
        return XST_FAILURE;
    }

    xil_printf("SWS has successfully initialized.\r\n");

    // Refer to xgpio.c for function implementation
    XGpio_SetDataDirection(&LEDs, 1, 0x0);
    XGpio_SetDataDirection(&RGB, 1, 0x0);
    XGpio_SetDataDirection(&SWS, 1, 0xF);

    while(1)
    {
    	SWS_status = XGpio_DiscreteRead(&SWS,1);

        if (SWS_status != prev_SWS_status)
        {
            xil_printf("SWS: 0x%X\r\n", SWS_status);
            prev_SWS_status = SWS_status;
        }

        switch(SWS_status)
        {
            case 0x01:
            {
            	XGpio_DiscreteWrite(&LEDs, 1, 0x1);
            	XGpio_DiscreteWrite(&RGB, 1, 0x4);

            }
            break;

            case 0x02:
            {
            	XGpio_DiscreteWrite(&LEDs, 1, 0x2);
            	XGpio_DiscreteWrite(&RGB, 1, 0x2);

            }
            break;

            case 0x04:
            {
            	XGpio_DiscreteWrite(&LEDs, 1, 0x4);
            	XGpio_DiscreteWrite(&RGB, 1, 0x1);

            }
            break;

            case 0x08:
            {
            	XGpio_DiscreteWrite(&LEDs, 1, 0x8);
            	XGpio_DiscreteWrite(&RGB, 1, 0x7);

            }
            break;

            case 0x03:
            {

            	XGpio_DiscreteWrite(&RGB, 1, 0x0);
                for (int led_count = 0x0; led_count <= 0xF; led_count++)
                {
                	XGpio_DiscreteWrite(&LEDs, 1, led_count);
                	xil_printf("LED: 0x%X\r\n", led_count);
                	for (delay = 0; delay < LED_DELAY; delay++);// Wait a small amount of time
                    if (XGpio_DiscreteRead(&SWS,1) != 0x3)
                    {
                        break;
                    }
                }

            }
            break;

            case 0x0C:
            {

            	XGpio_DiscreteWrite(&RGB, 1, 0x0);
                for (int led_count = 0x1; led_count <= 0x8; led_count <<= 1)
                {
                	XGpio_DiscreteWrite(&LEDs, 1, led_count);
                	xil_printf("LED: 0x%X\r\n", led_count);
                	for (delay = 0; delay < LED_DELAY; delay++);// Wait a small amount of time
                    if (XGpio_DiscreteRead(&SWS,1) != 0xC)
                    {
                        break;
                    }
                }
            }
            break;
            default:
            {

            	XGpio_DiscreteWrite(&LEDs, 1, 0x0);
            	XGpio_DiscreteWrite(&RGB, 1, 0x0);
            }
        }

    }
}
