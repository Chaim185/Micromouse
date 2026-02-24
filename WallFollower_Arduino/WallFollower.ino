#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(3);
Adafruit_DCMotor *myMotor3 = AFMS.getMotor(2);

const int pin1 = A2;
const int pin2 = A1;
const int led = 7;
const int led2 = 8;

const int echo = 5;
const int trig = 8;

const int echo2 = 6;
const int trig2 = 9;

const int echo3 = 7;
const int trig3 = 10;

long cm2 = 200;
long cm3 = 35;
long previouscm3[150];
long previouscm2[150];
int i = -1;

void setup() {
  Serial.begin(9600);
  if (!AFMS.begin()) {
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  myMotor2->setSpeed(20);
  myMotor3->setSpeed(20);

  myMotor2->run(FORWARD);
  myMotor3->run(FORWARD);

  myMotor2->run(RELEASE);
  myMotor3->run(RELEASE);

  forward();
  delay(1000);
}

void loop() {
  i++;
  if (i >= 150)
    i = 0;

  if (i == 0)
  {
    previouscm3[i] = 35;
    previouscm2[i] = 200;
  }
   else
   {
    previouscm3[i] = cm3;
    previouscm2[i] = cm2;
   }
  //delay(2000);
///////////////////////////////////////////
 /* long duration, cm;
///////////////////////////////////////////
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);
///////////////////////////////////////////
  pinMode(echo, INPUT);
  duration = pulseIn(echo, HIGH);
///////////////////////////////////////////
  cm = microsecondsToCentimeters(duration);
///////////////////////////////////////////
  Serial.print(cm);
  Serial.print("cm");
  Serial.print("          ");
  //Serial.println();
///////////////////////////////////////////
  delay(200);
*/

///////////////////////////////////////////
  long duration2;
///////////////////////////////////////////
  pinMode(trig2, OUTPUT);
  digitalWrite(trig2, LOW);
  delayMicroseconds(2);
  digitalWrite(trig2, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig2, LOW);
///////////////////////////////////////////
  pinMode(echo2, INPUT);
  duration2 = pulseIn(echo2, HIGH);
///////////////////////////////////////////
  cm2 = microsecondsToMilimeters(duration2);
///////////////////////////////////////////
  Serial.print(cm2);
  Serial.print("cm2");
  Serial.print("          ");
///////////////////////////////////////////
  delay(20);

  
  
  
  

///////////////////////////////////////////
  long duration3;

  
    
///////////////////////////////////////////
  pinMode(trig3, OUTPUT);
  digitalWrite(trig3, LOW);
  delayMicroseconds(2);
  digitalWrite(trig3, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig3, LOW);
///////////////////////////////////////////
  pinMode(echo3, INPUT);
  duration3 = pulseIn(echo3, HIGH);
///////////////////////////////////////////
  cm3 = microsecondsToMilimeters(duration3);
///////////////////////////////////////////
  Serial.print(cm3);
  Serial.print("cm3");
  Serial.println();
///////////////////////////////////////////
  delay(20);

  traverse(cm2, cm3, previouscm3, previouscm2);
}


long microsecondsToMilimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 2.9 / 2;
}

bool isStuckonLeft(long *previousmm2, long *previousmm3) {

  if (isStuckonRight(previousmm3))
    return false;
    
    for(int j=2; j < 150; j++)
    {
      if (abs(previousmm2[j] - previousmm2[j-1]) > 15) 
        return false;
    }
    
  return true;
}

bool isStuckonRight(long *previousmm3) {
    for(int j=2; j < 150; j++)
    {
      if ( (abs(previousmm3[j] - previousmm3[j-1]) > 3) || (previousmm3[j] > 100) || (previousmm3[j] < 50) ) 
      return false;
    }
    
  return true;
}

void forward(){
  myMotor2->setSpeed(20);
  myMotor3->setSpeed(20);

  myMotor2->run(FORWARD);
  myMotor3->run(FORWARD);
}

void backward(){

  myMotor2->setSpeed(20);
  myMotor3->setSpeed(20);
  
  myMotor2->run(BACKWARD);
  myMotor3->run(BACKWARD);
}

void stop(){

  myMotor2->run(RELEASE);
  myMotor3->run(RELEASE);
}

void left(){

  myMotor2->setSpeed(20);
  myMotor3->setSpeed(20);

  myMotor2->run(BACKWARD);
  myMotor3->run(FORWARD);

}

void right(){

  myMotor2->setSpeed(20);
  myMotor3->setSpeed(20);

  myMotor2->run(FORWARD);
  myMotor3->run(BACKWARD);
}

void oneSpaceForward() {

  forward();
  delay(2100);
 // stop();
 //delay(1000);
}

void veerRight(long mm3) {

long error = 35 - mm3;
  /*if ( (mm3 > 10) && (mm3 < 40) )
  {
    myMotor2->setSpeed(20);
    myMotor3->setSpeed(19);
  }
  else //if (mm3 > 10)
  {
    stop();
    delay(1000);
    myMotor2->setSpeed(20);
    myMotor3->setSpeed(18);
  }/*
  else
  {*/
    myMotor2->setSpeed(20);
    myMotor3->setSpeed(19);
  

  myMotor2->run(FORWARD);
  myMotor3->run(FORWARD);
}

void veerLeft(long mm3) {

long error = mm3 - 35;
  /*if (mm3 < 45)
  {
    myMotor2->setSpeed(19);
    myMotor3->setSpeed(20);
  }
  else //if (mm3 < 50)
  {
    myMotor2->setSpeed(18);
    myMotor3->setSpeed(20);
  }/*
  else
  {
    myMotor2->setSpeed(17);
    myMotor3->setSpeed(20);
  }*/
  myMotor2->setSpeed(19);
  myMotor3->setSpeed(20);

  myMotor2->run(FORWARD);
  myMotor3->run(FORWARD);
}

void maintainStraightLine(long mm3, long *previousmm3, long *previousmm2) {
  if (isStuckonRight(previousmm3))  // crashed into rightt wall
  {
    stop();
    delay(500);
    backward();
    delay(2000);
    stop();
    delay(1500);
    veerRight(mm3);
    delay(2000);
    return;
  }
  else if (isStuckonLeft(previousmm2, previousmm3))  // crashed into left wall
  {
    stop();
    delay(500);
    backward();
    delay(2000);
    stop();
    delay(1500);
    veerRight(mm3);
    delay(2000);
    return;
  }
    
  if ( (mm3 < 35) || (mm3 > 8000) )
    veerRight(mm3);
  else if ( (mm3 >= 35) && (mm3 < 45) ) 
    forward();
  else
    veerLeft(mm3);
}

void traverse(long mm2, long mm3, long *previousmm3, long *previousmm2) {

  //oneSpaceForward();
     if ( (mm2 < 30) || (mm2 > 8000) ) // barrier ahead
     {
        stop();
        delay(1000);
        if ( (mm3 > 150) && (mm3 < 8000) ) // no wall on left
        {
          left();
          delay(930);
          stop();
          delay(1000);
          oneSpaceForward();
          return;
        }
        else // wall on left
        {
          right();
          delay(910);
          stop();
          delay(1000);
        }
     } 
     else if ( (mm3 > 150) && (mm3 < 8000) ) // no barrier ahead and no wall on left
     {
        delay(1000);
        stop();
        delay(1000);
        left();
        delay(930);
        stop();
        delay(1000);
        oneSpaceForward();
        return;
     }
      
     //forward();
     maintainStraightLine(mm3, previousmm3, previousmm2);
}
