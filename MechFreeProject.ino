#include <LiquidCrystal.h>
#include "IRremote.h"

const int receiver = 6; // Signal Pin of IR receiver to Arduino Digital Pin 11
const int Light = A0;
const int Temp1 = A1;
const int Temp2 = A2;
const int buzzer = 11;
const int rs = 12, en = 13, d4 = 9, d5 = 10, d6 = 8, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int adjustmentTemp = 25;

IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'


void setup() {
  // put your setup code here, to run once:
  pinMode(Light, INPUT);
  pinMode(Temp1, INPUT);
  pinMode(Temp2, INPUT);
  pinMode(receiver, INPUT);
  pinMode(buzzer, OUTPUT);

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
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //lcd.setCursor(0,0);
  //lcd.print("Therm: " + adjustmentTemp);
  Serial.print("Therm: "); Serial.println(adjustmentTemp);
  lcd.setCursor(0, 0);
  lcd.print("Now: "); lcd.print(avg, 2);
  Serial.print("Now: "); Serial.println(avg, 2);
  lcd.setCursor(0,1);
  lcd.print("Therm: "); lcd.print(adjustmentTemp);

  // IR remote commands
  if (irrecv.decode(&results)) // have we received an IR signal?

  {
    translateIR(); 
    irrecv.resume(); // receive the next value
  }
  delay(1000);
}
