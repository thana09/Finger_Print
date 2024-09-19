#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

WiFiMulti WiFiMulti;

void setup()
{
    Serial.begin(115200);
    delay(10);

    // We start by connecting to a WiFi network
    WiFiMulti.addAP("SSID", "password");

    Serial.println();
    Serial.println();
    Serial.print("Waiting for WiFi... ");

    while(WiFiMulti.run() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    delay(500);
}


void loop()
{
      if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;

        int val=analogRead(A0);
        float voltage=val*0.0048828125;
        
        String url = "https://script.google.com/macros/s/AKfycbw4CssykiDqyoHSWY9KiabM7Q3_DD8l9OAf54Qtsw6o2Yi-y8GU_hKM3rPR1CucUsGFDA/exec?sensor=S1&val="+String(voltage);
        Serial.println("Making a request");
        http.begin(url.c_str()); //Specify the URL and certificate
        http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
        int httpCode = http.GET();
        String payload;
        
        if (httpCode > 0) { //Check for the returning code
          payload = http.getString();
          Serial.println(httpCode);
          Serial.println(payload);
        }
        else {
          Serial.println("Error on HTTP request");
        }
        http.end();
      }


    Serial.println("Waiting 5 seconds before restarting...");
    delay(5000);
}
