/*
 * IRremoteESP8266: IRServer - demonstrates sending IR codes controlled from a webserver
 * Version 0.2 June, 2017
 * Copyright 2015 Mark Szabo
 *
 * An IR LED circuit *MUST* be connected to the ESP8266 on a pin
 * as specified by IR_LED below.
 *
 * TL;DR: The IR LED needs to be driven by a transistor for a good result.
 *
 * Suggested circuit:
 *     https://github.com/markszabo/IRremoteESP8266/wiki#ir-sending
 *
 * Common mistakes & tips:
 *   * Don't just connect the IR LED directly to the pin, it won't
 *     have enough current to drive the IR LED effectively.
 *   * Make sure you have the IR LED polarity correct.
 *     See: https://learn.sparkfun.com/tutorials/polarity/diode-and-led-polarity
 *   * Typical digital camera/phones can be used to see if the IR LED is flashed.
 *     Replace the IR LED with a normal LED if you don't have a digital camera
 *     when debugging.
 *   * Avoid using the following pins unless you really know what you are doing:
 *     * Pin 0/D3: Can interfere with the boot/program mode & support circuits.
 *     * Pin 1/TX/TXD0: Any serial transmissions from the ESP8266 will interfere.
 *     * Pin 3/RX/RXD0: Any serial transmissions to the ESP8266 will interfere.
 *   * ESP-01 modules are tricky. We suggest you use a module with more GPIOs
 *     for your first time. e.g. ESP-12 etc.
 */
#ifndef UNIT_TEST
#include <Arduino.h>
#endif
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <WiFiClient.h>

const char* ssid = "NVRAM WARNING";
const char* password = "Lift80Lift";
MDNSResponder mdns;

ESP8266WebServer server(80);

#define IR_LED 12  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(IR_LED);  // Set the GPIO to be used to sending the message.

void handleRoot() {
  server.send(200, "text/html",
              "<html>" \
                "<head><title>IR</title></head>" \
                "<body>" \
                  "<h1>Yamaha" \
                      "</h1>" \

                  "<input style=\"width:200px;height:200px;font-size:48;\" type=\"button\" onclick=\"location.href='ir?code=0x7E817E81';\" value=\"On\" />" \
                  "<input style=\"width:200px;height:200px;font-size:48;\" type=\"button\" onclick=\"location.href='ir?code=0x7E81FE01';\" value=\"Off\" /><br />" \
                  "<input style=\"width:200px;height:200px;font-size:48;\" type=\"button\" onclick=\"location.href='ir?code=0x5EA158A7';\" value=\"vol+\" />" \
                  "<input style=\"width:200px;height:200px;font-size:48;\" type=\"button\" onclick=\"location.href='ir?code=0x5EA1D827';\" value=\"vol-\" /><br />" \
                  "<input style=\"width:200px;height:200px;font-size:48;\" type=\"button\" onclick=\"location.href='ir?code=0x5EA138C7';\" value=\"Mute\" />" \ 
                "</body>" \
              "</html>");
}

void handleIr() {
  for (uint8_t i = 0; i < server.args(); i++) {
    if (server.argName(i) == "code") {
      uint32_t code = strtoul(server.arg(i).c_str(), NULL, 16);
#if SEND_NEC
      irsend.sendNEC(code, 32);
#endif  // SEND_NEC
    }
  }
  handleRoot();
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++)
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  server.send(404, "text/plain", message);
}

void setup(void) {
  irsend.begin();

  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP().toString());

  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/ir", handleIr);

  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}
