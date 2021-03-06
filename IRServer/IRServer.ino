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

const char* ssid = "Tenda_FBA7C0";
const char* password = "121314150";
MDNSResponder mdns;

//uint16_t rawData[227];

ESP8266WebServer server(80);

#define IR_LED 12  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(IR_LED);  // Set the GPIO to be used to sending the message.

void handleRoot() {
  server.send(200, "text/html",
              "<html>" \
                "<head><title>IR</title></head>" \
                "<body>" \
                  "<h1>Sakura" \
                      "</h1>" \

                  "<input style=\"width:200px;height:200px;font-size:48;\" type=\"button\" onclick=\"location.href='ir?code=1';\" value=\"On\" />" \
                  "<input style=\"width:200px;height:200px;font-size:48;\" type=\"button\" onclick=\"location.href='ir?code=2';\" value=\"Off\" />" \
                  "<input style=\"width:200px;height:200px;font-size:48;\" type=\"button\" onclick=\"location.href='ir?code=3';\" value=\"Sw On\" />" \
                  "<input style=\"width:200px;height:200px;font-size:48;\" type=\"button\" onclick=\"location.href='ir?code=4';\" value=\"Sw Off\" /><br />" \

                  "<input style=\"width:200px;height:200px;font-size:48;\" type=\"button\" onclick=\"location.href='ir?code=5';\" value=\"Cool\" />" \
                  "<input style=\"width:200px;height:200px;font-size:48;\" type=\"button\" onclick=\"location.href='ir?code=6';\" value=\"Low\" />" \
                  "<input style=\"width:200px;height:200px;font-size:48;\" type=\"button\" onclick=\"location.href='ir?code=7';\" value=\"Mid\" />" \
                  "<input style=\"width:200px;height:200px;font-size:48;\" type=\"button\" onclick=\"location.href='ir?code=8';\" value=\"High\" /><br />" \
                  
                  "<input style=\"width:200px;height:200px;font-size:48;\" type=\"button\" onclick=\"location.href='ir?code=22';\" value=\"22\" />" \
                  "<input style=\"width:200px;height:200px;font-size:48;\" type=\"button\" onclick=\"location.href='ir?code=23';\" value=\"23\" />" \
                  "<input style=\"width:200px;height:200px;font-size:48;\" type=\"button\" onclick=\"location.href='ir?code=24';\" value=\"24\" />" \
                  "<input style=\"width:200px;height:200px;font-size:48;\" type=\"button\" onclick=\"location.href='ir?code=25';\" value=\"25\" />" \
                  
                "</body>" \
              "</html>");
}

