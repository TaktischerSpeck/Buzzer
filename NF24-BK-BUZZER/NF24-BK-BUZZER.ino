#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
#include "NF24BK.h"
#include <Wire.h>
#include "Adafruit_NeoPixel.h"

RF24 radio(9, 10); //#1

#define BUTTON_PIN 4 //#2

int PIN = 3; //#3
int NUMPIXELS = 16; //#4

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

byte buzzerId = 1; //#5

void setup() {
  Serial.begin(57600);

  printf_begin();
  printf("*** SWITCH (%2d) ***\n\r", buzzerId);

  initRadio(radio);
  setPipes(radio, pipes[0], pipes[1]);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(PIN , OUTPUT);
  
  light(true);
  delay(500);
  light(false);
  delay(500);

  radio.startListening();
}

long lastPress = 0;

void loop(void) {

  if (isButtonPressed() && millis() - lastPress > 100) {
    sendButtonPressed();
    radio.startListening();
    lastPress = millis();
  }

  if (radio.available()) {
    radio.read(&bk_msg, sizeof(bk_msg));
    printf("Received (DEVICE/CMD): (%2d,%2d) !\n\r", bk_msg.device, bk_msg.cmd);
    if (bk_msg.device == buzzerId) {
      switch (bk_msg.cmd) {
        case BK_LIGHT_ON:
            for (int i = 0; i <= NUMPIXELS; i++) {
                pixels.setPixelColor(i, pixels.Color(255,0,0)); //#6
            }
            pixels.show();
          break;
        case BK_LIGHT_OFF:
            for (int i = 0; i < NUMPIXELS; i++) {
                pixels.setPixelColor(i, pixels.Color(255,55,0)); //#7
            }
            pixels.show();
          break;
      }
    }
  }
}

boolean isButtonPressed() {
  return digitalRead(BUTTON_PIN) == LOW;
}

void light(boolean on) {

    if (on){
        for (int i = 0; i <= NUMPIXELS; i++) {
            pixels.setPixelColor(i, pixels.Color(255,0,0)); //#8
        }
        pixels.show();
    }

    if (!on){
        for (int i = 0; i <= NUMPIXELS; i++) {
            pixels.setPixelColor(i, pixels.Color(0,0,0)); //#9
        }
        pixels.show();
    } 
}

boolean sendButtonPressed() {

  Serial.print("Send Button press ...");
  radio.stopListening();
  Serial.print("Stop listening ...");

  bk_msg.device = buzzerId;
  bk_msg.cmd = BK_BTN_PRESSED;

  bool send = radio.write(&bk_msg, sizeof(bk_msg));
  Serial.print("Send: ");
  Serial.println(send);

  return send;
}
