//Update 1.2 
// Operation keep the banana plant alive for winter break
// Change made to water for 1 minute every 24 hours
// 

//Update 1.1:
//  Change watering time to 5 sec
//  Raise sensor rating to 950
//  additional test code to trigger watering

//Read potentiameter value from analog input A0, A3 and output 
//  value to LCD
//  Relay pin 13, active high
//    - Love, past Kevin Kawecki



#include <LiquidCrystal.h>

#define CH1 13

//sensor value to indicate water
#define WATER_VALUE 1000
//minutes waited between watering
#define WATER_AFTER 1440
//watering time in seconds
#define WATER_TIME 10

int potPin = A0;    // spot pin
int potValue = 0;  // variable to store the value coming from the sensor
int sensorPin = A2;
int sensorValue = 0;
int count = 0;        //counter variable.. don't print too much kid. 
int waterCount = 0;   //control time watering

//hilo memory
int high = 0;
int low = 1023;

//clock memory
int milli = 0;
int hours = 0;
int minutes = 0;
int seconds = 0;

//water memory
bool waterDiff = false;
int waterHours = 0;
int waterMinutes = 0;
int waterSeconds = 0;
int waterTime = 0;

//string 
int temp;
char clockPrint[16];

//lcd pin declarations
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  pinMode(CH1, OUTPUT);
  digitalWrite(CH1, LOW);
}

//function to print default screen
void base()
{
  //print value
  lcd.setCursor(0,0); 
  lcd.print("Sensor : Hi : Lo");
  lcd.setCursor(0, 1);
  lcd.print(sensorValue);
  lcd.setCursor(6, 1);
  lcd.print(" :");
  lcd.print(high);
  lcd.print(" :");
  lcd.print(low);
  return;
}

//print clock screen
void printClock()
{
  lcd.setCursor(0,0);
  lcd.print("  Run Time");
  lcd.setCursor(4, 1);
  temp = sprintf(clockPrint, "%02d:%02d:%02d", hours, minutes, seconds);
  lcd.print(clockPrint);
}

//show last watering
void lastWater()
{
  lcd.setCursor(0,0);
  lcd.print("Last water:");
  lcd.setCursor(4, 1);
  temp = sprintf(clockPrint, "%02d:%02d:%02d", waterHours, waterMinutes, waterSeconds);
  lcd.print(clockPrint);
  
}

//show reset has happened
void displayReset()
{
  lcd.setCursor(0,0);
  lcd.print("Reset All");
  lcd.setCursor(4, 1);
  temp = sprintf(clockPrint, "%02d:%02d:%02d", hours, minutes, seconds);
  lcd.print(clockPrint);
}

void loop() {

  seconds++;
    if (seconds >= 60)
    {
      seconds = 0;
      minutes++;
    }
    if (minutes >= 60)
    {
      minutes = 0;
      hours++;
    }
    if (hours >= 24)
    {
      hours = 0;
    }
    milli = 0;

    if (waterDiff)
      waterTime++;

  //watering math
  //watering process
  
  //if (sensorValue > WATER_VALUE && ((minutes - waterMinutes) >= WATER_AFTER))// || potValue > 1000)

  //Change made to water for a minute every 24 hrs
  if (minutes == 0 && hours == 0 && seconds <= WATER_TIME)
  {
    digitalWrite(CH1, HIGH);
  }
  else 
  {
    digitalWrite(CH1, LOW);
  }

  //sensor and lcd update 
  if (1)//(count >= 4000)
  {
    // let pot reset
    potValue = analogRead(potPin);
    if (potValue < 100)
    {
      high = 0;
      low = 1023;
    }
    
    //read sensor
    sensorValue = analogRead(sensorPin);
    
    //high low detection
    if (sensorValue > high)
    {
      high = sensorValue;
    }
    if (sensorValue < low)
    {
      low = sensorValue;
    }
    
    //clear current value
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("                ");

    //turn display on and off
    if (potValue >= 1000)
    {
      lcd.noDisplay();
    }
    else 
    {
      lcd.display();
    }
    
    //display switch case
    if (potValue > 700)// && potValue < 1000)
    {
      base();
    }
    else if (potValue <= 700 && potValue >= 400)
    {
      printClock();
    }
    else if (potValue <= 400 && potValue >= 100)
    {
      lastWater();
    }
    else
    {
      displayReset();
      high = 0;
      low = 1023;
      milli = 0;
      seconds = 0;
      minutes = 0;
      hours = 0;
    }
    
    count = 0;
  }
  milli++;
  count++;
  delay(1000);
}
