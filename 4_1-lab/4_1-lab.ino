const int DATA_PIN = 3;
const int CLOCK_PIN = 4;
const int LATCH_PIN = 5;

const int STEP_DELAY = 200;

class RunningLight
{
private:
  int _dataPin;
  int _clockPin;
  int _latchPin;
  int _stepDelay;
  int _currentStep;

  void tickClock()
  {
    digitalWrite(_clockPin, HIGH);
    digitalWrite(_clockPin, LOW);
  }

  void tickLatch()
  {
    digitalWrite(_latchPin, HIGH);
    digitalWrite(_latchPin, LOW);
  }

  void pushBit(int bitValue)
  {
    digitalWrite(_dataPin, bitValue);
    tickClock();
    tickLatch();
  }

public:
  RunningLight(int dataPin, int clockPin, int latchPin, int stepDelay)
  {
    _dataPin = dataPin;
    _clockPin = clockPin;
    _latchPin = latchPin;
    _stepDelay = stepDelay;
    _currentStep = 0;
  }

  void resetAll()
  {
    digitalWrite(_dataPin, LOW);

    for (int i = 0; i < 8; i++)
    {
      tickClock();
    }

    tickLatch();
  }

  void setupPins()
  {
    pinMode(_dataPin, OUTPUT);
    pinMode(_clockPin, OUTPUT);
    pinMode(_latchPin, OUTPUT);

    digitalWrite(_dataPin, LOW);
    digitalWrite(_clockPin, LOW);
    digitalWrite(_latchPin, LOW);

    resetAll();
  }

  void stepLight()
  {
    int bitToSend = (_currentStep == 0) ? HIGH : LOW;

    pushBit(bitToSend);

    _currentStep = (_currentStep + 1) % 8;
    delay(_stepDelay);
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
