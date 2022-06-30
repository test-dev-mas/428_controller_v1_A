#include "essentials.hpp"
#include "end.hpp"
#include "ui.hpp"

void end(Adafruit_TFTLCD &tft) {
    // tft.fillScreen(0x0000);
    tft.fillScreen(color_primary);
    tft.setCursor(80,150);
    tft.setTextColor(0xffff);
    tft.setTextSize(1);
    // tft.setFont(&FreeMono9pt7b);
    tft.print("All tests passed.");

    tft.fillRoundRect(80, 261, 160, 40, 8, 0x4239);
    tft.setCursor(130,285);
    tft.setTextColor(0xffff);
    tft.setTextSize(1);
    // tft.setFont(&FreeMono9pt7b);
    tft.print("RESET");

    touch(tft, 80, 240, 261, 301);
}