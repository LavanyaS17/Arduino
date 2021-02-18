int b=12,i;
void setup() {
  // put your setup code here, to run once:
pinMode(b,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.begin(9600);
 for(i=1;i<5;i++)
 {
  digitalWrite(b,HIGH);
  delay(1000);
  digitalWrite(b,LOW);
  delay(1000);
 }
 exit(0);
}
