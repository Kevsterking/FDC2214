#include <FDC2214/FDC2214.h>
#include <FDC2214/core/core.h>

//
// TODO: auto configuration with Q factor calculations etc..
// Should be possible to approximate with LOW_amplitude warnings 
// and known LC tank LC values
//

FDC2214Config FDC2214_read_current_config(FDC2214* fdc) {
  FDC2214Config config;
  // CONFIG
  config.SENSOR_ACTIVATE_SEL = FDC2214_read_register_bits(fdc, FDC2214_REG_CONFIG, 11, 11);;
  config.REF_CLK_SRC = FDC2214_read_register_bits(fdc, FDC2214_REG_CONFIG, 9, 9);
  // Channel 0
  config.channel[0].lc_capacitance = fdc->config.channel[0].lc_capacitance;
  config.channel[0].lc_inductance = fdc->config.channel[0].lc_inductance;
  config.channel[0].SETTLECOUNT = FDC2214_read_register(fdc, FDC2214_REG_SETTLECOUNT_CH(0));
  config.channel[0].RCOUNT = FDC2214_read_register(fdc, FDC2214_REG_RCOUNT_CH(0)); 
  config.channel[0].FREF_DIVIDER = FDC2214_get_FREF(fdc, 0);
  config.channel[0].FIN_SEL = FDC2214_get_FIN_SEL(fdc, 0);
  config.channel[0].IDRIVE = FDC2214_get_IDRIVE(fdc, 0);
  // Channel 1
  config.channel[1].lc_capacitance = fdc->config.channel[0].lc_capacitance;
  config.channel[1].lc_inductance = fdc->config.channel[0].lc_inductance;
  config.channel[1].SETTLECOUNT = FDC2214_read_register(fdc, FDC2214_REG_SETTLECOUNT_CH(1));
  config.channel[1].RCOUNT = FDC2214_read_register(fdc, FDC2214_REG_RCOUNT_CH(1)); 
  config.channel[1].FREF_DIVIDER = FDC2214_get_FREF(fdc, 1);
  config.channel[1].FIN_SEL = FDC2214_get_FIN_SEL(fdc, 1);
  config.channel[1].IDRIVE = FDC2214_get_IDRIVE(fdc, 1);
  return config;
}

void _static_config(FDC2214* fdc) {
  // RESERVED = 1 -> Datasheet specifies 1 (Page 34)
  FDC2214_write_register_bits(fdc, FDC2214_REG_CONFIG, 12, 12, 1);
  // RESERVED = 1 -> Datasheet specifies 1 (Page 34)
  FDC2214_write_register_bits(fdc, FDC2214_REG_CONFIG, 10, 10, 1);
}

void FDC2214_update_config(FDC2214* fdc) {
  // Sleep mode is required for configuration
  FDC2214_sleep(fdc);
  // SENSOR_ACTIVATE_SEL (Page 18 & 34)
  FDC2214_write_register_bits(fdc, FDC2214_REG_CONFIG, 11, 11, fdc->config.SENSOR_ACTIVATE_SEL);
  // REF_CLK_SRC (Page 13 & 34)
  FDC2214_write_register_bits(fdc, FDC2214_REG_CONFIG, 9, 9, fdc->config.REF_CLK_SRC);
  // MUX_CONFIG.DEGLITCH (Page 20 & 35)  
  FDC2214_write_register_bits(fdc, FDC2214_REG_MUX_CONFIG, 0, 2, fdc->config.DEGLITCH);
  // RR_SEQUENCE (Page 14 & 35)
  FDC2214_write_register_bits(fdc, FDC2214_REG_MUX_CONFIG, 13, 14, fdc->config.RR_SEQUENCE);
  // AUTOSCAN_EN (Page 14 & 35)
  FDC2214_write_register_bits(fdc, FDC2214_REG_MUX_CONFIG, 15, 15, fdc->config.AUTOSCAN_EN);
  // HIGH_CURRENT_DRV (Page 18)
  FDC2214_write_register_bits(fdc, FDC2214_REG_MUX_CONFIG, 6, 6, fdc->config.HIGH_CURRENT_DRV);
  // Channel Configuration
  for (uint8_t i = 0; i < fdc->config.channels; i++) {
    // SETTLECOUNT_CHx (Page 16 & 28)
    FDC2214_write_register(fdc, FDC2214_REG_SETTLECOUNT_CH(i), fdc->config.channel[i].SETTLECOUNT);
    // RCOUNT_CHx (Page 16 & 25)
    FDC2214_write_register(fdc, FDC2214_REG_RCOUNT_CH(i), fdc->config.channel[i].RCOUNT); 
    // CHx_FREF_DIVIDER (Page 13 & 29-30)
    FDC2214_write_register_bits(fdc, FDC2214_REG_CLOCK_DIVIDERS_CH(i), 0, 9, fdc->config.channel[i].FREF_DIVIDER);
    // CHx_FIN_SEL (Page 13 & 29-30)
    FDC2214_write_register_bits(fdc, FDC2214_REG_CLOCK_DIVIDERS_CH(i), 12, 13, fdc->config.channel[i].FIN_SEL);
    // CHx_IDRIVE (Page 18-19 & 36)
    FDC2214_write_register_bits(fdc, FDC2214_REG_DRIVE_CURRENT_CH(i), 11, 15, fdc->config.channel[i].IDRIVE);
  }
}
