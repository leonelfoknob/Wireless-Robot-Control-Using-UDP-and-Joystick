String inputString = "";   // A String to hold incoming data
bool stringComplete = false;  // Whether the string is complete

float axis0,axis1,axis2,axis3;
int hat0_0,hat0_1,button1, button2, button3,button4, button5, button6;
int button7,button8, button9, button10, button11, button12;

int Speed = 0;

//ledler 
int fenar_control = 23;

int red_back_left = 27;
int red_back_right = 29;

int withe_front_left = 31;
int withe_front_right = 33;
//motors
//right wheel
#define RPWM_1 4
#define LPWM_1 5
//left_wheel
#define RPWM_2 6
#define LPWM_2 7

//direction motor
#define RPWM_3 8
#define LPWM_3 9

//cultivator motor
#define RPWM_4 11
#define LPWM_4 10

#define pot A0

int cul_switch_up = 24;
int cul_switch_down = 22;
int cul_switch_up_val,cul_switch_down_val;

int pot_angle;
int turn_speed = 130;
int angle_toleranse = 5;
int center_angle = 94;
int max_turn_left_angle = 0;
int max_turn_right_angle = 143;

int cultivator_speed = 80;

int desired_angle;

int blink_led = 13;

int linear_vel_motor= 65;
int cultivator_motor_speed = 100;



void setup(){
  Serial.begin(9600);
  //ledler
 pinMode(fenar_control,OUTPUT);
 pinMode(red_back_left,OUTPUT);
 pinMode(red_back_right,OUTPUT);
 pinMode(withe_front_left,OUTPUT);
 pinMode(withe_front_right,OUTPUT);

  // Set motor connections as outputs
  pinMode(RPWM_1, OUTPUT);
  pinMode(LPWM_1, OUTPUT);
  pinMode(RPWM_2, OUTPUT);
  pinMode(LPWM_2, OUTPUT);
  pinMode(RPWM_3, OUTPUT);
  pinMode(LPWM_3, OUTPUT);
  pinMode(RPWM_4, OUTPUT);
  pinMode(LPWM_4, OUTPUT);

  //culivator_switch
  pinMode(cul_switch_up,INPUT_PULLUP);
  pinMode(cul_switch_down,INPUT_PULLUP);

  // Stop motors
  stoppe();
  stoppe_cul();
  stoppedirmot();
  direction_motor_calibration();
  delay(500);
  pinMode(blink_led,OUTPUT);

}

