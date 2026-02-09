#ifndef FDC2214_ARDUINO_H
#define FDC2214_ARDUINO_H

#include "../FDC2214.h"

typedef struct {
  FDC2214 fdc;
  uint8_t sd_pin;
  uint8_t intb_pin;
} FDC2214Arduino;

void FDC2214_Arduino_create(FDC2214Arduino* fdc, uint8_t sd_pin, uint8_t intb_pin);
void FDC2214_Arduino_destroy(FDC2214Arduino* fdc);

#endif // FDC2214_ARDUINO_H