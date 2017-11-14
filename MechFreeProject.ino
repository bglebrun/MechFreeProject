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
  Serial.println("Light: ", analogRead(Light), " Tmp1: ", analogRead(Temp1), " Tmp2: ", analogRead(Temp2));
}
