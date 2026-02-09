#ifndef FDC2214_LOG_UTIL_H
#define FDC2214_LOG_UTIL_H

#include <stdint.h>

#include <FDC2214/FDC2214.h>

// STATUS (Page 32)
#define FDC2214_LOG_MESSAGE_MAXLEN 128
#define FDC2214_ERR_WD 1 << 10
#define FDC2214_ERR_AHW 1 << 10
#define FDC2214_ERR_ALW 1 << 9
#define FDC2214_DRDY 1 << 6
#define FDC2214_UNREADCONV_CH(X) 1 << (3 - X)
#define FDC2214_CH0_UNREADCONV 1 << 3
#define FDC2214_CH1_UNREADCONV 1 << 2
#define FDC2214_CH2_UNREADCONV 1 << 1
#define FDC2214_CH3_UNREADCONV 1 << 0

// ALL
#if FDC2214_LOG_LEVEL > FDC2214_LOG_LEVEL_ALL
#define FDC2214_LOG_ALL(fdc, message, ...)
#else
#define FDC2214_LOG_ALL(fdc, message, ...) FDC2214_log((fdc), "[?]: " message, ##__VA_ARGS__)
#endif
// DEBUG
#if FDC2214_LOG_LEVEL > FDC2214_LOG_LEVEL_DEBUG
#define FDC2214_LOG_DEBUG(fdc, message, ...)
#else
#define FDC2214_LOG_DEBUG(fdc, message, ...) FDC2214_log((fdc), "[DEBUG]: " message, ##__VA_ARGS__)
#endif
// WARNING
#if FDC2214_LOG_LEVEL > FDC2214_LOG_LEVEL_WARNING
#define FDC2214_LOG_WARNING(fdc, message, ...)
#else
#define FDC2214_LOG_WARNING(fdc, message, ...) FDC2214_log((fdc), "[WARNING]: " message, ##__VA_ARGS__)
#endif
// ERROR
#if FDC2214_LOG_LEVEL >= FDC2214_LOG_LEVEL_ERROR
#define FDC2214_LOG_ERROR(fdc, message, ...)
#else
#define FDC2214_LOG_ERROR(fdc, message, ...) FDC2214_log((fdc), "[ERROR]: " message, ##__VA_ARGS__)
#endif

#define _STATUS_CHANNEL(STATUS) (uint8_t) ((STATUS >> 14) & 0b11)

void FDC2214_log(FDC2214* fdc, const char* format, ...);
void FDC2214_log_status(FDC2214* fdc, uint32_t status);

#endif // FDC2214_LOG_UTIL_H