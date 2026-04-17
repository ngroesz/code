#include <Wire.h>
#include <PVision.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 0

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define CAM_WIDTH 1024
#define CAM_HEIGHT 768


#define SCREEN_ADDRESS 0x3D ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

PVision ircam;
byte result;

struct Target {
  boolean active;
  int x;
  int y;
  int size;
};

Target targets[4];

unsigned long previous_update_millis = 0;
const long update_delay_millis = 5;
int border_x;

void setup()
{
    Serial.begin(9600);
    delay(500);

    border_x = ((float) CAM_HEIGHT / (float) CAM_WIDTH) * SCREEN_WIDTH;

    display.begin(SSD1306_SWITCHCAPVCC, 0x3D);  // initialize with the I2C addr 0x3D (for the 128x64)
    splash_screen();

    ircam.init();

}

void loop()
{
    if (millis() > previous_update_millis + update_delay_millis) {
      update_targets();
      display.clearDisplay();
      draw_border();
      draw_targets();
      display.display();
      previous_update_millis = millis();
    }
}

void draw_border()
{
    display.drawLine(border_x, 0, border_x, display.height() - 1, SSD1306_WHITE);
}

void draw_targets()
{
  for (int i = 0; i < sizeof(targets) / sizeof(targets[0]); ++i) {
    if (targets[i].active) {
      draw_target(targets[i].x, targets[i].y, targets[i].size);
      if (i == 0) {
        write_coordinates(targets[i].x, targets[i].y, targets[i].size);
      }
    }
  }
}

void write_coordinates(int target_x, int target_y, int size) {
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(border_x + 1, 0);
  display.print("1 x: ");
  display.setCursor(border_x + 1, 10);
  display.print(target_x);
  display.setCursor(border_x + 1, 20);
  display.print("1 y: ");
  display.setCursor(border_x + 1, 30);
  display.print(target_y);
  display.setCursor(border_x + 1, 40);
  display.print("size: ");
  display.setCursor(border_x + 1, 50);
  display.print(size);
}

void draw_target(int target_x, int target_y, int size)
{
    int screen_width = SCREEN_WIDTH - (SCREEN_WIDTH - border_x);
    int draw_x = screen_width - (int) ((target_x / (float) CAM_WIDTH) * screen_width);
    int draw_y = (int)((target_y / (float) CAM_HEIGHT) * (float) SCREEN_HEIGHT);
    display.fillRect(draw_x, draw_y, size, size, WHITE);
}

void update_targets()
{
    // this function is probably dumber than it needs to be and I don't even
    // necessarily need to save-off the camera data into a separate data
    // structure. but, also, i think that this implementation is fine.

    result = ircam.read();
    if (result & BLOB1) {
        targets[0].active = true;
        targets[0].x = ircam.Blob1.X;
        targets[0].y = ircam.Blob1.Y;
        targets[0].size = ircam.Blob1.Size;
    } else {
        targets[0].active = false;
    }

    if (result & BLOB1) {
        targets[1].active = true;
        targets[1].x = ircam.Blob1.X;
        targets[1].y = ircam.Blob1.Y;
        targets[1].size = ircam.Blob1.Size;
    } else {
        targets[1].active = false;
    }

    if (result & BLOB1) {
        targets[2].active = true;
        targets[2].x = ircam.Blob1.X;
        targets[2].y = ircam.Blob1.Y;
        targets[2].size = ircam.Blob1.Size;
    } else {
        targets[2].active = false;
    }
    if (result & BLOB1) {
        targets[3].active = true;
        targets[3].x = ircam.Blob1.X;
        targets[3].y = ircam.Blob1.Y;
        targets[3].size = ircam.Blob1.Size;
    } else {
        targets[3].active = false;
    }
}

void splash_screen()
{
  display.clearDisplay();
  display.setTextSize(4);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(35, 0);
  display.println(F("IR"));
  display.setCursor(20, 30);
  display.println(F("CAM"));

  display.display();
  delay(1000);
}
