#include <LiquidCrystal.h>

// ---------------------
const float blueThres = 30;
const float greenThres = 10;
const float redThres = 0;
// ---------------------

const int eleInput = 13;
const int eleOutput = 6;

const int redPin = 7;
const int greenPin = 8;
const int bluePin = 9;

const int buttonPin = 10;
int buttonState = 0;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup() {
  pinMode(eleInput, INPUT);
  pinMode(eleOutput, OUTPUT);
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);

  lcd.begin(16,2);
}

void loop() {
buttonState = digitalRead(buttonPin);

if (buttonState == HIGH) {
  reset();
  
  // Initial analog reading
  digitalWrite(eleOutput, HIGH);
  delay(10);
  float analog = analogRead(eleInput);
  digitalWrite(eleOutput, LOW);

  // Volts
  float volts = analog * (5/1024);
  // Resistance (Ohms)
  float resistance = (50000/volts) - 10000;
  // Conductivity (microSiemens)
  float siemens = 1 / (resistance/1000000);
  // TDS (ppm)
  float TDS = 500 * (siemens/1000);

  // LCD results
  float roundedVoltage = round(volts * 10000) / 10000;
  float roundedTDS = round(TDS * 10000) / 10000;
  lcd.print("vts: " + String(roundedVoltage));
  lcd.setCursor(0, 2);
  lcd.print("ppm: " + String(roundedTDS));

  // LED concentration indication
  if (TDS >= blueThres) {
    digitalWrite(bluePin, HIGH);
   } else if (TDS > = greenThres) {
     digitalWrite(greenPin, HIGH);
   } else {
     digitalWrite(redPin, HIGH); 
   }
  delay(500);
  }
}

void reset() {
  lcd.clear();
  
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
 }
