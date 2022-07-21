/* Bluetooth Interfacing with Arduino
   Author: Electrofun
   Prerequisites video: https://www.youtube.com/watch?v=3Iha7kBGjHQ&ab_channel=Electrofun
   Video explanation at: https://www.youtube.com/watch?v=sY9rmyxqofM&ab_channel=Electrofun


   joystick values: abcdefg

   abc are from 0-360 and represent the angle in cartesian coordinates.
   def are from 0-100 and represent how far the stick is from the center position.
   g is the push button
*/
int DIR_L = 12;
int PWM_L = 3;
int BRAKE_L = 9;

int L_speed = 255;
int R_speed = 255;

int DIR_R = 13;
int PWM_R = 11;
int BRAKE_R = 8;
String Command;

char data;   //Variable to store the data

void setup() {
  Serial.begin(9600);           //Initializing the Serial Port to Baud rate 9600
  pinMode(DIR_L, OUTPUT);
  pinMode(PWM_L, OUTPUT);
  pinMode(BRAKE_L, OUTPUT);

  pinMode(DIR_R, OUTPUT);
  pinMode(PWM_R, OUTPUT);
  pinMode(BRAKE_R, OUTPUT);

}

void loop() {
  if (Serial.available()) {    //Checks the availability of Serial port
    Serial.println("hello");
    data = Serial.read();      // Read the data and stores it in variable
      switch(data){
        case'w':
        //Go forward at high speed
          digitalWrite(DIR_L, HIGH);
          digitalWrite(DIR_R, HIGH);
          analogWrite(PWM_L, L_speed);
          analogWrite(PWM_R, R_speed);
        case's':
        //Go backwards
          digitalWrite(DIR_L, LOW);
          digitalWrite(DIR_R, LOW);
        case'a':
        //Slow down
          analogWrite(PWM_L, 100);
          analogWrite(PWM_R, 100);
        case'b':
        //Stop
          analogWrite(PWM_L, 0);
          analogWrite(PWM_R, 0);
        default:
          analogWrite(PWM_L, 0);
          analogWrite(PWM_R, 0);
      }
    

  }
}
