#pragma once
#include <Arduino.h>
#include <Wire.h>

class SSD1306 {
public:
    SSD1306(uint8_t addr = 0x3C) : _addr(addr) {}

    void begin();
    void clear();
    void display();

    void setCursor(uint8_t x, uint8_t y) { _x = x; _y = y; }
    void print(const char* str);
    void print(int num);
    void drawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
    void drawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h);

    static const uint8_t WIDTH = 128;
    static const uint8_t HEIGHT = 64;

private:
    uint8_t _addr, _x = 0, _y = 0;
    uint8_t _buf[128 * 64 / 8];

    void cmd(uint8_t c);
    void data(uint8_t d);
    void drawPixel(int16_t x, int16_t y, bool on);
    void drawChar(char c);
};
