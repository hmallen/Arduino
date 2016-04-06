/*
   RF24 Receiver Unit
*/

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
#include <Adafruit_NeoPixel.h>
#include <Servo.h>

#define neoPin_eyes A0
#define neoPin_mouth A1
#define pixelCount_eyes 8
#define pixelCount_mouth 9

#define servoPin 5

Adafruit_NeoPixel strip_eyes = Adafruit_NeoPixel(pixelCount_eyes, neoPin_eyes, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_mouth = Adafruit_NeoPixel(pixelCount_mouth, neoPin_mouth, NEO_GRB + NEO_KHZ800);

Servo servo;

const int m_short = 125;
const int m_medium = 225;
const int m_long = 500;

RF24 radio(9, 10);
// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = {0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL};

void setup(void) {
  Serial.begin(57600);
  printf_begin();
  Serial.println();

  radio.begin();

  // optionally, increase the delay between retries & # of retries
  radio.setRetries(15, 15);

  // optionally, reduce the payload size.  seems to
  // improve reliability
  radio.setPayloadSize(8);

  //radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1, pipes[0]);
  radio.startListening();

  radio.printDetails();
  //Serial.println("Hey Gillian, guess what??");
  Serial.println();

  strip_eyes.begin();
  strip_eyes.show();
  strip_mouth.begin();
  strip_mouth.show();

  servo.attach(servoPin);
  servo.write(90);
  delay(500);
}

void loop(void) {
  if (radio.available()) {
    //char message[12];
    unsigned long message;
    bool done = false;
    while (!done) {
      done = radio.read(&message, sizeof(unsigned long));
    }
    Serial.println(message);

    if (message == 1) {
      servo.write(80);
      delay(150);
      servo.write(90);
      delay(150);

      // Arguments: "mouth_color", "eyes_color_outer", "eyes_color_inner"
      droneMonologue("blue", "green", "blue");
    }
  }
}

////////////////////////////////////
//////// NeoPixel Functions ////////
////////////////////////////////////
void droneMonologue(String mouth_color, String eyes_color_outer, String eyes_color_inner) {
  mouthAction("closed", mouth_color);
  delay(2000);
  hello_there_gillian(mouth_color);
  delay(2000);
  looking_lovely_today(mouth_color);
  delay(2000);
  been_watching_you(mouth_color);
  delay(2000);
  mouthHeart(true, true);

  mouthAction("closed", mouth_color);
  eyesAction("open", eyes_color_outer, eyes_color_inner);
  delay(1000);

  for (int x = 0; x < 10; x++) {
    eyesBlink(eyes_color_outer, eyes_color_inner);
    delay(500);
  }
}

//// Dialogue & Other Mouth Output ////
void hello_there_gillian(String color) {
  // Well, hello there, Gillian
  mouthAction("open", color);  // Well
  delay(m_medium);
  mouthAction("closed", color);
  delay(m_medium);
  mouthAction("open", color);  // He-
  delay(m_short);
  mouthAction("closed", color);
  delay(m_medium);
  mouthAction("open", color);  // -llo
  delay(m_medium);
  mouthAction("closed", color);
  delay(m_medium);
  mouthAction("open", color);  // there
  delay(m_long);
  mouthAction("closed", color);
  delay(m_medium);
  mouthAction("open", color);  // Gi-
  delay(m_short);
  mouthAction("closed", color);
  delay(m_short);
  mouthAction("open", color);  // -lli-
  delay(m_short);
  mouthAction("closed", color);
  delay(m_short);
  mouthAction("open", color);  // -an
  delay(m_long);
  mouthAction("closed", color);
}

void looking_lovely_today(String color) {
  // You're looking quite lovely today (my dear)
  mouthAction("open" , color);  // You're
  delay(m_medium);
  mouthAction("closed", color);
  delay(m_medium);
  mouthAction("open" , color);  // loo-
  delay(m_short);
  mouthAction("closed", color);
  delay(m_short);
  mouthAction("open" , color);  // -king
  delay(m_medium);
  mouthAction("closed", color);
  delay(m_medium);
  mouthAction("open" , color);  // quite
  delay(m_medium);
  mouthAction("closed", color);
  delay(m_medium);
  mouthAction("open" , color);  // lov-
  delay(m_short);
  mouthAction("closed", color);
  delay(m_short);
  mouthAction("open" , color);  // -ely
  delay(m_medium);
  mouthAction("closed", color);
  delay(m_medium);
  mouthAction("open" , color);  // to-
  delay(m_short);
  mouthAction("closed", color);
  delay(m_short);
  mouthAction("open" , color);  // -day
  delay(m_medium);
  mouthAction("closed", color);
  delay(m_medium);
  mouthAction("open" , color);  // my
  delay(m_medium);
  mouthAction("closed", color);
  delay(m_medium);
  mouthAction("open" , color);  // dear
  delay(m_long);
  mouthAction("closed", color);
}

void been_watching_you(String color) {
  // You should know...I've been watching you
  mouthAction("open" , color);  // You
  delay(m_short);
  mouthAction("closed", color);
  delay(m_short);
  mouthAction("open" , color);  // should
  delay(m_medium);
  mouthAction("closed", color);
  delay(m_medium);
  mouthAction("open" , color);  // know
  delay(m_long);
  mouthAction("closed", color); // ...
  delay(1000);
  mouthAction("open" , color);  // I've
  delay(m_medium);
  mouthAction("closed", color);
  delay(m_medium);
  mouthAction("open" , color);  // been
  delay(m_long);
  mouthAction("closed", color); // ...
  delay(1000);
  mouthAction("open" , color);  // wat-
  delay(m_short);
  mouthAction("closed", color);
  delay(m_short);
  mouthAction("open" , color);  // -ching
  delay(m_medium);
  mouthAction("closed", color);
  delay(m_medium);
  mouthAction("open" , color);  // you
  delay(m_long);
  mouthAction("closed", color);
}

void mouthHeart(boolean fade, boolean beat) {
  if (fade == true) {
    for (int x = 0; x < 256; x++) {
      strip_mouth.setPixelColor(0, x, 0 , 0);
      strip_mouth.setPixelColor(1, 0, 0, 0);
      strip_mouth.setPixelColor(2, x, 0 , 0);
      strip_mouth.setPixelColor(3, x, 0 , 0);
      strip_mouth.setPixelColor(4, x, 0 , 0);
      strip_mouth.setPixelColor(5, x, 0 , 0);
      strip_mouth.setPixelColor(6, 0, 0, 0);
      strip_mouth.setPixelColor(7, x, 0 , 0);
      strip_mouth.setPixelColor(8, 0, 0, 0);

      strip_mouth.show();
      delay(10);
    }
    delay(1000);
  }

  else {
    uint32_t heartColor = colorPicker("mouth", "red");
    strip_mouth.setPixelColor(0, heartColor);
    strip_mouth.setPixelColor(1, 0, 0, 0);
    strip_mouth.setPixelColor(2, heartColor);
    strip_mouth.setPixelColor(3, heartColor);
    strip_mouth.setPixelColor(4, heartColor);
    strip_mouth.setPixelColor(5, heartColor);
    strip_mouth.setPixelColor(6, 0, 0, 0);
    strip_mouth.setPixelColor(7, heartColor);
    strip_mouth.setPixelColor(8, 0, 0, 0);

    strip_mouth.show();
  }

  if (beat == true) {
    for (int x = 0; x < 6; x++) {
      strip_mouth.setPixelColor(0, 0, 0, 0);
      strip_mouth.setPixelColor(1, 0, 0, 0);
      strip_mouth.setPixelColor(2, 0, 0, 0);
      strip_mouth.setPixelColor(3, 0, 0, 0);
      strip_mouth.setPixelColor(4, 0, 0, 0);
      strip_mouth.setPixelColor(5, 0, 0, 0);
      strip_mouth.setPixelColor(6, 0, 0, 0);
      strip_mouth.setPixelColor(7, 0, 0, 0);
      strip_mouth.setPixelColor(8, 0, 0, 0);
      strip_mouth.show();

      delay(100);

      strip_mouth.setPixelColor(0, 255, 0, 0);
      strip_mouth.setPixelColor(1, 0, 0, 0);
      strip_mouth.setPixelColor(2, 255, 0, 0);
      strip_mouth.setPixelColor(3, 255, 0, 0);
      strip_mouth.setPixelColor(4, 255, 0, 0);
      strip_mouth.setPixelColor(5, 255, 0, 0);
      strip_mouth.setPixelColor(6, 0, 0, 0);
      strip_mouth.setPixelColor(7, 255, 0, 0);
      strip_mouth.setPixelColor(8, 0, 0, 0);
      strip_mouth.show();

      delay(200);

      strip_mouth.setPixelColor(0, 0, 0, 0);
      strip_mouth.setPixelColor(1, 0, 0, 0);
      strip_mouth.setPixelColor(2, 0, 0, 0);
      strip_mouth.setPixelColor(3, 0, 0, 0);
      strip_mouth.setPixelColor(4, 0, 0, 0);
      strip_mouth.setPixelColor(5, 0, 0, 0);
      strip_mouth.setPixelColor(6, 0, 0, 0);
      strip_mouth.setPixelColor(7, 0, 0, 0);
      strip_mouth.setPixelColor(8, 0, 0, 0);
      strip_mouth.show();

      delay(100);

      strip_mouth.setPixelColor(0, 255, 0, 0);
      strip_mouth.setPixelColor(1, 0, 0, 0);
      strip_mouth.setPixelColor(2, 255, 0, 0);
      strip_mouth.setPixelColor(3, 255, 0, 0);
      strip_mouth.setPixelColor(4, 255, 0, 0);
      strip_mouth.setPixelColor(5, 255, 0, 0);
      strip_mouth.setPixelColor(6, 0, 0, 0);
      strip_mouth.setPixelColor(7, 255, 0, 0);
      strip_mouth.setPixelColor(8, 0, 0, 0);
      strip_mouth.show();

      delay(750);
    }
  }

  if (fade == true) {
    for (int x = 255; x > -1; x--) {
      strip_mouth.setPixelColor(0, x, 0 , 0);
      strip_mouth.setPixelColor(1, 0, 0, 0);
      strip_mouth.setPixelColor(2, x, 0 , 0);
      strip_mouth.setPixelColor(3, x, 0 , 0);
      strip_mouth.setPixelColor(4, x, 0 , 0);
      strip_mouth.setPixelColor(5, x, 0 , 0);
      strip_mouth.setPixelColor(6, 0, 0, 0);
      strip_mouth.setPixelColor(7, x, 0 , 0);
      strip_mouth.setPixelColor(8, 0, 0, 0);

      strip_mouth.show();
      delay(10);
    }
    delay(1000);
  }
}

//// Mouth Functions ////
void mouthAction(String state, String color) {
  uint32_t mouthColor = colorPicker("mouth", color);

  if (state == "open") {
    strip_mouth.setPixelColor(0, mouthColor);
    strip_mouth.setPixelColor(1, mouthColor);
    strip_mouth.setPixelColor(2, mouthColor);
    strip_mouth.setPixelColor(3, mouthColor);
    strip_mouth.setPixelColor(4, 0, 0, 0);
    strip_mouth.setPixelColor(5, mouthColor);
    strip_mouth.setPixelColor(6, mouthColor);
    strip_mouth.setPixelColor(7, mouthColor);
    strip_mouth.setPixelColor(8, mouthColor);

    strip_mouth.show();
  }

  else if (state == "closed") {
    strip_mouth.setPixelColor(0, 0, 0, 0);
    strip_mouth.setPixelColor(1, 0, 0, 0);
    strip_mouth.setPixelColor(2, 0, 0, 0);
    strip_mouth.setPixelColor(3, mouthColor);
    strip_mouth.setPixelColor(4, mouthColor);
    strip_mouth.setPixelColor(5, mouthColor);
    strip_mouth.setPixelColor(6, mouthColor);
    strip_mouth.setPixelColor(7, mouthColor);
    strip_mouth.setPixelColor(8, mouthColor);

    strip_mouth.show();
  }

  else Serial.println("Invalid mouth state selection.");
}

//// Eyes Output ////
void eyesBlink(String colorOuter, String colorInner) {
  eyesAction("closed", colorOuter, colorInner);
  delay(100);
  eyesAction("open", colorOuter, colorInner);
}

//// Eyes Functions ////
void eyesAction(String state, String colorOuter, String colorInner) {
  uint32_t eyesColorOuter = colorPicker("eyes", colorOuter);
  uint32_t eyesColorInner = colorPicker("eyes", colorInner);

  if (state == "open") {
    strip_eyes.setPixelColor(0, eyesColorOuter);
    strip_eyes.setPixelColor(1, eyesColorInner);
    strip_eyes.setPixelColor(2, eyesColorOuter);
    strip_eyes.setPixelColor(3, 0, 0, 0);
    strip_eyes.setPixelColor(4, 0, 0, 0);
    strip_eyes.setPixelColor(5, eyesColorOuter);
    strip_eyes.setPixelColor(6, eyesColorInner);
    strip_eyes.setPixelColor(7, eyesColorOuter);

    strip_eyes.show();
  }

  else if (state == "closed") {
    strip_eyes.setPixelColor(0, eyesColorOuter);
    strip_eyes.setPixelColor(1, eyesColorOuter);
    strip_eyes.setPixelColor(2, eyesColorOuter);
    strip_eyes.setPixelColor(3, 0, 0, 0);
    strip_eyes.setPixelColor(4, 0, 0, 0);
    strip_eyes.setPixelColor(5, eyesColorOuter);
    strip_eyes.setPixelColor(6, eyesColorOuter);
    strip_eyes.setPixelColor(7, eyesColorOuter);

    strip_eyes.show();
  }

  else Serial.println("Invalid eyes state selection.");
}

//// Color Picker (uint32_t variable storage) ////
uint32_t colorPicker(String strip, String color) {
  if (strip == "eyes") {
    uint32_t eyes_color;

    if (color == "red") eyes_color = strip_eyes.Color(255, 0, 0);
    else if (color == "green") eyes_color = strip_eyes.Color(0, 255, 0);
    else if (color == "blue") eyes_color = strip_eyes.Color(0, 0, 255);
    else if (color == "yellow") eyes_color = strip_eyes.Color(255, 255, 0);
    else if (color == "cyan") eyes_color = strip_eyes.Color(0, 255, 255);
    else if (color == "magenta") eyes_color = strip_eyes.Color(255, 0, 255);
    else if (color == "off") eyes_color = strip_eyes.Color(0, 0, 0);

    return eyes_color;
  }

  else if (strip == "mouth") {
    uint32_t mouth_color;

    if (color == "red") mouth_color = strip_mouth.Color(255, 0, 0);
    else if (color == "green") mouth_color = strip_mouth.Color(0, 255, 0);
    else if (color == "blue") mouth_color = strip_mouth.Color(0, 0, 255);
    else if (color == "yellow") mouth_color = strip_mouth.Color(255, 255, 0);
    else if (color == "cyan") mouth_color = strip_mouth.Color(0, 255, 255);
    else if (color == "magenta") mouth_color = strip_mouth.Color(255, 0, 255);
    else if (color == "off") mouth_color = strip_mouth.Color(0, 0, 0);

    return mouth_color;
  }

  else {
    Serial.println("Invalid color selection.");

    return 0;
  }
}
