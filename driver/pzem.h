#include "../src/PZEM/src/PZEM004Tv30.h"
#include <SoftwareSerial.h>

#if defined(ESP32)
    #error "Software Serial is not supported on the ESP32"
#endif


PZEM004Tv30 pzem_R(13,16);  //PIN D7, D0
PZEM004Tv30 pzem_S(D5,D6);   //PIN D5. D6
PZEM004Tv30 pzem_T(Serial);  //PIN TX, RX


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

