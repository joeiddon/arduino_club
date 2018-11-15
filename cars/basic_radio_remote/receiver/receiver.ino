#include <RH_ASK.h>

#define ENA 3
#define ENB 6
#define IN1 2
#define IN2 4
#define IN3 5
#define IN4 7

//rxpin = 11, txpin = 12
RH_ASK driver(3000);

//protocol is to send bytes of:
//[A SPEED, A DIRECTION, B SPEED, B DIRECTION]

void setup() {
    Serial.begin(9600);
    if (!driver.init()){
        Serial.println("init failed");
    }
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    //hacky code to get a 5v output
    pinMode(10, OUTPUT);
}

void loop() {
    digitalWrite(10, HIGH);
    uint8_t message[4];
    uint8_t msg_len = sizeof(message);
    if (driver.recv(message, &msg_len)){
        if (msg_len != 4){
            //Serial.println("wrong message length");
            return;
        }
        //Serial.print("recieved over radio: ");
        for (int i = 0; i < 4; i++){
            //Serial.print(message[i]);
            //Serial.print(' ');
        }   
        //Serial.println();
        set_motors(message[0],
            (bool) message[1],
                   message[2],
            (bool) message[3]);
    }
}

void set_motors(uint8_t a_spd, bool a_dir, uint8_t b_spd, bool b_dir){
    //a_spd, b_spd: 0 - 255
    //a_dir, b_dir: false / true
    
    Serial.print("motor a speed: ");
    Serial.print(a_spd);
    Serial.print(", dir: ");
    Serial.print(a_dir);
    Serial.print("; motor b speed: ");
    Serial.print(b_spd);
    Serial.print(", dir: ");
    Serial.print(b_dir);
    Serial.println();
    digitalWrite(IN1, a_dir);
    digitalWrite(IN2, !a_dir);
    analogWrite(ENA, a_spd);
    digitalWrite(IN3, b_dir);
    digitalWrite(IN4, !b_dir);
    analogWrite(ENB, b_spd);
}
