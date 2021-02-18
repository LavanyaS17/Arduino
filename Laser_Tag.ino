#include <IRremote.h>
#include <LiquidCrystal.h>
IRsend irsend;
int button = 4;
int buzzer = 2;
int vibrator = 11;
int ammo, i, health;
int recvPin = 12;  // CONNECT THE OUTPUT PIN OF THE IR RECIEVER TO THIS PIN
const int rs = 10, en = 9, d4 = 8, d5 =7, d6 = 6, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
IRrecv irrecv(recvPin);
decode_results results;
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  ammo = 100;
  health = 20;
  lcd.begin(16, 2);
  pinMode(button, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  pinMode(vibrator, OUTPUT);
  irrecv.enableIRIn();
  Serial.println("AMMO="); Serial.println(ammo);
  Serial.println("HEALTH="); Serial.println(health);
  lcd.setCursor(0,0);
  lcd.print("AMMO=");lcd.print(ammo);
  lcd.setCursor(0,1);
  lcd.print("HEALTH=");lcd.print(health);
}
void loop()
{
  // put your main code here, to run repeatedly:
  if (digitalRead(button) == LOW)
  {
    digitalWrite(vibrator, HIGH);
    irsend.sendNEC(0xAAAAAAAA, 32); //sends message in HEX
    Serial.println("CODE SENT"); //prints on serial monitor
    digitalWrite(LED_BUILTIN, HIGH); // built-in led glows
    irrecv.enableIRIn();
    ammo--;
    if (ammo == 0)
    {
      digitalWrite(vibrator, LOW);
      Serial.print("END GAME");
      for (i = 0; i < 3; i++)
      {
        digitalWrite(buzzer, HIGH);
        delay(500);
        digitalWrite(buzzer, LOW);
        delay(500);
      }
    }
    else
    {
      Serial.print("AMMO="); Serial.println(ammo);
      Serial.print("HEALTH="); Serial.println(health);
      lcd.setCursor(0,0);
      lcd.print("AMMO=");lcd.print(ammo);
      lcd.setCursor(0,1);
      lcd.print("HEALTH=");lcd.print(health);
    }
  }
  else
  {
    digitalWrite(vibrator, LOW);
    if (irrecv.decode(&results))
    {
      if (results.value == 3149642683)
      {
        health--;
        Serial.println(results.value, HEX);
        digitalWrite(LED_BUILTIN, HIGH);
        if (health == 0)
        {
          Serial.print("END GAME");
          digitalWrite(buzzer, HIGH);
        }
        else
        {
          Serial.print("AMMO="); Serial.println(ammo);
          Serial.print("HEALTH="); Serial.println(health);
          lcd.setCursor(0,0);
          lcd.print("AMMO=");lcd.print(ammo);
          lcd.setCursor(0,1);
          lcd.print("HEALTH=");lcd.print(health);
        }
        irrecv.resume();
      }
    }
    digitalWrite(LED_BUILTIN, LOW);
  }
}
