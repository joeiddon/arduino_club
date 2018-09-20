/*
Servo Driver Datasheet:
https://cdn-learn.adafruit.com/downloads/pdf/16-channel-pwm-servo-driver.pdf

Wiring:
A5 --> SCL
A4 --> SDA

Terminology:
 *with y axis orientated forward*
 - `legs` refer to the 6 servos connected to the body
     that rotate around the z axis.
 - `feet` refer to the servos on the ends of the legs
     that rotate around the x axis.
*/

//include relevent libraries
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

//create a `PWMServoDriver` object called `pwm`
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//the min and max servo pulse widths out of 4096
#define SERVOMIN    150
#define SERVOMAX    600

//the pause between each walking position
#define PAUSE_LENGTH 4000

//up and down servo positions in walking sequence (L = leg, F = foot)
#define LU    85    //leg up (forward)
#define LD    95    //leg down (bakward)
#define FLU   130   //front left foot up
#define FRU   50    //front right foot up
#define FLD   90    //front left foot down
#define FRD   90    //front right foot down

//variables
//keeps track of which walking position we are in for the switch...case
int mode = 0;

//two length 6 arrays to store the boolean positions of the limbs
int legs[6];
int feet[6];

void setup() {
    //serial is useful for debugging...
    Serial.begin(9600);
    //call begin on the pwm object (just establishes the i2c connection)
    //i.e. call WIRE.begin()
    pwm.begin();
    //set the frequency of how often the IC sends a pulse to the servos
    //can be from 40Hz - 1000Hz
    pwm.setPWMFreq(60);
}

void loop() {
    switch (mode){
        case 0:
            set_servos(LD,LU,LD, LD,LU,LD, FLU,FLD,FLU, FRD,FRU,FRD);
            break;
        case 1:
            set_servos(LD,LU,LD, LD,LU,LD, FLD,FLD,FLD, FRD,FRD,FRD);
            break;
        case 2:
            set_servos(LD,LU,LD, LD,LU,LD, FLD,FLU,FLD, FRU,FRD,FRU);
            break;
        case 3:
            set_servos(LU,LD,LU, LU,LD,LU, FLD,FLU,FLD, FRU,FRD,FRU);
            break;
        case 4:
            set_servos(LU,LD,LU, LU,LD,LU, FLD,FLD,FLD, FRD,FRD,FRD);
            break;
        case 5:
            set_servos(LU,LD,LU, LU,LD,LU, FLU,FLD,FLU, FRD,FRU,FRD);
            break;
    }
    if (mode++ > 5) mode = 0;
    delay(PAUSE_LENGTH);
}

//takes 12 servo positions (in degrees) and writes to the servos
void set_servos(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k, int l){
    set_servo(0,  a);
    set_servo(1,  b);
    set_servo(2,  c);
    set_servo(3,  d);
    set_servo(4,  e);
    set_servo(5,  f);
    set_servo(6,  g);
    set_servo(7,  h);
    set_servo(8,  i);
    set_servo(9,  j);
    set_servo(10, k);
    set_servo(11, l);
}

//function that moves a servo to an angle in degrees (0 - 180)
void set_servo(int servo, int angle){
    //define a variable for how long to have the pulse be on for
    //we do this by mapping the angle to the servo min and max pulse lengths
    int pulse_len = map(angle, 0, 180, SERVOMIN, SERVOMAX);
    //then we set the servo position to that pulse length
    //the second arg is 0 as the servos begin at high and then drop to low
    pwm.setPWM(servo, 0, pulse_len);
}
