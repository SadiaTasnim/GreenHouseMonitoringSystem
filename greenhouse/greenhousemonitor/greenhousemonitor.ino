#define LDRpin A15
#define light1 31
#define light2 32
#define light3 33
#define light4 34 
#define light5 35

#define dhtpin A14
#define spray 37
#define blinkingtime 6
#define fan1 A2
#define fan2 A3
#define fan3 A7
#define fan4 A6

#define soilmotor 3
#define soil A13

#define sw1 51
#define sw2 52
#define sw3 53
#define led1 44
#define led2 45
#define led3 46


#include <LiquidCrystal.h>
#include <dht11.h>
#include <Servo.h>

//LCD
const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//LDR
int ldr = LDRpin;
float valueldr=0;

//WaterLevel
int motorPin= A0; 
int x, y,z;

//DHT11 
dht11 dht;
Servo soilservo;

int Fan1 = fan1;
int Fan2 = fan2;
int Fan3 = fan3;
int Fan4 = fan4;
int F1,F2,F3,F4 ;

void setup() 
{
 Serial.begin(9600);
 //LCD
 lcd.begin(16, 2);
 lcd.setCursor(0, 1);
 lcd.clear();
 
 //LDR BULB
  pinMode(light1, OUTPUT);
  pinMode(light2, OUTPUT);
  pinMode(light3, OUTPUT);
  pinMode(light4, OUTPUT);
  pinMode(light5, OUTPUT);
  digitalWrite(light1, LOW);
  digitalWrite(light2, LOW);
  digitalWrite(light3, LOW);
  digitalWrite(light4, LOW);
  digitalWrite(light5, LOW);

  //DHT11
  pinMode(spray, OUTPUT);
  digitalWrite(spray, LOW);

  pinMode(fan1, OUTPUT);
  pinMode(fan2, OUTPUT);
  pinMode(fan3, OUTPUT);
  pinMode(fan4, OUTPUT);
   
 
  //soil
  soilservo.attach(soilmotor);

  //Water level
  pinMode(motorPin, OUTPUT);
  pinMode(sw1, INPUT);
  pinMode(sw2, INPUT);
  pinMode(sw3, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void loop() {
  //LDR
  lcd.setCursor(0, 0);
  lcd.print("Light Sensitivity : ");
  lcd.setCursor(0,1);
  valueldr = analogRead(ldr);
  lcd.print(valueldr);
  lcd.setCursor(0, 0);
  delay(2000);
  lcd.clear();
 if(valueldr <100.00)
  { 
    lcd.print("TURN ON 5 LIGHTS");
    digitalWrite(light1, HIGH);
    digitalWrite(light2, HIGH);
    digitalWrite(light3, HIGH);
    digitalWrite(light4, HIGH);
    digitalWrite(light5, HIGH);
    delay(2000);
  }
  else if(valueldr <200.00)
  {
    lcd.print("TURN ON 3 LIGHTS");
    digitalWrite(light1, HIGH);
    digitalWrite(light2, LOW);
    digitalWrite(light3, HIGH);
    digitalWrite(light4, LOW);
    digitalWrite(light5, HIGH); 
    delay(2000);
  }
  else if(valueldr <400.00)
  {
    lcd.print("TURN ON 2 LIGHTS");
    digitalWrite(light1, HIGH);
    digitalWrite(light2, LOW);
    digitalWrite(light3, LOW);
    digitalWrite(light4, LOW);
    digitalWrite(light5, HIGH); 
    delay(2000);
  }
  else if(valueldr <500.00)
  {
    lcd.print("TURN ON 1 LIGHTS");
    digitalWrite(light1, LOW);
    digitalWrite(light2, LOW);
    digitalWrite(light3, HIGH);
    digitalWrite(light4, LOW);
    digitalWrite(light5, LOW); 
    delay(2000);
  }
  else
  {
    lcd.print("LIGHTS TURNED OFF");
    digitalWrite(light1, LOW);
    digitalWrite(light2, LOW);
    digitalWrite(light3, LOW);
    digitalWrite(light4, LOW);
    digitalWrite(light5, LOW); 
    delay(1000);
  } 
    digitalWrite(light1, LOW);
    digitalWrite(light2, LOW);
    digitalWrite(light3, LOW);
    digitalWrite(light4, LOW);
    digitalWrite(light5, LOW);
    lcd.clear();

  //DHT11 humidity
  dht.read(dhtpin);
  lcd.setCursor(0,0);
  int humidity = dht.humidity;
  int temp = dht.temperature;
  lcd.print("Temperature : ");
  lcd.print(temp);
  lcd.print("C ");
  lcd.setCursor(0,1);
  lcd.print("Humdity : ");
  lcd.print(humidity);
  lcd.print(" % ");
  delay(2000);
  lcd.clear();
  if (humidity<50)
  {
    lcd.print("Humidity is low");
    lcd.setCursor(0,1);
    lcd.print("Spray ON");
    int count= blinkingtime;
    
    while(count--)
    {
      digitalWrite(spray, HIGH);
      delay(100);
      digitalWrite(spray, LOW);
      delay(100);
      digitalWrite(spray, HIGH);
      delay(100);
    }
    delay(500);
  }
  else
  {
    lcd.print("Humidity normal");
    lcd.setCursor(0,1);
    lcd.print("Spray OFF");
    delay(2000);
  }
  digitalWrite(spray, LOW);
  lcd.clear();
  
  //DHT11 temp
 
  if (temp<20)
  {
    lcd.print("Temp is ");
    lcd.print(temp);
    lcd.print(" C.");
    lcd.setCursor(0,1);
    lcd.print("All fan OFF.");
    digitalWrite(Fan1, LOW);
    digitalWrite(Fan2, LOW);
    digitalWrite(Fan3, LOW);
    digitalWrite(Fan4, LOW);
    delay(5000);
  }
  else if (temp<30)
  {   
    //fan1
    lcd.print("Temp is ");
    lcd.print(temp);
    lcd.print(" C.");
    lcd.setCursor(0,1);
    lcd.print("2 FAN ON.");
    digitalWrite(Fan1, HIGH);
    digitalWrite(Fan2, HIGH);
    digitalWrite(Fan3, LOW);
    digitalWrite(Fan4, LOW);
    delay(5000);  
 
  }
  else if (temp<40)
  {
    //fan1 &fan4
    lcd.print("Temp is ");
    lcd.print(temp);
    lcd.print(" C.");
    lcd.setCursor(0,1);
    lcd.print("3 FAN ON.");
    digitalWrite(Fan1, HIGH);
    digitalWrite(Fan2, HIGH);
    digitalWrite(Fan3, HIGH);
    digitalWrite(Fan4, LOW);
    delay(5000);
    
 
  }
  else 
  {
    //all fan on
    lcd.print("Temp is ");
    lcd.print(temp);
    lcd.print(" C.");
    lcd.setCursor(0,1);
    lcd.print("All FAN ON");
    digitalWrite(Fan1, HIGH);
    digitalWrite(Fan2, HIGH);
    digitalWrite(Fan3, HIGH);
    digitalWrite(Fan4, HIGH);
    delay(5000);
 
  }
  lcd.clear();

    digitalWrite(Fan1, LOW);
    digitalWrite(Fan2, LOW);
    digitalWrite(Fan3, LOW);
    digitalWrite(Fan4, LOW);
  
 
 //BC547

 if (digitalRead(soil)==1)
 {
     lcd.clear();
     lcd.print("Low Soil Moisture.");
     lcd.setCursor(0,1);
     lcd.print("Motor turned ON."); 

     for(int i = 0; i <= 180; ++i)
    {
     
      soilservo.write(i);
      delay(20);
    }
    for(int i = 180; i >0; i--)
    {
      
      soilservo.write(i);
      delay(20);
    }
    delay(300);

        
 }
 if (digitalRead(soil)==0)
 {
     lcd.clear();
     lcd.print("Soil Moisture Normal.");
     lcd.setCursor(0,1);
     lcd.print("Motor turned OFF.");
     delay(2000);    
 }

 //WaterLevel
 x= digitalRead(sw1);
 y= digitalRead(sw2);
 z= digitalRead(sw3);

// if(x==HIGH && y==LOW && z== LOW)

if (z==HIGH && y==HIGH && x==HIGH)
   digitalWrite(led1,HIGH);
if (z==HIGH && y==HIGH && x==LOW)
   digitalWrite(led2,HIGH);
if (z==HIGH && x==LOW && y==LOW)
  digitalWrite(led3,HIGH);

if (z==HIGH && x==LOW && y==LOW)
 {
     lcd.clear();
     lcd.print("Low Water level.");
     lcd.setCursor(0,1);
     lcd.print("Motor turned ON.");
     digitalWrite(motorPin, HIGH);   
     delay(2000);
 }
  else if (z==HIGH && y==HIGH && x==LOW)
 {
     lcd.clear();
     lcd.print("Medium Water level.");
     lcd.setCursor(0,1);
     lcd.print("Motor is ON.");
     digitalWrite(motorPin, HIGH);
     delay(2000);
 }
 else if (z==HIGH && y==HIGH && x==HIGH)
 {
      lcd.clear();
     lcd.print("Water Tank Full.");
     lcd.setCursor(0,1);
     lcd.print("Motor is Off.");
     digitalWrite(motorPin, LOW);
   
     delay(2000);
 }
 else
 {
     lcd.clear();
     lcd.print("Water Tank Full.");
     lcd.setCursor(0,1);
     lcd.print("Motor is Off.");
     digitalWrite(motorPin, LOW);
   
     delay(2000);
 }
  digitalWrite(led1, LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
  digitalWrite(motorPin, LOW);

lcd.clear();
}
