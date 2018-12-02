
/*
  INA260 Current Sensor
*/
  

#include "Arduino.h"
#include <Wire.h>
#include <Thanos_INA260.h>


Thanos_INA260 ina260;

//****Global Variable Definition*********************************
#define SERIAL_BAUD   9600
float shunt_volts = 0;  //INA260 shunt voltage
float bus_volts   = 0;  //INA260 bus voltage
float bus_current = 0;  //INA260 bus current
uint8_t alert_i   = HIGH;
float current_thresh = 8800; //Overcurrent Threshold, above = PA Overcurrent fault state

void setup() {
  //Initialize USB Serial
  SerialUSB.begin(SERIAL_BAUD);

  //Initialize current Sensor
  ina260.begin(0x40);

  
}

void loop() {
  /* ---- GET DC Power information---- */
  getDCPower(&shunt_volts, &bus_volts, &bus_current);
  printTlmString();
  delay(100);
}

void printTlmString(){
  SerialUSB.print("$,");
  SerialUSB.print(shunt_volts); SerialUSB.print(",");
  SerialUSB.print(bus_volts); SerialUSB.print(",");
  SerialUSB.println(bus_current);
  return;
}

void getDCPower(float* shuntvoltage, float* busvoltage, float* current_mA)
{
  *shuntvoltage = ina260.getShuntVoltage_mV();
  *busvoltage   = ina260.getBusVoltage_V();
  *current_mA   = ina260.getCurrent_mA();
  delay(10); //small delay for the terminal
  return;  
}
