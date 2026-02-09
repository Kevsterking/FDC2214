#ifndef FDC2214_CORE_H
#define FDC2214_CORE_H

#include <FDC2214/FDC2214.h>

#define FDC2214_I2C_ADDRESS 0x2B

#define FDC2214_MANUFACTURER_ID 0x5449
#define FDC2214_DEVICE_ID 0x3055

#define FDC2214_FCLK 40e6

// Registers (Page 21)
#define FDC2214_REG_DATA_CH(X) X * 2 
#define FDC2214_REG_DATA_LSB_CH(X) X * 2 + 1 
#define FDC2214_REG_RCOUNT_CH(X) 0x08 + X 
#define FDC2214_REG_OFFSET_CH(X) 0x0C + X 
#define FDC2214_REG_SETTLECOUNT_CH(X) 0x10 + X 
#define FDC2214_REG_CLOCK_DIVIDERS_CH(X) 0x14 + X 
#define FDC2214_REG_STATUS 0x18 
#define FDC2214_REG_STATUS_CONFIG 0x19 
#define FDC2214_REG_CONFIG 0x1A 
#define FDC2214_REG_MUX_CONFIG 0x1B 
#define FDC2214_REG_RESET_DEV 0x1C 
#define FDC2214_REG_DRIVE_CURRENT_CH(X) 0x1E + X 
#define FDC2214_REG_MANUFACTORURER_ID 0x7E 
#define FDC2214_REG_DEVICE_ID 0x7F

// State
void FDC2214_power_on(FDC2214* fdc);
void FDC2214_power_off(FDC2214* fdc);
void FDC2214_wakeup(FDC2214* fdc);
void FDC2214_sleep(FDC2214* fdc);

// Interrupts
void FDC2214_ISR(FDC2214* fdc);
void FDC2214_disable_interrupts(FDC2214* fdc);
void FDC2214_enable_interrupts(FDC2214* fdc);

// Utility
uint8_t FDC2214_verify(FDC2214* fdc);
uint16_t FDC2214_read_register(FDC2214* fdc, uint8_t address);
uint16_t FDC2214_read_register_bits(FDC2214* fdc, uint8_t address, uint8_t from_bit, uint8_t to_bit);
void FDC2214_write_register(FDC2214* fdc, uint8_t address, uint16_t data);
void FDC2214_write_register_bits(FDC2214* fdc, uint8_t address, uint8_t from_bit, uint8_t to_bit, uint16_t data);

// Registers
uint32_t FDC2214_get_DATA(FDC2214* fdc, uint8_t channel);
double FDC2214_get_FREF(FDC2214* fdc, uint8_t channel);
uint8_t FDC2214_get_FIN_SEL(FDC2214* fdc, uint8_t channel);
double FDC2214_get_IDRIVE(FDC2214* fdc, uint8_t channel);

#endif // FDC2214_CORE_H