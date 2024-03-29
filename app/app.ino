
#include "NewPing.h"

#define TRIGGER_PIN  5  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     2  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 400 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define VIBRATION_MOTOR_PIN 8

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.

  pinMode(VIBRATION_MOTOR_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  //delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  int distanceCM = uS / US_ROUNDTRIP_CM;
  
  Serial.print("Ping: ");
  Serial.print(distanceCM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");

  int vibrationsDelay = 10;

  if (distanceCM > 350){
    vibrationsDelay = 1000;
  }
  else if(distanceCM > 250){
    vibrationsDelay = 500;
  }
  else if(distanceCM > 100){
    vibrationsDelay = 250;
  }
  else if(distanceCM > 50){
    vibrationsDelay = 100;
  }
  else if(distanceCM > 25){
    vibrationsDelay = 50;
  }
  else if(distanceCM > 10){
    vibrationsDelay = 25;
  }
  else{
    vibrationsDelay = 10;
  }
  
  vibrate(vibrationsDelay);  
}

void vibrate(int secs){
  digitalWrite(VIBRATION_MOTOR_PIN, HIGH);
  delay(secs);
  digitalWrite(VIBRATION_MOTOR_PIN, LOW);
  delay(secs);
}

