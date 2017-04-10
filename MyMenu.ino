#include <OneButton.h>
#include <Encoder.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C  lcd(0x27,2,1,0,4,5,6,7);

// ROTARY ENCODER
long oldPosition  = 0;
int encoderDTpin = 2;
int encoderCLKpin = 3;
Encoder myEnc(encoderDTpin, encoderCLKpin);

int buttonPin = 8;
OneButton button0(buttonPin, true);

int cursorPos = 0;

int currentPosition=0;
int lcdUpdated = 0;

int itemSelected = 5;

byte cursor[8] = {
  0b10000,
  0b10000,
  0b01000,
  0b00110,
  0b01000,
  0b10000,
  0b10000,
  0b00000
};

String menu[] = {
  "RED   :",
  "GREEN :",
  "BLUE  :",
  "WHITE :"
  };

int colorValues[] = {
  25,
  50,
  100,
  250
};

void setup() {
  Serial.begin(9600);
  Serial.println("Begin : " + String(currentPosition));
  // Map rotary button to actions
   button0.attachClick(singleClick);
   button0.attachDoubleClick(doubleClick);

  // Setup LCD
  lcd.begin (16,2);
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home();

  //Create 
  lcd.createChar(0, cursor);
  lcd.setCursor (2,0);
  lcd.print("RGBW Colors");
  delay(1000);
  lcd.setCursor (0,0);   
  lcd.print("                ");
  lcd.setCursor (0,0); 
  writeCursor();
  
}

void loop() {

  button0.tick();
  lcdMenu();
  rotary_check();


}


void singleClick() {
  
  Serial.println("Button Pressed");
  lcdUpdated = 0;
  if(itemSelected == 5){
    itemSelected = currentPosition;
  }
  else{
    itemSelected = 5;
  }

}

void doubleClick() {}

void clearLine(int line){
  lcd.setCursor (0,line);
  lcd.print("                ");
}

void writeCursor(){
  
  lcd.write(byte(0));
}

void lcdMenu(){
  if(lcdUpdated == 0){
   
  clearMenu();
  Serial.println("Update LCD : " + String(currentPosition));

  if(currentPosition == 0){
    lcd.setCursor(0, 0);
    writeCursor();
    if(itemSelected == 0){
    lcd.setCursor(1, 0);
    lcd.print("*");
    }
    lcd.setCursor(2, 0);
    lcd.print(menu[0]);
    lcd.print(colorValues[0]);
    
    lcd.setCursor(2, 1);
    lcd.print(menu[1]);
    lcd.print(colorValues[1]);
  }
  if(currentPosition == 1){
    lcd.setCursor(0, 1);
    writeCursor();
    if(itemSelected == 1){
    lcd.setCursor(1, 1);
    lcd.print("*");
    }
    lcd.setCursor(2, 0);
    lcd.print(menu[0]);
    lcd.print(colorValues[0]);

    lcd.setCursor(2, 1);
    lcd.print(menu[1]);
    lcd.print(colorValues[1]);
  }
  
  if(currentPosition == 2){
    lcd.setCursor(0, 0);
    writeCursor();
    if(itemSelected == 2){
    lcd.setCursor(1, 0);
    lcd.print("*");
    }
    lcd.setCursor(2, 0);
    lcd.print(menu[2]);
    lcd.print(colorValues[2]);
    
    lcd.setCursor(2, 1);
    lcd.print(menu[3]);
    lcd.print(colorValues[3]);
  }
  if(currentPosition == 3){
    lcd.setCursor(0, 1);
    writeCursor();
    if(itemSelected == 3){
    lcd.setCursor(1, 1);
    lcd.print("*");
    }
    lcd.setCursor(2, 0);
    lcd.print(menu[2]);
    lcd.print(colorValues[2]);
    
    lcd.setCursor(2, 1);
    lcd.print(menu[3]);
    lcd.print(colorValues[3]);
  }
  lcdUpdated = 1;
  }
}

void clearMenu(){
  lcd.setCursor (0,0);
  lcd.print("               ");
  lcd.setCursor (0,1);
  lcd.print("               ");
}


void rotary_check(){
  long newPosition = myEnc.read() /4;
  
  if(newPosition != oldPosition){

      
      if(newPosition > oldPosition ){
        selectNext();
      }
      else if (newPosition < oldPosition ){
        selectPrevious();
      }

    lcdUpdated = 0;
    oldPosition = newPosition;
  }
}

void selectNext(){
  if(itemSelected == 5){
    if(currentPosition<3){
    
  currentPosition = (currentPosition+1) %4;
    }
  Serial.println("Select Next currentPosition : " + String(currentPosition));
  }
  else
  {
    colorValues[itemSelected] = (colorValues[itemSelected] +1) %255;
  }

}

void selectPrevious(){
 if(itemSelected == 5){
  if(currentPosition >0){
  currentPosition = (currentPosition-1) %4;
  }
  Serial.println("Select Previous currentPosition : " + String(currentPosition));
 }
 else
  {
    colorValues[itemSelected] = (colorValues[itemSelected] -1) %255;
  }

}























