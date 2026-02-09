#include "core.h"
#include "log.h"

uint32_t FDC2214_get_DATA(FDC2214* fdc, uint8_t channel) {
  FDC2214_LOG_DEBUG(fdc, "(%s) reading DATA from channel %u", __func__, channel);
  // Read 28 bit value (Page 14-15 & 21-23)
  // OBS! this is different from the FDC21XX
  // OBS OBS!! Datasheet specifies that registers must be 
  // read in order msb -> lsb (hence 'volatile'). (Page 21)  
  // Failure to do so seems to not clear INTB.
  volatile uint16_t msb = FDC2214_read_register_bits(fdc, FDC2214_REG_DATA_CH(channel), 0, 11);
  volatile uint16_t lsb = FDC2214_read_register(fdc, FDC2214_REG_DATA_LSB_CH(channel));
  return (msb << 16) + lsb;
}

double FDC2214_get_FREF(FDC2214* fdc, uint8_t channel) {
  // FCLK / CHx_FREF_DIVIDER (Page 13 & 30)
  return ((double) FDC2214_FCLK) / (FDC2214_read_register_bits(fdc, FDC2214_REG_CLOCK_DIVIDERS_CH(channel), 0, 9));
}

uint8_t FDC2214_get_FIN_SEL(FDC2214* fdc, uint8_t channel) {
  // CHx_FIN_SEL (Page 13 & 30)
  return FDC2214_read_register_bits(fdc, FDC2214_REG_CLOCK_DIVIDERS_CH(channel), 12, 13);
}

double FDC2214_get_IDRIVE(FDC2214* fdc, uint8_t channel) {
  //
  // TODO: check that we are in IDRIVE mode?
  // else if in max current mode we should return max current
  //
  // CHx_IDRIVE Page (18-19 & 35-36) 
  // IDRIVE index => I in amperes (Page 36) 
  static const double IDRIVE[32] = { 
    0.016e-3, 0.018e-3, 0.021e-3, 0.025e-3, 0.028e-3, 0.033e-3, 0.038e-3, 0.044e-3, 
    0.052e-3, 0.060e-3, 0.069e-3, 0.081e-3, 0.093e-3, 0.108e-3, 0.126e-3, 0.146e-3,
    0.169e-3, 0.196e-3, 0.228e-3, 0.264e-3, 0.307e-3, 0.356e-3, 0.413e-3, 0.479e-3,
    0.555e-3, 0.644e-3, 0.747e-3, 0.867e-3, 1.006e-3, 1.167e-3, 1.354e-3, 1.571e-3
  };
  return IDRIVE[FDC2214_read_register_bits(fdc, FDC2214_REG_DRIVE_CURRENT_CH(channel), 11, 15)];
}