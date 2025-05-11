#include <Servo.h>

#define TRIG_PIN 9
#define ECHO_PIN 10

Servo myServo;  // Create servo object

const int on = 0;
const int off = 90;

int distance = 0;
int open_distance = 10;

int cup_time = 3000; // open for 3 seconds

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);   // Set trig as output
  pinMode(ECHO_PIN, INPUT);    // Set echo as input
  myServo.attach(6);  // Attach to digital pin 6
}

void loop() {
  distance = getDistance();

  if(distance <= open_distance && distance > 0){
    Serial.println("Cup Detected!");
    myServo.write(on);
    delay(cup_time);
    myServo.write(off);
    delay(3000); // will not open after 3 sec para avoid spill
  }  

  myServo.write(off); // for safety para always off

}


int getDistance(){
// Send Sound wave for 10us
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW); // Dont send sound waves
  delayMicroseconds(10); 

  long duration = pulseIn(ECHO_PIN, HIGH); //measures the time how long the sound wave last
  // sound wave hit the wall, then go back to sensor therefore the duration = distance * 2

  //convert duration(us) to cm
  distance = duration * 0.034/2;

  // Print distance to Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(100);

  return distance;
}







// // Test code for servo motor

// #include <Servo.h>

// #define SERVO_PIN 6  // Pin connected to the servo

// Servo dispenserServo;

// void setup() {
//   Serial.begin(9600);
  
//   dispenserServo.attach(SERVO_PIN); // Attach the servo to the pin
// }

// void loop() {
//   // Move the servo to 0° position
//   dispenserServo.write(0);
//   Serial.println("Servo moving to 0°");
//   delay(1000);  // Wait for 1 second

//   // Move the servo to 90° position
//   dispenserServo.write(90);
//   Serial.println("Servo moving to 90°");
//   delay(1000);  // Wait for 1 second
// }


