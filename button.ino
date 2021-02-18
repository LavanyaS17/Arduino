#include <IRremote.h>
#include <LiquidCrystal.h>
IRsend irsend;
int button=12;
int a;
int h;
int recvPin = 7;  // CONNECT THE OUTPUT PIN OF THE IR RECIEVER TO THIS PIN
const int rs = 8, en = 11, d4 = 5, d5 = 4, d6 = 6, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
IRrecv irrecv(recvPin);
decode_results results;
void setup() {
  // put your setup code here, to run once:
  a=100;h=20;
   lcd.begin(16, 2);
pinMode(12,INPUT_PULLUP);
irrecv.enableIRIn();
 lcd.print("AMMO=");lcd.print(a);
  lcd.print("HEALTH=");lcd.print(h);
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
  lcd.print("END GAME");
}
else
{
  lcd.print("AMMO=");lcd.print(a);
  lcd.print("HEALTH=");lcd.print(h);
}

 }
else
{
 // Serial.println("in else");
  if(irrecv.decode(&results))
{
  Serial.println(results.value,HEX);
  irrecv.resume();
  digitalWrite(LED_BUILTIN,HIGH);
  h--;
  if(h==0)
{
  lcd.print("END GAME");
}
else
{
  lcd.print("AMMO=");lcd.print(a);
  lcd.print("HEALTH=");lcd.print(h);
}
  
  //delay(500);
}
  digitalWrite(LED_BUILTIN,LOW);
}

}
