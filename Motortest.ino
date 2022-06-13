//Motorshield
#include <AFMotor.h> 

//Motors 
AF_DCMotor rightMotor(3); 
AF_DCMotor leftMotor(4);

//INPUT PINS
int drive = A3;
int reverse = A5;
int leftTurn = 2;
int rightTurn = 13;

//BOOLS
int go = 0;
int back = 0;
int left = 0;
int right = 0;


//SPEEDS
int drivingSpeed = 1000;
int turningTop = 1500;
int turningBot = 500;

void setup() {
  Serial.begin(9600); // set up Serial library at 9600 bps
  Serial.println("Dual motor test! Both ways!");
  
  //SET PINS 
  pinMode(drive,INPUT);
  pinMode(reverse, INPUT);
  pinMode(leftTurn, INPUT);
  pinMode(rightTurn, INPUT);
  
  //TURN ON MOTORS
  rightMotor.setSpeed(drivingSpeed);
  leftMotor.setSpeed(drivingSpeed);
  rightMotor.run(RELEASE);
  leftMotor.run(RELEASE);
}

//DRIVE FORWARD FUNCRION
void forward(){
    rightMotor.run(BACKWARD);
    leftMotor.run(FORWARD);
    Serial.println("GO");
}

//RUNNING LOOP
void loop() {
  //UPDTAING THE BOOLS
  go = digitalRead(drive);
  back = digitalRead(reverse);
  left = digitalRead(leftTurn);
  right = digitalRead(rightTurn);


 //FORWARD DRIVE
  if(go && !back){
    forward();
    //FORWARD WITH A RIGHT TURN
    if(right){
      leftMotor.setSpeed(turningTop);
      rightMotor.setSpeed(turningBot);
    }
    //FORWARD WITH A LEFT TURN
    else if(left){
      leftMotor.setSpeed(turningBot);
      rightMotor.setSpeed(turningTop);
    }
  }
  //REVERSE
  else if(back && !go){
    rightMotor.run(FORWARD);
    leftMotor.run(BACKWARD);
    Serial.println("REVERSE");
    //REVERSE WITH RIGHTTURN
    if(right){
      leftMotor.setSpeed(turningTop);
      rightMotor.setSpeed(turningBot);
    }
    //REVERSE WITH LEFTTURN
    else if(left){
      leftMotor.setSpeed(turningBot);
      rightMotor.setSpeed(turningTop);
    }
  }

 //RIGHTTURN
  else if(right && !go && !back){
    if(!left){
      rightMotor.run(RELEASE);
      leftMotor.run(FORWARD);
      Serial.println("RIGHTTURN");
    }
    //IF YOU PRESS BOTH LEFT AND RIGHT
    else{
      forward();
    }
  }

  //LEFTTURN
  else if(left && !go && !back){
    if(!right){
      leftMotor.run(RELEASE);
      rightMotor.run(BACKWARD);
      Serial.println("LEFTTURN");
    }
  //IF YOU PRESS BOTH LEFT AN RIGHT
    else{
      forward();
    }
  }

  //IF YOU DON'T PRESS ANYTHNIG
  else{
    rightMotor.run(RELEASE);
    leftMotor.run(RELEASE);
    Serial.println("STOP");
 }
  delay(500);
}
