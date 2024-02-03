#define pin_relay 2  //pin ini digunakan sebagai relay

void Relay_Init(){
  pinMode (pin_relay, OUTPUT);
   digitalWrite(pin_relay, 0);
}
void Relay_On(){
  digitalWrite(pin_relay, 0);
  // Serial.println("pin relay on");
}

void Relay_Off(){
  digitalWrite(pin_relay,     1);
  // Serial.println("pin relay off");
}



