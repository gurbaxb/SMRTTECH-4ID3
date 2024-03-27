#include "photometric.h"  // Include the modified header file

void setup() {
  // Start the serial monitor at 115200 baud
  Serial.begin(115200);

  // Initialize the I2C communication
  Wire.begin(SDA_PIN, SCL_PIN);  // SDA on GPIO4 (D2), SCL on GPIO5 (D1)

  // Initialize TSL2561 sensor
  if (!tsl.begin()) {
    Serial.println("TSL2561 not found");
    while (1)
      ;
  }

  // Configure the sensor gain and integration time
  tsl.enableAutoRange(true);
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_402MS);
}

void loop() {
  // Get a new sensor event from the TSL2561 sensor
  sensors_event_t tslEvent;
  tsl.getEvent(&tslEvent);

  // Check if the event was successful
  if (tslEvent.light) {
    // Printing sensor readings to serial monitor
    Serial.print("\n-");
    Serial.println("Light Intensity: " + String(tslEvent.light) + " lux");
  } else {
    Serial.println("Light Sensor Disconnected");
  }

  delay(DELAY_BETWEEN_SAMPLES_MS);
}
