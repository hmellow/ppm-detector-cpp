#include <LiquidCrystal.h>

// ===== Main Variables =====
// -- LEDs --
int blueRangeLow = 1;
int blueRangeHigh = 10000;
int redRangeLow = 2;
int redRangeHigh = 10000;
int greenRangeLow = 3;
int greenRangeHigh = 10000;

// -- Wait --
int wait = 500;

// ===== Pin Setup =====
const int rs = 16, en = 17, d4 = 18, d5 = 19, d6 = 20, d7 = 21;
int inputPin = A2;
int greenLED = 12;
int redLED = 11;
int blueLED = 10;

// ===== Other Variable Setup =====
const float ArduinoVoltage = 3.3; // CHANGE THIS FOR 3.3v Arduinos
const float ArduinoResolution = ArduinoVoltage / 1024;
const float resistorValue = 10000.0;

// ===== Pre Setup =====
 LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// ===== Setup =====
void setup()
{
 Serial.begin(9600);
 pinMode(inputPin, INPUT);
 lcd.begin(16,2);
}

// ===== Loop =====

void loop()
{
 int analogValue=0;
 float returnVoltage=0.0;
 float resistance=0.0;
 double Siemens;
 float TDS=0.0;
 float funcationatedTDS=0;

 digitalWrite( 4, HIGH);

 
 if (digitalRead( 5 ) != HIGH)
 {
   return;
 }

 // -- LCD --
 lcd.setCursor(0,0);
// lcd.clear();

 // -- Analog --
 analogValue = analogRead( inputPin );
// Serial.println(analogValue);

 // -- Voltage --
 returnVoltage = analogValue * ArduinoResolution;
// Serial.println(returnVoltage);

 funcationatedTDS = 10.1 * (pow(returnVoltage, 16.1));
 TDS = funcationatedTDS;
// Serial.println(funcationatedTDS);

/*
 // -- Resistance --
 resistance = ((5.00 * resistorValue) / returnVoltage) - resistorValue;
// Serial.println(resistance);

 // -- Siemens --
 Siemens = 1.0/(resistance/1000000);
// Serial.println(Siemens);

  // -- TDS --
 TDS = 500 * (Siemens/1000);
// Serial.print(TDS);
*/

 delay(wait);


 // -- LED Code --
 // Blue
 if (blueRangeLow < TDS && TDS < blueRangeHigh) 
 {
  digitalWrite( blueLED, HIGH);
 } else
 {
  digitalWrite( blueLED, LOW);
 }

 // Red
 if (redRangeLow < TDS && TDS < redRangeHigh) 
 {
  digitalWrite( redLED, HIGH);
 } else
 {
  digitalWrite( redLED, LOW);
 }

 // Green
 if (greenRangeLow < TDS && TDS < greenRangeHigh) 
 {
  digitalWrite( greenLED, HIGH);
 } else
 {
  digitalWrite( greenLED, LOW);
 }

  // -- LCD Update --
 lcd.print(returnVoltage);
 lcd.setCursor(0, 1);
 lcd.print(funcationatedTDS);
}
