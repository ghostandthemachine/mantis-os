/** @file st_LIS3L.h
 * @brief Header file of Accelerometer(st_LIS3L)
 * @author Mostafizur Rahman Mozumdar
 * @email  mostafizur.mozumdar@delen.polito.it
 * @date Created: 12/03/2007
 */


#ifndef _ST_LIS3L_H
#define _ST_LIS3L_H


#include "msp430-i2c.h"

#ifndef LIS3L_I2C_ADDRESS
#define LIS3L_I2C_ADDRESS 0x1D
#endif

enum {
   SET_RW_REG= 0,              // Set the Read Write Register
   SET_DEFAULT_MODE,           // Initialize three control registers
   SET_THRESHOLD,              // Set the threshold
   SET_DURATION,               // Set the duration
   SET_ONOFF,                  // Set the accelerometer On/Off 
   SET_AXIS_ZYX,               // Disable/Enable the Z,Y,X axis reading
   SET_INTERRUPT_REG,          // Set the interrupt flags
   SET_CTRL_REGS               // Set the three control registers
}; 


void init_i2c();
uint8_t fixAddress(uint8_t length, uint8_t regAddress);
uint8_t  st_LIS3LreadSingleRegister(uint8_t reg, uint8_t* buffer);
uint8_t  st_LIS3LwriteSingleRegister(uint8_t reg, uint8_t* buffer);
uint8_t st_LIS3LreadMultipleRegisters(uint8_t reg,uint8_t count, uint8_t* buffer );
uint8_t st_LIS3LwriteMultipleRegisters(uint8_t reg,uint8_t count, uint8_t* buffer );
void st_LIS3LHiddenInit();
void st_LIS3LgetXYZ(uint8_t* buffer );
uint8_t st_LIS3LgetWhoAmI();
uint8_t st_LIS3LgetDuration();
void st_LIS3LsetDuration(uint8_t value);
void st_LIS3LsetOnOff(uint8_t setStatus);
void st_LIS3LsetAxis(uint8_t x,uint8_t y,uint8_t z);
uint16_t st_LIS3LgetThreshold();

void st_LIS3LsetThreshold(uint16_t threshold);
void st_LIS3LsetInterrupt(uint8_t orAnd, uint8_t latched, uint8_t xUp, uint8_t xDown,		\
 uint8_t yUp, uint8_t yDown, uint8_t zUp, uint8_t zDown);		\

void st_LIS3LsetInterruptReg(uint8_t reg_value);
uint8_t st_LIS3LgetInterruptReg();


#endif
