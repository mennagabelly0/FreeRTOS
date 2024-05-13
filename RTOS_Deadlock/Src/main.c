/**
 ******************************************************************************
 * @file           : main.c
 * @author         : ENG. MENNA GABELY
 * @brief          : RTOS Deadlock
 ******************************************************************************
 **/

/***************** Includes ****************/
#include "stdio.h"
#include "string.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "semphr.h"
#include "task.h"
#include "STM32F103X6.h"
#include "RCC_DRIVER_STM32F103C6.h"
#include "GPIO_DRIVER_STM32F103C6.h"
#include "USART_DRIVER_STM32F103C6.h"

/***************** General variables *****************/
char UART_Message[60] ;
#define Taken		0
#define Given		1


/***************** Task Handler *****************/
TaskHandle_t xTask1_Handel = NULL ;
TaskHandle_t xTask2_Handel = NULL ;
TaskHandle_t xTask3_Handel = NULL ;

/***************** Semaphore Handler *****************/
SemaphoreHandle_t xSemaphore1 = NULL ;
SemaphoreHandle_t xSemaphore2 = NULL ;

/***************** Function Prototypes **************/
void FunUARTConfig(void) ;
void FunGPIOConfig(void) ;
void FunPrintSemaphoreState(char tasknum , char semaphNum , char semaphrstate) ;


/***************** Task Prototypes **************/
void vTask1Handler(void *parms) ;
void vTask2Handler(void *parms) ;
void vTask3Handler(void *parms) ;


/***************** General FUNs **************/

void Clock_init(void)
{
	RCC_GPIOA_CLK_EN() ;
	RCC_GPIOB_CLK_EN() ;
	RCC_AFIO_CLK_EN() ;
}

void FunUARTConfig(void)
{
	//==========================UART2 INIT=============================
	/* PA9  TX
	 * PA10 RX
	 * PA11 CTC
	 * PA12 RTS
	 */
	UART_Config uart1CFG ;
	uart1CFG.BaudRate = UART_BaudRate_115200;
	uart1CFG.HW_Flow_Conterl = UART_HW_Flow_Conterl_NONE;
	uart1CFG.IRQ_Enable = UART_IRQ_Enable_RXNEIE;
	uart1CFG.Parity = UART_Parity_NONE;
	uart1CFG.Payload_length = UART_Payload_length_8B;
	uart1CFG.Stop_Bits = UART_Stop_Bits_1;
	uart1CFG.UART_Mode = UART_Mode_TX_RX;
	MCAL_UART_Init(USART2, &uart1CFG);
	MCAL_UART_GPIO_Set_Pins(USART2);

}

void FunGPIOConfig(void)
{
	// Task LED as Output

	GPIO_PinConfig_t PIN13AGF ;
	PIN13AGF.GPIO_PinNumber = GPIO_PIN_13 ;
	PIN13AGF.GPIO_MODE = GPIO_MODE_Output_push_pull  ;
	PIN13AGF.GPIO_Output_Speed = GPIO_Output_Speed_10M ;
	MCAL_GPIO_Init(GPIOA, &PIN13AGF) ;
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, 0) ;

	GPIO_PinConfig_t PIN12AGF ;
	PIN12AGF.GPIO_PinNumber = GPIO_PIN_12 ;
	PIN12AGF.GPIO_MODE = GPIO_MODE_Output_push_pull  ;
	PIN12AGF.GPIO_Output_Speed = GPIO_Output_Speed_10M ;
	MCAL_GPIO_Init(GPIOA, &PIN12AGF) ;
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 0) ;

	GPIO_PinConfig_t PIN11AGF ;
	PIN11AGF.GPIO_PinNumber = GPIO_PIN_11 ;
	PIN11AGF.GPIO_MODE = GPIO_MODE_Output_push_pull  ;
	PIN11AGF.GPIO_Output_Speed = GPIO_Output_Speed_10M ;
	MCAL_GPIO_Init(GPIOA, &PIN11AGF) ;
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 0) ;

	GPIO_PinConfig_t PIN10BGF_Tick ;
	PIN10BGF_Tick.GPIO_PinNumber = GPIO_PIN_10 ;
	PIN10BGF_Tick.GPIO_MODE = GPIO_MODE_Output_push_pull  ;
	PIN10BGF_Tick.GPIO_Output_Speed = GPIO_Output_Speed_10M ;
	MCAL_GPIO_Init(GPIOB, &PIN10BGF_Tick) ;
	MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, 0) ;

}

int main(void)
{
	Clock_init() ;
	FunUARTConfig() ;
	FunGPIOConfig() ;

	/***************** Task Alignment RTOS ************/

	//	BaseType_t xTaskCreate(    TaskFunction_t pvTaskCode,
	//	                            const char * const pcName,
	//	                            const configSTACK_DEPTH_TYPE uxStackDepth,
	//	                            void *pvParameters,
	//	                            UBaseType_t uxPriority,
	//	                            TaskHandle_t *pxCreatedTask
	//	                          );
	xTaskCreate(vTask1Handler, " TASK1 ", 128, NULL, 1, xTask1_Handel) ;
	xTaskCreate(vTask2Handler, " TASK2 ", 128, NULL, 2, xTask2_Handel) ;
	xTaskCreate(vTask3Handler, " TASK3 ", 128, NULL, 3, xTask3_Handel) ;

	// Enable Semaphore to Synch
	xSemaphore1 = xSemaphoreCreateBinary() ;
	xSemaphore2 = xSemaphoreCreateBinary() ;

	xSemaphoreGive(xSemaphore1) ;
	xSemaphoreGive(xSemaphore2) ;

	// Start With RTOS Scheduler " NO Return "
	vTaskStartScheduler() ;

	/* Loop forever */
	while(1);

}

