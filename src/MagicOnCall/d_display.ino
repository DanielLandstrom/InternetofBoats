// Include for the Display functionality 
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// Variables for the Display
#define BACKLIGHT_PIN     20

void Display_setup(void);
void Display_welcome(void); 

//extern LiquidCrystal_I2C lcd(0x3f,20,4);
extern LiquidCrystal_I2C lcd;
LiquidCrystal_I2C lcd(0x3f,20,4);
void Display_setup(void) {
  //pinMode(BACKLIGHT_PIN, OUTPUT);
  //digitalWrite(BACKLIGHT_PIN, HIGH);
  lcd.begin(20,4,0);
  lcd.init();
  lcd.backlight();
  lcd.home();
  lcd.display();
}


void Display_welcome(void) {    
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("- = Simply Magic = -");
  lcd.setCursor(0,2);
  lcd.print("Wind: 12.4m/s 271deg");
//  lcd.setCursor(1,3);
//  lcd.print("IP: 192.168.000.117");
}
