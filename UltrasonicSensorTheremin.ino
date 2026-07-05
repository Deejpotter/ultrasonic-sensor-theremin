#include <Arduino.h>

// Sensor 1 (Volume Control) Pins
const int trigPinVolume = 5;  // GPIO5 connected to Trig of Volume Control Sensor
const int echoPinVolume = 19; // GPIO19 connected to Echo of Volume Control Sensor

// Sensor 2 (Pitch Control) Pins
const int trigPinPitch = 27; // GPIO27 connected to Trig of Pitch Control Sensor
const int echoPinPitch = 14; // GPIO14 connected to Echo of Pitch Control Sensor

// KY-006 Passive Buzzer Pin
const int buzzerPin = 17; // Connect the Buzzer to GPIO17

long durationVolume, durationPitch;
int distanceVolume, distancePitch;
int volumeThreshold = 10; // Distance threshold in cm for volume control

void setup()
{
    pinMode(trigPinVolume, OUTPUT); // Set the Trig pin of Volume Sensor as OUTPUT
    pinMode(echoPinVolume, INPUT);  // Set the Echo pin of Volume Sensor as INPUT
    pinMode(trigPinPitch, OUTPUT);  // Set the Trig pin of Pitch Sensor as OUTPUT
    pinMode(echoPinPitch, INPUT);   // Set the Echo pin of Pitch Sensor as INPUT
    pinMode(buzzerPin, OUTPUT);     // Set the Buzzer pin as OUTPUT for sound generation
    Serial.begin(9600);             // Start serial communication for debugging
}

void loop()
{
    // Measuring Distance from Volume Control Sensor
    digitalWrite(trigPinVolume, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinVolume, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinVolume, LOW);
    durationVolume = pulseIn(echoPinVolume, HIGH);
    distanceVolume = durationVolume * 0.034 / 2; // Calculate distance in cm

    // Measuring Distance from Pitch Control Sensor
    digitalWrite(trigPinPitch, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinPitch, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinPitch, LOW);
    durationPitch = pulseIn(echoPinPitch, HIGH);
    distancePitch = durationPitch * 0.034 / 2; // Calculate distance in cm

    // Mapping Distance to Buzzer Frequency for Pitch
    int frequency = map(distancePitch, 0, 30, 100, 2000); // Map distance to frequency range

    // Volume Control: Sound On/Off based on distance threshold
    if (distanceVolume < volumeThreshold)
    {
        tone(buzzerPin, frequency); // Play tone with calculated frequency
    }
    else
    {
        noTone(buzzerPin); // Turn off sound if above volume threshold
    }

    // Debugging Output to Serial Monitor
    Serial.print("Volume Distance: ");
    Serial.print(distanceVolume);
    Serial.print(" cm, Pitch Distance: ");
    Serial.print(distancePitch);
    Serial.println(" cm");

    delay(100); // Short delay before next loop iteration
}
