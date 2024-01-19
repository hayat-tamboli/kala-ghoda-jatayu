// // // For single motor instance
#include <L298N.h>

// motor & L298N pins

int m1Pin1 = 50;       // Connect to IN1 on the motor driver
int m1Pin2 = 48;       // Connect to IN2 on the motor driver
int m1enablePin = 52;  // Connect to ENA on the motor driver

int m2Pin1 = 46;  // Connect to IN3 on the motor driver
int m2Pin2 = 44;  // Connect to IN4 on the motor driver
int m2enablePin = 42;  // Connect to ENB on the motor driver

// ultrasonic sensor pins

const int u1trigPin = 22;
const int u1echoPin = 23;
const int u2trigPin = 24;
const int u2echoPin = 25;
const int u3trigPin = 26;
const int u3echoPin = 27;

L298N motor1(m1enablePin, m1Pin1, m1Pin2);
L298N motor2(m2enablePin, m2Pin1, m2Pin2);

// used for full drop and full pull
bool direction = 0;  // 0 = blocks are up , 1 = blocks are down now
long timeToPickUp = 10000;
long timeToDropDown = 1000;

void setup() {

  Serial.begin(9600);

  // connections to ultrasonic sensors
  pinMode(u1trigPin, OUTPUT);
  pinMode(u1echoPin, INPUT);
  pinMode(u2trigPin, OUTPUT);
  pinMode(u2echoPin, INPUT);
  pinMode(u3trigPin, OUTPUT);
  pinMode(u3echoPin, INPUT);


  // connections to motor
  pinMode(m1Pin1, OUTPUT);
  pinMode(m1Pin2, OUTPUT);
  pinMode(m1enablePin, OUTPUT);
  pinMode(m2Pin1, OUTPUT);
  pinMode(m2Pin2, OUTPUT);
  pinMode(m2enablePin, OUTPUT);
  // Set initial speed
  motor1.setSpeed(100);
  motor2.setSpeed(100);

  motor1.stop();
  motor2.stop();
}

void loop() {
  testingLoop()
  // mainLoop();
}
void testingLoop()
{
  Serial.println("Testing loop 🌊🌊🌊");
  pullBlocks();
  delay(5000);
  dropBlocks();
}
void mainLoop()
{
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
  Serial.println("Throwing the blocks down 🔽🔽🔽");
  motor1.backward();
  // motor2.backward();
  delay(timeToDropDown);
  motor1.stop();
  // motor2.stop();
  direction = 1;
}
void pullBlocks() {
  Serial.println("picking up the blocks ⬆️⬆️⬆️");
  motor1.forward();
  // motor2.forward();
  delay(timeToPickUp);
  motor1.stop();
  // motor2.stop();
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

bool isPersonBlocking()
{
  int dist1 = getU1Distance();
  int dist2 = getU2Distance();
  int dist3 = getU3Distance();
  if(dist1<100)
  {
    Serial.println("stopped because of sensor 1");
    return true;
  }
  if(dist2<100)
  {
    Serial.println("stopped because of sensor 2");
    return true;
  }
  if(dist3<100)
  {
    Serial.println("stopped because of sensor 3");
    return true;
  }
  return false;
}
