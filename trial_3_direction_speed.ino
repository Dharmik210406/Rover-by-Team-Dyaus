// Pin definitions
const int PWM_PIN = 9;    // PWM pin connected to the Cytron motor driver
const int DIR_PIN = 8;    // Direction pin connected to the Cytron motor driver

// Variables
int pwmValue = 0;
bool isClockwise = true;

void setup() {
  Serial.begin(9600);
  pinMode(PWM_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  printInstructions();  
}

void loop() {
  if (Serial.available() >=2) {
    char direction = Serial.read();
    char speed = Serial.read();
    
    if (direction == 'c' || direction == 'w') {
      isClockwise = (direction == 'c');
      digitalWrite(DIR_PIN, isClockwise ? HIGH : LOW);
      
      switch (speed) {
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
        default:
          Serial.println("Invalid speed. Please try again.");
          printInstructions();
          return;
      }
      
      analogWrite(PWM_PIN, pwmValue);
      printStatus();
    }
    else if (direction == 's') {
      stopMotor();
    }
    else {
      Serial.println("Invalid input. Please try again.");
      printInstructions();
    }
  }
}

void printInstructions() {
  Serial.println("\nEnter a command to control the motor:");
  Serial.println("c1: Clockwise 50 PWM    w1: Anticlockwise 50 PWM");
  Serial.println("c2: Clockwise 100 PWM   w2: Anticlockwise 100 PWM");
  Serial.println("c3: Clockwise 125 PWM   w3: Anticlockwise 125 PWM");
  Serial.println("c4: Clockwise 150 PWM   w4: Anticlockwise 150 PWM");
  Serial.println("s: Stop motor");
}

void printStatus() {
  Serial.print("Motor running ");
  Serial.print(isClockwise ? "clockwise" : "anticlockwise");
  Serial.print(" at PWM value: ");
  Serial.println(pwmValue);
}

void stopMotor() {
  pwmValue = 0;
  analogWrite(PWM_PIN, pwmValue);
  Serial.println("Motor stopped.");
}