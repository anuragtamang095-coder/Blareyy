#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

// Screen pin definitions mapped to your XIAO ESP32-C3 routing
#define TFT_SCLK 9   // D9 (SCK / SCL)
#define TFT_MOSI 10  // D10 (SDA / MOSI)
#define TFT_RST  8   // D8 (Reset)
#define TFT_DC   4   // D4 (Data/Command)
#define TFT_CS   5   // D5 (Chip Select)
#define TFT_BL   6   // D6 (Backlight)

// Hardware peripheral pins
#define BTN_1    0   // D0
#define BTN_2    1   // D1
#define BTN_3    2   // D2
#define BTN_4    3   // D3
#define BUZZER   7   // D7

// Software SPI display constructor as specified by BLARE docs
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

void setup() {
  Serial.begin(115200);

  // Configure switch pins with internal pull-up resistors
  pinMode(BTN_1, INPUT_PULLUP);
  pinMode(BTN_2, INPUT_PULLUP);
  pinMode(BTN_3, INPUT_PULLUP);
  pinMode(BTN_4, INPUT_PULLUP);

  // Configure buzzer pin
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);

  // Enable display backlight
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  // Initialize the custom resolution ST7789 display (284x76)
  tft.init(76, 284);
  tft.setRotation(1); // Set landscape orientation (0-3 depending on enclosure orientation)
  tft.fillScreen(ST77XX_BLACK);

  // Render initial display frame
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.setCursor(15, 18);
  tft.println("BLARE v2 READY");

  tft.setTextSize(1);
  tft.setTextColor(ST77XX_CYAN);
  tft.setCursor(15, 48);
  tft.println("Press any button to test...");
}

void loop() {
  // Check SW1 (Pin D0)
  if (digitalRead(BTN_1) == LOW) {
    displayButtonAction("BUTTON 1 (D0)", 1000);
  }

  // Check SW2 (Pin D1)
  if (digitalRead(BTN_2) == LOW) {
    displayButtonAction("BUTTON 2 (D1)", 1500);
  }

  // Check SW3 (Pin D2)
  if (digitalRead(BTN_3) == LOW) {
    displayButtonAction("BUTTON 3 (D2)", 2000);
  }

  // Check SW4 (Pin D3)
  if (digitalRead(BTN_4) == LOW) {
    displayButtonAction("BUTTON 4 (D3)", 2500);
  }

  delay(20);
}

// Helper function to update screen and sound the buzzer on button press
void displayButtonAction(const char* label, int freq) {
  tft.fillRect(0, 42, 284, 34, ST77XX_BLACK);
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_GREEN);
  tft.setCursor(15, 48);
  tft.print("Active: ");
  tft.print(label);

  // Sound buzzer tone briefly
  tone(BUZZER, freq, 80);
  delay(150); // Debounce delay
}