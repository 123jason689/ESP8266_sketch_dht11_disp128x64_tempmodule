#include <Wire.h>

#include <Adafruit_SSD1306.h>

#include <Adafruit_GFX.h>

#include <DHT.h>

#define OLED_WIDTH 128

#define OLED_HEIGHT 64

#define OLED_RESET -1

#define OLED_ADDR 0x3C

#define DHT_TYPE DHT11

const int scl = 5;
const int sda = 4;
const int dhtpin = 14;
const int ledpin = 2;

bool ticktock = true;

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET);
DHT dht(dhtpin, DHT_TYPE);

void setup()

{
  Serial.begin(9600);

  pinMode(ledpin, OUTPUT);
  digitalWrite(ledpin, HIGH);

  if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.display();
  delay(5000);

  display.clearDisplay();

  display.setTextSize(1);

  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.print("Temperature\n&\nHummidity\nIdentifier\n");

  display.print("Initializing...");
  display.display();

  Serial.println(F("Initializing...."));

  delay(2000);

  dht.begin();
  Serial.println("DHT started");
}

void loop()

{
  delay(1000);
  Serial.println("---------------loop-----------------");
  if(ticktock){
    ticktock = false;
    digitalWrite(ledpin, LOW);
  } else {
    ticktock = true;
    digitalWrite(ledpin, HIGH);
  }

  float hum = dht.readHumidity();

  float temp = dht.readTemperature();

  display.clearDisplay();
  display.setTextSize(1);

  display.setCursor(0,10);
  if(!temp){
    display.print("Temp: Na");
    display.println("C");
    
    Serial.print("Temp: Na");
    Serial.println("C");
  } else {
    display.print("Temp: ");
    display.print(temp);
    display.println("C");
    
    Serial.print("Temp: ");
    Serial.print(temp);
    Serial.println("C");
  }

  display.println("");
  // display.setCursor(0,8);
  if(!hum){
    display.print("Humid = Na");
    display.println("%");
    
    Serial.print("Humid = Na");
    Serial.println("%");
  } else {
    display.print("Humid = ");
    display.print(hum);
    display.println("%");
    
    Serial.print("Humid = ");
    Serial.print(hum);
    Serial.println("%");
  }

  display.display();
  

}
