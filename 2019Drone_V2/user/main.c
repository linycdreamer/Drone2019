#include "main.h"
#include "modules.h"
int main(void)
{
	droneConfig();
	droneInit();
	while (1)
	{
	}
}
RCC_ClocksTypeDef rcc;
void droneConfig(void)
{
	RCC_GetClocksFreq(&rcc);
	SystemInit();
	while(SysTick_Config(72000));		
	CAN_Config();
	TIM_Config();
	USART_Config();
}
void droneInit(void)
{
	modules_init();
}
void SysTick_Handler(void)
{
	modules_task();
}
