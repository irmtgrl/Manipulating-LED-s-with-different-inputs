#define RED_LED_PIN 9
#define YELLOW_LED_PIN 10
#define GREEN_LED_PIN 11
#define POTENTIOMETER_PIN A2
#define BUTTON_PIN 3

int redLedState = LOW;
int yellowLedState = LOW;
int greenLedState = LOW;

unsigned long lastTimeRedLedWasLit = millis();
unsigned long redLedBlinkInterval = 700;

void setup() {
  Serial.begin(115200);
  Serial.println("Arduino on!");

  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

  pinMode(POTENTIOMETER_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT);

  digitalWrite(RED_LED_PIN, redLedState);
  digitalWrite(YELLOW_LED_PIN, yellowLedState);
  digitalWrite(GREEN_LED_PIN, greenLedState);
}

void loop() {
  if(Serial.available() > 0) {
    int userInput = Serial.parseInt();
    if(userInput >= 100 && userInput <=5000) {
      redLedBlinkInterval = userInput;
    }
  }

  unsigned long timeNow = millis();
  //Red LED - user input
  if(timeNow - lastTimeRedLedWasLit > redLedBlinkInterval) {
    if(redLedState == LOW) {
      redLedState = HIGH;
    } else {
      redLedState = LOW;
    }
  digitalWrite(RED_LED_PIN, redLedState);
  lastTimeRedLedWasLit += redLedBlinkInterval;
  }

  //Green LED - potentiometer
  analogWrite(GREEN_LED_PIN, analogRead(POTENTIOMETER_PIN)/4);

  //Yellow LED - button
  if(digitalRead(BUTTON_PIN) == HIGH) {
    if(yellowLedState == LOW) {
      yellowLedState = HIGH;
      digitalWrite(YELLOW_LED_PIN, yellowLedState);
    }
  } else {
    yellowLedState = LOW;
    digitalWrite(YELLOW_LED_PIN, yellowLedState);
  }
}
