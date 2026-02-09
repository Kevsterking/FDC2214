#include "core.h"
#include "log.h"
#include <Arduino.h>

void FDC2214_power_on(FDC2214* fdc) {
  FDC2214_LOG_DEBUG(fdc, "(%s) powering on...", __func__);
  // (Page 20)
  // SD-pin -> LOW => boot up
  fdc->interface.set_sd_pin_low(fdc->interface.platform_context);
  digitalWrite(LED_BUILTIN, LOW);
  // Makes sense to wait a bit for boot 
  // but idk if necessary
  fdc->interface.sleep(fdc->interface.platform_context, 50);
}

void FDC2214_power_off(FDC2214* fdc) {
  FDC2214_LOG_DEBUG(fdc, "(%s) powering off...", __func__);
  // (Page 20)
  // SD-pin -> HIGH => shut down
  fdc->interface.set_sd_pin_high(fdc->interface.platform_context);
  // Makes sense to wait a bit for boot 
  // but idk if necessary
  fdc->interface.sleep(fdc->interface.platform_context, 50);
}

void FDC2214_wakeup(FDC2214* fdc) {
  FDC2214_LOG_DEBUG(fdc, "(%s) Waking up...", __func__);
  // SLEEP_MODE_EN = 0 -> Device is active - (Page 20, 34 & 40)
  FDC2214_write_register_bits(fdc, FDC2214_REG_CONFIG, 13, 13, 0);
}

void FDC2214_sleep(FDC2214* fdc) {
  FDC2214_LOG_DEBUG(fdc, "(%s) Going to sleep...", __func__);
  // SLEEP_MODE_EN = 1 -> Device goes to sleep - (Page 20, 34 & 40)
  FDC2214_write_register_bits(fdc, FDC2214_REG_CONFIG, 13, 13, 1);
}