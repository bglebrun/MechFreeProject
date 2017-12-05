#include <LiquidCrystal.h>
#include "IRremote.h"

const int receiver = 6; // Signal Pin of IR receiver to Arduino Digital Pin 11
const int Light = A0;
const int Temp1 = A1;
const int Temp2 = A2;
const int buzzer = 11;
const int rs = 12, en = 13, d4 = 9, d5 = 10, d6 = 8, d7 = 7;
const int lightLevels[] = {700, 800, 900};
enum levelMode { lowLight, medLight, highLight };
levelMode currentLevel = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int incomingByte = 0;   // for incoming serial data
bool isOpen = false;
bool manualMode = false;

IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'


void setup() {
  // put your setup code here, to run once:
  pinMode(Light, INPUT);
  pinMode(Temp1, INPUT);
  pinMode(Temp2, INPUT);
  pinMode(receiver, INPUT);
  pinMode(buzzer, OUTPUT);

  resetShades();

  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}

void loop() {
  // put your main code here, to run repeatedly:
  float Read1 = ((analogRead(Temp1)/1023.0*5.0) - 0.52) / 0.0096;
  float Read2 = ((analogRead(Temp2)/1023.0*5.0) - 0.52) / 0.0096;
  float avg = (Read1+Read2)/2;
  int lightLevel = analogRead(Light);
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 0);
  lcd.print("Temp: "); lcd.print(avg, 2); lcd.print(" C");
  if (manualMode) {
    lcd.setCursor(0,1);
    lcd.print("MANUAL MODE");
  } else {
    autoMode(lightLevel, avg);
  }
  // IR remote commands
  if (irrecv.decode(&results)) // have we received an IR signal?
  {
    translateIR(); 
    irrecv.resume(); // receive the next value
  }

  delay(1000);
}

void autoMode(int lightLevel, float averageTemp) {
  lcd.setCursor(0,1);
  lcd.print("Light: ");
  switch(currentLevel) {
    case lowLight: lcd.print("Low      "); break;
    case medLight: lcd.print("Med     "); break;
    case highLight: lcd.print("High     "); break;
    defaut: lcd.print("dunMESSEDup"); break;
  }
  Serial.println(lightLevel);
  if (lightLevels[currentLevel] > lightLevel) {
    if (!isOpen) {
      OpenWindow();
    }
  } else {
    if (isOpen) {
      CloseWindow();
    }
  }
}

void resetShades() {
  lcd.clear();
  lcd.print("RESETTING...");
  for (int i = 0; i < 5000; i++) Open();
  OpenWindow();
  isOpen = true;
}

void hardReset() {
  lcd.clear();
  lcd.print("RESETTING...");
  lcd.setCursor(0,1);
  lcd.print("BRB");
  CloseWindow();
  OpenWindow();
}

