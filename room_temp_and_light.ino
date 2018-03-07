
#include <OneWire.h>
#include <DallasTemperature.h>

//#define LEDPIN 11         //LED brightness (PWM) writing
#define LIGHTSENSORPIN A0 //Ambient light sensor reading 

// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

int sampWin = 3000;

unsigned long previousMillis = 0;

void setup(void) {
  pinMode(LIGHTSENSORPIN,  INPUT);  
//  pinMode(LEDPIN, OUTPUT);  
  Serial.begin(9600);
  Serial.println("Arduino Digital Temperature // Serial Monitor Version"); //Print a message
  sensors.begin();

  // put your setup code here, to run once:

}

void loop() {
  lightSensor();
  roomTemp();


}
void roomTemp(void)
{

unsigned long currentMillis = millis();
  if((unsigned long)(currentMillis - previousMillis >= sampWin))
 {
  // Send the command to get temperatures
  sensors.requestTemperatures();  
  Serial.print("Temperature is: ");
  Serial.println(sensors.getTempCByIndex(0)); // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  //Update value every 1 sec.
  previousMillis = currentMillis;
  }

  
}

void lightSensor()
{

float reading = analogRead(LIGHTSENSORPIN); //Read light level
  float square_ratio = reading / 1023.0;      //Get percent of maximum value (1023)
  square_ratio = pow(square_ratio, 2.0);      //Square to make response more obvious
  if(reading >= 50.00)
  {
//  analogWrite(LEDPIN, 255.0 * square_ratio); //Adjust LED brightness relatively
  Serial.print(" The light reading is");
  Serial.println(reading); //Display reading in serial monitor
  delay(1000);
  
}
}

