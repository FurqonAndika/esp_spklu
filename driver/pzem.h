/*
Copyright (c) 2021 Jakub Mandula

Example of using one PZEM module with Software Serial interface.
================================================================

If only RX and TX pins are passed to the constructor, software 
serial interface will be used for communication with the module.

*/

#include "../src/PZEM/src/PZEM004Tv30.h"
#include <SoftwareSerial.h>

#if defined(ESP32)
    #error "Software Serial is not supported on the ESP32"
#endif

/* Use software serial for the PZEM
 * Pin 12 Rx (Connects to the Tx pin on the PZEM)
 * Pin 13 Tx (Connects to the Rx pin on the PZEM)
*/
// #if !defined(PZEM_RX_PIN) && !defined(PZEM_TX_PIN)
// #define PZEMR_RX_PIN D6
// #define PZEMR_TX_PIN D5
// #define PZEMS_RX_PIN D0
// #define PZEMS_TX_PIN D7
// #define PZEMT_RX_PIN D1
// #define PZEMT_TX_PIN D0
// #endif


// SoftwareSerial pzemSWSerial_R(PZEMS_RX_PIN, PZEMS_TX_PIN);
// SoftwareSerial pzemSWSerial_S(PZEMR_RX_PIN, PZEMR_TX_PIN);

// SoftwareSerial pzemSWSerial_T(PZEMT_RX_PIN, PZEMT_TX_PIN);
// SoftwareSerial pzemSWSerial_T(PZEMT_RX_PIN, PZEMT_TX_PIN);

PZEM004Tv30 pzem_R(13,16);
PZEM004Tv30 pzem_S(D5,D6);
PZEM004Tv30 pzem_T(Serial);


float Voltage_R(){
    return pzem_R.voltage();
}


float Voltage_S(){
    return pzem_S.voltage();
}


float Voltage_T(){
    return pzem_T.voltage();
}

float Current_R(){
    return pzem_R.current();
}

float Current_S(){
    return pzem_S.current();
}

float Current_T(){
    return pzem_T.current();
}


/*
void loop() {
         
    Serial.print("Custom Address:");
    Serial.println(pzem.readAddress(), HEX);

    // Read the data from the sensor
    float voltage = pzem.voltage();
    float current = pzem.current();
    float power = pzem.power();
    float energy = pzem.energy();
    float frequency = pzem.frequency();
    float pf = pzem.pf();

    // Check if the data is valid
    if(isnan(voltage)){
        Serial.println("Error reading voltage");
    } else if (isnan(current)) {
        Serial.println("Error reading current");
    } else if (isnan(power)) {
        Serial.println("Error reading power");
    } else if (isnan(energy)) {
        Serial.println("Error reading energy");
    } else if (isnan(frequency)) {
        Serial.println("Error reading frequency");
    } else if (isnan(pf)) {
        Serial.println("Error reading power factor");
    } else {

        // Print the values to the Serial console
        Serial.print("Voltage: ");      Serial.print(voltage);      Serial.println("V");
        Serial.print("Current: ");      Serial.print(current);      Serial.println("A");
        Serial.print("Power: ");        Serial.print(power);        Serial.println("W");
        Serial.print("Energy: ");       Serial.print(energy,3);     Serial.println("kWh");
        Serial.print("Frequency: ");    Serial.print(frequency, 1); Serial.println("Hz");
        Serial.print("PF: ");           Serial.println(pf);
    }

    Serial.println();
    delay(2000);
}

*/