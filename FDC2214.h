#ifndef FDC2214_H
#define FDC2214_H

#include <stdint.h>

#include <FDC2214/definitions.h>

void FDC2214_create(FDC2214* fdc);
void FDC2214_update(FDC2214* fdc);
void FDC2214_start(FDC2214* fdc);
void FDC2214_stop(FDC2214* fdc);

// Configuration
void FDC2214_update_config(FDC2214* fdc);
FDC2214Config FDC2214_read_current_config(FDC2214* fdc);

// Calculations
uint32_t FDC2214_get_data(FDC2214* fdc, uint8_t channel);
double FDC2214_get_frequency(FDC2214* fdc, FDC2214Data* data);
double FDC2214_get_capacitance(FDC2214* fdc, FDC2214Data* data);

#endif // FDC2214_H