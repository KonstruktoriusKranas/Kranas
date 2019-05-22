#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00002";
const int SW_pin = 4; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 4; // analog pin connected to Y output
const int X_pin2 = 7;
const int Y_pin2 = 2;
const int SW_pin2 = 5;

int joystick[4];
void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);
}
void loop() {
  //int Y=analogRead(Y_pin);
  //int X=analogRead(X_pin);
  joystick[0] = analogRead(Y_pin);
  joystick[1] = analogRead(X_pin);
  joystick[2]=analogRead(Y_pin2);
  joystick[3]=analogRead(X_pin2);
  radio.write(joystick, sizeof(joystick));
  Serial.print("X:");
  Serial.print(analogRead(X_pin));
  Serial.print("\n");
  Serial.print("Y:");
  Serial.print(analogRead(Y_pin));
  Serial.print("\n");
  
  /*

  if(digitalRead(SW_pin)==0)
  {
  Serial.print("Mygtukas nuspaustas");
  Serial.print("\n");
  }
  else
  {
    Serial.print("Mygtukas nenuspaustas");
    Serial.print("\n");
  }
  if(Y_pin>510)
  {
  Serial.print("Į kairę");
  Serial.print("\n");
  }
  if(Y_pin<500)
  {
    Serial.print("Į dešinę");
    Serial.print("\n");
  }
  if(Y_pin>500&&Y_pin<510)
  {
    Serial.print("Tiesiai");
    Serial.print("\n");
  }
  if(X_pin>500)
  {
  Serial.print("Į priekį");
  Serial.print(X_pin);
  Serial.print("\n");
  }
  if(X_pin<493)
  {
    Serial.print("Atgal");
    Serial.print(X_pin);
    Serial.print("\n");
  }
  if(X_pin>493&&X_pin<500)
  {
    Serial.print("Stovėti");
    Serial.print(X_pin);
    Serial.print("\n");
  }
  */
  Serial.print("\n\n");
  delay(20);
}
