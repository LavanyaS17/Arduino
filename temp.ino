#include <IRremote.h>
#include <LiquidCrystal.h>
IRsend irsend;
int button=12;
int b=8;
int a,h,i;
int recvPin = 7;  // CONNECT THE OUTPUT PIN OF THE IR RECIEVER TO THIS PIN
IRrecv irrecv(recvPin);
decode_results results;
const int rs = 10, en = 11, d4 = 4, d5 = 5, d6 = 6, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
  // put your setup code here, to run once:
a=50,h=10;
lcd.begin(16, 2);
pinMode(12,INPUT_PULLUP);
pinMode(b,OUTPUT);
irrecv.enableIRIn();
/* lcd.print("AMMO=");lcd.print(a);
  lcd.print("HEALTH=");lcd.print(h);*/
  Serial.print("AMMO=");Serial.print(a);
  Serial.print("HEALTH=");Serial.print(h);
Serial.begin(9600);
}

void loop() {
  
  // put your main code here, to run repeatedly:
if (digitalRead(12)== LOW)
{
  irsend.sendNEC(3899977530,32); //sends message in HEX 
Serial.println("CODE SENT"); //prints on serial monitor
digitalWrite(LED_BUILTIN,HIGH);// built-in led glows
irrecv.enableIRIn();
a--;
if(a==0)
{
  for(i=0;i<3;i++)
  {
    digitalWrite(b,HIGH);
    delay(500);
    digitalWrite(b,LOW);
    delay(500);
  }
  //lcd.print("END GAME");
  Serial.println("END GAME");
}
else
{
  /*lcd.print("AMMO=");lcd.print(a);
  lcd.print("HEALTH=");lcd.print(h);*/
  Serial.print("AMMO=");Serial.print(a);
  Serial.print("HEALTH=");Serial.print(h);
}
}
else
{
  if(irrecv.decode(&results))
{
  Serial.println(results.value,HEX);
  irrecv.resume();
  digitalWrite(LED_BUILTIN,HIGH);  
   h--;
  if(h==0)
{
  digitalWrite(b,HIGH);
  //lcd.print("END GAME");
   Serial.println("END GAME");
  
}
else
{
 /* lcd.print("AMMO=");lcd.print(a);
  lcd.print("HEALTH=");lcd.print(h);*/
   Serial.print("AMMO=");Serial.print(a);
  Serial.print("HEALTH=");Serial.print(h);
  
}
}
  digitalWrite(LED_BUILTIN,LOW);
}

}
