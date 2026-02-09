#include "FDC2214.h"
#include "core/core.h"
#include "core/log.h"
#include <ui/ui.h>

uint16_t _get_log_and_clear_status(FDC2214* fdc) {
  uint16_t status = FDC2214_read_register(fdc, FDC2214_REG_STATUS);
  FDC2214_log_status(fdc, status);
  return status;
}

void FDC2214_create(FDC2214* fdc) {
  FDC2214_power_on(fdc);
  if (!FDC2214_verify(fdc)) {
    FDC2214_LOG_ERROR(fdc, "FDC2214 could not be verified!");
    update_display("FDC2214 could not be verified!", true);
    update_display("Check cables!");
    return;
  }
  FDC2214_enable_interrupts(fdc);
}

void FDC2214_update(FDC2214* fdc) {
  if (fdc->handle_interrupt) {
    uint16_t status = _get_log_and_clear_status(fdc);
    for (uint8_t i = 0; i < fdc->config.channels; i++) {
      if (status & FDC2214_UNREADCONV_CH(i)) {
        fdc->on_data({
          .channel = i,
          .data = FDC2214_get_DATA(fdc, i),
          .timestamp = fdc->interface.get_time(fdc->interface.platform_context)
        });
        // Status apparently needs to be read again to clear the interrupt
        FDC2214_read_register(fdc, FDC2214_REG_STATUS);
      }
    }
    fdc->handle_interrupt = 0;
    return;
  }
}

void FDC2214_start(FDC2214* fdc) {
  FDC2214_wakeup(fdc);
}

void FDC2214_stop(FDC2214* fdc) {
  FDC2214_sleep(fdc);
}
