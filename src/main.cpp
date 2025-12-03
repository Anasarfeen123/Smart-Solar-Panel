//=======================Real Field=================================
// #include <Wire.h>
// #include <RTClib.h>
// #include <Servo.h>

// RTC_DS3231 rtc;
// Servo servoMotor;

// const int servoPin = 9;   // plug servo signal pin here
// const int sunriseHour = 6;
// const int sunsetHour = 18;

// void moveToAngle(int angle) {
//   // servo only accepts 0–180
//   angle = constrain(angle, 0, 180);
//   servoMotor.write(angle);
//   delay(500); // tiny delay to allow physical movement
// }

// void setup() {
//   Serial.begin(9600);
//   Wire.begin();

//   if (!rtc.begin()) {
//     Serial.println("Couldn't find RTC");
//     while (1);
//   }

//   // rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // run once then comment out

//   servoMotor.attach(servoPin);

//   Serial.println("Servo-Based Solar Tracker Initialized!");
// }

// void loop() {
//   DateTime now = rtc.now();
//   int currentHour = now.hour();
//   int currentMinute = now.minute();

//   if (currentHour >= sunriseHour && currentHour <= sunsetHour) {
//     float totalMinutes = (currentHour - sunriseHour) * 60 + currentMinute;
//     float angle = map(totalMinutes, 0, (sunsetHour - sunriseHour) * 60, 0, 180);

//     moveToAngle(angle);

//     Serial.print("Time: ");
//     Serial.print(currentHour);
//     Serial.print(":");
//     Serial.print(currentMinute);
//     Serial.print(" → Angle: ");
//     Serial.println(angle);
//   } 
//   else {
//     moveToAngle(0);
//     Serial.println("Nighttime: Reset to 0°");
//   }

//   delay(600000); // 10 minutes
// }
//==========================DEMO====================================
#include <Arduino.h>
#include <Servo.h>

Servo servoMotor;
const int servoPin = 9;

// conceptual angles
int rawAngles[] = { -40, -20, 0, 20, 40, 60, 80 };
const int totalAngles = 7;

// map function (center at 90°)
int mapToServo(int rawAngle) {
  int servoAngle = 90 + rawAngle;
  return constrain(servoAngle, 0, 180);
}

void setup() {
  Serial.begin(9600);
  servoMotor.attach(servoPin);
  Serial.println("FAST DEMO: Solar Tracker (Mapped Angles)");
}

void loop() {
  for (int i = 0; i < totalAngles; i++) {
    int servoAngle = mapToServo(rawAngles[i]);

    servoMotor.write(servoAngle);

    Serial.print("Raw → ");
    Serial.print(rawAngles[i]);
    Serial.print("°,  Servo Output → ");
    Serial.println(servoAngle);

    delay(800);
  }

  delay(500);
}
