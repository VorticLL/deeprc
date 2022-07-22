// figure what direction the servo spins
// the pin ports of both ultrasonics and the servo
// color sensing code
// check directions of motors

#include <Servo.h>
int DIR_L = 12;
int PWM_L = 3;
int BRAKE_L = 9;

int DIR_R = 13;
int PWM_R = 11;
int BRAKE_R = 8;
String Command;
Servo servo;

//TO-DO: change pin numbers
int echoPinR = 2;
int trigPinR = 3;
int echoPinL = 4;
int trigPinL = 5;

int distanceL, distanceR;
long durationL, durationR;


char data;   //Variable to store the data

void setup() {
  Serial.begin(9600);           //Initializing the Serial Port to Baud rate 9600
  pinMode(DIR_L, OUTPUT);
  pinMode(PWM_L, OUTPUT);
  pinMode(BRAKE_L, OUTPUT);

  pinMode(DIR_R, OUTPUT);
  pinMode(PWM_R, OUTPUT);
  pinMode(BRAKE_R, OUTPUT);


  servo.attach(9); //TO-DO: change port number


  pinMode(trigPinR, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPinR, INPUT); // Sets the echoPin as an INPUT
  pinMode(trigPinL, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPinL, INPUT); // Sets the echoPin as an INPUT
}

void loop() {
  if ( Serial.available()) {    //Checks the availability of Serial port
    data = Serial.read();      // Read the data and stores it in variable
    if (data == '#') {
      EnterCommand(Command);
      Command = "";
    } else {
      Command = Command + String(data);
    }
  }
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

void EnterCommand(String Command) {
  float angle = float(Command.substring(0, 3).toInt());     //firt get the abc numbers out of the command and then convert to integer.
  float power = float(Command.substring(3, 6).toInt() * 2.55); //firt get the def numbers out of the command and then convert to integer. Finally convert this 0-100 value into a 0-255 value.
  int button = float(Command.substring(6).toInt());       //firt get the g number out of the command and then convert to integer.
  int L_direction;
  int R_direction;
  float L_speed;
  float R_speed;



  // define direction for L motor
  if (angle <= 180 || angle >= 330) {
    L_direction = 1;
  } else {
    L_direction = 0;
  }

  // define direction for R motor
  if (angle <= 200) {
    R_direction = 1;
  } else {
    R_direction = 0;
  }

  // define L speed
  if (angle >= 90 && angle <= 270) {
    L_speed = abs(((angle - 90.0) / 90.0) - 1.0) * power; //MyMap(angle,90.0,270.0,1.0,0.0);
  } else if (angle < 90) {
    L_speed = (0.5 + (angle / 180.0)) * power;
  } else {
    L_speed = abs(0.7 + (((angle - 360.0) / 90.0) * 1.7)) * power;
  }

  // define R speed
  if (angle <= 90) {
    R_speed = (angle / 90.0) * power;
  } else if (angle >= 270) {
    R_speed = abs((angle - 360) / 90) * power;
  } else if (angle > 90 && angle < 180) {
    R_speed = (1 - ((angle - 90) / 180)) * power;
  } else {
    R_speed = abs(0.7 - (((angle - 180.0) / 90.0) * 1.7)) * power;
  }
  if (L_direction > 0) {
    digitalWrite(DIR_L, HIGH);
  } else {
    digitalWrite(DIR_L, LOW);
  }

  if (R_direction > 0) {
    digitalWrite(DIR_R, HIGH);
  } else {
    digitalWrite(DIR_R, LOW);
  }

  if (button == 3) {
    autoMode(angle);
  }

  // Next set speed:
  servo.write(servoAngle(angle));
  analogWrite(PWM_L, L_speed);
  analogWrite(PWM_R, R_speed);
}

float servoAngle(float angle) {
  if (angle < 180.0) {
    return angle;
  }
  else return 180.0 - angle;
}

void autoMode(float angle) {
  while(true) {
    if (distL() < 10 && distR() < 10) {
      digitalWrite(DIR_L, HIGH);
      digitalWrite(DIR_R, HIGH);
      angle = 90.0;
    }
    else if (distL() < 10 && distR() > 10) {
      Serial.println("turn left");
      digitalWrite(DIR_L, LOW);
      digitalWrite(DIR_R, HIGH);
      angle = 180.0;
    }
    else if (distL() > 10 && distR() < 10) {
      Serial.println("turn right");
      digitalWrite(DIR_L, HIGH);
      digitalWrite(DIR_R, LOW);
      angle = 0.0;
    }
    else Serial.println("???");


    servo.write(servoAngle(angle));
    analogWrite(PWM_L, 100);
    analogWrite(PWM_R, 100);
    delay(100);
  }
}
