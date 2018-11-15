#include <RH_ASK.h>

//rxpin = 11, txpin = 12
RH_ASK driver;

void setup() {
    Serial.begin(9600);
    if (!driver.init()){
        Serial.println("init failed");
    }
}

void loop() {
    uint8_t queued_bytes = Serial.available();
    if (queued_bytes >= 4){
        uint8_t message[4];
        for (uint8_t i = 0; i < 4; i ++){
            message[i] = Serial.read();    
        }
        driver.send(message, 4);
        //empty the queue in case of error
        while (Serial.available()) Serial.read();
    }
}
