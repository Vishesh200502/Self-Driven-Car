#include <SoftwareSerial.h>
#include <AFMotor.h>
#include <Servo.h>
#include <NewPing.h>

#define trigPin A0
#define echoPin A1

#define Max_Distance 200

NewPing sonar(trigPin, echoPin, Max_Distance);

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

SoftwareSerial BT_Serial(9,10);

Servo myServo; 

boolean goesForward = false;
int distance = 100;

char bt_data;

int mode = 0;

int Speed = 255;

void setup() 
{
  myServo.attach(10);
  myServo.write(90);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  Serial.begin(9600);
  BT_Serial.begin(9600);
}

void loop() 
{
  if(BT_Serial.available() > 0)
  {
    bt_data = BT_Serial.read(); 
    Serial.println(bt_data);
  }
  
  if(bt_data == '8')
  {
    mode = 1; 
  }
  
  else if(bt_data == '9')
  {
    mode = 0;
  }  
  
  if(mode == 0)
  {
    if(bt_data == '1')
    {
      moveForward(); 
    }
    else if(bt_data == '2')
    {
      moveBackward();
    }
    else if(bt_data == '3')
    {
      turnLeft();
    }
    else if(bt_data == '4')
    {
      turnRight();
    }
    else if(bt_data == '5')
    {
      moveStop(); 
    }   
    else if(bt_data == '6')
    {
      turnLeft();
      bt_data = '5';
    }
    else if(bt_data == '7')
    {
      turnRight(); 
      bt_data = '5';
    }
  }

void moveStop() 
{
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
} 

void moveForward()
{
  if(!goesForward)
  {
    goesForward = true;
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
    motor1.setSpeed(255);
    motor2.setSpeed(255);
    motor3.setSpeed(255);
    motor4.setSpeed(255);
  }
}

void moveBackward() 
{
  goesForward = false;
  motor1.run(BACKWARD);      
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);  
  motor1.setSpeed(255);
  motor2.setSpeed(255);
  motor3.setSpeed(255);
  motor4.setSpeed(255);
} 

void turnRight() 
{
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);     
  delay(500);
  motor1.run(FORWARD);      
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);      
} 

void turnLeft() 
{
  motor1.run(BACKWARD);     
  motor2.run(BACKWARD);  
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);   
  delay(500);
  motor1.run(FORWARD);     
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}
