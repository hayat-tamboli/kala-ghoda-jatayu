// // // For single motor instance
#include <L298N.h>

// motor & L298N pins

int m1Pin1 = 50;       // Connect to IN1 on the motor driver
int m1Pin2 = 48;       // Connect to IN2 on the motor driver
int m1enablePin = 52;  // Connect to ENA on the motor driver

// ultrasonic sensor pins

const int u1trigPin = 22;
const int u1echoPin = 23;
const int switchPin = 19; // used to switch from testing mode (debug mode) to main mode
const int pushButtonPin1 = 21;
const int pushButtonPin2 = 20;

L298N motor1(m1enablePin, m1Pin1, m1Pin2);

// used for full drop and full pull
bool direction = 0;  // 0 = blocks are up , 1 = blocks are down now
long timeToPickUp = 10 * 1000;
long timeToDropDown = 1 * 1000;
bool testMode = true;
int pushButtonPinState1 = 0;
int pushButtonPinState2 = 0;
int limitToDetect = 100;

void setup() {

  Serial.begin(9600);

  // connections to ultrasonic sensors
  pinMode(u1trigPin, OUTPUT);
  pinMode(u1echoPin, INPUT);
  pinMode(pushButtonPin1, INPUT_PULLUP);
  pinMode(pushButtonPin2, INPUT_PULLUP);
  pinMode(switchPin, INPUT);


  // connections to motor
  pinMode(m1Pin1, OUTPUT);
  pinMode(m1Pin2, OUTPUT);
  pinMode(m1enablePin, OUTPUT);
  // Set initial speed
  motor1.setSpeed(100);

  motor1.stop();
}

void loop() {
  testMode = digitalRead(switchPin);
  Serial.println(testMode);
  if (testMode) {
    testingLoop();
  } else {
    mainLoop();
  }
}

void testingLoop() {
  Serial.println("🌊🌊🌊");
checkpin1:
  pushButtonPinState1 = digitalRead(pushButtonPin1);
  if (pushButtonPinState1 == LOW) {
    Serial.println("🌈");
    motor1.forward();
    delay(400);
    goto checkpin1;
  } else {
    Serial.println("🔴");
    motor1.stop();
  }
checkpin2:
  pushButtonPinState2 = digitalRead(pushButtonPin2);
  if (pushButtonPinState2 == LOW) {
    Serial.println("🌈🌈");
    motor1.backward();
    goto checkpin2;
  } else {
    Serial.println("🔴🔴");
    motor1.stop();
  }
  delay(50);
}
void mainLoop() {
  Serial.println("✨✨✨");
  if (direction == 0) {
    if (isPersonBlocking()) {
      dropBlocks();
    }
  }
  if (direction == 1) {
    if (!isPersonBlocking()) {
      Serial.println("waiting for 10 secs");
      delay(10000);
      pullBlocks();
    }
  }
}

void dropBlocks() {
  Serial.println("Throwing the blocks down 🔽🔽🔽");
  motor1.forward();
  delay(timeToDropDown);
  motor1.stop();
  direction = 1;
}
void pullBlocks() {
  Serial.println("picking up the blocks ⬆️⬆️⬆️");
  motor1.backward();
  delay(timeToPickUp);
  motor1.stop();
  direction = 0;
}

int getU1Distance() {
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

bool isPersonBlocking() {
  int dist1 = getU1Distance();
  if (dist1 < limitToDetect) {
    Serial.println("stopped because of sensor 1");
    return true;
  }
  return false;
}
