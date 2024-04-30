/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Eng.MENNA_Gabely
 * @brief          : Main program body
 ******************************************************************************
 */


/***************** Includes ****************/
#include "stdio.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "semphr.h"
#include "task.h"
#include "STM32F103X6.h"
#include "RCC_DRIVER_STM32F103C6.h"
#include "GPIO_DRIVER_STM32F103C6.h"

/***************** Handler *****************/
SemaphoreHandle_t xSemaphore = NULL ;
TaskHandle_t vTaskLEDHandler = NULL ;
TaskHandle_t vTaskButtonHandler = NULL ;

uint8_t Button_Curr_Stetas = 0 ;
uint8_t Button_Prev_Stetas = 0 ;


/***************** Prototypes **************/
void vTaskLEDHandle(void *parms) ;
void vTaskButtonHandle(void *parms) ;


/***************** General FUNs **************/
void Clock_init(void)
{
	RCC_GPIOA_CLK_EN() ;
}

void HW_Init(void)
{
	// Task LED as Output
	GPIO_PinConfig_t PIN13ACFG ;
	PIN13ACFG.GPIO_PinNumber = GPIO_PIN_13 ;
	PIN13ACFG.GPIO_MODE = GPIO_MODE_Output_push_pull ;
	PIN13ACFG.GPIO_Output_Speed = GPIO_Output_Speed_10M ;

	MCAL_GPIO_Init(GPIOA, &PIN13ACFG) ;

	// Task Button as Input
	GPIO_PinConfig_t PIN15ACFG ;
	PIN15ACFG.GPIO_PinNumber = GPIO_PIN_15 ;
	PIN15ACFG.GPIO_MODE = GPIO_MODE_Input_Pull_down ;

	MCAL_GPIO_Init(GPIOA, &PIN15ACFG) ;

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
	xTaskCreate(vTaskLEDHandle, " Controlling LED ", 128, NULL, 1, vTaskLEDHandler) ;
	xTaskCreate(vTaskButtonHandle, " Press Button ", 128, NULL, 2, vTaskButtonHandler) ;

	// Enable Semaphore to Synch
	xSemaphore = xSemaphoreCreateBinary() ;

	// Start With RTOS Scheduler " NO Return "
	vTaskStartScheduler() ;



	/* Loop forever */
	while(1)
	{

	}
	return 0 ;
}

/***************** Task Handler ************/
void vTaskLEDHandle(void *parms)
{
	while(1)
	{
		if(xSemaphoreTake(xSemaphore , (TickType_t) 5) == pdTRUE)
		{
			if(Button_Curr_Stetas == 1)
			{
				MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, 1) ;
			}
			else
			{
				MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, 0) ;
			}
		}
		vTaskDelay(30) ;
	}
}


void vTaskButtonHandle(void *parms)
{
	while(1)
	{
		Button_Curr_Stetas = MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) ;
		if(Button_Curr_Stetas != Button_Prev_Stetas)
		{
			xSemaphoreGive(xSemaphore) ;
		}
		Button_Prev_Stetas = Button_Curr_Stetas ;
		vTaskDelay(25) ;
	}
}
