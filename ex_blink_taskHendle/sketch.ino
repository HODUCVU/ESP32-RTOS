// Task handles
TaskHandle_t blinkTaskHandle = NULL;
TaskHandle_t serialTaskHandle = NULL;

// Pin for the LED
const int ledPin = 7; // GPIO2 (built-in LED)

// Delay duration for blinking
const TickType_t blinkDelay = pdMS_TO_TICKS(1000); // 1000 milliseconds

// Blink task function
void blinkTask(void *pvParameters) {
  while (1) {
    digitalWrite(ledPin, HIGH); // Turn LED on
    vTaskDelay(blinkDelay);     // Wait for blinkDelay
    digitalWrite(ledPin, LOW);  // Turn LED off
    vTaskDelay(blinkDelay);     // Wait for blinkDelay
  }
}

// Serial read task function
void serialTask(void *pvParameters) {
  char receivedChar;
  while (1) {
    if (Serial.available()) {
      receivedChar = Serial.read();
      if (receivedChar == 's') {
        // Suspend blink task
        vTaskSuspend(blinkTaskHandle);
      } else if (receivedChar == 'r') {
        // Resume blink task
        vTaskResume(blinkTaskHandle);
      }
    }
    vTaskDelay(pdMS_TO_TICKS(100)); // Short delay to prevent excessive CPU usage
  }
}

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  
  // Initialize LED pin
  pinMode(ledPin, OUTPUT);
  
  // Create tasks
  xTaskCreate(blinkTask, "Blink Task", 2048, NULL, 1, &blinkTaskHandle);
  xTaskCreate(serialTask, "Serial Task", 2048, NULL, 1, &serialTaskHandle);
}

void loop() {
  // Nothing needed here, tasks are handled by FreeRTOS
}
