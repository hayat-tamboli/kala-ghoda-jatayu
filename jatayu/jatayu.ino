// // // For single motor instance
#include <L298N.h>

// motor & L298N pins

int m1Pin1 = 50;       // Connect to IN1 on the motor driver
int m1Pin2 = 48;       // Connect to IN2 on the motor driver
int m1enablePin = 52;  // Connect to ENA on the motor driver

// int m2Pin1 = 3;  // Connect to IN3 on the motor driver
// int m2Pin2 = 4;  // Connect to IN4 on the motor driver
// int m2enablePin = 2;  // Connect to ENB on the motor driver

// ultrasonic sensor pins

const int u1trigPin = 22;
const int u1echoPin = 23;
const int u2trigPin = 24;
const int u2echoPin = 25;
const int u3trigPin = 26;
const int u3echoPin = 27;
const int u4trigPin = 28;
const int u4echoPin = 29;
const int u5trigPin = 30;
const int u5echoPin = 31;

L298N motor1(m1enablePin, m1Pin1, m1Pin2);
// L298N motor2(m2enablePin, m2Pin1, m2Pin2);

// used for full drop and full pull
bool direction = 0;  // 0 = blocks are up , 1 = blocks are down now
long timeToPickUp = 5000;
long timeToDropDown = 5000;

void setup() {

  Serial.begin(9600);

  // connections to ultrasonic sensors
  pinMode(u1trigPin, OUTPUT);
  pinMode(u1echoPin, INPUT);
  pinMode(u2trigPin, OUTPUT);
  pinMode(u2echoPin, INPUT);
  pinMode(u3trigPin, OUTPUT);
  pinMode(u3echoPin, INPUT);
  pinMode(u4trigPin, OUTPUT);
  pinMode(u4echoPin, INPUT);
  pinMode(u5trigPin, OUTPUT);
  pinMode(u5echoPin, INPUT);


  // connections to motor
  pinMode(m1Pin1, OUTPUT);
  pinMode(m1Pin2, OUTPUT);
  pinMode(m1enablePin, OUTPUT);
  //   // pinMode(m2Pin1, OUTPUT);
  //   // pinMode(m2Pin2, OUTPUT);
  //   // pinMode(m2enablePin, OUTPUT);
  // Set initial speed
  motor1.setSpeed(100);
  //   // motor2.setSpeed(100);

  motor1.stop();
  //   // motor2.stop();
}

void loop() {

  if (direction == 0) {
    if (isPersonBlocking()) {
      dropBlocks();
    }
  }
  if (direction == 1) {
    if (!isPersonBlocking())
    {
      Serial.println("waiting for 10 secs");
      delay(10000);
      pullBlocks();
    }
  }
}

void dropBlocks() {
  Serial.println("Throwing the blocks down");
  motor1.backward();
  delay(timeToPickUp);
  motor1.stop();
  direction = 1;
}
void pullBlocks() {
  Serial.println("picking up the blocks");
  motor1.forward();
  delay(timeToDropDown);
  motor1.stop();
  direction = 0;
}

int getU1Distance()
{
  digitalWrite(u1trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(u1trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(u1trigPin, LOW);

  long duration = pulseIn(u1echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  Serial.print("Distance 1 🎉 : ");
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
}

int getU2Distance()
{
  digitalWrite(u2trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(u2trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(u2trigPin, LOW);

  long duration = pulseIn(u2echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  Serial.print("Distance 2 🥲: ");
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
}

int getU3Distance()
{
  digitalWrite(u3trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(u3trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(u3trigPin, LOW);

  long duration = pulseIn(u3echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  Serial.print("Distance 3 🪨: ");
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
}
int getU4Distance()
{
  digitalWrite(u4trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(u4trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(u4trigPin, LOW);

  long duration = pulseIn(u4echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  Serial.print("Distance 3 🪨: ");
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
}
int getU5Distance()
{
  digitalWrite(u5trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(u5trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(u5trigPin, LOW);

  long duration = pulseIn(u5echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  Serial.print("Distance 3 🪨: ");
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
}

bool isPersonBlocking()
{
  int dist1 = getU1Distance();
  int dist2 = getU2Distance();
  int dist3 = getU3Distance();
  int dist4 = getU4Distance();
  int dist5 = getU5Distance();
  if(dist1<100)
  {
    return true;
  }
  if(dist2<100)
  {
    return true;
  }
  if(dist3<100)
  {
    return true;
  }
  if(dist4<100)
  {
    return true;
  }
  if(dist5<100)
  {
    return true;
  }
  return false;
}
