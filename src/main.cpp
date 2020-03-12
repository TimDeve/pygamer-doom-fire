#include <Adafruit_Arcada.h>

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 128

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

uint8_t fire[SCREEN_WIDTH * SCREEN_HEIGHT] = {0};

bool isLightOn = false;

int wind = 2;

void moreWind()
{
  if (wind < 5)
  {
    wind++;
  }
}

void lessWind()
{
  if (wind > 1)
  {
    wind--;
  }
}

void blink()
{
  if (isLightOn)
  {
    isLightOn = false;
    arcada.pixels.setPixelColor(2, 0x000000);
  }
  else
  {
    isLightOn = true;
    arcada.pixels.setPixelColor(2, 0x110000);
  }
  arcada.pixels.show();
}

void seedBottomFireRow()
{
  for (int i = 0; i < SCREEN_WIDTH; i++)
  {
    fire[(SCREEN_WIDTH) * (SCREEN_HEIGHT - 1) + i] = 36;
  }
}

void seedBottomFireRowLess()
{
  for (int i = 0; i < SCREEN_WIDTH; i++)
  {
    if (random(0, 2))
    {
      fire[(SCREEN_WIDTH) * (SCREEN_HEIGHT - 1) + i] = 30;
    }
    else
    {
      fire[(SCREEN_WIDTH) * (SCREEN_HEIGHT - 1) + i] = 20;
    }
  }
}

void checkButtons()
{
  uint8_t buttons = arcada.readButtons();

  if (buttons & ARCADA_BUTTONMASK_A)
  {
    seedBottomFireRow();
  }
  if (buttons & ARCADA_BUTTONMASK_B)
  {
    seedBottomFireRowLess();
  }
  if (buttons & ARCADA_BUTTONMASK_RIGHT)
  {
    lessWind();
  }
  if (buttons & ARCADA_BUTTONMASK_LEFT)
  {
    moreWind();
  }
}

void renderFire()
{
  for (int x = 0; x < SCREEN_WIDTH; x++)
  {
    for (int y = 1; y < SCREEN_HEIGHT; y++)
    {
      int randY = random(0, 2);
      int randX = random(0, wind);

      int color = fire[(y * SCREEN_WIDTH + x)] - (randY & 1);
      int index = (y * SCREEN_WIDTH + x) - randX - SCREEN_WIDTH;
      fire[index < 0 ? 0 : index] = color < 0 ? 0 : color;

      canvas->drawPixel(x, y, colors[fire[y * SCREEN_WIDTH + x]]);
    }
  }

  arcada.blitFrameBuffer(0, 0);
}

void initArcada()
{
  if (!arcada.arcadaBegin())
  {
    Serial.print("Failed to start Arcada");
    while (true)
      ;
  }
}

void initDisplay()
{
  arcada.displayBegin();
  arcada.display->fillScreen(colors[0]);
  arcada.setBacklight(255);
}

void initCanvas()
{
  if (!arcada.createFrameBuffer(SCREEN_WIDTH, SCREEN_HEIGHT))
  {
    arcada.haltBox("Failed to allocate framebuffer");
  }
  canvas = arcada.getCanvas();
}

void setup()
{
  initArcada();

  initDisplay();

  initCanvas();

  seedBottomFireRow();

  randomSeed(analogRead(0));
}

void loop()
{
  blink();

  checkButtons();

  renderFire();
}
