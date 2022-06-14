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
int turningSpeed = 1000;
//int turningBot = 100;

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
void setSpeed(){
  rightMotor.setSpeed(drivingSpeed);
  leftMotor.setSpeed(drivingSpeed);
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
    setSpeed();
    forward();
    //FORWARD WITH A RIGHT TURN
    if(right){
      rightMotor.setSpeed(turningSpeed);
    }
    //FORWARD WITH A LEFT TURN
    else if(left){
      leftMotor.setSpeed(turningSpeed);
    }
  }
  //REVERSE
  else if(back && !go){
    setSpeed();
    rightMotor.run(FORWARD);
    leftMotor.run(BACKWARD);
    Serial.println("REVERSE");
    //REVERSE WITH RIGHTTURN
    if(right){
      rightMotor.setSpeed(turningSpeed);
    }
    //REVERSE WITH LEFTTURN
    else if(left){
      leftMotor.setSpeed(turningSpeed);
    }
  }

 //RIGHTTURN
  else if(right && !go && !back){
    setSpeed();
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
    setSpeed();
    if(!right){
      leftMotor.run(RELEASE);
      rightMotor.run(BACKWARD);
      Serial.println("LEFTTURN");
    }
  
  //IF YOU PRESS BOTH LEFT AND RIGHT
    else{
      setSpeed();
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
