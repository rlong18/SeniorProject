#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>

#include <SparkFunTMP102.h>

TMP102 sensor0(0x48);

// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
const int sampleWindow = 250;// Sample window width in mS (250 mS = 4Hz)
unsigned int knock;
//int ledPin = 9;
int count = 0;

.
unsigned long previousMillis = 0;

int sampWin = 3000;






void setup() {
   Serial.begin(9600);
   pinMode(A3,INPUT);// Declare alertPin as an input
   Serial.println("Arduino Digital Temperature // Serial Monitor Version"); //Print a message
  sensors.begin();
  
  sensor0.begin();  // Join I2C bus
 

  

  // set the sensor in Comparator Mode (0) or Interrupt Mode (1).
 sensor0.setAlertMode(0); // Comparator Mode.

  // set the Conversion Rate (how quickly the sensor gets a new reading)
  //0-3: 0:0.25Hz, 1:1Hz, 2:4Hz, 3:8Hz
  sensor0.setConversionRate(2);

  //set Extended Mode.
  //0:12-bit Temperature(-55C to +128C) 1:13-bit Temperature(-55C to +150C)
  sensor0.setExtendedMode(0);
  // put your setup code here, to run once:

}

void loop() {

  roomTemp();
  soundDetector();
  bodyTemp();
 

}

void roomTemp()
{
  int tm = 4000;
   unsigned long currentMillis = millis();
  if((unsigned long)(currentMillis - previousMillis >= tm))
  {
  // Send the command to get temperatures
  sensors.requestTemperatures();  
  Serial.print("The Room Temperature is: ");
  Serial.println(sensors.getTempCByIndex(0)); // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire

  previousMillis = currentMillis;
  }
}


void soundDetector()
{
  unsigned long start= millis();  // Start of sample window
 unsigned int peakToPeak = 0;   // peak-to-peak level

 unsigned int signalMax = 0;
 unsigned int signalMin = 1024;

 
 int interval = 3000; 
  sensor0.begin();   

 // collect data for 250 miliseconds
 while (millis() - start < sampleWindow)
 {
   knock = analogRead(0);
      if (knock < 1024)  //This is the max of the 10-bit ADC so this loop will include all readings
      {
         if (knock > signalMax)
         {
           signalMax = knock;  // save just the max levels
         }
      else if (knock < signalMin)
        {
         signalMin = knock;  // save just the min levels
         }
     }
 }
 
 

 peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
 double volts = (peakToPeak * 3.3) / 1024;  // convert to volts



 if (volts >=1.0)
 {
  
   delay(500);
  Serial.println("Noise");
  
  count++;
  Serial.println(count);
 }

}

void bodyTemp()
{
  signed long currentMillis = millis();

float temperature;boolean alertPinState, alertRegisterState;


if((unsigned long)(currentMillis - previousMillis) >= sampWin)


{
  sensor0.wakeup();
  temperature = sensor0.readTempF();
  //temperature = sensor0.readTempC();
  
  Serial.print(" Body Temperature: ");
  Serial.println(temperature);
  
  previousMillis = currentMillis;
  

  
 
  
  sensor0.sleep();
 
}
  else 
      sensor0.sleep();
    
    
}
