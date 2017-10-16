#include <Servo.h>

// TINKERKIT DEFINITIONS (ignore this)
#define I0 A0
#define I1 A1
#define I2 A2
#define I3 A3
#define I4 A4
#define I5 A5

#define O0 11
#define O1 10
#define O2 9
#define O3 6
#define O4 5
#define O5 3

// SENSOR PINS
// Ultrasonic sensor
const int usTrigPin = 20;
const int usEchoPin = 21;

// Accelerometer module
const int accelerometerXpin = I0;
const int accelerometerYpin = I1;

// Microphone module
const int microphonePin = I2;

// Potentiometer module
const int potentiometerPin = I3;

// Vibration module
const int vibrationPin = O0;

// LED modules
const int ledPin1 = O1;
const int ledPin2 = O2;

// Servo modules
const int servoPin1 = O3;
const int servoPin2 = O4; 

Servo servo1;
Servo servo2;

// FUNCTION PROTOTYPES (ignore this)
int readUltrasonicSensor();
int readAccelerometerXposition();
int readAccelerometerYposition();
float readSoundLevel();
int readPotentiometer();

void vibrate(int duration);
void turnOnLED(int led, int duration);
void moveServo(Servo servo, int startPos, int endPos, int tempo);


void setup() {
  
  // Start the serial communication
  Serial.begin(9600); 
  
  // SET PINMODES (you can ignore this)
  // Ultrasonic sensor
  pinMode(usTrigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(usEchoPin, INPUT); // Sets the echoPin as an Input

  // Accelerometer module
  pinMode(accelerometerXpin, INPUT);
  pinMode(accelerometerYpin, INPUT);

  // Microphone module
  pinMode(microphonePin, INPUT);

  // Potentiometer module
  pinMode(potentiometerPin, INPUT);
  
  // Vibration module
  pinMode(vibrationPin, OUTPUT);

  // LED modules
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);

  // Servo modules
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);

}

void loop() {
  // WRITE YOUR CODE HERE :)
}

/*
 * Read the data from the ultrasonic sensor
 * 
 * @return int : The distance in cm.
 */
int readUltrasonicSensor() {

  long duration;
  int distance;
  
  // Clears the trigPin
  digitalWrite(usTrigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(usTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(usTrigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(usEchoPin, HIGH);
  // Calculating the distance
  distance = duration*0.034/2;

  return distance;
}

/*
 * Vibrates the vibration module
 * 
 * @param int duration : The time in milliseconds which the module should vibrate
 * @param int pause : The time in milliseconds which the module should pause after virbrating
 */
void vibrate(int duration, int pause) {
  digitalWrite(vibrationPin, HIGH);
  delay(duration);
  digitalWrite(vibrationPin, LOW);
  delay(pause);
}

/*
 * Reads the X axis of the accelerometer and maps it to a value between 0-100
 * 
 * @return int : The X axis (between 0-100)
 */
int readAccelerometerXposition() {
  int xPos = analogRead(accelerometerXpin);
  xPos = map(xPos, 380, 600, 0, 100);
  return xPos;
}

/*
 * Reads the Y axis of the accelerometer and maps it to a value between 0-100
 * 
 * @return int : The Y axis (between 0-100)
 */
int readAccelerometerYposition() {
  int yPos = analogRead(accelerometerYpin);
  yPos = map(yPos, 380, 600, 0, 100);
  return yPos;
}

/*
 * Turns on a LED
 * 
 * @param int led : The number of the LED to turn on (1 or 2)
 * @param int duration : The time in milliseconds which the LED should stay turned on
 */
void turnOnLED(int led, int duration) {

  int ledPin = led == 1 ? ledPin1 : ledPin2;
  
  digitalWrite(ledPin, HIGH);
  delay(duration);
  digitalWrite(ledPin, LOW);
}

/*
 * Reads the potentiometer position and maps it to a value between 0-100
 * 
 * @return int : The potentiometer value (between 0-100)
 */
int readPotentiometer() {
  int potentiometerPos = analogRead(potentiometerPin);
  potentiometerPos = map(potentiometerPos, 5, 910, 0, 100);
  return potentiometerPos;
}


/*
 *  Move a servo motor
 *  
 *  @param Servo servoToMove : The servo to move
 *  @param int startPos : The position the servo will start moving from
 *  @param int endPos : The position the servo will end in
 *  @param int wait : The wait time in milliseconds between the movement
 */
void moveServo(Servo servoToMove, int startPos, int endPos, int wait) {

  if(startPos < endPos) {
    for (int pos = startPos; pos <= endPos; pos++) { // goes from 0 degrees to 180 degrees
      servoToMove.write(pos);              // tell servo to go to position in variable 'pos'
      delay(wait);                       // waits 15ms for the servo to reach the position
    }
  } else {
    for (int pos = startPos; pos >= endPos; pos--) { // goes from 0 degrees to 180 degrees
      servoToMove.write(pos);              // tell servo to go to position in variable 'pos'
      delay(wait);                       // waits 15ms for the servo to reach the position
    }
  }
}

/*
 * Reads the microphone for 250ms and converts the reading to a usable level
 * 
 * @return float : The current soundlevel
 */
float readSoundLevel() {
  const int sampleWindow = 250; // Sample window width in mS (250 mS = 4Hz)
  unsigned int knock;
  
  unsigned long start = millis();  // Start of sample window
  unsigned int peakToPeak = 0;   // peak-to-peak level

  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  while (millis() - start < sampleWindow) {
    knock = analogRead(microphonePin);
    if (knock < 1024) {
      if (knock > signalMax) {
        signalMax = knock;  // save just the max levels
      } else if (knock < signalMin) {
        signalMin = knock;  // save just the min levels
      }
    }
  }
  peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
  float volts = (peakToPeak * 3.3) / 1024;  // convert to volts

  return volts;
}

