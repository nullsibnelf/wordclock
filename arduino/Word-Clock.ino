
#include <Wire.h>
#include <DS3231.h>
#include <Adafruit_NeoPixel.h>

#define NeoPixelPin     12
#define StatusLed       13

#define NeoPixelAmount 144

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NeoPixelAmount, NeoPixelPin, NEO_GRB + NEO_KHZ800);
DS3231 Clock;

bool Century;
bool h12;
bool PM;

byte Temp1, Temp2, Temp3;

int led_brightness = 30;

int nr0 [7][5]={{0, 1, 1, 1, 0},
                {1, 0, 0, 0, 1},
                {1, 0, 0, 1, 1},
                {1, 0, 1, 0, 1},
                {1, 1, 0, 0, 1},
                {1, 0, 0, 0, 1},
                {0, 1, 1, 1, 0}};

int nr1 [7][5]={{0, 0, 1, 0, 0},
                {0, 1, 1, 0, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 1, 0, 0},
                {0, 1, 1, 1, 0}};

int nr2 [7][5]={{0, 1, 1, 1, 0},
                {1, 0, 0, 0, 1},
                {0, 0, 0, 0, 1},
                {0, 0, 0, 1, 0},
                {0, 0, 1, 0, 0},
                {0, 1, 0, 0, 0},
                {1, 1, 1, 1, 1}};

int nr3 [7][5]={{0, 1, 1, 1, 0},
                {1, 0, 0, 0, 1},
                {0, 0, 0, 0, 1},
                {0, 0, 0, 1, 0},
                {0, 0, 0, 0, 1},
                {1, 0, 0, 0, 1},
                {0, 1, 1, 1, 0}};

int nr4 [7][5]={{1, 0, 0, 0, 1},
                {1, 0, 0, 0, 1},
                {1, 0, 0, 0, 1},
                {1, 1, 1, 1, 1},
                {0, 0, 0, 0, 1},
                {0, 0, 0, 0, 1},
                {0, 0, 0, 0, 1}};

int nr5 [7][5]={{1, 1, 1, 1, 1},
                {1, 0, 0, 0, 0},
                {1, 0, 0, 0, 0},
                {1, 1, 1, 1, 1},
                {0, 0, 0, 0, 1},
                {0, 0, 0, 0, 1},
                {1, 1, 1, 1, 1}};

int nr6 [7][5]={{0, 1, 1, 1, 0},
                {1, 0, 0, 0, 1},
                {1, 0, 0, 0, 0},
                {1, 1, 1, 1, 0},
                {1, 0, 0, 0, 1},
                {1, 0, 0, 0, 1},
                {0, 1, 1, 1, 0}};

int nr7 [7][5]={{1, 1, 1, 1, 1},
                {0, 0, 0, 0, 1},
                {0, 0, 0, 0, 1},
                {0, 0, 0, 1, 0},
                {0, 0, 1, 0, 0},
                {0, 1, 0, 0, 0},
                {1, 0, 0, 0, 0}};

int nr8 [7][5]={{0, 1, 1, 1, 0},
                {1, 0, 0, 0, 1},
                {1, 0, 0, 0, 1},
                {0, 1, 1, 1, 0},
                {1, 0, 0, 0, 1},
                {1, 0, 0, 0, 1},
                {0, 1, 1, 1, 0}};

int nr9 [7][5]={{0, 1, 1, 1, 0},
                {1, 0, 0, 0, 1},
                {1, 0, 0, 0, 1},
                {0, 1, 1, 1, 1},
                {0, 0, 0, 0, 1},
                {0, 0, 0, 0, 1},
                {0, 1, 1, 1, 0}};




void setup() 
{
  pinMode(StatusLed,   OUTPUT);
  pinMode(NeoPixelPin, OUTPUT);
  pixels.begin();                             // Initialisierung der NeoPixel
  cls();
  Serial.begin(9600);                         // setup serial for debugging
  Wire.begin();

  Serial.println("Enter config-menue?   y / n");
  get_serial(1, 20);
  if (Temp3 == 170)                           // "y"
    serial_config();
}




