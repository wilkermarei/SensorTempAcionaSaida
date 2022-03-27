#include <OneWire.h>
#include <DallasTemperature.h>
#include <LCD_I2C.h>

//LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
LCD_I2C lcd(0x27,16,2); // Default address of most PCF8574 modules, change according

#define entrada_temp_1 3

#define botao_liga_bomba 10

#define saida_liga_bomba 7

bool estado_botao_liga_bomba;
bool estado_saida_liga_bomba;

float temperatura_atual = 0;


OneWire oneWire(entrada_temp_1);
DallasTemperature sensors(&oneWire);



void setup()
{
  // initialize the lcd
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  // setcursor (col,lin)
  //inicializa sensor
  sensors.begin();


pinMode(saida_liga_bomba,OUTPUT);
pinMode(botao_liga_bomba,INPUT);
  

lcd.setCursor(0,0);
lcd.print("Temp Sensor Bomb");
//         01234567890123456

lcd.setCursor(5,1);
lcd.print(sensors.getDeviceCount(),DEC);
}

void loop()
{

    //le temperatura do sensor
   sensors.requestTemperatures();
   temperatura_atual = sensors.getTempCByIndex(0);
   lcd.setCursor(0,1);
   lcd.print(temperatura_atual,1);

   estado_botao_liga_bomba = digitalRead(botao_liga_bomba);

   if (temperatura_atual>40) 
   {
    digitalWrite(saida_liga_bomba,LOW);

    if (estado_botao_liga_bomba == 1)
      {
      digitalWrite(saida_liga_bomba,HIGH);     
      }
   }
  
   if (temperatura_atual<40)
   {
    digitalWrite(saida_liga_bomba,HIGH);
       
       if (estado_botao_liga_bomba == 1)
        {
        digitalWrite(saida_liga_bomba,LOW);     
        }
   }
    lcd.setCursor(12,1);
    lcd.print(estado_botao_liga_bomba);
   
}