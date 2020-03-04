#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "inc/tm4c123gh6pm.h"
#include "driverlib/sysctl.h"

#define 	RED_MASK 		0x02
#define 	BLUE_MASK 	0x04
#define 	GREEN_MASK 	0x08
//*****************************************************************************
//
//!
//! A very simple example that interfaces with the blud LED (PF2) and SW2 (PF0) 
//! using direct register access. When SW2 is pressed, the LED is turned on. When 
//! SW2 is released, the LED is turned off. 
//
//*****************************************************************************


void
PortFunctionInit(void)
{

		volatile uint32_t ui32Loop;   
	
		// Enable the clock of the GPIO port that is used for the on-board LED and switch.
    SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;

    //
    // Do a dummy read to insert a few cycles after enabling the peripheral.
    //
    ui32Loop = SYSCTL_RCGC2_R;

		// Unlock GPIO Port F
		GPIO_PORTF_LOCK_R = 0x4C4F434B;   
		GPIO_PORTF_CR_R |= 0x01;           // allow changes to PF0

    // Set the direction of PF1 (red LED) as output
    GPIO_PORTF_DIR_R |= 0x02;
	
    GPIO_PORTF_DIR_R |= 0x04;
    GPIO_PORTF_DIR_R |= 0x08;
	
		// Set the direction of PF0 (SW2) as input by clearing the bit
    GPIO_PORTF_DIR_R &= ~0x01;
	
    // Enable both PF3 and PF0 for digital function.
    GPIO_PORTF_DEN_R |= 0x03;
		
		GPIO_PORTF_DEN_R |= 0x05;
		GPIO_PORTF_DEN_R |= 0x09;
	
		//Enable pull-up on PF0
		GPIO_PORTF_PUR_R |= 0x01; 

}



int main(void)
{
		//initialize the GPIO ports	
		PortFunctionInit();
    //
		int state = 0;
	  bool pressed = false;
		int temp;
		int timer = 0;
	/*
		int delay = 1000 * (1); 
		clock_t last_time = clock(); 
		*/
    // Loop forever.
    //
    while(1)
    {
        if((GPIO_PORTF_DATA_R&0x01)==0x00) //SW2 is pressed
				{
						// Turn off the LED.
					if(!pressed)
					{
					
						switch(state)
							{
								case 0:
									GPIO_PORTF_DATA_R &= ~RED_MASK;
									break;
								case 1:
									GPIO_PORTF_DATA_R &= ~BLUE_MASK;
									break;
								case 2:
									GPIO_PORTF_DATA_R &= ~GREEN_MASK;
									break;
								case 3:
									GPIO_PORTF_DATA_R &= ~RED_MASK;
									GPIO_PORTF_DATA_R &= ~BLUE_MASK;
									break;
								case 4:
									GPIO_PORTF_DATA_R &= ~RED_MASK;
									GPIO_PORTF_DATA_R &= ~GREEN_MASK;
									break;
								case 5:
									GPIO_PORTF_DATA_R &= ~BLUE_MASK;
									GPIO_PORTF_DATA_R &= ~GREEN_MASK;
									break;
								case 6:
									GPIO_PORTF_DATA_R &= ~RED_MASK;
									GPIO_PORTF_DATA_R &= ~BLUE_MASK;
									GPIO_PORTF_DATA_R &= ~GREEN_MASK;
									break;
								case 7:
									GPIO_PORTF_DATA_R &= ~RED_MASK;
									GPIO_PORTF_DATA_R &= ~BLUE_MASK;
									GPIO_PORTF_DATA_R &= ~GREEN_MASK;
									break;
								case 8:
									GPIO_PORTF_DATA_R &= ~RED_MASK;
									GPIO_PORTF_DATA_R &= ~BLUE_MASK;
									GPIO_PORTF_DATA_R &= ~GREEN_MASK;
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
								
								GPIO_PORTF_DATA_R |= RED_MASK;
								break;
							case 1:
								GPIO_PORTF_DATA_R |= BLUE_MASK;
								break;
							case 2:
								GPIO_PORTF_DATA_R |= GREEN_MASK;
								break;
							case 3:
								GPIO_PORTF_DATA_R |= RED_MASK;
								GPIO_PORTF_DATA_R |= BLUE_MASK;
								break;
							case 4:
								GPIO_PORTF_DATA_R |= RED_MASK;
								GPIO_PORTF_DATA_R |= GREEN_MASK;
								break;
							case 5:
								GPIO_PORTF_DATA_R |= BLUE_MASK;
								GPIO_PORTF_DATA_R |= GREEN_MASK;
								break;
							case 6:
								GPIO_PORTF_DATA_R |= RED_MASK;
								GPIO_PORTF_DATA_R |= BLUE_MASK;
								GPIO_PORTF_DATA_R |= GREEN_MASK;
								break;
							case 7:
									if (timer < 0) 
									{
										timer = 200000;
										temp = rand() % 3 ;
										if(temp == 0)
											GPIO_PORTF_DATA_R ^= RED_MASK;
										else if(temp == 1)
											GPIO_PORTF_DATA_R ^= BLUE_MASK;
										else
											GPIO_PORTF_DATA_R ^= GREEN_MASK;
									}
									timer--;
								break;
								case 8:
									if (timer < 0) 
									{
										timer = 20000;
										temp = rand() % 3 ;
										if(temp == 0)
											GPIO_PORTF_DATA_R ^= RED_MASK;
										else if(temp == 1)
											GPIO_PORTF_DATA_R ^= BLUE_MASK;
										else
											GPIO_PORTF_DATA_R ^= GREEN_MASK;
									}
									timer--;
								break;
							default:
								state = 0;
						}
						
							
				}
    }
}
