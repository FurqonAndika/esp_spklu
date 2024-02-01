#define BUZZER_PIN D3


void buzzer_init(){
    pinMode(BUZZER_PIN,OUTPUT);
}
void buzzer_once(){
    digitalWrite(BUZZER_PIN,HIGH);
    delayMicroseconds(250);
    digitalWrite(BUZZER_PIN,LOW);
}

void buzzer_twice(){
    buzzer_once();
    delayMicroseconds(150);
    buzzer_once();
}