#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define TRIG_PIN 9
#define ECHO_PIN 10

Servo myServo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int on = 0;
const int off = 90;

int distance = 0;
int open_distance = 10;
int cup_time = 3000;

int water_ml = 5000;
const int dispense_amount = 200;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  myServo.attach(6);

  lcd.init();
  lcd.backlight();

  lcd.print("Insert cup");
}

void loop() {
  distance = getDistance();

  if(distance <= open_distance && distance > 0){
    Serial.println("Cup Detected!");
    myServo.write(on);

    water_ml -= dispense_amount;
    if(water_ml < 0) water_ml = 0;

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Filling cup");
    lcd.setCursor(0,1);
    lcd.print(water_ml);
    lcd.print(" ml left");

    delay(cup_time);
    myServo.write(off);
    delay(3000);
  }
  else {
    lcd.clear();
    if(water_ml > 0){
      lcd.print("Insert cup");
    }
    else {
      lcd.print("Out of water!");
    }
  }

  myServo.write(off);
}

int getDistance(){
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(100);

  return distance;
}
