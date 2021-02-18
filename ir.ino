#include <IRremote.h>
IRsend irsend;
int i;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(LED_BUILTIN,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
irsend.sendNEC(3899977530,32); //sends message in HEX 
Serial.println("CODE SENT"); //prints on serial monitor
for(i=1;i<=3;i++)
{
digitalWrite(LED_BUILTIN,HIGH);// built-in led glows
delay(100);
}
}
