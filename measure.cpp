#include "core/core.h"

#define TWO_PI 6.283185307179
#define TWO_TO_28 268435456

uint32_t FDC2214_get_data(FDC2214* fdc, uint8_t channel) {
    return fdc->data[channel];
}

double FDC2214_get_frequency(FDC2214* fdc, FDC2214Data* data) {
    // DATAx, fREF, FIN_SEL -> Fsens (Page 18)
    uint8_t fin_sel = FDC2214_get_FIN_SEL(fdc, data->channel);
    double fref = FDC2214_get_FREF(fdc, data->channel);
    return (((double)fin_sel * (double)fref * (double)data->data)) / ((double)TWO_TO_28);
}

double FDC2214_get_capacitance(FDC2214* fdc, FDC2214Data* data) {
    // DATAx, fREF, FIN_SEL -> Fsens (Page 18)
    double pwr = TWO_PI * FDC2214_get_frequency(fdc, data);
    return (((double) 1) / ((double) fdc->config.channel[data->channel].lc_inductance * pwr * pwr)); //- fdc->config.channel[data->channel].lc_capacitance;
}
