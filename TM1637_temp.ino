#include <Arduino.h>
#include <TM1637Display.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// DHT DATA pin 
#define DHTPIN 2     
// 4-digit Module pins
#define CLK 3
#define DIO 4

// The amount of time (in milliseconds) in loop
#define TEST_DELAY   1000

// array to hold characters to display
uint8_t DISP[] = {
  0,   // blank
  0,   // blank
  0,   // blank
  SEG_A | SEG_D | SEG_E | SEG_F                    // C for Celsius
  };

#define DHTTYPE    DHT11     // DHT 11

//initiate objects
DHT_Unified dht(DHTPIN, DHTTYPE);
TM1637Display display(CLK, DIO);

//variable for holding temperature
int temp;

void setup()
{
  //initialize DHT
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
}

void loop()
{
  display.setBrightness(0x0f);       //seven segment brightness
  sensors_event_t event;              
  dht.temperature().getEvent(&event); //read temperature
  temp = event.temperature; 
  //Routine for displaying temperature on the display
  int tens = temp / 10;               
  int ones = temp - tens*10;
  DISP[0] = display.encodeDigit(tens);
  DISP[1] = display.encodeDigit(ones);
  display.setSegments(DISP);
  //Delay between reads
  delay(TEST_DELAY); 
 
}
