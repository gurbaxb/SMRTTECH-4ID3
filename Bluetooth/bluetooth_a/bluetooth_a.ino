#include "bluetooth_a.h"

void setup() {
  Serial.begin(9600);
  Serial.print("\n\n------------------------\n"
    + group_name + " : " + device_name + "\n------------------------\n\n"); 

  Wire.begin();
  Wire.beginTransmission(ADDR);
  Wire.endTransmission();
  delay(300);
  
  light_sensor.begin(apds_gain, apds_time);
  
}

void loop() {
  Wire.beginTransmission(ADDR);
  Wire.write(TMP_CMD);
  Wire.endTransmission();
  delay(100);

  Wire.requestFrom(ADDR, 2);

  char data[2];
  if(Wire.available() == 2){
    data[0] = Wire.read();
   // Serial.print("Data[0] : ");
   // Serial.println((float)data[0]);
    data[1] = Wire.read();
   // Serial.print("Data[1] : ");
   // Serial.println((float)data[1]);
  }

  float temp = ((data[0] * 256.0) + data[1]);
  float temp_c = ((175.72 * temp) / 65536.0) - 46.85;

  Wire.beginTransmission(ADDR);
  Wire.write(HMD_CMD);
  Wire.endTransmission();
  delay(100);

  Wire.requestFrom(ADDR, 2);

  char datatwo[2];
  if(Wire.available() == 2){
    datatwo[0] = Wire.read();
   // Serial.print("Data[0] : ");
   // Serial.println((float)data[0]);
    datatwo[1] = Wire.read();
   // Serial.print("Data[1] : ");
   // Serial.println((float)data[1]);
  }

  float humidity = ((datatwo[0] * 256.0) + datatwo[1]);
  humidity = ((125 * humidity) / 65536.0) - 6;

  AsyncAPDS9306Data light_data = light_sensor.syncLuminosityMeasurement();
  float lux = light_data.calculateLux();

  String formatted_data = 
    "{ \"" + group_name + "\": { \"" 
    + device_name + "\": { \"Temp\": \"" 
    + String(temp_c) + "\", \"Humidity\": \"" 
    + String(humidity) + "\", \"Luminosity\": \"" 
    + String(lux) + "\"} } }" + '\n';
      
  Serial.println(formatted_data);
  
  delay(DELAY_BETWEEN_SAMPLES_MS);

}
