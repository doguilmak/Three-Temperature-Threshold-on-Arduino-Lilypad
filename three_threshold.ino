// Thermistor Project on Arduino Lilypad with 3 threshold.
// Doğu İlmak

float hotAlert = 80.0;  // 80 degrees
float marrowAlert = 30; // 30 degrees
float coldAlert = 4.0; // 3 degrees

// Temperature sensor is connected to A1
int sensorPin = A1;  

// The LEDs in the tri-color LED
int RGB_red = 9;
int RGB_green = 11;
int RGB_blue = 10;

// The vibe board
int motor = 3;

void setup()
{
  // Set the temperature sensor pin as an INPUT:
  pinMode(sensorPin, INPUT);

  // Make all of our LED pins outputs:
  
  pinMode(RGB_red, OUTPUT);
  pinMode(RGB_green, OUTPUT);
  pinMode(RGB_blue, OUTPUT);
  
  pinMode(motor, OUTPUT);

  // Initialize Serial, set the baud rate to 9600 bps.
  Serial.begin(9600);
}

void loop()
{
  // Variable to store raw temperature
  long rawTemp;

  // Variable to store voltage calculation
  float voltage;

  // Variable to store Fahrenheit value
  float fahrenheit;

  // Variable to store Celsius value
  float celsius;

  // Read the raw 0-1023 value of temperature into a variable.
  rawTemp = analogRead(sensorPin);

  // Calculate the voltage, based on that value.
  // Multiply by maximum voltage (4.2V for USB power) and divide by maximum ADC value (1023).
  voltage = rawTemp * (4.2 / 1023.0);
  Serial.print("Voltage: "); // Print voltage reading to serial monitor
  Serial.println(voltage);

  // Calculate the celsius temperature, based on that voltage..
  celsius = (voltage - 0.5) * 100;
  Serial.print("Celsius: "); // Print celcius temp to serial monitor
  Serial.println(celsius);

  // Use a common equation to convert celsius to Fahrenheit. F = C*9/5 + 32.
  fahrenheit = (celsius * 9.0 / 5.0) + 32.0;
  Serial.print("Fahrenheit: "); // Print Fahrenheit temp to serial monitor
  Serial.println(fahrenheit); 
  // Print a blank line
  Serial.println();       

  // Check the temperature, and turn on the LEDs associated with the hot or cold thresholds
  if (celsius >= hotAlert) // If the temperature rises above the hot threshold:
  {
    digitalWrite(RGB_red, HIGH);
    delay(500);
    digitalWrite(RGB_red,LOW);
    
    digitalWrite(RGB_red, HIGH);
    delay(500);
    digitalWrite(RGB_red,LOW);
    
    digitalWrite(RGB_red, HIGH);
    delay(500);
    digitalWrite(RGB_red,LOW);  
  }
  else if (hotAlert < celsius < marrowAlert) // If the temperature falls below the cold threshold:
  {
    digitalWrite(RGB_red, HIGH);   // Turn the red LED off
    digitalWrite(RGB_green, HIGH); // Turn the green LED off
    digitalWrite(RGB_blue, LOW);   // Turn the blue LED on
  }
  else if (marrowAlert < celsius < coldAlert) // If the temperature falls below the cold threshold:
  {
    digitalWrite(RGB_red, LOW);   // Turn the red LED off
    digitalWrite(RGB_green, HIGH); // Turn the green LED off
    digitalWrite(RGB_blue, HIGH);   // Turn the blue LED on
  }
  
  else // For all other temperature readings (between hot and cold):
  {
    digitalWrite(RGB_blue, HIGH);
    delay(500);
    digitalWrite(RGB_blue,LOW);
    
    digitalWrite(RGB_blue, HIGH);
    delay(500);
    digitalWrite(RGB_blue,LOW);
    
    digitalWrite(RGB_blue, HIGH);
    delay(500);
    digitalWrite(RGB_blue,LOW);
  }

  // Wait 1 second between readings
  delay(1000);  
}
