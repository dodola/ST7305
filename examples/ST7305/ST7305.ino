#include <SPI.h>
#include "ST7305.h"

// Pin definitions
#define TFT_CS    SS
#define TFT_DC    8
#define TFT_RST   10
#define TFT_TE    -1  // Set to valid pin if using TE, or -1 if not used

// Display dimensions
#define SCREEN_WIDTH 384  
#define SCREEN_HEIGHT  168

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
  
    display.setRotation(0);
    // Draw some test patterns
    display.clearDisplay();
    
  // Basic shapes demo
    drawShapesDemo();
    delay(3000);
    
    // Text demo
    drawTextDemo();
    delay(3000);
    
    // Graphics demo
    drawGraphicsDemo();
    delay(3000);
    
    // Animation demo
    drawAnimationDemo();
    // Update display
    display.display();
}


void loop() {
    // Main loop animation
    static int counter = 0;
    counter++;
    
    // Create a bouncing ball animation
    static int x = SCREEN_WIDTH/2;
    static int y = SCREEN_HEIGHT/4;
    static int dx = 2, dy = 1;
    
    // Clear previous position
    display.fillCircle(x, y, 5, 0);
    
    // Update position
    x += dx;
    y += dy;
    
    // Bounce off edges
    if (x <= 5 || x >= SCREEN_WIDTH-5) dx = -dx;
    if (y <= 5 || y >= SCREEN_HEIGHT/2-5) dy = -dy;
    
    // Draw new position
    display.fillCircle(x, y, 5, 1);
    display.display();
    
    delay(20); // Control animation speed
}


void drawShapesDemo() {
    display.fillScreen(0);
    
    // Draw rectangles
    display.drawRect(10, 10, 50, 30, 1);
    display.fillRect(70, 10, 50, 30, 1);
    
    // Draw circles
    display.drawCircle(35, 70, 20, 1);
    display.fillCircle(95, 70, 20, 1);
    
    // Draw lines
    display.drawLine(10, 100, 60, 140, 1);
    display.drawLine(60, 100, 10, 140, 1);
    
    // Draw triangle
    display.drawTriangle(10, 160, 60, 160, 35, 200, 1);
    
    // Draw rounded rectangle
    display.drawRoundRect(70, 160, 50, 30, 5, 1);
    
    // Draw vertical lines pattern
    for(int x = 0; x < SCREEN_WIDTH; x += 10) {
        display.drawFastVLine(x, 240, 100, 1);
    }
    
    // Draw horizontal lines pattern
    for(int y = 350; y < SCREEN_HEIGHT; y += 5) {
        display.drawFastHLine(0, y, SCREEN_WIDTH, 1);
    }
    
    display.display();
}

void drawTextDemo() {
    display.fillScreen(0);
    
    // Set text properties
    display.setTextSize(1);
    display.setTextColor(1);
    
    // Draw different text sizes
    display.setCursor(0, 0);
    display.println("ST7305 Display");
    
    display.setTextSize(2);
    display.setCursor(0, 20);
    display.println("168x384");
    
    // Draw rotated text
    display.setTextSize(1);
    for (int i = 0; i < 4; i++) {
        display.setRotation(i);
        display.setCursor(0, 0);
        display.printf("Rotation %d", i);
    }
    
    // Return to original rotation
    display.setRotation(0);
    
    // Draw text at different positions
    for (int y = 100; y < 300; y += 40) {
        display.setCursor(10, y);
        display.printf("Line at Y=%d", y);
    }
    
    display.display();
}

void drawGraphicsDemo() {
    display.fillScreen(0);
    
    // Draw checkerboard pattern
    int blockSize = 16;
    for (int y = 0; y < SCREEN_HEIGHT; y += blockSize) {
        for (int x = 0; x < SCREEN_WIDTH; x += blockSize) {
            if ((x + y) % (blockSize * 2) == 0) {
                display.fillRect(x, y, blockSize, blockSize, 1);
            }
        }
    }
    
    // Draw sine wave
    int centerY = SCREEN_HEIGHT / 4;
    int amplitude = 30;
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        int y = centerY + sin(x * 0.05) * amplitude;
        display.drawPixel(x, y, 1);
    }
    
    // Draw concentric circles
    int centerX = SCREEN_WIDTH / 2;
    centerY = SCREEN_HEIGHT * 3 / 4;
    for (int r = 10; r <= 50; r += 10) {
        display.drawCircle(centerX, centerY, r, 1);
    }
    
    display.display();
}

void drawAnimationDemo() {
    // Expanding circles animation
    int centerX = SCREEN_WIDTH / 2;
    int centerY = SCREEN_HEIGHT / 2;
    int maxRadius = min(SCREEN_WIDTH, SCREEN_HEIGHT/2) / 2;
    
    for (int r = 0; r < maxRadius; r += 2) {
        display.fillScreen(0);
        display.drawCircle(centerX, centerY, r, 1);
        display.display();
        delay(50);
    }
    
    // Scrolling text animation
    display.fillScreen(0);
    display.setTextSize(2);
    String message = "ST7305 - 168x384 Display";
    int textWidth = message.length() * 12; // Approximate width of text
    
    for (int i = SCREEN_WIDTH; i > -textWidth; i--) {
        display.fillScreen(0);
        display.setCursor(i, SCREEN_HEIGHT/2);
        display.print(message);
        display.display();
        delay(20);
    }
    
    // Vertical scanning lines
    for (int x = 0; x < SCREEN_WIDTH; x += 4) {
        display.fillScreen(0);
        display.drawFastVLine(x, 0, SCREEN_HEIGHT, 1);
        if (x > 4) {
            display.drawFastVLine(x-4, 0, SCREEN_HEIGHT, 1);
        }
        display.display();
        delay(20);
    }
}