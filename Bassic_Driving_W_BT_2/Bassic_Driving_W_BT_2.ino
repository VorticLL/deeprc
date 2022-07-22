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
  if ( Serial.available()){     //Checks the availability of Serial port
    data = Serial.read();      // Read the data and stores it in variable
    if(data == '#'){  
      EnterCommand(Command);
      Command = "";
    }else{
      Command = Command + String(data);
    }
  }
}



void EnterCommand(String Command){
  float angle = float(Command.substring(0,3).toInt());      //firt get the abc numbers out of the command and then convert to integer.
  float power = float(Command.substring(3,6).toInt()*2.55); //firt get the def numbers out of the command and then convert to integer. Finally convert this 0-100 value into a 0-255 value.
  int button = float(Command.substring(6).toInt());       //firt get the g number out of the command and then convert to integer.
  int L_direction;
  int R_direction;
  float L_speed;
  float R_speed;
  
  // define direction for L motor
  if(angle<=180 ||angle>=330){
    L_direction = 1;
  }else{
    L_direction = 0;
  }

  // define direction for R motor
  if(angle<=200){
    R_direction = 1;
  }else{
    R_direction = 0;
  }

  // define L speed
  if(angle>=90 && angle<=270){
    L_speed = abs(((angle-90.0)/90.0)-1.0)*power; //MyMap(angle,90.0,270.0,1.0,0.0);
  }else if(angle<90){
    L_speed = (0.5+(angle/180.0))*power;
  }else{
    L_speed = abs(0.7 + (((angle-360.0)/90.0)*1.7))*power;
  }

  // define R speed
  if(angle<=90){
    R_speed = (angle/90.0)*power;
  }else if(angle>=270){
    R_speed = abs((angle-360)/90)*power;
  }else if(angle>90 && angle<180){
    R_speed = (1-((angle-90)/180))*power;
  }else{
    R_speed = abs(0.7 - (((angle-180.0)/90.0)*1.7))*power;
  }

  // Using sensors, check if driver input is correct. If not, change power and direction settings as needed to aid driver.
  // YOUR CODE GOES HERE:
//_____________________________________________________________________________________________________________________________________________________







  
  
//______________________________________________________________________________________________________________________________________________________
  // Now apply calculated power and direction settings to mototrs 
  // First set direction:
  if(L_direction>0){
    digitalWrite(DIR_L, HIGH);
  }else{
    digitalWrite(DIR_L, LOW);
  }

  if(R_direction>0){
    digitalWrite(DIR_R, HIGH);
  }else{
    digitalWrite(DIR_R, LOW);
  }
  
  // Next set speed:
  analogWrite(PWM_L, L_speed);
  analogWrite(PWM_R, R_speed);
}
