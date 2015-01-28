/*
 Example Arduino sketch for
 SainSmart IIC/I2C/TWI Serial 2004 20x4 LCD Module Shield For Arduino UNO MEGA R3
 http://www.sainsmart.com/sainsmart-iic-i2c-twi-serial-2004-20x4-lcd-module-shield-for-arduino-uno-mega-r3.html
 
 and
 
 Real Time Clock DS3231 (when displaying temperature will be omitted can be used also for DS1307
 http://macetech.com/store/index.php?main_page=product_info&products_id=8 
 http://nicegear.co.nz/raspberry-pi/high-precision-real-time-clock-for-raspberry-pi/

 
 This example uses F Malpartida's NewLiquidCrystal library. Obtain from:
 https://bitbucket.org/fmalpartida/new-liquidcrystal 
 
 This example also uses Tennsy Time.h library. Obtain from:
 http://www.pjrc.com/teensy/td_libs_Time.html 
 
 Tested on:
 Arduino Pro Mini, Arduino Uno - A4 (SDA), A5 (SCL)
 Arduino Mega 2560 - 20 (SDA), 21 (SCL)
 
 Last modified: 16-Dec-2013
 
*/
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <Time.h>

#define I2C_ADDR      0x3F // I2C address of PCF8574A
#define BACKLIGHT_PIN 3
#define En_pin        2
#define Rw_pin        1
#define Rs_pin        0
#define D4_pin        4
#define D5_pin        5
#define D6_pin        6
#define D7_pin        7

int sensorPin = A0;    // select the input pin for the potentiometer
int sensorPin2 = A1;
int buttonPin = 7;
int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
int sensorValue2 = 0;


LiquidCrystal_I2C twilcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin, BACKLIGHT_PIN, POSITIVE);

//////////////////////////////////////////////////////////////
#define TRIGGER_INIT_VALUE  0
#define INTERVAL_INIT_VALUE 1
#define INTERVAL_MAX_VALUE  512
#define EMBEDDED_LED_PIN    13
long interval = INTERVAL_INIT_VALUE;
byte trigger;
byte ledState = LOW;
//////////////////////////////////////////////////////////////
void setup(){

  pinMode(ledPin, OUTPUT); 
pinMode(buttonPin, INPUT);
Serial.begin(9600); 

  pinMode(EMBEDDED_LED_PIN, OUTPUT);
  trigger = TRIGGER_INIT_VALUE;
  twilcd.begin(20,4);
  twilcd.home();
  //1234567890123456
  //I2C/TWI BackPack
    twilcd.clear();
  


  };

void loop(){
    // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  sensorValue2 = analogRead(sensorPin2);   
  
    twilcd.print("Control Firmware .01");
  twilcd.setCursor(0,1);
  twilcd.print("X Value: ");
  twilcd.print(sensorValue); 
  twilcd.setCursor(0,2);
  twilcd.print("Y Value: ");
  twilcd.print(sensorValue2);
    delay(100);
  twilcd.clear();

}
//*** GLOBAL VARIABLE DECS ***//
int ch1_old_range, ch2_old_range;
int ch1_new_range, ch2_new_range;
int ch1_old_max = 1970, ch2_old_max = 1970;
int ch1_old_min = 970, ch2_old_min = 970;
int ch1_new_max = 126, ch2_new_max = 126;
int ch1_new_min =  0, ch2_new_min =  0;



//*** FUNCTION FORWARD DECS ***//
void setup_io();
void setup_uart_1(); //bluetooth communication
void setup_uart_2(); //motor controller communication
void setup_timer_1();
void setup_ic_2();
void setup_ic_3();
void get_ch1_value(); //receive, measure, and convert PWM signal to serial data for motor control
void get_ch2_value();


int main(void){

//*** VARIABLE DECS ***//

//*** SETUP RECEIVER PARSES ***//

    //ch1
     ch1_old_range = (ch1_old_max - ch1_old_min);
     ch1_new_range = (ch1_new_max - ch1_new_min);

    //ch2
     ch2_old_range = (ch2_old_max - ch2_old_min);
     ch2_new_range = (ch2_new_max - ch2_new_min);

