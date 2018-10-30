/*
 * radio head documentation:
 * https://www.airspayce.com/mikem/arduino/RadioHead/classRH__ASK.html
 * download link:
 * http://www.airspayce.com/mikem/arduino/RadioHead/RadioHead-1.41.zip
 * tutorial: 
 * https://randomnerdtutorials.com/rf-433mhz-transmitter-receiver-module-with-arduino/
 */

/*
 arrays are always passed as addresses, so passing message is equivalent to &message[0]
 & means "address of a value", * means the "value at that address"
 in declarations, *p = 5 means place 5 in memory and give me a pointer to it
 you can assign to pointers too with, e.g., *p += 1 meaning take the pointer, p gets its value and add 1
*/

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
    uint8_t message[50];
    uint8_t msg_len = sizeof(message);
    if (driver.recv(message, &msg_len)){
        for (int i = 0; i < msg_len; i++){
            Serial.print((char) message[i]);
        }
        Serial.println();
    }
}
