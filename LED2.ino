#include "Audio.h"
#include "SPIFFS.h"
#include <Wire.h>
#include "SparkFun_VL53L1X.h" //Click here to get the library: http://librarymanager/All#SparkFun_VL53L1X


int ledPin = 17;
unsigned long current_time = 0;  // Shared variable to track time
bool forceLEDOff = false;         // Flag to turn off LED during silence/delay

bool flag1 = true;

unsigned int current_counter = 0;

int times = 0;
int distance_sense = 0;

//TaskHandle_t ledTaskHandle;  // Task handle for LED control

Audio audio;
SFEVL53L1X distanceSensor;
void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  delay(1000);  // Allow time for Serial Monitor to open
  Wire.begin();
  // Initialize SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("[ERROR] SPIFFS Mount Failed");
    return;
  }

  // Check if the audio file exists
  if (!SPIFFS.exists("/audio.mp3")) {
    Serial.println("[ERROR] MP3 file not found! Upload it to SPIFFS.");
    return;
  }

   if (distanceSensor.begin() != 0) //Begin returns 0 on a good init
  {
    Serial.println("Sensor failed to begin. Please check wiring. Freezing...");
    while (1)
      ;
  }
  Serial.println("Sensor online!");

  // Set I2S audio output pinout
  audio.setPinout(25, 26, 14);  // BCLK, LRCLK, DIN
  audio.setVolume(255);  // Set to max volume

}

void loop() {

  //Write configuration bytes to initiate measurement
//  while (!distanceSensor.checkForDataReady())
//  {
//    delay(1);
//  }

  if (!audio.isRunning()) {
    current_counter = 0;
    Serial.println("not audio running");
    if (flag1 == true) {
      Serial.println("if flag1 is true, now set to false, and loading 1st audio");
      audio.connecttoFS(SPIFFS, "/audio.mp3");  // Reload the audio       
      flag1 = false;
    }
    else {
    digitalWrite(ledPin, HIGH);
    if(distance_sense <= 80){
      distance_sense = 80;
    }
    else if(distance_sense >= 1000){
      distance_sense = 1000;
    }
      delay(distance_sense);
      //audio.connecttoFS(SPIFFS, "/2nd.mp3");  // Reload the audio
      Serial.println("if flag1 is false, now set to true, and loading nd audio");
      flag1 = true;
    }
    Serial.println("[INFO] Reloading audio...");
    //current_time = 0;  // Reset the shared time variable
  }
  audio.loop();
  if (current_counter++ >= 10000) {
    distanceSensor.startRanging(); 
    distance_sense = distanceSensor.getDistance(); //Get the result of the measurement from the sensor
    distanceSensor.stopRanging();
    Serial.print("Distance(mm): ");
    Serial.print(distance_sense);
    distanceSensor.clearInterrupt();
    digitalWrite(ledPin, LOW);
    current_counter = 0;
    Serial.println("delay done");
  }

}
