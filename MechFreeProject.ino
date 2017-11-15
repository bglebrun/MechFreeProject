const int Light = A0;
const int Temp1 = A1;
const int Temp2 = A2;

void setup() {
  // put your setup code here, to run once:
  pinMode(Light, INPUT);
  pinMode(Temp1, INPUT);
  pinMode(Temp2, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  float Read1 = ((analogRead(Temp1)/1023.0*5.0) - 0.52) / 0.0096;
  float Read2 = ((analogRead(Temp2)/1023.0*5.0) - 0.52) / 0.0096;
  // Above 900 -> switch shades
  /*
  Serial.print("Light: ");
  Serial.println(analogRead(Light));
  Serial.print("Temp1: ");
  Serial.println(Read1);
  Serial.print("Temp2: ");
  Serial.println(Read2);
  Serial.print("Average: ");
  Serial.println((Read1 + Read2)/2);
  delay(1000);*/
  OpenMaw();
  delay(500);
  CloseMaw();
  delay(500);
}

void OpenMaw() {
  for (int i = 0; i < 48 * 64 / 4; i++) Open();
}

void CloseMaw() {
  for (int i = 0; i < 48 * 64 / 4; i++) Close();
}
