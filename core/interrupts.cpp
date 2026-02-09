#include "core.h"
#include "log.h"

void FDC2214_ISR(FDC2214* fdc) {
  FDC2214_LOG_DEBUG(fdc, "(%s) interrupt", __func__);
  fdc->handle_interrupt = 1;
}

void FDC2214_enable_interrupts(FDC2214* fdc) {
  FDC2214_LOG_DEBUG(fdc, "(%s) enabling interrupts", __func__);
  // Interrupts (Page 19)
  // CONFIG.INTB_DIS = 0 (Page 34)
  FDC2214_write_register_bits(fdc, FDC2214_REG_CONFIG, 7, 7, 0);
  // STATUS_CONFIG / ERROR_CONFIG (Page 19, 30 & 33)
  FDC2214_write_register_bits(fdc, FDC2214_REG_STATUS_CONFIG, 11, 13, 0b111);
  FDC2214_write_register_bits(fdc, FDC2214_REG_STATUS_CONFIG, 5, 5, 1);
  FDC2214_write_register_bits(fdc, FDC2214_REG_STATUS_CONFIG, 0, 0, 1);
}

void FDC2214_disable_interrupts(FDC2214* fdc) {
  FDC2214_LOG_DEBUG(fdc, "(%s) disabling interrupts", __func__);
  // Interrupts (Page 19)
  // CONFIG.INTB_DIS = 1 (Page 34)
  FDC2214_write_register_bits(fdc, FDC2214_REG_CONFIG, 7, 7, 1);
  // STATUS_CONFIG / ERROR_CONFIG (Page 19, 30 & 33)
  FDC2214_write_register_bits(fdc, FDC2214_REG_STATUS_CONFIG, 11, 13, 0b000);
  FDC2214_write_register_bits(fdc, FDC2214_REG_STATUS_CONFIG, 5, 5, 0);
  FDC2214_write_register_bits(fdc, FDC2214_REG_STATUS_CONFIG, 0, 0, 0);
}
  