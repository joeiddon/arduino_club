/*
remember to link the grounds between
the arduino and the motor driver

the motors can handle up to ~6V, but must
be about ~6.5V to regulate for 5V, so will
just rely on the PWM to not over work them

some links:
https://www.sparkfun.com/datasheets/Robotics/L298_H_Bridge.pdf  (for the datasheet)
https://www.teachmemicro.com/use-l298n-motor-driver/  (for the breakout)
*/

#define ENA 5
#define ENB 10
#define IN1 6
#define IN2 7
#define IN3 8
#define IN4 9
#define SPEED 10

void setup() {
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
}

void loop() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    for (uint8_t p = 0; p < 255; p++){
        analogWrite(ENA, p);
        analogWrite(ENB, p);
        delay(SPEED);
    }
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    for (uint8_t p = 255; p > 0; p--){
        analogWrite(ENA, p);
        analogWrite(ENB, p);
        delay(SPEED);
    }
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    for (uint8_t p = 0; p < 255; p++){
        analogWrite(ENA, p);
        analogWrite(ENB, p);
        delay(SPEED);
    }
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    for (uint8_t p = 255; p > 0; p--){
        analogWrite(ENA, p);
        analogWrite(ENB, p);
        delay(SPEED);
    }
}
