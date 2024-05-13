################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM32F103C6_Driver/EXTI_DRIVER_STM32F103C6.c \
../STM32F103C6_Driver/GPIO_DRIVER_STM32F103C6.c \
../STM32F103C6_Driver/I2C_DRIVER_STM32F103C6.c \
../STM32F103C6_Driver/RCC_DRIVER_STM32F103C6.c \
../STM32F103C6_Driver/SPI_DRIVER_STM32F103C6.c \
../STM32F103C6_Driver/Timer.c \
../STM32F103C6_Driver/USART_DRIVER_STM32F103C6.c 

OBJS += \
./STM32F103C6_Driver/EXTI_DRIVER_STM32F103C6.o \
./STM32F103C6_Driver/GPIO_DRIVER_STM32F103C6.o \
./STM32F103C6_Driver/I2C_DRIVER_STM32F103C6.o \
./STM32F103C6_Driver/RCC_DRIVER_STM32F103C6.o \
./STM32F103C6_Driver/SPI_DRIVER_STM32F103C6.o \
./STM32F103C6_Driver/Timer.o \
./STM32F103C6_Driver/USART_DRIVER_STM32F103C6.o 

C_DEPS += \
./STM32F103C6_Driver/EXTI_DRIVER_STM32F103C6.d \
./STM32F103C6_Driver/GPIO_DRIVER_STM32F103C6.d \
./STM32F103C6_Driver/I2C_DRIVER_STM32F103C6.d \
./STM32F103C6_Driver/RCC_DRIVER_STM32F103C6.d \
./STM32F103C6_Driver/SPI_DRIVER_STM32F103C6.d \
./STM32F103C6_Driver/Timer.d \
./STM32F103C6_Driver/USART_DRIVER_STM32F103C6.d 


# Each subdirectory must supply rules for building sources it contributes
STM32F103C6_Driver/EXTI_DRIVER_STM32F103C6.o: ../STM32F103C6_Driver/EXTI_DRIVER_STM32F103C6.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/learn in depth Assignment/RTOS/FREE RTOS/RTOS_Deadlock/FreeRTOS/include" -I"D:/learn in depth Assignment/RTOS/FREE RTOS/RTOS_Deadlock/FreeRTOS/portable/GCC/ARM_CM3" -I"D:/learn in depth Assignment/RTOS/FREE RTOS/RTOS_Deadlock/STM32F103C6_Driver/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F103C6_Driver/EXTI_DRIVER_STM32F103C6.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
STM32F103C6_Driver/GPIO_DRIVER_STM32F103C6.o: ../STM32F103C6_Driver/GPIO_DRIVER_STM32F103C6.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/learn in depth Assignment/RTOS/FREE RTOS/RTOS_Deadlock/FreeRTOS/include" -I"D:/learn in depth Assignment/RTOS/FREE RTOS/RTOS_Deadlock/FreeRTOS/portable/GCC/ARM_CM3" -I"D:/learn in depth Assignment/RTOS/FREE RTOS/RTOS_Deadlock/STM32F103C6_Driver/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F103C6_Driver/GPIO_DRIVER_STM32F103C6.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
STM32F103C6_Driver/I2C_DRIVER_STM32F103C6.o: ../STM32F103C6_Driver/I2C_DRIVER_STM32F103C6.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/learn in depth Assignment/RTOS/FREE RTOS/RTOS_Deadlock/FreeRTOS/include" -I"D:/learn in depth Assignment/RTOS/FREE RTOS/RTOS_Deadlock/FreeRTOS/portable/GCC/ARM_CM3" -I"D:/learn in depth Assignment/RTOS/FREE RTOS/RTOS_Deadlock/STM32F103C6_Driver/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F103C6_Driver/I2C_DRIVER_STM32F103C6.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
STM32F103C6_Driver/RCC_DRIVER_STM32F103C6.o: ../STM32F103C6_Driver/RCC_DRIVER_STM32F103C6.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/learn in depth Assignment/RTOS/FREE RTOS/RTOS_Deadlock/FreeRTOS/include" -I"D:/learn in depth Assignment/RTOS/FREE RTOS/RTOS_Deadlock/FreeRTOS/portable/GCC/ARM_CM3" -I"D:/learn in depth Assignment/RTOS/FREE RTOS/RTOS_Deadlock/STM32F103C6_Driver/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F103C6_Driver/RCC_DRIVER_STM32F103C6.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
STM32F103C6_Driver/SPI_DRIVER_STM32F103C6.o: ../STM32F103C6_Driver/SPI_DRIVER_STM32F103C6.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/learn in depth Assignment/RTOS/FREE RTOS/RTOS_Deadlock/FreeRTOS/include" -I"D:/learn in depth Assignment/RTOS/FREE RTOS/RTOS_Deadlock/FreeRTOS/portable/GCC/ARM_CM3" -I"D:/learn in depth Assignment/RTOS/FREE RTOS/RTOS_Deadlock/STM32F103C6_Driver/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F103C6_Driver/SPI_DRIVER_STM32F103C6.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
STM32F103C6_Driver/Timer.o: ../STM32F103C6_Driver/Timer.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/learn in depth Assignment/RTOS/FREE RTOS/RTOS_Deadlock/FreeRTOS/include" -I"D:/learn in depth Assignment/RTOS/FREE RTOS/RTOS_Deadlock/FreeRTOS/portable/GCC/ARM_CM3" -I"D:/learn in depth Assignment/RTOS/FREE RTOS/RTOS_Deadlock/STM32F103C6_Driver/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F103C6_Driver/Timer.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
STM32F103C6_Driver/USART_DRIVER_STM32F103C6.o: ../STM32F103C6_Driver/USART_DRIVER_STM32F103C6.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/learn in depth Assignment/RTOS/FREE RTOS/RTOS_Deadlock/FreeRTOS/include" -I"D:/learn in depth Assignment/RTOS/FREE RTOS/RTOS_Deadlock/FreeRTOS/portable/GCC/ARM_CM3" -I"D:/learn in depth Assignment/RTOS/FREE RTOS/RTOS_Deadlock/STM32F103C6_Driver/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F103C6_Driver/USART_DRIVER_STM32F103C6.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

