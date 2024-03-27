#define sensorPin 0          // the pH meter Analog output is connected with the Arduino’s Analog

void setup()
{
  //pinMode(13,OUTPUT);  
  Serial.begin(9600);  
  pinMode(sensorPin, INPUT);
  Serial.println("Ready");    //Test the serial monitor
}
void loop()
{
    double buf = 0;
    double storedpH = 0;
    for (int i = 0; i < 3; i++){
      buf=analogRead(sensorPin);
      delay(1000);
      storedpH += buf;
    }
    Serial.print("pH = ");
    double avgpH = storedpH * (5/(1.024*3));
    Serial.print(String((avgpH/1000)+3.7)); //conversion to pH
    Serial.print(" \n");
}
