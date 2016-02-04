// includes:
#include <EEPROM.h>
#include <LiquidCrystal.h>

const char leftButton = 3;
const char rightButton = 2;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);

// Grain characters
#define GRAIN 0
#define LEFT_ARROW 1
#define RIGHT_ARROW 2

byte grain[8] = {
  0b00000,
  0b01110,
  0b11101,
  0b11011,
  0b11011,
  0b10111,
  0b01110,
  0b00000
};

byte leftArrow[8] = {
  0b00000,
  0b00000,
  0b00010,
  0b00110,
  0b01110,
  0b00110,
  0b00010,
  0b00000
};

byte rightArrow[8] = {
  0b00000,
  0b00000,
  0b01000,
  0b01100,
  0b01110,
  0b01100,
  0b01000,
  0b00000
};

// Coffees
#define COFFEE_FRANCAIS  0
#define COFFEE_ITALIEN   1
#define COFFEE_MOKA      2
#define COFFEE_COLOMBIE  3
#define COFFEE_BRESILIEN 4
#define COFFEE_COSTARICA 5
#define COFFEE_PAPOUASIE 6
#define COFFEE_MAX       7

char leftCoffee = 0;
char rightCoffee = 0;

void setup() {
  pinMode(leftButton, INPUT);
  pinMode(rightButton, INPUT);

  // Create custom caracters
  lcd.createChar(GRAIN, grain);
  lcd.createChar(LEFT_ARROW, leftArrow);
  lcd.createChar(RIGHT_ARROW, rightArrow);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  unsigned char value;
  value = EEPROM.read(0);
  if (value < COFFEE_MAX) {
    leftCoffee = value;
  }
  value = EEPROM.read(1);
  if (value < COFFEE_MAX) {
    rightCoffee = value;
  }
  
  printLeft();
  printRight();
}

void printLeft() {
  lcd.home();
  lcd.write((uint8_t) LEFT_ARROW);
  lcd.print(" " + getCoffee(leftCoffee) + " ");
  for (char i = 0; i < getStrength(leftCoffee); i++) {
    lcd.write((uint8_t) GRAIN);
  }
  lcd.print("      ");
}

void printRight() {
  lcd.setCursor(0, 1);
  lcd.write((uint8_t) RIGHT_ARROW);
  lcd.print(" " + getCoffee(rightCoffee) + " ");
  for (char i = 0; i < getStrength(rightCoffee); i++) {
    lcd.write((uint8_t) GRAIN);
  }
  lcd.print("      ");
}

void nextCoffee(char &coffee) {
  coffee++;
  if (coffee == COFFEE_MAX) {
    coffee = 0;
  }
}

void loop() {
  if (digitalRead(leftButton) == HIGH)
  {
    nextCoffee(leftCoffee);
    printLeft();
    EEPROM.write(0, leftCoffee);
    delay(1500);
  }
  else if (digitalRead(rightButton) == HIGH)
  {
    nextCoffee(rightCoffee);
    printRight();
    EEPROM.write(1, rightCoffee);
    delay(1500);
  }

}

static String getCoffee(const char type) {
  switch(type) {
    case COFFEE_FRANCAIS:
      return "Francais";
    case COFFEE_ITALIEN:
      return "Italien";
    case COFFEE_MOKA:
      return "Moka";
    case COFFEE_COLOMBIE:
      return "Colombie";
    case COFFEE_BRESILIEN:
      return "Bresilien";
    case COFFEE_COSTARICA:
      return "Costa Rica";
    case COFFEE_PAPOUASIE:
      return "Papouasie";
    default:
      return "";
  }
}

static char getStrength(const char type) {
  switch(type) {
    case COFFEE_FRANCAIS:
    case COFFEE_ITALIEN:
      return 4;
    case COFFEE_MOKA:
    case COFFEE_COLOMBIE:
      return 3;
    case COFFEE_PAPOUASIE:
    case COFFEE_BRESILIEN:
    case COFFEE_COSTARICA:
      return 2;
    default:
      return 0;
  }
}



