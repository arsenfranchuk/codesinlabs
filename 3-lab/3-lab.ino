const int PULL_RESET_PIN = 2;
const int TRIGGER_BUTTON_PIN = 3;
const int TRIGGER_NOT_Q_PIN = 4;
const int TRIGGER_Q_PIN = 5;
const int LED_FORBIDDEN_PIN = 13;

const int SERIAL_RATE = 9600;
const int LOOP_DELAY = 25;

void setupPins()
{
  pinMode(PULL_RESET_PIN, INPUT);
  pinMode(TRIGGER_BUTTON_PIN, OUTPUT);
  digitalWrite(TRIGGER_BUTTON_PIN, LOW);

  pinMode(TRIGGER_Q_PIN, INPUT);
  pinMode(TRIGGER_NOT_Q_PIN, INPUT);

  pinMode(LED_FORBIDDEN_PIN, OUTPUT);
  digitalWrite(LED_FORBIDDEN_PIN, LOW);
}

void setup()
{
  setupPins();
  Serial.begin(SERIAL_RATE);
}

void syncReset()
{
  int resetBtn = digitalRead(PULL_RESET_PIN);
  digitalWrite(TRIGGER_BUTTON_PIN, resetBtn == HIGH ? HIGH : LOW);
}

int isForbidden(int qState, int notQState)
{
  bool state = (qState == LOW && notQState == LOW);
  digitalWrite(LED_FORBIDDEN_PIN, state ? HIGH : LOW);
  return state ? 1 : 0;
}

void printStatus(int qState, int notQState, int forbidden)
{
  Serial.print("Q:");
  Serial.print(qState);
  Serial.print(" notQ:");
  Serial.print(notQState);
  Serial.print(" Forbidden:");
  Serial.println(forbidden);
}

void loop()
{
  syncReset();

  int qState = digitalRead(TRIGGER_Q_PIN);
  int notQState = digitalRead(TRIGGER_NOT_Q_PIN);
  int forbidden = isForbidden(qState, notQState);

  printStatus(qState, notQState, forbidden);
  delay(LOOP_DELAY);
}
