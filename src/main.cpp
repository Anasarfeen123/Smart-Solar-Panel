#include <Wire.h>
#include <RTClib.h>
#include <AccelStepper.h>

#define MOTOR_INTERFACE_TYPE 8
#define STEPS_PER_REV 2048

RTC_DS3231 rtc;
AccelStepper stepper(MOTOR_INTERFACE_TYPE, 8, 10, 9, 11);

const int sunriseHour = 6;
const int sunsetHour = 18;

void moveToAngle(float angle) {
  long targetStep = angle * STEPS_PER_REV / 360.0;
  stepper.moveTo(targetStep);
  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }
}

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  // Uncomment this once to set the RTC time:
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  stepper.setMaxSpeed(500);
  stepper.setAcceleration(200);

  Serial.println("Solar Tracker Initialized!");
}

void loop() {
  DateTime now = rtc.now();
  int currentHour = now.hour();
  int currentMinute = now.minute();

  if (currentHour >= sunriseHour && currentHour <= sunsetHour) {
    // Map time to angle (6 AM = 0°, 6 PM = 180°)
    float totalMinutes = (currentHour - sunriseHour) * 60 + currentMinute;
    float angle = map(totalMinutes, 0, (sunsetHour - sunriseHour) * 60, 0, 180);
    
    moveToAngle(angle);

    Serial.print("Time: ");
    Serial.print(currentHour);
    Serial.print(":");
    Serial.print(currentMinute);
    Serial.print(" → Angle: ");
    Serial.println(angle);
  } 
  else {
    // Night time: move back to 0° and chill
    moveToAngle(0);
    Serial.println("Nighttime: Reset to 0°");
  }

  delay(600000); // check every 10 minutes (300,000 ms)
}
