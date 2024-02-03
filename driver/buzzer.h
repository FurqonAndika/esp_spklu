#define BUZZER_PIN 10   //s3


void buzzer_init(){
    pinMode(BUZZER_PIN,OUTPUT);
      digitalWrite(BUZZER_PIN,LOW);
}
void buzzer_once(){
    digitalWrite(BUZZER_PIN,HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN,LOW);
}

void buzzer_twice(){
    buzzer_once();
    delay(100);
    buzzer_once();
}