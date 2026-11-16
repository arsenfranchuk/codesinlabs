const int DATA_PIN = 3;
const int CLOCK_PIN = 4;
const int LATCH_PIN = 5;

const int STEP_DELAY = 200;

class RunningLight
{
private:
  int dataPin;
  int clockPin;
  int latchPin;
  int stepDelay;
  int currentStep;

  void tickClock()
  {
    digitalWrite(clockPin, HIGH);
    digitalWrite(clockPin, LOW);
  }

  void tickLatch()
  {
    digitalWrite(latchPin, HIGH);
    digitalWrite(latchPin, LOW);
  }

  void pushBit(int bitValue)
  {
    digitalWrite(dataPin, bitValue);
    tickClock();
    tickLatch();
  }

public:
  RunningLight(int dataPin, int clockPin, int latchPin, int stepDelay)
  {
    dataPin = dataPin;
    clockPin = clockPin;
    latchPin = latchPin;
    stepDelay = stepDelay;
    currentStep = 0;
  }

  void resetAll()
  {
    digitalWrite(dataPin, LOW);

    for (int i = 0; i < 8; i++)
    {
      tickClock();
    }

    tickLatch();
  }

  void setupPins()
  {
    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(latchPin, OUTPUT);

    digitalWrite(dataPin, LOW);
    digitalWrite(clockPin, LOW);
    digitalWrite(latchPin, LOW);

    resetAll();
  }

  void stepLight()
  {
    int bitToSend = (currentStep == 0) ? HIGH : LOW;

    pushBit(bitToSend);

    currentStep = (currentStep + 1) % 8;
    delay(stepDelay);
  }
};

RunningLight runningLight(DATA_PIN, CLOCK_PIN, LATCH_PIN, STEP_DELAY);

void setup()
{
  runningLight.setupPins();
}

void loop()
{
  runningLight.stepLight();
}
