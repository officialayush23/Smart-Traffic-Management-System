#include <TM1637Display.h>

// Define the pins for the traffic lights
#define red3 9
#define green3 5
#define yellow3 6

// Define the pins for the IR sensors
#define ir1 7
#define ir2 8

// Define the pins for the TM1637 display
#define CLK 2
#define DIO 3

// Initialize the TM1637 display
TM1637Display display(CLK, DIO);

void setup() {
  // Set the traffic light pins as outputs
  pinMode(red3, OUTPUT);
  pinMode(green3, OUTPUT);
  pinMode(yellow3, OUTPUT);

  // Set the IR sensor pins as inputs
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);

  // Initialize the display with brightness level 5
  display.setBrightness(7);

  // Start with the red light on
  digitalWrite(red3, HIGH);
  digitalWrite(green3, LOW);
  digitalWrite(yellow3, LOW);

  // Start serial communication for debugging
  Serial.begin(9600);
  Serial.println("System initialized. Red light is ON.");
}

void loop() {
  // Read the IR sensors
  bool vehicledetected1 = digitalRead(ir1) == 0;
  bool vehicledetected2 = digitalRead(ir2) == 0;

  // Check if both sensors detect vehicles
  if (vehicledetected1 && vehicledetected2) {
    Serial.println("Both sensors detect vehicles. Displaying custom message.");
     // Display a custom message on the 7-segment display
    uint8_t data[] {
    SEG_F | SEG_E | SEG_D ,
    SEG_A | SEG_F| SEG_G| SEG_E | SEG_D , 
    SEG_A | SEG_F| SEG_G| SEG_E,
    SEG_F | SEG_A | SEG_E,
                     
    };
     display.setSegments(data);
     delay(10000);
     display.clear();

  

    
    digitalWrite(red3,HIGH);

    delay(100);
    
   
  } 
  // Check if only ir1 detects a vehicle
  else if (vehicledetected1) {
    Serial.println("Sensor 1 detects a vehicle. Switching to Lane 3.");
    digitalWrite(red3,LOW);
    digitalWrite(yellow3,HIGH);
    delay(1000);
    digitalWrite(yellow3,LOW);
    digitalWrite(green3,HIGH);
    delay(3000);
    digitalWrite(green3,LOW);
    digitalWrite(red3,HIGH);
    delay(100);
  }
}

