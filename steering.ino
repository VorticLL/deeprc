// ---------------------------------------------------------------- //
// Arduino Ultrasoninc Sensor HC-SR04
// Re-writed by Arbi Abdul Jabbaar
// Using Arduino IDE 1.8.7
// Using HC-SR04 Module
// Tested on 17 September 2019
// ---------------------------------------------------------------- //

#define echoPinR 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPinR 3 //attach pin D3 Arduino to pin Trig of HC-SR04
#define echoPinL 4 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPinL 5 //attach pin D3 Arduino to pin Trig of HC-SR04

int distanceL, distanceR;
long durationL, durationR;

void setup() {
  pinMode(trigPinR, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPinR, INPUT); // Sets the echoPin as an INPUT
  pinMode(trigPinL, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPinL, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600);

}

int distL() {
  // Clears the trigPin condition
  digitalWrite(trigPinL, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPinL, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinL, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationL = pulseIn(echoPinL, HIGH);
  // Calculating the distance
  distanceL = durationL * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
//  Serial.print("Distance Left: ");
//  Serial.print(distanceL);
//  Serial.println(" cm");
  return distanceL;
}

int distR() {
  // Clears the trigPin condition
  digitalWrite(trigPinR, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPinR, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinR, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationR = pulseIn(echoPinR, HIGH);
  // Calculating the distance
  distanceR = durationR * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
//  Serial.print("Distance Right: ");
//  Serial.print(distanceR);
//  Serial.println(" cm");
  return distanceR;
}

void loop(){
  if(distL() < 10 && distR() < 10) Serial.println("go straight");
  else if(distL()< 10 && distR() > 10) Serial.println("turn left");
  else if(distL()> 10 && distR() < 10) Serial.println("turn right");
  else Serial.println("???");

  delay(100);
}
