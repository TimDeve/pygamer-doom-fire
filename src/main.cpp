#include <Adafruit_Arcada.h>

Adafruit_Arcada arcada;
extern Adafruit_SPIFlash Arcada_QSPI_Flash;

GFXcanvas16 *canvas;

int width, height;

bool flip;

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

  width = arcada.display->width();
  height = arcada.display->height();
  if (!arcada.createFrameBuffer(width, height))
  {
    arcada.haltBox("Failed to allocate framebuffer");
  }
  canvas = arcada.getCanvas();
}

int16_t x = 10;

void loop()
{
  x++;

  if (x > 100)
  {
    x = 10;
  }

  canvas->fillScreen(ARCADA_BLACK);

  canvas->drawPixel(60, x - 3, 0xFFFF);
  canvas->drawPixel(61, x - 2, 0xFFFF);
  canvas->drawPixel(62, x - 1, 0xFFFF);
  canvas->drawPixel(63, x, 0xFFFF);
  canvas->drawPixel(64, x + 1, 0xFFFF);
  canvas->drawPixel(65, x + 2, 0xFFFF);
  canvas->drawPixel(66, x + 3, 0xFFFF);

  arcada.blitFrameBuffer(0, 0);
}
