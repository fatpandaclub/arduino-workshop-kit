
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

// Vibration module
const int vibrationPin = O0;

// Accelerometer module
const int accelerometerXpin = I0;
const int accelerometerYpin = I1;

// LED modules
const int ledPin1 = O1;
const int ledPin2 = O2;

// FUNCTION PROTOTYPES (ignore this)
int readUltrasonicSensor();
void vibrate(int duration);
int readAccelerometerXposition();
int readAccelerometerYposition();
void turnOnLED(int led, int duration);

void setup() {
  
  // Start the serial communication
  Serial.begin(9600); 
  
  // SET PINMODES
  // Ultrasonic sensor
  pinMode(usTrigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(usEchoPin, INPUT); // Sets the echoPin as an Input

  // Vibration module
  pinMode(vibrationPin, OUTPUT);

  // Accelerometer module
  pinMode(accelerometerXpin, INPUT);
  pinMode(accelerometerYpin, INPUT);

  // LED modules
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);

}

void loop() {
  turnOnLED(2, 2000);
  delay(500);
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
