#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {2, 3, 4, 5}; 
byte colPins[COLS] = {6, 7, 8, 9};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int greenLEDPin = 12;  
const int redLEDPin = 1;    
const int motorPin1 = 0;     // Motor antihorário
const int motorPin2 = 13;    // Motor horário
const int velocidade = 10;
const int buttonPin = 11;   

String password = "1234";
String inputPassword = "";

void setup() {
  pinMode(greenLEDPin, OUTPUT); 
  pinMode(redLEDPin, OUTPUT);    
  
  pinMode(velocidade, OUTPUT); 
  pinMode(motorPin1, OUTPUT);   
  pinMode(motorPin2, OUTPUT);   

  pinMode(buttonPin, INPUT_PULLUP);  
  
  lcd.init();
  lcd.backlight();
  lcd.print("Aguardando...");
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {  
    lcd.clear();
    lcd.print("Digite a senha");
    inputPassword = "";
    
   
    while (inputPassword.length() < 4) {
      char key = keypad.getKey();
      if (key) {
        inputPassword += key;
        lcd.setCursor(0, 1);
        lcd.print("*");  
        delay(300); 
      }
    }
    

    if (inputPassword == password) {
      digitalWrite(greenLEDPin, HIGH);  
      lcd.clear();
      lcd.print("Acesso Permitido");
      activateMotor();  
      delay(4000);  
      digitalWrite(greenLEDPin, LOW);  
    } else {
      digitalWrite(redLEDPin, HIGH);  
      lcd.clear();
      lcd.print("Acesso Negado");
      delay(2000);  
      delay(4000);  
      digitalWrite(redLEDPin, LOW);   
    }
    
    resetSystem(); 
  }
}

void activateMotor() {
  digitalWrite(motorPin1, HIGH);  
  digitalWrite(motorPin2, LOW);   
  delay(5000);  
  digitalWrite(motorPin1, LOW);  
}

void resetSystem() {
  inputPassword = "";
  lcd.clear();
  lcd.print("Aguardando...");
}