void loop()
{
  print_TimeDateTemp(); 

  
  int hour = Clock.getHour(h12, PM);
  int minute = Clock.getMinute();

  if (hour == 6 and minute == 55)
  {
    coffee_mug(0);
    delay(5000);
  }
  else if (hour == 6 and minute == 56)
  {
    coffee_mug(1);
    delay(5000);
  }
  else if (hour == 6 and minute == 57)
  {
    coffee_mug(2);
    delay(5000);
  }
  else if (hour == 6 and minute == 58)
  {
    coffee_mug(3);
    delay(5000);
  }
  else if (hour == 6 and minute == 59)
  {
    coffee_mug(4);
    delay(5000);
  }
  else if (hour == 7 and minute <= 05)
  {
    coffee_mug(5);
    delay(5000);
  }
  else
  {
    show_time_digital(led_brightness, 2000);
    //
    show_wordclock(led_brightness, led_brightness, led_brightness);
    delay(18000);
  }

  serial_debug();
}




void serial_config (void)
{
  Serial.println("Enter LED Brightness");   get_serial(2, 10);    led_brightness = Temp3;
  Serial.println("Enter Day");              get_serial(2, 10);    Clock.setDate(Temp3);
  Serial.println("Enter Month");            get_serial(2, 10);    Clock.setMonth(Temp3);
  Serial.println("Enter Year");             get_serial(2, 10);    Clock.setYear(Temp3);
  Serial.println("Enter Hour");             get_serial(2, 10);    Clock.setHour(Temp3);
  Serial.println("Enter Minute");           get_serial(2, 10);    Clock.setMinute(Temp3);
  Serial.println("Enter Second");           get_serial(2, 10);    Clock.setSecond(Temp3);
}




void serial_debug (void)
{
  while (Serial.available() > 0)
  {
    char buffer__[2];
    buffer__[0] = Serial.read();
    buffer__[1] = '\0';
    //Serial.println(buffer__);
    if (buffer__[0] == 'b')
    {
      Serial.println("Enter LED Brightness");   get_serial(2, 10);    led_brightness = Temp3;
    }
    if (buffer__[0] == 't')
    {
      Serial.println("Enter Hour");             get_serial(2, 10);    Clock.setHour(Temp3);
      Serial.println("Enter Minute");           get_serial(2, 10);    Clock.setMinute(Temp3);
      Serial.println("Enter Second");           get_serial(2, 10);    Clock.setSecond(Temp3);
    }
    if (buffer__[0] == 'd')
    {
      Serial.println("Enter Day");              get_serial(2, 10);    Clock.setDate(Temp3);
      Serial.println("Enter Month");            get_serial(2, 10);    Clock.setMonth(Temp3);
      Serial.println("Enter Year");             get_serial(2, 10);    Clock.setYear(Temp3);
    }
  }
}




void print_ (int val[7][5], int offset, int  r, int g, int b)
{  
  for (int i=0; i<5; i++)
  {
    for (int ii=0; ii<7; ii++)
    {
      if (val[ii][i] == 1)
        pixels.setPixelColor(offset + i*12 + (6-ii), pixels.Color(r, g, b));
      else
        pixels.setPixelColor(offset + i*12 + (6-ii), pixels.Color(0, 0, 0));
    }
  }
  pixels.show();
}




void cls (void)
{
  for (int i=0; i< NeoPixelAmount; i++)
    pixels.setPixelColor(i, pixels.Color(0,0,0));
  pixels.show();
}