/***************** Function Prototypes **************/

void FunPrintSemaphoreState(char tasknum , char semaphNum , char semaphrstate)
{
	int counter = 0 ;
	if(semaphrstate == Taken)
	{
		strcpy(UART_Message , "\nTask  : The Semaphore 	 was Taken by Me \n" ) ;

		UART_Message[6] = tasknum ;
		UART_Message[23] = semaphNum ;

		for(counter =0 ; counter<strlen(UART_Message) ;counter++)
		{
			MCAL_UART_Send_Data(USART2, (UART_Message+counter), Enable) ;
		}
	}
	else if(semaphrstate == Given)
	{
		strcpy(UART_Message , "\nTask  : The Semaphore 	 was Given by Me \n" ) ;

		UART_Message[6] = tasknum ;
		UART_Message[23] = semaphNum ;

		for(counter =0 ; counter<strlen(UART_Message) ;counter++)
		{
			MCAL_UART_Send_Data(USART2, (UART_Message+counter), Enable) ;
		}
	}
}

/***************** Task Handler ************/

void vTask1Handler(void *parms)
{
	int i = 0 , j = 0 ;  // Related to Get DeadLock Example
	int xlastWakeTime = xTaskGetTickCount() ;

	while(1)
	{
		//Try to take semaphore1 and Semaphore2 ================  to Solve Deadlock ================

		if(xSemaphoreTake(xSemaphore1 , portMAX_DELAY) == 1)
		{
			FunPrintSemaphoreState('1' , '1' , Taken) ;
		}
		if(xSemaphoreTake(xSemaphore2 , portMAX_DELAY) == 1)
		{
			FunPrintSemaphoreState('1' , '2' , Taken) ;
		}

		/*
		 *================ Deadlock ================
		j = 0 ;		// work as flag

		//Try to take semaphore2 after 1/2 time

		for(i = 0 ; i<300000 ; i++)
		{
			if(i>200000 && j==0)
			{
				j = 1 ;		// work as flag
				if(xSemaphoreTake(xSemaphore2 , portMAX_DELAY) == 1)
				{
					FunPrintSemaphoreState('1' , '2' , Taken) ;
				}
			}
		}
		 */

		MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 0) ;
		vTaskDelay(10) ;
		MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 1) ;
		vTaskDelay(10) ;

		if(xSemaphoreGive(xSemaphore1) == 1)
		{
			FunPrintSemaphoreState('1' , '1' , Given) ;
		}

		if(xSemaphoreGive(xSemaphore2) == 1)
		{
			FunPrintSemaphoreState('1' , '2' , Given) ;
		}

		vTaskDelayUntil(&xlastWakeTime , 120) ;

	}
}

void vTask2Handler(void *parms)
{
	int xLastWakeTime = xTaskGetTickCount() ;
	while(1)
	{
		MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, 0) ;
		vTaskDelay(10) ;

		MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, 1) ;
		vTaskDelay(10) ;

		vTaskDelayUntil(&xLastWakeTime,120) ;
	}

}

void vTask3Handler(void *parms)
{
	int xLastWakeTime = xTaskGetTickCount() ;

	while(1)
	{
		/*
		 * ================ Deadlock ================
		// Take Semaphore 2
		if(xSemaphoreTake(xSemaphore2 ,portMAX_DELAY) == 1)
		{
			FunPrintSemaphoreState('3' , '2' , Taken) ;
		}

		// Take Semaphore 1
		if(xSemaphoreTake(xSemaphore1 ,portMAX_DELAY) == 1)
		{
			FunPrintSemaphoreState('3' , '1' , Taken) ;
		}
		 */

		// ================ Solve Deadlock ================

		// Take Semaphore 1
		if(xSemaphoreTake(xSemaphore1 ,portMAX_DELAY) == 1)
		{
			FunPrintSemaphoreState('3' , '1' , Taken) ;
		}
		// Take Semaphore 2
		if(xSemaphoreTake(xSemaphore2 ,portMAX_DELAY) == 1)
		{
			FunPrintSemaphoreState('3' , '2' , Taken) ;
		}

		// Toggle P11
		MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 0) ;
		vTaskDelay(10) ;
		MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1) ;
		vTaskDelay(10) ;

		// Give Semaphore 2
		if(xSemaphoreGive(xSemaphore2) == 1)
		{
			FunPrintSemaphoreState('3' , '2' , Given) ;
		}

		// Give Semaphore 1
		if(xSemaphoreGive(xSemaphore1) == 1)
		{
			FunPrintSemaphoreState('3' , '1' , Given) ;
		}
		vTaskDelayUntil(&xLastWakeTime,120) ;
	}
}

void vApplicationTickHook( void )
{
	MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, 0) ;
	MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, 1) ;
}
