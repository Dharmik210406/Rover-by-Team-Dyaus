// Pin definitions
const int PWM_PIN = 9;    // PWM pin connected to the Cytron motor driver
const int DIR_PIN = 8;    // Direction pin connected to the Cytron motor driver

// Variables
int pwmValue = 0;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Set pin modes
  pinMode(PWM_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  
  // Set initial direction (forward)
  digitalWrite(DIR_PIN, HIGH);
  
  printInstructions();
}

void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read();
    
    switch (input) {
      case '1':
        pwmValue = 50;
        break;
      case '2':
        pwmValue = 100;
        break;
      case '3':
        pwmValue = 125;
        break;
      case '4':
        pwmValue = 150;
        break;
      case 's':
      case 'S':
        pwmValue = 0;
        break;
      default:
        Serial.println("Invalid input. Please try again.");
        printInstructions();
        return;
    }
    
    analogWrite(PWM_PIN, pwmValue);
    
    if (pwmValue > 0) {
      Serial.print("Motor running at PWM value: ");
      Serial.println(pwmValue);
    } else {
      Serial.println("Motor stopped.");
    }
  }
  // Motor continues to run at the last set PWM value
}

void printInstructions() {
  Serial.println("\nEnter a number to control the motor:");
  Serial.println("1: 50 PWM");
  Serial.println("2: 100 PWM");
  Serial.println("3: 125 PWM");
  Serial.println("4: 150 PWM");
  Serial.println("s: Stop motor");
}