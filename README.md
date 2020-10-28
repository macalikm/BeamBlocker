**Add details about BeamBlocker**

Arduino Uno sketch.
uses 2 Adafruit Motor Drive Shields v2.
I2C Addresses are 0x60 for Motors 1 and 2.
and 0x61 for Motors 3 and 4.

Adafruit_MotorShield AFMS1 = Adafruit_MotorShield(0x60) 
Adafruit_MotorShield AFMS2 = Adafruit_MotorShield(0x61) 

###Beam Blocker Flag for each trap's beam path:
Input 1,2, or 3 are active (logic HIGH level)
the corroeponding output will activate its stepper in the FORWARD DIRECTION
thus raising the beam blocker flag.

###Control the Wavemeter path:
motor output 4 will drive forward if inputs 1 or 2 or 3 are active.
Otherwise it will drive in the REVERSE direction. This output is intended to