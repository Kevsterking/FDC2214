#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "core.h"
#include "log.h"

void FDC2214_log(FDC2214* fdc, const char* format, ...) {
  // Construct message
  char log_message[FDC2214_LOG_MESSAGE_MAXLEN];
  va_list args;
  va_start(args, format);
  vsnprintf(log_message, FDC2214_LOG_MESSAGE_MAXLEN, format, args);
  va_end(args);
  fdc->interface.log(fdc->interface.platform_context, log_message);
}

void FDC2214_log_status(FDC2214* fdc, uint32_t status) {
  if (status & FDC2214_ERR_AHW) {
    FDC2214_LOG_WARNING(fdc, "(FDC2214_ERR_AHW) HIGH Peak Amplitude (>1.8V) Was Detected on Channel %i", _STATUS_CHANNEL(status));
  }
  if (status & FDC2214_ERR_ALW) {
    FDC2214_LOG_WARNING(fdc, "(FDC2214_ERR_ALW) Low Peak Amplitude (<1.2V) Was Detected on Channel %i", _STATUS_CHANNEL(status));
  }
  if (status & FDC2214_ERR_WD) {
    FDC2214_LOG_ERROR(fdc, "(FDC2214_ERR_WD) Watchdog Timeout Triggered on Channel %i", _STATUS_CHANNEL(status));
  }
  if (status & FDC2214_DRDY) {
    FDC2214_LOG_DEBUG(fdc, "(FDC2214_DRDY) Data Conversion Result is Ready");
  }
  if (status & FDC2214_CH0_UNREADCONV) {
    FDC2214_LOG_DEBUG(fdc, "(FDC2214_CH0_UNREADCONV) CH0 Has Buffered Results");
  }
  if (status & FDC2214_CH1_UNREADCONV) {
    FDC2214_LOG_DEBUG(fdc, "(FDC2214_CH1_UNREADCONV) CH1 Has Buffered Results");
  }
  if (status & FDC2214_CH2_UNREADCONV) {
    FDC2214_LOG_DEBUG(fdc, "(FDC2214_CH2_UNREADCONV) CH2 Has Buffered Results");
  }
  if (status & FDC2214_CH3_UNREADCONV) {
    FDC2214_LOG_DEBUG(fdc, "(FDC2214_CH3_UNREADCONV) CH3 Has Buffered Results");
  }
}
