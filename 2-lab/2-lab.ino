const int PIN_NTC = A0;
const int PIN_TEMP_OUT = 3;
const int PIN_OR_OUT = 4;

const int RED_PIN = 5;
const int GREEN_PIN = 6;
const int BLUE_PIN = 9;

const int SERIAL_RATE = 9600;

const int SENSOR_READ_DELAY = 50;
const int DANGER_WARNING_DELAY = 500;
const int SAFE_DELAY = 1000;

const float WARNING_TEMP = 30.0;
const float DANGER_TEMP = 35.0;

void applyColor(int redValue, int greenValue, int blueValue)
{
  analogWrite(RED_PIN, redValue);
  analogWrite(GREEN_PIN, greenValue);
  analogWrite(BLUE_PIN, blueValue);
}

void flashColor(int redValue, int greenValue, int blueValue, int delayMs)
{
  applyColor(redValue, greenValue, blueValue);
  delay(delayMs);
  applyColor(0, 0, 0);
  delay(delayMs);
}

void showAlarm(float tempC, bool flameDetected)
{
  if (flameDetected || tempC >= DANGER_TEMP) return flashColor(255, 0, 0, DANGER_WARNING_DELAY);
  if (tempC >= WARNING_TEMP) return flashColor(255, 165, 0, DANGER_WARNING_DELAY);
  flashColor(255, 255, 255, SAFE_DELAY);
}

void setupPins()
{
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  pinMode(PIN_TEMP_OUT, OUTPUT);
  pinMode(PIN_OR_OUT, INPUT);
  pinMode(PIN_NTC, INPUT);
}

void setup()
{
  Serial.begin(SERIAL_RATE);
  setupPins();
  analogReference(DEFAULT);
}

float calcKelvin()
{
  const int   ADC_MAX   = 1023;
  const float RSER_OHM  = 4700.0;
  const float R0_OHM    = 10000.0;
  const float BETA      = 3950.0;
  const float T0_K      = 25.0 + 273.15;

  int adc = analogRead(PIN_NTC);
  if (adc < 1)
  {
    adc = 1;
  }

  float Rntc = RSER_OHM * ( (float)ADC_MAX / (float)adc - 1.0 );
  float invT  = (1.0 / T0_K) + (1.0 / BETA) * log(Rntc / R0_OHM);
  float tempK = 1.0 / invT;
  return tempK;
}

float readCelsius()
{
  return calcKelvin() - 273.15;
}

bool hasFlame()
{
  digitalWrite(PIN_TEMP_OUT, LOW);
  delayMicroseconds(SENSOR_READ_DELAY);
  return (digitalRead(PIN_OR_OUT) == HIGH);
}

void sendTempSignal(float tempC)
{
  digitalWrite(PIN_TEMP_OUT, tempC > WARNING_TEMP ? HIGH : LOW);
  delayMicroseconds(SENSOR_READ_DELAY);
}

void loop()
{
  float temp = readCelsius();
  bool flameDetected = hasFlame();

  sendTempSignal(temp);
  Serial.println(temp);
  showAlarm(temp, flameDetected);
}
