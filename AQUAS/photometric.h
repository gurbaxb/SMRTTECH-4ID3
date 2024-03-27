#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>

// Define the GPIO pins for SDA and SCL
#define SDA_PIN 4  // GPIO4 (D2)
#define SCL_PIN 5  // GPIO5 (D1)

// Define the delay between sensor samples in milliseconds
#define DELAY_BETWEEN_SAMPLES_MS 5000  // Example: 5 seconds delay

// Initialize the TSL2561 sensor with the appropriate pins
#define TSL2561_ADDR_FLOAT  (0x39)       // Default address, floating i2c address

Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);