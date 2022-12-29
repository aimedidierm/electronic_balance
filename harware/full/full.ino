#include <LiquidCrystal.h>
#include <Keypad.h>
#include <ArduinoJson.h>
#include <HX711_ADC.h>
#if defined(ESP8266)|| defined(ESP32) || defined(AVR)
#include <EEPROM.h>
//LiquidCrystal_I2C lcd(0x27,20,4);
#endif
//pins:
const int HX711_dout = 4; //mcu > HX711 dout pin
const int HX711_sck = 5; //mcu > HX711 sck pin

//HX711 constructor:
HX711_ADC LoadCell(HX711_dout, HX711_sck);

const int calVal_eepromAdress = 0;
unsigned long t = 0;
const int rs = A0, en = A1, d4 = A2, d5 = A3, d6 = A4, d7 = A5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
String data = "";
const byte ROWS = 4;
const byte COLS = 4;
char newNum[12] = "", amount[12] = "", number[12] = "";
char keys[ROWS][COLS] = {

  {'1', '2', '3'},

  {'4', '5', '6'},

  {'7', '8', '9'},

  {'*', '0', '#'}

};

byte rowPins[ROWS] = {7, 6, 3, 2};
byte colPins[COLS] = {8, 9, 10};
int mi = 1;
float mass = 0,i =0;
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
int product = 0, price = 0, k = 0, totalam = 0;
void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  LoadCell.begin();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Smart electronic");
  lcd.setCursor(0, 1);
  lcd.print(" balance");
  //LoadCell.setReverseOutput(); //uncomment to turn a negative output value to positive
  float calibrationValue; // calibration value (see example file "Calibration.ino")
  calibrationValue = 34.45; // uncomment this if you want to set the calibration value in the sketch
#if defined(ESP8266)|| defined(ESP32)
  //EEPROM.begin(512); // uncomment this if you use ESP8266/ESP32 and want to fetch the calibration value from eeprom
#endif
  //EEPROM.get(calVal_eepromAdress, calibrationValue); // uncomment this if you want to fetch the calibration value from eeprom

  unsigned long stabilizingtime = 2000; // preciscion right after power-up can be improved by adding a few seconds of stabilizing time
  boolean _tare = true; //set this to false if you don't want tare to be performed in the next step
  LoadCell.start(stabilizingtime, _tare);
  if (LoadCell.getTareTimeoutFlag()) {
    Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
    while (1);
  }
  else {
    LoadCell.setCalFactor(calibrationValue); // set calibration value (float)
    Serial.println("Startup is complete");
  }
  delay(3000);
}

void loop() {
  sproduct();
  select();
  enteramount();
  enterphone();
}
void sproduct() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Select product");
  delay(2000);
  while (mi > 0) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("1. Sugar");
    lcd.setCursor(0, 1);
    lcd.print("# Next");
    int key = keypad.getKey();
    if (key == '1') {
      product = 1;
      select();
    }
    if (key == '#') {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("2. Rice");
      lcd.setCursor(0, 1);
      lcd.print("# Next");
      while (mi > 0) {
        int key = keypad.getKey();
        if (key == '2') {
          product = 2;
          select();
        }
        if (key == '#') {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("3. Beans");
          lcd.setCursor(0, 1);
          lcd.print("# Next");
          if (key == '#') {
            while (mi > 0) {
              int key = keypad.getKey();
              if (key == '3') {
                product = 3;
                select();
              }
              if (key == '#') {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("4. Salt");
                lcd.setCursor(0, 1);
                lcd.print("5. Meat");
                while (mi > 0) {
                  int key = keypad.getKey();
                  if (key == '4') {
                    product = 4;
                    select();
                  }
                  if (key == '5') {
                    product = 5;
                    select();
                  }
                  delay(200);
                }
              }
              delay(200);
            }
          }
          delay(200);
        }
      }
      delay(200);
    }
  }
}
void select() {
  //Serial.println((String)"product="+product);
  Serial.println((String)"{'productt':" + product + "}");
  /*while (k == 0) {
    if (Serial.available() > 0) {
      data = Serial.readStringUntil('\n');
      Serial.println(data);
      DynamicJsonBuffer jsonBuffer;
      JsonObject& root = jsonBuffer.parseObject(data);
      if (root["p"]) {
        price = root["p"];
        balance();
      }
    }
  }*/
  price=random(1000,2500);
  balance();
  delay(500);
}
void balance() {
    //my test codes
    int my = 0;
    static boolean newDataReady = 0;
    const int serialPrintInterval = 0; //increase value to slow down serial print activity

    // check for new data/start next conversion:
    if (LoadCell.update()) newDataReady = true;

    // get smoothed value from the dataset:
    if (newDataReady) {
      if (millis() > t + serialPrintInterval) {
        i = LoadCell.getData();
        Serial.println("Load_cell output val: ");
        Serial.println(i);
        lcd.clear();
        lcd.setCursor(0, 0);
        totalam = (i * price)/1000;
        lcd.print("Mass:");
        lcd.println(i);
        lcd.print("g");
        lcd.setCursor(0, 1);
        lcd.print(totalam);
        lcd.print("Rwf");
        newDataReady = 0;
        t = millis();
      }
    }

    // receive command from serial terminal, send 't' to initiate tare operation:
    if (Serial.available() > 0) {
      char inByte = Serial.read();
      if (inByte == 't') LoadCell.tareNoDelay();
    }

    // check if last tare operation is complete:
    if (LoadCell.getTareStatus() == true) {
      Serial.println("Tare complete");
    }
    int key = keypad.getKey();
    if (key == '#') {
      enteramount();
    }
    balance();
  }
void enteramount() {
  int i = 0, j = 0, m = 0, x = 0, s = 0, k = 0;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Please enter");
  lcd.setCursor(0, 1);
  lcd.print("amount payed");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter money");
  lcd.setCursor(0, 1);
  for (i = 2; i > 0; i++) {
    lcd.setCursor(0, 1);
    int key = keypad.getKey();
    if (key != NO_KEY && key != '#' && key != '*') {
      amount[j] = key;
      amount[j + 1] = '\0';
      j++;
      lcd.print(amount);
    }
    if (key == '#' && j > 0)
    {
      enterphone();
    }
    delay(100);
  }
}
void enterphone() {
  int i = 0, j = 0, m = 0, x = 0, s = 0, k = 0;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Please enter");
  lcd.setCursor(0, 1);
  lcd.print("phone number");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter number");
  lcd.setCursor(0, 1);
  for (i = 2; i > 0; i++) {
    lcd.setCursor(0, 1);
    int key = keypad.getKey();
    if (key != NO_KEY && key != '#' && key != '*') {
      number[j] = key;
      number[j + 1] = '\0';
      j++;
      lcd.print(number);
    }
    if (key == '#' && j > 0)
    {
      ending();
    }
    delay(100);
  }
}
void ending() {
  //Serial.println((String)"bill="+product+"product="+product+"&phone="+number+"&total="+totalam+"&amount="+amount+"&mass="+mass);

  Serial.println((String)"{'bill':" + product + ", '" + "product':" + product + ", '" + "phone':'" + number + "', '" + "total':" + totalam + ", '" + "amount':" + amount + ", '" + "mass':" + i + "}");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Bill sent");
  delay(4000);
  sproduct();
}
