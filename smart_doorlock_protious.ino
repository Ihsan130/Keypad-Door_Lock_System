#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

Servo myServo;
const int servoPin     = 10;
const int redLedPin    = 11;
const int greenLedPin  = 12;
const int pirPin       = 2;   

String correctPassword = "87654";
String inputPassword = "";


bool systemActive = false;
unsigned long lastActivityTime = 0;
const unsigned long idleTimeout = 10000; 

void setup() {
  pinMode(pirPin, INPUT);
  myServo.write(0);
  myServo.attach(servoPin);

  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  digitalWrite(redLedPin, LOW);
  digitalWrite(greenLedPin, LOW);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.noDisplay(); 
  systemActive = false;
}

void loop() {
  int pirState = digitalRead(pirPin);

  
  if (!systemActive) {
    if (pirState == HIGH) {
      systemActive = true;
      lcd.display(); 
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Welcome!");
      delay(1500);
      showEnterPassword();
      lastActivityTime = millis();
    }
    return; 
  }

  
  if (systemActive && (millis() - lastActivityTime > idleTimeout)) {
    lcd.clear();
    lcd.noDisplay(); 
    digitalWrite(redLedPin, LOW);
    digitalWrite(greenLedPin, LOW);
    inputPassword = "";
    systemActive = false; 
    return;
  }

 
  char key = keypad.getKey();

  if (key) {
    lastActivityTime = millis(); 

    if (key == '#') {
      if (inputPassword.length() > 0) {
        inputPassword.remove(inputPassword.length() - 1);
        showEnterPassword();
      }
    }
    else if (key == '*') {
      if (inputPassword == correctPassword) {
        showMessage("Status:", "Access Granted!");
        digitalWrite(greenLedPin, HIGH);
        digitalWrite(redLedPin, LOW);

        myServo.write(90); 
        delay(4000);
        myServo.write(0); 

        digitalWrite(greenLedPin, LOW);
      }
      else {
        showMessage("Status:", "Wrong Password!");
        digitalWrite(redLedPin, HIGH);
        digitalWrite(greenLedPin, LOW);
        delay(2000);
        digitalWrite(redLedPin, LOW);
      }
      inputPassword = "";
      
      
      lastActivityTime = millis(); 
      showEnterPassword();
    }
    else {
      if (inputPassword.length() < 6) {
        inputPassword += key;
        showEnterPassword();
      }
    }
  }
}

void showMessage(String line1, String line2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
}

void showEnterPassword() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");
  lcd.setCursor(0, 1);
  for (int i = 0; i < inputPassword.length(); i++) {
    lcd.print('*');
  }
}