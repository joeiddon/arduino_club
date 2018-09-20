/*
Useful .pdf:
https://cdn-learn.adafruit.com/downloads/pdf/16-channel-pwm-servo-driver.pdf

Wiring:
A5 --> SCL
A4 --> SDA
*/

//include relevent libraries
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

//create a `PWMServoDriver` object called `pwm`
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//define the min and max servo pulse widths (out of 4096)
#define SERVOMIN    150
#define SERVOMAX    600


void setup() {
    //call begin on the pwm object (just establishes the i2c connection)
    //i.e. call WIRE.begin()
    pwm.begin();
    //set the frequency of how often the IC sends a pulse to the servos
    //can be from 40Hz - 1000Hz
    pwm.setPWMFreq(60);
}

//function that moves a servo to an angle in degrees (0 - 180)
void setServo(int servo, int angle){
    //define a variable for how long to have the pulse be on for
    //we do this by mapping the angle to the servo min and max pulse lengths
    int pulseLength = map(angle, 0, 180, SERVOMIN, SERVOMAX);
    //then we set the servo position to that pulse length
    //the second arg is 0 as the servos begin at high and then drop to low
    pwm.setPWM(servo, 0, pulseLength);
}

//loops through the first 3 servos, prints and moves to 180 then back to 0
void loop() {
    for (int s = 0; s < 12; s++) {
        for (int p = 0; p < 180; p++){
            setServo(s, p);
            delay(2);
        }
        for (int p = 180; p > 0; p--){
            setServo(s, p);
            delay(2);
        }
    }
    delay(200);
}
