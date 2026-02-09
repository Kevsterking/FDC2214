#include "core.h"
#include "log.h"

uint8_t FDC2214_verify(FDC2214* fdc) {
  FDC2214_LOG_DEBUG(fdc, "(%s) Verifying chip", __func__);
  // Check for FDC2214 chip
  bool is_ti = FDC2214_read_register(fdc, FDC2214_REG_MANUFACTORURER_ID) == FDC2214_MANUFACTURER_ID;
  bool is_fdc2214 = FDC2214_read_register(fdc, FDC2214_REG_DEVICE_ID) == FDC2214_DEVICE_ID;
  if (!is_fdc2214) {
    FDC2214_LOG_WARNING(fdc, "Chip is not identified as an FDC2214");
    return 0;
  }
  if (!is_ti) {
    FDC2214_LOG_WARNING(fdc, "Chip is not manufactured by Texas Instruments");
    return 0;
  }
  return 1;
}

uint16_t FDC2214_read_register(FDC2214* fdc, uint8_t address) {
  FDC2214_LOG_DEBUG(fdc, "(%s) Reading 0x%02X", "FDC2214_read_register", address);
  return fdc->interface.read16(fdc->interface.platform_context, address);
}

uint16_t FDC2214_read_register_bits(FDC2214* fdc, uint8_t address, uint8_t from_bit, uint8_t to_bit) {
  FDC2214_LOG_DEBUG(fdc, "(%s) Reading 0x%02X[%02u:%02u]", "FDC2214_read_register_bits", address, from_bit, to_bit);
  return (FDC2214_read_register(fdc, address) >> from_bit) & ((1U << (to_bit - from_bit + 1)) - 1);
}

void FDC2214_write_register(FDC2214* fdc, uint8_t address, uint16_t data) {
  FDC2214_LOG_DEBUG(fdc, "(%s) Writing 0x%02X = %04u", __func__, address, data);
  fdc->interface.write16(fdc->interface.platform_context, address, data);
}

void FDC2214_write_register_bits(FDC2214* fdc, uint8_t address, uint8_t from_bit, uint8_t to_bit, uint16_t data) {
  FDC2214_LOG_DEBUG(fdc, "(%s) Writing 0x%02X[%02u:%02u] = %04u", __func__, address, from_bit, to_bit, data);
  uint16_t mask = ((1U << (to_bit - from_bit + 1)) - 1);
  uint16_t new_value = FDC2214_read_register(fdc, address) & ~(mask << from_bit);
  FDC2214_write_register(fdc, address, new_value | ((data & mask) << from_bit));
}




