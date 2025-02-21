
// Define the pins for the IR sensors
const int sensor1 = 3;
const int sensor2 = 2;
const int sensor3 = 4;
const int sensor4 = 5;

// Define the pins for the traffic lights
const int green1 = 9;
const int yellow1 = 10;
const int red1 = 11;
const int green2 = 6;
const int yellow2 = 7;
const int red2 = 8;

void setup() {
  pinMode(green1, OUTPUT);
  pinMode(yellow1, OUTPUT);
  pinMode(red1, OUTPUT);
  pinMode(green2, OUTPUT);
  pinMode(yellow2, OUTPUT);
  pinMode(red2, OUTPUT);
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  Serial.begin(9600);

  // Default state: all red
  digitalWrite(red1, HIGH);
  digitalWrite(red2, HIGH);
}

void loop() {
  bool vehicleDetected1 = digitalRead(sensor1) == 0;
  bool vehicleDetected2 = digitalRead(sensor2) == 0;
  bool vehicleDetected3 = digitalRead(sensor3) == 0;
  bool vehicleDetected4 = digitalRead(sensor4) == 0;

  if (vehicleDetected1 && vehicleDetected2 && vehicleDetected3 && vehicleDetected4) {
    // If all sensors detect vehicles, prioritize Lane 1 first, then Lane 2
    Serial.println("All sensors detect vehicles. Prioritizing Lane 1 first.");
    switchToLane1_8(); 
    delay(100);// Lane 1 gets extended green light
    switchToLane2_8(); // Lane 2 gets extended green light
  } else if (vehicleDetected1 && vehicleDetected2) {
    // If both sensors on Lane 1 detect vehicles, prioritize Lane 1
    Serial.println("Lane 1 sensors detect vehicles. Prioritizing Lane 1.");
    switchToLane1_8(); 
    // Lane 1 gets extended green light
  } else if (vehicleDetected3 && vehicleDetected4) {
    // If both sensors on Lane 2 detect vehicles, prioritize Lane 2
    Serial.println("Lane 2 sensors detect vehicles. Prioritizing Lane 2.");
    switchToLane2_8(); // Lane 2 gets extended green light
  } else if (vehicleDetected1) {
    // If only sensor1 detects a vehicle, give Lane 1 standard green light
    Serial.println("Sensor 1 detects a vehicle. Switching to Lane 1.");
    switchToLane1();
  } else if (vehicleDetected3) {
    // If only sensor3 detects a vehicle, give Lane 2 standard green light
    Serial.println("Sensor 3 detects a vehicle. Switching to Lane 2.");
    switchToLane2();
  } else if (vehicleDetected3 && vehicleDetected4 && vehicleDetected1) {
    // If both sensors on Lane 2 detect vehicles, prioritize Lane 2
    Serial.println("Lane 2 sensors detect vehicles. Prioritizing Lane 2.");
    switchToLane2_8(); // Lane 2 gets extended green light
  } else if (vehicleDetected1 && vehicleDetected2 && vehicleDetected3) {
    // If both sensors on Lane 2 detect vehicles, prioritize Lane 2
    Serial.println("Lane 2 sensors detect vehicles. Prioritizing Lane 2.");
    switchToLane1_8(); // Lane 2 gets extended green light
  } 


}

void switchToLane1() {
  Serial.println("Lane 1 Green");
  setLights(HIGH, LOW, LOW, LOW, LOW, HIGH);
  delay(5000);
  transitionToRed();
}

void switchToLane1_8() {
  Serial.println("Lane 1 Green (Extended)");
  setLights(HIGH, LOW, LOW, LOW, LOW, HIGH);
  delay(8000);
  transitionToRed();
}

void switchToLane2() {
  Serial.println("Lane 2 Green");
  setLights(LOW, LOW, HIGH, HIGH, LOW, LOW);
  delay(5000);
  transitionToRed();
}

void switchToLane2_8() {
  Serial.println("Lane 2 Green (Extended)");
  setLights(LOW, LOW, HIGH, HIGH, LOW, LOW);
  delay(8000);
  transitionToRed();
}

void transitionToRed() {
  setLights(LOW, HIGH, LOW, LOW, HIGH, LOW);
  delay(2000);
  digitalWrite(yellow1, LOW);
  digitalWrite(yellow2, LOW);
  digitalWrite(red1, HIGH);
  digitalWrite(red2, HIGH);
}

void setLights(bool g1, bool y1, bool r1, bool g2, bool y2, bool r2) {
  digitalWrite(green1, g1);
  digitalWrite(yellow1, y1);
  digitalWrite(red1, r1);
  digitalWrite(green2, g2);
  digitalWrite(yellow2, y2);
  digitalWrite(red2, r2);
}