void show_wordclock (int r, int g, int b)
{
  int my_hour = Clock.getHour(h12, PM);
  int my_minute = Clock.getMinute();

  cls();
  
  pixels.setPixelColor( 11, pixels.Color(r,g,b)); // E
  pixels.setPixelColor( 23, pixels.Color(r,g,b)); // s
  
  pixels.setPixelColor( 47, pixels.Color(r,g,b)); // i
  pixels.setPixelColor( 59, pixels.Color(r,g,b)); // s
  pixels.setPixelColor( 71, pixels.Color(r,g,b)); // t

  switch (my_minute)
  {
    case  0:
    case  1:
    case  2:
    case  3:
    case  4:
              pixels.setPixelColor(  84, pixels.Color(r,g,b)); // U
              pixels.setPixelColor(  96, pixels.Color(r,g,b)); // h
              pixels.setPixelColor( 108, pixels.Color(r,g,b)); // r
              break;
    case  5:
    case  6:
    case  7:
    case  8:
    case  9:
              pixels.setPixelColor(  22, pixels.Color(r,g,b)); // f
              pixels.setPixelColor(  34, pixels.Color(r,g,b)); // ü
              pixels.setPixelColor(  46, pixels.Color(r,g,b)); // n
              pixels.setPixelColor(  58, pixels.Color(r,g,b)); // f
              
              pixels.setPixelColor(  80, pixels.Color(r,g,b)); // n
              pixels.setPixelColor(  92, pixels.Color(r,g,b)); // a
              pixels.setPixelColor( 104, pixels.Color(r,g,b)); // c
              pixels.setPixelColor( 116, pixels.Color(r,g,b)); // h
              break;
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
              pixels.setPixelColor(  70, pixels.Color(r,g,b)); // z
              pixels.setPixelColor(  82, pixels.Color(r,g,b)); // e
              pixels.setPixelColor(  94, pixels.Color(r,g,b)); // h
              pixels.setPixelColor( 106, pixels.Color(r,g,b)); // n
              
              pixels.setPixelColor(  80, pixels.Color(r,g,b)); // n
              pixels.setPixelColor(  92, pixels.Color(r,g,b)); // a
              pixels.setPixelColor( 104, pixels.Color(r,g,b)); // c
              pixels.setPixelColor( 116, pixels.Color(r,g,b)); // h
              break;
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
              pixels.setPixelColor(  22, pixels.Color(r,g,b)); // f
              pixels.setPixelColor(  34, pixels.Color(r,g,b)); // ü
              pixels.setPixelColor(  46, pixels.Color(r,g,b)); // n
              pixels.setPixelColor(  58, pixels.Color(r,g,b)); // f
              pixels.setPixelColor(  70, pixels.Color(r,g,b)); // z
              pixels.setPixelColor(  82, pixels.Color(r,g,b)); // e
              pixels.setPixelColor(  94, pixels.Color(r,g,b)); // h
              pixels.setPixelColor( 106, pixels.Color(r,g,b)); // n
              
              pixels.setPixelColor(  80, pixels.Color(r,g,b)); // n
              pixels.setPixelColor(  92, pixels.Color(r,g,b)); // a
              pixels.setPixelColor( 104, pixels.Color(r,g,b)); // c
              pixels.setPixelColor( 116, pixels.Color(r,g,b)); // h
              break;
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
              pixels.setPixelColor(  69, pixels.Color(r,g,b)); // z
              pixels.setPixelColor(  81, pixels.Color(r,g,b)); // w
              pixels.setPixelColor(  93, pixels.Color(r,g,b)); // a
              pixels.setPixelColor( 105, pixels.Color(r,g,b)); // n
              pixels.setPixelColor( 117, pixels.Color(r,g,b)); // z
              pixels.setPixelColor( 129, pixels.Color(r,g,b)); // i
              pixels.setPixelColor( 141, pixels.Color(r,g,b)); // g
              
              pixels.setPixelColor(  80, pixels.Color(r,g,b)); // n
              pixels.setPixelColor(  92, pixels.Color(r,g,b)); // a
              pixels.setPixelColor( 104, pixels.Color(r,g,b)); // c
              pixels.setPixelColor( 116, pixels.Color(r,g,b)); // h
              break;
    case 25:
    case 26:
    case 27:
    case 28:
    case 29:
              pixels.setPixelColor(  22, pixels.Color(r,g,b)); // f
              pixels.setPixelColor(  34, pixels.Color(r,g,b)); // ü
              pixels.setPixelColor(  46, pixels.Color(r,g,b)); // n
              pixels.setPixelColor(  58, pixels.Color(r,g,b)); // f
              pixels.setPixelColor( 118, pixels.Color(r,g,b)); // u
              pixels.setPixelColor( 130, pixels.Color(r,g,b)); // n
              pixels.setPixelColor( 142, pixels.Color(r,g,b)); // d
              pixels.setPixelColor(  69, pixels.Color(r,g,b)); // z
              pixels.setPixelColor(  81, pixels.Color(r,g,b)); // w
              pixels.setPixelColor(  93, pixels.Color(r,g,b)); // a
              pixels.setPixelColor( 105, pixels.Color(r,g,b)); // n
              pixels.setPixelColor( 117, pixels.Color(r,g,b)); // z
              pixels.setPixelColor( 129, pixels.Color(r,g,b)); // i
              pixels.setPixelColor( 141, pixels.Color(r,g,b)); // g
              
              pixels.setPixelColor(  80, pixels.Color(r,g,b)); // n
              pixels.setPixelColor(  92, pixels.Color(r,g,b)); // a
              pixels.setPixelColor( 104, pixels.Color(r,g,b)); // c
              pixels.setPixelColor( 116, pixels.Color(r,g,b)); // h
              break;    
    case 30:
    case 31:
    case 32:
    case 33:
    case 34:
    case 35:
    case 36:
    case 37:
    case 38:
    case 39:
              pixels.setPixelColor(  21, pixels.Color(r,g,b)); // h
              pixels.setPixelColor(  33, pixels.Color(r,g,b)); // a
              pixels.setPixelColor(  45, pixels.Color(r,g,b)); // l
              pixels.setPixelColor(  57, pixels.Color(r,g,b)); // b
              my_hour++;
              break;
    case 40:
    case 41:
    case 42:
    case 43:
    case 44:
              pixels.setPixelColor(  69, pixels.Color(r,g,b)); // z
              pixels.setPixelColor(  81, pixels.Color(r,g,b)); // w
              pixels.setPixelColor(  93, pixels.Color(r,g,b)); // a
              pixels.setPixelColor( 105, pixels.Color(r,g,b)); // n
              pixels.setPixelColor( 117, pixels.Color(r,g,b)); // z
              pixels.setPixelColor( 129, pixels.Color(r,g,b)); // i
              pixels.setPixelColor( 141, pixels.Color(r,g,b)); // g
              
              pixels.setPixelColor(  44, pixels.Color(r,g,b)); // v
              pixels.setPixelColor(  56, pixels.Color(r,g,b)); // o
              pixels.setPixelColor(  68, pixels.Color(r,g,b)); // r
              my_hour++;
              break;
    case 45:
    case 46:
    case 47:
    case 48:
    case 49:
              pixels.setPixelColor(  22, pixels.Color(r,g,b)); // f
              pixels.setPixelColor(  34, pixels.Color(r,g,b)); // ü
              pixels.setPixelColor(  46, pixels.Color(r,g,b)); // n
              pixels.setPixelColor(  58, pixels.Color(r,g,b)); // f
              pixels.setPixelColor(  70, pixels.Color(r,g,b)); // z
              pixels.setPixelColor(  82, pixels.Color(r,g,b)); // e
              pixels.setPixelColor(  94, pixels.Color(r,g,b)); // h
              pixels.setPixelColor( 106, pixels.Color(r,g,b)); // n
              
              pixels.setPixelColor(  44, pixels.Color(r,g,b)); // v
              pixels.setPixelColor(  56, pixels.Color(r,g,b)); // o
              pixels.setPixelColor(  68, pixels.Color(r,g,b)); // r
              my_hour++;
              break;
    case 50:
    case 51:
    case 52:
    case 53:
    case 54:
              pixels.setPixelColor(  70, pixels.Color(r,g,b)); // z
              pixels.setPixelColor(  82, pixels.Color(r,g,b)); // e
              pixels.setPixelColor(  94, pixels.Color(r,g,b)); // h
              pixels.setPixelColor( 106, pixels.Color(r,g,b)); // n
              
              pixels.setPixelColor(  44, pixels.Color(r,g,b)); // v
              pixels.setPixelColor(  56, pixels.Color(r,g,b)); // o
              pixels.setPixelColor(  68, pixels.Color(r,g,b)); // r
              my_hour++;
              break;
    case 55:
    case 56:
    case 57:
    case 58:
    case 59:
              pixels.setPixelColor(  22, pixels.Color(r,g,b)); // f
              pixels.setPixelColor(  34, pixels.Color(r,g,b)); // ü
              pixels.setPixelColor(  46, pixels.Color(r,g,b)); // n
              pixels.setPixelColor(  58, pixels.Color(r,g,b)); // f
              
              pixels.setPixelColor(  44, pixels.Color(r,g,b)); // v
              pixels.setPixelColor(  56, pixels.Color(r,g,b)); // o
              pixels.setPixelColor(  68, pixels.Color(r,g,b)); // r
              my_hour++;
              break;
  }

  switch (my_hour)
  {
    case 1:
    case 13:
              pixels.setPixelColor(  7, pixels.Color(r,g,b)); // e
              pixels.setPixelColor( 19, pixels.Color(r,g,b)); // i
              pixels.setPixelColor( 31, pixels.Color(r,g,b)); // n
              if (my_minute > 4)
                pixels.setPixelColor( 43, pixels.Color(r,g,b)); // s
              break;
    case 2:
    case 14:
              pixels.setPixelColor( 65, pixels.Color(r,g,b)); // z
              pixels.setPixelColor( 77, pixels.Color(r,g,b)); // w
              pixels.setPixelColor( 89, pixels.Color(r,g,b)); // e
              pixels.setPixelColor(101, pixels.Color(r,g,b)); // i
              break;
    case 3:
    case 15:
              pixels.setPixelColor( 90, pixels.Color(r,g,b)); // d
              pixels.setPixelColor(102, pixels.Color(r,g,b)); // r
              pixels.setPixelColor(114, pixels.Color(r,g,b)); // e
              pixels.setPixelColor(126, pixels.Color(r,g,b)); // i
              break;
    case 4:
    case 16:
              pixels.setPixelColor( 67, pixels.Color(r,g,b)); // v
              pixels.setPixelColor( 79, pixels.Color(r,g,b)); // i
              pixels.setPixelColor( 91, pixels.Color(r,g,b)); // e
              pixels.setPixelColor(103, pixels.Color(r,g,b)); // r
              break;
    case 5:
    case 17:
              pixels.setPixelColor( 14, pixels.Color(r,g,b)); // f
              pixels.setPixelColor( 26, pixels.Color(r,g,b)); // ü
              pixels.setPixelColor( 38, pixels.Color(r,g,b)); // n
              pixels.setPixelColor( 50, pixels.Color(r,g,b)); // f
              break;
    case 6:
    case 18:
              pixels.setPixelColor( 75, pixels.Color(r,g,b)); // s
              pixels.setPixelColor( 87, pixels.Color(r,g,b)); // e
              pixels.setPixelColor( 99, pixels.Color(r,g,b)); // c
              pixels.setPixelColor(111, pixels.Color(r,g,b)); // h
              pixels.setPixelColor(123, pixels.Color(r,g,b)); // s
              break;
    case 7:
    case 19:
              pixels.setPixelColor(  4, pixels.Color(r,g,b)); // s
              pixels.setPixelColor( 16, pixels.Color(r,g,b)); // i
              pixels.setPixelColor( 28, pixels.Color(r,g,b)); // e
              pixels.setPixelColor( 40, pixels.Color(r,g,b)); // b
              pixels.setPixelColor( 52, pixels.Color(r,g,b)); // e
              pixels.setPixelColor( 64, pixels.Color(r,g,b)); // n
              break;
    case 8:
    case 20:
              pixels.setPixelColor( 18, pixels.Color(r,g,b)); // a
              pixels.setPixelColor( 30, pixels.Color(r,g,b)); // c
              pixels.setPixelColor( 42, pixels.Color(r,g,b)); // h
              pixels.setPixelColor( 54, pixels.Color(r,g,b)); // t
              break;
    case 9:
    case 21:
              pixels.setPixelColor( 88, pixels.Color(r,g,b)); // n
              pixels.setPixelColor(100, pixels.Color(r,g,b)); // e
              pixels.setPixelColor(112, pixels.Color(r,g,b)); // u
              pixels.setPixelColor(124, pixels.Color(r,g,b)); // n
              break;
    case 10:
    case 22:
              pixels.setPixelColor( 13, pixels.Color(r,g,b)); // z
              pixels.setPixelColor( 25, pixels.Color(r,g,b)); // e
              pixels.setPixelColor( 37, pixels.Color(r,g,b)); // h
              pixels.setPixelColor( 49, pixels.Color(r,g,b)); // n
              break;
    case 11:
    case 23:
              pixels.setPixelColor( 12, pixels.Color(r,g,b)); // e
              pixels.setPixelColor( 24, pixels.Color(r,g,b)); // l
              pixels.setPixelColor( 36, pixels.Color(r,g,b)); // f
              break;
    case 0:
    case 12:
    case 24:
              pixels.setPixelColor( 61, pixels.Color(r,g,b)); // z
              pixels.setPixelColor( 73, pixels.Color(r,g,b)); // w
              pixels.setPixelColor( 85, pixels.Color(r,g,b)); // ö
              pixels.setPixelColor( 97, pixels.Color(r,g,b)); // l
              pixels.setPixelColor(109, pixels.Color(r,g,b)); // f
              break;
  }
  pixels.show();
}




