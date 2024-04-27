/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Eng.MENNA_Gabely
 * @brief          : Main program body
 ******************************************************************************
 */


/***************** Includes ****************/
#include "FreeRTOS.h"
#include "task.h"
#include "STM32F103X6.h"
#include "RCC_DRIVER_STM32F103C6.h"
#include "GPIO_DRIVER_STM32F103C6.h"

/***************** Handler *****************/
TaskHandle_t vBlinkingLED = NULL ;

/***************** Prototypes **************/
void vBlinkingLEDHandler(void *parms) ;


/***************** General FUNs **************/
void Clock_init(void)
{
	RCC_GPIOA_CLK_EN() ;
}

void HW_Init(void)
{
	GPIO_PinConfig_t PIN13ACFG ;
	PIN13ACFG.GPIO_PinNumber = GPIO_PIN_13 ;
	PIN13ACFG.GPIO_MODE = GPIO_MODE_Output_push_pull ;
	PIN13ACFG.GPIO_Output_Speed = GPIO_Output_Speed_10M ;

	MCAL_GPIO_Init(GPIOA, &PIN13ACFG) ;
}

int main(void)
{
	Clock_init() ;
	HW_Init() ;

	/***************** Task Alignment RTOS ************/

//	BaseType_t xTaskCreate(    TaskFunction_t pvTaskCode,
//	                            const char * const pcName,
//	                            const configSTACK_DEPTH_TYPE uxStackDepth,
//	                            void *pvParameters,
//	                            UBaseType_t uxPriority,
//	                            TaskHandle_t *pxCreatedTask
//	                          );
	xTaskCreate(vBlinkingLEDHandler, "Blinking LED", 128, NULL, 1, vBlinkingLED) ;
	// Start With RTOS Scheduler " NO Return "
	vTaskStartScheduler() ;



	/* Loop forever */
	while(1)
	{

	}
	return 0 ;
}

/***************** Task Handler ************/
void vBlinkingLEDHandler(void *parms)
{
	while(1)
	{
		MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, 0) ;
		vTaskDelay(100) ;
		MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, 1) ;
		vTaskDelay(100) ;
	}
}
