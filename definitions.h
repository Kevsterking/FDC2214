#ifndef FDC2214_DEFINITIONS_H
#define FDC2214_DEFINITIONS_H

#include <stdint.h>

#define FDC2214_LOG_LEVEL_ALL 0
#define FDC2214_LOG_LEVEL_DEBUG 1
#define FDC2214_LOG_LEVEL_WARNING 2
#define FDC2214_LOG_LEVEL_ERROR 3
#define FDC2214_LOG_LEVEL_NONE 4

#define FDC2214_LOG_LEVEL FDC2214_LOG_LEVEL_WARNING

#define FDC2214_MAX_CHANNELS 4

// Channel configuration structure
typedef struct {
  float lc_capacitance;
  float lc_inductance;
  uint16_t SETTLECOUNT;
  uint16_t RCOUNT;
  uint8_t FREF_DIVIDER;
  uint8_t FIN_SEL;
  uint8_t IDRIVE;
} FDC2214ChannelConfig;

// Configuration structure
typedef struct {
  uint8_t SENSOR_ACTIVATE_SEL;
  uint8_t REF_CLK_SRC;
  uint8_t DEGLITCH;
  uint8_t RR_SEQUENCE;
  uint8_t AUTOSCAN_EN;
  uint8_t HIGH_CURRENT_DRV;
  uint8_t channels;
  FDC2214ChannelConfig channel[FDC2214_MAX_CHANNELS]; 
} FDC2214Config;

// Platform-specific interface
typedef struct {
  void* platform_context;
  void(*set_sd_pin_low)(void* platform_context);
  void(*set_sd_pin_high)(void* platform_context);
  uint16_t(*read16)(void* platform_context, uint8_t address);
  void(*write16)(void* platform_context, uint8_t address, uint16_t data);
  void(*sleep)(void* platform_context, uint32_t ms);
  uint64_t(*get_time)(void* platform_context);
  void(*log)(void* platform_context, char* str);
} FDC2214Interface;

typedef struct {
  uint8_t channel;
  uint32_t data;
  uint64_t timestamp;
} FDC2214Data;

// FDC2214 structure
typedef struct {
  FDC2214Interface interface;
  FDC2214Config config;
  uint8_t handle_interrupt;
  uint32_t data[FDC2214_MAX_CHANNELS];
  void(*on_data)(FDC2214Data data);
} FDC2214;

#endif // FDC2214_DEFINITIONS_H