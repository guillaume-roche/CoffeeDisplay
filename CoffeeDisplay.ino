// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);

// Grain caracters
#define GRAIN 0

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

// Coffees
#define COFFEE_FRANCAIS  0
#define COFFEE_ITALIEN   1
#define COFFEE_MOKA      2
#define COFFEE_COLOMBIE  3
#define COFFEE_BRESILIEN 4
#define COFFEE_COSTARICA 5
#define COFFEE_PAPOUASIE 6

char leftCoffee = 0;
char rightCoffee = 0;

volatile int leftSelection = 0;
volatile int rightSelection = 0;

void setup() {
  // Create grain caracters
  lcd.createChar(GRAIN, grain);
  
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  
  // Print left coffee
  lcd.print(getCoffee(leftCoffee));
  
  // Print right coffee right aligned
  lcd.setCursor(16 - getCoffee(rightCoffee).length(), 0);
  lcd.print(getCoffee(rightCoffee));
  
  lcd.setCursor(0, 1);
  lcd.write((uint8_t) GRAIN);
  lcd.write((uint8_t) GRAIN);
  lcd.write((uint8_t) GRAIN);
  
  // Attach interrupt to handle edit mode on pin 2
  attachInterrupt(0, switchMode, LOW);
}

void switchMode() {
  leftSelection++;
  if (leftSelection == 7) {
    leftSelection = 0;
  }
}

void loop() {
  if (leftSelection != leftCoffee)
  {
    lcd.clear();
    lcd.setCursor(16 - getCoffee(rightSelection).length(), 0);
    lcd.print(getCoffee(rightSelection));
    
    lcd.setCursor(0, 0);
    lcd.print(getCoffee(leftSelection));
  }
  delay(1000);
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
    case COFFEE_PAPOUASIE:
      return 3;
    case COFFEE_BRESILIEN:
    case COFFEE_COSTARICA:
      return 2;
    default:
      return 0;
  }
}



