//*****************************************************************************
// Copyright (c) 2014 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
//   Redistribution and use in source and binary forms, with or without
//   modification, are permitted provided that the following conditions
//   are met:
// 
//   Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the  
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// This file was automatically generated by the Tiva C Series PinMux Utility
// Version: 1.0.4
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "switch_PinMux.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom_map.h"
#include "driverlib/gpio.h"
#include "inc/tm4c123gh6pm.h"

#define	RED_MASK  0x02
#define BLUE_MASK  0x04
#define GREEN_MASK  0x08
//*****************************************************************************
void
PortFunctionInit(void)
{
    //
    // Enable Peripheral Clocks 
    //
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    //
    // Enable pin PF0 for GPIOInput
    //

    //
    //First open the lock and select the bits we want to modify in the GPIO commit register.
    //
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) = 0x1;

    //
    //Now modify the configuration of the pins that we unlocked.
    //
    MAP_GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0);

    //
    // Enable pin PF2 for GPIOOutput
    //
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);

    //
    // Enable pin PF3 for GPIOOutput
    //
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);

    //
    // Enable pin PF1 for GPIOOutput
    //
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);

    //
    // Enable pin PF4 for GPIOInput
    //
    MAP_GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
		
		GPIO_PORTF_PUR_R |= 0x01;
		GPIO_PORTF_PUR_R |= 0x10;
}

int main(void)
{
	
		//initialize the GPIO ports	
		PortFunctionInit();
		uint8_t LED_tog;
	
		int state = 0;
	  bool pressed = false;
		int temp;
		int timer = 0;
    //
    // Loop forever.
    //
    while(1)
    {
			
			if((GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0) == 0x00 )|| GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) == 0x00) //SW2 is pressed
				{
						// Turn off the LED.
					if(!pressed)
					{
					
						switch(state)
							{
								case 0:
									GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);
									break;
								case 1:
									GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x00);
									break;
								case 2:
									GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
									break;
								case 3:
									GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);
									GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x00);
									break;
								case 4:
									GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);
									GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
									break;
								case 5:
									GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x00);
									GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
									break;
								case 6:
									GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);
									GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x00);
									GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
									break;
								case 7:
									GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);
									GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x00);
									GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
									break;
								case 8:
									GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);
									GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x00);
									GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
									break;
							}
						state++;
						pressed = true;
						SysCtlDelay(500);	
					}
				}
				else
				{
					pressed = false;
						switch(state)
						{
							case 0:
								
								GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, RED_MASK);
								break;
							case 1:
								GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, BLUE_MASK);
								break;
							case 2:
								GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GREEN_MASK);
								break;
							case 3:
								GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, RED_MASK);
								GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, BLUE_MASK);
								break;
							case 4:
								GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, RED_MASK);
								GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GREEN_MASK);
								break;
							case 5:
								GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, BLUE_MASK);
								GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GREEN_MASK);
								break;
							case 6:
								GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, RED_MASK);
								GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, BLUE_MASK);
								GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GREEN_MASK);
								break;
							case 7:
									if (timer < 0) 
									{
										timer = 200000;
										temp = rand() % 3 ;
										if(temp == 0)
										{
											LED_tog ^= RED_MASK;
											GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, LED_tog);
										}
										else if(temp == 1)
										{
											LED_tog ^= BLUE_MASK;
											GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, LED_tog);
										}
										else
										{
											LED_tog ^= GREEN_MASK;
											GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, LED_tog);
										}
									}
									timer--;
								break;
								case 8:
									if (timer < 0) 
									{
										timer = 20000;
										temp = rand() % 3 ;
										if(temp == 0)
										{
											LED_tog ^= RED_MASK;
											GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, LED_tog);
										}
										else if(temp == 1)
										{
											LED_tog ^= BLUE_MASK;
											GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, LED_tog);
										}
										else
										{
											LED_tog ^= GREEN_MASK;
											GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, LED_tog);
										}
									}
									timer--;
								break;
							default:
								state = 0;
						}
						
							
				}
    }
}