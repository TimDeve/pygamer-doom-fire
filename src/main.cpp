#include <Adafruit_Arcada.h>

#define FIRE_WIDTH 100
#define FIRE_HEIGHT 100

Adafruit_Arcada arcada;
extern Adafruit_SPIFlash Arcada_QSPI_Flash;

GFXcanvas16 *canvas;

int width, height;

uint16_t colors[] = {
    0x0841,
    0x2041,
    0x3081,
    0x4881,
    0x58C1,
    0x6901,
    0x7101,
    0x8941,
    0x9981,
    0xAA01,
    0xBA41,
    0xC241,
    0xDA81,
    0xDAA1,
    0xDAA1,
    0xD2E1,
    0xD2E1,
    0xD322,
    0xCB62,
    0xCBA2,
    0xCBE2,
    0xCC23,
    0xC423,
    0xC463,
    0xC4A4,
    0xBCE4,
    0xBCE4,
    0xBD25,
    0xBD25,
    0xBD66,
    0xB566,
    0xB5A6,
    0xB5A7,
    0xCE6D,
    0xDEF3,
    0xEF78,
    0xFFFF};

uint8_t fire[FIRE_WIDTH * FIRE_HEIGHT] = {0};

bool flip = false;

void blink()
{
  if (flip)
  {
    flip = false;
    arcada.pixels.setPixelColor(2, 0x000000);
    arcada.pixels.show();
  }
  else
  {
    flip = true;
    arcada.pixels.setPixelColor(2, 0xFFFFFF);
    arcada.pixels.show();
  }
}

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

  for (int i = 0; i < FIRE_WIDTH; i++)
  {
    fire[(FIRE_HEIGHT) * (FIRE_WIDTH - 1) + i] = 36;
  }

  randomSeed(analogRead(0));
}

void loop()
{
  delay(50);
  canvas->fillScreen(ARCADA_BLACK);

  blink();

  for (int x = 0; x < FIRE_WIDTH; x++)
  {
    for (int y = 1; y < FIRE_HEIGHT; y++)
    {
      int rand = random(0, 3);

      int color = fire[(y * FIRE_WIDTH + x)] - (rand & 1);
      fire[(y * FIRE_WIDTH + x) - FIRE_WIDTH] = color < 0 ? 0 : color;

      canvas->drawPixel(x, y, colors[fire[y * FIRE_WIDTH + 1]]);
    }
  }

  arcada.blitFrameBuffer(0, 0);
}