void show_time_digital (int helligkeit, int pause_ms)
{
  cls();
  print_2digit(Clock.getHour(h12, PM), helligkeit, helligkeit, helligkeit);
  pixels.setPixelColor(  0, pixels.Color(helligkeit, helligkeit, helligkeit));
  pixels.setPixelColor( 11, pixels.Color(0,0,0));
  pixels.setPixelColor(132, pixels.Color(0,0,0));
  pixels.setPixelColor(143, pixels.Color(0,0,0));
  pixels.show();
  delay(pause_ms);
  
  print_2digit(Clock.getMinute(), helligkeit, helligkeit, helligkeit);
  pixels.setPixelColor(  0, pixels.Color(0,0,0));
  pixels.setPixelColor( 11, pixels.Color(0,0,0));
  pixels.setPixelColor(132, pixels.Color(helligkeit, helligkeit, helligkeit));
  pixels.setPixelColor(143, pixels.Color(0,0,0));
  pixels.show();
  delay(pause_ms);
}




void show_temperature (int helligkeit, int punkt)
{
  print_2digit(Clock.getTemperature(), helligkeit, helligkeit, helligkeit);
  if (punkt)
  {
    pixels.setPixelColor(  0, pixels.Color(0,0,0));
    pixels.setPixelColor( 11, pixels.Color(0,0,0));
    pixels.setPixelColor(132, pixels.Color(0,0,0));
    pixels.setPixelColor(143, pixels.Color(1,1,1));
  }
  pixels.show();
}




