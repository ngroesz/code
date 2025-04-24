// Example of using the PVision library for interaction with the Pixart sensor on a WiiMote
// This work was derived from Kako's excellent Japanese website
// http://www.kako.com/neta/2007-001/2007-001.html

// Steve Hobley 2009 - www.stephenhobley.com

#include <Wire.h>
#include <PVision.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 0

#define SCREEN_WIDTH 126
#define SCREEN_HEIGHT 62
#define CAM_WIDTH 1024
#define CAM_HEIGHT 768

Adafruit_SSD1306 display(OLED_RESET);
PVision ircam;
byte result;

int blob_1_x, blob_1_y, blob_1_size;
int blob_2_x, blob_2_y, blob_2_size;
int blob_3_x, blob_3_y, blob_3_size;
int blob_4_x, blob_4_y, blob_4_size;

const int led_pin = 13;
int led_state = LOW;
unsigned long previous_millis = 0;
const long interval = 500;

void draw_blob(int x, int y, int size)
{
    int blob_x = SCREEN_WIDTH - int(x / (CAM_WIDTH / SCREEN_WIDTH)) - int(size / 2);
    int blob_y = int(y / (CAM_HEIGHT / SCREEN_HEIGHT)) - int(size / 2);
    display.fillRect(blob_x, blob_y, size, size, WHITE);
}

//void blank_blob(int x, int y, int size)
//{
//    int blob_x = int(x / (1024 / 126)) - int(size / 2);
//    int blob_y = int(y / (768 / 62)) - int(size / 2);
//    display.fillRect(blob_x, blob_y, size, size, BLACK);
//}

void clear_display()
{
    display.clearDisplay();
    display.display();
}

//void blank_blobs()
//{
//    blank_blob(blob_1_x, blob_1_y, blob_1_size);
//    blank_blob(blob_2_x, blob_2_y, blob_2_size);
//    blank_blob(blob_3_x, blob_3_y, blob_3_size);
//    blank_blob(blob_4_x, blob_4_y, blob_4_size);
//}

void draw_blobs()
{
    result = ircam.read();
    if (result & BLOB1) {
        blob_1_x = ircam.Blob1.X;
        blob_1_y = ircam.Blob1.Y;
        blob_1_size = ircam.Blob1.Size;
        draw_blob(blob_1_x, blob_1_y, blob_1_size);
    }

    if (result & BLOB2) {
        blob_2_x = ircam.Blob2.X;
        blob_2_y = ircam.Blob2.Y;
        blob_2_size = ircam.Blob2.Size;
        draw_blob(blob_2_x, blob_2_y, blob_2_size);
    }

    if (result & BLOB3) {
        blob_3_x = ircam.Blob3.X;
        blob_3_y = ircam.Blob3.Y;
        blob_3_size = ircam.Blob3.Size;
        draw_blob(blob_3_x, blob_3_y, blob_3_size);
    }

    if (result & BLOB4) {
        blob_4_x = ircam.Blob4.X;
        blob_4_y = ircam.Blob4.Y;
        blob_4_size = ircam.Blob4.Size;
        draw_blob(blob_4_x, blob_4_y, blob_4_size);
    }
}


void setup()
{
    pinMode(led_pin, OUTPUT);
    digitalWrite(led_pin, HIGH);
    delay(500);
    digitalWrite(led_pin, LOW);
    delay(500);
    digitalWrite(led_pin, HIGH);
    delay(500);
    digitalWrite(led_pin, LOW);

    ircam.init();

    digitalWrite(led_pin, HIGH);
    delay(1000);
    digitalWrite(led_pin, LOW);
    delay(1000);
    digitalWrite(led_pin, HIGH);
    delay(1000);
    digitalWrite(led_pin, LOW);


    display.begin(SSD1306_SWITCHCAPVCC, 0x3D);  // initialize with the I2C addr 0x3D (for the 128x64)
    display.clearDisplay();
    display.display();

    for (int i = 1; i<=1024; i += 100) {
        display.clearDisplay();
        draw_blob(i, 300, 10);
        display.display();
        delay(100);
    }
    display.clearDisplay();
}

void loop()
{
    unsigned long current_millis = millis();

    display.clearDisplay();
    //blank_blobs();
    draw_blobs();
    display.display();

    if (current_millis - previous_millis >= interval) {
        previous_millis = current_millis;
        if (led_state == LOW) {
          led_state = HIGH;
        } else {
          led_state = LOW;
        }
        digitalWrite(led_pin, led_state);
    }
}
