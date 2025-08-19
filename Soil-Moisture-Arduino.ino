// Include necessary libraries
#include <LiquidCrystal_I2C.h>

// initializing pins for moisture sensor, dc_motor , tmp32 temperature sensor and LCD_I2C display
const int soilsensorPin = A0; // Analog input pin for the soil moisture sensor
const int dc_Motor = 3; // Pin connected to the DC motor
int temp = A1; // TMP36 temperature sensor connected to analog A1  
LiquidCrystal_I2C lcd(32,16,2); // Initialize LCD display (I2C address, number of columns, number of rows)

//custom variables 
float voltage; // Variable to store voltage value
float celcius; // Variable to store temperature in Celsius

//  degree symbol character
byte degree[8] = {0b01100, 0b10010, 0b01100, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000};


void setup() {
// Initialize serial communication
  Serial.begin(9600); 
  
  pinMode(dc_Motor, OUTPUT); // Set motor pin as output
  
//Lcd_I2C configurations
  lcd.init(); // Initialize LCD display
  lcd.createChar(0, degree); // Create the custom character for degree symbol
  lcd.setCursor(0,0); // Set cursor to the beginning of the LCD
  lcd.backlight(); // Turn on LCD backlight
  lcd.display(); // Turn on LCD display
  
   
}


void loop() {

//take the data from the soil moisture sensor 
  int soilMoistureValue = analogRead(soilsensorPin); // Read soil moisture sensor value
  Serial.println(soilMoistureValue); // Print soil moisture value to serial monitor
  


// convert the reading from the temperature sensor into degree Celsius
  voltage = analogRead(temp)*(5.0/1023.0); // Convert analog reading to voltage
  celcius = (voltage - 0.5)* 100; // Convert voltage to Celsius
  String soilMoistureLevel; // Variable to store soil moisture level
  
// Determine soil moisture level based on sensor value
  if (soilMoistureValue < 200){
    soilMoistureLevel = "Dry";
  } else if (soilMoistureValue < 600) {
    soilMoistureLevel = "OK";
  } else {
    soilMoistureLevel = "Wet";
  }
  
// Activate DC motor (fan) if temperature is above 40 degrees Celsius
  if (celcius > 40.00) {
    analogWrite(dc_Motor, 225); // Turn on the fan
  } else {
    analogWrite(dc_Motor, 0); // Turn off the fan
  }
  
// Display soil moisture level and temperature on LCD
//lcd.setCursor(0, 0);  Set cursor to the beginning of the LCD
  lcd.print(soilMoistureLevel + " "); // Print soil moisture level
  lcd.print(celcius); // Print temperature
  lcd.write(byte(0)); // Write the custom character for degree symbol
  lcd.print("C");    // Print 'C' for Celsius
  delay(2000);      // Wait for 2 seconds
  lcd.clear();     // Clear the LCD
  
// Wait for a short period before taking new readings
  delay(500);
}
