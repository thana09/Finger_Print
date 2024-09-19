#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "12345678";           // Your WiFi SSID
const char* password = "24446666677777777";   // Your WiFi Password
const char* googleScriptURL = "https://docs.google.com/spreadsheets/d/1U4ovjle53CXTBqu1pN-sDQoHWnTS3Zu4qlmKFSCU0O8/edit?gid=0#gid=0"; // Web App URL

void setup() {
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  if(WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Your sensor data (replace with actual sensor readings)
    float sensor1 = analogRead(34); // Example analog sensor
    float sensor2 = analogRead(35); // Example analog sensor
    float sensor3 = analogRead(32); // Example analog sensor

    // Create JSON string
    String jsonData = "{\"sensor1\":" + String(sensor1) + ",\"sensor2\":" + String(sensor2) + ",\"sensor3\":" + String(sensor3) + "}";

    http.begin(googleScriptURL);    // Specify destination URL
    http.addHeader("Content-Type", "application/json"); // Specify content-type header

    int httpResponseCode = http.POST(jsonData);

    // Print HTTP response
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end(); // Close connection
  }

  delay(60000); // Send data every 60 seconds
}
function doPost(e) {
  var sheet = SpreadsheetApp.getActiveSpreadsheet().getActiveSheet();
  var data = JSON.parse(e.postData.contents);
  sheet.appendRow([new Date(), data.sensor1, data.sensor2, data.sensor3]);
  return ContentService.createTextOutput('Success');
}