void print_TimeDateTemp (void)
{
  Serial.print(Clock.getDate(),         DEC);
  Serial.print('.');
  Serial.print(Clock.getMonth(Century), DEC);
  Serial.print('.');  
  Serial.print("2");
  if (Century)
    Serial.print("1");
  else
    Serial.print("0");
  Serial.print(Clock.getYear(),         DEC);
  Serial.print("   ");
  Serial.print(Clock.getHour(h12, PM),  DEC);
  Serial.print(':');
  Serial.print(Clock.getMinute(),       DEC);
  Serial.print(':');
  Serial.print(Clock.getSecond(),       DEC);
  Serial.println(' ');
  
  Serial.print(Clock.getTemperature());
  Serial.println("°C");
  Serial.println(' ');
}




void get_serial (int NUMBER_OF_DIGITS_IN_VALUE, int timeout)
{
  char buffer_[NUMBER_OF_DIGITS_IN_VALUE+1];
  int timer = 0;

  Temp3 = 0;

  while ((Serial.available() < NUMBER_OF_DIGITS_IN_VALUE) and (timer < timeout * 10))
  {
    if (timer < timeout * 10)
      timer++;
    else
      timeout = 1;
    delay(100);
  }
  if (Serial.available() == NUMBER_OF_DIGITS_IN_VALUE)
  {
    for (int i=0; i<NUMBER_OF_DIGITS_IN_VALUE; i++)
    {
      buffer_[i] = Serial.read();
      buffer_[i+1] = '\0';
    }
    Temp1 = (byte)buffer_[0] -48;
    Temp2 = (byte)buffer_[1] -48;
    Temp3 = Temp1*10 + Temp2;
    Serial.println(Temp3);
  }
}




