const int eleInput = A3;
const int eleOutput = A1;


void setup() {
  Serial.begin(9600);
  Serial.println(0);
  Serial.println(1024);
  
  pinMode(eleInput, INPUT);
  pinMode(eleOutput, OUTPUT);
}

void loop() {
  
  // Initial analog reading
  digitalWrite(eleOutput, HIGH);
  delay(10);
  float analog = analogRead(eleInput);
  digitalWrite(eleOutput, LOW);

  // Volts
  float volts = (analog * 5) / 1024;
  // Resistance (Ohms)
  float resistance = (50000/volts) - 10000;
  float siemens = 1 / (resistance/1000000);
  float TDS = 500 * (siemens/1000);
  
  Serial.println(analog);
  delay(500);
}
