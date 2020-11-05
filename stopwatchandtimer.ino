#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
long currentMillis;
long endMillis;
int oreTimer = 1;
int minuteTimer = 1;
int secundeTimer = 1;
int oreStopwatch = 0;
int minuteStopwatch = 0;
int secundeStopwatch = 0;
byte rowPins[ROWS] = {28,29,27,26};
byte colPins[COLS] = {25,24,23,22};
bool stopwatch = false;
bool timer = false;
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  currentMillis = 0;
  endMillis = 0;
  Serial.begin(9600);
  lcd.begin();

}

void loop() {
  char customKey = customKeypad.getKey();
   /*Stopwatch*/
  if (customKey == 'A' && stopwatch == true) {
    lcd.begin();
    lcd.setCursor(0,0);
    lcd.print("Timp final:");
    delay(500);
    lcd.setCursor(5,1);
    timerString(oreStopwatch,minuteStopwatch,secundeStopwatch);
    stopwatch = false;
  }
  if (customKey == '1') {
    stopwatch = true;
    timer = false;
    oreStopwatch=0;
    minuteStopwatch=0;
    secundeStopwatch=0;
    lcd.begin();
    lcd.setCursor(0,0);
    lcd.print("Incepem");
    lcd.setCursor(5,1);
    lcd.print("cronometru!");
  }
  
  if (stopwatch) {
    currentMillis = millis();
    if (currentMillis - endMillis > 1000) {
      timerString(oreStopwatch,minuteStopwatch,secundeStopwatch);
      lcd.setCursor(0,1);
      if (secundeStopwatch == 59 && minuteStopwatch!=59) {
        minuteStopwatch++;
        secundeStopwatch = 0;
      } else {
        secundeStopwatch++;
      }
      if(minuteStopwatch == 59 && secundeStopwatch == 59){
        timerString(oreStopwatch,minuteStopwatch,secundeStopwatch);
        oreStopwatch++;
        minuteStopwatch=0;
        secundeStopwatch=0;
    }
    endMillis = millis();
  }
  }
  
  //////////////////////////////////////////////////////////////////////////////////////////////////////
  /*TIMER*/
  if (customKey == '4') {
      lcd.begin();
      lcd.setCursor(2,0);
      lcd.print("Timer mode");
    stopwatch = false;
  }
  if (customKey == 'B') {
    timer = true;
  }
  if (timer) {
    currentMillis = millis();
    if (currentMillis - endMillis > 1000) {
      timerString(oreTimer,minuteTimer,secundeTimer);
      if (secundeTimer == 0) {
        minuteTimer--;
        secundeTimer = 59;
      } else {
        secundeTimer--;
      }
      if (minuteTimer == 0 && secundeTimer==0 && oreTimer!=0) {
         timerString(oreTimer,minuteTimer,secundeTimer);
          oreTimer--;
          minuteTimer = 59;
          secundeTimer = 59;  
      }
      if (secundeTimer == 0 && minuteTimer == 0 && oreTimer == 0) {
          lcd.begin();
          lcd.print("Timpul a");
          lcd.setCursor(6,1);
          lcd.print("expirat!");
          timer = false;
      }
      endMillis = millis();
    }
  }
  /*Setare timer*/
  if(customKey == '7'){
    if(secundeTimer<59)
      secundeTimer++;
    timerString(oreTimer,minuteTimer,secundeTimer);
      
  }
   if(customKey == '8'){
    if(minuteTimer<59)
      minuteTimer++;
    timerString(oreTimer,minuteTimer,secundeTimer);
    
  }
   if(customKey == '9'){
    if(oreTimer<23)
      oreTimer++;
   timerString(oreTimer,minuteTimer,secundeTimer);
     
  }
  if(customKey == '*'){
    if(secundeTimer>=1)
      secundeTimer--;
   timerString(oreTimer,minuteTimer,secundeTimer);
      
  }
   if(customKey == '0'){
    if(minuteTimer>=1)
      minuteTimer--;
    timerString(oreTimer,minuteTimer,secundeTimer);
    
  }
   if(customKey == '#'){
    if(oreTimer>=1)
      oreTimer--;
     timerString(oreTimer,minuteTimer,secundeTimer);
  }
}
void timerString(int oref,int minutef,int secundef){
       String temp="";
  if(oref<10){
     temp += "0"+String(oref)+":";
  }else{
     temp += String(oref)+":"; 
  }
  if(minutef<10){
     temp += "0"+String(minutef)+":";
  }else{
     temp += String(minutef)+":"; 
  }
  if(secundef<10){
     temp += "0"+String(secundef);
  }else{
     temp += String(secundef); 
  }
  lcd.begin();
  lcd.setCursor(0,0);
  lcd.print("Time: hh/mm/ss");
  lcd.setCursor(6,1);
  lcd.print(temp);
}
 
