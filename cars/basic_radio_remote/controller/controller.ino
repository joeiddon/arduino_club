#include <RH_ASK.h>

#define POT_PIN_1 0
#define POT_PIN_2 1
#define DIR_BUT_1 2
#define DIR_BUT_2 3

//rxpin = 11, txpin = 12
RH_ASK driver(3000); //change bit rate !!!

//protocol is to send bytes of:
//[A SPEED, A DIRECTION, B SPEED, B DIRECTION]

void setup() {
    //Serial.begin(9600);
    if (!driver.init()){
        //Serial.println("init failsed");
    }
    pinMode(DIR_BUT_1, INPUT_PULLUP);
    pinMode(DIR_BUT_2, INPUT_PULLUP);
}

void loop() {
    uint8_t message[4];
    //map pot readings from 0-1024 to 0-256
    uint8_t spd_a = analogRead(POT_PIN_1) / 4;
    uint8_t spd_b = analogRead(POT_PIN_2) / 4;
    uint8_t dir_a = digitalRead(DIR_BUT_1);
    uint8_t dir_b = digitalRead(DIR_BUT_2);
    Serial.println(spd_a);
    message[0] = spd_a;
    message[1] = dir_a;
    message[2] = spd_b;
    message[3] = dir_b;
    driver.send(message, 4);
    delay(10);
}
