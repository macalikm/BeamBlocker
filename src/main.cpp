/*  This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
    It won't work with v1.x motor shields! Only for the v2's with built in PWM
    control

    For use with the Adafruit Motor Shield v2 
    ---->	http://www.adafruit.com/products/1438
    Quantum Communications Laboratory
    CathodeRay 20201028
    Added Comment
*/

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
int STEPS = 255;
int DLY02S = 2000;
int DLY04S = 4000;

int motorPin1 = 8;
int motorPin2 = 9;
int motorPin3 = 10;
//int motorPin4 = 11;

bool up1 = false;
bool up2 = false;
bool up3 = false;
bool up4 = false;


bool dn1 = true;
bool dn2 = true;
bool dn3 = true;
bool dn4 = true;

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS1 = Adafruit_MotorShield(0x60); 
Adafruit_MotorShield AFMS2 = Adafruit_MotorShield(0x61); 


// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port 1 and 2 (M1 and M2) and (M3 and M4)
Adafruit_StepperMotor *flagMotor1 = AFMS1.getStepper(200, 1);
Adafruit_StepperMotor *flagMotor2 = AFMS1.getStepper(200, 2);
Adafruit_StepperMotor *flagMotor3 = AFMS2.getStepper(200, 1);
Adafruit_StepperMotor *flagMotor4 = AFMS2.getStepper(200, 2);

void setup() {
  pinMode(motorPin1, INPUT);    //set control input pins
  pinMode(motorPin2, INPUT);
  pinMode(motorPin3, INPUT);
//  pinMode(motorPin4, INPUT);
  
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Stepper driver On-line...");

  AFMS1.begin();  // create with the default frequency 1.6KHz
  AFMS2.begin();  // create with the default frequency 1.6KHz
  //AFMSx.begin(1000);  // OR with a different frequency, say 1KHz
  
  flagMotor1->setSpeed(70);  // 70 rpm 
  flagMotor2->setSpeed(70);  // 70 rpm 
  flagMotor3->setSpeed(70);  // 70 rpm 
  flagMotor4->setSpeed(70);  // 70 rpm   
}

void loop() {

//
//Flag 1 motor control loop
//
  if ( digitalRead(motorPin1) == HIGH && up1 == false) {
    Serial.println("Raise Flag 1");
    flagMotor1->step(STEPS, FORWARD, DOUBLE); 
//    if ( up4 == false ){
//      Serial.print("Raise Flag 4\n");
//      up4 = true;
//    } 
    up1 = true;
    dn1 = false;
    delay(DLY02S);
  }
 
  if ( digitalRead(motorPin1) == LOW && up1 == true) {
    Serial.println("Lower Flag 1");
    flagMotor1->step(STEPS, BACKWARD, DOUBLE);
//    if ( up4 == true) {
//      Serial.print("lower Flag 4\n");
//      flagMotor4->step(STEPS, BACKWARD, DOUBLE); 
//      up4 = false;
//    }
    up1 = false;
    dn1 = true;
    delay(DLY02S);
  }

//
//Flag 2 motor control loop
//
  int flag2 = digitalRead(motorPin2);
  if ( flag2 >= 1 && up2 == false ) {
    Serial.println("Raise Flag 2");
    flagMotor2->step(STEPS, FORWARD, DOUBLE); 
    up2 = true;
    dn2 = false;
    delay(DLY02S);
  }
  flag2 = digitalRead(motorPin2); 
  if ( flag2 < 1 && dn2 == false ) {
    Serial.println("Lower Flag 2");
    flagMotor2->step(STEPS, BACKWARD, DOUBLE);
    Serial.println("Lower Flag 2");
    dn2 = true;
    up2 = false;
    delay(DLY02S);
  }

//
//Flag 3 motor control loop
//
  int flag3 = digitalRead(motorPin3);
  if ( flag3 >= 1 && up3 == false ) {
    Serial.println("Raise Flag 3");
    flagMotor3->step(STEPS, FORWARD, DOUBLE); 
    up3 = true;
    dn3 = false;
    delay(DLY02S);
  }
  flag3 = digitalRead(motorPin3); 
  if ( flag3 < 1 && dn3 == false ) {
    Serial.println("Lower Flag 3");
    flagMotor3->step(STEPS, BACKWARD, DOUBLE);
    dn3 = true;
    up3 = false;
    delay(DLY02S);
  }

//
// Flag 4 motor control loop
// Wave meter shutter
//  If 1,2, or 3 are up Raise flag 4
//
bool flag4;
 
 if ( up1 == true || up2 == true || up3 == true ){
    flag4 = true;
    }
   else {
    flag4 = false;
   }
  
 if ( (up1 == true || up2 == true || up3 == true) && up4 == false ) {
    Serial.println("Raise Flag 4");
    flagMotor4->step(STEPS, FORWARD, DOUBLE); 
    up4 = true;
    dn4 = false;
    delay(DLY02S);
  }

 if ( up1 == false && up2 == false && up3 == false && up4 == true ) {
    Serial.println("Lower Flag 4");
    flagMotor4->step(STEPS, BACKWARD, DOUBLE);
    dn4 = true;
    up4 = false;
    delay(DLY02S);
 }
} // End of Sketch
