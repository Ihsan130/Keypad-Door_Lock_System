#  Arduino Keypad Door Lock System

A password-based door lock system built with **Arduino Uno** and simulated in **Proteus**. The user enters a password through a 4x3 keypad. If the password is correct, the servo motor unlocks the door and the green LED turns on. If it is wrong, the red LED turns on and an error message is shown on the LCD.

##  Features
- Password authentication using a 4x3 matrix keypad
- 16x2 LCD (LM016L) shows prompts and status messages
- Servo motor acts as the door lock/unlock mechanism
- Green LED indicates access granted
- Red LED indicates access denied
- Fully simulated in Proteus (no hardware required)

##  Components Used
| Component | Quantity |
|---|---|
| Arduino Uno (ATmega328P) | 1 |
| 16x2 LCD (LM016L) | 1 |
| 4x3 Keypad | 1 |
| Servo Motor | 1 |
| LED (Red) | 1 |
| LED (Green) | 1 |
| Resistor 1kΩ | 1 |

##  Pin Connections
| Component | Arduino Pin |
|---|---|
| LCD RS, E, D4–D7 | A0 – A5 |
| Keypad Rows / Columns | D2 – D8 |
| Servo Motor | D9 / D10 |
| Red LED | D11 / D12 |
| Green LED | D11 / D12 |

> Note: Please adjust the pin numbers according to your actual code.

##  How It Works
1. System starts and LCD shows "Enter Password".
2. User types the password using the keypad.
3. Arduino compares it with the stored password.
4. **Correct:** Servo rotates (door opens), green LED ON, LCD shows "Access Granted".
5. **Wrong:** Red LED ON, LCD shows "Wrong Password".

##  How to Run<img width="1127" height="806" alt="Screenshot 2026-11-18 201638" src="https://github.com/user-attachments/assets/ed2a6a9d-cd9b-4205-83a1-ff42f254fdb0" />

1. Open the `.pdsprj` file in **Proteus**.
2. Double-click the Arduino and load the compiled `.hex` file.
3. Run the simulation and use the keypad.

## 📁 Project Structure
