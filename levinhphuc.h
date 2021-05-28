/*
*********************************************************************************************************
* File : levinhphuc.h
* By   : Le Vinh Phuc
* Further modifications: phuclevinh2000@gmail.com
*********************************************************************************************************
This is the very first time I have worked with a header file and function prototype and L9733 so everything
is new to me. I have a lot of things to learn and this is what I did with the task you provide.

High-side swithching: The gate voltage have to be higher than Ut+Us to active the switch, in this case Us=(Vcc*Rl)/(Rl+Rds) (connected in parallel)
is similar to Vcc because Rl is much larger than Rds. '
Low-side switching: This one is much more farmiliar than the high-side switching because it require much smaller voltage 
to active the switch because Vs is 0V since it is connected to the ground. V gate only need to be about Ut.

I have limitation with the output 6-8 when it is controlled by the SPI BUS
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

/* Includes ------------------------------------------------------------------*/
#include "spi.h"											/*include of the serial peripheral interface*/
#include "stm32l1xx,h"										/*include the header file for STM32L152RE */
#include "nucleo152start.h"
/* Function Prototype ------------------------------------------------------- */
void delay_Ms(int delay);									/*Delay function for the system in ms*/

/*Low-side driver and high-side driver*/
bool SetSideDriver(int Source, int Drain);					/*Return the state of the driver (low state for low-side drivers and igh state for high-side drivers*/
void SetTheDriver(bool DriverSide, int Source, int Drain);	/*Return the Gate voltage to switch on the switch*/

/*Supply pins*/
void GetBatteySupply (void);								/*Get the Battery Supply Vbat*/
void GetMainPowerInput(void);								/*Get the external value of Vdd*/
void GetDiscreteInputVoltageSupply(void);					/*Get VDO value*/

/*Discrete input*/
void GetDiscrete(void);										/*Get the discrete input usded to PWM output driver 6,7 or 8*/
void Set_RES(bool level)									/*Set the reset input of In6, In7, In8 (active low)*/

/*Serial peripheral interface (SPI)*/
void Get_SCLK(void);										/*Get the serial clock signal input generate by the MCU*/
int spi_SetCSEdges(int CSDelayStart, int CSDelayStop) 		/*Defines the slave select edges position*/
int spi_GetCSDelayStart(void)								/*Returns the slave select start edge positions*/
int spi_GetCSDelayStop(void)								/*Returns the slave select stop edge positions*/
void spi_SetCSActiveLevel(bool Level) 						/*Sets the CS signal(s) active level.*/
bool spi_GetSSActiveLevel(void)								/*Return the CS signal(s) active level.*/
void spi_GetDI(void);										/*Get SPI data in*/
int spi_SetDO(void);										/*Set SPI data out*/

/*Fault operation*/
void SetFaultOperation(bool D1, bool D0);					/*Get the fault operation by the state of D1 and D1 and the fault logic definition*/

#ifdef __cplusplus
}
#endif


#endif /* L9733_H*/
