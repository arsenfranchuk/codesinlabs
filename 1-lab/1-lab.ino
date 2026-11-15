const int PIN_AND_OUT = 5;
const int LED_COUNT = 3;
const int LED_PINS[LED_COUNT] = {4, 3, 2};

const int TARGET_COUNT = 10;
const int LOOP_DELAY = 1000;

int highCount = 0;
int activeLed = -1;

void setupPins() {
  pinMode(PIN_AND_OUT, INPUT);

  for (int i = 0; i < LED_COUNT; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], LOW);
  }
}

void nextLed() {
  if (activeLed >= 0) {
    digitalWrite(LED_PINS[activeLed], LOW);
  }

  activeLed = (activeLed + 1) % LED_COUNT;
  digitalWrite(LED_PINS[activeLed], HIGH);
}

void checkTrigger() {
  if (digitalRead(PIN_AND_OUT) == HIGH) {
    highCount++;

    if (highCount >= TARGET_COUNT) {
      highCount = 0;
      nextLed();
    }
  }
}

void setup() {
  setupPins();
}

void loop() {
  checkTrigger();
  delay(LOOP_DELAY);
}
