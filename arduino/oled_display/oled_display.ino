#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 0
Adafruit_SSD1306 display(OLED_RESET);

void draw_blob(int x, int y)
{
    int blob_x = int(x / (1024 / 126));
    int blob_y = int(y / (768 / 62));
    display.drawRect(blob_x, blob_y, 2, 2, WHITE);
    display.display();
    display.drawRect(blob_x, blob_y, 2, 2, BLACK);
}

void setup()
{
    Serial.begin(9600);

    display.begin(SSD1306_SWITCHCAPVCC, 0x3D);  // initialize with the I2C addr 0x3D (for the 128x64)
    display.clearDisplay();
}

void loop()
{
    for (int i = 1; i<=1024; i += 10) {
        draw_blob(i, 300);
    }
}

