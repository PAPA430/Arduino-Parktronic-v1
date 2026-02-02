#define PIN_TRIG 2
#define PIN_ECHO 3
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);

int red =10;
int blue =9;
int yellow=8;

long duration, cm;

int buzzerPin =7;



void setup(){
  Serial.begin (9600);
  //Светодиоды
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(yellow, OUTPUT);

  //Датчик расстояния
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

  //Buzzer
  pinMode(buzzerPin, OUTPUT);

  //LCD
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();

  
}

void loop(){

  // Сначала генерируем короткий импульс длительностью 2-5 микросекунд.
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(PIN_TRIG,HIGH);

  // Выставив высокий уровень сигнала, ждем около 10 микросекунд. В этот момент датчик будет посылать сигналы с частотой 40 КГц.
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  //  Время задержки акустического сигнала на эхолокаторе.
  duration=pulseIn(PIN_ECHO, HIGH);

  // Теперь осталось преобразовать время в расстояние
  cm=(duration/2)/29.1;

  Serial.print("Расстояние до объекта:");
  Serial.print(cm);
  Serial.println(" см.");
  // Задержка между измерениями для корректной работы скеча
  delay(1000);

  
  
  if (cm >=0 && cm<=15){
    digitalWrite(red, HIGH);
    digitalWrite(yellow, LOW);
    digitalWrite(blue, LOW);
    tone(buzzerPin, 3000); // G4
    
    
  }
  else if (cm>=15 && cm<=40){
    digitalWrite(red, LOW);
    digitalWrite(yellow, HIGH);
    digitalWrite(blue, LOW);
    tone(buzzerPin, 500); // D4
    
    
  }
  else {
    digitalWrite(blue, HIGH);
    digitalWrite(yellow, LOW);
    digitalWrite(red, LOW);
    noTone(buzzerPin);
   
  }
  //Настройка и передача показателей на дисплей!
  lcd.setCursor(0,0);
  lcd.print("Analog: ");
  lcd.print(cm);
  lcd.print(" cm ");
  delay(1000);  

    
}