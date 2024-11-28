#ifndef _ST7305_H_
#define _ST7305_H_

#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_GFX.h"


class ST7305 : public Adafruit_GFX {
  public:
    ST7305(int16_t w, int16_t h, SPIClass *spi, int8_t cs_pin, int8_t dc_pin, 
           int8_t rst_pin, int8_t te_pin = -1);
    
    bool begin();
    void display();
    void clearDisplay();
    void drawPixel(int16_t x, int16_t y, uint16_t color);
    
  private:
    SPIClass *_spi;
    int8_t _cs_pin;
    int8_t _dc_pin;
    int8_t _rst_pin;
    int8_t _te_pin;
    
    uint8_t *buffer;       // 384 * 21 bytes (each byte maps to 8 vertical pixels)
    uint8_t *temp_buffer;  // 192 * 14 * 3 bytes (conversion buffer)
    
    void sendCommand(uint8_t command);
    void sendData(uint8_t data);
    void sendData(uint8_t *data, size_t len);
    void initDisplay();
    void convertBuffer();
};

#endif // _ST7305_H_
