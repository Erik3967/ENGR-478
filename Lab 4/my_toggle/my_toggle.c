#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "inc/tm4c123gh6pm.h"
#include "driverlib/sysctl.h"

#define 	RED_MASK 		0x02
#define 	BLUE_MASK 	0x04
#define 	GREEN_MASK 	0x08
//*****************************************************************************
//
//!
//! A very simple example that toggles the on-board red LED using direct register
//! access.
//
//*****************************************************************************


void
PortFunctionInit(void)
{
//
		volatile uint32_t ui32Loop;   
	// Enable the GPIO port that is used for the on-board LED.
    //
    SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;

    //
    // Do a dummy read to insert a few cycles after enabling the peripheral.
    //
    ui32Loop = SYSCTL_RCGC2_R;

    //
    // Enable the GPIO pin for the red LED (PF1).  Set the direction as output, and
    // enable the GPIO pin for digital function.
    //
    GPIO_PORTF_DIR_R |= 0x02;
    GPIO_PORTF_DEN_R |= 0x02;
		GPIO_PORTF_DIR_R |= 0x04;
    GPIO_PORTF_DEN_R |= 0x04;
		GPIO_PORTF_DIR_R |= 0x08;
    GPIO_PORTF_DEN_R |= 0x08;

}


int main(void)
{
	
		//initialize the GPIO ports	
		PortFunctionInit();
	
		int state = 0;
	
    // Turn on the LED.
    //GPIO_PORTF_DATA_R |= 0x02;
		//GPIO_PORTF_DATA_R |= 0x04;
		//GPIO_PORTF_DATA_R |= 0x08;

    
    //
    // Loop forever.
    //
    while(1)
    {
        // Delay for a bit.
				//SysCtlDelay(2000000);	

				state = rand() % 7 ;
			
        
			
			switch(state)
						{
							case 0:
								
								GPIO_PORTF_DATA_R ^= RED_MASK;
								SysCtlDelay(2000000);
								GPIO_PORTF_DATA_R ^= RED_MASK;
								SysCtlDelay(2000000);
								break;
							case 1:
								GPIO_PORTF_DATA_R ^= BLUE_MASK;
								SysCtlDelay(2000000);
								GPIO_PORTF_DATA_R ^= BLUE_MASK;
								SysCtlDelay(2000000);
								break;
							case 2:
								GPIO_PORTF_DATA_R ^= GREEN_MASK;
								SysCtlDelay(2000000);
								GPIO_PORTF_DATA_R ^= GREEN_MASK;
								SysCtlDelay(2000000);
								break;
							case 3:
								GPIO_PORTF_DATA_R ^= RED_MASK;
								GPIO_PORTF_DATA_R ^= BLUE_MASK;
								SysCtlDelay(2000000);
								GPIO_PORTF_DATA_R ^= RED_MASK;
								GPIO_PORTF_DATA_R ^= BLUE_MASK;
								SysCtlDelay(2000000);
								break;
							case 4:
								GPIO_PORTF_DATA_R ^= RED_MASK;
								GPIO_PORTF_DATA_R ^= GREEN_MASK;
								SysCtlDelay(2000000);
								GPIO_PORTF_DATA_R ^= RED_MASK;
								GPIO_PORTF_DATA_R ^= GREEN_MASK;
								SysCtlDelay(2000000);
								break;
							case 5:
								GPIO_PORTF_DATA_R ^= BLUE_MASK;
								GPIO_PORTF_DATA_R ^= GREEN_MASK;
								SysCtlDelay(2000000);
								GPIO_PORTF_DATA_R ^= BLUE_MASK;
								GPIO_PORTF_DATA_R ^= GREEN_MASK;
								SysCtlDelay(2000000);
								break;
							case 6:
								GPIO_PORTF_DATA_R ^= RED_MASK;
								GPIO_PORTF_DATA_R ^= BLUE_MASK;
								GPIO_PORTF_DATA_R ^= GREEN_MASK;
								SysCtlDelay(2000000);
								GPIO_PORTF_DATA_R ^= RED_MASK;
								GPIO_PORTF_DATA_R ^= BLUE_MASK;
								GPIO_PORTF_DATA_R ^= GREEN_MASK;
								SysCtlDelay(2000000);
								break;
						}
    }
}
