/*
Initial code to setup joystick, lcd, and bluetooth for the land based rover.
 
Last modified: 27 Jan 2015 
*/

#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR      0x3F
#define BACKLIGHT_PIN 3
#define En_pin        2
#define Rw_pin        1
#define Rs_pin        0
#define D4_pin        4
#define D5_pin        5
#define D6_pin        6
#define D7_pin        7

int joy_x_pin = A0;    // select the input pin for the potentiometer
int joy_y_pin = A1;
int joy_button_pin = 7;
int bluetooth_status_pin = 8;

int joy_x_value = 0;  // variable to store the value coming from the sensor
int joy_y_value = 0;
int joy_x_raw = 0;
int joy_x_modified = 0;
int joy_y_raw = 0;
int joy_y_modified = 0;
int bluetooth_status = 0;

int x_old_range, y_old_range;
int x_new_range, y_new_range;
int x_old_max = 1022, y_old_max = 1022;
int x_old_min = 20, y_old_min = 20;
int x_new_max = 100, y_new_max = 100;
int x_new_min = -100, y_new_min = 0;

LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin, BACKLIGHT_PIN, POSITIVE);

void setup(){
  pinMode(joy_button_pin, INPUT);
  pinMode(bluetooth_status_pin, INPUT);
  
  Serial.begin(9600); 
  
//set x range
  x_old_range = (x_old_max - x_old_min);
  x_new_range = (x_new_max - x_new_min);
//set y range
  y_old_range = (y_old_max - y_old_min);
  y_new_range = (y_new_max - y_new_min);


  lcd.begin(20,4);
  lcd.home();
  lcd.clear();
  
  //ENABLE BELOW TO TURN ON BLUETOOTH CONNECTION CHECK
  
//  lcd.print("Bluetooth");
//  lcd.setCursor(0,1);
//  lcd.print("Not Connected");  
//  
//  while(bluetooth_status == 0){
//    bluetooth_status = digitalRead(bluetooth_status_pin);
//
//    Serial.println(bluetooth_status);
//    delay(100);
//  }
  
  lcd.clear();
  lcd.print("Control Firmware .01");

};

void loop(){
  joy_x_value = get_x_value();
  joy_y_value = get_y_value();  

  lcd.setCursor(0,1);
  lcd.print("X Value: ");
  lcd.print(joy_x_value);
  lcd.print("       ");
  lcd.setCursor(0,2);
  lcd.print("Y Value: ");
  lcd.print(joy_y_value);
  lcd.print("       ");
  
  //Serial.write("X: ");
  Serial.write(joy_x_value);
  //Serial.write(LF);
//  Serial.write("Y: ");
//  Serial.write(joy_y_value);
//  Serial.write(0x08);
  
  delay(50);
  lcd.home();

}

int get_x_value(){
    joy_x_raw = analogRead(joy_x_pin);
    
    joy_x_raw = joy_x_raw/10.24;
    
    x_old_range = (x_old_max - x_old_min);
    x_new_range = (x_new_max - x_new_min);
    
    joy_x_modified = (((joy_x_raw - x_old_min) * x_new_range) / x_old_range) + x_new_min; 
    
    //return joy_x_modified; //DEBUG!
    return joy_x_raw;
  }
int get_y_value(){
    int joy_y_raw = analogRead(joy_y_pin);
    
    joy_y_raw = joy_y_raw/10.24;
    
    y_old_range = (y_old_max - y_old_min);
    y_new_range = (y_new_max - y_new_min);
    
    joy_y_modified = (((joy_y_raw - y_old_min) * y_new_range) / y_old_range) + y_new_min; 
    
    //return joy_y_modified; //DEBUG!
    return joy_y_raw;
  }

