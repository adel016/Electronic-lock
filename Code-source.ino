#include <EEPROM.h>

#include <Wire.h>

#include <LiquidCrystal_I2C.h>

#include <Keypad.h>

char key_pressed=0;
char initial_password[4],new_password[4];
char password[4];
int i= 0;
int const passe = 1234;
const byte ROWS = 4; //4 Lignes (4 Lines, 4 rows)
const byte COLS = 4; //4 Colonnes (4 columns)
char keys[ROWS][COLS] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};

// FR: Connecté sur les lignes du KeyPad (L1, L2, L3, L4) 
// EN: Connect to the row pinouts of the keypad
byte rowPins[ROWS] = {9, 8, 7, 6};

// FR: Connecté sur les colonnes dy KeyPad (C1, C2, C3, C4)
// EN: connect to the column pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


LiquidCrystal_I2C lcd(0x20, 16, 2);

void setup(){
  Serial.begin(9600);
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.print(" ACHOUCHE ADEL");

  lcd.setCursor(0,1);

  lcd.print("Electronic Lock ");

  delay(2000);

  lcd.clear();

  lcd.print("Enter Password");

  lcd.setCursor(0,1);

  initialpassword();
  
  // LED 
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
}

void loop(){
  char key = keypad.getKey();
  //if (key != NO_KEY){
    //Serial.println(key);
    //lcd.clear();
    if(key == '#'){
      change();
    }
  if (key)

  {

    password[i++]=key;

    lcd.print(key);

      }
    
  if(i==4)

  {

    delay(200);

    for(int j=0;j<4;j++)

      initial_password[j]=EEPROM.read(j);

    if(!(strncmp(password, initial_password,4)))

    {

      lcd.clear();
    
      digitalWrite(12, HIGH);
      lcd.print("Pass Accepted");
      

      delay(2000);

      lcd.setCursor(0,1);
    digitalWrite(12, LOW);
      lcd.print("Pres # to change");

      delay(2000);

      lcd.clear();

      lcd.print("Enter Password:");

      lcd.setCursor(0,1);

      i=0;
    }
      else

    {

      lcd.clear();

      lcd.print("Wrong Password");
    // clignoter la led rouge
      digitalWrite(13, HIGH);
        delay(200);
      digitalWrite(13, LOW);
        delay(200);
      digitalWrite(13, HIGH);
        delay(200);
      digitalWrite(13, LOW);
        delay(200);
      digitalWrite(13, HIGH);
        delay(200);
      digitalWrite(13, LOW);
        delay(200);
       

      lcd.setCursor(0,1);

      lcd.print("Pres # to Change");

      delay(2000);

      lcd.clear();

      lcd.print("Enter Password");

      lcd.setCursor(0,1);

      i=0;

    


    }
    }
}

void change() {
  int j = 0;
  lcd.clear();
  lcd.print("Current Password");
  lcd.setCursor(0,1);
  while(j<4)

  {

    char key=keypad.getKey();

    if(key)

    {

      new_password[j++]=key;

      lcd.print(key);
    }
    key=0;
    
}
  delay(500);
  
  if((strncmp(new_password, initial_password, 4)))

  {

    lcd.clear();

    lcd.print("Wrong Password");
    // Clignoter la led rouge 
    digitalWrite(13, HIGH);
        delay(200);
      digitalWrite(13, LOW);
        delay(200);
      digitalWrite(13, HIGH);
        delay(200);
      digitalWrite(13, LOW);
        delay(200);
      digitalWrite(13, HIGH);
        delay(200);
      digitalWrite(13, LOW);
        delay(200);
  digitalWrite(13, HIGH);
        delay(100);
      digitalWrite(13, HIGH);
        delay(100);
      digitalWrite(13, HIGH);
        delay(100);
    lcd.setCursor(0,1);

    lcd.print("Try Again");
  
    delay(1000);
  }
   else

  {

    j=0;

    lcd.clear();

    lcd.print("New Password:");

    lcd.setCursor(0,1);

    while(j<4)

    {

      char key=keypad.getKey();

      if(key)

      {

        initial_password[j]=key;

        lcd.print(key);

        EEPROM.write(j,key);

        j++;

     

      }

    }

    lcd.print("Pass Changed");
  digitalWrite(12, HIGH);
    delay(2000);

  }

  lcd.clear();

  lcd.print("Enter Password");

  lcd.setCursor(0,1);

  key_pressed=0;

}



void initialpassword() {
  for(int j=0;j<4;j++){
    EEPROM.write(j, j+49);
  } 

  for(int j=0;j<4;j++){
    initial_password[j]=EEPROM.read(j);
  }
}
