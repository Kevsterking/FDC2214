#ifdef ARDUINO

#include <Arduino.h>
#include <Wire.h>
//#include <stdio.h>

//#include <SD/SD.h>

#include "FDC2214.h"
#include "../core/core.h"


void _sd_low(void* platform_context) {
  //SD_create_new_file(&session1, "debug", "txt");


  /* int pin = ((FDC2214ArduinoContext*)platform_context)->sd_pin;

  char buffer[64];
  sprintf(buffer, "%d", pin);
  SD_write(&session1, buffer);
  SD_close_file(&session1); */

  // digitalWrite(1, LOW);
  
  digitalWrite(((FDC2214Arduino*)platform_context)->sd_pin, LOW);
  
}

void _sd_high(void* platform_context) {
  digitalWrite(((FDC2214Arduino*)platform_context)->sd_pin, HIGH);
}

void _write16(void* platform_context, uint8_t address, uint16_t data) {
  Wire.beginTransmission(FDC2214_I2C_ADDRESS);
  Wire.write(address);
  Wire.write((uint8_t)(data >> 8));
  Wire.write((uint8_t)data);
  Wire.endTransmission();
}

uint16_t _read16(void* platform_context, uint8_t address) {
  Wire.beginTransmission(FDC2214_I2C_ADDRESS);
  Wire.write(address);
  Wire.endTransmission();
  Wire.requestFrom(FDC2214_I2C_ADDRESS, 2);
  uint16_t data = 0x00;
  if (2 <= Wire.available()) {
    data = (Wire.read() << 8) + Wire.read();
  }
  return data;
}

void _sleep(void* platform_context, uint32_t ms) {
  delay(ms);
}

uint64_t _get_time(void* platform_context) {
  return millis();
}

void _print(void* platform_context, char* str) {
  Serial.println(str);
}

FDC2214* fdcp;

void _isr() {
  FDC2214_ISR(fdcp);
}

void FDC2214_Arduino_create(FDC2214Arduino* fdc, uint8_t sd_pin, uint8_t intb_pin) {
  fdcp = &fdc->fdc;
  pinMode(sd_pin, OUTPUT);
  pinMode(intb_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(intb_pin), _isr, FALLING);
  fdc->fdc.interface.platform_context = fdc;
  fdc->fdc.interface.set_sd_pin_low = _sd_low;
  fdc->fdc.interface.set_sd_pin_high = _sd_high;
  fdc->fdc.interface.read16 = _read16;
  fdc->fdc.interface.write16 = _write16;
  fdc->fdc.interface.sleep = _sleep;
  fdc->fdc.interface.log = _print;
  fdc->fdc.interface.get_time = _get_time;
  FDC2214_create(&fdc->fdc);
}

void FDC2214_Arduino_destroy(FDC2214* fdc) {
  free(fdc->interface.platform_context);
}

#endif