void loop() {
  //read_pot_angle();
read_pot_angle();
 // Process serial input when a full string has been received ************ joystick command **
  if (stringComplete) {
    inputString.trim();  // Remove any extra whitespace or newline
    
    processInput(inputString);
    //lcd_print_commad();
    control_with_command();
    
    inputString = "";  // Clear the string
    stringComplete = false;
  }
  
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

void processInput(String data) {
  // Split the data by commas
  String commands[18];
  int index = 0;
  int lastIndex = 0;
  for (int i = 0; i < data.length(); i++) {
    if (data[i] == ',') {
      commands[index++] = data.substring(lastIndex, i);
      lastIndex = i + 1;
    }
  }
  commands[index] = data.substring(lastIndex);

  // Use the received data and map it with joystick touch
  axis0 = commands[0].toFloat();
  axis1 = commands[1].toFloat();
  axis2 = commands[2].toFloat();
  axis3 = commands[3].toFloat();

  hat0_0 = commands[4].toInt(); 
  hat0_1 = commands[5].toInt();
  
  button1 = commands[6].toInt();
  button2 = commands[7].toInt();
  button3 = commands[8].toInt();
  button4 = commands[9].toInt();
  button5 = commands[10].toInt();
  button6 = commands[11].toInt();
  button7 = commands[12].toInt();
  button8 = commands[13].toInt();
  button9 = commands[14].toInt();
  button10 = commands[15].toInt();
  button11 = commands[16].toInt();
  button12 = commands[17].toInt();
}

//funtion that use command data to control led can be modify with another hardware like motor ...
void control_with_command(){
  int Speed = 100;
  if(axis1 < -0.5 ){ //ilere
    Forward(Speed);
    //Serial.print("komut : ");Serial.print("ilere"); 
  }
  else if(axis1 > 0.5){ //geri
    Back(Speed);
    //Serial.print("komut : ");Serial.print("geri");
  }
  else{
    stoppe();
    //Serial.print(" komut : ");Serial.print("dur");
  }
//------------------------------------------------------------direction
  if(axis3 > 0.5 ){ //right
    turn_desired_angle(max_turn_right_angle);
    Serial.println(" sag");
  }
  else if(axis3 < -0.5){ //left
    turn_desired_angle(max_turn_left_angle);
    Serial.println(" sol");
  }
  else if(axis3 < 0.5 && axis3 > -0.5){
    turn_desired_angle(center_angle);
    Serial.println(" duz");
  }
  //-------------------------------------------------------------cultivator
  if(hat0_1==1){
    cultivator_UP(cultivator_speed);
  }
  else if(hat0_1==-1){
    cultivator_Down(cultivator_speed);
  }
  else{
    stoppe_cul();
  }
}


void Forward(int Speed){
  //motor forward direction
  analogWrite(RPWM_1, LOW);
  analogWrite(LPWM_1, Speed);  
  digitalWrite(RPWM_2, LOW);
  analogWrite(LPWM_2, Speed);
   digitalWrite(red_back_left,0);
 digitalWrite(red_back_right,0);
 digitalWrite(withe_front_left,1);
 digitalWrite(withe_front_right,1);
 
}

void Back(int Speed){
  //motor back direction
  analogWrite(RPWM_1, Speed);
  analogWrite(LPWM_1, LOW);  
  analogWrite(RPWM_2, Speed);
  digitalWrite(LPWM_2, LOW);
    
}
void stoppe(){
  // Stop motors
analogWrite(RPWM_1, 0);
analogWrite(LPWM_1, 0);
analogWrite(RPWM_2, 0);
analogWrite(LPWM_2, 0);
 digitalWrite(red_back_left,1);
 digitalWrite(red_back_right,1);
  digitalWrite(withe_front_left,0);
 digitalWrite(withe_front_right,0);
}
//cultivator functions
void cultivator_UP(int Speed){
  //cultivator up function
  cul_switch_up_val = digitalRead(cul_switch_up);
  if(cul_switch_up_val == 0){
    analogWrite(RPWM_4, 0);
    analogWrite(LPWM_4, 0);
  }
  else{
    analogWrite(RPWM_4, LOW);
    analogWrite(LPWM_4, Speed);
  }
  //Serial.print("komut : ");Serial.println("çapalama yukarı hareket");   
}

void cultivator_Down(int Speed){
  //cultivator down function
  cul_switch_down_val  = digitalRead(cul_switch_down);
  if(cul_switch_down_val == 0){
    analogWrite(RPWM_4, 0);
    analogWrite(LPWM_4, 0);
  }
  else{
    analogWrite(RPWM_4, Speed);
    analogWrite(LPWM_4, LOW);
  }
  //Serial.print("komut : ");Serial.println("çapalama asağa hareket");   
}

void stoppe_cul(){
  // Stop motors
analogWrite(RPWM_4, 0);
analogWrite(LPWM_4, 0);
//Serial.print("komut : ");Serial.println("çapalama stop");
}

// direction motor

//turn left function
void Left(int Speed){
  analogWrite(RPWM_3, LOW);
  analogWrite(LPWM_3, Speed);
   digitalWrite(red_back_left,1);
 digitalWrite(red_back_right,10);
  digitalWrite(withe_front_left,1);
 digitalWrite(withe_front_right,0);
}

//turn right function
void Right(int Speed){
  analogWrite(RPWM_3, Speed);
  analogWrite(LPWM_3, LOW);
   digitalWrite(red_back_left,0);
 digitalWrite(red_back_right,1);
  digitalWrite(withe_front_left,0);
 digitalWrite(withe_front_right,1);
}

//direction motor stop function
void stoppedirmot(){
analogWrite(RPWM_3, 0);
analogWrite(LPWM_3, 0);
}
//read pot angle for debugging

void read_pot_angle(){
  int pot_val= analogRead(pot);
  pot_angle = map(pot_val,0,1024,0,180);
  //Serial.print("pot value : ");Serial.println(pot_val); 
  Serial.print("pot angle : ");Serial.println(pot_angle); 

}

//turn to desired angle

void turn_desired_angle(int desired_angle){
pot_angle = map(analogRead(pot),0,1024,0,180);

if(pot_angle > (desired_angle+ angle_toleranse)){
  Left(turn_speed);
}
else if(pot_angle < (desired_angle- angle_toleranse)){
  Right(turn_speed);
}
else{
  stoppedirmot();
}
}


//direction motor calibration

void direction_motor_calibration(){ 
pot_angle = map(analogRead(pot),0,1024,0,180);
do{
  pot_angle = map(analogRead(pot),0,1024,0,180);
  
if(pot_angle > (center_angle+angle_toleranse)){
  Left(turn_speed);
}
else if(pot_angle< (center_angle-angle_toleranse)){
  Right(turn_speed);
}
else{
  stoppedirmot();
  break;
}
}while(pot_angle < (center_angle-angle_toleranse) || pot_angle>(center_angle+angle_toleranse));
}

//ledler
void dortluk(){
 digitalWrite(red_back_left,0);
 digitalWrite(red_back_right,0);
 digitalWrite(withe_front_left,0);
 digitalWrite(withe_front_right,0);
 delay(100);
 digitalWrite(red_back_left,1);
 digitalWrite(red_back_right,1);
 digitalWrite(withe_front_left,1);
 digitalWrite(withe_front_right,1);
 delay(100);
 Serial.print("komut : ");Serial.println("dortluk");
}
