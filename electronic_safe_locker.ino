#include<Keypad.h>
#include<LiquidCrystal.h>
#include<Servo.h>

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
Servo motor;
char masterLock[4] = {'d', 'd', 'd', 'd'};
char ipPsw[4];
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'a', 'e', 'c', 'd'},
  {'b', 'f', 'g', 'h'},
  {'c', 'g', 'k', 'l'},
  {'d', 'h', 'o', 'p'}
};
int flag = 0;
int i = 0;

byte rowPins[ROWS] = {7, 6, 5, 4};
byte colPins[COLS] = {3, 2, 1, 0};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  Serial.begin(9600);
  motor.attach(A0);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);

  lcd.print("Electronic Safe");
  delay(5000);


}

void loop() {
    lcd.clear();
closed();
  char key = keypad.getKey();
  if (key) {
    Serial.println(key);
    ipPsw[i] = key;
    i++;
  }
  Serial.println(ipPsw);
  Serial.println(i);
  if (i >= 4) {
    for (int a = 0; a <= 4; a++) {

      if (masterLock[a] == ipPsw[a]) {
        flag++;
        delay(10);
      }
    }
  }

  if (flag == 4) {
    Serial.println("open");
 opened();

 
    motor.write(0);
    delay(10000);                     //change timer
    motor.write(70);
 
closed();
    
    flag = 0;
    i = 0;
    for (int x = 0; x <= 4; x++) {
      ipPsw[x] = '\0';
    }
  }


}
void opened(){
 lcd.clear();
  lcd.setCursor(0, 0);
    lcd.print("Enter Password");
    lcd.setCursor(0, 1);
    lcd.print("OPEN");
    delay(10);
}
void closed(){
  lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter Password");
    lcd.setCursor(0, 1);
    lcd.print("CLOSE"); 
    delay(10);
}
