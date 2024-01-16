// For single motor instance
#include <L298N.h>

const int LEDpin = 13;
//const int motorPin = 5;
const int photoPIN1 = A0;
const int photoPIN2 = A1;
const int photoPIN3 = A2;
int motorPin1 = 5;  // Connect to IN1 on the motor driver
int motorPin2 = 6;  // Connect to IN2 on the motor driver
int enablePin = 4;  // Connect to ENA on the motor driver

L298N motor1(enablePin, motorPin1, motorPin2);
//L298N motor2(enablePin2, motorPin3, motorPin4);
bool direction = 0;  // 0 = up , 1 = down

void setup() {

  Serial.begin(9600);

  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);



  pinMode(photoPIN1, INPUT);
  pinMode(photoPIN2, INPUT);
  pinMode(photoPIN3, INPUT);
  // Set initial speed
  motor1.setSpeed(0);
  // motor1.stop();
  motor1.forward();


  // pinMode(motorPin, OUTPUT);
  pinMode(LEDpin, OUTPUT);
}
void loop() {
  motor1.forward();
  // reading the sensor:
  int sensorStatus1 = analogRead(photoPIN1);
  int sensorStatus2 = analogRead(photoPIN2);
  int sensorStatus3 = analogRead(photoPIN3);
  // status of the sensor is < 200

  // Serial.println(motor_speed);
  Serial.println(sensorStatus1);
  if (sensorStatus1 < 700) {
    Serial.print("yesssss");
    Serial.println("LED is ON, status of sensor is DARK");
    //motor1.setSpeed(255);
    motor1.backward();
    delay(1000);
  }
  // Serial.println(sensorStatus2);
  // Serial.println(sensorStatus3);
  //if (((sensorStatus1 <200) && (sensorStatus2 <200)) || ((sensorStatus1 <200) && (sensorStatus3 <200)) || ((sensorStatus2 <200) && (sensorStatus3 <200)) )
  // if ((sensorStatus1 <700))// || (sensorStatus2 <700)) || (sensorStatus3 <500))
  // //if (sensorStatus2 <1200)
  // {
  //   direction = 1;
  //   Serial.println("LED is ON, status of sensor is DARK");
  //   //motor1.setSpeed(255);
  //   motor1.backward();
  //   //printSomeInfo();
  //   digitalWrite(LEDpin, HIGH); // LED is ON
  //   delay(12000);

  //   motor1.stop();
  //   // delay(500);
  //   direction = 0;
  //   // motor1.backward();
  //   delay(10000);
  // }
  // else if (sensorStatus3 <200)
  // {
  //   Serial.println("LED is ON, status of sensor is DARK");
  //   motor1.backward();
  //   motor1.setSpeed(255);
  //   delay(1000);
  //   //motor2.backward();
  //   //delay(5000);
  //   //motor2.stop();
  //   //printSomeInfo();
  // }

  // else
  // {
  //   // digitalWrite(motorPin1, LOW);
  //  //digitalWrite(motorPin2, HIGH);
  //  if(direction == 0)
  //  {

  //  }
  //  motor1.forward();
  //   digitalWrite(LEDpin, LOW);
  //   Serial.println("*");
  //   //motor1.setSpeed(10);
  //   //printSomeInfo();
  //   // delay(1000);
  //   // motor1.stop();
  //   //motor2.stop();
  // }
  // analogWrite(enablePin, motor_speed);
}

// void printSomeInfo()
// {
//   delay(2000);
//   Serial.print("Motor is moving = ");
//   Serial.print(motor1.isMoving());
//   Serial.print(" at speed = ");
//  // Serial.println(motor1.getSpeed());
// }