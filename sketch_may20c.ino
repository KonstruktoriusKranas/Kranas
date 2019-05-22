#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

int motor_1A = 2;
int motor_1B = 3;
int motor_2A = 5;
int motor_2B = 4;
int motor_3A = 7;
int motor_3B = 6;
int motor_4A=14;-+
int motor_4B=8;

int speedLeft=0;
int speedRight=0;
int Xasis;
int Yasis;
int Y;
int X;
int a;
int b;
int c;
int d;
int joystick[2];
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00002";
void setup() {
  pinMode(motor_1A, OUTPUT); //direction
  pinMode(motor_1B, OUTPUT); //speed
  pinMode(motor_2A, OUTPUT); //direction
  pinMode(motor_2B, OUTPUT); //speed
  pinMode(motor_3A, OUTPUT); //direction
  pinMode(motor_3B, OUTPUT); //speed
  pinMode(motor_4A, OUTPUT); //direction
  pinMode(motor_4B, OUTPUT); //speed
  
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.startListening();
  radio.setPALevel(RF24_PA_MAX);
}


void loop() {
  if (radio.available()) 
  {
      radio.read(joystick, sizeof(joystick));
      Yasis = joystick[0];
      Xasis = joystick[1];
      Serial.print(Xasis);
      Serial.print("\n");
      Serial.print(Yasis);
      Serial.print("\n");
      

      
   if (Xasis > 515) {
    //LEFT
    digitalWrite(motor_1B, LOW);
    digitalWrite(motor_1A, HIGH);
    digitalWrite(motor_2B,LOW);
    digitalWrite(motor_2A,HIGH);
    //RIGHT
    digitalWrite(motor_3B,LOW);
    digitalWrite(motor_3A,HIGH);
    digitalWrite(motor_4B,LOW);
    digitalWrite(motor_4A,HIGH);
    
    
    
    speedLeft   = map(Xasis, 515, 1023, 0, 255);
    speedRight   = map(Xasis, 515, 1023, 0, 255);
    
    a=motor_1A;
    b=motor_2A;
    c=motor_3A;
    d=motor_4A;
  }
  
  if (Xasis < 480) {
    //antras=true;
    digitalWrite(motor_1B, HIGH);
    digitalWrite(motor_1A, LOW);
    digitalWrite(motor_2B, HIGH);
    digitalWrite(motor_2A, LOW);
    //RIGHT
    digitalWrite(motor_3B,HIGH);
    digitalWrite(motor_3A,LOW);
    digitalWrite(motor_4B,HIGH);
    digitalWrite(motor_4A,LOW);
    speedLeft   = map(Xasis, 480, 0, 0, 255);
    speedRight   = map(Xasis, 480, 0, 0, 255);
    a=motor_1B;
    b=motor_2B;
    c=motor_3B;
    d=motor_4B;
  }
   if  (Xasis>480 && Xasis<530){
    speedLeft   = 0;
    speedRight=0;
  }
  if (Yasis < 470) {
    // Convert the declining X-axis readings from 470 to 0 into increasing 0 to 255 value
    int xMapped = map(Yasis, 470, 0, 0, 255);
    // Move to left - decrease left motor speed, increase right motor speed
    speedLeft = speedLeft - xMapped;
    speedRight = speedRight + xMapped;
    // Confine the range from 0 to 255
    if (speedLeft < 0) {
      speedLeft = 0;
    }
    if (speedRight > 255) {
      speedRight = 255;
    }
  }
  if (Yasis > 550) {
    // Convert the increasing X-axis readings from 550 to 1023 into 0 to 255 value
    int xMapped = map(Yasis, 550, 1023, 0, 255);
    // Move right - decrease right motor speed, increase left motor speed
    speedLeft = speedLeft + xMapped;
    speedRight = speedRight - xMapped;
    // Confine the range from 0 to 255
    if (speedLeft > 255) {
      speedLeft = 255;
    }
    if (speedRight < 0) {
      speedRight = 0;
    }
  }

  //if (Xasis < 70) {
    //speedLeft = 0;
    //Serial.print("\n");
   //Serial.print(speedLeft);
  
  Serial.print(speedLeft);
  Serial.print("\n");
  }
  analogWrite(a, speedLeft);
  analogWrite(b, speedLeft);
  analogWrite(c,speedRight);
  analogWrite(d,speedRight);
  
  
  
}
    
