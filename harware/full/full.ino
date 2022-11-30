#include <LiquidCrystal.h>
#include <Keypad.h>


const int rs = A0, en = A1, d4 = A2, d5 = A3, d6 = A4, d7 = A5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const byte ROWS = 4;
const byte COLS = 4;
char newNum[12]="",amount[12]="",number[12]="";
char keys[ROWS][COLS] = {

    {'1','2','3'},

    {'4','5','6'},

    {'7','8','9'},

    {'*','0','#'}

};

byte rowPins[ROWS] = {7, 6, 3, 2};
byte colPins[COLS] = {8, 9, 10};
int mi=1;
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
int product=0;
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);

}

void loop() {
  sproduct();
  select();
  enteramount();
  enterphone();
}
void sproduct(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Select product");
  delay(2000);
  while(mi>0){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("1. Sugar");
  lcd.setCursor(0, 1);
  lcd.print("# Next");
  int key = keypad.getKey();
  if (key=='1') {
    product=1;
    select();
  }
  if (key=='#') {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("2. Rice");
  lcd.setCursor(0, 1);
  lcd.print("# Next");
  while(mi>0){
  int key = keypad.getKey();
  if (key=='2') {
    product=2;
    select();
  }
  if (key=='#') {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("3. Beans");
  lcd.setCursor(0, 1);
  lcd.print("# Next");
  if (key=='#') {
  while(mi>0){
  int key = keypad.getKey();
  if (key=='3') {
    product=3;
    select();
  }
  if (key=='#') {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("4. Salt");
  lcd.setCursor(0, 1);
  lcd.print("5. Meat");
  while(mi>0){
  int key = keypad.getKey();
  if (key=='4') {
    product=4;
    select();
  }
  if (key=='5') {
    product=5;
    select();
  }
  delay(200);}
  }
  delay(200);}
  }
  delay(200);}
  }
  delay(200);}
  }
  }
void select(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Place product");
  lcd.setCursor(0, 1);
  lcd.print("on the balance");
  delay(4000);
  enteramount();
  }
void enteramount(){
  int i=0,j=0,m=0,x=0,s=0,k=0;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Please enter");
  lcd.setCursor(0,1);
  lcd.print("amount payed");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter money");
  lcd.setCursor(0,1);
  for(i=2;i>0;i++){
    lcd.setCursor(0,1);
    int key = keypad.getKey();
    if (key!=NO_KEY && key!='#' && key!='*'){
        newNum[j] = key;
        newNum[j+1]='\0';   
        j++;
        lcd.print(newNum);
    }
    if (key=='#'&& j>0)
    {
      enterphone();
      }
      delay(100);
      }
  }
void enterphone(){
  int i=0,j=0,m=0,x=0,s=0,k=0;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Please enter");
  lcd.setCursor(0,1);
  lcd.print("phone number");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter number");
  lcd.setCursor(0,1);
  for(i=2;i>0;i++){
    lcd.setCursor(0,1);
    int key = keypad.getKey();
    if (key!=NO_KEY && key!='#' && key!='*'){
        number[j] = key;
        number[j+1]='\0';   
        j++;
        lcd.print(number);
    }
    if (key=='#'&& j>0)
    {
      sproduct();
      }
      delay(100);
      }
  }