void handleIr() {
  for (uint8_t i = 0; i < server.args(); i++) {
    if (server.argName(i) == "code") {
      uint32_t code = strtoul(server.arg(i).c_str(), NULL, 10);
//#if SEND_NEC
//      irsend.sendNEC(code, 32);
//#endif  // SEND_NEC

      if(code == 1){
          uint16_t rawData[227] = {3076, 1630,  548, 1134,  540, 1142,  544, 362,  514, 400,  514, 354,  514, 1142,  544, 362,  514, 386,  518, 1134,  540, 1142,  544, 352,  514, 1178,  544, 362,  514, 352,  518, 1134,  540, 1176,  544, 354,  514, 1134,  544, 1142,  544, 396,  514, 354,  512, 1142,  546, 360,  514, 392,  514, 1142,  544, 362,  514, 362,  512, 400,  514, 362,  514, 366,  514, 360,  514, 396,  518, 362,  514, 362,  518, 360,  514, 396,  518, 362,  514, 362,  514, 366,  514, 396,  514, 366,  514, 354,  512, 1144,  544, 396,  514, 354,  518, 1168,  514, 362,  518, 430,  514, 1160,  518, 1168,  514, 366,  514, 396,  516, 364,  512, 362,  514, 362,  518, 396,  514, 362,  518, 362,  512, 354,  514, 1208,  514, 360,  514, 366,  514, 362,  514, 400,  514, 354,  514, 1168,  518, 352,  514, 1198,  514, 1160,  514, 1174,  512, 362,  514, 400,  514, 362,  514, 366,  512, 362,  514, 400,  514, 362,  514, 362,  518, 362,  514, 396,  518, 362,  514, 362,  514, 366,  514, 396,  514, 366,  514, 362,  514, 366,  514, 396,  514, 366,  514, 362,  514, 362,  514, 400,  514, 362,  514, 366,  514, 362,  514, 400,  514, 362,  514, 366,  514, 362,  514, 400,  514, 362,  514, 362,  514, 366,  514, 396,  514, 356,  514, 1160,  514, 1164,  514, 1194,  514, 1164,  514, 1160,  518, 1168,  514, 392,  514};  // UNKNOWN 6E94C72F
          irsend.sendRaw(rawData, 227, 38);
      }
        if(code == 2){
          uint16_t rawData[227] = {3080, 1626,  552, 1130,  544, 1138,  548, 332,  544, 396,  518, 322,  544, 1138,  548, 332,  544, 362,  544, 1130,  544, 1142,  544, 322,  544, 1176,  544, 358,  518, 328,  544, 1130,  544, 1176,  544, 352,  514, 1134,  544, 1138,  548, 366,  544, 326,  544, 1138,  544, 336,  544, 358,  544, 1142,  544, 332,  544, 336,  544, 366,  544, 336,  544, 332,  544, 360,  514, 370,  544, 362,  514, 336,  544, 362,  514, 370,  544, 362,  514, 360,  518, 358,  518, 370,  544, 358,  518, 362,  518, 358,  518, 396,  492, 374,  518, 1168,  492, 384,  518, 430,  492, 1156,  544, 1168,  492, 388,  488, 422,  492, 388,  488, 388,  492, 388,  488, 422,  492, 388,  488, 388,  488, 388,  492, 422,  488, 388,  492, 388,  488, 388,  492, 422,  488, 378,  492, 1194,  488, 378,  492, 1220,  488, 1190,  486, 1194,  492, 388,  488, 422,  492, 388,  488, 388,  488, 392,  488, 422,  488, 392,  488, 388,  488, 390,  488, 422,  488, 392,  488, 388,  488, 392,  488, 422,  488, 392,  488, 386,  514, 362,  492, 422,  514, 362,  492, 388,  514, 362,  514, 400,  512, 362,  512, 366,  514, 362,  514, 400,  514, 362,  514, 366,  514, 362,  514, 400,  514, 362,  512, 366,  514, 360,  514, 400,  514, 352,  514, 1172,  514, 362,  514, 392,  514, 1160,  518, 1160,  514, 1168,  518, 388,  514};  // UNKNOWN 39908069
          irsend.sendRaw(rawData, 227, 38);
      }
        if(code == 3){
          uint16_t rawData[227] = {3078, 1634,  544, 1160,  514, 1168,  514, 366,  514, 396,  514, 358,  514, 1168,  514, 366,  514, 386,  514, 1164,  514, 1168,  514, 358,  514, 1202,  514, 366,  514, 352,  514, 1164,  514, 1204,  514, 356,  514, 1160,  514, 1172,  514, 396,  514, 352,  518, 1168,  514, 362,  514, 392,  514, 1170,  512, 366,  514, 362,  514, 400,  514, 362,  514, 362,  518, 362,  514, 396,  514, 366,  514, 362,  514, 366,  514, 396,  514, 366,  514, 362,  514, 362,  514, 400,  514, 362,  514, 358,  514, 1168,  514, 400,  514, 352,  514, 1172,  514, 362,  514, 434,  514, 1160,  514, 1172,  514, 362,  514, 400,  514, 362,  514, 366,  510, 366,  514, 396,  514, 366,  512, 362,  512, 358,  510, 1208,  514, 366,  514, 360,  514, 362,  514, 400,  514, 362,  514, 366,  514, 354,  514, 1198,  514, 1160,  514, 1172,  514, 362,  514, 400,  510, 366,  514, 362,  514, 366,  514, 396,  514, 366,  510, 366,  514, 366,  510, 400,  514, 362,  512, 366,  514, 362,  514, 400,  510, 366,  514, 366,  510, 366,  514, 396,  514, 366,  514, 362,  514, 366,  510, 400,  514, 362,  514, 366,  514, 362,  514, 400,  510, 366,  514, 366,  510, 366,  514, 400,  510, 366,  514, 362,  514, 366,  510, 400,  514, 366,  510, 358,  512, 1160,  514, 1198,  514, 1164,  510, 1164,  514, 1174,  510, 392,  514};  // UNKNOWN C86A016D
          irsend.sendRaw(rawData, 227, 38);
      }
        if(code == 4){
          uint16_t rawData[227] = {3076, 1630,  544, 1160,  518, 1170,  514, 362,  514, 400,  514, 354,  514, 1168,  518, 362,  514, 388,  518, 1160,  514, 1170,  514, 356,  514, 1202,  514, 366,  514, 352,  514, 1164,  514, 1204,  514, 358,  514, 1160,  514, 1168,  514, 400,  514, 352,  514, 1174,  514, 362,  514, 392,  514, 1170,  514, 362,  514, 366,  512, 396,  514, 366,  514, 362,  514, 362,  514, 400,  514, 362,  514, 366,  514, 362,  514, 396,  514, 366,  514, 362,  514, 366,  510, 400,  514, 362,  514, 358,  514, 1168,  514, 400,  514, 352,  514, 1168,  514, 366,  514, 434,  510, 1164,  514, 1170,  512, 366,  514, 396,  514, 366,  514, 362,  514, 362,  514, 400,  514, 362,  514, 366,  514, 352,  514, 1208,  514, 362,  514, 362,  514, 366,  514, 396,  514, 366,  514, 362,  514, 362,  514, 400,  514, 362,  514, 366,  510, 366,  514, 396,  512, 366,  514, 362,  514, 362,  514, 400,  514, 362,  514, 366,  510, 366,  514, 400,  510, 366,  514, 362,  514, 366,  510, 400,  514, 362,  514, 366,  510, 366,  514, 402,  508, 366,  514, 362,  514, 366,  510, 400,  514, 362,  514, 366,  488, 388,  514, 400,  510, 366,  514, 362,  514, 366,  510, 400,  514, 366,  508, 366,  488, 388,  514, 400,  510, 366,  514, 354,  514, 1174,  488, 422,  514, 366,  510, 358,  514, 1168,  514, 392,  514};  // UNKNOWN 3634BC29
          irsend.sendRaw(rawData, 227, 38);
      }

        if(code == 5){
          uint16_t rawData[227] = {3076, 1630,  544, 1134,  544, 1142,  540, 362,  518, 396,  514, 352,  518, 1142,  540, 362,  518, 388,  514, 1134,  544, 1142,  540, 352,  518, 1178,  540, 362,  518, 352,  514, 1134,  544, 1178,  538, 354,  518, 1130,  544, 1144,  542, 396,  514, 352,  518, 1142,  538, 362,  518, 388,  514, 1142,  544, 362,  514, 362,  518, 396,  514, 362,  518, 362,  514, 362,  514, 400,  514, 362,  514, 366,  514, 362,  514, 396,  518, 362,  512, 362,  518, 362,  514, 396,  518, 362,  514, 352,  514, 1172,  514, 396,  514, 358,  512, 1142,  540, 366,  514, 430,  518, 1134,  540, 1142,  544, 362,  514, 396,  514, 366,  514, 362,  514, 362,  518, 396,  514, 362,  514, 366,  514, 352,  514, 1206,  514, 362,  514, 362,  518, 362,  514, 396,  514, 358,  512, 1144,  540, 358,  514, 1168,  540, 1164,  514, 1142,  540, 366,  512, 396,  514, 362,  518, 362,  514, 362,  514, 400,  514, 362,  514, 366,  514, 362,  514, 400,  514, 362,  514, 362,  514, 366,  514, 396,  514, 366,  514, 362,  514, 362,  518, 396,  514, 362,  518, 362,  514, 362,  514, 400,  514, 362,  514, 366,  514, 362,  514, 396,  518, 362,  512, 362,  514, 366,  514, 396,  514, 366,  514, 362,  512, 362,  518, 396,  514, 354,  514, 1164,  514, 1160,  518, 1194,  514, 1164,  514, 1160,  514, 1172,  514, 388,  514};  // UNKNOWN 6E94C72F
          irsend.sendRaw(rawData, 227, 38);
      }
        if(code == 6){
          uint16_t rawData[227] = {3082, 1630,  544, 1134,  540, 1142,  544, 362,  514, 400,  514, 352,  514, 1144,  542, 362,  512, 392,  514, 1134,  540, 1142,  544, 354,  512, 1178,  544, 362,  514, 358,  514, 1134,  538, 1178,  544, 352,  514, 1134,  544, 1142,  540, 400,  514, 352,  514, 1142,  544, 362,  514, 392,  512, 1142,  540, 366,  514, 362,  514, 400,  512, 362,  514, 366,  514, 362,  514, 396,  518, 362,  514, 362,  514, 366,  514, 396,  514, 366,  514, 362,  514, 362,  518, 396,  514, 362,  518, 354,  514, 1168,  518, 396,  514, 352,  514, 1172,  514, 362,  514, 434,  514, 1160,  518, 1168,  514, 362,  518, 396,  514, 362,  514, 366,  514, 362,  514, 400,  514, 362,  514, 362,  518, 354,  514, 1202,  518, 362,  514, 362,  518, 362,  514, 398,  512, 358,  514, 1168,  514, 352,  518, 1194,  514, 1160,  518, 1168,  514, 366,  514, 396,  514, 366,  514, 362,  514, 362,  518, 396,  514, 362,  514, 366,  514, 362,  514, 400,  514, 362,  514, 362,  518, 362,  514, 396,  518, 362,  514, 362,  514, 366,  514, 396,  514, 366,  514, 360,  514, 362,  518, 396,  514, 362,  512, 366,  514, 362,  514, 400,  514, 362,  514, 366,  514, 362,  514, 400,  514, 362,  514, 362,  514, 366,  514, 396,  514, 358,  514, 1160,  514, 1160,  518, 1194,  514, 1164,  514, 1160,  514, 1172,  514, 388,  514};  // UNKNOWN 6E94C72F
          irsend.sendRaw(rawData, 227, 38);
      }
        if(code == 7){
          uint16_t rawData[227] = {3078, 1630,  548, 1130,  544, 1142,  544, 362,  514, 396,  518, 348,  518, 1168,  514, 362,  518, 388,  514, 1134,  544, 1138,  544, 356,  516, 1174,  544, 362,  518, 350,  518, 1134,  538, 1178,  544, 326,  540, 1134,  544, 1168,  514, 370,  544, 354,  514, 1144,  544, 362,  514, 362,  540, 1142,  544, 336,  540, 362,  518, 396,  514, 362,  518, 358,  518, 336,  540, 396,  518, 362,  514, 362,  514, 366,  514, 396,  514, 362,  518, 362,  514, 362,  518, 396,  514, 362,  514, 354,  518, 1168,  514, 396,  518, 354,  514, 1142,  544, 362,  514, 430,  518, 1160,  514, 1168,  518, 360,  514, 396,  518, 356,  518, 362,  514, 362,  518, 396,  512, 362,  514, 362,  518, 354,  514, 1178,  544, 362,  514, 362,  514, 362,  518, 388,  514, 1160,  518, 1168,  514, 354,  514, 1198,  514, 1160,  514, 1168,  518, 362,  514, 400,  514, 362,  514, 362,  514, 366,  514, 396,  514, 366,  514, 362,  514, 362,  492, 422,  514, 362,  514, 366,  514, 362,  514, 400,  514, 362,  514, 362,  514, 366,  514, 396,  514, 366,  514, 362,  514, 362,  514, 400,  514, 362,  514, 366,  514, 362,  514, 400,  514, 362,  514, 362,  514, 366,  514, 396,  514, 366,  514, 362,  514, 362,  514, 392,  514, 1160,  514, 1160,  518, 1160,  514, 1194,  518, 1160,  514, 1160,  518, 1170,  514, 388,  518};  // UNKNOWN 61E995CF
          irsend.sendRaw(rawData, 227, 38);
      }
        if(code == 8){
          uint16_t rawData[227] = {3076, 1630,  544, 1134,  544, 1142,  540, 336,  544, 370,  540, 328,  540, 1142,  544, 336,  540, 392,  514, 1134,  540, 1142,  544, 328,  540, 1178,  544, 362,  514, 358,  514, 1134,  540, 1178,  544, 328,  540, 1134,  544, 1144,  540, 370,  544, 328,  538, 1144,  544, 336,  540, 362,  540, 1142,  544, 360,  514, 366,  514, 396,  514, 366,  514, 336,  540, 336,  544, 370,  540, 362,  514, 366,  514, 362,  514, 400,  514, 336,  540, 362,  518, 362,  514, 396,  518, 362,  514, 352,  514, 1142,  544, 396,  514, 358,  514, 1168,  514, 362,  518, 430,  514, 1164,  514, 1168,  514, 366,  514, 396,  514, 362,  518, 362,  514, 362,  514, 400,  514, 362,  514, 366,  514, 352,  514, 1202,  518, 362,  514, 362,  518, 362,  514, 388,  514, 1174,  512, 354,  514, 1164,  514, 1168,  540, 1164,  514, 1142,  540, 366,  514, 396,  514, 366,  514, 362,  514, 362,  518, 396,  514, 362,  518, 362,  514, 360,  514, 400,  514, 362,  514, 366,  514, 362,  514, 400,  514, 362,  514, 362,  514, 366,  514, 396,  514, 366,  514, 362,  514, 366,  512, 396,  514, 362,  518, 362,  514, 362,  514, 400,  514, 362,  514, 366,  514, 362,  514, 400,  514, 362,  514, 362,  514, 366,  514, 388,  514, 1172,  514, 362,  514, 366,  514, 396,  514, 366,  514, 362,  514, 358,  488, 1220,  514};  // UNKNOWN DD1ED62E
          irsend.sendRaw(rawData, 227, 38);
      }
      
        if(code == 22){
          uint16_t rawData[227] = {3080, 1626,  548, 1160,  512, 1174,  514, 362,  514, 400,  514, 354,  514, 1142,  544, 362,  514, 392,  514, 1134,  540, 1142,  544, 354,  514, 1206,  514, 362,  518, 352,  514, 1160,  514, 1208,  514, 352,  514, 1160,  518, 1142,  544, 396,  514, 352,  514, 1168,  518, 362,  514, 392,  514, 1168,  514, 366,  514, 362,  514, 396,  518, 362,  514, 362,  518, 362,  514, 396,  518, 362,  514, 362,  514, 362,  518, 396,  514, 362,  518, 362,  514, 362,  514, 400,  514, 362,  514, 358,  514, 1168,  514, 400,  514, 352,  514, 1168,  518, 362,  514, 436,  514, 1160,  514, 1168,  518, 362,  514, 400,  514, 362,  514, 362,  518, 362,  512, 388,  518, 1168,  514, 360,  518, 352,  514, 1204,  518, 362,  514, 362,  514, 366,  514, 388,  514, 1168,  518, 362,  514, 352,  518, 1194,  514, 1160,  518, 1168,  514, 362,  518, 396,  514, 362,  518, 362,  514, 362,  514, 400,  514, 362,  514, 366,  514, 362,  514, 396,  518, 362,  514, 362,  514, 366,  512, 396,  514, 366,  514, 362,  512, 362,  518, 396,  514, 362,  514, 366,  512, 362,  512, 400,  514, 362,  512, 366,  514, 362,  514, 400,  512, 362,  514, 362,  514, 366,  514, 396,  514, 366,  514, 362,  514, 366,  514, 396,  514, 354,  518, 1160,  514, 1160,  518, 1194,  514, 1164,  514, 1160,  514, 1168,  518, 388,  514};  // UNKNOWN 3A81B38D
          irsend.sendRaw(rawData, 227, 38);
      }
        if(code == 23){
          uint16_t rawData[227] = {3106, 1604,  550, 1128,  570, 1116,  568, 306,  568, 344,  570, 322,  544, 1116,  568, 332,  522, 382,  544, 1104,  574, 1112,  570, 326,  544, 1146,  548, 358,  544, 322,  522, 1128,  570, 1150,  570, 296,  570, 1108,  570, 1112,  548, 392,  544, 322,  522, 1138,  570, 336,  544, 332,  570, 1116,  570, 304,  544, 336,  568, 366,  518, 362,  544, 330,  544, 336,  544, 366,  522, 358,  544, 332,  544, 336,  544, 366,  518, 362,  544, 332,  544, 336,  544, 366,  518, 362,  544, 322,  544, 1142,  544, 366,  518, 352,  544, 1138,  518, 362,  544, 404,  514, 1160,  544, 1144,  544, 332,  544, 370,  518, 356,  544, 336,  512, 362,  544, 370,  518, 358,  544, 332,  518, 352,  544, 1178,  518, 356,  544, 330,  518, 362,  518, 382,  518, 1168,  544, 332,  518, 354,  518, 1190,  518, 1160,  544, 1142,  518, 358,  544, 370,  518, 356,  544, 336,  514, 360,  544, 370,  518, 358,  518, 362,  514, 362,  518, 396,  512, 362,  518, 356,  518, 362,  544, 366,  518, 362,  518, 358,  544, 336,  518, 392,  518, 362,  518, 356,  544, 336,  514, 396,  518, 362,  518, 358,  518, 362,  514, 396,  544, 334,  514, 362,  518, 362,  512, 396,  518, 362,  514, 362,  518, 358,  518, 388,  518, 1168,  514, 352,  518, 1160,  512, 1194,  518, 1160,  518, 1156,  518, 1168,  518, 388,  514};  // UNKNOWN 9B4A5D4D
          irsend.sendRaw(rawData, 227, 38);
      }
        if(code == 24){
          uint16_t rawData[227] = {3106, 1604,  570, 1108,  544, 1138,  570, 336,  544, 340,  570, 328,  518, 1138,  570, 332,  522, 382,  544, 1130,  522, 1138,  570, 322,  518, 1178,  570, 332,  522, 322,  570, 1104,  570, 1152,  570, 324,  544, 1108,  570, 1112,  570, 370,  544, 322,  544, 1116,  570, 332,  544, 336,  544, 1138,  570, 336,  518, 356,  544, 370,  518, 358,  544, 332,  518, 360,  544, 366,  544, 336,  544, 332,  544, 336,  518, 392,  544, 336,  514, 360,  544, 330,  544, 370,  544, 332,  544, 328,  518, 1164,  544, 370,  518, 348,  544, 1142,  518, 356,  544, 404,  518, 1156,  544, 1144,  518, 358,  544, 370,  518, 356,  544, 330,  544, 336,  544, 358,  544, 1134,  544, 1130,  544, 1142,  544, 366,  546, 334,  518, 358,  544, 336,  514, 388,  544, 1142,  540, 336,  544, 324,  544, 1168,  544, 1130,  544, 1142,  544, 330,  544, 370,  544, 330,  544, 336,  514, 362,  518, 396,  514, 362,  518, 358,  544, 336,  518, 392,  544, 336,  518, 358,  544, 336,  514, 396,  518, 362,  540, 336,  518, 358,  544, 370,  518, 358,  544, 336,  514, 362,  544, 370,  540, 336,  518, 356,  544, 336,  514, 396,  544, 336,  512, 362,  518, 362,  514, 396,  518, 362,  540, 336,  518, 358,  518, 396,  514, 362,  518, 354,  538, 1134,  518, 1194,  514, 1160,  544, 1134,  514, 1168,  544, 362,  514};  // UNKNOWN BC0203F
          irsend.sendRaw(rawData, 227, 38);
      }
        if(code == 25){
          uint16_t rawData[227] = {3102, 1608,  544, 1156,  518, 1168,  518, 362,  514, 396,  518, 352,  514, 1168,  518, 362,  514, 388,  518, 1160,  514, 1168,  518, 352,  514, 1204,  518, 362,  514, 352,  518, 1160,  514, 1202,  518, 354,  514, 1160,  518, 1168,  514, 396,  518, 352,  514, 1168,  518, 362,  514, 388,  518, 1168,  514, 362,  518, 362,  514, 396,  518, 362,  514, 362,  518, 362,  514, 396,  518, 362,  514, 362,  514, 366,  514, 396,  514, 360,  518, 362,  514, 362,  518, 396,  514, 362,  518, 352,  514, 1168,  518, 396,  512, 354,  514, 1172,  514, 362,  518, 430,  514, 1160,  518, 1168,  514, 366,  514, 396,  514, 362,  518, 362,  514, 362,  512, 400,  514, 352,  514, 1164,  514, 1168,  518, 396,  514, 366,  514, 362,  512, 362,  518, 388,  514, 1172,  514, 362,  514, 352,  514, 1198,  514, 1164,  514, 1168,  514, 366,  514, 396,  512, 366,  514, 362,  548, 302,  574, 340,  574, 300,  574, 306,  574, 300,  574, 336,  578, 302,  574, 302,  552, 326,  574, 336,  552, 328,  574, 302,  574, 306,  574, 336,  552, 326,  574, 300,  574, 300,  578, 336,  574, 306,  574, 300,  574, 300,  552, 362,  574, 302,  552, 326,  574, 300,  574, 340,  574, 300,  574, 306,  574, 300,  574, 330,  574, 1100,  574, 1108,  578, 292,  574, 1134,  578, 1100,  574, 1100,  578, 1108,  574, 332,  574};  // UNKNOWN 96AB6EDD
          irsend.sendRaw(rawData, 227, 38);
      }
            
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
