#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Bounce2.h>
 
/**************************Configure OLED Display Here********************/
//I2C OLED with address 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_SCL D1
#define OLED_SCA D2
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/**************************Configure LORA Module Here********************/ 
#define SS D8
#define RST D0
#define DIO0 D3

/**************************Configure GPIOs Here**************************/
#define MOTOR_SWITCH D4


/**************************Declare Global Variables *********************/ 
int motor_switch_status = LOW;

/**************************Declare Global Objects************************/ 
Bounce bounce = Bounce();

/**************************Declare Global Functions *********************/ 
void updateDashBoard(const char* motor_status, const char* RSSI)
{
  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.print(F("Status : "));
  display.print(motor_status);
  display.setCursor(0,10);
  display.print(F("RSSI   : "));
  display.print(RSSI);
  display.display();
  delay(2);
}


/**************************Main Code Starts Here ************************/ 
void setup() 
{
  Serial.begin(9600); 
  Wire.begin();
  bounce.attach( MOTOR_SWITCH, INPUT );

  // DEBOUNCE INTERVAL IN MILLISECONDS
  bounce.interval(50); // interval in ms

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
/*   while (!Serial);
  Serial.println("LoRa Sender");
  LoRa.setPins(ss, rst, dio0);
    if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    delay(100);
    while (1);
  } */
  
  display.display();
  display.clearDisplay();
  delay(2000);
  //Update current state
}
 
void loop() 
{
  // Update the Bounce instance (YOU MUST DO THIS EVERY LOOP)
  bounce.update();

  // <Bounce>.changed() RETURNS true IF THE STATE CHANGED (FROM HIGH TO LOW OR LOW TO HIGH)
  if ( bounce.changed() ) {
    // THE STATE OF THE INPUT CHANGED
    // GET THE STATE
    int debouncedInput = bounce.read();
    switch (debouncedInput)
    {
      case HIGH:
        Serial.println("Motor is OFF");
        updateDashBoard("OFF\n","0\n");
        break;
      case LOW:
        Serial.println("Motor is ON");
        updateDashBoard("ON\n","0\n");        
        break;
      default:
        break;
    }
  }


  // send packet
/*   LoRa.beginPacket();
  LoRa.print(F("Pkt No:"));
  LoRa.println(counter);
  
  LoRa.endPacket(); */
 
  
}
