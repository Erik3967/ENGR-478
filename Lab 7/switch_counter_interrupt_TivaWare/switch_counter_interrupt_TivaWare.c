#include <stdint.h>
#include <stdbool.h>
#include "switch_delay_interrupt_PinMux.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom_map.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "inc/tm4c123gh6pm.h"

#define RED_MASK 0x02
#define BLUE_MASK 0x04
#define GREEN_MASK 0x08
//*****************************************************************************
volatile unsigned long count = 0;
void PortFunctionInit(void)
{
	//
	// Enable Peripheral Clocks
	//
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	//
	// Enable pin PF2 for GPIOOutput
	//
	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);
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
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
	GPIOPinTypeGPIOOutput (GPIO_PORTF_BASE, GPIO_PIN_1);
	GPIOPinTypeGPIOOutput (GPIO_PORTF_BASE, GPIO_PIN_3);
	GPIOPinTypeGPIOOutput (GPIO_PORTF_BASE, GPIO_PIN_2);
	//
	// Enable pin PF4 for GPIOInput
	//
	MAP_GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
	//
	// Enable pin PF1 for GPIOOutput
	//
	
	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);
	
	//
	// Enable pin PF3 for GPIOOutput
	//
	
	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);
	//Enable pull-up on PF4 and PF0
	GPIO_PORTF_PUR_R |= 0x11;
}
void Interrupt_Init(void)
{
	IntEnable(INT_GPIOF); // enable interrupt 30 in NVIC (GPIOF)
	NVIC_EN0_R |= 0x40000000;
	NVIC_PRI7_R &= 0x00E00000;
	IntPrioritySet(INT_GPIOF, 0x00); // configure GPIOF interrupt priority as 0
	GPIO_PORTF_IM_R |= 0x11; // arm interrupt on PF0 and PF4
	GPIO_PORTF_IS_R &= ~0x11; // PF0 and PF4 are edge-sensitive
	GPIO_PORTF_IBE_R &= ~0x11; // PF0 and PF4 not both edges trigger
	GPIO_PORTF_IEV_R &= ~0x11; // PF0 and PF4 falling edge event
	IntMasterEnable(); // globally enable interrupt
}
//interrupt handler
void GPIOPortF_Handler(void)
{
	//switch debounce
	NVIC_EN0_R &= ~0x40000000;
	SysCtlDelay(53333);	
	NVIC_EN0_R |= 0x40000000;
	// Rotary Counter
	//SW1 is pressed
	if(GPIO_PORTF_RIS_R&0x10)
	{
		// acknowledge flag for PF4
		GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_4);
		//counter imcremented by 1
		count++;
		count=count&7;
	}
	//SW2 is pressed
	if(GPIO_PORTF_RIS_R&0x01)
	{
		// acknowledge flag for PF0
		GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_0);
		//counter decremented by 1
		count--;
		count=count&7;
	}
}

int main(void)
{
	//initialize the GPIO ports
	PortFunctionInit();
	//configure the GPIOF interrupt
	Interrupt_Init();
	//
	// Loop forever.
	//
	while(1)
	{
		if (count==0)
			{
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);//turn off red
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x00); //turn off blue
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00); //turn off green
		}
		else if (count==1)
		{
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x02);//turn on red
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x00); //turn off blue
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00); //turn off green
		}
		else if (count==2)
		{
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00); //turn off red
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x04); //turn on blue
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00); //turn off green
		}
		else if (count==3)
		{
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x02); //turn on red
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x04); //turn on blue
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00); //turn off green
		}
		else if (count==4)
		{
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00); //turn off red
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x00); //turn off blue
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GREEN_MASK); //turn on green
		}
		else if (count==5)
		{
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x02); //turn on red
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x00); //turn off blue
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GREEN_MASK); //turn on green
		}
		else if (count==6)
		{
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00); //turn off red
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x04); //turn on blue
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GREEN_MASK); //turn on green
		}
		else if (count==7)
		{
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x02); //turn on red
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x04); //turn on blue
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GREEN_MASK); //turn om green
		}
	}
}
