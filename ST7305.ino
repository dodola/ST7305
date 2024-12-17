#include <SPI.h>
#include "ST7305.h"

// Pin definitions
#define TFT_CS    SS
#define TFT_DC    8
#define TFT_RST   10
#define TFT_TE    -1  // Set to valid pin if using TE, or -1 if not used

// Display dimensions
#define SCREEN_WIDTH   168
#define SCREEN_HEIGHT  384

// Create display instance
ST7305 display(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, TFT_CS, TFT_DC, TFT_RST, TFT_TE);

void setup() {
    Serial.begin(115200);
    Serial.println("ST7305 Test");

    // Initialize SPI
    SPI.begin();
    
    // Initialize display
    if (!display.begin()) {
        Serial.println("Failed to initialize display!");
        while (1);
    }
  
    display.setRotation(1);
    // Draw some test patterns
    display.clearDisplay();
    
    // Draw a border
    display.drawRect(0, 0, display.width(), display.height(), 1);
    
    // Draw some text
    display.setTextSize(2);
    display.setTextColor(1);
    display.setCursor(10, 10);
    display.println("Hello World!");
    
    // Draw some shapes
    display.drawRect(10, 50, 60, 40, 1);
    display.fillRect(100, 50, 60, 40, 1);
    display.drawCircle(200, 70, 20, 1);
    display.fillCircle(280, 70, 20, 1);
    display.drawRoundRect(10, 200, 30, 50, 30, 1);
    
    
    // Update display
    display.display();
}

void loop() {
    // Your code here
    delay(1000);
}
