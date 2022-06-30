#include "essentials.hpp"
#include "start.hpp"
#include "ui.hpp"

int start(Adafruit_TFTLCD &tft, char* version_number) {
    // tft.fillScreen(0x0000);
    tft.fillScreen(color_primary);
    tft.setCursor(50,50);
    tft.setTextColor(0xffff);
    tft.setTextSize(3);
    tft.setFont(&FreeMonoBold9pt7b);
    tft.print("AMBRELL");

    tft.setCursor(80,80);
    tft.setTextColor(0xffff);
    tft.setTextSize(1);
    tft.print("SOFT START BOARD");

    tft.setCursor(120,100);
    tft.setTextColor(0xffff);
    tft.setTextSize(1);
    tft.print(version_number);

    tft.setCursor(120,200);
    tft.setTextColor(0xE7E2);
    tft.setTextSize(1);
    tft.print("WARNING");

    tft.setCursor(90,220);
    // tft.setTextColor(0xffff);
    tft.setTextSize(1);
    // tft.setFont(&FreeMono9pt7b);
    tft.print("HIGH VOLTAGE!");
    // tft.setCursor(50,240);
    // tft.print("before proceeding.");

    tft.drawRoundRect(80, 261, 160, 40, 8, 0xffff);
    tft.setCursor(130,285);
    tft.setTextColor(0xffff);
    tft.setTextSize(1);
    // tft.setFont(&FreeMono9pt7b);
    tft.print("START");


    // tft.fillRect(0,380,320,100,0x0000);

    tft.setCursor(0,430);
    tft.setTextColor(0x1584);
    tft.setTextSize(1);
    tft.print("Microart Services INC 2022");

    /* debug mode */
    // tft.fillRoundRect(220, 440, 100, 40, 8, 0x632C);
    // tft.setCursor(247,463);
    // tft.setTextColor(0xCE59);
    // tft.setTextSize(1);
    // tft.print("DEBUG");

    return touch(tft, 80, 240, 261, 301, 220, 320, 440, 480);
}