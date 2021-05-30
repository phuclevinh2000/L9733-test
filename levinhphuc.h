/*
*********************************************************************************************************
* File : levinhphuc.h
* By   : Le Vinh Phuc
* Further modifications: phuclevinh2000@gmail.com
*********************************************************************************************************
This is the very first time I have worked with a header file and function prototype and L9733 so everything
is new to me. I have a lot of things to learn and this is what I did with the task you provide.

In thí file, the MCU that I am using is NUCLEO STM32L152RE, the block diagram for this MCU will be provided in the attach github link: https://github.com/phuclevinh2000/L9733-test/blob/main/STM32L152RE%20block%20diagram.xlsx

High-side swithching: The gate voltage have to be higher than Ut+Us to active the switch, in this case Us=(Vcc*Rl)/(Rl+Rds) (connected in parallel)
is similar to Vcc because Rl is much larger than Rds. 
Low-side switching: This one is much more farmiliar than the high-side switching because it require much smaller voltage 
to active the switch because Vs is 0V since it is connected to the ground. V gate only need to be about Ut.

I have limitation with the fault operation, I just made one function prototype to check the D1 and D0, compare to the logic table provided 
on page 25 of the datasheet

There is another file for RTOS configuration named OS_CFG.H that have all the state for SEMAPHORES, MESSAGE QUEUES, EVENTS FLAGS,etc. 
*********************************************************************************************************

*/

#ifndef L9733_H
#define L9733_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define BAUD_RATE 9600										/*Set the baud rate to 9600*/

/* Header Includes ------------------------------------------------------------------*/
/*Standard C Library*/
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <time.h>

/*
 * If stdint.h cannot be located then:
 *   + If using GCC ensure the -nostdint options is *not* being used.
 *   + Ensure the project's include path includes the directory in which your
 *     compiler stores stdint.h.
 *   + Set any compiler options necessary for it to support C99, as technically
 *     stdint.h is only mandatory with C99 (FreeRTOS does not require C99 in any
 *     other way).
 *   + The FreeRTOS download includes a simple stdint.h definition that can be
 *     used in cases where none is provided by the compiler.  The files only
 *     contains the typedefs required to build FreeRTOS.  Read the instructions
 *     in FreeRTOS/source/stdint.readme for more information.
 */
#include <stdint.h>											/*FreeRTOS, as explained above*/
#include "spi.h"											/*include of the serial peripheral interface*/
#include "stm32l1xx,h"										/*include the header file for STM32L152RE */
#include "nucleo152start.h"									/*Header file for STM32L152RE*/

/*The Real-Time Kernel (by Jean J. Labrosse) for WIN32 PORT & LINUX PORT*/
#ifndef __GNUC__
#include <conio.h>
#endif

#ifdef __WIN32__
#include <windows.h>
#endif

#ifdef __GNUC__
#include <unistd.h>
#include <termios.h>
#include <sys/time.h>
#endif

#include "os_cpu.h"
#include "os_cfg.h"											/*Configuration file for RTOS*/
#include "ucos_ii.h"
#include "pc.h"

/* Function Prototype ------------------------------------------------------- */
/*Delay function*/
void delay_Ms(long long delay);								/*Delay function for the system in ms*/
void delay_Us(long long delay);								/*Delay function for the system in us*/

/*Low-side driver and high-side driver*/
bool SetSideDriver(int Source, int Drain);					/*Return the state of the driver (low state for low-side drivers and igh state for high-side drivers*/
void SetTheDriver(bool DriverSide, int Source, int Drain);	/*Return the Gate voltage to switch on the switch*/

/*Supply pins*/
void GetBatteySupply (void);								/*Get the Battery Supply Vbat*/
void GetMainPowerInput(void);								/*Get the external value of Vdd*/
void GetDiscreteInputVoltageSupply(void);					/*Get the Discrete inputs voltage supply VDO value*/

/*Discrete input*/
void GetDiscrete(void);										/*Get the discrete input usded to PWM output driver 6,7 or 8*/
void Set_RES(bool level)									/*Set the reset  level of In6, In7, In8 (active low)*/

/*Serial peripheral interface (SPI)
* All function prototype with SPI will have the spi_t type which represents the SPI controller of the MCU
*/
void Get_SCLK(spi_t spiHandler);										/*Get the serial clock signal input generate by the MCU*/
int spi_SetSSEdges(spi_t spiHandler, int SSDelayStart, int SSDelayStop)	/*Defines the slave select edges position.*/
int spi_SetReqClock(spi_t spiHandler, int Freq)							/*Defines the requested operating clock frequency (in Hz).*/
int spi_GetReqClock(spi_t spiHandler)									/*Returns the current requested operating clock frequency (in Hz).*/

int spi_GetSSDelayStart(spi_t spiHandler)								/*Returns the slave select start edge positions*/
int spi_GetSSDelayStop(spi_t spiHandler)								/*Returns the slave select stop edge positions*/
void spi_SetSSActiveLevel(spi_t spiHandler, bool Level) 				/*Sets the CS signal(s) active level.*/
bool spi_GetSSActiveLevel(spi_t spiHandler)								/*Return the CS signal(s) active level.*/

void spi_GetDI(spi_t spiHandler);										/*Get SPI data in*/
int spi_SetDO(spi_t spiHandler);										/*Set SPI data out*/

void spi_SetMaster(spi_t spiHandler)									/*Sets master mode with SS pin control enabled*/
void spi_SetSlave(spi_t spiHandler)										/*Sets slave mode with SS pin control enabled*/
void spi_SetPins(spi_t spiHandler)										/*Sets SPI pins*/
void spi_SetDataMode(spi_t spiHandler, BYTE mode)						/*Set SPI data mode*/
void spi_TranferByte(spi_t spiHandler, BYTE data)						/*Transfer 1 byte*/
int spi_Read (spi_t spiHandler, BYTE* data, int length, int addr)		/*Read a byte of data from a specific address*/
void spi_WriteValue(spi_t spiHandler, int addr, int value)				/*Write a byte of data to a specific address */

/*Fault operation*/
void SetFaultOperation(bool D1, bool D0, bool DriverState);				/*Get the driver state (high-side P or low-side N) and fault operation by the state of D0 and D1 and the fault logic definition*/

#ifdef __cplusplus
}
#endif


#endif /* L9733_H*/
