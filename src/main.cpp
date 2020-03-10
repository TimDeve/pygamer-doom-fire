#include <Adafruit_Arcada.h>

Adafruit_Arcada arcada;
extern Adafruit_SPIFlash Arcada_QSPI_Flash;

uint8_t lastButtons = 255;

void setup()
{
  Serial.println("Hello PyGamer");
  if (!arcada.arcadaBegin())
  {
    Serial.print("Failed to start Arcada");
    while (true)
      ;
  }

  arcada.displayBegin();
  arcada.display->fillScreen(ARCADA_BLACK);
  arcada.setBacklight(255);

  arcada.pixels.setPixelColor(0, 0xFFFFFFFF);
  arcada.pixels.setPixelColor(1, 0xFF0000);
  arcada.pixels.setPixelColor(2, 0x00FF00);
  arcada.pixels.setPixelColor(3, 0x0000FF);
  arcada.pixels.setPixelColor(4, 0xFFFFFFFF);
  arcada.pixels.show();
}

void loop()
{
  delay(16);

  uint8_t buttons = arcada.readButtons();

  if (lastButtons != buttons)
  {
    arcada.display->fillScreen(ARCADA_BLACK);

    arcada.display->setCursor(0, 0);

    arcada.display->println("Hello World!");

    if (buttons & ARCADA_BUTTONMASK_A)
    {
      arcada.display->println("Button A");
    }
    if (buttons & ARCADA_BUTTONMASK_B)
    {
      arcada.display->println("Button B");
    }
    if (buttons & ARCADA_BUTTONMASK_SELECT)
    {
      arcada.display->println("Select");
    }
    if (buttons & ARCADA_BUTTONMASK_START)
    {
      arcada.display->println("Start");
    }
    if (buttons & ARCADA_BUTTONMASK_UP)
    {
      arcada.display->println("Up");
    }
    if (buttons & ARCADA_BUTTONMASK_RIGHT)
    {
      arcada.display->println("Right");
    }
    if (buttons & ARCADA_BUTTONMASK_DOWN)
    {
      arcada.display->println("Down");
    }
    if (buttons & ARCADA_BUTTONMASK_LEFT)
    {
      arcada.display->println("Left");
    }
  }

  lastButtons = buttons;
}