void print_2digit (int val, int r, int g, int b)
{
  int stelle1 =  3;
  int stelle2 = 75; 
  
  switch (val%10)
  {
    case 0:
            print_(nr0, stelle2,  r, g, b);
            break;
    case 1:
            print_(nr1, stelle2,  r, g, b);
            break;
    case 2:
            print_(nr2, stelle2,  r, g, b);
            break;
    case 3:
            print_(nr3, stelle2,  r, g, b);
            break;
    case 4:
            print_(nr4, stelle2,  r, g, b);
            break;
    case 5:
            print_(nr5, stelle2,  r, g, b);
            break;
    case 6:
            print_(nr6, stelle2,  r, g, b);
            break;
    case 7:
            print_(nr7, stelle2,  r, g, b);
            break;
    case 8:
            print_(nr8, stelle2,  r, g, b);
            break;
    case 9:
            print_(nr9, stelle2,  r, g, b);
            break;
  }
  
  switch (val/10)
  {
    case 0:
            print_(nr0, stelle1,  r, g, b);
            break;
    case 1:
            print_(nr1, stelle1,  r, g, b);
            break;
    case 2:
            print_(nr2, stelle1,  r, g, b);
            break;
    case 3:
            print_(nr3, stelle1,  r, g, b);
            break;
    case 4:
            print_(nr4, stelle1,  r, g, b);
            break;
    case 5:
            print_(nr5, stelle1,  r, g, b);
            break;
    case 6:
            print_(nr6, stelle1,  r, g, b);
            break;
    case 7:
            print_(nr7, stelle1,  r, g, b);
            break;
    case 8:
            print_(nr8, stelle1,  r, g, b);
            break;
    case 9:
            print_(nr9, stelle1,  r, g, b);
            break;
  }
}



