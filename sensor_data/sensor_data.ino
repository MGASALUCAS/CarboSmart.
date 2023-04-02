#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "YourSSID";
const char* password = "YourPassword";

const char* serverName = "https://f40d-41-222-181-163.eu.ngrok.io";

// Define button pins
#define BUTTON_PIN_1 2
#define BUTTON_PIN_2 3

// Button state variables
bool button1State = false;
bool button2State = false;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  // Connect to Wi-Fi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Set button pins as inputs
  pinMode(BUTTON_PIN_1, INPUT);
  pinMode(BUTTON_PIN_2, INPUT);
}

void loop() {
  // Read button states
  button1State = digitalRead(BUTTON_PIN_1);
  button2State = digitalRead(BUTTON_PIN_2);
  
  // Send API request if button is pressed
  if (button1State == HIGH) {
    sendAPIRequest("ph value is %s ");
  }

  if (button2State == HIGH) {
    sendAPIRequest("ph value is %s");
  }

  delay(100);
}

void sendAPIRequest(String message) {
  // Create HTTP client
  HTTPClient http;
  
  // Set server URL
  String serverURL = serverName + "?message=" + message;
  
  // Send request
  http.begin(serverURL);
  int httpCode = http.GET();
  String payload = http.getString();

  Serial.println("API response: " + payload);
  
  // Close connection
  http.end();
}
