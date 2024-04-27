#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Set the I2C address and dimensions (16x2)

const int buttonPin1 = 7; 
int buttonState1 = LOW; 
const int ledPin1 = 6; 
const int buttonPin2 = 8; 
int buttonState2 = LOW; 
const int ledPin2 = 9; 
const int buttonPin3 = 4; 
int buttonState3 = LOW; 
const int ledPin3 = 5; 
const int buttonPin4 = 2; 
int buttonState4 = LOW; 
const int ledPin4 = 3; 

int randomLED = 0; // Initialize with an invalid LED number
int previousLED = 0; // Track the previously generated LED
int score = 0; 
bool gameEnded = false; 

unsigned long startTime = 0; // Variable to track the start time for each round
const unsigned long roundDuration = 700; // Set the duration for each round in milliseconds (3 seconds)

void setup() {
  pinMode(buttonPin1, INPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(buttonPin4, INPUT);
  pinMode(ledPin4, OUTPUT);
  Serial.begin(9600);
  randomSeed(analogRead(0)); 

  lcd.init();  // Initialize the LCD
  lcd.backlight();  // Turn on the backlight
  lcd.begin(16, 2);  // Set the LCD dimensions (16x2)

  lcd.clear();
  lcd.print("Press any button");
}

void loop() {
  if (!gameEnded) {
    unsigned long currentTime = millis(); // Get the current time

    if (startTime == 0 || currentTime - startTime >= roundDuration) {
      startNewRound(); // Start a new round
      startTime = currentTime; // Update the start time for the round
    }

    if (currentTime - startTime <= roundDuration) {
      checkButtonPress();
       Serial.println (checkButtonPress());
      // Check if the correct button was pressed
    } else if(!checkButtonPress()){
      Serial.println (checkButtonPress());
      endGame();
       // If the time limit is exceeded, end the game
    }
    else
    endGame();

    updateScoreDisplay(); // Update and display the score on the LCD
  }
}

void startNewRound() {
  do {
    randomLED = random(1, 5); // Generate a random number between 1 and 4
  } while (randomLED == previousLED); // Ensure it's not the same as the previous LED

  previousLED = randomLED; // Update the previously generated LED

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Press button " + String(randomLED) + "!");

  flashLED(randomLED);
  delay(500); 
}

int checkButtonPress() {
  switch (randomLED) {
    case 1:
      if (digitalRead(buttonPin1) == HIGH) {
        score++;
        return 1;
      } else {
        endGame();
      }
      break;
    case 2:
      if (digitalRead(buttonPin2) == HIGH) {
        score++;
        return 2;
      } else {
        endGame();
      }
      break;
    case 3:
      if (digitalRead(buttonPin3) == HIGH) {
        score++;
        return 3;
      } else {
        endGame();
      }
      break;
    case 4:
      if (digitalRead(buttonPin4) == HIGH) {
        score++;
        return 4;
      } else {
        endGame();
      }
      break;
  }
}

void updateScoreDisplay() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Score: " + String(score));
  delay(500); 
}

void flashLED(int led) {
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
  digitalWrite(ledPin4, LOW);

  switch (led) {
    case 1:
      digitalWrite(ledPin1, HIGH);
      break;
    case 2:
      digitalWrite(ledPin2, HIGH);
      break;
    case 3:
      digitalWrite(ledPin3, HIGH);
      break;
    case 4:
      digitalWrite(ledPin4, HIGH);
      break;
      default:
      return 0;
  }
}

void endGame() {
  gameEnded = true;
  if(gameEnded){
  Serial.println("Game Over! Final Score: " + String(score));
  score = 0; // Reset score for a new round
  
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
  digitalWrite(ledPin4, LOW);
  delay(500);
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin3, HIGH);
  digitalWrite(ledPin4, HIGH);
  delay(500);
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
  digitalWrite(ledPin4, LOW);
  delay(500);

  lcd.clear();
  lcd.print("Game Over! Score: " + String(score));
  delay(500); // Delay for 2 seconds before starting a new game
  }
  gameEnded = false;
}
