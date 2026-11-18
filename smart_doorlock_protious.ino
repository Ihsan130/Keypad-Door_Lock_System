#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>

// ---------- LCD (4-bit mode) ----------
// LiquidCrystal(RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

// ---------- Keypad (4 row, 3 column) ----------
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

// ---------- Servo ও LED ----------
Servo myServo;
const int servoPin    = 10;
const int redLedPin   = 11;
const int greenLedPin = 12;

// ---------- Password ----------
String correctPassword = "87654";
String inputPassword = "";

void setup() {
  // Servo আগে 0 degree এ set, তারপর attach
  myServo.write(0);
  myServo.attach(servoPin);

  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  digitalWrite(redLedPin, LOW);
  digitalWrite(greenLedPin, LOW);

  // LCD চালু (16 column, 2 row)
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Smart Door Lock");
  delay(2000);

  showEnterPassword();
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == '#') {
      // শেষ অক্ষর delete
      if (inputPassword.length() > 0) {
        inputPassword.remove(inputPassword.length() - 1);
        showEnterPassword();
      }
    }
    else if (key == '*') {
      // Password check
      if (inputPassword == correctPassword) {
        showMessage("Status:", "Access Granted!");
        digitalWrite(greenLedPin, HIGH);
        digitalWrite(redLedPin, LOW);

        myServo.write(90);   // Unlock
        delay(4000);
        myServo.write(0);    // আবার Lock

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
      showEnterPassword();
    }
    else {
      // সর্বোচ্চ 6 digit
      if (inputPassword.length() < 6) {
        inputPassword += key;
        showEnterPassword();
      }
    }
  }
}

// দুই লাইনের message দেখানোর function
void showMessage(String line1, String line2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
}

// Password '*' দিয়ে mask করে দেখানোর function
void showEnterPassword() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");
  lcd.setCursor(0, 1);
  for (int i = 0; i < inputPassword.length(); i++) {
    lcd.print('*');
  }
}