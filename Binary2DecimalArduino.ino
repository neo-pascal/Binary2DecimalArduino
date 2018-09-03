//LANGUAGE               Arduino C++
//GITHUB                 https://github.com/neo-pascal
//WRITTEN BY             Neo Ayestaran
//DATE                   01/09/18             
//FILE SAVED AS          Binary2DecimalArduino.ino
//FOR Arduino UNO        With 1602 LCD Shield with Keypad
//SOFTWARE FUNCTION      'Display an 8-bit binary value and 
//                        ask the user to work out the 
//                        decimal value'

#include <LiquidCrystal.h>
#include <DFR_LCD_Keypad.h>

//This is the factory config shield initialisation
LiquidCrystal lcd(8,9,4,5,6,7); 

// initialise the keypad
DFR_LCD_Keypad keypad(A0, &lcd);

//Global Variables
String modeSelectResult;
char mode;
byte valueToConvert;

byte rightArrow[] = 
{
  B00000,
  B00100,
  B00110,
  B11111,
  B00110,
  B00100,
  B00000,
  B00000
};

byte upArrow[] = 
{
  B00100,
  B01110,
  B11111,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100
};

byte downArrow[] = 
{
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B11111,
  B01110,
  B00100
};

//The setup routine runs once you press reset
void setup()
{
  lcd.begin(16, 2);
  lcd.createChar(0, rightArrow);
  lcd.createChar(1, upArrow);
  lcd.createChar(2, downArrow);
  splash();
}

void splash()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Binary 2 Decimal");
  lcd.setCursor(0,1);
  lcd.print("By Neo Ayestaran");
  delay(5000);
}

String modeSelect()
{
  lcd.setCursor(0,0);
  lcd.print("5sec Timed Mode?");
  lcd.setCursor(0,1);
  lcd.print("UP=Yes / Down=No");

  int last_key, key, modeConfirmed, count;
  last_key = keypad.get_last_key();
  modeConfirmed = 0;
  count = 0;
  String modeSelectResult;
  
  do
  {
    count = count + 1;
    key = keypad.read_key();
  
    if (key != last_key) 
    {
      // key has changed
      
       switch (key) 
       {
        case KEY_UP:
        modeSelectResult = '1';
        modeSelectResult.concat(String(char(count)));
        modeConfirmed = 1;
          break;
                  
        case KEY_DOWN:
        modeSelectResult = '2';
        modeSelectResult.concat(String(char(count)));
        modeConfirmed = 1;
          break;
       }
  
       delay(10);
    }

  }
  while (modeConfirmed == 0);
 
  return modeSelectResult;
}

String DecTo8bitBinary(int dec) 
{
 String result = "";
 for (unsigned int i = 0x80; i; i >>= 1) 
 {
 result.concat(dec  & i ? '1' : '0');
 }
 return result;
}

void waitForSpecificKeyPress(int KEY_NUMBER)
{
int key, KeyPressed = -1;
  do
  {
    key = keypad.read_key();

       if (KEY_NUMBER == 0) 
       {
         switch (key) 
         {
          case KEY_RIGHT:
          KeyPressed = 0;
            break;
         }
       }
       
       if (KEY_NUMBER == 1) 
       {
         switch (key) 
         {
          case KEY_UP:
          KeyPressed = 1;
            break;
         }
       }

       if (KEY_NUMBER == 2) 
       {
         switch (key) 
         {
          case KEY_DOWN:
          KeyPressed = 1;
            break;
         }
       }
       
       delay(10);
  }
  while (KeyPressed == -1);
}
  
void TimedYes(byte valueToConvert)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Convert " + DecTo8bitBinary(valueToConvert));
  lcd.setCursor(0,1);
  lcd.print("Answer in ");

  for (int i=5; i > 0; i--){
     lcd.setCursor(11,1);
     lcd.print(i);
     delay(1000);
   }

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Answer is... ");
  lcd.setCursor(13,0);
  lcd.print(valueToConvert);
  lcd.setCursor(0,1);
  lcd.print("Tap   to end");
  lcd.setCursor(4,1);
  lcd.print(char(0));

  waitForSpecificKeyPress(0);
}

void TimedNo(byte valueToConvert)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Convert " + DecTo8bitBinary(valueToConvert));
  lcd.setCursor(0,1);
  lcd.print("Tap   for answer");
  lcd.setCursor(4,1);
  lcd.print(char(1));

  waitForSpecificKeyPress(1);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Answer is... ");
  lcd.setCursor(13,0);
  lcd.print(valueToConvert);
  lcd.setCursor(0,1);
  lcd.print("Tap   to end");
  lcd.setCursor(4,1);
  lcd.print(char(0));
  
  waitForSpecificKeyPress(0);
}

void loop()
{
  modeSelectResult = modeSelect();
  mode = modeSelectResult[0];
  valueToConvert = modeSelectResult[1];
  
  if (mode == '1')
  {  
    TimedYes(valueToConvert);
  } 
  
  if (mode == '2')
  {  
    TimedNo(valueToConvert);
  }
  
//infinity:goto infinity; 
}


