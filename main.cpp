#include <Arduino.h>

#undef NDEBUG

#define INTB_PIN 0
#define SD_PIN 1 

// MUX_CONFIG.DEGLITCH = 0b100 -> for 3.3MHz < Fsens < 10MHz (Page 20 & 35)  
// important to use the right value or output either stops making any 
// sense above a certain frequency. Maybe gets noisy if Fsens << DEGLITCH
//
// it seems one filter can only be used at the time for 
// all channels. Perhaps we should consider switching configs 
// manually instead of using built in multichannel sampling?

FDC2214Arduino fdc;

static void fdc_config() {
  fdc.fdc.config.SENSOR_ACTIVATE_SEL = 0;
  fdc.fdc.config.REF_CLK_SRC = 1;
  fdc.fdc.config.DEGLITCH = 0b100;
  fdc.fdc.config.RR_SEQUENCE = 0;
  fdc.fdc.config.AUTOSCAN_EN = 1;
  fdc.fdc.config.HIGH_CURRENT_DRV = 0;
  fdc.fdc.config.channels = 2;
  // Channel 0
  fdc.fdc.config.channel[0].lc_inductance = 18e-6;
  fdc.fdc.config.channel[0].lc_capacitance = 10e-12;
  fdc.fdc.config.channel[0].SETTLECOUNT = 4096;
  fdc.fdc.config.channel[0].RCOUNT = 32000; 
  fdc.fdc.config.channel[0].FREF_DIVIDER = 2;
  fdc.fdc.config.channel[0].FIN_SEL = 1;
  fdc.fdc.config.channel[0].IDRIVE = 17;
  // Channel 1
  fdc.fdc.config.channel[1].lc_inductance = 18e-6;
  fdc.fdc.config.channel[1].lc_capacitance = 330e-12;
  fdc.fdc.config.channel[1].SETTLECOUNT = 4096;
  fdc.fdc.config.channel[1].RCOUNT = 32000; 
  fdc.fdc.config.channel[1].FREF_DIVIDER = 2;
  fdc.fdc.config.channel[1].FIN_SEL = 1;
  fdc.fdc.config.channel[1].IDRIVE = 17;
  FDC2214_update_config(&fdc.fdc);
} 

void fdc_on_data(FDC2214Data data) {
  if (data.channel == 0) {
    Serial.print("A: ");
    Serial.print(FDC2214_get_capacitance(&fdc.fdc, &data) * 1e12);
    Serial.print(" ");
    Serial.println(data.timestamp);
  } else if (data.channel == 1) {
    Serial.print("B: ");
    Serial.print(FDC2214_get_capacitance(&fdc.fdc, &data) * 1e12);
    Serial.print(" ");
    Serial.println(data.timestamp);
  }
}

void _start() {
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.print("FDC2214 _start");
  FDC2214_read_current_config(&fdc.fdc);
  FDC2214_start(&fdc.fdc);
  digitalWrite(LED_BUILTIN, LOW);
}

void _stop() {
  Serial.print("FDC2214 _stop");
  FDC2214_stop(&fdc.fdc);
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  digitalWrite(LED_BUILTIN, HIGH);
  FDC2214_Arduino_create(&fdc, SD_PIN, INTB_PIN);
  digitalWrite(LED_BUILTIN, LOW);
  fdc.fdc.on_data = fdc_on_data;
  fdc_config();
  _start();
}

void loop() {
  FDC2214_update(&fdc.fdc);
  // if (should_exit) _stop();
}