void coffee_mug (int level)
{
  int coffee_mug_r = 0;
  int coffee_mug_g = 10;
  int coffee_mug_b = 25;
  
  int coffee_r = 25;
  int coffee_g = 2;
  int coffee_b =  2;
  
  int smoke_r = 40;
  int smoke_g = 40;
  int smoke_b = 40;

  cls();
  
  // mug
  pixels.setPixelColor(  26, pixels.Color(coffee_mug_r, coffee_mug_g, coffee_mug_b));
  pixels.setPixelColor(  27, pixels.Color(coffee_mug_r, coffee_mug_g, coffee_mug_b));
  pixels.setPixelColor(  28, pixels.Color(coffee_mug_r, coffee_mug_g, coffee_mug_b));
  pixels.setPixelColor(  29, pixels.Color(coffee_mug_r, coffee_mug_g, coffee_mug_b));
  pixels.setPixelColor(  30, pixels.Color(coffee_mug_r, coffee_mug_g, coffee_mug_b));
  pixels.setPixelColor(  31, pixels.Color(coffee_mug_r, coffee_mug_g, coffee_mug_b));  
  pixels.setPixelColor(  37, pixels.Color(coffee_mug_r, coffee_mug_g, coffee_mug_b));
  pixels.setPixelColor(  49, pixels.Color(coffee_mug_r, coffee_mug_g, coffee_mug_b));
  pixels.setPixelColor(  61, pixels.Color(coffee_mug_r, coffee_mug_g, coffee_mug_b));
  pixels.setPixelColor(  73, pixels.Color(coffee_mug_r, coffee_mug_g, coffee_mug_b));
  pixels.setPixelColor(  85, pixels.Color(coffee_mug_r, coffee_mug_g, coffee_mug_b));  
  pixels.setPixelColor(  98, pixels.Color(coffee_mug_r, coffee_mug_g, coffee_mug_b));
  pixels.setPixelColor(  99, pixels.Color(coffee_mug_r, coffee_mug_g, coffee_mug_b));
  pixels.setPixelColor( 100, pixels.Color(coffee_mug_r, coffee_mug_g, coffee_mug_b));
  pixels.setPixelColor( 101, pixels.Color(coffee_mug_r, coffee_mug_g, coffee_mug_b));
  pixels.setPixelColor( 102, pixels.Color(coffee_mug_r, coffee_mug_g, coffee_mug_b));
  pixels.setPixelColor( 103, pixels.Color(coffee_mug_r, coffee_mug_g, coffee_mug_b));  
  pixels.setPixelColor( 111, pixels.Color(coffee_mug_r, coffee_mug_g, coffee_mug_b));
  pixels.setPixelColor( 114, pixels.Color(coffee_mug_r, coffee_mug_g, coffee_mug_b));
  pixels.setPixelColor( 124, pixels.Color(coffee_mug_r, coffee_mug_g, coffee_mug_b));
  pixels.setPixelColor( 125, pixels.Color(coffee_mug_r, coffee_mug_g, coffee_mug_b));

  if (level >= 1)
  {
    pixels.setPixelColor(  38, pixels.Color(coffee_r, coffee_g, coffee_b));
    pixels.setPixelColor(  50, pixels.Color(coffee_r, coffee_g, coffee_b));
    pixels.setPixelColor(  62, pixels.Color(coffee_r, coffee_g, coffee_b));
    pixels.setPixelColor(  74, pixels.Color(coffee_r, coffee_g, coffee_b));
    pixels.setPixelColor(  86, pixels.Color(coffee_r, coffee_g, coffee_b));
  }

  if (level >= 2)
  {
    pixels.setPixelColor(  39, pixels.Color(coffee_r, coffee_g, coffee_b));
    pixels.setPixelColor(  51, pixels.Color(coffee_r, coffee_g, coffee_b));
    pixels.setPixelColor(  63, pixels.Color(coffee_r, coffee_g, coffee_b));
    pixels.setPixelColor(  75, pixels.Color(coffee_r, coffee_g, coffee_b));
    pixels.setPixelColor(  87, pixels.Color(coffee_r, coffee_g, coffee_b));
  }
  
  if (level >= 3)
  {
    pixels.setPixelColor(  40, pixels.Color(coffee_r, coffee_g, coffee_b));
    pixels.setPixelColor(  52, pixels.Color(coffee_r, coffee_g, coffee_b));
    pixels.setPixelColor(  64, pixels.Color(coffee_r, coffee_g, coffee_b));
    pixels.setPixelColor(  76, pixels.Color(coffee_r, coffee_g, coffee_b));
    pixels.setPixelColor(  88, pixels.Color(coffee_r, coffee_g, coffee_b));
  }

  if (level >= 4)
  {
    pixels.setPixelColor(  41, pixels.Color(coffee_r, coffee_g, coffee_b));
    pixels.setPixelColor(  53, pixels.Color(coffee_r, coffee_g, coffee_b));
    pixels.setPixelColor(  65, pixels.Color(coffee_r, coffee_g, coffee_b));
    pixels.setPixelColor(  77, pixels.Color(coffee_r, coffee_g, coffee_b));
    pixels.setPixelColor(  89, pixels.Color(coffee_r, coffee_g, coffee_b));
  }

  if (level >= 5)
  {
    pixels.setPixelColor(  42, pixels.Color(coffee_r, coffee_g, coffee_b));
    pixels.setPixelColor(  54, pixels.Color(coffee_r, coffee_g, coffee_b));
    pixels.setPixelColor(  66, pixels.Color(coffee_r, coffee_g, coffee_b));
    pixels.setPixelColor(  78, pixels.Color(coffee_r, coffee_g, coffee_b));
    pixels.setPixelColor(  90, pixels.Color(coffee_r, coffee_g, coffee_b));
    // coffee smoke
    pixels.setPixelColor(  33, pixels.Color(smoke_r, smoke_g, smoke_b));
    pixels.setPixelColor(  34, pixels.Color(smoke_r, smoke_g, smoke_b));
    pixels.setPixelColor(  44, pixels.Color(smoke_r, smoke_g, smoke_b));
    pixels.setPixelColor(  68, pixels.Color(smoke_r, smoke_g, smoke_b));
    pixels.setPixelColor(  69, pixels.Color(smoke_r, smoke_g, smoke_b));
    pixels.setPixelColor(  70, pixels.Color(smoke_r, smoke_g, smoke_b));
    pixels.setPixelColor(  92, pixels.Color(smoke_r, smoke_g, smoke_b));
    pixels.setPixelColor( 105, pixels.Color(smoke_r, smoke_g, smoke_b));
    pixels.setPixelColor( 106, pixels.Color(smoke_r, smoke_g, smoke_b));
  }
  pixels.show();
}

