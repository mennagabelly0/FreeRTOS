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
#include "queue.h"
#include "task.h"
#include "STM32F103X6.h"
#include "RCC_DRIVER_STM32F103C6.h"
#include "GPIO_DRIVER_STM32F103C6.h"

/***************** Handler *****************/
QueueHandle_t xQueue= NULL ;
TaskHandle_t vTaskMaster = NULL ;
TaskHandle_t vTaskSlave = NULL ;




/***************** Prototypes **************/
void vTaskMasterHandle(void *parms) ;
void vTaskSlaveHandle(void *parms) ;


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
	xTaskCreate(vTaskMasterHandle, " Master ", 128, NULL, 1, vTaskMaster) ;
	xTaskCreate(vTaskSlaveHandle, " Slave ", 128, NULL, 2, vTaskSlave) ;

	// Enable Queue to Synch
	xQueue = xQueueCreate( 10, sizeof( uint8_t ) );

	// Start With RTOS Scheduler " NO Return "
	vTaskStartScheduler() ;



	/* Loop forever */
	while(1)
	{

	}
	return 0 ;
}

/***************** Task Handler ************/
void vTaskMasterHandle(void *parms)
{
	uint8_t OFFcomannd = 0 ;
	uint8_t ONcomannd = 1 ;

	while(1)
	{
		xQueueSend(xQueue , &OFFcomannd , (TickType_t)5 ) ;
		vTaskDelay(15) ;
		xQueueSend(xQueue , &ONcomannd , (TickType_t)5 ) ;
		vTaskDelay(15) ;
	}
}


void vTaskSlaveHandle(void *parms)
{
	uint8_t CommandRecive  = 0 ;

	while(1)
	{
		xQueueReceive(xQueue, &CommandRecive, (TickType_t)5) ;

		if(CommandRecive == 0)
		{
			MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, 0) ;

		}
		else if (CommandRecive == 1)
		{
			MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, 1) ;
		}
		vTaskDelay(10) ;
	}
}
