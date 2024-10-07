#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
LiquidCrystal_I2C lcd(0x27,16,2);
#include <Servo.h>
Servo myservo;
int pos = 0;
char Incoming_value = 0;
                
void setup() 
{
  Serial.begin(9600);   
  lcd.init();                // Initiate the LCD
  lcd.backlight();           // Initiate backlight ON
  lcd.setCursor(0,0);             // Point the cursor in first row first column
  lcd.print("ELECTRONIC SAFE");               //Text to be displayed
  lcd.setCursor(1,1);                
  pinMode(13, OUTPUT); 
  myservo.attach(7);      
}

void loop()
{
  if(Serial.available() > 0)  
  {
    Incoming_value = Serial.read();      
    Serial.print(Incoming_value);        
    Serial.print("\n");        
    if(Incoming_value == '1') 
       {     
        digitalWrite(13, HIGH);  
      for (pos = 0; pos <= 90; pos += 1){
        myservo.write(pos);
        delay(15);}
      lcd.print("OPENED"); 
      delay(2000);
      clearLCDLine(1);
      //lcd.clear();     
        }
    else if(Incoming_value == '0')       
      {   
      digitalWrite(13, LOW);   
      for (pos = 90; pos >= 0; pos -= 1){
        myservo.write(pos);
          delay(15);}
      lcd.print("CLOSED"); 
      delay(2000);
      clearLCDLine(1);
      //lcd.clear();
      }
   }
   
 }   
 void clearLCDLine(int line)
{               
        lcd.setCursor(0,line);
        for(int n = 0; n < 20; n++) 
        {
                lcd.print(" ");
        }
}                         

