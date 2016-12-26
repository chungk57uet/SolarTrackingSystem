#include <Stepper.h>

#define pin1  8
#define pin2  9
#define pin3  10
#define pin4  11

#define delaytime 80

int ssP1 = 0;
int ssP2 = 1;
int ssP3 = 2;
int lightPin = 2;

// Variables
int lowThreshold = 180;
int highTreshold = 280;

void setup() {

   // initialize the 8 pin as an output:
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT); 
  pinMode(pin3, OUTPUT); 
  pinMode(pin4, OUTPUT);
  
  Serial.begin(9600);
  pinMode(lightPin,OUTPUT);
}

void loop() {
  
  // Read the sensor pin
  int ssV1 = analogRead(ssP1);
  int ssV2 = analogRead(ssP2);
  int ssV3 = analogRead(ssP3);
  Serial.print(ssV1);
  Serial.print(" ");
  Serial.print(ssV2);
  Serial.print(" ");
  Serial.println(ssV3);
  if ((ssV1 > ssV3) && (ssV1 > ssV2) && (ssV3 > ssV2))
    if (ssV1 - ssV3 < 10)
      step_OFF();
      else
      forward();
      else if ((ssV1 < ssV3) && (ssV1 > ssV2) && (ssV3 > ssV2))
      if (ssV3 - ssV1 < 10)
        step_OFF();
        else
        backward();
        else if ((ssV2 > ssV1) && (ssV2> ssV3))
          step_OFF();
          
  if (ssV1 < lowThreshold){
    digitalWrite(lightPin, HIGH);
  }

  if (ssV1 > highTreshold){ 
    digitalWrite(lightPin, LOW);
  }
}


void Step_A(){
  digitalWrite(pin1, HIGH);//turn on coil 1 
  digitalWrite(pin2, LOW); 
  digitalWrite(pin3, LOW); 
  digitalWrite(pin4, LOW); 
}
void Step_B(){
  digitalWrite(pin1, LOW); 
  digitalWrite(pin2, HIGH);//turn on coil 2
  digitalWrite(pin3, LOW); 
  digitalWrite(pin4, LOW); 
}
void Step_C(){
  digitalWrite(pin1, LOW); 
  digitalWrite(pin2, LOW); 
  digitalWrite(pin3, HIGH); //turn on coil 3
  digitalWrite(pin4, LOW); 
}
void Step_D(){
  digitalWrite(pin1, LOW); 
  digitalWrite(pin2, LOW); 
  digitalWrite(pin3, LOW); 
  digitalWrite(pin4, HIGH); //turn on coil 4
}
void step_OFF(){
  digitalWrite(pin1, LOW); //power all coils down
  digitalWrite(pin2, LOW); 
  digitalWrite(pin3, LOW); 
  digitalWrite(pin4, LOW); 
}

void forward(){
  Step_A();
  delay(delaytime);
  Step_B();
  delay(delaytime);
  Step_C();
  delay(delaytime);
  Step_D();
  delay(delaytime);
}

void backward(){//one tooth backward
  Step_D();
  delay(delaytime);
  Step_C();
  delay(delaytime);
  Step_B();
  delay(delaytime);
  Step_A();
  delay(delaytime);
}

