#include <EmonLib.h>
#include <LiquidCrystal.h>

EnergyMonitor emon1;

int currentPin = A1;              // Strāvmainim tiek piešķirta ieeja A1
double kilos = 0;
int peakPower = 0;
unsigned long startMillis;
unsigned long endMillis;
LiquidCrystal lcd(12,11,5,4,3,2);  // LCD ekrāna ieejas

void setup() 
{ 
  Serial.begin(9600);
  emon1.current(A1, 13.7);
  lcd.begin(16,2);              // Kolonnas, rindiņas priekš 16x2 LCD ekrāna
  lcd.clear();
  lcd.setCursor(0,0);           // Pirmās rindiņas sākums
  lcd.print("Ulda Katlapa");
  lcd.setCursor(0,1);           // Otrās rindiņas sākums
  lcd.print("Vatmetrs");
  startMillis = millis();
}

void loop() 
{
  double Irms = emon1.calcIrms(1480);  // Tiek aprēķināta strāva izmantojot EmonLib.h
  double Prms = Irms*230.0;
  Serial.print(Prms);           // Aktīvā jauda
  Serial.print(" ");
  Serial.println(Irms);               // Strāva
  if(Irms <= 0.02)
  {
    Irms = 0;
    Prms = 0;
  }
  delay (2000);
  lcd.clear();
  lcd.setCursor(0,0);           // Uz LCD ekrāna parāda iegūtos datus
  lcd.print(Irms);
  lcd.print("A");
  lcd.setCursor(0,1);
  lcd.print(Prms);
  lcd.print("W");
}
