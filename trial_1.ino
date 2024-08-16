// Pin definitions
const int PWM_PIN = 9;    // PWM pin connected to the Cytron motor driver
const int DIR_PIN = 8;    // Direction pin connected to the Cytron motor driver

// Variables
int pwmValue = 0;
bool isRunning = true;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Set pin modes
  pinMode(PWM_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  
  // Set initial direction (forward)
  digitalWrite(DIR_PIN, HIGH);
  
  Serial.println("Press any key to stop the motor.");
}

void loop() {
  if (isRunning) {
    // Gradually increase PWM from 0 to 255
    for (pwmValue = 0; pwmValue <= 255; pwmValue++) {
      analogWrite(PWM_PIN, pwmValue);
      Serial.print("PWM Value: ");
      Serial.println(pwmValue);
      delay(200);  // Adjust this delay to change the speed of PWM increase
      if (pwmValue==255){
          for(pwmValue=255;pwmValue>=0;pwmValue--){
            analogWrite(PWM_PIN,pwmValue);
            Serial.print("PWM values ");
            Serial.println(pwmValue);
            delay(200);
          }
      }
      // Check for keyboard interrupt
      if (Serial.available() > 0) {
        stopMotor();
        break;
      }
    }
    
    // Keep running at full speed until interrupt
    while (isRunning) {
      if (Serial.available() > 0) {
        stopMotor();
      }
    }
  }
}

void stopMotor() {
  analogWrite(PWM_PIN, 0);
  pwmValue = 0;
  isRunning = false;
  Serial.println("Motor stopped.");
}