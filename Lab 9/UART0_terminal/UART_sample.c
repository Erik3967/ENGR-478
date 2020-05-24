#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "inc/tm4c123gh6pm.h"
#include "driverlib/uart.h"

#define 	RED_MASK 			0x02
#define 	BLUE_MASK 		0x04
#define 	GREEN_MASK 		0x08


volatile char newChar;
void PortFunctionInit(void)
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
	
	// Set the direction of LED outputs
    GPIO_PORTF_DIR_R |= 0x0E;
		
    // Enable PF4, PF3, PF2, PF1 and PF0 for digital function.
    GPIO_PORTF_DEN_R |= 0x1F;
	
		//Enable pull-up on PF0
		GPIO_PORTF_PUR_R |= 0x01; 

		//Enable pull-up on PF0
		GPIO_PORTF_PUR_R |= 0x10; 

}

void UART_int_init()
{
	  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);


    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
		UARTFlowControlSet(UART0_BASE,UART_FLOWCONTROL_RX);
	
		IntPrioritySet(INT_UART0, 0x00);
    IntMasterEnable(); //enable processor interrupts
    IntEnable(INT_UART0); //enable the UART interrupt
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT); //only enable RX and TX interrupts

}


void UARTIntHandler(void)
{
    uint32_t ui32Status;
    UARTIntClear(UART0_BASE, ui32Status); //clear the asserted interrupts
    ui32Status = UARTIntStatus(UART0_BASE, true); //get interrupt status
	
		while(UARTCharsAvail(UART0_BASE)) //loop while there are chars
		{
		newChar = UARTCharGet(UART0_BASE);
			
		}

}

void UARTStringPut(char arr[], int size){
	for(int i = 0; i < size; i++)
	{
		UARTCharPut(UART0_BASE, arr[i]);
	}
}

int main(void) {
	
		uint8_t LED_tog;
		bool r_led;
		bool b_led;
		bool g_led;
		PortFunctionInit();
	  SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

		UART_int_init();

	UARTStringPut("\rEnter Text:\t", 13);
		
	
		while (1) //let interrupt handler do the UART echo function
		{
			// if (UARTCharsAvail(UART0_BASE)) UARTCharPut(UART0_BASE, UARTCharGet(UART0_BASE));
		if (newChar != NULL) 
			{
				
			switch (newChar) 
		{
			case 'R':
				GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1); // Red LED ON
				UARTCharPut(UART0_BASE, newChar); // prints R to terminal
				break;
			case 'r':
				GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0); // Red LED OFF
				UARTCharPut(UART0_BASE, newChar); // prints r to terminal
				break;
			case 'B':
				GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2); // Blue LED on
				UARTCharPut(UART0_BASE, newChar); // prints B to terminal
				break;
			case 'b':
				GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0); // Blue LED OFF
				UARTCharPut(UART0_BASE, newChar); // prints b to terminal
				break;
			case 'G':
				GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3,
					GPIO_PIN_3); // Green LED ON
				UARTCharPut(UART0_BASE, newChar); // prints G to terminal
				break;
			case 'g':
				GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0); // Green LED OFF
				UARTCharPut(UART0_BASE, newChar); // prints g to terminal
				break;
			case 't':
				GPIO_PORTF_DATA_R ^=RED_MASK;
				GPIO_PORTF_DATA_R ^=BLUE_MASK;
				GPIO_PORTF_DATA_R ^=GREEN_MASK;
				UARTCharPut(UART0_BASE, newChar); // prints g to terminal
				break;
			case 'o':
				GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0); // Green LED OFF
				GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0); // Blue LED OFF
				GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0); // red LED OFF
				UARTCharPut(UART0_BASE, newChar); // prints g to terminal
				break;
			case 'O':
				GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3); // Green LED ON
				GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2); // Blue LED ON
				GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1); // red LED On
				UARTCharPut(UART0_BASE, newChar); // prints g to terminal
				break;
			case 'm':
				UARTStringPut("m - ", 4);
					r_led = false;
					b_led = false;
					g_led = false;
				while(1)
				{
					if(newChar != NULL && newChar != 'm')
					{
						if(newChar == '\r')
							break;
						switch(newChar)
						{
							case 'r':
								if(r_led == false)
								{
									r_led = true;
									UARTCharPut(UART0_BASE, newChar); // prints r to terminal
								}
								break;
							case 'b':
								if(b_led == false)
								{
									b_led = true;
									UARTCharPut(UART0_BASE, newChar); // prints b to terminal
								}
								break;
							case 'g':
								if(g_led == false)
								{
									g_led = true;
									UARTCharPut(UART0_BASE, newChar); // prints g to terminal
								}
								break;
						}
					}
				}
				if(r_led)
					GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0); // red LED OFF
				if(b_led)
					GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0); // blue LED OFF
				if(g_led)
					GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0); // green LED OFF
				break;
				case 'M':
				UARTStringPut("M - ", 4);
					r_led = false;
					b_led = false;
					g_led = false;
				while(1)
				{
					if(newChar != NULL && newChar != 'M')
					{
						if(newChar == '\r')
							break;
						switch(newChar)
						{
							case 'R':
								if(r_led == false)
								{
									r_led = true;
									UARTCharPut(UART0_BASE, newChar); // prints  to terminal
								}
								break;
							case 'B':
								if(b_led == false)
								{
									b_led = true;
									UARTCharPut(UART0_BASE, newChar); // prints b to terminal
								}
								break;
							case 'G':
								if(g_led == false)
								{
									g_led = true;
									UARTCharPut(UART0_BASE, newChar); // prints g to terminal
								}
								break;
						}
					}
				}
				if(r_led)
					GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1); // red LED ON
				if(b_led)
					GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2); // blue LED ON
				if(g_led)
					GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3); // green LED OFF
				break;
			default: // prints Invalid Input to terminal
				UARTCharPut(UART0_BASE, newChar);
				UARTStringPut(" - Invalid Input", 16);
				break;
		}
			newChar = NULL;
			
		UARTStringPut("\n\rEnter Text:\t", 14);
		}
		}

}
